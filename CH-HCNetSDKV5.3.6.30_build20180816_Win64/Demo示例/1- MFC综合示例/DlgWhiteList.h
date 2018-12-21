#if !defined(AFX_DLGWHITELIST_H__FCF5FAE7_E6E7_4BA1_ADAF_1875568B2A7E__INCLUDED_)
#define AFX_DLGWHITELIST_H__FCF5FAE7_E6E7_4BA1_ADAF_1875568B2A7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWhiteList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgWhiteList dialog

class DlgWhiteList : public CDialog
{
// Construction
public:
	DlgWhiteList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgWhiteList)
	enum { IDD = IDD_DLG_WHITE_LIST_CFG };
	CListCtrl	m_listDisArm;
	CListCtrl	m_listClearAlarm;
	CListCtrl	m_listArm;
	CListCtrl	m_listZoneReport;
	CComboBox	m_comIntervalTime;
	CComboBox	m_comAlarmType;
	CComboBox	m_comAlarmPhoneCfg;
	BOOL	m_bAlarmRestore;
	BOOL	m_bArm;
	BOOL	m_bBypass;
	BOOL	m_bBypassRestore;
	BOOL	m_bCancelReport;
	BOOL	m_bDisarm;
	BOOL	m_bEnable;
	BOOL	m_bHjack;
	BOOL	m_bSoftZone;
	BOOL	m_bSystemState;
	BOOL	m_bTest;
	CString	m_sPhone;
	UINT	m_defineTime;
	//}}AFX_DATA
	int m_iDeviceIndex;
	long m_lUserID;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgWhiteList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(DlgWhiteList)
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnSelchangeCombIntervalTime();
	afx_msg void OnSelchangeComAlarmPhoneCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    BOOL m_bChkDetectorConnectionReport;
    BOOL m_bChkDetectorPowerReport;
    BOOL m_bChkVideoAlarm;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWHITELIST_H__FCF5FAE7_E6E7_4BA1_ADAF_1875568B2A7E__INCLUDED_)
