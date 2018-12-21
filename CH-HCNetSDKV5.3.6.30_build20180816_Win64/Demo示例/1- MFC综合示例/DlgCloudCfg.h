#if !defined(AFX_DLGCLOUDCFG_H__BADE3136_DEB8_4398_8D60_326096B7364E__INCLUDED_)
#define AFX_DLGCLOUDCFG_H__BADE3136_DEB8_4398_8D60_326096B7364E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCloudCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudCfg dialog

class CDlgCloudCfg : public CDialog
{
// Construction
public:
	CDlgCloudCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCloudCfg)
	enum { IDD = IDD_DLG_CLOUD_CFG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCloudCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCloudCfg)
	afx_msg void OnBtnGetCloudCfg();
	afx_msg void OnBtnSetCloudCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    CComboBox m_comboEnable;
    CComboBox m_comboCloudType;
    CComboBox m_comboStatus;
    CString	m_csAuthCode;
    CString	m_csAlias;
    int m_i64TotalCapability;
    int m_i64UsedSpace;
    char m_szStatusBuf[ISAPI_STATUS_LEN];
    NET_DVR_CLOUD_CFG m_struCloudCfg;
    NET_DVR_STD_CONFIG m_struStdConfig;
public:
    int m_lUserID;
    int m_lChanNo;
    int m_iDevIndex;   
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCLOUDCFG_H__BADE3136_DEB8_4398_8D60_326096B7364E__INCLUDED_)
