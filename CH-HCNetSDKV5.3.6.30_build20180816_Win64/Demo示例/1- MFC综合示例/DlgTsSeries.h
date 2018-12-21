#if !defined(AFX_DLGTSSERIES_H__AF90FCCB_1AE2_486C_9C20_97F3FD18BFFF__INCLUDED_)
#define AFX_DLGTSSERIES_H__AF90FCCB_1AE2_486C_9C20_97F3FD18BFFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTsSeries.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTsSeries dialog

class CDlgTsSeries : public CDialog
{
// Construction
public:
	CDlgTsSeries(CWnd* pParent = NULL);   // standard constructor
    ~CDlgTsSeries();
// Dialog Data
	//{{AFX_DATA(CDlgTsSeries)
	enum { IDD = IDD_DLG_TS };
	CComboBox	m_comVehicleType;
	CComboBox	m_comPlateColor;
	CComboBox	m_comCardStatus;
	CComboBox	m_comEntranceNo;
	CComboBox	m_comGateCtrl;
	CComboBox	m_comLaneNo;
	CComboBox	m_comParkingCardType;
	CButton	m_checkDelCard;
	CButton	m_checkDelAllCard;
	CComboBox	m_comCardType;
	CComboBox	m_comVehicleLogoRecog;
	CComboBox	m_comCarColorDeep;
	CComboBox	m_comCarColor;
	CComboBox	m_comRelateLaneNo2;
	CComboBox	m_comParkingStatus2;
	CComboBox	m_comLampColorStatus;
	CComboBox	m_comFlickerStatus;
	CComboBox	m_comRelateLaneNo;
	CComboBox	m_comParkingStatus;
	CComboBox	m_comParkingLamp;
	CComboBox	m_comRelateParkingLamp;
	CComboBox	m_comLEDDev;
	CComboBox	m_comChargeMode;
	CComboBox	m_comCharge;
	CComboBox	m_comParkIndex;
	CButton	m_checkIO3;
	CButton	m_checkIO2;
	CButton	m_checkIO1;
	CComboBox	m_comLampFlicker;
	CComboBox	m_comLampEnable;
	CComboBox	m_comParkSpaceAttribute;
	CComboBox	m_comParkSpaceInfo;
	CComboBox	m_comParkNum;
	CComboBox	m_comParkStatus;
	CComboBox	m_comFlicker;
	CComboBox	m_comEnable;
	CComboBox	m_comParkInfo;
	CComboBox	m_comIOSTate;
	CComboBox	m_comLampColor;
    CComboBox	m_comMixLampMode;
	CComboBox	m_comLampCtrlMode;
	CComboBox	m_comCardMode;
	CComboBox	m_comLprMode;
	CComboBox	m_comGateLaneMode;
	CComboBox	m_cmbCode;
	CComboBox	m_cmbValid;
	CComboBox	m_cmbIpcType;
	CComboBox	m_cmbGateLane;
	CComboBox	m_cmbDirection;
	CString	m_csSendData;
	int		m_iCamLaneID;
	CString	m_csGateInfo;
	CString	m_csGateSiteID;
	int		m_iLaneID;
	int		m_iRelativeIONum;
	int		m_iRemoteCamlaneID;
	int		m_iRemoteLaneID;
	CString	m_csLaneName;
	BYTE	m_byCtrlChannelIndex;
	BYTE	m_byGateIndex;
	BYTE	m_byLedIndex;
	BYTE	m_byRelatIndex;
	CString	m_csLicense;
	CString	m_csParkingNo;
	CString	m_strCardNo;
	BYTE	m_byChargeRuleID;
	COleDateTime	m_startDate;
	COleDateTime	m_startTime;
	COleDateTime	m_stopDate;
	COleDateTime	m_stopTime;
	CString	m_csRelateCardNo;
	CString	m_csVehicleLicense;
	COleDateTime	m_startDate2;
	COleDateTime	m_startTime2;
	COleDateTime	m_stopDate2;
	COleDateTime	m_stopTime2;
	DWORD	m_dwUpdataSerialNum;
	DWORD	m_dwParkingNum;
	CString	m_csAppSerialNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTsSeries)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTsSeries)
	afx_msg void OnBtnSetTrans();
	afx_msg void OnBtnOutTrans();
	afx_msg void OnBtnSendDataTrans();
	afx_msg void OnBtnGetChanLane();
	afx_msg void OnBtnSetChanLane();
	afx_msg void OnBtnSaveLane();
	afx_msg void OnSelchangeComboGatelane();
	afx_msg void OnBtnRemoteCommand();
	afx_msg void OnBtnGetEctWorkStatus2();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGetEctDevStatue();
	afx_msg void OnBtnPreLampCtrlInfo();
	afx_msg void OnBtnSetLampCtrlInfo();
	afx_msg void OnBtnGetLampCtrlInfo();
	afx_msg void OnSelchangeComboLampctrlmode();
	afx_msg void OnSelchangeComboParknum();
	afx_msg void OnSelchangeComboParkinfo();
	afx_msg void OnSelchangeComboParkstatus();
	afx_msg void OnBtnSetParkspaceAttribute();
	afx_msg void OnBtnGetParkspaceAttribute();
	afx_msg void OnSelchangeComboParkSpaceInfo();
	afx_msg void OnBtnSetLampExternal();
	afx_msg void OnBtnGetLampExternal();
	afx_msg void OnBtnSetCompelCapture();
	afx_msg void OnBtnSetCustominfo();
	afx_msg void OnBtnGetCustominfo();
	afx_msg void OnBtnPreParkspaceAttribute();
	afx_msg void OnSelchangeComboLedDev();
	afx_msg void OnSelchangeComboParklamp();
	afx_msg void OnSelchangeComboParkingstate();
	afx_msg void OnBtnGetstatus();
	afx_msg void OnSelchangeComboMixlampmode();
	afx_msg void OnBtnDelTemporaryCard();
	afx_msg void OnBtnCreateLink();
	afx_msg void OnBtnTemporaryCardSend();
	afx_msg void OnBtnStopSend();
	afx_msg void OnBtnGateCtrl();
	afx_msg void OnBtnVehicleCreateLinkVehicle();
	afx_msg void OnBtnTemporaryVehicleSend();
	afx_msg void OnBtnVehicleStopSend();
	afx_msg void OnBtnItcIoin();
	afx_msg void OnBtnTmeCfg();
	afx_msg void OnBtnSetParkingDatastate();
	afx_msg void OnBtnGetParkingDatastate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG m_lLoginID;
	INT  m_iDeviceIndex;
	LONG m_lChannel;
	LONG m_lTranHandle;
	NET_ITS_GATE_LANE_CFG m_strITSGateLaneCfg[4];
	NET_DVR_LAMP_CTRL_INFO m_struLampCtrlInfo;
	NET_DVR_PARKSPACE_ATTRIBUTE m_struParkSpaceAttribute;
	NET_DVR_LAMP_EXTERNAL_CFG m_struLampExternal;
	NET_DVR_COMPEL_CAPTURE m_struCompelCapTure;

	char m_szStatusBuf[ISAPI_STATUS_LEN];
	LONG m_lCardSendHandle;
    LONG m_lVehicleSendHandle;
//	NET_DVR_CUSTOMINFO_CFG m_struCustomInfo;
    void MixlampModeStatusAndValue(int type);
    void SinglelampModeStatus();
    BOOL m_byUnLock;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTSSERIES_H__AF90FCCB_1AE2_486C_9C20_97F3FD18BFFF__INCLUDED_)
