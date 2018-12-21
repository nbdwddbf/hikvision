#if !defined(AFX_DLGPRODUCTCFG_H__55AC6BBF_5994_4C79_9E8B_6CE53A99BD19__INCLUDED_)
#define AFX_DLGPRODUCTCFG_H__55AC6BBF_5994_4C79_9E8B_6CE53A99BD19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DlgProductVcaCfg.h"
#include "DlgProductAlarmHostCfg.h"
#include "SubDlgDVRNVRCfg.h"
#include "SubDlgCVRCfg.h"
#include "SubDlgMatDecCfg.h"
#include "DlgProductDH.h"
#include "DlgSubIPCCfg.h"
#include "DlgSubITSCfg.h"
#include "DlgProductAcs.h"
#include "DlgVideoIntercomCfg.h"
// DlgProductCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProductCfg dialog

class CDlgProductCfg : public CDialog
{
// Construction
public:
	CDlgProductCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgProductCfg)
	enum { IDD = IDD_DLG_PRODUCT_CFG };
	CTabCtrl	m_tabProductType;
	//}}AFX_DATA
    enum
	{   
		SUB_WND_VCA = 0,
		SUB_WND_ALARMHOST = 1,
        SUB_WND_NVR = 2,
        SUB_WND_CVR = 3,
        SUB_WND_MATDEC = 4,
		SUB_WND_IPCD = 5,
		SUB_WND_ITS = 6,
        SUB_WND_ACS = 7,
		SUB_WND_VIS = 8,
        SUB_WND_DH=9
	};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProductCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProductCfg)
	afx_msg void OnSelchangeTabProductType(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void ShowChildWnd(int nChildWnd);
public:
	void UpdateWindowParam(LONG lDevIndex,LONG lChanIndex);
private:
	CDlgProductVcaCfg m_subDlgVca;
	CDlgProductAlarmHostCfg m_subdlgAlarmHost;
    CSubDlgDVRNVRCfg m_subDVRNVRCfg;
    CSubDlgCVRCfg m_subCVRCfg;
    CMatDecCFG m_subDlgMatDecCfg;
	CDlgSubIPCCfg m_subDlgIpcCfg;
	CSubDlgITSCfg m_subDlgItsCfg;
    CDlgProductAcs m_subDlgAcsCfg;
	CDlgVideoIntercomCfg m_subDlgVISCfg;
    CDlgProductDH m_subDlgDH;
	CRect m_rcChildWnd;

public:
	LONG m_lUserID;
	LONG m_lChannel;
	int  m_iDevIndex;
	
};	

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPRODUCTCFG_H__55AC6BBF_5994_4C79_9E8B_6CE53A99BD19__INCLUDED_)
