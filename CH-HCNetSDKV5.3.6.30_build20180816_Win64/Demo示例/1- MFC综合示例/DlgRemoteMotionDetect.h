#pragma once
#include "afxwin.h"


// CDlgRemoteMotionDetect dialog

class CDlgRemoteMotionDetect : public CDialog
{
	DECLARE_DYNAMIC(CDlgRemoteMotionDetect)

public:
	CDlgRemoteMotionDetect(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRemoteMotionDetect();

// Dialog Data



public:
	
	
	//{{AFX_DATA(CDlgRemoteMotionDetect)
	enum { IDD = IDD_DLG_REMOTE_MOTION_DETECT };
	CTreeCtrl	m_treeFTPChan;
	CTreeCtrl	m_treeAlarmRelChan;
	CComboBox	m_comboAreaNo;
	CComboBox	m_comboWorkType;
	CComboBox	m_comboConfigRationCfg;
	CTreeCtrl	m_treeAlarmOut;
	CTreeCtrl	m_treeChan;
	BOOL m_bChkMonitorAlarm;
	BOOL m_bChkAudioAlarm;
	BOOL m_bChkReportCenter;
	BOOL m_bChkInvokeAlarmOut;
	BOOL m_bChkInvokeJpegCapture;
	BOOL m_bChkEmapAlarmOut;
	BOOL m_bChkAlarmOut1;
	BOOL m_bChkAlarmOut2;
	BOOL m_bChkAlarmOut3;
	BOOL m_bChkAlarmOut4;
	BOOL m_bChkAlarmOut5;
	BOOL m_bChkAlarmOut6;
	BOOL m_bChkAlarmOut7;
	BOOL m_bChkAlarmOut8;
	BOOL m_bChkAlarmOut9;
	BOOL m_bChkAlarmOut10;
	BOOL m_bChkAlarmOut11;
	BOOL m_bChkAlarmOut12;
	BOOL m_bChkAlarmOut13;
	BOOL m_bChkAlarmOut14;
	BOOL m_bChkAlarmOut15;
	BOOL m_bChkAlarmOut16;
	BOOL m_bChkAlarmOut17;
	BOOL m_bChkAlarmOut18;
	BOOL m_bChkAlarmOut19;
	BOOL m_bChkAlarmOut20;
	BOOL m_bChkAlarmOut21;
	BOOL m_bChkAlarmOut22;
	BOOL m_bChkAlarmOut23;
	BOOL m_bChkAlarmOut24;
	BOOL m_bChkAlarmOut25;
	BOOL m_bChkAlarmOut26;
	BOOL m_bChkAlarmOut27;
	BOOL m_bChkAlarmOut28;
	BOOL m_bChkAlarmOut29;
	BOOL m_bChkAlarmOut30;
	BOOL m_bChkAlarmOut31;
	BOOL m_bChkAlarmOut32;
	CComboBox m_comboWeekday;
	CComboBox m_comboDayCopy;
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
	BOOL m_bChkMotionShow;
	BOOL m_bChkMotionSet;
	CComboBox m_comboMotionSensitive;
	CStatic m_picMotionDetect;	
	CComboBox m_comboPrecision;
	BOOL	m_bChkPicFtp;
    BOOL    m_bChkPicCloud;
    BOOL    m_bChkWirelessSoundLightAlarm;
	BOOL	m_bChkShowMotion;
	COleDateTime	m_startTime;
	COleDateTime	m_stopTime;
	int		m_iMotionSensitive;
	int		m_iMotionSensitiveAutoD;
	int		m_iMotionSensitiveAutoN;
	int		m_iObjectSize;
	int		m_iObjectSizeAutoD;
	int		m_iObjectSizeAutoN;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CDlgRemoteMotionDetect)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteMotionDetect)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);	
	afx_msg void OnBnClickedChkInvokeAlarmOut();
	afx_msg void OnCbnSelchangeComboWeekday();
	afx_msg void OnBnClickedChkMotionDetectShow();
	afx_msg void OnBnClickedChkMotionDetectSet();
	afx_msg void OnBnClickedMotionDayOk();
	afx_msg void OnBnClickedBtnMotionDayCopy();
	afx_msg void OnBnClickedBtnMotionOk();
	afx_msg void OnBnClickedBtnMotionExit();
	afx_msg void OnCbnSelchangeComboPrecisioin();
	afx_msg void OnClickTreeChan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnSelchangeComboConfigurationCfg();
	afx_msg void OnSelchangeComboWorktype();
	afx_msg void OnSelchangeComboAreano();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnAlarmoutSelectall();
	afx_msg void OnBtnChanSelectall();
	afx_msg void OnBtnSetAlarmRelate();
	afx_msg void OnClickTreeAlarmRelateChan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeFtpChan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnGetAlarmRelate();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	DWORD m_dwDevIndex; 
	int	m_iChanShowNum;
	LONG	m_lLoginID;
	BOOL	m_bDrawArea;//draw motion detect area
	LONG	m_lPlayHandle;
	BOOL	m_bSetMotion;//set motion detect area
	DWORD m_dwAlarmOutNum;
	int m_iChanCount;//preview channel number
	BOOL TimeTest();
	int m_iSelPrecision; 
	void CreateTree();
// 	BOOL m_bAlarmOut[MAX_ALARMOUT_V30];
// 	BOOL m_bRecordChan[MAX_CHANNUM_V30];
	
    BOOL *m_pbAlarmOut;
	BOOL *m_pbRecordChan;
    BOOL m_bCurConfigurationMode;

	BOOL *m_pbFTP;
	BOOL *m_pbAlarmRelChan;
    
    NET_DVR_HOLIDAY_HANDLE m_struHolidayHandle;
	BYTE m_byAreaID;
	CRect   m_rcWnd;
	BOOL m_bMouseMove;
	LPNET_DVR_ALARM_RELATE_CFG m_pStruAlarmRel;
	LPNET_DVR_ALARM_RELATE_COND m_pStruAlarmRelCond;
public:
    BOOL GetMotionHolidayHandle(NET_DVR_HOLIDAY_HANDLE &struHolidayHandle);
    BOOL SetMotionHolidayHandle(NET_DVR_HOLIDAY_HANDLE &struHolidayHandle);
	void SetAlarmRelCond(int iIndex, BYTE byRelateActType);
	void SetAlarmRelChan(int iIndex, DWORD dwTreeIndex, BOOL bCheck);
	void SetAlarmRelCFG(int iIndex);

	void F_DrawFun(/*long lPlayHandle, */HDC hDc, DWORD dwUser);
	void F_DrawRect(HDC hDc);
	void DrawITCRect(HDC hDc, NET_VCA_RECT struRect,  CRect rcWnd, DWORD dwCurRect, COLORREF color);
    CComboBox m_all_sentive_motion;
    CComboBox m_comboDiscardFalseAlarm;
};
