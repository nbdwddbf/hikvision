#if !defined(AFX_DIALOGRECORDTIMESPAN_H__01F0EC22_2242_40AE_BB56_6A25ABE683BE__INCLUDED_)
#define AFX_DIALOGRECORDTIMESPAN_H__01F0EC22_2242_40AE_BB56_6A25ABE683BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogRecordTimeSpan.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogRecordTimeSpan dialog

class CDialogRecordTimeSpan : public CDialog
{
// Construction
public:
	CDialogRecordTimeSpan(CWnd* pParent = NULL);   // standard constructor

	LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;

// Dialog Data
	//{{AFX_DATA(CDialogRecordTimeSpan)
	enum { IDD = IDD_DLG_RECORD_TIME_SPAN };
	CComboBox	m_comboRecordTypeReturn;
	CComboBox	m_comboRecordType;
	CTime	m_StartDate;
	CTime	m_StopDate;
	CTime	m_StartTime;
	CTime	m_StopTime;
	int		m_iCurrentChan;
	CString	m_csStartTime;
	CString	m_csStopTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogRecordTimeSpan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogRecordTimeSpan)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnButtonInruiry();
	afx_msg void OnButtonExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGRECORDTIMESPAN_H__01F0EC22_2242_40AE_BB56_6A25ABE683BE__INCLUDED_)
