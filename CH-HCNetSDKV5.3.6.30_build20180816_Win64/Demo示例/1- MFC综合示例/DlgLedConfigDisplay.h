#if !defined(AFX_DLGLEDCONFIGDISPLAY_H__7BD4C72E_82A6_4159_B0B4_7782C690CCF9__INCLUDED_)
#define AFX_DLGLEDCONFIGDISPLAY_H__7BD4C72E_82A6_4159_B0B4_7782C690CCF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLedConfigDisplay.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLedConfigDisplay dialog

class CDlgLedConfigDisplay : public CDialog
{
// Construction
public:
	CDlgLedConfigDisplay(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLedConfigDisplay)
	enum { IDD = IDD_DLG_LED_CONFIG_DISPLAY };
	CComboBox	m_cmbTestSignalType;
	CComboBox	m_cmbNoSignalMode;
	CComboBox	m_cmbDisplayType;
	CComboBox	m_cmbImageMode;
	CComboBox	m_cmbDisplayMode;
	BOOL	m_bTestSignalEnable;
	DWORD	m_dwEndCol;
	DWORD	m_dwEndRow;
	DWORD	m_dwStartCol;
	DWORD	m_dwStartRow;
	DWORD	m_dwSignalBlue;
	DWORD	m_dwSignalGreen;
	DWORD	m_dwSignalRed;
	DWORD	m_dwBlue;
	DWORD	m_dwBlueOffset;
	DWORD	m_dwContrast;
	DWORD	m_dwGreen;
	DWORD	m_dwGreenOffset;
	DWORD	m_dwHue;
	DWORD	m_dwLight;
	DWORD	m_dwPort;
	DWORD	m_dwRed;
	DWORD	m_dwRedOffset;
	DWORD	m_dwSaturation;
	DWORD	m_dwSharpness;
	DWORD	m_dwNoSignalOutputNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLedConfigDisplay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLedConfigDisplay)
	afx_msg void OnBtnNosignalGet();
	afx_msg void OnBtnNosignalSet();
	afx_msg void OnBtnTestsignalGet();
	afx_msg void OnBtnTestsignalSet();
	afx_msg void OnButDisplayParameterGet();
	afx_msg void OnButDisplayParameterSet();
	afx_msg void OnExit();
	afx_msg void OnSelchangeComboDisplayDisplayMode();
	afx_msg void OnSelchangeComboDisplayType();
	afx_msg void OnSelchangeComboTestsignalType();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;
	int  m_iDeviceIndex;
	int  m_iDisplayType;
	BYTE m_byDisplayMode;
	BYTE m_bySignalType;

public:
	void Init(LONG lUserID, int iDeviceIndex){m_lUserID = lUserID; m_iDeviceIndex = iDeviceIndex;};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLEDCONFIGDISPLAY_H__7BD4C72E_82A6_4159_B0B4_7782C690CCF9__INCLUDED_)
