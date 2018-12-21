#if !defined(AFX_DLGVCAFORENSICSMODECFG_H__FC7E9132_9E18_4D48_955A_A5EE1C869747__INCLUDED_)
#define AFX_DLGVCAFORENSICSMODECFG_H__FC7E9132_9E18_4D48_955A_A5EE1C869747__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaForensicsModeCfg.h : header file
//
#include "VcaCommonOperations.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgVcaForensicsModeCfg dialog

class CDlgVcaForensicsModeCfg : public CDialog,public CVcaCommonOperations
{
	// Construction
public:
	CDlgVcaForensicsModeCfg(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CDlgVcaForensicsModeCfg)
	enum { IDD = IDD_DLG_VCA_FORENSICS_MODE };
	enum {
		TFS_FORENSICS_MODE_MANUAL = 0,
		TFS_FORENSICS_MODE_AUTO   = 1,
        TFS_FORENSICS_MODE_SEMIAUTO   = 2
	};
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaForensicsModeCfg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CDlgVcaForensicsModeCfg)
	afx_msg void OnBtnSave();
	afx_msg void OnRadioAuto();
	afx_msg void OnRadioManual();
    afx_msg void OnRadioSemiAuto();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	BOOL GetTfsForensicsMode();
	BOOL SetTfsForensicsMode();
	void InitWndCtrlState();
private:
	int                    m_nCurForensicsMode;
	NET_DVR_FORENSICS_MODE m_struForenciscMode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAFORENSICSMODECFG_H__FC7E9132_9E18_4D48_955A_A5EE1C869747__INCLUDED_)
