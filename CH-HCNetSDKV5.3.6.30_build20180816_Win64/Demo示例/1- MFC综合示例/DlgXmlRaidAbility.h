#if !defined(AFX_DLGXMLRAIDABILITY_H__8154FD28_6897_49A6_9A14_AEB10DB2BC7F__INCLUDED_)
#define AFX_DLGXMLRAIDABILITY_H__8154FD28_6897_49A6_9A14_AEB10DB2BC7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgXmlRaidAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXmlRaidAbility dialog

class CDlgXmlRaidAbility : public CDialog
{
// Construction
public:
	CDlgXmlRaidAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgXmlRaidAbility)
	enum { IDD = IDD_DLG_XML_RAID_ABILITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXmlRaidAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXmlRaidAbility)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    char*   m_pRecvBuf;
    LONG    m_lServerID;
    int     m_iDevIndex;
	
	BOOL WirteBufToFile(char *pBuf, DWORD dwBufSize);
	void GetRaidAbility();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGXMLRAIDABILITY_H__8154FD28_6897_49A6_9A14_AEB10DB2BC7F__INCLUDED_)
