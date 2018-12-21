#if !defined(AFX_DLGDECODERCONTROL_H__ADC2C8AA_D641_41F3_9CC4_6C02E7FF6071__INCLUDED_)
#define AFX_DLGDECODERCONTROL_H__ADC2C8AA_D641_41F3_9CC4_6C02E7FF6071__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDecoderControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDecoderControl dialog

class CDlgDecoderControl : public CDialog
{
// Construction
public:
	CDlgDecoderControl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDecoderControl)
	enum { IDD = IDD_DLG_DECODE_CONTROL };
	CSliderCtrl	m_sliLowLight;
	CSliderCtrl	m_sliDefog;
	CComboBox	m_cmbScaleStatus;
	CComboBox	m_cmbDelay;
	CComboBox	m_cmbNoiseReduction;
	BOOL	m_BVcaInfo;
	BOOL	m_BSpartan;
	DWORD	m_dwDecChan;
	DWORD	m_dwDefog;
	DWORD	m_dwLowLight;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDecoderControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDecoderControl)
	afx_msg void OnButDecodeGet();
	afx_msg void OnButDecodeSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnCDrawSliderDecodeDefog(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCDSliderDecodeLowlight(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID; 
	LONG m_lDeviceID; 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDECODERCONTROL_H__ADC2C8AA_D641_41F3_9CC4_6C02E7FF6071__INCLUDED_)
