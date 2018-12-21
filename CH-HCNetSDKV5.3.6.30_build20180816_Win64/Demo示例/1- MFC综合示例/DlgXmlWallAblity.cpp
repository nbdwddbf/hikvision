// DlgXmlWallAblity.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgXmlWallAblity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgXmlWallAblity dialog


CDlgXmlWallAblity::CDlgXmlWallAblity(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXmlWallAblity::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgXmlWallAblity)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_iDevIndex = -1;
    m_pRecvBuf = NULL;
}


void CDlgXmlWallAblity::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgXmlWallAblity)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgXmlWallAblity, CDialog)
	//{{AFX_MSG_MAP(CDlgXmlWallAblity)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgXmlWallAblity message handlers

BOOL CDlgXmlWallAblity::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
	if (NULL == m_pRecvBuf)
    {
        m_pRecvBuf = new char[XML_BUF];
		memset(m_pRecvBuf, 0, XML_BUF);
    }	
	
    GetWallAbility();	
    UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgXmlWallAblity::GetWallAbility()
{
	if (NET_DVR_GetDeviceAbility(m_lServerID, WALL_ABILITY, NULL,0, m_pRecvBuf, XML_BUF))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "WALL_ABILITY");
		WirteBufToFile(m_pRecvBuf, strlen(m_pRecvBuf));
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "WALL_ABILITY");
    }
}

BOOL CDlgXmlWallAblity::WirteBufToFile(char *pBuf, DWORD dwBufSize)
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


void CDlgXmlWallAblity::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_pRecvBuf != NULL)
    {
        delete []m_pRecvBuf;
        m_pRecvBuf = NULL;
    }
}
