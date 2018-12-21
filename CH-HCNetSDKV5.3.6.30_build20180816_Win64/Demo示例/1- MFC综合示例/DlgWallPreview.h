#if !defined(AFX_DLGWALLPREVIEW_H__36A89DA0_7DE1_491C_9CF9_FE059404EA01__INCLUDED_)
#define AFX_DLGWALLPREVIEW_H__36A89DA0_7DE1_491C_9CF9_FE059404EA01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWallPreview.h : header file
//
#include "Picture.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgWallPreview dialog

class CDlgWallPreview : public CDialog
{
// Construction
public:
	CDlgWallPreview(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWallPreview)
	enum { IDD = IDD_DLG_VIDEOWALL_WINPREVIEW };
	CStatic	m_StaPreview;
	CComboBox	m_CmResolution;
	DWORD	m_dwChannel;
	CString	m_csDeviceID;
	DWORD	m_dwFrame;
	DWORD	m_dwLayerNo;
	DWORD	m_dwScreenNo;
	DWORD	m_dwSignalIndex;
	DWORD	m_dwWallNo;
	DWORD	m_dwSubWin;
	DWORD	m_dwWinNo;
	int		m_iSourceType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWallPreview)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWallPreview)
	afx_msg void OnButWpictureStop();
	afx_msg void OnButWpictureStart();
	afx_msg void OnRadSourcetype();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG  m_lUserID;
	LONG  m_iDeviceIndex;
    CPicture_Ex m_Picture;
    LONG  m_lHandle; 

    void DrawPicture(BYTE* pBuffer, int nSize);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWALLPREVIEW_H__36A89DA0_7DE1_491C_9CF9_FE059404EA01__INCLUDED_)
