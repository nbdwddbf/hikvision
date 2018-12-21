#include "afxwin.h"
#if !defined(AFX_DLGDOORCONFIG_H__6C8540A0_6ADA_4A43_84C8_001D20AD00C2__INCLUDED_)
#define AFX_DLGDOORCONFIG_H__6C8540A0_6ADA_4A43_84C8_001D20AD00C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDoorConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDoorConfig dialog

class CDlgDoorConfig : public CDialog
{
// Construction
public:
	CDlgDoorConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDoorConfig)
	enum { IDD = IDD_DLG_ACDC };
	CComboBox	m_cmbOpenButType;
	CComboBox	m_cmbMagneticType;
	CSliderCtrl	m_SlidLOpenDuration;
	CSliderCtrl	m_SlidDOpenDuration;
	CSliderCtrl	m_SlidAlarmTimeout;
	CSliderCtrl	m_SlidOpenDuration;
	DWORD	m_dwDoorChan;
	CString	m_csDoorName;
	CString	m_csStressPasswd;
	CString	m_csSuperPasswd;
    CString	m_csUnlockPassword;
	BOOL	m_BDoorLock;
	BOOL	m_BLeaderCard;
	CString	m_csDOpenDuration;
	CString	m_csLOpenDuration;
	CString	m_csOpenDuration;
	CString	m_csAlarmTimeout;
    int     m_iLadderControlDelayTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDoorConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDoorConfig)
	afx_msg void OnButGet();
	afx_msg void OnButSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnCdrawOpenduration(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCdrawDOpenduration(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCdrawLOpenduration(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCdrawAlarmtimeout(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID; 
    LONG m_lDeviceID; 

    CComboBox m_cmbLeaderCardMode;
    BOOL m_bUserLocalController;
    int m_iLocalControllerID;
    int m_iLocalControllerDoorNumber;
    CComboBox m_cmbLocalControllerStatus;
    BOOL m_bLockInputCheck;
    afx_msg void OnCbnSelchangeComAcdcLeadercardmode();
    CComboBox m_cmbLockInputType;
    CComboBox m_cmbDoorTerminalMode;
    BOOL m_bOpenButton;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDOORCONFIG_H__6C8540A0_6ADA_4A43_84C8_001D20AD00C2__INCLUDED_)
