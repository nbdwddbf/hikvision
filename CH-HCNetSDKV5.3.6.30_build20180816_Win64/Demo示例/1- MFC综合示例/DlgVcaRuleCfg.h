#if !defined(AFX_DLGVCARULECFG_H__B678DBAB_24C9_4063_A990_784B443D35E7__INCLUDED_)
#define AFX_DLGVCARULECFG_H__B678DBAB_24C9_4063_A990_784B443D35E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaRuleCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaRuleCfg dialog
#include "DrawFun.h"
class CDlgVcaRuleCfg : public CDialog
{
// Construction
public:
	CDlgVcaRuleCfg(CWnd* pParent = NULL);   // standard constructor
    enum
	{
		TRIGGER_MODE_NONE       = 0,
		TRIGGER_MODE_TRACKPOINT = 1,
		TRIGGER_MODE_TARGETAREA = 2
	};

	enum
	{
		TRIGGER_POINT_CENTER = 0,
		TRIGGER_POINT_UP     = 1,
		TRIGGER_POINT_DOWN   = 2,
	};
	enum
	{
		FILTER_STRATEGY_NONE             = 0,
		FILTER_STRATEGY_WIDTH_AND_HEIGHT = 1,
		FILTER_STRATEGY_AERA             = 2
	};
// Dialog Data
	//{{AFX_DATA(CDlgVcaRuleCfg)
	enum { IDD = IDD_DLG_VCA_RULE_CFG };
	CComboBox	m_comDetectMode;
	CComboBox	m_comboRelSnapChan3;
	CComboBox	m_comboRelSnapChan2;
	CComboBox	m_comboRelSnapChan1;
	CComboBox	m_comboPersonType;
	CComboBox	m_comboFilterStrategy;
	CComboBox	m_comboTriggerPoint;
	CComboBox	m_comboTriggerMode;
	CTreeCtrl	m_treeAlarmOut;
	CComboBox	m_comboEventParamMode;
	CStatic	m_staticDelayTime;
	CComboBox	m_comboAudioMode;
	CComboBox	m_comboAlarmDelay;
	CComboBox	m_cmUpLastAlarm;
	CComboBox	m_comboRunMode;
	CComboBox	m_comboFilterMode;
	CStatic	m_staticAlarmArea;
	CStatic	m_staticAlarmText;
	CComboBox	m_comboAlarmDirect;
	CListCtrl	m_listRecordChan;
	CComboBox	m_comboWeekday;
	CComboBox	m_comboCopyTime;
	CComboBox	m_comboSensitive;
	CComboBox	m_comboRuleType;
	CComboBox	m_comboRuleID;
	CComboBox	m_comboResolution;
	CComboBox	m_comboProPicType;
	CComboBox	m_comboPicQuality;
	BOOL	m_bFilterActive;
	BOOL	m_bSetMaxFilter;
	BOOL	m_bSetMiniFilter;
	BOOL	m_bHandleType1;
	BOOL	m_bHandleType2;
	BOOL	m_bHandleType3;
	BOOL	m_bHandleType4;
	BOOL	m_bHandleType5;
	BOOL	m_bDrawPolygon;
	BOOL	m_bRuleActive;
	CString	m_csRuleName;
	int		m_iHour11;
	int		m_iHour12;
	int		m_iHour21;
	int		m_iHour22;
	int		m_iMin11;
	int		m_iMin12;
	int		m_iMin21;
	int		m_iMin22;
	int		m_iAlarmPersist;
	BOOL	m_bDrawLine;
	float	m_fAlarmRate;
	float	m_fMinHeight;
	float	m_fMinWidth;
	float	m_fMaxHeight;
	float	m_fMaxWidth;
	DWORD	m_dwLeaveDelay;
	DWORD	m_dwStaticDelay;
	BOOL	m_bChkPicRecordEn;
	int		m_iHour31;
	int		m_iHour32;
	int		m_iHour41;
	int		m_iHour42;
	int		m_iHour51;
	int		m_iHour52;
	int		m_iHour61;
	int		m_iHour62;
	int		m_iHour71;
	int		m_iHour72;
	int		m_iHour81;
	int		m_iHour82;
	int		m_iMin31;
	int		m_iMin32;
	int		m_iMin41;
	int		m_iMin42;
	int		m_iMin51;
	int		m_iMin52;
	int		m_iMin61;
	int		m_iMin62;
	int		m_iMin71;
	int		m_iMin72;
	int		m_iMin81;
	int		m_iMin82;
	DWORD	m_dwEventDelayTime;
	float	m_fTriggerArea;
	BYTE	m_byHeightThreshold;
	BOOL	m_bNoneStateEffective;
	BYTE	m_byPeopleNumThreshold;
	float	m_fSpacingThreshold;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaRuleCfg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaRuleCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetRuleCfg();
    afx_msg void OnBtnSetOneRule();
	afx_msg void OnSelchangeComboRuleId();
	afx_msg void OnChkRuleActive();
	afx_msg void OnSelchangeComboRuleType();
	afx_msg void OnChkDrawPolygon();
	afx_msg void OnCheckFilterActive();
	afx_msg void OnCheckSetMiniFilter();
	afx_msg void OnCheckSetMaxFilter();
	afx_msg void OnChkDrawLine();
	afx_msg void OnSelchangeComlinealarmdirect();
	afx_msg void OnTimeOk();
	afx_msg void OnTimeCopy();
	afx_msg void OnSelchangeComboweekday();
	afx_msg void OnCheckhandletype4();
	afx_msg void OnChangeEditRuleName();
	afx_msg void OnSelchangeComboFilterMode();
	afx_msg void OnClickTreeAlarmOutRelate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnSelchangeComboTriggermode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	//Data
	LONG	m_lServerID;
	int     m_iDevIndex;
	int		m_iVcaChannel; 


	NET_VCA_RULECFG_V41 m_struRuleCfg;  
    NET_VCA_ONE_RULE_V41 m_struOneRule;
	NET_VCA_BEHAVIOR_ABILITY m_struBehaviorAbility;
    NET_VCA_CHAN_IN_PARAM m_struVcaChanInParam;
    NET_VCA_CTRLCFG     m_struVcaCtrlCfg;
    NET_VCA_SIZE_FILTER m_struSizeFilter;
    NET_DVR_PU_STREAM_CFG m_struPuStream;
	DWORD m_dwEventType;
    
	CRect m_rcWnd; 
	long m_lPlayHandle; 

	DWORD m_dwPosNum;  
	NET_VCA_POLYGON m_struVcaPolygon[MAX_RULE_NUM]; 
	NET_VCA_LINE m_struVcaLine[MAX_RULE_NUM]; 
	BOOL m_bCloseIn[MAX_RULE_NUM]; 
	BOOL m_bNeedRedraw[MAX_RULE_NUM]; 
	BOOL m_bMouseMove[MAX_RULE_NUM];  
	BOOL m_bAlarmOut[MAX_ALARMOUT_V30];

	int  m_iCurRuleID; 

    void F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser);

    LONG m_lPUServerID;

	BYTE m_byVCAType;
	BYTE m_byMode;
private:
    BOOL    GetVcaCtrlCfg();
    BOOL    GetVcaChanAbility();
    BOOL    GetVcaRuleCfg();
    BOOL    SetVcaRuleCfg();
    BOOL    GetVcaParam();

    void InitWnd();
    BOOL InitRuleType(int iBehaviorAbilityType, int iBehaviorAbilityTypeEx);  
    BOOL InitRuleID(int RuleNum); 

    void SetVcaRuleToWnd(NET_VCA_RULECFG_V41 const &struVcaRuleCfg);
    void GetVcaRuleFromWnd(NET_VCA_RULECFG_V41 &struVcaRuleCfg);
    void SetOneVcaRuleToWnd(NET_VCA_ONE_RULE_V41 const &struVcaOneRule);
    void GetOneVcaRuleFromWnd(NET_VCA_ONE_RULE_V41 &struOneRule);
    void SetEventTypeToWnd(DWORD dwEventType);
    DWORD GetEventTypeFromWnd();
    void SetEventUnionToWnd(NET_VCA_EVENT_UNION const & uEventParam, DWORD dwEventType);
    void GetEventUnionFromWnd(NET_VCA_EVENT_UNION &uEventParam, DWORD dwEventType);
    void SetSizeFilterToWnd(NET_VCA_SIZE_FILTER const &struSizeFilter);
    void GetSizeFilterFromWnd(NET_VCA_SIZE_FILTER &struSizeFilter);
    void SetHandleExceptionToWnd(NET_DVR_HANDLEEXCEPTION_V30 const &struHandleException);
    void GetHandleExceptionFromWnd(NET_DVR_HANDLEEXCEPTION_V30 &struHandleException);
    void SetRelRecordChanToWnd(BYTE const *byRelRecordChan, int nChanNum);
    void GetRelRecordChanFromWnd(BYTE *byRelRecordChan, int nChanNum);
    void SetAlarmTimeToWnd(NET_DVR_SCHEDTIME const *pAlarmTime, int nDay);
    void GetAlarmTimeFromWnd(NET_DVR_SCHEDTIME *pAlarmTime, int nDay);
	void SetFilterStrategyToWnd(NET_VCA_FILTER_STRATEGY const&struFilterStrategy);
	void GetFilterStrategyFromWnd(NET_VCA_FILTER_STRATEGY* pFilterStrategy);
	void SetRuleTriggerParamToWnd(NET_VCA_RULE_TRIGGER_PARAM const &struRuleTriggerParam);
	void GetRuleTriggerParamFromWnd(NET_VCA_RULE_TRIGGER_PARAM* pRuleTriggerParam);

    LONG StartPlay();
    BOOL StopPlay();

    BOOL EnableRuleWindow(BOOL bEnable);
    BOOL EnablAlarmTime(BOOL bEnable);
    BOOL EnableHandleException(BOOL bEnable);
    BOOL EnableSizeFilter(BOOL bEnable);
    BOOL ShowRuleTypeWnd(VCA_RULE_EVENT_TYPE_EX struEventType); 

    void F_DrawFrame(HDC hDc);
    void F_DrawFilter(HDC hDc);
    void F_DrawLine(HDC hDc);
    BOOL F_TimeTest(); 

    void ShowPixMode(int nCmdShow);
    void ShowRealMode(int nCmdShow);
    void ShowDefaultMode(int nCmdShow);

    BOOL GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream);
	void CreateTree(void);
	void CreateAlarmOutTree(CTreeCtrl &m_treeAlarmOut, int iDeviceIndex, BOOL *bAlarmOut);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCARULECFG_H__B678DBAB_24C9_4063_A990_784B443D35E7__INCLUDED_)
