#if !defined(AFX_XMLUSERABILITY_H__4EC1CC36_8E6F_409E_B2B5_7925286EAF0D__INCLUDED_)
#define AFX_XMLUSERABILITY_H__4EC1CC36_8E6F_409E_B2B5_7925286EAF0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XmlUserAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXmlUserAbility dialog

class CXmlUserAbility : public CDialog
{
// Construction
public:
	CXmlUserAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXmlUserAbility)
	enum { IDD = IDD_DLG_XML_USER_ABILITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXmlUserAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXmlUserAbility)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    char    *m_pRecvBuf;
    char    *m_pSendBuf;
	
	BOOL    WirteBufToFile(char *pBuf, DWORD dwBufSize);
	BOOL GetUserAbility();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMLUSERABILITY_H__4EC1CC36_8E6F_409E_B2B5_7925286EAF0D__INCLUDED_)
