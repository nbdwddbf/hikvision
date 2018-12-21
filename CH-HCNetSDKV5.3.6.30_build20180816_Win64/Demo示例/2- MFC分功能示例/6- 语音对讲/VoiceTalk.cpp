/*******************************************************
Copyright 2008-2011 Hikvision Digital Technology Co., Ltd. 
文  件：	TalkMR.cpp
开发单位：	杭州海康威视
编  写：	shizhiping
日  期：	2009.5
描  述：	语音对讲
修  改：	
********************************************************/

#include "stdafx.h"
#include "Voice.h"
#include "VoiceTalk.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/*************************************************
函数名:    	fVoiceTalkDataCallBack
函数描述:	回调函数，采集PCM数据，加上wav头
输入参数:   lVoiceComHandle-语音转发句柄
            pRecvDataBuffer-数据缓冲区
            dwBufSize-缓冲区大小
            byAudioFlag-语音数据类型0-本地采集的语音，1-接收到得语音
			pUser-用户数据
输出参数:   		
返回值:	   
*************************************************/
void CALLBACK fVoiceTalkDataCallBack(LONG lVoiceComHandle, char *pRecvDataBuffer, DWORD dwBufSize, BYTE byAudioFlag, void *pUser)
{
    ASSERT(pRecvDataBuffer);
	CVoiceTalk *pVoiceTalkDlg = (CVoiceTalk*)pUser;
	if(!pVoiceTalkDlg->m_bIsRecording)  //录音键未按下
		return;
    //0-本地数据，1-DVR发过来的数据
	if(byAudioFlag == 1)
	{
		::mmioWrite(pVoiceTalkDlg->m_hmmio,pRecvDataBuffer,dwBufSize);
	}
	
}



/////////////////////////////////////////////////////////////////////////////
// CVoiceTalk dialog


CVoiceTalk::CVoiceTalk(CWnd* pParent /*=NULL*/)
	: CDialog(CVoiceTalk::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVoiceTalk)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_lVoiceHandle = -1;
	m_bIsRecording = FALSE;
	m_iCurChanIndex = -1;
}


void CVoiceTalk::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVoiceTalk)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVoiceTalk, CDialog)
	//{{AFX_MSG_MAP(CVoiceTalk)
	ON_BN_CLICKED(IDC_BUTTON_TALK, OnButtonTalk)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnButtonRecord)
	ON_BN_CLICKED(IDC_RADIO_AUDIO1, OnRadioAudio1)
	ON_BN_CLICKED(IDC_RADIO_AUDIO2, OnRadioAudio2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVoiceTalk message handlers

BOOL CVoiceTalk::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
    m_iCurChanIndex = 1;
	((CButton*)GetDlgItem(IDC_RADIO_AUDIO1))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO_DATA_PCM))->SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*************************************************
函数名:    	OnButtonTalk
函数描述:	开始对讲/停止对讲 按钮
输入参数:   
输出参数:   		
返回值:	   
*************************************************/
void CVoiceTalk::OnButtonTalk() 
{
	
	if(!g_pMainDlg->m_bIsLogin)
	{
		MessageBox("Login fisrt!\n");
		return;
	}

	if(m_lVoiceHandle <0)    //start voice talk
	{
		StartVoiceTalk();
	}
	else     //stop talk
	{
	    StopVoiceTalk();
	}
	
}

/*************************************************
函数名:    	OnButtonRecord
函数描述:	开始录音/停止录音 按钮
输入参数:   
输出参数:   		
返回值:	   
*************************************************/
void CVoiceTalk::OnButtonRecord() 
{
	if(-1 == m_lVoiceHandle)
	{
		MessageBox(_T("start talk first"));
		return;
	}

	if(!m_bIsRecording)   //start record
	{
		StartRecord();
	}
	else                  //stop record
	{
		StopRecord();
	}	
}

/*************************************************
函数名:    	CreateWaveFile
函数描述:	创建wave音频文件
输入参数:   sFileName-文件名
输出参数:   		
返回值:	   
*************************************************/
BOOL CVoiceTalk::CreateWaveFile(char *sFileName)
{
	m_struWaveFormat.cbSize =			 sizeof(m_struWaveFormat);
	m_struWaveFormat.nBlockAlign =	 CHANNEL * BITS_PER_SAMPLE / 8;
	m_struWaveFormat.nChannels =		 CHANNEL;
	m_struWaveFormat.nSamplesPerSec =	 SAMPLES_PER_SECOND;
	m_struWaveFormat.wBitsPerSample =	 BITS_PER_SAMPLE;
	m_struWaveFormat.nAvgBytesPerSec = SAMPLES_PER_SECOND * m_struWaveFormat.nBlockAlign;
	m_struWaveFormat.wFormatTag =		 WAVE_FORMAT_PCM;
	
	if(!(m_hmmio = mmioOpen(sFileName,NULL,MMIO_CREATE|MMIO_WRITE|MMIO_EXCLUSIVE)))
	{
		//printf("opem file error\n");
		return FALSE;
	}
	
	ZeroMemory(&m_mmckinfoParent, sizeof(MMCKINFO));
	m_mmckinfoParent.fccType = mmioFOURCC('W','A','V','E');
	MMRESULT mmResult = ::mmioCreateChunk( m_hmmio,&m_mmckinfoParent, MMIO_CREATERIFF);
	
	ZeroMemory(&m_mmckinfoChild,sizeof(MMCKINFO));
	m_mmckinfoChild.ckid = mmioFOURCC('f','m','t',' ');
	m_mmckinfoChild.cksize = sizeof(WAVEFORMATEX) + m_struWaveFormat.cbSize;
	mmResult = ::mmioCreateChunk(m_hmmio, &m_mmckinfoChild, 0);
	
	mmResult = ::mmioWrite(m_hmmio, (char*)&m_struWaveFormat, sizeof(WAVEFORMATEX) + m_struWaveFormat.cbSize); 
	mmResult = ::mmioAscend(m_hmmio, &m_mmckinfoChild, 0);
	m_mmckinfoChild.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmResult = ::mmioCreateChunk(m_hmmio, &m_mmckinfoChild, 0);
	return TRUE;
}

/*************************************************
函数名:    	StopVoiceTalk
函数描述:	停止对讲
输入参数:   
输出参数:   		
返回值:	   
*************************************************/
void CVoiceTalk::StopVoiceTalk()
{
	if(m_bIsRecording)
	{
		OnButtonRecord();   //stop record
	}
	NET_DVR_StopVoiceCom(m_lVoiceHandle);
	GetDlgItem(IDC_BUTTON_TALK)->SetWindowText("开始对讲");
    m_lVoiceHandle = -1;
}

/*************************************************
函数名:    	StartVoiceTalk
函数描述:	开始对讲
输入参数:   
输出参数:   		
返回值:	   
*************************************************/
void CVoiceTalk::StartVoiceTalk()
{
	int iCurChan = GetCurVoiceChanIndex();
	m_lVoiceHandle = NET_DVR_StartVoiceCom_V30(g_pMainDlg->m_DeviceInfo.lLoginID,m_iCurChanIndex,iCurChan,fVoiceTalkDataCallBack,(void*)this);
	if(-1 == m_lVoiceHandle)
	{
		MessageBox(_T("Voice talk failed!"));
		return;
	}
	
	GetDlgItem(IDC_BUTTON_TALK)->SetWindowText("停止对讲");
}

/*************************************************
函数名:    	StartRecord
函数描述:	开始录音
输入参数:   
输出参数:   		
返回值:	   
*************************************************/
void CVoiceTalk::StartRecord()
{
	char RecName[256] = {0};
	
	CTime CurTime = CTime::GetCurrentTime();;
	sprintf(RecName,"%04d%02d%02d%02d%02d%02d.wav",CurTime.GetYear(),CurTime.GetMonth(),CurTime.GetDay(), \
		CurTime.GetHour(),CurTime.GetMinute(),CurTime.GetSecond());
	
	if(!CreateWaveFile(RecName))
	{
		MessageBox("create record file failed");
		return;
	}
	m_bIsRecording = TRUE;
	GetDlgItem(IDC_BUTTON_RECORD)->SetWindowText("停止录音");
}

/*************************************************
函数名:    	StopRecord
函数描述:	停止录音
输入参数:   
输出参数:   		
返回值:	   
*************************************************/
void CVoiceTalk::StopRecord()
{
	if(m_hmmio)
	{
		::mmioAscend(m_hmmio,&m_mmckinfoChild,0);
		::mmioAscend(m_hmmio,&m_mmckinfoParent,0);
		::mmioClose(m_hmmio,0);
		m_hmmio = NULL;
		m_bIsRecording = FALSE;
		GetDlgItem(IDC_BUTTON_RECORD)->SetWindowText("开始录音");
	}
}

/*************************************************
函数名:    	GetCurVoiceChanIndex
函数描述:	获取当前的语音通道
输入参数:   
输出参数:   		
返回值:	   当前选中的语音通道
*************************************************/
int CVoiceTalk::GetCurVoiceChanIndex()
{
    return m_iCurChanIndex;
}

/*************************************************
函数名:    	OnRadioAudio1
函数描述:	选中语音通道1
输入参数:   
输出参数:   		
返回值:	   
*************************************************/
void CVoiceTalk::OnRadioAudio1() 
{
	m_iCurChanIndex = 1;
}

/*************************************************
函数名:    	OnRadioAudio2
函数描述:	选中语音通道2
输入参数:   
输出参数:   		
返回值:	   
*************************************************/
void CVoiceTalk::OnRadioAudio2() 
{
    m_iCurChanIndex = 2;	
}

/*************************************************
函数名:    	SetChanRadioState
函数描述:	设置语音通道状态
输入参数:   iNum-通道号
            ChanStatus-状态
输出参数:   		
返回值:	   
*************************************************/
void CVoiceTalk::SetChanRadioState(int iNum,BYTE *ChanStatus)
{
   switch (iNum)
   {
   case 1:
	   GetDlgItem(IDC_RADIO_AUDIO1)->EnableWindow(TRUE);
	   GetDlgItem(IDC_RADIO_AUDIO2)->EnableWindow(FALSE);
	   switch(ChanStatus[0])   //8000设备不支持语音通道状态
	   {
	   case 0:      //not used
		   break;
	   case 1:      // using
		   break;
	   case 0xff:   //
		   break;
	   default:
		   break;
	   }
		break;
   case 2:
	   GetDlgItem(IDC_RADIO_AUDIO1)->EnableWindow(TRUE);
	   GetDlgItem(IDC_RADIO_AUDIO2)->EnableWindow(TRUE);
	   break;
   default:
	   break;
   }
}
