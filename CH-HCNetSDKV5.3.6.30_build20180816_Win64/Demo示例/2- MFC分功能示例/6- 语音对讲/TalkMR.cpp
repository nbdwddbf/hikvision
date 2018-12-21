/*******************************************************
Copyright 2008-2011 Hikvision Digital Technology Co., Ltd. 
文  件：	TalkMR.cpp
开发单位：	杭州海康威视
编  写：	shizhiping
日  期：	2009.5
描  述：	语音转发
修  改：	
********************************************************/

#include "stdafx.h"
#include "Voice.h"
#include "TalkMR.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif





/*************************************************
函数名:    	fDVRVoiceDataCallBack
函数描述:	回调函数，采集DVR发送过来的语音数据
输入参数:   lVoiceComHandle-语音转发句柄
            pRecvDataBuffer-数据缓冲区
            dwBufSize-缓冲区大小
            byAudioFlag-语音数据类型0-本地采集的语音，1-接收到得语音
			pUser-用户数据
输出参数:   		
返回值:	   
*************************************************/
void CALLBACK  fDVRVoiceDataCallBack(LONG  lVoiceComHandle, char  *pRecvDataBuffer, DWORD  dwBufSize, BYTE  byAudioFlag, void  *pUser)
{
	ASSERT(pRecvDataBuffer);
    CTalkMR *pDlgTalkMR = (CTalkMR*)pUser;
    switch(byAudioFlag)
	{
	case 0:
		TRACE("local audio data\n");
		break;
	case 1:
		pDlgTalkMR->PutIntoBuf(pRecvDataBuffer, (int)dwBufSize);
		TRACE("Input data size[%d]\n", dwBufSize);
		break;
	case 2:
		TRACE("audio sending and recving thread exit\n");
		break;
	default:
		break;
	}
}




/*************************************************
函数名:    	DataFromSoundIn
函数描述:	音频采集回调函数
输入参数:   buffer-音频数据缓存
            dwSize-缓存大小
			dwOwner-用户数据
输出参数:   		
返回值:	   
*************************************************/
void CALLBACK DataFromSoundIn(char* buffer, DWORD dwSize, DWORD dwOwner)
{
	ASSERT(dwOwner);
	CTalkMR* p = (CTalkMR*) dwOwner;
	p->SendDataToDVR(buffer, dwSize);
}


////////////// ///////////////////////////////////////////////////////////////
// CTalkMR dialog


CTalkMR::CTalkMR(CWnd* pParent /*=NULL*/)
	: CDialog(CTalkMR::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTalkMR)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bIsTalkMR = FALSE;
	m_bWaveDeal = FALSE;
	m_hFile = NULL;
	m_hExitEvent = NULL;
	m_hHaveRDataRV = NULL;
	
	m_pDecoder = NULL;
	m_pEncoder = NULL;
	
	m_bOpenWavOut = FALSE;
	m_bOpenWavIn = FALSE;
	
	m_dwBufSize = AUDENCSIZE;
	m_dwBufNum = 6;
	//init WAVEFORMATEX
	m_struWaveFormat.cbSize =			sizeof(m_struWaveFormat);
	m_struWaveFormat.nBlockAlign =		CHANNEL * BITS_PER_SAMPLE / 8;
	m_struWaveFormat.nChannels =		CHANNEL;
	m_struWaveFormat.nSamplesPerSec =	SAMPLES_PER_SECOND;
	m_struWaveFormat.wBitsPerSample =	BITS_PER_SAMPLE;
	m_struWaveFormat.nAvgBytesPerSec =	SAMPLES_PER_SECOND * m_struWaveFormat.nBlockAlign;
	m_struWaveFormat.wFormatTag =		WAVE_FORMAT_PCM;
	
	m_pRenderBuf = NULL;
	m_nBufNo = 0;
	m_rIndexRV = 0;
	m_ReceiveIndexRV = 0;
	
	m_bOpenPlayThread = FALSE;
}


void CTalkMR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTalkMR)
	DDX_Control(pDX, IDC_TREE_VOICE_CHAN, m_ctrlTreeChan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTalkMR, CDialog)
	//{{AFX_MSG_MAP(CTalkMR)
	ON_BN_CLICKED(IDC_BUTTON_TALK_MR, OnButtonTalkMr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTalkMR message handlers

BOOL CTalkMR::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_hExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hHaveRDataRV = CreateEvent(NULL, TRUE, FALSE, NULL);
	
	//audio buffer
	m_pRenderBuf = (PBYTE)::VirtualAlloc(NULL, 160*40L, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
	
	//decoder
	m_pDecoder = NET_DVR_InitG722Decoder(BIT_RATE_16000);
	//encoder
	m_pEncoder = NET_DVR_InitG722Encoder();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*************************************************
函数名:    	OnButtonTalkMr
函数描述:	开始/停止语音转发 按钮
输入参数:   
输出参数:   		
返回值:	   
*************************************************/
void CTalkMR::OnButtonTalkMr() 
{
	if(!g_pMainDlg->m_bIsLogin)
	{
		MessageBox("Login fisrt!\n");
		return;
	}

	if(!m_bIsTalkMR)
	{
        StartTalkMR();
		OpenWave();  //打开waveIn Out
	}
	else
	{
        StopTalkMR();
		CloseWave();
	}
}

/*************************************************
函数名:    	StartTalkMR
函数描述:	开始语音转发
输入参数:   
输出参数:   		
返回值:	   
*************************************************/
BOOL CTalkMR::StartTalkMR()
{
	m_vecVoiceMR.clear();
	//依次按选中的通道进行转发
    HTREEITEM ItemRoot = m_ctrlTreeChan.GetRootItem();
	if(ItemRoot == NULL)
		return FALSE;
	
	HTREEITEM ItemChan = m_ctrlTreeChan.GetChildItem(ItemRoot);
	while(ItemChan)
	{
		if(m_ctrlTreeChan.GetCheck(ItemChan))  //channel is selected, add to the vector
		{
			int iChanIndex = m_ctrlTreeChan.GetItemData(ItemChan)%2000;
			LONG hVoiceHandle = NET_DVR_StartVoiceCom_MR_V30(g_pMainDlg->m_DeviceInfo.lLoginID,iChanIndex,fDVRVoiceDataCallBack,(void*)this);  //建立语音转发
			if(hVoiceHandle == -1)
			{
				int err = NET_DVR_GetLastError();
				TRACE("NET_DVR_StartVoiceCom_MR_V30 chan:%d failed,error code %d\n",iChanIndex,err);
				
			}
			else      //添加到数组
			{
				VOICEMR_INFO voiceinfo;
				//voiceinfo.iDeviceIndex = iDevIndex;
				voiceinfo.iChanIndex = iChanIndex;
				voiceinfo.hVoiceHandle = hVoiceHandle;
				m_vecVoiceMR.push_back(voiceinfo);
			}
			
			//ArrayIndex++;
		}
         ItemChan = m_ctrlTreeChan.GetNextSiblingItem(ItemChan);
	}
	
    //没有通道选中，返回
	if(m_vecVoiceMR.empty())
	{
		return FALSE;
	}
    GetDlgItem(IDC_BUTTON_TALK_MR)->SetWindowText("停止转发");
	m_bIsTalkMR = TRUE;
	return TRUE;
}

/*************************************************
函数名:    	StopTalkMR
函数描述:	停止语音转发
输入参数:   
输出参数:   		
返回值:	   
*************************************************/
void CTalkMR::StopTalkMR()
{
	if (m_hExitEvent)
	{
		SetEvent(m_hExitEvent);
	}
	
	for(int i=0; i<m_vecVoiceMR.size(); i++)
	{
		if(m_vecVoiceMR[i].hVoiceHandle >=0)
		{
			NET_DVR_StopVoiceCom(m_vecVoiceMR[i].hVoiceHandle);
		}
	}
    m_vecVoiceMR.clear();
    GetDlgItem(IDC_BUTTON_TALK_MR)->SetWindowText("开始转发");
	m_bIsTalkMR = FALSE;
}

/*************************************************
函数名:    	CreateChannelTree
函数描述:	创建语音通道数
输入参数:   iNum-设备的语音通道数
            ChanStatus-通道状态
输出参数:   		
返回值:	   
*************************************************/
void CTalkMR::CreateChannelTree(int iNum, BYTE *ChanStatus)
{
    m_ctrlTreeChan.DeleteAllItems();
    m_ItemRoot = m_ctrlTreeChan.InsertItem("Device");
	for(int i=0; i<iNum; i++)
	{
		CString ChanName;
		ChanName.Format("Audio %d",i+1);
		HTREEITEM ChanItem = m_ctrlTreeChan.InsertItem(ChanName,m_ItemRoot);
        m_ctrlTreeChan.SetItemData(ChanItem,CHANNELTYPE*1000+i+1);
		//Set Status
	}

	//Expand the tree
    m_ctrlTreeChan.Expand(m_ItemRoot,TVE_EXPAND);
}

/*************************************************
函数名:    	OpenWave
函数描述:	打开音频采集和播放
输入参数:  
输出参数:   		
返回值:	   
*************************************************/
void CTalkMR::OpenWave()
{
	if(!m_bWaveDeal)
	{
		//open wavout
		if (m_SoundOut.OpenSound(m_struWaveFormat, m_dwBufNum, m_dwBufSize, CALLBACK_FUNCTION, 0))
		{	
			if (m_SoundOut.PlaySound())
			{
				m_bOpenWavOut = TRUE;
				//m_SoundOut.SetVolume(0x7fff7fff);
			}
		}
		else
		{
			TRACE("open waveout failed!");
		}

		//open wavin
		m_SoundIn.SetSoundInDataCB(DataFromSoundIn, (DWORD)this); //设置音频采集回调函数
		if (m_SoundIn.Start(&m_struWaveFormat, m_dwBufNum, m_dwBufSize))
		{
			m_bOpenWavIn = TRUE;
		}
		else
		{
			TRACE("open wavein failed!");
		}
		m_bWaveDeal = TRUE;
	}
}

/*************************************************
函数名:    	CloseWave
函数描述:	关闭音频采集和播放
输入参数:  
输出参数:   		
返回值:	   
*************************************************/
void CTalkMR::CloseWave()
{
	if(m_bWaveDeal)
	{
		//close wavout
		if (m_bOpenWavOut)
		{
			m_SoundOut.CloseSound();
			m_bOpenWavOut = FALSE;
		}
		
		//close wavin
		if (m_bOpenWavIn)
		{
			m_SoundIn.Stop();
			m_bOpenWavIn = FALSE;
		}
		m_bWaveDeal = FALSE;
	}
}

/*************************************************
函数名:    	SendDataToDVR
函数描述:	发送语音数据
输入参数:   buf-数据缓存
            dwSize-缓存大小
输出参数:   		
返回值:	   
*************************************************/
BOOL CTalkMR::SendDataToDVR(char *buf, DWORD dwSize)
{
	ASSERT(buf);
    if (!m_bWaveDeal)
	{
		return FALSE;
	}
	//encode 
	if (!NET_DVR_EncodeG722Frame(m_pEncoder, (BYTE*)buf, m_byEncBuf))
	{
		TRACE("NET_DVR_EncodeG722Frame failed\n");
		return FALSE;
	}

	for(int i=0; i<m_vecVoiceMR.size(); i++)
	{
		if(m_vecVoiceMR[i].hVoiceHandle >= 0)
		{
			//转发
			if(!NET_DVR_VoiceComSendData(m_vecVoiceMR[i].hVoiceHandle,(char*)m_byEncBuf,AUDDECSIZE))
			{
				int err = NET_DVR_GetLastError();
				TRACE("NET_DVR_VoiceComSendData falied,err:%d\n",err);
				continue;
			}
		}
	}
	return TRUE;

}


/*********************************************************
  Function:	PutIntoBuf
  Desc:		input the device audio data to buffer for decoding better/对收到的音频数据做缓冲处理
  Input:	lpTemp, voice data buffer;
			Bytes, voice data lenght;
  Output:	none
  Return:	none
**********************************************************/
BOOL CTalkMR::PutIntoBuf(char *lpTemp, int Bytes)
{
	int nTemp = 0;
	int nPacketStart = 0;
	if ((m_ReceiveIndexRV + Bytes) <= AUDIOBUF)
	{
		if (!m_bOpenPlayThread)
		{
			memcpy(m_pRenderBuf+m_ReceiveIndexRV, lpTemp, Bytes);
			m_ReceiveIndexRV += Bytes;
			m_ReceiveIndexRV = m_ReceiveIndexRV % AUDIOBUF;
		}
		else
		{
			if (((m_ReceiveIndexRV + Bytes) >= m_rIndexRV)  
				&& (m_ReceiveIndexRV < m_rIndexRV))
			{   //buffer1 overflow
				TRACE("buffer1 overflow.");
				::SetEvent(m_hHaveRDataRV);
				nPacketStart = (m_rIndexRV - AUDDECSIZE + m_ReceiveIndexRV % AUDDECSIZE);
				if ((nPacketStart + Bytes) <= (DWORD)AUDIOBUF)
				{
					memcpy(m_pRenderBuf + nPacketStart, lpTemp, Bytes);
					m_ReceiveIndexRV = nPacketStart + Bytes;
				}
				else
				{
					nTemp = AUDIOBUF - nPacketStart;
					memcpy(m_pRenderBuf + nPacketStart, lpTemp, nTemp);
					memcpy(m_pRenderBuf, lpTemp + nTemp, Bytes - nTemp);
					m_ReceiveIndexRV = Bytes - nTemp;
				}
			}
			else	
			{
				memcpy(m_pRenderBuf + m_ReceiveIndexRV, lpTemp, Bytes);
				m_ReceiveIndexRV += Bytes;
				m_ReceiveIndexRV = m_ReceiveIndexRV % AUDIOBUF;
			}
		}
	}
	else
	{
		if (m_bOpenPlayThread)
		{
			if ((Bytes >= (m_rIndexRV + AUDIOBUF - m_ReceiveIndexRV))
				|| (m_rIndexRV >= m_ReceiveIndexRV))
			{	//buffer2 overflow
				TRACE("buffer2 overflow");
				::SetEvent(m_hHaveRDataRV);
				if (m_rIndexRV != 0)
				{
					nPacketStart = (m_rIndexRV - AUDDECSIZE + m_ReceiveIndexRV % AUDDECSIZE);
				}
				else
				{
					nPacketStart = (m_rIndexRV + AUDIOBUF - AUDDECSIZE + m_ReceiveIndexRV % AUDDECSIZE);
				}
				if ((nPacketStart + Bytes) <= (DWORD)AUDIOBUF)
				{
					memcpy(m_pRenderBuf + nPacketStart, lpTemp, Bytes);
					m_ReceiveIndexRV = nPacketStart + Bytes;
				}
				else
				{
					nTemp = AUDIOBUF - nPacketStart;
					memcpy(m_pRenderBuf + nPacketStart, lpTemp, nTemp);
					memcpy(m_pRenderBuf, lpTemp + nTemp, Bytes - nTemp);
					m_ReceiveIndexRV = Bytes - nTemp;
				}
			}
			else
			{
				memcpy(m_pRenderBuf + m_ReceiveIndexRV, lpTemp, nTemp = AUDIOBUF - m_ReceiveIndexRV);
				memcpy(m_pRenderBuf, lpTemp + nTemp, Bytes - nTemp);
				m_ReceiveIndexRV = Bytes - nTemp;
			}
		}
	}

	TRACE("number:%d, m_nBufNo:%d\n", (m_ReceiveIndexRV + AUDIOBUF - m_rIndexRV) % (AUDIOBUF), m_nBufNo*AUDDECSIZE);
	if ((((m_ReceiveIndexRV + AUDIOBUF - m_rIndexRV) % (AUDIOBUF)) >= (m_nBufNo * AUDDECSIZE)))
	{
		::SetEvent(m_hHaveRDataRV);
		m_nBufNo = 1;
		if (!m_bOpenPlayThread)
		{
			AfxBeginThread(PlayAudioThread, (LPVOID)this);
			m_bOpenPlayThread = TRUE;
		}
	}

	return TRUE;
}

/*************************************************
函数名:    	PlayAudioThread
函数描述:	音频播放线程
输入参数:   pParam-用户数据
输出参数:   		
返回值:	   
*************************************************/
UINT CTalkMR::PlayAudioThread(LPVOID pParam)
{
	ASSERT(pParam);
	CTalkMR * pClient = (CTalkMR *)pParam;
	try
	{
		pClient->InputAudioData();
	}
	catch (...)
	{
		TRACE("Input data exception\n");
		return 1;
	}
	
	return 0;
}


/*********************************************************
Function:	InputAudioData
Desc:		input the device audio data to decoder and decode/取出音频数据并解码
Input:	none
Output:	none
Return:	none
**********************************************************/
void CTalkMR::InputAudioData()
{
	HANDLE hWaitEvents[2];
	hWaitEvents[0] = m_hExitEvent;
	hWaitEvents[1] = m_hHaveRDataRV;
	
	DWORD dwReadLength = AUDDECSIZE;
	BYTE  lpTemp[AUDDECSIZE * 2] = {0};
	DWORD dwWaitResult = 0;
	int i = 0;
	
	try
	{
		while (1)
		{
			dwWaitResult = WaitForMultipleObjects(2, hWaitEvents, FALSE, INFINITE);
			if (WAIT_OBJECT_0 == dwWaitResult)
			{
				m_bOpenPlayThread = FALSE;
				ResetEvent(m_hExitEvent);
				return ;
			}
			
			if (CopyAudioData(lpTemp, dwReadLength))
			{
				NET_DVR_DecodeG722Frame(m_pDecoder, (BYTE*)lpTemp, m_byDecBuf);
				for (i=0; i<35; i++)
				{
					if (m_SoundOut.InputData((BYTE*)m_byDecBuf, 0))
					{
						break;
					}
					Sleep(1);
				}
			}
		}
		
	}
	catch (...)
	{
		TRACE("InputAudioData exception\n");
		m_bOpenPlayThread = FALSE;
		return ;
	}
	
	m_bOpenPlayThread = FALSE;
	return ;
}


/*********************************************************
Function:	CopyAudioData
Desc:		deal the audio data from device/从接收缓冲区中拷贝数据出来解码
Input:	lpTemp, data buffer; dwReadLength, data length;
Output:	none
Return:	TRUE/FALSE
**********************************************************/
BOOL CTalkMR::CopyAudioData(PBYTE lpTemp, DWORD dwReadLength)
{
	DWORD dwTemp;
	int  dwPacketNumber = 0; //？？
	int itemp = 0;     //??
	__try
	{
		if (m_rIndexRV == m_ReceiveIndexRV)
		{
			dwPacketNumber = 0;
			m_nBufNo = 6;
			::ResetEvent(m_hHaveRDataRV);
			itemp = 0;
			return FALSE;
		}
		else if (m_rIndexRV < m_ReceiveIndexRV)    //read < write
		{
			if (dwReadLength > (DWORD)(m_ReceiveIndexRV-m_rIndexRV))
			{
				dwPacketNumber = 0;
				m_nBufNo = 6;
				::ResetEvent(m_hHaveRDataRV);
				itemp = 0;
				return FALSE;
			}
			else
			{
				CopyMemory(lpTemp, m_pRenderBuf + m_rIndexRV, dwReadLength);
				m_rIndexRV += dwReadLength;
				dwPacketNumber = (m_ReceiveIndexRV - m_rIndexRV) / dwReadLength;
				itemp = 1;
			}
		}
		else	//read > write,缓冲区满，从头开始????
		{
			if (dwReadLength > (DWORD)(AUDIOBUF - m_rIndexRV)) //
			{
				dwTemp = AUDIOBUF - m_rIndexRV;   //后面剩余量
				if ((dwReadLength-dwTemp) < (DWORD)(m_ReceiveIndexRV + 1))   //接受的新数据小于待拷贝数据量
				{
					CopyMemory(lpTemp, m_pRenderBuf + m_rIndexRV, dwTemp);       //拷贝后面剩余的
					CopyMemory(lpTemp + dwTemp, m_pRenderBuf, dwReadLength - dwTemp);    //再拷贝开始的
					m_rIndexRV = dwReadLength - dwTemp;                            //已读取，又重新开始
					dwPacketNumber = (m_ReceiveIndexRV-m_rIndexRV) / dwReadLength;   //？？
					itemp = 2;
				}
				else
				{
					dwPacketNumber = 0;
					::ResetEvent(m_hHaveRDataRV);
					m_nBufNo = 6;
					itemp = 3;
					return FALSE;	
				}
			}
			else
			{
				itemp = 4;
				CopyMemory(lpTemp, m_pRenderBuf + m_rIndexRV, dwReadLength);
				m_rIndexRV += dwReadLength;
				dwPacketNumber = (AUDIOBUF + m_ReceiveIndexRV - m_rIndexRV) / dwReadLength;
			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		return FALSE;
	}
	return TRUE;
}