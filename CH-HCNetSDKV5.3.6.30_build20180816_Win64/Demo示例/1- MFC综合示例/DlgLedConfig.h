#include "afxcmn.h"
#if !defined(AFX_DLGLEDCONFIG_H__53BE3452_0419_46D6_B472_4637F18C0C75__INCLUDED_)
#define AFX_DLGLEDCONFIG_H__53BE3452_0419_46D6_B472_4637F18C0C75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLEDConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLEDConfig dialog
#define MAX_COUNT 256
class CDlgLedConfig : public CDialog
{
// Construction
public:
	CDlgLedConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLedConfig)
	enum { IDD = IDD_DLG_LED_CONFIG };
	CComboBox	m_cmbPortMode;
	CListCtrl	m_lstRecvCardInfo;
	CListCtrl	m_lstOutput;
	CListCtrl	m_lstOutputPort;
	BOOL	m_BOutputEnable;
	DWORD	m_dwOutputPort;
	DWORD	m_dwOutputNo;
	BOOL	m_BZoom;
	DWORD	m_dwOutputNoCfg;
	DWORD	m_dwRefresh;
	DWORD	m_dwRelateInput;
	DWORD	m_dwHeight;
	DWORD	m_dwWidth;
	DWORD	m_dwOutputNoDisplay;
	DWORD	m_dwLineNo;
	DWORD	m_dwColumnNo;
	DWORD	m_dwDisplayWidth;
	DWORD	m_dwDisplayHeight;
	BOOL	m_BPortCfgEnable;
	DWORD	m_dwOutputJs;
	DWORD	m_dwPortIndexJs;
	DWORD	m_dwColumnNoPort;
	DWORD	m_dwHeightPortCfg;
	DWORD	m_dwWidthPortCfg;
	DWORD	m_dwLineNoPortCfg;
	DWORD	m_dwOutputPortCfgOne;
	DWORD	m_dwRealOutputPortCfg;
	DWORD	m_dwPairPort;
	BOOL	m_bBackupEnable;
	BOOL	m_bBlackedgeEnable;
	DWORD	m_dwCardWidth;
	DWORD	m_dwCardHeight;
	BOOL	m_bAutoAjust;
	DWORD	m_dwClock;
	DWORD	m_dwHPosition;
	DWORD	m_dwPhase;
	DWORD	m_dwRefreshRate;
	DWORD	m_dwResolutionHeight;
	DWORD	m_dwResolutionWidth;
	DWORD	m_dwVPosition;
	DWORD	m_dwInputNo;
	DWORD	m_dwCount;
	NET_DVR_UPLOAD_PICTURE_INFO m_struPicInfo;
	char* m_pPicInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLedConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLedConfig)
	afx_msg void OnButOutputPortAdd();
	afx_msg void OnButOutputPortDelete();
	afx_msg void OnButOutputCfgGet();
	afx_msg void OnButOutputCfgSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickLstLedOutputPort(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButOutputGet();
	afx_msg void OnButOutputSet();
	afx_msg void OnButDisplayGet();
	afx_msg void OnButDisplaySet();
	afx_msg void OnButPortcfgAdd();
	afx_msg void OnButPortcfgDel();
	afx_msg void OnButPortCfgPortAdd();
	afx_msg void OnButPortCfgPortDel();
	afx_msg void OnButPortCfgPortMod();
	afx_msg void OnButPortcfgGet();
	afx_msg void OnClickLstPortcfgOutput(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickLstRecvcardinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButPortcfgGetall();
	afx_msg void OnButPortcfgSet();
	afx_msg void OnBtnInputcfgGet();
	afx_msg void OnBtnInputcfgSet();
	afx_msg void OnBtnDisplayConfig();
	afx_msg void OnBtnRecvcardConfig();
	afx_msg void OnButOutputPortModify();
	afx_msg void OnButOutputPortcfgMod();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID; 
	LONG m_lDeviceID; 
	int  m_iCurSel; 
	int  m_iCurSelOutputPortCfg; 
	int  m_iCurSelRecvCardInfo; 
	NET_DVR_LED_PORT_CFG   m_struPortCfg[MAX_COUNT];
	DWORD m_status[MAX_COUNT];
	DWORD m_dwOutputPortCfg[MAX_COUNT];


protected:
	void UpdatePortList(const NET_DVR_LED_OUTPUT_PORT_CFG &struOutputCfg);
	void UpdateOutputListPortCfg(DWORD dwCount); 
	void UpdatRecvCardList(); 

public:
	void Init(LONG lUserID, LONG lDeviceID){m_lUserID = lUserID;m_lDeviceID = lDeviceID;};
   
    afx_msg void OnBnClickedBtnEnableGet();
    afx_msg void OnBnClickedBtnEnableSet();
	afx_msg void OnBnClickedBtnBrosepicpath();
	afx_msg void OnBnClickedBtnUploadledpic();
	BOOL CDlgLedConfig::UploadLedPic(CString csFileName, BYTE byPicType, int listIndex);
	void CDlgLedConfig::RefreshList();
	afx_msg void OnBnClickedBtnCheck();
	afx_msg void OnBnClickedButDelLedPic();
	CProgressCtrl m_ProUploadLedPic;
	CListCtrl m_ListLedPic;
	CString m_filePathSel[MAX_COUNT];
	CString m_filePathOld[MAX_COUNT];
	CString m_filePathNew[MAX_COUNT];
	DWORD m_dwEnableID;
	BOOL m_bCheckEnable;
	LONG m_lUploadLedPicHandle;
	int m_fileNo[MAX_COUNT];
	afx_msg void OnBnClickedButton1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DlgLedConfig_H__53BE3452_0419_46D6_B472_4637F18C0C75__INCLUDED_)
