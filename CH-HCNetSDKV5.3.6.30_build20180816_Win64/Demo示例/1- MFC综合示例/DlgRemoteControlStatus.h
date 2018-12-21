#if !defined(AFX_DLGREMOTECONTROLSTATUS_H__72CE5858_0C43_486E_80C9_24631B4A56B8__INCLUDED_)
#define AFX_DLGREMOTECONTROLSTATUS_H__72CE5858_0C43_486E_80C9_24631B4A56B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRemoteControlStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControlStatus dialog

class CDlgRemoteControlStatus : public CDialog
{
// Construction
public:
	CDlgRemoteControlStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRemoteControlStatus)
	enum { IDD = IDD_DLG_REMOTECONTROL_STATUS };
	CComboBox	m_comAlarmStatus;
	DWORD	m_dwAlarmDealyTime;
	DWORD	m_dwDisAlarmDealyTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRemoteControlStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteControlStatus)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGetRemotecontrolStatus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG    m_lServerID;
    LONG    m_iDevIndex;
    LONG    m_lChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREMOTECONTROLSTATUS_H__72CE5858_0C43_486E_80C9_24631B4A56B8__INCLUDED_)
