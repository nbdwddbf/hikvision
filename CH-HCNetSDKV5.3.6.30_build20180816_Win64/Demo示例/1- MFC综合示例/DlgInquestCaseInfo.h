#if !defined(AFX_DLGINQUESTCASEINFO_H__CDAE4817_6D53_433E_8C7C_F3B372496BEA__INCLUDED_)
#define AFX_DLGINQUESTCASEINFO_H__CDAE4817_6D53_433E_8C7C_F3B372496BEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInquestCaseInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInquestCaseInfo dialog

class CDlgInquestCaseInfo : public CDialog
{
// Construction
public:
	CDlgInquestCaseInfo(CWnd* pParent = NULL);   // standard constructor

	LONG m_lUserID;
	int m_iDeviceIndex;
	NET_DVR_INQUEST_CASE_INFO m_struInqCaseInfo;

// Dialog Data
	//{{AFX_DATA(CDlgInquestCaseInfo)
	enum { IDD = IDD_DLG_INQ_CASE_INFO };
	CComboBox	m_cmbPosition;
	CComboBox	m_cmbInqRoomNo;
	CComboBox	m_cmbInqRoomNo2;
	UINT	m_nCaseShowTime;
	CString	m_sCustomInfo1;
	CString	m_sCustomInfo2;
	CString	m_sCustomInfo3;
	CString	m_sCaseName;
	CString	m_sCaseNo;
	UINT	m_nCaseRealTimeShowTime;
	BOOL	m_bShowCaseInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInquestCaseInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInquestCaseInfo)
		// NOTE: the ClassWizard will add member functions here
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnControl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINQUESTCASEINFO_H__CDAE4817_6D53_433E_8C7C_F3B372496BEA__INCLUDED_)
