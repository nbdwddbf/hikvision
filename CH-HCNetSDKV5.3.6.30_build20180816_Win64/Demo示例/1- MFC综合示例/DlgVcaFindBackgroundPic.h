#if !defined(AFX_DLGVCAFINDBACKGROUNDPIC_H__4DF44930_2BD1_4428_9F53_5EF3D7099D37__INCLUDED_)
#define AFX_DLGVCAFINDBACKGROUNDPIC_H__4DF44930_2BD1_4428_9F53_5EF3D7099D37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaFindBackgroundPic.h : header file
//
#include "Picture.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFindBackgroundPic dialog

class CDlgVcaFindBackgroundPic : public CDialog
{
// Construction
public:
	CDlgVcaFindBackgroundPic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaFindBackgroundPic)
	enum { IDD = IDD_DLG_VCA_FIND_BACKGROUNDPIC };
	CStatic	m_PicWnd;
	DWORD	m_dwFacePicID;
	CString	m_csPicPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaFindBackgroundPic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaFindBackgroundPic)
	afx_msg void OnBtnFind();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lServerID;
    int  m_iDevIndex;
	CPicture m_picture;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAFINDBACKGROUNDPIC_H__4DF44930_2BD1_4428_9F53_5EF3D7099D37__INCLUDED_)
