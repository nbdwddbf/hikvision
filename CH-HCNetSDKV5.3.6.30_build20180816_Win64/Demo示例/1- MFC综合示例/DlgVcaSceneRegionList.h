#if !defined(AFX_DLGVCASCENEREGIONLIST_H__912286E4_17FE_496C_AF71_60431625182B__INCLUDED_)
#define AFX_DLGVCASCENEREGIONLIST_H__912286E4_17FE_496C_AF71_60431625182B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaSceneRegionList.h : header file
//
#include "VcaCommonOperations.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneRegionList dialog

class CDlgVcaSceneRegionList : public CDialog,public CVcaCommonOperations
{
	// Construction
public:
	CDlgVcaSceneRegionList(int nRegionListType,CWnd* pParent = NULL);   // standard constructor
    
	// Dialog Data
	//{{AFX_DATA(CDlgVcaSceneRegionList)
	enum { IDD = IDD_DLG_VCA_SCENE_REGIONLIST };
	enum { 
		REGIONLIST_TYPE_NONE      = 0,
			REGIONLIST_TYPE_MASK      = 1,
			REGIONLIST_TYPE_REFERENCE = 2
	};
	CComboBox	m_comboScene;
	CComboBox	m_comboRegionIndex;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaSceneRegionList)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CDlgVcaSceneRegionList)
	afx_msg void OnBtnSave();
	afx_msg void OnBtnDrawRegion();
	afx_msg void OnBtnStopDraw();
	afx_msg void OnSelchangeComboScene();
	afx_msg void OnSelchangeComboRegionindex();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void InitCtrlState();
    BOOL SetMaskRegion();
    BOOL GetMaskRegion();
    BOOL SetReferenceRegion();
    BOOL GetReferenceRegion();
	BOOL GetSceneCond(NET_DVR_SCENE_COND& struSceneCond);
public:
	void DrawRegionFun(HDC hdc);
protected:
	void LoadSceneRgnWndContent(int nSceneIndex);
	void SaveSceneRgnWndContent(int nSceneIndex);
private:
	int                 m_nRegionListType;
	CRect               m_rcPlayWnd;
	NET_DVR_REGION_LIST m_struSceneRegionList[MAX_ITS_SCENE_NUM];
	BOOL                m_bDrawingRegion;
	int                 m_nCurRegionIndex;
	int                 m_nCurSceneIndex;
	NET_DVR_REGION_LIST m_struDrawingRgnList;
	NET_DVR_SCENE_CFG   m_struSceneCfg;
	int                 m_nDrawPointNum;
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCASCENEREGIONLIST_H__912286E4_17FE_496C_AF71_60431625182B__INCLUDED_)
