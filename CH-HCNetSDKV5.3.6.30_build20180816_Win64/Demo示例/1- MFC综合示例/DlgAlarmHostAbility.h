#if !defined(AFX_DLGALARMHOSTABILITY_H__E8D32A35_962E_498D_A31A_C233C03FFEEF__INCLUDED_)
#define AFX_DLGALARMHOSTABILITY_H__E8D32A35_962E_498D_A31A_C233C03FFEEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostAbility dialog

class CDlgAlarmHostAbility : public CDialog
{
// Construction
public:
	CDlgAlarmHostAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostAbility)
	enum { IDD = IDD_DLG_ALARMHOST_ABILITY };
	CListCtrl	m_listSubsystemEvent;
	CListCtrl	m_listSubsystemArmType;
	CListCtrl	m_listFaultType;
	CListCtrl	m_listOverallEvent;
	int		m_iAudioOutNum;
	int		m_iElectrolLockNum;
	int		m_iExpandAlarmInNum;
	int		m_iExpandAlarmOutNum;
	int		m_iExpandRs485Num;
	int		m_iExpandSensorNum;
	int		m_iFullDuplexRs485Num;
	int		m_iLocalAlarmInNum;
	int		m_iLocalAlarmOutNum;
	int		m_iLocalRs485Num;
	int		m_iLocalSensorNum;
	int		m_iMobileGateNum;
	int		m_iSirenNum;
    BYTE     m_byAlarmLampNum;
	int		m_iSubSystemNum;
	int		m_iTotalAlarmOutNum;
	int		m_iTotalRs485Num;
	int		m_iTotalSensorNum;
	int		m_iTotalAlarmInNum;
	BOOL	m_bAlarminType1;
	BOOL	m_bAlarminType2;
	BOOL	m_bAlarminType3;
	BOOL	m_bAlarminType4;
	BOOL	m_bAlarminType5;
	BOOL	m_bSupportAlarmDelay;
	BOOL	m_bSupportArrayBypass;
	BOOL	m_bSupportDetector;
	BOOL	m_bSupportSens;
	int		m_iBoardUserNums;
	int		m_iNetUserNums;
	int		m_iOperateUserNums;
	BOOL	m_bAlarminType6;
	BOOL	m_bAlarminType7;
	BOOL	m_bAlarminType8;
	BOOL	m_bAlarminType9;
	DWORD	m_dw3GCenter;
	DWORD	m_dwAudioNum;
	DWORD	m_dwCenterNum;
	DWORD	m_dwGPRSCenter;
	DWORD	m_dwNetCenterNum;
	DWORD	m_dwTelCenterNum;
	BYTE	m_byAnalogChan;
	BYTE	m_byDigitalChan;
	BYTE	m_byPublicSystemNum;
	BOOL	m_bSubsystemEnable;
	BOOL	m_bSubSystemTime;
	BOOL	m_bTriggerOffAlarmout;
	BOOL	m_bTriggerOnAlarmout;
	BOOL	m_bArmZoom;
	int		m_iPublicSubsystemAsssociateSubsystem;
	BOOL	m_bSubsystemAutoArm;
	BOOL	m_bKeyzoomOperateSubsystem;
	BOOL	m_bReportSoundOnKeyboard;
	BOOL	m_bFaultAssociateSound;
	BOOL	m_bSearchStatus;
	BOOL	m_bExternalSubsystemCfg;
	int		m_iOverallKeyboard;
	BOOL	m_bConfigFile;
	BOOL	m_bFaultLinakgeLed;
	BYTE	m_by485SlotNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostAbility)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    NET_DVR_ALARMHOST_ABILITY m_struAlarmHostAbility;

    void SetAlarmHostAbilityToWnd(NET_DVR_ALARMHOST_ABILITY& struAlarmHostAlility);
protected:
	void InitListWnd();
	void InitOverallEventList();
	void InitSubsystemEventList();
	void InitFaultTypeList();
	void InitAlarmTypeList();
public:
    BOOL m_bAlarminType10;
    BOOL m_bAlarminType11;
    BOOL m_bAlarminType12;
    BOOL m_bAlarminType13;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTABILITY_H__E8D32A35_962E_498D_A31A_C233C03FFEEF__INCLUDED_)
