#if !defined(AFX_DLGRECORDHOSTFILMMODECFG_H__4C9EE89E_BFD8_4B01_BA32_3E0F662B6998__INCLUDED_)
#define AFX_DLGRECORDHOSTFILMMODECFG_H__4C9EE89E_BFD8_4B01_BA32_3E0F662B6998__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordHostFilmModeCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostFilmModeCfg dialog

class CDlgRecordHostFilmModeCfg : public CDialog
{
// Construction
public:
	CDlgRecordHostFilmModeCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecordHostFilmModeCfg)
	enum { IDD = IDD_DLG_RECORD_HOST_FILM_MODE_CFG };
		// NOTE: the ClassWizard will add data members here
    CComboBox	m_comType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecordHostFilmModeCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(CDlgRecordHostFilmModeCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lLoginID;
    INT  m_iDeviceIndex;
    DWORD m_dwChannel;
    
    NET_DVR_FILM_MODE_CFG m_struFilmModeCfg;
    char m_szStatusBuf[ISAPI_STATUS_LEN];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDHOSTFILMMODECFG_H__4C9EE89E_BFD8_4B01_BA32_3E0F662B6998__INCLUDED_)
