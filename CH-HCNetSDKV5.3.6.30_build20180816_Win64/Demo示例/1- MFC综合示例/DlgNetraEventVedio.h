#if !defined(AFX_DLGNETRAEVENTVEDIO_H__458FE900_C333_40B2_BDE9_C245DFB2741A__INCLUDED_)
#define AFX_DLGNETRAEVENTVEDIO_H__458FE900_C333_40B2_BDE9_C245DFB2741A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNetraEventVedio.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNetraEventVedio dialog

class CDlgNetraEventVedio : public CDialog
{
// Construction
public:
	CDlgNetraEventVedio(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNetraEventVedio)
	enum { IDD = IDD_DLG_EVENT_VEDIO };
	UINT	m_dwCmdType;
	CString	m_strEventID;
	UINT	m_dwRecordTimeLen;
	CString	m_strStreamID;
	UINT	m_uiChannelNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNetraEventVedio)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNetraEventVedio)
	afx_msg void OnBtnStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG    m_lLoginID;
	int     m_iDeviceIndex;
	LONG    m_lChannel;
    int m_iLockDuration;
    BOOL m_bBackup;
    BOOL m_bPreRecord;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNETRAEVENTVEDIO_H__458FE900_C333_40B2_BDE9_C245DFB2741A__INCLUDED_)
