#if !defined(AFX_DLGTERMMANAGE_H__73CB0DE6_578B_4BC1_A7D0_5ECD01826423__INCLUDED_)
#define AFX_DLGTERMMANAGE_H__73CB0DE6_578B_4BC1_A7D0_5ECD01826423__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTermManage.h : header file
//

#include "InfoDiffusionParamsConvert.h"
#include "afxcmn.h"

#define MAX_ID 256 //批量删除最大个数

/////////////////////////////////////////////////////////////////////////////
// CDlgTermManage dialog

struct IPC_INFO
{
	DWORD dwID;
	char  szIpcType[MAX_XML_ELEM_LEN];
	DWORD dwTermiChannelNo;
	char  szAddrFormatType[MAX_XML_ELEM_LEN];
	char  szHostName[MAX_XML_ELEM_LEN];
	char  szIPVersion[MAX_XML_ELEM_LEN];
	char  szIPv4[MAX_XML_ELEM_LEN];
	char  szIPv6[MAX_XML_ELEM_LEN];
	DWORD dwPort;
	char  szUser[MAX_XML_ELEM_LEN];
	char  szPwd[MAX_XML_ELEM_LEN];
};


struct TERM_INFO
{
	DWORD  dwID;
	char szTermName[MAX_XML_ELEM_LEN];
	char szRegType[MAX_XML_ELEM_LEN];
	char szCondCode[MAX_XML_ELEM_LEN];

	char szAddrFormatType[MAX_XML_ELEM_LEN];
	char szHostName[MAX_XML_ELEM_LEN];
	char szIPVersion[MAX_XML_ELEM_LEN];
	char szIPv4[MAX_XML_ELEM_LEN];
	char szIPv6[MAX_XML_ELEM_LEN];
	DWORD dwPort;
	char szUser[MAX_XML_ELEM_LEN];
	char szPwd[MAX_XML_ELEM_LEN];

	DWORD    dwIpcInfoCount;
	IPC_INFO aIPCInfo[MAX_IPCS_A_TERMINAL];

	DWORD dwBelongGroup;
    DWORD dwOrgNo;
};


class CDlgTermManage : public CDialog
{
// Construction
public:
	CDlgTermManage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTermManage)
	enum { IDD = IDD_DLG_TERM_MANAGE };
	CComboBox	m_cmbAddrType;
	CComboBox	m_comRegType;
	CComboBox   m_comPullAddrFormatType;
	CComboBox	m_comPullIPVersion;
	CComboBox	m_comIpcType;
	CComboBox	m_comIpcIPVersion;
	CString	m_csIpcAddrFormatType;
	int		m_nOperateType;
	DWORD	m_dwBelongGroup;
	DWORD	m_dwTerminalChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTermManage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	DWORD   m_dwTermID;
	CString m_csTermName;
	CString m_csRegType;

	CString m_CondCode;//特征代码

	CString m_csPullAddrFormatType;
	CString m_csPullHostName;
	CString m_csPullIPVersion;
	CString m_csPullIPv4;
	CString m_csPullIPv6;
	DWORD   m_dwPullPort;
	CString m_csPullUserName;
	CString m_csPullPwd;

	DWORD   m_dwIpcID;
	CString m_csIpcType;
	CString m_csIpcHostName;
	CString m_csIpcIPVersion;
	CString m_csIpcIPv4;
	CString m_csIpcIPv6;
	DWORD   m_dwIpcPort;
	CString m_csIpcUserName;
	CString m_csIpcPwd;

	CListCtrl* m_pListIpc;
	CListCtrl* m_pListTerm;

	IPC_INFO m_aIPCInfo[MAX_IPCS_A_TERMINAL];
	DWORD    m_dwIpcInfoCount;
	DWORD    m_dwIpcInfoIndex;

	TERM_INFO  m_struTermInfo;
	TERM_INFO* m_paTermInfo;
	DWORD      m_dwTermInfoCount;
	DWORD      m_dwTermInfoIndex;

	BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(CDlgTermManage)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnAddIpc();
	afx_msg void OnRadGetOne();
	afx_msg void OnRadGetMore();
	afx_msg void OnRadSet();
	afx_msg void OnRadAdd();
	afx_msg void OnRadDel();
	afx_msg void OnClickLstTermInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickLstIpcInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComAddrFormatType();
	afx_msg void OnSelchangeComIpcIpVersion();
	afx_msg void OnSelchangeComRegType();
	afx_msg void OnSelchangeComboAddrType();
	afx_msg void OnSelchangeComPullIpVersion();
	afx_msg void OnBtnDelIpc();
	afx_msg void OnBtnModIpc();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL m_bGetOne;

	char    m_szRequestURL[REQUEST_URL_LEN];
	char*   m_pXMLParamBuf;
	DWORD   m_dwXMLParamBufLen;
	char*   m_pXMLResultBuf;
	DWORD   m_dwXMLResultBufLen;	
	char    m_szXMLStatus[ISAPI_STATUS_LEN];
	
	CString ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf);
		
private:
	int   m_iDeviceIndex;
    LONG  m_lUserID;
    int m_nArrayId[MAX_ID];
    int m_nCountId;
public:
    afx_msg void OnBnClickedBtnBatchDel();
    CListCtrl m_listTermianl;
    DWORD m_dwOrgNo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTERMMANAGE_H__73CB0DE6_578B_4BC1_A7D0_5ECD01826423__INCLUDED_)
