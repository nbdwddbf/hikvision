#include "afxwin.h"
#if !defined(AFX_DLGCONFERENCEPARAM_H__E80A2FC3_760C_45CE_BB32_E0A987F5C628__INCLUDED_)
#define AFX_DLGCONFERENCEPARAM_H__E80A2FC3_760C_45CE_BB32_E0A987F5C628__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgConferenceParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgConferenceParam dialog

class CDlgConferenceParam : public CDialog
{
// Construction
public:
	CDlgConferenceParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgConferenceParam)
	enum { IDD = IDD_DLG_MCU_PARAMTERS };
	CComboBox	m_comboConferenceInput;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgConferenceParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgConferenceParam)
	virtual BOOL OnInitDialog();
	afx_msg void OnButCall();
	afx_msg void OnButConferenceRegion();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnButTerminalConferenceStatus();

	afx_msg void OnBtnAddConference();
	afx_msg void OnBtnSearchConferenceStatus();
	afx_msg void OnBtnGetConferenceStatus();
	afx_msg void OnBtnGetConfDailyDistribution();
	afx_msg void OnBtnGetConfCtrl();
	afx_msg void OnBtnClearConfHistory();
	afx_msg void OnBtnDelConference();
	afx_msg void OnBtnTerminalCtrl();
	afx_msg void OnBtnTermGroupList();
	afx_msg void OnBtnTermGroupCfg();

	afx_msg void OnBtnTermManCfg();

	afx_msg void OnBtnGetAbility();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    int m_iDeviceIndex;
    LONG m_lUserID;
public:
    afx_msg void OnBnClickedBtnGkConfig();
    afx_msg void OnBnClickedBtnGkServer();
    CComboBox m_comboStreamType;
    afx_msg void OnCbnSelchangeComboConferenceInput();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONFERENCEPARAM_H__E80A2FC3_760C_45CE_BB32_E0A987F5C628__INCLUDED_)
