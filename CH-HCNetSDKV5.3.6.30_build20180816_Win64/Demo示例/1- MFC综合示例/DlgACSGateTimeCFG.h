#if !defined(AFX_DLGACSGATETIMECFG_H__71F70BD7_6ADE_401C_A83E_A40A0909EE7B__INCLUDED_)
#define AFX_DLGACSGATETIMECFG_H__71F70BD7_6ADE_401C_A83E_A40A0909EE7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgACSGateTimeCFG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgACSGateTimeCFG dialog

class CDlgACSGateTimeCFG : public CDialog
{
// Construction
public:
	CDlgACSGateTimeCFG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgACSGateTimeCFG)
	enum { IDD = IDD_DLG_ACS_GATE_TIME_CFG };
	UINT	m_uHoldonAlarmTime;
	UINT	m_uHoldonGateOpenTime;
	UINT	m_uNolaneAccessTimeLimitTime;
	UINT	m_uPostponeIntrusionAlarmTime;
	UINT	m_uSafetyZoneStayTime;
    UINT	m_uIRTriggerTimeoutTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgACSGateTimeCFG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgACSGateTimeCFG)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    int m_iDevIndex;
    long m_lServerID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACSGATETIMECFG_H__71F70BD7_6ADE_401C_A83E_A40A0909EE7B__INCLUDED_)
