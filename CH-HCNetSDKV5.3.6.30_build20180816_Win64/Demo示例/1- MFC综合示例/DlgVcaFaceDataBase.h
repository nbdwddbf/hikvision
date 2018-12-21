#if !defined(AFX_DLGVCAFACEDATABASE_H__A039ADF5_1A8A_4081_B5C8_48A215D5E759__INCLUDED_)
#define AFX_DLGVCAFACEDATABASE_H__A039ADF5_1A8A_4081_B5C8_48A215D5E759__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaFaceDataBase.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFaceDataBase dialog
#define INQUIRE_FACE_DATABASE  0
#define SEARCH_FACE_DATABASE   1

class CDlgVcaFaceDataBase : public CDialog
{
// Construction
public:
	CDlgVcaFaceDataBase(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaFaceDataBase)
	enum { IDD = IDD_DLG_VCA_FACE_DATABASE };
	CComboBox	m_comboAdvanceDBType;
	CListCtrl	m_listDataBase;
	CComboBox	m_comboCerfiticateType;
	CComboBox	m_comboNativePlace;
	CComboBox	m_comboSex;
	CString	m_csBirthDate;
	CString	m_csName;
	CString	m_csCertificateNumber;
	DWORD	m_dwRecordID;
	CString	m_csRemark;
	CString	m_csFastRegPicPath;
	int		m_iDataBaseID;
	DWORD	m_dwFacePicID;
	DWORD	m_dwSearchNum;
	DWORD	m_dwThreld;
	CString	m_csUserInfo1;
	CString	m_csEndBirthDate;
	CString	m_csStartBirthDate;
	DWORD	m_dwTotalRecordNum;
	DWORD	m_dwAdvanceDBId;
	DWORD	m_dwAdvancePicId;
	BOOL	m_bChkAdvanceEn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaFaceDataBase)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaFaceDataBase)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBtnFastScan();
	afx_msg void OnBtnFastRegister();
	afx_msg void OnBtnRegister();
	afx_msg void OnBtnDeleteSingle();
	afx_msg void OnBtnDeleteBatch();
	afx_msg void OnBtnSearch();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnDestroy();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnGetFacePic();
	afx_msg void OnBtnStopInquire();
	afx_msg void OnBtnStartSearch();
	afx_msg void OnBtnStopSearch();
	afx_msg void OnBtnUpdateRecord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;
	LONG    m_lHandle;
	LONG    m_lSearchHandle;
//	LONG    m_lDataBaseID;
	char    m_chFilename[256]; 
	DWORD   m_dwFileSize;
	BOOL    m_bInquiring;
	BOOL    m_bSearching;
	LONG    m_lRecordNum;
	LONG    m_lTotalNum;

	NET_VCA_DATARECORD_INFO m_struDataRecordInfo;
	NET_VCA_FAST_DATARECORD_INFO m_struFastDataRecord;
	NET_VCA_DELETE_RECORD_COND m_struDeleteRecord;
	NET_VCA_DATARECORD_COND m_struInquireCond;
	NET_VCA_SEARCH_FACEDB_COND m_struSearchCond;
	void GetDataRecordInfoFromWnd(NET_VCA_HUMAN_ATTRIBUTE& struDataRecordInfo);
	void GetHumanAttrCondFromWnd(NET_VCA_HUMANATTRIBUTE_COND& struCond);
	LRESULT OnWMProcFaceCallback(WPARAM wParam, LPARAM lParam);
	void ProcInquireFaceCallback(WPARAM wParam, LPARAM lParam);
	void ProcSearchFaceCallback(WPARAM wParam, LPARAM lParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAFACEDATABASE_H__A039ADF5_1A8A_4081_B5C8_48A215D5E759__INCLUDED_)
