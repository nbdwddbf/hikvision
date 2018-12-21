#if !defined(AFX_DLGPRODUCTIONTEST_H__1F8F64CA_AB4C_444F_9CEA_78533616807E__INCLUDED_)
#define AFX_DLGPRODUCTIONTEST_H__1F8F64CA_AB4C_444F_9CEA_78533616807E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProductionTest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProductionTest dialog

class CDlgProductionTest : public CDialog
{
// Construction
public:
	CDlgProductionTest(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgProductionTest)
	enum { IDD = IDD_DLG_PRODUCTION_TEST };
	CComboBox	m_comSecurityMode;
	CComboBox	m_comSoundMode;
	CComboBox	m_comSelfCheck;
	BOOL	m_bAgeingCmd;
	BOOL	m_bDevFan1;
	BOOL	m_bDevFan2;
	BOOL	m_bDevHeater1;
	BOOL	m_bDevHeater2;
	BOOL	m_bRedlightTest;
	float	m_fHuml;
	float	m_fTemp;
	DWORD	m_dwChan;
	CString	m_csDialSwitch;
	DWORD	m_dwChanSecurityMode;
	CString	m_csRandCode;
	int		m_iICRTime;
	BOOL	m_bICR;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProductionTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProductionTest)
	afx_msg void OnButSelfcheckRefresh();
	afx_msg void OnButStartCommand();
	afx_msg void OnButStartDevtest();
	virtual BOOL OnInitDialog();
	afx_msg void OnButResumeInitrackpos();
	afx_msg void OnBtnGetTempHumi();
	afx_msg void OnBtnSetAutofocus();
	afx_msg void OnBtnGetSoundmode();
	afx_msg void OnBtnSetSoundmode();
	afx_msg void OnBtnGetDialSwitch();
	afx_msg void OnBtnGetSecuritymode();
    afx_msg void OnBnClickedBtnGet();
    afx_msg void OnBnClickedBtnSetAgingTrickScan();
    afx_msg void OnBnClickedBtnGetEccentricCorrectState();
    afx_msg void OnBnClickedButClearIpcParam();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG    m_lUserID;
    LONG    m_iDevIndex;
    DWORD   m_dwChannel;
    CButton m_bEccentricCorrention;
    BOOL m_bEccectricCorrection;
    BOOL m_bTrickScan;
    BOOL m_bElectronicCompassCorrect;
    CComboBox m_comElectronicCompassState;
    CComboBox m_comAging;
    CComboBox m_comWriteReadEnalbe;
    CComboBox m_comEccentricCorrectState;
    BOOL m_bAgingTrickScan;
    float m_fdtem;
    BYTE m_temp1;
    BYTE m_temp2;
    BYTE m_temp3;
    BYTE m_temp4;
    BYTE m_temp5;
    BYTE m_temp6;
    BYTE m_temp7;
    BYTE m_temp8;
    BYTE m_temp9;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPRODUCTIONTEST_H__1F8F64CA_AB4C_444F_9CEA_78533616807E__INCLUDED_)
