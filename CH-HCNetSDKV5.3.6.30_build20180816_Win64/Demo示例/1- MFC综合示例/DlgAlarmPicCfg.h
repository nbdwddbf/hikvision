#if !defined(AFX_DLGALARMPICCFG_H__60DDB28C_BD06_4969_81B9_893AE1229D00__INCLUDED_)
#define AFX_DLGALARMPICCFG_H__60DDB28C_BD06_4969_81B9_893AE1229D00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmPicCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmPicCfg dialog

class CDlgAlarmPicCfg : public CDialog
{
// Construction
public:
	CDlgAlarmPicCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmPicCfg)
	enum { IDD = IDD_DLG_ALARM_CAPTURE };
	CComboBox	m_comboChannel;
	CComboBox	m_comboResolution;
	UINT	m_nAlarmAfterPic;
	UINT	m_nAlarmBeforePic;
	UINT	m_nIntervalTime;
	//}}AFX_DATA

	LONG m_lUserID;
	int m_iDeviceIndex;
	NET_DVR_ALARM_CAPTRUE_CFG m_struAlarmCaptrueCfg;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmPicCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmPicCfg)
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMPICCFG_H__60DDB28C_BD06_4969_81B9_893AE1229D00__INCLUDED_)
