#if !defined(AFX_DLGSTREAMRECORDINFO_H__CAB2D74D_13C6_4C4D_B5F7_073C71AFF08F__INCLUDED_)
#define AFX_DLGSTREAMRECORDINFO_H__CAB2D74D_13C6_4C4D_B5F7_073C71AFF08F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStreamRecordInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamRecordInfo dialog

class CDlgStreamRecordInfo : public CDialog
{
// Construction
public:
	CDlgStreamRecordInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgStreamRecordInfo)
	enum { IDD = IDD_DLG_STREAM_RECORD_INFO };
	CComboBox	m_cmbStreamType;
	CComboBox	m_cmbRecordDelay;
	CComboBox	m_cmbPreRecordTime;
	CListCtrl	m_lstStreamRecordInfo;
	CString	m_strStreamID;
	CString	m_strRelatedChannel;
	BOOL	m_bTimingRecord;
	BOOL	m_bRedundancyRecord;
	CString	m_strDurationTime;
	BOOL	m_bRecordAudio;
	CString	m_strStatus;
	short	m_wLockDuration;
	BOOL	m_bBackup;
	BOOL	m_bPassback;
	//}}AFX_DATA

	NET_DVR_STREAM_RECORD_INFO	m_struStreamRecordInfo[64];


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgStreamRecordInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgStreamRecordInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAddStreamID();
	afx_msg void OnButtonDelStreamID();
	afx_msg void OnDblclkListStreamRecordInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonTimingRecordSet();
	afx_msg void OnCheckTimingRecord();
	afx_msg void OnButtonSetStreamRecordInfo();
	afx_msg void OnButtonGetStreamRecordInfo();
	afx_msg void OnClickListStreamRecordInfo(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSTREAMRECORDINFO_H__CAB2D74D_13C6_4C4D_B5F7_073C71AFF08F__INCLUDED_)
