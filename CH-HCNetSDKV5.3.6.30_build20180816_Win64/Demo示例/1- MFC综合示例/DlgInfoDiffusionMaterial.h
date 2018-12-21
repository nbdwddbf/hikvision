#if !defined(AFX_DLGINFODIFFUSIONMATERIAL_H__65BBEC6A_2634_4FA1_8381_4A9F955FAC49__INCLUDED_)
#define AFX_DLGINFODIFFUSIONMATERIAL_H__65BBEC6A_2634_4FA1_8381_4A9F955FAC49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionMaterial.h : header file
//

#include "InfoDiffusionParamsConvert.h"
#include "afxwin.h"

#define MAX_LEN_XML 10*1024*1024 //xml最大长度
#define TIMER_UPDOWNLOAD_MATERIAL_PROGRESS 1 //上传下载进度定时器
#define MAX_ID 256 //批量删除最大个数

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionMaterial dialog

class CDlgInfoDiffusionMaterial : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionMaterial(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionMaterial)
	enum { IDD = IDD_DLG_INFO_DIFFUSION_MATERIAL };
	CComboBox	m_cmbSearchApproveState;
	CComboBox	m_cmbSearchDynamicType;
	CComboBox	m_cmbSearchShareProp;
	CComboBox	m_cmbSearchStaticType;
	CComboBox	m_cmbSearchMaterialType;
	CListCtrl	m_listMaterial;
	CComboBox	m_cmbApprove;
	CComboBox	m_cmbShareProp;
	CComboBox	m_cmbEditShareProp;
	CStatic	m_statProgress;
	CComboBox	m_cmbDynamicMaterialType;
	CComboBox	m_cmbMaterialType;
	CComboBox	m_cmbStaticMaterialFormat;
	CComboBox	m_cmbStaticMaterialType;
	CComboBox	m_cmbStreamAddrType;
	CProgressCtrl	m_ctrlProgress;
	CString	m_szWebUrl;
	CString	m_szStreamUrl;
	DWORD	m_dwStreamPort;
	CString	m_szStreamIPAddr;
	CString	m_szStreamHostName;
	CString	m_szRssUrl;
	CString	m_szPropRemarks;
	CString	m_szPropName;
	DWORD	m_dwMaterialSize;
	CString	m_szMaterialRemarks;
	CString	m_szMaterialPath;
	CString	m_szMaterialName;
	DWORD	m_dwDownMaterialIndex;
	CString	m_szSavePath;
	CString	m_szApproveRemarks;
	DWORD	m_dwPlayDuration;
	COleDateTime	m_tmStartTime;
	COleDateTime	m_tmStartDate;
	COleDateTime	m_tmEndTime;
	COleDateTime	m_tmEndDate;
	CString	m_sUploader;
	DWORD	m_dwStartPosition;
	DWORD	m_dwMaterialNo;
	DWORD	m_dwStaticMinSize;
	DWORD	m_dwStaticMaxSize;
	DWORD	m_dwMaxResults;
	DWORD	m_dwMaterialID;
	CString	m_sSearchID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionMaterial)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionMaterial)
	afx_msg void OnBtnExit();
	afx_msg void OnBtnMaterialDel();
	afx_msg void OnBtnMaterialGet();
	afx_msg void OnBtnMaterialSet();
	afx_msg void OnBtnMaterialChoose();
	afx_msg void OnBtnMaterialDownload();
	afx_msg void OnBtnMaterialSave();
	afx_msg void OnBtnMaterialUpload();
	afx_msg void OnSelchangeComboDynamicMaterialType();
	afx_msg void OnSelchangeComboMaterialType();
	afx_msg void OnSelchangeComboStaticMaterialType();
	afx_msg void OnSelchangeComboStreamAddrType();
	virtual BOOL OnInitDialog();
	//afx_msg void OnTimer(UINT nIDEvent);
#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnDestroy();
	afx_msg void OnBtnMaterialSearch();
	afx_msg void OnSelchangeComboSearchMaterialType();
	afx_msg void OnClickListMaterial(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;
	int m_iDeviceIndex;
	
	NET_DVR_MATERIAL m_struMaterial;
	NET_DVR_MATERIAL_SEARCH_DESCRIPTION m_struDescription; //查询条件
	LPNET_DVR_MATERIAL_SEARCH_RESULT m_lpResult; //查询结果
	int m_iCurSelMaterial;
	
	LONG m_lUpdownloadHandle; //上传/下载句柄
	BOOL m_bUploading;        //正在上传
	BOOL m_bDownloading;      //正在下载

	char* m_pOutputXmlBuffer;
    int m_nArrayId[MAX_ID];
    int m_nCountId;

public:
	void InitMaterialList();
	void RefreshMaterialList();
    afx_msg void OnLvnItemchangedListMaterial(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedBtnBatchDel();
    afx_msg void OnBnClickedBtnBatchSet();
    CComboBox m_comOperatorType;
    DWORD m_dwOrgNo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONMATERIAL_H__65BBEC6A_2634_4FA1_8381_4A9F955FAC49__INCLUDED_)
