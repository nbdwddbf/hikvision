#pragma once
#include "afxwin.h"


// CDlgRemoteShowString dialog

class CDlgRemoteShowString : public CDialog
{
	DECLARE_DYNAMIC(CDlgRemoteShowString)

public:
	CDlgRemoteShowString(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRemoteShowString();

// Dialog Data

public:


	//{{AFX_DATA(CDlgRemoteShowString)
	enum { IDD = IDD_DLG_REMOTE_SHOW_STRING };
	CComboBox m_comboShowArea;
	BOOL m_bChkShow;
	int m_iStringX;
	int m_iStringY;
	CString m_csString;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CDlgRemoteShowString)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteShowString)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnStringOk();
	afx_msg void OnBnClickedBtnStringExit();
	afx_msg void OnBnClickedBtnStringSet();
	afx_msg void OnCbnSelchangeComboShowArea();
	afx_msg void OnBnClickedChkShow();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:	
	LONG	m_lLoginID;
	int		m_iChanShowNum;//displayed device channel number, usually start from 1
	NET_DVR_SHOWSTRING_V30 m_struShowString;
	DWORD dwReturned;
	
	void EnableString(BOOL bFlag);
    DWORD m_dwChanNo;
    afx_msg void OnBnClickedBtnGet();
};
