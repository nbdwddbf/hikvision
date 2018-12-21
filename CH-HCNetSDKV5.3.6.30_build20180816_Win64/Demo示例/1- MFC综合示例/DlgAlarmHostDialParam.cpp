// DlgAlarmHostDialParam.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmHostDialParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostDialParam dialog


CDlgAlarmHostDialParam::CDlgAlarmHostDialParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmHostDialParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlarmHostDialParam)
	m_strCenterName = _T("");
	m_strCenterPhone = _T("");
	m_iDialDelay = 0;
	m_strReceiveId = _T("");
	m_iRepeatCall = 0;
	m_wFirstReport = 0;
	m_iReportPeriod = 0;
    m_bEnable = FALSE;
	//}}AFX_DATA_INIT
    memset(&m_struAlarmDialCfg, 0 , sizeof(m_struAlarmDialCfg));
}


void CDlgAlarmHostDialParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmHostDialParam)
	DDX_Control(pDX, IDC_COMBO_REPORTVALID, m_cmReportValid);
	DDX_Control(pDX, IDC_COMBO_PSTNTRANS, m_PstnTransCtrl);
	DDX_Control(pDX, IDC_COMBO_PSTNPRT, m_PstnPrtCtrl);
	DDX_Control(pDX, IDC_COMBO_ENABLEMODE, m_EnableModeCtrl);
	DDX_Control(pDX, IDC_COMBO_CENTERPARAM, m_CenterParamCtrl);
	DDX_Control(pDX, IDC_COMBO_CENTERMODE, m_CenterModeCtrl);
	DDX_Text(pDX, IDC_EDIT_CENTERNAME, m_strCenterName);
	DDX_Text(pDX, IDC_EDIT_CENTERPHONE, m_strCenterPhone);
	DDX_Text(pDX, IDC_EDIT_DIALDELAY, m_iDialDelay);
	DDX_Text(pDX, IDC_EDIT_RECEIVEID, m_strReceiveId);
	DDX_Text(pDX, IDC_EDIT_REPEATCALL, m_iRepeatCall);
	DDX_Text(pDX, IDC_EDIT_FIRSTREPORT, m_wFirstReport);
	DDX_Text(pDX, IDC_EDIT_REPORTPERIOD, m_iReportPeriod);
    DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmHostDialParam, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmHostDialParam)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_CBN_SELCHANGE(IDC_COMBO_CENTERPARAM, OnSelchangeComboCenterparam)
	ON_BN_CLICKED(IDC_BUTTON_SURE, OnButtonSure)
	ON_BN_CLICKED(IDC_BTN_SETSETUPMODE, OnBtnSetsetupmode)
	ON_BN_CLICKED(IDC_BTN_GETSETUPMODE, OnBtnGetsetupmode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostDialParam message handlers

BOOL CDlgAlarmHostDialParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	memset(m_szLan, 0, sizeof(m_szLan));
	memset(&m_struAlarmDialCfg, 0, sizeof(m_struAlarmDialCfg));
	InitComboBox();
	m_CenterParamCtrl.SetCurSel(0);
	m_struAbility.dwSize = sizeof(m_struAbility);
	if (!NET_DVR_GetDeviceAbility(m_lServerID, ALARMHOST_ABILITY, NULL, 0, (char*)&m_struAbility, sizeof(m_struAbility)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetDeviceAbility FAILED");
	}
	else
	{
		CString csStr;
		for (int i=0; i<m_struAbility.byTelNum; i++)
		{
			g_StringLanType(m_szLan, "中心", "CENTER");

			csStr.Format("%s%d", m_szLan, i+1);
			m_CenterParamCtrl.AddString(csStr);
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmHostDialParam::InitComboBox()
{
	m_EnableModeCtrl.ResetContent();
	g_StringLanType(m_szLan, "不启用", "disable");
	m_EnableModeCtrl.AddString(m_szLan);
	g_StringLanType(m_szLan, "一直启用", "enable");
	m_EnableModeCtrl.AddString(m_szLan);
	g_StringLanType(m_szLan, "断网后启用", "enable when network disconnecting");
	m_EnableModeCtrl.AddString(m_szLan);

	m_CenterModeCtrl.ResetContent();
	g_StringLanType(m_szLan, "单中心", "one center");
	m_CenterModeCtrl.AddString(m_szLan);
	g_StringLanType(m_szLan, "双中心", "two centers");
	m_CenterModeCtrl.AddString(m_szLan);
	g_StringLanType(m_szLan, "一报一备", "a main center and a secondary center");
	m_CenterModeCtrl.AddString(m_szLan);

	m_cmReportValid.ResetContent();
	g_StringLanType(m_szLan, "不启用", "disable");
	m_cmReportValid.AddString(m_szLan);
	g_StringLanType(m_szLan, "启用", "enable");
	m_cmReportValid.AddString(m_szLan);
}

void CDlgAlarmHostDialParam::OnButtonGet() 
{
	// TODO: Add your control notification handler code here
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ALARMDIALMODECFG, -1, &m_struAlarmDialCfg, sizeof(m_struAlarmDialCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMDIALMODECFG");
		m_CenterParamCtrl.SetCurSel(0);
		UpdateData(FALSE);
        OnSelchangeComboCenterparam();
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMDIALMODECFG");
        return;
    }
}

void CDlgAlarmHostDialParam::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	OnButtonSure();
    m_struAlarmDialCfg.dwSize = sizeof(m_struAlarmDialCfg);
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_ALARMDIALMODECFG, -1, &m_struAlarmDialCfg, sizeof(m_struAlarmDialCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARMDIALMODECFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ALARMDIALMODECFG");
        return;
    }
}

void CDlgAlarmHostDialParam::OnSelchangeComboCenterparam() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int sel = m_CenterParamCtrl.GetCurSel();
	char strTemp[33] = {0};
    NET_DVR_PHONECENTERDIALCFG struCenterDialCfg = {0};
    
	m_cmReportValid.SetCurSel(m_struAlarmDialCfg.byReportValid);
	m_iReportPeriod = m_struAlarmDialCfg.wReportPeriod;
	m_wFirstReport = m_struAlarmDialCfg.wFirstReportTime;
    memcpy(&struCenterDialCfg, &m_struAlarmDialCfg.struPhoneCenterParam[sel], sizeof(struCenterDialCfg));

	memset(strTemp, 0, sizeof(strTemp));
	memcpy(strTemp, struCenterDialCfg.sCenterName, NAME_LEN);
    m_strCenterName.Format("%s", strTemp);

	memset(strTemp, 0, sizeof(strTemp));
	memcpy(strTemp, struCenterDialCfg.byPhoneNum, MAX_PHONE_NUM);
    m_strCenterPhone.Format("%s", strTemp);

    m_iRepeatCall = struCenterDialCfg.byRepeatCall;
    m_PstnPrtCtrl.SetCurSel(struCenterDialCfg.byPstnProtocol);
    m_iDialDelay = struCenterDialCfg.byDialDelay;
    m_PstnTransCtrl.SetCurSel(struCenterDialCfg.byPstnTransMode);
    m_strReceiveId = struCenterDialCfg.byReceiverId;
    m_bEnable = struCenterDialCfg.byEnable;

    UpdateData(FALSE);
}

void CDlgAlarmHostDialParam::OnButtonSure() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int sel = m_CenterParamCtrl.GetCurSel();
	char sLan[128] = {0};
	g_StringLanType(sLan, "请选择正确的中心类型", "Please check Center Index");
	if (sel<0 || sel>=m_struAbility.byTelNum)
	{
		MessageBox(sLan);
		return ;
	}
    NET_DVR_PHONECENTERDIALCFG struCenterDialCfg = {0};
   
    sprintf((char*)struCenterDialCfg.sCenterName, "%s", m_strCenterName);
    sprintf((char*)struCenterDialCfg.byPhoneNum, "%s", m_strCenterPhone);
    sprintf((char*)struCenterDialCfg.byReceiverId, "%s", m_strReceiveId);
    //memcpy(struCenterDialCfg.sCenterName, m_strCenterName, sizeof(struCenterDialCfg.sCenterName));
    //memcpy(struCenterDialCfg.byPhoneNum, m_strCenterPhone, sizeof(struCenterDialCfg.byPhoneNum));
    //memcpy(struCenterDialCfg.byReceiverId, m_strReceiveId, sizeof(struCenterDialCfg.byReceiverId));
    struCenterDialCfg.byRepeatCall = m_iRepeatCall;
    struCenterDialCfg.byPstnProtocol = m_PstnPrtCtrl.GetCurSel();
    struCenterDialCfg.byDialDelay = m_iDialDelay;
    struCenterDialCfg.byPstnTransMode = m_PstnTransCtrl.GetCurSel();
    struCenterDialCfg.byEnable = m_bEnable;
    
	m_struAlarmDialCfg.byReportValid = m_cmReportValid.GetCurSel();
	m_struAlarmDialCfg.wReportPeriod = m_iReportPeriod;
	m_struAlarmDialCfg.wFirstReportTime = m_wFirstReport;
    memset(&m_struAlarmDialCfg.struPhoneCenterParam[sel], 0 ,sizeof(struCenterDialCfg));
    memcpy(&m_struAlarmDialCfg.struPhoneCenterParam[sel], &struCenterDialCfg, sizeof(struCenterDialCfg));
}

void CDlgAlarmHostDialParam::OnBtnSetsetupmode() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	m_struSetupMode.dwSize = sizeof(m_struSetupMode);
	m_struSetupMode.byCallType = m_CenterModeCtrl.GetCurSel()+1;
	m_struSetupMode.byEnableMode = m_EnableModeCtrl.GetCurSel();
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_ALARMHOSTDIALSETUPMODE, -1, &m_struSetupMode, sizeof(m_struSetupMode)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARMHOSTDIALSETUPMODE");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ALARMHOSTDIALSETUPMODE");
        return;
    }
}

void CDlgAlarmHostDialParam::OnBtnGetsetupmode() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	memset(&m_struSetupMode, 0, sizeof(m_struSetupMode));
	m_struSetupMode.dwSize = sizeof(m_struSetupMode);
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ALARMHOSTDIALSETUPMODE, -1, &m_struSetupMode, sizeof(m_struSetupMode), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMHOSTDIALSETUPMODE");
        m_EnableModeCtrl.SetCurSel(m_struSetupMode.byEnableMode);
        m_CenterModeCtrl.SetCurSel(m_struSetupMode.byCallType - 1);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMHOSTDIALSETUPMODE");
        return;
    }
}
