#if !defined(AFX_DLGFISHEYECORRECT_H__89884B39_D957_4DD1_8480_33CACBA3A8E3__INCLUDED_)
#define AFX_DLGFISHEYECORRECT_H__89884B39_D957_4DD1_8480_33CACBA3A8E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DlgFisheyeFECWnd.h"
#include "VcaCommonOperations.h"
// DlgFisheyeCorrect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFisheyeCorrect dialog

class CDlgFisheyeCorrect : public CDialog,public CVcaCommonOperations
{
// Construction
public:
	CDlgFisheyeCorrect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFisheyeCorrect)
	enum { IDD = IDD_DLG_FISHEYE_CORRECT };
	CComboBox	m_comboMountType;
	CComboBox	m_comboCorrectType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFisheyeCorrect)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnCbnSelchangeComboMounttype();
	afx_msg void OnCbnSelchangeComboCorrecttype();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFisheyeCorrect)
	// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
protected:
	void   InitUI();
	BOOL   StartFECPlay();
	void   ArrangeCtrlPos();
protected:
	CDlgFisheyeFECWnd m_dlgFECWnd;
	//NET_DVR_FEC_PARAM m_struFisheyeParam;
	BOOL m_bDragFishEyePTZ;
private:
	DWORD     m_dwCorrectType;
	DWORD     m_dwMountType;
	CRect     m_rcPlayWnd;
	DWORD     m_dwCorrectHandle;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFISHEYECORRECT_H__89884B39_D957_4DD1_8480_33CACBA3A8E3__INCLUDED_)
