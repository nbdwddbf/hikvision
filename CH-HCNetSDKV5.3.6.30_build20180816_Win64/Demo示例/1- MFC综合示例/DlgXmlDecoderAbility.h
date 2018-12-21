#if !defined(AFX_DLGXMLDECODERABILITY_H__82E37F42_C446_4814_AFB3_0F18020385D0__INCLUDED_)
#define AFX_DLGXMLDECODERABILITY_H__82E37F42_C446_4814_AFB3_0F18020385D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgXmlDecoderAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXmlDecoderAbility dialog

class CDlgXmlDecoderAbility : public CDialog
{
// Construction
public:
	CDlgXmlDecoderAbility(CWnd* pParent = NULL);   // standard constructor
	~CDlgXmlDecoderAbility();

// Dialog Data
	//{{AFX_DATA(CDlgXmlDecoderAbility)
	enum { IDD = IDD_DLG_XML_DECODER_ABILITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXmlDecoderAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXmlDecoderAbility)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    char    *m_pRecvBuf;
    char    *m_pSendBuf;
	
	BOOL    WirteBufToFile(char *pBuf, DWORD dwBufSize);
	BOOL GetDecoderAbility();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGXMLDECODERABILITY_H__82E37F42_C446_4814_AFB3_0F18020385D0__INCLUDED_)
