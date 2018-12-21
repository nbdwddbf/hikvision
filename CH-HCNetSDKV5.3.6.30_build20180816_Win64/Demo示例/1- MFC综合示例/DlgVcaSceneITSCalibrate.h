#if !defined(AFX_DLGVCASCENEITSCALIBRATE_H__AC72566C_BDA8_43DF_A886_33DF714B5CA5__INCLUDED_)
#define AFX_DLGVCASCENEITSCALIBRATE_H__AC72566C_BDA8_43DF_A886_33DF714B5CA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaSceneITSCalibrate.h : header file
//
#include "VcaCommonOperations.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneITSCalibrate dialog

class CDlgVcaSceneITSCalibrate : public CDialog,public CVcaCommonOperations
{
	// Construction
public:
	CDlgVcaSceneITSCalibrate(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CDlgVcaSceneITSCalibrate)
	enum { IDD = IDD_DLG_VCA_SCENE_ITS_CALIBRATE };
	CComboBox	m_comboScene;
	BOOL	m_bEnable;
	float	m_fLength;
	float	m_fWidth;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaSceneITSCalibrate)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CDlgVcaSceneITSCalibrate)
	afx_msg void OnBtnSave();
	afx_msg void OnSelchangeComboScene();
	afx_msg void OnDestroy();
	afx_msg void OnBtnDrawRgn();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
protected:
	void InitCtrlState();
public:
	void DrawRegionFun(HDC hdc);
protected:
	BOOL SetCalibrateCfg();
    BOOL GetCalibrateCfg();
	void LoadSceneWndContent(int nSceneIndex);
	void SaveSceneWndContent(int nSceneIndex);
	BOOL GetSceneCond(NET_DVR_SCENE_COND& struSceneCond);
private:
	CRect m_rcPlayWnd;
	int   m_nCurSceneIndex;
	NET_DVR_CALIBRATION_CFG m_struSceneCaliCfg[MAX_ITS_SCENE_NUM];
	BOOL  m_bDrawingCaliRgn;
	int   m_nDrawPointNum;
	NET_DVR_SCENE_CFG m_struSceneCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCASCENEITSCALIBRATE_H__AC72566C_BDA8_43DF_A886_33DF714B5CA5__INCLUDED_)
