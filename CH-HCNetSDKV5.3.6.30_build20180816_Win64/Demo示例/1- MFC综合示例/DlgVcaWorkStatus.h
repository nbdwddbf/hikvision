#if !defined(AFX_DLGVCAWORKSTATUS_H__CB1A7DD2_0DA4_4C2F_83F3_93C26A22D5BF__INCLUDED_)
#define AFX_DLGVCAWORKSTATUS_H__CB1A7DD2_0DA4_4C2F_83F3_93C26A22D5BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaWorkStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaWorkStatus dialog

class CDlgVcaWorkStatus : public CDialog
{
// Construction
public:
	CDlgVcaWorkStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaWorkStatus)
	enum { IDD = IDD_DLG_VCA_WORK_STATUS };
	CComboBox	m_comboWorkStatus;
	CListCtrl	m_listChanStatus;
	int		m_iCpuLoad;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaWorkStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaWorkStatus)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    LONG    m_lChanNum;
    NET_DVR_VCA_DEV_WORKSTATUS m_struDevWorkStatus;
public:
    void InitWnd();
    BOOL GetVcaDevWorkStatus(NET_DVR_VCA_DEV_WORKSTATUS &struDevWorkStatus);

    void SetVcaDevWorkStatusToWnd(NET_DVR_VCA_DEV_WORKSTATUS &struDevWorkStatus);
    void SetVcaChanWorkStatusToWnd(NET_DVR_VCA_CHAN_WORKSTATUS &strVcaChanWorkStatus, int nItem);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAWORKSTATUS_H__CB1A7DD2_0DA4_4C2F_83F3_93C26A22D5BF__INCLUDED_)
