#if !defined(AFX_DLGVCABEHAVIORCALIBRATE_H__A37BCC5D_59B0_4123_9FD5_5EBB0355B867__INCLUDED_)
#define AFX_DLGVCABEHAVIORCALIBRATE_H__A37BCC5D_59B0_4123_9FD5_5EBB0355B867__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaBehaviorCalibrate.h : header file
//
#include "Picture.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBehaviorCalibrate dialog

class CDlgVcaBehaviorCalibrate : public CDialog
{
// Construction
public:
	CDlgVcaBehaviorCalibrate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaBehaviorCalibrate)
	enum { IDD = IDD_DLG_VCA_BEHAVIOR_CALIBRATE };
	CComboBox	m_comboCalibrationMode;
	CComboBox	m_comboChkType;
	CButton	m_ChkCalibrate;
	CStatic	m_staticPic;
	float	m_fCameraHeight;
	float	m_fCameraAngle;
	float	m_fCameraHorizon;
	BOOL	m_bAngle;
	BOOL	m_bHeight;
	BOOL	m_bHorizon;
	BOOL	m_bEanbleCal;
	float	m_fHeight;
	float	m_fLength;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaBehaviorCalibrate)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaBehaviorCalibrate)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnCheckCalibrate();
	afx_msg void OnBtnSave();
	afx_msg void OnSelchangeComboChecktype();
	afx_msg void OnBtnSetCameraHeight();
	afx_msg void OnRadioHeight();
	afx_msg void OnRadioLength();
	afx_msg void OnBtnRefresh();
	afx_msg void OnButtonReCapture();
	afx_msg void OnSelchangeComboCalibrationMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	long	m_lServerID;
	int		m_iDevIndex;
	int		m_lChannel;
    
    NET_DVR_CALIBRATION_CFG m_struCalibrateCfg;
    NET_DVR_BEHAVIOR_OUT_CALIBRATION  m_struBehaOutCal;		//calibrate list
    NET_DVR_BEHAVIOR_IN_CALIBRATION m_struBehaviorInCalibration;
    NET_DVR_LINE_SEGMENT    m_struVerifyLineSeg;      
    
	CPicture m_pic;	 
	char m_chFilename[256]; 
    
    int  m_iCalibrateLineType;   // 0 Height calibrate 1 length calibrate
    BOOL m_bMouseMove;
    CRect m_rcRect;
    int m_iCaliLineCount;
    int m_iInSampleCount;
    BOOL m_bDrawLine;
    
    LONG m_lPUServerID;
    LONG m_lPlayHandle;
    NET_DVR_PU_STREAM_CFG m_struPuStream;
    
    BOOL GetCursetCalibrate();
    void DrawBehaviorInCalibrate(HDC hDc, const NET_DVR_BEHAVIOR_IN_CALIBRATION& struInCalibrate);
    void DrawBehaviorOutCalibrate(HDC hDc, const NET_DVR_BEHAVIOR_OUT_CALIBRATION&  struOutCalibrate);
	BOOL SaveCursetCalibrate();
	//verift
	void RecordCurCheckPointPos(CPoint point);

	BOOL CaptureBmp();

    void GetCameraParamWnd(NET_DVR_CAMERA_PARAM& struCameraParam);
    void SetCameraParamWnd(NET_DVR_CAMERA_PARAM& struCameraParam);

    void InitWnd();
    void SetCalibrateTypeToWnd(int nCalibrateType);
    int GetCalibrateTypeFromWnd();
    void DrawCalibrateLine(HDC hDC, NET_DVR_LINE_SEGMENT const *lpLineSegment);
    BOOL PreDrawVerifyLine(MSG* pMsg, CPoint& pt);
    BOOL PreDrawOutCalibrate(MSG* pMsg,CPoint& pt);
    BOOL PreDrawInCalibrate(MSG* pMsg,CPoint& pt);
    
    BOOL GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream);
    LONG StartPlay();
    BOOL StopPlay();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCABEHAVIORCALIBRATE_H__A37BCC5D_59B0_4123_9FD5_5EBB0355B867__INCLUDED_)
