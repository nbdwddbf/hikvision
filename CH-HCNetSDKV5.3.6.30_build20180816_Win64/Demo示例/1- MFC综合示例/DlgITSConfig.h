#if !defined(AFX_DLGITSCONFIG_H__4CD3ACFA_B3AE_4EC1_9B54_97E3A5F33897__INCLUDED_)
#define AFX_DLGITSCONFIG_H__4CD3ACFA_B3AE_4EC1_9B54_97E3A5F33897__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgITSConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgITSConfig dialog

class CDlgITSConfig : public CDialog
{
// Construction
public:
	CDlgITSConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgITSConfig)
	enum { IDD = IDD_DLG_ITS_DEVICE_CFG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgITSConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgITSConfig)
	afx_msg void OnBtnDataUploadCfg();
	afx_msg void OnBtnGetItsBaseinfo();
	afx_msg void OnBtnItsImgmerge();
	afx_msg void OnBtnReuploadCfg();
	afx_msg void OnBtnItsIpcCfg();
	afx_msg void OnBtnItsOverlapCfg();
	afx_msg void OnBtnRoadInfoGet();
	afx_msg void OnBtnDevice();
	afx_msg void OnBtnGetitcAblity();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
    int     m_iDevIndex;
	LONG    m_lChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGITSCONFIG_H__4CD3ACFA_B3AE_4EC1_9B54_97E3A5F33897__INCLUDED_)
