#if !defined(AFX_DLGVEHICLECFG_H__958EC7BE_7DFB_4370_AC77_6EF24D2647A1__INCLUDED_)
#define AFX_DLGVEHICLECFG_H__958EC7BE_7DFB_4370_AC77_6EF24D2647A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVehicleCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVehicleControlCfg dialog

class CDlgVehicleControlCfg : public CDialog
{
// Construction
public:
	CDlgVehicleControlCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVehicleControlCfg)
	enum { IDD = IDD_SUBDLG_VEHICLE_CONTROL_CFG };
	CComboBox	m_UnderVoltPercent;
	CComboBox	m_AdjustTimeCtrl;
	CComboBox	m_ChanCtrl;
	CComboBox	m_BackupFileTypeCtrl;
	CComboBox	m_GpsSpeedUnitCtrl;
	CComboBox	m_GpsRetrieveCtrl;
	CComboBox	m_GpsConnectCtrl;
	CComboBox	m_GpsAdjustCtrl;
	CComboBox	m_TriggerChan4Ctrl;
	CComboBox	m_TriggerChan3Ctrl;
	CComboBox	m_TriggerChan2Ctrl;
	CComboBox	m_TriggerChan1Ctrl;
	CComboBox	m_Electric4Ctrl;
	CComboBox	m_Electric3Ctrl;
	CComboBox	m_Electric2Ctrl;
	CComboBox	m_Electric1Ctrl;
	CTreeCtrl	m_SensorTree;
	CTreeCtrl	m_GpsOsdTree;
	CTreeCtrl	m_treeGpsAlarmout;
	CTreeCtrl	m_GAlarmTree;
	CComboBox	m_ModuleSelectCtrl;
	CComboBox	m_HaltDelayCtrl;
	CComboBox	m_PowerCtrlMode;
	CComboBox	m_WeekdayCtrl;
	int		m_iHour12;
	int		m_iHour11;
	int		m_iHour21;
	int		m_iHour22;
	int		m_Min11;
	int		m_Min12;
	int		m_Min21;
	int		m_Min22;
	int		m_iMaxXAcc;
	int		m_iMaxYAcc;
	int		m_iMaxZAcc;
	BOOL	m_bGAlarmout;
	BOOL	m_bGMonitor;
	BOOL	m_bGCenter;
	BOOL	m_bGVoice;
	BOOL	m_bGJpegCapture;
	BOOL	m_bGpsInvokeAlarmout;
	CString	m_strDownloadServer;
	BOOL	m_bEnableGps;
	int		m_iGpsSpeedLimit;
	BOOL	m_bGpsAlarmMonitor;
	BOOL	m_bGpsUploadCenter;
	BOOL	m_bGpsVoice;
	BOOL	m_bGpsJpegCapture;
	int		m_iGpsInterval;
	BOOL	m_bEnableBackup;
	BOOL	m_bNeedBackup;
	int		m_iBackupDays;
	int		m_iStartMin1;
	int		m_iStartMin2;
	int		m_iStopMinute1;
	int		m_iStopMinute2;
	int		m_iStartHour1;
	int		m_iStartHour2;
	int		m_iStopHour1;
	int		m_iStopHour2;
	BOOL	m_bEnableUnderProtect;
	//}}AFX_DATA

	NET_DVR_MB_POWERCTRLPARA m_struPowerCtrlParam;
	NET_DVR_GSENSORPARA		 m_struGsensorPara;
	NET_DVR_MB_AUTOBACKUPPARA m_struAutoBackParam;
	NET_DVR_MB_GPSPARA		 m_struGpsParam;
	NET_DVR_MB_SENSORINPARA  m_struSensorParam;
	NET_DVR_MB_DOWNLOADSVRPARA m_struDownloadParam;
	LONG m_lServerID;
	void	CreateTree(void);
	DWORD	m_dwDevIndex;
    DWORD	m_dwAlarmOutNum;
    BOOL	m_bGpsAlarmOut[MAX_ALARMOUT_V30];
    BOOL	m_bGSensorAlarmOut[MAX_ALARMOUT_V30];
    DWORD   m_nChannel;
    DWORD   m_lStartChan;
	BOOL	m_bGpsOsdChan[MAX_CHANNUM_V30];
	BOOL	m_bSensorOsdChan[MAX_CHANNUM_V30];


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVehicleControlCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVehicleControlCfg)
	afx_msg void OnSure();
	afx_msg void OnGetautowork();
	afx_msg void OnSetautowork();
	afx_msg void OnSelchangeComboweekday();
	virtual BOOL OnInitDialog();
	afx_msg void OnGetgsensor();
	afx_msg void OnSetgsensor();
	afx_msg void OnGetautobackup();
	afx_msg void OnSetautobackup();
	afx_msg void OnSetsensorin();
	afx_msg void OnSetautodownip();
	afx_msg void OnSetgpscfg();
	afx_msg void OnGetsensorin();
	afx_msg void OnGetgpscfg();
	afx_msg void OnGetautodownip();
	afx_msg void OnChkAlarminInvokeAlarmoutG();
	afx_msg void OnPaint();
	afx_msg void OnClickTreeAlarmOutG(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChkAlarminInvokeAlarmout();
	afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeAddosd(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeSensorin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonExit();
	afx_msg void OnButtonSure();
	afx_msg void OnSelchangeComboChan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVEHICLECFG_H__958EC7BE_7DFB_4370_AC77_6EF24D2647A1__INCLUDED_)
