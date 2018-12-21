#if !defined(AFX_DLGGETALLSENSORJOINT_H__BE6FC260_AE11_4422_B595_1A0A83F49971__INCLUDED_)
#define AFX_DLGGETALLSENSORJOINT_H__BE6FC260_AE11_4422_B595_1A0A83F49971__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGetAllSensorJoint.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGetAllSensorJoint dialog

class CDlgGetAllSensorJoint : public CDialog
{
// Construction
public:
	CDlgGetAllSensorJoint(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGetAllSensorJoint)
	enum { IDD = IDD_DLG_GET_ALL_SENSOR_JOINT };
	CListCtrl	m_listSensorJoint;
	//}}AFX_DATA

	NET_DVR_ALARMHOST_SENSOR_JOINT_CFG m_struAlarmHostSensorJointCfg;
	DWORD m_iDeviceIndex;
	LONG m_lUserID;
	long m_lHandle;
	BOOL m_bGetNext;
	HANDLE	m_hGetInfoThread;
	DWORD m_iRowCount;
	char m_sTemp[256];
	void AddInfoToDlg();
	static DWORD WINAPI GetConfigThread (LPVOID lpArg);
	BOOL OnInitDialog();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGetAllSensorJoint)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGetAllSensorJoint)
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGETALLSENSORJOINT_H__BE6FC260_AE11_4422_B595_1A0A83F49971__INCLUDED_)
