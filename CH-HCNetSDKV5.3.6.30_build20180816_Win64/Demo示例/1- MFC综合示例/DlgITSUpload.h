#if !defined(AFX_DLGITSUPLOAD_H__DFA1DC4A_BE54_4652_84D7_08B467B4CDA7__INCLUDED_)
#define AFX_DLGITSUPLOAD_H__DFA1DC4A_BE54_4652_84D7_08B467B4CDA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgITSUpload.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgITSUpload dialog

class CDlgITSUpload : public CDialog
{
// Construction
public:
	CDlgITSUpload(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgITSUpload)
	enum { IDD = IDD_DLG_ITS_UPLOAD };
	int		m_iHostIndex;
	CString	m_strHostIP;
	int		m_iHostPort;
	BOOL	m_bStopUpload;
	int		m_iUploadStrategy;
	DWORD	m_dwUploadInterval;
	DWORD	m_dwUploadTimeout;
	BOOL	m_bPostData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgITSUpload)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
	LONG m_lChannel; 
    int  m_iDevIndex;
    LONG m_lServerID;
	NET_ITS_UPLOAD_CFG m_struUploadCfg;
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgITSUpload)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnsure();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeCmbHostIndex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGITSUPLOAD_H__DFA1DC4A_BE54_4652_84D7_08B467B4CDA7__INCLUDED_)
