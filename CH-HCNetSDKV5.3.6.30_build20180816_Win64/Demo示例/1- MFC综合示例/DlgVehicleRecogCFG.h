#if !defined(AFX_DLGVEHICLERECOGCFG_H__FFCBF2E9_2232_46DB_95BF_63B6F0A9D162__INCLUDED_)
#define AFX_DLGVEHICLERECOGCFG_H__FFCBF2E9_2232_46DB_95BF_63B6F0A9D162__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVehicleRecogCFG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVehicleRecogCFG dialog

class CDlgVehicleRecogCFG : public CDialog
{
// Construction
public:
	CDlgVehicleRecogCFG(CWnd* pParent = NULL);   // standard constructor
	~CDlgVehicleRecogCFG();
// Dialog Data
	//{{AFX_DATA(CDlgVehicleRecogCFG)
	enum { IDD = IDD_DLG_VEHICLE_RECOG_CFG };
	CComboBox	m_comPicDataType;
	CListCtrl	m_lstVehicle;
	BOOL	m_bChkCompleteTask;
	BOOL	m_bChkExecutionTask;
	BOOL	m_bChkFacePicCopilot;
	BOOL	m_bChkFacePicMain;
	BOOL	m_bChkPicOverlay;
	BOOL	m_bChkPicUpdata;
	BOOL	m_bChkPlateBaffleCopilot;
	BOOL	m_bChkPlateBaffleMain;
	BOOL	m_bChkPlatePic;
	BOOL	m_bChkPlateRecog;
	BOOL	m_bChkSafetyBeltCopilot;
	BOOL	m_bChkSafetyBeltMain;
	BOOL	m_bChkSafetyBeltPicCopilot;
	BOOL	m_bChkSafetyBeltPicMain;
	BOOL	m_bChkVehicleBrand;
	BOOL	m_bChkVehicleColor;
	BOOL	m_bChkVehiclePic;
	BOOL	m_bChkVehicleType;
	BOOL	m_bChkWaitTask;
    BOOL    m_bChkPicUpdataURL;
    BOOL    m_bChkYellowCar;
    BOOL    m_bChkMobilePhone;
    BOOL    m_bChkPendant;
    BOOL    m_bChkDangerousVehicles;
    BOOL    m_bChkPDVS;
    CTime m_ctTimeSet;
    CTime m_ctDateSet;
    DWORD m_dwMilisecondSet;
    DWORD m_dwPostID;
	float	m_fx;
	float	m_fY;
	CString	m_csDataIndex;
	CString	m_csDataIndex2;
	CString	m_csLicense;
	CString	m_csPicPath;
	CString	m_csPicURL;
	float	m_fWidth;
	DWORD	m_dwTaskNo;
	DWORD	m_dwTaskNo2;
	float	m_fHeight;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVehicleRecogCFG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVehicleRecogCFG)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboPicDataType();
	afx_msg void OnBtnPath();
	afx_msg void OnBtnSetVehicleDetection();
	afx_msg void OnBtnGetVehicleDetection();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lChannel;
	LONG m_lUserID;
	LONG m_lDevIndex;

	LONG    m_lHandle;
	BOOL	m_bGetNext;
	HANDLE	m_hGetInfoThread;
	int		m_iStruCount;

	NET_DVR_VEHICLE_RECOG_COND m_struVehRecogCond;
	NET_DVR_VEHICLE_RECOG_CFG m_struVehRecogCfg;
	NET_DVR_VEHICLE_RECOG_TASK_COND m_struVehRecogTaskCond;
	NET_DVR_VEHICLE_RECOG_TASK_INFO m_struVehRecogTaskInfo;
    NET_DVR_VEHICLERECOG_TASK_RESULT m_struVehicleRecogTaskResult;

	static DWORD WINAPI GetVehInfoThread(LPVOID lpVehInfo);
	void AddVehDetectInfoToDlg(LPNET_DVR_VEHICLE_RECOG_TASK_INFO lpInter);
    CString m_cJsonPath;
    CString m_csDevDataIndex;
    afx_msg void OnBnClickedBtnJsonPath();
    afx_msg void OnBnClickedBtnSetVehiclerecogTaskV50();
protected:
    BYTE *m_pJsonInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVEHICLERECOGCFG_H__FFCBF2E9_2232_46DB_95BF_63B6F0A9D162__INCLUDED_)
