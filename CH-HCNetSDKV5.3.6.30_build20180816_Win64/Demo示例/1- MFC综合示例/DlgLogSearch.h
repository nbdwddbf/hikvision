#pragma once
#include "afxwin.h"
#include "time.h"
#include "afxcmn.h"


// CDlgLogSearch dialog

class CDlgLogSearch : public CDialog
{
	DECLARE_DYNAMIC(CDlgLogSearch)

public:
	CDlgLogSearch(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgLogSearch();

// Dialog Data
public:
	//{{AFX_DATA(CDlgLogSearch)
	enum { IDD = IDD_DLG_LOG_SEARCH };
	CComboBox	m_comboSequence;
	CComboBox m_comboMode;
	CComboBox m_comboMajorType;
	CComboBox m_comboMinorType;
	CTime m_ctTimeStart;
	CTime m_ctDateStart;
	CTime m_ctDateStop;
	CTime m_ctTimeStop;
	CListCtrl m_listDeviceLog;
	BOOL m_bChkSmart;
	BOOL	m_bVideoPlatLog;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CDlgLogSearch)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgLogSearch)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSearch();
	afx_msg void OnDblclkListDeviceLog(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnExit();
	afx_msg void OnSelchangeComboMinorType();
	afx_msg void OnCheckVideoplat();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	int m_iDeviceIndex;
	LONG m_lLoginID;
	int m_iMode;
	int m_iMajType;
	int m_iMinType;
	
	BOOL m_bSearch;
	LONG m_lLogHandle;
	HANDLE m_hFileThread;
	LONG m_lLogNum;

	BOOL CheckInitParam();
	void DoHide();
	void EnableCtrl(BOOL bEnable);
	void AddMinorString();
	inline BOOL ValidIPv6(BYTE *ip);
};
