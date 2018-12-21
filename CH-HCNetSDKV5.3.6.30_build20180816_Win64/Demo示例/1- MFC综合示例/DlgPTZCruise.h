#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "ClientDemo.h"

// CDlgPTZCruise dialog

class CDlgPTZCruise : public CDialog
{
	DECLARE_DYNAMIC(CDlgPTZCruise)

public:
	CDlgPTZCruise(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPTZCruise();

// Dialog Data
public:
	//{{AFX_DATA(CDlgPTZCruise)
	enum { IDD = IDD_DLG_PTZ_CRUISE };
	CComboBox m_comboSeqPreset;
	CComboBox m_comboSeqTime;
	CComboBox m_comboSeqSpeed;
	CComboBox m_comboPoint;
	CComboBox m_comboCruiseRoute;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CDlgPTZCruise)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPTZCruise)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnCbnSelchangeComboCruisePoint();
	afx_msg void OnCbnSelchangeComboCruiseRoute();
	afx_msg void OnBnClickedBtnExit();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	long m_lRealHandle;	
	int m_iCruiseNum;
	int m_iSeqPoint;
	int m_iPresetNum;
	int m_iSeqDwell;//time interval
	int m_iSeqSpeed;
	BOOL m_bPrivateIPMode;
	NET_DVR_CRUISE_RET m_struCruiseRet;
	NET_DVR_CRUISEPOINT_COND m_struCruisePointCond;
	NET_DVR_CRUISEPOINT_V50 m_struCruisePointV50;
};
