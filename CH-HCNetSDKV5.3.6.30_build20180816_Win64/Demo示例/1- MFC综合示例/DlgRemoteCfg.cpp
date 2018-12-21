/**********************************************************
FileName:    DlgRemoteCfg.cpp
Description: Remote Config Dialog box      
Date:        2008/05/17
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRemoteCfg.h"
#include ".\dlgremotecfg.h"


// CDlgRemoteCfg dialog
/*********************************************************
  Function:	CDlgRemoteCfg
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgRemoteCfg, CDialog)
CDlgRemoteCfg::CDlgRemoteCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteCfg::IDD, pParent)
	, m_iDeviceIndex(-1)
	, m_iRemoteConfigType(REMOTE_DEVICE_CFG_T)
	, m_iChanIndex(-1)
	, m_lLoginID(-1)
	, m_iDeviceType(-1)
{
}
/*********************************************************
  Function:	~CDlgRemoteCfg
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgRemoteCfg::~CDlgRemoteCfg()
{
}
/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteCfg)
	DDX_Control(pDX, IDC_TAB_REMOTE_CFG, m_tabRemoteCfg);
        //}}AFX_DATA_MAP

}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgRemoteCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteCfg)	
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_REMOTE_CFG, OnTcnSelchangeTabRemoteCfg)
	ON_BN_CLICKED(IDC_BTN_SAVE_PARA, OnBnClickedRemoteSavePara)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_REBOOT, OnBtnReboot)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()


// CDlgRemoteCfg message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgRemoteCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char szLan[128] = {0};
	g_StringLanType(szLan, "设备参数配置", "Device Setup");
	m_tabRemoteCfg.InsertItem(0, szLan);
	g_StringLanType(szLan, "网络参数配置", "Network Setup");
	m_tabRemoteCfg.InsertItem(1, szLan);
	g_StringLanType(szLan, "通道参数配置", "Channel Setup");
	m_tabRemoteCfg.InsertItem(2, szLan);
	g_StringLanType(szLan, "串口参数配置", "Serial Port Setup");
	m_tabRemoteCfg.InsertItem(3, szLan);
	g_StringLanType(szLan, "报警参数配置", "Alarm Setup");
	m_tabRemoteCfg.InsertItem(4, szLan);
	g_StringLanType(szLan, "用户配置", "User Setup");
	m_tabRemoteCfg.InsertItem(5, szLan);	
	g_StringLanType(szLan, "异常信息", "Exception Setup");
	m_tabRemoteCfg.InsertItem(6, szLan);
	g_StringLanType(szLan, "交易信息", "Transaction Setup");
	m_tabRemoteCfg.InsertItem(7, szLan);
//	g_StringLanType(szLan, "解码矩阵配置", "Multi Decoder Setup");
//	m_tabRemoteCfg.InsertItem(8, szLan);	
    g_StringLanType(szLan, "零通道配置", "Zero Channel Setup");
    m_tabRemoteCfg.InsertItem(8,szLan);

	m_subDlgDeviceCfg.Create(IDD_SUB_DLG_DEVICE_CFG, &m_tabRemoteCfg);
	m_subDlgChanCfg.Create(IDD_SUB_DLG_CHAN_CFG, &m_tabRemoteCfg);
	m_subDlgSerialCfg.Create(IDD_SUB_DLG_SERIAL_CFG, &m_tabRemoteCfg);
	m_subDlgAlarmCfg.Create(IDD_SUB_DLG_ALARM_CFG, &m_tabRemoteCfg);
	m_subDlgExceptionCfg.Create(IDD_SUB_DLG_EXCEPTION_CFG, &m_tabRemoteCfg);
	m_subDlgUserCfg.Create(IDD_SUB_DLG_USER_CFG, &m_tabRemoteCfg);
	m_subDlgATMInfoCfg.Create(IDD_SUB_DLG_ATMINFO_CFG, &m_tabRemoteCfg);
//	m_subDlgMatDecCfg.Create(IDD_SUB_DLG_MAT_DEC_CFG, &m_tabRemoteCfg);
    m_subDlgZeroChanCfg.Create(IDD_SUB_DLG_ZEROCHAN_CFG, &m_tabRemoteCfg);
	m_subDlgNetworkCfg.Create(IDD_SUB_DLG_NETWORK_CFG,&m_tabRemoteCfg);

	m_subDlgDeviceCfg.ShowWindow(SW_HIDE);
	m_subDlgChanCfg.ShowWindow(SW_HIDE);
	m_subDlgSerialCfg.ShowWindow(SW_HIDE);
	m_subDlgAlarmCfg.ShowWindow(SW_HIDE);
	m_subDlgExceptionCfg.ShowWindow(SW_HIDE);
	m_subDlgUserCfg.ShowWindow(SW_HIDE);
	m_subDlgATMInfoCfg.ShowWindow(SW_HIDE);
//	m_subDlgMatDecCfg.ShowWindow(SW_HIDE);
    m_subDlgZeroChanCfg.ShowWindow(SW_HIDE);
	m_subDlgNetworkCfg.ShowWindow(SW_HIDE);
	return TRUE;
}

/*********************************************************
  Function:	TabSet
  Desc:		Dsiplay tabblefor selected device
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteCfg::TabSet()
{
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	char szLan[128] = {0};
	if (iDeviceIndex == -1)
	{
		return;
	}
	else if ( DEC_MAT != g_struDeviceInfo[iDeviceIndex].iDeviceType && DEC_MAT != m_iDeviceType)
	{
		return;
	}
	else if (DEC_MAT == g_struDeviceInfo[iDeviceIndex].iDeviceType && DEC_MAT != m_iDeviceType)
	{
		m_tabRemoteCfg.DeleteAllItems();
		m_iDeviceType = g_struDeviceInfo[iDeviceIndex].iDeviceType;
		g_StringLanType(szLan, "设备参数配置", "Device Setup");
		m_tabRemoteCfg.InsertItem(0, szLan);
		g_StringLanType(szLan, "通道参数配置", "Channel Setup");
		m_tabRemoteCfg.InsertItem(1, szLan);
		g_StringLanType(szLan, "串口参数配置", "Serial Port Setup");
		m_tabRemoteCfg.InsertItem(2, szLan);
		g_StringLanType(szLan, "报警参数配置", "Alarm Setup");
		m_tabRemoteCfg.InsertItem(3, szLan);
//		g_StringLanType(szLan, "解码矩阵配置", "Multi Decoder Setup");
//		m_tabRemoteCfg.InsertItem(4, szLan);

		m_subDlgDeviceCfg.Create(IDD_SUB_DLG_DEVICE_CFG, &m_tabRemoteCfg);
		m_subDlgChanCfg.Create(IDD_SUB_DLG_CHAN_CFG, &m_tabRemoteCfg);
		m_subDlgSerialCfg.Create(IDD_SUB_DLG_SERIAL_CFG, &m_tabRemoteCfg);
//		m_subDlgMatDecCfg.Create(IDD_SUB_DLG_MAT_DEC_CFG, &m_tabRemoteCfg);

		m_subDlgDeviceCfg.ShowWindow(SW_HIDE);
		m_subDlgChanCfg.ShowWindow(SW_HIDE);
		m_subDlgSerialCfg.ShowWindow(SW_HIDE);
//		m_subDlgMatDecCfg.ShowWindow(SW_HIDE);
	}
	else
	{
		m_tabRemoteCfg.DeleteAllItems();
		m_iDeviceType = g_struDeviceInfo[iDeviceIndex].iDeviceType;
		g_StringLanType(szLan, "设备参数配置", "Device Setup");
		m_tabRemoteCfg.InsertItem(0, szLan);
		g_StringLanType(szLan, "网络参数配置", "Network Setup");
	    m_tabRemoteCfg.InsertItem(1, szLan);
		g_StringLanType(szLan, "通道参数配置", "Channel Setup");
		m_tabRemoteCfg.InsertItem(2, szLan);
		g_StringLanType(szLan, "串口参数配置", "Serial Port Setup");
		m_tabRemoteCfg.InsertItem(3, szLan);
		g_StringLanType(szLan, "报警参数配置", "Alarm Setup");
		m_tabRemoteCfg.InsertItem(4, szLan);
		g_StringLanType(szLan, "用户配置", "User Setup");
		m_tabRemoteCfg.InsertItem(5, szLan);	
		g_StringLanType(szLan, "异常信息", "Exception Setup");
		m_tabRemoteCfg.InsertItem(6, szLan);
		g_StringLanType(szLan, "交易信息", "Transaction Setup");
		m_tabRemoteCfg.InsertItem(7, szLan);
        g_StringLanType(szLan, "零通道配置", "Zero Channel Setup");
        m_tabRemoteCfg.InsertItem(8,szLan);
	

		m_subDlgDeviceCfg.Create(IDD_SUB_DLG_DEVICE_CFG, &m_tabRemoteCfg);
		m_subDlgChanCfg.Create(IDD_SUB_DLG_CHAN_CFG, &m_tabRemoteCfg);
		m_subDlgSerialCfg.Create(IDD_SUB_DLG_SERIAL_CFG, &m_tabRemoteCfg);
		m_subDlgAlarmCfg.Create(IDD_SUB_DLG_ALARM_CFG, &m_tabRemoteCfg);
		m_subDlgExceptionCfg.Create(IDD_SUB_DLG_EXCEPTION_CFG, &m_tabRemoteCfg);
		m_subDlgUserCfg.Create(IDD_SUB_DLG_USER_CFG, &m_tabRemoteCfg);
		m_subDlgATMInfoCfg.Create(IDD_SUB_DLG_ATMINFO_CFG, &m_tabRemoteCfg);
        m_subDlgZeroChanCfg.Create(IDD_SUB_DLG_ZEROCHAN_CFG, &m_tabRemoteCfg);
		m_subDlgNetworkCfg.Create(IDD_SUB_DLG_NETWORK_CFG,&m_tabRemoteCfg);

		m_subDlgDeviceCfg.ShowWindow(SW_HIDE);
		m_subDlgChanCfg.ShowWindow(SW_HIDE);
		m_subDlgSerialCfg.ShowWindow(SW_HIDE);
		m_subDlgAlarmCfg.ShowWindow(SW_HIDE);
		m_subDlgExceptionCfg.ShowWindow(SW_HIDE);
		m_subDlgUserCfg.ShowWindow(SW_HIDE);
		m_subDlgATMInfoCfg.ShowWindow(SW_HIDE);
        m_subDlgZeroChanCfg.ShowWindow(SW_HIDE);
		m_subDlgNetworkCfg.ShowWindow(SW_HIDE);
	}
}

/*********************************************************
  Function:	ChangeCurConfigWnd
  Desc:		switch current configuration status
  Input:	iConfigType,current config type
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteCfg::ChangeCurConfigWnd(int iConfigType)
{
	if (iConfigType == REMOTE_DEVICE_CFG_T)
	{
		m_subDlgDeviceCfg.ShowWindow(SW_SHOW);
	}
	else
	{
		m_subDlgDeviceCfg.ShowWindow(SW_HIDE);
	}
	
	if (iConfigType == REMOTE_CHANNEL_CFG_T)
	{
		m_subDlgChanCfg.ShowWindow(SW_SHOW);
	}
	else
	{
		m_subDlgChanCfg.ShowWindow(SW_HIDE);
	}

	if (iConfigType == REMOTE_SEREIAL_CFG_T)
	{
		m_subDlgSerialCfg.ShowWindow(SW_SHOW);
	}
	else
	{
		m_subDlgSerialCfg.ShowWindow(SW_HIDE);
	}

	if (iConfigType == REMOTE_AlARM_CFG_T)
	{
		m_subDlgAlarmCfg.ShowWindow(SW_SHOW);
	}
	else
	{
		m_subDlgAlarmCfg.ShowWindow(SW_HIDE);
	}
	//if (DEC_MAT != m_iDeviceType)
	//{
	if (iConfigType == REMOTE_EXCEPTION_CFG_T)
	{
		m_subDlgExceptionCfg.ShowWindow(SW_SHOW);
	}
	else
	{
		m_subDlgExceptionCfg.ShowWindow(SW_HIDE);
	}

	if (iConfigType == REMOTE_USER_CFG_T)
	{
		m_subDlgUserCfg.ShowWindow(SW_SHOW);
	}
	else
	{
		m_subDlgUserCfg.ShowWindow(SW_HIDE);
	}

	if (iConfigType == REMOTE_ATM_INFO_CFG_T)
	{
		m_subDlgATMInfoCfg.ShowWindow(SW_SHOW);
	}
	else
	{
		m_subDlgATMInfoCfg.ShowWindow(SW_HIDE);
	}

// 	if (iConfigType == REMOTE_MAT_DEC_CFG_T)
// 	{
// //		m_subDlgMatDecCfg.ShowWindow(SW_SHOW);
// 	}
// 	else
// 	{
// //		m_subDlgMatDecCfg.ShowWindow(SW_HIDE);
// 	}
        
    if (iConfigType == REMOTE_ZERO_CHAN_CFG_T)
    {
        m_subDlgZeroChanCfg.ShowWindow(SW_SHOW);
    }
    else
    {
        m_subDlgZeroChanCfg.ShowWindow(SW_HIDE);
    }

	if (iConfigType == REMOTE_NETWORK_CFG_T)
	{
		m_subDlgNetworkCfg.ShowWindow(SW_SHOW);
	}
	else
	{
		m_subDlgNetworkCfg.ShowWindow(SW_HIDE);
	}
}

/*********************************************************
  Function:	RemoteConfigUpdate
  Desc:		paramter Update
  Input:	iConfigType, relative remote config page
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteCfg::RemoteConfigUpdate(int iConfigType)
{
	int iDevIndex = g_pMainDlg->GetCurDeviceIndex();
	if (iDevIndex == -1)
	{
		GetDlgItem(IDC_BTN_SAVE_PARA)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_REMOTE_RESTORE_DEFAULT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_REFRESH)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_REBOOT)->EnableWindow(FALSE);
	}
	else if (g_struDeviceInfo[iDevIndex].lLoginID == -1)
	{
		GetDlgItem(IDC_BTN_SAVE_PARA)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_REMOTE_RESTORE_DEFAULT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_REFRESH)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_REBOOT)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BTN_SAVE_PARA)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_REMOTE_RESTORE_DEFAULT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_REFRESH)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_REBOOT)->EnableWindow(TRUE);
	}
	g_bMustReboot = FALSE;
	switch (iConfigType)
	{
	case REMOTE_DEVICE_CFG_T:
		m_subDlgDeviceCfg.CurCfgUpdate();
		break;
	case REMOTE_CHANNEL_CFG_T:
		if (m_subDlgChanCfg.CheckInitParam())
		{
			//int iChanIndex = g_pMainDlg->GetCurChanIndex();
			int iChanIndexInTree = g_pMainDlg->GetCurChanIndexInTree();
			m_subDlgChanCfg.CurCfgUpdate(iChanIndexInTree);
			m_subDlgChanCfg.EnableWindow(TRUE);
		}
		else
		{
			m_subDlgChanCfg.EnableWindow(FALSE);
		}	
		break;
	case REMOTE_SEREIAL_CFG_T:
		m_subDlgSerialCfg.CurCfgUpdate();
		break;
	case REMOTE_AlARM_CFG_T:
		m_subDlgAlarmCfg.CurCfgUpdate();
		break;
	case REMOTE_USER_CFG_T:
		m_subDlgUserCfg.CurCfgUpdate();
		break;
	case REMOTE_EXCEPTION_CFG_T:
		m_subDlgExceptionCfg.CurCfgUpdate();
		break;
	case REMOTE_ATM_INFO_CFG_T:
		m_subDlgATMInfoCfg.CurCfgUpdate();
		break;	
// 	case REMOTE_MAT_DEC_CFG_T:
// //		m_subDlgMatDecCfg.CurCfgUpdate();
// 		break;	
    case REMOTE_ZERO_CHAN_CFG_T:
        m_subDlgZeroChanCfg.CurCfgUpdate();
        break;
	case REMOTE_NETWORK_CFG_T:
		m_subDlgNetworkCfg.CurCfgUpdate();
		break;
	default:
		m_iRemoteConfigType = REMOTE_DEVICE_CFG_T;
		RemoteConfigUpdate(m_iRemoteConfigType);
		break;
	}

	ChangeCurConfigWnd(m_iRemoteConfigType);
}

/*********************************************************
  Function:	OnTcnSelchangeTabRemoteCfg
  Desc:		select function of remote config table and update the parameters
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteCfg::OnTcnSelchangeTabRemoteCfg(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iSel = m_tabRemoteCfg.GetCurSel();
	//if (m_iDeviceType == DEC_MAT && iSel == 4)
	//{
	//	m_iRemoteConfigType = REMOTE_MAT_DEC_CFG_T;
	//}
	//else
	{
		m_iRemoteConfigType = iSel;
	}
	 
	RemoteConfigUpdate(m_iRemoteConfigType);

	*pResult = 0;
}

/*********************************************************
  Function:	OnBnClickedRemoteSavePara
  Desc:		Save remote configuration parameters
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteCfg::OnBnClickedRemoteSavePara()
{
	BOOL bSetup = FALSE;
	switch (m_iRemoteConfigType)
	{
	case REMOTE_DEVICE_CFG_T:
		bSetup = m_subDlgDeviceCfg.CfgSetup();
		break;
	case REMOTE_CHANNEL_CFG_T:
		bSetup = m_subDlgChanCfg.CfgSetup();
		break;
	case REMOTE_SEREIAL_CFG_T:
		bSetup = m_subDlgSerialCfg.CfgSetup();
		break;
	case REMOTE_AlARM_CFG_T:
		bSetup = m_subDlgAlarmCfg.CfgSetup();
		break;
	case REMOTE_USER_CFG_T:
		bSetup = m_subDlgUserCfg.CfgSetup();
		break;
	case REMOTE_EXCEPTION_CFG_T:
		bSetup = m_subDlgExceptionCfg.CfgSetup();
		break;
	case REMOTE_ATM_INFO_CFG_T:
		bSetup = m_subDlgATMInfoCfg.CfgSetup();
		break;
	case REMOTE_NETWORK_CFG_T:
		bSetup = m_subDlgNetworkCfg.CfgSetup();
		break;
	//case REMOTE_ATM_INFO_CFG_T:
	//	bSetup = m_subDlgMatDecCfg.CfgSetup();
	//	break;		
	default:
		break;
	}
	char szLan[128] = {0};
	if (bSetup&& g_bMustReboot)// 
	{
		g_StringLanType(szLan, "参数保存成功.需要重启后方生效", "Save parameter successfully, need reboot to be valid");
		AfxMessageBox(szLan);
	}
	else if (bSetup)
	{
		//g_StringLanType(szLan, "参数保存成功.", "Save parameter successfully.");
		//AfxMessageBox(szLan);
	}
	g_bMustReboot = FALSE;
}

/*********************************************************
  Function:	OnBtnRefresh
  Desc:		refresh current config
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteCfg::OnBtnRefresh() 
{
	switch (m_iRemoteConfigType)
	{
	case REMOTE_DEVICE_CFG_T:
		m_subDlgDeviceCfg.m_iDeviceIndex = -1;
		break;
	case REMOTE_CHANNEL_CFG_T:
		m_subDlgChanCfg.m_iDeviceIndex = -1;
		m_subDlgChanCfg.m_iCurChanIndex = -1;
		break;
	case REMOTE_SEREIAL_CFG_T:
		m_subDlgSerialCfg.m_iDeviceIndex = -1;
		break;
	case REMOTE_AlARM_CFG_T:
		m_subDlgAlarmCfg.m_iDeviceIndex = -1;
		break;
	case REMOTE_USER_CFG_T:
		m_subDlgUserCfg.m_iDeviceIndex = -1;
		break;
	case REMOTE_EXCEPTION_CFG_T:
		m_subDlgExceptionCfg.m_iDeviceIndex = -1;
		break;
	case REMOTE_ATM_INFO_CFG_T:
		m_subDlgATMInfoCfg.m_iDeviceIndex = -1;
		break;	
	case REMOTE_NETWORK_CFG_T:
		m_subDlgNetworkCfg.m_iDeviceIndex = -1;
		break;
// 	case REMOTE_MAT_DEC_CFG_T:
// 		m_subDlgMatDecCfg.CurCfgUpdate();
// 		break;
	default:
		break;
	}

	RemoteConfigUpdate(m_iRemoteConfigType);
}

/*********************************************************
  Function:	OnBtnReboot
  Desc:		reboot Device	
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteCfg::OnBtnReboot() 
{
	// TODO: Add your control notification handler code here
	g_pMainDlg->OnMenuReboot();
}
