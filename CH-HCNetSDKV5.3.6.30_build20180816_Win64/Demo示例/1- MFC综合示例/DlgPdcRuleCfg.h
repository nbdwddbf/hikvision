#if !defined(AFX_DLGPDCRULECFG_H__8DD08E30_0520_45F8_8882_61155DBA3827__INCLUDED_)
#define AFX_DLGPDCRULECFG_H__8DD08E30_0520_45F8_8882_61155DBA3827__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPdcRuleCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPdcRuleCfg dialog

class CDlgPdcRuleCfg : public CDialog
{
// Construction
public:
	CDlgPdcRuleCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPdcRuleCfg)
	enum { IDD = IDD_DLG_PDC_RULE_CFG };
	CComboBox	m_comboCopyTime;
	CComboBox	m_comboWeekday;
	CComboBox	m_comboStreamTransType;
	CComboBox	m_comboDvrTransType;
	CIPAddressCtrl	m_ipStream;
	CIPAddressCtrl	m_ipDvr;
	CComboBox	m_comboDvrTransProtocol;
	CComboBox	m_comboVcaType;
	CComboBox	m_comboStream;
	CComboBox	m_comboVcaChan;
	BOOL	m_bEnableRule;
	BOOL	m_bVcaActive;
	int		m_iDvrChannel;
	int		m_iDvrPort;
	CString	m_csPassword;
	int		m_iStreamPort;
	CString	m_csUserName;
	BOOL	m_bStreamValid;
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
	BYTE	m_byDayStartHour;
	BYTE	m_byDayStartMin;
	BYTE	m_byDayStartSec;
	BYTE	m_byNightStartHour;
	BYTE	m_byNightStartMin;
	BYTE	m_byNightStartSec;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPdcRuleCfg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPdcRuleCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnPdcRulecfg();
	afx_msg void OnRadioDrawPolygon();
	afx_msg void OnRadioDrawDirection();
	afx_msg void OnBtnCalibration();
	afx_msg void OnSelchangeComboVcaChan();
	afx_msg void OnBtnSetVcaCtrl();
	afx_msg void OnBtnSetPuStream();
	afx_msg void OnBtnPdcQuery();
	afx_msg void OnBtnResetCounte();
	afx_msg void OnTimeOk2();
	afx_msg void OnTimeCopy2();
	afx_msg void OnSelchangeComboweekday();
	afx_msg void OnBtnAdvResetCounte();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public: // func

public: // param
    NET_DVR_PDC_RULE_CFG_V41 m_struPdcRuleCfg;
    long        m_lServerID; // 用户ID
    int          m_iDevIndex; // 设备索引
 //   long        m_lChannel;  // 用户通道号
    long        m_lPlayHandle;  // 预览返回参数，作为停止预览等参数
    CRect       m_rcWndRect;   //预览窗口大小

    BOOL   m_bMouseMove;
    BOOL   m_bCloseIn;
    
    DWORD  m_dwPosNum;  //
    
    int     m_iDrawType; //画图类型
    int     m_iVcaChan;     // 当前智能通道 开始默认为0 
    int     m_iChannelNum;   //通道总数 
    int     m_iStartChannel;   // 起始通道

	int     m_iCurChannel;  //兼容iVMS6200(V2.0),按照各通道能力
    NET_VCA_CTRLCFG     m_struVcaCtrl;
    NET_DVR_PU_STREAM_CFG m_struPUStream;

	NET_VCA_DEV_ABILITY m_struVcaDevAbility;
	BOOL m_bSupportChanEx;
	NET_DVR_VCA_CTRLINFO_CFG m_struVcaCtrlInfo;
    
public: // func
    long StartRealPlay();  // 开始预览 
    BOOL StopRealPlay();  // 停止预览

    void F_DrawPdcRule(LONG lRealHandle, HDC hDc, DWORD dwUser);
    void F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser,  COLORREF color);
    BOOL IsCrossLine(NET_VCA_POLYGON *alarm_region);
    BOOL F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2);
    BOOL IsValidArea(NET_VCA_POLYGON *alarm_region);
    BOOL F_IsACrossLine(NET_VCA_POLYGON *alarm_region);
    BOOL F_IsStraightLine(NET_VCA_POLYGON *alarm_region);
    void PDCDrawDirection(HDC hDc, DWORD dwUser);
    void GetPdcRuleWnd();
    void GetCtrlWnd();
    void GetPUStreamWnd();
    void SetPUStreamCfg();

	BOOL F_TimeTest(); 
	void SetAlarmTimeToWnd(NET_DVR_SCHEDTIME const *pAlarmTime, int nDay);
	void GetAlarmTimeFromWnd(NET_DVR_SCHEDTIME *pAlarmTime, int nDay);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPDCRULECFG_H__8DD08E30_0520_45F8_8882_61155DBA3827__INCLUDED_)
