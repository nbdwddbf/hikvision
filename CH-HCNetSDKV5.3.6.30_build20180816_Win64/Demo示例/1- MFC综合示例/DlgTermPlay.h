#if !defined(AFX_DLGTERMPLAY_H__1CA83E43_56AF_4DFD_B040_6597875C9C67__INCLUDED_)
#define AFX_DLGTERMPLAY_H__1CA83E43_56AF_4DFD_B040_6597875C9C67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTermPlay.h : header file
//

#include "InfoDiffusionParamsConvert.h"

#define MAX_LEN_XML 10*1024*1024 //xml最大长度

/////////////////////////////////////////////////////////////////////////////
// CDlgTermPlay dialog

class CDlgTermPlay : public CDialog
{
// Construction
public:
	CDlgTermPlay(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTermPlay)
	enum { IDD = IDD_DLG_TERM_PLAY };
	CListCtrl	m_listTerminal;
	DWORD	m_dwTerminalID;
	DWORD	m_dwBackBrightLevel;
	BOOL	m_bLogoEnable;
	DWORD	m_dwVolume;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTermPlay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTermPlay)
	afx_msg void OnBtnExit();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnGetAll();
	afx_msg void OnBtnSet();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickLstTerminal(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;
	int m_iDeviceIndex;
	
	LPNET_DVR_PLAY_CFG_LIST m_lpPlayCfgList;
	char* m_pOutputXmlBuffer;
	
	int m_nCurSelTerminal;

public:
	void InitTerminalCtrlList();
	void RefreshTerminalList();
	void UpdatePlayParameters(int nTerminalIndex);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTERMPLAY_H__1CA83E43_56AF_4DFD_B040_6597875C9C67__INCLUDED_)
