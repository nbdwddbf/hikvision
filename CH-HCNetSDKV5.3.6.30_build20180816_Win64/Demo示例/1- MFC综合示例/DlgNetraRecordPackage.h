#if !defined(AFX_DLGNETRARECORDPACKAGE_H__228647F9_E346_4443_8293_DCA3D7CEE889__INCLUDED_)
#define AFX_DLGNETRARECORDPACKAGE_H__228647F9_E346_4443_8293_DCA3D7CEE889__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNetraRecordPackage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNetraRecordPackage dialog

class CDlgNetraRecordPackage : public CDialog
{
// Construction
public:
	CDlgNetraRecordPackage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNetraRecordPackage)
	enum { IDD = IDD_DLG_NETRA_RECORDPACKAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNetraRecordPackage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNetraRecordPackage)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG    m_lLoginID;
    int     m_iDevIndex;
	LONG    m_lChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNETRARECORDPACKAGE_H__228647F9_E346_4443_8293_DCA3D7CEE889__INCLUDED_)
