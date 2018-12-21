#if !defined(AFX_DLGMCUABILITYDETECT_H__B0517971_13EB_44B0_8094_0ED1E6B24237__INCLUDED_)
#define AFX_DLGMCUABILITYDETECT_H__B0517971_13EB_44B0_8094_0ED1E6B24237__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMCUAbilityDetect.h : header file
//

#include "XMLParamsConvert.h"
#include "MCUGeneralDef.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUAbilityDetect dialog

class CDlgMCUAbilityDetect : public CDialog
{
// Construction
public:
	CDlgMCUAbilityDetect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMCUAbilityDetect)
	enum { IDD = IDD_DLG_MCU_ABILITY_DETECT };
		// NOTE: the ClassWizard will add data members here
	CComboBox m_comAbilityType;
	CEdit     m_edtResult;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMCUAbilityDetect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMCUAbilityDetect)
	afx_msg void OnBtnGet();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL OnInitDialog();


private:

	DWORD   m_dwAbilityType;
	CString m_strResult;
	DWORD   m_dwReturnValue;
	DWORD   m_dwLastError;

	char	*m_pOutBuf;
	
	void ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf);
	
	DWORD GetAbliltyType();

public:
	int   m_iDeviceIndex;
    LONG  m_lUserID;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMCUABILITYDETECT_H__B0517971_13EB_44B0_8094_0ED1E6B24237__INCLUDED_)
