#if !defined(AFX_DLGCONFERENCEREGION_H__7A641415_C269_459D_A946_EE90CA2FCD2B__INCLUDED_)
#define AFX_DLGCONFERENCEREGION_H__7A641415_C269_459D_A946_EE90CA2FCD2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgConferenceRegion.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgConferenceRegion dialog

class CDlgConferenceRegion : public CDialog
{
// Construction
public:
	CDlgConferenceRegion(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgConferenceRegion)
	enum { IDD = IDD_DLG_CONFERENCE_REGION };
	DWORD	m_dwOuputHeight;
	DWORD	m_dwOutputWidth;
	DWORD	m_dwX1;
	DWORD	m_dwX2;
	DWORD	m_dwX3;
	DWORD	m_dwX4;
	DWORD	m_dwY1;
	DWORD	m_dwY2;
	DWORD	m_dwY3;
	DWORD	m_dwY4;
	BOOL	m_BEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgConferenceRegion)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgConferenceRegion)
	afx_msg void OnButMCUGet();
	afx_msg void OnButMCUSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;
	LONG m_iDeviceIndex;	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONFERENCEREGION_H__7A641415_C269_459D_A946_EE90CA2FCD2B__INCLUDED_)
