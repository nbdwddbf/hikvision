#if !defined(AFX_DLGC10S21CONFIG_H__576F173D_F5FE_4D91_832C_704E65898A81__INCLUDED_)
#define AFX_DLGC10S21CONFIG_H__576F173D_F5FE_4D91_832C_704E65898A81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgC10S21Config.h : header file
//

#include "ConvertC10S21Param.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgC10S21Config dialog

class CDlgC10S21Config : public CDialog
{
// Construction
public:
	CDlgC10S21Config(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgC10S21Config)
	enum { IDD = IDD_DLG_C10S21 };
	CListCtrl	m_listLoginCfg;
	DWORD	m_dwInputNo;
	CString	m_sIPAddress;
	CString	m_sPassword;
	DWORD	m_dwPort;
	DWORD	m_dwServerNo;
	CString	m_sUserName;
	DWORD	m_dwVideoWallNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgC10S21Config)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgC10S21Config)
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnGetAll();
	afx_msg void OnBtnOnekeyReset();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	afx_msg void OnDestroy();
	afx_msg void OnClickListLoginCfg(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;
	int m_iDevIndex;

	NET_DVR_SCREEN_SERVER_LOGIN_CFG m_struLoginCfg;
	NET_DVR_SCREEN_SERVER_LOGIN_CFG_LIST m_struLoginCfgList;

	int m_nCurItem;

	char* m_pXmlOutput;

public:
 	void InitListCtrl();
 	void RefreshList();
 	void RefreshListItem(int nItemIndex);
 	void UpdateLoginCfgToDlg(int nItemIndex);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGC10S21CONFIG_H__576F173D_F5FE_4D91_832C_704E65898A81__INCLUDED_)
