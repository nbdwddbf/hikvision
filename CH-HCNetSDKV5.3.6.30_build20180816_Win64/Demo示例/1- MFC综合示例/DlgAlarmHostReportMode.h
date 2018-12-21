#if !defined(AFX_DLGALARMHOSTREPORTMODE_H__29D6F479_2656_4ED9_8245_777672AF171C__INCLUDED_)
#define AFX_DLGALARMHOSTREPORTMODE_H__29D6F479_2656_4ED9_8245_777672AF171C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostReportMode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostReportMode dialog
const int g_struCheckSend[6] =
{
	IDC_CHECK_SEND1,
	IDC_CHECK_SEND2,
	IDC_CHECK_SEND3,
	IDC_CHECK_SEND4,
	IDC_CHECK_SEND5,
	IDC_CHECK_SEND6
};

//6个中心组 * 每个中心4个通道
const int g_struMode[24] = 
{
	IDC_COMBO_MODE1,
	IDC_COMBO_MODE2,
	IDC_COMBO_MODE3,
	IDC_COMBO_MODE4,
	IDC_COMBO_MODE5,
	IDC_COMBO_MODE6,
	IDC_COMBO_MODE7,
	IDC_COMBO_MODE8,
	IDC_COMBO_MODE9,
	IDC_COMBO_MODE10,
	IDC_COMBO_MODE11,
	IDC_COMBO_MODE12,
	IDC_COMBO_MODE13,
	IDC_COMBO_MODE14,
	IDC_COMBO_MODE15,
	IDC_COMBO_MODE16,
	IDC_COMBO_MODE17,
	IDC_COMBO_MODE18,
	IDC_COMBO_MODE19,
	IDC_COMBO_MODE20,
	IDC_COMBO_MODE21,
	IDC_COMBO_MODE22,
	IDC_COMBO_MODE23,
	IDC_COMBO_MODE24
};

const int g_struNetCard[24] =
{
    IDC_COMBO_NETCARD1,
    IDC_COMBO_NETCARD2,
    IDC_COMBO_NETCARD3,
    IDC_COMBO_NETCARD4,
    IDC_COMBO_NETCARD5,
    IDC_COMBO_NETCARD6,
    IDC_COMBO_NETCARD7,
    IDC_COMBO_NETCARD8,
    IDC_COMBO_NETCARD9,
    IDC_COMBO_NETCARD10,
    IDC_COMBO_NETCARD11,
    IDC_COMBO_NETCARD12,
    IDC_COMBO_NETCARD13,
    IDC_COMBO_NETCARD14,
    IDC_COMBO_NETCARD15,
    IDC_COMBO_NETCARD16,
    IDC_COMBO_NETCARD17,
    IDC_COMBO_NETCARD18,
    IDC_COMBO_NETCARD19,
    IDC_COMBO_NETCARD20,
    IDC_COMBO_NETCARD21,
    IDC_COMBO_NETCARD22,
    IDC_COMBO_NETCARD23,
    IDC_COMBO_NETCARD24
};


class CDlgAlarmHostReportMode : public CDialog
{
// Construction
public:
	CDlgAlarmHostReportMode(CWnd* pParent = NULL);   // standard constructor
	~CDlgAlarmHostReportMode();
	void EnableCheckWindow(DWORD dwCenterIndex);
	char szLan[1024];
	void InitComboBox();
	DWORD m_dwStatusList[MAX_CENTERGROUP_NUM];
	char* m_lpOutBuffer;
	DWORD m_dwBufLen;
	DWORD m_dwCenterNo[MAX_CENTERGROUP_NUM];
// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostReportMode)
	enum { IDD = IDD_DLG_ALARMHOST_REPORTMODE };
	CListCtrl	m_listZoneReport;
	CListCtrl	m_listNonZoneReport;
	CComboBox	m_cmCenter;
	CComboBox	m_cmDataType;
	BOOL	m_bValid;
	BOOL	m_bCheckSend1;
	BOOL	m_bCheckSend2;
	BOOL	m_bCheckSend3;
	BOOL	m_bCheckSend4;
	BOOL	m_bCheckSend5;
	BOOL	m_bCheckSend6;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostReportMode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_iDeviceIndex;
	long m_lUserID;
	LPNET_DVR_ALARMHOST_REPORT_CENTER_CFG_V40 m_pStruReportCenter;
	int m_iCenterNum;
	int m_iChanNum; //中心组个数*每个中心的通道数
	void SetReportMode();
	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostReportMode)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboCenter();
	afx_msg void OnBtnSure();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnMultiSet();
	afx_msg void OnBtnSingleGet();
	afx_msg void OnBtnMultiGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTREPORTMODE_H__29D6F479_2656_4ED9_8245_777672AF171C__INCLUDED_)
