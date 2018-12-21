#if !defined(AFX_DLGPREVIEWWIN_H__11392699_00AC_4D10_993E_A2666C1721A9__INCLUDED_)
#define AFX_DLGPREVIEWWIN_H__11392699_00AC_4D10_993E_A2666C1721A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreviewWin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreviewWin dialog

class CDlgPreviewWin : public CDialog
{
// Construction
public:
	CDlgPreviewWin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPreviewWin)
	enum { IDD = IDD_DLG_PREVIEW_WIN };
	CComboBox	m_comboStreamType;
	CComboBox	m_comboProtocol;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreviewWin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreviewWin)
	afx_msg void OnBtnExit();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnStart();
	afx_msg void OnBtnStop();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	int m_iDeviceIndex;
	NET_DVR_STREAM_INFO m_struStreamInfo;
	NET_DVR_PREVIEWINFO m_struPara;
	LONG m_lPreviewHandle;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREVIEWWIN_H__11392699_00AC_4D10_993E_A2666C1721A9__INCLUDED_)
