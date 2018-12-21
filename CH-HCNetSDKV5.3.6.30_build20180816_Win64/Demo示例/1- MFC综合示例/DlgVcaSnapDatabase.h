#if !defined(AFX_DLGVCASNAPDATABASE_H__1E691179_EBF5_4673_9EF1_E73A3DF9328C__INCLUDED_)
#define AFX_DLGVCASNAPDATABASE_H__1E691179_EBF5_4673_9EF1_E73A3DF9328C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaSnapDatabase.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSnapDatabase dialog
#define INQUIRE_SNAP_DATABASE  0
#define SEARCH_SNAP_DATABASE   1

class CDlgVcaSnapDatabase : public CDialog
{
// Construction
public:
	CDlgVcaSnapDatabase(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaSnapDatabase)
	enum { IDD = IDD_DLG_VCA_SNAP_DATABASE };
	CComboBox	m_comboAdvanceDBType;
	CListCtrl	m_listDataBase;
	CComboBox	m_comboSex;
	CTime	m_ctStartDate;
	CTime	m_ctStopDate;
	DWORD	m_dwDatabaseID;
	CString	m_csMaxBirthdate;
	CString	m_csMinBirthdate;
	DWORD	m_dwRecordID;
	DWORD	m_dwSearchMaxNum;
	DWORD	m_dwThreshold;
	CTime	m_ctStartTime;
	CTime	m_ctStopTime;
	int		m_iChannel;
	DWORD	m_dwFacePicID;
	DWORD	m_dwTotalRecordNum;
	BOOL	m_bChkAdvanceEn;
	DWORD	m_dwAdvanceDBId;
	DWORD	m_dwAdvanceRecordId;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaSnapDatabase)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaSnapDatabase)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBtnInquireSnapdb();
	afx_msg void OnBtnStopInquireSnapdb();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnDestroy();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnStartSearchSnapdb();
	afx_msg void OnBtnStopSearch();
	afx_msg void OnBtnDeleteSingle();
	afx_msg void OnBtnDeleteBatch();
	afx_msg void OnBtnGetFacePic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;
	LONG    m_lHandle;
	LONG    m_lSearchHandle;
	char    m_chFilename[256]; 
	DWORD   m_dwFileSize;
	BOOL    m_bInquiring;
	BOOL    m_bSearching;
	LONG    m_lRecordNum;
	LONG    m_lTotalNum;
	
	NET_VCA_INQUIRE_SNAPDB_COND m_struInquireCond;
	NET_VCA_SEARCH_SNAPDB_COND m_struSearchCond;
	NET_VCA_INQUIRE_SNAPRECORD_RESULT m_struRecordResult;
	NET_VCA_DELETE_SNAPRECORD_COND m_struDeleteRecord;
	void GetDataRecordInfoFromWnd(NET_VCA_HUMAN_ATTRIBUTE& struDataRecordInfo);
	LRESULT OnWMProcFaceCallback(WPARAM wParam, LPARAM lParam);
	void ProcInquireSnapCallback(WPARAM wParam, LPARAM lParam);
	void ProcSearchSnapCallback(WPARAM wParam, LPARAM lParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCASNAPDATABASE_H__1E691179_EBF5_4673_9EF1_E73A3DF9328C__INCLUDED_)
