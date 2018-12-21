#if !defined(AFX_DLGINFODIFFUSIONSCHEDULE_H__544B8FD4_F7D9_49C1_8BD8_04213CFCB3D1__INCLUDED_)
#define AFX_DLGINFODIFFUSIONSCHEDULE_H__544B8FD4_F7D9_49C1_8BD8_04213CFCB3D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionSchedule.h : header file
//

#include "InfoDiffusionParamsConvert.h"
#include "afxcmn.h"
#include "afxwin.h"

#define MAX_LEN_XML 10*1024*1024 //xml最大长度
#define TIMER_SCHEDULE_EXPORT_PROGRESS 1 //上传下载进度定时器

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionSchedule dialog

class CDlgInfoDiffusionSchedule : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionSchedule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionSchedule)
	enum { IDD = IDD_DLG_INFO_DIFFUSION_SCHEDULE };
	CComboBox	m_cmbApprove;
	CListCtrl	m_listSpan;
	CComboBox	m_cmbWeekday;
	CComboBox	m_cmbShareProp;
	CComboBox	m_cmbScheduleType;
	COleDateTime	m_timeEndDate;
	COleDateTime	m_timeEndTime;
	COleDateTime	m_timeStartDate;
	COleDateTime	m_timeStartTime;
	DWORD	m_dwScheduleID;
	CString	m_szScheduleName;
	CString	m_szScheduleRemarks;
	DWORD	m_dwProgramID;
	CString	m_szApproveRemarks;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionSchedule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionSchedule)
	afx_msg void OnBtnScheduleDel();
	afx_msg void OnBtnScheduleGet();
	afx_msg void OnBtnScheduleNew();
	afx_msg void OnBtnScheduleSet();
	afx_msg void OnBtnSpanAdd();
	afx_msg void OnBtnSpanDel();
	afx_msg void OnBtnSpanMod();
	afx_msg void OnClickListSpan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboScheduleType();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboWeekday();
	afx_msg void OnBtnReleaseManage();
	afx_msg void OnDestroy();
	afx_msg void OnBtnSelfdefineSchedule();
	afx_msg void OnBtnSearch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;


	NET_DVR_PLAY_SCHEDULE m_struSchedule;
	int m_nCurSelSpan;
	
	char* m_pOutputXmlBuffer;
    BOOL m_bExport;
    LONG m_lExportHandle;

public:
	void UpdateScheduleInfo();
	void InitPlaySpanList();
	void RefreshPlaySpanList(LPNET_DVR_PLAY_SCHEDULE lpSchedule, CString strScheduleType, int nWeekday = -1/*当strScheduleType为weekly时有效*/);
    CString m_csModeType;
    DWORD m_dwOrgNo;
    afx_msg void OnBnClickedBtnExport();
    DWORD WINAPI FileDownload(LPVOID pParam);
    CProgressCtrl m_ctrlProgress;
    CStatic m_statProgress;
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    int m_iDeviceIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONSCHEDULE_H__544B8FD4_F7D9_49C1_8BD8_04213CFCB3D1__INCLUDED_)
