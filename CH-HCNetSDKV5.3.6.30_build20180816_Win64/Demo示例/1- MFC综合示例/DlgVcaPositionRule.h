#include "afxwin.h"
#if !defined(AFX_DLGVCAPOSITIONRULE_H__694D24A1_D9F6_4B68_8002_68E05DDCAECE__INCLUDED_)
#define AFX_DLGVCAPOSITIONRULE_H__694D24A1_D9F6_4B68_8002_68E05DDCAECE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaPositionRule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaPositionRule dialog

class CDlgVcaPositionRule : public CDialog
{
// Construction
public:
	CDlgVcaPositionRule(CWnd* pParent = NULL);   // standard constructor
    ~CDlgVcaPositionRule();
// Dialog Data
	//{{AFX_DATA(CDlgVcaPositionRule)
	enum { IDD = IDD_DLG_VCA_POSITION_RULE };
	CTreeCtrl	m_treeChannel;
	CTreeCtrl	m_treeAlarmout;
	CComboBox	m_comDetTarget;
    CComboBox	m_comEventPriority;
	CComboBox	m_cmbVCARuleGroupNo;
	CComboBox	m_cmbVCARuleChannel;
	CComboBox	m_comboZoomMode;
	CComboBox	m_comboTrackingMode;
	CComboBox	m_comboPositionIndex;
    CComboBox	m_comboRuleSequence;
    DWORD   m_dwMinInterval;
    DWORD   m_dwMaxInterval;
    BYTE    m_byRuleID1;
    BYTE    m_byRuleID2;   
	CStatic	m_staticStickupAlarmPersist;
	CComboBox	m_comboAtmMode;
	CStatic	m_staticAlarmDirect;
	CComboBox	m_comboAlarmDirect;
	CStatic	m_staticMaxDistanceArea;
	CStatic	m_staticDenstityRateArea;
	CStatic	m_staticAlarmPersistArea;
	CStatic	m_staticAlarmDelayArea;
	CStatic	m_staticReadCardTimePersistArea;
	CEdit	m_editAlarmPersist;
	CEdit	m_editDenstityRate;
	CEdit	m_editReadCardTimePersist;
	CEdit	m_editMaxDistance;
	CEdit	m_editAlarmDelay;
	CStatic	m_staticReadCardTimePersist;
	CStatic	m_staticMaxDistance;
	CStatic	m_staticDenstityRate;
	CStatic	m_staticAlarmPersist;
	CStatic	m_staticAlarmDelay;
	CComboBox	m_comboWeekday;
	CComboBox	m_comboCopyTime;
	CComboBox	m_comboVcaType;
	CComboBox	m_comboVcaChan;
	CComboBox	m_comboStream;
	CComboBox	m_comboSensitive;
	CComboBox	m_comboRuleType;
	CComboBox	m_comboRuleID;
	CComboBox	m_comboResolution;
	CComboBox	m_comboProPicType;
	CComboBox	m_comboPicQuality;
	BOOL	m_bDSPAddRule;
	BOOL	m_bDSPAddTarget;
	BOOL	m_bPicAddRule;
	BOOL	m_bPicAddTarget;
	BOOL	m_bFilterActive;
	BOOL	m_bSetMaxFilter;
	BOOL	m_bSetMiniFilter;
	BOOL	m_bVcaActive;
	BOOL	m_bHandleType1;
	BOOL	m_bHandleType2;
	BOOL	m_bHandleType3;
	BOOL	m_bHandleType4;
	BOOL	m_bHandleType5;
    BOOL	m_bHandleType6;
	BOOL	m_bDrawPolygon;
	BOOL	m_bRuleActive;
	int		m_iBAdvanceChanNum;
	int		m_iBBaseChanNum;
	int		m_iBFullChanNum;
	int		m_iPlateChanNum;
	int		m_iVcaChanNum;
	CString	m_csRuleName;
	int		m_iHour11;
	int		m_iHour12;
	int		m_iHour21;
	int		m_iHour22;
	int		m_iMin11;
	int		m_iMin12;
	int		m_iMin21;
	int		m_iMin22;
	int		m_iAlarmDelay;
	int		m_iAlarmPersist;
	float	m_fMaxDistance;
	float	m_fDenstityRate;
	int		m_iReadCardTimePersist;
	BOOL	m_bDrawLine;
	int		m_iAtmChanNum;
	CString	m_csPtzPositionName;
	BOOL	m_bChkTrackEn;
	DWORD	m_dwTrackTime;
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
	BOOL	m_bChkPositionEn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaPositionRule)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaPositionRule)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetRuleCfg();
	afx_msg void OnBtnSetVcaCtrl();
	afx_msg void OnBtnRefesh();
	afx_msg void OnBtnSetOneRule();
	afx_msg void OnBtnVcaRestart();
	afx_msg void OnBtnSetVcaDrawMode();
	afx_msg void OnSelchangeComboVcaChan();
	afx_msg void OnCheckVcaActive();
	afx_msg void OnSelchangeComboRuleId();
	virtual void OnCancel();
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
	afx_msg void OnChangeEditAlarmDelay();
	afx_msg void OnChangeEditAlarmPersist();
	afx_msg void OnChangeEditDenstityRate();
	afx_msg void OnChangeEditMaxDistance();
	afx_msg void OnChangeEditReadCardTimePersist();
	afx_msg void OnBtnTrackCfg();
	afx_msg void OnBtnGetPtz();
	afx_msg void OnBtnPtzCtrl();
	afx_msg void OnBtnEnableCalibrate();
	afx_msg void OnBtnDomeConfig();
	afx_msg void OnSelchangeComboPositionIndex();
	afx_msg void OnBtnPositionTrack();
	afx_msg void OnBtnPositionLimitangle();
	afx_msg void OnBtnGetRuleCfg();
	afx_msg void OnClickTreeChannelVca(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeAlarmout(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSetPtz();
	afx_msg void OnBtnPtzLockcfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	//Data
	LONG	m_lServerID;
	int		m_iStartChannel; // start chan
	int     m_iDevIndex;
	int     m_iChannelnumber; // chan num
	DWORD	m_dwAlarmOutNum; // alarm out num

    int		m_iVcaChannel; // current vca channel
    int     m_iPositionIndex;// scence index
    NET_DVR_POSITION_RULE_CFG_V41 m_struPositionRule;
    NET_VCA_RULECFG_V42 m_struRuleCfgV42;
    NET_DVR_CHANNEL_GROUP m_struChanGroup;
    NET_DVR_PTZ_POSITION m_struPtzPosition;

	NET_VCA_CTRLCFG m_struVcaCtrlCfg; 
	NET_VCA_BEHAVIOR_ABILITY m_struBehaviorAbility; // channel behavior ability
	NET_VCA_RULECFG_V41 m_struRuleCfg;  
	NET_VCA_ONE_RULE_V41 m_struOneRule;
	NET_VCA_DRAW_MODE m_struVCADrawMode; 
    NET_VCA_RULECFG_V41 m_struRuleCfgEx;

	CRect m_rcWndRect; 
	long m_lPlayHandle; 

	DWORD m_dwPosNum;
	NET_VCA_POLYGON m_struVcaPolygon[MAX_RULE_NUM_V42]; 
	NET_VCA_LINE m_struVcaLine[MAX_RULE_NUM_V42];
	BOOL m_bCloseIn[MAX_RULE_NUM_V42]; 
	BOOL m_bNeedRedraw[MAX_RULE_NUM_V42]; 
	BOOL m_bMouseMove[MAX_RULE_NUM_V42]; 

	NET_DVR_SCHEDTIME m_struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_V30]; 

	int  m_iCurRuleID; 
    NET_DVR_TRACK_CFG m_struTrackCfg;

	//Fun
    void GetDevVcaChanPara(); 
	BOOL InsertComboVcaType(); 
	void SetComboVcaType();   
	BOOL EnableVcaWindow(BOOL bEnable);
	BOOL EnableRuleWindow(BOOL bEnable);
	BOOL GetVcaPara(int iChannel,NET_VCA_CHAN_IN_PARAM struVcaChanInpara); 
	BOOL InsertRuleType(int iBehaviorAbilityType, int iBehaviorAbilityTypeEx); 
	BOOL InsertRuleID(int RuleNum); 
	BOOL GetRuleCfg();
	BOOL SetRuleActiveAble(BOOL bEnable);
//	int  SetComboAlarmType(VCA_EVENT_TYPE uEVentType);
	BOOL SetOneRule(NET_VCA_ONE_RULE_V41 &struVcaOneRule); 
	BOOL GetEventTypeSet(VCA_EVENT_TYPE struEventType, WORD wEventType = 0); 
    BOOL SaveOneRule(NET_VCA_ONE_RULE_V41 &struVcaOneRule);

	BOOL F_TimeTest();
	void SetTimePara(); 
	void SetAlarmPara(NET_DVR_HANDLEEXCEPTION_V30 &struHandleType); 
	void SetVcaEventPara(NET_VCA_EVENT_UNION &uEventparam, VCA_EVENT_TYPE struEventType, WORD wEventTypeEx);
    void SetVcaEventParaV42(NET_VCA_EVENT_UNION &uEventparam, WORD wEventType);

	BOOL RefreshOneRule(NET_VCA_ONE_RULE_V41 struVcaOneRule); 
	VCA_EVENT_TYPE GetEventType(int num); 
	void SetRelRecordChan(NET_VCA_ONE_RULE_V41 &struVcaOneRule, int nChanNum); 

	void ShowAlarmNum(NET_VCA_ONE_RULE_V41 struVcaOneRule,int nAlarmNum); 
	void GetEventParaSet(VCA_EVENT_TYPE struEventType,NET_VCA_EVENT_UNION uEventParam, WORD wEventTypeEx); 
	BOOL F_ShowRecordChan(NET_VCA_ONE_RULE_V41 struVcaOneRule, int nChanNum); 

	BOOL ShowRuleTypeWnd(VCA_EVENT_TYPE struEventType, WORD wEventTypeEx);

	//drae
	void F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser);
	void F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser, DWORD dwRuleID, COLORREF color);
	void F_DrawFilter(long lRealHandle, HDC hDc, DWORD dwUser, DWORD dwRuleID, COLORREF color);
	BOOL IsCrossLine(NET_VCA_POLYGON *alarm_region);
	BOOL IsValidArea(NET_VCA_POLYGON *alarm_region);
	BOOL F_IsACrossLine(NET_VCA_POLYGON *alarm_region);
	void F_AddLabel(HDC hDc, int iAlarmType, DWORD dwRuleID);
	BOOL F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2);
	BOOL F_IsStraightLine(NET_VCA_POLYGON *alarm_region);
	void F_DrawArrowhead(HDC hDc, DWORD dwRuleID, int direction);
	void F_DrawLine(long lPlayHandle, HDC hDc, DWORD dwUser, DWORD dwRuleID, COLORREF color);

	void SetRuleBehaviorCfg();
    void SaveTempRuleBehaviorCfg();

	//draw mode
	void SetVcaDrawMode(); 
	BOOL GetVcaDrawMode(); 

    void RefreshBehavior(int iPosition, int iRuleID);

    BOOL GetTrackCfg();
    BOOL SetTrackCfg();
    BOOL EventTypeToEventTypeEx(VCA_EVENT_TYPE struEventType, WORD& wEventTypeEx);
    BOOL EventTypeExToEventType(VCA_EVENT_TYPE& struEventType, WORD wEventTypeEx);
    void OneRuleV41ToOneRuleV42(NET_VCA_ONE_RULE_V41* lpOld, NET_VCA_ONE_RULE_V42* lpV42, BOOL bV41ToV42);
    BOOL *m_pbChannel;
    BOOL *m_pbAlarmOut;
private:
	//Data
	//Fun
public:
    CComboBox m_comboPriority;
    int m_iParam1;
    int m_iParam2;
    int m_iParam3;
    int m_iParam4;
    int m_iParam5;
    int m_iParam6;
    afx_msg void OnCbnSelchangeComboPositionChannel();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAPOSITIONRULE_H__694D24A1_D9F6_4B68_8002_68E05DDCAECE__INCLUDED_)
