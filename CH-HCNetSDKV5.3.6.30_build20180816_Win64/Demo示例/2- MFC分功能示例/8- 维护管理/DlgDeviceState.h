#if !defined(AFX_DLGDEVICESTATE_H__135DAFB9_2E3F_42F7_B2EA_89497918FB74__INCLUDED_)
#define AFX_DLGDEVICESTATE_H__135DAFB9_2E3F_42F7_B2EA_89497918FB74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDeviceState.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceState dialog

class CDlgDeviceState : public CDialog
{
// Construction
public:
	CDlgDeviceState(CWnd* pParent = NULL);   // standard constructor
public:
	void UpdateDeviceInfo();
	CString m_csRecState;
	CString m_csSignalState;
	CString m_csHardWareState;
	CString m_csLinkCount;
	CString m_csBitrate;
	CString m_csDiskVolume;
	CString m_csDiskFreeSpace;
	CString m_csDiskState;

// Dialog Data
	//{{AFX_DATA(CDlgDeviceState)
	enum { IDD = IDD_DIALOG_DEVICE_STATE };
	CString m_csSerialNumber;
	CString m_csDeviceState;
	CListCtrl m_listChanState;
	CListCtrl m_listDiskState;
	CString m_csDeviceIP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDeviceState)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDeviceState)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEVICESTATE_H__135DAFB9_2E3F_42F7_B2EA_89497918FB74__INCLUDED_)
