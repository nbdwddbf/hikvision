#if !defined(AFX_DLGSCREENLOGOCFG_H__22F13F28_D8B7_4ABB_A06F_8E134DC1E3E3__INCLUDED_)
#define AFX_DLGSCREENLOGOCFG_H__22F13F28_D8B7_4ABB_A06F_8E134DC1E3E3__INCLUDED_

//#include "..\..\INCLUDE\CHINESE\HCNetSDK.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgScreenLogoCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgScreenLogoCfg dialog

class CDlgScreenLogoCfg : public CDialog
{
// Construction
public:
	int m_iDeviceIndex;
	NET_DVR_PICTURECFG m_struPicCfg;
	CFile m_logoFile;
	CDlgScreenLogoCfg(CWnd* pParent = NULL);   // standard constructor
	~CDlgScreenLogoCfg();
	LONG m_lUploadHandle;
	void InitComboBox();

// Dialog Data
	//{{AFX_DATA(CDlgScreenLogoCfg)
	enum { IDD = IDD_DLG_SCREEN_LOGCFG };
	CProgressCtrl	m_progress;
	CComboBox	m_cmUseType;
	CComboBox	m_cmLogoStatus;
	CString	m_csFilePath;
	BYTE	m_byLogoSequence;
	BYTE	m_byMapNum;
	BYTE	m_byScreenIndex;
	short	m_wSourWidth;
	short	m_wSourHeight;
	CString	m_csProgress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgScreenLogoCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgScreenLogoCfg)
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSCREENLOGOCFG_H__22F13F28_D8B7_4ABB_A06F_8E134DC1E3E3__INCLUDED_)
