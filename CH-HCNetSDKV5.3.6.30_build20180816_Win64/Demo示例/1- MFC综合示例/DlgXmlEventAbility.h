#if !defined(AFX_DLGXMLEVENTABILITY_H__59A88226_0114_4DA6_B52C_31322D5468E9__INCLUDED_)
#define AFX_DLGXMLEVENTABILITY_H__59A88226_0114_4DA6_B52C_31322D5468E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgXmlEventAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXmlEventAbility dialog

class CDlgXmlEventAbility : public CDialog
{
// Construction
public:
	CDlgXmlEventAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgXmlEventAbility)
	enum { IDD = IDD_DLG_XML_EVENT_ABILITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXmlEventAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXmlEventAbility)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    char    *m_pRecvBuf;
    char    *m_pSendBuf;
	
	BOOL    WirteBufToFile(char *pBuf, DWORD dwBufSize);
	BOOL GetITCAbility();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGXMLEVENTABILITY_H__59A88226_0114_4DA6_B52C_31322D5468E9__INCLUDED_)
