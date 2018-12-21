#if !defined(AFX_DLGLCDMATRIXRELATION_H__3470B016_3EFB_4150_A22F_B2152A168A64__INCLUDED_)
#define AFX_DLGLCDMATRIXRELATION_H__3470B016_3EFB_4150_A22F_B2152A168A64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLcdMatrixRelation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdMatrixRelation dialog

class CDlgLcdMatrixRelation : public CDialog
{
// Construction
public:
	CDlgLcdMatrixRelation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLcdMatrixRelation)
	enum { IDD = IDD_DLG_LCD_MATRIX_RELATION };
	CListCtrl	m_listRelation;
	DWORD	m_dwMatrixOutput;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLcdMatrixRelation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLcdMatrixRelation)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnModify();
	afx_msg void OnClickListMatrixRelation(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    NET_DVR_EXTERNAL_MATRIX_CFG *m_lpMatrixInfo;
    int m_iCurSel;
    void DrawList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLCDMATRIXRELATION_H__3470B016_3EFB_4150_A22F_B2152A168A64__INCLUDED_)
