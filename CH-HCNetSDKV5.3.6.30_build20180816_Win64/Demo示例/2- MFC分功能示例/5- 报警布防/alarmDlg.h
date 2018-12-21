// AlarmDlg.h : header file
//

#if !defined(AFX_AlarmDLG_H__9D6C2E2F_9F51_4B21_90A2_6FAD4269E430__INCLUDED_)
#define AFX_AlarmDLG_H__9D6C2E2F_9F51_4B21_90A2_6FAD4269E430__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

void CALLBACK MessageCallback(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void* pUser);

#define	HPR_OK			(0)
#define HPR_ERROR		(-1)

typedef signed char		HPR_INT8;
typedef unsigned char	HPR_UINT8;
typedef signed short	HPR_INT16;
typedef unsigned short	HPR_UINT16;
typedef signed int		HPR_INT32;
typedef unsigned int	HPR_UINT32;
typedef void*			HPR_VOIDPTR;
typedef signed long		HPR_LONG;
typedef unsigned long	HPR_ULONG;

#define HPR_VOID void

#ifndef  HPR_BOOL
#define HPR_BOOL HPR_INT32
#define HPR_TRUE  1
#define HPR_FALSE 0
#endif
/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg dialog

class CAlarmDlg : public CDialog
{
// Construction
public:
	CAlarmDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarmDlg)
	enum { IDD = IDD_ALARM_DIALOG };
	CListCtrl	m_listDev;
	CListCtrl	m_listAlarmInfo;
	CIPAddressCtrl	m_ctrlDeviceIP;
	CString	m_DeviceName;
	short	m_DevicePort;
	CString	m_Password;
	CString	m_UserName;
	UINT m_iDeviceIndex;
	//}}AFX_DATA
    
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	FILE * m_fLog;
	FILE * m_fAlarm;
    COleDateTime m_curTime;
    

	LRESULT OnWMProcAlarm(WPARAM wParam, LPARAM lParam);
	LRESULT OnWMAddLog(WPARAM wParam, LPARAM lParam);
	void ProcAlarmV30(WPARAM wParam, LPARAM lParam);
	void ProcAlarm(WPARAM wParam, LPARAM lParam);
    void AddLog(int iDeviceIndex, int iLogType, const char* format, ...);
	UINT GetFileThread(LPVOID pParam);
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAlarmDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnectDevice();
	afx_msg void OnConnectDeviceDel();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClean();
	afx_msg void OnClickListDev(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRdblclkListDev(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonRecSetAlarm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AlarmDLG_H__9D6C2E2F_9F51_4B21_90A2_6FAD4269E430__INCLUDED_)
