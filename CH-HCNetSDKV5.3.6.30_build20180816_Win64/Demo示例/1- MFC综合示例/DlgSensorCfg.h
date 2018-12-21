#if !defined(AFX_DLGSENSORCFG_H__F828A3D7_9DAD_4922_9746_CF2F341F7054__INCLUDED_)
#define AFX_DLGSENSORCFG_H__F828A3D7_9DAD_4922_9746_CF2F341F7054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSensorCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSensorCfg dialog

class CDlgSensorCfg : public CDialog
{
// Construction
public:
	CDlgSensorCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSensorCfg)
	enum { IDD = IDD_DLG_SENSORCFG };
	CComboBox	m_cmSensorStandard;
	CListCtrl	m_listOsdChan;
	CComboBox	m_comboSensorType;
	CComboBox	m_comboLineMode4;
	CComboBox	m_comboLineMode3;
	CComboBox	m_comboLineMode2;
	CComboBox	m_comboLineMode1;
	CComboBox	m_comboSensorIndex;
    CString	m_csSensorName;
	BOOL	m_bValid;
    float	m_fLineValue1;
	float	m_fLineValue2;
	float	m_fLineValue3;
	float	m_fLineValue4;
	float	m_fMeasureHigh;
	float	m_fMeasureLow;
	float	m_fSensorValue;
    float   m_fOriginalValue;
	BOOL	m_bEnable;
	float	m_fSensitive;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSensorCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSensorCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetSensorcfg();
	afx_msg void OnSelchangeComboSensorIndex();
	afx_msg void OnBtnConfirm();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnBtnGetValue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    DWORD   m_dwSensorNum;  
    LONG    m_lChanNum;
    NET_DVR_SENSOR_INFO m_struSensorInfo;
    NET_DVR_ALARMHOST_ABILITY m_struDevAbility;
	NET_DVR_SENSOR_ALARM m_struSensorAlarm;

    BOOL SetSensorCfg();
    BOOL GetSensorCfg();
    void InitWnd();
    
    BOOL GetSensorInfoFromWnd(NET_DVR_SENSOR_INFO &strusSensorInfo);
    BOOL SetSensorInfoToWnd(const NET_DVR_SENSOR_INFO &strusSensorInfo);

    BOOL SetSensorDate(NET_DVR_SENSOR_ALARM& struSensorAlarm);

    BOOL GetDevAbility(NET_DVR_ALARMHOST_ABILITY &struAbility);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSENSORCFG_H__F828A3D7_9DAD_4922_9746_CF2F341F7054__INCLUDED_)
