#if !defined(AFX_DLGTRIALHOSTSTATUS_H__8869400C_FB62_4E1D_A070_A587429A2D5B__INCLUDED_)
#define AFX_DLGTRIALHOSTSTATUS_H__8869400C_FB62_4E1D_A070_A587429A2D5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTrialHostStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTrialHostStatus dialog

class CDlgTrialHostStatus : public CDialog
{
// Construction
public:
	CDlgTrialHostStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTrialHostStatus)
	enum { IDD = IDD_DLG_TRIAL_HOST_STATUS };
	BOOL	m_bChkFpgaTempWarn;
	BOOL	m_bChkMainTempWarn;
	int		m_nFPGATemp;
	int		m_nMainBoardTemp;
	UINT	m_nFanSpeed;
	//}}AFX_DATA
	NET_DVR_TRIAL_HOST_STATUS m_struTrialHostStatus;
	LONG m_lUserID;
	int m_iDeviceIndex;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTrialHostStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTrialHostStatus)
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRIALHOSTSTATUS_H__8869400C_FB62_4E1D_A070_A587429A2D5B__INCLUDED_)
