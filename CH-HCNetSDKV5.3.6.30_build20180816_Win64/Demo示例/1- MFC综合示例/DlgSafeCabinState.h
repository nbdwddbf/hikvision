#if !defined(AFX_DLGSAFECABINSTATE_H__BE8210B8_583C_425C_9B75_C0A87B496106__INCLUDED_)
#define AFX_DLGSAFECABINSTATE_H__BE8210B8_583C_425C_9B75_C0A87B496106__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSafeCabinState.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSafeCabinState dialog

class CDlgSafeCabinState : public CDialog
{
// Construction
public:
	CDlgSafeCabinState(CWnd* pParent = NULL);   // standard constructor

	LONG m_lUserID;
	int  m_iDeviceIndex;

// Dialog Data
	//{{AFX_DATA(CDlgSafeCabinState)
	enum { IDD = IDD_DLG_SAFETYCABIN_STATE };
	CComboBox	m_cmbUrgencyBtnState;
	CComboBox	m_cmbPersonState;
	CComboBox	m_cmbLockState;
	CComboBox	m_cmbLightState;
	CComboBox	m_cmbFanState;
	CComboBox	m_cmbExitBtnState;
	CComboBox	m_cmbEnterBtnState;
	CComboBox	m_cmbDoorState;
	CComboBox	m_cmbAbnormalState;
	CComboBox   m_cmbFollowState;
	CComboBox	m_cmbFaintState;
	CComboBox	m_cmbManyPersonState;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSafeCabinState)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSafeCabinState)
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSAFECABINSTATE_H__BE8210B8_583C_425C_9B75_C0A87B496106__INCLUDED_)
