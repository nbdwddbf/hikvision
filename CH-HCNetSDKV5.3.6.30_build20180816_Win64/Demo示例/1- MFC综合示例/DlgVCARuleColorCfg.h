#if !defined(AFX_DLGVCARULECOLORCFG_H__9036D984_1E12_4E13_91AA_A34FBA3A900B__INCLUDED_)
#define AFX_DLGVCARULECOLORCFG_H__9036D984_1E12_4E13_91AA_A34FBA3A900B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVCARuleColorCfg.h : header file
//
#include "Picture.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgVCARuleColorCfg dialog

class CDlgVCARuleColorCfg : public CDialog
{
// Construction
public:
	CDlgVCARuleColorCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVCARuleColorCfg)
	enum { IDD = IDD_DLG_VCA_RULE_COLOR_CFG };
	CComboBox	m_cmbColorBlockNo;
	CStatic	m_showPicture1;
	CComboBox	m_cmbRuleID;
	CComboBox	m_cmbChannel;
	BOOL	m_bDrawPic1;
	BOOL	m_bEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVCARuleColorCfg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVCARuleColorCfg)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBtnGet();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCheckPic1();

	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnLoadPic1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	int  m_iDevIndex;
	BOOL m_bBtnDown;
	CString m_strPic1Name;
	CString m_strPic2Name;
	CString m_strPic3Name;
	CPoint m_RegionLeftTop;
	CPoint m_RegionRightBottom;
	NET_DVR_VCA_RULE_COLOR_CFG m_struVCARuleColorCfg;
	LONG m_lRemoteHandle;
	CPicture m_Pic;
	CRect   m_rcWnd;

    LRESULT OnProcessVCARuleColorCBInfo(WPARAM wParam, LPARAM lParam);
	BOOL PreDrawRectMsg(MSG* pMsg, CPoint &pt, NET_VCA_POLYGON &struRegion);


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCARULECOLORCFG_H__9036D984_1E12_4E13_91AA_A34FBA3A900B__INCLUDED_)
