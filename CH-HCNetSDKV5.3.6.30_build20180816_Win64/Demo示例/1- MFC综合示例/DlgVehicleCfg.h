#if !defined(AFX_DLGVEHICLECFG_H__E77FE27B_7F2E_46AD_890B_24D43DAA2DE5__INCLUDED_)
#define AFX_DLGVEHICLECFG_H__E77FE27B_7F2E_46AD_890B_24D43DAA2DE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVehicleCfg.h : header file
#include "DlgVehicleControlCfg.h"
#include "DlgVehicleMvaCfg.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgVehicleCfg dialog

class CDlgVehicleCfg : public CDialog
{
// Construction
public:
	CDlgVehicleCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVehicleCfg)
	enum { IDD = IDD_DLG_VEHICLE_CFG };
	CTabCtrl	m_tabVehicleCfg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVehicleCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVehicleCfg)
	afx_msg void OnSelchangeTabVehicleCfg(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG	m_lServerID;
	DWORD	m_dwDevIndex;
    DWORD	m_dwAlarmOutNum;
    DWORD   m_nChannel;
    DWORD   m_lStartChan;
	int m_iChannelIndex;
	CDlgVehicleControlCfg m_struVehicleControl;
	CDlgVehicleMvaCfg m_struVehicleMvaCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVEHICLECFG_H__E77FE27B_7F2E_46AD_890B_24D43DAA2DE5__INCLUDED_)
