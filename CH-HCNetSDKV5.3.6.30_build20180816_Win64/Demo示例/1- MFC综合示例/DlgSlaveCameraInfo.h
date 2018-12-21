#if !defined(AFX_DLGSLAVECAMERAINFO_H__1A2C2B2A_F0A1_4660_9026_85F763ABFD35__INCLUDED_)
#define AFX_DLGSLAVECAMERAINFO_H__1A2C2B2A_F0A1_4660_9026_85F763ABFD35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSlaveCameraInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSlaveCameraInfo dialog

class CDlgSlaveCameraInfo : public CDialog
{
// Construction
public:
	CDlgSlaveCameraInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSlaveCameraInfo)
	enum { IDD = IDD_DLG_SLAVECAMERA_INFO };
	CString	m_csSlaveIP;
	CString	m_csPassWD;
	int		m_iPort;
	CString	m_csSlaveUserName;
	BOOL	m_bChkSlaveLoginEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSlaveCameraInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSlaveCameraInfo)
	afx_msg void OnBtnLogin();
	afx_msg void OnBtnLogout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG m_lLoginID;
	LONG m_iDeviceIndex;
	NET_DVR_SLAVECAMERA_COND m_struSlaveCameraCond;
	NET_DVR_SLAVECAMERA_CFG m_struSlaveCameraCfg;
	NET_DVR_STD_CONFIG m_struSTDCfg;
	char m_szStatusBuf[1024];

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSLAVECAMERAINFO_H__1A2C2B2A_F0A1_4660_9026_85F763ABFD35__INCLUDED_)
