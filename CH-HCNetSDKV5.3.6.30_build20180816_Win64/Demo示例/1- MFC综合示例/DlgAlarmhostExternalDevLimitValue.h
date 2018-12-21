#if !defined(AFX_DLGALARMHOSTEXTERNALDEVLIMITVALUE_H__68C9889F_5D42_4BCB_B27A_9C55A96D27F5__INCLUDED_)
#define AFX_DLGALARMHOSTEXTERNALDEVLIMITVALUE_H__68C9889F_5D42_4BCB_B27A_9C55A96D27F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmhostExternalDevLimitValue.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmhostExternalDevLimitValue dialog

class CDlgAlarmhostExternalDevLimitValue : public CDialog
{
// Construction
public:
	CDlgAlarmhostExternalDevLimitValue(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmhostExternalDevLimitValue)
	enum { IDD = IDD_DLG_ALARMHOST_EXTERNAL_DEVICE_LIMIT_VALUE };
	CListCtrl	m_listLimitValue;
	CEdit	m_Edit;
	CComboBox	m_cmSlotIndex;
	CComboBox	m_cmDeviceType;
	CComboBox	m_cmChanIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmhostExternalDevLimitValue)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmhostExternalDevLimitValue)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboDeviceType();
	afx_msg void OnDblclkListLimitValue(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEditTemp();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	LONG m_lUserID;
	int m_iDeviceIndex;
	char m_sTemp[128];
	NET_DVR_ALARMHOST_ABILITY m_struAbility;
	NET_DVR_ALARMHOST_EXTERNAL_DEVICE_LIMIT_VALUE m_struLimitValue;
	NET_DVR_ALARMHOST_UPS_LIMIT_VALUE m_struUPSLimitValue;
	NET_DVR_ALARMHOST_TEMP_HUMIDITY_SENSOR_LIMIT_VALUE m_struSensorLimitValue;
	void SetUpsLimitValue();
	void SetTempHumiSensorLimitValue();
	void SaveLimitValue();
	int m_iItem;
	int m_iSubItem;
	int m_iRowCount;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTEXTERNALDEVLIMITVALUE_H__68C9889F_5D42_4BCB_B27A_9C55A96D27F5__INCLUDED_)
