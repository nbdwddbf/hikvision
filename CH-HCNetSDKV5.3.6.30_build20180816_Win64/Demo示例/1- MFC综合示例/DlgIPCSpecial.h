#if !defined(AFX_DLGIPCSPECIAL_H__25057DA2_3A6C_420B_8613_1113541AA449__INCLUDED_)
#define AFX_DLGIPCSPECIAL_H__25057DA2_3A6C_420B_8613_1113541AA449__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIPCSpecial.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIPCSpecial dialog

class CDlgIPCSpecial : public CDialog
{
// Construction
public:
	CDlgIPCSpecial(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgIPCSpecial();

// Dialog Data
	//{{AFX_DATA(CDlgIPCSpecial)
	enum { IDD = IDD_DLG_IPC_SPECIAL };
	CComboBox	m_comboRealTimeOutput;
	CListBox	m_listFishEyeCallback;
	CComboBox	m_comboPtzChannel;
	CComboBox	m_comboStreamMode;
	CComboBox	m_comboTrackType;
	CComboBox	m_comboPresetNo;
	CStatic	m_staNote;
	CComboBox	m_comboWeekday;
	CComboBox	m_comboPtzPreset;
	CComboBox	m_comboMotionTrackGet;
	CComboBox	m_comboMotionTrackSet;
	CListCtrl	m_listGetPreCruiseiInfo;
	CListCtrl	m_listGetPresetInfo;
	CListCtrl	m_listPresetInfo;
	CComboBox	m_comboCurisePreset;
	CComboBox	m_comboFECuriseCmd;
	CComboBox	m_comboFECCmd;
	CComboBox	m_comboFishEyeControlCommand;
	CComboBox	m_comboFishEyeMountType;
	CComboBox	m_comboFishEyeConnectMode;
	CComboBox	m_comboWpsConType;
	CComboBox	m_comboWirelessId;
	CComboBox	m_comboAuxAlarmType;
	CComboBox	m_comboAuxAlarmId;
	CTreeCtrl	m_treeAlarmOut;
	CComboBox	m_comboCmd;
	DWORD	m_dwDeadPixelX;
	DWORD	m_dwDeadPixelY;
	DWORD	m_dwDelayTime;
	BYTE	m_byWirelessIndex;
	BOOL	m_bChkMonitorAlarm;
	BOOL	m_bChkAudioAlarm;
	BOOL	m_bChkReportCenter;
	BOOL	m_bChkInvokeAlarmOut;
	BOOL	m_bChkInvokeJpegCapture;
	BOOL	m_bChkPicFtp;
	BOOL	m_bChkHanleAlarm;
	BOOL	m_bChkRecordEn;
	CString	m_csAlarmName;
	BOOL	m_bChkWirelessLight;
	BOOL	m_bChkWpsEn;
	CString	m_csAPPin;
	CString	m_csDevPin;
	CString	m_csWpsEssid;
	DWORD	m_dwPtzFishEyeX;
	DWORD	m_dwPtzFishEyeY;
	DWORD	m_dwFEChannelNum;
	DWORD	m_dwCruiseChannelNum;
	int		m_iPresetNum;
	int		m_iPtzCruiseNum;
	int		m_iPresetGroupNum;
	int		m_iPreCruiseGroupNum;
	int		m_iPresetGetGroupNum;
	int		m_iPreGetCruiseGroupNum;
	BYTE	m_byWirelessID;
	int		m_iHour11;
	int		m_iHour12;
	int		m_iHour21;
	int		m_iHour22;
	int		m_iHour31;
	int		m_iHour32;
	int		m_iHour41;
	int		m_iHour42;
	int		m_iHour51;
	int		m_iHour52;
	int		m_iHour61;
	int		m_iHour62;
	int		m_iHour71;
	int		m_iHour72;
	int		m_iHour81;
	int		m_iHour82;
	int		m_iMin11;
	int		m_iMin12;
	int		m_iMin21;
	int		m_iMin22;
	int		m_iMin31;
	int		m_iMin32;
	int		m_iMin41;
	int		m_iMin42;
	int		m_iMin51;
	int		m_iMin52;
	int		m_iMin61;
	int		m_iMin62;
	int		m_iMin71;
	int		m_iMin72;
	int		m_iMin81;
	int		m_iMin82;
	CString	m_strPresetName;
	float	m_fPtzPosX;
	float	m_fPtzPosY;
	BOOL	m_bRealTimeOutput;
	BOOL	m_bMobileDev;
	DWORD	m_dwSerialNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIPCSpecial)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIPCSpecial)
	afx_msg void OnBtnShutterComp();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnIpcOnepushFocus();
	afx_msg void OnBtnIpcResetLens();
	afx_msg void OnBtnRemotecontrolAlarm();
	afx_msg void OnBtnRemotecontrolDisalarm();
	afx_msg void OnBtnRemotecontrolStudy();
	afx_msg void OnBtnWirelessStudy();
	afx_msg void OnBtnGetAuxalarm();
	afx_msg void OnBtnSetAuxalarm();
	afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSaveAuxAlarm();
	afx_msg void OnSelchangeComboAuxAlarmId();
	afx_msg void OnSelchangeComboAuxalarmType();
	afx_msg void OnSelchangeComboWirelessAlarmId();
	afx_msg void OnPaint();
	afx_msg void OnChkWpsEn();
	afx_msg void OnBtnRefresh();
	afx_msg void OnBtnWpsConnect();
	afx_msg void OnBtnUpdatePin();
	afx_msg void OnBtnGetDevPin();
	afx_msg void OnBtnFishEyeSet();
	afx_msg void OnBtnFishEyeGet();
	afx_msg void OnBtnGetPresetNum();
	afx_msg void OnBtnGetPtzcruiseNum();
	afx_msg void OnBtnGetpresetInfo();
	afx_msg void OnBtnGetcruiseInfo();
	afx_msg void OnBtnMotionTrackSet();
	afx_msg void OnBtnMotionTrackGet();
	afx_msg void OnBtnIpaddrFilter();
	afx_msg void OnBtnUploadLogo();
	afx_msg void OnSelchangeComboAlarminWeekday();
	afx_msg void OnBtnGetpresetname();
	afx_msg void OnEditchangeComboPtzpresetno();
	afx_msg void OnBtnSetpresetname();
	afx_msg void OnBtnPtztask();
	afx_msg void OnBtnGettracktype();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnBtnCreatelink();
	afx_msg void OnBtnCloselink();
	afx_msg void OnBtnGetStreamMode();
	afx_msg void OnBntGetPtzPos();
	afx_msg void OnBntSetPtzPos();
	afx_msg void OnBtnSetDevparam();
	afx_msg void OnDestroy();
	afx_msg void OnBtnForensicsMode();
	afx_msg void OnBtnForcestopForensics();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
    int     m_iDevIndex;
	LONG    m_lChannel;
	LONG m_lAuxAlarmID;
	LONG m_lWirelessID;
	LONG m_lPlayHandle;
	DWORD dwChoosePtzindexNum;
	DWORD   m_dwPtzChannel;
	BOOL m_bAlarmOut[MAX_ALARMOUT_V30];
	NET_IPC_AUX_ALARMCFG m_struAuxAlarm;
	void CreateTree();
	void GetComboAlarminWeekdayData(int j);
	void SetComboAlarminWeekdayData(int j); 
	int m_iPtzPresetNum;

	CRect m_rcWnd; 
	NET_VCA_POINT m_struPoint;
	CPoint m_ptOriDrag;
	#define MAX_PRESET_NUM 300
	NET_DVR_PRESETCFG m_struPreSetCfg[128];
	NET_DVR_PRESET_NAME m_struPresetName[MAX_PRESET_NUM/*256*/];
	NET_VCA_RECT m_struVcaRect;
	BOOL m_bMouseMove;

	BOOL   m_bDragFishEyePTZ;
	LONG   m_lFishEyeCfgHandle;
	void   SendDragPtzPos(CPoint pt);
	void   AddFishEyeCallbackData(CString strData);
	void   DrawVcaRect(HDC hdc);
    float m_fX;
    float m_fY;
    float m_fZ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIPCSPECIAL_H__25057DA2_3A6C_420B_8613_1113541AA449__INCLUDED_)
