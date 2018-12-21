#if !defined(AFX_DLGNVRIPCCFG_H__9B196529_4D73_4044_AFBC_056594733CD1__INCLUDED_)
#define AFX_DLGNVRIPCCFG_H__9B196529_4D73_4044_AFBC_056594733CD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNVRIPCCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNVRIPCCfg dialog

class CDlgNVRIPCCfg : public CDialog
{
// Construction
public:
	CDlgNVRIPCCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNVRIPCCfg)
	enum { IDD = IDD_DLG_NVR_IPC_CFG };
	CComboBox	m_cmbChannel;
	CComboBox	m_cmbMirrorMode;
	BOOL	m_bEnableCorridor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNVRIPCCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNVRIPCCfg)
	afx_msg void OnBtnSetCorridorMode();
    afx_msg void OnBtnGetCorridorMode();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    int m_iDevIndex;
    LONG m_lChannel;
    LONG m_lUserID;
protected:
    NET_DVR_CORRIDOR_MODE m_struCorridorMode;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNVRIPCCFG_H__9B196529_4D73_4044_AFBC_056594733CD1__INCLUDED_)
