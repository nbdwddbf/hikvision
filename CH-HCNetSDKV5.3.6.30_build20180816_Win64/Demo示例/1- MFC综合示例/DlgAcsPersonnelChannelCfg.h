#if !defined(AFX_DLGACSPERSONNELCHANNELCFG_H__EF477F67_B0A2_4D9F_B1BB_D3872EA1B546__INCLUDED_)
#define AFX_DLGACSPERSONNELCHANNELCFG_H__EF477F67_B0A2_4D9F_B1BB_D3872EA1B546__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAcsPersonnelChannelCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgAcsPersonnelChannelCfg dialog

class DlgAcsPersonnelChannelCfg : public CDialog
{
// Construction
public:
	DlgAcsPersonnelChannelCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgAcsPersonnelChannelCfg)
	enum { IDD = IDD_DIALOG_PERSONNEL_CHANNEL_CFG };
	CComboBox	m_byScreenNo;
	CComboBox	m_byDegree;
	CComboBox	m_dwFirstRowPosition;
	CComboBox	m_dwFontSize;
	CComboBox	m_byScreenType;
	CComboBox	m_byEnableOfflineStatistics;
	CComboBox	m_byEnableStatistics;
	CComboBox	m_byResultType;
	CComboBox	m_byWorkMode;
	CComboBox	m_byOutMode;
	CComboBox	m_byInMode;
	CComboBox	m_channel;
	UINT	m_dwDoorNo;
	CString	m_strScreenDisplay;
	UINT	m_dwRowSpacing;
	UINT	m_dwColumnSpacing;
    CComboBox    m_cmbCountSignalStatisticalStandard;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgAcsPersonnelChannelCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    int m_iDeviceIndex;
    long m_lUserID;

	// Generated message map functions
	//{{AFX_MSG(DlgAcsPersonnelChannelCfg)
    virtual BOOL OnInitDialog();
	afx_msg void OnButtonGet();
	afx_msg void OnButtonSet();
	afx_msg void OnButtonPlatformVerifySet();
	afx_msg void OnButtonPersonStatisticsGet();
	afx_msg void OnButtonPersonStatisticsSet();
	afx_msg void OnButtonScreenDisplayGet();
	afx_msg void OnButtonScreenDisplaySet();
	afx_msg void OnButtonExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACSPERSONNELCHANNELCFG_H__EF477F67_B0A2_4D9F_B1BB_D3872EA1B546__INCLUDED_)
