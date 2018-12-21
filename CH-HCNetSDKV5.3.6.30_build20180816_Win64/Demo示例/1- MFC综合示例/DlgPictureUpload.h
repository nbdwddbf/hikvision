#if !defined(AFX_DLGPICTUREUPLOAD_H__710DA2CA_3633_40FF_A3D0_02DBDEBA1314__INCLUDED_)
#define AFX_DLGPICTUREUPLOAD_H__710DA2CA_3633_40FF_A3D0_02DBDEBA1314__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPictureUpload.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPictureUpload dialog

class CDlgPictureUpload : public CDialog
{
// Construction
public:
	CDlgPictureUpload(CWnd* pParent = NULL);   // standard constructor
    ~CDlgPictureUpload();
// Dialog Data
	//{{AFX_DATA(CDlgPictureUpload)
	enum { IDD = IDD_DLG_PICTURE_UPLOAD };
	CComboBox	m_comPicType;
	CString	m_csFilePath;
	CString	m_csPicUrl;
	BOOL	m_bPicStruct;
	COleDateTime	m_date;
	COleDateTime	m_time;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPictureUpload)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPictureUpload)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnFilePath();
	afx_msg void OnBtnPicUpload();
	afx_msg void OnCheckPicStruct();
	afx_msg void OnBtnPicDownload();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG m_lServerID;
    LONG m_lChannel;
    LONG m_lDeviceIndex;

    LONG m_lUploadHandle;
    BOOL m_bUpLoading;
	HANDLE	m_hUpLoadThread;
    DWORD m_dwThreadId;

    char* m_pPicInfo;
    NET_DVR_UPLOAD_PICTURE_INFO m_struPicInfo;
    static DWORD WINAPI GetUpLoadFileThread(LPVOID pParam);
  //  void ShowPicUrl(CString strUrl);
    CString m_csIp;
    DWORD m_dwPort;
    afx_msg void OnBnClickedBtnPicDownloadv50();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPICTUREUPLOAD_H__710DA2CA_3633_40FF_A3D0_02DBDEBA1314__INCLUDED_)
