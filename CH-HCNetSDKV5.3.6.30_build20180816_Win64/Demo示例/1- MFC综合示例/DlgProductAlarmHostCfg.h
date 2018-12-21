#if !defined(AFX_DLGPRODUCTALARMHOSTCFG_H__A2225D42_339C_42D9_B7A3_E080E53F15C6__INCLUDED_)
#define AFX_DLGPRODUCTALARMHOSTCFG_H__A2225D42_339C_42D9_B7A3_E080E53F15C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProductAlarmHostCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProductAlarmHostCfg dialog

class CDlgProductAlarmHostCfg : public CDialog
{
// Construction
public:
	CDlgProductAlarmHostCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgProductAlarmHostCfg)
	enum { IDD = IDD_SUBDLG_PRODUCT_ALARMHOST };
	
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProductAlarmHostCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProductAlarmHostCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnStatusQuery();
	afx_msg void OnBtnAlarmoutCfg();
	afx_msg void OnBtnAlarmhostAbility();
	afx_msg void OnBtnRs485Cfg();
	afx_msg void OnBtnNetUser();
	afx_msg void OnBtnOperatorUser();
	afx_msg void OnBtnBattaryVoltage();
	afx_msg void OnBtnAlarmhostEnablecfg();
	afx_msg void OnBtnGatewayCfg();
	afx_msg void OnButtonDialparam();
	afx_msg void OnBtnBypasssetup();
	afx_msg void OnBtnBypassStopsetup();
	afx_msg void OnBtnSubsystemCfg();
	afx_msg void OnBtnReportmode();
	afx_msg void OnBtnGprspara();
	afx_msg void OnBtnNetcfg();
	afx_msg void OnBtnZoomCode();
	afx_msg void OnBtnTriggerCode();
	afx_msg void OnBtnFaultProcess();
	afx_msg void OnBtnEventTrigger();
	afx_msg void OnBtnExternModule();
	afx_msg void OnBtnLed();
	afx_msg void OnBtnAudioAssociate();
	afx_msg void OnBtnSafetyCabin();
	afx_msg void OnBtnModuleCfg();
	afx_msg void OnBtnPrinter();
	afx_msg void OnButAlarmLogSearch();
	afx_msg void OnBtnAlarmChanAblitity();
	afx_msg void OnBtnAlarmCenter();
	afx_msg void OnBtnTamper();
    afx_msg void OnBtnGerAllModule();
    afx_msg void OnBtnSubSystemAlarm();
    afx_msg void OnBtnWhiteListCfg();
    afx_msg void OnBtnWirelessBusinnessSearch();
    afx_msg void OnBtnGetAllRemoteController();
    afx_msg void OnBtnAlarmCaptrueCfg();
    afx_msg void OnBtnLinkageChan();
    afx_msg void OnBtnCenterSvrCfg();
    afx_msg void OnBnClickedBtnDelayPreviewCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    int     m_iDevIndex;
    LONG    m_lServerID;
    LONG    m_lStartChan;
    LONG    m_lChannel;
	char    m_szLan[128];
	BOOL	m_bInit;

    NET_DVR_ALARMHOST_ABILITY   m_struAlarmHostAbility;
    NET_DVR_ALARMIN_PARAM_V50       m_struAlarmInParam;
    NET_DVR_ALARMIN_SETUP       m_struAlarmInSetup;
    
    float m_fBatteryVoltage;
public:
   
//    void InitAlarmOutCombo();

    BOOL GetAlarmHostAbility(NET_DVR_ALARMHOST_ABILITY& struAlarmHostAbility);
    BOOL GetBatteryVoltage();
    void UpdatePapam(); 
    afx_msg void OnBnClickedBtnAlarmOneKey();
    afx_msg void OnBnClickedBtnStdXmlConfig();
    afx_msg void OnBnClickedBtnZoneCfg();
    afx_msg void OnBnClickedBtnRegisterdetector();
    afx_msg void OnBnClickedBtnOutScale();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPRODUCTALARMHOSTCFG_H__A2225D42_339C_42D9_B7A3_E080E53F15C6__INCLUDED_)
