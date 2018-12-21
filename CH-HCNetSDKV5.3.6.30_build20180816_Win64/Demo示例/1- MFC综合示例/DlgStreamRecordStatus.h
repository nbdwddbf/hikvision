#if !defined(AFX_DLGSTREAMRECORDSTATUS_H__B51C4D58_3028_4A95_8F8C_F137B6269C17__INCLUDED_)
#define AFX_DLGSTREAMRECORDSTATUS_H__B51C4D58_3028_4A95_8F8C_F137B6269C17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStreamRecordStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamRecordStatus dialog

class CDlgStreamRecordStatus : public CDialog
{
// Construction
public:
	CDlgStreamRecordStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgStreamRecordStatus)
	enum { IDD = IDD_DLG_STREAM_RECORD_STATUS };
	CListCtrl	m_lstStreamRecordStatus;
	CComboBox	m_cmbRecordType;
	CString	m_strRelatedChannel;
	CString	m_strRelatedDisc;
	CString	m_strStreamID;
	CString	m_strStatus;
	BOOL	m_bOffLineRecord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgStreamRecordStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgStreamRecordStatus)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAddStreamID();
	afx_msg void OnButtonDelStreamID();
	afx_msg void OnButtonGetStreamRecordStatus();
	afx_msg void OnButtonSetStreamRecordStatus();
	afx_msg void OnClickListRecordStatus(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSTREAMRECORDSTATUS_H__B51C4D58_3028_4A95_8F8C_F137B6269C17__INCLUDED_)
