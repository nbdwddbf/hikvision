#if !defined(AFX_DLGXMLLCDABILITY_H__AE3E69DF_6A11_44F9_84D1_8EB0C245E4CA__INCLUDED_)
#define AFX_DLGXMLLCDABILITY_H__AE3E69DF_6A11_44F9_84D1_8EB0C245E4CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgXmlLCDAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXmlLCDAbility dialog

class CDlgXmlLCDAbility : public CDialog
{
// Construction
public:
	CDlgXmlLCDAbility(CWnd* pParent = NULL);   // standard constructor
	~CDlgXmlLCDAbility();
// Dialog Data
	//{{AFX_DATA(CDlgXmlLCDAbility)
	enum { IDD = IDD_DLG_XML_LCD_ABILITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXmlLCDAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXmlLCDAbility)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
    int     m_iDevIndex;
    char    *m_pRecvBuf;
    char    *m_pSendBuf;
	
	BOOL    WirteBufToFile(char *pBuf, DWORD dwBufSize);
	BOOL	GetLCDAbility();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGXMLLCDABILITY_H__AE3E69DF_6A11_44F9_84D1_8EB0C245E4CA__INCLUDED_)
