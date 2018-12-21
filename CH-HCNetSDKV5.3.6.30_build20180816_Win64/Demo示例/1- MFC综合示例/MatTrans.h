#if !defined(AFX_MATTRANS_H__CF342F1F_AC7C_4065_BA2F_2EA034517ED5__INCLUDED_)
#define AFX_MATTRANS_H__CF342F1F_AC7C_4065_BA2F_2EA034517ED5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatTrans.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatTrans dialog

class CMatTrans : public CDialog
{
// Construction
public:
	CMatTrans(CWnd* pParent = NULL);   // standard constructor

	int		m_iChannelnumber;
	LONG	m_lServerID;
	LONG	m_lStartChan;
	int     m_iDeviceType;

// Dialog Data
	//{{AFX_DATA(CMatTrans)
	enum { IDD = IDD_DLG_MATTRANS };
	CComboBox	m_BaudCtrl;
	CComboBox	m_StopBitCtrl;
	CListCtrl	m_List;
	CComboBox	m_FlowCtrl;
	CComboBox	m_DataBitCtrl;
	CComboBox	m_CheckBitCtrl;
	CComboBox	m_SerCtrl1;
	CComboBox	m_SerCtrl;
	CComboBox	m_ProCtrl;
	CString	m_Ip;
	int		m_Port;
	int		m_232FullDup;
	int		m_485FullDup;
	CString	m_strUser;
	CString	m_strPassword;
	DWORD	m_dwSerialNo;
	DWORD	m_dwSubBoard;
	DWORD	m_dwSubSys;
	DWORD	m_dwLocalSerialNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatTrans)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ConInfoToDisp(int index, int i);
protected:

	// Generated message map functions
	//{{AFX_MSG(CMatTrans)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButset();
	afx_msg void OnButexit();
	afx_msg void OnAddtolist();
	afx_msg void OnDelfromlist();
	afx_msg void OnSetfulldup();
	afx_msg void OnItemclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComser2();
	afx_msg void OnSelchangeComser();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	NET_DVR_MATRIX_TRAN_CHAN_CONFIG_V30 m_stru;
	LONG m_lSerialCount;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATTRANS_H__CF342F1F_AC7C_4065_BA2F_2EA034517ED5__INCLUDED_)
