#include "afxwin.h"
#if !defined(AFX_DLGDOTEST_H__11F806D5_0183_4788_8B8A_131925C9889E__INCLUDED_)
#define AFX_DLGDOTEST_H__11F806D5_0183_4788_8B8A_131925C9889E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDoTest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDoTest dialog

class CDlgDoTest : public CDialog
{
// Construction
public:
	CDlgDoTest(CWnd* pParent = NULL);   // standard constructor
	int m_iDeviceIndex;
	NET_DVR_PREVIEWCFG m_struPreviewCfg;
	NET_DVR_AUXOUTCFG m_struAuxOutCfg;
	NET_DVR_PTZPOS m_ptzPos;

    LONG    m_lDebugHandle;
    BOOL    m_bDebugVca;
// Dialog Data
	//{{AFX_DATA(CDlgDoTest)
	enum { IDD = IDD_DLG_DO_TEST };
	CComboBox	m_ComboHeadVer;
	CComboBox	m_ComboHeadModel;
	CComboBox	m_combo4;
	CComboBox	m_combo3;
	CComboBox	m_combo2;
	CComboBox	m_combo1;
	int		m_iPara1;
	int		m_iPara2;
	CString	m_csPara3;
	CString	m_csPara4;
	UINT	m_iVerHeadParam1;
	UINT	m_iVerHeadParam2;
	UINT	m_iVerHeadParam1_1;
	UINT	m_iVerHeadParam1_2;
	UINT	m_iVerHeadParam2_1;
	UINT	m_iVerHeadParam2_2;
	UINT	m_iVersion;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDoTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDoTest)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtn1();
	afx_msg void OnBtn2();
	afx_msg void OnBtn3();
	afx_msg void OnBtn4();
	afx_msg void OnBtn6();
	afx_msg void OnBtnAbility();
	afx_msg void OnBtnVcaDebug();
	afx_msg void OnBtnAbilityparse();
	afx_msg void OnBtnSetHeadVersion();
	afx_msg void OnBtnVerHeadGet();
	afx_msg void OnBtnVerHeadSet();
	afx_msg void OnBtnCharCodeCb();
	afx_msg void OnBtnXmlTransparent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    void TestTransferAbility();
    void TestTransferSwitchOn();
    void TestTransferSwitchOff();
    CComboBox m_comboFileType;
    afx_msg void OnBnClickedBtnFiletypeOk();
    afx_msg void OnBnClickedBtnAbilityparse2();
    int m_iHourDiffWithUTC;
    int m_iMinDiffWithUTC;
    afx_msg void OnDestroy();
    BOOL m_bISO8601;
};

int CALLBACK Demo_CharEncodeConvert(char *pInput, DWORD dwInputLen, DWORD dwInEncodeType, char *pOutput, DWORD dwOutputLen, DWORD dwOutEncodeType);
void CALLBACK TranslateNetWcharToMutilChar(char *dest, unsigned char *src, int length);
void CALLBACK TranslateMutilcharToNetWchar(unsigned char *dest, char *src, int length);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDOTEST_H__11F806D5_0183_4788_8B8A_131925C9889E__INCLUDED_)
