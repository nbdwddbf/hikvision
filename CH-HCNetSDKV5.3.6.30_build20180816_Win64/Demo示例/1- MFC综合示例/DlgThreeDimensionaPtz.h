#if !defined(AFX_DLGTHREEDIMENSIONAPTZ_H__A5E466A5_141D_44F8_AAB2_60C42121DABD__INCLUDED_)
#define AFX_DLGTHREEDIMENSIONAPTZ_H__A5E466A5_141D_44F8_AAB2_60C42121DABD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgThreeDimensionaPtz.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgThreeDimensionaPtz dialog

class CDlgThreeDimensionaPtz : public CDialog
{
// Construction
public:
	CDlgThreeDimensionaPtz(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgThreeDimensionaPtz)
	enum { IDD = IDD_DLG_IPC_3D_PTZ };
	CComboBox	m_cmbZDirection;
	CComboBox	m_cmbTDirection;
	CComboBox	m_cmbPDirection;
	BYTE	m_byXSpeed;
	BYTE	m_byYSpeed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgThreeDimensionaPtz)
	protected:
    virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgThreeDimensionaPtz)
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    LONG    m_lChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTHREEDIMENSIONAPTZ_H__A5E466A5_141D_44F8_AAB2_60C42121DABD__INCLUDED_)
