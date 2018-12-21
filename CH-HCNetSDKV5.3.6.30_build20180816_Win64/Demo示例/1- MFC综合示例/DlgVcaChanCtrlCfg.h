#include "afxwin.h"
#if !defined(AFX_DLGVCACHANCTRLCFG_H__C8AB4BC2_2810_4486_A328_9F83736A0687__INCLUDED_)
#define AFX_DLGVCACHANCTRLCFG_H__C8AB4BC2_2810_4486_A328_9F83736A0687__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaChanCtrlCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaChanCtrlCfg dialog

class CDlgVcaChanCtrlCfg : public CDialog
{
	// Construction
public:
	CDlgVcaChanCtrlCfg(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CDlgVcaChanCtrlCfg)
	enum { IDD = IDD_DLG_VCA_CHAN_CTRL };
	CComboBox	m_comboVcaMode;
	CComboBox	m_comboChanVcaType;
	CComboBox	m_comboChan;
	BOOL	m_bChkStreamWithVca;
	BOOL	m_bChkEnable;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaChanCtrlCfg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CDlgVcaChanCtrlCfg)
	afx_msg void OnBtnSure();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeComboChannel();
	afx_msg void OnSelchangeComboChanVcatype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
public:
	LONG    m_lServerID;
    int     m_iStartChannel;
    int     m_iDevIndex;
    int     m_iChannelNum;
	int     m_iVcaChannel;
	NET_VCA_DEV_ABILITY m_struVcaDevAbility;
	NET_VCA_CTRLCFG m_struVcaCtrlCfg;
	BOOL m_bSupportChanEx;
    NET_DVR_VCA_CTRLINFO_CFG m_struVcaCtrlInfo;
	
	BOOL SetVcaCtrlToWnd(NET_VCA_CTRLINFO const &struVcaCtrlInfo);
    BOOL GetVcaCtrlFromWnd(NET_VCA_CTRLINFO &struVcaCtrlInfo);
    BOOL SetVcaCtrlCfg();
    BOOL GetVcaCtrlCfg();
	BOOL SetVcaCtrlInfoToWnd(NET_DVR_VCA_CTRLINFO_CFG const &struVcaCtrlInfo);
    BOOL GetVcaCtrlInfoFromWnd(NET_DVR_VCA_CTRLINFO_CFG &struVcaCtrlInfo);
	void ShowVcaChanModeParam(int nVcaChanType,int nChanMode);
    int m_iRelatedChan1;
    int m_iRelatedChan2;
    int m_iRelatedChan3;
    int m_iRelatedChan4;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCACHANCTRLCFG_H__C8AB4BC2_2810_4486_A328_9F83736A0687__INCLUDED_)
