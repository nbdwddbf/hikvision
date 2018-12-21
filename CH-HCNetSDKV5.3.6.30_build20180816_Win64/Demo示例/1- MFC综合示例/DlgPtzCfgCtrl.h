#if !defined(AFX_DLGPTZCFGCTRL_H__DE74C389_CB94_40B7_A864_5C407D25050D__INCLUDED_)
#define AFX_DLGPTZCFGCTRL_H__DE74C389_CB94_40B7_A864_5C407D25050D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPtzCfgCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPtzCfgCtrl dialog
#include "PTZButton1.h"

class CDlgPtzCfgCtrl : public CDialog
{
// Construction
public:
	CDlgPtzCfgCtrl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPtzCfgCtrl)
	enum { IDD = IDD_DLG_IPD_PTZCFGCTRL };
	CComboBox	m_comboPositionDisplayFormat;
	CComboBox	m_comboPTZMotionTrack;
	CComboBox	m_comboRegionalID;
	CComboBox	m_comboColorType;
	CComboBox	m_comboActiveZoomRatio;
	CComboBox	m_comboPTZPrioritize;
	CComboBox	m_comboLimitStatus;
	CComboBox	m_comboLimitMode;
	CComboBox	m_comboResumeTimePoint;
	CComboBox	m_comboZoomStatus;
	CComboBox	m_comboPtStatus;
	CComboBox	m_comboPresetStatus;
	CComboBox	m_comboZoomingSpeed;
	CComboBox	m_comboAutoScanSpeed;
	CComboBox	m_comboPresetSpeed;
	CComboBox	m_comboKeyboardCtrlSpeed;
	BOOL	m_bChkProportionalPan;
	BOOL	m_bChkPresetFreezing;
	BOOL	m_bChkEnable;
	BOOL	m_bAllPatterms;
	BOOL	m_bAllPreset;
	BOOL	m_bAllPrivacyMasks;
	BOOL	m_bAllPTZLimited;
	BOOL	m_bAllScheduledTasks;
	BOOL	m_bAllParkAction;
	BOOL	m_bAllPatrols;
	BOOL	m_bDrawRectangular;
	int		m_iDelay;
	BOOL	m_bChkSmartTrackEnable;
	int		m_iDuration;
	BOOL	m_bChkPrivacyMaskEnable;
	BOOL	m_bChkSinglePrivacyMaskEnable;
	BOOL	m_bChkSinglePrivacyMaskClear;
	CString	m_csPrivacyMaskName;
	BOOL	m_bChkPrivacyMasksRect;
	BOOL	m_bChkPrivacyMasksRectClean;
	float   m_fActiveZoomRatio;
	BOOL    m_bChkRatioFloatEnable;
	CComboBox   m_comboManualTrackingTraget;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPtzCfgCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPtzCfgCtrl)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnOsdget();
	afx_msg void OnBtnOsdsave();
	afx_msg void OnBtnGetPoweroffmemcfg();
	afx_msg void OnBtnSetPoweroffmemcfg();
	afx_msg void OnBtnGetLimitcfg();
	afx_msg void OnBtnSetLimitcfg();
	afx_msg void OnBtnLimitset();
	afx_msg void OnBtnLimitclear();
	afx_msg void OnBtnClearctrl();
	afx_msg void OnBtnGetPtzPrioritizecfg();
	afx_msg void OnBtnSetPtzPrioritizecfg();
	afx_msg void OnBtnSetInitialpositionctrl();
	afx_msg void OnBtnGotoInitialpositionctrl();
	afx_msg void OnBtnClearInitialpositionctrl();
	afx_msg void OnBtnGetSmarttrack();
	afx_msg void OnBtnSaveSmarttrack();
	afx_msg void OnBtnZoomratioctrl();
	afx_msg void OnChkPrivacyMasksEnable();
	afx_msg void OnChkDrawRect();
	afx_msg void OnBtnGetPrivacyMasks();
	afx_msg void OnBtnGotoRegionalid();
	afx_msg void OnBtnGetAllPrivacyMaskscfg();
	afx_msg void OnBtnSavesingkeRegioninfo();
	afx_msg void OnBtnSaveAllPrivacyMaskscfg();
	afx_msg void OnSelchangeComboRegionalid();
	afx_msg void OnChkPrivacyMasksRect();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnChkPrivacyMasksRectClean();
	afx_msg void OnBtnGetSetSingleregion();
	afx_msg void OnBtnGetDetRegioncfg();
	afx_msg void OnCheckFloatRatio();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	~CDlgPtzCfgCtrl();
	#define MAX_PRIVACY_MASKS_REGION_NUM		8       //支持最大区域数

	CRect   m_rcWnd;
	
	//设备相关参数
	LONG    m_lLoginID;
	int     m_iDeviceIndex;
	LONG    m_lChannel;
	LONG	m_lPlayHandle;
	
	//当前已经画的点的个数
	DWORD m_dwPosNum; 
	BOOL m_bCloseIn;
	BOOL m_bMouseMovePolygon;
	BOOL m_bMouseMove;
	
	DWORD  m_dwRegionID;
	BOOL play();
	
    CPTZButton1 m_btnPtzUp;
    CPTZButton1 m_btnPtzDown;
    CPTZButton1 m_btnPtzLeft;
    CPTZButton1 m_btnPtzRight;
	
	void    ShowPrivacyMasksInfo(NET_DVR_PRIVACY_MASKS_CFG *pPrivacyMasksCfg);
	NET_DVR_PTZ_BASICPARAMCFG m_struPtzBasicParamCfg;
	NET_DVR_PTZ_OSDCFG m_struPtzOsdCfg;
	NET_DVR_PTZ_POWEROFFMEMCFG m_struPoweroffmemCfg;
	NET_DVR_PTZ_LIMITCOND m_struLimitCond;
	NET_DVR_PTZ_LIMITCFG m_struLimitCfg;
	NET_DVR_PTZ_LIMITCTRL m_struLimitCtrl;
	NET_DVR_CLEARCTRL m_struClearCtrl;
	NET_DVR_PTZ_PRIORITIZECFG m_struPrioritizeCfg;
	NET_DVR_INITIALPOSITIONCTRL m_struInitialPositionCtrl;
	NET_DVR_SMARTTRACKCFG m_struSmartTrackCfg;
	NET_DVR_ZOOMRATIOCTRL m_strZoomRatioCtrl;
	NET_DVR_PRIVACY_MASKS_ENABLECFG m_struPrivacyMasksEnableCfg;

	NET_DVR_PRIVACY_MASKS_COND m_struPrivacyMasksCond[MAX_PRIVACY_MASKS_REGION_NUM];
	NET_DVR_PRIVACY_MASKS_CFG m_struPrivacyMasksCfg[MAX_PRIVACY_MASKS_REGION_NUM];
	//	void DrawVcaRect(HDC hDc, DWORD dwCurRect);
	void F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser);
	void F_DrawRect(HDC hDc);
	void F_DrawPolygon(HDC hDc);
	BOOL PreDrawPolygonMsg(MSG* pMsg, CPoint &pt);

	HANDLE  m_hRegisterDrawThread;

	BOOL IsCrossLine(NET_VCA_POLYGON *struRuleRegion);
	BOOL F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2);
	BOOL IsValidArea(LPNET_VCA_POLYGON lpstruPolygon);
	BOOL F_IsStraightLine(NET_VCA_POLYGON *lpstruPolygon);
	BOOL F_IsACrossLine(NET_VCA_POLYGON *alarm_region);

	void F_DrawPrivacyMasksRegion(LONG lRealHandle, HDC hDc, DWORD dwUser);
	void F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser,  COLORREF color);
};
	
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPTZCFGCTRL_H__DE74C389_CB94_40B7_A864_5C407D25050D__INCLUDED_)
