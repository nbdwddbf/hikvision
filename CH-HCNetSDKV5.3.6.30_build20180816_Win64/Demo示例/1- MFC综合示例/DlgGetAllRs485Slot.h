#if !defined(AFX_DLGGETALLRS485SLOT_H__1ACE4726_0BB4_438A_89CF_AD8CF513CADF__INCLUDED_)
#define AFX_DLGGETALLRS485SLOT_H__1ACE4726_0BB4_438A_89CF_AD8CF513CADF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGetAllRs485Slot.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgGetAllRs485Slot dialog

class DlgGetAllRs485Slot : public CDialog
{
// Construction
public:
	DlgGetAllRs485Slot(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgGetAllRs485Slot)
	enum { IDD = IDD_DLG_GET_ALL_RS485_SLOT };
	CListCtrl	m_listRs485Slot;
	//}}AFX_DATA
	NET_DVR_ALARMHOST_RS485_SLOT_CFG m_struAlarmHostRs485SlotCfg;
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
	NET_DVR_DEVICE_TYPE_LIST m_struDevTypeList;
	BOOL GetDeviceTypeList(NET_DVR_DEVICE_TYPE_LIST& struDevTypeList);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgGetAllRs485Slot)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgGetAllRs485Slot)
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGETALLRS485SLOT_H__1ACE4726_0BB4_438A_89CF_AD8CF513CADF__INCLUDED_)
