
#include "afxwin.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIPCSimpIntellCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIPCSimpIntellCfg dialog

class CDlgIPCSimpIntellCfg : public CDialog
{
// Construction
public:
	CDlgIPCSimpIntellCfg(CWnd* pParent = NULL);   // standard constructor
	~CDlgIPCSimpIntellCfg();

public:
	CRect   m_rcWnd;

	//设备相关参数
	LONG    m_lLoginID;
	int     m_iDeviceIndex;
	LONG    m_lChannel;

	LONG	m_lPlayHandle;

	int		m_iChanCount;
	int		m_iAnaChanCount;
	int     m_iDStartChannel;
	LONG	m_lStartChannel;
    HANDLE  m_hRegisterDrawThread;

// Dialog Data
	//{{AFX_DATA(CDlgIPCSimpIntellCfg)
	enum { IDD = IDD_DLG_IPC_SIMP_INTELL };
	CComboBox	m_comTraverseDetTarget;
	CComboBox	m_comRunDetTarget;
	CComboBox	m_comIntrusionDetTarget;
	CComboBox	m_comboExitDetTarget;
	CComboBox	m_comboEnterDetTarget;
	CComboBox	m_cmbClipRegionNo;
	CComboBox	m_cmbStreamType;
	CComboBox	m_cmbUnattendedNo;
	CComboBox	m_cmbRapidMove;
	CComboBox	m_cmbParkNo;
	CComboBox	m_cmbLoiterNo;
	CComboBox	m_cmbGroupDetectionNo;
	CComboBox	m_cmbAttendedNo;
	CComboBox	m_cmbRegionExitNo;
	CComboBox	m_cmbRegionEntrNo;
	CComboBox	m_cmbGroupNo;
	CComboBox	m_comboPtzLockStatus;
	CComboBox	m_comEnable;
	CComboBox	m_ComboRegionID;
	CComboBox	m_Comnbo_FieldNo;
	CComboBox	m_Combo_LineNo;
	CComboBox	m_Combo_CfgType;
    CComboBox   m_cmbChannel;
	CStatic	m_wndPlay;
	CTreeCtrl	m_treeAlarmOut;
	CTreeCtrl	m_treeChan;
	CComboBox	m_comboWeekday;
	CComboBox	m_comboCopyTime;
	BOOL	m_bChkMonitorAlarm;
	BOOL	m_bChkVoiceAlarm;
	BOOL	m_bChkUploadCenter;
	BOOL	m_bChkInvokeAlarmOut;
	BOOL	m_bChkInvokeJpegCapture;
	BOOL	m_bChkEmapAlarmOut;
	BOOL    m_bChkFocusAlarm;
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
    int m_iZoneIndex;
	BOOL	m_bChkPicToFtp;
    BOOL	m_bChkPicToCloud;
	BOOL	m_bEnable;
	BOOL	m_bAudioAbnormal;
	CString	m_iAudioSen;
	CString	m_iAudioThreshold;
	int		m_iMaxChan;
	int		m_iUsedChan;
	CString	m_iLineSen;
	CString	m_iFieldDuration;
	CString	m_iFieldRate;
	CString	m_iFieldSen;
	CString	m_iCross;
	int     m_iSceneSen;
	BOOL	m_bTraverseDualVca;
	BOOL	m_bFieldDetectionDualVca;
	UINT	m_iDefocusSensortiveLevel;
	BYTE	m_bySensitivity;
	BOOL	m_bChkPTZAlarm;
	BYTE	m_byRegionEntrSensitivity;
	int		m_nAttendedSensitivity;
	int		m_nAttendedTimeThresgold;
	int		m_nGroupObjectOccup;
	int		m_nLoiterSensitivity;
	int		m_nLoiterTimeThreshold;
	int		m_nParkSensitivity;
	int		m_nParkTimeThreshold;
	int		m_nRapidMoveSensitivity;
	int		m_nRegionExitSensitivity;
	int		m_nUnattendedSensitivity;
	int		m_nUnattendedTimeThreshold;
	int		m_nResolutionWidth;
	int		m_nResolutionHeight;
	BOOL	m_bChkUnattendedBaggageTime;
	BOOL	m_bChkAttendedBaggageTime;
	//}}AFX_DATA

public:
	//结构体的部分成员
	BOOL* m_bRecordChan;
	NET_DVR_SCHEDTIME m_struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_V30]; 
    BYTE m_bySceneID[MAX_DAYS][MAX_TIMESEGMENT_V30];
	NET_DVR_HANDLEEXCEPTION_V41* m_pStruAlarmHandleType;
	BOOL* m_pbAlarmOut;
    
    NET_DVR_HOLIDAY_HANDLE m_struHolidayHandle;
	NET_DVR_HOLIDAY_HANDLE_COND m_struHolidayCond;

	//完整的参数
	NET_VCA_TRAVERSE_PLANE_DETECTION m_struLineDetection;
	NET_VCA_FIELDDETECION m_struFieldDetection;
	NET_VCA_DEFOCUSPARAM m_struDefousDetection;
	NET_DVR_AUDIO_EXCEPTION m_struAudioException;
	NET_DVR_SCENECHANGE_DETECTION m_struSceneDetection;//场景变更侦测2013-07-17
    NET_DVR_REGION_ENTRANCE_DETECTION m_struRegionEntrDetection;//进入区域侦测
    NET_DVR_REGION_EXITING_DETECTION m_struRegionExitDetection;
    NET_DVR_LOITERING_DETECTION m_struLoiterDetection;
    NET_DVR_GROUP_DETECTION m_struGroupDetection;
    NET_DVR_RAPIDMOVE_DETECTION m_struRapidMove;
    NET_DVR_PARKING_DETECTION   m_struParkDetection;
    NET_DVR_UNATTENDED_BAGGAGE_DETECTION    m_struUnattended;
    NET_DVR_ATTENDED_BAGGAGE_DETECTION  m_struAttended;
    NET_DVR_EVENT_TRIGGER   m_struEventTrigger;
    NET_DVR_EVENT_SCHEDULE  m_struEventSchedule;
    NET_DVR_REGION_CLIP_CFG m_struClipCfg;

	LONG m_lHandle;
	void OnGetPtzLockInfo();
	NET_DVR_PTZ_LOCKCFG m_struPtzLockCfg;
	NET_DVR_PTZLOCKINFO_COND m_struPtzLockInfoCond;
	NET_DVR_PTZLOCKINFO m_struPtzLockInfo;
	LPNET_DVR_PTZLOCKINFO m_pStruPtzLockInfo;
	static DWORD WINAPI GetPtzLockInfoThread(LPVOID lpPtzLockInfo);
	void SetPtzLockTime(const int i);

    long m_nMaxWidth;
    long m_nMaxHeight;
	//保存当前的索引值
	int m_iLineNo;
	int m_iFieldNo;

	//播放
	void Play();
	void F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser);

	//填写当前声音强度
	void SetAudioDecibel(const int &i);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIPCSimpIntellCfg)
	public:
		virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	//当前已经画的点的个数
	DWORD m_dwPosNum; 
	BOOL m_bCloseIn;
	BOOL m_bMouseMovePolygon;
	BOOL m_bMouseMove;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIPCSimpIntellCfg)
	afx_msg void OnClickTreeChan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedBtnAlarmInTimeOk();
	afx_msg void OnCbnSelchangeComboAlarminWeekday();
	afx_msg void OnBnClickedBtnAlarminTimeCopy();
	afx_msg void OnBnClickedChkAlarminInvokeAlarmout();
	afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCfgTypeChanged();
    afx_msg void OnChannelChanged();
	afx_msg void OnPaint();
	afx_msg void OnBtnSavecfg();
    afx_msg void OnBtnExit();
    afx_msg void OnBtnRefresh();
	afx_msg void OnLineNoChanged();
	afx_msg void OnFieldNoChanged();
	afx_msg void OnBtnClearpic();
	afx_msg void OnBtnPtzLockstatusSet();
	afx_msg void OnBtnRegionEntrRefresh();
	afx_msg void OnBtnRegionEntrSave();
	afx_msg void OnBtnRegionExitRefresh();
	afx_msg void OnBtnRegionExitSave();
	afx_msg void OnBtnLoiterRefresh();
	afx_msg void OnBtnLoiterSave();
	afx_msg void OnBtnGroupRefresh();
	afx_msg void OnBtnGroupSave();
	afx_msg void OnBtnRapidMoveRefresh();
	afx_msg void OnBtnRapidMoveSave();
	afx_msg void OnBtnParkRefresh();
	afx_msg void OnBtnParkSave();
	afx_msg void OnBtnUnattendedRefresh();
	afx_msg void OnBtnUnattendedSave();
	afx_msg void OnBtnAttendedRefresh();
	afx_msg void OnBtnAttendedSave();
	afx_msg void OnSelchangeCmbAttendedNo();
	afx_msg void OnSelchangeCmbGroupNo();
	afx_msg void OnSelchangeCmbLoiterNo();
	afx_msg void OnSelchangeCmbParkNo();
	afx_msg void OnSelchangeCmbRapidMove();
	afx_msg void OnSelchangeCmbRegionEntrNo();
	afx_msg void OnSelchangeCmbRegionExitNo();
	afx_msg void OnSelchangeCmbUnattendedNo();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	virtual BOOL OnInitDialog();
	BOOL TimeTest();
	void CreateTree();

	//显示数据
	void ShowData();
	//保存界面数据
	void SaveUIData();

    //add channel Info
    void AddChanInfo();
    void AddGroupNoInfo();
	//获取参数
	void GetLineDetection();
	void GetFieldDetection();
	void GetDefousDetection();
	void GetAudioException();
	void GetSceneDetection();
	void SaveLineDetection();
	void SaveFieldDetection();
	void SaveDefousDetection();
	void SaveAudioException();
	void SaveSceneDetection();

    void GetRegionEntrDetection();
    void SaveRegionEntrDetection();
    void GetRegionExitDetection();
    void SaveRegionExitDetection();
    void GetLoiterDetection();
    void SaveLoiterDetection();
    void GetGroupDetection();
    void SaveGroupDetection();
    void GetRapidMoveDetection();
    void SaveRapidMoveDetection();
    void GetParkDetection();
    void SaveParkDetection();
    void GetUnattendedDetection();
    void SaveUnattendedDetection();
    void GetAttendedDetection();
    void SaveAttendedDetection();
    void GetClipCfg();
    void SaveClipCfg();

    BOOL GetEventTrigger(DWORD dwCommand);
    BOOL SetEventTrigger(DWORD dwCommand);
    BOOL GetEventSchedule(DWORD dwCommand);
    BOOL SetEventSchedule(DWORD dwCommand);
	BOOL GetSMDHolidayCfg();
    BOOL SetSMDHolidayCfg();

	//
	BOOL PreDrawPolygonMsg(MSG* pMsg, CPoint &pt, NET_VCA_POLYGON &struRegion);
    BOOL PreDrawRectMsg(MSG* pMsg, CPoint &pt, NET_VCA_POLYGON &struRegion);
	BOOL PreDrawLineMsg(MSG* pMsg, CPoint &pt);

	BOOL ConvertHandleExceptionV40ToV41(NET_DVR_HANDLEEXCEPTION_V40 *pStruExpV40, NET_DVR_HANDLEEXCEPTION_V41 *pStruExpV41, BOOL bV40ToV41);

	void F_DrawLine(HDC hDc);
	void F_DrawPolygon(HDC hDc, NET_VCA_POLYGON &struRegion);

	//保存音频实时上传连接的handle
	int m_lAudioHandle;
    char m_szStatusBuf[ISAPI_STATUS_LEN];
public:
    DWORD m_dwPreset;
    CComboBox m_combDirection;
    BOOL m_bHumanMisFlineDetect;
    BOOL m_bHumanMisFFiledDetect;
    BOOL m_bHumanMisFRegionEDetect;
    BOOL m_bHumanMisFRegionExitDetect;
    CString m_strFaceLibID;
    CComboBox m_comSceneID1;
    CComboBox m_comSceneID2;
    CComboBox m_comSceneID3;
    CComboBox m_comSceneID4;
    CComboBox m_comSceneID5;
    CComboBox m_comSceneID6;
    CComboBox m_comSceneID7;
    CComboBox m_comSceneID8;
    BOOL m_bVehicleField;
    BOOL m_bVehicleLine;
    BOOL m_bVehicleEnter;
    BOOL m_bVehicleExit;
    BYTE m_bTraverseWhiteLightDurationTime;
    BYTE m_bIntrusionWhiteLightDurationTime;
    BOOL m_bTraverseDetTargetAll;
    BOOL m_bTraverseDetTargetHuman;
    BOOL m_bTraverseDetTargetVerhicle;
    BOOL m_bIntrusionDetTargetAll;
    BOOL m_bIntrusionDetTargetHuman;
    BOOL m_bIntrusionDetTargetVerhicle;
    BYTE m_bTraverseDetTarget;
    BYTE m_bIntrusionDetTarget;
    int m_iSensitivityLevel;
    int m_iDurationTime;
    int m_iMinTriggerTime;
    int m_iLinkageTime;
    int m_iFilterTime;
};

BOOL IsCrossLine(NET_VCA_POLYGON *struRuleRegion);
BOOL F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2);
BOOL IsValidArea(LPNET_VCA_POLYGON lpstruPolygon);
BOOL F_IsStraightLine(NET_VCA_POLYGON *lpstruPolygon);
BOOL F_IsACrossLine(NET_VCA_POLYGON *alarm_region);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


