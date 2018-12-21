#if !defined(AFX_DLGTRANSCONFIG_H__7164E1BF_EF3D_4075_A39E_58ABE78446CB__INCLUDED_)
#define AFX_DLGTRANSCONFIG_H__7164E1BF_EF3D_4075_A39E_58ABE78446CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTransConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTransConfig dialog
#include "DlgTransStreamSrcCfg.h"
#include "DlgTransCompression.h"
#include "DlgPassiveTransCode.h"
#include "DlgTransDevStatus.h"
#include "DlgTransAutoReboot.h"

class CDlgTransConfig : public CDialog
{
// Construction
public:
	CDlgTransConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTransConfig)
	enum { IDD = IDD_DLG_TRANS_CONFIG };
	CTabCtrl	m_tabCfgType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTransConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTransConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabConfigType(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CDlgTransStreamSrcCfg m_dlgStreamSrc;
	CDlgTransCompression m_dlgTransCmp;
	CDlgPassiveTransCode m_dlgPassiveTransCode;
	CDlgTransDevStatus m_dlgTransDevStatus;
	CDlgTransAutoReboot m_dlgTransAutoReboot;
	NET_DVR_STREAM_INFO m_lpStreamInfo[256];
	DWORD m_dwItemCount;

	int m_iTabSel;
	LONG m_lUserID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRANSCONFIG_H__7164E1BF_EF3D_4075_A39E_58ABE78446CB__INCLUDED_)
