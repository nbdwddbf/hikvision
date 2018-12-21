#if !defined(AFX_DLGXMLVIDEOPIC_H__FA34C8F0_72D6_4EC6_98F0_C9F5F0500FE9__INCLUDED_)
#define AFX_DLGXMLVIDEOPIC_H__FA34C8F0_72D6_4EC6_98F0_C9F5F0500FE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgXmlVideoPic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXmlVideoPic dialog

class CDlgXmlVideoPic : public CDialog
{
// Construction
public:
	CDlgXmlVideoPic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgXmlVideoPic)
	enum { IDD = IDD_DLG_XML_VIDEO_PIC_ABILITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXmlVideoPic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXmlVideoPic)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    char    *m_pRecvBuf;
    char    *m_pSendBuf;
	
	BOOL    WirteBufToFile(char *pBuf, DWORD dwBufSize);
	BOOL GetVideoPicAbility();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGXMLVIDEOPIC_H__FA34C8F0_72D6_4EC6_98F0_C9F5F0500FE9__INCLUDED_)
