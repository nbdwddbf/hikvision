#if !defined(AFX_DLGVCAALARMTIMECFG_H__627F8064_E0DD_4335_866B_937541080D49__INCLUDED_)
#define AFX_DLGVCAALARMTIMECFG_H__627F8064_E0DD_4335_866B_937541080D49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaAlarmTimeCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaAlarmTimeCfg dialog

class CDlgVcaAlarmTimeCfg : public CDialog
{
	// Construction
public:
	CDlgVcaAlarmTimeCfg(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CDlgVcaAlarmTimeCfg)
	enum { IDD = IDD_DLG_VCA_ALARMTIMECFG };
	CComboBox	m_comboCopyWeek;
	CComboBox	m_comboWeek;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaAlarmTimeCfg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CDlgVcaAlarmTimeCfg)
	afx_msg void OnBtnSave();
	afx_msg void OnSelchangeComboWeek();
	afx_msg void OnBtnCopy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void InitAlarmTimeCfg(NET_DVR_SCHEDTIME strArryAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_V30]);
	void GetAlarmTimeCfg(NET_DVR_SCHEDTIME struArryAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_V30]);
protected:
	void InitCtrlState();
	void LoadDayAlarmTime(int nDayIndex);
	void SaveDayAlarmTime(int nDayIndex);
	
	BOOL ValidateData();
	BOOL ValidateOneDayAlarmTime(int nDayIndex);
private:
	int m_ArryTimeSegBeginHour[MAX_TIMESEGMENT_V30];
	int m_ArryTimeSegBeginMin[MAX_TIMESEGMENT_V30];
	int m_ArryTimeSegEndHour[MAX_TIMESEGMENT_V30];
	int m_ArryTimeSegEndMin[MAX_TIMESEGMENT_V30];
	NET_DVR_SCHEDTIME m_strArryAlatmTime[MAX_DAYS][MAX_TIMESEGMENT_V30];
	int m_nPreSelDayIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAALARMTIMECFG_H__627F8064_E0DD_4335_866B_937541080D49__INCLUDED_)
