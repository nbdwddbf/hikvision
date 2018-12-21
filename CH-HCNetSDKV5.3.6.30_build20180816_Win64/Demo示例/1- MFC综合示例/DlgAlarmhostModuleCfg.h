#if !defined(AFX_DLGALARMHOSTMODULECFG_H__31FE6D12_A61D_4DD0_AC21_B4E9CBA3EF99__INCLUDED_)
#define AFX_DLGALARMHOSTMODULECFG_H__31FE6D12_A61D_4DD0_AC21_B4E9CBA3EF99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmhostModuleCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmhostModuleCfg dialog

class CDlgAlarmhostModuleCfg : public CDialog
{
// Construction
public:
	CDlgAlarmhostModuleCfg(CWnd* pParent = NULL);   // standard constructor
	long m_lUserID;
	int	 m_iDeviceIndex;
	NET_DVR_ALARMHOST_MODULE_CFG m_struModuleCfg;
	char m_szLan[256];
// Dialog Data
	//{{AFX_DATA(CDlgAlarmhostModuleCfg)
	enum { IDD = IDD_DLG_ALARMHOST_MODULE_CFG };
	CComboBox	m_cmZoneType;
	CComboBox	m_cmTriggerType;
	CComboBox	m_cmModuleType;
	CComboBox	m_cmModuleAddress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmhostModuleCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmhostModuleCfg)
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTMODULECFG_H__31FE6D12_A61D_4DD0_AC21_B4E9CBA3EF99__INCLUDED_)
