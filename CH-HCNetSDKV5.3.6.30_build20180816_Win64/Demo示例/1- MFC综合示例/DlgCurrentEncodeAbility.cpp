// DlgCurrentEncodeAbility.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCurrentEncodeAbility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCurrentEncodeAbility dialog


CDlgCurrentEncodeAbility::CDlgCurrentEncodeAbility(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCurrentEncodeAbility::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCurrentEncodeAbility)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_lResolution = -1;
    m_lEncodeType = -1;
    m_pRecvBuf = NULL;
    m_pSendBuf = NULL;
    memset(&m_struCurrentEncode, 0, sizeof(m_struCurrentEncode));
}


void CDlgCurrentEncodeAbility::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCurrentEncodeAbility)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCurrentEncodeAbility, CDialog)
	//{{AFX_MSG_MAP(CDlgCurrentEncodeAbility)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCurrentEncodeAbility message handlers

BOOL CDlgCurrentEncodeAbility::OnInitDialog() 
{
	CDialog::OnInitDialog();
    if (NULL == m_pRecvBuf)
    {
        m_pRecvBuf = new char[XML_BUF];
    }

    if (NULL == m_pSendBuf)
    {
        m_pSendBuf = new char[XML_BUF];
    }

    memset(m_pSendBuf, 0, XML_BUF);
    memset(m_pRecvBuf, 0, XML_BUF);

    FormatSendBufXml(m_pSendBuf);
    GetCurrentEncodeAbiliity(m_pSendBuf, strlen(m_pSendBuf));	

    ParseCurrentEncodeAbility(m_pRecvBuf, strlen(m_pRecvBuf));
	
    WirteBufToFile(m_pRecvBuf, strlen(m_pRecvBuf));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgCurrentEncodeAbility::PostNcDestroy() 
{
    // TODO: Add your specialized code here and/or call the base class
    
    if (NULL != m_pRecvBuf)
    {
        delete []m_pRecvBuf;
        m_pRecvBuf = NULL;
    }

    if (NULL != m_pSendBuf)
    {
        delete []m_pSendBuf;
    }
    CDialog::PostNcDestroy();
}

BOOL CDlgCurrentEncodeAbility::WirteBufToFile(char *pBuf, DWORD dwBufSize)
{
    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    char cFilename[256] = {0};
    sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
    
    sprintf(cFilename, "%s\\%s.xml", g_struLocalParam.chPictureSavePath, chTime);
    
    
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

BOOL CDlgCurrentEncodeAbility::FormatSendBufXml(char *pSendBuf)
{
    sprintf(pSendBuf,"<CurrentCompressInfo><VideoEncodeType>%d</VideoEncodeType><VideoResolution>%d</VideoResolution></CurrentCompressInfo>", m_lEncodeType, m_lResolution);
    return TRUE;
}

BOOL CDlgCurrentEncodeAbility::GetCurrentEncodeAbiliity(char *pSendBuf, DWORD dwBufSize)
{
    memset(m_pRecvBuf, 0, XML_BUF);
	strcpy(pSendBuf,"<CurrentCompressInfo><ChannelNumber>1</ChannelNumber><VideoEncodeType>0</VideoEncodeType><VideoResolution>17</VideoResolution></CurrentCompressInfo>");
    if (!NET_DVR_GetDeviceAbility(m_lServerID, DEVICE_ENCODE_CURRENT, pSendBuf, strlen(pSendBuf), m_pRecvBuf, XML_BUF))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "DEVICE_ENCODE_CURRENT");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "DEVICE_ENCODE_CURRENT");
        return TRUE;
    }
}

BOOL CDlgCurrentEncodeAbility::ParseCurrentEncodeAbility(char *pRecvBuf, DWORD dwBufSize)
{
    CMarkup	XmlMaker;
    XmlMaker.SetDoc(pRecvBuf);
    
    ParseCurrentEncodeAbilityXml(XmlMaker);
    return TRUE;
}

BOOL CDlgCurrentEncodeAbility::ParseCurrentEncodeAbilityXml(CMarkup &struMarkUp)
{
    if (struMarkUp.FindElem("CurrentCompressInfo"))
    {
        struMarkUp.IntoElem();

        ParseVideoEncodeTypeXml(struMarkUp);
        ParseVideoResolutionXml(struMarkUp);
        ParseVideoFrameRateXml(struMarkUp, m_struCurrentEncode.byVideoFrameRate, ARRAY_SIZE(m_struCurrentEncode.byVideoFrameRate));
        ParseSubChanlList(struMarkUp);

        struMarkUp.OutOfElem();
    }
    return TRUE;
}

BOOL CDlgCurrentEncodeAbility::ParseVideoEncodeTypeXml(CMarkup &struMarkUp)
{
    if (struMarkUp.FindElem("VideoEncodeType"))
    {
        m_struCurrentEncode.byVideoEncodeType = atoi(struMarkUp.GetData());
    }
    else
    {
        TRACE("Fail to find VideoEncodeType");
    }
    return TRUE;
}

BOOL CDlgCurrentEncodeAbility::ParseVideoResolutionXml(CMarkup &struMarkUp)
{
    if (struMarkUp.FindElem("VideoResolution"))
    {
        m_struCurrentEncode.byResolution = atoi(struMarkUp.GetData());
    }
    else
    {
        TRACE("Fail to find VideoResolution");
    }
    return TRUE;
}

BOOL CDlgCurrentEncodeAbility::ParseVideoFrameRateXml(CMarkup &struMarkUp, BYTE *byVideoFramRate, DWORD dwSize)
{
    if (struMarkUp.FindElem("VideoFrameRate"))
    {
        struMarkUp.IntoElem();

        if (struMarkUp.FindElem("Range"))
        {
            CString str;
            str = struMarkUp.GetData();
            ParseStrIndex(str, byVideoFramRate, dwSize);
        }
        struMarkUp.OutOfElem();
    }
    else
    {
        TRACE("Fail to find VideoFrameRate");
    }
    return TRUE;
}

BOOL CDlgCurrentEncodeAbility::ParseSubChanlList(CMarkup &struMarkup)
{
    int nIndex = 0;
    if (struMarkup.FindElem("SubChannelList"))
    {
        struMarkup.IntoElem();
        while (struMarkup.FindElem("SubChannelEntry"))
        {
            struMarkup.IntoElem();
            if (struMarkup.FindElem("index"))
            {
                 int ichannel =atoi(struMarkup.GetData());
                 while (struMarkup.FindElem("VideoResolutionList"))
                 {
                     struMarkup.IntoElem();
                     ParseResolutionEntry(struMarkup, ichannel -1);
                     struMarkup.OutOfElem();
                 }
            }
            nIndex++;
            struMarkup.OutOfElem();
        }

       m_struCurrentEncode.byChanNum = nIndex;
       
       struMarkup.OutOfElem();
    }
    else
    {
        TRACE("Fail to find SubChannelList");
    }
    return TRUE;
}

BOOL CDlgCurrentEncodeAbility::ParseResolutionEntry(CMarkup &struMarkup, int nChanIndex)
{
//     <VideoResolutionEntry>
//         <index>1</index>
//         <VideoFrameRate>
//         <Range>0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16</Range>
//         </VideoFrameRate>

    int nIndex = 0;
    while (struMarkup.FindElem("VideoResolutionEntry"))
    {
        struMarkup.IntoElem();
        if (struMarkup.FindElem("index"))
        {
            m_struCurrentEncode.struSubChanList[nChanIndex].struResolutionEntry[nIndex].byResolutionIndex = atoi(struMarkup.GetData());
        }
        struMarkup.OutOfElem();
        ParseVideoFrameRateXml(struMarkup, m_struCurrentEncode.struSubChanList[nChanIndex].struResolutionEntry[nIndex].byVideoFrameRate, ARRAY_SIZE(m_struCurrentEncode.struSubChanList[nChanIndex].struResolutionEntry[nIndex].byVideoFrameRate));
        nIndex ++;
    }
    m_struCurrentEncode.struSubChanList[nChanIndex].dwResolutionEntryNum = nIndex;
    return TRUE;
}

void CDlgCurrentEncodeAbility::SetCurrentEncodeParamToWnd(CURRENT_ENCODE_PARAM &struEncodeParam)
{

}

void CDlgCurrentEncodeAbility::SetSubChanListToWnd(SUB_CHAN_LIST &struSbuChanList)
{

}
void CDlgCurrentEncodeAbility::SetResolutionEntry(RESOLUTION_ENTRY &struResolutionEntry)
{

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
void CDlgCurrentEncodeAbility::ParseStrIndex(CString strIndex, byte* array, int iArrayLength)
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