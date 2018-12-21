#if !defined(AFX_DLGHOLIDAYCFG_H__B29B7A8E_BA82_4DBE_9969_D5EADE9417B3__INCLUDED_)
#define AFX_DLGHOLIDAYCFG_H__B29B7A8E_BA82_4DBE_9969_D5EADE9417B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHolidayCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgHolidayCfg dialog

class CDlgHolidayCfg : public CDialog
{
// Construction
public:
	CDlgHolidayCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgHolidayCfg)
	enum { IDD = IDD_DLG_HOLIDAY_CFG };
	CComboBox	m_comboStopWeekdayB;
	CComboBox	m_comboStartWeekdayB;
	CComboBox	m_comboHolidayIndex;
	CComboBox	m_comboHoliDateMode;
	CString	m_csHolidayName;
	BOOL	m_bEnable;
	int		m_iEndDayA;
	int		m_iEndDayC;
	int		m_iEndMonthB;
	int		m_iEndMonthC;
	int		m_iEndWeeknumB;
	int		m_iEndYearC;
	int		m_iEndMonthA;
	int		m_iStartDayC;
	int		m_iStartMonthA;
	int		m_iStartMonthB;
	int		m_iStartMonthC;
	int		m_iStartWeeknumB;
	int		m_iStartYearC;
	int		m_iStartDayA;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHolidayCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHolidayCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboHoliDateMode();
	afx_msg void OnSelchangeComboHolidayIndex();
	afx_msg void OnBtnConfirm();
	afx_msg void OnBtnSetUp();
	afx_msg void OnButtonUpdate();
	afx_msg void OnButtonExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    NET_DVR_HOLIDAY_PARAM_CFG  m_struHolidayParamCfg;
    

public:
    void InitWnd();
    void InitHolidayIndexCombo();
    void InitHoliDateModeCombo();
    void ShowHoliDateMode(int nDateMode);
    void ShowHoliDateModeA(int nCmdShow);
    void ShowHoliDateModeB(int nCmdShow);
    void ShowHoliDateModeC(int nCmdShow);
    
    BOOL GetHolidayParmCfg(NET_DVR_HOLIDAY_PARAM_CFG &struHolidayParmCfg);
    BOOL SetHolidayParmCfg(NET_DVR_HOLIDAY_PARAM_CFG &struHolidayParmCfg);

    void SetHolidayParamToWnd(NET_DVR_HOLIDAY_PARAM &struHolidayParam);
    void GetHolidayParamFromWnd(NET_DVR_HOLIDAY_PARAM &struHolidayParam);
    
    void GetHolidateUnionFromWnd(NET_DVR_HOLIDATE_UNION &uHolidate, int nDateMode);
    void SetHolidateUnionToWnd(NET_DVR_HOLIDATE_UNION &uHolidate, int nDateMode);

    void SetHoliDateModeAToWnd(NET_DVR_HOLIDATE_MODEA &struHolidateModeA);
    void GetHoliDateModeAFromWnd(NET_DVR_HOLIDATE_MODEA &struHolidateModeA);
    void SetHoliDateModeBToWnd(NET_DVR_HOLIDATE_MODEB &struHolidateModeB);
    void GetHoliDateModeBFromWnd(NET_DVR_HOLIDATE_MODEB &struHolidateModeB);
    void SetHoliDateModeCToWnd(NET_DVR_HOLIDATE_MODEC &struHolidateModeC);
    void GetHoliDateModeCFromWnd(NET_DVR_HOLIDATE_MODEC &struHolidateModeC);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHOLIDAYCFG_H__B29B7A8E_BA82_4DBE_9969_D5EADE9417B3__INCLUDED_)
