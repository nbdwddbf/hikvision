#if !defined(AFX_DLGBATHCUSERRIGHTCFG_H__D2E115F6_DF4C_4950_A4E6_AA4D0CE1C5F6__INCLUDED_)
#define AFX_DLGBATHCUSERRIGHTCFG_H__D2E115F6_DF4C_4950_A4E6_AA4D0CE1C5F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBathcUserRightCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBathcUserRightCfg dialog

class CDlgBathcUserRightCfg : public CDialog
{
// Construction
public:
	CDlgBathcUserRightCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBathcUserRightCfg)
	enum { IDD = IDD_DLG_BATCH_USER_RIGHT_CFG };
	CListCtrl	m_lstUserRight;
	BOOL	m_bAddMonitorPointRight;
	BOOL	m_bModMonitorPointRight;
	BOOL	m_bDelMonitorPointRight;
	BOOL	m_bSetRecordPlanRight;
	BOOL	m_bDelRecordPlanRight;
	BOOL	m_bSetAlarmRecordRight;
	BOOL	m_bRecordBackupRight;
	BOOL	m_bRecordDownloadRight;
	BOOL	m_bRecordDelRight;
	BOOL	m_bBackupRecordDelRight;
	BOOL	m_bSetBackupVolumeRight;
	BOOL	m_bRecordPlayRight;
	BOOL	m_bLogDeleteRight;
	BOOL	m_bLogDownloadRight;
	BOOL	m_bAddUserRight;
	BOOL	m_bDelUserRight;
	BOOL	m_bModUserRight;
	BOOL	m_bAllcoUserRightRight;
	CString	m_strPassword;
	CString	m_strUserName;
	UINT	m_dwStatus;
	BOOL	m_bRecordPlanRight;
	BOOL	m_bRecordRight;
	//}}AFX_DATA

	NET_DVR_USER_RIGHT_CFG m_struUserRightCfg[32];
	NET_DVR_USER_COND	   m_struUserCond[32];


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBathcUserRightCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBathcUserRightCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAddList();
	afx_msg void OnButtonDelList();
	afx_msg void OnButtonSet();
	afx_msg void OnButtonGet();
	afx_msg void OnClickListUser(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBATHCUSERRIGHTCFG_H__D2E115F6_DF4C_4950_A4E6_AA4D0CE1C5F6__INCLUDED_)
