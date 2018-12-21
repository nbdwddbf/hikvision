#if !defined(AFX_DLGMASTERSLAVETRACKING_H__F14CEFD2_564A_4D98_8724_B80FD67EC9D9__INCLUDED_)
#define AFX_DLGMASTERSLAVETRACKING_H__F14CEFD2_564A_4D98_8724_B80FD67EC9D9__INCLUDED_
#include "VcaCommonOperations.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMasterSlaveTracking.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMasterSlaveTracking dialog

class CDlgMasterSlaveTracking : public CDialog,public CVcaCommonOperations
{
// Construction
public:
	CDlgMasterSlaveTracking(CWnd* pParent = NULL);   // standard constructor
	~CDlgMasterSlaveTracking();
// Dialog Data
	//{{AFX_DATA(CDlgMasterSlaveTracking)
	enum { IDD = IDD_DLG_MASTER_SLAVE_TRACKING };
    CComboBox	m_comboChannel;
	CComboBox	m_comboTrackMode;
	CComboBox	m_comboCalibMode;
	CListCtrl	m_lstCalib;
	CComboBox	m_comboSlaveCameraID;
	int		m_iTrackingTime;
	int		m_iCoefficient;
    int		m_iHorValue;
    int		m_iVerValue;
    int     m_dwChannel;
    float	m_fInitialP;
    float	m_fInitialT;
    float	m_fInitialZ;
    float	m_fAdjustP;
    float	m_fAdjustT;
    float	m_fAdjustZ;
    float	m_fLeftposX;
    float	m_fLeftposY;
    float	m_fRightposX;
    float	m_fRightposY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMasterSlaveTracking)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMasterSlaveTracking)
	afx_msg void OnBtnLoginSlave1();
	afx_msg void OnBtnPreviewSlave();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnPtz();
	afx_msg void OnBtnReflashSlaveStatus();
	afx_msg void OnBtnTackingratio();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnRefush();
	afx_msg void OnBtnTrackcfg();
	afx_msg void OnBtnCalib();
	afx_msg void OnBtnCalibDel();
	afx_msg void OnSelchangeComboTrackmode();
	afx_msg void OnBtnControlPtzManualtrace();
	afx_msg void OnBtnTackInitposition();
	afx_msg void OnSetTrackratio();
	afx_msg void OnBtnGetTrackratio();
    afx_msg void OnButtonPtzAdjust();
    afx_msg void OnBUTTONAdjustPTZ();
    afx_msg void OnButtonGetHumanCalib();
    afx_msg void OnButtonSetHumanCalib();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	

public:
    LONG m_lChannel;
    LONG m_lLoginID;
	LONG m_lPlayHandle[5];
	BOOL Play(NET_DVR_CLIENTINFO* struClientInfo, LONG loginID, int index);
	BOOL SlaveLoginPlay(char *sDVRIP, WORD wDVRPort, char *sUserName, char *sPassword, NET_DVR_CLIENTINFO* struClientInfo, int index);
	LONG m_iDeviceIndex;
    char m_szStatusBuf[ISAPI_STATUS_LEN];
    LONG m_lUserID[5];
	CRect   m_rcWnd;
	NET_DVR_SLAVECAMERA_COND m_struSlaveCameraCond;
	NET_DVR_SLAVECAMERA_CFG m_struSlaveCameraCfg;
	NET_DVR_SLAVECAMERA_STATUS m_struSlaveCameraStatus;
	NET_DVR_SLAVECAMERA_CALIB_V50 m_struSlaveCameraCalibCfg;
	NET_DVR_TRACK_MODE m_struTrackMode;
	NET_DVR_TRACKING m_struTracking;

    NET_DVR_TRACK_INITPOSTION m_struTrackInitPostion;
    NET_DVR_MANUAL_TRACKRATIO m_struManualTrackRatio;

    //NET_DVR_SLAVECAMERA_CALIB_V50 m_struSlaveCameraCalibV50;

	BOOL m_bTrackMode;

    NET_VCA_POINT  m_struPoint;

	BOOL GetDataFromCalibList();
	BOOL SetDataToCalibList(NET_DVR_SLAVECAMERA_CALIB_V50* m_struSlaveCameraCalibCfg);
	BOOL SetPoint();

	void F_DrawFrame(HDC hDc);
	BOOL m_bCloseIn;
	BOOL m_bMouseMove;
    NET_VCA_POINT m_struTrackPoint;
	NET_VCA_POLYGON m_struRegionTemp;

    NET_DVR_BV_CALIB_POSITION m_struBvCalibPosotion;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMASTERSLAVETRACKING_H__F14CEFD2_564A_4D98_8724_B80FD67EC9D9__INCLUDED_)
