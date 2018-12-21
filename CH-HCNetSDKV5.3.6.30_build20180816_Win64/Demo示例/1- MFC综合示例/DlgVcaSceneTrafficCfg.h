#if !defined(AFX_DLGVCASCENETRAFFICCFG_H__CEDA4D35_4D6B_49D0_9180_70444BEE69DE__INCLUDED_)
#define AFX_DLGVCASCENETRAFFICCFG_H__CEDA4D35_4D6B_49D0_9180_70444BEE69DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaSceneTrafficCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneTrafficCfg dialog

class CDlgVcaSceneTrafficCfg : public CDialog
{
// Construction
public:
	CDlgVcaSceneTrafficCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaSceneTrafficCfg)
	enum { IDD = IDD_DLG_VCA_SCENE_TRAFFIC_CFG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaSceneTrafficCfg)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaSceneTrafficCfg)
	afx_msg void OnBtnSceneCfg();
	afx_msg void OnBtnSceneTimeCfg();
	afx_msg void OnBtnMaskRegion();
	afx_msg void OnBtnReferenceRegion();
	afx_msg void OnBtnLanecfg();
    afx_msg	void OnBtnItsCalibrate();
	afx_msg void OnBtnAidRulecfg();
	afx_msg void OnBtnTpsRulecfg();
	afx_msg void OnBtnForensicsMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    int     m_iDevIndex;
    LONG    m_lServerID;
    int     m_iStartChannel;
    int     m_iChannelnumber;
    int     m_iVcaChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCASCENETRAFFICCFG_H__CEDA4D35_4D6B_49D0_9180_70444BEE69DE__INCLUDED_)
