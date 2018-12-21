#if !defined(AFX_DLGITSOVERLAPCFG_H__B2224196_2CBE_404E_9604_EA7A92BD6FCD__INCLUDED_)
#define AFX_DLGITSOVERLAPCFG_H__B2224196_2CBE_404E_9604_EA7A92BD6FCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgITSOverlapCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgITSOverlapCfg dialog

class CDlgITSOverlapCfg : public CDialog
{
// Construction
public:
	CDlgITSOverlapCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgITSOverlapCfg)
	enum { IDD = IDD_DLG_ITS_OVERLAP_CFG };
	CComboBox	m_comRelateType;
	CComboBox	m_comSceneID;
	CComboBox	m_comPicMode;
	CComboBox	m_comboOverlapType;
	CComboBox	m_comboOverlapNO;
	CComboBox	m_comboItemStlye;
	CComboBox	m_comboConfigMode;
	CComboBox	m_comboCharStlye;
	CComboBox	m_comboCharSize;
	BOOL	m_bChkColorAdapt;
	BOOL	m_bChkEnable;
	DWORD	m_dwBackColorRGB;
	CString	m_csCameraNum;
	BYTE	m_byChangeLineNum;
	DWORD	m_dwCharInterval;
	CString	m_csDirection;
	CString	m_csDirectionInfo;
	DWORD	m_dwForeColorRGB;
	CString	m_csInstrumentNum;
	CString	m_csLaneInfo;
	DWORD	m_dwItemLength;
	DWORD	m_dwLinePercent;
	CString	m_csMonitor1Info;
	CString	m_csMonitor2Info;
	CString	m_csRoadNum;
	CString	m_csSite;
	BYTE	m_bySpaceNum;
	DWORD	m_dwStartLeftPos;
	DWORD	m_dwStartTopPos;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgITSOverlapCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgITSOverlapCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnSure();
	afx_msg void OnSelchangeComboOverlapNo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lChannel; 
    int  m_iDevIndex;
    LONG m_lServerID;
	DWORD m_dwOverlapSel;
	NET_ITS_OVERLAP_CFG m_struOverlap;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGITSOVERLAPCFG_H__B2224196_2CBE_404E_9604_EA7A92BD6FCD__INCLUDED_)
