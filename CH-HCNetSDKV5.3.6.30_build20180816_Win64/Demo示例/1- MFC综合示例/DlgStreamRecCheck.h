#include "afxcmn.h"
#include "afxwin.h"
#if !defined(AFX_DLGSTREAMRECCHECK_H__FFD6FCF5_7026_48BA_B9AC_921693B337B1__INCLUDED_)
#define AFX_DLGSTREAMRECCHECK_H__FFD6FCF5_7026_48BA_B9AC_921693B337B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStreamRecCheck.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamRecCheck dialog

class CDlgStreamRecCheck : public CDialog
{
// Construction
public:
	CDlgStreamRecCheck(CWnd* pParent = NULL);   // standard constructor
	~CDlgStreamRecCheck();

// Dialog Data
	//{{AFX_DATA(CDlgStreamRecCheck)
	enum { IDD = IDD_DLG_STREAM_RECORD_CHECK };
	CComboBox	m_cmbRecNotComplete;
	CListCtrl	m_listMissingRecFile;
	CComboBox	m_cmbCheckType;
	COleDateTime	m_oleDateStart;
	COleDateTime	m_oleDateStop;
	COleDateTime	m_oleTimeStart;
	COleDateTime	m_oleTimeStop;
	int		m_nChannel;
	CString	m_csStreamID;
	COleDateTime	m_oleDateStart2;
	COleDateTime	m_oleDateStop2;
	int		m_nChannel2;
	CString	m_csStreamID2;
	int		m_nTotalRecSize;
	COleDateTime	m_oleTimeStart2;
	COleDateTime	m_oleTimeStop2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgStreamRecCheck)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgStreamRecCheck)
	afx_msg void OnBtnCheck();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGetSegmentRec();
	LRESULT afx_msg OnMsgRecCheckFinish(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	int m_iDevIndex;
	
	LONG    m_lRecordCheckHandle;
	BOOL	m_bGetRecordCheckNext;
	HANDLE	m_hGetRecordCheckThread;
	NET_DVR_RECORD_CHECK_RET m_struRecordCheckRet;
	
	static DWORD WINAPI GetRecordCheckThread(LPVOID lpRecordCheck);
	void AddRecordCheckInfoToDlg(LPNET_DVR_RECORD_CHECK_RET lpInter);

	LONG    m_lRecordSegmentHandle;
	BOOL	m_bRecordSegmentNext;
	HANDLE	m_hRecordSegmentThread;
	NET_DVR_RECORD_SEGMENT_RET m_struRecordSegmentRet;
	
	static DWORD WINAPI GetRecordSegmentThread(LPVOID lpRecordSegment);
	void AddRecordSegmentInfoToDlg(LPNET_DVR_RECORD_SEGMENT_RET lpInter);
	CComboBox m_cmbTotalRec;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSTREAMRECCHECK_H__FFD6FCF5_7026_48BA_B9AC_921693B337B1__INCLUDED_)
