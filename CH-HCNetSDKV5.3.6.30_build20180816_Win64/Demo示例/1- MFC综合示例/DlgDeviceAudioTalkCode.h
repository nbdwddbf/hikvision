#if !defined(AFX_DLGDEVICEAUDIOTALKCODE_H__E24E6909_C620_4BE0_A35C_D4925238D3C0__INCLUDED_)
#define AFX_DLGDEVICEAUDIOTALKCODE_H__E24E6909_C620_4BE0_A35C_D4925238D3C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDeviceAudioTalkCode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceAudioTalkCode dialog

class CDlgDeviceAudioTalkCode : public CDialog
{
// Construction
public:
	CDlgDeviceAudioTalkCode(CWnd* pParent = NULL);   // standard constructor

	int m_iDeviceIndex;
	NET_DVR_COMPRESSION_AUDIO m_struCodeType;

// Dialog Data
	//{{AFX_DATA(CDlgDeviceAudioTalkCode)
	enum { IDD = IDD_DLG_AUDIOTALKCODE_CONFIG };
	CComboBox	m_AudioTalkCodeType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDeviceAudioTalkCode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDeviceAudioTalkCode)
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEVICEAUDIOTALKCODE_H__E24E6909_C620_4BE0_A35C_D4925238D3C0__INCLUDED_)
