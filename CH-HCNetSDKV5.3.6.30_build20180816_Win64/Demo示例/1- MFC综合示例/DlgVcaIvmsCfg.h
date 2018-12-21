#if !defined(AFX_DLGVCAIVMSCFG_H__CA7E1DC1_5C22_4E94_9028_BCDBEC034AC1__INCLUDED_)
#define AFX_DLGVCAIVMSCFG_H__CA7E1DC1_5C22_4E94_9028_BCDBEC034AC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaIvmsCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaIvmsCfg dialog

class CDlgVcaIvmsCfg : public CDialog
{
// Construction
public:
	CDlgVcaIvmsCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaIvmsCfg)
	enum { IDD = IDD_DLG_VCA_IVMS_CFG };
	CStatic	m_staticAlarmPersistStickUpArea;
	CComboBox	m_comboWeekdayCopy;
	CComboBox	m_comboAtmMode;
	CEdit	m_editReadCardTimePersist;
	CEdit	m_editMaxDistance;
	CEdit	m_editDenstityRate;
	CEdit	m_editAlarmPersist;
	CEdit	m_editAlarmDelay;
	CComboBox	m_comboTimePeriod;
	CComboBox	m_comboWeekday;
	CComboBox	m_comboAlarmDirect;
	CStatic	m_staticReadCardTimePersistArea;
	CStatic	m_staticReadCardTimePersist;
	CStatic	m_staticMaxDistanceArea;
	CStatic	m_staticMaxDistance;
	CStatic	m_staticDenstityRateArea;
	CStatic	m_staticDenstityRate;
	CStatic	m_staticAlarmPersistArea;
	CStatic	m_staticAlarmPersist;
	CStatic	m_staticAlarmDirect;
	CStatic	m_staticAlarmDelayArea;
	CStatic	m_staticAlarmDelay;
	CComboBox	m_comboVcaType;
	CComboBox	m_comboVcaChan;
	CComboBox	m_comboStream;
	CComboBox	m_comboSensitive;
	CComboBox	m_comboRuleType;
	CComboBox	m_comboRuleId;
	CComboBox	m_comboResolution;
	CComboBox	m_comboPicQuality;
	BOOL	m_bDspAddRule;
	BOOL	m_bDspAddTarget;
	BOOL	m_bFilterActive;
	BOOL	m_bPicAddRule;
	BOOL	m_bPicAddTarget;
	BOOL	m_bSetMaxFilter;
	BOOL	m_bSetMiniFilter;
	BOOL	m_bVcaActive;
	BOOL	m_bDrawLine;
	BOOL	m_bDrawPolygon;
	BOOL	m_bPicPro;
	BOOL	m_bRuleActive;
	int		m_iAlarmDelay;
	int		m_iAlarmPersist;
	int		m_iBAdvanceChanNum;
	int		m_iBBaseChanNum;
	int		m_iBFullChanNum;
	float	m_fDenstityRate;
	float	m_fMaxDistance;
	int		m_iPlateChanNum;
	int		m_iReadCardTimePersist;
	CString	m_csRuleName;
	int	m_iVcaChanNum;
	int		m_iAtmChanNum;	
	CString	m_csDevIP;
	CString	m_csTimePeriod;
	BOOL	m_bPicWithVca;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaIvmsCfg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaIvmsCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBtnSetVcaCtrl();
	afx_msg void OnBtnVcaRestart();
	afx_msg void OnBtnSetVcaDrawMode();
	afx_msg void OnBtnIvmsSched();
	afx_msg void OnBtnSetIvmsCfg();
	afx_msg void OnChkDrawLine();
	afx_msg void OnChkDrawPolygon();
	afx_msg void OnChkPicPro();
	afx_msg void OnChkRuleActive();
	afx_msg void OnCheckVcaActive();
	afx_msg void OnCheckFilterActive();
	afx_msg void OnCheckSetMiniFilter();
	afx_msg void OnCheckSetMaxFilter();
	afx_msg void OnSelchangeComboVcaChan();
	afx_msg void OnSelchangeComboWeekday();
	afx_msg void OnSelchangeComboTimePeriod();
	afx_msg void OnSelchangeComboLineAlarmDirect();
	afx_msg void OnSelchangeComboRuleType();
	afx_msg void OnSelchangeComboRuleId();
	afx_msg void OnBtnRuleOk();
	afx_msg void OnSelchangeComboPicQuality();
	afx_msg void OnSelchangeComboResolution();
	afx_msg void OnBtnPicOk();
	afx_msg void OnSelchangeComboVcaType();
	virtual void OnCancel();
	afx_msg void OnBtnMaskRegion();
	afx_msg void OnBtnEnterRegion();
	afx_msg void OnBtnCopyDay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	// data
	LONG	m_lServerID;
	int		m_iStartChannel;
	int     m_iDevIndex;
	int     m_iChannelnumber; //number of channels
	DWORD	m_dwAlarmOutNum;//

	int		m_iVcaChannel;//current ivms channel
	
	//IVMS
	NET_IVMS_BEHAVIORCFG m_struIvmsBehaviorCfg;
	NET_IVMS_STREAMCFG m_struIVMSStreamCfg; //IVMS config
	NET_IVMS_RULECFG m_struIvmsRuleCfg;//IVMS behavior config 

	NET_VCA_CTRLCFG m_struVcaCtrlCfg; //VCA control config
	NET_VCA_BEHAVIOR_ABILITY m_struBehaviorAbility; // channel behavior ability gotten from channel type
	NET_VCA_DRAW_MODE m_struVCADrawMode;//DSP target overlay mode
	CRect m_rcWndRect;//player window
	long m_lPlayHandle;//player handle
	
	DWORD m_dwPosNum;
	NET_VCA_POLYGON m_struVcaPolygon[MAX_RULE_NUM];
	NET_VCA_LINE m_struVcaLine[MAX_RULE_NUM];
	BOOL m_bCloseIn[MAX_RULE_NUM];
	BOOL m_bNeedRedraw[MAX_RULE_NUM];
	BOOL m_bMouseMove[MAX_RULE_NUM];
	
	int  m_iCurRuleID; //current rule ID
	
	int m_iWeekday; //current day.
	int m_iTimePeriod;//current time period

	NET_IVMS_MASK_REGION_LIST m_struIVMSMaskList;//config struct of mask region
	NET_IVMS_ENTER_REGION m_struIVMSEnterRegion;// config struct of enter region

	int m_lUserID;//user ID of front-end device

	//fun
	BOOL GetIvmsStreamPara(); // Get fetching stream config of iVMS
	BOOL SetIvmsStreamCfg(); // Set iVMS config

	BOOL GetIvmsBehaviorCfg(); //IVMS behavior analysis rule
	BOOL SetIvmsBehaviorCfg(); //Set IVMS behavior analysis rule

	BOOL SetMaskRegion(); //Set mask region
	BOOL GetMaskRegion(); // Get mask region config

	BOOL SetEnterRegion(); //Set enter region
	BOOL GetEnterRegion(); // Get enter region config
	void SetVcaDrawMode(); // Set DSP target overlay
	BOOL GetVcaDrawMode(); //Get DSP target overlay

	void GetDevVcaChanPara(); //Get all channels' ability
	//BOOL GetVcaPara(int iChannel,NET_VCA_CHAN_IN_PARAM struVcaChanInpara); //

	void StartPlay(int iTimeWeekday, int iTimePeriod); //start preview accroding to fetching stream schedule
	void StopPlay(); //stop preview in rule config

	//draw
	void F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser);
	void F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser, DWORD dwRuleID, COLORREF color);
	void F_DrawFilter(long lRealHandle, HDC hDc, DWORD dwUser, DWORD dwRuleID, COLORREF color);// draw area
	BOOL IsCrossLine(NET_VCA_POLYGON *alarm_region);
	BOOL IsValidArea(NET_VCA_POLYGON *alarm_region);
	BOOL F_IsACrossLine(NET_VCA_POLYGON *alarm_region);
	void F_AddLabel(HDC hDc, int iAlarmType, DWORD dwRuleID);
	BOOL F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2);
	BOOL F_IsStraightLine(NET_VCA_POLYGON *alarm_region);
	void F_DrawArrowhead(HDC hDc, DWORD dwRuleID, int direction);
	void F_DrawLine(long lPlayHandle, HDC hDc, DWORD dwUser, DWORD dwRuleID, COLORREF color);

	BOOL GetTimeSchedPara(int nWeekday, int nTimePeriod); //get parameters according to fetching stream schedule
	BOOL GetIVMSRuleCfg(NET_IVMS_RULECFG struIvmsBehaviorCfg, int iRUleID);

	VCA_EVENT_TYPE GetEventType(int num);
	void SetVcaEventPara(NET_VCA_EVENT_UNION &uEventparam, VCA_EVENT_TYPE struEventType);
	BOOL InsertComboVcaType();
	void SetComboVcaType(BYTE byVcaType);
	BOOL InsertRuleID(int RuleNum);
	BOOL InsertRuleType(int iBehaviorAbilityType);
	BOOL EnableRuleWindow(BOOL bEnable);
	BOOL GetEventTypeSet(VCA_EVENT_TYPE struEventType);
	BOOL GetIvmsOneRuleSet(NET_IVMS_ONE_RULE struIvmsRule);
	void GetEventParaSet(VCA_EVENT_TYPE struEventType,NET_VCA_EVENT_UNION uEventParam);
	BOOL ShowRuleTypeWnd(VCA_EVENT_TYPE struEventType);
	BOOL EnableVcaWindow(BOOL bEnable);
	BOOL SetRuleActiveAble(BOOL bEnable);
	BOOL SetOneIvmsRule(NET_IVMS_ONE_RULE &struIvmsRule);
	BOOL GetIVMSChanAbility(int m_iVcaChannel, NET_VCA_CHAN_IN_PARAM struVcaChanInparam);
	void RefreshVcaCtrl();


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAIVMSCFG_H__CA7E1DC1_5C22_4E94_9028_BCDBEC034AC1__INCLUDED_)
