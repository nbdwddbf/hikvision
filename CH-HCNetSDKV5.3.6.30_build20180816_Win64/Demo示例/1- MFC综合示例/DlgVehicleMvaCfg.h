#if !defined(AFX_DLGVEHICLEMVACFG_H__D0F628BB_3B8B_4659_BFC7_C35D95094E68__INCLUDED_)
#define AFX_DLGVEHICLEMVACFG_H__D0F628BB_3B8B_4659_BFC7_C35D95094E68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVehicleMvaCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVehicleMvaCfg dialog

class CDlgVehicleMvaCfg : public CDialog
{
// Construction
public:
	CDlgVehicleMvaCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVehicleMvaCfg)
	enum { IDD = IDD_SUBDLG_VEHICLE_MVA_CFG };
	CComboBox	m_comboCHN;
	CComboBox	m_comboVehiclePlateType;
	CComboBox	m_comboVehiclePlateColor;
	CComboBox	m_comboVehiclePeccType;
	CComboBox	m_comboRadarTargetType;
	CComboBox	m_comboRadarSpeedUnit;
	CComboBox	m_comboRadarStatus;
	CComboBox	m_comboRadarDir;
	CComboBox	m_comboPlateType;
	CComboBox	m_comboPlateEnvir;
	CComboBox	m_comboPlateDir;
	CComboBox	m_comboCapPicSize;
	CComboBox	m_comboCapPicQuality;
	CComboBox	m_comboCapOptHabit;
	CComboBox	m_comboCapFpsAdjType;
	BOOL	m_bCapPeccType;
	BOOL	m_bCapPeccCap;
	BOOL	m_bPlateTimeOverlay;
	BOOL	m_bPlateResultOverlay;
	BOOL	m_bPlateHintOverlay;
	BOOL	m_bPlateUpload;
	BOOL	m_bRadarEnable;
	BOOL	m_bRadarAlarm;
	BYTE	m_byRadarCapNum;
	BYTE	m_byRadarSensitivity;
	short	m_wRadarOverSpeed;
	BOOL	m_bRadarUpload;
	BOOL	m_bBlackListAlarm;
	BOOL	m_bBlackListCheck;
	BOOL	m_bBlackListHint;
	BOOL	m_bBlackListUpload;
	DWORD	m_dwVehicleChannal;
	CString	m_strVehiclePeccInfo;
	BYTE	m_byVehiclePeccNum;
	float	m_fVehicleRectX;
	float	m_fVehicleRectY;
	float	m_fVehicleRectHight;
	float	m_fVehicleRectWidth;
	BYTE	m_byVehicleBelive1;
	BYTE	m_byVehicleBelive2;
	BYTE	m_byVehicleBelive3;
	BYTE	m_byVehicleBelive4;
	BYTE	m_byVehicleBelive5;
	BYTE	m_byVehicleBelive6;
	BYTE	m_byVehicleBelive7;
	BYTE	m_byVehicleBelive8;
	BYTE	m_byVehicleBelive9;
	BYTE	m_byVehicleBelive10;
	BYTE	m_byVehicleBelive11;
	BYTE	m_byVehicleBelive12;
	BYTE	m_byVehicleBelive13;
	BYTE	m_byVehicleBelive14;
	BYTE	m_byVehicleBelive15;
	BYTE	m_byVehicleBelive16;
	short	m_wSendTime;
	BYTE	m_byVehicleBright;
	BYTE	m_byVehicleCharNum;
	CString	m_strVehiclePlateNumber;
	BYTE	m_byVehicleBelive;
	short	m_wTimeYear;
	BYTE	m_byTimeMonth;
	BYTE	m_byTimeDay;
	BYTE	m_byTimeHour;
	BYTE	m_byTimeMin;
	BYTE	m_byTimeSec;
	short	m_wTimeMsec;
	CString	m_strVehicleCustom;
	CString	m_strTransParam;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVehicleMvaCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVehicleMvaCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetCapCfg();
	afx_msg void OnBtnGetCapCfg();
	afx_msg void OnBtnSetPlateRecgCfg();
	afx_msg void OnBtnGetPlateRecgCfg();
	afx_msg void OnBtnSetRadarCfg();
	afx_msg void OnBtnGetRadarCfg();
	afx_msg void OnBtnSetBlackListCfg();
	afx_msg void OnBtnGetBlackListCfg();
	afx_msg void OnBtnVehicleDataSend();
	afx_msg void OnBtnSetTransParam();
	afx_msg void OnBtnGetTransParam();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	NET_DVR_MOBILE_CAPTUREPIC_CFG m_struCapCfg;
	NET_DVR_MOBILE_PLATE_RECOGCFG m_struPlateRecg;
	NET_DVR_MOBILE_RADAR_CFG m_struRadarCfg;
	NET_DVR_MOBILE_LOCALPLATECHK_CFG m_struBlackListCfg;
	NET_DVR_VEHICLE_CHECK m_struVehicleCheckData;
	LONG m_lServerID;
	DWORD m_dwDevIndex;
	LONG m_lTranHandle;
	LONG m_lChannal;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVEHICLEMVACFG_H__D0F628BB_3B8B_4659_BFC7_C35D95094E68__INCLUDED_)
