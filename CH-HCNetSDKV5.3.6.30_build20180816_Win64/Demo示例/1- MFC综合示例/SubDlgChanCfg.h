#pragma once
#include "afxwin.h"


// CSubDlgChanCfg dialog

class CSubDlgChanCfg : public CDialog
{
	DECLARE_DYNAMIC(CSubDlgChanCfg)

public:
	CSubDlgChanCfg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgChanCfg();

// Dialog Data
public:
	//{{AFX_DATA(CSubDlgChanCfg)
	enum { IDD = IDD_SUB_DLG_CHAN_CFG };
	CComboBox	m_comSVC;
	CComboBox	m_cmbVideoFormat;
	CComboBox	m_comboSamplingRate;
	CComboBox	m_comboAudioBitRate;
	CComboBox	m_cmbPoeAdapterType;
	CComboBox	m_comboAudioInType;
	CComboBox	m_comboVideoEncComplexity;
	CComboBox	m_cmbOsdFont;
	CComboBox	m_comboHourType;
	CComboBox	m_comboVideoType;
	CComboBox	m_comboAudioType;
	CComboBox m_comboCompressionType;
	BOOL m_bCheckHideAlarm;
	BOOL m_bCheckVILost;
	BOOL m_bCheckAULost;
	BOOL m_bCheckMotion;
	CComboBox m_comboRecDelay;
	CComboBox m_comboPreRecordTime;
	BOOL m_bCheckHideArea;
	CComboBox m_comboChanNum;
	CString m_csChanName;
	CComboBox m_comboImageQuality;
	CComboBox m_comboStreamType;
	CComboBox m_comboResolution;
	CComboBox m_comboBitRateType;
	CComboBox m_comboFrameRate;
	CComboBox m_comboBitRate;//max bit rate
    CComboBox m_comboAverageBitRate;
	int m_iBitRate;
    int m_iAvBitRate;
	int m_iFrameIInterval;
	CComboBox m_comboFrameBPInterval;
	BOOL m_bCheckRecord;
	BOOL m_bCheckOsd;
	int m_iOsdX;
	int m_iOsdY;
	BOOL m_bChkDispWeek;//display date
	CComboBox m_comboOsdAttrib;
	CComboBox m_comboOsdType;
    CComboBox m_comboAlignment;
	BOOL m_bCheckChanName;
	int m_iChanNameX;
	int m_iChanNameY;
	CComboBox m_comboCopyChan;
	DWORD m_dwDurationTime;
	BOOL	m_bChkRedundancyRec;
	BOOL	m_bChkAudioRec;
	BOOL	m_bEventCompress;
	CString	m_strAccessCameraType;
	int		m_iInterfaceType;
	BOOL	m_bCabacCheck;
	BYTE	m_byVolume;
	BOOL	m_bCallback;
	BOOL	m_bBackup;
	short	m_wLockDuration;
	CComboBox	m_cmbStreamType;
	BOOL	m_bChkEnableSvc;
	BOOL	m_bEnableNoiseFilter;
	BYTE	m_bSVCType;
	BOOL	m_bOSDColor;
	BYTE	m_byOsdColorB;
	BYTE	m_byOsdColorG;
	BYTE	m_byOsdColorR;
	BYTE	m_byStreamSmooth;
	BOOL	m_bChkAudioExtra;
    BOOL    m_bChkSmartCodec;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CSubDlgChanCfg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CSubDlgChanCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboMaxBitRate();
    afx_msg void OnCbnSelchangeComboAvcBitRate();
	afx_msg void OnCbnSelchangeComboCompressionType();
	afx_msg void OnBnClickedBtnCmpOk();
	afx_msg void OnBnClickedBtnRemoteRecordSetup();
	afx_msg void OnBnClickedBtnHideSetup();
	afx_msg void OnBnClickedBtnMotionSetup();
	afx_msg void OnBnClickedBtnHideAlarmSetup();
	afx_msg void OnBnClickedBtnVilostSetup();
	afx_msg void OnBnClickedBtnAUlostSetup();
	afx_msg void OnBnClickedBtnString();
	afx_msg void OnBnClickedBtnChanCopy();
	afx_msg void OnBnClickedBtnChanCfgOk();
	afx_msg void OnBnClickedBtnChanCfgExit();
	afx_msg void OnBnClickedChkRecord();
	afx_msg void OnBnClickedChkHideArea();
	afx_msg void OnBnClickedChkOsd();
	afx_msg void OnBnClickedChkChanNamePos();
	afx_msg void OnCbnSelchangeComboChan();
	afx_msg void OnCbnSelchangeComboCopyChan();
	afx_msg void OnBnClickedChkMotion();
	afx_msg void OnBnClickedChkHideAlarm();
	afx_msg void OnBnClickedChkVilost();
	afx_msg void OnBnClickedChkAUlost();
	afx_msg void OnCbnSelchangeComboFrameRate();
	afx_msg void OnBtnJpegCapture();
	afx_msg void OnBtnDiskQuota();
	afx_msg void OnButtonLimitFrameUpdate();
	afx_msg void OnButtonVideoInEffect();
	afx_msg void OnButtonConfigCameraType();
	afx_msg void OnButtonInquiryTimeSpan();
	afx_msg void OnButtonUpdateIndex();
	afx_msg void OnBtnVideoOutput();
	afx_msg void OnBtnWdEnable();
	afx_msg void OnBtnVeidopackage();
	afx_msg void OnBtnVediopackage();
	afx_msg void OnBtnDetectFace();
	afx_msg void OnBtnDeviceLanguageEncode();
	afx_msg void OnChkOSDColor();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	void AddResolution();
	BOOL CheckInitParam();
	void CurCfgUpdate(int iChanIndex);
	BOOL CfgSetup();
	void EnableOsd(BOOL bEnable);
	void EnableChanname(BOOL bEnable);
	WORD FrameIIntervalMap(DWORD nSelFrameRate);
	void EnableEventCtrl(BOOL bEnable);
	void SaveLastCompressTypePara(); 
	void DoUpdateFrame();
	BOOL GetCurChanInfo(int iChanIndex);
    void AddStreamType();
	int		m_iChanCount;//preview channel number
	LONG	m_lLoginID;
	LONG	m_lStartChannel;//start channel number(usually 1)
	
	int		m_iCurChanIndex;  //channel index in the tree of main windows.

    int     m_iCurGroupNo; //temp group No. of tree

	int		m_iCopyChanIndex;
	int		m_iChanShowNum;//display channel number (usually start from 1)
	DWORD	m_dwAlarmOutNum;
	BOOL *m_pbSetChannelPara;
	BOOL *m_pbGetChannelPara;

	NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND m_struMSCond[11];
	NET_DVR_MULTI_STREAM_COMPRESSIONCFG m_struMSCompressionCfg[MAX_CHANNUM_V40][5];

//	NET_DVR_COMPRESSIONCFG_V30 m_struCompressionCfg[MAX_CHANNUM_V30*2];
// 	NET_DVR_COMPRESSIONCFG m_compressionNew[MAX_CHANNUM_V30];
// 	NET_DVR_COMPRESSIONCFG_EX m_struCompressionCfg[MAX_CHANNUM_V30];
	NET_DVR_RECORD_V30	*m_pStruRemoteRecCfg;
	NET_DVR_RECORD_V40	*m_pStruRemoteRecCfgV40;
	//	NET_DVR_PICCFG_V30	m_struPicCfg[MAX_CHANNUM_V30*2];
	NET_DVR_PICCFG_V40 *m_pStruPicCfgV40;
	NET_DVR_AUDIO_INPUT_PARAM *m_pStruAudioIn;
	NET_DVR_POE_CHANNEL_ADD_MODE *m_pStruPOEAdapterType;

	NET_DVR_STREAM_CABAC *m_pStruCabac;

	BOOL m_bRemoteRecord[MAX_CHANNUM_V40];
	int m_iDeviceIndex;
	int m_iCompressionTypeSel;//selected compression parameter type

    NET_DVR_COMPRESSIONCFG_ABILITY *m_pCompresscfgAbility;
    BOOL GetCompressCfgAbility(DWORD dwIPChanIndex);
	void UpdateCompressionInfo();
	void CheckRebootParam(BYTE *byCurVal, int iModVal, BOOL bJudge);
    void GetResolutionAbility();
    void GetSubResolutionAbility();
    void GetEventResolutionAbility();
	void GetThirdResolutionAbility();
	void GetTranscodeResolutionAbility();
    void GetBitrateTypeAbility();
    void GetBitrateAbility();
    void GetFrameAbility();
    void GetStreamTypeAbility();

    void SetResolutionCurSel(DWORD dwData);
    void SetBitrateCurSel(DWORD dwData);
    void SetBitrateTypeCurSel(DWORD dwData);
    BOOL SetFrameCurSel(DWORD dwData);
    void SetStreamTypeCurSel(DWORD dwData);
    void SetAvBitrateCurSel(DWORD dwData);
    
    DWORD m_dwBoundary;
    BOOL m_bDepthMapEnable;
    BOOL m_bKeyEnable;
    BOOL m_bSelfBackColor;
    BYTE m_bySelfRed;
    BYTE m_bySelfGreen;
    BYTE m_bySelfBlue;
    BOOL m_bYStreamEnable;
};
