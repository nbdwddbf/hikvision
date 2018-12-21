#if !defined(AFX_DLGXMLNETAPPABILITY_H__5488952D_F5D7_4C8A_B779_14F9BD0AEE67__INCLUDED_)
#define AFX_DLGXMLNETAPPABILITY_H__5488952D_F5D7_4C8A_B779_14F9BD0AEE67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgXmlNetAppAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXmlNetAppAbility dialog

class CDlgXmlNetAppAbility : public CDialog
{
// Construction
public:
	CDlgXmlNetAppAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgXmlNetAppAbility)
	enum { IDD = IDD_DLG_XML_NETAPP_ABILITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXmlNetAppAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXmlNetAppAbility)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    char    *m_pRecvBuf;
    char    *m_pSendBuf;
	
	BOOL    WirteBufToFile(char *pBuf, DWORD dwBufSize);
	BOOL GetNetAppAbility();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGXMLNETAPPABILITY_H__5488952D_F5D7_4C8A_B779_14F9BD0AEE67__INCLUDED_)
