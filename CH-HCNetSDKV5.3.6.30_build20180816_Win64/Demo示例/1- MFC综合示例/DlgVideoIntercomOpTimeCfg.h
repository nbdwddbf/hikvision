#if !defined(AFX_DLGVIDEOINTERCOMOPTIMECFG_H__3B06357F_AEB9_4C9D_B09D_44824C56F55A__INCLUDED_)
#define AFX_DLGVIDEOINTERCOMOPTIMECFG_H__3B06357F_AEB9_4C9D_B09D_44824C56F55A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVideoIntercomOpTimeCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomOpTimeCfg dialog

class CDlgVideoIntercomOpTimeCfg : public CDialog
{
// Construction
public:
	CDlgVideoIntercomOpTimeCfg(CWnd* pParent = NULL);   // standard constructor
    inline BOOL ValidIPv6(BYTE *ip);

// Dialog Data
	//{{AFX_DATA(CDlgVideoIntercomOpTimeCfg)
	enum { IDD = IDD_DLG_VIDEO_INTERCOM_OP_TIME_CFG };
	int		m_nMaxMessageTime;
	int		m_nMaxMonitoringTime;
	int		m_nMaxRingTime;
	int		m_nMaxTalkTime;
	int		m_dwCallForwardingTime;
	//}}AFX_DATA
	enum VIDEO_INTERCOM_DEV_TYPE_ENUM
	{
		ENUM_OUTDOOR_UNIT = 1, 
		ENUM_MANAGE_UNIT = 2, 
		ENUM_INDOOR_UNIT = 3,
		ENUM_FENCE_UNIT = 4,
        ENUM_VILLA_OUTDOOR_UNIT = 5,
        ENUM_AGAIN_UNIT = 6
	};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVideoIntercomOpTimeCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVideoIntercomOpTimeCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnRadioIndoor();
	afx_msg void OnRadioManage();
	afx_msg void OnRadioOutdoor();
	afx_msg void OnRadioFenceUnit();
	afx_msg void OnRadioAgainUnit();
	afx_msg void OnRadioVillaOutdoorUnit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void CheckRaidoBtn();
protected:
	BOOL GetVideoIntercomOpTimeCfg();
	BOOL SetVideoIntercomOpTimeCfg();
	void ShowParamToWnd(NET_DVR_VIDEO_INTERCOM_OPERATION_TIME_CFG* pOpTimeCfg);
	void GetParamFromWnd(NET_DVR_VIDEO_INTERCOM_OPERATION_TIME_CFG* pOpTimeCfg);
private:
	int m_nUnitType;
public:
	LONG m_lServerID;
	LONG m_iDevIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIDEOINTERCOMOPTIMECFG_H__3B06357F_AEB9_4C9D_B09D_44824C56F55A__INCLUDED_)
