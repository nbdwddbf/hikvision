#if !defined(AFX_DLGLINKSTATUS_H__2DB2BF3E_2DFC_4FA8_A6C9_936E7B6CE5EA__INCLUDED_)
#define AFX_DLGLINKSTATUS_H__2DB2BF3E_2DFC_4FA8_A6C9_936E7B6CE5EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLinkStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLinkStatus dialog

class CDlgLinkStatus : public CDialog
{
// Construction
public:
	CDlgLinkStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLinkStatus)
	enum { IDD = IDD_DLG_LINK_STATUS };
	CListCtrl	m_listLinkStatus;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLinkStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLinkStatus)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    DWORD   m_dwIndex;
    NET_DVR_LINK_STATUS m_struLinkStatus;
public:
    BOOL GetLinkStatus(NET_DVR_LINK_STATUS &struLinkStatus, DWORD dwGroupNo);
    void InitWnd();
    void SetLinkStatusToWnd(NET_DVR_LINK_STATUS &struLinkStatus, DWORD dwGroupNo);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLINKSTATUS_H__2DB2BF3E_2DFC_4FA8_A6C9_936E7B6CE5EA__INCLUDED_)
