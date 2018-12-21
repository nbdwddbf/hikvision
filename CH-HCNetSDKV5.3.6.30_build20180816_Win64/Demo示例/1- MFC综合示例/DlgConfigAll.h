#pragma once


// CDlgConfigAll dialog

class CDlgConfigAll : public CDialog
{
	DECLARE_DYNAMIC(CDlgConfigAll)

public:
	CDlgConfigAll(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgConfigAll();

// Dialog Data


public:
	//{{AFX_DATA(CDlgConfigAll)
	enum { IDD = IDD_DLG_CONFIG_ALL };
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CDlgConfigAll)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgConfigAll)
	afx_msg void OnBnClickedBtnRemoteConfig();
	afx_msg void OnBnClickedBtnLocalConfig();
	afx_msg void OnBnClickedBtnIPAccess();
	afx_msg void OnBnClickedBtnBackPreview();
	afx_msg void OnBnClickedBtnHDConfig();
	afx_msg void OnBtnBatchConfig();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
public:
	
	int m_iDeviceIndex;
	int m_iConfigType;
	void ConfigWndUpdate();
	
};
