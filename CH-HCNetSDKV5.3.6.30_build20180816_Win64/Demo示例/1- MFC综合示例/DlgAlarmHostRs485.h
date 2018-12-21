#include "afxwin.h"
#if !defined(AFX_DLGALARMHOSTRS485_H__1086D4FB_F079_4007_9FB7_C525B4F24283__INCLUDED_)
#define AFX_DLGALARMHOSTRS485_H__1086D4FB_F079_4007_9FB7_C525B4F24283__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostRs485.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostRs485 dialog

class CDlgAlarmHostRs485 : public CDialog
{
// Construction
public:
	CDlgAlarmHostRs485(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostRs485)
	enum { IDD = IDD_DLG_ALARMHOST_RS485_CFG };
	CComboBox	m_cmbCascadeDevAddr;
	CComboBox	m_cmSlotIndex;
	CComboBox	m_cmDeviceTypeSlot;
	CComboBox	m_cmDeviceProtocolSlot;
	CComboBox	m_comboAircondition485Index;
	CComboBox	m_comboAirConditionMode;
	CComboBox	m_comboWorkMode;
	CComboBox	m_comboDuplex;
	CComboBox	m_comboBaud;
	CComboBox	m_comboCheckBit;
	CComboBox	m_comboDataBit;
	CComboBox	m_comboStopBit;
	CComboBox	m_comboDeviceProto;
	CComboBox	m_comboDeviceType;
	CComboBox	m_comboFlowControl;
	CComboBox	m_comboRs485Index;
	CString	m_csName;
	BOOL	m_bEnableAirCondition;
	int		m_iTemprature;
	CString	m_csNameSlot;
	DWORD	m_dwDevAddr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostRs485)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostRs485)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboRs485Index();
	afx_msg void OnSelchangeComboDeviceType();
	afx_msg void OnBtnSetRs485Cfg();
	afx_msg void OnBtnTransparent();
	afx_msg void OnBtnSetAircondition();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeComboDeviceTypeSlot();
	afx_msg void OnBtnGetAirCondition();
	afx_msg void OnBtnGetRs485Cfg();
	afx_msg void OnBtnGetCascadeCfg();
	afx_msg void OnBtnSetCascadeCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public: // param
    LONG    m_lServerID;
    int     m_iDevIndex;
    LONG    m_lRs485Index;

    NET_DVR_ALARMHOST_ABILITY m_struDevAbility;
    NET_DVR_ALARM_RS485CFG m_struRs485Cfg;
    NET_DVR_DEVICE_TYPE_LIST m_struDevTypeList;
    NET_DVR_DEVICE_PROTO_LIST m_struDevProtoList;
	NET_DVR_ALARMHOST_RS485_SLOT_CFG m_stru485Slot;


    LONG    m_lDevType;
public: // fun
    void InitWnd();
    void Init485IndexCombo();
    void InitDeviceTypeCombo();
    void InitDeviceProtoCombo();
    void InitBaudCombo();
    void InitCheckBitCombo();
    void InitDataBitCombo();
    void InitStopBitCombo();
    void InitFlowControlCombo();
    void InitDuplexCombo();
    void InitWorkMode();
    void InitAir485Combo();
    void InitAirconditionModeCombo();
	void InitDeviceProtoComboSlot();
	void InitCascadeDeviceAddrCombo();
    void InitSerialTypeCombo();
	void InitModeCombo();
//     CComboBox	m_comboBaud;
//     CComboBox	m_comboCheckBit;
//     CComboBox	m_comboDataBit;
//     CComboBox	m_comboStopBit;
//     CComboBox	m_comboDeviceProto;
//     CComboBox	m_comboDeviceType;
//     CComboBox	m_comboFlowControl;
//     CComboBox	m_comboRs485Index;

    
    BOOL GetRs485Cfg(NET_DVR_ALARM_RS485CFG &struRs485Cfg);
    BOOL SetRs485Cfg(NET_DVR_ALARM_RS485CFG &struRs485Cfg);
    BOOL GetDeviceTypeList(NET_DVR_DEVICE_TYPE_LIST& struDevTypeList);
    BOOL GetDeviceProtoList(NET_DVR_DEVICE_PROTO_LIST& struDevProtoList); 

    void GetRs485CfgFromWnd(NET_DVR_ALARM_RS485CFG &struRs485Cfg);
    void SetRs485CfgToWnd(NET_DVR_ALARM_RS485CFG &struRs485Cfg);

    BOOL SetAirCondition(NET_DVR_AIR_CONDITION_PARAM &struAirCondition);

    //ÃÅ½û¸´ÓÃ×Ö¶Î
    int m_iRS485Num; 
    int m_i485SlotNum; 
    CComboBox m_cmbSerialType;
	CComboBox m_cmbMode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTRS485_H__1086D4FB_F079_4007_9FB7_C525B4F24283__INCLUDED_)
