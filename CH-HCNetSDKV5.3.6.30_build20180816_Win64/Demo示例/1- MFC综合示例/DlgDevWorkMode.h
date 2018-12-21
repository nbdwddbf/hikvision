#if !defined(AFX_DLGDEVWORDMODE_H__41BE27BD_E064_487B_A8B2_09992CA0AA37__INCLUDED_)
#define AFX_DLGDEVWORDMODE_H__41BE27BD_E064_487B_A8B2_09992CA0AA37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDevWordMode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDevWordMode dialog

class CDlgDevWorkMode : public CDialog
{
// Construction
public:
	CDlgDevWorkMode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDevWordMode)
	enum { IDD = IDD_DLG_DEV_WORKMODE };
	BOOL	m_bEnableCS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDevWordMode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDevWordMode)
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnExit();
    afx_msg void OnBtnStorageServerSwitch();
	afx_msg void OnBtnStorageServerFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
    int  m_iDevIndex;
    LONG m_lChannel;
    NET_DVR_CLOUD_STORAGE_CFG m_struCSCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEVWORDMODE_H__41BE27BD_E064_487B_A8B2_09992CA0AA37__INCLUDED_)
