#if !defined(AFX_DLGGISINFO_H__25B6BF8B_D6B2_4F2E_946F_6D6704036340__INCLUDED_)
#define AFX_DLGGISINFO_H__25B6BF8B_D6B2_4F2E_946F_6D6704036340__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGISInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGISInfo dialog

class CDlgGISInfo : public CDialog
{
// Construction
public:
	CDlgGISInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGISInfo)
	enum { IDD = IDD_DLG_GIS_INFO };
	CComboBox	m_comPositionWorkMode;
	CComboBox	m_comGPSWorkMode;
	CComboBox	m_comGPSLongitudeType;
	CComboBox	m_comGPSLatitudeType;
	CComboBox	m_comLongitudeType2;
	CComboBox	m_comLatitudeType2;
	CComboBox	m_comLongitudeType;
	CComboBox	m_comLatitudeType;
	CComboBox	m_comSensorType;
	CComboBox	m_comControlType;
    CComboBox	m_comSensitivity;
	DWORD	m_dwLatitude;
	DWORD	m_dwLongitude;
	DWORD	m_dwTimeOut;
	float	m_fAzimuth;
	float	m_fFold;
	float	m_fHorizontalValue;
	float	m_fHorWidth;
	DWORD	m_dwLatitudeGIS;
	DWORD	m_dwLongitudeGIS;
	float	m_fMaxViewRadius;
	float	m_fVerticalValue;
	float	m_fVerWidth;
	float	m_fVisibleRadius;
	BOOL	m_chkUploadEnabled;
	BOOL	m_chkVoiceWarning;
	BOOL	m_chkSatelliteTimeEnable;
	BYTE	m_byLatitudeDegree;
	BYTE	m_byLatitudeDegree2;
	BYTE	m_byLatitudeMinute;
	BYTE	m_byLatitudeMinute2;
    BYTE    m_bySensitivity11;
	float	m_fLatitudeSec;
	float	m_fLatitudeSec2;
	BYTE	m_byLongitudeDegree;
	BYTE	m_byLongitudeDegree2;
	BYTE	m_byLongitudeMinute;
	BYTE	m_byLongitudeMinute2;
	float	m_fLongitudeSec;
	float	m_fLongitudeSec2;
	BOOL	m_bChkCentEnable;
	float	m_fPanPos;
	float	m_fTiltPos;
	float	m_fZoomPos;
	float	m_fDegree;
	int		m_iAzimuth;
	int		m_iTimeInterval;
	BOOL	m_bStreamEncryptionEnable;
	BYTE	m_byGPSLatitudeDegree;
	BYTE	m_byGPSLatitudeMinute;
	float	m_fGPSLatitudeSec;
	BYTE	m_byGPSLongitudeDegree;
	BYTE	m_byGPSLongitudeMinute;
	float	m_fGPSLongitudeSec;
	BOOL	m_chkStart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGISInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGISInfo)
	afx_msg void OnBtnSetCentralizedctrl();
	afx_msg void OnBtnGetCentralizedctrl();
	afx_msg void OnBtnGetGisinfo();
	afx_msg void OnBtnSetVandalproofalarm();
	afx_msg void OnBtnGetVandalproofalarm();
	afx_msg void OnBtnCompassCalibrateCtrl();
	afx_msg void OnBtnCompassNorthCtrl();
	afx_msg void OnBtnSetSatellitetime();
	afx_msg void OnBtnGetSatellitetime();
	afx_msg void OnBtnGetazimuth();
	afx_msg void OnBtnSetStreamencryption();
	afx_msg void OnBtnGetStreamencryption();
	afx_msg void OnBtnGetGps();
	afx_msg void OnBtnSetGps();
	afx_msg void OnSelchangeComboPositionWorkmode();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lChannel;
    LONG m_lUser;
    int  m_iDeviceIndex;
    char m_szStatusBuf[ISAPI_STATUS_LEN];
    void GetPosition(); 
    float m_PTZEXPan;
    float m_PTZEXTilt;
    float m_PTZEXZoom;
    float m_MinHorizontalValue;
    float MaxHorizontalValue;
    float m_MinVerticalValue;
    float m_MaxVerticalValue;
    BOOL m_PTZPosExEnable;
    DWORD m_PTZEXForcus;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGISINFO_H__25B6BF8B_D6B2_4F2E_946F_6D6704036340__INCLUDED_)
