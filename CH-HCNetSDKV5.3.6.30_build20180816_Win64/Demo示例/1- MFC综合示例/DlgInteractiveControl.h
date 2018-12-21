#if !defined(AFX_DLGINTERACTIVECONTROL_H__29EF103A_0CD5_486D_94FD_8E888D753A17__INCLUDED_)
#define AFX_DLGINTERACTIVECONTROL_H__29EF103A_0CD5_486D_94FD_8E888D753A17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInteractiveControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInteractiveControl dialog

class CDlgInteractiveControl : public CDialog
{
// Construction
public:
	CDlgInteractiveControl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInteractiveControl)
	enum { IDD = IDD_DLG_INTERACTIVE_CTRL };
	CComboBox	m_cmbMediaOperate;
	CComboBox	m_cmbMarkType;
	CStatic	m_statPPTStatus;
	CComboBox	m_cmbRemoteCtrl;
	CStatic	m_statParam;
	CComboBox	m_cmbSplotLight;
	CComboBox	m_cmbPPT;
	CComboBox	m_cmbMarkTools;
	CComboBox	m_cmbLineSize;
	CComboBox	m_cmbCtrlType;
	DWORD	m_dwMarkBlue;
	DWORD	m_dwMarkGreen;
	DWORD	m_dwMarkRed;
	DWORD	m_dwPage;
	DWORD	m_dwRemoterParam;
	DWORD	m_dwSplotLightRadius;
	DWORD	m_dwX;
	DWORD	m_dwY;
	DWORD	m_dwFileIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInteractiveControl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInteractiveControl)
	afx_msg void OnBtnControlOk();
	afx_msg void OnBtnInteractiveExit();
	afx_msg void OnSelchangeComboCtrlType();
	afx_msg void OnSelchangeComboPpt();
	afx_msg void OnSelchangeComboMarkTools();
	afx_msg void OnSelchangeComboSpotlight();
	afx_msg void OnSelchangeComboMarkType();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSelchangeComboRemoteCtrl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int  m_iDeviceIndex;

private:
	LONG m_lUserID;

	NET_DVR_SCREEN_CTRL_CMD m_struScreenCtrlCmd;
	LONG m_lCtrlHandle;

	BOOL m_bGraspMsg;

	BOOL m_bLButtonDown;
	CPoint m_ptPrePoint;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINTERACTIVECONTROL_H__29EF103A_0CD5_486D_94FD_8E888D753A17__INCLUDED_)
