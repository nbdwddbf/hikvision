#if !defined(AFX_DLGPTZPARKACTIONCFG_H__FA71E0C1_B46B_4D38_8AE5_737927FF97C1__INCLUDED_)
#define AFX_DLGPTZPARKACTIONCFG_H__FA71E0C1_B46B_4D38_8AE5_737927FF97C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPtzParkActionCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPtzParkActionCfg dialog

class CDlgPtzParkActionCfg : public CDialog
{
// Construction
public:
	CDlgPtzParkActionCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPtzParkActionCfg)
	enum { IDD = IDD_DIALOG_PTZ_PARKACTION };
	CComboBox	m_comLinearScanType;
	CComboBox	m_comboActionType;
	DWORD	m_dwID;
	DWORD	m_dwParkActionTime;
	BOOL	m_bChkTrace;
	BOOL	m_bChkEnable;
	BOOL	m_bChkOneKey;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPtzParkActionCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPtzParkActionCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnSetLinearscan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lLoginID;
	LONG m_lChanNum;
	int m_iDevIndex;
	NET_DVR_PTZ_PARKACTION_CFG m_struPtzParkAciton;
	NET_DVR_MOTION_TRACK_CFG m_strMotionTtackCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPTZPARKACTIONCFG_H__FA71E0C1_B46B_4D38_8AE5_737927FF97C1__INCLUDED_)
