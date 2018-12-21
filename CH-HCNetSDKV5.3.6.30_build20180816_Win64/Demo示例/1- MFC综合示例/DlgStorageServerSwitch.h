#if !defined(AFX_DLGSTORAGESERVERSWITCH_H__73A02777_60CE_45F3_9A8E_552493CBC0E9__INCLUDED_)
#define AFX_DLGSTORAGESERVERSWITCH_H__73A02777_60CE_45F3_9A8E_552493CBC0E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStorageServerSwitch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgStorageServerSwitch dialog

class CDlgStorageServerSwitch : public CDialog
{
// Construction
public:
	CDlgStorageServerSwitch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgStorageServerSwitch)
	enum { IDD = IDD_DLG_STORAGE_SERVER_SWITCH };
	BOOL	m_bAllAddInfoSwitch;
	BOOL	m_bAllPicSwitch;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgStorageServerSwitch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgStorageServerSwitch)
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSTORAGESERVERSWITCH_H__73A02777_60CE_45F3_9A8E_552493CBC0E9__INCLUDED_)
