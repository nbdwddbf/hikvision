#if !defined(AFX_DLGPTZCTRL_H__A4D1C0A1_BB6B_4A7F_AD4A_31B38AAD0DBA__INCLUDED_)
#define AFX_DLGPTZCTRL_H__A4D1C0A1_BB6B_4A7F_AD4A_31B38AAD0DBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPtzCtrl.h : header file
//
#include "PTZButton1.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgPtzCtrl dialog

class CDlgPtzCtrl : public CDialog
{
// Construction
public:
	CDlgPtzCtrl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPtzCtrl)
	enum { IDD = IDD_DLG_PTZ_CTRL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPtzCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPtzCtrl)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    CPTZButton1 m_btnPtzUp;
    CPTZButton1 m_btnPtzDown;
    CPTZButton1 m_btnPtzLeft;
    CPTZButton1 m_btnPtzRight;
    CPTZButton1 m_btnZoomIn;//zoom in
    CPTZButton1 m_btnZoomOut;//zoom out
    CPTZButton1 m_btnFocusNear;//focus near
    CPTZButton1 m_btnFocusFar;//focus far
    CPTZButton1 m_btnIrisOpen;//iris open
	CPTZButton1 m_btnIrisClose;//iris close

	
	CPTZButton1 m_btnPtzUpZoomIn;
	CPTZButton1 m_btnPtzUpZoomOut;
	CPTZButton1 m_btnPtzDownZoomIn;
	CPTZButton1 m_btnPtzDownZoomOut;
	
	CPTZButton1 m_btnPtzLeftZoomIn;
	CPTZButton1 m_btnPtzLeftZoomOut;
	CPTZButton1 m_btnPtzRightZoomIn;
	CPTZButton1 m_btnPtzRightZoomOut;
	
	CPTZButton1 m_btnPtzUpLeftZoomIn;
	CPTZButton1 m_btnPtzUpLeftZoomOut;
	CPTZButton1 m_btnPtzUpRightZoomIn;
	CPTZButton1 m_btnPtzUpRightZoomOut;
	
	CPTZButton1 m_btnPtzDownLeftZoomIn;
	CPTZButton1 m_btnPtzDownLeftZoomOut;
	CPTZButton1 m_btnPtzDownRightZoomIn;
	CPTZButton1 m_btnPtzDownRightZoomOut;

    long        m_lPlayHandle; // Ô¤ÀÀ¾ä±ú
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPTZCTRL_H__A4D1C0A1_BB6B_4A7F_AD4A_31B38AAD0DBA__INCLUDED_)
