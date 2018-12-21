#if !defined(AFX_DLGRECORDLABEL_H__F4F26509_25A7_4B1B_8322_1CACD0B3EAD1__INCLUDED_)
#define AFX_DLGRECORDLABEL_H__F4F26509_25A7_4B1B_8322_1CACD0B3EAD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordLabel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordLabel dialog

class CDlgRecordLabel : public CDialog
{
// Construction
public:
	CDlgRecordLabel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecordLabel)
	enum { IDD = IDD_DLG_RECORD_LABEL };
	CStatic	m_staticSearchState;
	CListCtrl	m_listRecordLabel;
	CComboBox	m_comboChannel;
	CTime	m_ctDateStart;
	CTime	m_ctDateStop;
	CTime	m_ctTimeStart;
	CTime	m_ctTimeStop;
	CString	m_csRecordName;
	CTime	m_ctLabelTime;
	CString	m_csDstLabelName;
	BOOL	m_bDrawFrame;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecordLabel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRecordLabel)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSearchRecord();
	afx_msg void OnBtnDelLabel();
	afx_msg void OnButtonModify();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lChannel;
    LONG    m_lServerID;
    int     m_iDevIndex;
    LONG    m_lFindHandle;
    DWORD   m_dwChanneNum;
    HANDLE  m_hFindThread;
    NET_DVR_FIND_LABEL  m_struFindLabel;

    NET_DVR_RECORD_LABEL m_struRecordLabel;
    NET_DVR_LABEL_IDENTIFY m_struLabelIdentify;
    NET_DVR_DEL_LABEL_PARAM m_struDelLabelParam;
public:
    BOOL CheckInitParam();
    void InitWnd();
    void InitComboChannel();
    void InitTimeControl();
    void InitListRecordLabel();
    void GetSearchParamFromWnd(NET_DVR_FIND_LABEL &struFindLabel);
    
    BOOL InsertRecordLabel(NET_DVR_RECORD_LABEL &struRecordLabel, NET_DVR_LABEL_IDENTIFY &struLabelIdentify);
    
    BOOL GetDelRecordLabelFrmWnd(NET_DVR_DEL_LABEL_PARAM &struDelLabelParam); 
    BOOL DelRecordLabel(NET_DVR_DEL_LABEL_PARAM &struDelLabelParam);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDLABEL_H__F4F26509_25A7_4B1B_8322_1CACD0B3EAD1__INCLUDED_)
