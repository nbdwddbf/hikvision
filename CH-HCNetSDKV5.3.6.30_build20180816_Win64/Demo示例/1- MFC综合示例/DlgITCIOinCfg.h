#if !defined(AFX_DLGITCIOINCFG_H__434E8B9F_B761_43D5_BCE5_1D8A8EDE7D8D__INCLUDED_)
#define AFX_DLGITCIOINCFG_H__434E8B9F_B761_43D5_BCE5_1D8A8EDE7D8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgITCIOinCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgITCIOinCfg dialog

class CDlgITCIOinCfg : public CDialog
{
// Construction
public:
	CDlgITCIOinCfg(CWnd* pParent = NULL);   // standard constructor
	~CDlgITCIOinCfg();
// Dialog Data
	//{{AFX_DATA(CDlgITCIOinCfg)
	enum { IDD = IDD_DLG_ITC_IOIN_CFG };
	CComboBox	m_comOperateTypeVeh;
	CComboBox	m_comDelCond;
	CComboBox	m_comTriggerMode;
	CComboBox   m_comCtrlMode;
	CComboBox	m_comPlateTypeTemp;
	CComboBox	m_comPlateColorTemp;
	CComboBox	m_comListTypeTemp;
	CComboBox	m_comListTypeVeh;
	CListCtrl	m_lstVehicle;
	CComboBox	m_comLampLaneNo;
	CComboBox	m_comLampCtrl;
	CComboBox	m_comPlateType;
	CComboBox	m_comPlateColor;
	CComboBox	m_comOperateType;
	CComboBox	m_comLaneNo;
	CComboBox	m_comGateCtrl;
	CComboBox	m_comVehicleControl;
	CComboBox	m_comRelayNum;
	CComboBox	m_comRelayInfo;
	CComboBox	m_comLane;
	CComboBox	m_comIOInNum;
	CComboBox	m_comGateType;
	CComboBox	m_comGateSingleIO;
	CComboBox	m_comDelListType;
	BOOL	m_bAlarmHost;
	BOOL	m_bArm;
	BOOL	m_bCard;
	BOOL	m_bEnable;
	BOOL	m_bEpolice;
	BOOL	m_bHVT;
	BOOL	m_bNoMatching;
	BOOL	m_bNoPlateColor;
	BOOL	m_bPlateColor;
	BOOL	m_bRelay;
	BOOL	m_bRS485;
	BOOL	m_bSingleIO;
	CString	m_csCardNum;
	CString	m_csPlateNum;
	CString	m_csCardNumVeh;
	CString	m_csPlateNumVeh;
	CString	m_csCardNoTemp;
	CString	m_csLicenseTemp;
	DWORD	m_dwDataIndexTemp;
	COleDateTime	m_startDate;
	COleDateTime	m_startTime;
	COleDateTime	m_stopDate;
	COleDateTime	m_stopTime;
	DWORD	m_startMilliSec;
	DWORD	m_stopMilliSec;
	BOOL	m_bCheckStartTime;
	BOOL	m_bCheckStopTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgITCIOinCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgITCIOinCfg)
	afx_msg void OnBtnGetEntrance();
	afx_msg void OnBtnSetEntrance();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboLane();
	afx_msg void OnSelchangeComboRelayNum();
	afx_msg void OnSelchangeComboVehicleControl();
	afx_msg void OnSelchangeComboIoinNo();
	afx_msg void OnBtnGateCtrl();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnLampCtrl();
	afx_msg void OnBtnVehicleControl();
//	afx_msg void OnClickListVehicle(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSyncVehicleControl();
	afx_msg void OnBtnSendVehData();
	afx_msg void OnBtnStopVehData();
	afx_msg void OnBtnCreateLink();
	afx_msg void OnSelchangeComboDelCond();
	afx_msg void OnSelchangeComboOperateType();
	afx_msg void OnBtnSaveEntrance();
	afx_msg void OnCheckStartTime();
	afx_msg void OnCheckStopTime();
	afx_msg void OnSelchangeComboOperateTypeVeh();
	afx_msg void OnDblclkListVehicle(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void CurCfgUpdate();
	static DWORD WINAPI GetVehInfoThread(LPVOID lpVehInfo);
	void AddVehInfotoDlg(int iItem, LPNET_DVR_VEHICLE_CONTROL_LIST_INFO lpInter);
	void AnalysisTime(CString strTime);
	void ListTest();
	LONG m_lServerID;
	BYTE m_byIOInNum;
	BYTE m_byRelayNum;
	LONG m_lHandle;
	BOOL	m_bGetNext;
	HANDLE	m_hGetInfoThread;
	int		m_iStruCount;
	int		m_iItem;
	LONG    m_lSyncVehHandle;
	BOOL m_bCheckSet;

	NET_DVR_BARRIERGATE_COND m_struGateCond;
	NET_DVR_ENTRANCE_CFG m_struEntrance;
	NET_DVR_BARRIERGATE_CFG m_struGateCFG;
	NET_DVR_VEHICLE_CONTROL_DELINFO m_struDelVehicleInfo;
	NET_DVR_GATELAMP_INFO m_struLampCtrl;
	NET_DVR_VEHICLE_CONTROL_COND m_struVehCond;
	LPNET_DVR_VEHICLE_CONTROL_LIST_INFO m_pStruVehInfo;
	NET_DVR_VEHICLE_CONTROL_LIST_INFO m_struVehInfo;
	NET_DVR_TIME_V30 m_struTime;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGITCIOINCFG_H__BE93276C_208E_4C82_91C7_2975281DDE23__INCLUDED_)
