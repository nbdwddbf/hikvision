#if !defined(AFX_DLGMICROPHONESTATUS_H__451A7A11_F7A3_4C26_BFAE_89EEAE08E4B6__INCLUDED_)
#define AFX_DLGMICROPHONESTATUS_H__451A7A11_F7A3_4C26_BFAE_89EEAE08E4B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMicrophoneStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMicrophoneStatus dialog

class CDlgMicrophoneStatus : public CDialog
{
// Construction
public:
	CDlgMicrophoneStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMicrophoneStatus)
	enum { IDD = IDD_DLG_TRIAL_MICROPHONE };
	CListCtrl	m_listMicrophone;
	//}}AFX_DATA
	NET_DVR_TRIAL_MICROPHONE_STATUS m_struTrialMicroPhoneStatus;
	int m_iDeviceIndex;
	LONG m_lUserID;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMicrophoneStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMicrophoneStatus)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListMicrophone(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void OnChkAllChan(BOOL bAll);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMICROPHONESTATUS_H__451A7A11_F7A3_4C26_BFAE_89EEAE08E4B6__INCLUDED_)
