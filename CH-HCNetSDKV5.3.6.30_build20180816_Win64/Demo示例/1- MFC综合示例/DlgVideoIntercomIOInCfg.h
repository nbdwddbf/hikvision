#if !defined(AFX_DLGVIDEOINTERCOMIOINCFG_H__C41AC768_10B8_44CD_9425_8A95FE826CD0__INCLUDED_)
#define AFX_DLGVIDEOINTERCOMIOINCFG_H__C41AC768_10B8_44CD_9425_8A95FE826CD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVideoIntercomIOInCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgVideoIntercomIOInCfg dialog

class DlgVideoIntercomIOInCfg : public CDialog
{
// Construction
public:
	DlgVideoIntercomIOInCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgVideoIntercomIOInCfg)
	enum { IDD = IDD_DLG_VIDEO_INTERCOM_IOINCFG };
	CComboBox	m_comboIO;
	CComboBox	m_comboUseType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgVideoIntercomIOInCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgVideoIntercomIOInCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeComboIoin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lServerID;
	LONG m_iDevIndex;
	NET_DVR_VIDEO_INTERCOM_IOIN_CFG m_struIOInCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIDEOINTERCOMIOINCFG_H__C41AC768_10B8_44CD_9425_8A95FE826CD0__INCLUDED_)
