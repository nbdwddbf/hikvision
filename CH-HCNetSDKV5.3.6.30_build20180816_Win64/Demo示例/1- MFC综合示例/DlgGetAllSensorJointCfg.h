#if !defined(AFX_DLGGETALLSENSORJOINTCFG_H__636EB0DB_4B61_4C9B_AE95_567A38E09B88__INCLUDED_)
#define AFX_DLGGETALLSENSORJOINTCFG_H__636EB0DB_4B61_4C9B_AE95_567A38E09B88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGetAllSensorJointCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgGetAllSensorJointCfg dialog

class DlgGetAllSensorJointCfg : public CDialog
{
// Construction
public:
	DlgGetAllSensorJointCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgGetAllSensorJointCfg)
	enum { IDD = IDD_DLG_GET_ALL_SENSOR_JOINT };
	//}}AFX_DATA
	NET_DVR_ALARMHOST_SENSOR_JOINT_CFG m_struAlarmHostSensorJoint;
	DWORD m_iDeviceIndex;
	LONG m_lUserID;
	long m_lHandle;
	BOOL m_bGetNext;
	HANDLE	m_hGetInfoThread;
	DWORD m_iRowCount;
	char m_sTemp[256];
	void AddInfoToDlg();
	//static DWORD WINAPI GetConfigThread (LPVOID lpArg);
	BOOL OnInitDialog();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgGetAllSensorJointCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgGetAllSensorJointCfg)
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGETALLSENSORJOINTCFG_H__636EB0DB_4B61_4C9B_AE95_567A38E09B88__INCLUDED_)
