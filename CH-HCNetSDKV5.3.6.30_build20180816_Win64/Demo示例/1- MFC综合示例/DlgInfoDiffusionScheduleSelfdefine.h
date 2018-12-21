#if !defined(AFX_DLGINFODIFFUSIONSCHEDULESELFDEFINE_H__5EEC02F3_F334_4E99_B322_76FDA28BE479__INCLUDED_)
#define AFX_DLGINFODIFFUSIONSCHEDULESELFDEFINE_H__5EEC02F3_F334_4E99_B322_76FDA28BE479__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionScheduleSelfdefine.h : header file
//

#include "InfoDiffusionParamsConvert.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionScheduleSelfdefine dialog

class CDlgInfoDiffusionScheduleSelfdefine : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionScheduleSelfdefine(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionScheduleSelfdefine)
	enum { IDD = IDD_DLG_INFO_DIFFUSION_SCHEDULE_SELFDEFINE };
	CListCtrl	m_listSpan;
	COleDateTime	m_timeEndDate;
	COleDateTime	m_timeEndTime;
	COleDateTime	m_timeStartDate;
	COleDateTime	m_timeStartTime;
	DWORD	m_dwProgramID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionScheduleSelfdefine)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionScheduleSelfdefine)
	afx_msg void OnBtnCancel();
	afx_msg void OnBtnOk();
	afx_msg void OnBtnSpanAdd();
	afx_msg void OnBtnSpanDel();
	afx_msg void OnBtnSpanMod();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListSpan(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void InitializeData(NET_DVR_PLAY_SELDEFINE* lpSelfdefine);
	void SaveData(NET_DVR_PLAY_SELDEFINE* lpSelfdefine);
	void InitPlaySpanList();
	void RefreshPlaySpanList();
	
private:
	NET_DVR_PLAY_SELDEFINE m_struSeldefineSchedule[MAX_NUM_SELDEFINE];
	int m_nCurSelSpan;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONSCHEDULESELFDEFINE_H__5EEC02F3_F334_4E99_B322_76FDA28BE479__INCLUDED_)
