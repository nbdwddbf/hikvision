#pragma once


// CDlgUpgrade dialog
//update operation
class CDlgUpgrade : public CDialog
{
	DECLARE_DYNAMIC(CDlgUpgrade)

public:
	CDlgUpgrade(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgUpgrade();

// Dialog Data

public:
	//{{AFX_DATA(CDlgUpgrade)
	enum { IDD = IDD_DLG_UPGRADE };
	CProgressCtrl	m_progressSub;
	CComboBox	m_comboChan;
	CComboBox	m_comboUpgradeType;
	CComboBox	m_comboEnvironment;
	CComboBox	m_comboCardType;
    CComboBox	m_comboAuxDev;
	CProgressCtrl	m_progressUpgrade;
	CString m_csUpgradeFile;
	CString m_csUpgradeStat;
	CString	m_csUpgradeStep;
	BOOL	m_bFuzzyUpgrade;
    CString m_csUnitID;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CDlgUpgrade)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgUpgrade)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnBrowseFile();
	afx_msg void OnBnClickedBtnUpgrade();
	afx_msg void OnBnClickedBtnUpgradeExit();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnBtnSetEnviro();
	afx_msg void OnSelchangeComboUpgradeType();
	afx_msg void OnBtnGetupgradeinfo();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	LONG m_lUpgradeHandle;
	
	LONG	m_lServerID;
	LONG    m_lChannel;
	UINT	m_lpUpgradeTimer;
	BOOL	m_bUpgrade;
	int		m_iDeviceIndex;
	int  findTargetFile(const char* szFilePath, const char* szFileFlag, char* szTargetFileName);
	int  ConvertData(const char *src, char *dst, int nLen);
	CString F_GetDirectoryPath();
    DWORD m_dwAcsNo;
};
