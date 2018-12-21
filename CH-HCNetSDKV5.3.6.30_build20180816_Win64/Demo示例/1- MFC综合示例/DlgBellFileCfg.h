#if !defined(AFX_DLGBELLFILECFG_H__E109B585_43F3_4C7C_8784_18DC4117F9E7__INCLUDED_)
#define AFX_DLGBELLFILECFG_H__E109B585_43F3_4C7C_8784_18DC4117F9E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DlgVideoIntercomCfg.h"
// DlgBellFileCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBellFileCfg dialog

class CDlgBellFileCfg : public CDialog
{
// Construction
public:
	CDlgBellFileCfg(CWnd* pParent = NULL);   // standard constructor
	~CDlgBellFileCfg();

// Dialog Data
	//{{AFX_DATA(CDlgBellFileCfg)
	enum { IDD = IDD_DLG_BELLFILE_CFG };
	CComboBox	m_comboStatus;
	CListCtrl	m_BellFileList;
	CString	m_csBellFilePath;
	DWORD	m_dwBellNO;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBellFileCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBellFileCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSearchButton();
	afx_msg LRESULT OnMsgGetbellCfgFinish(WPARAM wParam,LPARAM lParam);
    afx_msg LRESULT OnMsgAddbellCfgToList(WPARAM wParam,LPARAM lParam);
    afx_msg LRESULT OnMsgUpdateData(WPARAM wParam,LPARAM lParam);
	afx_msg void OnUploadButton();
	afx_msg void OnClickBellfileList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBrowseButton();
	afx_msg void OnAddButton();
	afx_msg void OnClose();
#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int m_iSelectItem;
	LONG m_lServerID;
	LONG m_iDevIndex;
	LONG m_lGetBellHandle;
	LONG m_lSetBellHandle;

protected:
	void AddToBellList(const NET_DVR_RING_SEARCH_CFG& struBellInfo , const DWORD dwBellNo, CString strFilePath = "Ô¶³ÌÎÄ¼þ");

public:
	void ProcessGetBellCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBELLFILECFG_H__E109B585_43F3_4C7C_8784_18DC4117F9E7__INCLUDED_)
