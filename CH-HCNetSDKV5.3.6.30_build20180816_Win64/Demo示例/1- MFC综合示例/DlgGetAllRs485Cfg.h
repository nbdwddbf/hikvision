#if !defined(AFX_DLGGETALLRS485CFG_H__95BC0450_221F_40A8_B032_AF9F3EA55EC6__INCLUDED_)
#define AFX_DLGGETALLRS485CFG_H__95BC0450_221F_40A8_B032_AF9F3EA55EC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGetAllRs485Cfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgGetAllRs485Cfg dialog

class DlgGetAllRs485Cfg : public CDialog
{
// Construction
public:
	DlgGetAllRs485Cfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgGetAllRs485Cfg)
	enum { IDD = IDD_DLG_GET_ALL_RS485 };
	CListCtrl	m_listRs485;
	//}}AFX_DATA
	NET_DVR_ALARM_RS485CFG m_struAlarmRs485Cfg;
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
	BOOL GetDeviceTypeList(NET_DVR_DEVICE_TYPE_LIST& struDevTypeList);
	NET_DVR_DEVICE_TYPE_LIST m_struDevTypeList;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgGetAllRs485Cfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgGetAllRs485Cfg)
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGETALLRS485CFG_H__95BC0450_221F_40A8_B032_AF9F3EA55EC6__INCLUDED_)
