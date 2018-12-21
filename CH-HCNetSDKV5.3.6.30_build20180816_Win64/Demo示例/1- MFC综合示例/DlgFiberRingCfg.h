#if !defined(AFX_DLGFIBERRINGCFG_H__9114A578_DADF_43BD_8AD4_AEA12B9FF261__INCLUDED_)
#define AFX_DLGFIBERRINGCFG_H__9114A578_DADF_43BD_8AD4_AEA12B9FF261__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFiberRingCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFiberRingCfg dialog

class CDlgFiberRingCfg : public CDialog
{
// Construction
public:
	CDlgFiberRingCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFiberRingCfg)
	enum { IDD = IDD_DLG_FIBER_RING_CFG };
	CComboBox	m_cmbDeviceMasterSlave;
	CComboBox	m_cmbStatus;
	CComboBox	m_cmbProtoType;
	CComboBox	m_cmbPortEthernet2;
	CComboBox	m_cmbPortEthernet;
	CComboBox	m_cmbMasterSlave2;
	CComboBox	m_cmbMasterSlave;
	CComboBox	m_cmbBandwidth;
	BOOL	m_BEnable;
	BYTE	m_byPortNo;
	BYTE	m_byPortNo2;
	DWORD	m_dwRingNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFiberRingCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFiberRingCfg)
	afx_msg void OnButGet();
	afx_msg void OnButSet();
	afx_msg void OnButGetStatus();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	LONG m_lUserID; 
	LONG m_lDeviceID; 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFIBERRINGCFG_H__9114A578_DADF_43BD_8AD4_AEA12B9FF261__INCLUDED_)
