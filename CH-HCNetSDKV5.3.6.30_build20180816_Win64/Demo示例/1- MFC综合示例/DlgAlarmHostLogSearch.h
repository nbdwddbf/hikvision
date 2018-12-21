#if !defined(AFX_DLGALARMHOSTLOGSEARCH_H__09841B14_3B4D_43B7_AB27_DFF4542750FA__INCLUDED_)
#define AFX_DLGALARMHOSTLOGSEARCH_H__09841B14_3B4D_43B7_AB27_DFF4542750FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostLogSearch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostLogSearch dialog

class CDlgAlarmHostLogSearch : public CDialog
{
// Construction
public:
	CDlgAlarmHostLogSearch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostLogSearch)
	enum { IDD = IDD_DLG_ALARMHOST_LOG_SEARCH };
	CComboBox	m_comboMode;
	CListCtrl	m_listAlarmHostLog;
	CComboBox	m_comboMinorType;
	CComboBox	m_comboMajorType;
	CTime	m_ctTimeStart;
	CTime	m_ctTimeStop;
	COleDateTime	m_oleDataStart;
	COleDateTime	m_oleDataStop;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostLogSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostLogSearch)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSearch();
	afx_msg void OnBtnExit();
	afx_msg void OnSelchangeComboMajorType();
	afx_msg void OnBtnExportLog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    LONG    m_lSearchHandle;    
    int     m_iDevIndex;

    BOOL    m_bSearch;
    long    m_lLogNum;
    HANDLE m_hFileThread;
    NET_DVR_ALARMHOST_SEARCH_LOG_PARAM m_struSearchParam;

public:
    void InitWnd();
    void InitModeCombo();
    void InitMajorTypeCombo();
    void InitMinorTypeCombo();
    void InitMinorAlarmCombo();
    void InitMinorOperatorCombo();
    void InitMinorExcepCombo();
    void InitMinorEventCombo();
    void InitAlarmHostLogList();

    void GetSearchParamFromWnd(NET_DVR_ALARMHOST_SEARCH_LOG_PARAM &struSearchParam);

    void InfoMinorAlarmMap(DWORD dwMinorType, CString &szTemp);  
    void InfoMinorExceptionMap(DWORD dwMinorType, CString &szTemp);
    void InfoMinorOperationMap(DWORD dwMinorType, CString &szTemp);
    void InfoMinorEventMap(DWORD dwMinorType, CString &szTemp);

//    void InfoMinorTypeMap(DWORD dwMinorType, CString &szTemp);
    void InfoMajorTypeMap(DWORD dwMajorType, CString &szTemp);
	void OnCancel() ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTLOGSEARCH_H__09841B14_3B4D_43B7_AB27_DFF4542750FA__INCLUDED_)
