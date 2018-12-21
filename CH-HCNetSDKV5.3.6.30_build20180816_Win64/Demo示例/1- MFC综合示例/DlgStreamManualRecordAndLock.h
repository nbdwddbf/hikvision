#if !defined(AFX_DLGSTREAMMANUALRECORDANDLOCK_H__C024DFB1_488B_449B_A643_83DC1323F361__INCLUDED_)
#define AFX_DLGSTREAMMANUALRECORDANDLOCK_H__C024DFB1_488B_449B_A643_83DC1323F361__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStreamManualRecordAndLock.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamManualRecordAndLock dialog

class CDlgStreamManualRecordAndLock : public CDialog
{
// Construction
public:
	CDlgStreamManualRecordAndLock(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgStreamManualRecordAndLock)
	enum { IDD = IDD_DLG_STREAM_MANUAL_RECORD_AND_LOCK };
    CComboBox	m_cmbChannel;
	CComboBox	m_cmbLockRecordType;
	CComboBox	m_cmbManualRecordType;
	int		m_iChannel;
	CString	m_strStreamID;
	CTime	m_ctDateEnd;
	CTime	m_ctDateStart;
	CTime	m_ctTimeEnd;
	CTime	m_ctTimeStart;
	int		m_iLockDuration;
	CTime	m_ctDateEndReturn;
	CTime	m_ctDateStartReturn;
	CTime	m_ctTimeEndReturn;
	CTime	m_ctTimeStartReturn;
	CTime	m_ctUnlockTimePointDate;
	CTime	m_ctUnlockTimePointTime;
    BOOL	m_bAllAnalogChan;
	BOOL	m_bAllIPChan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgStreamManualRecordAndLock)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	virtual BOOL OnInitDialog();
	afx_msg void OnButtonLock();
	afx_msg void OnButtonUnlock();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	// Generated message map functions
	//{{AFX_MSG(CDlgStreamManualRecordAndLock)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    void InitWindows();
private:
	int m_iDeviceIndex;
	LONG	m_lLoginID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSTREAMMANUALRECORDANDLOCK_H__C024DFB1_488B_449B_A643_83DC1323F361__INCLUDED_)
