#if !defined(AFX_PTZCONTROL_H__773F85DF_DBDC_40E5_9E2C_543EDDE45BB6__INCLUDED_)
#define AFX_PTZCONTROL_H__773F85DF_DBDC_40E5_9E2C_543EDDE45BB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PtzControl.h : header file
//
   
/////////////////////////////////////////////////////////////////////////////
// CPtzControl dialog

class CPtzControl : public CDialog
{
// Construction
public:
	CPtzControl(CWnd* pParent = NULL);   // standard constructor

	LONG m_lServerID;
	HANDLE m_Threadhandle;

// Dialog Data
	//{{AFX_DATA(CPtzControl)
	enum { IDD = IDD_DLG_SPLITTER_PTZCONTROL };
	CListBox	m_List;
	CComboBox	m_AddressCtrl;
	CComboBox	m_SpeedCtrl;
	CComboBox	m_PortCtrl;
	BOOL	m_bWithSpeed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPtzControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPtzControl)
	afx_msg void OnBtnLeft();
	afx_msg void OnBtnUp();
	afx_msg void OnBtnStopptz();
	afx_msg void OnBtnRight();
	afx_msg void OnBtnDown();
	afx_msg void OnBtnStart();
	afx_msg void OnBtnStop();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTZCONTROL_H__773F85DF_DBDC_40E5_9E2C_543EDDE45BB6__INCLUDED_)
