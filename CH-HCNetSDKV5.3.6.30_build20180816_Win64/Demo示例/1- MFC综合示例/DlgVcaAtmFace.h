#if !defined(AFX_DLGVCAATMFACE_H__D870CE7D_2C7F_4D67_B37B_2CD56D4FE771__INCLUDED_)
#define AFX_DLGVCAATMFACE_H__D870CE7D_2C7F_4D67_B37B_2CD56D4FE771__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaAtmFace.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaAtmFace dialog

class CDlgVcaAtmFace : public CDialog
{
// Construction
public:
	CDlgVcaAtmFace(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaAtmFace)
	enum { IDD = IDD_DLG_VCA_ATM_FACE };
	CComboBox	m_comboDetectType;
	CComboBox	m_comboAtmChanMode1;
    CComboBox	m_comboAtmChanMode2;
    CComboBox	m_comboAtmChanMode3;
    CComboBox	m_comboAtmChanMode4;
	CComboBox	m_comboVcaStream1;
    CComboBox	m_comboVcaStream2;
    CComboBox	m_comboVcaStream3;
    CComboBox	m_comboVcaStream4;
	CComboBox	m_comboChanType1;
    CComboBox	m_comboChanType2;
    CComboBox	m_comboChanType3;
    CComboBox	m_comboChanType4;
	CComboBox	m_comboResolution;
    CComboBox	m_comboProPicType;
	CComboBox	m_comboPicQuality;
    int		m_iHour11; 
    int		m_iHour12;
    int		m_iHour21;
    int		m_iHour22;
    int		m_iMin11;
    int		m_iMin12;
    int		m_iMin21;
	int		m_iMin22;
    CComboBox	m_comboWeekday;
    CComboBox	m_comboCopyTime;
    BOOL	m_bHandleType1;
    BOOL	m_bHandleType2;
    BOOL	m_bHandleType3;
    BOOL	m_bHandleType4;
	BOOL	m_bHandleType5;
    CListCtrl	m_listRecordChan;
	CListCtrl	m_listAlarmOut;
	BOOL	m_bVcaEnable1;
    BOOL	m_bVcaEnable2;
    BOOL	m_bVcaEnable3;
    BOOL	m_bVcaEnable4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaAtmFace)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaAtmFace)
	afx_msg void OnBtnSetDetectRule();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimeOk();
	afx_msg void OnTimeCopy();
    afx_msg void OnCheckhandletype4();
	afx_msg void OnChkVcaCtrl1();
	afx_msg void OnChkVcaCtrl2();
	afx_msg void OnChkVcaCtrl3();
	afx_msg void OnChkVcaCtrl4();
	afx_msg void OnBtnSetCtrlcfg();
	afx_msg void OnBtnGetCtrlcfg();
	afx_msg void OnSelchangeComboDetectType();
	afx_msg void OnSelchangeComboweekday();
	afx_msg void OnSelchangeCombocopytime();
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    long    m_lServerID;            
    int     m_iDevIndex;           
    int     m_iStartChannel;       
    int     m_iChannelNum;          
    NET_VCA_CTRLCFG m_struVcaCtrl; 

    long    m_lPlayHandle;
    
    NET_DVR_DETECT_RULECFG m_struDetectRule;    

    NET_DVR_DETECT_RECT_LIST m_struDetectRectList;

    long  m_lChannel; 

    long m_lDetectChannel;

    NET_DVR_SCHEDTIME m_struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_2]; 

    DWORD	m_dwAlarmOutNum; 
    
    CRect  m_rcWndRect;

    BOOL m_bMouseMove; 
    
    BOOL m_bMaxRectNum;
public:
    
    long StartRealPlay();   

    BOOL StopRealPlay();

    void F_DrawDetectRule(LONG lRealHandle, HDC hDc, DWORD dwUser);

    BOOL SetDetectRule();   

    BOOL GetDetectRule();

    BOOL F_TimeTest(); 

    void SetAlarmTimePara();

    void  GetAlarmTimeShow();
    
    void SetAlarmPara(NET_DVR_HANDLEEXCEPTION_V30 &struHandleType); 

    void GetDetectRuleShow(NET_DVR_DETECT_RULECFG struDetectRule);

    void GetVcaCtrlShow(NET_VCA_CTRLCFG struVcaCtrl);

    void InitlControls();

    void ShowAlarmNum(NET_DVR_HANDLEEXCEPTION_V30 struHandleType,int nAlarmNum);

    BOOL F_ShowRecordChan(NET_DVR_DETECT_RULECFG struDetectRule, int nChanNum);   

    void SetRelRecordChan(NET_DVR_DETECT_RULECFG &struDetectRule, int nChanNum);

    void F_DrawRect(HDC hDc, NET_VCA_RECT struRect, int iRectNo, COLORREF color);
    
    //void SetDetectRectList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAATMFACE_H__D870CE7D_2C7F_4D67_B37B_2CD56D4FE771__INCLUDED_)
