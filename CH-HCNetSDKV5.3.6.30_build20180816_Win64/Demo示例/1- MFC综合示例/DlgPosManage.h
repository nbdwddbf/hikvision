#if !defined(AFX_DLGPOSMANAGE_H__B84DADB7_70C5_4E5C_A16C_C80EA2A569D4__INCLUDED_)
#define AFX_DLGPOSMANAGE_H__B84DADB7_70C5_4E5C_A16C_C80EA2A569D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPosManage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPosManage dialog

class CDlgPosManage : public CDialog
{
// Construction
public:
	CDlgPosManage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPosManage)
	enum { IDD = IDD_DLG_POS_MANAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPosManage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPosManage)
	afx_msg void OnBtnFilterruleCfg();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnChanFilterCfg();
	afx_msg void OnBtnPosConnectCfg();
	afx_msg void OnBtnReceiveData();
	afx_msg void OnBtnComRecvdata();
    afx_msg void OnBnClickedBtnHiddenInfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int m_iUserID;
	int m_iDevIndex;
    int m_lChanNo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPOSMANAGE_H__B84DADB7_70C5_4E5C_A16C_C80EA2A569D4__INCLUDED_)
