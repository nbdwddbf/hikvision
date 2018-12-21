// DlgProductionTest.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgProductionTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProductionTest dialog


CDlgProductionTest::CDlgProductionTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProductionTest::IDD, pParent)
    , m_bEccectricCorrection(FALSE)
    , m_bTrickScan(FALSE)
    , m_bElectronicCompassCorrect(FALSE)
    , m_bAgingTrickScan(FALSE)
    , m_fdtem(0)
    , m_temp1(0)
    , m_temp2(0)
    , m_temp3(0)
    , m_temp4(0)
    , m_temp5(0)
    , m_temp6(0)
    , m_temp7(0)
    , m_temp8(0)
    , m_temp9(0)
{
	//{{AFX_DATA_INIT(CDlgProductionTest)
	m_bAgeingCmd = FALSE;
	m_bDevFan1 = FALSE;
	m_bDevFan2 = FALSE;
	m_bDevHeater1 = FALSE;
	m_bDevHeater2 = FALSE;
	m_bRedlightTest = FALSE;
	m_fHuml = 0.0f;
	m_fTemp = 0.0f;
	m_dwChan = 0;
	m_csDialSwitch = _T("");
	m_dwChanSecurityMode = 0;
	m_csRandCode = _T("");
	m_iICRTime = 0;
	m_bICR = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgProductionTest::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgProductionTest)
    DDX_Control(pDX, IDC_COMBO_SECURITYMODE, m_comSecurityMode);
    DDX_Control(pDX, IDC_COMBO_SOUND_MODE, m_comSoundMode);
    DDX_Control(pDX, IDC_COM_SELFCHECK, m_comSelfCheck);
    DDX_Check(pDX, IDC_CHK_AGEING_COMMAND, m_bAgeingCmd);
    DDX_Check(pDX, IDC_CHK_DEVFAN1, m_bDevFan1);
    DDX_Check(pDX, IDC_CHK_DEVFAN2, m_bDevFan2);
    DDX_Check(pDX, IDC_CHK_DEVHEATER1, m_bDevHeater1);
    DDX_Check(pDX, IDC_CHK_DEVHEATER2, m_bDevHeater2);
    DDX_Check(pDX, IDC_CHK_REDLIGHT_TESTMODE_COMMAND, m_bRedlightTest);
    DDX_Text(pDX, IDC_EDIT_HUMI, m_fHuml);
    DDX_Text(pDX, IDC_EDIT_TEMP, m_fTemp);
    DDX_Text(pDX, IDC_EDIT_CHANNEL, m_dwChan);
    DDX_Text(pDX, IDC_EDIT_DIAL_SWITCH, m_csDialSwitch);
    DDX_Text(pDX, IDC_EDIT_CHANNEL_SECURITYMODE, m_dwChanSecurityMode);
    DDX_Text(pDX, IDC_EDIT_RAND_CODE, m_csRandCode);
    DDX_Text(pDX, IDC_EDIT_ICR_TIME, m_iICRTime);
    DDX_Check(pDX, IDC_CHK_REDLIGHT_TESTMODE_COMMAND_ICR, m_bICR);
    DDX_Check(pDX, IDC_CHECK_ECCENTRC_CORRECTION, m_bEccectricCorrection);
    DDX_Check(pDX, IDC_CHECK_TRICK_SCAN, m_bTrickScan);
    DDX_Check(pDX, IDC_CHECK_ELECTRONIC_COMPASS_CORRECT, m_bElectronicCompassCorrect);
    DDX_Control(pDX, IDC_COMBO_ELECTRONIC_COMPASS_STATE, m_comElectronicCompassState);
    DDX_Control(pDX, IDC_COMBO_AGING_PARAM, m_comAging);
    DDX_Control(pDX, IDC_COMBO_WRITEREAD_ENABLE, m_comWriteReadEnalbe);
    DDX_Control(pDX, IDC_COMBO_ECCENTRIC_CORRECT_STATE, m_comEccentricCorrectState);
    DDX_Check(pDX, IDC_CHECK_CLEAR_TRICK_SCAN, m_bAgingTrickScan);
    DDX_Text(pDX, IDC_EDIT_FDTEM, m_fdtem);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_TEMP1, m_temp1);
    DDX_Text(pDX, IDC_EDIT_TEMP2, m_temp2);
    DDX_Text(pDX, IDC_EDIT_TEMP3, m_temp3);
    DDX_Text(pDX, IDC_EDIT_TEMP4, m_temp4);
    DDX_Text(pDX, IDC_EDIT_TEMP5, m_temp5);
    DDX_Text(pDX, IDC_EDIT_TEMP6, m_temp6);
    DDX_Text(pDX, IDC_EDIT_TEMP7, m_temp7);
    DDX_Text(pDX, IDC_EDIT_TEMP8, m_temp8);
    DDX_Text(pDX, IDC_EDIT_TEMP9, m_temp9);
}


BEGIN_MESSAGE_MAP(CDlgProductionTest, CDialog)
	//{{AFX_MSG_MAP(CDlgProductionTest)
	ON_BN_CLICKED(IDC_BUT_SELFCHECK_REFRESH, OnButSelfcheckRefresh)
	ON_BN_CLICKED(IDC_BUT_START_COMMAND, OnButStartCommand)
	ON_BN_CLICKED(IDC_BUT_START_DEVTEST, OnButStartDevtest)
	ON_BN_CLICKED(IDC_BUT_RESUME_INITRACKPOS, OnButResumeInitrackpos)
	ON_BN_CLICKED(IDC_BTN_GET_TEMP_HUMI, OnBtnGetTempHumi)
	ON_BN_CLICKED(IDC_BTN_SET_AUTOFOCUS, OnBtnSetAutofocus)
	ON_BN_CLICKED(IDC_BTN_GET_SOUNDMODE, OnBtnGetSoundmode)
	ON_BN_CLICKED(IDC_BTN_SET_SOUNDMODE, OnBtnSetSoundmode)
	ON_BN_CLICKED(IDC_BTN_GET_DIAL_SWITCH, OnBtnGetDialSwitch)
	ON_BN_CLICKED(IDC_BTN_GET_SECURITYMODE, OnBtnGetSecuritymode)
    ON_BN_CLICKED(IDC_BTN_GET, &CDlgProductionTest::OnBnClickedBtnGet)
    ON_BN_CLICKED(IDC_BTN_SET_AGING_TRICK_SCAN, &CDlgProductionTest::OnBnClickedBtnSetAgingTrickScan)
    ON_BN_CLICKED(IDC_BTN_GET_ECCENTRIC_CORRECT_STATE, &CDlgProductionTest::OnBnClickedBtnGetEccentricCorrectState)
    ON_BN_CLICKED(IDC_BUT_CLEAR_IPC_PARAM, &CDlgProductionTest::OnBnClickedButClearIpcParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProductionTest message handlers

void CDlgProductionTest::OnButSelfcheckRefresh() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_TEST_SELFCHECK_RESULT  struSelfcheckResult; 
    CString csError; 
    if (!NET_DVR_GetDeviceStatus(m_lUserID, NET_DVR_GET_SELFCHECK_RESULT, 1, NULL, 0, NULL, &struSelfcheckResult, sizeof(NET_DVR_TEST_SELFCHECK_RESULT)))
    {
        csError.Format(_T("获取错误 Error Code %d"),NET_DVR_GetLastError()); 
        AfxMessageBox(csError);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetDeviceStatus NET_DVR_GET_SELFCHECK_RESULT");
        m_comSelfCheck.SetCurSel(0);
        UpdateData(FALSE); 
        return ; 
    }
    switch (struSelfcheckResult.bySelfCheckStatus)
    {
    case 0:
    case 1:       
    case 2:         
    case 3:
        m_comSelfCheck.SetCurSel(struSelfcheckResult.bySelfCheckStatus+1); 
        break; 
    default:
        AfxMessageBox(_T("返回未知状态"));
        m_comSelfCheck.SetCurSel(0);
    }
    UpdateData(FALSE); 
}

void CDlgProductionTest::OnButStartCommand() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    NET_DVR_TEST_COMMAND struTestCmd; 
    memset(&struTestCmd, 0, sizeof(struTestCmd)); 
    struTestCmd.dwSize = sizeof(NET_DVR_TEST_COMMAND); 
    struTestCmd.dwChannel = m_dwChannel; 
    struTestCmd.byTestCommand[0] = m_bAgeingCmd; 
    struTestCmd.byTestCommand[1] = m_bRedlightTest; 
    struTestCmd.byTestCommand[2] = m_bICR; 
    struTestCmd.byTestCommand[3] = m_bEccectricCorrection;
    struTestCmd.byTestCommand[4] = m_bTrickScan;
    struTestCmd.byTestCommand[5] = m_bElectronicCompassCorrect;
    struTestCmd.wICRIntervalTime = m_iICRTime;
    struTestCmd.byElectronicCompassState = m_comElectronicCompassState.GetCurSel();
    struTestCmd.fDeviceTem = m_fdtem;
    struTestCmd.byTemp[0] = m_temp1;
    struTestCmd.byTemp[1] = m_temp2;
    struTestCmd.byTemp[2] = m_temp3;
    struTestCmd.byTemp[3] = m_temp4;
    struTestCmd.byTemp[4] = m_temp5;
    struTestCmd.byTemp[5] = m_temp6;
    struTestCmd.byTemp[6] = m_temp7;
    struTestCmd.byTemp[7] = m_temp8;
    struTestCmd.byTemp[8] = m_temp9;
    if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SET_TEST_COMMAND, &struTestCmd, sizeof(NET_DVR_TEST_COMMAND)))
    {
        CString csError; 
        csError.Format(_T("发送开启命令失败 Error Code %d"),NET_DVR_GetLastError()); 
        AfxMessageBox(csError);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_TEST_COMMAND");
    }
//    m_bAgeingCmd = FALSE; 
//    m_bRedlightTest = FALSE; 
    UpdateData(FALSE); 	
}
void CDlgProductionTest::OnBnClickedBtnGet()
{
    // TODO:  在此添加控件通知处理程序代码
    DWORD dwReturn = 0;
    NET_DVR_TEST_COMMAND struTestCmd = { 0 };
    struTestCmd.dwSize = sizeof(struTestCmd);

    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_TEST_COMMAND, m_dwChannel, &struTestCmd, sizeof(struTestCmd), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TEST_COMMAND Failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_TEST_COMMAND SUCC");

        m_dwChannel = struTestCmd.dwChannel;
        m_bAgeingCmd = struTestCmd.byTestCommand[0];
        m_bRedlightTest = struTestCmd.byTestCommand[1];
        m_bICR = struTestCmd.byTestCommand[2];
        m_bEccectricCorrection = struTestCmd.byTestCommand[3];
        m_bTrickScan = struTestCmd.byTestCommand[4];
        m_bElectronicCompassCorrect = struTestCmd.byTestCommand[5];
        m_iICRTime = struTestCmd.wICRIntervalTime;
        m_comElectronicCompassState.SetCurSel(struTestCmd.byElectronicCompassState);
        m_fdtem = struTestCmd.fDeviceTem;

        m_temp1 = struTestCmd.byTemp[0];
        m_temp2 = struTestCmd.byTemp[1];
        m_temp3 = struTestCmd.byTemp[2];
        m_temp4 = struTestCmd.byTemp[3];
        m_temp5 = struTestCmd.byTemp[4];
        m_temp6 = struTestCmd.byTemp[5];
        m_temp7 = struTestCmd.byTemp[6];
        m_temp8 = struTestCmd.byTemp[7];
        m_temp9 = struTestCmd.byTemp[8];
        UpdateData(FALSE);
    }
}
void CDlgProductionTest::OnButStartDevtest() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    NET_DVR_TEST_DEVMODULE_CFG struTestDevModuleCfg;
    memset(&struTestDevModuleCfg, 0, sizeof(struTestDevModuleCfg)); 
    struTestDevModuleCfg.dwSize = sizeof(struTestDevModuleCfg);
    struTestDevModuleCfg.dwChannel = m_dwChannel; 
    struTestDevModuleCfg.byDevFanModuleType[0] = m_bDevFan1; 
    struTestDevModuleCfg.byDevFanModuleType[1] = m_bDevFan2; 
    struTestDevModuleCfg.byDevHeaterModuleType[0] = m_bDevHeater1; 
    struTestDevModuleCfg.byDevHeaterModuleType[1] = m_bDevHeater2; 
    if (! NET_DVR_RemoteControl(m_lUserID, NET_DVR_SET_TEST_DEVMODULE, &struTestDevModuleCfg, sizeof(struTestDevModuleCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetDVRConfig NET_DVR_SET_TEST_DEVMODULE");
        CString csError; 
        csError.Format(_T("发送开启命令失败 Error Code %d"), NET_DVR_GetLastError()); 
        AfxMessageBox(csError);  
    }
    else
    {
        // 刷新一下状态
        //OnButRefreshDevtest(); 
        m_bDevFan1 = FALSE; 
        m_bDevFan2 = FALSE; 
        m_bDevHeater1 = FALSE; 
        m_bDevHeater2 = FALSE; 
        UpdateData(FALSE); 
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_LOGO_OVERLAYCFG");
	}	
}

BOOL CDlgProductionTest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UpdateData(TRUE);
	// TODO: Add extra initialization here

    m_comSoundMode.SetCurSel(0);
    m_comElectronicCompassState.SetCurSel(0);
    m_comAging.SetCurSel(0);
    m_comEccentricCorrectState.SetCurSel(0);
    m_comWriteReadEnalbe.SetCurSel(0);


	m_dwChan = m_dwChannel;

    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgProductionTest::OnButResumeInitrackpos() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_RESUME_INITRACKPOS_CFG struResumeITPCfg; 
    memset(&struResumeITPCfg, 0, sizeof(struResumeITPCfg)); 
    struResumeITPCfg.dwSize = sizeof(struResumeITPCfg); 
    struResumeITPCfg.dwChannel = m_dwChannel;
    if (! NET_DVR_RemoteControl(m_lUserID, NET_DVR_RESUME_INITRACKPOS, &struResumeITPCfg, sizeof(struResumeITPCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_RESUME_INITRACKPOS");
        CString csError; 
        csError.Format(_T("Error Code %d"), NET_DVR_GetLastError()); 
        AfxMessageBox(csError);  
	}	
}

void CDlgProductionTest::OnBtnGetTempHumi() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	DWORD dwRet = 0;
	char szLan[128] = {0};
	NET_DVR_TEMP_HUMI struTempHuml;
	memset(&struTempHuml, 0, sizeof(struTempHuml));

	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_TEMP_HUMI, m_dwChannel, &struTempHuml, sizeof(struTempHuml), &dwRet))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TEMP_HUMI Failed!");
		g_StringLanType(szLan, "获取温湿度失败", "Failed to get the Temperature And Humidity Parameters");
		AfxMessageBox(szLan);
		m_fTemp = 0;
		m_fHuml = 0;
		UpdateData(FALSE); 
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TEMP_HUMI Succ!");
	}

 	int iTemp = struTempHuml.iTemp/1000;
 	float fTemp2 = float(struTempHuml.iTemp%1000)/1000;
 	m_fTemp = (float)iTemp + fTemp2;
 
 	int iHuml = struTempHuml.iHumidity/1000;
	float fHuml2 = float(struTempHuml.iHumidity%1000)/1000;
 	m_fHuml = (float)iHuml + fHuml2;
	

	UpdateData(FALSE);
}

void CDlgProductionTest::OnBtnSetAutofocus() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_AUTOFOCUS_TESTCFG struAutoFocus = {0};
	struAutoFocus.dwSize = sizeof(NET_DVR_AUTOFOCUS_TESTCFG);
	struAutoFocus.dwChannel = m_dwChannel;
	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SET_AUTOFOCUS_TEST, &struAutoFocus, sizeof(struAutoFocus)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_SET_AUTOFOCUS_TEST");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_SET_AUTOFOCUS_TEST");
	}
}

void CDlgProductionTest::OnBtnGetSoundmode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_ALARMSOUNDMODE_CFG struSoundMode = {0};
	struSoundMode.dwSize = sizeof(NET_DVR_ALARMSOUNDMODE_CFG);
	DWORD dwRet = 0;
	m_comSoundMode.SetCurSel(0);

	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ALARMSOUNDMODE, m_dwChannel, &struSoundMode, sizeof(struSoundMode), &dwRet))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetDVRConfig NET_DVR_GET_ALARMSOUNDMODE");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetDVRConfig NET_DVR_GET_ALARMSOUNDMODE");
		m_comSoundMode.SetCurSel(struSoundMode.dwSoundMode);
		m_dwChan = struSoundMode.dwChannel;
	}
	UpdateData(FALSE);
}

void CDlgProductionTest::OnBtnSetSoundmode() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_ALARMSOUNDMODE_CFG struSoundMode = {0};
	struSoundMode.dwSize = sizeof(NET_DVR_ALARMSOUNDMODE_CFG);
	struSoundMode.dwChannel = m_dwChannel;
	struSoundMode.dwSoundMode = m_comSoundMode.GetCurSel();

	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_ALARMSOUNDMODE, m_dwChannel, &struSoundMode, sizeof(struSoundMode)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetDVRConfig NET_DVR_SET_ALARMSOUNDMODE");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetDVRConfig NET_DVR_SET_ALARMSOUNDMODE");
	}
}

void CDlgProductionTest::OnBtnGetDialSwitch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_DIAL_SWITCH_CFG struDialSwitch = {0};
	struDialSwitch.dwSize = sizeof(NET_DVR_DIAL_SWITCH_CFG);
	DWORD dwRet = 0;
	m_csDialSwitch.Format(_T(""));
	
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_DIAL_SWITCH_CFG, m_dwChannel, &struDialSwitch, sizeof(struDialSwitch), &dwRet))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetDVRConfig NET_DVR_GET_DIAL_SWITCH_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetDVRConfig NET_DVR_GET_DIAL_SWITCH_CFG");
		m_csDialSwitch.Format("%X", struDialSwitch.dwSwitchState);
	}
	UpdateData(FALSE);
}

void CDlgProductionTest::OnBtnGetSecuritymode() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_SECURITYMODE struSecurityMode = {0};
	struSecurityMode.dwSize = sizeof(NET_DVR_SECURITYMODE);
	DWORD dwRet = 0;
	m_csDialSwitch.Format(_T(""));
	
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SECURITYMODE, m_dwChannel, &struSecurityMode, sizeof(struSecurityMode), &dwRet))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetDVRConfig NET_DVR_GET_SECURITYMODE");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetDVRConfig NET_DVR_GET_SECURITYMODE");
		m_dwChanSecurityMode = struSecurityMode.dwChannel;
		m_comSecurityMode.SetCurSel(struSecurityMode.dwMode - 1);
		m_csRandCode.Format("_T(%s)", struSecurityMode.szRandCode);
	}
	UpdateData(FALSE);
}

void CDlgProductionTest::OnBnClickedBtnSetAgingTrickScan()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_AGING_TRICK_SCAN struAgingTrickScan = { 0 };
    struAgingTrickScan.dwSize = sizeof(NET_DVR_AGING_TRICK_SCAN);
    struAgingTrickScan.dwChannel = m_dwChannel;
    struAgingTrickScan.byAging = m_comAging.GetCurSel();
    struAgingTrickScan.byWriteReadEnalbe = m_comWriteReadEnalbe.GetCurSel();
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_AGING_TRICK_SCAN, m_dwChannel, &struAgingTrickScan, sizeof(struAgingTrickScan)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_AGING_TRICK_SCAN FAIL ERROE CODE %d", NET_DVR_GetLastError());
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_AGING_TRICK_SCAN SUCC");
    }
    UpdateData(FALSE);
}


void CDlgProductionTest::OnBnClickedBtnGetEccentricCorrectState()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_ECCENTRIC_CORRECT_STATE struEccentricCorrectState = { 0 };
    struEccentricCorrectState.dwSize = sizeof(NET_DVR_ECCENTRIC_CORRECT_STATE);
    DWORD dwRet = 0;
    m_csDialSwitch.Format(_T(""));

    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ECCENTRIC_CORRECT_STATE, m_dwChannel, &struEccentricCorrectState, sizeof(struEccentricCorrectState), &dwRet))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ECCENTRIC_CORRECT_STATE FAIL ERROR CODE %d", NET_DVR_GetLastError());
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ECCENTRIC_CORRECT_STATE SUCC");
        m_comEccentricCorrectState.SetCurSel(struEccentricCorrectState.byEccentricCorrectState);
    }
    UpdateData(FALSE);
}


void CDlgProductionTest::OnBnClickedButClearIpcParam()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_IPC_PARAM_TYPE struIpcParamType = { 0 };
    struIpcParamType.dwSize = sizeof(NET_DVR_IPC_PARAM_TYPE);
    if (m_bAgingTrickScan)
    {
        struIpcParamType.dwParamType |= IPC_PARAM_AGING_TRICK_SCAN;
    }

    if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_CLEAR_IPC_PARAM, &struIpcParamType, sizeof(NET_DVR_IPC_PARAM_TYPE)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_CLEAR_IPC_PARAM FAIL ERROR CODE %d", NET_DVR_GetLastError());
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_CLEAR_IPC_PARAM SUCC");
    }
    UpdateData(FALSE);
}

