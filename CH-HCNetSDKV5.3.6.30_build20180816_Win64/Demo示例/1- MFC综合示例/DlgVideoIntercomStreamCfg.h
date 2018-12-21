#if !defined(AFX_DLGVIDEOINTERCOMSTREAMCFG_H__D7B11406_B85D_411A_AED1_36D13491A740__INCLUDED_)
#define AFX_DLGVIDEOINTERCOMSTREAMCFG_H__D7B11406_B85D_411A_AED1_36D13491A740__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVideoIntercomStreamCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomStreamCfg dialog

class CDlgVideoIntercomStreamCfg : public CDialog
{
// Construction
public:
	CDlgVideoIntercomStreamCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVideoIntercomStreamCfg)
	enum { IDD = IDD_DLG_VIDEO_INTERCOM_STREAM };
	CComboBox	m_cmbVideoType;
	CComboBox	m_comboChannelID;
	CString	m_strDeviceID;
	CString	m_strDeviceName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVideoIntercomStreamCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVideoIntercomStreamCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeComboChannelId();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lServerID;
	LONG m_iDevIndex;
	NET_DVR_VIDEOINTERCOM_STREAM m_struStreamCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIDEOINTERCOMSTREAMCFG_H__D7B11406_B85D_411A_AED1_36D13491A740__INCLUDED_)
