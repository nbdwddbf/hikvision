#include "afxwin.h"
#if !defined(AFX_DLGRECORDHOSTFILEPUBLISH_H__C83496A1_D72A_4FDE_874B_FC95211415EE__INCLUDED_)
#define AFX_DLGRECORDHOSTFILEPUBLISH_H__C83496A1_D72A_4FDE_874B_FC95211415EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordHostFilePublish.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostFilePublish dialog

class CDlgRecordHostFilePublish : public CDialog
{
// Construction
public:
	CDlgRecordHostFilePublish(CWnd* pParent = NULL);   // standard constructor
    virtual BOOL OnInitDialog();

// Dialog Data
	//{{AFX_DATA(CDlgRecordHostFilePublish)
	enum { IDD = IDD_DLG_RECORD_HOST_FILE_PUBLISH };
		// NOTE: the ClassWizard will add data members here
    CComboBox	m_comPubilshStatus;
	CComboBox	m_comCMDType;
    CComboBox   m_comChannel;
	CString	m_csFileID;
	CString	m_csFileIDCond;
    CString m_csCourseName;
    CString m_csInstructorName;
    CString m_csCoureDescription;
	BYTE	m_byPubilshPercent;
	COleDateTime	m_startDate;
	COleDateTime	m_startTime;
	COleDateTime	m_stopDate;
	COleDateTime	m_stopTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecordHostFilePublish)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRecordHostFilePublish)
	afx_msg void OnButtonSetRecordingPublishFile();
	afx_msg void OnButtonGetPublishProgress();
    afx_msg void OnButtonGetPublishFileInfo();
    afx_msg void OnButtonSetPublishFileInfo();
    afx_msg void OnButtonRecordingPublishFile();
    afx_msg void OnButtonPublishProgress();
    afx_msg void OnButtonPublishInfo();
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

#endif // !defined(AFX_DLGRECORDHOSTFILEPUBLISH_H__C83496A1_D72A_4FDE_874B_FC95211415EE__INCLUDED_)
