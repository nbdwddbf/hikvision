// DlgIOOutCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgIOOutCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIOOutCfg dialog


CDlgIOOutCfg::CDlgIOOutCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIOOutCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIOOutCfg)
	m_bChkFlashLightEnable = FALSE;
	m_byEndHour = 0;
	m_byDutyRatio = 0;
	m_byEndMin = 0;
	m_byFreqMulti = 0;
	m_byStartHour = 0;
	m_byStartMin = 0;
	//}}AFX_DATA_INIT

	memset(&m_struIOOutCfgCond, 0, sizeof(NET_DVR_IOOUT_COND));
	memset(&m_struIOOutCfg, 0 , sizeof(NET_DVR_IOOUT_CFG));

}

void CDlgIOOutCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIOOutCfg)
	DDX_Control(pDX, IDC_COMBO_DEFAULTSTATE, m_cbDefaultState);
	DDX_Control(pDX, IDC_COMBO_WORKSTATE, m_cbWorkState);
	DDX_Control(pDX, IDC_COMBO_WORKMODE, m_cbWorkMode);
	DDX_Control(pDX, IDC_COMBO_SYNC_OUTPUTNO, m_cbSyncOutputNo);
	DDX_Check(pDX, IDC_CHECK_ENABLE_FLASHLIGHT, m_bChkFlashLightEnable);
	DDX_Text(pDX, IDC_EDIT_ENDHOUR, m_byEndHour);
	DDX_Text(pDX, IDC_EDIT_DUTYRATIO, m_byDutyRatio);
	DDX_Text(pDX, IDC_EDIT_ENDMIN, m_byEndMin);
	DDX_Text(pDX, IDC_EDIT_FREQMULTI, m_byFreqMulti);
	DDX_Text(pDX, IDC_EDIT_STARTHOUR, m_byStartHour);
	DDX_Text(pDX, IDC_EDIT_STARTMIN, m_byStartMin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIOOutCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgIOOutCfg)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_FLASHLIGHT, OnCheckEnableFlashlight)
	ON_CBN_SELCHANGE(IDC_COMBO_WORKMODE, OnSelchangeComboWorkmode)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_CBN_SELCHANGE(IDC_COMBO_SYNC_OUTPUTNO, OnSelchangeComboSyncOutputno)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIOOutCfg message handlers

void CDlgIOOutCfg::OnButtonGet() 
{
	// TODO: Add your control notification handler code here
	
	//获取前清空
	memset(&m_struIOOutCfg,0,sizeof(NET_DVR_IOOUT_CFG));
	m_struIOOutCfgCond.bySyncOutputNo = m_cbSyncOutputNo.GetCurSel();

	m_struIOOutCfgCond.dwSize = sizeof(NET_DVR_IOOUT_COND);
	m_struIOOutCfg.dwSize = sizeof(NET_DVR_IOOUT_CFG);
 
	CString strErr;
  	BOOL bRet = NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_IOOUT_CFG, 1, &m_struIOOutCfgCond, \
		sizeof(NET_DVR_IOOUT_COND),&m_iStatus, &m_struIOOutCfg,	sizeof(NET_DVR_IOOUT_CFG));
	if (bRet)
	{
		if (m_iStatus == 0) 
		{
			UpdateCtrlData(); //更新并显示第i索引的数据
		 	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_IOOUT_CFG Suss!");
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_IOOUT_CFG Failed!");
		}
	}
	else
	{
		strErr.Format("NET_DVR_GET_IOOUT_CFG failed! err Code[%d]", NET_DVR_GetLastError());
		MessageBox(strErr);
		return;
	}	
	UpdateData(FALSE);
}

BOOL CDlgIOOutCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cbSyncOutputNo.SetCurSel(0);
	EnableWindows(TRUE);
	EnableTimeCtrl(m_bChkFlashLightEnable);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgIOOutCfg::UpdateCtrlData()
{
	m_cbWorkMode.SetCurSel(m_struIOOutCfg.byWorkMode);
	if (m_struIOOutCfg.byWorkMode == 1) //如果是频闪模式
	{
		EnableWindows(TRUE); //控件窗口使能
		m_cbWorkState.SetCurSel(m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.byWorkState);
		m_cbDefaultState.SetCurSel(m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.byDefaultState);
		m_byFreqMulti = m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.byFreqMulti;
		m_byDutyRatio = m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.byDutyRatio;
		m_bChkFlashLightEnable = m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.byFlashLightEnable;
			
		if (m_bChkFlashLightEnable)
		{
			EnableTimeCtrl(TRUE); //使能时间控制
			m_byStartHour = m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.struFlashLightTime.byStartHour;
			m_byStartMin = m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.struFlashLightTime.byStartMin;
			m_byEndHour = m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.struFlashLightTime.byStopHour;
			m_byEndMin = m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.struFlashLightTime.byStopMin;
		}
		else
			EnableTimeCtrl(FALSE);
	}
	else
	{
		EnableWindows(FALSE); //当前界面显示参数无效
		EnableTimeCtrl(FALSE);
	}
	UpdateData(FALSE);
}

void CDlgIOOutCfg::EnableWindows(BOOL bEnable)
{
	GetDlgItem(IDC_STATIC_DEFAULTSTATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_DEFAULTSTATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_STATIC_WORKSTATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_WORKSTATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_STATIC_FREQMULTI)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_FREQMULTI)->EnableWindow(bEnable);
	GetDlgItem(IDC_STATIC_DUTYRATIO)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_DUTYRATIO)->EnableWindow(bEnable);
	GetDlgItem(IDC_STATIC_PERCENT)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_ENABLE_FLASHLIGHT)->EnableWindow(bEnable);
// 	GetDlgItem(IDC_STATIC_STARTTIME)->EnableWindow(bEnable);
// 	GetDlgItem(IDC_EDIT_STARTHOUR)->EnableWindow(bEnable);
// 	GetDlgItem(IDC_STATIC_STARTHOUR)->EnableWindow(bEnable);
// 	GetDlgItem(IDC_EDIT_STARTMIN)->EnableWindow(bEnable);
// 	GetDlgItem(IDC_STATIC_STARTMIN)->EnableWindow(bEnable);
// 	GetDlgItem(IDC_STATIC_ENDTIME)->EnableWindow(bEnable);
// 	GetDlgItem(IDC_EDIT_ENDHOUR)->EnableWindow(bEnable);
// 	GetDlgItem(IDC_STATIC_ENDHOUR)->EnableWindow(bEnable);
// 	GetDlgItem(IDC_EDIT_ENDMIN)->EnableWindow(bEnable);
// 	GetDlgItem(IDC_STATIC_ENDMIN)->EnableWindow(bEnable);

	UpdateData(TRUE);//控件有效的前提下才去判断时间控件是否有效
	if (bEnable)
	{
		EnableTimeCtrl(m_bChkFlashLightEnable);
	}
	else
	{
		EnableTimeCtrl(FALSE);
	}
}

void CDlgIOOutCfg::EnableTimeCtrl(BOOL bEnable)
{
	GetDlgItem(IDC_STATIC_STARTTIME)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_STARTHOUR)->EnableWindow(bEnable);
	GetDlgItem(IDC_STATIC_STARTHOUR)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_STARTMIN)->EnableWindow(bEnable);
	GetDlgItem(IDC_STATIC_STARTMIN)->EnableWindow(bEnable);
	GetDlgItem(IDC_STATIC_ENDTIME)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_ENDHOUR)->EnableWindow(bEnable);
	GetDlgItem(IDC_STATIC_ENDHOUR)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_ENDMIN)->EnableWindow(bEnable);
	GetDlgItem(IDC_STATIC_ENDMIN)->EnableWindow(bEnable);
}

void CDlgIOOutCfg::OnCheckEnableFlashlight() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	EnableTimeCtrl(m_bChkFlashLightEnable);
}

void CDlgIOOutCfg::OnSelchangeComboWorkmode() 
{
	// TODO: Add your control notification handler code here
	if (m_cbWorkMode.GetCurSel() == 0)
	{
		EnableWindows(FALSE);
	}
	else
		EnableWindows(TRUE);
}

void CDlgIOOutCfg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	
	SaveData();
	char szLan[128]={0};
	if (m_cbWorkMode.GetCurSel() == -1)	 	
	{
		g_StringLanType(szLan,"请选择要配置的工作模式!","please select the work mode to be set!");
		MessageBox(szLan);
		return;
	}

	m_struIOOutCfgCond.dwSize = sizeof(NET_DVR_IOOUT_COND);
	m_struIOOutCfg.dwSize = sizeof(NET_DVR_IOOUT_CFG);

	CString strErr;
	BOOL bRet = NET_DVR_SetDeviceConfig(m_lUserID,NET_DVR_SET_IOOUT_CFG,1,&m_struIOOutCfgCond,sizeof(NET_DVR_IOOUT_COND),\
							&m_iStatus,&m_struIOOutCfg,sizeof(NET_DVR_IOOUT_CFG));
	if (bRet)
	{
		if (m_iStatus== 0) 
		{
 			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, " NET_DVR_SET_IOOUT_CFG Suss!");
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_IOOUT_CFG Failed!");
		}
	}
	else
	{
		strErr.Format("NET_DVR_SET_IOOUT_CFG failed! err Code[%d]", NET_DVR_GetLastError());
		MessageBox(strErr);
	}
}

void CDlgIOOutCfg::SaveData()
{
	UpdateData(TRUE);
	char szLan[128]={0};
	m_struIOOutCfgCond.bySyncOutputNo = m_cbSyncOutputNo.GetCurSel();
	
	m_struIOOutCfg.byWorkMode = m_cbWorkMode.GetCurSel();
	if (m_cbWorkMode.GetCurSel() == 0) //若是报警输出模式，不进行参数配置
	{
		EnableWindows(FALSE);
		memset(&m_struIOOutCfg,0,sizeof(NET_DVR_IOOUT_CFG)); //全部清0
		m_struIOOutCfg.dwSize = sizeof(NET_DVR_IOOUT_CFG); //只给dwsize赋值
		return;
	}
	
	if(m_cbWorkState.GetCurSel() == -1 || m_cbDefaultState.GetCurSel() == -1)
	{
		g_StringLanType(szLan,"生效状态或默认状态无效!","Work state or Default state is invalid!");
		MessageBox(szLan);
		return;
	}
	
	m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.byDefaultState = m_cbDefaultState.GetCurSel();
	m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.byWorkState = m_cbWorkState.GetCurSel();
	m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.byFreqMulti = m_byFreqMulti;
	m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.byDutyRatio = m_byDutyRatio;
	m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.byFlashLightEnable = m_bChkFlashLightEnable;
	
	if (m_bChkFlashLightEnable == 0)
	{
		memset(&m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.struFlashLightTime,0,sizeof(NET_DVR_SCHEDTIME)); //将时间赋值为全0
	}
	else
	{
		m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.struFlashLightTime.byStartHour = m_byStartHour;
		m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.struFlashLightTime.byStartMin = m_byStartMin;
		m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.struFlashLightTime.byStopHour = m_byEndHour;
		m_struIOOutCfg.uWorkModeInfo.struStrobeLamp.struFlashLightTime.byStopMin = m_byEndMin;
	}
}

void CDlgIOOutCfg::OnSelchangeComboSyncOutputno() 
{
	// TODO: Add your control notification handler code here
	OnButtonGet();
}
