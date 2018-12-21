#if !defined(AFX_DLGUPLOADFILE_H__783307DC_B5F8_4377_97A0_3A5EC8C95A45__INCLUDED_)
#define AFX_DLGUPLOADFILE_H__783307DC_B5F8_4377_97A0_3A5EC8C95A45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUploadFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgUploadFile dialog
#define UPLOAD_RECORD_TIMER WM_USER+102
class CDlgUploadFile : public CDialog
{
// Construction
public:
	CDlgUploadFile(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgUploadFile)
	enum { IDD = IDD_DLG_UPLOAD_FILE };
	CComboBox	m_cmdVedioEncType;
	CComboBox	m_cmbAudioEncType;
	CComboBox	m_cmbFormatType;
	CComboBox	m_cmbFileType;
	CString	m_strFileName;
	CString	m_strCameraID;
	CTime	m_tmBeginDate;
	CTime	m_tmBeginTime;
	CTime	m_tmEndDate;
	CTime	m_tmEndTime;
	CString	m_csFileName;
	UINT	m_dwStoragePoolID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUploadFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUploadFile)
	afx_msg void OnButtonBrowseFile();
	afx_msg void OnUpload();
	virtual void OnCancel();
#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

        
public:
    LONG m_lUserID;
    int m_iDevIndex;
    LONG m_lUploadHandle;
    LONG    m_timerHandle;
protected:
    void AA();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUPLOADFILE_H__783307DC_B5F8_4377_97A0_3A5EC8C95A45__INCLUDED_)
