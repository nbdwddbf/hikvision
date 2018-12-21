#if !defined(AFX_DLGVCASCENETPSRULECFG_H__DE509701_A9B4_48F2_B89F_6ACA198FA4A2__INCLUDED_)
#define AFX_DLGVCASCENETPSRULECFG_H__DE509701_A9B4_48F2_B89F_6ACA198FA4A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaSceneTpsRuleCfg.h : header file
//
#include "VcaCommonOperations.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneTpsRuleCfg dialog

class CDlgVcaSceneTpsRuleCfg : public CDialog,public CVcaCommonOperations
{
// Construction
public:
	CDlgVcaSceneTpsRuleCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaSceneTpsRuleCfg)
	enum { IDD = IDD_DLG_VCA_SCENE_TPS_RULECFG };
	enum
	{
		DRAW_TYPE_NONE      = 0,          //不画图
		DRAW_TYPE_RULE      = 1,          //画规则框
		DRAW_TYPE_MINRECT   = 2,          //画最小尺寸过滤框
		DRAW_TYPE_MAXRECT   = 3           //画最大尺寸过滤框
	};
	CCheckListBox	m_listAlarmOutputChan;
	CCheckListBox	m_listTPSType;
	CComboBox	m_comboSizeFilterMode;
	CComboBox	m_comboScene;
	CComboBox	m_comboRule;
	CComboBox	m_comboLane;
	BOOL	m_bRuleActive;
	BOOL	m_bHandleType_EmailJpg;
	BOOL	m_bHandleType_Monitor;
	BOOL	m_bHandleType_Output;
	BOOL	m_bHandleType_Sound;
	BOOL	m_bHandleType_Upload;
	BOOL	m_bSizeFilterEnable;
	int		m_nMaxRectHeight;
	int		m_nMaxRectWidth;
	int		m_nMinRectHeight;
	int		m_nMinRectWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaSceneTpsRuleCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaSceneTpsRuleCfg)
	afx_msg void OnBtnDrawMaxrect();
	afx_msg void OnBtnDrawMinrect();
	afx_msg void OnBtnDrawRule();
	afx_msg void OnBtnStopdraw();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnSetAlarmtime();
	afx_msg void OnCheckSizefilterEnable();
	afx_msg void OnSelchangeComboLane();
	afx_msg void OnSelchangeComboRuleindex();
	afx_msg void OnSelchangeComboScene();
	afx_msg void OnSelchangeComboSizefilterMode();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void DrawTpsRuleFun(HDC hdc);
protected:
	void InitCtrlState();
	void LoadWndSceneContent(int nSceneIndex);
	void SaveWndSceneContent(int nSceneIndex);
	void LoadWndRuleContent(int nSceneIndex,int nRuleIndex);
	void SaveWndRuleContent(int nSceneIndex,int nRuleIndex);
	
protected:
	BOOL GetVcaChanAbility();
	BOOL SetTPSRuleCfg();
    BOOL GetTPSRuleCfg();
	BOOL GetLaneCfg();
	BOOL GetSceneCond(NET_DVR_SCENE_COND& struSceneCond);
	void EnableSetParams(BOOL bEnable);
	
private:
	NET_DVR_ITS_ABILITY     m_struItsAbility;
	NET_DVR_TPS_RULECFG_V41 m_struTPSRuleCfg[MAX_ITS_SCENE_NUM];
	NET_VCA_POLYGON         m_struCurRulePolygon;
	NET_VCA_RECT            m_struMinRect[MAX_ITS_SCENE_NUM][MAX_TPS_RULE];
	NET_VCA_RECT            m_struMaxRect[MAX_ITS_SCENE_NUM][MAX_TPS_RULE];
	NET_DVR_LANE_CFG        m_struSceneLaneCfg[MAX_ITS_SCENE_NUM];
	int                     m_nCurSceneIndex;
	int                     m_nCurRuleIndex;
	int                     m_nCurDrawType;
	CRect                   m_rcPlayWnd;
	BOOL                    m_bFirstDrawMaxRect;
	BOOL                    m_bFirstDrawMinRect;
	int                     m_nSizeFilterMode;
	int                     m_nCurLaneIndex;
	int                     m_nDrawPointNum;
	NET_DVR_SCENE_CFG       m_struSceneCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCASCENETPSRULECFG_H__DE509701_A9B4_48F2_B89F_6ACA198FA4A2__INCLUDED_)
