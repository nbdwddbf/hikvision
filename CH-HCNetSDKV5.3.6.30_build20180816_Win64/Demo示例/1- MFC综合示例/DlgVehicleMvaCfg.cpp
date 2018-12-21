// DlgVehicleMvaCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVehicleMvaCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVehicleMvaCfg dialog


CDlgVehicleMvaCfg::CDlgVehicleMvaCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVehicleMvaCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVehicleMvaCfg)
	m_bCapPeccType = FALSE;
	m_bCapPeccCap = FALSE;
	m_bPlateTimeOverlay = FALSE;
	m_bPlateResultOverlay = FALSE;
	m_bPlateHintOverlay = FALSE;
	m_bPlateUpload = FALSE;
	m_bRadarEnable = FALSE;
	m_bRadarAlarm = FALSE;
	m_byRadarCapNum = 0;
	m_byRadarSensitivity = 0;
	m_wRadarOverSpeed = 0;
	m_bRadarUpload = FALSE;
	m_bBlackListAlarm = FALSE;
	m_bBlackListCheck = FALSE;
	m_bBlackListHint = FALSE;
	m_bBlackListUpload = FALSE;
	m_dwVehicleChannal = 0;
	m_strVehiclePeccInfo = _T("");
	m_byVehiclePeccNum = 0;
	m_fVehicleRectX = 0.0f;
	m_fVehicleRectY = 0.0f;
	m_fVehicleRectHight = 0.0f;
	m_fVehicleRectWidth = 0.0f;
	m_byVehicleBelive1 = 0;
	m_byVehicleBelive2 = 0;
	m_byVehicleBelive3 = 0;
	m_byVehicleBelive4 = 0;
	m_byVehicleBelive5 = 0;
	m_byVehicleBelive6 = 0;
	m_byVehicleBelive7 = 0;
	m_byVehicleBelive8 = 0;
	m_byVehicleBelive9 = 0;
	m_byVehicleBelive10 = 0;
	m_byVehicleBelive11 = 0;
	m_byVehicleBelive12 = 0;
	m_byVehicleBelive13 = 0;
	m_byVehicleBelive14 = 0;
	m_byVehicleBelive15 = 0;
	m_byVehicleBelive16 = 0;
	m_wSendTime = 1;
	m_byVehicleBright = 0;
	m_byVehicleCharNum = 0;
	m_strVehiclePlateNumber = _T("");
	m_byVehicleBelive = 0;
	m_wTimeYear = 0;
	m_byTimeMonth = 0;
	m_byTimeDay = 0;
	m_byTimeHour = 0;
	m_byTimeMin = 0;
	m_byTimeSec = 0;
	m_wTimeMsec = 0;
	m_strVehicleCustom = _T("");
	m_strTransParam = _T("");
	//}}AFX_DATA_INIT
	m_dwDevIndex = -1;
	m_lServerID = -1;
	m_lTranHandle = 0;
}


void CDlgVehicleMvaCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVehicleMvaCfg)
	DDX_Control(pDX, IDC_COMBO_CHN, m_comboCHN);
	DDX_Control(pDX, IDC_COMBO_VEHICLE_PLATE_TYPE, m_comboVehiclePlateType);
	DDX_Control(pDX, IDC_COMBO_VEHICLE_PLATE_COLOR, m_comboVehiclePlateColor);
	DDX_Control(pDX, IDC_COMBO_VEHICLE_PECC_TYPE, m_comboVehiclePeccType);
	DDX_Control(pDX, IDC_COMBO_TARGET_TYPE, m_comboRadarTargetType);
	DDX_Control(pDX, IDC_COMBO_SPEED_UNIT, m_comboRadarSpeedUnit);
	DDX_Control(pDX, IDC_COMBO_RADAR_STATUS, m_comboRadarStatus);
	DDX_Control(pDX, IDC_COMBO_RADAR_DIR, m_comboRadarDir);
	DDX_Control(pDX, IDC_COMBO_PLATE_TYPE, m_comboPlateType);
	DDX_Control(pDX, IDC_COMBO_ENVIR, m_comboPlateEnvir);
	DDX_Control(pDX, IDC_COMBO_DIR, m_comboPlateDir);
	DDX_Control(pDX, IDC_COMBO_PIC_SIZE, m_comboCapPicSize);
	DDX_Control(pDX, IDC_COMBO_PIC_QUALITY, m_comboCapPicQuality);
	DDX_Control(pDX, IDC_COMBO_OPT_HABIT, m_comboCapOptHabit);
	DDX_Control(pDX, IDC_COMBO_FPS_ADJUST_MODE, m_comboCapFpsAdjType);
	DDX_Check(pDX, IDC_CHK_PECC_TYPE, m_bCapPeccType);
	DDX_Check(pDX, IDC_CHK_ENABLE_PECC_PIC_CAP, m_bCapPeccCap);
	DDX_Check(pDX, IDC_CHK_TIME_INFO_OVERLAY, m_bPlateTimeOverlay);
	DDX_Check(pDX, IDC_CHK_RESULT_OVERLAY, m_bPlateResultOverlay);
	DDX_Check(pDX, IDC_CHK_SUCCESS_HINT, m_bPlateHintOverlay);
	DDX_Check(pDX, IDC_CHK_UPLOAD_PLATE, m_bPlateUpload);
	DDX_Check(pDX, IDC_CHK_RADAR, m_bRadarEnable);
	DDX_Check(pDX, IDC_CHK_ALARM, m_bRadarAlarm);
	DDX_Text(pDX, IDC_EDIT_CAPTURE_NUM, m_byRadarCapNum);
	DDX_Text(pDX, IDC_EDIT_SENSITIVITY, m_byRadarSensitivity);
	DDX_Text(pDX, IDC_EDIT_VOER_SPEED, m_wRadarOverSpeed);
	DDX_Check(pDX, IDC_CHK_UPLOAD_OVERSPEED_PIC, m_bRadarUpload);
	DDX_Check(pDX, IDC_CHK_BLACK_LIST_ALARM, m_bBlackListAlarm);
	DDX_Check(pDX, IDC_CHK_BLACK_LIST_CHECK, m_bBlackListCheck);
	DDX_Check(pDX, IDC_CHK_BLACK_LIST_HINT, m_bBlackListHint);
	DDX_Check(pDX, IDC_CHK_BLACK_LIST_UPLOAD, m_bBlackListUpload);
	DDX_Text(pDX, IDC_EDIT_VEHICLE_CHANNAL, m_dwVehicleChannal);
	DDX_Text(pDX, IDC_EDIT_VEHICLE_PECC_INFO, m_strVehiclePeccInfo);
	DDX_Text(pDX, IDC_EDIT_VEHICLE_PECC_NUM, m_byVehiclePeccNum);
	DDX_Text(pDX, IDC_EDIT_RECT_X, m_fVehicleRectX);
	DDX_Text(pDX, IDC_EDIT_RECT_Y, m_fVehicleRectY);
	DDX_Text(pDX, IDC_EDIT_RECT_HIGHT, m_fVehicleRectHight);
	DDX_Text(pDX, IDC_EDIT_RECT_WIDTH, m_fVehicleRectWidth);
	DDX_Text(pDX, IDC_EDIT_BELEIVE1, m_byVehicleBelive1);
	DDX_Text(pDX, IDC_EDIT_BELEIVE2, m_byVehicleBelive2);
	DDX_Text(pDX, IDC_EDIT_BELEIVE3, m_byVehicleBelive3);
	DDX_Text(pDX, IDC_EDIT_BELEIVE4, m_byVehicleBelive4);
	DDX_Text(pDX, IDC_EDIT_BELEIVE5, m_byVehicleBelive5);
	DDX_Text(pDX, IDC_EDIT_BELEIVE6, m_byVehicleBelive6);
	DDX_Text(pDX, IDC_EDIT_BELEIVE7, m_byVehicleBelive7);
	DDX_Text(pDX, IDC_EDIT_BELEIVE8, m_byVehicleBelive8);
	DDX_Text(pDX, IDC_EDIT_BELEIVE9, m_byVehicleBelive9);
	DDX_Text(pDX, IDC_EDIT_BELEIVE10, m_byVehicleBelive10);
	DDX_Text(pDX, IDC_EDIT_BELEIVE11, m_byVehicleBelive11);
	DDX_Text(pDX, IDC_EDIT_BELEIVE12, m_byVehicleBelive12);
	DDX_Text(pDX, IDC_EDIT_BELEIVE13, m_byVehicleBelive13);
	DDX_Text(pDX, IDC_EDIT_BELEIVE14, m_byVehicleBelive14);
	DDX_Text(pDX, IDC_EDIT_BELEIVE15, m_byVehicleBelive15);
	DDX_Text(pDX, IDC_EDIT_BELEIVE16, m_byVehicleBelive16);
	DDX_Text(pDX, IDC_EDIT_SEND_TIME, m_wSendTime);
	DDX_Text(pDX, IDC_EDIT_VEHICLE_BRIGHT, m_byVehicleBright);
	DDX_Text(pDX, IDC_EDIT_VEHICLE_CHAR_NUM, m_byVehicleCharNum);
	DDX_Text(pDX, IDC_EDIT_VEHICLE_NUMBER, m_strVehiclePlateNumber);
	DDX_Text(pDX, IDC_EDIT_VEHICLE_BELIVE, m_byVehicleBelive);
	DDX_Text(pDX, IDC_EDIT_TIME_YEAR, m_wTimeYear);
	DDX_Text(pDX, IDC_EDIT_TIME_MONTH, m_byTimeMonth);
	DDX_Text(pDX, IDC_EDIT_TIME_DAY, m_byTimeDay);
	DDX_Text(pDX, IDC_EDIT_TIME_HOUR, m_byTimeHour);
	DDX_Text(pDX, IDC_EDIT_TIME_MIN, m_byTimeMin);
	DDX_Text(pDX, IDC_EDIT_TIME_SEC, m_byTimeSec);
	DDX_Text(pDX, IDC_EDIT_TIME_MSEC, m_wTimeMsec);
	DDX_Text(pDX, IDC_EDIT_VEHICLE_CUSTOM, m_strVehicleCustom);
	DDX_Text(pDX, IDC_EDIT_TRANS_PARAM, m_strTransParam);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVehicleMvaCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVehicleMvaCfg)
	ON_BN_CLICKED(IDC_BTN_SET_CAP_CFG, OnBtnSetCapCfg)
	ON_BN_CLICKED(IDC_BTN_GET_CAP_CFG, OnBtnGetCapCfg)
	ON_BN_CLICKED(IDC_BTN_SET_PLATE_RECG_CFG, OnBtnSetPlateRecgCfg)
	ON_BN_CLICKED(IDC_BTN_GET_PLATE_RECG_CFG, OnBtnGetPlateRecgCfg)
	ON_BN_CLICKED(IDC_BTN_SET_RADAR_CFG, OnBtnSetRadarCfg)
	ON_BN_CLICKED(IDC_BTN_GET_RADAR_CFG, OnBtnGetRadarCfg)
	ON_BN_CLICKED(IDC_BTN_SET_BLACK_LIST_CFG, OnBtnSetBlackListCfg)
	ON_BN_CLICKED(IDC_BTN_GET_BLACK_LIST_CFG, OnBtnGetBlackListCfg)
	ON_BN_CLICKED(IDC_BTN_VEHICLE_DATA_SEND, OnBtnVehicleDataSend)
	ON_BN_CLICKED(IDC_BTN_SET_TRANS_PARAM, OnBtnSetTransParam)
	ON_BN_CLICKED(IDC_BTN_GET_TRANS_PARAM, OnBtnGetTransParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVehicleMvaCfg message handlers

BOOL CDlgVehicleMvaCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);
	
	//Ê¡·ÝË÷Òý
	m_comboCHN.ResetContent();
	m_comboCHN.InsertString(0 , "Íî");
	m_comboCHN.SetItemData(0, 0);
	m_comboCHN.InsertString(1 , "°Ä");
	m_comboCHN.SetItemData(1, 1);
	m_comboCHN.InsertString(2 , "¾©");
	m_comboCHN.SetItemData(2, 2);
	m_comboCHN.InsertString(3 , "Óå");
	m_comboCHN.SetItemData(3, 3);
	m_comboCHN.InsertString(4 , "Ãö");
	m_comboCHN.SetItemData(4, 4);
	m_comboCHN.InsertString(5 , "¸Ê");
	m_comboCHN.SetItemData(5, 5);
	m_comboCHN.InsertString(6 , "ÔÁ");
	m_comboCHN.SetItemData(6, 6);
	m_comboCHN.InsertString(7 , "¹ð");
	m_comboCHN.SetItemData(7, 7);
	m_comboCHN.InsertString(8 , "¹ó");
	m_comboCHN.SetItemData(8, 8);
	m_comboCHN.InsertString(9 , "Çí");
	m_comboCHN.SetItemData(9, 9);
	m_comboCHN.InsertString(10 , "¼½");
	m_comboCHN.SetItemData(10, 10);
	m_comboCHN.InsertString(11 , "Ô¥");
	m_comboCHN.SetItemData(11, 11);
	m_comboCHN.InsertString(12 , "ºÚ");
	m_comboCHN.SetItemData(12, 12);
	m_comboCHN.InsertString(13 , "¶õ");
	m_comboCHN.SetItemData(13, 13);
	m_comboCHN.InsertString(14 , "Ïæ");
	m_comboCHN.SetItemData(14, 14);
	m_comboCHN.InsertString(15 , "¼ª");
	m_comboCHN.SetItemData(15, 15);
	m_comboCHN.InsertString(16 , "ËÕ");
	m_comboCHN.SetItemData(16, 16);
	m_comboCHN.InsertString(17 , "¸Ó");
	m_comboCHN.SetItemData(17, 17);
	m_comboCHN.InsertString(18 , "ÁÉ");
	m_comboCHN.SetItemData(18, 18);
	m_comboCHN.InsertString(19 , "ÃÉ");
	m_comboCHN.SetItemData(19, 19);
	m_comboCHN.InsertString(20 , "Äþ");
	m_comboCHN.SetItemData(20, 20);
	m_comboCHN.InsertString(21 , "Çà");
	m_comboCHN.SetItemData(21, 21);
	m_comboCHN.InsertString(22, "Â³");
	m_comboCHN.SetItemData(22, 22);
	m_comboCHN.InsertString(23 , "½ú");
	m_comboCHN.SetItemData(23, 23);
	m_comboCHN.InsertString(24 , "ÉÂ");
	m_comboCHN.SetItemData(24, 24);
	m_comboCHN.InsertString(25 , "»¦");
	m_comboCHN.SetItemData(25, 25);
	m_comboCHN.InsertString(26 , "´¨");
	m_comboCHN.SetItemData(26, 26);
	m_comboCHN.InsertString(27 , "Ì¨");
	m_comboCHN.SetItemData(27, 27);
	m_comboCHN.InsertString(28 , "½ò");
	m_comboCHN.SetItemData(28, 28);
	m_comboCHN.InsertString(29 , "²Ø");
	m_comboCHN.SetItemData(29, 29);
	m_comboCHN.InsertString(30 , "¸Û");
	m_comboCHN.SetItemData(30, 30);
	m_comboCHN.InsertString(31 , "ÐÂ");
	m_comboCHN.SetItemData(31, 31);
	m_comboCHN.InsertString(32 , "ÔÆ");
	m_comboCHN.SetItemData(32, 32);
	m_comboCHN.InsertString(33 , "Õã");
	m_comboCHN.SetItemData(33, 33);
	
	m_comboVehiclePeccType.SetItemData(0, 1349);
	m_comboVehiclePeccType.SetItemData(1, 1355);
	m_comboVehiclePeccType.SetItemData(2, 1625);
	m_comboVehiclePeccType.SetItemData(3, 1717);
	m_comboVehiclePeccType.SetItemData(4, 1718);
	m_comboVehiclePeccType.SetItemData(5, 5056);
	m_comboVehiclePeccType.SetItemData(6, 6022);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVehicleMvaCfg::OnBtnSetCapCfg() 
{
	UpdateData(TRUE);
	memset(&m_struCapCfg, 0, sizeof(NET_DVR_MOBILE_CAPTUREPIC_CFG));
	m_struCapCfg.dwSize = sizeof(NET_DVR_MOBILE_CAPTUREPIC_CFG);
	m_struCapCfg.byPreviewFpsAdjMode = m_comboCapFpsAdjType.GetCurSel();
	m_struCapCfg.bySelPeccType = m_bCapPeccType;
	m_struCapCfg.byOptHabit = m_comboCapOptHabit.GetCurSel();
	m_struCapCfg.byEnablePeccRec = m_bCapPeccCap;
	m_struCapCfg.byPicSize = m_comboCapPicSize.GetCurSel();
	m_struCapCfg.byPicQuality = m_comboCapPicQuality.GetCurSel();

	if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_CAPTUREPIC_CFG, m_lChannal, &m_struCapCfg, sizeof(NET_DVR_MOBILE_CAPTUREPIC_CFG)))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CAPTUREPIC_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CAPTUREPIC_CFG");
        return;
    }
	
}

void CDlgVehicleMvaCfg::OnBtnGetCapCfg() 
{
	DWORD dwReturn = 0;
	memset(&m_struCapCfg, 0, sizeof(NET_DVR_MOBILE_CAPTUREPIC_CFG));
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_CAPTUREPIC_CFG, m_lChannal, &m_struCapCfg, sizeof(NET_DVR_MOBILE_CAPTUREPIC_CFG), &dwReturn))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMDIALMODECFG");
		m_comboCapFpsAdjType.SetCurSel(m_struCapCfg.byPreviewFpsAdjMode);
		m_bCapPeccType = m_struCapCfg.bySelPeccType;
		m_comboCapOptHabit.SetCurSel(m_struCapCfg.byOptHabit);
		m_bCapPeccCap = m_struCapCfg.byEnablePeccRec;
		m_comboCapPicSize.SetCurSel(m_struCapCfg.byPicSize);
		m_comboCapPicQuality.SetCurSel(m_struCapCfg.byPicQuality); 
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMDIALMODECFG");
        return;
    }
	UpdateData(FALSE);
}

void CDlgVehicleMvaCfg::OnBtnSetPlateRecgCfg() 
{
	UpdateData(TRUE);
	memset(&m_struPlateRecg, 0, sizeof(NET_DVR_MOBILE_PLATE_RECOGCFG));
	
	m_struPlateRecg.dwSize = sizeof(NET_DVR_MOBILE_PLATE_RECOGCFG);
//	sprintf(m_struPlateRecg.byDefaultCHN, "%s", m_comboPlateCHN.GetItemData(m_comboPlateCHN.GetCurSel()));

	m_struPlateRecg.byTimeOsd = m_bPlateTimeOverlay;
	m_struPlateRecg.byRecogResultOsd = m_bPlateResultOverlay;
	m_struPlateRecg.byRecogHint = m_bPlateHintOverlay;
	m_struPlateRecg.byRecogDir = m_comboPlateDir.GetCurSel();
	m_struPlateRecg.byRecogEnv = m_comboPlateEnvir.GetCurSel();
	m_struPlateRecg.byRecogPlateType = m_comboPlateType.GetCurSel();
	m_struPlateRecg.byUploadPlate = m_bPlateUpload;
	
	if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_MOBILEPLATE_RECOG_CFG, m_lChannal, &m_struPlateRecg, sizeof(NET_DVR_MOBILE_PLATE_RECOGCFG)))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MOBILEPLATE_RECOG_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MOBILEPLATE_RECOG_CFG");
        return;
    }
	
}

void CDlgVehicleMvaCfg::OnBtnGetPlateRecgCfg() 
{
	DWORD dwReturn = 0;
	CString csDefaultChn;
	int i, j;
	memset(&m_struPlateRecg, 0, sizeof(NET_DVR_MOBILE_PLATE_RECOGCFG));
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_MOBILEPLATE_RECOG_CFG, m_lChannal, &m_struPlateRecg, sizeof(NET_DVR_MOBILE_PLATE_RECOGCFG), &dwReturn))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_MOBILEPLATE_RECOG_CFG");
		for (i = 0; i < m_comboCHN.GetCount(); i++)
		{
			m_comboCHN.GetLBText(i, csDefaultChn);
			for (j = 0; j < MAX_CHJC_NUM; j++)
			{
				if (m_struPlateRecg.byDefaultCHN[j] != csDefaultChn[j])
				{
					break;
				}
			}
			if (j == MAX_CHJC_NUM)
			{
				m_comboCHN.SetCurSel(i);
				break;
			}
			
		}
		m_bPlateTimeOverlay = m_struPlateRecg.byTimeOsd;
		m_bPlateResultOverlay = m_struPlateRecg.byRecogResultOsd;
		m_bPlateHintOverlay = m_struPlateRecg.byRecogHint;
		m_comboPlateDir.SetCurSel(m_struPlateRecg.byRecogDir);
		m_comboPlateEnvir.SetCurSel(m_struPlateRecg.byRecogEnv);
		m_comboPlateType.SetCurSel(m_struPlateRecg.byRecogPlateType);
		m_bPlateUpload = m_struPlateRecg.byUploadPlate;
	
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_MOBILEPLATE_RECOG_CFG");
        return;
    }
	UpdateData(FALSE);
	
}

void CDlgVehicleMvaCfg::OnBtnSetRadarCfg() 
{
	UpdateData(TRUE);
	memset(&m_struRadarCfg, 0, sizeof(NET_DVR_MOBILE_RADAR_CFG));
	m_struRadarCfg.dwSize = sizeof(NET_DVR_MOBILE_RADAR_CFG);
	m_struRadarCfg.byEnableRadar = m_bRadarEnable;
	m_struRadarCfg.byEnableAlarm = m_bRadarAlarm;
	m_struRadarCfg.wOverSpeed = m_wRadarOverSpeed;
	m_struRadarCfg.bySpeedUnits = m_comboRadarSpeedUnit.GetCurSel();
	m_struRadarCfg.bydirection = m_comboRadarDir.GetCurSel();
	m_struRadarCfg.byMeasureMode = m_comboRadarStatus.GetCurSel();
	m_struRadarCfg.byTargetType = m_comboRadarTargetType.GetCurSel();
	m_struRadarCfg.bySensitivity = m_byRadarSensitivity;
	m_struRadarCfg.byCaptureNum = m_byRadarCapNum;
	m_struRadarCfg.byUploadPlate = m_bRadarUpload;
	
	if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_MOBILE_RADAR_CFG, m_lChannal, &m_struRadarCfg, sizeof(NET_DVR_MOBILE_RADAR_CFG)))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MOBILE_RADAR_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MOBILE_RADAR_CFG");
        return;
    }
	
}

void CDlgVehicleMvaCfg::OnBtnGetRadarCfg() 
{
	DWORD dwReturn = 0;
	memset(&m_struRadarCfg, 0, sizeof(NET_DVR_MOBILE_RADAR_CFG));
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_MOBILE_RADAR_CFG, m_lChannal, &m_struRadarCfg, sizeof(NET_DVR_MOBILE_RADAR_CFG), &dwReturn))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_MOBILE_RADAR_CFG");
		
		m_bRadarEnable = m_struRadarCfg.byEnableRadar;
		m_bRadarAlarm = m_struRadarCfg.byEnableAlarm;
		m_wRadarOverSpeed = m_struRadarCfg.wOverSpeed;
		m_comboRadarSpeedUnit.SetCurSel(m_struRadarCfg.bySpeedUnits);
		m_comboRadarDir.SetCurSel(m_struRadarCfg.bydirection);
		m_comboRadarStatus.SetCurSel(m_struRadarCfg.byMeasureMode);
		m_comboRadarTargetType.SetCurSel(m_struRadarCfg.byTargetType);
		m_byRadarSensitivity = m_struRadarCfg.bySensitivity;
		m_byRadarCapNum = m_struRadarCfg.byCaptureNum;
		m_bRadarUpload = m_struRadarCfg.byUploadPlate;	
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_MOBILE_RADAR_CFG");
        return;
    }
	UpdateData(FALSE);
	
}

void CDlgVehicleMvaCfg::OnBtnSetBlackListCfg() 
{
	UpdateData(TRUE);
	memset(&m_struBlackListCfg, 0, sizeof(NET_DVR_MOBILE_LOCALPLATECHK_CFG));
	m_struBlackListCfg.dwSize = sizeof(NET_DVR_MOBILE_LOCALPLATECHK_CFG);
	m_struBlackListCfg.byCheck = m_bBlackListCheck;
	m_struBlackListCfg.byCheckAlarm = m_bBlackListAlarm;
	m_struBlackListCfg.byCheckHint = m_bBlackListHint;
	m_struBlackListCfg.byUploadBlackCar = m_bBlackListUpload;
	
	if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_MOBILE_LOCALPLATECHK_CFG, m_lChannal, &m_struBlackListCfg, sizeof(NET_DVR_MOBILE_LOCALPLATECHK_CFG)))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MOBILE_LOCALPLATECHK_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MOBILE_LOCALPLATECHK_CFG");
        return;
    }
	
}

void CDlgVehicleMvaCfg::OnBtnGetBlackListCfg() 
{
	DWORD dwReturn = 0;
	memset(&m_struBlackListCfg, 0, sizeof(NET_DVR_MOBILE_LOCALPLATECHK_CFG));
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_MOBILE_LOCALPLATECHK_CFG, m_lChannal, &m_struBlackListCfg, sizeof(NET_DVR_MOBILE_LOCALPLATECHK_CFG), &dwReturn))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_MOBILE_LOCALPLATECHK_CFG");
		
		m_bBlackListCheck = m_struBlackListCfg.byCheck;
		m_bBlackListAlarm = m_struBlackListCfg.byCheckAlarm;
		m_bBlackListHint = m_struBlackListCfg.byCheckHint;
		m_bBlackListUpload = m_struBlackListCfg.byUploadBlackCar;
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_MOBILE_LOCALPLATECHK_CFG");
        return;
    }
	UpdateData(FALSE);
	
}

short g_stime = 0;

void CALLBACK g_fTransBlackListDataCallBack(DWORD dwType, void *pRecvDataBuffer, DWORD dwBufSize, void* pUserData)
{
	CDlgVehicleMvaCfg *pThis = (CDlgVehicleMvaCfg*)pUserData;
	switch (dwType)
	{

	case NET_SDK_CALLBACK_STATUS_FAILED:
		g_pMainDlg->AddLog(pThis->m_dwDevIndex, OPERATION_FAIL_T, "Send Black list info");
	case NET_SDK_CALLBACK_STATUS_SUCCESS:
		if (g_stime > 0)
		{
			if (!NET_DVR_SendRemoteConfig(pThis->m_lTranHandle, ENUM_DVR_VEHICLE_CHECK, (char *)(&pThis->m_struVehicleCheckData), sizeof(NET_DVR_VEHICLE_CHECK)))
			{
				g_pMainDlg->AddLog(pThis->m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SendRemoteConfig");
			}
			g_stime--;
		}
		else
		{
			if (!NET_DVR_StopRemoteConfig(pThis->m_lTranHandle))
			{
				g_pMainDlg->AddLog(pThis->m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig");
				return;
			}
		}
		
		break;
	default:
		break;
		
	}

}

void CDlgVehicleMvaCfg::OnBtnVehicleDataSend() 
{
	UpdateData(TRUE);
	g_stime = m_wSendTime;
	memset(&m_struVehicleCheckData, 0, sizeof(NET_DVR_VEHICLE_CHECK));
	m_struVehicleCheckData.dwSize = sizeof(NET_DVR_VEHICLE_CHECK);
	m_struVehicleCheckData.dwChannel = m_dwVehicleChannal;
	m_struVehicleCheckData.struPlateInfo.byPlateType = m_comboVehiclePlateType.GetCurSel();
	m_struVehicleCheckData.struPlateInfo.byColor = m_comboVehiclePlateColor.GetCurSel();
	m_struVehicleCheckData.struPlateInfo.byBright = m_byVehicleBright;
	m_struVehicleCheckData.struPlateInfo.byLicenseLen = m_byVehicleCharNum;
	m_struVehicleCheckData.struPlateInfo.byEntireBelieve = m_byVehicleBelive;
	m_struVehicleCheckData.struPlateInfo.struPlateRect.fX = m_fVehicleRectX;
	m_struVehicleCheckData.struPlateInfo.struPlateRect.fY = m_fVehicleRectY;
	m_struVehicleCheckData.struPlateInfo.struPlateRect.fWidth = m_fVehicleRectWidth;
	m_struVehicleCheckData.struPlateInfo.struPlateRect.fHeight = m_fVehicleRectHight;
	sprintf(m_struVehicleCheckData.struPlateInfo.sLicense, "%s", m_strVehiclePlateNumber);
	

	m_struVehicleCheckData.struPlateInfo.byBelieve[0] = m_byVehicleBelive1;
	m_struVehicleCheckData.struPlateInfo.byBelieve[1] = m_byVehicleBelive2;
	m_struVehicleCheckData.struPlateInfo.byBelieve[2] = m_byVehicleBelive3;
	m_struVehicleCheckData.struPlateInfo.byBelieve[3] = m_byVehicleBelive4;
	m_struVehicleCheckData.struPlateInfo.byBelieve[4] = m_byVehicleBelive5;
	m_struVehicleCheckData.struPlateInfo.byBelieve[5] = m_byVehicleBelive6;
	m_struVehicleCheckData.struPlateInfo.byBelieve[6] = m_byVehicleBelive7;
	m_struVehicleCheckData.struPlateInfo.byBelieve[7] = m_byVehicleBelive8;
	m_struVehicleCheckData.struPlateInfo.byBelieve[8] = m_byVehicleBelive9;
	m_struVehicleCheckData.struPlateInfo.byBelieve[9] = m_byVehicleBelive10;
	m_struVehicleCheckData.struPlateInfo.byBelieve[10] = m_byVehicleBelive11;
	m_struVehicleCheckData.struPlateInfo.byBelieve[11] = m_byVehicleBelive12;
	m_struVehicleCheckData.struPlateInfo.byBelieve[12] = m_byVehicleBelive13;
	m_struVehicleCheckData.struPlateInfo.byBelieve[13] = m_byVehicleBelive14;
	m_struVehicleCheckData.struPlateInfo.byBelieve[14] = m_byVehicleBelive15;
	m_struVehicleCheckData.struPlateInfo.byBelieve[15] = m_byVehicleBelive16;
	
	m_struVehicleCheckData.wIllegalType = m_comboVehiclePeccType.GetItemData(m_comboVehiclePeccType.GetCurSel());
	sprintf(m_struVehicleCheckData.sIllegalTypeInfo, "%s", m_strVehiclePeccInfo);
	m_struVehicleCheckData.struIllegalTime.wYear = m_wTimeYear;
	m_struVehicleCheckData.struIllegalTime.byMonth = m_byTimeMonth;
	m_struVehicleCheckData.struIllegalTime.byDay = m_byTimeDay;
	m_struVehicleCheckData.struIllegalTime.byHour = m_byTimeHour;
	m_struVehicleCheckData.struIllegalTime.byMinute = m_byTimeMin;
	m_struVehicleCheckData.struIllegalTime.bySecond = m_byTimeSec;
	m_struVehicleCheckData.struIllegalTime.wMilliSec = m_wTimeMsec;
	m_struVehicleCheckData.byIllegalVehicleNum = m_byVehiclePeccNum;
	sprintf(m_struVehicleCheckData.sCustomInfo, "%s", m_strVehicleCustom);


	m_lTranHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_VEHICLE_CHECK_START, NULL, 0, g_fTransBlackListDataCallBack, this);
	if (m_lTranHandle  == -1)
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_StartRemoteConfig Failed!");
		AfxMessageBox("Start Direct Transmission Failed");
		return;
	}

	g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_StartRemoteConfig Success!");
	MessageBox("success to start!");
	
	if (!NET_DVR_SendRemoteConfig(m_lTranHandle, ENUM_DVR_VEHICLE_CHECK, (char *)(&m_struVehicleCheckData), sizeof(NET_DVR_VEHICLE_CHECK)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SendRemoteConfig");
	}
	
	g_stime--;
	return;
}

void CDlgVehicleMvaCfg::OnBtnSetTransParam() 
{
	UpdateData(TRUE);

	if (NET_DVR_SetTransparentParam(m_lServerID, (LPSTR)(LPCTSTR)m_strTransParam, m_strTransParam.GetLength()))
	{
		AfxMessageBox("set success!\n");
	}
	else
	{
		AfxMessageBox("set failed!\n");
	}
	
}

void CDlgVehicleMvaCfg::OnBtnGetTransParam() 
{
	char Tmp[100];
	if (NET_DVR_GetTransparentParam(m_lServerID, NULL, 0, Tmp, 100))
	{
		AfxMessageBox("Get success!\n");
		m_strTransParam.Format("%s", Tmp);
		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox("Get failed!\n");
	}	
}
