// DlgTmeCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTmeCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTmeCfg dialog
#define XML_ABILITY_OUT_LEN	3*1024*1024


CDlgTmeCfg::CDlgTmeCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTmeCfg::IDD, pParent)
    , m_csFilePath(_T(""))
    , m_csTMEVoiceFileName(_T(""))
    , m_iBroadcastNum(0)
    , m_iIntervalTime(0)
{
	//{{AFX_DATA_INIT(CDlgTmeCfg)
	m_csBarCode = _T("");
	m_csLicense = _T("");
	m_dwPaymentOutFailureTime = 0;
	m_fPaymentAmount = 0.0f;
	m_csPaymentTime = _T("");
	m_csVehicleInTime = _T("");
	m_bChkVehicleOutEnabled = FALSE;
	m_dwTotalParkingLot = 0;
	m_dwCurrParkingLot = 0;
	m_bChkAlarmEnabled = FALSE;
	m_bChkChargeEnabled = FALSE;
	m_bChkFixCar = FALSE;
	m_bChkFixCard = FALSE;
	m_bChkFreeFixCar = FALSE;
	m_bChkFreeTempCar = FALSE;
	m_bChkNoPlate = FALSE;
	m_bChkOffEnabled = FALSE;
	m_bChkSingleInSingleOutEnabled = FALSE;
	m_bChkTempCar = FALSE;
	m_bChkTempCard = FALSE;
	m_bChkVehCardMatchEnabled = FALSE;
	m_dwTimeWait = 0;
	m_bChkMultiChansCapEnabled = FALSE;
	m_dwMultiChansWaitTime = 0;
	m_bChkillegalCardFilteringEnabled = FALSE;
	m_fAccount = 0.0f;
	m_csVehCardCond = _T("");
	m_csEntranceVehCardXMLBlock = _T("");
	m_csLEDDefaultInfo = _T("");
	m_bChkGroundSensingCoil = FALSE;
	m_bChkGateSwitchSignal = FALSE;
    m_bChkVerifyKeyEnabled = FALSE;
    m_bChkWriteCardEnabled = FALSE;
	m_csLEDInfo = _T("");
	m_dwShowTime = 0;
	m_csVoiceInfo = _T("");
	m_bChkPrintInTime = FALSE;
	m_csCustomInfo = _T("");
	m_csPhoneNum = _T("");
	m_csTitleInfo = _T("");
	m_csBeginTime = _T("");
	m_csBeginTime2 = _T("");
	m_csBeginTime3 = _T("");
	m_csBeginTime4 = _T("");
	m_csEndTime = _T("");
	m_csEndTime2 = _T("");
	m_csEndTime3 = _T("");
	m_csEndTime4 = _T("");
    m_bChkSendCardSensingCoil = FALSE;
    m_bChkWiegendSensingCoil = FALSE;
    m_bChkVerifyKeyWriteCard = FALSE;
	m_bNoplateTakeCardEnabled = FALSE;
	m_byVoicePitch = 0;
	m_byVoiceSpeed = 0;
	m_byVoiceVolum = 0;
	m_sInfo = _T("");
	//}}AFX_DATA_INIT

    m_lLoginID = -1;
    m_iDeviceIndex = -1;
	m_lChannel = -1;

    m_bUpLoading = FALSE;
    m_lUploadHandle = -1;
    m_hUpLoadThread = NULL;
    m_lprogress = 0;
    memset(m_szStatusBuf, 0, sizeof(m_szStatusBuf));
    memset(m_szLan, 0, 128);
}

CDlgTmeCfg::~CDlgTmeCfg()
{
    WaitForSingleObject(m_hUpLoadThread, INFINITE);
    m_hUpLoadThread = NULL;

    if (m_lUploadHandle < 0)
    {
        NET_DVR_StopUploadFile(m_lUploadHandle);
        m_lUploadHandle = -1;
    }
}

void CDlgTmeCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgTmeCfg)
    DDX_Control(pDX, IDC_COMBO_VOICEROLE, m_comVoiceRole);
    DDX_Control(pDX, IDC_COMBO_DISPLAY_MODE, m_comDisplayMode);
    DDX_Control(pDX, IDC_COMBO_SPEED_TYPE, m_comSpeedType);
    DDX_Control(pDX, IDC_COMBO_RECORDSOURCE, m_comRecordSource);
    DDX_Text(pDX, IDC_EDIT_BARCODE, m_csBarCode);
    DDX_Text(pDX, IDC_EDIT_LICENSE, m_csLicense);
    DDX_Text(pDX, IDC_EDIT_PAYMENTOUTFAILURETIME, m_dwPaymentOutFailureTime);
    DDX_Text(pDX, IDC_EDIT_PAYMENTAMOUNT, m_fPaymentAmount);
    DDX_Text(pDX, IDC_EDIT_PAYMENTTIME, m_csPaymentTime);
    DDX_Text(pDX, IDC_EDIT_VEHICLEINTIME, m_csVehicleInTime);
    DDX_Check(pDX, IDC_CHECK_VEHICLEOUTENABLED, m_bChkVehicleOutEnabled);
    DDX_Text(pDX, IDC_EDIT_TOTALPARKINGLOT, m_dwTotalParkingLot);
    DDX_Text(pDX, IDC_EDIT_CURRPARKINGLOT, m_dwCurrParkingLot);
    DDX_Check(pDX, IDC_CHECK_ALARMENABLED, m_bChkAlarmEnabled);
    DDX_Check(pDX, IDC_CHECK_CHARGEENABLE, m_bChkChargeEnabled);
    DDX_Check(pDX, IDC_CHECK_FIXCAR, m_bChkFixCar);
    DDX_Check(pDX, IDC_CHECK_FIXCARD, m_bChkFixCard);
    DDX_Check(pDX, IDC_CHECK_FREEFIXCAR, m_bChkFreeFixCar);
    DDX_Check(pDX, IDC_CHECK_FREETEMPCAR, m_bChkFreeTempCar);
    DDX_Check(pDX, IDC_CHECK_NOPLATE, m_bChkNoPlate);
    DDX_Check(pDX, IDC_CHECK_PXOFFLINE_ENABLED, m_bChkOffEnabled);
    DDX_Check(pDX, IDC_CHECK_SINGLEINSINGLEOUT, m_bChkSingleInSingleOutEnabled);
    DDX_Check(pDX, IDC_CHECK_TEMPCAR, m_bChkTempCar);
    DDX_Check(pDX, IDC_CHECK_TEMPCARD, m_bChkTempCard);
    DDX_Check(pDX, IDC_CHECK_VEHCARDMATCH, m_bChkVehCardMatchEnabled);
    DDX_Text(pDX, IDC_EDIT_TIMEWAIT, m_dwTimeWait);
    DDX_Check(pDX, IDC_CHECK_MULTICHANSCAPENABLED, m_bChkMultiChansCapEnabled);
    DDX_Text(pDX, IDC_EDIT_MULTICHANSWAITTIME, m_dwMultiChansWaitTime);
    DDX_Check(pDX, IDC_CHECK_ILLEGALCARDFILTERINGENABLED, m_bChkillegalCardFilteringEnabled);
    DDX_Text(pDX, IDC_EDIT_CHARGEACCOUNT, m_fAccount);
    DDX_Text(pDX, IDC_EDIT_VEHCARD_COND, m_csVehCardCond);
    DDX_Text(pDX, IDC_EDIT_ENTRANCEVEHCARD_XML_BLOCK, m_csEntranceVehCardXMLBlock);
    DDX_Text(pDX, IDC_EDIT_LED_DEFAULTINFO, m_csLEDDefaultInfo);
    DDX_Check(pDX, IDC_CHECK_GROUNDSENSINGCOIL, m_bChkGroundSensingCoil);
    DDX_Check(pDX, IDC_CHECK_GATESWITCHSIGNAL, m_bChkGateSwitchSignal);
    DDX_Check(pDX, IDC_CHECK_VERIFYKEY, m_bChkVerifyKeyEnabled);
    DDX_Check(pDX, IDC_CHECK_WRITECARD, m_bChkWriteCardEnabled);
    DDX_Text(pDX, IDC_EDIT_LED_INFO, m_csLEDInfo);
    DDX_Text(pDX, IDC_EDIT_SHOWTIME, m_dwShowTime);
    DDX_Text(pDX, IDC_EDIT_VOICE_INFO, m_csVoiceInfo);
    DDX_Check(pDX, IDC_CHECK_PRINT_INTIME, m_bChkPrintInTime);
    DDX_Text(pDX, IDC_EDIT_CUSTOM_INFO, m_csCustomInfo);
    DDX_Text(pDX, IDC_EDIT_PHONE_NUM, m_csPhoneNum);
    DDX_Text(pDX, IDC_EDIT_TITLEINFO, m_csTitleInfo);
    DDX_Text(pDX, IDC_EDIT_BEGIN_TIME, m_csBeginTime);
    DDX_Text(pDX, IDC_EDIT_BEGIN_TIME2, m_csBeginTime2);
    DDX_Text(pDX, IDC_EDIT_BEGIN_TIME3, m_csBeginTime3);
    DDX_Text(pDX, IDC_EDIT_BEGIN_TIME4, m_csBeginTime4);
    DDX_Text(pDX, IDC_EDIT_END_TIME, m_csEndTime);
    DDX_Text(pDX, IDC_EDIT_END_TIME2, m_csEndTime2);
    DDX_Text(pDX, IDC_EDIT_END_TIME3, m_csEndTime3);
    DDX_Text(pDX, IDC_EDIT_END_TIME4, m_csEndTime4);
    DDX_Check(pDX, IDC_CHECK_SENDCARD_SENSINGCOIL, m_bChkSendCardSensingCoil);
    DDX_Check(pDX, IDC_CHECK_WIEGEND_SENSINGCOIL, m_bChkWiegendSensingCoil);
    DDX_Check(pDX, IDC_CHECK_VERIFYKEY_WRITECARD, m_bChkVerifyKeyWriteCard);
    DDX_Check(pDX, IDC_CHECK_NOPLATE_TAKE_CARD, m_bNoplateTakeCardEnabled);
    DDX_Text(pDX, IDC_EDIT_VOICEPITCH, m_byVoicePitch);
    DDX_Text(pDX, IDC_EDIT_VOICESPEED, m_byVoiceSpeed);
    DDX_Text(pDX, IDC_EDIT_VOICEVOLUM, m_byVoiceVolum);
    DDX_Text(pDX, IDC_EDIT_TMEVOICE_INFO, m_sInfo);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_FILE_PATH, m_csFilePath);
    DDX_Text(pDX, IDC_EDIT_TMEVOICE_FILENAME, m_csTMEVoiceFileName);
    DDX_Text(pDX, IDC_EDIT_BROADCAST_NUM, m_iBroadcastNum);
    DDX_Text(pDX, IDC_EDIT_INTERVAL_TIME, m_iIntervalTime);
}


BEGIN_MESSAGE_MAP(CDlgTmeCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgTmeCfg)
	ON_BN_CLICKED(IDC_BTN_SET_PAPERCHARGEINFO_CFG, OnBtnSetPaperchargeinfoCfg)
	ON_BN_CLICKED(IDC_BTN_SET_PARKINGSAPCE_CFG, OnBtnSetParkingsapceCfg)
	ON_BN_CLICKED(IDC_BTN_SET_PXOFFLINE_CFG, OnBtnSetPxofflineCfg)
	ON_BN_CLICKED(IDC_BTN_GET_PXOFFLINE_CFG, OnBtnGetPxofflineCfg)
	ON_BN_CLICKED(IDC_BTN_SET_PXMULTICTRL_CFG, OnBtnSetPxmultictrlCfg)
	ON_BN_CLICKED(IDC_BTN_GET_PXMULTICTRL_CFG, OnBtnGetPxmultictrlCfg)
	ON_BN_CLICKED(IDC_BTN_SET_ILLEGALCARDFILTERING_CFG, OnBtnSetIllegalcardfilteringCfg)
	ON_BN_CLICKED(IDC_BTN_GET_ILLEGALCARDFILTERING_CFG, OnBtnGetIllegalcardfilteringCfg)
	ON_BN_CLICKED(IDC_BTN_SET_CHARGE_ACCOUNTINFO, OnBtnSetChargeAccountinfo)
	ON_BN_CLICKED(IDC_BTN_SET_ENTRANCE_VEHCARD_CFG, OnBtnSetEntranceVehcardCfg)
	ON_BN_CLICKED(IDC_BTN_GET_ENTRANCE_VEHCARD_CFG, OnBtnGetEntranceVehcardCfg)
	ON_BN_CLICKED(IDC_BTN_SET_LEDDISPLAY, OnBtnSetLeddisplay)
	ON_BN_CLICKED(IDC_BTN_GET_LEDDISPLAY, OnBtnGetLeddisplay)
	ON_BN_CLICKED(IDC_BTN_SET_VOICEBROADCAST_CFG, OnBtnSetVoicebroadcastCfg)
	ON_BN_CLICKED(IDC_BTN_SET_PAPERPRINTFORMAT, OnBtnSetPaperprintformat)
	ON_BN_CLICKED(IDC_BTN_GET_PAPERPRINTFORMAT, OnBtnGetPaperprintformat)
	ON_BN_CLICKED(IDC_BTN_SET_LOCKGATE, OnBtnSetLockgate)
	ON_BN_CLICKED(IDC_BTN_GET_LOCKGATE, OnBtnGetLockgate)
	ON_BN_CLICKED(IDC_BTN_SET_TMEVOICE, OnBtnSetTmevoice)
	ON_BN_CLICKED(IDC_BTN_GET_TMEVOICE, OnBtnGetTmevoice)
    ON_WM_TIMER()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_IMPORT, &CDlgTmeCfg::OnBnClickedBtnImport)
    ON_BN_CLICKED(IDC_BTN_SET_UPLOADFILE, &CDlgTmeCfg::OnBnClickedBtnSetUploadfile)
    ON_BN_CLICKED(IDC_BTN_DEL_TMEVOICE, &CDlgTmeCfg::OnBnClickedBtnDelTmevoice)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTmeCfg message handlers

void CDlgTmeCfg::OnBtnSetPaperchargeinfoCfg() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_PAPERCHARGEINFO_CFG struPaperChargeInfo = {0};
    memcpy(struPaperChargeInfo.szBarCode,  m_csBarCode.GetBuffer(0), m_csBarCode.GetLength());
    memcpy(struPaperChargeInfo.szLicense,  m_csLicense.GetBuffer(0), m_csLicense.GetLength());
    memcpy(struPaperChargeInfo.szVehicleInTime,  m_csVehicleInTime.GetBuffer(0), m_csVehicleInTime.GetLength());
    memcpy(struPaperChargeInfo.szPaymentTime,  m_csPaymentTime.GetBuffer(0), m_csPaymentTime.GetLength());
    struPaperChargeInfo.fPaymentAmount = m_fPaymentAmount;
    struPaperChargeInfo.dwPaymentOutFailureTime = m_dwPaymentOutFailureTime;
    struPaperChargeInfo.byVehicleOutEnabled = m_bChkVehicleOutEnabled;
    struPaperChargeInfo.dwSize = sizeof(struPaperChargeInfo);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struPaperChargeInfo;
    struCfg.dwInSize = sizeof(struPaperChargeInfo);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_PAPERCHARGEINFO, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PAPERCHARGEINFO");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PAPERCHARGEINFO");
    }
}


void CDlgTmeCfg::OnBtnSetParkingsapceCfg() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_PARKINGSAPCE_CFG struParkingSpace = {0};
    struParkingSpace.dwTotalParkingLot = m_dwTotalParkingLot;
    struParkingSpace.dwCurrParkingLot = m_dwCurrParkingLot;
    struParkingSpace.dwSize = sizeof(struParkingSpace);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struParkingSpace;
    struCfg.dwInSize = sizeof(struParkingSpace);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_PARKINGSAPCE_INFO, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PARKINGSAPCE_INFO");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PARKINGSAPCE_INFO");
    }
}

void CDlgTmeCfg::OnBtnSetPxofflineCfg()
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_PXOFFLINE_CFG struPXOfflineCfg = {0};
    struPXOfflineCfg.byEnabled = m_bChkOffEnabled;
    struPXOfflineCfg.byChargeEnabled = m_bChkChargeEnabled;
    struPXOfflineCfg.byAlarmEnabled = m_bChkAlarmEnabled;
    struPXOfflineCfg.byRecordSource = m_comRecordSource.GetCurSel();
    struPXOfflineCfg.dwTimeWait = m_dwTimeWait;
    struPXOfflineCfg.dwRealeaseMode = 0;
    struPXOfflineCfg.dwRealeaseMode |= (m_bChkFixCar << 0);
    struPXOfflineCfg.dwRealeaseMode |= (m_bChkFixCard << 1);
    struPXOfflineCfg.dwRealeaseMode |= (m_bChkTempCar << 2);
    struPXOfflineCfg.dwRealeaseMode |= (m_bChkTempCard << 3);
    struPXOfflineCfg.dwRealeaseMode |= (m_bChkNoPlate << 4);
    struPXOfflineCfg.dwRealeaseMode |= (m_bChkFreeFixCar << 5);
    struPXOfflineCfg.dwRealeaseMode |= (m_bChkFreeTempCar << 6);
    struPXOfflineCfg.byVehCardmatch = m_bChkVehCardMatchEnabled;
    struPXOfflineCfg.bySingleInSingleOut = m_bChkSingleInSingleOutEnabled;
    struPXOfflineCfg.dwSize = sizeof(struPXOfflineCfg);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struPXOfflineCfg;
    struCfg.dwInSize = sizeof(struPXOfflineCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_PXOFFLINE_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PXOFFLINE_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PXOFFLINE_CFG");
    }
}

void CDlgTmeCfg::OnBtnGetPxofflineCfg() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_PXOFFLINE_CFG struPXOfflineCfg = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struPXOfflineCfg;
    struCfg.dwOutSize = sizeof(struPXOfflineCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_PXOFFLINE_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PXOFFLINE_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PXOFFLINE_CFG");
    }
    
    m_bChkOffEnabled = struPXOfflineCfg.byEnabled;
    m_bChkChargeEnabled = struPXOfflineCfg.byChargeEnabled;
    m_bChkAlarmEnabled = struPXOfflineCfg.byAlarmEnabled;
    m_comRecordSource.SetCurSel(struPXOfflineCfg.byRecordSource);
    m_dwTimeWait = struPXOfflineCfg.dwTimeWait;
    m_bChkFixCar = struPXOfflineCfg.dwRealeaseMode &0x01;
	m_bChkFixCard = (struPXOfflineCfg.dwRealeaseMode>>1)&0x01;
	m_bChkTempCar = (struPXOfflineCfg.dwRealeaseMode>>2)&0x01;
    m_bChkTempCard = (struPXOfflineCfg.dwRealeaseMode>>3)&0x01;
    m_bChkNoPlate = (struPXOfflineCfg.dwRealeaseMode>>4)&0x01;
    m_bChkFreeFixCar = (struPXOfflineCfg.dwRealeaseMode>>5)&0x01;
    m_bChkFreeTempCar = (struPXOfflineCfg.dwRealeaseMode>>6)&0x01;
    m_bChkVehCardMatchEnabled = struPXOfflineCfg.byVehCardmatch;
    m_bChkSingleInSingleOutEnabled = struPXOfflineCfg.bySingleInSingleOut;
    
    UpdateData(FALSE);
}

void CDlgTmeCfg::OnBtnSetPxmultictrlCfg() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_PXMULTICTRL_CFG struPXMultiCtrlCfg = {0};
    struPXMultiCtrlCfg.dwMultiChansWaitTime = m_dwMultiChansWaitTime;
    struPXMultiCtrlCfg.byMultiChansCapEnabled = m_bChkMultiChansCapEnabled;
    struPXMultiCtrlCfg.dwSize = sizeof(struPXMultiCtrlCfg);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struPXMultiCtrlCfg;
    struCfg.dwInSize = sizeof(struPXMultiCtrlCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_PXMULTICTRL_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PXMULTICTRL_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PXMULTICTRL_CFG");
    }
}

void CDlgTmeCfg::OnBtnGetPxmultictrlCfg() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_PXMULTICTRL_CFG struPXMultiCtrlCfg = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struPXMultiCtrlCfg;
    struCfg.dwOutSize = sizeof(struPXMultiCtrlCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_PXMULTICTRL_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PXMULTICTRL_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PXMULTICTRL_CFG");
    }
    
    m_dwMultiChansWaitTime = struPXMultiCtrlCfg.dwMultiChansWaitTime;
    m_bChkMultiChansCapEnabled = struPXMultiCtrlCfg.byMultiChansCapEnabled;
    
    UpdateData(FALSE);
}

void CDlgTmeCfg::OnBtnSetIllegalcardfilteringCfg() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_ILLEGALCARDFILTERING_CFG struillegalCardFilteringCfg = {0};
    struillegalCardFilteringCfg.byillegalCardFilteringEnabled = m_bChkillegalCardFilteringEnabled;
    struillegalCardFilteringCfg.byGateSwitchEnabled = m_bChkGateSwitchSignal;
    struillegalCardFilteringCfg.bySendCardSensingCoilEnabled = m_bChkSendCardSensingCoil;
    struillegalCardFilteringCfg.byWiegendSensingCoilEnabled = m_bChkWiegendSensingCoil;
    struillegalCardFilteringCfg.byVerifyKeyWriteCardEnabled = m_bChkVerifyKeyWriteCard;
    memcpy(struillegalCardFilteringCfg.sLEDDefaultInfo, m_csLEDDefaultInfo.GetBuffer(0), m_csLEDDefaultInfo.GetLength());
    struillegalCardFilteringCfg.byNoplateTakeCardEnabled = m_bNoplateTakeCardEnabled;
    struillegalCardFilteringCfg.dwSize = sizeof(struillegalCardFilteringCfg);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struillegalCardFilteringCfg;
    struCfg.dwInSize = sizeof(struillegalCardFilteringCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_ILLEGALCARDFILTERING_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ILLEGALCARDFILTERING_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ILLEGALCARDFILTERING_CFG");
    }
}

void CDlgTmeCfg::OnBtnGetIllegalcardfilteringCfg() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_ILLEGALCARDFILTERING_CFG struillegalCardFilteringCfg = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struillegalCardFilteringCfg;
    struCfg.dwOutSize = sizeof(struillegalCardFilteringCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_ILLEGALCARDFILTERING_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ILLEGALCARDFILTERING_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ILLEGALCARDFILTERING_CFG");
    }
    
    m_bChkillegalCardFilteringEnabled = struillegalCardFilteringCfg.byillegalCardFilteringEnabled;
    m_bChkGateSwitchSignal = struillegalCardFilteringCfg.byGateSwitchEnabled;
    m_bChkSendCardSensingCoil = struillegalCardFilteringCfg.bySendCardSensingCoilEnabled;
    m_bChkWiegendSensingCoil = struillegalCardFilteringCfg.byWiegendSensingCoilEnabled;
    m_bChkVerifyKeyWriteCard = struillegalCardFilteringCfg.byVerifyKeyWriteCardEnabled;
    m_csLEDDefaultInfo.Format(_T("%s"), struillegalCardFilteringCfg.sLEDDefaultInfo);
    m_bNoplateTakeCardEnabled = struillegalCardFilteringCfg.byNoplateTakeCardEnabled;
    
    UpdateData(FALSE);
}

void CDlgTmeCfg::OnBtnSetChargeAccountinfo() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_CHARGEACCOUNT_CFG struChargeAccountCfg = {0};
    struChargeAccountCfg.fAccount = m_fAccount;
    struChargeAccountCfg.dwSize = sizeof(struChargeAccountCfg);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struChargeAccountCfg;
    struCfg.dwInSize = sizeof(struChargeAccountCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_CHARGE_ACCOUNTINFO, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_CHARGE_ACCOUNTINFO");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_CHARGE_ACCOUNTINFO");
    }
}

void CDlgTmeCfg::OnBtnSetEntranceVehcardCfg() 
{
	// TODO: Add your control notification handler code here
 
    UpdateData(TRUE);

    
    NET_DVR_TME_CHARGERULE_COND struEntranceVehCond = {0};
    struEntranceVehCond.dwChannel = m_lChannel;
    memcpy(struEntranceVehCond.szCardNo,  m_csVehCardCond.GetBuffer(0), m_csVehCardCond.GetLength());
    struEntranceVehCond.dwSize = sizeof(struEntranceVehCond);
    
    char* pSetXmlBuf = NULL;
    pSetXmlBuf = new char[XML_ABILITY_OUT_LEN];
    memset(pSetXmlBuf, 0, XML_ABILITY_OUT_LEN);
    memcpy(pSetXmlBuf,  m_csEntranceVehCardXMLBlock.GetBuffer(0), m_csEntranceVehCardXMLBlock.GetLength()+1);

//     CXmlBase xmlBase;
//     xmlBase.Parse(pSetXmlBuf);
//     xmlBase.SetRoot();
//    m_csEntranceVehCardXMLBlock = xmlBase.GetChildren().c_str();
    m_csEntranceVehCardXMLBlock.Replace("\r\n", "\n");

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struEntranceVehCond;
    struCfg.dwCondSize = sizeof(struEntranceVehCond);
    struCfg.lpInBuffer = pSetXmlBuf;
    struCfg.dwInSize = strlen(pSetXmlBuf);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_TME_CHARGERULE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_TME_CHARGERULE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_TME_CHARGERULE");
    }

    if (pSetXmlBuf != NULL)
    {
        delete[] pSetXmlBuf;
        pSetXmlBuf = NULL;
    }
}

void CDlgTmeCfg::OnBtnGetEntranceVehcardCfg() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_TME_CHARGERULE_COND struEntranceVehCond = {0};
    struEntranceVehCond.dwChannel = m_lChannel;
    memcpy(struEntranceVehCond.szCardNo,  m_csVehCardCond.GetBuffer(0), m_csVehCardCond.GetLength());
    struEntranceVehCond.dwSize = sizeof(struEntranceVehCond);
    char* pGetXmlBuf = NULL;
    pGetXmlBuf = new char[XML_ABILITY_OUT_LEN];
    memset(pGetXmlBuf, 0, XML_ABILITY_OUT_LEN);

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struEntranceVehCond;
    struCfg.dwCondSize = sizeof(struEntranceVehCond);
    struCfg.lpOutBuffer = pGetXmlBuf;
    struCfg.dwOutSize = XML_ABILITY_OUT_LEN;
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_TME_CHARGERULE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_TME_CHARGERULE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_TME_CHARGERULE");
    }
    
   // m_csEntranceVehCardXMLBlock.Format(_T("%s"), pGetXmlBuf);
    CXmlBase xmlBase;
    xmlBase.Parse(pGetXmlBuf);
    xmlBase.SetRoot();
    m_csEntranceVehCardXMLBlock = xmlBase.GetChildren().c_str();
    m_csEntranceVehCardXMLBlock.Replace("\n", "\r\n");
    
    if (pGetXmlBuf != NULL)
    {
        delete[] pGetXmlBuf;
        pGetXmlBuf = NULL;
    }
    
    UpdateData(FALSE);
}

void CDlgTmeCfg::OnBtnSetLeddisplay() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_LEDDISPLAY_CFG struLedDisplayCfg = {0};
    memcpy(struLedDisplayCfg.sDisplayInfo,  m_csLEDInfo.GetBuffer(0), m_csLEDInfo.GetLength());
    struLedDisplayCfg.byDisplayMode = m_comDisplayMode.GetCurSel();
    struLedDisplayCfg.bySpeedType = m_comSpeedType.GetCurSel();
    struLedDisplayCfg.dwShowTime = m_dwShowTime;
    struLedDisplayCfg.dwSize = sizeof(struLedDisplayCfg);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struLedDisplayCfg;
    struCfg.dwInSize = sizeof(struLedDisplayCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_LEDDISPLAY_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LEDDISPLAY_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LEDDISPLAY_CFG");
    }
}

void CDlgTmeCfg::OnBtnGetLeddisplay() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_LEDDISPLAY_CFG struLedDisplayCfg = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struLedDisplayCfg;
    struCfg.dwOutSize = sizeof(struLedDisplayCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_LEDDISPLAY_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LEDDISPLAY_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LEDDISPLAY_CFG");
    }
    
    m_csLEDInfo.Format(_T("%s"), struLedDisplayCfg.sDisplayInfo);
    m_comDisplayMode.SetCurSel(struLedDisplayCfg.byDisplayMode);
    m_comSpeedType.SetCurSel(struLedDisplayCfg.bySpeedType);
    m_dwShowTime = struLedDisplayCfg.dwShowTime;
    UpdateData(FALSE);
}

void CDlgTmeCfg::OnBtnSetVoicebroadcastCfg() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_VOICEBROADCAST_CFG struVoicebroadcast = {0};
    memcpy(struVoicebroadcast.sInfo,  m_csVoiceInfo.GetBuffer(0), m_csVoiceInfo.GetLength());
    struVoicebroadcast.byBroadcastNum = m_iBroadcastNum;
    struVoicebroadcast.byIntervalTime = m_iIntervalTime;
    struVoicebroadcast.dwSize = sizeof(struVoicebroadcast);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struVoicebroadcast;
    struCfg.dwInSize = sizeof(struVoicebroadcast);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_VOICEBROADCAST_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_VOICEBROADCAST_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_VOICEBROADCAST_CFG");
    }
}

void CDlgTmeCfg::OnBtnSetPaperprintformat() 
{
	// TODO: Add your control notification handler code here

    UpdateData(TRUE);
    NET_DVR_PAPERPRINTFORMAT_CFG struPrperPrintFormat = {0};
    memcpy(struPrperPrintFormat.sTitleInfo,  m_csTitleInfo.GetBuffer(0), m_csTitleInfo.GetLength());
    memcpy(struPrperPrintFormat.sCustomInfo,  m_csCustomInfo.GetBuffer(0), m_csCustomInfo.GetLength());
    memcpy(struPrperPrintFormat.sPhoneNum,  m_csPhoneNum.GetBuffer(0), m_csPhoneNum.GetLength());
    struPrperPrintFormat.byPrintInTimeEnabled = m_bChkPrintInTime;
    struPrperPrintFormat.dwSize = sizeof(struPrperPrintFormat);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struPrperPrintFormat;
    struCfg.dwInSize = sizeof(struPrperPrintFormat);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_PAPERPRINTFORMAT_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PAPERPRINTFORMAT_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PAPERPRINTFORMAT_CFG");
    }
}

void CDlgTmeCfg::OnBtnGetPaperprintformat() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_PAPERPRINTFORMAT_CFG struPrperPrintFormat = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struPrperPrintFormat;
    struCfg.dwOutSize = sizeof(struPrperPrintFormat);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_PAPERPRINTFORMAT_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PAPERPRINTFORMAT_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PAPERPRINTFORMAT_CFG");
    }
    
    m_csTitleInfo.Format(_T("%s"), struPrperPrintFormat.sTitleInfo);
    m_csCustomInfo.Format(_T("%s"), struPrperPrintFormat.sCustomInfo);
    m_csPhoneNum.Format(_T("%s"), struPrperPrintFormat.sPhoneNum);
    m_bChkPrintInTime = struPrperPrintFormat.byPrintInTimeEnabled;
    UpdateData(FALSE);
}

void CDlgTmeCfg::OnBtnSetLockgate() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_LOCKGATE_CFG struLockGateCfg = {0};
    memcpy(struLockGateCfg.struTime[0].sBeginTime,  m_csBeginTime.GetBuffer(0), m_csBeginTime.GetLength());
    memcpy(struLockGateCfg.struTime[0].sEndTime,  m_csEndTime.GetBuffer(0), m_csEndTime.GetLength());
    memcpy(struLockGateCfg.struTime[1].sBeginTime,  m_csBeginTime2.GetBuffer(0), m_csBeginTime2.GetLength());
    memcpy(struLockGateCfg.struTime[1].sEndTime,  m_csEndTime2.GetBuffer(0), m_csEndTime2.GetLength());
    memcpy(struLockGateCfg.struTime[2].sBeginTime,  m_csBeginTime3.GetBuffer(0), m_csBeginTime3.GetLength());
    memcpy(struLockGateCfg.struTime[2].sEndTime,  m_csEndTime3.GetBuffer(0), m_csEndTime3.GetLength());
    memcpy(struLockGateCfg.struTime[3].sBeginTime,  m_csBeginTime4.GetBuffer(0), m_csBeginTime4.GetLength());
    memcpy(struLockGateCfg.struTime[3].sEndTime,  m_csEndTime4.GetBuffer(0), m_csEndTime4.GetLength());
    struLockGateCfg.dwSize = sizeof(struLockGateCfg);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struLockGateCfg;
    struCfg.dwInSize = sizeof(struLockGateCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_LOCKGATE_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LOCKGATE_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LOCKGATE_CFG");
    }
}

void CDlgTmeCfg::OnBtnGetLockgate() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_LOCKGATE_CFG struLockGateCfg = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struLockGateCfg;
    struCfg.dwOutSize = sizeof(struLockGateCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_LOCKGATE_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LOCKGATE_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LOCKGATE_CFG");
    }
    
    m_csBeginTime.Format(_T("%s"), struLockGateCfg.struTime[0].sBeginTime);
    m_csEndTime.Format(_T("%s"), struLockGateCfg.struTime[0].sEndTime);
    m_csBeginTime2.Format(_T("%s"), struLockGateCfg.struTime[1].sBeginTime);
    m_csEndTime2.Format(_T("%s"), struLockGateCfg.struTime[1].sEndTime);
    m_csBeginTime3.Format(_T("%s"), struLockGateCfg.struTime[2].sBeginTime);
    m_csEndTime3.Format(_T("%s"), struLockGateCfg.struTime[2].sEndTime);
    m_csBeginTime4.Format(_T("%s"), struLockGateCfg.struTime[3].sBeginTime);
    m_csEndTime4.Format(_T("%s"), struLockGateCfg.struTime[3].sEndTime);

    UpdateData(FALSE);
}

void CDlgTmeCfg::OnBtnSetTmevoice() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_TMEVOICE_CFG struTMEVoiceCfg = {0};
    struTMEVoiceCfg.dwSize = sizeof(struTMEVoiceCfg);
    struTMEVoiceCfg.byVoiceSpeed = m_byVoiceSpeed;
    struTMEVoiceCfg.byVoicePitch = m_byVoicePitch;
    struTMEVoiceCfg.byVoiceVolum = m_byVoiceVolum;
    memcpy(struTMEVoiceCfg.sInfo,  m_sInfo.GetBuffer(0), m_sInfo.GetLength());
    memcpy(struTMEVoiceCfg.sFileName, m_csTMEVoiceFileName.GetBuffer(0), m_csTMEVoiceFileName.GetLength());

    if (0 == m_comVoiceRole.GetCurSel())
    {
        struTMEVoiceCfg.dwVoiceRole = 3;    
    }
    else if (1 == m_comVoiceRole.GetCurSel())
    {
        struTMEVoiceCfg.dwVoiceRole = 51;    
    }
    else if (2 == m_comVoiceRole.GetCurSel())
    {
        struTMEVoiceCfg.dwVoiceRole = 52;    
    }
    else if (3 == m_comVoiceRole.GetCurSel())
    {
        struTMEVoiceCfg.dwVoiceRole = 53;    
    }
    else if (4 == m_comVoiceRole.GetCurSel())
    {
        struTMEVoiceCfg.dwVoiceRole = 54;    
    }
    else if (5 == m_comVoiceRole.GetCurSel())
    {
        struTMEVoiceCfg.dwVoiceRole = 55;    
    }

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struTMEVoiceCfg;
    struCfg.dwInSize = sizeof(struTMEVoiceCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_TMEVOICE_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_TMEVOICE_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_TMEVOICE_CFG");
    }
}

void CDlgTmeCfg::OnBtnGetTmevoice() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_TMEVOICE_CFG struTMEVoiceCfg = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struTMEVoiceCfg;
    struCfg.dwOutSize = sizeof(struTMEVoiceCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_TMEVOICE_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_TMEVOICE_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_TMEVOICE_CFG");
    }
    
    m_byVoiceSpeed = struTMEVoiceCfg.byVoiceSpeed;
    m_byVoicePitch = struTMEVoiceCfg.byVoicePitch;
    m_byVoiceVolum = struTMEVoiceCfg.byVoiceVolum;

    if(3 == struTMEVoiceCfg.dwVoiceRole)
    {
        m_comVoiceRole.SetCurSel(0);
    }
    else if (51 == struTMEVoiceCfg.dwVoiceRole)
    {
        m_comVoiceRole.SetCurSel(1);
    }
    else if (52 == struTMEVoiceCfg.dwVoiceRole)
    {
        m_comVoiceRole.SetCurSel(2);
    }
    else if (53 == struTMEVoiceCfg.dwVoiceRole)
    {
        m_comVoiceRole.SetCurSel(3);
    }
    else if (54 == struTMEVoiceCfg.dwVoiceRole)
    {
        m_comVoiceRole.SetCurSel(4);
    }
    else if (55 == struTMEVoiceCfg.dwVoiceRole)
    {
        m_comVoiceRole.SetCurSel(5);
    }
    m_sInfo.Format(_T("%s"), struTMEVoiceCfg.sInfo);

    m_csTMEVoiceFileName.Format(_T("%s"), struTMEVoiceCfg.sFileName);
    UpdateData(FALSE);
}


void CDlgTmeCfg::OnBnClickedBtnImport()
{
    // TODO:  在此添加控件通知处理程序代码
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_csFilePath = dlg.GetPathName();
        UpdateData(FALSE);
    }
}

DWORD  GetVideoUpLoadFileThread(LPVOID pParam)
{
    CDlgTmeCfg *pThis = (CDlgTmeCfg*)pParam;

    DWORD dwState = 0;
    DWORD dwProgress = 0;
    char szLan[256] = { 0 };


    while (TRUE)
    {
        dwState = NET_DVR_GetUploadState(pThis->m_lUploadHandle, &dwProgress);
        if (dwState == 1)
        {
            g_StringLanType(szLan, "上传成功", "Upload successfully");
            pThis->m_bUpLoading = FALSE;
            memcpy(pThis->m_szLan, szLan, 128);
          //  pThis->KillTimer(1);
            break;
        }
        else if (dwState == 2)
        {
            g_StringLanType(szLan, "正在上传,已上传:", "Is uploading,progress:");
            sprintf(szLan, "%s%d", szLan, dwProgress);
            memcpy(pThis->m_szLan, szLan, 128);

        }
        else if (dwState == 3)
        {
            g_StringLanType(szLan, "上传失败", "Upload failed");
            memcpy(pThis->m_szLan, szLan, 128);
         //   pThis->KillTimer(1);
            break;
        }
        else if (dwState == 4)
        {
            if (dwProgress == 100)
            {
                g_StringLanType(szLan, "上传成功", "Upload successfully");
                memcpy(pThis->m_szLan, szLan, 128);
                pThis->m_bUpLoading = FALSE;
            //    pThis->KillTimer(1);
                break;
            }
            else
            {
                g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
                memcpy(pThis->m_szLan, szLan, 128);
             //   pThis->KillTimer(1);
                break;
            }

        }
        else if (dwState == 10)
        {
            g_StringLanType(szLan, "文件个数超过上限", "Exceed max file num");
            memcpy(pThis->m_szLan, szLan, 128);
            break;
        }
        else if (dwState == 11)
        {
            g_StringLanType(szLan, "文件过大", "File size exceed");
            memcpy(pThis->m_szLan, szLan, 128);
            break;
        }
        else if (dwState == 12)
        {
            g_StringLanType(szLan, "文件格式错误", "Incorrect file type");
            memcpy(pThis->m_szLan, szLan, 128);
            break;
        }

        if (dwState != 2 && dwState != 5)
        {
            NET_DVR_UploadClose(pThis->m_lUploadHandle);
            pThis->m_bUpLoading = FALSE;
            pThis->KillTimer(1);
        }
    }

    return FALSE;
}

void CDlgTmeCfg::OnBnClickedBtnSetUploadfile()
{
    // TODO:  在此添加控件通知处理程序代码
    char szLan[1280] = { 0 };
    if (!m_bUpLoading)
    {
        UpdateData(TRUE);
        char szFileName[MAX_PATH] = { 0 };
        strcpy(szFileName, m_csFilePath);
        CFile cFile;
        if (!cFile.Open(szFileName, NULL))
        {
            g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
            AfxMessageBox(szLan);
            return;
        }
        DWORD dwFileSize = (DWORD)cFile.GetLength();
        if (dwFileSize == 0)
        {
            g_StringLanType(szLan, "配置文件为空", "Configure file is empty");
            AfxMessageBox(szLan);
        }
        cFile.Close();

        m_lUploadHandle = NET_DVR_UploadFile(m_lLoginID, UPLOAD_AUDIO_FILE, NULL, NULL, szFileName);



        if (m_lUploadHandle < 0)
        {

            sprintf(szLan, "UPLOAD_AUDIO_FILE Upload Failed! \r\n Error Msg:%s Error Code:%d", NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());

            NET_DVR_StopUploadFile(m_lUploadHandle);
            AfxMessageBox(szLan);
            return;
        }
        SetTimer(1, 100, NULL);
        DWORD dwThreadId = 0;
        m_hUpLoadThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetVideoUpLoadFileThread), this, 0, &dwThreadId);
        if (m_hUpLoadThread == NULL)
        {
            char szLan[256] = { 0 };
            g_StringLanType(szLan, "打开长传文件线程失败!", "open UpLoad thread Fail!");
            AfxMessageBox(szLan);
            return;
        }

        m_bUpLoading = TRUE;
    }
    else
    {
        KillTimer(1);
        NET_DVR_CloseUploadHandle(m_lUploadHandle);
        m_bUpLoading = FALSE;

    }
    UpdateData(FALSE);
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgTmeCfg::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgTmeCfg::OnTimer(UINT nIDEvent)
#endif
{
    if (nIDEvent == 1)
    {
        GetDlgItem(IDC_STATIC_INFO)->SetWindowText(m_szLan);
    }
   

    CDialog::OnTimer(nIDEvent);
}

void CDlgTmeCfg::OnBnClickedBtnDelTmevoice()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_TMEVOICE_CFG struTMEVoiceCfg = { 0 };
    struTMEVoiceCfg.dwSize = sizeof(struTMEVoiceCfg);
    struTMEVoiceCfg.byVoiceSpeed = m_byVoiceSpeed;
    struTMEVoiceCfg.byVoicePitch = m_byVoicePitch;
    struTMEVoiceCfg.byVoiceVolum = m_byVoiceVolum;
    memcpy(struTMEVoiceCfg.sInfo, m_sInfo.GetBuffer(0), m_sInfo.GetLength());
    memcpy(struTMEVoiceCfg.sFileName, m_csTMEVoiceFileName.GetBuffer(0), m_csTMEVoiceFileName.GetLength());

    if (0 == m_comVoiceRole.GetCurSel())
    {
        struTMEVoiceCfg.dwVoiceRole = 3;
    }
    else if (1 == m_comVoiceRole.GetCurSel())
    {
        struTMEVoiceCfg.dwVoiceRole = 51;
    }
    else if (2 == m_comVoiceRole.GetCurSel())
    {
        struTMEVoiceCfg.dwVoiceRole = 52;
    }
    else if (3 == m_comVoiceRole.GetCurSel())
    {
        struTMEVoiceCfg.dwVoiceRole = 53;
    }
    else if (4 == m_comVoiceRole.GetCurSel())
    {
        struTMEVoiceCfg.dwVoiceRole = 54;
    }
    else if (5 == m_comVoiceRole.GetCurSel())
    {
        struTMEVoiceCfg.dwVoiceRole = 55;
    }

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struTMEVoiceCfg;
    struCfg.dwInSize = sizeof(struTMEVoiceCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_DEL_TMEVOICE_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_DEL_TMEVOICE_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_DEL_TMEVOICE_CFG");
    }
}

