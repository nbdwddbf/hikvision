#if !defined(AFX_DLGBATCHCONFIG_H__13445A4F_9E64_4CBE_8C7F_B00E44D23F3F__INCLUDED_)
#define AFX_DLGBATCHCONFIG_H__13445A4F_9E64_4CBE_8C7F_B00E44D23F3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBatchConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBatchConfig dialog

#include "DlgBathcUserRightCfg.h"

//batch config type

class CDlgBatchConfig : public CDialog
{
// Construction
public:
	CDlgBatchConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBatchConfig)
	enum { IDD = IDD_DLG_BATCH_CONFIG };
	CTabCtrl	m_tabBatchConfig;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBatchConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBatchConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabBatchConfig(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CDlgBathcUserRightCfg m_UserRightCfg;

	int m_iDeviceIndex;
	LONG m_lLoginID;
	int m_iTabIndex;
	// selected channel index
	//int m_iChanIndex;
	//int m_iDeviceType;

	void BatchConfigUpdate(void);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBATCHCONFIG_H__13445A4F_9E64_4CBE_8C7F_B00E44D23F3F__INCLUDED_)
