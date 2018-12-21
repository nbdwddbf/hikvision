#if !defined(AFX_DLGLCDSCREEN_H__6D38C662_506A_481B_9079_229088167226__INCLUDED_)
#define AFX_DLGLCDSCREEN_H__6D38C662_506A_481B_9079_229088167226__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLCDScreen.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLCDScreen dialog

class CDlgLCDScreen : public CDialog
{
// Construction
public:
	CDlgLCDScreen(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLCDScreen)
	enum { IDD = IDD_DLG_LCD };
	CComboBox	m_cmbZoomStatus;
	CComboBox	m_comScreenWallEable;
	CComboBox	m_comDefogModel;
	CComboBox	m_comDefogLevel;
	CComboBox	m_comDefogEnable;
	CComboBox	m_comSourcePip;
	CComboBox	m_comEnablePip;
	CComboBox	m_comPipColor;
	CComboBox	m_comDuration;
	CComboBox	m_comTransparency;
	CComboBox	m_comMenuLanguage;
	CComboBox	m_comEnableAuto;
	CComboBox	m_comWorkMode;
	CComboBox	m_comSignlType;
	CComboBox	m_comSignlPic;
	BYTE	m_bySpliceIndex;
	BYTE	m_bySpliceX;
	BYTE	m_bySpliceY;
	BYTE	m_byTemperatureLimitValue;
	BYTE	m_byClock;
	BYTE	m_byHorizontalPosition;
	BYTE	m_byPhase;
	BYTE	m_byVerticalPosition;
	short	m_wHeightPip;
	short	m_wWidthPip;
	short	m_wXCoordinate;
	short	m_wYCoordinate;
	BYTE	m_bySpliceHeight;
	BYTE	m_bySpliceWidth;
	BYTE	m_byScreenPosCol;
	BYTE	m_byScreenPosRow;
	DWORD	m_dwSignalNo;
	DWORD	m_dwBottomValue;
	DWORD	m_dwLeftValue;
	DWORD	m_dwRightValue;
	DWORD	m_dwTopValue;
	DWORD	m_dwWndID;
	DWORD	m_dwLeftTopX;
	DWORD	m_dwLeftTopY;
	DWORD	m_dwRightBtmX;
	DWORD	m_dwRightBtmY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLCDScreen)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLCDScreen)
	afx_msg void OnBtnRemoteOpen();
	afx_msg void OnBtnRemoteClose();
	afx_msg void OnBtnSignal();
	afx_msg void OnBtnMenu();
	afx_msg void OnBtnInfo();
	afx_msg void OnBtnAscertain();
	afx_msg void OnBtnUp();
	afx_msg void OnBtnLeft();
	afx_msg void OnBtnRight();
	afx_msg void OnBtnDown();
	afx_msg void OnBtnReturn();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSetSplice();
	afx_msg void OnBtnGetSplice();
	afx_msg void OnBtnSetFan();
	afx_msg void OnBtnGetFan();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboWorkMode();
	afx_msg void OnBtnScreenWorkStatus();
	afx_msg void OnSelchangeComboEnableAuto();
	afx_msg void OnBntSetVga();
	afx_msg void OnBntGetVga();
	afx_msg void OnBtnSetMenu();
	afx_msg void OnBtnGetMenu();
	afx_msg void OnBtnSetPip();
	afx_msg void OnBtnGetPip();
	afx_msg void OnSelchangeComboEnablePip();
	afx_msg void OnSelchangeComboDefogEnable();
	afx_msg void OnSelchangeComboDefogModel();
	afx_msg void OnBtnSetDefog();
	afx_msg void OnBtnGetDefog();
	afx_msg void OnBtnScreenDisplay();
	afx_msg void OnBtnShowIp();
	afx_msg void OnBtnMaintenanceWall();
	afx_msg void OnBtnSetScreenPos();
	afx_msg void OnBtnGetScreenPos();
	afx_msg void OnBtnTypenum();
	afx_msg void OnBtnControl0();
	afx_msg void OnBtnControl1();
	afx_msg void OnBtnControl2();
	afx_msg void OnBtnControl3();
	afx_msg void OnBtnControl4();
	afx_msg void OnBtnControl5();
	afx_msg void OnBtnControl6();
	afx_msg void OnBtnControl7();
	afx_msg void OnBtnControl8();
	afx_msg void OnBtnControl9();
	afx_msg void OnBtnSignalCut();
	afx_msg void OnBtnGetCutparam();
	afx_msg void OnButtonZoomin();
	afx_msg void OnButtonGetZoomStatus();
	afx_msg void OnBtnScreenTimer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
public:
	void SetRemoteScreen(BYTE byControlType);

	LONG m_lUserID;
	int m_iDevIndex;
	NET_DVR_SIMULATE_SCREEN_REMOTE_CTRL m_struRemoteScreen;
	NET_DVR_SCREEN_SIGNAL_CFG m_struSignalCFG;
	NET_DVR_SCREEN_SPLICE_CFG m_struSpliceCFG;
	NET_DVR_SCREEN_FAN_WORK_MODE_CFG m_struFanMode;
	NET_DVR_SCREEN_VGA_CFG m_struVGA;
	NET_DVR_SCREEN_MENU_CFG m_struMenu;
	NET_DVR_PIP_CFG m_struPip;
	NET_DVR_DEFOG_LCD m_struDefog;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLCDSCREEN_H__6D38C662_506A_481B_9079_229088167226__INCLUDED_)
