#if !defined(AFX_DLGTPSRULECFG_H__60CF83DC_E2BC_44B6_8B92_94F1D3D20F71__INCLUDED_)
#define AFX_DLGTPSRULECFG_H__60CF83DC_E2BC_44B6_8B92_94F1D3D20F71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTPSRuleCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTPSRuleCfg dialog

class CDlgTPSRuleCfg : public CDialog
{
// Construction
public:
	CDlgTPSRuleCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTPSRuleCfg)
	enum { IDD = IDD_DLG_VCA_TPS_RULECFG };
	CComboBox	m_comboFilterMode;
	CListCtrl	m_listAlarmOut;
	CComboBox	m_comboLaneID;
	CComboBox	m_comboTPSIndex;
	CComboBox	m_comboWeekday;
	CComboBox	m_comboCopyTime;
	CListCtrl	m_listTPSType;
	BOOL	m_bEnable;
	BOOL	m_bFilterActive;
	BOOL	m_bSetMaxFilter;
	BOOL	m_bSetMiniFilter;
	BOOL	m_bHandleType1;
	BOOL	m_bHandleType2;
	BOOL	m_bHandleType3;
	BOOL	m_bHandleType4;
	BOOL	m_bHandleType5;
	BOOL	m_bDrawPolygon;
	float	m_fMaxHeight;
	float	m_fMaxWidth;
	float	m_fMinHeight;
	float	m_fMinWidth;
	int		m_iHour11;
	int		m_iMin11;
	int		m_iHour12;
	int		m_iMin12;
	int		m_iHour21;
	int		m_iMin21;
	int		m_iHour22;
	int		m_iMin22;
	int		m_iHour31;
	int		m_iMin31;
	int		m_iHour32;
	int		m_iMin32;
	int		m_iHour41;
	int		m_iMin41;
	int		m_iHour42;
	int		m_iMin42;
	int		m_iHour51;
	int		m_iMin51;
	int		m_iHour52;
	int		m_iMin52;
	int		m_iHour61;
	int		m_iMin61;
	int		m_iHour62;
	int		m_iMin62;
	int		m_iHour71;
	int		m_iMin71;
	int		m_iHour72;
	int		m_iMin72;
	int		m_iHour81;
	int		m_iMin81;
	int		m_iHour82;
	int		m_iMin82;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTPSRuleCfg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTPSRuleCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboCalcId();
	afx_msg void OnBtnSetTpsRulecfg();
	afx_msg void OnSelchangeComboTpsIndex();
	afx_msg void OnSelchangeComboweekday();
	afx_msg void OnTimeOk();
	afx_msg void OnTimeCopy();
	afx_msg void OnCheckDrawVirtualLoop();
	afx_msg void OnCheckFilterActive();
	afx_msg void OnCheckSetMiniFilter();
	afx_msg void OnCheckSetMaxFilter();
	afx_msg void OnSelchangeComboFilterMode();
	afx_msg void OnBtnConfirm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    int     m_iDevIndex;
    LONG    m_lServerID;
    LONG    m_lChannel;
    NET_DVR_TPS_RULECFG_V41 m_struTPSRuleCfg;
    NET_DVR_LANE_CFG m_struLaneCfg;

    LONG    m_lPlayHandle;

    int     m_iTPSIndex;
    DWORD	m_dwAlarmOutNum; // 报警输出的个数

    DWORD   m_dwPosNum; 
    CRect   m_rcWnd;
    BOOL    m_bCloseIn[MAX_AID_RULE];
    BOOL    m_bMouseMove[MAX_AID_RULE];
    BOOL    m_bNeedRedraw[MAX_AID_RULE];
    NET_VCA_POLYGON m_struVcaPolygon[MAX_AID_RULE];

    NET_VCA_CHAN_IN_PARAM m_struVcaChanInParam;
    NET_DVR_ITS_ABILITY m_struItsAbility;
    
    NET_DVR_PU_STREAM_CFG m_struPUStream;
    LONG    m_lPUServerID;
    
    LONG StartPlay();
    BOOL StopPlay();

    BOOL F_TimeTest();
    BOOL SetTPSRuleCfg();
    BOOL GetTPSRuleCfg();
    BOOL GetLaneCfg();
    BOOL GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream);

    BOOL SetTPSRuleToWnd(NET_DVR_TPS_RULECFG_V41 const &struTpsRule);
    BOOL GetTPSRuleFromWnd(NET_DVR_TPS_RULECFG_V41  &struTpsRule);

    
    BOOL SetOneTpsRuleToWnd(NET_DVR_ONE_TPS_RULE_V41 const &struOneTpsRule);
    BOOL GetOneTpsRuleFromWnd(NET_DVR_ONE_TPS_RULE_V41 &struOneTpsRule);

    

    BOOL SetHandleExceptionToWnd(NET_DVR_HANDLEEXCEPTION_V30 const &struHandleType,int nAlarmNum);
    BOOL GetHandleExceptionFromWnd(NET_DVR_HANDLEEXCEPTION_V30 &struHandleType);


    BOOL InitWnd();
    BOOL PreDrawSizeFilterMsg(MSG* pMsg, CPoint &pt);
    BOOL PreDrawPolygonMsg(MSG* pMsg, CPoint &pt);
    void F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser);

    void DrawLane(HDC hDc);

    void SetSizeFilterToWnd(const NET_VCA_SIZE_FILTER &struSizeFilter);
    void EnableFilterModeWnd(BYTE byMode);
    void GetSizeFilterFromWnd(NET_VCA_SIZE_FILTER &struSizeFilter);
    BOOL GetVcaChanAbility();

	void SetAlarmTimeToWnd(NET_DVR_SCHEDTIME const *pAlarmTime, int nDay);
    void GetAlarmTimeFromWnd(NET_DVR_SCHEDTIME *pAlarmTime, int nDay);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTPSRULECFG_H__60CF83DC_E2BC_44B6_8B92_94F1D3D20F71__INCLUDED_)
