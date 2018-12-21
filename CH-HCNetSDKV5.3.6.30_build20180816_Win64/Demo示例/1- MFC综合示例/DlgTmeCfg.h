#if !defined(AFX_DLGTMECFG_H__DD849AB7_49B0_4AF2_B613_4E9D6C7AA46E__INCLUDED_)
#define AFX_DLGTMECFG_H__DD849AB7_49B0_4AF2_B613_4E9D6C7AA46E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTmeCfg.h : header file
//
#include "./xml/XmlBase.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgTmeCfg dialog

class CDlgTmeCfg : public CDialog
{
// Construction
public:
	CDlgTmeCfg(CWnd* pParent = NULL);   // standard constructor
    ~CDlgTmeCfg();
// Dialog Data
	//{{AFX_DATA(CDlgTmeCfg)
	enum { IDD = IDD_DLG_TME_CFG };
	CComboBox	m_comVoiceRole;
	CComboBox	m_comDisplayMode;
	CComboBox	m_comSpeedType;
	CComboBox	m_comRecordSource;
	CString	m_csBarCode;
	CString	m_csLicense;
	DWORD	m_dwPaymentOutFailureTime;
	float	m_fPaymentAmount;
	CString	m_csPaymentTime;
	CString	m_csVehicleInTime;
	BOOL	m_bChkVehicleOutEnabled;
	DWORD	m_dwTotalParkingLot;
	DWORD	m_dwCurrParkingLot;
	BOOL	m_bChkAlarmEnabled;
	BOOL	m_bChkChargeEnabled;
	BOOL	m_bChkFixCar;
	BOOL	m_bChkFixCard;
	BOOL	m_bChkFreeFixCar;
	BOOL	m_bChkFreeTempCar;
	BOOL	m_bChkNoPlate;
	BOOL	m_bChkOffEnabled;
	BOOL	m_bChkSingleInSingleOutEnabled;
	BOOL	m_bChkTempCar;
	BOOL	m_bChkTempCard;
	BOOL	m_bChkVehCardMatchEnabled;
	DWORD	m_dwTimeWait;
	BOOL	m_bChkMultiChansCapEnabled;
	DWORD	m_dwMultiChansWaitTime;
	BOOL	m_bChkillegalCardFilteringEnabled;
	float	m_fAccount;
	CString	m_csVehCardCond;
	CString	m_csEntranceVehCardXMLBlock;
	CString	m_csLEDDefaultInfo;
	BOOL	m_bChkGroundSensingCoil;
	BOOL	m_bChkGateSwitchSignal;
    BOOL    m_bChkVerifyKeyEnabled;
    BOOL    m_bChkWriteCardEnabled;
	CString	m_csLEDInfo;
	DWORD	m_dwShowTime;
	CString	m_csVoiceInfo;
	BOOL	m_bChkPrintInTime;
	CString	m_csCustomInfo;
	CString	m_csPhoneNum;
	CString	m_csTitleInfo;
	CString	m_csBeginTime;
	CString	m_csBeginTime2;
	CString	m_csBeginTime3;
	CString	m_csBeginTime4;
	CString	m_csEndTime;
	CString	m_csEndTime2;
	CString	m_csEndTime3;
	CString	m_csEndTime4;
    BOOL	m_bChkSendCardSensingCoil;
    BOOL    m_bChkWiegendSensingCoil;
    BOOL    m_bChkVerifyKeyWriteCard;
	BOOL	m_bNoplateTakeCardEnabled;
	BYTE	m_byVoicePitch;
	BYTE	m_byVoiceSpeed;
	BYTE	m_byVoiceVolum;
	CString	m_sInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTmeCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTmeCfg)
	afx_msg void OnBtnSetPaperchargeinfoCfg();
	afx_msg void OnBtnSetParkingsapceCfg();
	afx_msg void OnBtnSetPxofflineCfg();
	afx_msg void OnBtnGetPxofflineCfg();
	afx_msg void OnBtnSetPxmultictrlCfg();
	afx_msg void OnBtnGetPxmultictrlCfg();
	afx_msg void OnBtnSetIllegalcardfilteringCfg();
	afx_msg void OnBtnGetIllegalcardfilteringCfg();
	afx_msg void OnBtnSetChargeAccountinfo();
	afx_msg void OnBtnSetEntranceVehcardCfg();
	afx_msg void OnBtnGetEntranceVehcardCfg();
	afx_msg void OnBtnSetLeddisplay();
	afx_msg void OnBtnGetLeddisplay();
	afx_msg void OnBtnSetVoicebroadcastCfg();
	afx_msg void OnBtnSetPaperprintformat();
	afx_msg void OnBtnGetPaperprintformat();
	afx_msg void OnBtnSetLockgate();
	afx_msg void OnBtnGetLockgate();
	afx_msg void OnBtnSetTmevoice();
	afx_msg void OnBtnGetTmevoice();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:

    LONG m_lLoginID;
    INT  m_iDeviceIndex;
	LONG m_lChannel;
    BOOL m_bUpLoading;
    LONG m_lUploadHandle;
    HANDLE	m_hUpLoadThread;
    char m_szLan[128];
    LONG m_lprogress;
    char    m_szStatusBuf[ISAPI_STATUS_LEN];
    CString m_csFilePath;
    afx_msg void OnBnClickedBtnImport();
    afx_msg void OnBnClickedBtnSetUploadfile();
    CString m_csTMEVoiceFileName;
    afx_msg void OnBnClickedBtnDelTmevoice();
    int m_iBroadcastNum;
    int m_iIntervalTime;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTMECFG_H__DD849AB7_49B0_4AF2_B613_4E9D6C7AA46E__INCLUDED_)
