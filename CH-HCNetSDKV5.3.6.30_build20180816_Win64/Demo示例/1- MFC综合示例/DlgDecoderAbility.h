#if !defined(AFX_DLGDECODERABILITY_H__97B504C7_7B7A_4CC8_A5D7_E8DCBB1B33F6__INCLUDED_)
#define AFX_DLGDECODERABILITY_H__97B504C7_7B7A_4CC8_A5D7_E8DCBB1B33F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDecoderAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDecoderAbility dialog

class CDlgDecoderAbility : public CDialog
{
// Construction
public:
	void GetResolutionString(DWORD dwRes, char *lpResString);
	void SetInfoToDlg(LPNET_DVR_MATRIX_ABILITY_V41 lpInter);
	int m_iDeviceIndex;
	CDlgDecoderAbility(CWnd* pParent = NULL);   // standard constructor
	NET_DVR_MATRIX_ABILITY_V41 m_struMatrixAbility;
// Dialog Data
	//{{AFX_DATA(CDlgDecoderAbility)
	enum { IDD = IDD_DLG_DECODER_ABILITY };
	CComboBox	m_cmDispSeq;
	CComboBox	m_cmWindowDispMode;
	CComboBox	m_cmSupRes;
	CComboBox	m_cmDispWindowChanType;
	CComboBox	m_cmDispMode;
	BYTE	m_byDecChanNums;
	BYTE	m_byDispChanSeq;
	BYTE	m_byDspNums;
	BYTE	m_byScreenX;
	BYTE	m_byScreenY;
	BYTE	m_byStartScreenNums;
	BYTE	m_byStartChan;
	BYTE	m_bySupportScreenNums;
	BYTE	m_byDispChanNums;
	BYTE	m_byDispStartChan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDecoderAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDecoderAbility)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnRfresh();
	afx_msg void OnSelchangeComboDispmode();
	afx_msg void OnSelchangeComboDispSeq();
	afx_msg void OnSelchangeComboWindownum();
	afx_msg void OnSelendokComboDispmode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDECODERABILITY_H__97B504C7_7B7A_4CC8_A5D7_E8DCBB1B33F6__INCLUDED_)
