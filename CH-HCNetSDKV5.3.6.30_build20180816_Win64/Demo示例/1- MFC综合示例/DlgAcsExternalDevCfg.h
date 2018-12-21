#if !defined(AFX_DLGACSEXTERNALDEVCFG_H__42673380_CF0E_45DC_B784_0447282BAB59__INCLUDED_)
#define AFX_DLGACSEXTERNALDEVCFG_H__42673380_CF0E_45DC_B784_0447282BAB59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAcsExternalDevCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgAcsExternalDevCfg dialog

class DlgAcsExternalDevCfg : public CDialog
{
// Construction
public:
	DlgAcsExternalDevCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgAcsExternalDevCfg)
	enum { IDD = IDD_DLG_ACS_EXTERNAL_DEV_CFG };
	CComboBox	m_wDevDetailType;
	CComboBox	m_byQRCodeVerifyMode;
	CComboBox	m_channel;
	CComboBox	m_byIDCardUpMode;
	CComboBox	m_byDoorMode;
	CComboBox	m_byACSDevType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgAcsExternalDevCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    int m_iDeviceIndex;
    long m_lUserID;

	// Generated message map functions
	//{{AFX_MSG(DlgAcsExternalDevCfg)
    virtual BOOL OnInitDialog();
	afx_msg void OnButtonGet();
	afx_msg void OnButtonSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACSEXTERNALDEVCFG_H__42673380_CF0E_45DC_B784_0447282BAB59__INCLUDED_)
