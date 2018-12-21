#include "afxwin.h"
#if !defined(AFX_DLGRECORDHOSTV120_H__AA942A05_04B2_4EC1_A9A6_1BD933E15CC9__INCLUDED_)
#define AFX_DLGRECORDHOSTV120_H__AA942A05_04B2_4EC1_A9A6_1BD933E15CC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordHostV120.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostV120 dialog

class CDlgRecordHostV120 : public CDialog
{
// Construction
public:
	CDlgRecordHostV120(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecordHostV120)
	enum { IDD = IDD_DLG_RECORD_HOST_V120 };
	CComboBox	m_comPubilshStatus;
	CComboBox	m_comExportType;
	CComboBox	m_comCMDType;
	CString	m_csFileID;
	CString	m_csFileIDCond;
	BYTE	m_byPubilshPercent;
	COleDateTime	m_startDate;
	COleDateTime	m_startTime;
	COleDateTime	m_stopDate;
	COleDateTime	m_stopTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecordHostV120)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRecordHostV120)
	afx_msg void OnButtonSetRecordingPublishFile();
	afx_msg void OnButtonGetPublishProgress();
	afx_msg void OnButtonSetRecordVideo();
	afx_msg void OnButtonGetRecordVideo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lLoginID;
    INT  m_iDeviceIndex;
	LONG m_lChannel;
    char    m_szStatusBuf[ISAPI_STATUS_LEN];
    CComboBox m_ComboFileType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDHOSTV120_H__AA942A05_04B2_4EC1_A9A6_1BD933E15CC9__INCLUDED_)
