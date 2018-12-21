#if !defined(AFX_DLGVCASCENEAIDRULECFG_H__DF8B6EE6_8232_4F85_B704_659D0F59C8AB__INCLUDED_)
#define AFX_DLGVCASCENEAIDRULECFG_H__DF8B6EE6_8232_4F85_B704_659D0F59C8AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "VcaCommonOperations.h"
// DlgVcaSceneAidRuleCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneAidRuleCfg dialog

class CDlgVcaSceneAidRuleCfg : public CDialog,public CVcaCommonOperations
{
// Construction
public:
	CDlgVcaSceneAidRuleCfg(CWnd* pParent = NULL);   // standard constructor
	enum
	{
		DRAW_TYPE_NONE      = 0,          //不画图
		DRAW_TYPE_RULE      = 1,          //画规则框
		DRAW_TYPE_MINRECT   = 2,          //画最小尺寸过滤框
		DRAW_TYPE_MAXRECT   = 3           //画最大尺寸过滤框
	};
// Dialog Data
	//{{AFX_DATA(CDlgVcaSceneAidRuleCfg)
	enum { IDD = IDD_DLG_VCA_SCENE_AID_RULECFG };
	CComboBox	m_comboPicResolution;
	CComboBox	m_comboPicQuality;
	CComboBox	m_comboProPicType;
	CComboBox	m_comboSizeFilterMode;
    CCheckListBox	m_listRecordChan;
	CCheckListBox	m_listAlarmOutputChan;
	CCheckListBox	m_listAIDType;
	CComboBox	m_comboRuleIndex;
	CComboBox	m_comboScene;
	BOOL	m_bRuleActive;
	CString	m_strRuleName;
	BOOL	m_bHandleType_EmailJpg;
	BOOL	m_bHandleType_Monitor;
	BOOL	m_bHandleType_Sound;
	BOOL	m_bHandleType_Output;
	BOOL	m_bHandleType_Upload;
	int		m_nPedestrian;
	int		m_nParking;
	int		m_nMinRectWidth;
	int 	m_nMinRectHeight;
	int		m_nMaxRectWidth;
	int		m_nMaxRectHeight;
	int		m_nInverseDuration;
	int		m_nInverseDistance;
	int		m_nInverseAngle;
	int		m_nDebris;
	int		m_nCongestionDuration;
	int		m_nCongestionLength;
	BOOL	m_bSizeFilterEnable;
	int		m_nIllegalParkingTime;
	int		m_nIllegalParkingPicNum;
	BOOL	m_bMergePic;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaSceneAidRuleCfg)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaSceneAidRuleCfg)
	afx_msg void OnSelchangeComboScene();
	afx_msg void OnSelchangeComboSizefilterMode();
	afx_msg void OnSelchangeComboRuleindex();
	afx_msg void OnBtnDrawMaxrect();
	afx_msg void OnBtnDrawMinrect();
	afx_msg void OnBtnDrawRule();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnSetAlarmtime();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBtnStopdraw();
	afx_msg void OnCheckSizefilterEnable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void DrawAidRuleFun(HDC hdc);
protected:
	void InitCtrlState();
	void LoadWndSceneContent(int nSceneIndex);
	void SaveWndSceneContent(int nSceneIndex);
	void LoadWndRuleContent(int nSceneIndex,int nRuleIndex);
	void SaveWndRuleContent(int nSceneIndex,int nRuleIndex);

protected:
	BOOL GetVcaChanAbility();
	BOOL SetAIDRuleCfg();
    BOOL GetAIDRuleCfg();
	BOOL GetLaneCfg();
	BOOL GetSceneCond(NET_DVR_SCENE_COND& struSceneCond);
	void EnableSetParams(BOOL bEnable);

private:
	NET_DVR_ITS_ABILITY     m_struItsAbility;
	NET_DVR_AID_RULECFG_V41 m_struAIDRuleCfg[MAX_ITS_SCENE_NUM];
	NET_VCA_POLYGON         m_struCurRulePolygon;
	NET_VCA_RECT            m_struMinRect[MAX_ITS_SCENE_NUM][MAX_AID_RULE];
	NET_VCA_RECT            m_struMaxRect[MAX_ITS_SCENE_NUM][MAX_AID_RULE];
	NET_DVR_LANE_CFG        m_struSceneLaneCfg[MAX_ITS_SCENE_NUM];
	int                     m_nCurSceneIndex;
	int                     m_nCurRuleIndex;
	int                     m_nCurDrawType;
	CRect                   m_rcPlayWnd;
	BOOL                    m_bFirstDrawMaxRect;
	BOOL                    m_bFirstDrawMinRect;
	int                     m_nSizeFilterMode;
	int                     m_nDrawPointNum;
	NET_DVR_SCENE_CFG       m_struSceneCfg;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCASCENEAIDRULECFG_H__DF8B6EE6_8232_4F85_B704_659D0F59C8AB__INCLUDED_)
