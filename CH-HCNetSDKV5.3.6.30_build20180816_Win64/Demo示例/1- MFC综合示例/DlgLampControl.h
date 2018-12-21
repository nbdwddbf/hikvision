#if !defined(AFX_DLGLAMPCONTROL_H__C1C41474_4F69_44A1_B4D7_D71EA1AA7AF3__INCLUDED_)
#define AFX_DLGLAMPCONTROL_H__C1C41474_4F69_44A1_B4D7_D71EA1AA7AF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLampControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLampControl dialog

class CDlgLampControl : public CDialog
{
// Construction
public:
	CDlgLampControl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLampControl)
	enum { IDD = IDD_DLG_LAMP_CONTROL };
	CComboBox	m_comboLampStateNo;
	CComboBox	m_comboLampNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLampControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLampControl)
	afx_msg void OnBtnControl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLAMPCONTROL_H__C1C41474_4F69_44A1_B4D7_D71EA1AA7AF3__INCLUDED_)
