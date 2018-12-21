#if !defined(AFX_DLGSENCECONTROL_H__D558880A_302E_4098_93FD_7113DBB57256__INCLUDED_)
#define AFX_DLGSENCECONTROL_H__D558880A_302E_4098_93FD_7113DBB57256__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSenceControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSenceControl dialog
#define SCENE_NUM 8
class CDlgSenceControl : public CDialog
{
// Construction
public:
	CDlgSenceControl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSenceControl)
	enum { IDD = IDD_DLG_SCENE_CONTROL };
	CListCtrl	m_listScene;
	CComboBox	m_comboSceneOperate;
	DWORD	m_dwCopyScene;
	CString	m_csSceneName;
	DWORD	m_dwSceneNum;
	DWORD	m_dwSceneNumOperate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSenceControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSenceControl)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnModeGet();
	afx_msg void OnBtnModeSet();
	afx_msg void OnBtnSave();
	afx_msg void OnClickListScene(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSceneGet();
	afx_msg void OnSelchangeComboSceneOperate();
	afx_msg void OnBtnControl();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	int m_iDeviceIndex;
	int m_iCurSel;
	DWORD m_dwSetCount;
    DWORD m_dwSceneNo[SCENE_NUM];
	DWORD m_dwSceneNoSet[SCENE_NUM];
	NET_DVR_WALLSCENECFG m_struSenceName[SCENE_NUM];
	NET_DVR_WALLSCENECFG m_struSenceNameSet[SCENE_NUM];
	DWORD m_dwStatus[SCENE_NUM];

	void DrawList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSENCECONTROL_H__D558880A_302E_4098_93FD_7113DBB57256__INCLUDED_)
