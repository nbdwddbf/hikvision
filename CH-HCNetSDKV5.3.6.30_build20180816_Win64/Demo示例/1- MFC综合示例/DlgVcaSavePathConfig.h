#if !defined(AFX_DLGVCASAVEPATHCONFIG_H__69233F0B_688E_478F_A692_EF2D4E3F56DA__INCLUDED_)
#define AFX_DLGVCASAVEPATHCONFIG_H__69233F0B_688E_478F_A692_EF2D4E3F56DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaSavePathConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSavePathConfig dialog

class CDlgVcaSavePathConfig : public CDialog
{
// Construction
public:
	CDlgVcaSavePathConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaSavePathConfig)
	enum { IDD = IDD_DLG_VCA_SAVE_PATH_CONFIG };
	CComboBox	m_comboSaveType;
	CComboBox	m_comboDiskNum;
	DWORD	m_dwDiskNo;
	DWORD	m_dwLeftSpace;
	BOOL	m_bChkEnableSave;
	BOOL	m_bChkSaveAlarmPic;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaSavePathConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaSavePathConfig)
	afx_msg void OnBtnSure();
	afx_msg void OnBtnGetSavePath();
	afx_msg void OnBtnSetSavePath();
	afx_msg void OnSelchangeComboDiskNum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;
	LONG    m_lDiskNum;
	NET_VCA_SAVE_PATH_CFG m_struSavePathCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCASAVEPATHCONFIG_H__69233F0B_688E_478F_A692_EF2D4E3F56DA__INCLUDED_)
