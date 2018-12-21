#if !defined(AFX_DLGSCREENLOGOCFG_H__22F13F28_D8B7_4ABB_A06F_8E134DC1E3E3__INCLUDED_)
#define AFX_DLGSCREENLOGOCFG_H__22F13F28_D8B7_4ABB_A06F_8E134DC1E3E3__INCLUDED_

#include "HCNetSDK.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgScreenLogoCfg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgScreenLogoCfgUniform dialog

class CDlgScreenLogoCfgUniform : public CDialog
{
// Construction
public:
	int m_iDeviceIndex;
	NET_DVR_PICTURECFG m_struPicCfg;
	CFile m_logoFile;
	CDlgScreenLogoCfgUniform(CWnd* pParent = NULL);   // standard constructor
	~CDlgScreenLogoCfgUniform();
	LONG m_lUploadHandle;
	void InitComboBox();
	NET_DVR_PICTURE_PARAM m_struPictureParam;

// Dialog Data
	//{{AFX_DATA(CDlgScreenLogoCfgUniform)
	enum { IDD = IDD_DLG_SCREEN_LOGCFG_UNIFORM };
	CProgressCtrl	m_progress;
	CComboBox	m_cmUseType;
	CComboBox	m_cmLogoStatus;
	CString	m_csFilePath;
	BYTE	m_byMapNum;
	BYTE	m_byScreenIndex;
	short	m_wSourWidth;
	short	m_wSourHeight;
	CString	m_csProgress;
	DWORD	m_dwWallNoCtrl;
	DWORD	m_dwWallNoUpload;
	CString	m_csPictureName;
	BOOL	m_BPictureExist;
	DWORD	m_dwLogSeq;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgScreenLogoCfgUniform)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgScreenLogoCfgUniform)
	afx_msg void OnBtnBrowsefile();
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnCtrl();
	virtual void OnCancel();
#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnBtnStop();
	afx_msg void OnButDeletePicture();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSCREENLOGOCFG_H__22F13F28_D8B7_4ABB_A06F_8E134DC1E3E3__INCLUDED_)
