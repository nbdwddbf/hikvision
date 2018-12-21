#if !defined(AFX_DLGMCUTERMINALMANAGECFG_H__40436551_A57B_4C20_A7F9_9D82C10DC722__INCLUDED_)
#define AFX_DLGMCUTERMINALMANAGECFG_H__40436551_A57B_4C20_A7F9_9D82C10DC722__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMCUTerminalManageCfg.h : header file
//



#include "MCUGeneralDef.h"
#include "XMLParamsConvert.h"
#include "afxcmn.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUTerminalManageCfg dialog

class CDlgMCUTerminalManageCfg : public CDialog
{
// Construction
public:
	CDlgMCUTerminalManageCfg(CWnd* pParent = NULL);   // standard constructor

    ~CDlgMCUTerminalManageCfg();
// Dialog Data
	//{{AFX_DATA(CDlgMCUTerminalManageCfg)
	enum { IDD = IDD_DLG_MCU_TERM_MANAGE_CFG };
	CString	m_csAddFormatType;
	CString	m_csProtocolType;
	CString	m_csIPVersion;
	CString	m_csUser;
	CString	m_csPwd;
	CString	m_csOSDName;
	CString	m_csTerminalName;

	CString	m_csHostName;
	BOOL	m_bEnable;
	CString	m_csIP;
	CString	m_csIPV6;
	int		m_IPortNo;


    CString m_csUUID;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMCUTerminalManageCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMCUTerminalManageCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnOk();
	afx_msg void OnButGet();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	char    *m_szRequestURL;
	char*   m_pXMLParamBuf;
	DWORD   m_dwXMLParamBufLen;
	char    *m_szXMLResultBuf;
	DWORD   m_dwXMLResultBufLen;	
	char    *m_szXMLStatus;

	CString ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf);

    char m_szUUID[128];
    char m_szName[64][256];
    int m_nIdCount;

public:
	int   m_iDeviceIndex;
    LONG  m_lUserID;

    CListCtrl m_ctrlTerminal;
    afx_msg void OnBnClickedBtnGetAll();
    BOOL ConvertTermNameXmlToStruList(const char* pXmlBuf);
    void RefreshList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMCUTERMINALMANAGECFG_H__40436551_A57B_4C20_A7F9_9D82C10DC722__INCLUDED_)
