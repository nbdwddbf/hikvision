#if !defined(AFX_DLGBATTERYPOWER_H__6EC67A0C_85B7_45D8_AB48_4D924CF91DF0__INCLUDED_)
#define AFX_DLGBATTERYPOWER_H__6EC67A0C_85B7_45D8_AB48_4D924CF91DF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBatteryPower.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgBatteryPower dialog

class DlgBatteryPower : public CDialog
{
// Construction
public:
	DlgBatteryPower(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgBatteryPower)
	enum { IDD = IDD_DLG_BATTERY_POWER };
	BOOL	m_byBatteryPower;
    CComboBox	m_comChannel;
	float	m_fX;
	float	m_fY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgBatteryPower)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgBatteryPower)
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
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBATTERYPOWER_H__6EC67A0C_85B7_45D8_AB48_4D924CF91DF0__INCLUDED_)
