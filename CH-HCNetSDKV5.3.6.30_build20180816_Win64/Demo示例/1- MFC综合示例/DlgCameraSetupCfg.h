#if !defined(AFX_DLGCAMERASETUPCFG_H__37A800A6_9520_41C1_8A02_E8CDF8149521__INCLUDED_)
#define AFX_DLGCAMERASETUPCFG_H__37A800A6_9520_41C1_8A02_E8CDF8149521__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCameraSetupCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCameraSetupCfg dialog

class CDlgCameraSetupCfg : public CDialog
{
// Construction
public:
	CDlgCameraSetupCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCameraSetupCfg)
	enum { IDD = IDD_DLG_CAMERA_SETUP_CFG };
	CComboBox	m_comHeightUnit;
	CComboBox	m_comCameraAngle;
	BYTE	m_byDetailLens;
	DWORD	m_dwHorizontalDistance;
	DWORD	m_dwSetupHeight;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCameraSetupCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCameraSetupCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG	m_lLoginID;
	LONG	m_lChannel;
	LONG	m_iDeviceIndex;
    CComboBox m_ErectMethod;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCAMERASETUPCFG_H__37A800A6_9520_41C1_8A02_E8CDF8149521__INCLUDED_)
