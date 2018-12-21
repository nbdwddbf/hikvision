#if !defined(AFX_DLGVCABLACKLIST_H__514F1BD8_20AD_41E1_B63D_2570F02DD002__INCLUDED_)
#define AFX_DLGVCABLACKLIST_H__514F1BD8_20AD_41E1_B63D_2570F02DD002__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaBlackList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBlackList dialog

class CDlgVcaBlackList : public CDialog
{
// Construction
public:
	CDlgVcaBlackList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaBlackList)
	enum { IDD = IDD_DLG_VCA_BLACKLIST };
	CComboBox	m_comboLevel;
	CListCtrl	m_listBlackList;
	CComboBox	m_comboNativePlace;
	CComboBox	m_comboCerfiticateType;
	CComboBox	m_comboBlackListType;
	CComboBox	m_comboSex;
	CString	m_csCertificateNumber;
	DWORD	m_dwGroupID;
	CString	m_csName;
	CString	m_csRemark;
	DWORD	m_dwRegisterID;
	CString	m_csBirthDate;
	CString	m_csFastRegPicPath;
	BOOL	m_bChkImportPicModel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaBlackList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaBlackList)
	afx_msg void OnBtnRegister();
	afx_msg void OnBtnSearch();
	afx_msg void OnBtnExit();
	afx_msg void OnDblclkListBlacklist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnUpdate();
	afx_msg void OnBtnDelete();
	afx_msg void OnBtnGetBlacklistPic();
	afx_msg void OnBtnFastScan();
	afx_msg void OnBtnFastRegister();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;
	LONG    m_lFindHandle;
	HANDLE  m_hFindThread;
	LONG    m_lBlackListNum;
	char    m_chFilename[256]; //抓图保存的位置
	DWORD   m_dwFileSize;

	NET_VCA_BLACKLIST_PARA m_struBlackListPara;
	NET_VCA_BLACKLIST_PIC m_struBlackListPic;
	void GetBlackListInfoFromWnd(NET_VCA_BLACKLIST_INFO& struBlackListInfo);
	NET_VCA_BLACKLIST_FASTREGISTER_PARA m_struBlFastPara;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCABLACKLIST_H__514F1BD8_20AD_41E1_B63D_2570F02DD002__INCLUDED_)
