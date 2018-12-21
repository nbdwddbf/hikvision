// DlgCMSParam.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCMSParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgCMSParam dialog


DlgCMSParam::DlgCMSParam(CWnd* pParent /*=NULL*/)
	: CDialog(DlgCMSParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgCMSParam)
	m_bRegister = FALSE;
	m_sDeviceID = _T("");
	m_sIP = _T("");
	m_Port = 0;
	m_sVersion = _T("");
	m_csDomain = _T("");
    m_bEnable = FALSE;
	//}}AFX_DATA_INIT
	memset(&m_struCmsParam,0,sizeof(m_struCmsParam));
}


void DlgCMSParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgCMSParam)
	DDX_Control(pDX, IDC_CMB_ADDR_TYPE, m_cmbAddrType);
	DDX_Control(pDX, IDC_PROTOCOL, m_ProtocolType);
	DDX_Control(pDX, IDC_INDEX, m_index);
	DDX_Control(pDX, IDC_CMB_NETWORK_TYPE, m_networkType);
	DDX_Check(pDX, IDC_REGISTER, m_bRegister);
	DDX_Text(pDX, IDC_DEVICEID, m_sDeviceID);
	DDX_Text(pDX, IDC_IP, m_sIP);
	DDX_Text(pDX, IDC_PORT, m_Port);
	DDX_Text(pDX, IDC_VERSION, m_sVersion);
	DDX_Text(pDX, IDC_EDIT_DOMAIN2, m_csDomain);
    DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	//}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_CMB_PROTOCOL_VERSION, m_comboProtocolVersion);
}


BEGIN_MESSAGE_MAP(DlgCMSParam, CDialog)
	//{{AFX_MSG_MAP(DlgCMSParam)
	ON_BN_CLICKED(IDC_SET, OnSet)
	ON_BN_CLICKED(IDC_GET, OnGet)
	ON_EN_CHANGE(IDC_DEVICEID, OnChangeDeviceid)
	ON_CBN_SELCHANGE(IDC_INDEX, OnSelchangeIndex)
	ON_CBN_SELCHANGE(IDC_CMB_ADDR_TYPE, OnSelchangeCmbAddrType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgCMSParam message handlers

BOOL DlgCMSParam::OnInitDialog() 
{
	CDialog::OnInitDialog();

	UpdateData(TRUE);
	DWORD dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	char szLan[128] = {0};
	DWORD dwReturn;
	if(NET_DVR_GetDVRConfig(g_struDeviceInfo[dwDeviceIndex].lLoginID,NET_DVR_GET_CMS_CFG,0xffffffff,&m_struCmsParam,sizeof(m_struCmsParam),&dwReturn))
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_CMS_CFG");
		//g_StringLanType(szLan, "获取成功", "Get cms cfg successed!");
		//AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_CMS_CFG");
		g_StringLanType(szLan, "获取失败", "Get cms cfg failed!");
		AfxMessageBox(szLan);
	}
	int sel = (int)m_struCmsParam.bySeverProtocolType-1;
	m_ProtocolType.SetCurSel(sel);
	m_bRegister = m_struCmsParam.byStatus - 1;
	m_sDeviceID.Format("%s",(char*)m_struCmsParam.sDeviceId);
	m_sIP.Format("%s",m_struCmsParam.struAddr.sIpV4);
	m_Port = m_struCmsParam.wServerPort;
	m_index.SetCurSel(0);
	int sel2 = (int)m_struCmsParam.byNetWork;
	m_networkType.SetCurSel(sel2);
	m_sVersion.Format("%s",(char*)m_struCmsParam.sPlatformEhomeVersion);//2014-03-21
// 	GetDlgItem(IDC_PROTOCOL)->EnableWindow(FALSE);
// 	GetDlgItem(IDC_REGISTER)->EnableWindow(FALSE);
	m_cmbAddrType.SetCurSel(m_struCmsParam.byAddressType);
	m_csDomain.Format("%s",m_struCmsParam.sDomainName);
    m_comboProtocolVersion.SetCurSel(m_struCmsParam.byProtocolVersion);
    m_bEnable = m_struCmsParam.byEnable;
	UpdateData(FALSE);
	OnSelchangeCmbAddrType();
	return TRUE;
}
void DlgCMSParam::OnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struCmsParam.bySeverProtocolType = m_ProtocolType.GetCurSel()+1;
	m_struCmsParam.byStatus = m_bRegister+1;
	sprintf((char*)m_struCmsParam.sDeviceId,"%s",m_sDeviceID.GetBuffer(m_sDeviceID.GetLength()));
	sprintf(m_struCmsParam.struAddr.sIpV4,"%s",m_sIP.GetBuffer(m_sIP.GetLength()));
	m_struCmsParam.wServerPort = m_Port;
	m_struCmsParam.dwSize = sizeof(m_struCmsParam);
	m_struCmsParam.byAddressType = m_cmbAddrType.GetCurSel();
    m_struCmsParam.byProtocolVersion = m_comboProtocolVersion.GetCurSel();
	m_struCmsParam.byNetWork = m_networkType.GetCurSel();
    m_struCmsParam.byEnable = m_bEnable;

	sprintf((char*)m_struCmsParam.sDomainName,"%s",m_csDomain.GetBuffer(m_csDomain.GetLength()));

	DWORD dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	char szLan[128] = {0};
	if(NET_DVR_SetDVRConfig(g_struDeviceInfo[dwDeviceIndex].lLoginID,NET_DVR_SET_CMS_CFG,m_index.GetCurSel()+1,&m_struCmsParam,sizeof(m_struCmsParam)))
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_SET_CMS_CFG");
		g_StringLanType(szLan, "设置成功", "Set cms cfg successed!");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_SET_CMS_CFG");
		g_StringLanType(szLan, "设置失败", "Set cms cfg failed!");
		AfxMessageBox(szLan);
	}
}

void DlgCMSParam::OnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	char szLan[128] = {0};
	DWORD dwReturn;
	if(NET_DVR_GetDVRConfig(g_struDeviceInfo[dwDeviceIndex].lLoginID,NET_DVR_GET_CMS_CFG,m_index.GetCurSel()+1,&m_struCmsParam,sizeof(m_struCmsParam),&dwReturn))
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_CMS_CFG");
		g_StringLanType(szLan, "获取成功", "Get cms cfg successed!");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_CMS_CFG");
		g_StringLanType(szLan, "获取失败", "Get cms cfg failed!");
		AfxMessageBox(szLan);
	}
	int sel = (int)m_struCmsParam.bySeverProtocolType-1;
	m_ProtocolType.SetCurSel(sel);
	int sel2 = (int)m_struCmsParam.byNetWork;
	m_networkType.SetCurSel(sel2);
	m_bRegister = m_struCmsParam.byStatus - 1;
	m_sDeviceID.Format("%s",(char*)m_struCmsParam.sDeviceId);
	m_sIP.Format("%s",m_struCmsParam.struAddr.sIpV4);
	m_Port = m_struCmsParam.wServerPort;
	m_sVersion.Format("%s",(char*)m_struCmsParam.sPlatformEhomeVersion);//2014-03-21
// 	GetDlgItem(IDC_PROTOCOL)->EnableWindow(FALSE);
// 	GetDlgItem(IDC_REGISTER)->EnableWindow(FALSE);
	m_cmbAddrType.SetCurSel(m_struCmsParam.byAddressType);
	m_csDomain.Format("%s",m_struCmsParam.sDomainName);
    m_comboProtocolVersion.SetCurSel(m_struCmsParam.byProtocolVersion);
	UpdateData(FALSE);
	OnSelchangeCmbAddrType();
}

void DlgCMSParam::OnChangeDeviceid() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void DlgCMSParam::OnSelchangeIndex() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	char szLan[128] = {0};
	DWORD dwReturn;
	if(NET_DVR_GetDVRConfig(g_struDeviceInfo[dwDeviceIndex].lLoginID,NET_DVR_GET_CMS_CFG,m_index.GetCurSel()+1,&m_struCmsParam,sizeof(m_struCmsParam),&dwReturn))
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_CMS_CFG");
		g_StringLanType(szLan, "获取成功", "Get cms cfg successed!");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_CMS_CFG");
		g_StringLanType(szLan, "获取失败", "Get cms cfg failed!");
		AfxMessageBox(szLan);
	}
	int sel = (int)m_struCmsParam.bySeverProtocolType-1;
	if(sel == 1)
		m_ProtocolType.SetCurSel(0);
	else if(sel == 0)
		m_ProtocolType.SetCurSel(1);
	UpdateData(FALSE);
	m_bRegister = m_struCmsParam.byStatus - 1;
	m_sDeviceID.Format("%s",(char*)m_struCmsParam.sDeviceId);
	m_sIP.Format("%s",m_struCmsParam.struAddr.sIpV4);
	m_Port = m_struCmsParam.wServerPort;
	m_sVersion.Format("%s",(char*)m_struCmsParam.sPlatformEhomeVersion);//2014-03-21
//	GetDlgItem(IDC_PROTOCOL_TYPE)->EnableWindow(FALSE);
// 	GetDlgItem(IDC_PROTOCOL)->EnableWindow(FALSE);
// 	GetDlgItem(IDC_REGISTER)->EnableWindow(FALSE);
	m_cmbAddrType.SetCurSel(m_struCmsParam.byAddressType);
	m_csDomain.Format("%s",m_struCmsParam.sDomainName);
	UpdateData(FALSE);
	OnSelchangeCmbAddrType();
}

void DlgCMSParam::OnSelchangeCmbAddrType() 
{
	// TODO: Add your control notification handler code here
	if (0 == m_cmbAddrType.GetCurSel() || 1 == m_cmbAddrType.GetCurSel())
	{
		GetDlgItem(IDC_IP)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DOMAIN2)->EnableWindow(FALSE);
	} 
	else
	{
		GetDlgItem(IDC_IP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DOMAIN2)->EnableWindow(TRUE);
	}
}
