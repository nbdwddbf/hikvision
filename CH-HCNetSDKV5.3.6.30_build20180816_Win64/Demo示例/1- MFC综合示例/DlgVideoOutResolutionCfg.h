#if !defined(AFX_DLGVIDEOOUTRESOLUTIONCFG_H__7DECCF06_2E94_4E7F_9EE9_745DA4889108__INCLUDED_)
#define AFX_DLGVIDEOOUTRESOLUTIONCFG_H__7DECCF06_2E94_4E7F_9EE9_745DA4889108__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVideoOutResolutionCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoOutResolutionCfg dialog

class CDlgVideoOutResolutionCfg : public CDialog
{
// Construction
public:
	CDlgVideoOutResolutionCfg(CWnd* pParent = NULL);   // standard constructor

	LONG    m_lUserID;
    LONG    m_lChannel;
	DWORD   m_dwDevIndex;

// Dialog Data
	//{{AFX_DATA(CDlgVideoOutResolutionCfg)
	enum { IDD = IDD_DLG_VIDEOOUT_RESOLUTION_CFG };
	CComboBox	m_cmbVideoOutNo;
	CComboBox	m_cmbResulotion;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVideoOutResolutionCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVideoOutResolutionCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIDEOOUTRESOLUTIONCFG_H__7DECCF06_2E94_4E7F_9EE9_745DA4889108__INCLUDED_)
