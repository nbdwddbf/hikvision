#if !defined(AFX_DLGRECPASSBACKSCHECFG_H__651D7391_116A_4F64_8A40_A9F1C6805626__INCLUDED_)
#define AFX_DLGRECPASSBACKSCHECFG_H__651D7391_116A_4F64_8A40_A9F1C6805626__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecPassBackScheCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRecPassBackScheCfg dialog

class CDlgRecPassBackScheCfg : public CDialog
{
// Construction
public:
	CDlgRecPassBackScheCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecPassBackScheCfg)
	enum { IDD = IDD_DLG_RECORD_PASS_BACK_SCHEDULE };
	CComboBox m_comboWeekday;
	BOOL m_bCheckAllDay; 
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
	BOOL	m_bChkAllWeek;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecPassBackScheCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRecPassBackScheCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnRemoteRecOk();
	afx_msg void OnBnClickedBtnRemoteRecExit();	
	afx_msg void OnBnClickedBtnRemoteRecCopy();
	afx_msg void OnCbnSelchangeComboWeekDay();
	afx_msg void OnBnClickedChkAllDay();
	afx_msg void OnChkAllWeek();
	afx_msg void OnBnClickedBtnPassbackAllWeekOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int m_nDate;
	int m_nCopyDate;
	void EnableControlAllDay(BOOL bEnable);
	void EnableControlAllWeek(BOOL bEnable);
	BOOL TimeTest();

	LPNET_DVR_RECORD_PASSBACK_SCH_CFG m_pStruRecordPassBackSchCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECPASSBACKSCHECFG_H__651D7391_116A_4F64_8A40_A9F1C6805626__INCLUDED_)
