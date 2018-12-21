#if !defined(AFX_DLGRECORDSTATUS_H__48CCD273_0E8F_4BF2_A6A3_41FAAD5642E8__INCLUDED_)
#define AFX_DLGRECORDSTATUS_H__48CCD273_0E8F_4BF2_A6A3_41FAAD5642E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordStatus dialog

class CDlgRecordStatus : public CDialog
{
// Construction
public:
	CDlgRecordStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecordStatus)
	enum { IDD = IDD_DLG_RECORD_STATUS };
	CComboBox	m_comRecordStatus;
	DWORD	m_dwChannel;
	CString	m_byRecUUID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecordStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRecordStatus)
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	int  m_iDeviceIndex;
	int m_iStartChannel;

	char m_szStatusBuf[ISAPI_STATUS_LEN];
    int m_iRecordingTime;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDSTATUS_H__48CCD273_0E8F_4BF2_A6A3_41FAAD5642E8__INCLUDED_)
