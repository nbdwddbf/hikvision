#if !defined(AFX_DLGRECORDSTREAMTRANSTYPE_H__48955134_BE66_496D_9918_FB43D6746B9E__INCLUDED_)
#define AFX_DLGRECORDSTREAMTRANSTYPE_H__48955134_BE66_496D_9918_FB43D6746B9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordStreamTransType.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordStreamTransType dialog

class CDlgRecordStreamTransType : public CDialog
{
// Construction
public:
	CDlgRecordStreamTransType(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecordStreamTransType)
	enum { IDD = IDD_DLG_STREAM_TRANS_TYPE_CFG };
	CComboBox	m_ctrlStreamTransType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecordStreamTransType)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRecordStreamTransType)
	afx_msg void OnBtnSaveStreamType();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDSTREAMTRANSTYPE_H__48955134_BE66_496D_9918_FB43D6746B9E__INCLUDED_)
