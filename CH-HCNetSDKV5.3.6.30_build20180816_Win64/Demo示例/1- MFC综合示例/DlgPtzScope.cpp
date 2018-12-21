// DlgPtzScope.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPtzScope.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPtzScope dialog


CDlgPtzScope::CDlgPtzScope(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPtzScope::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPtzScope)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_lChannel = -1;
    memset(&m_struPtzScope, 0, sizeof(m_struPtzScope));
}


void CDlgPtzScope::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPtzScope)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPtzScope, CDialog)
	//{{AFX_MSG_MAP(CDlgPtzScope)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPtzScope message handlers

BOOL CDlgPtzScope::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    GetPtzScope(m_struPtzScope);
    SetPtzScoprToWnd(m_struPtzScope);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPtzScope::SetPtzScoprToWnd(NET_DVR_PTZSCOPE &struPtzScope)
{
    char szLan[128] = {0};
    sprintf(szLan, "p Value Max:0x%x  Min:0x%x", struPtzScope.wPanPosMax, struPtzScope.wPanPosMin);
    GetDlgItem(IDC_STATIC_P_RANGE)->SetWindowText(szLan);
    sprintf(szLan, "T Value Max:0x%x  Min:0x%x", struPtzScope.wTiltPosMax, struPtzScope.wTiltPosMin);
    GetDlgItem(IDC_STATIC_T_RANGE)->SetWindowText(szLan);
    sprintf(szLan, "Z Value Max:0x%x  Min:0x%x", struPtzScope.wZoomPosMax, struPtzScope.wZoomPosMin);
    GetDlgItem(IDC_STATIC_Z_RANGE)->SetWindowText(szLan);

}

BOOL CDlgPtzScope::GetPtzScope(NET_DVR_PTZSCOPE &struPtzScope)
{
    DWORD dwReturn;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PTZSCOPE, m_lChannel, &struPtzScope, sizeof(struPtzScope), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PTZSCOPE");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZSCOPE");
        return FALSE;
    }

}
