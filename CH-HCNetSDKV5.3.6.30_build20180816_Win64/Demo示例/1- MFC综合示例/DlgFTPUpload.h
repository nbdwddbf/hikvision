#if !defined(AFX_DLGFTPUPLOAD_H__78E970E1_4C01_4A78_BB6B_A5D219909E5D__INCLUDED_)
#define AFX_DLGFTPUPLOAD_H__78E970E1_4C01_4A78_BB6B_A5D219909E5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFTPUpload.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFTPUpload dialog

class CDlgFTPUpload : public CDialog
{
// Construction
public:
	CDlgFTPUpload(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFTPUpload)
	enum { IDD = IDD_DLG_IPC_FTPUPLOAD };
	CComboBox	m_cmbFTPUploadParam;
	CComboBox	m_cmbRuleTypeItem;
	CComboBox	m_byPicMode;
	CComboBox	m_byEventMode;
	CString	m_strCameraName;
	CString	m_strRuleTypeItem;
	UINT	m_uCameraNameNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFTPUpload)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFTPUpload)
	virtual void OnCancel();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeComboPicmode();
	afx_msg void OnSelchangeComboRuleTypeItem();
	afx_msg void OnBtnSave();
	afx_msg void OnSelchangeComboFtpuploadParma();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lServerID;
    int m_iDevIndex; 
protected:
    NET_DVR_FTPUPLOADCFG m_struMacFilter;
    char    m_szStatusBuf[ISAPI_STATUS_LEN];
    afx_msg void OnitCombox();
    afx_msg int RuleTypeItemNo(int i);
    afx_msg char* RuleTypeItemsz();
    afx_msg int RuleTypeItemSzToNo(char* szStr);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFTPUPLOAD_H__78E970E1_4C01_4A78_BB6B_A5D219909E5D__INCLUDED_)
