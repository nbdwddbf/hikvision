#if !defined(AFX_DLGITSMONITOR_H__6FF43051_AEDE_4CFF_A89A_650EEB36141C__INCLUDED_)
#define AFX_DLGITSMONITOR_H__6FF43051_AEDE_4CFF_A89A_650EEB36141C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgITSMonitor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgITSMonitor dialog

class CDlgITSMonitor : public CDialog
{
// Construction
public:
	CDlgITSMonitor(CWnd* pParent = NULL);   // standard constructor
    ~CDlgITSMonitor();
// Dialog Data
	//{{AFX_DATA(CDlgITSMonitor)
	enum { IDD = IDD_DLG_ITS_MONITOR };
	CComboBox	m_comSwitch;
	CComboBox	m_comDeviceType2;
	CComboBox	m_comDeviceID2;
	CListCtrl	m_lstSensor;
	CComboBox	m_comSwitchStatus;
	CComboBox	m_comSensorStatus;
	CComboBox	m_comQueryType;
	CComboBox	m_comDeviceType;
	CComboBox	m_comDeviceID;
	float	m_fMaxCur;
	float	m_fMaxHum;
	float	m_fMaxTmp;
	float	m_fMaxVol;
	float	m_fMinCur;
	float	m_fMinHum;
	float	m_fMinTmp;
	float	m_fMinVol;
	COleDateTime	m_startDate;
	COleDateTime	m_startTime;
	COleDateTime	m_stopDate;
	COleDateTime	m_stopTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgITSMonitor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgITSMonitor)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGetSensorCfg();
	afx_msg void OnSelchangeComboQueryType();
	afx_msg void OnSelchangeComboDeviceType();
	afx_msg void OnBtnSensorSwitch();
	afx_msg void OnSelchangeComboDeviceType2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG    m_lServerID;
    int     m_iDevIndex;
	LONG    m_lChannel;

    BOOL m_bGetNext;
    LONG m_lHandle;
	HANDLE m_hGetInfoThread;
    
    NET_DVR_SENSOR_COND m_struSensorCond;
    NET_DVR_SENSOR_CFG m_struSensorCfg;

    char    m_szStatusBuf[ISAPI_STATUS_LEN];

    static DWORD WINAPI GetSensorResultThread(LPVOID lpPdcResult);
	void AddSensorResultLst(LPNET_DVR_SENSOR_CFG lpInter);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGITSMONITOR_H__6FF43051_AEDE_4CFF_A89A_650EEB36141C__INCLUDED_)
