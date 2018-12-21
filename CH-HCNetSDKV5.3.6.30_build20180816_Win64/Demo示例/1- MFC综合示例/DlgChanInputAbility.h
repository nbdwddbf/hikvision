#if !defined(AFX_DLGCHANINPUTABILITY_H__735E97AC_A1AA_4802_A7E7_D78A6F85726C__INCLUDED_)
#define AFX_DLGCHANINPUTABILITY_H__735E97AC_A1AA_4802_A7E7_D78A6F85726C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgChanInputAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgChanInputAbility dialog

class CDlgChanInputAbility : public CDialog
{
// Construction
public:
	CDlgChanInputAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgChanInputAbility)
	enum { IDD = IDD_DLG_CHAN_INPUT_ABILITY };
	UINT	m_dwChannelNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgChanInputAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgChanInputAbility)
	afx_msg void OnBtnGetAbility();
	virtual BOOL OnInitDialog();
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

#endif // !defined(AFX_DLGCHANINPUTABILITY_H__735E97AC_A1AA_4802_A7E7_D78A6F85726C__INCLUDED_)
