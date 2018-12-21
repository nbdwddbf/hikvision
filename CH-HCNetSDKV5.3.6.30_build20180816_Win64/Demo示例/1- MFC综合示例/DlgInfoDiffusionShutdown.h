#if !defined(AFX_DLGINFODIFFUSIONSHUTDOWN_H__3C1E4190_69C7_488D_B907_2B57017085F2__INCLUDED_)
#define AFX_DLGINFODIFFUSIONSHUTDOWN_H__3C1E4190_69C7_488D_B907_2B57017085F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionShutdown.h : header file
//
#include "InfoDiffusionParamsConvert.h"

#define MAX_LEN_XML 10*1024*1024 //xml最大长度
/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionShutdown dialog

class CDlgInfoDiffusionShutdown : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionShutdown(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionShutdown)
	enum { IDD = IDD_DLG_INFO_DIFFUSION_SHUTDOWN };
	CComboBox	m_cmbPlanType;
	CComboBox	m_cmbOperType;
	CListCtrl	m_listTerminal;
	CListCtrl	m_listGroup;
	CComboBox	m_cmbSwitchType;
	CListCtrl	m_listSpan;
	CComboBox	m_cmbWeekday;
	COleDateTime	m_tmDate;
	COleDateTime	m_tmTime;
	DWORD	m_dwGetID;
	DWORD	m_dwGroupId;
	DWORD	m_dwTerminalId;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionShutdown)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionShutdown)

	afx_msg void OnBtnPlanSpanAdd();
	afx_msg void OnBtnPlanSpanDel();
	afx_msg void OnBtnPlanSpanMod();
	afx_msg void OnSelchangeComboPlanType();
	afx_msg void OnSelchangeComboWeekday();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnClickListSpan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnGroupAdd();
	afx_msg void OnBtnGroupDel();
	afx_msg void OnBtnGroupMod();
	afx_msg void OnBtnTerAdd();
	afx_msg void OnBtnTerDel();
	afx_msg void OnBtnTerMod();
	afx_msg void OnClickListGroup(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListTerminal(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSwitchSet();
	afx_msg void OnBtnSwitchGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    LONG m_lUserID;
    int m_iDeviceIndex;
    
    NET_DVR_SWITCH_PLAN_CFG m_strSwitchCfg;
    int m_nCurSelSpan;
    int m_nCurSelGroup;
    int m_nCurSelTerminal;
    
	char* m_pOutputXmlBuffer;

public:
    void UpdateList();
    void InitSwitchPlanList();
	void RefreshSwitchSpanList(NET_DVR_SWITCH_PLAN *lpSwitch, CString strPlanType, int nWeekday = -1/*当strPlanType为weekly时有效*/);
    void RefreshPlanList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONSHUTDOWN_H__3C1E4190_69C7_488D_B907_2B57017085F2__INCLUDED_)
