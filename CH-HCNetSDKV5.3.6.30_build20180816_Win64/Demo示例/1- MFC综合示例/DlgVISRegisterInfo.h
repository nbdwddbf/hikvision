#if !defined(AFX_DLGVISREGISTERINFO_H__A76DB7E9_1AC8_4638_A183_F7C10D5E1C2B__INCLUDED_)
#define AFX_DLGVISREGISTERINFO_H__A76DB7E9_1AC8_4638_A183_F7C10D5E1C2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVISRegisterInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVISRegisterInfo dialog

class CDlgVISRegisterInfo : public CDialog
{
// Construction
public:
	CDlgVISRegisterInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVISRegisterInfo)
	enum { IDD = IDD_DLG_VIDEO_INTERCOM_REGISTER_INFO };
	CListCtrl	m_lstRegisterInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVISRegisterInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVISRegisterInfo)
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG m_lUserID;
    int m_iDevIndex;
    LONG m_lHande;
    HANDLE m_hGetInfoThread;
    BOOL m_bGetNext;
protected:
    static DWORD WINAPI GetRegisterDevInfoThread(LPVOID lpVehInfo);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVISREGISTERINFO_H__A76DB7E9_1AC8_4638_A183_F7C10D5E1C2B__INCLUDED_)
