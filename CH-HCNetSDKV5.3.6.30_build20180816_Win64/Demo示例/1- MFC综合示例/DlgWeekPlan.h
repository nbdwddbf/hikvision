#if !defined(AFX_DLGWEEKPLAN_H__F0886D48_C36D_438F_9CB9_1C56437DB9CE__INCLUDED_)
#define AFX_DLGWEEKPLAN_H__F0886D48_C36D_438F_9CB9_1C56437DB9CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWeekPlan.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWeekPlan dialog

class CDlgWeekPlan : public CDialog
{
// Construction
public:
	CDlgWeekPlan(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWeekPlan)
	enum { IDD = IDD_DLG_ACCESSCARD_WEEKPLAN };
	CListCtrl	m_lstTemplate;
	CListCtrl	m_lstHolidayPlan;
	CComboBox	m_cmbDeviceTypeS;
	CComboBox	m_cmbGroupIndexP;
	CComboBox	m_cmbDeviceTypeP;
	CComboBox	m_cmbDeviceTypeG;
	CComboBox	m_cmbGroupIndex;
	CComboBox	m_cmbVerifyH;
	CComboBox	m_cmbDoorStatusH;
	CComboBox	m_cmbTimeSegmentH;
	CComboBox	m_cmbDeviceTypeH;
	COleDateTime	m_DTStartTime;
	COleDateTime	m_DTEndTime;
	CComboBox	m_cmbVerify;
	CComboBox	m_cmbDoorStatus;
	CComboBox	m_cmbTimeSegment;
	CComboBox	m_cmbDeviceType;
	CComboBox	m_cmbDay;
	DWORD	m_dwPlanNo;
	BOOL	m_BEnable;
	BOOL	m_BTSEnable;
	BOOL	m_BEnableH;
	BOOL	m_BTSEnableH;
	COleDateTime	m_dtEndDate;
	COleDateTime	m_dtStartDate;
	COleDateTime	m_dtEndTimeH;
	COleDateTime	m_dtStartTimeH;
	DWORD	m_dwPlanNoH;
	BOOL	m_BEnableG;
	CString	m_csGroupName;
	DWORD	m_dwGroupNo;
	DWORD	m_dwGroupPlanNo;
	BOOL	m_BEnableP;
	DWORD	m_dwGroupNoP;
	CString	m_csTemplateName;
	DWORD	m_dwTemplateNo;
	DWORD	m_dwWeekPlanNoP;
	DWORD	m_dwTemplatePlanNo;
	DWORD	m_dwDoorNo;
	CString	m_csDoorOrCardNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWeekPlan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWeekPlan)
	virtual BOOL OnInitDialog();
	afx_msg void OnButGet();
	afx_msg void OnButSet();
	afx_msg void OnSelchangeTimeSegment();
	afx_msg void OnButGetHoliday();
	afx_msg void OnButSetHoliday();
	afx_msg void OnSelchangeTimesegmentH();
	afx_msg void OnButAchgGet();
	afx_msg void OnButAchgSet();
	afx_msg void OnSelchangeGroupIndex();
	afx_msg void OnButAcptGet();
	afx_msg void OnButAcptSet();
	afx_msg void OnSelchangeGroupindexP();
	afx_msg void OnButAcspGet();
	afx_msg void OnButAcspSet();
	afx_msg void OnSelchangeAcspDevicetype();
	afx_msg void OnSelchangeDay();
	afx_msg void OnClickLstHolidayplan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEdtAchgGroupno();
	afx_msg void OnKillfocusEdtAchgGroupno();
	afx_msg void OnClickLstAcwpTemplate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEdtAcptGroupno();
	afx_msg void OnButAcwpTimesegementSet();
	afx_msg void OnButAcwpTimesegementH();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID; 
    LONG m_lDeviceID; 

private:
   NET_DVR_WEEK_PLAN_CFG m_struPlanCfg; 
   NET_DVR_HOLIDAY_PLAN_CFG m_struPlanCfgH;  
   NET_DVR_HOLIDAY_GROUP_CFG m_struGroupCfg;  
   NET_DVR_PLAN_TEMPLATE m_struTemplateCfg; 
   NET_DVR_WEEK_PLAN_COND m_struPlanCond;
   NET_DVR_HOLIDAY_PLAN_COND m_struPlanCondH;
   NET_DVR_HOLIDAY_GROUP_COND m_struGroupCond;
   NET_DVR_PLAN_TEMPLATE_COND m_struTemplateCond;
   int m_iLastSel; 
   int m_iLastSelH; 
   int m_iLastGroupIndex; 
   int m_iLastGroupIndexP; 
   void UpdateTimeSegment(BYTE byDay = 0, BYTE byTimeSegment = 0); 
   void UpdateTimeSegmentH(BYTE byTimeSegment = 0); 
   void SaveTimeSegment(DWORD dwSel); 
   void SaveTimeSegmentH(DWORD dwSelH); 

   BOOL CheckDate(const NET_DVR_SIMPLE_DAYTIME& struItem);
   BOOL CheckDate(const NET_DVR_DATE& struItem);

   int m_iCurGroupNo; 
   void UpdateLstGroupNo(); 
   int m_iCurGroupNoP; 
   void UpdateLstGroupNoP();  
public:
   int m_iWeekPlanLocalController;
   int m_iHolidayPlanLocalController;
   int m_iHolidayGroupLocalController;
   int m_iPlanTemplateLocalController;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWEEKPLAN_H__F0886D48_C36D_438F_9CB9_1C56437DB9CE__INCLUDED_)
