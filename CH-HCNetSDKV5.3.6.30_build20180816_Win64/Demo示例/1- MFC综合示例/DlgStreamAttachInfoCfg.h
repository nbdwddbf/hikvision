#if !defined(AFX_DLGSTREAMATTACHINFOCFG_H__2C8D77E1_66E4_411A_A923_5052F81FDA51__INCLUDED_)
#define AFX_DLGSTREAMATTACHINFOCFG_H__2C8D77E1_66E4_411A_A923_5052F81FDA51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStreamAttachInfoCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamAttachInfoCfg dialog

class CDlgStreamAttachInfoCfg : public CDialog
{
// Construction
public:
	CDlgStreamAttachInfoCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgStreamAttachInfoCfg)
	enum { IDD = IDD_DLG_STREAM_ATTACHINFO_CFG };
	BOOL	m_bStreamWithVca;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgStreamAttachInfoCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgStreamAttachInfoCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	BOOL GetStreamAttachInfoCfg();
	BOOL SetStreamAttachInfoCfg();
public:
	LONG m_lServerID;
	LONG m_lChannel;
	int  m_iDeviceIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSTREAMATTACHINFOCFG_H__2C8D77E1_66E4_411A_A923_5052F81FDA51__INCLUDED_)
