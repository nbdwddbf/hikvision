#if !defined(AFX_DLGCLOUDURLCFG_H__A7629274_33D8_42D9_A208_D7FC9D9C501F__INCLUDED_)
#define AFX_DLGCLOUDURLCFG_H__A7629274_33D8_42D9_A208_D7FC9D9C501F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCloudUrlCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudUrlCfg dialog

class CDlgCloudUrlCfg : public CDialog
{
// Construction
public:
	CDlgCloudUrlCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCloudUrlCfg)
	enum { IDD = IDD_DLG_CLOUD_URL_CFG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCloudUrlCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCloudUrlCfg)
	afx_msg void OnBtnGetCloudUrl();
    virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    CComboBox m_comboCloudType;
    CString	m_csCloudUrl;
    char m_szStatusBuf[ISAPI_STATUS_LEN];
public:
    int m_lUserID;
    int m_lChanNo;
    int m_iDevIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCLOUDURLCFG_H__A7629274_33D8_42D9_A208_D7FC9D9C501F__INCLUDED_)
