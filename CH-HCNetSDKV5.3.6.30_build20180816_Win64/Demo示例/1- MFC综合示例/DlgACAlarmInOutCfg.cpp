// DlgACAlarmInOutCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgACAlarmInOutCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgACAlarmInOutCfg dialog


CDlgACAlarmInOutCfg::CDlgACAlarmInOutCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgACAlarmInOutCfg::IDD, pParent)
    , m_dwAlarmInNum(0)
    , m_dwAlarmOutNum(0)
{
	//{{AFX_DATA_INIT(CDlgACAlarmInOutCfg)
	m_csAlarmInName = _T("");
	m_dwOutDelay = 0;
	m_csOutName = _T("");
	//}}AFX_DATA_INIT
    memset(&m_struAlarmHostAbility, 0, sizeof(m_struAlarmHostAbility));
    memset(&m_struAlarmIn, 0, sizeof(m_struAlarmIn));
}


void CDlgACAlarmInOutCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgACAlarmInOutCfg)
	DDX_Control(pDX, IDC_LIST_ALARM_IN, m_listAlarmIn);
	DDX_Control(pDX, IDC_COMBO_SENSITIVITYPARAM, m_cmbSensiParam);
	DDX_Control(pDX, IDC_LIST_SIREN_OUT, m_lstSirenOut);
	DDX_Control(pDX, IDC_LIST_ALARM_OUT, m_lstAlarmOut);
	DDX_Control(pDX, IDC_COMBO_DETECTOR, m_cmbDetector);
	DDX_Control(pDX, IDC_COMBO_DEFENSE_TYPE, m_cmbDefenseType);
	DDX_Control(pDX, IDC_COMBO_ALARM_OUT, m_cmbAlarmOut);
	DDX_Control(pDX, IDC_COMBO_ALARM_IN, m_cmbAlarmIn);
	DDX_Text(pDX, IDC_EDIT_ALARMIN_NAME, m_csAlarmInName);
	DDV_MaxChars(pDX, m_csAlarmInName, 32);
	DDX_Text(pDX, IDC_EDIT_ALARMOUT_DELAY, m_dwOutDelay);
	DDX_Text(pDX, IDC_EDIT_ALARMOUT_NAME, m_csOutName);
	DDV_MaxChars(pDX, m_csOutName, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgACAlarmInOutCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgACAlarmInOutCfg)
	ON_BN_CLICKED(IDC_BUT_AC_ALARMIN_GET, OnButAlarmInGet)
	ON_BN_CLICKED(IDC_BUT_AC_ALARMIN_SET, OnButAlarmInSet)
	ON_BN_CLICKED(IDC_BUT_AC_ALARMOUT_GET, OnButAlarmOutGet)
	ON_BN_CLICKED(IDC_BUT_AC_ALARMOUT_SET, OnButAlarmOutSet)
	ON_BN_CLICKED(IDC_BUT_AC_ALARMOUT_CLOSE, OnButAcAlarmoutClose)
	ON_BN_CLICKED(IDC_BUT_AC_ALARMOUT_OPEN, OnButAcAlarmoutOpen)
	ON_BN_CLICKED(IDC_BUT_AC_ALARMOUT_ALLCLOSE, OnButAcAlarmoutAllclose)
	ON_BN_CLICKED(IDC_BUT_AC_ALARMOUT_ALLOPEN, OnButAcAlarmoutAllopen)
	ON_BN_CLICKED(IDC_BUT_AC_ALARMIN_SETUPALRM, OnButAlarmInSetupAlrm)
	ON_BN_CLICKED(IDC_BUT_AC_ALARMIN_CLOSEALRM, OnButAlarmInCloseAlrm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgACAlarmInOutCfg message handlers
BOOL CDlgACAlarmInOutCfg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    m_lDeviceID = g_pMainDlg->GetCurDeviceIndex(); 
    m_lUserID = g_struDeviceInfo[m_lDeviceID].lLoginID; 
    if (GetAlarmHostAbility(m_struAlarmHostAbility))
    {
        m_dwAlarmInNum = m_struAlarmHostAbility.wTotalAlarmInNum;
        m_dwAlarmOutNum = m_struAlarmHostAbility.wTotalAlarmOutNum;
    }
    else
    {
        m_dwAlarmInNum = g_struDeviceInfo[m_lDeviceID].iAlarmInNum;
        m_dwAlarmOutNum = g_struDeviceInfo[m_lDeviceID].iAlarmOutNum;
    }

    int i = 0, iIndex; 
    CString csTemp; 
    for (i=0; i<m_dwAlarmInNum; i++)
    {
        csTemp.Format("%d", i+1); 
        iIndex = m_cmbAlarmIn.AddString(csTemp); 
        m_cmbAlarmIn.SetItemData(iIndex, i); 
    }
    for (i=0; i<m_dwAlarmOutNum; i++)
    {
        csTemp.Format("%d", i+1);
        iIndex = m_cmbAlarmOut.AddString(csTemp); 
        m_cmbAlarmOut.SetItemData(iIndex, i); 
    }
    m_cmbAlarmIn.SetCurSel(0); 
    m_cmbAlarmOut.SetCurSel(0); 

    InitDetectorCombox(); 
    InitArmTypeCombox(); 
    InitList();
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgACAlarmInOutCfg::InitDetectorCombox()
{
    char szLan[128] = {0};
    m_cmbDetector.ResetContent();
    int nIndex = 0;

    g_StringLanType(szLan, "紧急开关", "Panic Button");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, PANIC_BUTTON);
    nIndex++;

    g_StringLanType(szLan, "门磁开关", "Magnetic Contact");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, MAGNETIC_CONTACT);
    nIndex++;

    g_StringLanType(szLan, "烟感探测器", "Smoke Detector");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, SMOKE_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "主动红外探测器", "Active Infrared Detector");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, ACTIVE_INFRARED_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "被动红外探测器", "Passive Infrared Detector");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, PASSIVE_INFRARED_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "玻璃破碎探测器", "Glass Break Detector");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, GLASS_BREAK_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "震动探测器", "Vibration detector");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, VIBRATION_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "双鉴移动探测器", "Dual Technology PIR detector");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, DUAL_TECHNOLOGY_PIR_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "三技术探测器", "Triple Technology PIR detector");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, TRIPLE_TECHNOLOGY_PIR_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "湿度探测器", "Humidity Dectector");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, HUMIDITY_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "温感探测器", "Temperature Dectector");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, TEMPERATURE_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "可燃气体探测器", "Combustible Gas Detector");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, COMBUSTIBLE_GAS_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "随动开关", "dynamic switch");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, DYNAMIC_SWITCH);
    nIndex++;

    g_StringLanType(szLan, "控制开关", "control switch");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, CONTROL_SWITCH);
    nIndex++;

    g_StringLanType(szLan, "智能锁", "smart lock");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, SMART_LOCK);
    nIndex++;

    g_StringLanType(szLan, "水感探测器", "water detector");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, WATER_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "位移探测器", "displacement detector");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, DISPLACEMENT_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "单体门磁探测器", "single infrared detector");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, SINGLE_INFRARED_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "无线单防区模块", "wireless single zone module");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, SINGLE_ZONE_MODULE);
    nIndex++;

    g_StringLanType(szLan, "幕帘红外人体探测器", "curtain infrared detector");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, CURTAIN_INFRARED_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "门铃开关", "bell switch");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, DOORBELL_SWITCH);
    nIndex++;

    g_StringLanType(szLan, "医疗求助按钮", "medical help");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, MEDICAL_HELP_BUTTON);
    nIndex++;

    g_StringLanType(szLan, "室外双鉴传感器", "outdoor dual detector");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, OUTDOOR_DUAL_TECH);
    nIndex++;

    g_StringLanType(szLan, "其他探测器", "Other Detector");
    m_cmbDetector.InsertString(nIndex, szLan);
    m_cmbDetector.SetItemData(nIndex, OTHER_DETECTOR);
    nIndex++;
}

void CDlgACAlarmInOutCfg::InitArmTypeCombox()
{
    char szLan[128] = {0};
    m_cmbDefenseType.ResetContent();
    int iIndex ; 
    g_StringLanType(szLan, "即时防区", "Instant zone");
    iIndex = m_cmbDefenseType.AddString(szLan);
    m_cmbDefenseType.SetItemData(iIndex, iIndex);
    g_StringLanType(szLan, "24小时有声防区", "24-hour zone");
    iIndex = m_cmbDefenseType.AddString(szLan);
    m_cmbDefenseType.SetItemData(iIndex, iIndex);

    g_StringLanType(szLan, "延时防区", "Delay zone");
    iIndex = m_cmbDefenseType.AddString(szLan);
    m_cmbDefenseType.SetItemData(iIndex, iIndex);

    g_StringLanType(szLan, "内部防区", "Inter zone");
    iIndex = m_cmbDefenseType.AddString(szLan);
    m_cmbDefenseType.SetItemData(iIndex, iIndex);

    g_StringLanType(szLan, "钥匙布撤防防区", "Key zone");
    iIndex = m_cmbDefenseType.AddString(szLan);
    m_cmbDefenseType.SetItemData(iIndex, iIndex);

    g_StringLanType(szLan, "火警防区", "Fire zone");
    iIndex = m_cmbDefenseType.AddString(szLan);
    m_cmbDefenseType.SetItemData(iIndex, iIndex);

    g_StringLanType(szLan, "周界防区", "perimeter zone");
    iIndex = m_cmbDefenseType.AddString(szLan);
    m_cmbDefenseType.SetItemData(iIndex, iIndex);

    g_StringLanType(szLan, "24小时无声防区", "24-hour silent zone");
    iIndex = m_cmbDefenseType.AddString(szLan);
    m_cmbDefenseType.SetItemData(iIndex, iIndex);

    g_StringLanType(szLan, "24小时辅助防区", "24-hour assist zone");
    iIndex = m_cmbDefenseType.AddString(szLan);
    m_cmbDefenseType.SetItemData(iIndex, iIndex);

    g_StringLanType(szLan, "24小时震动防区", "24-hour shake zone");
    iIndex = m_cmbDefenseType.AddString(szLan);
    m_cmbDefenseType.SetItemData(iIndex, iIndex);

    g_StringLanType(szLan, "门禁紧急开门防区", "Entrance guard Urgent to open the door");
    iIndex = m_cmbDefenseType.AddString(szLan);
    m_cmbDefenseType.SetItemData(iIndex, iIndex);

    g_StringLanType(szLan, "门禁紧急关门防区", "Entrance guard Urgent to close the door");
    iIndex = m_cmbDefenseType.AddString(szLan);
    m_cmbDefenseType.SetItemData(iIndex, iIndex);

    g_StringLanType(szLan, "超时防区", "time-out zone");
    iIndex = m_cmbDefenseType.AddString(szLan);
    m_cmbDefenseType.SetItemData(iIndex, iIndex);

    g_StringLanType(szLan, "紧急防区", "emergency zone");
    iIndex = m_cmbDefenseType.AddString(szLan);
    m_cmbDefenseType.SetItemData(iIndex, iIndex);

    g_StringLanType(szLan, "屏蔽防区", "shield zone");
    iIndex = m_cmbDefenseType.AddString(szLan);
    m_cmbDefenseType.SetItemData(iIndex, 0xff);
}

void CDlgACAlarmInOutCfg::InitList()
{
    char szLan[128] = {0};
    int i = 0;
    m_lstAlarmOut.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < m_dwAlarmOutNum; i++)
    {
        sprintf(szLan, "Alarm Out %d", (i+1));
        m_lstAlarmOut.InsertItem(i, szLan);
    }    

    m_lstSirenOut.SetExtendedStyle(LVS_EX_CHECKBOXES);
    const int iSirenNum = 8; 
    for (i = 0; i < iSirenNum; i++)
    {
        sprintf(szLan, "Siren %d", (i+1));
        m_lstSirenOut.InsertItem(i, szLan);
    }

    m_listAlarmIn.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < m_dwAlarmInNum ; i++)
    {
        sprintf(szLan, "Alarm In %d", (i+1));
        m_listAlarmIn.InsertItem(i, szLan);
    }
}
void CDlgACAlarmInOutCfg::SetList(const NET_DVR_ALARMIN_PARAM &struAlarmInParam)
{
    //UpdateData(TRUE); 
    int i = 0;
    for (i = 0; i < m_lstAlarmOut.GetItemCount(); i++ )
    {
        if (1==  struAlarmInParam.byAssociateAlarmOut[i])
        {
            m_lstAlarmOut.SetCheck(i, TRUE);
        }
        else
        {
            m_lstAlarmOut.SetCheck(i, FALSE);
        }
    }
    
    for (i = 0; i < m_lstSirenOut.GetItemCount(); i++)
    {
        if (1 == struAlarmInParam.byAssociateSirenOut[i])
        {
            m_lstSirenOut.SetCheck(i, TRUE);
        }
        else
        {
            m_lstSirenOut.SetCheck(i, FALSE);
        }
    }
    UpdateData(FALSE); 
}
void CDlgACAlarmInOutCfg::GetList(NET_DVR_ALARMIN_PARAM &struAlarmInParam)
{
    UpdateData(TRUE); 
    int i = 0;
    for (i = 0; i < m_lstAlarmOut.GetItemCount(); i++)
    {
        if (TRUE == m_lstAlarmOut.GetCheck(i))
        {
            struAlarmInParam.byAssociateAlarmOut[i] = 1;
        }
        else
        {
            struAlarmInParam.byAssociateAlarmOut[i] = 0;
        }
    }
    
    for (i = 0; i < m_lstSirenOut.GetItemCount(); i++)
    {
        if (TRUE == m_lstSirenOut.GetCheck(i))
        {
            struAlarmInParam.byAssociateSirenOut[i] = 1;
        }
        else
        {
            struAlarmInParam.byAssociateSirenOut[i] = 0;
        }
    }
    UpdateData(FALSE);
}
void CDlgACAlarmInOutCfg::OnButAlarmInGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    NET_DVR_ALARMIN_PARAM struInParam = {0}; 
    LONG lAlarmIn = m_cmbAlarmIn.GetItemData(m_cmbAlarmIn.GetCurSel());
    DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ALARMIN_PARAM, lAlarmIn, &struInParam, sizeof(struInParam), &dwReturn))
    {
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_GET_ALARMIN_PARAM");
        return ; 
    }

    g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_GET_ALARMIN_PARAM");
    char szName[sizeof(struInParam.byName)+1] = {0}; 
    memcpy(szName, struInParam.byName, sizeof(struInParam.byName)); 
    m_csAlarmInName.Format("%s", szName);
    if (struInParam.wDetectorType == 0xffff)
    {
        m_cmbDetector.SetCurSel(24);
    } 
    else
    {
        m_cmbDetector.SetCurSel(struInParam.wDetectorType);
    }

    if (struInParam.byType == 0xff)
    {
        m_cmbDefenseType.SetCurSel(14);
    } 
    else
    {
        m_cmbDefenseType.SetCurSel( struInParam.byType );
    }
    
    m_cmbSensiParam.SetCurSel( struInParam.bySensitivityParam ); 

    SetList(struInParam); 
    UpdateData(FALSE);
}

void CDlgACAlarmInOutCfg::OnButAlarmInSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    LONG lAlarmIn = m_cmbAlarmIn.GetItemData(m_cmbAlarmIn.GetCurSel());
    NET_DVR_ALARMIN_PARAM struInParam = {0}; 
    struInParam.dwSize = sizeof(struInParam);
    strncpy((char *)struInParam.byName, (LPCSTR)m_csAlarmInName, sizeof(struInParam.byName)); 
    struInParam.byName[m_csAlarmInName.GetLength()] = 0; 
    struInParam.wDetectorType = m_cmbDetector.GetItemData(m_cmbDetector.GetCurSel()); 
    struInParam.byType = m_cmbDefenseType.GetItemData(m_cmbDefenseType.GetCurSel());
    struInParam.bySensitivityParam = m_cmbSensiParam.GetCurSel(); 
    GetList(struInParam); 
    if (! NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_ALARMIN_PARAM, lAlarmIn, &struInParam, sizeof(struInParam)))
    {
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_SET_ALARMIN_PARAM");
        return ; 
    }
  
    g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_SET_ALARMIN_PARAM");   
}

void CDlgACAlarmInOutCfg::OnButAlarmOutGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    NET_DVR_ALARMOUT_PARAM struOutParam = {0}; 
    LONG lAlarmOut = m_cmbAlarmOut.GetItemData(m_cmbAlarmOut.GetCurSel());
    DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ALARMOUT_PARAM, lAlarmOut , &struOutParam, sizeof(struOutParam), &dwReturn))
    {
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_GET_ALARMOUT_PARAM");
        return ; 
    }
    g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_GET_ALARMOUT_PARAM");
    char szName[sizeof(struOutParam.byName)+1] = {0}; 
    memcpy(szName, struOutParam.byName, sizeof(struOutParam.byName)); 
    m_csOutName.Format("%s", szName); 
    m_dwOutDelay = struOutParam.wDelay; 
    UpdateData(FALSE); 
}

void CDlgACAlarmInOutCfg::OnButAlarmOutSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    LONG lAlarmOut = m_cmbAlarmOut.GetItemData(m_cmbAlarmOut.GetCurSel());
    NET_DVR_ALARMOUT_PARAM struOutParam = {0}; 
    struOutParam.dwSize = sizeof(struOutParam); 
    struOutParam.wDelay = m_dwOutDelay; 
//    strcpy((char *)struOutParam.byName, (LPCSTR)m_csOutName);
    strncpy((char *)struOutParam.byName, (LPCSTR)m_csOutName, sizeof(struOutParam.byName)); 
    struOutParam.byName[m_csOutName.GetLength()] = 0; 
    if (! NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_ALARMOUT_PARAM, lAlarmOut, &struOutParam, sizeof(struOutParam)))
    {
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_SET_ALARMOUT_PARAM");  
        return ; 
    }
    g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_SET_ALARMOUT_PARAM"); 
    UpdateData(FALSE); 
}

BOOL CDlgACAlarmInOutCfg::SetAlarmOut(LONG lAlarmOutPort, LONG lAlarmOutStatic)
{
    BOOL bRet = FALSE;  
    if (NET_DVR_SetAlarmHostOut(m_lUserID, lAlarmOutPort, lAlarmOutStatic))
    {
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_SetAlarmHostOut");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_SetAlarmHostOut");
        bRet = FALSE;
    }
    return bRet;
}

BOOL CDlgACAlarmInOutCfg::GetAlarmHostAbility(NET_DVR_ALARMHOST_ABILITY& struAlarmHostAbility)
{
    BOOL bRet = FALSE;
    DWORD dwReturn = 0;
    if (NET_DVR_GetDeviceAbility(m_lUserID, ALARMHOST_ABILITY, NULL, 0, (char*)&struAlarmHostAbility, sizeof(struAlarmHostAbility)))
    {
        char szLan[128] = { 0 };
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "ALARMHOST_ABILITY");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "ALARMHOST_ABILITY");
        bRet = FALSE;
    }
    return bRet;
}

void CDlgACAlarmInOutCfg::OnButAcAlarmoutClose() 
{
	// TODO: Add your control notification handler code here
	SetAlarmOut(m_cmbAlarmOut.GetItemData(m_cmbAlarmOut.GetCurSel() ),  0);
}

void CDlgACAlarmInOutCfg::OnButAcAlarmoutOpen() 
{
	// TODO: Add your control notification handler code here
	SetAlarmOut(m_cmbAlarmOut.GetItemData(m_cmbAlarmOut.GetCurSel() ),  1);
}

void CDlgACAlarmInOutCfg::OnButAcAlarmoutAllclose() 
{
	// TODO: Add your control notification handler code here
	SetAlarmOut( 0xffffffff,  0);
}

void CDlgACAlarmInOutCfg::OnButAcAlarmoutAllopen() 
{
	// TODO: Add your control notification handler code here
	SetAlarmOut( 0xffffffff,  1);
}

void CDlgACAlarmInOutCfg::OnButAlarmInSetupAlrm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    int i = 0; 
    for (i = 0; i < m_listAlarmIn.GetItemCount(); i++)
    {
        if (TRUE == m_listAlarmIn.GetCheck(i))
        {
            m_struAlarmIn.byAssiciateAlarmIn[i] = 1;
        }
        else
        {
            m_struAlarmIn.byAssiciateAlarmIn[i] = 0;
        }   
    }
    if (!NET_DVR_AlarmHostSetupAlarmChan(m_lUserID, &m_struAlarmIn))
    {
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_AlarmHostSetupAlarmChan");
    }
    else
    {
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_AlarmHostSetupAlarmChan");
    }
}

void CDlgACAlarmInOutCfg::OnButAlarmInCloseAlrm() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    int i = 0; 
    for (i = 0; i < m_listAlarmIn.GetItemCount(); i++)
    {
        if (TRUE == m_listAlarmIn.GetCheck(i))
        {
            m_struAlarmIn.byAssiciateAlarmIn[i] = 1;
        }
        else
        {
            m_struAlarmIn.byAssiciateAlarmIn[i] = 0;
        }   
    }    
    if (!NET_DVR_AlarmHostCloseAlarmChan(m_lUserID, &m_struAlarmIn))
    {
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_AlarmHostSetupAlarmChan");
    }
    else
    {
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_AlarmHostSetupAlarmChan");
    }
}
