#if !defined(AFX_DLGCODESPLITTER_H__33CF90A6_CD0D_42F2_A064_8A2496C32ECE__INCLUDED_)
#define AFX_DLGCODESPLITTER_H__33CF90A6_CD0D_42F2_A064_8A2496C32ECE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCodeSplitter.h : header file
//
#include "DeviceDlg.h"
#include "UserDlg.h"
#include "DecoderCfg.h"
#include "PtzControl.h"
#include "DlgSplitterTransparent.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgCodeSplitter dialog

class CDlgCodeSplitter : public CDialog
{
// Construction
public:
	CDlgCodeSplitter(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCodeSplitter)
	enum { IDD = IDD_DLG_CODESPITTER };
	CTabCtrl	m_Tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCodeSplitter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCodeSplitter)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnRestore();
	afx_msg void OnBtnReboot();
	afx_msg void OnBtnExit();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lServerID;
		
	CDeviceDlg m_DlgDevice;
    CUserDlg m_DlgUser;
	CPtzControl m_DlgPtz;
	CDecoderCfg m_DlgDecoder;
	CDlgSplitterTransparent m_DlgTransparent;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCODESPLITTER_H__33CF90A6_CD0D_42F2_A064_8A2496C32ECE__INCLUDED_)
