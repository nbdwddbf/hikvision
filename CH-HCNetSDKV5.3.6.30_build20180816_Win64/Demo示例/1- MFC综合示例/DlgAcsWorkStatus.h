#include "afxwin.h"
#if !defined(AFX_DLGACSWORKSTATUS_H__E57FEE0C_4968_46AB_8489_90B3C6E4FC7A__INCLUDED_)
#define AFX_DLGACSWORKSTATUS_H__E57FEE0C_4968_46AB_8489_90B3C6E4FC7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAcsWorkStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAcsWorkStatus dialog

class CDlgAcsWorkStatus : public CDialog
{
// Construction
public:
	CDlgAcsWorkStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAcsWorkStatus)
	enum { IDD = IDD_DLG_ACS_WORK_STATUS };
	CComboBox	m_comboIndicatorLightStatus;
	CListCtrl	m_lstArmStatus;
	CListCtrl	m_listDoor;
	CListCtrl	m_listCardReader;
	CListCtrl	m_listCaseSensor;
	CListCtrl	m_listAlarmOut;
	CListCtrl	m_listAlarmIn;
	CComboBox	m_comboPowerSupplyMode;
    CComboBox	m_cmbBatteryChargeStatus;
    CComboBox	m_cmbMasterChannelControllerStatus;
    CComboBox	m_cmbSlaveChannelControllerStatus;
	BOOL	m_bAntiSneak;
	BOOL	m_bHostAntiDismantle;
	BOOL	m_bLowBattery;
	BOOL	m_bMultiDoorInterlock;
	float	m_fBatteryVoltage;
	DWORD	m_dwCardNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAcsWorkStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAcsWorkStatus)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnUpdate();
	afx_msg void OnDlgExit();	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
    int m_iDeviceIndex;   

private:
    NET_DVR_ACS_WORK_STATUS_V50 m_struAcsWorkStatus;
    void UpdateControlData();
    
public:
    CComboBox m_cmbFireAlarmStatus;
    DWORD m_dwWhiteFaceNum;
    DWORD m_dwBlackFaceNum;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACSWORKSTATUS_H__E57FEE0C_4968_46AB_8489_90B3C6E4FC7A__INCLUDED_)
