#if !defined(AFX_DLGDEVICESELFCHECKSTATE_H__42CE26F6_6DD0_459B_90C7_8EDBF32DE8F0__INCLUDED_)
#define AFX_DLGDEVICESELFCHECKSTATE_H__42CE26F6_6DD0_459B_90C7_8EDBF32DE8F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDeviceSelfCheckState.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgDeviceSelfCheckState dialog

class DlgDeviceSelfCheckState : public CDialog
{
// Construction
public:
	DlgDeviceSelfCheckState(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgDeviceSelfCheckState)
	enum { IDD = IDD_DLG_DEVICE_SELF_CHECK_STATE };
	CListCtrl	m_listSensorChan;
	CComboBox	m_comChan;
	CListCtrl	m_listSlot;
	//}}AFX_DATA
	NET_DVR_DEVICE_SELF_CHECK_STATE m_struDeviceSelfCheckState;
	LONG m_lUserID;
	UINT m_iDeviceIndex;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgDeviceSelfCheckState)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(DlgDeviceSelfCheckState)
	afx_msg void OnGet();
	afx_msg void OnSelchangeComChan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEVICESELFCHECKSTATE_H__42CE26F6_6DD0_459B_90C7_8EDBF32DE8F0__INCLUDED_)
