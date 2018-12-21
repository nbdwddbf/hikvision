// DlgTransAutoReboot.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTransAutoReboot.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTransAutoReboot dialog


CDlgTransAutoReboot::CDlgTransAutoReboot(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTransAutoReboot::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTransAutoReboot)
	m_byHour = 0;
	m_byMinute = 0;
	m_BEnableVCADec = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgTransAutoReboot::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTransAutoReboot)	
	DDX_Control(pDX, IDC_COMBO_DISPLAY_MODE, m_comboDisplayMode);
	DDX_Control(pDX, IDC_COMBO_WORKMODE, m_comboWorkMode);
	DDX_Control(pDX, IDC_COMBO_REBOOT_DATE, m_comboRebootDate);
	DDX_Control(pDX, IDC_COMBO_AUTO_REBOOT_MODE, m_comboAutoRebootMode);
	DDX_Text(pDX, IDC_EDIT_HOUR, m_byHour);
	DDV_MinMaxByte(pDX, m_byHour, 0, 23);
	DDX_Text(pDX, IDC_EDIT_MINUTE, m_byMinute);
	DDV_MinMaxByte(pDX, m_byMinute, 0, 59);
	DDX_Check(pDX, IDC_CHK_ENABLEVCADEC, m_BEnableVCADec);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTransAutoReboot, CDialog)
	//{{AFX_MSG_MAP(CDlgTransAutoReboot)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTransAutoReboot message handlers

BOOL CDlgTransAutoReboot::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);

	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	memset(&m_struAutoReboot, 0, sizeof(m_struAutoReboot));
	memset(&m_struDevWorkMode, 0, sizeof(m_struDevWorkMode));

	int  i = 0;
	CString cs;
	DWORD dwReturn = 0;
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_DEV_WORK_MODE, 0, &m_struDevWorkMode, sizeof(m_struDevWorkMode), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRANS_DEV_WORK_MODE");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRANS_DEV_WORK_MODE");
		m_comboWorkMode.SetCurSel(m_struDevWorkMode.byWorkMode - 1);
		m_comboDisplayMode.SetCurSel(m_struDevWorkMode.byDisplayMode);
        m_BEnableVCADec = m_struDevWorkMode.byEnableVcaDec;
	}

	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_AUTO_REBOOT_CFG, 0, &m_struAutoReboot, sizeof(m_struAutoReboot), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_AUTO_REBOOT_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_AUTO_REBOOT_CFG");
		m_comboAutoRebootMode.SetCurSel(m_struAutoReboot.struRebootTime.byRebootMode);
		if (m_struAutoReboot.struRebootTime.byRebootMode == 0)
		{
			m_comboRebootDate.AddString("Monday");
			m_comboRebootDate.AddString("Tuesday");
			m_comboRebootDate.AddString("Wednesday");
			m_comboRebootDate.AddString("Thursday");
			m_comboRebootDate.AddString("Friday");
			m_comboRebootDate.AddString("Saturday");
			m_comboRebootDate.AddString("Sunday");
		}
		else
		{
			for (i = 0; i < 31; i++)
			{
				cs.Format("%d", i + 1);
				m_comboRebootDate.AddString(cs);
			}
		}
		m_comboRebootDate.SetCurSel(m_struAutoReboot.struRebootTime.byDate - 1);
		m_byHour = m_struAutoReboot.struRebootTime.byHour;
		m_byMinute = m_struAutoReboot.struRebootTime.byMinute;
		UpdateData(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTransAutoReboot::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};	

	m_struAutoReboot.dwSize = sizeof(m_struAutoReboot);
	m_struAutoReboot.struRebootTime.byDate = m_comboRebootDate.GetCurSel() + 1;
	m_struAutoReboot.struRebootTime.byHour = m_byHour;
	m_struAutoReboot.struRebootTime.byMinute = m_byMinute;	

	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_AUTO_REBOOT_CFG, 0, &m_struAutoReboot, sizeof(m_struAutoReboot)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_AUTO_REBOOT_CFG");
		AfxMessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_AUTO_REBOOT_CFG");		
	}
	

	if (m_struDevWorkMode.byWorkMode == m_comboWorkMode.GetCurSel() + 1 &&
		m_struDevWorkMode.byDisplayMode == m_comboDisplayMode.GetCurSel())
	{
		return;
	}
	g_StringLanType(szLan, "切换工作模式后设备将重启，是否继续?", "Device will reboot after switching work mode,continue?");
	if (IDOK!=MessageBox(szLan, "Warning",IDOK))
	{
		return;
	}
	m_struDevWorkMode.dwSize = sizeof(m_struDevWorkMode);	
	m_struDevWorkMode.byWorkMode = m_comboWorkMode.GetCurSel() + 1;
	m_struDevWorkMode.byDisplayMode = m_comboDisplayMode.GetCurSel();
	m_struDevWorkMode.byEnableVcaDec = m_BEnableVCADec; 
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_DEV_WORK_MODE, 0, &m_struDevWorkMode, sizeof(m_struDevWorkMode)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_DEV_WORK_MODE");
		AfxMessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_DEV_WORK_MODE");
		g_StringLanType(szLan, "模式切换成功吗，正在重启", "Mode switch success, rebooting...");
		return;
	}

	//AfxMessageBox("Success");
}

void CDlgTransAutoReboot::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;	

	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_AUTO_REBOOT_CFG, 0, &m_struAutoReboot, sizeof(m_struAutoReboot), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_AUTO_REBOOT_CFG");
		AfxMessageBox(NET_DVR_GetErrorMsg());
	}
	else
	{
		m_byHour = m_struAutoReboot.struRebootTime.byHour;
		m_byMinute = m_struAutoReboot.struRebootTime.byMinute;
		m_comboRebootDate.SetCurSel(m_struAutoReboot.struRebootTime.byDate - 1);
		m_comboAutoRebootMode.SetCurSel(m_struAutoReboot.struRebootTime.byRebootMode);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_AUTO_REBOOT_CFG");		
	}

	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_DEV_WORK_MODE, 0, &m_struDevWorkMode, sizeof(m_struDevWorkMode), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRANS_DEV_WORK_MODE");
		AfxMessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRANS_DEV_WORK_MODE");
		m_comboWorkMode.SetCurSel(m_struDevWorkMode.byWorkMode - 1);
		m_comboDisplayMode.SetCurSel(m_struDevWorkMode.byDisplayMode);

	}

	AfxMessageBox("Success");
	UpdateData(FALSE);
}
