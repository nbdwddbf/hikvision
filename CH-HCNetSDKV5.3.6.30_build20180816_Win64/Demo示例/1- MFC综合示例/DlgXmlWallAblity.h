#if !defined(AFX_DLGXMLWALLABLITY_H__63086FAB_79B9_4B77_8A3C_6EA62AE5D108__INCLUDED_)
#define AFX_DLGXMLWALLABLITY_H__63086FAB_79B9_4B77_8A3C_6EA62AE5D108__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgXmlWallAblity.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXmlWallAblity dialog

class CDlgXmlWallAblity : public CDialog
{
// Construction
public:
	CDlgXmlWallAblity(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgXmlWallAblity)
	enum { IDD = IDD_DLG_XML_WALL_ABILITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXmlWallAblity)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXmlWallAblity)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	char*   m_pRecvBuf;
    LONG    m_lServerID;
    int     m_iDevIndex;
	
	BOOL WirteBufToFile(char *pBuf, DWORD dwBufSize);
	void GetWallAbility();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGXMLWALLABLITY_H__63086FAB_79B9_4B77_8A3C_6EA62AE5D108__INCLUDED_)
