#if !defined(AFX_DLGRECORDHOSTVIDEOCFG_H__25DACAB0_E367_456A_A29D_2290C5FB745F__INCLUDED_)
#define AFX_DLGRECORDHOSTVIDEOCFG_H__25DACAB0_E367_456A_A29D_2290C5FB745F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordHostVideoCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostVideoCfg dialog

class CDlgRecordHostVideoCfg : public CDialog
{
// Construction
public:
	CDlgRecordHostVideoCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecordHostVideoCfg)
	enum { IDD = IDD_DLG_RECORD_HOST_VIDEO_CFG };
		// NOTE: the ClassWizard will add data members here
	CComboBox	m_comExportType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecordHostVideoCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(CDlgRecordHostVideoCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG  m_lUserID;
    int   m_iDeviceIndex;

    char  m_szStatusBuf[ISAPI_STATUS_LEN];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDHOSTVIDEOCFG_H__25DACAB0_E367_456A_A29D_2290C5FB745F__INCLUDED_)
