// DlgChanInputAbility.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgChanInputAbility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgChanInputAbility dialog


CDlgChanInputAbility::CDlgChanInputAbility(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChanInputAbility::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgChanInputAbility)
	m_dwChannelNum = 0;
	//}}AFX_DATA_INIT
}


void CDlgChanInputAbility::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChanInputAbility)
	DDX_Text(pDX, IDC_EDIT_CHANNEL_NO, m_dwChannelNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChanInputAbility, CDialog)
	//{{AFX_MSG_MAP(CDlgChanInputAbility)
	ON_BN_CLICKED(IDC_BTN_GET_ABILITY, OnBtnGetAbility)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChanInputAbility message handlers

BOOL CDlgChanInputAbility::WirteBufToFile(char *pBuf, DWORD dwBufSize)
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

void CDlgChanInputAbility::OnBtnGetAbility() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_pRecvBuf = new char[2*1024*1024];
	memset(m_pRecvBuf,0,2*1024*1024);
	
	char sSendBuf[1024];
	memset(sSendBuf, 0, 1024);
	sprintf(sSendBuf, "<ChannelInputAbility ><channelNO>%d</channelNO></ChannelInputAbility >", m_dwChannelNum);
    if (NET_DVR_GetDeviceAbility(m_lServerID, DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), m_pRecvBuf, 2*1024*1024))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "DEVICE_ABILITY_INFO ChannelInputAbility");
		WirteBufToFile(m_pRecvBuf, strlen(m_pRecvBuf));
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "DEVICE_ABILITY_INFO ChannelInputAbility");
    }
}

BOOL CDlgChanInputAbility::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_dwChannelNum = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
