#if !defined(AFX_DLGPREVIEWSWITCHCFG_H__DB10E602_9A83_4D90_80E9_4FF7CA1CBB35__INCLUDED_)
#define AFX_DLGPREVIEWSWITCHCFG_H__DB10E602_9A83_4D90_80E9_4FF7CA1CBB35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPreviewSwitchCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPreviewSwitchCfg dialog

class CDlgPreviewSwitchCfg : public CDialog
{
// Construction
public:
	CDlgPreviewSwitchCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPreviewSwitchCfg)
	enum { IDD = IDD_PREVIEW_SWITCH_CFG };
	CComboBox	m_cmbPreviewNumber;
	CComboBox	m_cmbSwitchTime;
	CComboBox	m_cmbVideoOutType;
	CComboBox	m_cmbAudioPreview;
	CComboBox	m_cmbWnd1;
	CComboBox	m_cmbWnd2;
	CComboBox	m_cmbWnd3;
	CComboBox	m_cmbWnd4;
	CComboBox	m_cmbWnd5;
	CComboBox	m_cmbWnd6;
	CComboBox	m_cmbWnd7;
	CComboBox	m_cmbWnd8;
	CComboBox	m_cmbWnd9;
	CComboBox	m_cmbWnd10;
	CComboBox	m_cmbWnd11;
	CComboBox	m_cmbWnd12;
	CComboBox	m_cmbWnd13;
	CComboBox	m_cmbWnd14;
	CComboBox	m_cmbWnd15;
	CComboBox	m_cmbWnd16;
	CComboBox	m_cmbWnd17;
	CComboBox	m_cmbWnd18;
	CComboBox	m_cmbWnd19;
	CComboBox	m_cmbWnd20;
	CComboBox	m_cmbWnd21;
	CComboBox	m_cmbWnd22;
	CComboBox	m_cmbWnd23;
	CComboBox	m_cmbWnd24;
	CComboBox	m_cmbWnd25;
	CComboBox	m_cmbWnd26;
	CComboBox	m_cmbWnd27;
	CComboBox	m_cmbWnd28;
	CComboBox	m_cmbWnd29;
	CComboBox	m_cmbWnd30;
	CComboBox	m_cmbWnd31;
	CComboBox	m_cmbWnd32;
	CComboBox	m_cmbWnd33;
	CComboBox	m_cmbWnd34;
	CComboBox	m_cmbWnd35;
	CComboBox	m_cmbWnd36;
	CComboBox	m_cmbWnd37;
	CComboBox	m_cmbWnd38;
	CComboBox	m_cmbWnd39;
	CComboBox	m_cmbWnd40;
	CComboBox	m_cmbWnd41;
	CComboBox	m_cmbWnd42;
	CComboBox	m_cmbWnd43;
	CComboBox	m_cmbWnd44;
	CComboBox	m_cmbWnd45;
	CComboBox	m_cmbWnd46;
	CComboBox	m_cmbWnd47;
	CComboBox	m_cmbWnd48;
	CComboBox	m_cmbWnd49;
	CComboBox	m_cmbWnd50;
	CComboBox	m_cmbWnd51;
	CComboBox	m_cmbWnd52;
	CComboBox	m_cmbWnd53;
	CComboBox	m_cmbWnd54;
	CComboBox	m_cmbWnd55;
	CComboBox	m_cmbWnd56;
	CComboBox	m_cmbWnd57;
	CComboBox	m_cmbWnd58;
	CComboBox	m_cmbWnd59;
	CComboBox	m_cmbWnd60;
	CComboBox	m_cmbWnd61;
	CComboBox	m_cmbWnd62;
	CComboBox	m_cmbWnd63;
	CComboBox	m_cmbWnd64;
	BYTE		m_byGroup;
	BOOL		m_bSameSource;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreviewSwitchCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPreviewSwitchCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGetPreviewcfg();
	afx_msg void OnBtnSetPreviewcfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lUserID;
    LONG    m_dwDevIndex;
	BOOL	m_bSupportTrail;
public:
	void AddChanInfoToCmb(CComboBox* cmbWnd1);
    void AddChanInfoToCmb(CComboBox* cmbWnd, DWORD dwItemData);

	void AddChanItemInfo(CComboBox* cmbBox);
    void SelectChanItemInfo(CComboBox* cmbBox, DWORD dwItemData);
    NET_DVR_TRIAL_SYSTEM_INFO m_struSystemInfo;
    BOOL m_bGetDefault;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREVIEWSWITCHCFG_H__DB10E602_9A83_4D90_80E9_4FF7CA1CBB35__INCLUDED_)
