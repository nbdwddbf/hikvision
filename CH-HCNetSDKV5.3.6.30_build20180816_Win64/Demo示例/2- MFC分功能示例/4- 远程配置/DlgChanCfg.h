#if !defined(AFX_DLGCHANCFG_H__FD32E50F_9D0E_4B78_B7B2_01162F7A1D5C__INCLUDED_)
#define AFX_DLGCHANCFG_H__FD32E50F_9D0E_4B78_B7B2_01162F7A1D5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgChanCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgChanCfg dialog

class CDlgChanCfg : public CDialog
{
// Construction
public:
	LONG	m_lStartChannel;//显示的设备初始通道号,一般为1开始
	void CurCfgUpdate();
	NET_DVR_COMPRESSIONCFG_V30 m_struCompressionCfg[MAX_CHANNUM_V30];
	NET_DVR_RECORD_V30 m_struRecordCfg[MAX_CHANNUM_V30];
	NET_DVR_PICCFG_V30 m_struPicCfg[MAX_CHANNUM_V30];
	CDlgChanCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgChanCfg)
	enum { IDD = IDD_DIALOG_CHAN_CFG };
	CComboBox	m_comboCopyChan;
	CComboBox	m_comboHourType;
	CComboBox	m_comboOsdType;
	CComboBox	m_comboOsdAttrib;
	CComboBox	m_comboRecordDelay;
	CComboBox	m_comboPrerecordTime;
	CComboBox	m_comboCompressionType;
	CComboBox	m_comboChanNum;
	CComboBox	m_comboFrameBPInterval;
	CComboBox	m_comboMaxBitRate;
	CComboBox	m_comboFrameRate;
	CComboBox	m_comboResolution;
	CComboBox	m_comboBitRateType;
	CComboBox	m_comboStreamType;
	CComboBox	m_comboImageQuality;
	UINT	m_iFrame_I_Iterval;
	BOOL	m_bCheckRecord;
	DWORD	m_dwDurationTime;
	BOOL	m_bCheckOsd;
	int		m_iOsdX;
	int		m_iOsdY;
	BOOL	m_bChkDispWeek;
	BOOL	m_bCheckChanName;
	int		m_iChanNameX;
	int		m_iChanNameY;
	BOOL	m_bCheckHideArea;
	BOOL	m_bCheckMotion;
	BOOL	m_bCheckHideAlarm;
	BOOL	m_bCheckVILost;
	int		m_iBitRate;
	CString	m_csChannelName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgChanCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgChanCfg)
	afx_msg void OnBnClickedChkHideArea();
	afx_msg void OnBnClickedChkRecord();
	afx_msg void OnBnClickedChkMotion();
	afx_msg void OnBnClickedChkVilost();
	afx_msg void OnBnClickedChkHideAlarm();
	afx_msg void OnBnClickedChkOsd();
	afx_msg void OnBnClickedChkChanNamePos();
	afx_msg void OnButtonSetCompressionCfg();
	afx_msg void OnButtonSetRecordCfg();
	afx_msg void OnButtonSetPictureCfg();
	afx_msg void OnBnClickedBtnString();
	afx_msg void OnBnClickedBtnHideSetup();
	afx_msg void OnBnClickedBtnHideAlarmSetup();
	afx_msg void OnBnClickedBtnRemoteRecordSetup();
	afx_msg void OnBnClickedBtnMotionSetup();
	afx_msg void OnBnClickedBtnVilostSetup();
	afx_msg void OnCbnSelchangeComboChan();
	afx_msg void OnCbnSelchangeComboMaxBitRate();
	afx_msg void OnBnClickedChanCfgOK();
	afx_msg void OnBnClickedChanCfgCopy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHANCFG_H__FD32E50F_9D0E_4B78_B7B2_01162F7A1D5C__INCLUDED_)
