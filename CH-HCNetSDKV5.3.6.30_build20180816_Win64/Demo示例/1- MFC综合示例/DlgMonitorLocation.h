#if !defined(AFX_DLGMONITORLOCATION_H__CF72611D_F0C7_401B_AE7D_4D27C0A10616__INCLUDED_)
#define AFX_DLGMONITORLOCATION_H__CF72611D_F0C7_401B_AE7D_4D27C0A10616__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMonitorLocation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMonitorLocation dialog

class CDlgMonitorLocation : public CDialog
{
// Construction
public:
	CDlgMonitorLocation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CDlgMonitorLocation)
    enum { IDD = IDD_DLG_MONITOR_LOCATION_INFO };
	CComboBox	m_comRelateType;
	CComboBox	m_comDirection;
	CString	m_csDevID;
	CString	m_csMonitorInfo;
	CString	m_csMonitoringSiteID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMonitorLocation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMonitorLocation)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGetMonitorLocation();
	afx_msg void OnBtnSetMonitorLocation();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG  m_lUserID;
    DWORD m_dwDevIndex;
    LONG  m_lChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMONITORLOCATION_H__CF72611D_F0C7_401B_AE7D_4D27C0A10616__INCLUDED_)
