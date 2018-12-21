#if !defined(AFX_DLGINFODIFFUSIONCONTENT_H__E73146EE_2514_41CE_94BD_3A4070477513__INCLUDED_)
#define AFX_DLGINFODIFFUSIONCONTENT_H__E73146EE_2514_41CE_94BD_3A4070477513__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionContent.h : header file
//

#include "InfoDiffusionParamsConvert.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionContent dialog

class CDlgInfoDiffusionContent : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionContent(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionContent)
	enum { IDD = IDD_DLG_INFO_DIFFUSION_CONTENT };
	CComboBox	m_cmbSwitchEffect;
	CComboBox	m_cmbFont;
	CComboBox	m_cmbWinMaterialType;
	CComboBox	m_cmbStaticMaterialType;
	CListCtrl	m_listPlay;
	CComboBox	m_cmbEffect;
	CComboBox	m_cmbDurationType;
	CComboBox	m_cmbMarqueeScrollType;
	CComboBox	m_cmbMarqueeScrollDiretion;
	DWORD	m_dwLayerNo;
	DWORD	m_dwMarqueeScrollSpeed;
	DWORD	m_dwMaterialID;
	DWORD	m_dwPosHeight;
	DWORD	m_dwPosWidth;
	DWORD	m_dwPosX;
	DWORD	m_dwPosY;
	DWORD	m_dwDuration;
	BOOL	m_bFontEnable;
	DWORD	m_dwBackGreen;
	DWORD	m_dwBackRed;
	DWORD	m_dwBackBlue;
	DWORD	m_dwFontBlue;
	DWORD	m_dwFontGreen;
	DWORD	m_dwFontRed;
	DWORD	m_dwFontSize;
	DWORD	m_dwFontSpeed;
	DWORD	m_dwTransparent;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionContent)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionContent)
	afx_msg void OnBtnCancel();
	afx_msg void OnBtnOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnMod();
	afx_msg void OnSelchangeComboEffect();
	afx_msg void OnClickListPlay(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboWinMaterial();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bNewOrEdit;
	NET_DVR_CONTENT m_struContent;

	int m_nCurSelItem;

public:
	void SetContent(const LPNET_DVR_CONTENT lpstruContent);
	void GetContent(LPNET_DVR_CONTENT lpstruContent);
	void UpdateContent();
	void InitPlayListCtrl();
	void RefreshPlayList();
	void RefreshPlayItem(int nItemIndex);
	void UpdatePlayItem(int nItemIndex);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONCONTENT_H__E73146EE_2514_41CE_94BD_3A4070477513__INCLUDED_)
