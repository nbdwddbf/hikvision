// DlgEncodeAbility.cpp : implementation file
//
#include "stdafx.h"
#include "clientdemo.h"
#include "DlgEncodeAbility.h"
#include "DlgCurrentEncodeAbility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEncodeAbility dialog


CDlgEncodeAbility::CDlgEncodeAbility(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEncodeAbility::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEncodeAbility)
	m_iMaxVideoBitrate = 0;
	m_iMinVideoBitrate = 0;
	m_iEFrame = 0;
	m_sVideoFrame = _T("");
	//}}AFX_DATA_INIT
	m_dwVideoChan = 0;
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_pRecvBuf = NULL;
	m_pRecvBuf10 = NULL;
    m_pSendBuf = NULL;
	m_dwVideoChanNO = 0;
	m_bEncode20 = FALSE;
	m_bEncode10 = FALSE;
    memset(&m_struEncodeAbility, 0, sizeof(m_struEncodeAbility));
}


void CDlgEncodeAbility::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEncodeAbility)
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_comboResolution);
	DDX_Control(pDX, IDC_COMBO_ENCODE_TYPE, m_comboEncodeType);
	DDX_Control(pDX, IDC_LIST_VIDEO_FRAMERATE, m_listVideoFrameRate);
	DDX_Control(pDX, IDC_LIST_VIDEO_RESOLUTION, m_listVideoResolution);
	DDX_Control(pDX, IDC_LIST_VIDEO_ENCODE_TYPE, m_listVideoEncode);
	DDX_Control(pDX, IDC_LIST_INTERVAL_BPFRAME, m_listIntervalBPFrame);
	DDX_Control(pDX, IDC_COMBO_STREAM_TYPE, m_comboStreamType);
	DDX_Control(pDX, IDC_LIST_AUDIO_ENCODE, m_listAudioEncode);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comboChannel);
	DDX_Control(pDX, IDC_LIST_VOICETALK_ENCODE, m_listVoicetalkEncode);
	DDX_Text(pDX, IDC_EDIT_MAX_VIDEO_BITRATE, m_iMaxVideoBitrate);
	DDX_Text(pDX, IDC_EDIT_MIN_VIDEO_BITRATE, m_iMinVideoBitrate);
	DDX_Text(pDX, IDC_EDIT_EFRAME, m_iEFrame);
	DDX_Text(pDX, IDC_EDIT_VIDEO_FRAME_RATE, m_sVideoFrame);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEncodeAbility, CDialog)
	//{{AFX_MSG_MAP(CDlgEncodeAbility)
	ON_CBN_SELCHANGE(IDC_COMBO_STREAM_TYPE, OnSelchangeComboStreamType)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnSelchangeComboChannel)
	ON_BN_CLICKED(IDC_BTN_CURREN_ENCODE_ABILITY, OnBtnCurrenEncodeAbility)
	ON_BN_CLICKED(IDC_BTN_DEVICE_ALL_ABILITY, OnBtnDeviceAllAbility)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEncodeAbility message handlers

BOOL CDlgEncodeAbility::OnInitDialog() 
{
	CDialog::OnInitDialog();

    if (NULL == m_pRecvBuf)
    {
        m_pRecvBuf = new char[XML_BUF];
    }

	if (NULL == m_pRecvBuf10)
    {
        m_pRecvBuf10 = new char[XML_BUF];
    }
    
    if (NULL == m_pSendBuf)
    {
        m_pSendBuf = new char[XML_BUF];
    }
	//////////////////////////////////////////////////////////////////////////
//	GetCurrentEncodeAbility();
//	WirteBufToFile(m_pRecvBuf,strlen(m_pRecvBuf));
	//////////////////////////////////////////////////////////////////////////
    InitString();
    GetEncodeAbility();
    
    ParseEncodeAbility(m_pRecvBuf, strlen(m_pRecvBuf));

//	ParseEncodeAbility(m_pRecvBuf10, strlen(m_pRecvBuf10));
    
    InitWnd();
    
    m_comboChannel.SetCurSel(0);
    m_comboStreamType.SetCurSel(0);
    SetEncodeAbilityToWnd(m_struEncodeAbility);

    InitReolutionCombo();
    InitEncodeTypeCombo();

    UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEncodeAbility::InitString()
{
    InitVideiEncodeTypeString();
}

void CDlgEncodeAbility::InitVideiEncodeTypeString()
{
    int i = 0; 
    for (i = 0; i < MAXENCODETYPE; i++)
    {
        m_csVideoEncodeType[i].Format("%s", _T(""));
    }
    
    m_csVideoEncodeType[0].Format("%s", _T("Private 264"));
    m_csVideoEncodeType[1].Format("%s", _T("TD_MPEG4"));
    m_csVideoEncodeType[2].Format("%s", _T("STD_H264"));
}

void CDlgEncodeAbility::InitWnd()
{
    m_comboChannel.ResetContent();
    
    char szLan[128] = {0};
    for (int i = 0; i < m_struEncodeAbility.dwVideoChanNum; i++)
    {
        sprintf(szLan, "chan %d", m_dwVideoChanNO/*i + 1*/);
        m_comboChannel.AddString(szLan);
    }

    m_comboStreamType.ResetContent();
    g_StringLanType(szLan, "主码流", "Main stream");
    m_comboStreamType.AddString(szLan);
    g_StringLanType(szLan, "子码流", "Sub stream");
    m_comboStreamType.AddString(szLan);
    m_comboStreamType.SetCurSel(0);
}

void CDlgEncodeAbility::InitReolutionCombo()
{
	char szLan[128] = {0};
    m_comboResolution.ResetContent();
	m_listVideoFrameRate.ResetContent();
    LONG lChannel = m_dwVideoChanNO-1/*m_comboChannel.GetCurSel()*/;
    LONG lStreamType = m_comboStreamType.GetCurSel(); // 0 主
    int nIndex = 0;
    int i = 0;
    if (0 ==  lStreamType)
    {
        for ( i = 0; i < MAXRESOLUTIONTYPE; i++)
        {
            if (1 == m_struEncodeAbility.struVideoCompressCfg[lChannel].struMainPara.byVideoResolution[i])
            {
                m_comboResolution.InsertString(nIndex, m_csVideoResolution[i]);
                m_comboResolution.SetItemData(nIndex, i);
				m_sVideoFrame = m_csVideoFrameRate[i];
				m_iMaxVideoBitrate = m_lMaxVideoBitrate[i];
				m_iMinVideoBitrate = m_lMinVideoBitrate[i];
                nIndex++;
            }
        }

    }
    else if (1 == lStreamType)
    {
        for (i = 0; i < MAXRESOLUTIONTYPE; i++)
        {
            if (1 == m_struEncodeAbility.struVideoCompressCfg[lChannel].struSubPara.byVideoResolution[i])
            {
                m_comboResolution.InsertString(nIndex, m_csVideoResolution[i]);
                m_comboResolution.SetItemData(nIndex, i);
                nIndex++;
            }
        }
    }

    if (nIndex > 0)
    {
        m_comboResolution.SetCurSel(0);
    }
}

void CDlgEncodeAbility::InitEncodeTypeCombo()
{
    m_comboEncodeType.ResetContent();
    LONG lChannel = m_dwVideoChanNO-1/*m_comboChannel.GetCurSel()*/;
    LONG lStreamType = m_comboStreamType.GetCurSel(); // 0 主
    int nIndex = 0;
    int i = 0;
    if (0 ==  lStreamType)
    {
        for ( i = 0; i < MAXENCODETYPE; i++)
        {
            if (1 == m_struEncodeAbility.struVideoCompressCfg[lChannel].struMainPara.byVideoEncodeType[i])
            {
                m_comboEncodeType.InsertString(nIndex, m_csVideoEncodeType[i]);
                m_comboEncodeType.SetItemData(nIndex, i);
                nIndex++;
            }
        }
        
    }
    else if (1 == lStreamType)
    {
        for (i = 0; i < MAXRESOLUTIONTYPE; i++)
        {
            if (1 == m_struEncodeAbility.struVideoCompressCfg[lChannel].struSubPara.byVideoEncodeType[i])
            {
                m_comboEncodeType.InsertString(nIndex, m_csVideoEncodeType[i]);
                m_comboEncodeType.SetItemData(nIndex, i);
                nIndex++;
            }
        }
    }
    if (nIndex > 0)
    {
        m_comboEncodeType.SetCurSel(0);
    }
}

BOOL CDlgEncodeAbility::GetEncodeAbility()
{
    memset(m_pRecvBuf, 0, XML_BUF);
	memset(m_pRecvBuf10, 0, XML_BUF);
//	strcpy(m_pSendBuf,"<AudioVideoCompressInfo><ChannelNumber>17</ChannelNumber></AudioVideoCompressInfo>");
	sprintf(m_pSendBuf,"<AudioVideoCompressInfo version=\"2.0\"><AudioChannelNumber>1</AudioChannelNumber><VoiceTalkChannelNumber>1</VoiceTalkChannelNumber><VideoChannelNumber>%d</VideoChannelNumber></AudioVideoCompressInfo>",m_dwVideoChan);
//    strcpy(m_pSendBuf,"<AudioVideoCompressInfo><AudioChannelNumber>1</AudioChannelNumber><VoiceTalkChannelNumber>1</VoiceTalkChannelNumber><VideoChannelNumber>1</VideoChannelNumber></AudioVideoCompressInfo>");
	
    if (!NET_DVR_GetDeviceAbility(m_lServerID, DEVICE_ENCODE_ALL_ABILITY_V20, m_pSendBuf, strlen(m_pSendBuf), m_pRecvBuf, XML_BUF))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "DEVICE_ENCODE_ALL_ABILITY_V20");
		return FALSE;
    }
    else
    {
		m_bEncode20 = TRUE;
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "DEVICE_ENCODE_ALL_ABILITY_V20");
		return TRUE;
    }

//  	if (!NET_DVR_GetDeviceAbility(m_lServerID, DEVICE_ENCODE_ALL_ABILITY, NULL, 0, m_pRecvBuf10, XML_BUF))
//      {
//          g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "DEVICE_ENCODE_ALL_ABILITY");
//          return FALSE;
//      }
//      else
//      {
//  		m_bEncode10 = TRUE;
//          g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "DEVICE_ENCODE_ALL_ABILITY");
//          return TRUE;
//      }
}

BOOL CDlgEncodeAbility::GetCurrentEncodeAbility()
{
    memset(m_pRecvBuf, 0, XML_BUF);
	strcpy(m_pSendBuf,"<CurrentCompressInfo><ChannelNumber>1</ChannelNumber><VideoEncodeType>0</VideoEncodeType><VideoResolution>17</VideoResolution></CurrentCompressInfo>");
    if (!NET_DVR_GetDeviceAbility(m_lServerID, DEVICE_ENCODE_CURRENT, m_pSendBuf, strlen(m_pSendBuf), m_pRecvBuf, XML_BUF))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "DEVICE_ENCODE_CURRENT");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "DEVICE_ENCODE_CURRENT");
        return TRUE;
        
    }
}

void CDlgEncodeAbility::PostNcDestroy() 
{
    if (m_pSendBuf != NULL)
    {
        delete []m_pSendBuf;
        m_pSendBuf = NULL;
    }

    if (m_pRecvBuf != NULL)
    {
        delete []m_pRecvBuf;
        m_pRecvBuf = NULL;
    }

	if (m_pRecvBuf10 != NULL)
    {
        delete []m_pRecvBuf10;
        m_pRecvBuf10 = NULL;
    }
    	
	CDialog::PostNcDestroy();
}

BOOL CDlgEncodeAbility::ParseEncodeAbility(char *pBuf, DWORD dwBufSize)
{
    // todo!!!
    WirteBufToFile(pBuf, dwBufSize);
    
    CMarkup	XmlMaker;
    XmlMaker.SetDoc(pBuf);
    
//    ParseAudioVideoXml(XmlMaker);
        
    return TRUE;
}

/*************************************************
Function:    	ParseStrIndex
Description:	解析摄像机XML字符串中数字,设置数组的值。
如：strIndex = "1,5",则array[1] = 1; array[5] = 1;
Input:        CString strIndex：仅含有','及数字的XML字符串，如"1,5,6,9"
byte* array:存储解析结果的数组地址
int iArrayLength：数组的维数
Output:      	无
Return:		无
*************************************************/
void CDlgEncodeAbility::ParseStrIndex(CString strIndex, byte* array, int iArrayLength)
{
    CString strTemp1 = _T("");
    CString strTemp2 = _T("");
    int iIndex = -1;
    
    strTemp1.Format("%s", strIndex);
    
    iIndex = strTemp1.Find(',', 0);
    
    //当没有','时，直接转换为数字
    if (-1 == iIndex)
    {
        //若转换得到的数字大于数组的维数或者小于0，则返回
        if (atoi(strTemp1) >= iArrayLength || atoi(strTemp1) < 0)
        {
            return;
        }
        array[atoi(strTemp1)] = 1;
        return;
    }
    
    //解析strIndex，设置数组的值
    while (iIndex != -1 )
    {
        strTemp2.Format("%s", strTemp1.Left(iIndex));
        //若转换得到的数字大于数组的维数或者小于0，则返回
        if (atoi(strTemp2) >= iArrayLength || atoi(strTemp2) < 0)
        {
            return;
        }
        array[atoi(strTemp2)] = 1;
        strTemp1.Delete(0, iIndex + 1);
        iIndex = strTemp1.Find(',', 0);
    }
    
    //若转换得到的数字大于数组的维数或者小于0，则返回
    if (atoi(strTemp2) >= iArrayLength || atoi(strTemp2) < 0)
    {
        return;
    }
    array[atoi(strTemp1)] = 1;
}


BOOL CDlgEncodeAbility::WirteBufToFile(char *pBuf, DWORD dwBufSize)
{
    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    char cFilename[256] = {0};
    sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
    
	if (m_bEncode20)
	{
		sprintf(cFilename, "%s\\ALL_ENCODE_20_%s.xml", g_struLocalParam.chPictureSavePath, chTime);
	}
// 	if (m_bEncode10)
// 	{
// 		sprintf(cFilename, "%s\\ALL_ENCODE_%s.xml", g_struLocalParam.chPictureSavePath, chTime);
// 	}    
    
    HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        int nError = 0;
        nError = GetLastError();
        return FALSE;
    }
    DWORD dwReturn = 0;
    WriteFile(hFile, pBuf, dwBufSize, &dwReturn, NULL);
    CloseHandle(hFile);
    hFile = NULL;
    
    return TRUE;
}



BOOL CDlgEncodeAbility::ParseAudioVideoXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("AudioVideoCompressInfo"))
    {
        struMarkup.IntoElem();
        ParseAudioCompressXml(struMarkup);
        ParseVideoCompressXml(struMarkup);
        struMarkup.OutOfElem();
    }
    else
    {
        AfxMessageBox("AudioVideoCompressInfo Fail");
    }
    return TRUE;
}


BOOL CDlgEncodeAbility::ParseAudioCompressXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("AudioCompressInfo"))
    {
       struMarkup.IntoElem();
       ParseAudioEncodeTypeXml(struMarkup);
       ParseVoiceTalkEncodeTypeXml(struMarkup);
       struMarkup.OutOfElem();
    }
    else
    {
        AfxMessageBox("AudioCompressInfo fail");
    }

    return TRUE;
}

BOOL CDlgEncodeAbility::ParseAudioEncodeTypeXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("AudioEncodeType"))
    {   
        struMarkup.IntoElem();
        
//         str = struMarkup.GetChildData();
        if (struMarkup.FindElem("Range"))
        {
            CString str;
            str = struMarkup.GetData();
            ParseStrIndex(str, m_struEncodeAbility.struAudioCompress.byAudioEncodeType, sizeof(m_struEncodeAbility.struAudioCompress.byAudioEncodeType));
        }
        struMarkup.OutOfElem();
    }

    if (struMarkup.FindElem("VoiceTalkEncodeType"))
    {
        struMarkup.IntoElem();
        if (struMarkup.FindElem("Range"))
        {
            CString str;
            str = struMarkup.GetData();
            ParseStrIndex(str, m_struEncodeAbility.struAudioCompress.byVoiceTalkEncodeType, sizeof(m_struEncodeAbility.struAudioCompress.byVoiceTalkEncodeType));
        }
        struMarkup.OutOfElem();
    }

    return TRUE;
}

BOOL CDlgEncodeAbility::ParseVoiceTalkEncodeTypeXml(CMarkup &struMarkup)
{
//     <VoiceTalkEncodeType>
//         <Range>0,1,2,3,4,5,99</Range>
// </VoiceTalkEncodeType>
    if (struMarkup.FindElem("VoiceTalkEncodeType"))
    {   
        struMarkup.IntoElem();
        
        if (struMarkup.FindElem("Range"))
        {
            CString str;
            str = struMarkup.GetData();
            ParseStrIndex(str, m_struEncodeAbility.struAudioCompress.byVoiceTalkEncodeType, sizeof(m_struEncodeAbility.struAudioCompress.byVoiceTalkEncodeType));
         }
        struMarkup.OutOfElem();
    }
    return TRUE;
}

BOOL CDlgEncodeAbility::ParseVideoCompressXml(CMarkup &struMarkup)
{
    CString str = "";
    if (struMarkup.FindElem("VideoCompressInfo"))
    {
        struMarkup.IntoElem();
        
        if (struMarkup.FindElem("ChannelList"))
        {
            struMarkup.IntoElem();
            if (struMarkup.FindElem("ChannelEntry"))
            {
                struMarkup.IntoElem();
                m_struEncodeAbility.dwVideoChanNum = 0;
                while (struMarkup.FindElem("ChannelNumber"))
                {
                    m_struEncodeAbility.dwVideoChanNum++;
                    int nChannelNum = 0;
                    nChannelNum = atoi(struMarkup.GetData());
					m_dwVideoChanNO = nChannelNum;
                    ParseMainChanXml(struMarkup, m_struEncodeAbility.struVideoCompressCfg[nChannelNum - 1].struMainPara);

                    ParseSubChanXml(struMarkup, m_struEncodeAbility.struVideoCompressCfg[nChannelNum - 1].struSubPara);
                }
                struMarkup.OutOfElem();
            }
            struMarkup.OutOfElem();
        }
        struMarkup.OutOfElem();
    }
    
    return TRUE;
}

BOOL CDlgEncodeAbility::ParseMainChanXml(CMarkup &struMarkup, VIDEOCOMPRESSINFO& struMainPara)
{
    if (struMarkup.FindElem("MainChannel"))
    {
        struMarkup.IntoElem();
        ParseVideoEncodeType(struMarkup, struMainPara.byVideoEncodeType, sizeof(struMainPara.byVideoEncodeType));
        ParseVideoResolution(struMarkup, struMainPara.byVideoResolution, sizeof(struMainPara.byVideoResolution));
        ParseVideoFrameRate(struMarkup, struMainPara.byVideoFrameRate, sizeof(struMainPara.byVideoFrameRate));
//        ParseMinMaxVideoRate(struMarkup, struMainPara.lMinVideoBitrate, struMainPara.lMaxVideoBitrate);
        ParseIntervalBPFrame(struMarkup, struMainPara.byIntervalBPFrame, sizeof(struMainPara.byIntervalBPFrame));
        ParseEFrame(struMarkup, struMainPara.lEFrame);

        struMarkup.OutOfElem();
    }
    else
    {
        AfxMessageBox("Fail to find main channel");
    }
    return TRUE;
}

BOOL CDlgEncodeAbility::ParseSubChanXml(CMarkup &struMarkup, VIDEOCOMPRESSINFO& struSubPara)
{
    int  iTemp = 0;
    if (struMarkup.FindElem("SubChannelList"))
    {
        struMarkup.IntoElem();;
        if (struMarkup.FindElem("SubChannelEntry"))
        {
            struMarkup.IntoElem();

            if (struMarkup.FindElem("index"))//暂时无用，以后做事件扩展时要根据此index来判断是子码流还是事件，现在1-子码流
            {
                iTemp = atoi(struMarkup.GetData());
    		}	

            ParseVideoEncodeType(struMarkup, struSubPara.byVideoEncodeType, sizeof(struSubPara.byVideoEncodeType));
            ParseVideoResolution(struMarkup, struSubPara.byVideoResolution, sizeof(struSubPara.byVideoResolution));
            ParseVideoFrameRate(struMarkup, struSubPara.byVideoFrameRate, sizeof(struSubPara.byVideoFrameRate));
            ParseMinMaxVideoRate(struMarkup, struSubPara.lMinVideoBitrate, struSubPara.lMaxVideoBitrate);
            ParseIntervalBPFrame(struMarkup, struSubPara.byIntervalBPFrame, sizeof(struSubPara.byIntervalBPFrame));
            ParseEFrame(struMarkup, struSubPara.lEFrame);

            struMarkup.OutOfElem();
        }
        struMarkup.OutOfElem();
    }
    return TRUE;
}


BOOL CDlgEncodeAbility::ParseMinMaxVideoRate(CMarkup &struMarkup, LONG *lMinVideoBitrate, LONG *lMaxVideoBitrate)
{
	int iTemp = 0;
    CString strTemp;
    //VideoResolutionList-分辨率参数列表
    struMarkup.FindElem("VideoResolutionList");
    struMarkup.IntoElem();
    //循环获取分辨率参数类型
    while (struMarkup.FindElem("VideoResolutionEntry"))
    {
        struMarkup.IntoElem();

		if (struMarkup.FindElem("Index"))
        {
            iTemp = atoi(struMarkup.GetData());
        }

        if (struMarkup.FindElem("VideoBitrate"))
        {
            struMarkup.IntoElem();
		        
			if (struMarkup.FindElem("Min"))
			{
			  lMinVideoBitrate[iTemp] = atoi(struMarkup.GetData());
			}
			
			if (struMarkup.FindElem("Max"))
			{
			  lMaxVideoBitrate[iTemp] = atoi(struMarkup.GetData());
			}
			 
           struMarkup.OutOfElem();
        }
        
        struMarkup.OutOfElem();
    }
	struMarkup.OutOfElem();
    return TRUE;
//     if (struMarkup.FindElem("VideoBitrate"))
//     {
//         struMarkup.IntoElem();
//         
//         if (struMarkup.FindElem("Min"))
//         {
//             lMinVideoBitrate = atoi(struMarkup.GetData());
//         }
// 
//         if (struMarkup.FindElem("Max"))
//         {
//             lMaxVideoBitrate = atoi(struMarkup.GetData());
//         }
// 
//         struMarkup.OutOfElem();
//     }
    
    return TRUE;
}


BOOL CDlgEncodeAbility::ParseEFrame(CMarkup &struMarkup, LONG &lEFrame)
{
    if (struMarkup.FindElem("EFrame"))
    {
        lEFrame = atoi(struMarkup.GetData());
    }
    return TRUE;
}

BOOL CDlgEncodeAbility::ParseVideoEncodeType(CMarkup &struMarkup, BYTE *byVideoEncodeType, DWORD dwArraySize)
{

    CString strTemp = "";
    if (struMarkup.FindElem("VideoEncodeType"))
    {
        struMarkup.IntoElem();
        if (struMarkup.FindElem("Range"))
        {
            strTemp.Format("%s", struMarkup.GetData());
            ParseStrIndex(strTemp, byVideoEncodeType, dwArraySize);
        }
        struMarkup.OutOfElem();
    }
    
    return TRUE;
}

BOOL CDlgEncodeAbility::ParseVideoResolution(CMarkup &struMarkup, BYTE *byVideoResolution, DWORD dwArraySize)
{
    int iTemp = 0;
    CString strTemp;
    //VideoResolutionList-分辨率参数列表
    struMarkup.FindElem("VideoResolutionList");
    struMarkup.IntoElem();
    //循环获取分辨率参数类型
    while (struMarkup.FindElem("VideoResolutionEntry"))
    {
        struMarkup.IntoElem();
        if (struMarkup.FindElem("Index"))
        {
            iTemp = atoi(struMarkup.GetData());
            if (iTemp >= 0 && iTemp <= dwArraySize) 
            {
                byVideoResolution[iTemp] = TRUE;
            }
        }
        if (struMarkup.FindElem("Name"))
        {
            strTemp.Format("%s", struMarkup.GetData());
            m_csVideoResolution[iTemp].Format("%s", strTemp);
        }

		if (struMarkup.FindElem("VideoFrameRate"))
		{
			strTemp.Format("%s", struMarkup.GetData());
			m_csVideoFrameRate[iTemp].Format("%s", strTemp);
		}

		if (struMarkup.FindElem("VideoBitrate"))
        {
            struMarkup.IntoElem();
			
			if (struMarkup.FindElem("Min"))
			{
				m_lMinVideoBitrate[iTemp] = atoi(struMarkup.GetData());
			}
			
			if (struMarkup.FindElem("Max"))
			{
				m_lMaxVideoBitrate[iTemp] = atoi(struMarkup.GetData());
			}
			
			struMarkup.OutOfElem();
        }
        struMarkup.OutOfElem();
    }
		struMarkup.OutOfElem();
    return TRUE;
}

BOOL CDlgEncodeAbility::ParseVideoFrameRate(CMarkup &struMarkup, BYTE *byVideoFrameRate, DWORD dwArraySize)
{
    CString strTemp;
    //VideoFrameRate - 视频帧率列表
    struMarkup.FindElem("VideoFrameRate");
    struMarkup.IntoElem();
    if (struMarkup.FindElem("Range"))
    {
        strTemp.Format("%s", struMarkup.GetData());
        ParseStrIndex(strTemp, byVideoFrameRate, dwArraySize);
    }
	struMarkup.OutOfElem();
    return TRUE;
}

BOOL CDlgEncodeAbility::ParseIntervalBPFrame(CMarkup &struMarkup, BYTE *byIntervalBPFrameRate, DWORD dwArraySize)
{
    CString strTemp;
    //IntervalBPFrame - 帧类型
    struMarkup.FindElem("IntervalBPFrame");
    struMarkup.IntoElem();
    if (struMarkup.FindElem("Range"))
    {
        strTemp.Format("%s", struMarkup.GetData());
        ParseStrIndex(strTemp, byIntervalBPFrameRate, dwArraySize);
    }
    struMarkup.OutOfElem();

    return TRUE;
}



void CDlgEncodeAbility::SetEncodeAbilityToWnd(ENCODE_ABILITY_PARAM &struEncodeAbility)
{
    SetAudioCompressInfoToWnd(struEncodeAbility.struAudioCompress);
    SetVideoCompressCfgToWnd(struEncodeAbility.struVideoCompressCfg[m_dwVideoChanNO-1/*m_comboChannel.GetCurSel()*/]);
}

void CDlgEncodeAbility::SetAudioCompressInfoToWnd(AUDIOCOMPRESSINFO &struAudioCompressInfo)
{
    m_listAudioEncode.ResetContent();
    char szLan[128] = {0};
    int i = 0;
    for (i = 0; i < ARRAY_SIZE(struAudioCompressInfo.byAudioEncodeType); i++)
    {
        if (1 == struAudioCompressInfo.byAudioEncodeType[i])
        {
            sprintf(szLan, "%d", i);
            m_listAudioEncode.AddString(szLan);
        }
    }
    
    for (i = 0; i < ARRAY_SIZE(struAudioCompressInfo.byVoiceTalkEncodeType); i++)
    {
        if (1 == struAudioCompressInfo.byVoiceTalkEncodeType[i])
        {
            sprintf(szLan, "%d", i);
            m_listVoicetalkEncode.AddString(szLan);
        }
    }

}

void CDlgEncodeAbility::SetVideoCompressCfgToWnd(VIDEOCOMPRESSCFG &struVideoCompressCfg)
{
    if (0 == m_comboStreamType.GetCurSel()) // 主码流
    {
        SetVideoCompressInfoToWnd(struVideoCompressCfg.struMainPara);
    }
    else if (1 == m_comboStreamType.GetCurSel())
    {
        SetVideoCompressInfoToWnd(struVideoCompressCfg.struSubPara);
    }
}

void CDlgEncodeAbility::SetVideoCompressInfoToWnd(VIDEOCOMPRESSINFO &struVideoCompressInfo)
{
    m_iEFrame = struVideoCompressInfo.lEFrame;

    int i = 0;
    char szLan[128] = {0};

    m_listVideoEncode.ResetContent();
    for (i = 0; i < ARRAY_SIZE(struVideoCompressInfo.byVideoEncodeType); i++)
    {
        if (1 == struVideoCompressInfo.byVideoEncodeType[i])
        {
            sprintf(szLan, "%d", i);
            m_listVideoEncode.AddString(szLan);
        }
    }
    
    m_listVideoResolution.ResetContent();
    for (i = 0; i < ARRAY_SIZE(struVideoCompressInfo.byVideoResolution); i++)
    {
        if (1 == struVideoCompressInfo.byVideoResolution[i])
        {
            sprintf(szLan, "%d", i);
            m_listVideoResolution.AddString(szLan);
			m_iMaxVideoBitrate = struVideoCompressInfo.lMaxVideoBitrate[i];
            m_iMinVideoBitrate = struVideoCompressInfo.lMinVideoBitrate[i];
        }
    }

    m_listVideoFrameRate.ResetContent();
    for (i = 0; i < ARRAY_SIZE(struVideoCompressInfo.byVideoFrameRate); i++)
    {
        if (1 == struVideoCompressInfo.byVideoFrameRate[i])
        {
            sprintf(szLan, "%d", i);
            m_listVideoFrameRate.AddString(szLan);
        }
    }

    m_listIntervalBPFrame.ResetContent();
    for (i = 0; i< ARRAY_SIZE(struVideoCompressInfo.byIntervalBPFrame); i++)
    {
        if (1 == struVideoCompressInfo.byIntervalBPFrame[i])
        {
            sprintf(szLan, "%d", i);
            m_listIntervalBPFrame.AddString(szLan);
        }
    }


}

void CDlgEncodeAbility::OnSelchangeComboStreamType() 
{
    int lChannel = m_comboChannel.GetCurSel();
    SetVideoCompressCfgToWnd(m_struEncodeAbility.struVideoCompressCfg[lChannel]);	
    InitEncodeTypeCombo();
    InitReolutionCombo();

}

void CDlgEncodeAbility::OnSelchangeComboChannel() 
{
    int lChannel = m_comboChannel.GetCurSel();
    SetVideoCompressCfgToWnd(m_struEncodeAbility.struVideoCompressCfg[lChannel]);
    InitEncodeTypeCombo();
    InitReolutionCombo();
}

void CDlgEncodeAbility::OnBtnCurrenEncodeAbility() 
{
    CDlgCurrentEncodeAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lEncodeType = m_comboEncodeType.GetItemData(m_comboEncodeType.GetCurSel());
    dlg.m_lResolution = m_comboResolution.GetItemData(m_comboResolution.GetCurSel());
    dlg.DoModal();
}

void CDlgEncodeAbility::OnBtnDeviceAllAbility() 
{

}
