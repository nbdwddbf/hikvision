#if !defined(AFX_DLGVCAFACEDETECT_H__CBACD806_FF76_40EF_90EF_4E9C84848B32__INCLUDED_)
#define AFX_DLGVCAFACEDETECT_H__CBACD806_FF76_40EF_90EF_4E9C84848B32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaFaceDetect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFaceDetect dialog

class CDlgVcaFaceDetect : public CDialog
{
// Construction
public:
	CDlgVcaFaceDetect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaFaceDetect)
	enum { IDD = IDD_DLG_VCA_FACE_DETECT };
	CComboBox	m_comboRelSnapChan3;
	CComboBox	m_comboRelSnapChan2;
	CComboBox	m_comboRelSnapChan1;
	CComboBox	m_comboPIPDiv;
	CComboBox	m_comboBackChannel;
	CComboBox	m_comboPosition;
	CComboBox	m_comboAlarmDelay;
	CComboBox	m_cmUpLastAlarm;
	CComboBox	m_comboSensitive;
	CListCtrl	m_listRecordChan;
	CListCtrl	m_listAlarmOut;
	CComboBox	m_comboWeekDay;
	CComboBox	m_comboCopyTime;
	CComboBox	m_comboResolution;
	CComboBox	m_comboProPicType;
	CComboBox	m_comboPicQuality;
	BOOL	m_bFilterActive;
	BOOL	m_bSetMaxFilter;
	BOOL	m_bSetMiniFilter;
	BOOL	m_bHandleType1;
	BOOL	m_bHandleType2;
	BOOL	m_bHandleType3;
	BOOL	m_bHandleType4;
	BOOL	m_bHandleType5;
	BOOL	m_bDrawPolygon;
	BOOL	m_bEnable;
	CString	m_csRuleName;
	int		m_iHour11;
	int		m_iHour12;
	int		m_iHour21;
	int		m_iHour22;
	int		m_iMin11;
	int		m_iMin12;
	int		m_iMin21;
	int		m_iMin22;
	int		m_iAlarmDuration;
	BOOL	m_bChkUploadFacePic;
	BOOL	m_bChkPicRecordEn;
	int		m_iHour31;
	int		m_iHour32;
	int		m_iHour41;
	int		m_iHour42;
	int		m_iHour51;
	int		m_iHour52;
	int		m_iHour61;
	int		m_iHour62;
	int		m_iHour71;
	int		m_iHour72;
	int		m_iHour81;
	int		m_iHour82;
	int		m_iMin31;
	int		m_iMin32;
	int		m_iMin41;
	int		m_iMin42;
	int		m_iMin51;
	int		m_iMin52;
	int		m_iMin61;
	int		m_iMin62;
	int		m_iMin71;
	int		m_iMin72;
	int		m_iMin81;
	int		m_iMin82;
	BOOL	m_bChkEnablePIP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaFaceDetect)
	public:
	virtual void OnFinalRelease();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaFaceDetect)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnChkDrawPolygon();
	afx_msg void OnTimeOk();
	afx_msg void OnTimeCopy();
	afx_msg void OnBtnSetFacedetect();
	afx_msg void OnCheckSetMiniFilter();
	afx_msg void OnCheckSetMaxFilter();
	afx_msg void OnCheckFilterActive();
	afx_msg void OnSelchangeComboweekday();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;
	int     m_iChannelNum;
                
    NET_DVR_FACEDETECT_RULECFG_V41 m_struFaceDetectRule;

    LONG    m_lPlayHandle;
    
    CRect   m_rcWnd;
    BOOL    m_bCloseIn;
    BOOL    m_bMouseMove;
    BOOL    m_bNeedRedraw;
    DWORD   m_dwPosNum; 
    BOOL    m_bACS; //是否是指纹一体机
    
    DWORD   m_dwAlarmOutNum;

    int     m_iChannelnumber;
    LONG StartPlay();
    BOOL StopPlay();
    BOOL SetFaceDetectRule();
    BOOL GetFaceDetectRule();

    void F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser);
    void F_DrawFrame(HDC hDc);

    BOOL F_TimeTest();

    BOOL PreDrawSizeFilterMsg(MSG* pMsg, CPoint &pt);
    BOOL PreDrawPolygonMsg(MSG* pMsg, CPoint &pt);

    void GetFaceDetectRuleFromWnd(NET_DVR_FACEDETECT_RULECFG_V41& struFaceDetectRule);
    void SetFaceDetectRuleToWnd(NET_DVR_FACEDETECT_RULECFG_V41 const &struFaceDetectRule);
    void GetSchedTimeFromWnd(NET_DVR_SCHEDTIME *pSchedTime);
    void SetSchedTimeToWnd(const NET_DVR_SCHEDTIME *pSchedTime);
    void SetHandleToWnd(NET_DVR_HANDLEEXCEPTION_V30 const &struHandleException);
    void GetHandleFromWnd(NET_DVR_HANDLEEXCEPTION_V30 &struHandleException);
    void SetRelRecordChanToWnd(BYTE const *byRelRecordChan, int ChanNum);
    void GetRelRecordChanFromWnd(BYTE  *byRelRecordChan, int ChanNum);
//     HPR_UINT32          dwSize;
//     HPR_UINT8           byEnable;  
//     BYTE                byRuleName[NAME_LEN];
//     NET_VCA_POLYGON     struVcaPolygon;    // 人脸检测规则区域
//     HPR_UINT8           byPicProType;	//报警时图片处理方式 0-不处理 非0-上传
//     HPR_UINT8           bySensitivity;   // 规则灵敏度
//     HPR_UINT16          wDuration;      // 触发人脸报警时间阈值
//     NET_DVR_JPEGPARA    struPictureParam; 		//图片规格结构
//     NET_VCA_SIZE_FILTER struSizeFilter;         //尺寸过滤器
//     NET_DVR_SCHEDTIME   struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_2];//布防时间
//     NET_DVR_HANDLEEXCEPTION_V30 struHandleType;	  //处理方式 
//     HPR_UINT8           byRelRecordChan[MAX_CHANNUM_V30];			//报警触发的录象通道,为1表示触发该通道

//     BYTE           byEnable;  
//     BYTE                byRuleName[NAME_LEN];
//     NET_VCA_POLYGON     struPolygon;    // 人脸检测规则区域
//     BYTE           byPicProType;	//报警时图片处理方式 0-不处理 非0-上传
//     BYTE           bySensitivity;   // 规则灵敏度
//     WORD          wDuration;      // 触发人脸报警时间阈值
//     NET_DVR_JPEGPARA    struPictureParam; 		//图片规格结构
//     NET_VCA_SIZE_FILTER struSizeFilter;         //尺寸过滤器
//     NET_DVR_SCHEDTIME   struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_2];//布防时间
//     NET_DVR_HANDLEEXCEPTION_V30 struHandleType;	  //处理方式 
//     BYTE           byRelRecordChan[MAX_CHANNUM_V30];			//报警触发的录象通道,为1表示触发该通道

    BOOL m_bAbnormalFace;
    BOOL m_bCallingFace;
    BOOL m_bMultiFace;
    BOOL m_bNormalFace;
    BOOL m_bSunglassesFace;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAFACEDETECT_H__CBACD806_FF76_40EF_90EF_4E9C84848B32__INCLUDED_)
