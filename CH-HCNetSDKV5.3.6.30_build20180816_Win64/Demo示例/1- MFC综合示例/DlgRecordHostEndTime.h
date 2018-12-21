#if !defined(AFX_DLGRECORDHOSTENDTIME_H__AEC98D72_8983_45A8_AAE0_778F28919FDE__INCLUDED_)
#define AFX_DLGRECORDHOSTENDTIME_H__AEC98D72_8983_45A8_AAE0_778F28919FDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordHostEndTime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgRecordHostEndTime dialog

class DlgRecordHostEndTime : public CDialog
{
// Construction
public:
	DlgRecordHostEndTime(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgRecordHostEndTime)
	enum { IDD = IDD_DLG_RECORD_END_TIME };
	CTime	m_ctData;
	CTime	m_ctTime;
	//}}AFX_DATA

	LONG m_lUserID;
	int  m_iDeviceIndex;
	int m_iMirrorNum;
	int m_iStartChannel;
	NET_DVR_TIME_EX m_TimeEx;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgRecordHostEndTime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(DlgRecordHostEndTime)
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDHOSTENDTIME_H__AEC98D72_8983_45A8_AAE0_778F28919FDE__INCLUDED_)
