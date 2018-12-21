#if !defined(AFX_DLGINFODIFFUSIONSERVER_H__BCA378E3_A5A9_499C_93C6_0774E2D1DF76__INCLUDED_)
#define AFX_DLGINFODIFFUSIONSERVER_H__BCA378E3_A5A9_499C_93C6_0774E2D1DF76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionServer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionServer dialog

class CDlgInfoDiffusionServer : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionServer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionServer)
	enum { IDD = IDD_DLG_INFO_DIFFUSION_SERVER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionServer)
	afx_msg void OnBtnExit();
	afx_msg void OnBtnXmlCfg();
	afx_msg void OnBtnUpdownload();
	afx_msg void OnBtnMaterialManage();
	afx_msg void OnBtnScheduleManage();
	afx_msg void OnBtnTerminalManage();
	afx_msg void OnBtnCapabilites();
	afx_msg void OnBtnShutdown();
	afx_msg void OnBtnProgramManage();
	afx_msg void OnBtnVolume();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnXmlTest();
    afx_msg void OnBnClickedBtnPic();
    afx_msg void OnBnClickedBtnCall();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONSERVER_H__BCA378E3_A5A9_499C_93C6_0774E2D1DF76__INCLUDED_)
