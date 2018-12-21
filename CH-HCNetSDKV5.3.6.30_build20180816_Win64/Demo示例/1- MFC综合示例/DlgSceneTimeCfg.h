#if !defined(AFX_DLGSCENETIMECFG_H__C0D9F478_56E2_4D5A_856C_47CE9FDAF36B__INCLUDED_)
#define AFX_DLGSCENETIMECFG_H__C0D9F478_56E2_4D5A_856C_47CE9FDAF36B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSceneTimeCfg.h : header file
//
#include "VcaCommonOperations.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgSceneTimeCfg dialog

class CDlgSceneTimeCfg : public CDialog,public CVcaCommonOperations
{
	// Construction
public:
	CDlgSceneTimeCfg(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CDlgSceneTimeCfg)
	enum { IDD = IDD_DLG_VCA_SCENETIME_CFG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSceneTimeCfg)
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CDlgSceneTimeCfg)
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	BOOL GetSceneTimeCfg();
	BOOL SaveSceneTimeCfg();
protected:
	void InitCtrlState();
	void InitWndContent();
	void GetWndContent();
	BOOL ValidateParams();
private:
	COleDateTime  m_dtArryTimeBegin[MAX_SCENE_TIMESEG_NUM];
	COleDateTime  m_dtArryTimeEnd[MAX_SCENE_TIMESEG_NUM];
	CDateTimeCtrl m_dtCtrlArryTimeBegin[MAX_SCENE_TIMESEG_NUM];
	CDateTimeCtrl m_dtCtrlArryTimeEnd[MAX_SCENE_TIMESEG_NUM];
	CComboBox     m_comboArryScene[MAX_SCENE_TIMESEG_NUM];
	BOOL          m_bArryActive[MAX_SCENE_TIMESEG_NUM];
	
	NET_DVR_SCENE_TIME_CFG m_struSceneTimeCfg;
	NET_DVR_SCENE_CFG      m_struSceneCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSCENETIMECFG_H__C0D9F478_56E2_4D5A_856C_47CE9FDAF36B__INCLUDED_)
