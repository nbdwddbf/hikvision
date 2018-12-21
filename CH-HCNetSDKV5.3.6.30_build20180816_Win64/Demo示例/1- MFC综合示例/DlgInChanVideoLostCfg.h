#if !defined(AFX_DLGINCHANVIDEOLOSTCFG_H__71D1E6CB_8098_4AC4_B6FA_E77B5C760493__INCLUDED_)
#define AFX_DLGINCHANVIDEOLOSTCFG_H__71D1E6CB_8098_4AC4_B6FA_E77B5C760493__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInChanVideoLostCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInChanVideoLostCfg dialog

class CDlgInChanVideoLostCfg : public CDialog
{
// Construction
public:
	CDlgInChanVideoLostCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInChanVideoLostCfg)
	enum { IDD = IDD_DLG_INCHAN_REOMTE_VILOST };
    CTreeCtrl	m_treeAlarmOut;
    BOOL m_bChkMonitorAlarm;
    BOOL m_bChkAudioAlarm;
    BOOL m_bChkReportCenter;
    BOOL m_bChkInvokeAlarmOut;
    BOOL m_bChkEmapAlarmOut;
    CComboBox m_comboWeekday;
    CComboBox m_comboCopyDay;
    BOOL m_bChkInvokeJpegCapture;
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
	CComboBox	m_cmbChannel;
    BOOL	m_bChkPicToFtp;
	BOOL	m_bEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInChanVideoLostCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInChanVideoLostCfg)
	afx_msg void OnBtnSet();
    afx_msg void OnBnClickedChkVilostInvokeAlarmOut();
    afx_msg void OnBnClickedBtnVilostDayOk();
    afx_msg void OnBnClickedBtnVilostDayCopy();
    afx_msg void OnCbnSelchangeComboVilostWeekday();
    afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnPaint();
	afx_msg void OnBtnAlarmoutSelectall();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    
    int	m_iChanShowNum;
    LONG	m_lLoginID;	
    DWORD	m_dwAlarmOutNum;
    int	m_iDevIndex;
    BOOL TimeTest();
    //	BOOL m_bAlarmOut[MAX_ALARMOUT_V30];
   	BOOL   *m_pbAlarmOut;
    void CreateTree();
    NET_DVR_HOLIDAY_HANDLE m_struVLHolidayHandle;
    BOOL GetVLHolidayHandle(NET_DVR_HOLIDAY_HANDLE &struHolidayHandle);
    BOOL SetVLHolidayHandle(NET_DVR_HOLIDAY_HANDLE &struHolidayHandle);
    NET_DVR_PICCFG_V30 m_struPicCfg;
    NET_DVR_TRIAL_SYSTEM_INFO m_struSystemInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINCHANVIDEOLOSTCFG_H__71D1E6CB_8098_4AC4_B6FA_E77B5C760493__INCLUDED_)
