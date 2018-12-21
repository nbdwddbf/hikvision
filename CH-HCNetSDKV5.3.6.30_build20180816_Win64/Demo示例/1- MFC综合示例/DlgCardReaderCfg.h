#include "afxwin.h"
#if !defined(AFX_DLGCARDREADERCFG_H__A7DE20F8_FEBB_4919_87A1_B62B03464A76__INCLUDED_)
#define AFX_DLGCARDREADERCFG_H__A7DE20F8_FEBB_4919_87A1_B62B03464A76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCardReaderCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCardReaderCfg dialog

class CDlgCardReaderCfg : public CDialog
{
// Construction
public:
	CDlgCardReaderCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCardReaderCfg)
	enum { IDD = IDD_DLG_AC_CARDREADERCFG };
	CComboBox	m_cmbType;
	CComboBox	m_cmbBuzzerPolarity;
	CComboBox	m_cmbErrorLed;
	CComboBox	m_cmbOKLed;
    CComboBox	m_cmbFPImageQuality;
    CComboBox	m_cmbFPContrastTimeOut;
    CComboBox	m_cmbFPRecogizeInterval;
    CComboBox	m_cmbFPMatchFastMode;
    CComboBox	m_cmbFPModuleSensitive;
    CComboBox	m_cmbFPModuleLightCondition;
    CComboBox	m_cmbFaceRecogizeTimeOut;
    CComboBox	m_cmbFaceRecogizeInterval;
    CComboBox   m_cmbLivingBodyDetect;
    DWORD   m_byFaceContrastThreshold;
    DWORD   m_byFaceContrastThreshold2;
    DWORD   m_byFaceQuality;
    DWORD   m_wFaceImageSensitometry;
    DWORD   m_byDayFaceMatchThresholdN;
    DWORD   m_byNightFaceMatchThresholdN;
    CComboBox   m_cmbFaceRecogizeEnable;
    CString m_csCardReaderDescription;
	BOOL	m_BEnable;
    BOOL	m_BFingerPrint;
    BOOL	m_BFace;
    BOOL	m_BVena;
	BOOL	m_BEnableFailAlarm;
	DWORD	m_dwCardReaderNo;
	DWORD	m_dwSwipeInterval;
	DWORD	m_dwPressTimeOut;
	DWORD	m_dwMaxReadCardFailNum;
	BOOL	m_BEnableTamperCheck;
	DWORD	m_dwOfflineCheckTime;
    DWORD	m_byFingerPrintCheckLevel;
    DWORD	m_dwBuzzerTime;
    CComboBox   m_cmbLiveDetLevel;
    CComboBox   m_cmbFaceContrastMotionDetLevel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCardReaderCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCardReaderCfg)
	afx_msg void OnButGet();
	afx_msg void OnButSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    int m_iUserID; 
    int m_iDeviceID; 
    CComboBox m_cmbCardReaderChannel;
    int m_iLocalControllerID;
    int m_iLocalControllerReaderID;
    BOOL m_bUseLocalController;
    CComboBox m_cmbSecurityLevel1;
    CComboBox m_cmbSecurityLevelN;
    BYTE m_byLiveDetAntiAttackCntLimit;
    CComboBox m_cmbLiveDetLevelSet;
    CComboBox m_cmbEnvirMode;
    CComboBox m_cmbEnableAntiAttackProtect;
    DWORD m_dwFpCapicity;
    DWORD m_dwFpNum;
    BOOL m_bIsSupport;
    DWORD m_dwBlackListThreshold;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCARDREADERCFG_H__A7DE20F8_FEBB_4919_87A1_B62B03464A76__INCLUDED_)
