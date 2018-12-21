#include "afxwin.h"
#if !defined(AFX_DLGVCAFACESNAPCFG_H__A42FD62C_FB09_4AC7_8310_DE9DA45C423A__INCLUDED_)
#define AFX_DLGVCAFACESNAPCFG_H__A42FD62C_FB09_4AC7_8310_DE9DA45C423A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaFaceSnapCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFaceSnapCfg dialog

class CDlgVcaFaceSnapCfg : public CDialog
{
// Construction
public:
	CDlgVcaFaceSnapCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaFaceSnapCfg)
	enum { IDD = IDD_DLG_VCA_FACE_SNAP };
	CComboBox	m_cmbChannel;
	CComboBox	m_comROI;
	CComboBox	m_comFaceEnable;
	CComboBox	m_comBackgroundPic;
	CComboBox	m_comboMatchType;
	CComboBox	m_comboSensitive;
	CComboBox	m_comboSnapTimes;
	CComboBox	m_comboRuleNum;
	CComboBox	m_comboPicQuality;
	CComboBox	m_comboPicResolution;
	BOOL	m_bChkFilterActive;
	BOOL	m_bDrawPolygon;
	BOOL	m_bChkEnable;
	BYTE	m_byRate;
	BOOL	m_bSetMiniFilter;
	BOOL	m_bSetMaxFilter;
	BYTE	m_bySnapInterval;
	BYTE	m_bySnapThreshold;
	BYTE	m_byReferBright;
	BYTE	m_byMatchThreshold;
	DWORD	m_dwFaceExposureMinDuration;
	DWORD	m_dwTerminalNo;
	DWORD	m_dwUploadInterval;
	DWORD	m_dwValidFaceMinDuration;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaFaceSnapCfg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaFaceSnapCfg)
	afx_msg void OnBtnSure();
	afx_msg void OnBtnSetFacesnap();
	afx_msg void OnCheckSetMiniFilter();
	afx_msg void OnCheckSetMaxFilter();
	afx_msg void OnCheckFilterActive();
	afx_msg void OnChkDrawPolygon();
	afx_msg void OnSelchangeComboRuleNum();
	afx_msg void OnBtnGetFacesnap();
	afx_msg void OnSelchangeComboChannel();
	afx_msg void OnBtnEventSearchList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;
	
    NET_VCA_FACESNAPCFG m_struFaceSnap;
	
    LONG    m_lPlayHandle;
    
    CRect   m_rcWnd;
	BOOL    m_bCloseIn;
    BOOL    m_bMouseMove;
    BOOL    m_bNeedRedraw;
    DWORD   m_dwPosNum; 
	DWORD   m_dwRuleNum;
	
	LONG StartPlay();
	BOOL StopPlay();
	BOOL GetFaceSnap();
	BOOL SetFaceSnap();
	void GetFaceSnapFromWnd(NET_VCA_FACESNAPCFG& struFaceSnap);
	void SetFaceSnapToWnd(NET_VCA_FACESNAPCFG const &struFaceSnap);
	
	void F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser);
    void F_DrawFrame(HDC hDc);
	
	BOOL PreDrawPolygonMsg(MSG* pMsg, CPoint &pt);
	BOOL PreDrawSizeFilterMsg(MSG* pMsg, CPoint &pt);
    DWORD m_FaceFilteringTime;
    CComboBox m_comSceneID;
	CComboBox m_comInvalCapFilterEnable;
	BYTE m_byInvalCapFilterThreshold;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAFACESNAPCFG_H__A42FD62C_FB09_4AC7_8310_DE9DA45C423A__INCLUDED_)
