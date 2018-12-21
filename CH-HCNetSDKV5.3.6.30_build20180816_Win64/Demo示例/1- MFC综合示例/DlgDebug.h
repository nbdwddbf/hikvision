#if !defined(AFX_DLGDEBUG_H__85226D1D_2B3E_4DC5_A831_8D00AF117FB8__INCLUDED_)
#define AFX_DLGDEBUG_H__85226D1D_2B3E_4DC5_A831_8D00AF117FB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDebug.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDebug dialog

class CDlgDebug : public CDialog
{
// Construction
public:
	CDlgDebug(CWnd* pParent = NULL);   // standard constructor
    ~CDlgDebug();
// Dialog Data
	//{{AFX_DATA(CDlgDebug)
	enum { IDD = IDD_DLG_DEBUG };
	char	m_sDebugInfo[256];
    char	m_sAllDebugInfo[5120];
    CString m_csDebugInfo;
	CString	m_csDebugCMD;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDebug)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDebug)
	virtual BOOL OnInitDialog();
	afx_msg void OnOk();
#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif	afx_msg void OnBtnRefuse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
	LONG    m_lChannel;
    long    m_lHandle;

    NET_DVR_DEBUG_CMD m_struDebugCMD;
    NET_DVR_DEBUG_INFO m_struDebugInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEBUG_H__85226D1D_2B3E_4DC5_A831_8D00AF117FB8__INCLUDED_)
