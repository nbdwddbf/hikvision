#if !defined(AFX_DLGINQUESTFILE_H__18106AA3_E9E7_4FA8_8C8E_941DC6F8945A__INCLUDED_)
#define AFX_DLGINQUESTFILE_H__18106AA3_E9E7_4FA8_8C8E_941DC6F8945A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInquestFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInquestFile dialog

class CDlgInquestFile : public CDialog
{
// Construction
public:
	CDlgInquestFile(CWnd* pParent = NULL);   // standard constructor

	DWORD    m_dwDeviceIndex;
	LONG     m_lLoginID;
	char     m_FileDir[MAX_PATH];
	int		 m_iFileNum;
	LONG     m_lUploadHandle;
	NET_DVR_INQUEST_ROOM m_strInquestRoom;//Inquest room command

// Dialog Data
	//{{AFX_DATA(CDlgInquestFile)
	enum { IDD = IDD_DLG_INQUEST_FILE };
	CListCtrl	m_listFile;
	CString	m_csUploadState;
	CString	m_csFilePath;
	CString	m_csInquestRoom;
	BOOL	m_bChkCourtFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInquestFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInquestFile)
	afx_msg void OnButtonScan();

#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif

	afx_msg void OnButtonExit();
	afx_msg void OnButtonUpload();
	afx_msg void OnButtonSearch();
	afx_msg void OnButtonDelete();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINQUESTFILE_H__18106AA3_E9E7_4FA8_8C8E_941DC6F8945A__INCLUDED_)
