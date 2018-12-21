// DlgAlarmHostRs485.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmHostRs485.h"
#include "DlgAlarmHostTransparent.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostRs485 dialog


CDlgAlarmHostRs485::CDlgAlarmHostRs485(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmHostRs485::IDD, pParent)
    , m_iRS485Num(0) 
    , m_i485SlotNum(0) 
{
	//{{AFX_DATA_INIT(CDlgAlarmHostRs485)
	m_csName = _T("");
	m_bEnableAirCondition = FALSE;
	m_iTemprature = 0;
	m_csNameSlot = _T("");
	m_dwDevAddr = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_lRs485Index = -1;
    m_lDevType = -1;
    memset(&m_struDevAbility, 0, sizeof(m_struDevAbility));
    memset(&m_struRs485Cfg, 0, sizeof(m_struRs485Cfg));
    memset(&m_struDevTypeList, 0, sizeof(m_struDevTypeList));
    memset(&m_struDevProtoList, 0, sizeof(m_struDevProtoList));
}


void CDlgAlarmHostRs485::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgAlarmHostRs485)
    DDX_Control(pDX, IDC_CMB_DEVICE_ADDR, m_cmbCascadeDevAddr);
    DDX_Control(pDX, IDC_COMBO_RS485_SLOT_INDEX, m_cmSlotIndex);
    DDX_Control(pDX, IDC_COMBO_DEVICE_TYPE_SLOT, m_cmDeviceTypeSlot);
    DDX_Control(pDX, IDC_COMBO_DEVICE_PROTO_SLOT, m_cmDeviceProtocolSlot);
    DDX_Control(pDX, IDC_COMBO_AIRCONDITION_RS485_INDEX, m_comboAircondition485Index);
    DDX_Control(pDX, IDC_COMBO_AIRCONDITION_MODE, m_comboAirConditionMode);
    DDX_Control(pDX, IDC_COMBO_WORK_MODE, m_comboWorkMode);
    DDX_Control(pDX, IDC_COMBO_DUPLEX, m_comboDuplex);
    DDX_Control(pDX, IDC_COMBO_485_BAUD, m_comboBaud);
    DDX_Control(pDX, IDC_COMBO_485_CHECK_BIT, m_comboCheckBit);
    DDX_Control(pDX, IDC_COMBO_485_DATA_BIT, m_comboDataBit);
    DDX_Control(pDX, IDC_COMBO_485_STOP_BIT, m_comboStopBit);
    DDX_Control(pDX, IDC_COMBO_DEVICE_PROTO, m_comboDeviceProto);
    DDX_Control(pDX, IDC_COMBO_DEVICE_TYPE, m_comboDeviceType);
    DDX_Control(pDX, IDC_COMBO_FLOW_CONTROL, m_comboFlowControl);
    DDX_Control(pDX, IDC_COMBO_RS485_INDEX, m_comboRs485Index);
    DDX_Text(pDX, IDC_EDIT_NAME, m_csName);
    DDV_MaxChars(pDX, m_csName, 32);
    DDX_Check(pDX, IDC_CHK_EANBLE_AIRCONDITION, m_bEnableAirCondition);
    DDX_Text(pDX, IDC_EDIT_TEMPERATURE, m_iTemprature);
    DDX_Text(pDX, IDC_EDIT_NAME_SLOT, m_csNameSlot);
    DDX_Text(pDX, IDC_EDIT_ADDRESS, m_dwDevAddr);
    DDV_MinMaxDWord(pDX, m_dwDevAddr, 0, 65535);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_CMB_SERIAL_TYPE, m_cmbSerialType);
	DDX_Control(pDX, IDC_COMBO_MODE, m_cmbMode);
}


BEGIN_MESSAGE_MAP(CDlgAlarmHostRs485, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmHostRs485)
	ON_CBN_SELCHANGE(IDC_COMBO_RS485_INDEX, OnSelchangeComboRs485Index)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICE_TYPE, OnSelchangeComboDeviceType)
	ON_BN_CLICKED(IDC_BTN_SET_RS485_CFG, OnBtnSetRs485Cfg)
	ON_BN_CLICKED(IDC_BTN_TRANSPARENT, OnBtnTransparent)
	ON_BN_CLICKED(IDC_BTN_SET_AIRCONDITION, OnBtnSetAircondition)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICE_TYPE_SLOT, OnSelchangeComboDeviceTypeSlot)
	ON_BN_CLICKED(IDC_BTN_GET_AIR_CONDITION, OnBtnGetAirCondition)
	ON_BN_CLICKED(IDC_BTN_GET_RS485_CFG, OnBtnGetRs485Cfg)
	ON_BN_CLICKED(IDC_BTN_GET_CASCADE_CFG, OnBtnGetCascadeCfg)
	ON_BN_CLICKED(IDC_BTN_SET_CASCADE_CFG, OnBtnSetCascadeCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostRs485 message handlers

BOOL CDlgAlarmHostRs485::OnInitDialog() 
{
	CDialog::OnInitDialog();
    GetDeviceTypeList(m_struDevTypeList);

    InitWnd();
    m_comboAirConditionMode.SetCurSel(0);
    m_comboAircondition485Index.SetCurSel(0);
    m_comboRs485Index.SetCurSel(0);
	m_cmbCascadeDevAddr.SetCurSel(0);
    OnSelchangeComboRs485Index();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmHostRs485::InitWnd()
{
    Init485IndexCombo();
    InitDeviceTypeCombo();
    InitBaudCombo();
    InitCheckBitCombo();
    InitDataBitCombo();
    InitStopBitCombo();
    InitFlowControlCombo();
    InitDuplexCombo();
    InitWorkMode();
    InitAir485Combo();
	InitCascadeDeviceAddrCombo();
    InitSerialTypeCombo();
	InitModeCombo();
}


void CDlgAlarmHostRs485::Init485IndexCombo()
{
    char szLan[128] = {0};
    m_comboRs485Index.ResetContent();
    int i = 0; 
    int iRs485Num ; 
    iRs485Num = m_struDevAbility.wTotalRs485Num;
    iRs485Num = (m_iRS485Num != 0)? m_iRS485Num : iRs485Num;
    for (i = 0; i < iRs485Num; i++)
    {
        sprintf(szLan, "Rs485 %d", i+1);
        m_comboRs485Index.AddString(szLan);
    }

    int i485SlotNum; 
    i485SlotNum = m_struDevAbility.by485SlotNum;
    i485SlotNum = (m_i485SlotNum != 0)? m_i485SlotNum:i485SlotNum;
    for (i = 0; i < i485SlotNum; i++)
    {
        sprintf(szLan, "Slot %d", i+1);
        m_cmSlotIndex.AddString(szLan);
    }
}

void CDlgAlarmHostRs485::InitDeviceTypeCombo()
{
    m_comboDeviceType.ResetContent();
    for (int i = 0; i <m_struDevTypeList.dwTypeNum; i++)
    {
        m_comboDeviceType.InsertString(i, (char*)m_struDevTypeList.struDeviceType[i].byDescribe);
        m_comboDeviceType.SetItemData(i, m_struDevTypeList.struDeviceType[i].dwType);

		//界面上有两个设备列表框 ， 一个是485参数配置结构体中的，一个是槽位参数配置结构体中的
		m_cmDeviceTypeSlot.InsertString(i, (char*)m_struDevTypeList.struDeviceType[i].byDescribe);
        m_cmDeviceTypeSlot.SetItemData(i, m_struDevTypeList.struDeviceType[i].dwType);
    }
}

void CDlgAlarmHostRs485::InitDeviceProtoCombo()
{
    m_comboDeviceProto.ResetContent();
    for (int i = 0; i < m_struDevProtoList.dwProtoNum; i++)
    {
        m_comboDeviceProto.InsertString(i, (char*)m_struDevProtoList.struProtoType[i].byDescribe);
        m_comboDeviceProto.SetItemData(i, m_struDevProtoList.struProtoType[i].dwType);
    }
}

void CDlgAlarmHostRs485::InitBaudCombo()
{
    int nIndex = 0;
    m_comboBaud.ResetContent();

    m_comboBaud.InsertString(nIndex, "50");
    m_comboBaud.SetItemData(nIndex, 0);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "75");
    m_comboBaud.SetItemData(nIndex, 1);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "110");
    m_comboBaud.SetItemData(nIndex, 2);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "150");
    m_comboBaud.SetItemData(nIndex, 3);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "300");
    m_comboBaud.SetItemData(nIndex, 4);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "600");
    m_comboBaud.SetItemData(nIndex, 5);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "1200");
    m_comboBaud.SetItemData(nIndex, 6);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "2400");
    m_comboBaud.SetItemData(nIndex, 7);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "4800");
    m_comboBaud.SetItemData(nIndex, 8);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "9600");
    m_comboBaud.SetItemData(nIndex, 9);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "19200");
    m_comboBaud.SetItemData(nIndex, 10);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "38400");
    m_comboBaud.SetItemData(nIndex, 11);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "57600");
    m_comboBaud.SetItemData(nIndex, 12);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "76800");
    m_comboBaud.SetItemData(nIndex, 13);
    nIndex++;
	m_comboBaud.InsertString(nIndex, "115200");
    m_comboBaud.SetItemData(nIndex, 14);
}

void CDlgAlarmHostRs485::InitCheckBitCombo()
{
//     BYTE    byParity;               //是否校验：0-无校验，1-奇校验，2-偶校验 
    // No parity, 1 - odd parity, 2 - even parity
    int nIndex = 0;
    m_comboCheckBit.ResetContent();
    m_comboCheckBit.InsertString(nIndex, "No parity");
    m_comboCheckBit.SetItemData(nIndex, 0);
    nIndex++;
    m_comboCheckBit.InsertString(nIndex, "odd parity");
    m_comboCheckBit.SetItemData(nIndex, 1);
    nIndex++;
    m_comboCheckBit.InsertString(nIndex, "even parity");
    m_comboCheckBit.SetItemData(nIndex, 2);
    nIndex++;
}

void CDlgAlarmHostRs485::InitDataBitCombo()
{
    //     BYTE    byDataBit;              // 数据有几位：0-5位，1-6位，2-7位，3-8位 
    int nIndex = 0;
    m_comboDataBit.ResetContent();
    m_comboDataBit.InsertString(nIndex, "5bit");
    m_comboDataBit.SetItemData(nIndex, 0);
    nIndex++;
    m_comboDataBit.InsertString(nIndex, "6bit");
    m_comboDataBit.SetItemData(nIndex, 1);
    nIndex++;
    m_comboDataBit.InsertString(nIndex, "7bit");
    m_comboDataBit.SetItemData(nIndex, 2);
    nIndex++;
    m_comboDataBit.InsertString(nIndex, "8bit");
    m_comboDataBit.SetItemData(nIndex, 3);
    nIndex++;

}

void CDlgAlarmHostRs485::InitStopBitCombo()
{
    int nIndex = 0;
    m_comboStopBit.ResetContent();
    m_comboStopBit.InsertString(nIndex, "1bit");
    m_comboStopBit.SetItemData(nIndex, 0);
    nIndex++;
    m_comboStopBit.InsertString(nIndex, "2bit");
    m_comboStopBit.SetItemData(nIndex, 1);
    nIndex++;
}

void CDlgAlarmHostRs485::InitFlowControlCombo()
{
    int nIndex = 0;
    m_comboFlowControl.ResetContent();
    m_comboFlowControl.InsertString(nIndex, "No");
    m_comboFlowControl.SetItemData(nIndex, 0);
    nIndex++;
    m_comboFlowControl.InsertString(nIndex, "Soft");
    m_comboFlowControl.SetItemData(nIndex, 1);
    nIndex++;    
    m_comboFlowControl.InsertString(nIndex, "Hard");
    m_comboFlowControl.SetItemData(nIndex, 2);
    nIndex++;
}
void CDlgAlarmHostRs485::InitDuplexCombo()
{
    m_comboDuplex.ResetContent();
    m_comboDuplex.AddString("Half duplex");
    m_comboDuplex.AddString("Full duplex");
}

void CDlgAlarmHostRs485::InitWorkMode()
{
	CString tmp;
	char szLan[128] = {0};
    m_comboWorkMode.ResetContent();
	
	g_StringLanType(szLan, "控制台","Console");
	m_comboWorkMode.AddString(szLan);
	m_comboWorkMode.SetItemData(0, 0);
	
	g_StringLanType(szLan, "透明通道", "Transparent channel");
	m_comboWorkMode.AddString(szLan);
	m_comboWorkMode.SetItemData(1, 1);
	
	g_StringLanType(szLan, "梯控", "Elevator Control");
	m_comboWorkMode.AddString(szLan);
	m_comboWorkMode.SetItemData(2, 2);
	
	g_StringLanType(szLan, "读卡器", "Card Reader");
	m_comboWorkMode.AddString(szLan);
	m_comboWorkMode.SetItemData(3, 3);
	
	g_StringLanType(szLan, "自定义", "Custom");
	m_comboWorkMode.AddString(szLan);
	m_comboWorkMode.SetItemData(4, 254);
	
	g_StringLanType(szLan, "禁用", "Disabled");
	m_comboWorkMode.AddString(szLan);
	m_comboWorkMode.SetItemData(5, 255);
}

void CDlgAlarmHostRs485::InitAir485Combo()
{
    char szLan[128] = {0};
    m_comboAircondition485Index.ResetContent();
    for (int i = 0; i < (m_struDevAbility.wLocalRs485Num + m_struDevAbility.wExpandRs485Num); i++)
    {
        sprintf(szLan, "Rs485 %d", i+1);
        m_comboAircondition485Index.AddString(szLan);
    }
}

void CDlgAlarmHostRs485::InitAirconditionModeCombo()
{
    char szLan[128] = {0};
    m_comboAirConditionMode.ResetContent();
    g_StringLanType(szLan, "制冷", "Refrigeration");
    m_comboAirConditionMode.AddString(szLan);
    g_StringLanType(szLan, "制热", "Heating");
    m_comboAirConditionMode.AddString(szLan);
    g_StringLanType(szLan, "抽湿", "Dehumidifier");
    m_comboAirConditionMode.AddString(szLan);
    g_StringLanType(szLan, "自动", "Auto");
    m_comboAirConditionMode.AddString(szLan);
}

BOOL CDlgAlarmHostRs485::GetRs485Cfg(NET_DVR_ALARM_RS485CFG &struRs485Cfg)
{
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ALARM_RS485CFG, m_lRs485Index, &struRs485Cfg, sizeof(struRs485Cfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARM_RS485CFG");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARM_RS485CFG");
        return FALSE;
    }
}
BOOL CDlgAlarmHostRs485::SetRs485Cfg(NET_DVR_ALARM_RS485CFG &struRs485Cfg)
{
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_ALARM_RS485CFG, m_lRs485Index, &struRs485Cfg, sizeof(struRs485Cfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVE_SET_ALARM_RS485CFG");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVE_SET_ALARM_RS485CFG");
        return FALSE;
    }
}

BOOL CDlgAlarmHostRs485::GetDeviceTypeList(NET_DVR_DEVICE_TYPE_LIST& struDevTypeList)
{
    if (NET_DVR_GetDeviceTypeList(m_lServerID, &struDevTypeList))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetDeviceTypeList");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetDeviceTypeList");
        return FALSE;
    }
}

BOOL CDlgAlarmHostRs485::GetDeviceProtoList(NET_DVR_DEVICE_PROTO_LIST& struDevProtoList)
{
    if (NET_DVR_GetDeviceProtoList(m_lServerID, m_lDevType, &struDevProtoList))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetDeviceProtoList");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetDeviceProtoList");
        return FALSE;
    }
}

void CDlgAlarmHostRs485::GetRs485CfgFromWnd(NET_DVR_ALARM_RS485CFG &struRs485Cfg)
{
    strncpy((char*)struRs485Cfg.sDeviceName, m_csName.GetBuffer(0), sizeof(struRs485Cfg.sDeviceName));
    struRs485Cfg.wDeviceType = m_comboDeviceType.GetItemData(m_comboDeviceType.GetCurSel());
    struRs485Cfg.wDeviceProtocol = m_comboDeviceProto.GetItemData(m_comboDeviceProto.GetCurSel());
    struRs485Cfg.dwBaudRate = m_comboBaud.GetItemData(m_comboBaud.GetCurSel());
    struRs485Cfg.byDataBit = m_comboDataBit.GetItemData(m_comboDataBit.GetCurSel());
    struRs485Cfg.byStopBit = m_comboStopBit.GetItemData(m_comboStopBit.GetCurSel());
    struRs485Cfg.byParity = m_comboCheckBit.GetItemData(m_comboCheckBit.GetCurSel());
    struRs485Cfg.byFlowcontrol = m_comboFlowControl.GetItemData(m_comboFlowControl.GetCurSel());
    struRs485Cfg.byDuplex = m_comboDuplex.GetCurSel();
    struRs485Cfg.byWorkMode = m_comboWorkMode.GetCurSel();
    struRs485Cfg.bySerialType = m_cmbSerialType.GetCurSel();
	struRs485Cfg.byMode = m_cmbMode.GetCurSel();
}
void CDlgAlarmHostRs485::SetRs485CfgToWnd(NET_DVR_ALARM_RS485CFG &struRs485Cfg)
{
    int nIndex = 0;
    char szLan[40] = {0};
    strncpy(szLan, (char *)struRs485Cfg.sDeviceName, sizeof(struRs485Cfg.sDeviceName));
    m_csName = szLan;
    for (nIndex = 0; nIndex < m_comboDeviceType.GetCount(); nIndex++)
    {
        if (m_comboDeviceType.GetItemData(nIndex) == struRs485Cfg.wDeviceType)
        {
            m_comboDeviceType.SetCurSel(nIndex);
            OnSelchangeComboDeviceType();
            break;
        }
    }
    for (nIndex = 0; nIndex < m_comboDeviceProto.GetCount(); nIndex++)
    {
        if (m_comboDeviceProto.GetItemData(nIndex) == struRs485Cfg.wDeviceProtocol)
        {
            m_comboDeviceProto.SetCurSel(nIndex);
            break;
        }
    }
    m_comboBaud.SetCurSel(struRs485Cfg.dwBaudRate);
    m_comboDataBit.SetCurSel(struRs485Cfg.byDataBit);
    m_comboStopBit.SetCurSel(struRs485Cfg.byStopBit);
    m_comboCheckBit.SetCurSel(struRs485Cfg.byParity);
    m_comboFlowControl.SetCurSel(struRs485Cfg.byFlowcontrol);
    m_comboDuplex.SetCurSel(struRs485Cfg.byDuplex);
    m_comboWorkMode.SetCurSel(struRs485Cfg.byWorkMode);
    m_cmbSerialType.SetCurSel(struRs485Cfg.bySerialType);
	m_cmbMode.SetCurSel(struRs485Cfg.byMode);
}

void CDlgAlarmHostRs485::OnSelchangeComboRs485Index() 
{
    m_lRs485Index = m_comboRs485Index.GetCurSel() + 1;

    if (m_lRs485Index == 1)
    {
        m_comboDuplex.EnableWindow(TRUE);
    }
    else
    {
        m_comboDuplex.EnableWindow(FALSE);
    }
    if (!GetRs485Cfg(m_struRs485Cfg))
    {
        AfxMessageBox("Fail to get rs485 config");
        return;
    }
    
    SetRs485CfgToWnd(m_struRs485Cfg);
    UpdateData(FALSE);
}

void CDlgAlarmHostRs485::OnSelchangeComboDeviceType() 
{
    m_lDevType = m_comboDeviceType.GetItemData(m_comboDeviceType.GetCurSel());
    
    GetDeviceProtoList(m_struDevProtoList);
    InitDeviceProtoCombo();
}

void CDlgAlarmHostRs485::OnBtnSetRs485Cfg() 
{
    UpdateData(TRUE);
    GetRs485CfgFromWnd(m_struRs485Cfg);
    if (SetRs485Cfg(m_struRs485Cfg))
    {
        AfxMessageBox("Succ to set rs485 config");
    }
}

void CDlgAlarmHostRs485::OnBtnTransparent() 
{
	CDlgAlarmHostTransparent dlg;
    dlg.m_lServerID = m_lServerID;
    memcpy(&dlg.m_struDevAbility, &m_struDevAbility, sizeof(m_struDevAbility));
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgAlarmHostRs485::OnBtnSetAircondition() 
{
	NET_DVR_AIR_CONDITION_PARAM struAirCondition;
    memset(&struAirCondition, 0, sizeof(struAirCondition));

    UpdateData(TRUE);
    struAirCondition.dwSize = sizeof(struAirCondition);
    struAirCondition.byEnable = m_bEnableAirCondition;
    struAirCondition.byMode = m_comboAirConditionMode.GetCurSel();
    struAirCondition.byTemperature = (BYTE)m_iTemprature;

	if (!SetAirCondition(struAirCondition))
	{
        AfxMessageBox("Fail to control aircondition");
	}
}


BOOL CDlgAlarmHostRs485::SetAirCondition(NET_DVR_AIR_CONDITION_PARAM &struAirCondition)
{
    BOOL bRet = FALSE;

    DWORD dwChanIndex = 0;
    DWORD dwSlotIndex = 0;
    DWORD dwInput = 0;
    //485号从1开始
    dwChanIndex = m_comboRs485Index.GetCurSel() + 1;
    dwChanIndex = dwChanIndex << 16;
    //槽位号从1开始
    dwSlotIndex = m_cmSlotIndex.GetCurSel() + 1;
    dwInput = dwChanIndex | dwSlotIndex;

    if (NET_DVR_SetAirCondition(m_lServerID, dwInput, &struAirCondition))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetAirCondition");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetAirCondition");
        bRet = FALSE;
    }
    return bRet;
}

void CDlgAlarmHostRs485::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn = 0;
	DWORD dwChanIndex = 0;
	DWORD dwSlotIndex = 0;
	DWORD dwInput = 0; 
	int i=0;
	//485号从1开始
	dwChanIndex = m_comboRs485Index.GetCurSel() + 1;
	dwChanIndex = dwChanIndex << 16;
	//槽位号从1开始
	dwSlotIndex = m_cmSlotIndex.GetCurSel() + 1;
	dwInput = dwChanIndex | dwSlotIndex;
	
	m_stru485Slot.dwSize = sizeof(NET_DVR_ALARMHOST_RS485_SLOT_CFG);
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ALARMHOST_RS485_SLOT_CFG, dwInput, &m_stru485Slot, sizeof(NET_DVR_ALARMHOST_RS485_SLOT_CFG), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Get RS485 slot failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Get RS485 slot successful");
	}

	m_dwDevAddr = m_stru485Slot.wAddress;
	m_csNameSlot.Format("%s", m_stru485Slot.sDeviceName);
    for (i = 0; i < m_cmDeviceTypeSlot.GetCount(); i++)
    {
        if (m_cmDeviceTypeSlot.GetItemData(i) == m_stru485Slot.wDeviceType)
        {
            m_cmDeviceTypeSlot.SetCurSel(i);
			UpdateData(FALSE);
            OnSelchangeComboDeviceTypeSlot();
            break;
        }
    }
    for (i = 0; i < m_cmDeviceProtocolSlot.GetCount(); i++)
    {
        if (m_cmDeviceProtocolSlot.GetItemData(i) == m_stru485Slot.wDeviceProtocol)
        {
            m_cmDeviceProtocolSlot.SetCurSel(i);
            break;
        }
    }
	UpdateData(FALSE);
}

void CDlgAlarmHostRs485::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwChanIndex = 0;
	DWORD dwSlotIndex = 0;
	DWORD dwInput = 0; 
	//485号从1开始
	dwChanIndex = m_comboRs485Index.GetCurSel() + 1;
	dwChanIndex = dwChanIndex << 16;
	//槽位号从1开始
	dwSlotIndex = m_cmSlotIndex.GetCurSel() + 1;
	dwInput = dwChanIndex | dwSlotIndex;
	
	//设备类型
	m_stru485Slot.wDeviceType = m_cmDeviceTypeSlot.GetItemData(m_cmDeviceTypeSlot.GetCurSel());
	//协议类型
	m_stru485Slot.wDeviceProtocol = m_cmDeviceProtocolSlot.GetItemData(m_cmDeviceProtocolSlot.GetCurSel());
	//设备地址
	m_stru485Slot.wAddress = m_dwDevAddr;
	sprintf((char*)m_stru485Slot.sDeviceName, m_csNameSlot, NAME_LEN);

	m_stru485Slot.dwSize = sizeof(NET_DVR_ALARMHOST_RS485_SLOT_CFG);
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_ALARMHOST_RS485_SLOT_CFG, dwInput, &m_stru485Slot, sizeof(NET_DVR_ALARMHOST_RS485_SLOT_CFG)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Set RS485 slot failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Set RS485 slot successful");
	}
}

void CDlgAlarmHostRs485::OnSelchangeComboDeviceTypeSlot() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iDevIndex = m_cmDeviceTypeSlot.GetCurSel();
	m_lDevType = m_cmDeviceTypeSlot.GetItemData(iDevIndex);
    GetDeviceProtoList(m_struDevProtoList);
    InitDeviceProtoComboSlot();
}
void CDlgAlarmHostRs485::InitDeviceProtoComboSlot() 
{
    m_cmDeviceProtocolSlot.ResetContent();
    for (int i = 0; i < m_struDevProtoList.dwProtoNum; i++)
    {	
		m_cmDeviceProtocolSlot.InsertString(i, (char*)m_struDevProtoList.struProtoType[i].byDescribe);
        m_cmDeviceProtocolSlot.SetItemData(i, m_struDevProtoList.struProtoType[i].dwType);
    }
	UpdateData(FALSE);
}


void CDlgAlarmHostRs485::OnBtnGetAirCondition() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_AIR_CONDITION_PARAM struAirCondition;
	DWORD dwChanIndex = 0;
	DWORD dwSlotIndex = 0;
	DWORD dwInput = 0; 
	//485号从1开始
	dwChanIndex = m_comboRs485Index.GetCurSel() + 1;
	dwChanIndex = dwChanIndex << 16;
	//槽位号从1开始
	dwSlotIndex = m_cmSlotIndex.GetCurSel() + 1;
	//dwSlotIndex = dwSlotIndex << 16;
	dwInput = dwChanIndex | dwSlotIndex;
	
	DWORD returned = 0;
	if(!NET_DVR_GetDVRConfig(m_lServerID,NET_DVR_GET_AIR_CONDITION_PARAM,dwInput,&struAirCondition,sizeof(struAirCondition),&returned))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Set RS485 slot failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Set RS485 slot successful");
	}
    m_bEnableAirCondition = struAirCondition.byEnable;
    m_comboAirConditionMode.SetCurSel(struAirCondition.byMode);
    m_iTemprature = struAirCondition.byTemperature;
	UpdateData(FALSE);
}

void CDlgAlarmHostRs485::OnBtnGetRs485Cfg() 
{
	// TODO: Add your control notification handler code here
    if (!GetRs485Cfg(m_struRs485Cfg))
    {
        AfxMessageBox("Fail to get rs485 config");
        return;
    }
    SetRs485CfgToWnd(m_struRs485Cfg);
    UpdateData(FALSE);
}


void CDlgAlarmHostRs485::InitCascadeDeviceAddrCombo()
{
	char szLan[128] = {0};
    m_cmbCascadeDevAddr.ResetContent();
	
	g_StringLanType(szLan, "主机", "Host Device");
	m_cmbCascadeDevAddr.AddString(szLan);
    for (int i = 1; i < 16; i++)
    {
		g_StringLanType(szLan, "从机", "Slave Device");
        sprintf(szLan, "%s-%d", szLan, i);
        m_cmbCascadeDevAddr.AddString(szLan);
    }
}

void CDlgAlarmHostRs485::InitModeCombo()
{
	char szLan[128] = { 0 };
	m_cmbMode.ResetContent();
	g_StringLanType(szLan, "连接读卡器", "Connect card reader");
	m_cmbMode.AddString(szLan);
	g_StringLanType(szLan, "连接客户端", "Connect client");
	m_cmbMode.AddString(szLan);
	g_StringLanType(szLan, "连接扩展模块", "Connect extension module");
    m_cmbMode.AddString(szLan);
    g_StringLanType(szLan, "连接门禁主机", "Connect acs host");
	m_cmbMode.AddString(szLan);
    g_StringLanType(szLan, "禁用", "Disabled");
    m_cmbMode.AddString(szLan);
    m_cmbMode.SetItemData(4, 255);
}

void CDlgAlarmHostRs485::InitSerialTypeCombo()
{
    char szLan[128] = { 0 };
    m_cmbSerialType.ResetContent();

    g_StringLanType(szLan, "485", "485");
    m_cmbSerialType.AddString(szLan);
    g_StringLanType(szLan, "232", "232");
    m_cmbSerialType.AddString(szLan);
}

void CDlgAlarmHostRs485::OnBtnGetCascadeCfg()
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	char szLan[128] = {0};
	NET_DVR_RS485_CASCADE_CFG struRs485CascadeCfg = {0};
	struRs485CascadeCfg.dwSize = sizeof(NET_DVR_RS485_CASCADE_CFG);
	
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_RS485_CASCADE_CFG, 0, &struRs485CascadeCfg, sizeof(NET_DVR_RS485_CASCADE_CFG), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_RS485_CASCADE_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_RS485_CASCADE_CFG");
		g_StringLanType(szLan, "获取Rs485级联配置失败", "Get rs485 cascade config failed!");
		AfxMessageBox(szLan);
        return;
    }
	
	m_cmbCascadeDevAddr.SetCurSel(struRs485CascadeCfg.byDevAddr);
	UpdateData(FALSE);
}

void CDlgAlarmHostRs485::OnBtnSetCascadeCfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	char szLan[128] = {0};
	NET_DVR_RS485_CASCADE_CFG struRs485CascadeCfg = {0};
	struRs485CascadeCfg.dwSize = sizeof(NET_DVR_RS485_CASCADE_CFG);
	struRs485CascadeCfg.byDevAddr = m_cmbCascadeDevAddr.GetCurSel();
	
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_RS485_CASCADE_CFG, 0, &struRs485CascadeCfg, sizeof(NET_DVR_RS485_CASCADE_CFG)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_RS485_CASCADE_CFG");
		g_StringLanType(szLan, "设置Rs485级联配置失败", "Set rs485 cascade config failed!");
		AfxMessageBox(szLan);
        return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_RS485_CASCADE_CFG");
	}
}