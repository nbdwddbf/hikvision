#if !defined(AFX_DLGXMLJPEGCAPABILITY_H__9E3C1BC0_0247_4C87_A3CD_D9B55B7D0E7A__INCLUDED_)
#define AFX_DLGXMLJPEGCAPABILITY_H__9E3C1BC0_0247_4C87_A3CD_D9B55B7D0E7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgXmlJpegCapAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXmlJpegCapAbility dialog

class CDlgXmlJpegCapAbility : public CDialog
{
// Construction
public:
	CDlgXmlJpegCapAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgXmlJpegCapAbility)
	enum { IDD = IDD_DLG_XML_JPEG_CAP_ABILITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXmlJpegCapAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXmlJpegCapAbility)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    char    *m_pRecvBuf;
    char    *m_pSendBuf;
	
	BOOL    WirteBufToFile(char *pBuf, DWORD dwBufSize);
	BOOL GetJpegCapAbility();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGXMLJPEGCAPABILITY_H__9E3C1BC0_0247_4C87_A3CD_D9B55B7D0E7A__INCLUDED_)
