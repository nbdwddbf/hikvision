#if !defined(AFX_ADDDEVICE_H__DB89F211_2DA4_483E_A738_72B2797F6E97__INCLUDED_)
#define AFX_ADDDEVICE_H__DB89F211_2DA4_483E_A738_72B2797F6E97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddDevice.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddDevice dialog

class CAddDevice : public CDialog
{
// Construction
public:
	CAddDevice(CWnd* pParent = NULL);   // standard constructor

	char NodeName[30];
	char DeviceIP[30];
	UINT Port;
	char UserName[30];
	char Password[30];
// Dialog Data
	//{{AFX_DATA(CAddDevice)
	enum { IDD = IDD_DIALOG_ADD_DEV };
	CIPAddressCtrl	m_ctrlIP;
	CString	m_csNodeName;
	UINT	m_nPort;
	CString	m_csPWD;
	CString	m_csUser;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddDevice)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddDevice)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDDEVICE_H__DB89F211_2DA4_483E_A738_72B2797F6E97__INCLUDED_)
