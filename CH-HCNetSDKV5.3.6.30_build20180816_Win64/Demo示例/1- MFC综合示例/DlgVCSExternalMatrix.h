#if !defined(AFX_DLGVCSEXTERNALMATRIX_H__5C8CF930_39E4_4B1E_A2D3_377A4E9CF3AC__INCLUDED_)
#define AFX_DLGVCSEXTERNALMATRIX_H__5C8CF930_39E4_4B1E_A2D3_377A4E9CF3AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVCSExternalMatrix.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVCSExternalMatrix dialog

class CDlgVCSExternalMatrix : public CDialog
{
// Construction
public:
	CDlgVCSExternalMatrix(CWnd* pParent = NULL);   // standard constructor
	~CDlgVCSExternalMatrix();
// Dialog Data
	//{{AFX_DATA(CDlgVCSExternalMatrix)
	enum { IDD = IDD_DLG_SCREEN_EXTERNAL_MATRIX };
	CComboBox	m_cmMatrixIndex;
	CComboBox	m_cmMatrixType;
	CComboBox	m_cmMatrixChanType;
	CIPAddressCtrl	m_IPDigtalMatrix;
	CComboBox	m_cmWorkType;
	CComboBox	m_cmStopBit;
	CComboBox	m_cmParity;
	CComboBox	m_cmProtocol;
	CComboBox	m_cmFlowControl;
	CComboBox	m_cmDataBit;
	CComboBox	m_cmBaudRate;
	BOOL	m_bValid;
	DWORD	m_dwInputNum;
	CString	m_csMatrixName;
	DWORD	m_dwOutputNum;
	DWORD	m_dwPort;
	DWORD	m_dwMatrixID;
	DWORD	m_dwSerialNum;
	BOOL	m_BLoop;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVCSExternalMatrix)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVCSExternalMatrix)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGetAllMatrix();
	afx_msg void OnKillfocusEditTemp();
	afx_msg void OnBtnGetSingleMatrix();
	afx_msg void OnBtnSetMatrix();
	afx_msg void OnSelchangeComboMatrixType();
	afx_msg void OnSelchangeComboExternalMatrixIndex();
	afx_msg void OnBtnRelation();
	afx_msg void OnBtnMatrixSwitch();
	afx_msg void OnBtnExit();
	afx_msg void OnChk232loop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	int m_iDeviceIndex;
	long m_lUserID;
	char m_szLan[128];
	NET_DVR_EXTERNAL_MATRIX_CFG m_strMatrixCfg[4];
	DWORD m_lpStatusList[4];
	int m_iCurMatirx;
	char* m_pAllMatrixCfgBuf;
protected:
	void InitListWnd();
	void InitComboWnd();
	void GetMatrixFromDlg();
	void SetMatrixToDlg();
    void ChangeAnlogLoopDlg(); 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCSEXTERNALMATRIX_H__5C8CF930_39E4_4B1E_A2D3_377A4E9CF3AC__INCLUDED_)
