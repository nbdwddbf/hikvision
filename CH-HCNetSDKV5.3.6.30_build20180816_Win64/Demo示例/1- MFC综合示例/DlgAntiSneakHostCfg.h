#if !defined(AFX_DLGANTISNEAKHOSTCFG_H__2626D601_36C9_44E3_95D0_CD43B04FD254__INCLUDED_)
#define AFX_DLGANTISNEAKHOSTCFG_H__2626D601_36C9_44E3_95D0_CD43B04FD254__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAntiSneakHostCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgAntiSneakHostCfg dialog

class DlgAntiSneakHostCfg : public CDialog
{
// Construction
public:
	DlgAntiSneakHostCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgAntiSneakHostCfg)
	enum { IDD = IDD_DIG_ANTI_SNEAK_HOST_CFG };
    CComboBox	m_byHostNo;
    BOOL	m_byEnableAnti;
    BOOL	m_byIsStartAddr;
    int     m_byAntiSnealHostNo;
    int     m_wFollowUpCardReader;
    int     m_Port;
    CString	m_sIP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgAntiSneakHostCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    int m_iDeviceIndex;
    long m_lUserID;
	NET_DVR_ANTI_SNEAK_MULTI_HOST_CFG m_struAntiSneakCfg;
	// Generated message map functions
	//{{AFX_MSG(DlgAntiSneakHostCfg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangeStruSneakHost();
    afx_msg void OnBtnSure();
    afx_msg void OnBtnGet();
    afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGANTISNEAKHOSTCFG_H__2626D601_36C9_44E3_95D0_CD43B04FD254__INCLUDED_)
