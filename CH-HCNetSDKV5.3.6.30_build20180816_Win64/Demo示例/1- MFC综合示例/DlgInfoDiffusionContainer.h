#if !defined(AFX_DLGINFODIFFUSIONCONTAINER_H__2A86AD31_8B60_4154_8549_7D2A1948E7C7__INCLUDED_)
#define AFX_DLGINFODIFFUSIONCONTAINER_H__2A86AD31_8B60_4154_8549_7D2A1948E7C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionContainer.h : header file
//

#include "InfoDiffusionParamsConvert.h"

#define MAX_LEN_XML 10*1024*1024

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionContainer dialog

class CDlgInfoDiffusionContainer : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionContainer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionContainer)
	enum { IDD = IDD_DLG_INFO_DIFFUSION_CONTAINER };
	CListCtrl	m_listContainer;
	CComboBox	m_cmbSwitchEffect;
	DWORD	m_dwContainerID;
	CString	m_szContainerName;
	DWORD	m_dwPlayDuration;
	DWORD	m_dwSwitchTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionContainer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionContainer)
	afx_msg void OnBtnSet();
	afx_msg void OnBtnNew();
	afx_msg void OnBtnGetall();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnExit();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListContainer(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnDel();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;
	int m_iDeviceIndex;

	LPNET_DVR_CONTAINER_LIST m_lpContainerList;
	char* m_pOutputXmlBuffer;

	int m_nCurSelContainer;

public:
	void InitContainerCtrlList();
	void RefreshContainerItem(int nContainer);
	void RefreshContainerList();
	void UpdateContainerInfo(int nContainer);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONCONTAINER_H__2A86AD31_8B60_4154_8549_7D2A1948E7C7__INCLUDED_)
