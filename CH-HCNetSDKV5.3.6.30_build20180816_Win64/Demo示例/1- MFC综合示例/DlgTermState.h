#if !defined(AFX_DLGTERMSTATE_H__47A8EA42_AC98_43E9_92BA_CB8E211601D3__INCLUDED_)
#define AFX_DLGTERMSTATE_H__47A8EA42_AC98_43E9_92BA_CB8E211601D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTermState.h : header file
//

#include "InfoDiffusionParamsConvert.h"

struct CPU_INFO
{
	char  szCpuDesc[MAX_XML_ELEM_LEN];
	DWORD dwCpuUtil;
};

struct MEM_INFO
{
	char  szMemDesc[MAX_XML_ELEM_LEN];
	FLOAT fMemUsage;
	FLOAT fMemAvailable;
};

struct PLAY_INFO_
{
	DWORD dwScheduleNo;
	char  szScheduleName[MAX_XML_ELEM_LEN];
};

struct DISK_INFO
{
	char  szDiskDesc[MAX_XML_ELEM_LEN];
	FLOAT fDiskUsage;
	FLOAT fDiskAvailable;

};

struct TIMING_PLAN
{
	BYTE bySwitchEnabled;
	BYTE byVolumeEnabled;

};

struct IPC_STATE
{
	DWORD dwID;
	char szOnlineState[MAX_XML_ELEM_LEN];
};

struct TERM_STATE
{
	DWORD dwID;
	char  szTermName[MAX_XML_ELEM_LEN];
	char  szHardwareVersion[MAX_XML_ELEM_LEN];
	char  szSystemVersion[MAX_XML_ELEM_LEN];
	char  szVersion[MAX_XML_ELEM_LEN];
	char  szCondCode[MAX_XML_ELEM_LEN];
	char  szRegTime[MAX_XML_ELEM_LEN];

	char szAddrFormatType[MAX_XML_ELEM_LEN];
	char szHostName[MAX_XML_ELEM_LEN];
	char szIPVersion[MAX_XML_ELEM_LEN];
	char szIPv4[MAX_XML_ELEM_LEN];
	char szIPv6[MAX_XML_ELEM_LEN];

	char szMacAddr[MAX_XML_ELEM_LEN];
	char szServerURL[MAX_XML_ELEM_LEN];
	char szOnlineState[MAX_XML_ELEM_LEN];
	char szAbnormalState[MAX_XML_ELEM_LEN];

	DWORD  dwCpuInfoCount;
	CPU_INFO aCpuInfo[MAX_CPUS_A_TERMINAL];

	DWORD  dwMemInfoCount;
	MEM_INFO aMemInfo[MAX_MEMS_A_TERMINAL];

	DWORD  dwDiskInfoCount;
	DISK_INFO aDiskInfo[MAX_DISK_A_TERMINAL];
	DWORD  dwTemperature;

	

	PLAY_INFO_ struPlayInfo;
	TIMING_PLAN struTimingPlan;

	DWORD dwIPCStateCount;
	IPC_STATE struIPCStateList;

};

/////////////////////////////////////////////////////////////////////////////
// DlgTermState dialog

class CDlgTermState : public CDialog
{
// Construction
public:
	CDlgTermState(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgTermState)
	enum { IDD = IDD_DLG_TERM_STATE };
	CComboBox   m_comAddrFormatType;
	CComboBox	m_comIPVersion;
	CComboBox	m_comOnlineState;
	CComboBox	m_comAbnormalState;
	CString	m_csScheduleName;
	DWORD	m_dwScheduleNo;
	DWORD	m_dwTemperature;
	CString	m_csHardVersion;
	CString	m_SysVersion;
	BOOL	m_bySwitch;
	BOOL	m_byVolum;
	//}}AFX_DATA
	DWORD   m_dwTermID;
	CString m_csTermType;
	CString m_csTermName;

	CString m_csVersion;
	CString m_CondCode;//ÌØÕ÷´úÂë
	CString m_csRegCode;
	CString m_csRegTime;
	
	CString m_csAddrFormatType;
	CString m_csHostName;
	CString m_csIPVersion;
	CString m_csIPv4;
	CString m_csIPv6;

	CString m_csMacAddr;
	CString m_csServerURL;
	CString m_csOnlineState;
	CString m_csAbnormalState;

	CString m_csCpuDesc;
	CString m_csCpuUsage;

	CString m_csMemDesc;
	CString m_csMemUsage;
	CString m_csMemAvailable;

	CString m_csDiskDesc;
	CString m_csDiskUsage;
	CString m_csDiskAvailable;


	CListCtrl* m_pListTerm;
	CListCtrl* m_pListCPU;
	CListCtrl* m_pListMem;
	CListCtrl* m_pListDisk;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgTermState)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgTermState)
		afx_msg void OnRadGetOne();
		afx_msg void OnRadGetMore();
		afx_msg void OnBtnGet();
		afx_msg void OnClickLstTermInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	BOOL OnInitDialog();
	
	DECLARE_MESSAGE_MAP()

	BOOL m_bGetOne;

	DWORD m_dwTermStateCount;
	DWORD m_dwCpuIndex;
	DWORD m_dwMemIndex;
	DWORD m_dwDiskIndex;
	DWORD m_dwTermIndex;
	TERM_STATE* m_paTermState;

	char    m_szRequestURL[REQUEST_URL_LEN];
	char*   m_pXMLParamBuf;
	DWORD   m_dwXMLParamBufLen;
	char*   m_pXMLResultBuf;
	DWORD   m_dwXMLResultBufLen;	
	char    m_szXMLStatus[ISAPI_STATUS_LEN];

private:
	int   m_iDeviceIndex;
    LONG  m_lUserID;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTERMSTATE_H__47A8EA42_AC98_43E9_92BA_CB8E211601D3__INCLUDED_)
