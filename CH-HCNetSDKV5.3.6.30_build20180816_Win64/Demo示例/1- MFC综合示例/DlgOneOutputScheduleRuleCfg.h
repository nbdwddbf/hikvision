#if !defined(AFX_ONEOUTPUTSCHEDULERULECFG_H__B0C1FF34_A781_4BF1_AFB4_CC58CD434095__INCLUDED_)
#define AFX_ONEOUTPUTSCHEDULERULECFG_H__B0C1FF34_A781_4BF1_AFB4_CC58CD434095__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OneOutputScheduleRuleCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COutputScheduleRuleCfg dialog

class CDlgOneOutputScheduleRuleCfg : public CDialog
{
	// Construction
public:
	CDlgOneOutputScheduleRuleCfg(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(COneOutputScheduleRuleCfg)
	enum { IDD = IDD_DLG_ONE_OUTPUT_SCHEDULE_RULECFG };
	CListCtrl m_listTrigger;
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COneOutputScheduleRuleCfg)
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(COneOutputScheduleRuleCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSaveSingle();
	afx_msg void OnSelchangeComboRuleno();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
protected:
	void InitCtrlState();
protected:
	BOOL GetOutputScheduleRuleCfg();
	//BOOL SetOutputScheduleRuleCfg();
	//void LoadWndRuleContent(int nRuleIndex);
	//void SaveWndRuleContent(int nRuleIndex);
public:
	LONG m_lUserID;
	LONG m_lChannel;
	int  m_iDeviceIndex;
	int  m_nCurRuleIndex;
private:
	BOOL          m_bArryOutputEnable[MAX_RULE_NUM];
	COleDateTime  m_dtArryOutputBeginTime[MAX_RULE_NUM];
	COleDateTime  m_dtArryOutputEndTime[MAX_RULE_NUM];
	CDateTimeCtrl m_dtCtrlArryBeginTime[MAX_RULE_NUM];
	CDateTimeCtrl m_dtCtrlArryEndTime[MAX_RULE_NUM];
	int           m_nBeginDate_month;
	int           m_nBeginDate_day;
	int           m_nEndDate_month;
	int           m_nEndDate_day;
	CComboBox     m_comboRuleNo;
	BOOL          m_bEnableRule;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONEOUTPUTSCHEDULERULECFG_H__B0C1FF34_A781_4BF1_AFB4_CC58CD434095__INCLUDED_)
