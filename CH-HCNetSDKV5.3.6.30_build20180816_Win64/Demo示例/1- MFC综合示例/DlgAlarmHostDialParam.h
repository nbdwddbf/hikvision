#if !defined(AFX_DLGALARMHOSTDIALPARAM_H__279106DC_A9C2_4680_929D_61A45BB88654__INCLUDED_)
#define AFX_DLGALARMHOSTDIALPARAM_H__279106DC_A9C2_4680_929D_61A45BB88654__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostDialParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostDialParam dialog

class CDlgAlarmHostDialParam : public CDialog
{
// Construction
public:
	CDlgAlarmHostDialParam(CWnd* pParent = NULL);   // standard constructor

    int m_lServerID;
    int m_iDevIndex;
    NET_DVR_ALARMHOSTDIALCFG m_struAlarmDialCfg;
	NET_DVR_ALARMHOSTDIALSETUPMODE m_struSetupMode;
	NET_DVR_ALARMHOST_ABILITY m_struAbility;
	char m_szLan[128];

	void InitComboBox();

// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostDialParam)
	enum { IDD = IDD_DLG_ALARMHOST_DIALPARAM };
	CComboBox	m_cmReportValid;
	CComboBox	m_PstnTransCtrl;
	CComboBox	m_PstnPrtCtrl;
	CComboBox	m_EnableModeCtrl;
	CComboBox	m_CenterParamCtrl;
	CComboBox	m_CenterModeCtrl;
	CString	m_strCenterName;
	CString	m_strCenterPhone;
	int		m_iDialDelay;
	CString	m_strReceiveId;
	int		m_iRepeatCall;
	int		m_wFirstReport;
	int		m_iReportPeriod;
    BOOL   m_bEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostDialParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostDialParam)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGet();
	afx_msg void OnButtonSet();
	afx_msg void OnSelchangeComboCenterparam();
	afx_msg void OnButtonSure();
	afx_msg void OnBtnSetsetupmode();
	afx_msg void OnBtnGetsetupmode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTDIALPARAM_H__279106DC_A9C2_4680_929D_61A45BB88654__INCLUDED_)
