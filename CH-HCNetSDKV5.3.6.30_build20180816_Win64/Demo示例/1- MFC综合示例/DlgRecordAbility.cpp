// DlgRecordAbility.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordAbility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordAbility dialog


CDlgRecordAbility::CDlgRecordAbility(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecordAbility::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRecordAbility)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRecordAbility::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecordAbility)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRecordAbility, CDialog)
	//{{AFX_MSG_MAP(CDlgRecordAbility)
	ON_BN_CLICKED(IDC_BTN_GET_ABILITY, OnBtnGetAbility)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordAbility message handlers

BOOL CDlgRecordAbility::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgRecordAbility::WirteBufToFile(char *pBuf, DWORD dwBufSize)
{
    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    char cFilename[256] = {0};
    sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
    
    sprintf(cFilename, "%s\\DYNCHAN_%s.xml", g_struLocalParam.chPictureSavePath, chTime);
    
    
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

void CDlgRecordAbility::OnBtnGetAbility() 
{
	// TODO: Add your control notification handler code here
	m_pRecvBuf = new char[2*1024*1024];
	memset(m_pRecvBuf,0,2*1024*1024);
	
	char sSendBuf[1024];
	memset(sSendBuf, 0, 1024);
	strcpy(sSendBuf, "<RecordAbility version=\"2.0\"></RecordAbility>");
    if (NET_DVR_GetDeviceAbility(m_lServerID, DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), m_pRecvBuf, 2*1024*1024))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "DEVICE_ABILITY_INFO RecordAbility");
		WirteBufToFile(m_pRecvBuf, strlen(m_pRecvBuf));
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "DEVICE_ABILITY_INFO RecordAbility");
    }

    delete[] m_pRecvBuf;
}
