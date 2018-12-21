#if !defined(AFX_DLGALARMHOSTEXTERNALDEVSTATE_H__3AE3F998_9AD0_4A1E_B161_C1890C12D2A3__INCLUDED_)
#define AFX_DLGALARMHOSTEXTERNALDEVSTATE_H__3AE3F998_9AD0_4A1E_B161_C1890C12D2A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostExternalDevState.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostExternalDevState dialog

class CDlgAlarmHostExternalDevState : public CDialog
{
// Construction
public:
	CDlgAlarmHostExternalDevState(CWnd* pParent = NULL);   // standard constructor
 
// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostExternalDevState)
	enum { IDD = IDD_DLG_ALARMHOST_EXTERNAL_DEVICE_STATE };
	CComboBox	m_cmDevType;
	CListCtrl	m_listState;
	CComboBox	m_cmSlotIndex;
	CComboBox	m_cm485ChanIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostExternalDevState)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostExternalDevState)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboExternalDeviceType();
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	int m_iDeviceIndex;
	long m_lUserID;
	NET_DVR_ALARMHOST_EXTERNAL_DEVICE_STATE  m_struExternalDeviceState;
	NET_DVR_ALARMHOST_UPS_STATE m_struUpsState;		//UPS状态
	NET_DVR_ALARMHOST_SWITCH_POWER_SUPPLY_STATE m_struSwitchPowerState;//开关电源状态
	NET_DVR_ALARMHOST_GAS_DETECTOR_STATE m_struGasDetectorState;//气体检测系统状态
	NET_DVR_ALARMHOST_TEMP_HUMI_SENSOR_STATE m_struTempHumiSensorState;//温湿度传感器状态
	NET_DVR_ALARMHOST_AIRCONDITION_STATE m_struAirConditionState;//空调状态
	NET_DVR_ALARMHOST_ELECTRICITY_STATE m_struElectricityState;//电量表状态
	NET_DVR_ALARMHOST_TRANSFORMER_TEMP_STATE m_struTransformaterTempState; //变压器温显表状态
	NET_DVR_ALARMHOST_WATERLEVEL_SENSOR m_struWaterLevelSensor;//水位传感器
    NET_DVR_ALARMHOST_DUSTNOISE_SENSOR m_struDustNoiseSensor;//扬尘噪声传感器
    NET_DVR_ALARMHOST_ENVIRONMENTAL_LOGGER m_struEnvironmentLogger;//环境采集仪
	NET_DVR_ALARMHOST_ABILITY m_struAbility;
	
	void SetGasDetectSystemState() ;
	void SetTempHumiSensorState() ;
	void SetAirConditionState() ;
	void SetSwitchPowerState();
	void SetUpsState();
	void SetElectricityState() ;
	void SetTransformaterState();
	void SetWaterLevelSensorParam();
	void SetDustNoiseSensorParam();
	void SetEnvironmentLoggerParam();
	void SetInfoToDlg();
	char m_sTemp[128];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTEXTERNALDEVSTATE_H__3AE3F998_9AD0_4A1E_B161_C1890C12D2A3__INCLUDED_)
