#if !defined(AFX_DLGSDIAUTOTRACKCFG_H__EF87D4E4_6FC3_42FB_AEFF_C13AD65FCCF3__INCLUDED_)
#define AFX_DLGSDIAUTOTRACKCFG_H__EF87D4E4_6FC3_42FB_AEFF_C13AD65FCCF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSDIAutoTrackCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgSDIAutoTrackCfg dialog

class DlgSDIAutoTrackCfg : public CDialog
{
// Construction
public:
	DlgSDIAutoTrackCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgSDIAutoTrackCfg)
	enum { IDD = IDD_DLG_AUTO_TRACK_CFG };
	CIPAddressCtrl	m_IPAddress;
	CComboBox	m_comProtocolType;
    CComboBox   m_cmbCameraType;
	CComboBox	m_comSDIChan;
	BOOL	m_bEnable;
	UINT	m_nChan;
	CString	m_sDomain;
	CString	m_sPassword;
	UINT	m_nPort;
	CString	m_sUserName;
	UINT	m_nPriority;
	UINT	m_nDirectDelayTime;
	CString	m_sChan;
	//}}AFX_DATA

	LONG m_lUserID;
	int  m_iDeviceIndex;
	int m_iMirrorNum;
	int m_iStartChannel;

	NET_DVR_AUTO_TRACK_CFG m_struAutoTrackCfg;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgSDIAutoTrackCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(DlgSDIAutoTrackCfg)
	afx_msg void OnBtnOk();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnSelchangeComboSdiChan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSDIAUTOTRACKCFG_H__EF87D4E4_6FC3_42FB_AEFF_C13AD65FCCF3__INCLUDED_)
