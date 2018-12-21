#if !defined(AFX_DLGSUBSYSNETCFG_H__9ADF5259_4A1E_4745_BF20_49A0FB65637C__INCLUDED_)
#define AFX_DLGSUBSYSNETCFG_H__9ADF5259_4A1E_4745_BF20_49A0FB65637C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSubsysNetCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSubsysNetCfg dialog

class CDlgSubsysNetCfg : public CDialog
{
// Construction
public:
	CDlgSubsysNetCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSubsysNetCfg)
	enum { IDD = IDD_DLG_SUBSYSTEM_NETCFG };
	CComboBox	m_cmbNetCardType;
	CComboBox	m_cmbNetInterface;
//	CComboBox	m_cmbCardType;
	CComboBox	m_cmbNetCard;
	BOOL	m_bCardDHCP;
	CString	m_csDNSFirst;
	CString	m_csDNSSecond;
	CString	m_csGateway;
	CString	m_csIP;
	CString	m_csMacAddr;
	CString	m_csMask;
	short	m_wMTU;
	BYTE	m_byCardNum;
	DWORD	m_dwSlotChan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSubsysNetCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSubsysNetCfg)
	afx_msg void OnSelchangeNetcard();
	afx_msg void OnButGet();
	afx_msg void OnButSave();
	afx_msg void OnButSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
	LONG m_iDeviceIndex;
    NET_DVR_SUBSYSTEM_NETCFG m_struNetCfg; 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSUBSYSNETCFG_H__9ADF5259_4A1E_4745_BF20_49A0FB65637C__INCLUDED_)
