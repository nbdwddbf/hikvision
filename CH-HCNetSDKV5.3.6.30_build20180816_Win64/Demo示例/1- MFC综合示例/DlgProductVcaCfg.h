#if !defined(AFX_DLGPRODUCTVCACFG_H__C7EA74CD_54A1_4A8C_B904_563A11DF7AB2__INCLUDED_)
#define AFX_DLGPRODUCTVCACFG_H__C7EA74CD_54A1_4A8C_B904_563A11DF7AB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DlgVcaDevAbility.h"
// DlgProductVcaCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProductVcaCfg dialog

class CDlgProductVcaCfg : public CDialog
{
// Construction
public:
	CDlgProductVcaCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgProductVcaCfg)
	enum { IDD = IDD_SUBDLG_PRODUCT_VCA };
	//}}AFX_DATA

	enum
	{
		SUBWND_IDNEX_DEV  = 0,
		SUBWND_INDEX_CHAN = 1
	};


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProductVcaCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProductVcaCfg)
	afx_msg void OnBtnVcachanCtrl();
	afx_msg void OnBtnPustream();
	afx_msg void OnBtnRestartVcalib();
	afx_msg void OnBtnVcaDrawMode();
	afx_msg void OnBtnVcarule();
	afx_msg void OnBtnKeyparam();
	afx_msg void OnBtnVcaVersion();
	afx_msg void OnBtnVcaFun();
	afx_msg void OnBtnDiagnoisticServer();
	afx_msg void OnBtnPositionRule();
	afx_msg void OnBtnBvCalibCfg();
	afx_msg void OnBtnBvCorrectParam();
	afx_msg void OnBtnVcaDecodecfg();
	afx_msg void OnBtnRuleColorCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void UpdateWindowParam(LONG lDevIndex,LONG lChannel);
protected:
	void ShowChildWnd();
	void ArrangeWndLayout();
private:
	CDlgVcaDevAbility m_dlgVcaDevAbility;
public:
	LONG m_lUserID;
    LONG m_lChannel;
    LONG m_iDevIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPRODUCTVCACFG_H__C7EA74CD_54A1_4A8C_B904_563A11DF7AB2__INCLUDED_)
