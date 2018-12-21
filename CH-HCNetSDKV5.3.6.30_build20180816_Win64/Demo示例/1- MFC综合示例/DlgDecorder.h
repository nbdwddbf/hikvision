#if !defined(AFX_DLGDECORDER_H__954C31A7_2159_44ED_BB4A_F74E8D65F5BC__INCLUDED_)
#define AFX_DLGDECORDER_H__954C31A7_2159_44ED_BB4A_F74E8D65F5BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDecorder.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDecorder dialog

class CDlgDecorder : public CDialog
{
// Construction
public:
	CDlgDecorder(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDecorder)
	enum { IDD = IDD_DLG_DECORDER };
	BOOL	m_bRoamEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDecorder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDecorder)
	afx_msg void OnButtonGet();
	afx_msg void OnButtonSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	LONG m_lUserID;
	int m_iDeviceIndex;
	NET_DVR_WIN_ROAM_SWITCH_CFG m_struRoamCfg;
	
public:
	void Init(LONG lUserID, int iDevIndex){m_lUserID = lUserID; m_iDeviceIndex = iDevIndex;};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDECORDER_H__954C31A7_2159_44ED_BB4A_F74E8D65F5BC__INCLUDED_)
