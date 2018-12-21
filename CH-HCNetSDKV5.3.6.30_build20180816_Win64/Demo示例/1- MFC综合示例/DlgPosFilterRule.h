#if !defined(AFX_DLGPOSFILTERRULE_H__95CC9870_4D58_42B1_B88E_7B7F5965A01C__INCLUDED_)
#define AFX_DLGPOSFILTERRULE_H__95CC9870_4D58_42B1_B88E_7B7F5965A01C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPosFilterRule.h : header file
//
#include "DlgPOSRegion.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgPosFilterRule dialog

typedef enum tagPROTOCAL_TYPE
{
	MODE_GENERIC = 1,
	MODE_AVE_VSI_ADD,
	MODE_AVE_VNET,
	MODE_EPOSN,
    MODE_NUCLEUS,
    MODE_GILBRARCO,
    MODE_NCR
}PROTOCAL_TYPE;

class CDlgPosFilterRule : public CDialog
{
// Construction
public:
	CDlgPosFilterRule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPosFilterRule)
	enum { IDD = IDD_DLG_POS_FILTERRULE };
	CComboBox	m_cmbCharSetType;
	CStatic	m_picOsdRegion;
	CComboBox	m_cmbFilterID;
	CListCtrl	m_listRule;
	CComboBox	m_comboProtocalType;
	BOOL	m_bEnable;
	BOOL	m_bGenericCaseSensitive;
    BOOL	m_bGenericCaseStartFlag;
    BOOL	m_bGenericCaseEndFlag;
	BOOL	m_bGenericEndHex;
	BOOL	m_bGenericNewLineHex;
	BOOL	m_bGenericStartAnyChar;
	BOOL	m_bGenericStartHex;
	BOOL	m_bOverlayOsd;
	UINT	m_dwActionDelayTime;
	UINT	m_dwAveDisAppearTime;
	CString	m_csFilterRuleName;
	CString	m_csGenericEndData;
	UINT	m_dwGenericEndLine;
	CString	m_csGenericNewlineData;
	CString	m_csGenericStartData;
	CString	m_csGenericIgnore1;
	CString	m_csGenericIgnore2;
	CString	m_csGenericIgnore3;
	CString	m_csGenericIgnore4;
	UINT	m_dwGenericDispearTime;
	UINT	m_dwRegionY;
	UINT	m_dwRegionX;
	UINT	m_dwRegionHeight;
	UINT	m_dwRegionWidth;
	UINT	m_dwAveAddr;
	BOOL	m_bSetDraw;
	BOOL	m_bShowOSD;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPosFilterRule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPosFilterRule)
	afx_msg void OnBtnExport();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboProtocalType();
	afx_msg void OnClickListRule(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnImport();
	afx_msg void OnChkGenericStartAnychar();
	afx_msg void OnBtnDefault();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtnTestEffect();
	afx_msg void OnKillfocusEditGenericStart();
	afx_msg void OnKillfocusEditGenericDispeartime();
	afx_msg void OnChkGenericStartHex();
	afx_msg void OnKillfocusEditAveDisappertime();
	afx_msg void OnKillfocusEditGenericEnd();
	afx_msg void OnChkGenericEndHex();
	afx_msg void OnClose();
	afx_msg void OnKillfocusEditAddrAve();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnChkSet();
	afx_msg void OnChkShow();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SetGenericInfoShow(BOOL bShow);
	void showFilterRuleInfoByIndex(UINT iIndex );
	BOOL SetFilterRuleInfo();
	void AddFilterRuleInfoToList(UINT dwTheFileterNum, BOOL bModify = FALSE);
	BOOL WriteDataToFile(char* szFileName);
	BOOL ReadDataFromFile(char* szFileName);
	void PreviewVedio();
	void ShowDrawOSDRegionInfo(BOOL bShow);
	void GetVideoInfo();
	void HideAllWindows();
private:
	NET_DVR_POS_FILTER_CFG m_struPosFilterCfg;
	DWORD m_dwTheRuleNum;   //当前组的规则总数
	DWORD m_dwCurselectIndx;
	NET_DVR_POS_OSD_REGION m_struPOsOSDRegin;

	CDlgPOSRegion m_dlgRegion;

	LONG	m_lPlayHandle;
	BOOL    m_bDrawdetect;
	CRect m_rcWindowOSDRegion;
	CRect m_rcClientOSDRegion;
	int m_ClientX;
	int m_ClientY;
	CPoint m_ptStart;
	CPoint m_ptEnd;
    DWORD m_dwVedioWidth;
	DWORD m_dwVedioLength;
public:
	int m_iUserID;
	int m_iDevIndex;
	CRect m_DefaultRegion;
	CBrush m_bkBrush;
	CBrush m_bOverBrush;
    CString m_szEmployeeNo;
    CString m_szTerminalNo;
    CString m_szShiftNo;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPOSFILTERRULE_H__95CC9870_4D58_42B1_B88E_7B7F5965A01C__INCLUDED_)
