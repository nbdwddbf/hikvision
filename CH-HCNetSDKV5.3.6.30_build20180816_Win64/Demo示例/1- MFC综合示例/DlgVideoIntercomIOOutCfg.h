#if !defined(AFX_DLGVIDEOINTERCOMIOOUTCFG_H__3D94FEB8_7211_4BB1_A118_69D2C6437922__INCLUDED_)
#define AFX_DLGVIDEOINTERCOMIOOUTCFG_H__3D94FEB8_7211_4BB1_A118_69D2C6437922__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVideoIntercomIOOutCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomIOOutCfg dialog

class CDlgVideoIntercomIOOutCfg : public CDialog
{
// Construction
public:
	CDlgVideoIntercomIOOutCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVideoIntercomIOOutCfg)
	enum { IDD = IDD_DLG_VIDEO_INTERCOM_IOOUT };
	CComboBox	m_comboUseType;
	CComboBox	m_comboIOOut;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVideoIntercomIOOutCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVideoIntercomIOOutCfg)
	afx_msg void OnSelchangeComboIoout();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lServerID;
	LONG m_iDevIndex;
	NET_DVR_VIDEO_INTERCOM_IOOUT_CFG m_struIOOutCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIDEOINTERCOMIOOUTCFG_H__3D94FEB8_7211_4BB1_A118_69D2C6437922__INCLUDED_)
