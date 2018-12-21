#if !defined(AFX_DLGXMLITCABILITY_H__8D76CDA9_FB7C_4EF8_95EA_5BBB197496AA__INCLUDED_)
#define AFX_DLGXMLITCABILITY_H__8D76CDA9_FB7C_4EF8_95EA_5BBB197496AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgXmlItcAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXmlItcAbility dialog

class CDlgXmlItcAbility : public CDialog
{
// Construction
public:
	CDlgXmlItcAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgXmlItcAbility)
	enum { IDD = IDD_DLG_XML_ITC_ITS_ABILITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXmlItcAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXmlItcAbility)
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

#endif // !defined(AFX_DLGXMLITCABILITY_H__8D76CDA9_FB7C_4EF8_95EA_5BBB197496AA__INCLUDED_)
