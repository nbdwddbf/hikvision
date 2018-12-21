#if !defined(AFX_DLGCREATEVD_H__F882ECA1_1968_4134_AA20_7B4F7C28F405__INCLUDED_)
#define AFX_DLGCREATEVD_H__F882ECA1_1968_4134_AA20_7B4F7C28F405__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCreateVD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateVD dialog

class CDlgCreateVD : public CDialog
{
// Construction
public:
	CDlgCreateVD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCreateVD)
	enum { IDD = IDD_DLG_CREATE_VD };
	CComboBox	m_cmbVDType;
	CComboBox	m_comboInitType;
	CComboBox	m_comboVDSlot;
	CString	m_csVDName;
	CString	m_csArrayName;
	UINT	m_nVDCapacity;
	UINT	m_dwBlockSize;
	CString	m_strWarrantIP;
	CString	m_strArrayIDGroup;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCreateVD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCreateVD)
	afx_msg void OnBtnCrateArray();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboVdSlot();
	afx_msg void OnSelchangeComboVdType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    void InitWnd();
public:
    BOOL GetArraySpaceAlloc(DWORD dwArraySlot);
    BOOL CreateVD();
	inline BOOL ValidIPv6(BYTE *ip);
public:
    LONG    m_lServerID;
    int     m_iDevIndex;

    NET_DVR_OPERATE_VD_PARAM_EX m_struOpeateVD;
    NET_DVR_ARRAY_SPACE_ALLOC_INFO m_struArraySpaceAlloc;
    NET_DVR_ARRAY_INFO m_struArrayInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCREATEVD_H__F882ECA1_1968_4134_AA20_7B4F7C28F405__INCLUDED_)
