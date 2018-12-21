#if !defined(AFX_DLGVCASCENELANECFG_H__46ED8C63_E1B8_4BB1_86A4_B199533F126F__INCLUDED_)
#define AFX_DLGVCASCENELANECFG_H__46ED8C63_E1B8_4BB1_86A4_B199533F126F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaSceneLaneCfg.h : header file
//
#include "VcaCommonOperations.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneLaneCfg dialog

class CDlgVcaSceneLaneCfg : public CDialog,public CVcaCommonOperations
{
	// Construction
public:
	CDlgVcaSceneLaneCfg(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CDlgVcaSceneLaneCfg)
	enum { IDD = IDD_DLG_VCA_SCENE_LANECFG };
	enum {
		    DRAW_TYPE_NONE = 0,
			DRAW_TYPE_LANE = 1,
			DRAW_TYPE_DIR  = 2
	};
	CComboBox	m_comboScene;
	CComboBox	m_comboLane;
	CString	m_strLaneName;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaSceneLaneCfg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CDlgVcaSceneLaneCfg)
	afx_msg void OnSelchangeComboLane();
	afx_msg void OnSelchangeComboScene();
	afx_msg void OnBtnDrawdirection();
	afx_msg void OnBtnDrawlane();
	afx_msg void OnBtnSave();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void InitCtrlState();
public:
	void DrawSceneLaneFun(HDC hdc);
protected:
	BOOL GetLaneCfg();
    BOOL SetLaneCfg();
	BOOL GetSceneCond(NET_DVR_SCENE_COND& struSceneCond);
	void LoadSceneWndContent(int nSceneIndex);
	void SaveSceneWndContent(int nSceneIndex);
	void LoadLaneWndContent(int nLaneIndex);
	void SaveLaneWndContent(int nLaneIndex);
private:
	CRect             m_rcPlayWnd;
	int               m_nCurSceneIndex;
	int               m_nCurLaneIndex;
	NET_DVR_LANE_CFG  m_struSceneLaneCfg[MAX_ITS_SCENE_NUM];
	NET_DVR_ONE_LANE  m_struDrawingLane[MAX_LANE_NUM];
	int               m_nCurDrawType;
	BOOL              m_bCheckLaneEnable;
	BOOL              m_bFirstDrawDirection;
	int               m_nDrawPointNum;
	NET_DVR_SCENE_CFG m_struSceneCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCASCENELANECFG_H__46ED8C63_E1B8_4BB1_86A4_B199533F126F__INCLUDED_)
