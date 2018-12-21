#if !defined(AFX_DLGIPPARACFGV40_H__5B3D0092_DDBA_4222_9C94_EBBA4A872C2A__INCLUDED_)
#define AFX_DLGIPPARACFGV40_H__5B3D0092_DDBA_4222_9C94_EBBA4A872C2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIPParaCfgV40.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIPParaCfgV40 dialog

class CDlgIPParaCfgV40 : public CDialog
{
// Construction
public:
	CDlgIPParaCfgV40(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIPParaCfgV40)
	enum { IDD = IDD_DGL_IPPARACFG_V40 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIPParaCfgV40)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIPParaCfgV40)
	afx_msg void OnBtnSetup();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    NET_DVR_IPPARACFG_V40 m_struIPParaCfgV40; 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIPPARACFGV40_H__5B3D0092_DDBA_4222_9C94_EBBA4A872C2A__INCLUDED_)
