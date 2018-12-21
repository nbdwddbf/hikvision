#if !defined(AFX_DLGALARMCAMCFG_H__0712FADA_821C_4C63_900F_0B3CF738BB21__INCLUDED_)
#define AFX_DLGALARMCAMCFG_H__0712FADA_821C_4C63_900F_0B3CF738BB21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmCamCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmCamCfg dialog

class CDlgAlarmCamCfg : public CDialog
{
// Construction
public:
	CDlgAlarmCamCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmCamCfg)
	enum { IDD = IDD_DLG_ALARM_CAMCFG };
	CComboBox	m_comboAlarmOffMode;
	CComboBox	m_comboAlarmChannel;
	CComboBox	m_comboPtzType;
	CComboBox	m_comboIndex;
	BOOL	m_bPtzEnable;
	BOOL	m_bEnable;
	int		m_iMonID;
	int		m_iNum;
	int		m_iPtzNo;
	int		m_iRecordTime;
	int		m_iResidentTime;
	int		m_iCamID;
	int		m_iAlarmOffCam;
	int		m_iAlarmOffMonitor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmCamCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmCamCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboIndex();
	afx_msg void OnBtnAlarmoffMon();
	afx_msg void OnBtnConfirm();
	afx_msg void OnBtnSetUp();
	afx_msg void OnSelchangeComboAlarmChannel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;

    NET_DVR_ALARM_CAM_CFG   m_struAlarmCamCfg;

    int     m_lAlarmCamIndex;
public:
    void InitComboIndex();
    void InitAlarmChanCombo();
    void InitPtzTypeCombo();
    void InitAlarmOffCombo();
    // IDC_COMBO_ALARMOFF_MODE
    void SetAlarmCamCfgToWnd(NET_DVR_ALARM_CAM_CFG &struAlarmCamCfg);
    void GetAlarmCamCfgFromWnd(NET_DVR_ALARM_CAM_CFG &struAlarmCamCfg);
    void SetAlarmCamInfoToWnd(NET_DVR_ALARM_CAM_INFO &struAlarmCamInfo);
    void GetAlarmCamInfoFromWnd(NET_DVR_ALARM_CAM_INFO &struAlarmCamInfo);

    BOOL SetAlarmCamCfg(NET_DVR_ALARM_CAM_CFG &sturAlarmCamCfg);
    BOOL GetAlarmCamCfg(NET_DVR_ALARM_CAM_CFG &sturAlarmCamCfg);

    BOOL AlarmOffMonitor();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMCAMCFG_H__0712FADA_821C_4C63_900F_0B3CF738BB21__INCLUDED_)
