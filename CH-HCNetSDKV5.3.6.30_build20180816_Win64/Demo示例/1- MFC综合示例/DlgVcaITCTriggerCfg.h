#if !defined(AFX_DLGVCAITCTRIGGERCFG_H__26EC1A7B_5A97_4F7A_83CA_340E7CACB8D0__INCLUDED_)
#define AFX_DLGVCAITCTRIGGERCFG_H__26EC1A7B_5A97_4F7A_83CA_340E7CACB8D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "VcaCommonOperations.h"
// DlgVcaITCTriggerCfg.h : header file
//

#define MAX_BUFFER_LEN   (32*1024)

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaITCTriggerCfg dialog

class CDlgVcaITCTriggerCfg : public CDialog,public CVcaCommonOperations
{
// Construction
public:
	CDlgVcaITCTriggerCfg(CWnd* pParent = NULL);   // standard constructor
	~CDlgVcaITCTriggerCfg();
    enum
	{
		DRAW_TYPE_NONE      = 0,          //不画图
	    DRAW_TYPE_LANE_BOUNDARY_LINE = 1, //车道边界线
        DRAW_TYPE_LANE_LINE   = 2,        //车道线
        DRAW_TYPE_PLATE_RECOG_RGN   = 3,   //牌识区别
        DRAW_TYPE_SNAP_LINE = 4    //抓拍线
	};
// Dialog Data
	//{{AFX_DATA(CDlgVcaITCTriggerCfg)
	enum { IDD = IDD_DLG_VCA_ITC_TRIGGER_CFG };
	CComboBox	m_cmbRoadType;
	CComboBox	m_comRegion;
	CComboBox	m_comProvince;
	CComboBox	m_comDetSceneID;
	CComboBox	m_comIONo;
	CComboBox	m_comTriggerType;
	CComboBox	m_comRelateChan;
	CComboBox	m_comSourceType;
	CComboBox	m_comTriggerMode;
	CComboBox	m_comChan;
	CComboBox	m_comboVehicleType;
	CComboBox	m_comboTimeType;
	CComboBox	m_comboSceneType;
	CComboBox	m_comboRecogType;
	CComboBox	m_comboRecogPos;
	CComboBox	m_comboLocateType;
	CComboBox	m_comboLaneUseageType;
	CComboBox	m_comboLaneNumber;
	CComboBox	m_comboLaneDirection;
	CComboBox	m_comboDriveDirection;
	CComboBox	m_comboCarDriveDirect;
	BOOL	m_bFarmVehicleRecog;
	BOOL	m_bMicroPlateRecog;
	BOOL	m_bPlateRecog;
	BOOL	m_bTriggerCfg;
	BOOL	m_bVehicleColorRecog;
	BOOL	m_bVehicleLogoRecog;
	BOOL	m_bViaVtcoil;
	CString	m_strProvinceName;
	BOOL	m_bFuzzyRecog;
	BOOL	m_bMotocarRecog;
	int		m_nAssociateLaneNO;
	BYTE	m_nLaneNum;
	CString	m_szSceneName;
	BOOL	m_bEnable;
	BOOL	m_bIpcHvt;
	DWORD	m_dwPlatePixelWidthMax;
	DWORD	m_dwPlatePixelWidthMin;
    CString	m_szFilePath;
	CString	m_strDownloadStatus;
	CString	m_strUploadStatus;
	DWORD	m_wDelayTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaITCTriggerCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaITCTriggerCfg)
	afx_msg void OnDestroy();
	afx_msg void OnBtnDrawLaneBoundaryLine();
	afx_msg void OnBtnDrawLaneLine();
	afx_msg void OnBtnDrawPlateRecogRgn();
	afx_msg void OnSelchangeComboLaneNumber();
	afx_msg void OnBtnSave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);;
	afx_msg void OnBtnEndDraw();
	afx_msg void OnSelchangeComboTriggerMode();
	afx_msg void OnSelchangeComboSourceType();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnGetCurtriggermode();
	afx_msg void OnBtnSetCurtriggermode();
	afx_msg void OnBtnGetCalibration();
	afx_msg void OnBtnBlackwhitelstUpload();
	afx_msg void OnBtnBlackwhitelstDownload();
	afx_msg void OnBtnBlackwhitelstDownloadStop();
	afx_msg void OnBtnBlackwhitelstUploadStop();
	afx_msg void OnBtnBlackwhitelistBrowse();
	afx_msg void OnSelchangeComboRoadType();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void DrawRgnFun(HDC hdc);
protected:
	void InitCtrlState();
protected:
	void LoadWndContent();
	void SaveWndContent();
    
	void LoadViaLaneWndContent(int nLaneIndex);
	void SaveViaLaneWndContent(int nLaneIndex);
	BOOL GetITCTriggerCfg();
	BOOL SetITCTriggerCfg();
//   	long StartRealPlay();  // 开始预览 
//     BOOL StopRealPlay();  // 停止预览
	static DWORD WINAPI UpLoadSendThread(LPVOID pParam);
private:
	int  m_iTriggerMode;
	LONG m_lPlayHandle;
	CRect m_rcPlayWnd;
	NET_ITC_TRIGGERCFG m_struItcTriggerCfg;
	int m_nCurDrawType;
	int m_nCurLaneIndex;
	int m_nDrawPointNum;
	BOOL m_bFirstDrawLaneBoundary;
	BOOL m_bFirstDrawLaneLine;
    BOOL m_bFirstDrawSnapLine;
	NET_DVR_CALIBRATION m_struCalibration;
	char m_szStatusBuf[ISAPI_STATUS_LEN];

	HANDLE	m_hFile;
 	LONG	m_lUploadHandle;
 	HANDLE	m_hUpLoadThread;
    DWORD	m_dwThreadId;
	LONG	m_lDownloadHandle;
 	LONG    m_timerHandle;
 	BOOL	m_bStop;
public:
    afx_msg void OnBnClickedBtnDrawSnapLine();
    BYTE m_bCountryIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAITCTRIGGERCFG_H__26EC1A7B_5A97_4F7A_83CA_340E7CACB8D0__INCLUDED_)
