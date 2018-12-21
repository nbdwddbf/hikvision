#include "afxwin.h"
#if !defined(AFX_DLGTHERMALDOUBLESPECTRUM_H__287F2624_ADE1_448E_B359_53ECB7ADBD40__INCLUDED_)
#define AFX_DLGTHERMALDOUBLESPECTRUM_H__287F2624_ADE1_448E_B359_53ECB7ADBD40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgThermalDoubleSpectrum.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgThermalDoubleSpectrum dialog

class CDlgThermalDoubleSpectrum : public CDialog
{
// Construction
public:
	CDlgThermalDoubleSpectrum(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgThermalDoubleSpectrum)
	enum { IDD = IDD_DLG_THERMAL_DOUBLE_SPECTRUM };
	CComboBox	m_byMode;
	COleDateTime	m_struStartTime;
	COleDateTime	m_struStopTime;
	BOOL	m_bZoomLinkageEnable;
	BOOL	m_byEnabled;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgThermalDoubleSpectrum)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgThermalDoubleSpectrum)
	afx_msg void OnButtonSetLowpower();
	afx_msg void OnButtonGetLowpower();
	afx_msg void OnButtonSetZoomlinkage();
	afx_msg void OnButtonGetZoomlinkage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG  m_lChannel;
    LONG m_lUserID;
    int m_iDeviceIndex;
    
    char m_szStatusBuf[ISAPI_STATUS_LEN];
    CComboBox m_comboCurrentLock;
    afx_msg void OnBnClickedButtonSetCurrentLock();
    afx_msg void OnBnClickedButtonGetCurrentLock();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTHERMALDOUBLESPECTRUM_H__287F2624_ADE1_448E_B359_53ECB7ADBD40__INCLUDED_)
