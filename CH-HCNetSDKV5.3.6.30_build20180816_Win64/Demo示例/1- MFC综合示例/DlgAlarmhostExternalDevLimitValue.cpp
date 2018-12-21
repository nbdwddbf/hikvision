// DlgAlarmhostExternalDevLimitValue.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmhostExternalDevLimitValue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmhostExternalDevLimitValue dialog


CDlgAlarmhostExternalDevLimitValue::CDlgAlarmhostExternalDevLimitValue(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmhostExternalDevLimitValue::IDD, pParent)
	, m_lUserID(-1)
	, m_iDeviceIndex(-1)
{
	//{{AFX_DATA_INIT(CDlgAlarmhostExternalDevLimitValue)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgAlarmhostExternalDevLimitValue::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmhostExternalDevLimitValue)
	DDX_Control(pDX, IDC_LIST_LIMIT_VALUE, m_listLimitValue);
	DDX_Control(pDX, IDC_EDIT_TEMP, m_Edit);
	DDX_Control(pDX, IDC_COMBO_SLOT_INDEX, m_cmSlotIndex);
	DDX_Control(pDX, IDC_COMBO_DEVICE_TYPE, m_cmDeviceType);
	DDX_Control(pDX, IDC_COMBO_CHAN_INDEX, m_cmChanIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmhostExternalDevLimitValue, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmhostExternalDevLimitValue)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICE_TYPE, OnSelchangeComboDeviceType)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_LIMIT_VALUE, OnDblclkListLimitValue)
	ON_EN_KILLFOCUS(IDC_EDIT_TEMP, OnKillfocusEditTemp)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmhostExternalDevLimitValue message handlers

BOOL CDlgAlarmhostExternalDevLimitValue::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_listLimitValue.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	g_StringLanType(m_sTemp, "变量", "Variable");
	m_listLimitValue.InsertColumn(0, m_sTemp, LVCFMT_LEFT, 200, -1);
	g_StringLanType(m_sTemp, "值", "value");
	m_listLimitValue.InsertColumn(1, m_sTemp, LVCFMT_LEFT, 200, -1);
	
	m_cmDeviceType.AddString("UPS");
	g_StringLanType(m_sTemp, "温湿度传感器", "Temperature Humidity sensor");
	m_cmDeviceType.AddString(m_sTemp);
	
	m_struAbility.dwSize = sizeof(m_struAbility);
	if(!NET_DVR_GetDeviceAbility(m_lUserID, ALARMHOST_ABILITY, NULL, 0, (char*)&m_struAbility, sizeof(m_struAbility)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Get Alarmhost Abilty failed");
		return FALSE;
	}
	CString csStr;
	m_cmChanIndex.ResetContent();
	int i=0;
	for (i=0; i<(m_struAbility.wLocalRs485Num +  m_struAbility.wExpandRs485Num); i++)
	{
		csStr.Format("Chan%d", i+1);
		m_cmChanIndex.AddString(csStr);
	}
	
	m_cmSlotIndex.ResetContent();
	for (i=0; i<m_struAbility.by485SlotNum; i++)
	{
		csStr.Format("Slot%d", i+1);
		m_cmSlotIndex.AddString(csStr);
	}
	m_cmChanIndex.SetCurSel(0);
	m_cmSlotIndex.SetCurSel(0);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgAlarmhostExternalDevLimitValue::OnSelchangeComboDeviceType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iIndex = m_cmDeviceType.GetCurSel() + 1;
	if (1 == iIndex) //UPS
	{
		memcpy(&m_struUPSLimitValue, &m_struLimitValue.struAlarmValue.struUpsLimitValue, sizeof(NET_DVR_ALARMHOST_UPS_LIMIT_VALUE));
		SetUpsLimitValue();
	}
	else if(2 == iIndex)
	{
		memcpy(&m_struSensorLimitValue, &m_struLimitValue.struAlarmValue.struTempHumidityLimitValue, sizeof(NET_DVR_ALARMHOST_TEMP_HUMIDITY_SENSOR_LIMIT_VALUE));
		SetTempHumiSensorLimitValue();	
	}
	m_iRowCount = m_listLimitValue.GetItemCount();
	UpdateData(FALSE);
}

void CDlgAlarmhostExternalDevLimitValue::SetUpsLimitValue() 
{
	m_listLimitValue.DeleteAllItems();
	int index = 0;
	
	m_listLimitValue.InsertItem(index, "输入电压高限值", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struLimitValue.struAlarmValue.struUpsLimitValue.iInputVolHigh/10);
	m_listLimitValue.SetItemText(index++, 1, m_sTemp);
	
	m_listLimitValue.InsertItem(index, "输入电压低限值", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struLimitValue.struAlarmValue.struUpsLimitValue.iInputVolLow/10);
	m_listLimitValue.SetItemText(index++, 1, m_sTemp);

	m_listLimitValue.InsertItem(index, "输入频率高限值", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struLimitValue.struAlarmValue.struUpsLimitValue.iInputFreHigh/10);
	m_listLimitValue.SetItemText(index++, 1, m_sTemp);
	
	m_listLimitValue.InsertItem(index, "输入频率低限值", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struLimitValue.struAlarmValue.struUpsLimitValue.iInputFreLow/10);
	m_listLimitValue.SetItemText(index++, 1, m_sTemp);

	m_listLimitValue.InsertItem(index, "输出电压高限值", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struLimitValue.struAlarmValue.struUpsLimitValue.iOutputVolHigh/10);
	m_listLimitValue.SetItemText(index++, 1, m_sTemp);
	
	m_listLimitValue.InsertItem(index, "输出电压过低限值", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struLimitValue.struAlarmValue.struUpsLimitValue.iOutputVolLow/10);
	m_listLimitValue.SetItemText(index++, 1, m_sTemp);

	m_listLimitValue.InsertItem(index, "电池电压低限值", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struLimitValue.struAlarmValue.struUpsLimitValue.iBatteryVoltageLow/10);
	m_listLimitValue.SetItemText(index++, 1, m_sTemp);
	
	m_listLimitValue.InsertItem(index, "电池后备时间低限值", 0);
	sprintf(m_sTemp, "%d", m_struLimitValue.struAlarmValue.struUpsLimitValue.iBatterySurplus);
	m_listLimitValue.SetItemText(index++, 1, m_sTemp);

	m_listLimitValue.InsertItem(index, "电池温度高限值", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struLimitValue.struAlarmValue.struUpsLimitValue.iBatteryTemperatureHigh/10);
	m_listLimitValue.SetItemText(index++, 1, m_sTemp);

	UpdateData(FALSE);
}

void CDlgAlarmhostExternalDevLimitValue::SetTempHumiSensorLimitValue()
{
	m_listLimitValue.DeleteAllItems();
	int index = 0;
	
	m_listLimitValue.InsertItem(index, "温度高限值", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struLimitValue.struAlarmValue.struTempHumidityLimitValue.iTemperatureHighLimit/10);
	m_listLimitValue.SetItemText(index++, 1, m_sTemp);
	
	m_listLimitValue.InsertItem(index, "温度低限值", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struLimitValue.struAlarmValue.struTempHumidityLimitValue.iTemperatureLowLimit/10);
	m_listLimitValue.SetItemText(index++, 1, m_sTemp);

	m_listLimitValue.InsertItem(index, "湿度高限值", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struLimitValue.struAlarmValue.struTempHumidityLimitValue.iHumidityHighLimit/10);
	m_listLimitValue.SetItemText(index++, 1, m_sTemp);
	
	m_listLimitValue.InsertItem(index, "湿度低限值", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struLimitValue.struAlarmValue.struTempHumidityLimitValue.iHumidityLowLimit/10);
	m_listLimitValue.SetItemText(index++, 1, m_sTemp);

	UpdateData(FALSE);
}


void CDlgAlarmhostExternalDevLimitValue::OnDblclkListLimitValue(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
	CRect  EditRect;
		
	m_iItem = pEditCtrl->iItem;
	m_iSubItem = pEditCtrl->iSubItem;
	
// 	if (m_iItem == -1)
// 	{
// 		return;
// 	}
	if (0==m_iSubItem)
	{
		return;
	}
	
	if (m_iItem < m_iRowCount)
	{	
		m_listLimitValue.GetSubItemRect(m_iItem,m_iSubItem,LVIR_LABEL,EditRect);
		m_Edit.SetParent(&m_listLimitValue); //将list control设置为父窗口,生成的Edit才能正确定位
		
		EditRect.SetRect(EditRect.left,EditRect.top,EditRect.left+m_listLimitValue.GetColumnWidth(m_iSubItem),EditRect.bottom);
		
		//将选中的list控件中的内容copy到edit控件中
		CString strItem = m_listLimitValue.GetItemText(m_iItem,m_iSubItem);
		m_Edit.MoveWindow(&EditRect);
		m_Edit.ShowWindow(SW_SHOW);
		m_Edit.SetWindowText(strItem);
		m_Edit.SetFocus();//设置为焦点
		m_Edit.SetSel(0,-1);  //0,-1表示单元格内容全选中
	}
	else
	{
		m_Edit.ShowWindow(SW_HIDE);
	}
	*pResult = 0;
}

void CDlgAlarmhostExternalDevLimitValue::OnKillfocusEditTemp() 
{
	// TODO: Add your control notification handler code here
	CString  csEditStr;
	char  szListStr[NAME_LEN];
	m_listLimitValue.GetItemText(m_iItem, m_iSubItem, szListStr, NAME_LEN);
	m_Edit.GetWindowText(csEditStr); 
	if (csEditStr.Compare(szListStr))
	{
		m_listLimitValue.SetItemText(m_iItem, m_iSubItem, csEditStr); 
		SaveLimitValue();
	}	
	m_Edit.ShowWindow(SW_HIDE);
}

void CDlgAlarmhostExternalDevLimitValue::SaveLimitValue() 
{
	int iDevType = m_cmDeviceType.GetCurSel() + 1;
	char  szStr[128] = {0};
	if (1 == iDevType) //UPS
	{
		m_listLimitValue.GetItemText(m_iItem, 1, szStr, 128);
		if (7 == m_iItem)
		{
			//电池后备时间，传给设备的时候不用乘以10
			*(int*)((char*)&m_struUPSLimitValue + 4*m_iItem) = atoi(szStr);
		}
		else
		{
			*(int*)((char*)&m_struUPSLimitValue + 4*m_iItem) = (int)(atof(szStr)*10);
		}
	}
	else if (2 == iDevType) //温湿度传感器
	{
		m_listLimitValue.GetItemText(m_iItem, 1, szStr, 128);
		*(int*)((char*)&m_struSensorLimitValue + 4*m_iItem) = (int)(atof(szStr)*10);
	}
}

void CDlgAlarmhostExternalDevLimitValue::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwStatus = 0;
	DWORD dwChanIndex = 0;
	DWORD dwSlotIndex = 0;
	DWORD dwInput = 0; 
	dwChanIndex = m_cmChanIndex.GetCurSel() + 1;
	dwChanIndex = dwChanIndex << 16;
	dwSlotIndex = m_cmSlotIndex.GetCurSel() + 1;
	dwInput = dwChanIndex | dwSlotIndex;

	DWORD dwReturn = 0;

	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ALARMHOST_EXTERNAL_DEVICE_LIMIT_VALUE, dwInput, &m_struLimitValue, sizeof(m_struLimitValue), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Get Device limit value failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Get device limit value successful");
	}
	m_cmDeviceType.SetCurSel(m_struLimitValue.byDevType - 1);
	UpdateData(FALSE);	
	OnSelchangeComboDeviceType();
}

void CDlgAlarmhostExternalDevLimitValue::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	BYTE byDevType = m_cmDeviceType.GetCurSel() + 1;
	DWORD dwChanIndex = 0;
	DWORD dwSlotIndex = 0;
	DWORD dwInput = 0; 
	dwChanIndex = m_cmChanIndex.GetCurSel() + 1;
	dwChanIndex = dwChanIndex << 16;
	dwSlotIndex = m_cmSlotIndex.GetCurSel() + 1;
	dwInput = dwChanIndex | dwSlotIndex;

	m_struLimitValue.byDevType = byDevType;
	m_struLimitValue.dwSize = sizeof(NET_DVR_ALARMHOST_EXTERNAL_DEVICE_LIMIT_VALUE);
	if (1 == byDevType) // UPS
	{
		memcpy(&m_struLimitValue.struAlarmValue.struUpsLimitValue,  &m_struUPSLimitValue, sizeof(NET_DVR_ALARMHOST_UPS_LIMIT_VALUE));
	}
	else if (2 == byDevType)// 温湿度传感器
	{
		memcpy(&m_struLimitValue.struAlarmValue.struTempHumidityLimitValue, &m_struSensorLimitValue, sizeof(NET_DVR_ALARMHOST_TEMP_HUMIDITY_SENSOR_LIMIT_VALUE));
	}
	
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_ALARMHOST_EXTERNAL_DEVICE_LIMIT_VALUE, dwInput, &m_struLimitValue, sizeof(m_struLimitValue)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Set device limit value failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set device limit value successful");
	}
}
