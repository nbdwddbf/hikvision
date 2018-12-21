#if !defined(AFX_DLGSENSORADDPREVIEW_H__492781DE_3ACF_48E5_B990_C1504B210849__INCLUDED_)
#define AFX_DLGSENSORADDPREVIEW_H__492781DE_3ACF_48E5_B990_C1504B210849__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSensorAddPreview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSensorAddPreview dialog
// typedef struct tagLOCAL_SENSOR_ADD_PREVIEW
// {
//     BYTE    byEnable;      // 是否启用
//     BYTE    byRes[3];       // 保留字节
//     NET_DVR_IPADDR struIPAddr;  //  IP地址
//     LONG    lChannel;       // 通道号
// }LOCAL_SENSOR_ADD_PREVIEW, *LPLOCAL_SENSOR_ADD_PREVIEW;

class CDlgSensorAddPreview : public CDialog
{
// Construction
public:
	CDlgSensorAddPreview(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSensorAddPreview)
	enum { IDD = IDD_DLG_SENSOR_ADD_PREVIEW };
	CComboBox	m_comboSensorIndex;
	BOOL	m_bEnable;
	int		m_iChannel;
	CString	m_csIPAddress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSensorAddPreview)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSensorAddPreview)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboSensorIndex();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnConfirm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
public:
    void    InitWnd();

    NET_DVR_ALARMHOST_ABILITY   m_struAlarmHostAbility;
    BOOL GetAlarmHostAbility(NET_DVR_ALARMHOST_ABILITY& struAlarmHostAbility);
    
//    LOCAL_SENSOR_ADD_PREVIEW m_struSensorAddPreview[MAX_ALARMHOST_ALARMIN_NUM];

    BOOL GetSensorAddPreviewList();
    BOOL SetSensorAddPreviewList();

    void GetSensorAddPreviewFromWnd(LOCAL_SENSOR_ADD_PREVIEW &struSensorAddPreview);
    void SetSensorAddPreviewToWnd(LOCAL_SENSOR_ADD_PREVIEW &struSensorAddPreview);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSENSORADDPREVIEW_H__492781DE_3ACF_48E5_B990_C1504B210849__INCLUDED_)
