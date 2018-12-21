#if !defined(AFX_DLGWINPREVIEW_H__D5D99097_6324_401A_B6CF_272D595CDCA2__INCLUDED_)
#define AFX_DLGWINPREVIEW_H__D5D99097_6324_401A_B6CF_272D595CDCA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWinPreview.h : header file
//
#include "Picture.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgWinPreview dialog

class CDlgWinPreview : public CDialog
{
// Construction
public:
	CDlgWinPreview(CWnd* pParent = NULL);   // standard constructor
	~CDlgWinPreview();

// Dialog Data
	//{{AFX_DATA(CDlgWinPreview)
	enum { IDD = IDD_DLG_WIN_PREVIEW };
	CComboBox	m_comboResourceType;
	CStatic	m_staticPreview;
	DWORD	m_wChannel;
	CString	m_csPassword;
	DWORD	m_wPort;
	CString	m_csAddress;
	DWORD	m_dwSubWinNo;
	CString	m_csUserName;
	DWORD	m_dwWinNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWinPreview)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWinPreview)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnLogin();
	afx_msg void OnBtnPreStart();
	afx_msg void OnBtnPreStop();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lServerID;
	LONG m_lDecID;
	int m_iDeviceIndex;
	LONG m_lHandle;
	CPicture_Ex *m_picture;
	NET_DVR_WININDEX_INFO m_struWinIndexInfo;
	NET_DVR_ASSOCIATEDDEV_CHAN_INFO m_struDecChanInfo;
	NET_DVR_START_PIC_VIEW_INFO m_struPicPreviewInfo;

	void DrawPicture(BYTE* pBuffer, int nSize);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWINPREVIEW_H__D5D99097_6324_401A_B6CF_272D595CDCA2__INCLUDED_)
