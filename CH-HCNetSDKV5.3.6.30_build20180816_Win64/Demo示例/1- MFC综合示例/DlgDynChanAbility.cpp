// DlgDynChanAbility.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgDynChanAbility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDynChanAbility dialog


CDlgDynChanAbility::CDlgDynChanAbility(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDynChanAbility::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDynChanAbility)
	m_dwChannelNO = 1;
	//}}AFX_DATA_INIT
}


void CDlgDynChanAbility::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDynChanAbility)
	DDX_Text(pDX, IDC_EDIT_CHANNEL_NO, m_dwChannelNO);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDynChanAbility, CDialog)
	//{{AFX_MSG_MAP(CDlgDynChanAbility)
	ON_BN_CLICKED(IDC_BTN_GET_ABILITY, OnBtnGetAbility)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDynChanAbility message handlers
BOOL CDlgDynChanAbility::WirteBufToFile(char *pBuf, DWORD dwBufSize)
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

void CDlgDynChanAbility::OnBtnGetAbility() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_pRecvBuf = new char[2*1024*1024];
	memset(m_pRecvBuf,0,2*1024*1024);

	char sSendBuf[1024];
	memset(sSendBuf, 0, 1024);
	sprintf(sSendBuf, "<DynChannelAbility><channelNO>%d</channelNO></DynChannelAbility>", m_dwChannelNO);
    if (NET_DVR_GetDeviceAbility(m_lServerID, DEVICE_DYNCHAN_ABILITY, sSendBuf, strlen(sSendBuf), m_pRecvBuf, 2*1024*1024))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "DEVICE_DYNCHAN_ABILITY");
		WirteBufToFile(m_pRecvBuf, strlen(m_pRecvBuf));
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "DEVICE_DYNCHAN_ABILITY");
    }
}
