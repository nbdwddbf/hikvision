#if !defined(AFX_DLGREMOTECONTROLPLAY_H__9B0E1F45_7242_4491_A025_DC1E5988B5DC__INCLUDED_)
#define AFX_DLGREMOTECONTROLPLAY_H__9B0E1F45_7242_4491_A025_DC1E5988B5DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRemoteControlPlay.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControlPlay dialog

class CDlgRemoteControlPlay : public CDialog
{
// Construction
public:
	CDlgRemoteControlPlay(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRemoteControlPlay)
	enum { IDD = IDD_DLG_REMOTE_PLAY };
	BOOL	m_bHDMI1;
	BOOL	m_bHDMI2;
	BOOL	m_bVGA1;
	BOOL	m_bVGA2;
	BOOL	m_bVGA3;
	BOOL	m_bVGA4;
	BOOL	m_bVGA5_10;
	CString	m_sPlayFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRemoteControlPlay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteControlPlay)
	afx_msg void OnBtnPlay();
	afx_msg void OnBtnStopPlay();
	afx_msg void OnBtnPause();
	afx_msg void OnBtnResume();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREMOTECONTROLPLAY_H__9B0E1F45_7242_4491_A025_DC1E5988B5DC__INCLUDED_)
