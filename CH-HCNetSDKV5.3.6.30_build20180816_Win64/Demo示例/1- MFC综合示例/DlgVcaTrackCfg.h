#if !defined(AFX_DLGVCATRACKCFG_H__7466C5FB_D67C_4714_AF03_615CC334E5DD__INCLUDED_)
#define AFX_DLGVCATRACKCFG_H__7466C5FB_D67C_4714_AF03_615CC334E5DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaTrackCfg.h : header file
//
#include "PTZButton1.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgVcaTrackCfg dialog

class CDlgVcaTrackCfg : public CDialog
{
// Construction
public:
	CDlgVcaTrackCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaTrackCfg)
	enum { IDD = IDD_DLG_VCA_TRACK_CFG };
	CComboBox	m_comboConfMode;
	CComboBox   m_cmbChannel;
	BOOL	m_bEnableCalibration;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaTrackCfg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaTrackCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnPreview();
	afx_msg void OnRadioAlarmTrack();
	afx_msg void OnCheckCalibration();
	afx_msg void OnBtnSetCalibration();
	afx_msg void OnRadioTargetTrack();
	afx_msg void OnSelchangeComboConfMode();
	afx_msg void OnRadioManualTrack();
	afx_msg void OnBtnGetCalibration();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG	m_lServerID;   
    int     m_iDevIndex;    
    int		m_iChannel;     
    long    m_lPlayHandle; 
    NET_DVR_TRACK_CFG   m_struTrackCfg;   
    NET_DVR_TRACK_MODE  m_struTrackMode;    

    CPTZButton1 m_btnPtzUp;
    CPTZButton1 m_btnPtzDown;
    CPTZButton1 m_btnPtzLeft;
    CPTZButton1 m_btnPtzRight;
    CPTZButton1 m_btnZoomIn;//zoom in
	CPTZButton1 m_btnZoomOut;//zoom out

public:
    BOOL GetTrackCfg();   
  
    BOOL SetTrackCfg();
    
    BOOL GetTrackMode();
    
    BOOL SetTrackMode();
    
    void ShowTrackModeWnd(NET_DVR_TRACK_MODE struTrackMode);

    long StartRealPlay();
    BOOL StopRealPlay();
    void EnableWnd(BOOL bEnable);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCATRACKCFG_H__7466C5FB_D67C_4714_AF03_615CC334E5DD__INCLUDED_)
