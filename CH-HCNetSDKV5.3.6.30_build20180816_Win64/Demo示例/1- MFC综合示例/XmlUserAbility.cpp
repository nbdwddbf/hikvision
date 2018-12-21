// XmlUserAbility.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "XmlUserAbility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXmlUserAbility dialog


CXmlUserAbility::CXmlUserAbility(CWnd* pParent /*=NULL*/)
	: CDialog(CXmlUserAbility::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXmlUserAbility)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_iDevIndex = -1;
    m_pRecvBuf = NULL;
    m_pSendBuf = NULL;
}


void CXmlUserAbility::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXmlUserAbility)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXmlUserAbility, CDialog)
	//{{AFX_MSG_MAP(CXmlUserAbility)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXmlUserAbility message handlers
BOOL CXmlUserAbility::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    if (NULL == m_pRecvBuf)
    {
        m_pRecvBuf = new char[XML_BUF];
		memset(m_pRecvBuf, 0, XML_BUF);
    }
    
    if (NULL == m_pSendBuf)
    {
        m_pSendBuf = new char[XML_BUF];
		memset(m_pSendBuf, 0, XML_BUF);
    }
	//////////////////////////////////////////////////////////////////////////
	//	GetCurrentEncodeAbility();
	//	WirteBufToFile(m_pRecvBuf,strlen(m_pRecvBuf));
	//////////////////////////////////////////////////////////////////////////
    GetUserAbility();
	
    UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CXmlUserAbility::GetUserAbility()
{
    memset(m_pRecvBuf, 0, XML_BUF);
	//	strcpy(m_pSendBuf,"<AudioVideoCompressInfo><ChannelNumber>17</ChannelNumber></AudioVideoCompressInfo>");
    strcpy(m_pSendBuf,"<UserAbility>version=\"2.0\"</UserAbility>");
	
    if (!NET_DVR_GetDeviceAbility(m_lServerID, DEVICE_USER_ABILITY, m_pSendBuf, strlen(m_pSendBuf), m_pRecvBuf, XML_BUF))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "DEVICE_USER_ABILITY");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "DEVICE_USER_ABILITY");
    }
	
	WirteBufToFile(m_pRecvBuf, strlen(m_pRecvBuf));
	
	return TRUE;
}

BOOL CXmlUserAbility::WirteBufToFile(char *pBuf, DWORD dwBufSize)
{
    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    char cFilename[256] = {0};
    sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
    
    sprintf(cFilename, "%s\\user_%s.xml", g_struLocalParam.chPictureSavePath, chTime);
    
    
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
