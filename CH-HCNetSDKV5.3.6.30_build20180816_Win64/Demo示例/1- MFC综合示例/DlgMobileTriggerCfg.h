#include "afxwin.h"
#if !defined(AFX_DLGMOBILETRIGGERCFG_H__FBCFC8ED_A1EA_4B5C_BEB5_EA1ABF6FABF9__INCLUDED_)
#define AFX_DLGMOBILETRIGGERCFG_H__FBCFC8ED_A1EA_4B5C_BEB5_EA1ABF6FABF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMobileTriggerCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMobileTriggerCfg dialog

class CDlgMobileTriggerCfg : public CDialog
{
// Construction
public:
	CDlgMobileTriggerCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMobileTriggerCfg)
	enum { IDD = IDD_DLG_MOBILE_TRIGGER_CFG };
	CComboBox	m_comboSceneMode;
	BOOL	m_bChkEnable;
	BOOL	m_bChkHoldSpecialRoad;
	BOOL	m_bChkBigCar;
	BOOL	m_bChkCarPressRoad;
	BOOL	m_bChkPost;
	BOOL	m_bChkPost2;
	BOOL	m_bChkPressRoad;
	BOOL	m_bChkRecordEnable;
	DWORD	m_dwOverRecordTime;
	DWORD	m_dwCapNum;
	DWORD	m_dwPreRecordTime;

	//}}AFX_DATA
	LONG m_lPlayHandle;
	CRect m_rcWnd;
	DWORD m_dwPosNum;
	BOOL m_bCloseIn;
	BOOL m_bPolygonMouseMove;
	BOOL m_bMouseMove;

	NET_ITC_LINE  m_struLaneLine1;
	NET_ITC_LINE  m_struLaneLine2;
	NET_ITC_POLYGON m_struPolygon;
	NET_ITC_LINE m_struLaneBoundaryLine;


	BOOL Play();
	void F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser);
	BOOL PreDrawLineMsg(MSG* pMsg, CPoint &pt, LPNET_VCA_LINE pStruLine);
	BOOL PreDrawPolygonMsg(MSG* pMsg, CPoint &pt, LPNET_ITC_POLYGON pStruPolygon);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMobileTriggerCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMobileTriggerCfg)
	afx_msg void OnBrnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeComboSceneMode();
	afx_msg void OnChkCarpressRoad();
	afx_msg void OnChkHoldSpecialroad();
	afx_msg void OnChkPost2();
	virtual BOOL OnInitDialog();
	afx_msg void OnChkPost();
	afx_msg void OnChkBigcar();
	afx_msg void OnChkPressRoad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG  m_lChannel;
    long  m_lServerID; // 用户ID
    int   m_iDevIndex; // 设备索引
    NET_ITC_TRIGGERCFG m_struTrigger;
	BOOL m_bChkBackRecog;
	BOOL m_bChkForWardRecog;
	BOOL m_bBoundaryLine;
	BOOL m_bCleanPloygon;
	BOOL m_bDriveLine;
	BOOL m_bIllegalPark;
	BOOL m_bLaneLine1;
	BOOL m_bLaneLine2;
	BOOL m_bPolygon;
	BOOL m_bReverseDrive;
	BOOL m_bShowPolygon;
	CComboBox m_comLaneDir;
	afx_msg void OnBnClickedChkForwardRecog();
	afx_msg void OnBnClickedChkBackRecog();
	afx_msg void OnBnClickedChkShowPolygon();
	afx_msg void OnBnClickedChkCleanPloygon();
	afx_msg void OnBnClickedChkLaneline1();
	afx_msg void OnBnClickedChkLaneline2();
	afx_msg void OnBnClickedChkBoundaryline();
	afx_msg void OnBnClickedChkPolygon();
	afx_msg void OnCbnSelchangeComboIntervalType();
	CComboBox m_comboIntervalType;
	DWORD m_dwInterval2;
	DWORD m_dwInterval1;
	afx_msg void OnBnClickedChkDriveLine();
	afx_msg void OnBnClickedChkReverseDrive();
	afx_msg void OnBnClickedChkIllegalPark();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMOBILETRIGGERCFG_H__FBCFC8ED_A1EA_4B5C_BEB5_EA1ABF6FABF9__INCLUDED_)
