#if !defined(AFX_DLGITSBASEINFO_H__E5754EC2_3F05_400B_AABB_6FDF1CF15E3E__INCLUDED_)
#define AFX_DLGITSBASEINFO_H__E5754EC2_3F05_400B_AABB_6FDF1CF15E3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgITSBaseInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgITSBaseInfo dialog

class CDlgITSBaseInfo : public CDialog
{
// Construction
public:
	CDlgITSBaseInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgITSBaseInfo)
	enum { IDD = IDD_DLG_ITS_GET_BASEINFO };
	CString	m_csMainVersion;
	CString	m_csBvtVersion;
	CString	m_csLptVersion;
	CString	m_csMprVersion;
	CString	m_csTldVersion;
	CString	m_csTvdVersion;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgITSBaseInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgITSBaseInfo)
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lChannel; 
    int  m_iDevIndex;
    LONG m_lServerID;
	NET_ITS_BASEINFO m_struBaseInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGITSBASEINFO_H__E5754EC2_3F05_400B_AABB_6FDF1CF15E3E__INCLUDED_)
