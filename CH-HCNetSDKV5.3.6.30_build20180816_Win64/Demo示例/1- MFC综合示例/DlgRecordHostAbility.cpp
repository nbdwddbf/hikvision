// DlgRecordHostAbility.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordHostAbility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgRecordHostAbility dialog


DlgRecordHostAbility::DlgRecordHostAbility(CWnd* pParent /*=NULL*/)
	: CDialog(DlgRecordHostAbility::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgRecordHostAbility)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_iDevIndex = -1;
    m_pRecvBuf = NULL;
    m_pSendBuf = NULL;
}


void DlgRecordHostAbility::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgRecordHostAbility)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgRecordHostAbility, CDialog)
	//{{AFX_MSG_MAP(DlgRecordHostAbility)
		// NOTE: the ClassWizard will add message map macros here
		ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgRecordHostAbility message handlers
BOOL DlgRecordHostAbility::OnInitDialog() 
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
    GetITCAbility();
	
    UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL DlgRecordHostAbility::GetITCAbility()
{
    memset(m_pRecvBuf, 0, XML_BUF);
	//	strcpy(m_pSendBuf,"<AudioVideoCompressInfo><ChannelNumber>17</ChannelNumber></AudioVideoCompressInfo>");
    strcpy(m_pSendBuf,"<RecordingHostAbility version='2.0'></RecordingHostAbility >");
	
    if (!NET_DVR_GetDeviceAbility(m_lServerID, DEVICE_ABILITY_INFO, m_pSendBuf, strlen(m_pSendBuf), m_pRecvBuf, XML_BUF))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "DEVICE_ABILITY_INFO-EventAbility ");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "DEVICE_ABILITY_INFO-EventAbility ");
    }
	
	WirteBufToFile(m_pRecvBuf, strlen(m_pRecvBuf));
	
	return TRUE;
}

BOOL DlgRecordHostAbility::WirteBufToFile(char *pBuf, DWORD dwBufSize)
{
    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    char cFilename[256] = {0};
    sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
    
    sprintf(cFilename, "%s\\EventAbility_%s.xml", g_struLocalParam.chPictureSavePath, chTime);
    
    
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

void DlgRecordHostAbility::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
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
}