#if !defined(AFX_DLGVCADATABASE_H__934B582A_EEA9_4A09_9DF4_AD4AE7571465__INCLUDED_)
#define AFX_DLGVCADATABASE_H__934B582A_EEA9_4A09_9DF4_AD4AE7571465__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaDataBase.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDataBase dialog

class CDlgVcaDataBase : public CDialog
{
// Construction
public:
	CDlgVcaDataBase(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaDataBase)
	enum { IDD = IDD_DLG_VCA_DATABASE };
	CListCtrl	m_listDataBase;
	CComboBox	m_comboDBType;
	DWORD	m_dwDataBaseID;
	CString	m_csDataBaseName;
	CString	m_csDataBaseAttr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaDataBase)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaDataBase)
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnUpdateDatabase();
	afx_msg void OnBtnDeleteDatabase();
	afx_msg void OnBtnFindDatabase();
	afx_msg void OnBtnStopFind();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;
	LONG    m_lHandle;
	HANDLE  m_hThread;
	LONG    m_lDataBaseNum;

	NET_VCA_DATABASE_PARAM m_struDataBaseParam;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCADATABASE_H__934B582A_EEA9_4A09_9DF4_AD4AE7571465__INCLUDED_)
