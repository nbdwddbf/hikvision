// DlgInfrareCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfrareCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfrareCfg dialog


CDlgInfrareCfg::CDlgInfrareCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfrareCfg::IDD, pParent)
    , m_byFocusSensitivity(0)
{
	//{{AFX_DATA_INIT(CDlgInfrareCfg)
	m_iMinFocusDistance = 0;
	m_iIrBrightness = 0;
	m_iIrSensitivity = 0;
	m_iChromaSuppress = 0;
	m_flrisset = 0.0f;
	m_fGainSet = 0.0f;
	m_fGainLimit = 0.0f;
	m_fExposureCompenSate = 0.0f;
	m_iOpticalZoom = 0;
	m_iDigtitalZoom = 0;
	m_iBrightnessLimit = 0;
	m_byMaxIrisSet = 0;
	m_byMinIrisSet = 0;
	m_fOpticalZoomLevel = 0.0f;
	m_csFocusPos = _T("");
	m_csPhyRatio = _T("");
	//}}AFX_DATA_INIT
	memset(&m_struPhyRatio, 0, sizeof(m_struPhyRatio));
}


void CDlgInfrareCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgInfrareCfg)
    DDX_Control(pDX, IDC_COMBO_MIN_SHUTTERSET, m_comMinShutterSet);
    DDX_Control(pDX, IDC_COMBO_MAX_SHUTTERSET, m_comMaxShutterSet);
    DDX_Control(pDX, IDC_COM_TRIGGERTYPE, m_comboTriggertype);
    DDX_Control(pDX, IDC_COMBO_SHUTTERSET, m_comboShutterSet);
    DDX_Control(pDX, IDC_COMBO_INITIALIZELENS, m_comboInitializeLens);
    DDX_Control(pDX, IDC_COMBO_IMAGESTABILIZE_LEVEL, m_comboImageStabilizeLevel);
    DDX_Control(pDX, IDC_COMBO_HIGHSENSITIVITY, m_comboHighSensitivity);
    DDX_Control(pDX, IDC_COMBO_CAMERAIR_CORRECT, m_comboCameraIrCorrect);
    DDX_Control(pDX, IDC_COMBO_EXPOSUREMODE, m_comboExposureModeSet);
    DDX_Control(pDX, IDC_COMBO_CONTROL_MODE, m_comboControlMode);
    DDX_Control(pDX, IDC_COMBO_ZOOMSPEEDLEVEL, m_comboZoomSpeedLevel);
    DDX_Control(pDX, IDC_COMBO_FOCUSSPEEDLEVEL, m_comboFocusSpeedLevel);
    DDX_Control(pDX, IDC_COMBO_AUTOFOCUSMODE, m_comboAutoFocusMode);
    DDX_Control(pDX, IDC_COMBO_FOCUSMODE, m_comboFocusMode);
    DDX_Control(pDX, IDC_COMBO_LOWLIGHTLIMTLEVEL, m_comboLowLightLimtLevel);
    DDX_Control(pDX, IDC_COMBO_LOWLIGHTLIMT, m_comboLowLightLimt);
    DDX_Text(pDX, IDC_EDIT_MINFOCUSDISTANCE, m_iMinFocusDistance);
    DDX_Text(pDX, IDC_EDIT_BRIGHTNESS, m_iIrBrightness);
    DDV_MinMaxInt(pDX, m_iIrBrightness, 0, 100);
    DDX_Text(pDX, IDC_EDIT_SENSITIVITY, m_iIrSensitivity);
    DDV_MinMaxInt(pDX, m_iIrSensitivity, 0, 100);
    DDX_Text(pDX, IDC_EDIT_CHROMA_SUPPRESS, m_iChromaSuppress);
    DDV_MinMaxInt(pDX, m_iChromaSuppress, 0, 255);
    DDX_Text(pDX, IDC_EDIT_ILRISSET, m_flrisset);
    DDX_Text(pDX, IDC_EDIT_IGAINSET, m_fGainSet);
    DDX_Text(pDX, IDC_EDIT_IGAINLIMIT, m_fGainLimit);
    DDX_Text(pDX, IDC_EDIT_IEXPOSURECOMPENSATE, m_fExposureCompenSate);
    DDX_Text(pDX, IDC_EDIT_OPTICALZOOM, m_iOpticalZoom);
    DDX_Text(pDX, IDC_EDIT_DIGTITALZOOM, m_iDigtitalZoom);
    DDX_Text(pDX, IDC_EDIT_BRIGHTNESS_LIMIT, m_iBrightnessLimit);
    DDX_Text(pDX, IDC_EDIT_MAX_ILRISSET, m_byMaxIrisSet);
    DDX_Text(pDX, IDC_EDIT_MIN_ILRISSET, m_byMinIrisSet);
    DDX_Text(pDX, IDC_EDIT_DIGOPTICALZOOMLEVEL, m_fOpticalZoomLevel);
    DDX_Text(pDX, IDC_EDIT_FOCUSPOS, m_csFocusPos);
    DDX_Text(pDX, IDC_EDIT_PHY_RATIO, m_csPhyRatio);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_ExposureLevel, m_ExposureLeve);
    DDX_Text(pDX, IDC_EDIT2, m_byFocusSensitivity);
}


BEGIN_MESSAGE_MAP(CDlgInfrareCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgInfrareCfg)
	ON_BN_CLICKED(IDC_BTN_LOWLIGHT_SET, OnBtnLowlightSet)
	ON_BN_CLICKED(IDC_BTN_LOWLIGHT_GET, OnBtnLowlightGet)
	ON_BN_CLICKED(IDC_BTN_FOCUSMODE_SET, OnBtnFocusmodeSet)
	ON_BN_CLICKED(IDC_BTN_FOCUSMODE_GET, OnBtnFocusmodeGet)
	ON_BN_CLICKED(IDC_BTN_INFRARE_SET, OnBtnInfrareSet)
	ON_BN_CLICKED(IDC_BTN_INFRARE_GET, OnBtnInfrareGet)
	ON_CBN_SELCHANGE(IDC_COMBO_CONTROL_MODE, OnEditchangeComboControlMode)
	ON_BN_CLICKED(IDC_BTN_AEMODECFG_GET, OnBtnAemodecfgGet)
	ON_BN_CLICKED(IDC_BTN_AEMODECFG_SET, OnBtnAemodecfgSet)
	ON_CBN_SELCHANGE(IDC_COMBO_EXPOSUREMODE, OnSelchangeComboExposuremode)
	ON_BN_CLICKED(IDC_BTN_RESTART_SUPPORT, OnBtnRestartSupport)
	ON_BN_CLICKED(IDC_BTN_RESTORE_SUPPORT, OnBtnRestoreSupport)
	ON_BN_CLICKED(IDC_BTN_PHY_RATIO_SET, OnBtnPhyRatioSet)
	ON_BN_CLICKED(IDC_BTN_PHY_RATIO_GET, OnBtnPhyRatioGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfrareCfg message handlers

void CDlgInfrareCfg::OnBtnLowlightSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_LOW_LIGHT_CFG struLowLightCfg;
	memset(&struLowLightCfg, 0, sizeof(struLowLightCfg));
	struLowLightCfg.dwSize = sizeof(struLowLightCfg);
	struLowLightCfg.byLowLightLimt = m_comboLowLightLimt.GetCurSel();
	struLowLightCfg.byLowLightLimtLevel = m_comboLowLightLimtLevel.GetCurSel();

	if (!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDevIndex].lLoginID, NET_DVR_SET_LOW_LIGHTCFG, 1, &struLowLightCfg, sizeof(struLowLightCfg)))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_SET_LOW_LIGHTCFG");
    }
	else
	{
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_SET_LOW_LIGHTCFG");
	}
}

void CDlgInfrareCfg::OnBtnLowlightGet() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_LOW_LIGHT_CFG struLowLightCfg;
	memset(&struLowLightCfg, 0, sizeof(struLowLightCfg));
	DWORD dwReturn = 0;
	if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDevIndex].lLoginID, NET_DVR_GET_LOW_LIGHTCFG, 1, &struLowLightCfg, sizeof(struLowLightCfg), &dwReturn))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_LOW_LIGHTCFG");
    }
	else
	{
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_LOW_LIGHTCFG");
	}
	m_comboLowLightLimt.SetCurSel(struLowLightCfg.byLowLightLimt);
	m_comboLowLightLimtLevel.SetCurSel(struLowLightCfg.byLowLightLimtLevel);

	UpdateData(FALSE);
}

DWORD DecToHex(DWORD wDec)
{
    return (wDec / 1000) * 4096 + ((wDec % 1000) / 100) * 256 + ((wDec % 100) / 10) * 16 + (wDec % 10);
}

DWORD HexToDec(DWORD wHex)
{
    return (wHex / 4096) * 1000 + ((wHex % 4096) / 256) * 100 + ((wHex % 256) / 16) * 10 + (wHex % 16);
}

void CDlgInfrareCfg::OnBtnFocusmodeSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_FOCUSMODE_CFG  struFocusModeCfg;
	memset(&struFocusModeCfg, 0, sizeof(struFocusModeCfg));
	struFocusModeCfg.dwSize = sizeof(struFocusModeCfg);
	struFocusModeCfg.byFocusMode = m_comboFocusMode.GetCurSel();
	struFocusModeCfg.byAutoFocusMode = m_comboAutoFocusMode.GetCurSel();
	struFocusModeCfg.wMinFocusDistance = m_iMinFocusDistance;
	struFocusModeCfg.byZoomSpeedLevel = (m_comboZoomSpeedLevel.GetCurSel() + 1);
	struFocusModeCfg.byFocusSpeedLevel = (m_comboFocusSpeedLevel.GetCurSel() + 1);
	struFocusModeCfg.byOpticalZoom = m_iOpticalZoom;
	struFocusModeCfg.byDigtitalZoom = m_iDigtitalZoom;
    struFocusModeCfg.fOpticalZoomLevel = m_fOpticalZoomLevel;

    struFocusModeCfg.byFocusSensitivity = m_byFocusSensitivity;

    sscanf(m_csFocusPos, "%x", &struFocusModeCfg.dwFocusPos);

    if (!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDevIndex].lLoginID, NET_DVR_SET_FOCUSMODECFG, m_lChannel, &struFocusModeCfg, sizeof(struFocusModeCfg)))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_SET_FOCUSMODECFG");
    }
	else
	{
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_SET_FOCUSMODECFG");
	}
}

void CDlgInfrareCfg::OnBtnFocusmodeGet() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_FOCUSMODE_CFG  struFocusModeCfg;
	memset(&struFocusModeCfg, 0, sizeof(struFocusModeCfg));
	DWORD dwReturn = 0;

    if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDevIndex].lLoginID, NET_DVR_GET_FOCUSMODECFG, m_lChannel, &struFocusModeCfg, sizeof(struFocusModeCfg), &dwReturn))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_FOCUSMODECFG");
    }
	else
	{
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_FOCUSMODECFG");
	}
	
	m_comboFocusMode.SetCurSel(struFocusModeCfg.byFocusMode);
	m_comboAutoFocusMode.SetCurSel(struFocusModeCfg.byAutoFocusMode);
	m_iMinFocusDistance = struFocusModeCfg.wMinFocusDistance;
	m_comboZoomSpeedLevel.SetCurSel(struFocusModeCfg.byZoomSpeedLevel - 1);
	m_comboFocusSpeedLevel.SetCurSel(struFocusModeCfg.byFocusSpeedLevel - 1);
	m_iDigtitalZoom = struFocusModeCfg.byDigtitalZoom;
	m_iOpticalZoom = struFocusModeCfg.byOpticalZoom;
    m_fOpticalZoomLevel = struFocusModeCfg.fOpticalZoomLevel;
    m_csFocusPos.Format("%x", struFocusModeCfg.dwFocusPos);
    m_byFocusSensitivity = struFocusModeCfg.byFocusSensitivity;
	UpdateData(FALSE);
}

void CDlgInfrareCfg::OnBtnInfrareSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	struInfrareCfg.dwSize = sizeof(struInfrareCfg);
	struInfrareCfg.byIrSensitivity = m_iIrSensitivity;
	struInfrareCfg.byIrBrightness = m_iIrBrightness;
	struInfrareCfg.byIrTrigMode = m_comboTriggertype.GetCurSel();
	struInfrareCfg.byIrBrightnessLimit = m_iBrightnessLimit;

	if (!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDevIndex].lLoginID, NET_DVR_SET_INFRARECFG, 1, &struInfrareCfg, sizeof(struInfrareCfg)))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_SET_INFRARECFG");
    }
	else
	{
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_SET_INFRARECFG");
	}
}

void CDlgInfrareCfg::OnBtnInfrareGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDevIndex].lLoginID, NET_DVR_GET_INFRARECFG, 1, &struInfrareCfg, sizeof(struInfrareCfg), &dwReturn))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_INFRARECFG");
    }
	else
	{
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_INFRARECFG");
	}
	m_comboControlMode.SetCurSel(struInfrareCfg.byIrControlMode);
	m_iBrightnessLimit = struInfrareCfg.byIrBrightnessLimit;
	m_comboTriggertype.SetCurSel(struInfrareCfg.byIrTrigMode);

	if (0 == struInfrareCfg.byIrControlMode)
	{
		GetDlgItem(IDC_EDIT_SENSITIVITY)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_BRIGHTNESS)->EnableWindow(FALSE);
		m_iIrBrightness = struInfrareCfg.byIrBrightness;
	} 
	else
	{
		GetDlgItem(IDC_EDIT_BRIGHTNESS)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SENSITIVITY)->EnableWindow(FALSE);
		m_iIrSensitivity = struInfrareCfg.byIrSensitivity;
	}
	UpdateData(FALSE);
}

BOOL CDlgInfrareCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_EDIT_SENSITIVITY)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_BRIGHTNESS)->EnableWindow(FALSE);

	GetDlgItem(IDC_COMBO_SHUTTERSET)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_IGAINLIMIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_IGAINSET)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_ILRISSET)->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInfrareCfg::OnEditchangeComboControlMode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	struInfrareCfg.byIrControlMode = m_comboControlMode.GetCurSel();
	if (struInfrareCfg.byIrControlMode == 0)
	{
		GetDlgItem(IDC_EDIT_SENSITIVITY)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_BRIGHTNESS)->EnableWindow(FALSE);
		struInfrareCfg.byIrBrightness = 0;
		GetDlgItem(IDC_COM_TRIGGERTYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_BRIGHTNESS_LIMIT)->EnableWindow(TRUE);
	} 
	else
	{
		GetDlgItem(IDC_EDIT_BRIGHTNESS)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SENSITIVITY)->EnableWindow(FALSE);
		struInfrareCfg.byIrSensitivity = 0;
		GetDlgItem(IDC_COM_TRIGGERTYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_BRIGHTNESS_LIMIT)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}

void CDlgInfrareCfg::OnBtnAemodecfgGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDevIndex].lLoginID, NET_DVR_GET_AEMODECFG, 1, &struAemodeCfg, sizeof(struAemodeCfg), &dwReturn))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_AEMODECFG");
    }
	else
	{
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_AEMODECFG");
	}

	m_flrisset = (float)struAemodeCfg.iIrisSet/100;
	m_fGainSet = (float)struAemodeCfg.iGainSet/100;
	m_fGainLimit = (float)struAemodeCfg.iGainLimit/100;
	m_fExposureCompenSate = (float)struAemodeCfg.iExposureCompensate/100;
	m_comboExposureModeSet.SetCurSel(struAemodeCfg.byExposureModeSet);
	m_comboShutterSet.SetCurSel(struAemodeCfg.byShutterSet);
	m_comboImageStabilizeLevel.SetCurSel(struAemodeCfg.byImageStabilizeLevel);
	m_comboCameraIrCorrect.SetCurSel(struAemodeCfg.byCameraIrCorrect);
	m_comboHighSensitivity.SetCurSel(struAemodeCfg.byHighSensitivity);
	m_comboInitializeLens.SetCurSel(struAemodeCfg.byInitializeLens);
	m_iChromaSuppress = struAemodeCfg.byChromaSuppress;
    m_comMaxShutterSet.SetCurSel(struAemodeCfg.byMaxShutterSet);
    m_comMinShutterSet.SetCurSel(struAemodeCfg.byMinShutterSet);
    m_byMaxIrisSet = struAemodeCfg.byMaxIrisSet;
    m_byMinIrisSet = struAemodeCfg.byMinIrisSet;
    m_ExposureLeve.SetCurSel(struAemodeCfg.byExposureLevel);
	if (1 == struAemodeCfg.byExposureModeSet)
	{
		//GetDlgItem(IDC_EDIT_IEXPOSURECOMPENSATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_SHUTTERSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IGAINLIMIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IGAINSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_ILRISSET)->EnableWindow(FALSE);

        GetDlgItem(IDC_COMBO_MAX_SHUTTERSET)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_MIN_SHUTTERSET)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_MAX_ILRISSET)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_MIN_ILRISSET)->EnableWindow(TRUE);
	} 
	else if(2 == struAemodeCfg.byExposureModeSet)
	{
		//GetDlgItem(IDC_EDIT_IEXPOSURECOMPENSATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_SHUTTERSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IGAINLIMIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IGAINSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_ILRISSET)->EnableWindow(TRUE);

        GetDlgItem(IDC_COMBO_MAX_SHUTTERSET)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_MIN_SHUTTERSET)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_MAX_ILRISSET)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MIN_ILRISSET)->EnableWindow(FALSE);
	}
	else if (3 == struAemodeCfg.byExposureModeSet)
	{
		GetDlgItem(IDC_COMBO_SHUTTERSET)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IGAINLIMIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IGAINSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_ILRISSET)->EnableWindow(FALSE);

        GetDlgItem(IDC_COMBO_MAX_SHUTTERSET)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_MIN_SHUTTERSET)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MAX_ILRISSET)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_MIN_ILRISSET)->EnableWindow(TRUE);
	}
	else if (4 == struAemodeCfg.byExposureModeSet)
	{
		GetDlgItem(IDC_COMBO_SHUTTERSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IGAINLIMIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IGAINSET)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_ILRISSET)->EnableWindow(FALSE);

        GetDlgItem(IDC_COMBO_MAX_SHUTTERSET)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_MIN_SHUTTERSET)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MAX_ILRISSET)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MIN_ILRISSET)->EnableWindow(FALSE);
	}
	else if(0 == struAemodeCfg.byExposureModeSet)
	{
		GetDlgItem(IDC_COMBO_SHUTTERSET)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IGAINLIMIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IGAINSET)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_ILRISSET)->EnableWindow(TRUE);	  
        
        GetDlgItem(IDC_COMBO_MAX_SHUTTERSET)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_MIN_SHUTTERSET)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MAX_ILRISSET)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MIN_ILRISSET)->EnableWindow(FALSE);
	}

	UpdateData(FALSE);
}

void CDlgInfrareCfg::OnBtnAemodecfgSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	struAemodeCfg.dwSize = sizeof(struAemodeCfg);
	struAemodeCfg.iIrisSet = (m_flrisset+1.0e-6) * 100;
	if (m_fGainSet < 0)
	{
		struAemodeCfg.iGainSet = (((-1)*m_fGainSet+1.0e-6) * 100)*(-1);
	} 
	else
	{
		struAemodeCfg.iGainSet = (m_fGainSet+1.0e-6) * 100;
	}
	if (m_fGainLimit < 0)
	{
		struAemodeCfg.iGainLimit = (((-1)*m_fGainLimit+1.0e-6) * 100)*(-1);
	} 
	else
	{
		struAemodeCfg.iGainLimit = (m_fGainLimit+1.0e-6) * 100;
	}
	
	if (m_fExposureCompenSate < 0)
	{
		struAemodeCfg.iExposureCompensate = (((-1)*m_fExposureCompenSate+1.0e-6) * 100)*(-1);
	} 
	else
	{
		struAemodeCfg.iExposureCompensate = (m_fExposureCompenSate+1.0e-6) * 100;
	}
	struAemodeCfg.byShutterSet = m_comboShutterSet.GetCurSel();
	struAemodeCfg.byImageStabilizeLevel = m_comboImageStabilizeLevel.GetCurSel();
	struAemodeCfg.byCameraIrCorrect = m_comboCameraIrCorrect.GetCurSel();
	struAemodeCfg.byHighSensitivity = m_comboHighSensitivity.GetCurSel();
	struAemodeCfg.byInitializeLens = m_comboInitializeLens.GetCurSel();
	struAemodeCfg.byChromaSuppress = m_iChromaSuppress;
    struAemodeCfg.byMaxShutterSet = m_comMaxShutterSet.GetCurSel();
    struAemodeCfg.byMinShutterSet = m_comMinShutterSet.GetCurSel();
    struAemodeCfg.byMaxIrisSet = m_byMaxIrisSet;
    struAemodeCfg.byMinIrisSet = m_byMinIrisSet;
    struAemodeCfg.byExposureLevel = m_ExposureLeve.GetCurSel();
	if (!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDevIndex].lLoginID, NET_DVR_SET_AEMODECFG, 1, &struAemodeCfg, sizeof(struAemodeCfg)))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_SET_AEMODECFG");
    }
	else
	{
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_SET_AEMODECFG");
	}

}

void CDlgInfrareCfg::OnSelchangeComboExposuremode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	struAemodeCfg.byExposureModeSet = m_comboExposureModeSet.GetCurSel();

	if (1 == struAemodeCfg.byExposureModeSet)
	{
		//GetDlgItem(IDC_EDIT_IEXPOSURECOMPENSATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_SHUTTERSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IGAINLIMIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IGAINSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_ILRISSET)->EnableWindow(FALSE);

        GetDlgItem(IDC_COMBO_MAX_SHUTTERSET)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_MIN_SHUTTERSET)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_MAX_ILRISSET)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_MIN_ILRISSET)->EnableWindow(TRUE);
	} 
	else if(2 == struAemodeCfg.byExposureModeSet)
	{
		//GetDlgItem(IDC_EDIT_IEXPOSURECOMPENSATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_SHUTTERSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IGAINLIMIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IGAINSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_ILRISSET)->EnableWindow(TRUE);

        GetDlgItem(IDC_COMBO_MAX_SHUTTERSET)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_MIN_SHUTTERSET)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_MAX_ILRISSET)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MIN_ILRISSET)->EnableWindow(FALSE);
	}
	else if (3 == struAemodeCfg.byExposureModeSet)
	{
		GetDlgItem(IDC_COMBO_SHUTTERSET)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IGAINLIMIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IGAINSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_ILRISSET)->EnableWindow(FALSE);

        GetDlgItem(IDC_COMBO_MAX_SHUTTERSET)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_MIN_SHUTTERSET)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MAX_ILRISSET)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_MIN_ILRISSET)->EnableWindow(TRUE);
	}
	else if (4 == struAemodeCfg.byExposureModeSet)
	{
		GetDlgItem(IDC_COMBO_SHUTTERSET)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IGAINLIMIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IGAINSET)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_ILRISSET)->EnableWindow(FALSE);

        GetDlgItem(IDC_COMBO_MAX_SHUTTERSET)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_MIN_SHUTTERSET)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MAX_ILRISSET)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MIN_ILRISSET)->EnableWindow(FALSE);
	}
	else if(0 == struAemodeCfg.byExposureModeSet)
	{
		GetDlgItem(IDC_COMBO_SHUTTERSET)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IGAINLIMIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IGAINSET)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_ILRISSET)->EnableWindow(TRUE);	
        
        GetDlgItem(IDC_COMBO_MAX_SHUTTERSET)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_MIN_SHUTTERSET)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MAX_ILRISSET)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MIN_ILRISSET)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}

void CDlgInfrareCfg::OnBtnRestartSupport() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTECONTROL_STUDY_PARAM struRemoteControl;
	memset(&struRemoteControl, 0, sizeof(struRemoteControl));
	struRemoteControl.dwSize = sizeof(struRemoteControl);
	struRemoteControl.dwChannel = 1;
	if (!NET_DVR_RemoteControl(g_struDeviceInfo[m_iDevIndex].lLoginID, NET_DVR_CONTROL_RESTART_SUPPORT, &struRemoteControl, sizeof(struRemoteControl)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl DVR_CONTROL_RESTART_SUPPORT");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl DVR_CONTROL_RESTART_SUPPORT");
	}
}

void CDlgInfrareCfg::OnBtnRestoreSupport() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTECONTROL_STUDY_PARAM struRemoteControl;
	memset(&struRemoteControl, 0, sizeof(struRemoteControl));
	struRemoteControl.dwSize = sizeof(struRemoteControl);
	struRemoteControl.dwChannel = 1;
	if (!NET_DVR_RemoteControl(g_struDeviceInfo[m_iDevIndex].lLoginID, NET_DVR_CONTROL_RESTORE_SUPPORT, &struRemoteControl, sizeof(struRemoteControl)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl DVR_CONTROL_RESTORE_SUPPORT");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl DVR_CONTROL_RESTORE_SUPPORT");
	}
}

void CDlgInfrareCfg::OnBtnPhyRatioSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struPhyRatio.dwSize =  sizeof(m_struPhyRatio);
	sscanf(m_csPhyRatio, "%x", &m_struPhyRatio.dwPhysicsRatio);

	if (!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDevIndex].lLoginID, NET_DVR_SET_PHY_RATIO, 1, &m_struPhyRatio, sizeof(m_struPhyRatio)))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_SET_PHY_RATIO");
    }
	else
	{
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_SET_PHY_RATIO");
	}

}

void CDlgInfrareCfg::OnBtnPhyRatioGet() 
{
	// TODO: Add your control notification handler code here
	
	memset(&m_struPhyRatio, 0, sizeof(m_struPhyRatio));
	DWORD dwReturn = 0;
	if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDevIndex].lLoginID, NET_DVR_GET_PHY_RATIO, 1, &m_struPhyRatio, sizeof(m_struPhyRatio), &dwReturn))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_PHY_RATIO");
    }
	else
	{
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_PHY_RATIO");
	}

	m_csPhyRatio.Format("%x", m_struPhyRatio.dwPhysicsRatio);
	
	UpdateData(FALSE);
}
