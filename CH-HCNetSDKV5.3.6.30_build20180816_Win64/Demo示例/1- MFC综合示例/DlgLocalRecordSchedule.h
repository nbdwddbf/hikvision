#pragma once
#include "afxwin.h"


// CDlgLocalRecordSchedule dialog

class CDlgLocalRecordSchedule : public CDialog
{
	DECLARE_DYNAMIC(CDlgLocalRecordSchedule)

public:
	CDlgLocalRecordSchedule(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgLocalRecordSchedule();

// Dialog Data


public:
	//{{AFX_DATA(CDlgLocalRecordSchedule)
	enum { IDD = IDD_DLG_LOCAL_RECORD_SCHEDULE };
	CComboBox m_comboScheduleWeekday;
	CComboBox m_comboCopyWeekday;
	int m_iHour11;
	int m_iMin11;
	int m_iHour12;
	int m_iMin12;
	int m_iHour21;
	int m_iMin21;
	int m_iHour22;
	int m_iMin22;
	int m_iHour31;
	int m_iMin31;
	int m_iHour32;
	int m_iMin32;
	int m_iHour41;
	int m_iMin41;
	int m_iHour42;
	int m_iMin42;
	int m_iHour51;
	int m_iMin51;
	int m_iHour52;
	int m_iMin52;
	int m_iHour61;
	int m_iMin61;
	int m_iHour62;
	int m_iMin62;
	int m_iHour71;
	int m_iMin71;
	int m_iHour72;
	int m_iMin72;
	int m_iHour81;
	int m_iMin81;
	int m_iHour82;
	int m_iMin82;
	//}}AFX_DATA



	//{{AFX_VIRTUAL(CDlgLocalRecordSchedule)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgLocalRecordSchedule)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedLocalRecOk();
	afx_msg void OnBnClickedLocalRecExit();
	afx_msg void OnBnClickedBtnRecCopy();
	afx_msg void OnCbnSelchangeComboWeekday();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	
	
};
