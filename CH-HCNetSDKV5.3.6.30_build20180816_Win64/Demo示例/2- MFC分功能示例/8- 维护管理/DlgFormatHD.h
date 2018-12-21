#if !defined(AFX_DLGFORMATHD_H__2C8105A9_6F31_4ABF_B204_563BBBC0A6DF__INCLUDED_)
#define AFX_DLGFORMATHD_H__2C8105A9_6F31_4ABF_B204_563BBBC0A6DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFormatHD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFormatHD dialog

class CDlgFormatHD : public CDialog
{
// Construction
public:
	CDlgFormatHD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFormatHD)
	enum { IDD = IDD_DIALOG_FORMAT_HD };
	CComboBox m_comboHDDriver;
	CString m_csFormatStat;
	CProgressCtrl m_progressFormat;
	//}}AFX_DATA
public:
	LONG	m_lFormat[MAX_DISKNUM_V30];		
	LONG	m_lFormatAll;
	UINT	m_nTime;
	BOOL	m_bFormat[MAX_DISKNUM_V30];	
	DWORD   m_dwDiskNum;
	LONG	m_lDiskSel;
	BOOL	m_bFormatAll;
	int     m_iDiskIndex;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFormatHD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFormatHD)
	afx_msg void OnBtnDoFormat();
	afx_msg void OnBtnFormatExit();
	virtual BOOL OnInitDialog();
	#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
	#else
    afx_msg void OnTimer(UINT nIDEvent);
	#endif
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFORMATHD_H__2C8105A9_6F31_4ABF_B204_563BBBC0A6DF__INCLUDED_)
