#if !defined(AFX_DLGGETDIGITALCHANNELSTATUS_H__FF8FE5B3_FC45_4478_BCEF_9FE0B19A468B__INCLUDED_)
#define AFX_DLGGETDIGITALCHANNELSTATUS_H__FF8FE5B3_FC45_4478_BCEF_9FE0B19A468B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGetDigitalChannelStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGetDigitalChannelStatus dialog

class CDlgGetDigitalChannelStatus : public CDialog
{
// Construction
public:
	CDlgGetDigitalChannelStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGetDigitalChannelStatus)
	enum { IDD = IDD_DIALOG_DIGITAL_CHANNEL_STATE };
	CString	m_strDChannelStatus;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGetDigitalChannelStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGetDigitalChannelStatus)
	afx_msg void OnButtonGet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	DWORD m_dwDevIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGETDIGITALCHANNELSTATUS_H__FF8FE5B3_FC45_4478_BCEF_9FE0B19A468B__INCLUDED_)
