#if !defined(AFX_DLGVISDEVINFO_H__89B6E922_473E_4ACA_B67A_AD026C8ECD7F__INCLUDED_)
#define AFX_DLGVISDEVINFO_H__89B6E922_473E_4ACA_B67A_AD026C8ECD7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVISDevInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVISDevInfo dialog

class CDlgVISDevInfo : public CDialog
{
// Construction
public:
	CDlgVISDevInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVISDevInfo)
	enum { IDD = IDD_DLG_VIDEO_INTERCOM_DEVINFO };
	CString	m_csDevID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVISDevInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVISDevInfo)
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG m_lUserID;
    int m_iDevIndex;
private:
    NET_DVR_VIS_DEV_INFO m_struDevInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVISDEVINFO_H__89B6E922_473E_4ACA_B67A_AD026C8ECD7F__INCLUDED_)
