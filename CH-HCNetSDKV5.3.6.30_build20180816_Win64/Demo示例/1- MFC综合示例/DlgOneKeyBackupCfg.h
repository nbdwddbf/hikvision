#if !defined(AFX_DLGONEKEYBACKUPCFG_H__B76E11C6_1F8F_41F5_8EA2_15D0C05D04FE__INCLUDED_)
#define AFX_DLGONEKEYBACKUPCFG_H__B76E11C6_1F8F_41F5_8EA2_15D0C05D04FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOneKeyBackupCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgOneKeyBackupCfg dialog

class DlgOneKeyBackupCfg : public CDialog
{
// Construction
public:
	DlgOneKeyBackupCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgOneKeyBackupCfg)
	enum { IDD = IDD_DLG_ONE_KEY_BACKUP_CFG };
	CComboBox	m_comChan;
    CComboBox   m_comStreamType;
	BOOL		m_bEnable;
	BOOL		m_bContinue;
	//}}AFX_DATA
	LONG m_lUserID;
	int m_iDeviceIndex;
	int m_iMirrorNum;
	int m_iStartChannel;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgOneKeyBackupCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	NET_DVR_BACKUP_RECORD_PARAM m_struBackupCfg; 

// Implementation
protected:

	BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(DlgOneKeyBackupCfg)
	afx_msg void OnBtnOk();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnSelchangeComboChan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGONEKEYBACKUPCFG_H__B76E11C6_1F8F_41F5_8EA2_15D0C05D04FE__INCLUDED_)
