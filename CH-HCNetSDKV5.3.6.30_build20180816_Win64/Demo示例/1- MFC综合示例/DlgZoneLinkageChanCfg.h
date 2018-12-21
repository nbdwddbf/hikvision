#if !defined(AFX_DLGZONELINKAGECHANCFG_H__72157D81_852D_4D7F_A5A2_9FF23D2E4B2C__INCLUDED_)
#define AFX_DLGZONELINKAGECHANCFG_H__72157D81_852D_4D7F_A5A2_9FF23D2E4B2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgZoneLinkageChanCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgZoneLinkageChanCfg dialog

class CDlgZoneLinkageChanCfg : public CDialog
{
// Construction
public:
	CDlgZoneLinkageChanCfg(CWnd* pParent = NULL);   // standard constructor

	LONG m_lUserID;
	int m_iDeviceIndex;
	NET_DVR_ZONE_CHANNEL_LINKAGE_CFG m_struZoneChannLinkageCfg;

// Dialog Data
	//{{AFX_DATA(CDlgZoneLinkageChanCfg)
	enum { IDD = IDD_DLG_ZONE_LINKAGE_CHAN_CFG };
	CComboBox	m_cmbServerType;
	CComboBox	m_cmbDevAddrType;
	CComboBox	m_cmbChanNo;
	CString	m_csIP;
	CString	m_csIPV6;
	UINT	m_nPort;
	CString	m_csPwd;
	CString	m_csUser;
	UINT	m_nChan;
	CComboBox	m_cmbZoneIndex;
	CString	m_csDevName;
	CString	m_csDevSerialNo;
	UINT	m_nServerPort;
	CString	m_csServerAddr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgZoneLinkageChanCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgZoneLinkageChanCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnSave();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboDevAddrType();
	afx_msg void OnSelchangeComboChan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGZONELINKAGECHANCFG_H__72157D81_852D_4D7F_A5A2_9FF23D2E4B2C__INCLUDED_)
