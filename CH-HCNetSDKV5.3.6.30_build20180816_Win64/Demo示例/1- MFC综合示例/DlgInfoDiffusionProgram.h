#if !defined(AFX_DLGINFODIFFUSIONPROGRAM_H__4392B62A_C7FE_46D5_A28B_D3BF8B838FA2__INCLUDED_)
#define AFX_DLGINFODIFFUSIONPROGRAM_H__4392B62A_C7FE_46D5_A28B_D3BF8B838FA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionProgram.h : header file
//

#include "InfoDiffusionParamsConvert.h"
#include "afxwin.h"

#define MAX_LEN_XML 10*1024*1024 //xml最大长度
#define MAX_ID 256 //批量删除最大个数

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionProgram dialog

class CDlgInfoDiffusionProgram : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionProgram(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionProgram)
	enum { IDD = IDD_DLG_INFO_DIFFUSION_PROGRAM };
	CComboBox	m_cmbPlayMode;
	CComboBox	m_cmbApproveState;
	CComboBox	m_cmbProApproveState;
	CComboBox	m_cmbProShareProp;
	CComboBox	m_cmbSwitchEffect;
	CComboBox	m_cmbShareProp;
	CListCtrl	m_listContent;
	CListCtrl	m_listPage;
	CListCtrl	m_listProgram;
	CString	m_szProgramRemarks;
	CString	m_szProgramName;
	DWORD	m_dwProgramID;
	DWORD	m_dwPageID;
	DWORD	m_dwImageWidth;
	DWORD	m_dwImageHeight;
	DWORD	m_dwBlue;
	DWORD	m_dwGreen;
	DWORD	m_dwRed;
	DWORD	m_dwSwitchDuration;
	DWORD	m_dwPlayDuration;
	COleDateTime	m_tmStartTime;
	COleDateTime	m_tmStartDate;
	COleDateTime	m_tmEndTime;
	COleDateTime	m_tmEndDate;
	CString	m_sUploader;
	DWORD	m_dwStartPosition;
	CString	m_sSearchID;
	DWORD	m_dwProImageWitdth;
	DWORD	m_dwProImageHeight;
	DWORD	m_dwMaxResults;
	CString	m_sApproveRemarks;
	CString	m_sPageName;
	DWORD   m_dwBackgroundPic;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionProgram)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionProgram)
	afx_msg void OnBtnExit();
	afx_msg void OnBtnPageDel();
	afx_msg void OnBtnPageGet();
	afx_msg void OnBtnPageGetall();
	afx_msg void OnBtnPageNew();
	afx_msg void OnBtnPageSet();
	afx_msg void OnBtnProgramDel();
	afx_msg void OnBtnProgramGet();
	afx_msg void OnBtnProgramNew();
	afx_msg void OnBtnProgramSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickListContent(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListContent(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuitemAdd();
	afx_msg void OnMenuitemDel();
	afx_msg void OnMenuitemMod();
	afx_msg void OnClickListPage(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnBtnProSearch();
	afx_msg void OnSelchangeComboPlayMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;
	int m_iDeviceIndex;

	LPNET_DVR_PROGRAM m_lpProgram;
	NET_DVR_PROGRAM_SEARCH_DESCRIPTION m_struDescription;
	LPNET_DVR_PROGRAM_SEARCH_RESULT m_lpResult;
	int m_nCurSelProgram;
	int m_nCurSelPage;
	int m_nCurContent;

	char* m_pOutputXmlBuffer;
    int m_nArrayId[MAX_ID];
    int m_nCountId;

public:
	void InitProgramListCtrl();
	void InitPageListCtrl();
	void InitContentListCtrl();
	void RefreshProgramItem(int nProgramIndex);
	void RefreshProgramList();
	void UpdateProgramInfo();
	void RefreshPageItem(int nPageIndex);
	void RefreshPageList();
	void RefreshContentItem(int nPageIndex, int nContentIndex);
	void RefreshContentList(int nPageIndex);
    //BOOL ConvertProgramIdToXml(char* *pXmlBuf, DWORD &dwXmlLen);
    afx_msg void OnBnClickedBtnDelMore();
    afx_msg void OnLvnItemchangedListPage(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedBtnBatcgSet();
    CComboBox m_comOperatorType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONPROGRAM_H__4392B62A_C7FE_46D5_A28B_D3BF8B838FA2__INCLUDED_)
