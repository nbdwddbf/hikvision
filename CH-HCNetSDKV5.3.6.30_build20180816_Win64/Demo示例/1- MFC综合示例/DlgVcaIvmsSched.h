#if !defined(AFX_DLGVCAIVMSSCHED_H__8A4A2736_842E_427D_A987_EB69154045D4__INCLUDED_)
#define AFX_DLGVCAIVMSSCHED_H__8A4A2736_842E_427D_A987_EB69154045D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaIvmsSched.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaIvmsSched dialog

class CDlgVcaIvmsSched : public CDialog
{
// Construction
public:
	CDlgVcaIvmsSched(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaIvmsSched)
	enum { IDD = IDD_DLG_VCA_IVMS_SCHED };
	CIPAddressCtrl	m_ipStream;
	CIPAddressCtrl	m_ipDvr;
	CComboBox	m_comboWeekday;
	CComboBox	m_comboTimePeriod;
	CComboBox	m_comboStreamTransType;
	CComboBox	m_comboDvrTransMode;
	CComboBox	m_comboDvrTransProtocol;
	BOOL	m_bStreamValid;
	int		m_iDvrPort;
	CString	m_csPassword;
	int		m_iStreamPort;
	CString	m_csUserName;
	int		m_iHour11;
	int		m_iHour12;
	int		m_iMin11;
	int		m_iMin12;
	int		m_iDvrChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaIvmsSched)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaIvmsSched)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckStreamValid();
	afx_msg void OnSelchangeComboWeekday();
	afx_msg void OnSelchangeComboTimePeriod();
	afx_msg void OnBtnCancel();
	afx_msg void OnBtnConfirm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL EnableStream(BOOL bEnable);
	BOOL GetPUStreamPara(int iWeekday, int iTimePeriod);
	BOOL SetVcaIvmsSched(int iWeekday, int iTimePaerod);
	NET_DVR_SCHEDTIME 	m_struTime; //Time parameter
	NET_DVR_PU_STREAM_CFG m_struPUStream; //parameter of getting stream from front-end device

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAIVMSSCHED_H__8A4A2736_842E_427D_A987_EB69154045D4__INCLUDED_)
