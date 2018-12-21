#include "afxwin.h"
#include "ATLComTime.h"
#if !defined(AFX_DLGPDCRULECFGEX_H__0770FB1D_3DE8_4691_9C83_0A206E440CE3__INCLUDED_)
#define AFX_DLGPDCRULECFGEX_H__0770FB1D_3DE8_4691_9C83_0A206E440CE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPdcRuleCfgEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPdcRuleCfgEx dialog

class CDlgPdcRuleCfgEx : public CDialog
{
// Construction
public:
	CDlgPdcRuleCfgEx(CWnd* pParent = NULL);   // standard constructor
	~CDlgPdcRuleCfgEx();
// Dialog Data
	//{{AFX_DATA(CDlgPdcRuleCfgEx)
	enum { IDD = IDD_DLG_PDC_RULE_CFG_EX };
	CComboBox	m_comboUploadCycle;
	CComboBox	m_comboCopyTime;
	CComboBox	m_comboWeekday;
	CComboBox	m_comboDetType;
	BOOL	m_bEnableRule;
	BOOL	m_bUploadCenter;
	BYTE	m_byDetSensitivity;
	BYTE	m_byGeneratieSpeedSpace;
	BYTE	m_byGeneratieSpeedTime;
	BYTE	m_byTargetSizeCorrect;
	BYTE	m_byCountSpeed;
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
	BOOL	m_bEnableOSD;
	float   m_fPointX;
	float   m_fPointY;
	BOOL	m_bChkSECUpload;
	float	m_fWidth;
	BOOL	m_bChkRemovePDC;
	//}}AFX_DATA
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPdcRuleCfgEx)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPdcRuleCfgEx)
	afx_msg void OnBtnPdcRulecfg();
	afx_msg void OnRadioDrawPolygon();
	afx_msg void OnRadioDrawDirection();
    afx_msg void OnRadioDetectLine();
	afx_msg void OnTimeOk2();
	afx_msg void OnTimeCopy2();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnPdcQuery();
	afx_msg void OnBtnCalibration();
	afx_msg void OnBtnGetPdcRulecfg();
	afx_msg void OnBtnPdcResult();
    afx_msg void OnBtnGetPdcLint();
    afx_msg void OnBtnSetPdcLint();
	afx_msg void OnBtnAdvResetCounte();
	afx_msg void OnBtnGetpdcrecommend();
	afx_msg void OnBtnRemoveFlashstorage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void PDCDrawDirection(HDC hDc, DWORD dwUser);
    void PDCDetectLine(HDC hDc, NET_VCA_LINE struLine);
	void GetPdcRuleWnd();
    void PDCDrawCalibResult(HDC hDc, DWORD dwUser);
    void PDCDrawCalib(HDC hDc, DWORD dwUser);
	long StartRealPlay();  // 开始预览 
    BOOL StopRealPlay();  // 停止预览
	void F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser,  COLORREF color);
	void F_DrawPdcRule(LONG lRealHandle, HDC hDc, DWORD dwUser);

    NET_DVR_PDC_RULE_CFG_V42 m_struPdcRuleCfg;
	NET_DVR_PDC_RULE_COND m_struPdcRuleCond;
	LPNET_DVR_PDC_RULE_CFG_V42 m_pStruPdcRuleCfg;
    long        m_lServerID; // 用户ID
    int         m_iDevIndex; // 设备索引
    long        m_lPlayHandle;  // 预览返回参数，作为停止预览等参数
    CRect       m_rcWndRect;   //预览窗口大小
    BOOL    m_bMouseMove;
    BOOL    m_bCloseIn;
    DWORD   m_dwPosNum;  //
    int     m_iDrawType; //画图类型
	LONG    m_lChannel;
	LONG    m_lChanNum; //通道号总数

	BOOL F_TimeTest(); 
	LONG    m_lLoginID;
	void SetAlarmTimeToWnd(NET_DVR_SCHEDTIME const *pAlarmTime, int nDay);
	void GetAlarmTimeFromWnd(NET_DVR_SCHEDTIME *pAlarmTime, int nDay);

	BOOL IsCrossLine(NET_VCA_POLYGON *alarm_region);
    BOOL F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2);
    BOOL IsValidArea(NET_VCA_POLYGON *alarm_region);
    BOOL F_IsACrossLine(NET_VCA_POLYGON *alarm_region);
    BOOL F_IsStraightLine(NET_VCA_POLYGON *alarm_region);

    char m_szStatusBuf[ISAPI_STATUS_LEN];
    CComboBox m_dwID;
    CComboBox m_OSDEnable_New;
    BOOL m_ShadowEnable;
    BOOL m_AroundEnable;
    BOOL m_PushCarEnable;
    BOOL m_DayReportEnable;
    BOOL m_WeekReportEnable;
    BOOL m_MonthReportEnable;
    BOOL m_YearReportEnable;
    afx_msg void OnBnClickedBtnHeightSet();
    CComboBox m_cmbHeightFilterEnabled;
    CComboBox m_cmbHeightFilter;
    float m_fHeightFilter;
    CComboBox m_cmbCalibType;
    float m_fHeight;
    float m_fTiltAngle;
    float m_fHeelAngle;
    afx_msg void OnBnClickedBtnCalib();
    afx_msg void OnBnClickedRadioCalib();
    afx_msg void OnCbnSelchangeCmbCalibType();
    NET_DVR_SETUP_CALIB_RESULT m_strSetupResult;
    afx_msg void OnBnClickedBtnHeightGet();
    CComboBox m_cmbType;
    afx_msg void OnBnClickedBtnCalibGet();
    CComboBox m_cmbArgType;
    BOOL m_bStreamOverlayRuleInfos;
    BOOL m_bRS485TransmissionEnabled;
    CComboBox m_comboCountingType;
    CComboBox m_comboSignalType;
    afx_msg void OnBnClickedRadioPolyLine();
    COleDateTime m_ctResetDate;
    COleDateTime m_ctResetTime;
    void F_DrawPolyLine(long lRealHandle, HDC hDc, DWORD dwUser, COLORREF color);

    DWORD   m_dwLineNum;
    BYTE m_byDetectThreshold;
    BOOL m_bLightStream;
    bool m_bCountPolygon;
    afx_msg void OnBnClickedCountPolygon();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPDCRULECFGEX_H__0770FB1D_3DE8_4691_9C83_0A206E440CE3__INCLUDED_)
