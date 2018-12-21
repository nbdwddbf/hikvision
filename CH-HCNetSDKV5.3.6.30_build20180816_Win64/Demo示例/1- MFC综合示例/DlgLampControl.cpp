// DlgLampControl.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLampControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLampControl dialog


CDlgLampControl::CDlgLampControl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLampControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLampControl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgLampControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLampControl)
	DDX_Control(pDX, IDC_COMBO_LAMP_STATE_NO, m_comboLampStateNo);
	DDX_Control(pDX, IDC_COMBO_LAMP_NO, m_comboLampNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLampControl, CDialog)
	//{{AFX_MSG_MAP(CDlgLampControl)
	ON_BN_CLICKED(IDC_BTN_CONTROL, OnBtnControl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLampControl message handlers

void CDlgLampControl::OnBtnControl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int lampNo = m_comboLampNo.GetCurSel() + 1;
	int lampStateNo = m_comboLampStateNo.GetCurSel() + 1;
	NET_DVR_LAMP_CONTROL struLampControl = {0};
	struLampControl.dwSize = sizeof(NET_DVR_LAMP_CONTROL);
	struLampControl.byLampStateNo = lampStateNo;
	struLampControl.byLampNo = lampNo;
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	if(!NET_DVR_RemoteControl(lUserID,NET_DVR_LAMP_REMOTE_CONTROL,&struLampControl,sizeof(NET_DVR_LAMP_CONTROL)))
	{
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_LAMP_REMOTE_CONTROL");
		char szLan[1024] = {0};
		sprintf(szLan,"NET_DVR_LAMP_REMOTE_CONTROL failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}
}
