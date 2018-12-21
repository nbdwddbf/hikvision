#if !defined(AFX_DLGVCAFUNCFG_H__EE3C71E2_7E5A_413F_9268_A238901C042D__INCLUDED_)
#define AFX_DLGVCAFUNCFG_H__EE3C71E2_7E5A_413F_9268_A238901C042D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaFunCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFunCfg dialog

class CDlgVcaFunCfg : public CDialog
{
// Construction
public:
	CDlgVcaFunCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaFunCfg)
	enum { IDD = IDD_DLG_VCA_FUN };
	DWORD	m_dwReserveTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaFunCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaFunCfg)
	afx_msg void OnBtnGetTrialCfg();
	afx_msg void OnBtnSynChanName();
	afx_msg void OnBtnDiskCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long  m_lServerID; // 用户ID
    int   m_iDevIndex; // 设备索引
	int   m_iChannelIndex; //通道号
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAFUNCFG_H__EE3C71E2_7E5A_413F_9268_A238901C042D__INCLUDED_)
