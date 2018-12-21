#if !defined(AFX_DLGGROUPCFG_H__79050E8A_19EB_4083_B43D_1DD9ED5E5272__INCLUDED_)
#define AFX_DLGGROUPCFG_H__79050E8A_19EB_4083_B43D_1DD9ED5E5272__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGroupCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGroupCfg dialog

class CDlgGroupCfg : public CDialog
{
// Construction
public:
	CDlgGroupCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGroupCfg)
	enum { IDD = IDD_DLG_GROUP_CFG };
	BOOL	m_bEnable;
	BOOL	m_bValidEnable;
	CString	m_csGroupName;
	COleDateTime	m_startDate;
	COleDateTime	m_startTime;
	COleDateTime	m_stopDate;
	COleDateTime	m_stopTime;
	DWORD	m_dwGroupNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGroupCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGroupCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGetGroupCfg();
	afx_msg void OnBtnSetGroupCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	LONG m_lChannel;
	int m_iDevIndex;

	NET_DVR_GROUP_CFG m_struGroupCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGROUPCFG_H__79050E8A_19EB_4083_B43D_1DD9ED5E5272__INCLUDED_)
