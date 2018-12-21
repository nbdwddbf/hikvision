#if !defined(AFX_SUBDLGPREVIEWCFGV30_H__24CC8DCC_53A2_4C34_94D1_107028116762__INCLUDED_)
#define AFX_SUBDLGPREVIEWCFGV30_H__24CC8DCC_53A2_4C34_94D1_107028116762__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubDlgPreviewCfgV30.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubDlgPreviewCfgV30 dialog

#include "SubDlgWndSequence.h"
class CSubDlgPreviewCfgV30 : public CDialog
{
// Construction
public:
	CSubDlgPreviewCfgV30(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgPreviewCfgV30();

// Dialog Data
	//{{AFX_DATA(CSubDlgPreviewCfgV30)
	enum { IDD = IDD_SUBDLG_PREVIEWCFG_V30 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubDlgPreviewCfgV30)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubDlgPreviewCfgV30)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetPreviewcfg();
	afx_msg void OnDropdownPreviewMode();
	afx_msg void OnSelchangePreviewMode();
	afx_msg void OnSelchangePreviewNumber();
	afx_msg void OnBtnGetPreviewcfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL OnInitDialog();
	CComboBox m_ctlPreviewNumber;
	CComboBox m_ctlEnableAudio;
	CComboBox m_ctlSwitchTime;
	CComboBox m_ctlPreviewMode;
// 	afx_msg void OnBnClickedBtnGet();
// 	afx_msg void OnBnClickedBtnSet();
	void F_Get(void);
	void F_Set(void);
	void F_ResizeWnd(int nMaxWndNumber);
	void F_GetSwitchSeq(int nPreviewMode);
	void F_SetSwitchSeq(int nPreviewMode);
	CSubDlgWndSequence m_SubDlgWndSequence[MAX_WINDOW_V30];
	NET_DVR_PREVIEWCFG_V30 m_stPreviewCfgV30;
	DWORD m_dwCommand;
// 	afx_msg void OnCbnSelchangePreviewMode();
// 	afx_msg void OnCbnDropdownPreviewMode();
    void GetPreviewCfg();
public:
    long    m_lServerID;
    int     m_iDevIndex;
    int     m_iPreviewType; // 0 = main 1 = sub
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBDLGPREVIEWCFGV30_H__24CC8DCC_53A2_4C34_94D1_107028116762__INCLUDED_)
