#if !defined(AFX_DLGDYNCHANABILITY_H__71AB52AB_127A_4722_A906_0CEAD8A1C351__INCLUDED_)
#define AFX_DLGDYNCHANABILITY_H__71AB52AB_127A_4722_A906_0CEAD8A1C351__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDynChanAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDynChanAbility dialog

class CDlgDynChanAbility : public CDialog
{
// Construction
public:
	CDlgDynChanAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDynChanAbility)
	enum { IDD = IDD_DLG_DYNCHAN_ABILITY };
	DWORD	m_dwChannelNO;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDynChanAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDynChanAbility)
	afx_msg void OnBtnGetAbility();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    char*   m_pRecvBuf;
    LONG    m_lServerID;
    int     m_iDevIndex;
	
	BOOL WirteBufToFile(char *pBuf, DWORD dwBufSize);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDYNCHANABILITY_H__71AB52AB_127A_4722_A906_0CEAD8A1C351__INCLUDED_)
