#if !defined(AFX_DLGDELAYPREVIEWCFG_H__41C7D3D0_FAF8_471D_A5A3_EDFE14A25763__INCLUDED_)
#define AFX_DLGDELAYPREVIEWCFG_H__41C7D3D0_FAF8_471D_A5A3_EDFE14A25763__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDelayPreviewCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDelayPreviewCfg dialog

class CDlgDelayPreviewCfg : public CDialog
{
// Construction
public:
	CDlgDelayPreviewCfg(CWnd* pParent = NULL);   // standard constructor

	LONG m_lUserID;
	int m_iDeviceIndex;
	LONG m_lChannel;
	void OnBtnGet();

// Dialog Data
	//{{AFX_DATA(CDlgDelayPreviewCfg)
	enum { IDD = IDD_DLG_DELAY_PREVIEW_CFG };
	UINT	m_iDelayTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDelayPreviewCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDelayPreviewCfg)
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDELAYPREVIEWCFG_H__41C7D3D0_FAF8_471D_A5A3_EDFE14A25763__INCLUDED_)
