#if !defined(AFX_DLGREMOTEVIDEOINPUT_H__CBAECF49_DB72_4023_875E_2ED51905ED4C__INCLUDED_)
#define AFX_DLGREMOTEVIDEOINPUT_H__CBAECF49_DB72_4023_875E_2ED51905ED4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRemoteVideoInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteVideoInput dialog

#define MAX_RANGE 255

class CDlgRemoteVideoInput : public CDialog
{
// Construction
public:
	CDlgRemoteVideoInput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRemoteVideoInput)
	enum { IDD = IDD_DLG_REMOTE_VIDOE_INPUT };
	CSliderCtrl	m_sliderSharpness;
	CSliderCtrl	m_sliderDenoising;
	CSliderCtrl	m_sliderSaturation;
	CSliderCtrl	m_sliderHue;
	CSliderCtrl	m_sliderContrast;
	CSliderCtrl	m_sliderBrightness;
	CComboBox	m_comboMode;
	//}}AFX_DATA

	LONG    m_lUserID;
    LONG    m_lChannel;
	DWORD   m_dwDevIndex;
	LONG    m_lRealHandle;
	NET_DVR_VIDEO_INPUT_EFFECT m_struVidowInEffect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRemoteVideoInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteVideoInput)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonUpdate();
	afx_msg void OnButtonSetup();
	afx_msg void OnButtonExit();
	afx_msg void OnSelchangeComboInputMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREMOTEVIDEOINPUT_H__CBAECF49_DB72_4023_875E_2ED51905ED4C__INCLUDED_)
