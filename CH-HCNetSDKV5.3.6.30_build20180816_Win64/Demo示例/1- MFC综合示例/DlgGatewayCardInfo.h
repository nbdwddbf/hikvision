#if !defined(AFX_DLGGATEWAYCARDINFO_H__71FBF502_05D1_4532_8C25_943A381F546D__INCLUDED_)
#define AFX_DLGGATEWAYCARDINFO_H__71FBF502_05D1_4532_8C25_943A381F546D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGatewayCardInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGatewayCardInfo dialog
struct GATEWAY_CARD_INFO
{
	BYTE byCardNumber[ACS_CARD_NO_LEN];
	BYTE byCardType;
};
class CDlgGatewayCardInfo : public CDialog
{
// Construction
public:
	CDlgGatewayCardInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGatewayCardInfo)
	enum { IDD = IDD_DLG_GATEWAY_CARD_INFO };
	CComboBox	m_comboCardType;
	CString	m_strCardNumber;
	int		m_nCardType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGatewayCardInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGatewayCardInfo)
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void InitCtrlState();
public:
	void SetCardInfo(const GATEWAY_CARD_INFO& struCardInfo);
	void GetCardInfo(GATEWAY_CARD_INFO& struCardInfo);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGATEWAYCARDINFO_H__71FBF502_05D1_4532_8C25_943A381F546D__INCLUDED_)
