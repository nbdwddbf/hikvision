#include "ATLComTime.h"
#if !defined(AFX_DLGRECPASSBACK_H__A8D55758_1F58_4F7C_BD70_154BE149EF1B__INCLUDED_)
#define AFX_DLGRECPASSBACK_H__A8D55758_1F58_4F7C_BD70_154BE149EF1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecPassBack.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRecPassBack dialog

class CDlgRecPassBack : public CDialog
{
// Construction
public:
	CDlgRecPassBack(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecPassBack)
	enum { IDD = IDD_DLG_REC_PASS_BACK };
	CComboBox	m_cmbTaskCtrl;
	CComboBox	m_cmbDelType;
	CListCtrl	m_listDelTaskInfo;
	CComboBox	m_cmbCheckType;
	CListCtrl	m_listAllTaskInfo;
	CString	m_csStreamID4;
	int		m_nChannel4;
	CString	m_csStatus;
	CListCtrl	m_listAddRecPassBackTask;
	COleDateTime	m_oleDateStart;
	COleDateTime	m_oleDateStop;
	COleDateTime	m_oleTimeStart;
	COleDateTime	m_oleTimeStop;
	int		m_nChannel2;
	CString	m_csStreamID2;
	int		m_nDelTaskID;
	CString	m_csDelStreamID;
	int		m_nDelChannel;
	CString	m_csDelStatus;
	BOOL	m_bChkRecPassBackSche;
	CString	m_csStreamIDPlan;
	int		m_nChannelPlan;
    COleDateTime	m_oleDateStart1;
    COleDateTime	m_oleDateStop1;
    COleDateTime	m_oleTimeStart1;
    COleDateTime	m_oleTimeStop1;
    BOOL m_bTimeRange;
    CString	m_csStreamIDGetAllTask;
    int		m_nChannelGetAllTask;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecPassBack)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRecPassBack)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAddTask();
	afx_msg void OnBtnDelTask();
	afx_msg void OnBtnSetTask();
	afx_msg void OnClickListAddRecPassbackTask(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnGetAllTask();
	afx_msg void OnBtnSetDelTask();
	afx_msg void OnBtnRemoveDelTask();
	afx_msg void OnBtnAddDelTask();
	afx_msg void OnSelchangeCmbDelType();
	afx_msg void OnClickListDelTaskInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnTaskCtrl();
	afx_msg void OnChkRecordPassBack();
	afx_msg void OnBtnRecordPassBackSetup();
	afx_msg void OnBtnPassBackSchedGet();
	afx_msg void OnBtnPassBackSchedSet();
    afx_msg void OnBnClickedBtnPassBackSchedGet2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	int m_iDevIndex;

	int		m_ilastDelTypeSel;
	LONG    m_lGetAllTaskHandle;
	BOOL	m_bGetAllTaskNext;
	HANDLE	m_hGetAllTaskThread;
	NET_DVR_RECORD_PASSBACK_MANUAL_TASK_RET m_struRecordPassBackTaskRet;
	
	static DWORD WINAPI GetAllTaskThread(LPVOID lpGetAllTask);
	void AddTaskInfoToDlg(LPNET_DVR_RECORD_PASSBACK_MANUAL_TASK_RET lpInter);

	LPNET_DVR_RECORD_PASSBACK_SCH_CFG m_pStruRecordPassBackSchCfg;
    LPNET_DVR_RECORD_PASSBACK_HISTORY_PLAN_CFG m_pStruRecordPassBackHistoryPlanCfg;
    DWORD m_dwTaskID;
    DWORD m_dwTaskIDGet;
    DWORD m_dwHistoryChannelPlan;
    BOOL m_bRecPassbackHistory;
    CString m_strStreamIDHistory;
    char    m_szStatusBuf[ISAPI_STATUS_LEN];
    afx_msg void OnBnClickedBtnRecordPassBackSetupHistory();
    afx_msg void OnBnClickedBtnPassBackSchedGetHistory();
    afx_msg void OnBnClickedBtnPassBackSchedSetHistory();
    afx_msg void OnBnClickedChkRecordPassBackHistory();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECPASSBACK_H__A8D55758_1F58_4F7C_BD70_154BE149EF1B__INCLUDED_)
