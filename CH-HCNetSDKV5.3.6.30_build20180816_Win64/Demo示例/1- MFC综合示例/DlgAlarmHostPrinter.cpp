// DlgAlarmHostPrinter.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmHostPrinter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostPrinter dialog


CDlgAlarmHostPrinter::CDlgAlarmHostPrinter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmHostPrinter::IDD, pParent)
	, m_iDeviceIndex(-1)
	, m_lUserID(-1)
{
	//{{AFX_DATA_INIT(CDlgAlarmHostPrinter)
	m_chEnable = FALSE;
	m_chPrintTime = FALSE;
	m_chFault = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgAlarmHostPrinter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmHostPrinter)
	DDX_Control(pDX, IDC_LIST_OPERATE_INFO, m_listOperateInfo);
	DDX_Control(pDX, IDC_LIST_DEVICE_INFO, m_listDeviceInfo);
	DDX_Control(pDX, IDC_LIST_ALARM_INFO, m_listAlarmInfo);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_chEnable);
	DDX_Check(pDX, IDC_CHECK_PRINT_TIME, m_chPrintTime);
	DDX_Check(pDX, IDC_CHECK_FAULT, m_chFault);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmHostPrinter, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmHostPrinter)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostPrinter message handlers

BOOL CDlgAlarmHostPrinter::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_listAlarmInfo.SetExtendedStyle(LVS_EX_CHECKBOXES);
	m_listDeviceInfo.SetExtendedStyle(LVS_EX_CHECKBOXES);
	m_listOperateInfo.SetExtendedStyle(LVS_EX_CHECKBOXES);
	int iIndex = 0;
	//bit0-zone alarm，bit1-zone alarm restore，bit2-emergency Keypad Alarms，bit-3-duress alarm
	g_StringLanType(m_szLan, "防区报警", "zone Alarm");
	m_listAlarmInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "防区报警恢复", "zone Alarm restore");
	m_listAlarmInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "紧急报警", "emergency keypad Alarms");
	m_listAlarmInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "挟持报警", "duress alarm");
	m_listAlarmInfo.InsertItem(iIndex++, m_szLan);
	
	//bit17-BUS Fault、bit18-BUS restore
	iIndex = 0;
	g_StringLanType(m_szLan, "交流电断电", "AC loss");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "交流电断电恢复", "AC loss restore");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "蓄电池电压低", "low battery");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "蓄电池电压低恢复", "low battery restore");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "电话线故障", "PSTN fault");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "电话线故障恢复", "PSTN fault restore");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "测试报告", "Test Report");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);

	g_StringLanType(m_szLan, "防拆", "tamper alarm");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "防拆恢复", "tamper restore");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);

	g_StringLanType(m_szLan, "485设备掉线", "485 device fault");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "485设备掉线恢复", "485 device restore");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);

	g_StringLanType(m_szLan, "GPRS/3G故障", "GPRS/3G fault");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "GPRS/3G故障", "GPRS/3G fault restore");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);

	g_StringLanType(m_szLan, "有线网络异常", "NetWork fault");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "有线网络异常恢复", "NetWork fault restore");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);

	g_StringLanType(m_szLan, "总线异常", "BUS fault");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "总线异常恢复", "BUS fault restore");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "硬盘故障", "hard disk fault");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "硬盘故障恢复", "hard disk fault restore");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "键盘锁定", "keyboard locked");
	m_listDeviceInfo.InsertItem(iIndex++, m_szLan);
	
	iIndex = 0;
	g_StringLanType(m_szLan, "布防", "Arm");
	m_listOperateInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "撤防", "Disarm");
	m_listOperateInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "消警", "Clear Alarm");
	m_listOperateInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "旁路", "Bypass");
	m_listOperateInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "旁路恢复", "Bypass restore");
	m_listOperateInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "进入编程", "Enter Code");
	m_listOperateInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "退出编程", "Exit Code");
	m_listOperateInfo.InsertItem(iIndex++, m_szLan);
	g_StringLanType(m_szLan, "主机复位", "Device restore");
	m_listOperateInfo.InsertItem(iIndex++, m_szLan);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmHostPrinter::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	memset(&m_struPrinter, 0, sizeof(m_struPrinter));
	m_struPrinter.dwSize = sizeof(m_struPrinter);
	DWORD dwReturn = 0;
	BOOL	bState = 0;
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ALARMHOST_PRINTER_CFG, 0, &m_struPrinter, sizeof(m_struPrinter), &dwReturn))
	{
		g_StringLanType(m_szLan, "获取打印机配置失败", "Get Printer Config Failed");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, m_szLan);
		return;
	}
	else
	{
		m_chEnable = m_struPrinter.byPrinterEnable;
		m_chPrintTime = m_struPrinter.byPrintTime;
		m_chFault = m_struPrinter.byFaultDetect;
		int i=0;
		for (i=0; i<m_listAlarmInfo.GetItemCount(); i++)
		{
			bState = (m_struPrinter.dwAlarmInfo>>i) & 0x01;
			m_listAlarmInfo.SetCheck(i, bState);
		}
		for (i=0; i<m_listDeviceInfo.GetItemCount(); i++)
		{
			bState = (m_struPrinter.dwDeviceInfo>>i) & 0x01;
			m_listDeviceInfo.SetCheck(i, bState);
		}
		for (i=0; i<m_listOperateInfo.GetItemCount(); i++)
		{
			bState = (m_struPrinter.dwOperateInfo>>i) & 0x01;
			m_listOperateInfo.SetCheck(i, bState);
		}
		g_StringLanType(m_szLan, "获取打印机配置成功", "Get Printer Config Successful");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, m_szLan);
	}
	UpdateData(FALSE);
}

void CDlgAlarmHostPrinter::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	memset((char*)&m_struPrinter, 0, sizeof(m_struPrinter));
	UpdateData(TRUE);
	m_struPrinter.byPrinterEnable = m_chEnable;
	m_struPrinter.byPrintTime = m_chPrintTime;
	m_struPrinter.byFaultDetect = m_chFault;
	int test =  m_listAlarmInfo.GetItemCount();
	int i=0;
	for (i=0; i<m_listAlarmInfo.GetItemCount(); i++)
	{
		m_struPrinter.dwAlarmInfo |= m_listAlarmInfo.GetCheck(i)<<i;
	}
	for (i=0; i<m_listDeviceInfo.GetItemCount(); i++)
	{
		m_struPrinter.dwDeviceInfo |= m_listDeviceInfo.GetCheck(i)<<i;
	}
	for (i=0; i<m_listOperateInfo.GetItemCount(); i++)
	{
		m_struPrinter.dwOperateInfo |= m_listOperateInfo.GetCheck(i)<<i;
	}

	m_struPrinter.dwSize = sizeof(m_struPrinter);
	DWORD dwReturn = 0;
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_ALARMHOST_PRINTER_CFG, 0, &m_struPrinter, sizeof(m_struPrinter)))
	{
		g_StringLanType(m_szLan, "设置打印机配置失败", "Set Printer Config Failed");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, m_szLan);
		return;
	}
	else
	{
		g_StringLanType(m_szLan, "设置打印机配置成功", "Set Printer Config Successful");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, m_szLan);
	}
}
