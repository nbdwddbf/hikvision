#if !defined(AFX_DLGVCABEHAVIORCFG_H__4EBD75E1_AFF5_4308_974D_FFC38019252E__INCLUDED_)
#define AFX_DLGVCABEHAVIORCFG_H__4EBD75E1_AFF5_4308_974D_FFC38019252E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaBehaviorCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBehaviorCfg dialog

class CDlgVcaBehaviorCfg : public CDialog
{
// Construction
public:
	CDlgVcaBehaviorCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaBehaviorCfg)
	enum { IDD = IDD_DLG_VCA_BEHAVIORCFG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaBehaviorCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaBehaviorCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnMaskRegion();
	afx_msg void OnBtnEnterRegion2();
	afx_msg void OnBtnLfCfg();
	afx_msg void OnBtnSetRulecfg();
	afx_msg void OnBtnBehaviorCalibrate();
	afx_msg void OnBtnSizeFilter();
	afx_msg void OnBtnFaceDetect();
	afx_msg void OnBtnVcaWorkStatus();
	afx_msg void OnBtnObjectColor();
	afx_msg void OnBtnAuxArea();
	afx_msg void OnBtnChannelWorkMode();
	afx_msg void OnBtnBaselineScene();
	afx_msg void OnBtnVQDEventRule();
	afx_msg void OnBtnGetVQDAlarmPic();
	afx_msg void OnBtnFacesnap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    int     m_iChannelNum;
    int     m_iVcaChannel;
	BYTE    m_byVcaType;
	BYTE    m_byVcaChanMode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCABEHAVIORCFG_H__4EBD75E1_AFF5_4308_974D_FFC38019252E__INCLUDED_)
