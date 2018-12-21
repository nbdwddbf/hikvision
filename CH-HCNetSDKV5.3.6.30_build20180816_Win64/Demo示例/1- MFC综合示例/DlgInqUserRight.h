#if !defined(AFX_DLGINQUSERRIGHT_H__E07FAC71_09B0_4E92_8D5E_17E46EF51BE8__INCLUDED_)
#define AFX_DLGINQUSERRIGHT_H__E07FAC71_09B0_4E92_8D5E_17E46EF51BE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInqUserRight.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInqUserRight dialog

class CDlgInqUserRight : public CDialog
{
// Construction
public:
	CDlgInqUserRight(CWnd* pParent = NULL);   // standard constructor

	LONG m_lUserID;
	int m_iDeviceIndex;
	NET_DVR_INQUEST_USER_RIGHT_CFG m_struInqUserRightCfg;
	int m_iCurRightType;
	int	m_iUserIndex;

	BOOL m_bSuperUserLogin;
	BOOL m_bSetUserParams;

	void InitUserIndexCombo();
	void InitRightList();
	//void OnBtnGet();
	void GetChanInfoFromWnd();
	void SetChanInfoToDlg();
	

// Dialog Data
	//{{AFX_DATA(CDlgInqUserRight)
	enum { IDD = IDD_DLG_INQ_USER_RIGHT };
	CListCtrl	m_listCtrl_Chan;
	CComboBox	m_cmbUserIndex;
	CComboBox	m_cmbRightType;
	BOOL	m_bLocalDelRecRight;
	BOOL	m_bNetPreviewAudio;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInqUserRight)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInqUserRight)
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboUserIndex();
	afx_msg void OnSelchangeComboRightType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINQUSERRIGHT_H__E07FAC71_09B0_4E92_8D5E_17E46EF51BE8__INCLUDED_)
