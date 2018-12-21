// DlgFrameCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgFrameCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFrameCtrl dialog


CDlgFrameCtrl::CDlgFrameCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFrameCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFrameCtrl)
	m_iChannel = 0;
    m_lUser = -1;
    m_iDeviceIndex = 0;
	//}}AFX_DATA_INIT
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
}


void CDlgFrameCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFrameCtrl)
	DDX_Control(pDX, IDC_COMBO_STREAMTYPE, m_comboStreamType);
	DDX_Text(pDX, IDC_EDIT_CHANNEL, m_iChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFrameCtrl, CDialog)
	//{{AFX_MSG_MAP(CDlgFrameCtrl)
	ON_BN_CLICKED(IDC_BTN_REFRESH_FRAME, OnBtnRefreshFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFrameCtrl message handlers

void CDlgFrameCtrl::OnBtnRefreshFrame() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[128] = {0};
    NET_DVR_STREAMING_COND m_struStreamingCond = {0};
    m_struStreamingCond.dwSize = sizeof(m_struStreamingCond);
    m_struStreamingCond.dwChannel = m_iChannel;
    m_struStreamingCond.byStreamType = m_comboStreamType.GetCurSel();
    
    NET_DVR_STD_CONTROL struControl = {0};
    struControl.lpCondBuffer = &m_struStreamingCond;
    struControl.dwCondSize = sizeof(m_struStreamingCond);
    
    memset(m_szStatusBuf, 0, 1024);
    struControl.lpStatusBuffer = m_szStatusBuf;
    struControl.dwStatusSize = 1024;
    
    if(!NET_DVR_STDControl(m_lUser, NET_DVR_STREAMING_REFRESH_FRAME, &struControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STREAMING_REFRESH_FRAME");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STREAMING_REFRESH_FRAME");
    }
    
}
