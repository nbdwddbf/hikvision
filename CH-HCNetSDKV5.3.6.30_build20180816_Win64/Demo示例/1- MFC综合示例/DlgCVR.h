#include "afxwin.h"
#if !defined(AFX_DLGCVR_H__6C7FA515_0BBA_4CA7_9DFF_E4B253A226DC__INCLUDED_)
#define AFX_DLGCVR_H__6C7FA515_0BBA_4CA7_9DFF_E4B253A226DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCVR.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCVR dialog

#define ONE_KEY_CONFIG_CVR_TIMER		WM_USER+100		//timer for one key config CVR
#define ONE_KEY_CONFIG_SAN_TIMER		WM_USER+101		//timer for one key config SAN

class CDlgCVR : public CDialog
{
// Construction
public:
	CDlgCVR(CWnd* pParent = NULL);   // standard constructor

	inline BOOL ValidIPv6(BYTE *ip);

// Dialog Data
	//{{AFX_DATA(CDlgCVR)
	enum { IDD = IDD_DLG_CVR };
	CComboBox	m_cmbWorkMode;
	CListCtrl	m_lstAddedMachine;
	CListCtrl	m_lstFC;
	CComboBox	m_cmbAccModeIscsi;
	CComboBox	m_cmbFCAccMode;
	CComboBox	m_cmbDelType;
	CComboBox	m_cmbAddType;
	CString	m_strStatus;
	UINT	m_dwMaxPCNum;
	BOOL	m_bDelData;
	BOOL	m_bEnableDataCallback;
	CString	m_strIP;
	CString	m_strCardSN;
	CString	m_strClientIP;
	INT		m_iFCChannel;
	UINT	m_dwFCID;
	UINT	m_dwLunIDFC;
	UINT	m_dwLunIDIscsi;
	UINT	m_dwTargetID;
	UINT	m_dwLunIDNas;
	CString	m_strPassword;
	BOOL	m_bDisableBackup;
    CString	m_csRelocationAddr;
    short	m_wRelocationPort;
    CString	m_csStreamIDN0;
	DWORD   m_dwN0Chan;
	int		m_nOnlineUserNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCVR)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCVR)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonRestartService();
	afx_msg void OnButtonOneKeyCfgCVR();
	afx_msg void OnButtonOneKeyCfgSAN();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnButtonGetMaxPcNum();
	afx_msg void OnButtonSetMaxPcNum();
	afx_msg void OnButtonGetDataCallback();
	afx_msg void OnButtonSetDataCallback();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDel();
	afx_msg void OnButtonOpenIscsi();
	afx_msg void OnButtonCloseIscsi();
	afx_msg void OnButtonOpenFc();
	afx_msg void OnButtonCloseFc();
	afx_msg void OnButtonCreateNas();
	afx_msg void OnButtonDelNas();
	afx_msg void OnButtonGetFc();
	afx_msg void OnButtonGetAddedMachine();
	afx_msg void OnButtonGetWorkMode();
	afx_msg void OnButtonSetWorkMode();
    afx_msg void OnBtnGetRelocate();
	afx_msg void OnBtnGetOnlineUserCfg();
    afx_msg LRESULT OnMsgGetOneKeyResultFinish(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


public:
	LONG m_lUserID;
	int m_iDevIndex;

	LONG m_lOneKeyCfgCVRHandle;
	LONG m_lOneKeyCfgSANHandle;
	LONG m_lOneKeyCfgTimer;

	NET_DVR_MACHINE_MAX_NUM_CFG m_struMachineMaxNum;
	NET_DVR_DATA_CALLBACK_CFG	m_struDataCallback;

	BOOL m_bFCGeting;
	BOOL m_bAddedMachineGeting;
	LONG m_hRemoteConfig;
	LONG m_hAddedMachineRemoteConfig;
	HANDLE m_hThread;
	HANDLE m_hAddedMachineThread;
	int m_iFCNum;
	int m_iMachineNum;
    CComboBox m_cmbRAIDType;
    CComboBox m_cmbSpareRAIDProportion;
    int m_iPicQuota;
    CComboBox m_cmbRAIDTypeSAN;
    CComboBox m_cmbSpareRAIDProportionSAN;

    CString m_csFilePath;
    HANDLE  m_hDownloadThread;
    BOOL    m_bDownLoading;
    LONG    m_lDownloadHandle;

    CString m_csClusterFilePath;
    HANDLE  m_hClusterDownloadThread;
    BOOL    m_bClusterDownLoading;
    LONG    m_lClusterDownloadHandle;

    CString m_csSqlFilePath;
    HANDLE  m_hSqlDownloadThread;
    BOOL    m_bSqlDownLoading;
    LONG    m_lSqlDownloadHandle;

    afx_msg void OnBnClickedButtonDownloadLogFile();
    afx_msg void OnBnClickedBtnBrowse();
    CString m_strUserName;
    afx_msg void OnBnClickedButtonAddV50();
    afx_msg void OnBnClickedBtnBrowseCluster();
    afx_msg void OnBnClickedButtonDownloadClusterMaintenanceLog();
    CComboBox m_comboClusterLogMode;
    afx_msg void OnBnClickedBtnBrowseSql();
    afx_msg void OnBnClickedButtonDownloadSql();
    afx_msg void OnBnClickedButtonOneKeyCfgv51();

    void ProcGetOneKeyResult(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
    void GetOneKeyResultItem(const NET_DVR_ONE_KEY_RESULT_V51 &Item);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCVR_H__6C7FA515_0BBA_4CA7_9DFF_E4B253A226DC__INCLUDED_)
