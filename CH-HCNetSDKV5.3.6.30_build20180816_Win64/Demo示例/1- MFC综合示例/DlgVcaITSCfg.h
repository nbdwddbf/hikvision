#if !defined(AFX_DLGVCAITSCFG_H__FBF48ECE_C485_475E_B949_C74BEDEE105B__INCLUDED_)
#define AFX_DLGVCAITSCFG_H__FBF48ECE_C485_475E_B949_C74BEDEE105B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaITSCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaITSCfg dialog

class CDlgVcaITSCfg : public CDialog
{
// Construction
public:
	CDlgVcaITSCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaITSCfg)
	enum { IDD = IDD_DLG_VCA_ITS_CFG };
	CComboBox	m_comboSceneMode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaITSCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaITSCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnMaskRegion();
	afx_msg void OnBtnReferenceRegion();
	afx_msg void OnBtnLanecfg();
	afx_msg void OnBtnAidRulecfg();
	afx_msg void OnBtnTpsRulecfg();
	afx_msg void OnBtnItsCalibrate();
	afx_msg void OnBtnSetSceneMode();
	afx_msg void OnBtnItcTriggerCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    int     m_iDevIndex;
    LONG    m_lServerID;
    int     m_iVcaChannel;
public:
    DWORD m_dwSceneMode;    
    BOOL GetSceneMode();
    BOOL SetSceneMode();
    void InitWnd();
    void SetSceneModeToWnd();
    void GetSceneModeFromWnd();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAITSCFG_H__FBF48ECE_C485_475E_B949_C74BEDEE105B__INCLUDED_)
