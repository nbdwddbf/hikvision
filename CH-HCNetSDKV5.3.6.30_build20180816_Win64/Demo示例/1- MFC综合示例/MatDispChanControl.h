#if !defined(AFX_MATDISPCHANCONTROL_H__4E7F7877_C3A4_4A42_90EA_50614ED9FC17__INCLUDED_)
#define AFX_MATDISPCHANCONTROL_H__4E7F7877_C3A4_4A42_90EA_50614ED9FC17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatDispChanControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatDispChanControl dialog



typedef struct 
{
    DWORD dwResolutionSeq; 
    char *sResolutionName;  
}RESOLUTION;

const RESOLUTION struResolutin[] = 
{
	{0, "NOT_AVALIABLE"}, 
	{1, "(VGA)SVGA_60HZ"}, 
	{2, "(VGA)SVGA_75HZ"}, 
	{3, "(VGA)XGA_60HZ"}, 
	{4, "(VGA)XGA_70HZ"}, 
	{5, "(VGA)SXGA_60HZ"},
	{6, "(VGA)720P_60HZ"}, 
	{7, "(VGA)1080I_60HZ"}, 
	{8, "(VGA)1080P_30HZ"},
	{9, "(VGA)UXGA_30HZ"},
	{10, "(HDMI)XGA_60HZ"},
	{11, "(HDMI)SXGA_60HZ"}, 
	{12, "(HDMI)SXGA2_60HZ"},
	{13, "(HDMI)720P_60HZ"}, 
	{14, "(HDMI)720P_50HZ"}, 
	{15, "(HDMI)1080I_60HZ"},
	{16, "(HDMI)1080I_50HZ"}, 
	{17, "(HDMI)1080P_25HZ"},
	{18, "(HDMI)1080P_30HZ"}, 
	{19, "(HDMI)1080P_50HZ"}, 
	{20, "(HDMI)1080P_60HZ"}, 
	{21, "(HDMI)UXGA_60HZ"}, 
	{22, "(DVI)XGA_60HZ"}, 
	{23, "(DVI)SXGA_60HZ"}, 
	{24, "(DVI)SXGA2_60HZ"},
	{25, "(DVI)720P_60HZ"}, 
	{26, "(DVI)720P_50HZ"}, 
	{27, "(DVI)1080I_60HZ"},
	{28, "(DVI)1080I_50HZ"},
	{29, "(DVI)1080P_25HZ"}, 
	{30, "(DVI)1080P_30HZ"}, 
	{31, "(DVI)1080P_50HZ"}, 
	{32, "(DVI)1080P_60HZ"},
	{33, "(DVI)UXGA_60HZ"} 
};
class CMatDispChanControl : public CDialog
{
// Construction
public:
	void GetResolutionString(DWORD dwRes, char *lpResString);
	CMatDispChanControl(CWnd* pParent = NULL);   // standard constructor
	
	int  m_iDeviceIndex;
    LONG m_lServerID;
    NET_DVR_MATRIX_VOUTCFG m_DispChanCfg[MAX_ANALOG_CHANNUM];
    NET_DVR_MATRIX_ABILITY_V41 m_Ability;

	int m_iVGAResolutionNum;
	int m_iHDMIResolutionNum;
	int m_iDVIResolutionNum;

// Dialog Data
	//{{AFX_DATA(CMatDispChanControl)
	enum { IDD = IDD_DLG_MAT_DISPCHAN };
	CComboBox	m_BNCScaleCtrl;
	CComboBox	m_VedioFormatCtrl;
	CComboBox	m_comboAudioWindow;
	CComboBox	m_comboAudioWnw;
	CComboBox	m_ComboSubWindowDecChan;
	CComboBox	m_ComboSubWindowNum;
	CComboBox	m_ComboDispChan;
	CComboBox	m_ComboOpenAudio;
	CComboBox	m_ComboPicMode;
	CComboBox	m_ComboVgaResolution;
	BYTE	m_bySubWindowIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatDispChanControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMatDispChanControl)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombodispchan();
	afx_msg void OnExit();
	// afx_msg void OnCloseaudio();
	// afx_msg void OnOpenaudio();
	afx_msg void OnRenewwindow();
	afx_msg void OnEnlargewindow();
	afx_msg void OnDispchancfg();
	afx_msg void OnSelchangeCombosubwindownum();
	afx_msg void OnSure();
	afx_msg void OnSubsure();
	afx_msg void OnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATDISPCHANCONTROL_H__4E7F7877_C3A4_4A42_90EA_50614ED9FC17__INCLUDED_)
