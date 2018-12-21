#if !defined(AFX_DLGMATDECODECHANJOINT_H__00D3C329_C9FE_46DE_820D_40A15C0775D8__INCLUDED_)
#define AFX_DLGMATDECODECHANJOINT_H__00D3C329_C9FE_46DE_820D_40A15C0775D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMatDecodeChanJoint.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMatDecodeChanJoint dialog

class CDlgMatDecodeChanJoint : public CDialog
{
// Construction
public:
	CDlgMatDecodeChanJoint(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CDlgMatDecodeChanJoint)
	enum { IDD = IDD_DLG_MATDECODECHAN_JOINT };
	CIPAddressCtrl	m_IPV4;
	CComboBox	m_cmChanNum;
	BOOL	m_chJoint;
	DWORD	m_dwChanNum;
	CString	m_csIPV6;
	DWORD	m_dwPort;
	CString	m_csJointChanName;
	CString	m_csJointDevName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMatDecodeChanJoint)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int		m_iDeviceIndex;
	LONG	m_lUserID;

	NET_DVR_DECODER_JOINT_PARAM m_struDecodeJointParam;
	// Generated message map functions
	//{{AFX_MSG(CDlgMatDecodeChanJoint)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnSelchangeComboChannum();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMATDECODECHANJOINT_H__00D3C329_C9FE_46DE_820D_40A15C0775D8__INCLUDED_)
