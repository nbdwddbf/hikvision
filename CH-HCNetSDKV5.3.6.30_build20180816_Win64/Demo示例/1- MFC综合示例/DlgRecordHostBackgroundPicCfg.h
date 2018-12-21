#if !defined(AFX_DLGRECORDHOSTBACKGROUNDPICCFG_H__EAF0EACF_0003_4505_B2A4_E3AF0285F486__INCLUDED_)
#define AFX_DLGRECORDHOSTBACKGROUNDPICCFG_H__EAF0EACF_0003_4505_B2A4_E3AF0285F486__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordHostBackgroundPicCfg.h : header file
//
#include "GDIPLUS/GdiPlus.h"
using namespace Gdiplus;

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostBackgroundPicCfg dialog

class CDlgRecordHostBackgroundPicCfg : public CDialog
{
// Construction
public:
	CDlgRecordHostBackgroundPicCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecordHostBackgroundPicCfg)
	enum { IDD = IDD_DLG_RECORD_HOST_BACKGROUND_PIC_CFG };
		// NOTE: the ClassWizard will add data members here
    CComboBox	m_comDirectedChannel;
	CComboBox	m_comPicType;

	CButton   m_chkEnable;

	CStatic   m_labProgress;

	CEdit       m_edtPicSize;
	CEdit       m_edtPicWidth;
	CEdit       m_edtPicHeight;
	CEdit       m_edtPicName;
	CEdit       m_edtPicID;
	CEdit       m_edtFileName;

    CButton     m_btnSelectFile;


	CButton     m_radPicUpload;
	CButton     m_btnStartUpload;
	CButton     m_btnStopUpload;
	CButton     m_btnGetUploadState;
	CComboBox	m_comUploadState;

	CButton     m_radPicCfg;
	CButton     m_btnGetPic;
	CButton     m_btnSetPic;

	CButton   m_radPicQuery;
	CButton     m_btnQueryPic;

	CButton   m_radPicDel;
	CButton     m_btnDelPic;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecordHostBackgroundPicCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL        m_bEnable;
    
    DWORD       m_dwChannel;

	DWORD		m_dwPicSize;
	DWORD		m_dwPicType;
	DWORD        m_dwPicWidth;
	DWORD        m_dwPicHeight;

	CString m_strPicName;
	CString m_strPicID;
	CString m_strFileName;

    

	LONG m_lUploadHandle;

	DWORD m_dwUploadProgress;

	

	// Generated message map functions
	//{{AFX_MSG(CDlgRecordHostBackgroundPicCfg)
	afx_msg void OnRadPicUpload();
	afx_msg void OnRadPicCfg();
	afx_msg void OnRadPicQuery();
	afx_msg void OnRadPicDel();
	afx_msg void OnBtnStartUpload();
	afx_msg void OnBtnStopUpload();
	afx_msg void OnBtnGetUploadState();
	afx_msg void OnBtnGetBGPicCfg();
	afx_msg void OnBtnSetBGPicCfg();
	afx_msg void OnBtnSetBGPicQuery();
	afx_msg void OnBtnSetBGPicDel();
    afx_msg void OnBtnSelectFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL OnInitDialog();

public:
    LONG  m_lChannel;
    LONG  m_lUserID;
    int   m_iDeviceIndex;

    char  m_szStatusBuf[ISAPI_STATUS_LEN];

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDHOSTBACKGROUNDPICCFG_H__EAF0EACF_0003_4505_B2A4_E3AF0285F486__INCLUDED_)
