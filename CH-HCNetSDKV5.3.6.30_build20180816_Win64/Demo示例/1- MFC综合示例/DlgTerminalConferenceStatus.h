#if !defined(AFX_DLGTERMINALCONFERENCESTATUS_H__C0C4D335_06EC_4D5D_9F10_C157C5856BD6__INCLUDED_)
#define AFX_DLGTERMINALCONFERENCESTATUS_H__C0C4D335_06EC_4D5D_9F10_C157C5856BD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTerminalConferenceStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTerminalConferenceStatus dialog

class CDlgTerminalConferenceStatus : public CDialog
{
// Construction
public:
	CDlgTerminalConferenceStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTerminalConferenceStatus)
	enum { IDD = IDD_DLG_TERMINIAL_CONFERENCE_STATE };
	CComboBox	m_comboConferenceType;
	CComboBox	m_comboConferenceState;
	BOOL	m_bDisabledAudioIn;
	BOOL	m_bMute;
	CString	m_csConferenceID;
	CString	m_csConferenceName;
	CString	m_csEndTime;
	CString	m_csStartTime;
	CString	m_csURL;
	BYTE	m_byVolumeIn;
	BYTE	m_byVolumeOut;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTerminalConferenceStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTerminalConferenceStatus)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboConferenceType();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    int m_iDeviceIndex;
    LONG m_lUserID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTERMINALCONFERENCESTATUS_H__C0C4D335_06EC_4D5D_9F10_C157C5856BD6__INCLUDED_)
