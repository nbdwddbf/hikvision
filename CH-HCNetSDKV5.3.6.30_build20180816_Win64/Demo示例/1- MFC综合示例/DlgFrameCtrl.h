#if !defined(AFX_DLGFRAMECTRL_H__E0383D15_7607_49FC_ABCF_2FB827D0BF68__INCLUDED_)
#define AFX_DLGFRAMECTRL_H__E0383D15_7607_49FC_ABCF_2FB827D0BF68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFrameCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFrameCtrl dialog

class CDlgFrameCtrl : public CDialog
{
// Construction
public:
	CDlgFrameCtrl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFrameCtrl)
	enum { IDD = IDD_DLG_FRAMECTRL };
	CComboBox	m_comboStreamType;
	int		m_iChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFrameCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFrameCtrl)
	afx_msg void OnBtnRefreshFrame();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG m_lUser;
    int  m_iDeviceIndex;
    char m_szStatusBuf[ISAPI_STATUS_LEN];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFRAMECTRL_H__E0383D15_7607_49FC_ABCF_2FB827D0BF68__INCLUDED_)
