#if !defined(AFX_DLGALARMHOSTLEDBRIGHTNESS_H__3B785800_219A_4EA4_AFFC_79A7335679C2__INCLUDED_)
#define AFX_DLGALARMHOSTLEDBRIGHTNESS_H__3B785800_219A_4EA4_AFFC_79A7335679C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostLEDBrightness.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostLEDBrightness dialog

class CDlgAlarmHostLEDBrightness : public CDialog
{
// Construction
public:
	CDlgAlarmHostLEDBrightness(CWnd* pParent = NULL);   // standard constructor
	int		m_iDeviceIndex;
	long	m_lUserID;
	char	m_szTemp[128];
	NET_DVR_LED_BRIGHTNESS_STEP m_struBrightnessStep;
	NET_DVR_LED_STATUS m_struLEDStatus;
	NET_DVR_CONTROL_PARAM m_struCtrlParam;
// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostLEDBrightness)
	enum { IDD = IDD_DLG_ALARMHOST_LED_BRIGHTNESS };
	CComboBox	m_cmTime;
	CSliderCtrl	m_sliderBrightness;
	int		m_radioCtrl;
	BOOL	m_chTimeValid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostLEDBrightness)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostLEDBrightness)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioManual();
	afx_msg void OnRadioTimer();
//	afx_msg void OnCustomdrawSliderBrightness(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnCopytoall();
	afx_msg void OnSelchangeComboBrightnessTime();
	afx_msg void OnBtnGetTimerBrightness();
	afx_msg void OnBtnSetTimerBrightness();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTLEDBRIGHTNESS_H__3B785800_219A_4EA4_AFFC_79A7335679C2__INCLUDED_)
