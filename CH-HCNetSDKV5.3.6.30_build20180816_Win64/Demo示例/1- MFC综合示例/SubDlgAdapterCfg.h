#if !defined(AFX_SUBDLGADAPTERCFG_H__CAED5920_9013_4084_89B9_F1E7B48E5AF6__INCLUDED_)
#define AFX_SUBDLGADAPTERCFG_H__CAED5920_9013_4084_89B9_F1E7B48E5AF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubDlgAdapterCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubDlgAdapterCfg dialog

class CSubDlgAdapterCfg : public CDialog
{
// Construction
public:
	CSubDlgAdapterCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSubDlgAdapterCfg)
	enum { IDD = IDD_SUB_DLG_ADAPTER_CFG };
	CString	m_csVersion;
	CString	m_csPortNum;
	CString	m_csPortType;
	CString	m_csRaidType;
	CString	m_csSupportExpand;
	CString	m_csSupportMigrate;
	BOOL	m_bAutoRebuild;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubDlgAdapterCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubDlgAdapterCfg)
	afx_msg void OnBtnSetAdapter();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    NET_DVR_RAID_ADAPTER_INFO m_struAdapterInfo;
public:
    BOOL CheckInitParam();
    void CurCfgUpdate();
    BOOL GetAdapterInfo();
    BOOL SetAdapterInfo();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBDLGADAPTERCFG_H__CAED5920_9013_4084_89B9_F1E7B48E5AF6__INCLUDED_)
