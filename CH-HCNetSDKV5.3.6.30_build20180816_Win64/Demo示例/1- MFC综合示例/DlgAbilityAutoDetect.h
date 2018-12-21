#if !defined(AFX_DLGABILITYAUTODETECT_H__2C0022B9_9459_45F8_9988_49F73E923A42__INCLUDED_)
#define AFX_DLGABILITYAUTODETECT_H__2C0022B9_9459_45F8_9988_49F73E923A42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAbilityAutoDetect.h : header file
//

#include "./xml/XmlBase.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgAbilityAutoDetect dialog


class CDlgAbilityAutoDetect : public CDialog
{
// Construction
public:
	CDlgAbilityAutoDetect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAbilityAutoDetect)
	enum { IDD = IDD_DLG_ABILITY_AUTO_DETECT };
	CComboBox	m_cmbStreamType;
	CComboBox	m_cmbChannel;
	CComboBox	m_cmbAbilityType;
	CString	m_strDevAbility;
	CString	m_strLostAbility;
	DWORD	m_dwLastError;
	DWORD	m_dwReturnValue;
	CString	m_strInputParam;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAbilityAutoDetect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
		LONG	m_lServerID;
		NET_DVR_SDKLOCAL_CFG m_struSdkLocalCfg;
		char	*m_pOutBuf;
		DWORD	m_dwAbilityType;
public:
	void	ParseAbility();
	void	ParseSimpleAbility(CXmlBase &xmlAll, char* szAbilityName);
	void	ParseAbilityRecursive(CXmlBase &xmlAll, CXmlBase &xmlDev);

    DWORD   m_bSTDAbility;
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAbilityAutoDetect)
	afx_msg void OnBtnUseSimAbility();
	afx_msg void OnBtnGet();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCmbAbilityType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnCbnEditchangeCmbAbilityType();
private:
    int GetSelectedAbilityIndex();
    vector<CString> m_vecAbilityType;
    vector<CString> m_vecCurAbilityType;
public:
    afx_msg void OnCbnSetfocusCmbAbilityType();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGABILITYAUTODETECT_H__2C0022B9_9459_45F8_9988_49F73E923A42__INCLUDED_)
