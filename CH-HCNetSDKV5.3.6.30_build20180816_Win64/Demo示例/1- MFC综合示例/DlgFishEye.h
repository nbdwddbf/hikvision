#if !defined(AFX_DLGFISHEYE_H__1B8001A7_4DD2_4CAC_85AD_0F77FAD85182__INCLUDED_)
#define AFX_DLGFISHEYE_H__1B8001A7_4DD2_4CAC_85AD_0F77FAD85182__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Resource.h"
// DlgFishEye.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFishEye dialog

class CDlgFishEye : public CDialog
{
// Construction
public:
	CDlgFishEye(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFishEye)
	enum { IDD = IDD_DLG_FISHEYE };
	CComboBox	m_cmbChannel;
	CComboBox	m_comboRealTimeOutput;
	CListCtrl	m_listPreset;
	CListCtrl	m_listCruisePath;
	CComboBox	m_comboStreamStatus;
	CComboBox	m_comboMountType;
	CComboBox	m_comboCorrectMode;
	BOOL	m_bRealtimeOutput;
	int		m_nCruiseGroupNo;
	int		m_nCruiseGroupNumber;
	int		m_nCruiseNumber;
	int		m_nPresetGroupNo;
	int		m_nPresetGroupNumber;
	int		m_nPresetNumber;
	BOOL	m_byEnableEPTZ;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFishEye)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFishEye)
	afx_msg void OnBtnGetCruiseGroupinfo();
	afx_msg void OnBtnGetCruisePathInfo();
	afx_msg void OnBtnGetPresetGroupinfo();
	afx_msg void OnBtnGetPresetParaminfo();
	afx_msg void OnBtnGetDisplayCfg();
	afx_msg void OnBtnGetStreamStatus();
	afx_msg void OnBtnPtzControl();
	afx_msg void OnBtnSetDisplayCfg();
	afx_msg void OnBtnTracklinkage();
	afx_msg void OnBtnPtzTrackcfg();
	afx_msg void OnBtnFec();
	afx_msg void OnButtonEptzGet();
	afx_msg void OnButtonEptzSet();
	afx_msg void OnButtonCenterPoint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void InitCtrlState();
public:
	LONG m_lServerID;
	LONG m_lChannel;
	int  m_iDevIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFISHEYE_H__1B8001A7_4DD2_4CAC_85AD_0F77FAD85182__INCLUDED_)
