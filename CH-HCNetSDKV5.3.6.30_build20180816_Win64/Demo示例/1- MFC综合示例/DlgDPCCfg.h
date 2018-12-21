#include "afxwin.h"
#if !defined(AFX_DLGDPCCFG_H__DDAB0E56_02D9_49B9_BAA7_91BE64945E22__INCLUDED_)
#define AFX_DLGDPCCFG_H__DDAB0E56_02D9_49B9_BAA7_91BE64945E22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDPCCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDPCCfg dialog

class CDlgDPCCfg : public CDialog
{
// Construction
public:
	CDlgDPCCfg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgDPCCfg();
// Dialog Data
	//{{AFX_DATA(CDlgDPCCfg)
	enum { IDD = IDD_DLG_DPC };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDPCCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDPCCfg)
	afx_msg void OnBtnDpcCorrect();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBtnDpcRight();
	afx_msg void OnBtnDpcDown();
	afx_msg void OnBtnDpcUp();
	afx_msg void OnBtnDpcLeft();
	afx_msg void OnBtnDpcCorrectCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG m_lUserID;
	LONG m_lChannel;
	int m_iDevIndex;
	NET_DVR_DPC_PARAM m_struDpcParam;
	BOOL Play();
	LONG	m_lPlayHandle;
	CRect   m_rcWnd;

	void F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser);
	void F_DrawRect(HDC hDc);
	void ShowDPC();
	void CloseShowDPC();

    afx_msg void OnBnClickedBtnDpcSave();
    afx_msg void OnBnClickedBtnAllCorrect();

    CComboBox m_comboDPCMode;
    afx_msg void OnCbnSelchangeComboDpcMode();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDPCCFG_H__DDAB0E56_02D9_49B9_BAA7_91BE64945E22__INCLUDED_)
