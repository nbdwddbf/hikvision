#if !defined(AFX_DLGINFODIFFUSIONTERNIMALPREVIEW_H__4BA06E3A_080F_4D4C_A397_68528BA0988B__INCLUDED_)
#define AFX_DLGINFODIFFUSIONTERNIMALPREVIEW_H__4BA06E3A_080F_4D4C_A397_68528BA0988B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionTernimalPreview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionTernimalPreview dialog

class CDlgInfoDiffusionTernimalPreview : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionTernimalPreview(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionTernimalPreview)
	enum { IDD = IDD_DLG_INFO_DIFFUSION_TERMINAL_PREVIEW };
	DWORD	m_dwChannelNo;
	DWORD	m_dwTerminalNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionTernimalPreview)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionTernimalPreview)
	afx_msg void OnBtnStartPreview();
	afx_msg void OnBtnStopPreview();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;
	int m_iDevIndex;

	NET_DVR_CLIENTINFO m_struPreview;
	LONG m_lPreviewHandle;

public:
	LONG StartPreview();
	BOOL StopPreview();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONTERNIMALPREVIEW_H__4BA06E3A_080F_4D4C_A397_68528BA0988B__INCLUDED_)
