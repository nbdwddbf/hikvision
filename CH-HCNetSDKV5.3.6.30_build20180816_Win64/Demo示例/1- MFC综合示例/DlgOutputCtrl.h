#pragma once


// CDlgOutputCtrl dialog
#include "PTZButton.h"
#include "afxcmn.h"
#include "afxwin.h"

class CDlgOutputCtrl : public CDialog
{
	DECLARE_DYNAMIC(CDlgOutputCtrl)

public:
	CDlgOutputCtrl(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgOutputCtrl();
	int m_iSelSpeed;
// Dialog Data
//	enum { IDD = IDD_DLG_OUTPUT_CTRL };

public:
	//{{AFX_DATA(CDlgOutputCtrl)
	enum { IDD = IDD_DLG_OUTPUT_CTRL };
	CComboBox	m_comboTrackType;
	CComboBox	m_comboPatternID;
	CSliderCtrl m_sliderVolume;
	CSliderCtrl m_sliderHue;//hue
	CSliderCtrl m_sliderSaturation;//saturation
	CSliderCtrl m_sliderContrast;//contrast
	CSliderCtrl m_sliderBrightness;//brightness
	CSliderCtrl m_sliderSharpness;
	CSliderCtrl m_sliderDenoising;
	CComboBox m_comboPreset;
	CComboBox m_comboCruise;
	CComboBox m_comboSpeed;
	BOOL	m_bChkTrack;
	BOOL	m_bChkPtzManualTrace;
	//}}AFX_DATA
	

	//{{AFX_VIRTUAL(CDlgOutputCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgOutputCtrl)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnCruiseAdjust();	
	afx_msg void OnBnClickedBtnAdjustPreset();
	afx_msg void OnBnClickedBtnDefaut();
	afx_msg void OnBnClickedBtnPresetSetup();	
	afx_msg void OnBnClickedBtnCruiseSetup();
	afx_msg void OnBnClickedBtnTrackStartMem();
	afx_msg void OnBnClickedBtnTrackStopMem();
	afx_msg void OnBnClickedBtnTrackRun();
	afx_msg void OnCbnSelchangeComboCruise();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSelchangeComboSpeed();
	afx_msg void OnBtnTrackDeleteId();
	afx_msg void OnBtnTrackDeleteAll();
	afx_msg void OnBtnTrackStop();
	afx_msg void OnBtnPtzParkaction();
	afx_msg void OnChkPtzManualtrace();
	afx_msg void OnEditchangeComboTracktype();
	afx_msg void OnBtnCruiseDel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
public:
	
	//The order of the below icon must be same as in CPTZButton
	CPTZButton m_btnPtzUp;
	CPTZButton m_btnPtzDown;
	CPTZButton m_btnPtzLeft;
	CPTZButton m_btnPtzRight;
	CPTZButton m_btnZoomIn;//zoom in
	CPTZButton m_btnZoomOut;//zoom out
	CPTZButton m_btnFocusNear;//focus near
	CPTZButton m_btnFocusFar;//focus far
	CPTZButton m_btnIrisOpen;//iris open
	CPTZButton m_btnIrisClose;//iris close
	int m_iCruiseRoute;
	void UpdateVideoEff();//update video parameters

};
