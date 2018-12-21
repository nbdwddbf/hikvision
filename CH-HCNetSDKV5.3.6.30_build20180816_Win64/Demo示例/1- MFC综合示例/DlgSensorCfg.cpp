// DlgSensorCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSensorCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define SENSOR_ALARM_TIMER			100		//timer for system parameter,cpu

/////////////////////////////////////////////////////////////////////////////
// CDlgSensorCfg dialog

CDlgSensorCfg::CDlgSensorCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSensorCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSensorCfg)
	m_csSensorName = _T("");
	m_bValid = FALSE;
	m_fLineValue1 = 0.0f;
	m_fLineValue2 = 0.0f;
	m_fLineValue3 = 0.0f;
	m_fLineValue4 = 0.0f;
	m_fMeasureHigh = 0.0f;
	m_fMeasureLow = 0.0f;
	m_fSensorValue = 0.0f;
    m_fOriginalValue = 0.0f;
	m_bEnable = FALSE;
	m_fSensitive = 0.0f;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_dwSensorNum = 0;
    m_lChanNum = -1;
    memset(&m_struSensorInfo, 0, sizeof(m_struSensorInfo));
    memset(&m_struDevAbility, 0, sizeof(m_struDevAbility));
}


void CDlgSensorCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSensorCfg)
	DDX_Control(pDX, IDC_COMBO_SENSOR_STANDARD, m_cmSensorStandard);
	DDX_Control(pDX, IDC_LIST_OSD_CHAN, m_listOsdChan);
	DDX_Control(pDX, IDC_COMBO_SENSOR_TYPE, m_comboSensorType);
	DDX_Control(pDX, IDC_COMBO_LINE_MODE4, m_comboLineMode4);
	DDX_Control(pDX, IDC_COMBO_LINE_MODE3, m_comboLineMode3);
	DDX_Control(pDX, IDC_COMBO_LINE_MODE2, m_comboLineMode2);
	DDX_Control(pDX, IDC_COMBO_LINE_MODE1, m_comboLineMode1);
	DDX_Control(pDX, IDC_COMBO_SENSOR_INDEX, m_comboSensorIndex);
	DDX_Text(pDX, IDC_EDIT_SENSOR_NAME, m_csSensorName);
	DDX_Check(pDX, IDC_CHK_VALID, m_bValid);
	DDX_Text(pDX, IDC_EDIT_LINE_VALUE1, m_fLineValue1);
	DDX_Text(pDX, IDC_EDIT_LINE_VALUE2, m_fLineValue2);
	DDX_Text(pDX, IDC_EDIT_LINE_VALUE3, m_fLineValue3);
	DDX_Text(pDX, IDC_EDIT_LINE_VALUE4, m_fLineValue4);
	DDX_Text(pDX, IDC_EDIT_MEASURE_HIGH, m_fMeasureHigh);
	DDX_Text(pDX, IDC_EDIT_MEASURE_LOW, m_fMeasureLow);
	DDX_Text(pDX, IDC_EDIT_SENSOR_VALUE, m_fSensorValue);
    DDX_Text(pDX, IDC_EDIT_ORIGINAL_VALUE, m_fOriginalValue);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_SENSITIVE, m_fSensitive);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSensorCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgSensorCfg)
	ON_BN_CLICKED(IDC_BTN_SET_SENSORCFG, OnBtnSetSensorcfg)
	ON_CBN_SELCHANGE(IDC_COMBO_SENSOR_INDEX, OnSelchangeComboSensorIndex)
	ON_BN_CLICKED(IDC_BTN_CONFIRM, OnBtnConfirm)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_GET_VALUE, OnBtnGetValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSensorCfg message handlers

BOOL CDlgSensorCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    g_pDlgSensor = this;
    
    m_dwSensorNum = m_struDevAbility.wTotalSensorNum;

    InitWnd();

    m_comboSensorIndex.SetCurSel(0);
    OnSelchangeComboSensorIndex();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// NET_DVR_SET_SENSOR_CFG

BOOL CDlgSensorCfg::SetSensorCfg()
{
    BOOL bRet = FALSE;
    LONG m_lSensorChannel = m_comboSensorIndex.GetCurSel() + 1;
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_SENSOR_CFG, m_lSensorChannel, &m_struSensorInfo,sizeof(m_struSensorInfo)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SENSOR_CFG");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SENSOR_CFG");
        bRet = FALSE;
    }
    return bRet;
}

BOOL CDlgSensorCfg::GetSensorCfg()
{
    DWORD dwReturn = 0;
    BOOL bRet = FALSE;
    LONG m_lSensorChannel = m_comboSensorIndex.GetCurSel() + 1;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_SENSOR_CFG, m_lSensorChannel, &m_struSensorInfo, sizeof(m_struSensorInfo), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SENSOR_CFG");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SENSOR_CFG");
        bRet = FALSE;
    }
    return bRet;
}

void CDlgSensorCfg::OnBtnSetSensorcfg() 
{
    UpdateData(TRUE);
    GetSensorInfoFromWnd(m_struSensorInfo);
    if (!SetSensorCfg())
    {
        AfxMessageBox("fail to set sensor config");
    }
}


void CDlgSensorCfg::InitWnd()
{
    m_comboSensorIndex.ResetContent();
    char szLan[256] = {0};
	int i = 0;
    for (i = 0; i < m_dwSensorNum; i++)
    {
        sprintf(szLan, "Sensor %d", i + 1);
        m_comboSensorIndex.AddString(szLan);
    }

    int nIndex = 0;
    m_comboSensorType.ResetContent();
	g_StringLanType(szLan, "无", "NO");
    m_comboSensorType.InsertString(nIndex, szLan);
    m_comboSensorType.SetItemData(nIndex, SENSOR_TYPE_NONE);
    nIndex++;

	g_StringLanType(szLan, "温度", "Temperature");
    m_comboSensorType.InsertString(nIndex, szLan);
    m_comboSensorType.SetItemData(nIndex, SENSOR_TYPE_TEMPERATURE);
    nIndex++;

	g_StringLanType(szLan, "湿度", "Humidity");
    m_comboSensorType.InsertString(nIndex, szLan);
    m_comboSensorType.SetItemData(nIndex, SENSOR_TYPE_HUMIDITY);
    nIndex++;

	g_StringLanType(szLan, "风速", "Wind velocity");
    m_comboSensorType.InsertString(nIndex, szLan);
    m_comboSensorType.SetItemData(nIndex, SENSOR_TYPE_WINDSPEED);
    nIndex++;

	g_StringLanType(szLan, "气体", "Gas");
    m_comboSensorType.InsertString(nIndex, szLan);
    m_comboSensorType.SetItemData(nIndex, SENSOR_TYPE_GAS);
    nIndex++;

	g_StringLanType(szLan, "交流电压", "AC VOLTAGE");
	m_comboSensorType.InsertString(nIndex, szLan);
    m_comboSensorType.SetItemData(nIndex, SENSOR_AC_VOLTAGE);
    nIndex++;
	
	g_StringLanType(szLan, "交流电流", "AC CURRENT");
	m_comboSensorType.InsertString(nIndex, szLan);
    m_comboSensorType.SetItemData(nIndex, SENSOR_AC_CURRENT);
    nIndex++;
	
	g_StringLanType(szLan, "直流电压", "DC VOLTAGE");
	m_comboSensorType.InsertString(nIndex, szLan);
    m_comboSensorType.SetItemData(nIndex, SENSOR_DC_VOLTAGE);
    nIndex++;
	
	g_StringLanType(szLan, "直流电流", "DC CURRENT");
	m_comboSensorType.InsertString(nIndex, szLan);
    m_comboSensorType.SetItemData(nIndex, SENSOR_DC_CURRENT);
    nIndex++;
	
	g_StringLanType(szLan, "水压", "WATER PRESSUR");
	m_comboSensorType.InsertString(nIndex, szLan);
    m_comboSensorType.SetItemData(nIndex, SENSOR_WATER_PRESSURE);
    nIndex++;
	
	g_StringLanType(szLan, "压力变送器", "PRESSURE TRANSMITTER");
	m_comboSensorType.InsertString(nIndex, szLan);
    m_comboSensorType.SetItemData(nIndex, SENSOR_PRESSURE_TRANSMITTER);
    nIndex++;
	
	g_StringLanType(szLan, "流量变送器", "FLOW TRANSMITTER");
	m_comboSensorType.InsertString(nIndex, szLan);
    m_comboSensorType.SetItemData(nIndex, SENSOR_FLOW_TRANSMITTER);
    nIndex++;

	g_StringLanType(szLan, "漏水传感器", "WATER LEAKAGE");
	m_comboSensorType.InsertString(nIndex, szLan);
    m_comboSensorType.SetItemData(nIndex, SENSOR_WATER_LEAKAGE);
    nIndex++;
	
	g_StringLanType(szLan, "一体化温变", "INTERGRATED TEMPERATURE DETECTOR");
	m_comboSensorType.InsertString(nIndex, szLan);
    m_comboSensorType.SetItemData(nIndex, SENSOR_INTERGRATED_TEMPERATURE_DETECTOR);
    nIndex++;
	
	g_StringLanType(szLan, "隔离式温变", "ISOLATION TEMPERATURE DETECTOR");
	m_comboSensorType.InsertString(nIndex, szLan);
    m_comboSensorType.SetItemData(nIndex, SENSOR_ISOLATION_TEMPERATURE_DETECTOR);
    nIndex++;
	
	g_StringLanType(szLan, "在线余氯仪", "RESIDUAL CHLORINE");
	m_comboSensorType.InsertString(nIndex, szLan);
    m_comboSensorType.SetItemData(nIndex, SENSOR_RESIDUAL_CHLORINE);
    nIndex++;

	g_StringLanType(szLan, "未定义", "Undefined");
    m_comboSensorType.InsertString(nIndex, szLan);
    m_comboSensorType.SetItemData(nIndex, SENSOR_TYPE_UNKNOW);
    nIndex++;

    m_listOsdChan.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < m_lChanNum; i++)
    {
        sprintf(szLan, "Chan%d", (i+1));
        m_listOsdChan.InsertItem(i, szLan);
    }

	m_comboLineMode1.ResetContent();
	m_comboLineMode2.ResetContent();
	m_comboLineMode3.ResetContent();
	m_comboLineMode4.ResetContent();
	g_StringLanType(szLan, "下限", "Lower limit");
	m_comboLineMode1.AddString(szLan);
	m_comboLineMode2.AddString(szLan);
	m_comboLineMode3.AddString(szLan);
	m_comboLineMode4.AddString(szLan);

	g_StringLanType(szLan, "上限", "Upper limit");
	m_comboLineMode1.AddString(szLan);
	m_comboLineMode2.AddString(szLan);
	m_comboLineMode3.AddString(szLan);
	m_comboLineMode4.AddString(szLan);
}


BOOL CDlgSensorCfg::GetSensorInfoFromWnd(NET_DVR_SENSOR_INFO &strusSensorInfo)
{
    strusSensorInfo.byEnable = m_bEnable;
    strusSensorInfo.byValid = m_bValid;
    strncpy((char*)strusSensorInfo.byName, m_csSensorName.GetBuffer(0), sizeof(strusSensorInfo.byName));
    strusSensorInfo.byType = m_comboSensorType.GetItemData(m_comboSensorType.GetCurSel());
    
    strusSensorInfo.fMeasureHigh = m_fMeasureHigh;
    strusSensorInfo.fMeasureLow = m_fMeasureLow;
    strusSensorInfo.fAlarm1 = m_fLineValue1;
    strusSensorInfo.fAlarm2 = m_fLineValue2;
    strusSensorInfo.fAlarm3 = m_fLineValue3;
    strusSensorInfo.fAlarm4 = m_fLineValue4;
    
    strusSensorInfo.fSensitive = m_fSensitive / 100;
    strusSensorInfo.byAlarmMode = ((m_comboLineMode1.GetCurSel() << 0) | (m_comboLineMode2.GetCurSel() << 1)\
        | (m_comboLineMode3.GetCurSel() << 2) | (m_comboLineMode4.GetCurSel() << 3)  );
    
    
    strusSensorInfo.dwOsdCfg = 0;
    for (int i = 0; i < m_listOsdChan.GetItemCount(); i++)
    {
        strusSensorInfo.dwOsdCfg |=  (m_listOsdChan.GetCheck(i) << i);
    }
    
	strusSensorInfo.bySensorStandard = m_cmSensorStandard.GetCurSel();
    return TRUE;
}

BOOL CDlgSensorCfg::SetSensorInfoToWnd(const NET_DVR_SENSOR_INFO &strusSensorInfo)
{   
    m_bEnable = strusSensorInfo.byEnable;
    m_bValid = strusSensorInfo.byValid;
    char szName[40] = {0};
    strncpy(szName, (char*)strusSensorInfo.byName, sizeof(strusSensorInfo.byName));
    m_csSensorName = szName;
	int i = 0;
    for (i = 0; i < m_comboSensorType.GetCount(); i++)
    {
        if (m_comboSensorType.GetItemData(i) == strusSensorInfo.byType)
        {
            m_comboSensorType.SetCurSel(i);
            break;
        }
    }

    m_fMeasureHigh = strusSensorInfo.fMeasureHigh;
    m_fMeasureLow = strusSensorInfo.fMeasureLow;
    m_fLineValue1 = strusSensorInfo.fAlarm1;
    m_fLineValue2 = strusSensorInfo.fAlarm2;
    m_fLineValue3 = strusSensorInfo.fAlarm3;
    m_fLineValue4 = strusSensorInfo.fAlarm4;
    m_fSensitive = strusSensorInfo.fSensitive * 100;

    m_comboLineMode1.SetCurSel((strusSensorInfo.byAlarmMode >> 0) & 0x01 );
    m_comboLineMode2.SetCurSel((strusSensorInfo.byAlarmMode >> 1) & 0x01);
    m_comboLineMode3.SetCurSel((strusSensorInfo.byAlarmMode >> 2) & 0x01);
    m_comboLineMode4.SetCurSel((strusSensorInfo.byAlarmMode >> 3) & 0x01);


    for ( i = 0; i < m_listOsdChan.GetItemCount(); i++)
    {
        m_listOsdChan.SetCheck(i, ((strusSensorInfo.dwOsdCfg >> i ) & 0x01));
    }

	m_cmSensorStandard.SetCurSel(m_struSensorInfo.bySensorStandard);
    return TRUE;
}

void CDlgSensorCfg::OnSelchangeComboSensorIndex() 
{
    GetSensorCfg();
    SetSensorInfoToWnd(m_struSensorInfo);
    UpdateData(FALSE);
}

void CDlgSensorCfg::OnBtnConfirm() 
{
//     int nIndex = m_comboSensorIndex.GetCurSel();
//     UpdateData(TRUE);
//     GetSensorInfoFromWnd(m_struSensorCfg.struSensorInfo[nIndex]);
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgSensorCfg::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgSensorCfg::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: Add your message handler code here and/or call default
    switch (nIDEvent)
    {
    case SENSOR_ALARM_TIMER:
        
        break;
    default:
        break;
    }
	CDialog::OnTimer(nIDEvent);
}

void CDlgSensorCfg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
    g_pDlgSensor = NULL;
	
	CDialog::PostNcDestroy();
}

BOOL CDlgSensorCfg::SetSensorDate(NET_DVR_SENSOR_ALARM& struSensorAlarm)
{
    if (struSensorAlarm.bySensorChannel == m_comboSensorIndex.GetCurSel() + 1)
    {
        m_fSensorValue = struSensorAlarm.fValue;
        char szBuf[128] = {0};
            sprintf(szBuf, "%.3f ",struSensorAlarm.fValue);
        SetDlgItemText(IDC_EDIT_SENSOR_VALUE, szBuf);
		GetDlgItem(IDC_EDIT_SENSOR_VALUE)->UpdateData(FALSE);
    }
	//UpdateData(FALSE);
    return TRUE;
}

BOOL CDlgSensorCfg::GetDevAbility(NET_DVR_ALARMHOST_ABILITY &struAbility)
{
    BOOL bRet = FALSE;
    if (NET_DVR_GetDeviceAbility(m_lServerID, ALARMHOST_ABILITY, NULL, 0, (char*)&struAbility, sizeof(struAbility)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "ALARMHOST_ABILITY");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "ALARMHOST_ABILITY");
        bRet = TRUE;
    }
    return bRet;
}

void CDlgSensorCfg::OnBtnGetValue() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	UpdateData(TRUE);
	int iSensorIndex = m_comboSensorIndex.GetCurSel() + 1;
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ALARMHOST_SENSOR_VALUE, iSensorIndex, &m_struSensorAlarm, sizeof(m_struSensorAlarm), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Get Sensor Value failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Get Sensor Value successful");
	}
	m_fSensorValue = m_struSensorAlarm.fValue;
    m_fOriginalValue = m_struSensorAlarm.fOriginalValue;
	UpdateData(FALSE);
}
