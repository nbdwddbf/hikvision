#if !defined(AFX_DLGVCAALARMLOGO_H__8FFF8FAA_C9ED_41F8_9C6D_7BD703B127B1__INCLUDED_)
#define AFX_DLGVCAALARMLOGO_H__8FFF8FAA_C9ED_41F8_9C6D_7BD703B127B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVCAAlarmLogo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgVCAAlarmLogo dialog

class DlgVCAAlarmLogo : public CDialog
{
// Construction
public:
	DlgVCAAlarmLogo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgVCAAlarmLogo)
	enum { IDD = IDD_DLG_VCA_ALARMLOGO };
	BOOL	m_BEnableLogo;
	BOOL	m_BAlarmFlash;
	DWORD	m_dwChannel;
	DWORD	m_dwFlashTime;
	DWORD	m_dwLogoX;
	DWORD	m_dwLogoY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgVCAAlarmLogo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgVCAAlarmLogo)
	afx_msg void OnButVcaGet();
	afx_msg void OnButVcaSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID; 
    LONG m_lDeviceID; 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAALARMLOGO_H__8FFF8FAA_C9ED_41F8_9C6D_7BD703B127B1__INCLUDED_)
