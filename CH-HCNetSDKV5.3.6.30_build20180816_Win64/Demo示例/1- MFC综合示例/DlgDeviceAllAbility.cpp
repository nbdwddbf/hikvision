// DlgDeviceAllAbility.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgDeviceAllAbility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceAllAbility dialog


CDlgDeviceAllAbility::CDlgDeviceAllAbility(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDeviceAllAbility::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDeviceAllAbility)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_lResolution = -1;
    m_lEncodeType = -1;
    m_pRecvBuf = NULL;
    m_pSendBuf = NULL;
}


void CDlgDeviceAllAbility::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDeviceAllAbility)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDeviceAllAbility, CDialog)
	//{{AFX_MSG_MAP(CDlgDeviceAllAbility)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceAllAbility message handlers

BOOL CDlgDeviceAllAbility::OnInitDialog() 
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

    FormatSendBufXml(m_pSendBuf);
    GetDeviceAllAbility(m_pSendBuf, strlen(m_pSendBuf));
    
    WirteBufToFile(m_pRecvBuf, strlen(m_pRecvBuf));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDeviceAllAbility::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
    if (m_pSendBuf != NULL)
    {   
        delete []m_pSendBuf;
        m_pSendBuf = NULL;
    }

    if (m_pRecvBuf != NULL)
    {
        delete []m_pSendBuf;
        m_pSendBuf = NULL;
    }

	CDialog::PostNcDestroy();
}

BOOL CDlgDeviceAllAbility::FormatSendBufXml(char *pSendBuf)
{
    sprintf(pSendBuf,"<CurrentCompressInfo><VideoEncodeType>%d</VideoEncodeType><VideoResolution>%d</VideoResolution></CurrentCompressInfo>", m_lEncodeType, m_lResolution);
    return TRUE;
}

BOOL CDlgDeviceAllAbility::GetDeviceAllAbility(char *pSendBuf, DWORD dwBufSize)
{
    if (NET_DVR_GetDeviceAbility(m_lServerID, DEVICE_ALL_ABILITY, pSendBuf, dwBufSize, m_pRecvBuf, XML_BUF))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "DEVICE_ALL_ABILITY");
        return TRUE;
    } 
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "DEVICE_ALL_ABILITY");
        return FALSE;
    }
}

BOOL CDlgDeviceAllAbility::WirteBufToFile(char *pBuf, DWORD dwBufSize)
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