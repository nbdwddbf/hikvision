#if !defined(AFX_DLGGETALLSENSOR_H__0FC11692_824B_42C8_ABF6_EB30454CFDCA__INCLUDED_)
#define AFX_DLGGETALLSENSOR_H__0FC11692_824B_42C8_ABF6_EB30454CFDCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGetAllSensor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgGetAllSensor dialog

class DlgGetAllSensor : public CDialog
{
// Construction
public:
	DlgGetAllSensor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgGetAllSensor)
	enum { IDD = IDD_DLG_GET_ALL_SENSOR };
	CListCtrl	m_listSensor;
	//}}AFX_DATA
	NET_DVR_SENSOR_INFO m_struSensorInfo;
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
	//{{AFX_VIRTUAL(DlgGetAllSensor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgGetAllSensor)
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGETALLSENSOR_H__0FC11692_824B_42C8_ABF6_EB30454CFDCA__INCLUDED_)
