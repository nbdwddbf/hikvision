#if !defined(AFX_DLGLCDSWITCHCFG_H__40611CF5_BA4A_4202_A7D5_6ADF649EAEC5__INCLUDED_)
#define AFX_DLGLCDSWITCHCFG_H__40611CF5_BA4A_4202_A7D5_6ADF649EAEC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLcdSwitchCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdSwitchCfg dialog

class CDlgLcdSwitchCfg : public CDialog
{
// Construction
public:
	CDlgLcdSwitchCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLcdSwitchCfg)
	enum { IDD = IDD_DLG_LCD_SWITCH_CFG };
	CComboBox	m_comboWeekDay;
	CComboBox	m_comboSwitchType4;
	CComboBox	m_comboSwitchType3;
	CComboBox	m_comboSwitchType2;
	CComboBox	m_comboSwitchType1;
	CComboBox	m_comboSwitchTypeHoliday;
	CComboBox	m_comboHolidayNo;
	CComboBox	m_comboCopy;
	DWORD	m_dwDelayBootTme;
	COleDateTime	m_ctHms;
	COleDateTime	m_ctHmsTp1;
	COleDateTime	m_ctHmsTp2;
	COleDateTime	m_ctHmsTp3;
	COleDateTime	m_ctYmd;
	BYTE	m_byWallNo;
	BOOL	m_bTp1;
	BOOL	m_bTp2;
	BOOL	m_bTp3;
	BOOL	m_bTp4;
	BOOL	m_bHolidayTp;
	COleDateTime	m_ctHmsTp4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLcdSwitchCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLcdSwitchCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnLcdSwitchOk();
	afx_msg void OnBtnLcdSwitchCopy();
	afx_msg void OnBtnLcdHolidayOk();
	afx_msg void OnSelchangeComboWeekDay();
	afx_msg void OnSelchangeComboHolidayTpNo();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserId;
    int m_iDeviceIndex;
    NET_DVR_VIDEO_WALL_AREA m_struWallArea;
    NET_DVR_TIME_SWITCH_CFG m_struTimeSwitch;
    NET_DVR_DELAY_TIME m_struDelayTime;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLCDSWITCHCFG_H__40611CF5_BA4A_4202_A7D5_6ADF649EAEC5__INCLUDED_)
