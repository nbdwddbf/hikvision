#if !defined(AFX_DLGITSIOINCFG_H__2CF64D33_A641_4122_B079_D81DEEBC36DA__INCLUDED_)
#define AFX_DLGITSIOINCFG_H__2CF64D33_A641_4122_B079_D81DEEBC36DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgITSIOinCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgITSIOinCfg dialog

class CDlgITSIOinCfg : public CDialog
{
// Construction
public:
	CDlgITSIOinCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgITSIOinCfg)
	enum { IDD = IDD_DLG_ITS_IOIN_CFG };
	CComboBox	m_comOfflineDet;
	CComboBox	m_comOffLine;
	CIPAddressCtrl	m_ReaderDevIP;
	CIPAddressCtrl	m_LEDDevIP;
	CComboBox	m_comScreenUse;
	CComboBox	m_comLedScreenType;
	CComboBox	m_comLedExteMode;
	CComboBox	m_comLedDisMode;
	CComboBox	m_comLedCardType;
	CComboBox	m_comGateWayIsData;
	CComboBox	m_comDevType3;
	CComboBox	m_comRelativeIndex2;
	CComboBox	m_comLaneID2;
	CComboBox	m_comDevType2;
	CComboBox	m_comRelativeIndex;
	CListCtrl	m_lstExDevStatus;
	CComboBox	m_comLaneID;
	CComboBox	m_comDevType;
	BYTE	m_byRelativeIndex;
	CString	m_csDevName;
	BYTE	m_byGateWayDevCode;
	BYTE	m_byGateWayRS485No;
	CString	m_csLEDCustInfo;
	BYTE	m_byLEDDevCode;
	DWORD	m_dwLEDDevPort;
	BYTE	m_byLEDRs485No;
	DWORD	m_dwReaderDevPort;
	BYTE	m_byDetCycle;
	BYTE	m_byDevCtrlCode;
	BYTE	m_byDevCode;
	BYTE	m_byManualIssuedData;
	BOOL    m_bManualIssuedData;
	BYTE	m_byEnissuedCode;
	DWORD	m_dwLEDScreenH;
	DWORD	m_dwLEDScreenW;
	BYTE	m_byEntrDetCycle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgITSIOinCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgITSIOinCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGetItsExdevstatus();
	afx_msg void OnSelchangeComboDevType();
	afx_msg void OnBtnSetItsExdevcfg();
	afx_msg void OnBtnGetItsExdevcfg();
	afx_msg void OnSelchangeComboDevType2();
	afx_msg void OnSelchangeComboDevType3();
	afx_msg void OnSelchangeComboLedExternalMode();
	afx_msg void OnBtnSetEntrncedet();
	afx_msg void OnBtnGetEntrncedet();
	afx_msg void OnBtnControlEntrancedev();
	afx_msg void OnBtnControlEnissuedDatadel();
	afx_msg void OnBtnSaveItsExdevcfg();
	afx_msg void OnSelchangeComboRelativeIndex2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG    m_lUserID;
    LONG    m_iDevIndex;
    DWORD   m_dwChannel;
	LONG    m_lHandle;
	BOOL	m_bGetNext;
	HANDLE	m_hGetInfoThread;
	int		m_iStruCount;

	NET_DVR_EXTERNAL_DEVCOND m_struExternalDevCond;
	NET_DVR_EXTERNAL_DEVSTATUS m_struDevStatus;
	LPNET_DVR_EXTERNAL_DEVSTATUS m_pStruDevStatus;
	//NET_DVR_EXTERNAL_DEVCFG m_struExternalDevCFG;
	LPNET_DVR_EXTERNAL_DEVCFG m_pStruExternalDevCFG;
	LPNET_DVR_EXTERNAL_DEVCOND m_pStruExternalDevCond;

public:
	static DWORD WINAPI GetVehInfoThread(LPVOID lpVehInfo);
	void AddDevStatusToDlg(int iItem, LPNET_DVR_EXTERNAL_DEVSTATUS lpInter);
	void SetExternalDevCond(int iIndex);
	void ExternalDevCFGToDlg(BOOL bSave);
	~CDlgITSIOinCfg();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGITSIOINCFG_H__2CF64D33_A641_4122_B079_D81DEEBC36DA__INCLUDED_)
