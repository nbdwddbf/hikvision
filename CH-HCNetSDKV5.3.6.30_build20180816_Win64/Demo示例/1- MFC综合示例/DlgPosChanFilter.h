#if !defined(AFX_DLGPOSCHANFILTER_H__4272EF55_9569_470E_86FE_757CB3E4B397__INCLUDED_)
#define AFX_DLGPOSCHANFILTER_H__4272EF55_9569_470E_86FE_757CB3E4B397__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPosChanFilter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPosChanFilter dialog

class CDlgPosChanFilter : public CDialog
{
// Construction
public:
	CDlgPosChanFilter(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPosChanFilter();
// Dialog Data
	//{{AFX_DATA(CDlgPosChanFilter)
	enum { IDD = IDD_DLG_POS_CHAN_FLTERCFG };
	CComboBox	m_cmbOverlayMode;
	CComboBox	m_cmbDayCopy;
	CComboBox	m_cmbWeekDay;
	CTreeCtrl	m_treeChan;
	CTreeCtrl	m_treeAlarmOut;
	CComboBox	m_cmbFontSize;
	CComboBox	m_comboTheFilterNum;
	CComboBox	m_comboGroup;
	CComboBox	m_comboChannel;
	BYTE	m_byColorB;
	BYTE	m_byColorG;
	BYTE	m_byColorR;
	UINT	m_wDelayTime;
	UINT	m_dwHour11;
	UINT	m_dwHour12;
	UINT	m_dwHour21;
	UINT	m_dwHour22;
	UINT	m_dwHour31;
	UINT	m_dwHour32;
	UINT	m_dwHour41;
	UINT	m_dwHour42;
	UINT	m_dwHour51;
	UINT	m_dwHour52;
	UINT	m_dwHour61;
	UINT	m_dwHour62;
	UINT	m_dwHour71;
	UINT	m_dwHour72;
	UINT	m_dwHour81;
	UINT	m_dwHour82;
	UINT	m_dwMin11;
	UINT	m_dwMin12;
	UINT	m_dwMin21;
	UINT	m_dwMin22;
	UINT	m_dwMin31;
	UINT	m_dwMin32;
	UINT	m_dwMin41;
	UINT	m_dwMin42;
	UINT	m_dwMin51;
	UINT	m_dwMin52;
	UINT	m_dwMin61;
	UINT	m_dwMin62;
	UINT	m_dwMin71;
	UINT	m_dwMin72;
	UINT	m_dwMin81;
	UINT	m_dwMin82;
	float	m_fRegionLenth;
	float	m_fRegionWight;
	float	m_fReginX;
	float	m_fRegionY;
	BOOL	m_bChkAudioAlarm;
	BOOL	m_bChkInvokeAlarmOut;
	BOOL	m_bChkInvokeJepgCap;
	BOOL	m_bPicFtp;
    BOOL	m_bPicCloud;
	BOOL	m_bReportCenter;
	BOOL	m_bShowPosInfo;
	BOOL	m_bMonitorAlarm;
	BOOL	m_bAlarmoutEmap;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPosChanFilter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPosChanFilter)
	afx_msg void OnBtnRefresh();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboGroup();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnSelchangeComboChannel();
	afx_msg void OnEditchangeComboThefilternum();
	afx_msg void OnSelchangeComboThefilternum();
	afx_msg void OnBtnMotionDayCopy();
	afx_msg void OnSelchangeComboMotionWeekday();
	afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeChan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMotionDayOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void GetFilterCfgInfo(UINT dwIndex);
	void AddChanInfo();
	void ShowPosFilterInfo( UINT dwTheFilterNum)  ; //dwTheFilterNum ´Ó0¿ªÊ¼
	void CreateTree();
	void GetChanFilterInfo();
	void SetChanFilterInfo();
	BOOL TimeTest();
public:
	int m_iUserID;
	int m_iDevIndex;
	DWORD m_dwCurselectIndx;
    NET_DVR_CHAN_FILTER_CFG m_struChanFilterCfg; 
	NET_DVR_CHANNEL_GROUP m_struChanGroup;
	BOOL *m_pbAlarmOut;
	BOOL *m_pbRecordChan;

    DWORD m_dwTimeOut;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPOSCHANFILTER_H__4272EF55_9569_470E_86FE_757CB3E4B397__INCLUDED_)
