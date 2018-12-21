#if !defined(AFX_DLGALARMTAMPER_H__0C59B633_108D_4D9E_80D0_F9C45D379018__INCLUDED_)
#define AFX_DLGALARMTAMPER_H__0C59B633_108D_4D9E_80D0_F9C45D379018__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmTamper.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmTamper dialog

class CDlgAlarmTamper : public CDialog
{
// Construction
public:
	CDlgAlarmTamper(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmTamper)
	enum { IDD = IDD_DLG_ALARM_TAMPER };
	CListCtrl	m_listSirenOut;
	CListCtrl	m_listAlarmOut;
	CComboBox	m_comboTamper;
	CComboBox	m_comboAlarmIn;
	CComboBox	m_cmbTamperResistor;
	BOOL	m_bChkUploadAlarmRecoveryReport;
	float	m_fTamperResistorManual;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmTamper)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	int m_iDeviceIndex;
	LONG m_lUserID;
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmTamper)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeCmbTamperResistor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMTAMPER_H__0C59B633_108D_4D9E_80D0_F9C45D379018__INCLUDED_)
