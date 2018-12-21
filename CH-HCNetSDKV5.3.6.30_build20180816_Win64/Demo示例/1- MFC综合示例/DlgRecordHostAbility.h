#if !defined(AFX_DLGRECORDHOSTABILITY_H__73C0547E_697D_4E87_B18B_5BFCD4FF55DC__INCLUDED_)
#define AFX_DLGRECORDHOSTABILITY_H__73C0547E_697D_4E87_B18B_5BFCD4FF55DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordHostAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgRecordHostAbility dialog

class DlgRecordHostAbility : public CDialog
{
// Construction
public:
	DlgRecordHostAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgRecordHostAbility)
	enum { IDD = IDD_DLG_RECORDHOST_ABILITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	LONG    m_lServerID;
    int     m_iDevIndex;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgRecordHostAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgRecordHostAbility)
		// NOTE: the ClassWizard will add member functions here
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
    char    *m_pRecvBuf;
    char    *m_pSendBuf;
	
	BOOL    WirteBufToFile(char *pBuf, DWORD dwBufSize);
	BOOL GetITCAbility();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDHOSTABILITY_H__73C0547E_697D_4E87_B18B_5BFCD4FF55DC__INCLUDED_)
