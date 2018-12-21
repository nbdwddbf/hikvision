#if !defined(AFX_DLGINFODIFFUSIONVOLUM_H__F4370CDA_E25D_4251_AC15_FF0250DC89C9__INCLUDED_)
#define AFX_DLGINFODIFFUSIONVOLUM_H__F4370CDA_E25D_4251_AC15_FF0250DC89C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionVolum.h : header file
//
#include "InfoDiffusionParamsConvert.h"
#define MAX_LEN_XML 10*1024*1024 //xml最大长度

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionVolum dialog

class CDlgInfoDiffusionVolum : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionVolum(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionVolum)
	enum { IDD = IDD_DLG_INFODIFFUDION_VOLUM };
	CListCtrl	m_listTerminal;
	CListCtrl	m_listGroup;
	CComboBox	m_cmbOperType;
	CListCtrl	m_listSpan;
	CComboBox	m_cmbWeekday;
	CComboBox	m_cmbPlanType;
	DWORD	m_dwVolum;
	COleDateTime	m_dtDate;
	COleDateTime	m_dtTime;
	COleDateTime	m_dtTimeEnd;
	COleDateTime	m_dtDateEnd;
	DWORD	m_dwGetID;
	DWORD	m_dwGroupId;
	DWORD	m_dwTerminalId;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionVolum)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionVolum)
	afx_msg void OnBtnPlanSpanAdd();
	afx_msg void OnBtnPlanSpanDel();
	afx_msg void OnBtnPlanSpanMod();
	afx_msg void OnBtnSwitchPlanExit();
	afx_msg void OnSelchangeComboPlanType();
	afx_msg void OnSelchangeComboWeekday();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnClickListSpan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnTerAdd();
	afx_msg void OnBtnTerDel();
	afx_msg void OnBtnTerMod();
	afx_msg void OnBtnVolueGet();
	afx_msg void OnBtnVolumeSet();
	afx_msg void OnClickListGroup(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListTerminal(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnGroupAdd();
	afx_msg void OnBtnGroupDel();
	afx_msg void OnBtnGroupMod();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    LONG m_lUserID;
    int m_iDeviceIndex;
    
    NET_DVR_VOLUME_PLAN_CFG m_struVolumeCfg;
    int m_nCurSelSpan;
    int m_nCurSelGroup;
    int m_nCurSelTerminal;
    
    char* m_pOutputXmlBuffer;
    
public:
    void UpdateList();
    void InitVolumePlanList();
    void RefreshVolumeSpanList(NET_DVR_VOLUME_PLAN *lpVolume, CString strPlanType, int nWeekday = -1/*当strPlanType为weekly时有效*/);
    void RefreshPlanList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONVOLUM_H__F4370CDA_E25D_4251_AC15_FF0250DC89C9__INCLUDED_)
