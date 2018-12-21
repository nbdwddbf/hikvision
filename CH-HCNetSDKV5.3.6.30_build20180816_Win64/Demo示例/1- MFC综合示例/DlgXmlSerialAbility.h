#if !defined(AFX_DLGXMLSERIALABILITY_H__E5EFF477_8764_44E7_A139_C5AEEDBE1E01__INCLUDED_)
#define AFX_DLGXMLSERIALABILITY_H__E5EFF477_8764_44E7_A139_C5AEEDBE1E01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgXmlSerialAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXmlSerialAbility dialog

class CDlgXmlSerialAbility : public CDialog
{
// Construction
public:
	CDlgXmlSerialAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgXmlSerialAbility)
	enum { IDD = IDD_DLG_XML_SERIAL_ABILITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXmlSerialAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXmlSerialAbility)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    char    *m_pRecvBuf;
    char    *m_pSendBuf;
	
	BOOL    WirteBufToFile(char *pBuf, DWORD dwBufSize);
	BOOL GetSerialAbility();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGXMLSERIALABILITY_H__E5EFF477_8764_44E7_A139_C5AEEDBE1E01__INCLUDED_)
