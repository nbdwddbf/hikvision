#include "afxwin.h"
#if !defined(AFX_DLGINTERACTIVEFILEINFOCFG_H__9BDA9787_5822_4915_A64C_0B016CC14A38__INCLUDED_)
#define AFX_DLGINTERACTIVEFILEINFOCFG_H__9BDA9787_5822_4915_A64C_0B016CC14A38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInteractiveFileInfoCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInteractiveFileInfoCfg dialog

class CDlgInteractiveFileInfoCfg : public CDialog
{
// Construction
public:
	CDlgInteractiveFileInfoCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInteractiveFileInfoCfg)
	enum { IDD = IDD_DLG_INTERACTIVE_FILEINFO };
	CComboBox	m_comVideoFormat;
	CComboBox	m_comPicFormat;
	CListCtrl	m_listFileInfoCfg;
	CString	m_csFileName;
	int		m_nFileType;
	DWORD	m_dwFileIndex;
	long	m_dwFileSize;
	DWORD	m_dwPPTPage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInteractiveFileInfoCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInteractiveFileInfoCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnRadPic();
	afx_msg void OnRadVideo();
	afx_msg void OnBtnGetFileinfo();
	afx_msg void OnClickListFileinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadioAll();
	afx_msg void OnBtnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG	m_lServerID;
	int     m_iDevIndex;
	LONG    m_lChannel;
	NET_DVR_SCREEN_FILE_INFO m_struScreenFileInfo;
	int     m_nCurSelFile;
    CComboBox m_cmbDocFormat;
    CString m_sOtherFileFormat;
    afx_msg void OnBnClickedRadDoc();
    afx_msg void OnBnClickedRadOther();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINTERACTIVEFILEINFOCFG_H__9BDA9787_5822_4915_A64C_0B016CC14A38__INCLUDED_)
