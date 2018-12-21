// #if !defined(AFX_DLGALARMHOSTEXTERNALDEVLIMITVALUE_H__68C9889F_5D42_4BCB_B27A_9C55A96D27F5__INCLUDED_)
// #define AFX_DLGALARMHOSTEXTERNALDEVLIMITVALUE_H__68C9889F_5D42_4BCB_B27A_9C55A96D27F5__INCLUDED_

#include "afxwin.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmhostExternalDevLimitValue.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmhostPointCfg dialog

class CDlgAlarmhostPointCfg : public CDialog
{
// Construction
public:
	CDlgAlarmhostPointCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmhostPointCfg)
	enum { IDD = IDD_DLG_ALARMHOST_POINT_CFG };
	CListCtrl	m_listOSDIPChan;
	CComboBox	m_cmLimitLineType;
	CListCtrl	m_listOsdChan;
	CComboBox	m_cmVarType;
	CComboBox	m_cmVarNo;
	CComboBox	m_cmChanType;
	CButton	m_btnSet;
	CButton	m_btnGet;
	CComboBox	m_cmSlotIndex;
	CComboBox	m_cmChanIndex;
	CComboBox	m_comboLineMode4;
	CComboBox	m_comboLineMode3;
	CComboBox	m_comboLineMode2;
	CComboBox	m_comboLineMode1;
	float	m_fLineValue1;
	float	m_fLineValue2;
	float	m_fLineValue3;
	float	m_fLineValue4;
	float	m_fMeasureHigh;
	float	m_fMeasureLow;
	float	m_fSensitive;
	DWORD	m_dwPointNO;
	CString	m_csPointName;
	CString	m_csVarName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmhostPointCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmhostPointCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnGetPointCfg();
	afx_msg void OnBtnSetPointCfg();
	afx_msg void OnSelchangeComboChanType();
	afx_msg void OnBtnStop();
	afx_msg void OnSelchangeComboVarNo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	LONG m_lUserID;
	int m_iDeviceIndex;
    //用于保存某个点号下，NVR通道事件类型的数组---m_byNVRChanType[0]表示通道1的信息
    //m_byNVRChanType的值表示含义为：0-无效；1-支持录像；2-支持抓图；3支持录像和抓图
    BYTE m_byNVRChanType[MAX_LINKAGE_CHAN_NUM];
    BYTE m_byPicNum[MAX_LINKAGE_CHAN_NUM];
    WORD m_wRecTime[MAX_LINKAGE_CHAN_NUM];
	char m_sTemp[128];
	NET_DVR_ALARMHOST_ABILITY m_struAbility;

	NET_DVR_INPUT_INFO m_struInputInfo;
	int m_iItem;
	int m_iSubItem;
	//int m_iRowCount;
	long m_lHandle;
	BOOL m_bGetNext;
	int m_iVarCount;
	NET_DVR_ALARM_VARIABLE_CFG m_struVariCfg[256]; 
	HANDLE	m_hGetInfoThread;
	NET_DVR_ALARM_POINT_CFG	m_struPointCfg;
    NET_DVR_ALARM_LINKAGE_PARAM m_struAlarmLikageParam;
	DWORD dwStatusList;
	LONG m_lAnalogChannel;
	LONG m_lIPChanNum;

	static DWORD WINAPI GetConfigThread (LPVOID lpArg);
	void AddInfoToDlg();
	void InitWnd();
public:
    CComboBox m_cmNvrChanNo;
    CComboBox m_cmNvrChanEventType;
    afx_msg void OnCbnSelchangeComboAlarmNvrChannel();
    afx_msg void OnBnClickedBtnSaveAlarmNvrChanInfo();
    afx_msg void OnBnClickedBtnSetChanLinkageCfg();
    afx_msg void OnBnClickedBtnGetChanLinkageCfg();
    BYTE m_byLinkagePicCount;
    DWORD m_dwLinkageRecTime;
    CComboBox m_cmVariableCond;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#endif // !defined(AFX_DLGALARMHOSTEXTERNALDEVLIMITVALUE_H__68C9889F_5D42_4BCB_B27A_9C55A96D27F5__INCLUDED_)
