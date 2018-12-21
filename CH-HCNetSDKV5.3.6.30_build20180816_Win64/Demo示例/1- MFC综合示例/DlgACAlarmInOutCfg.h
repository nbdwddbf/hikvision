#if !defined(AFX_DLGACALARMINOUTCFG_H__3F80E700_496B_484A_98D7_F0AF22F6BFD4__INCLUDED_)
#define AFX_DLGACALARMINOUTCFG_H__3F80E700_496B_484A_98D7_F0AF22F6BFD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgACAlarmInOutCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgACAlarmInOutCfg dialog

class CDlgACAlarmInOutCfg : public CDialog
{
// Construction
public:
	CDlgACAlarmInOutCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgACAlarmInOutCfg)
	enum { IDD = IDD_DLG_AC_ALARMINANDOUT };
	CListCtrl	m_listAlarmIn;
	CComboBox	m_cmbSensiParam;
	CListCtrl	m_lstSirenOut;
	CListCtrl	m_lstAlarmOut;
	CComboBox	m_cmbDetector;
	CComboBox	m_cmbDefenseType;
	CComboBox	m_cmbAlarmOut;
	CComboBox	m_cmbAlarmIn;
	CString	m_csAlarmInName;
	DWORD	m_dwOutDelay;
	CString	m_csOutName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgACAlarmInOutCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgACAlarmInOutCfg)
	afx_msg void OnButAlarmInGet();
	afx_msg void OnButAlarmInSet();
	afx_msg void OnButAlarmOutGet();
	afx_msg void OnButAlarmOutSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnButAcAlarmoutClose();
	afx_msg void OnButAcAlarmoutOpen();
	afx_msg void OnButAcAlarmoutAllclose();
	afx_msg void OnButAcAlarmoutAllopen();
	afx_msg void OnButAlarmInSetupAlrm();
	afx_msg void OnButAlarmInCloseAlrm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG  m_lUserID; 
    LONG  m_lDeviceID; 
    NET_DVR_ALARMIN_SETUP m_struAlarmIn; 
    NET_DVR_ALARMHOST_ABILITY   m_struAlarmHostAbility;
protected:
    DWORD m_dwAlarmInNum; 
    DWORD m_dwAlarmOutNum; 

    void InitDetectorCombox(); 
    void InitArmTypeCombox(); 
    void InitList();
    void SetList(const NET_DVR_ALARMIN_PARAM &struAlarmInParam); 
    void GetList(NET_DVR_ALARMIN_PARAM &struAlarmInParam); 

    BOOL SetAlarmOut(LONG lAlarmOutPort, LONG lAlarmOutStatic);
    BOOL GetAlarmHostAbility(NET_DVR_ALARMHOST_ABILITY& struAlarmHostAbility);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACALARMINOUTCFG_H__3F80E700_496B_484A_98D7_F0AF22F6BFD4__INCLUDED_)
