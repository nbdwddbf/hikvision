#if !defined(AFX_DLGREMOTECONTROLABILITY_H__6A56DD74_CD30_43AB_934E_D56EFBA9EEE8__INCLUDED_)
#define AFX_DLGREMOTECONTROLABILITY_H__6A56DD74_CD30_43AB_934E_D56EFBA9EEE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRemoteControlAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControlAbility dialog

class CDlgRemoteControlAbility : public CDialog
{
// Construction
public:
	CDlgRemoteControlAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRemoteControlAbility)
	enum { IDD = IDD_DLG_REMOTE_CONTROL_ABILITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRemoteControlAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteControlAbility)
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

#endif // !defined(AFX_DLGREMOTECONTROLABILITY_H__6A56DD74_CD30_43AB_934E_D56EFBA9EEE8__INCLUDED_)
