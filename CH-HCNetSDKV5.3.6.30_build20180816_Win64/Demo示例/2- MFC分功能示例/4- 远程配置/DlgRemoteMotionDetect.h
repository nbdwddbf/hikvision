#pragma once
#include "afxwin.h"
#include "GeneralDef.h"
#include "resource.h"
#include "config.h"


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
	CTreeCtrl	m_treeAlarmOut;
	CTreeCtrl	m_treeChan;
	BOOL m_bChkMonitorAlarm;
	BOOL m_bChkAudioAlarm;
	BOOL m_bChkReportCenter;
	BOOL m_bChkInvokeAlarmOut;
	BOOL m_bChkInvokeJpegCapture;
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
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CDlgRemoteMotionDetect)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
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
	afx_msg void OnCancel();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	int	m_iChanShowNum;
	LONG	m_lLoginID;
	BOOL	m_bDrawArea;//是否画移动侦测区域
	LONG	m_lPlayHandle;
	BOOL	m_bSetMotion;//是否设置移动区域
	DWORD m_dwAlarmOutNum;
	int m_iChanCount;//设备的预览通道数
	BOOL TimeTest();
	int m_iSelPrecision;
	DWORD m_dwDevIndex;
	void CreateTree();
	BOOL m_bAlarmOut[MAX_ALARMOUT_V30];
	BOOL m_bRecordChan[MAX_CHANNUM_V30];
};
