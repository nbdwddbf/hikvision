#if !defined(AFX_DLGFIREDETECTION_H__A89643A0_26F1_4E88_9B73_BD639787EC2E__INCLUDED_)
#define AFX_DLGFIREDETECTION_H__A89643A0_26F1_4E88_9B73_BD639787EC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "VcaCommonOperations.h"
#include "afxwin.h"
// DlgFireDetection.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFireDetection dialog

class CDlgFireDetection : public CDialog,public CVcaCommonOperations
{
// Construction
public:
	CDlgFireDetection(CWnd* pParent = NULL);   // standard constructor
    ~CDlgFireDetection();
// Dialog Data
	//{{AFX_DATA(CDlgFireDetection)
	enum { IDD = IDD_DLG_FIRE_DETECTION };
	CComboBox	m_comShipsRule;
	CComboBox	m_comShipsDraw;
	CComboBox	m_comRuleCalibType;
	CComboBox	m_comTemperatureRange;
	CListCtrl	m_lstThermometric;
	CListCtrl	m_lstRealtimeThermometry;
	CComboBox	m_comDiffComparisonType;
	CComboBox	m_comDiffComparisonAlarmType;
	CComboBox	m_comDiffComparisonAlarmRule;
	CComboBox	m_comThermometryAlarmType;
	CComboBox	m_comThermometryAlarmRule;
	CComboBox	m_comRule;
	CComboBox	m_comPresetNo;
	CComboBox	m_comThermometryUnit;
	CComboBox	m_comThermometryRange;
    CComboBox   m_comTemperatureColor;
    CComboBox   m_comDistanceUnit;
    CComboBox   m_cmbThermometryCurve;
    CComboBox   m_cmbFireImageModea;
	BOOL	m_bEnable;
	BOOL	m_bFireRegionOverlay;
	BYTE	m_byFireComfirmTime;
	BYTE	m_bySensitivity;
	BOOL	m_bEnbaleThermometry;
	BOOL	m_bPictureOverlay;
	BOOL	m_bStreamOverlay;
	BOOL	m_bEnableRule;
	BOOL	m_bChkRegion;
	DWORD	m_dwDistance;
	float	m_fEmissivity;
	float	m_fReflectiveTemperature;
	BYTE	m_byRuleID;
	CString	m_csRuleName;
	BOOL	m_bChkAlarmRuleEnable;
	BYTE	m_byThermometryRuleID;
	CString	m_csThermometryRuleName;
	float	m_fAlarm;
	float	m_fAlert;
	float	m_fThreshold;
	BOOL	m_bChkDiffComparisonEnable;
	float	m_fTemperatureDiff;
	BYTE	m_byAlarmID1;
	BYTE	m_byAlarmID2;
	BYTE	m_byDiffRuleID;
	float	m_fThermPointX;
	float	m_fThermPointY;
	float	m_fCenterPointEmissionRate;
	CString	m_csFilePath;
	BOOL	m_bReflectiveEnabled;
	float	m_fThresholdTemperature;
	BOOL	m_bEnableBareDataOverlay;
	BYTE	m_byInterTimeBareDataOverlay;
	BOOL	m_bShipsEnable;
	BOOL	m_bShipsFrameOverlayEnabled;
	BOOL	m_bShipsRuleEnable;
	float	m_fLookDownUpAngle;
	float	m_fHorizontalHeight;
	BYTE	m_byShipsSensitivity;
	BOOL	m_bShipsShow;
	BOOL	m_bThermShow;
	BYTE	m_byShipRuleID;
	//}}AFX_DATA
    LONG    m_lRealTimeInfoHandle;
    LONG    m_lThermometricHandle;
    LONG    m_lPlayHandle;
	CRect   m_rcPlayWnd;
   // LONG    m_lChannel;
   // LONG    m_lUser;
   // int     m_iDeviceIndex;
    char    m_szStatusBuf[ISAPI_STATUS_LEN];
    int     m_nDrawPointNum;
    int     m_nShipsDrawPointNum;

    LONG    m_lUploadHandle;
    BOOL    m_bUpLoading;
    HANDLE	m_hUpLoadThread;
    HANDLE	m_hDownloadThread;
    BOOL    m_bDownLoading;
	LONG    m_lDownloadHandle;
    BOOL    m_bDrawEnd;
    int     m_iHighTemperature;
    int     m_iLowTemperature;
    float   m_fThernomertryEmissivity;
    BYTE    m_byEnviroHumidity;
    int		m_iEnviroTemperature;
    int     m_iCorrectionVolume;
    BOOL    m_bChkCenterSpecialPoint;
    BOOL    m_bChkHighestSpecialPoint;
    BOOL    m_bChkLowestSpecialPoint;
    BOOL	m_bChkReflectiveEnabled;
    BYTE    m_bySpecialPointThermType;
    DWORD	m_dwDistanceMeter;
    float   m_fReflectiveTemp;

    NET_DVR_FIREDETECTION_CFG m_struFireDetection;
    NET_DVR_THERMOMETRY_PRESETINFO m_struThermometryInfo;
    NET_DVR_THERMOMETRY_COND m_struThermometryCond;
    NET_DVR_THERMOMETRY_ALARMRULE m_struThermometryAlarmInfo;
    NET_DVR_THERMOMETRY_DIFFCOMPARISON m_struThermometryDiffComparison;
    NET_VCA_POLYGON m_struPolyGon;
    NET_VCA_LINE m_struLine;
    NET_ITC_POLYGON m_struITCPolyGon;
    NET_DVR_SHIPSDETECTION_CFG m_struShipsDet;
    void DrawRgnFun(HDC hdc);
    void InitComboBoxCtrl();
    void InitListCtrl();
    void SaveThermometryCond();
    void ProcessGetRealtimeThermometryCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
    void ProcessGetThermometryCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFireDetection)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFireDetection)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnSetThermometry();
	afx_msg void OnBtnGetThermometry();
	afx_msg void OnBtnGetThermometryPresetinfo();
	afx_msg void OnBtnSetThermometryPresetinfo();
	afx_msg void OnBtnSaveThermometryPresetinfo();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSelchangeComboRule();
	afx_msg void OnBtnSaveThermometryAlarmrule();
	afx_msg void OnSelchangeComboThermometryAlarmrule();
	afx_msg void OnBtnSetThermometryAlarmrule();
	afx_msg void OnBtnGetThermometryAlarmrule();
	afx_msg void OnSelchangeComboDiffcomparisonAlarmrule();
	afx_msg void OnBtnSaveDiffcomparison();
	afx_msg void OnBtnSetDiffcomparison();
	afx_msg void OnBtnGetDiffcomparison();
	afx_msg void OnBtnGetRealtimeThermometry();
    afx_msg LRESULT OnMsgAddRealtimeCfgToList(WPARAM wParam,LPARAM lParam);
    afx_msg LRESULT OnMsgRealtimeCfgFinish(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBtnGetThermometric();
    afx_msg LRESULT OnMsgAddThermometryCfgToList(WPARAM wParam,LPARAM lParam);
    afx_msg LRESULT OnMsgThermometryCfgFinish(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBtnFilePath();
	afx_msg void OnBtnFileDownload();
	afx_msg void OnBtnFileUpload();
	afx_msg void OnSelchangeComboRuleCalibType();
	afx_msg void OnBtnSetBaredataoverlay();
	afx_msg void OnBtnGetBaredataoverlay();
	afx_msg void OnBtnShipsRuleSave();
	afx_msg void OnSelchangeComboShipsRule();
	afx_msg void OnBtnShipsGet();
	afx_msg void OnBtnShipsSet();
	afx_msg void OnSelchangeComboShipsDraw();
	afx_msg void OnChkThermometryShow();
	afx_msg void OnChkShipsShow();
	afx_msg void OnBtnShipscount();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnFocuszoom();
    BOOL m_bManualRangEnable;
    afx_msg void OnBnClickedBtnSetManualranging();
	afx_msg void OnBnClickedBtnSetManualdeicing();
	afx_msg void OnBnClickedBtnGetManualdeicing();
	BOOL m_bManualDeicingEnable;
    CComboBox m_comIntellType;
    afx_msg void OnBnClickedBtnSetThermintell();
    afx_msg void OnBnClickedBtnGetThermintell();
    afx_msg void OnBnClickedBtnRegionCfg();
    afx_msg void OnBnClickedBtnGetManualthermInfo();
    CComboBox mDetectionMode;
    CComboBox mFireFocusMode;
    CComboBox mStrategyType;
    CComboBox m_comFireZoomMode;
    CComboBox m_comSmokeFireEnabled;
    BYTE m_byFireZoomLevel;
    BOOL mSmokeEnabled;
    int mSmokeSensitivity;
    afx_msg void OnBnClickedBtnThermalPipCfg();
    float m_fAlarmVal;
    float m_fAlertVal;
    BOOL m_bShowTempStripEnable;
    afx_msg void OnBnClickedBtnSetThermometryMode();
    afx_msg void OnBnClickedBtnGetThermometryMode();
    CComboBox m_cmbThermometryMode;
    afx_msg void OnBnClickedBtnGetAlginfo();
    CString m_sShipsAlgName;
    CString m_sThermAlgName;
    CString m_csFireAlgName;
    CComboBox m_comModeCond;
    int m_iRuleIDCond;
    BOOL m_bFireManualWaitEnabled;
    afx_msg void OnBnClickedBtnFirescanStart();
    float m_ThermalOpticalTransmittance;
    float m_externalOpticsWindowCorrection;
    BOOL m_CancelRepeatedAlarmEnabled;
    CComboBox m_ApplicationSceneMode;
    int m_InstallationHeight;
    BYTE m_PatrolSensitivity;
    BYTE m_DoubleCheckSensitivity;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFIREDETECTION_H__A89643A0_26F1_4E88_9B73_BD639787EC2E__INCLUDED_)
