#if !defined(AFX_DLGTERMGROUP_H__334734A0_1912_462B_9EBB_1CAB21FB906F__INCLUDED_)
#define AFX_DLGTERMGROUP_H__334734A0_1912_462B_9EBB_1CAB21FB906F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTermGroup.h : header file
//

#include "InfoDiffusionParamsConvert.h"

#define MAX_LEN_XML 10*1024*1024 //xml最大长度

/////////////////////////////////////////////////////////////////////////////
// CDlgTermGroup dialog

class CDlgTermGroup : public CDialog
{
// Construction
public:
	CDlgTermGroup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTermGroup)
	enum { IDD = IDD_DLG_TERM_GROUP };
	CListCtrl	m_listTerminal;
	CListCtrl	m_listGroup;
	DWORD	m_dwGroupID;
	DWORD	m_dwTerminalID;
	CString	m_szGroupName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTermGroup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTermGroup)
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnDelGroup();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnGetAll();
	afx_msg void OnBtnMod();
	afx_msg void OnBtnNew();
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnClickListGroup(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListTerminal(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;
	int m_iDeviceIndex;

	LPNET_DVR_TERMINAL_GROUP m_lpGroup;
	LPNET_DVR_TERMINAL_GROUP_LIST m_lpGroupList;
	char* m_pOutputXmlBuffer;

	int m_nCurSelGroup;
	int m_nCurSelTerminal;

public:
	void InitTerminalCtrlList();
	void InitGroupCtrlList();
	void RefreshTerminalList(DWORD dwaTerminal[], DWORD dwTermCount);
	void RefreshGroupList();
	void UpdateGroupInfo(LPNET_DVR_TERMINAL_GROUP lpGroup);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTERMGROUP_H__334734A0_1912_462B_9EBB_1CAB21FB906F__INCLUDED_)
