#if !defined(AFX_DLGALARMHOSTSENSORLINKAGE_H__8F2F75DD_152B_4A21_BA16_B0AF5CC4B9CC__INCLUDED_)
#define AFX_DLGALARMHOSTSENSORLINKAGE_H__8F2F75DD_152B_4A21_BA16_B0AF5CC4B9CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmhostSensorLinkage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmhostSensorLinkage dialog

class CDlgAlarmhostSensorLinkage : public CDialog
{
// Construction
public:
	CDlgAlarmhostSensorLinkage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmhostSensorLinkage)
	enum { IDD = IDD_DLG_ALARMHOST_SENSOR_LINKAGE };
	CListCtrl	m_listSirenType;
	CListCtrl	m_listSensorType;
	CComboBox	m_cmAlarmOutChan;
	CComboBox	m_cmSensorIndex;
	CListCtrl	m_listSiren;
	CListCtrl	m_listAlarmOut;
	BOOL	m_chJointByAlarmType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmhostSensorLinkage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmhostSensorLinkage)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeComboSensorIndex();
	afx_msg void OnCheckJointByAlarmtype();
	afx_msg void OnBtnSave();
	afx_msg void OnSelchangeComboSensorJointAlarmout();
	afx_msg void OnBtnGetaAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void AddInfoToStru();
	static DWORD WINAPI GetConfigThread (LPVOID lpArg);
	int m_iDeviceIndex;
	long m_lUserID;
	NET_DVR_ALARMHOST_ABILITY m_struAlarmHostAbility;
	void InitListWnd() ;
	NET_DVR_ALARMHOST_SENSOR_JOINT_CFG m_struSensor;
	NET_DVR_ALARMHOST_SENSOR_JOINT_CFG m_struSensorlist[256];
	char m_szTemp[128];
	long m_lHandle;
	BOOL m_bGetNext;
	BOOL m_bGetAll;
	HANDLE	m_hGetInfoThread;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTSENSORLINKAGE_H__8F2F75DD_152B_4A21_BA16_B0AF5CC4B9CC__INCLUDED_)
