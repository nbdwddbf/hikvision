#if !defined(AFX_DLGCLOUDSTORAGECFG_H__DAC5D05F_F956_4D74_AA27_82BC35009409__INCLUDED_)
#define AFX_DLGCLOUDSTORAGECFG_H__DAC5D05F_F956_4D74_AA27_82BC35009409__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCloudStorageCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudStorageCfg dialog

class CDlgCloudStorageCfg : public CDialog
{
// Construction
public:
	CDlgCloudStorageCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCloudStorageCfg)
	enum { IDD = IDD_DLG_CLOUDSTORAGE_CFG };
		// NOTE: the ClassWizard will add data members here
	CComboBox	m_comboPoolParam;
	BOOL	m_bEnable;
	CString	m_csIP;
	CString	m_csIPV6;
	DWORD	m_wPort;
	CString	m_csPasswd;
	CString	m_csUserName;
	DWORD	m_dwPoolID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCloudStorageCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCloudStorageCfg)
		// NOTE: the ClassWizard will add member functions here
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnSelchangeComboPoolparam();
	afx_msg void OnBtnSure();
	afx_msg void OnBtnGet();
	//	afx_msg void OnChangeEditPort();
	//	afx_msg void OnErrspaceEditPort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	NET_DVR_CLOUDSTORAGE_CFG m_struCloudStorageCfg;
	NET_DVR_CLOUDSTORAGE_COND m_struCloudStorageCond;
	BOOL SaveDataFromUI();
	BOOL UpdataDataToUI();
	LONG m_lServerID;
	void CurCfgUpdate();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCLOUDSTORAGECFG_H__DAC5D05F_F956_4D74_AA27_82BC35009409__INCLUDED_)
