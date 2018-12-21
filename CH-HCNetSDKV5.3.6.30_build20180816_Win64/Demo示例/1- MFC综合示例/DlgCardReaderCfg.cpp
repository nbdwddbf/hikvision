// DlgCardReaderCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCardReaderCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCardReaderCfg dialog


CDlgCardReaderCfg::CDlgCardReaderCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCardReaderCfg::IDD, pParent)
    ,m_iUserID(0)
    ,m_iDeviceID(0)
    , m_iLocalControllerID(0)
    , m_iLocalControllerReaderID(0)
    , m_bUseLocalController(FALSE)
    , m_byLiveDetAntiAttackCntLimit(0)
    , m_dwFpCapicity(0)
    , m_dwFpNum(0)
    , m_bIsSupport(FALSE)
    , m_dwBlackListThreshold(0)
{
	//{{AFX_DATA_INIT(CDlgCardReaderCfg)
	m_BEnable = FALSE;
    m_BFingerPrint = FALSE;
    m_BFace = FALSE;
    m_BVena = FALSE;
	m_BEnableFailAlarm = FALSE;
	m_dwCardReaderNo = 1;
	m_dwSwipeInterval = 0;
	m_dwPressTimeOut = 0;
	m_dwMaxReadCardFailNum = 0;
	m_BEnableTamperCheck = FALSE;
	m_dwOfflineCheckTime = 0;
    m_byFingerPrintCheckLevel=0;
    m_byFaceContrastThreshold = 0;
    m_byFaceContrastThreshold2 = 0;
    m_byDayFaceMatchThresholdN = 0;
    m_byNightFaceMatchThresholdN = 0;
    m_byFaceQuality = 0;
    m_wFaceImageSensitometry = 0;
    m_csCardReaderDescription = _T("");
    m_dwBuzzerTime = 0;
	//}}AFX_DATA_INIT
}


void CDlgCardReaderCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgCardReaderCfg)
    DDX_Control(pDX, IDC_COMB_AC_CREADER_TYPE, m_cmbType);
    DDX_Control(pDX, IDC_COMB_AC_CREADER_BUZZERPOLARITY, m_cmbBuzzerPolarity);
    DDX_Control(pDX, IDC_COMB_AC_CREADER_ERRORLED, m_cmbErrorLed);
    DDX_Control(pDX, IDC_COMB_AC_CREADER_OKLED, m_cmbOKLed);
    DDX_Control(pDX, IDC_CMB_FP_IMAGE_QUALITY, m_cmbFPImageQuality);
    DDX_Control(pDX, IDC_CMB_FP_CONTRAST_TIME_OUT, m_cmbFPContrastTimeOut);
    DDX_Control(pDX, IDC_CMB_FP_RECOGIZE_INTERVAL, m_cmbFPRecogizeInterval);
    DDX_Control(pDX, IDC_CMB_FP_MATCH_FAST_MODE, m_cmbFPMatchFastMode);
    DDX_Control(pDX, IDC_CMB_FP_MODULE_SENSITIVE, m_cmbFPModuleSensitive);
    DDX_Control(pDX, IDC_CMB_FP_MODULE_LIGHT_CONDITION, m_cmbFPModuleLightCondition);
    DDX_Control(pDX, IDC_CMB_FACE_RECOGIZE_TIME_OUT, m_cmbFaceRecogizeTimeOut);
    DDX_Control(pDX, IDC_CMB_FACE_RECOGIZE_INTERVAL, m_cmbFaceRecogizeInterval);
    DDX_Control(pDX, IDC_CMB_LIVING_BODY_DETECT, m_cmbLivingBodyDetect);
    DDX_Control(pDX, IDC_CMB_FACE_RECOGIZE_ENABLE, m_cmbFaceRecogizeEnable);
    DDX_Text(pDX, IDC_EDIT_FACE_CONTRAST_THRESHOLD, m_byFaceContrastThreshold);
    DDX_Text(pDX, IDC_EDIT_FACE_CONTRAST_THRESHOLD2, m_byFaceContrastThreshold2);
    DDX_Text(pDX, IDC_EDIT_DAY_FACE_CONTRAST_THRESHOLD, m_byDayFaceMatchThresholdN);
    DDX_Text(pDX, IDC_EDIT_NIGHT_FACE_CONTRAST_THRESHOLD, m_byNightFaceMatchThresholdN);
    DDX_Text(pDX, IDC_EDIT_FACE_QUALITY, m_byFaceQuality);
    DDX_Text(pDX, IDC_EDIT_FACE_IMAGE_SENSITOMETRY, m_wFaceImageSensitometry);
    DDX_Text(pDX, IDC_EDIT_CARD_READER_DESCRIPTION, m_csCardReaderDescription);
    DDX_Check(pDX, IDC_CHK_AC_READER_ENABLE, m_BEnable);
    DDX_Check(pDX, IDC_CHK_AC_FINGER_PRINT, m_BFingerPrint);
    DDX_Check(pDX, IDC_CHK_AC_FACE, m_BFace);
    DDX_Check(pDX, IDC_CHK_AC_VENA, m_BVena);
    DDX_Check(pDX, IDC_CHK_AC_READER_ENABLEFAILALARM, m_BEnableFailAlarm);
    DDX_Text(pDX, IDC_EDT_AC_CARDERCFG_NO, m_dwCardReaderNo);
    DDX_Text(pDX, IDC_EDT_AC_CARDERCFG_SWIPEINTERVAL, m_dwSwipeInterval);
    DDX_Text(pDX, IDC_EDT_AC_CARDERCFG_PRESSTIMEOUT, m_dwPressTimeOut);
    DDX_Text(pDX, IDC_EDT_AC_CARDERCFG_MAXREADCARDFAILNUM, m_dwMaxReadCardFailNum);
    DDX_Check(pDX, IDC_CHK_AC_READER_ENABLETAMPERCHECK, m_BEnableTamperCheck);
    DDX_Text(pDX, IDC_EDT_AC_OFFLINE_CHECKTIME, m_dwOfflineCheckTime);
    DDX_Text(pDX, IDC_EDIT_CHECK_LEVEL, m_byFingerPrintCheckLevel);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMB_AC_CARDREADER_CHANNEL, m_cmbCardReaderChannel);
    DDX_Text(pDX, IDC_EDT_ACDC_LOCALCONTROLLERID, m_iLocalControllerID);
    DDX_Text(pDX, IDC_EDT_ACDC_LOCALCONTROLLER_READERID, m_iLocalControllerReaderID);
    DDX_Check(pDX, IDC_CHK_ACDC_USELOCALCONTROLLER, m_bUseLocalController);
    DDX_Text(pDX, IDC_EDIT_BUZZER_TIME, m_dwBuzzerTime);
    DDX_Control(pDX, IDC_CMB_FACE_RECOGIZE_SECURITY_1V1, m_cmbSecurityLevel1);
    DDX_Control(pDX, IDC_CMB_FACE_RECOGIZE_SECURITY_1VN, m_cmbSecurityLevelN);
    DDX_Text(pDX, IDC_EDIT_FACE_ANTIATTACK_TIMES_LIMIT, m_byLiveDetAntiAttackCntLimit);
    DDX_Control(pDX, IDC_CMB_LIVING_BODY_DETECT_THRESHOLD, m_cmbLiveDetLevelSet);
    DDX_Control(pDX, IDC_CMB_FACE_RECONG_CONDITON, m_cmbEnvirMode);
    DDX_Control(pDX, IDC_CMB_LIVING_BODY_DETECT_THRESHOLD2, m_cmbEnableAntiAttackProtect);
    DDX_Control(pDX, IDC_CMB_LIVE_DET_LEVEL, m_cmbLiveDetLevel);
    DDX_Control(pDX, IDC_CMB_FACE_CONTRAST_MOTION_DET_LEVEL, m_cmbFaceContrastMotionDetLevel);
    DDX_Text(pDX, IDC_EDIT_FP_CAPACITY, m_dwFpCapicity);
    DDX_Text(pDX, IDC_EDIT_FP_NUM, m_dwFpNum);
    DDX_Check(pDX, IDC_CHECK1, m_bIsSupport);
    DDX_Text(pDX, IDC_EDIT_BLACK_FACE_CONTRAST_THRESHOLD, m_dwBlackListThreshold);
}


BEGIN_MESSAGE_MAP(CDlgCardReaderCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgCardReaderCfg)
	ON_BN_CLICKED(IDC_BUT_AC_CARDREADERCFG_GET, OnButGet)
	ON_BN_CLICKED(IDC_BUT_AC_CARDREADERCFG_SET, OnButSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCardReaderCfg message handlers

void CDlgCardReaderCfg::OnButGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    NET_DVR_CARD_READER_CFG_V50 struReaderCfg = {0}; 
    DWORD dwRet; 
    if ( !NET_DVR_GetDVRConfig(m_iUserID, NET_DVR_GET_CARD_READER_CFG_V50, m_dwCardReaderNo, &struReaderCfg, sizeof(struReaderCfg),  &dwRet))
    {
        g_pMainDlg->AddLog(m_iDeviceID, OPERATION_FAIL_T, "NET_DVR_GET_CARD_READER_CFG_V50");
        MessageBox("NET_DVR_GET_CARD_READER_CFG_V50 Fail"); 
        return ; 
    }
    g_pMainDlg->AddLog(m_iDeviceID, OPERATION_SUCC_T, "NET_DVR_GET_CARD_READER_CFG_V50");
    m_BEnable = struReaderCfg.byEnable; 
    m_BEnableFailAlarm = struReaderCfg.byEnableFailAlarm; 
    m_cmbType.SetCurSel(struReaderCfg.byCardReaderType);
    m_cmbOKLed.SetCurSel(struReaderCfg.byOkLedPolarity); 
    m_cmbErrorLed.SetCurSel(struReaderCfg.byErrorLedPolarity); 
    m_cmbBuzzerPolarity.SetCurSel(struReaderCfg.byBuzzerPolarity); 
    m_dwSwipeInterval = struReaderCfg.bySwipeInterval; 
    m_dwPressTimeOut = struReaderCfg.byPressTimeout; 
    m_dwMaxReadCardFailNum = struReaderCfg.byMaxReadCardFailNum; 
    m_BEnableTamperCheck = struReaderCfg.byEnableTamperCheck; 
    m_dwOfflineCheckTime = struReaderCfg.byOfflineCheckTime; 
    m_byFingerPrintCheckLevel = struReaderCfg.byFingerPrintCheckLevel;

    m_cmbSecurityLevel1.SetCurSel(struReaderCfg.byFaceMatch1SecurityLevel);
    m_cmbSecurityLevelN.SetCurSel(struReaderCfg.byFaceMatchNSecurityLevel);
    m_cmbLiveDetLevelSet.SetCurSel(struReaderCfg.byLiveDetLevelSet);
    m_cmbEnvirMode.SetCurSel(struReaderCfg.byEnvirMode);
    m_byLiveDetAntiAttackCntLimit = struReaderCfg.byLiveDetAntiAttackCntLimit;
    m_cmbEnableAntiAttackProtect.SetCurSel(struReaderCfg.byEnableLiveDetAntiAttack);

    m_bUseLocalController = struReaderCfg.byUseLocalController;
    m_iLocalControllerID = struReaderCfg.wLocalControllerID;
    m_iLocalControllerReaderID = struReaderCfg.wLocalControllerReaderID;
    m_cmbCardReaderChannel.SetCurSel(struReaderCfg.wCardReaderChannel);

    m_cmbFPImageQuality.SetCurSel(struReaderCfg.byFingerPrintImageQuality);
    //21代表发送的为0xff
    if (struReaderCfg.byFingerPrintContrastTimeOut != 0xff)
    {
        m_cmbFPContrastTimeOut.SetCurSel(struReaderCfg.byFingerPrintContrastTimeOut);
    }
    else
    {
        m_cmbFPContrastTimeOut.SetCurSel(21);
    }
    //11代表发送的为0xff
    if (struReaderCfg.byFingerPrintRecogizeInterval != 0xff)
    {
        m_cmbFPRecogizeInterval.SetCurSel(struReaderCfg.byFingerPrintRecogizeInterval);
    }
    else
    {
        m_cmbFPRecogizeInterval.SetCurSel(11);
    }
    //6代表发送的为0xff
    if (struReaderCfg.byFingerPrintMatchFastMode != 0xff)
    {
        m_cmbFPMatchFastMode.SetCurSel(struReaderCfg.byFingerPrintMatchFastMode);
    }
    else
    {
        m_cmbFPMatchFastMode.SetCurSel(6);
    }
    m_cmbFPModuleSensitive.SetCurSel(struReaderCfg.byFingerPrintModuleSensitive);
    m_cmbFPModuleLightCondition.SetCurSel(struReaderCfg.byFingerPrintModuleLightCondition);
    m_byFaceContrastThreshold = struReaderCfg.byFaceMatchThresholdN;
    m_byFaceContrastThreshold2 = struReaderCfg.byFaceMatchThreshold1;
    m_byDayFaceMatchThresholdN = struReaderCfg.byDayFaceMatchThresholdN;
    m_byNightFaceMatchThresholdN = struReaderCfg.byNightFaceMatchThresholdN;
    m_byFaceQuality = struReaderCfg.byFaceQuality;
    //21代表发送的为0xff
    if (struReaderCfg.byFaceRecogizeTimeOut != 0xff)
    {
        m_cmbFaceRecogizeTimeOut.SetCurSel(struReaderCfg.byFaceRecogizeTimeOut);
    }
    else
    {
        m_cmbFaceRecogizeTimeOut.SetCurSel(21);
    }
    //11代表发送的为0xff
    if (struReaderCfg.byFaceRecogizeInterval != 0xff)
    {
        m_cmbFaceRecogizeInterval.SetCurSel(struReaderCfg.byFaceRecogizeInterval);
    }
    else
    {
        m_cmbFaceRecogizeInterval.SetCurSel(11);
    }
    m_csCardReaderDescription = struReaderCfg.byCardReaderDescription;
    m_wFaceImageSensitometry = struReaderCfg.wFaceImageSensitometry;
    m_cmbLivingBodyDetect.SetCurSel(struReaderCfg.byLivingBodyDetect);
    m_cmbFaceRecogizeEnable.SetCurSel(struReaderCfg.byFaceRecogizeEnable);
    if ((struReaderCfg.wCardReaderFunction & 0x01) == 0x01)
    {
        m_BFingerPrint = TRUE;
    }
    else
    {
        m_BFingerPrint = FALSE;
    }
    if ((struReaderCfg.wCardReaderFunction & 0x02) == 0x02)
    {
        m_BFace = TRUE;
    }
    else
    {
        m_BFace = FALSE;
    }
    if ((struReaderCfg.wCardReaderFunction & 0x04) == 0x04)
    {
        m_BVena = TRUE;
    }
    else
    {
        m_BVena = FALSE;
    }
    m_dwBuzzerTime = struReaderCfg.wBuzzerTime;
    //m_cmbLiveDetLevel.SetCurSel(struReaderCfg.byLiveDetLevel);
    m_cmbFaceContrastMotionDetLevel.SetCurSel(struReaderCfg.byFaceContrastMotionDetLevel);
    m_bIsSupport = struReaderCfg.byEnableFingerPrintNum;
    m_dwFpCapicity = struReaderCfg.dwFingerPrintCapacity;
    m_dwFpNum = struReaderCfg.dwFingerPrintNum;
    m_dwBlackListThreshold = struReaderCfg.byBlackFaceMatchThreshold;
	UpdateData(FALSE); 
}

void CDlgCardReaderCfg::OnButSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    NET_DVR_CARD_READER_CFG_V50 struReaderCfg = {0}; 
    struReaderCfg.dwSize = sizeof(struReaderCfg);
    struReaderCfg.byEnable = m_BEnable;
    struReaderCfg.byEnableFailAlarm = m_BEnableFailAlarm;
    struReaderCfg.byCardReaderType = m_cmbType.GetCurSel();
    struReaderCfg.byOkLedPolarity = m_cmbOKLed.GetCurSel(); 
    struReaderCfg.byErrorLedPolarity = m_cmbErrorLed.GetCurSel(); 
    struReaderCfg.byBuzzerPolarity = m_cmbBuzzerPolarity.GetCurSel(); 
    struReaderCfg.bySwipeInterval = (BYTE) m_dwSwipeInterval; 
    struReaderCfg.byPressTimeout = (BYTE) m_dwPressTimeOut;
    struReaderCfg.byMaxReadCardFailNum = (BYTE)m_dwMaxReadCardFailNum;
    struReaderCfg.byEnableTamperCheck = m_BEnableTamperCheck; 
    struReaderCfg.byOfflineCheckTime = (BYTE)m_dwOfflineCheckTime; 
    struReaderCfg.byFingerPrintCheckLevel = (BYTE)m_byFingerPrintCheckLevel; 

    struReaderCfg.byFaceMatch1SecurityLevel = m_cmbSecurityLevel1.GetCurSel();
    struReaderCfg.byFaceMatchNSecurityLevel = m_cmbSecurityLevelN.GetCurSel();
    struReaderCfg.byLiveDetLevelSet = m_cmbLiveDetLevelSet.GetCurSel();
    struReaderCfg.byEnvirMode = m_cmbEnvirMode.GetCurSel();
    struReaderCfg.byLiveDetAntiAttackCntLimit = m_byLiveDetAntiAttackCntLimit;
    struReaderCfg.byEnableLiveDetAntiAttack = m_cmbEnableAntiAttackProtect.GetCurSel();

    struReaderCfg.byUseLocalController = m_bUseLocalController;
    struReaderCfg.wLocalControllerID = m_iLocalControllerID;
    struReaderCfg.wLocalControllerReaderID = m_iLocalControllerReaderID;
    struReaderCfg.wCardReaderChannel = m_cmbCardReaderChannel.GetCurSel();

    struReaderCfg.byFingerPrintImageQuality = m_cmbFPImageQuality.GetCurSel();
    //21代表接收的为0xff
    if (m_cmbFPContrastTimeOut.GetCurSel() == 21)
    {
        struReaderCfg.byFingerPrintContrastTimeOut = 0xff;
    }
    else
    {
        struReaderCfg.byFingerPrintContrastTimeOut = m_cmbFPContrastTimeOut.GetCurSel();
    }
    //11代表接收的为0xff
    if (m_cmbFPRecogizeInterval.GetCurSel() == 11)
    {
        struReaderCfg.byFingerPrintRecogizeInterval = 0xff;
    }
    else
    {
        struReaderCfg.byFingerPrintRecogizeInterval = m_cmbFPRecogizeInterval.GetCurSel();
    }
    //6代表接收的为0xff
    if (m_cmbFPMatchFastMode.GetCurSel() == 6)
    {
        struReaderCfg.byFingerPrintMatchFastMode = 0xff;
    }
    else
    {
        struReaderCfg.byFingerPrintMatchFastMode = m_cmbFPMatchFastMode.GetCurSel();
    }
    struReaderCfg.byFingerPrintModuleSensitive = m_cmbFPModuleSensitive.GetCurSel();
    struReaderCfg.byFingerPrintModuleLightCondition = m_cmbFPModuleLightCondition.GetCurSel();
    struReaderCfg.byFaceMatchThresholdN = (BYTE)m_byFaceContrastThreshold;
    struReaderCfg.byFaceMatchThreshold1 = (BYTE)m_byFaceContrastThreshold2;
    struReaderCfg.byDayFaceMatchThresholdN = (BYTE)m_byDayFaceMatchThresholdN;
    struReaderCfg.byNightFaceMatchThresholdN = (BYTE)m_byNightFaceMatchThresholdN;
    struReaderCfg.byFaceQuality = (BYTE)m_byFaceQuality;
    struReaderCfg.wBuzzerTime = (WORD)m_dwBuzzerTime;
    //21代表接收的为0xff
    if (m_cmbFaceRecogizeTimeOut.GetCurSel() == 21)
    {
        struReaderCfg.byFaceRecogizeTimeOut = 0xff;
    }
    else
    {
        struReaderCfg.byFaceRecogizeTimeOut = m_cmbFaceRecogizeTimeOut.GetCurSel();
    }
    //11代表接收的为0xff
    if (m_cmbFaceRecogizeInterval.GetCurSel() == 11)
    {
        struReaderCfg.byFaceRecogizeInterval = 0xff;
    }
    else
    {
        struReaderCfg.byFaceRecogizeInterval = m_cmbFaceRecogizeInterval.GetCurSel();
    }
    struReaderCfg.wFaceImageSensitometry = (WORD)m_wFaceImageSensitometry;
    struReaderCfg.byLivingBodyDetect = m_cmbLivingBodyDetect.GetCurSel();
    struReaderCfg.byFaceRecogizeEnable = m_cmbFaceRecogizeEnable.GetCurSel();
    //struReaderCfg.byLiveDetLevel = m_cmbLiveDetLevel.GetCurSel();
    struReaderCfg.byFaceContrastMotionDetLevel = m_cmbFaceContrastMotionDetLevel.GetCurSel();
    struReaderCfg.byBlackFaceMatchThreshold = (BYTE)m_dwBlackListThreshold;

    if (!NET_DVR_SetDVRConfig(m_iUserID, NET_DVR_SET_CARD_READER_CFG_V50, m_dwCardReaderNo, &struReaderCfg, sizeof(struReaderCfg)))
    {
        g_pMainDlg->AddLog(m_iDeviceID, OPERATION_FAIL_T, "NET_DVR_SET_CARD_READER_CFG_V50");
        MessageBox("NET_DVR_SET_CARD_READER_CFG_V50 Fail");
        return ; 
	}
    g_pMainDlg->AddLog(m_iDeviceID, OPERATION_SUCC_T, "NET_DVR_SET_CARD_READER_CFG_V50");
}

BOOL CDlgCardReaderCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_iDeviceID = g_pMainDlg->GetCurDeviceIndex(); 
    m_iUserID = g_struDeviceInfo[m_iDeviceID].lLoginID; 
	// TODO: Add extra initialization here

    m_cmbType.ResetContent();
    m_cmbType.InsertString(0,"cannot");
    m_cmbType.InsertString(1,"DS-K110XM/MK/C/CK");
    m_cmbType.InsertString(2,"DS-K192AM/AMP");
    m_cmbType.InsertString(3,"DS-K192BM/BMP");
    m_cmbType.InsertString(4,"DS-K182AM/AMP");
    m_cmbType.InsertString(5,"DS-K182BM/BMP");
    m_cmbType.InsertString(6,"DS-K182AMF/ACF");
    m_cmbType.InsertString(7,"Wiegand\485Offline");
    m_cmbType.InsertString(8,"DS-K1101M/MK");
    m_cmbType.InsertString(9,"DS-K1101C/CK");
    m_cmbType.InsertString(10,"DS-K1102M/MK/M-A");
    m_cmbType.InsertString(11,"DS-K1102C/CK");
    m_cmbType.InsertString(12,"DS-K1103M/MK");
    m_cmbType.InsertString(13,"DS-K1103C/CK");
    m_cmbType.InsertString(14,"DS-K1104M/MK");
    m_cmbType.InsertString(15,"DS-K1104C/CK");
    m_cmbType.InsertString(16,"DS-K1102S/SK/S-A");
    m_cmbType.InsertString(17,"DS-K1102G/GK");
    m_cmbType.InsertString(18,"DS-K1100S-B");
    m_cmbType.InsertString(19,"DS-K1102EM/EMK");
    m_cmbType.InsertString(20,"DS-K1102E/EK");
    m_cmbType.InsertString(21,"DS-K1200EF");
    m_cmbType.InsertString(22,"DS-K1200MF");
    m_cmbType.InsertString(23,"DS-K1200CF");
    m_cmbType.InsertString(24,"DS-K1300EF");
    m_cmbType.InsertString(25,"DS-K1300MF");
    m_cmbType.InsertString(26,"DS-K1300CF");
    m_cmbType.InsertString(27,"DS-K1105E");
    m_cmbType.InsertString(28,"DS-K1105M");
    m_cmbType.InsertString(29,"DS-K1105C");
    m_cmbType.InsertString(30,"DS-K182AMF");
    m_cmbType.InsertString(31,"DS-K196AMF");
    m_cmbType.InsertString(32,"DS-K194AMP");
    m_cmbType.InsertString(33,"DS-K1T200EF/EF-C/MF/MF-C/CF/CF-C");
    m_cmbType.InsertString(34,"DS-K1T300EF/EF-C/MF/MF-C/CF/CF-C");
    m_cmbType.InsertString(35,"DS-K1T105E/E-C/M/M-C/C/C-C");
    m_cmbType.InsertString(36, "DS-K1T803F/MF/SF/EF");
    m_cmbType.InsertString(37, "DS-K1A801F/MF/SF/EF");
    m_cmbType.InsertString(38, "DS-K1107M/MK");
    m_cmbType.InsertString(39, "DS-K1107E/EK");
    m_cmbType.InsertString(40, "DS-K1107S/SK");
    m_cmbType.InsertString(41, "DS-K1108M/MK");
    m_cmbType.InsertString(42, "DS-K1108E/EK");
    m_cmbType.InsertString(43, "DS-K1108S/SK");
    m_cmbType.InsertString(44, "DS-K1200F");
    m_cmbType.InsertString(45, "DS-K1S110-I");
    m_cmbType.InsertString(46, "DS-K1T200M-PG/PGC");
    m_cmbType.InsertString(47, "DS-K1T200M-PZ/PZC");
    m_cmbType.InsertString(48, "DS-K1109H");

	m_cmbType.SetCurSel(0);

    m_cmbCardReaderChannel.SetCurSel(0);
    m_cmbFPImageQuality.SetCurSel(0);
    m_cmbFPContrastTimeOut.SetCurSel(0);
    m_cmbFPRecogizeInterval.SetCurSel(0);
    m_cmbFPMatchFastMode.SetCurSel(0);
    m_cmbFPModuleSensitive.SetCurSel(0);
    m_cmbFPModuleLightCondition.SetCurSel(0);
    m_cmbFaceRecogizeTimeOut.SetCurSel(0);
    m_cmbFaceRecogizeInterval.SetCurSel(0);
    m_cmbLivingBodyDetect.SetCurSel(0);
    m_cmbFaceRecogizeEnable.SetCurSel(0);
    m_cmbLiveDetLevel.SetCurSel(0);
    m_cmbFaceContrastMotionDetLevel.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
