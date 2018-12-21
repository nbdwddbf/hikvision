#include "afxwin.h"
#if !defined(AFX_DLGHEATMAPCFG_H__FAA08680_BF8D_4456_AABF_224251DC4DB5__INCLUDED_)
#define AFX_DLGHEATMAPCFG_H__FAA08680_BF8D_4456_AABF_224251DC4DB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHeatMapCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgHeatMapCfg dialog

class CDlgHeatMapCfg : public CDialog
{
// Construction
public:
	CDlgHeatMapCfg(CWnd* pParent = NULL);   // standard constructor
	~CDlgHeatMapCfg();
// Dialog Data
	//{{AFX_DATA(CDlgHeatMapCfg)
	enum { IDD = IDD_DLG_HEATMAP };
	CComboBox	m_cmbChannel;
	CComboBox	m_comReportType;
	CComboBox	m_comSceneID;
	CComboBox	m_comSceneID2;
	CListCtrl	m_lstHeatMap;
	CComboBox	m_comboCopyTime;
	CComboBox	m_comboWeekday;
	CComboBox	m_comboAreaID;
	CComboBox	m_comboTargetTrackEnable;
	BYTE	m_bySensitivity;
	BOOL	m_bEnable;
	BOOL	m_bUploadCenter;
	BYTE	m_byBackgroundUpdateRate;
	BYTE	m_byMinTargetSize;
	BYTE	m_bySceneChangeLevel;
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
	DWORD	m_dwTimeSlot;
	COleDateTime	m_startDate;
	COleDateTime	m_startTime;
	COleDateTime	m_stopDate;
	COleDateTime	m_stopTime;
	DWORD	m_dwTerminalNo;
	//}}AFX_DATA
	int     iAreaID;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHeatMapCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHeatMapCfg)
	afx_msg void OnBtnPdcRulecfg();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimeOk2();
	afx_msg void OnTimeCopy2();
	afx_msg void OnSelchangeComboAreaid();
	afx_msg void OnBtnGetHeatmapInfo();
	afx_msg void OnBtnGetHeatmap();
	afx_msg void OnBtnCleanHeatmapInfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void PDCDrawDirection(HDC hDc, DWORD dwUser);
	void GetHeatMapRuleWnd();
	
	long StartRealPlay();  // 开始预览 
    BOOL StopRealPlay();  // 停止预览
	void F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser,  COLORREF color);
	void F_DrawHeatMapRegion(LONG lRealHandle, HDC hDc, DWORD dwUser);

	NET_DVR_HEATMAP_COND m_struHeatMapCond;
    NET_DVR_HEATMAP_CFG m_struHeatMapCfg;

    long        m_lServerID; // 用户ID
    int         m_iDevIndex; // 设备索引
    long        m_lPlayHandle;  // 预览返回参数，作为停止预览等参数
    CRect       m_rcWndRect;   //预览窗口大小
    BOOL    m_bMouseMove;
    BOOL    m_bCloseIn;
    DWORD   m_dwPosNum;  //
    int     m_iDrawType; //画图类型
	LONG    m_lChannel;
	BOOL F_TimeTest(); 
	LONG    m_lLoginID;
	void SetAlarmTimeToWnd(NET_DVR_SCHEDTIME const *pAlarmTime, int nDay);
	void GetAlarmTimeFromWnd(NET_DVR_SCHEDTIME *pAlarmTime, int nDay);
	
	BOOL IsCrossLine(NET_VCA_POLYGON *alarm_region);
    BOOL F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2);
    BOOL IsValidArea(NET_VCA_POLYGON *alarm_region);
    BOOL F_IsACrossLine(NET_VCA_POLYGON *alarm_region);
    BOOL F_IsStraightLine(NET_VCA_POLYGON *alarm_region);
	
	int	 m_iStruCount;
	BOOL m_bGetNext;
	LONG m_lHandle;
	HANDLE m_hGetInfoThread;
	NET_DVR_HEATMAP_QUERY_COND m_struHeatMapQueryCond;
	//LPNET_DVR_HEATMAP_INFO m_pStruHeatMapInfo;
	NET_DVR_HEATMAP_INFO m_struHeatMapInfo;

	static DWORD WINAPI GetHeatMapInfoThread(LPVOID lpVehInfo);
	void AddHeatMapDlg(char* lpInterBuff);
	CComboBox m_comInfoType;
    CComboBox m_comboStatisticalModel;
    float m_fConfidence;
    CComboBox m_comboUploadHeatMapResultType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHEATMAPCFG_H__FAA08680_BF8D_4456_AABF_224251DC4DB5__INCLUDED_)
