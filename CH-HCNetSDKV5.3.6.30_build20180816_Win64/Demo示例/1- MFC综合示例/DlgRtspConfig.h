#if !defined(AFX_DLGRTSPCONFIG_H__D214FDA2_92A0_496D_9061_0ED2661347D9__INCLUDED_)
#define AFX_DLGRTSPCONFIG_H__D214FDA2_92A0_496D_9061_0ED2661347D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRtspConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRtspConfig dialog

class CDlgRtspConfig : public CDialog
{
// Construction
public:
	CDlgRtspConfig(CWnd* pParent = NULL);   // standard constructor
	NET_DVR_RTSPCFG m_struRtspCfg;
	int m_iDeviceIndex;
// Dialog Data
	//{{AFX_DATA(CDlgRtspConfig)
	enum { IDD = IDD_DLG_RTSP };
	int		m_iPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRtspConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRtspConfig)
	afx_msg void OnBtnSet();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRTSPCONFIG_H__D214FDA2_92A0_496D_9061_0ED2661347D9__INCLUDED_)
