#if !defined(AFX_DLGINFODIFFUSIONSCHEDULESEARCH_H__116F9854_5CE0_4920_9BE3_7FA9C095F43C__INCLUDED_)
#define AFX_DLGINFODIFFUSIONSCHEDULESEARCH_H__116F9854_5CE0_4920_9BE3_7FA9C095F43C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionScheduleSearch.h : header file
//

#include "InfoDiffusionParamsConvert.h"

#define MAX_LEN_XML 10*1024*1024 //xml最大长度
#define MAX_ID 256 //批量删除最大个数

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionScheduleSearch dialog

class CDlgInfoDiffusionScheduleSearch : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionScheduleSearch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionScheduleSearch)
	enum { IDD = IDD_DLG_INFO_DIFFUSION_SCHEDULE_SEARCH };
	CListCtrl	m_listSchedule;
	CComboBox	m_cmbScheduleType;
	CComboBox	m_cmbShareProp;
	CComboBox	m_cmbApproveState;
	CString	m_sSearchID;
	DWORD	m_dwMaxResults;
	DWORD	m_dwStartPosition;
	CString	m_sUploader;
	COleDateTime	m_tmEndDate;
	COleDateTime	m_tmEndTime;
	COleDateTime	m_tmStartDate;
	COleDateTime	m_tmStartTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionScheduleSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionScheduleSearch)
	afx_msg void OnBtnScheduleSearch();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;
	int m_iDeviceIndex;

	NET_DVR_SCHEDULE_SEARCH_DESCRIPTION m_struDescription;
	LPNET_DVR_SCHEDULE_SEARCH_RESULT m_lpSearchResult;
	char* m_pOutputXmlBuffer;
    int m_nArrayId[MAX_ID];
    int m_nCountId;

public:
	void InitScheduleCtrlList();
	void RefreshScheduleItem(int nScheduleIndex);
	void RefreshScheduleList();
    afx_msg void OnBnClickedBtnBatchDel();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONSCHEDULESEARCH_H__116F9854_5CE0_4920_9BE3_7FA9C095F43C__INCLUDED_)
