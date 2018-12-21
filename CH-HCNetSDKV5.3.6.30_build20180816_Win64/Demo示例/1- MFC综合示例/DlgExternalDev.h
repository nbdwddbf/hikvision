#include "afxwin.h"
#if !defined(AFX_DLGEXTERNALDEV_H__AF303E51_9B0D_4033_84A6_34D3D0969C8F__INCLUDED_)
#define AFX_DLGEXTERNALDEV_H__AF303E51_9B0D_4033_84A6_34D3D0969C8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgExternalDev.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgExternalDev dialog

class DlgExternalDev : public CDialog
{
// Construction
public:
	DlgExternalDev(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgExternalDev)
	enum { IDD = IDD_DLG_EXTERNAL_DEV };
	CComboBox	m_byMode;
	BOOL	m_byEnable;
	COleDateTime	m_struStartTime;
	COleDateTime	m_struStopTime;
	DWORD	m_HighBeamBrightness;
	DWORD	m_LowBeamBrightness;
    DWORD   m_dwFilteringTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgExternalDev)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgExternalDev)
    virtual BOOL OnInitDialog();
	afx_msg void OnButtonSet();
	afx_msg void OnButtonGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG  m_lChannel;
    LONG m_lUserID;
    int m_iDeviceIndex;
    
    char m_szStatusBuf[ISAPI_STATUS_LEN];
    BYTE m_bySensitivity;
    BYTE m_byBrightness;
    CComboBox m_bBrightnessRegulatMode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEXTERNALDEV_H__AF303E51_9B0D_4033_84A6_34D3D0969C8F__INCLUDED_)
