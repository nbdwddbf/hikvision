#if !defined(AFX_DLGVCAAUXAREALIST_H__9144A34C_36C2_4A07_B3ED_A8858EABE2AC__INCLUDED_)
#define AFX_DLGVCAAUXAREALIST_H__9144A34C_36C2_4A07_B3ED_A8858EABE2AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "VcaCommonOperations.h"
// DlgVcaAuxAreaList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaAuxAreaList dialog

class CDlgVcaAuxAreaList : public CDialog,public CVcaCommonOperations
{
// Construction
public:
	CDlgVcaAuxAreaList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaAuxAreaList)
	enum { IDD = IDD_DLG_VCA_AUXAREALIST };
	CComboBox	m_comboAreaIndex;
	CComboBox	m_comboAreaType;
	BOOL	m_bEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaAuxAreaList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaAuxAreaList)
	afx_msg void OnBtnSave();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeComboAreaIndex();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBtnDrawRegion();
	afx_msg void OnBtnStopDraw();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void DrawAreaFun(HDC hdc);
protected:
	void InitCtrlState();
	void LoadWndContent(int nAreaIndex);
	void SaveWndContent(int nAreaIndex);
	BOOL GetAuxAreaList();
	BOOL SetAuxAreaList();
private:
	CRect                m_rcPlayWnd;
	NET_DVR_AUXAREA_LIST m_struAuxAreaList;
	BOOL                 m_bDrawingRegion;
	int                  m_nCurRegionIndex;
	int                  m_nDrawPointNum;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAAUXAREALIST_H__9144A34C_36C2_4A07_B3ED_A8858EABE2AC__INCLUDED_)
