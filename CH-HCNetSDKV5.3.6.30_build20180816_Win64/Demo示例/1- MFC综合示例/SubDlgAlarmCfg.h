#pragma once
#include "afxwin.h"


// CSubDlgAlarmCfg dialog

class CSubDlgAlarmCfg : public CDialog
{
	DECLARE_DYNAMIC(CSubDlgAlarmCfg)

public:
	CSubDlgAlarmCfg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgAlarmCfg();

// Dialog Data
public:

	//{{AFX_DATA(CSubDlgAlarmCfg)
	enum { IDD = IDD_SUB_DLG_ALARM_CFG };
	CComboBox	m_comboCopyAnalogAlarmIn;
	CComboBox	m_comboAnalogAlarmIn;
	CComboBox	m_comboAlarmOutGroupNO;
	CComboBox	m_comboAlarmInGroupNO;
	CComboBox m_comboAlarmIn;
	CComboBox m_comboAlarmInType;
	CString m_csAlarmInName;
	BOOL m_bChkAlarmInHandle;
	CComboBox m_comboCopyAlarmIn;
	CComboBox m_comboAlarmOut;
	CComboBox m_comboAlarmOutDelay;
	CComboBox m_comboWeekday;
	CComboBox m_comboCopyDay;
	int m_iHour11;
	int m_iMin11;
	int m_iHour12;
	int m_iMin12;
	int m_iHour21;
	int m_iMin21;
	int m_iHour22;
	int m_iMin22;
	int m_iHour31;
	int m_iMin31;
	int m_iHour32;
	int m_iMin32;
	int m_iHour41;
	int m_iMin41;
	int m_iHour42;
	int m_iMin42;
	int m_iHour51;
	int m_iMin51;
	int m_iHour52;
	int m_iMin52;
	int m_iHour61;
	int m_iMin61;
	int m_iHour62;
	int m_iMin62;
	int m_iHour71;
	int m_iMin71;
	int m_iHour72;
	int m_iMin72;
	int m_iHour81;
	int m_iMin81;
	int m_iHour82;
	int m_iMin82;
	CComboBox m_comboCopyAlarmOut;
	CString	m_csAlarmInIP;
	CString	m_csAlarmInChan;
	CString	m_csAlarmOutChan;
	CString	m_csAlarmOutIP;
	CString	m_csAlarmOutName;
	int		m_iState;
	int		m_iVcaChannel;
	BOOL	m_bChkAnalogAlarmInHandle;
	CString	m_csAnalogAlarmInName;
	UINT	m_uiAnalogAlarmInVoltLower;
	UINT	m_uiAnalogAlarmInVoltUpper;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CSubDlgAlarmCfg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CSubDlgAlarmCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboAlarmIn();
	afx_msg void OnBnClickedChkAlarmInHandle();
	afx_msg void OnBnClickedBtnAlarmOutDayOk();
	afx_msg void OnCbnSelchangeComboAlarmOutWeekday();
	afx_msg void OnCbnSelchangeComboAlarmOut();
	afx_msg void OnBnClickedBtnAlarmOutDayCopy();
	afx_msg void OnBnClickedBtnAlarmOutCopy();
	afx_msg void OnBnClickedBtnAlarmInOk();
	afx_msg void OnBnClickedBtnAlarmOutOk();
	afx_msg void OnBnClickedBtnAlarmInHandle();
	afx_msg void OnBnClickedBtnAlarmInPtz();
	afx_msg void OnBnClickedBtnAlarmInCopy();
	afx_msg void OnBtnSetState();
	afx_msg void OnSelchangeComboAlarminGroupNo();
	afx_msg void OnSelchangeComboAlarmoutGroupNo();
	afx_msg void OnBtnDetectFace();
	afx_msg void OnCbnSelchangeComboAnalogAlarmIn();
	afx_msg void OnBtnAnalogAlarmInOk();
	afx_msg void OnBtnAnalogAlarmInCopy();
	afx_msg void OnChkAnalogAlarmInHandle();
	afx_msg void OnBtnAnalogAlarmInHandle();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	
	int	m_iChanCount;//该设备的预览通道数
	int m_iAnalogChannel;
	int m_iDStartChannel;
	LONG	m_lLoginID;
	LONG	m_lStartChannel;
	BOOL	*m_pbSetAlarmIn;
	BOOL	*m_pbSetAnalogAlarmIn;
	BOOL	*m_pbSetAlarmOut;
	int m_iAlarmInIndex;
	int m_iAnalogAlarmInIndex;
	int m_iCopyAlarmIn;
	int m_iCopyAnalogAlarmIn;
	int m_iAlarmOutIndex;
	int m_iCopyAlarmOut;
	int m_nCopyOutTime;
	NET_DVR_ALARMINCFG_V40 *m_pStruAlarmInCfgV40;
	NET_DVR_ANALOG_ALARMINCFG m_struAnalogAlarmInCfg[MAX_ANALOG_ALARM_WITH_VOLT_LIMIT];
	BOOL *m_pbGetAlarmIn;
	BOOL m_bGetAnalogAlarmIn[MAX_ALARMIN_V30];
	NET_DVR_ALARMOUTCFG_V30 m_struAlarmOutCfg[MAX_ALARMOUT_V30];
	//NET_DVR_IPALARMINCFG m_struIPAlarmInCfg;
	NET_DVR_IPALARMINCFG_V40 *m_pStruIPAlarmInCfgV40;
//	NET_DVR_IPALARMOUTCFG m_struIPAlarmOutCfg;
	NET_DVR_IPALARMOUTCFG_V40 *m_pStruIPAlarmOutCfgV40;

	NET_DVR_IP_ALARM_GROUP_NUM m_struIPAlarmInOutNum;
	NET_DVR_DEVICECFG_V40 m_struDeviceCfg;
	int m_iIPAlarmInGroupNO;
	int m_iIPAlarmOutGroupNO;
	BOOL m_bSupportMultiGroupAlarm; 
	BOOL *m_pbGetAlarmOut;
	DWORD m_dwAlarmInNum;
	DWORD m_dwAnalogAlarmInNum;
	DWORD m_dwAlarmOutNum;

	BOOL TimeTest();
	BOOL CheckInitParam(BOOL bInit = true, int iInGroupNO = 0, int iOutGroupNO = 0);
	void CurCfgUpdate();
	BOOL CfgSetup();
	BOOL GetAlarmInOutGroupNum();
	BOOL GetCurAlarmInCfgByIndex(DWORD dwAlarmInNo);

	int m_iDeviceIndex;
    NET_DVR_HOLIDAY_HANDLE m_struAlarmOutHolidayHandle;
    BOOL GetAlarmOutHolidayHandle(NET_DVR_HOLIDAY_HANDLE &struHolidayHandle);
    BOOL SetAlarmOutHolidayHandle(NET_DVR_HOLIDAY_HANDLE &struHolidayHandle);

    CComboBox m_comboInputType;
    CComboBox m_comboAlarmOutHandle;
};
