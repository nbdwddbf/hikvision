#pragma once

#define SAVE_FILE_STANDARD

typedef int (_stdcall *ChannelOpenProc)(long, HANDLE*);
typedef int (_stdcall *SetStreamOpenModeProc)(HANDLE, ULONG);
typedef int (_stdcall *OpenStreamProc)(HANDLE, PBYTE, DWORD);
typedef int (_stdcall *SetDisplayParaProc)(HANDLE, DISPLAY_PARA*);
typedef int (_stdcall *PlayProc)(HANDLE);
typedef int (_stdcall *InputDataProc)(HANDLE, PBYTE, DWORD);
typedef int (_stdcall *InputVideoData)(HANDLE, PBYTE, DWORD);
typedef int (_stdcall *InputVideoDataProc)(HANDLE, PBYTE, DWORD);
typedef int (_stdcall *StopProc)(HANDLE);
typedef int (_stdcall *CloseStreamProc)(HANDLE);
typedef int (_stdcall *SetAudioPreviewProc)(HANDLE, BOOL);
typedef int (_stdcall *SetVolumeProc)(HANDLE, ULONG);
typedef int (_stdcall *GetPictureSizeProc)(HANDLE, ULONG*, ULONG*);
typedef int (_stdcall *GetYV12ImageProc)(HANDLE, PBYTE, ULONG);
typedef int (_stdcall *ConvertToBmpFileProc)(BYTE* ,ULONG, ULONG, ULONG, char*, ULONG);
typedef int (_stdcall *SetDecoderAudioOutputProc)(UINT, BOOL, UINT);

#define GET_NPQ_STATE_TIMER  6666

class CDlgOutput : public CDialog
{
	DECLARE_DYNAMIC(CDlgOutput)

public:
	CDlgOutput(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgOutput();
	void CapturePicture();
	char m_szFileName[256];
	BOOL m_bCapture;
	//preview window index
	int m_iSubWndIndex;
	
	//window
	HWND m_hWnd;
	// save previewing channel info
	CHANNEL_INFO m_struChanInfo;
	// save previewing node
	HTREEITEM m_hChanItem;
	// delay buffer number
	int m_iNetDelayBufNum;
	// Open sound on preview
	BOOL m_bPlaySound;
    BOOL m_bShowOSD;
    LONG m_lDeviceType;
	// preview handle
	LONG m_lPlayHandle;
	// preview window position
	CRect m_OutputRect;
	
	BOOL m_bLocalManualRec;//local manual record

    LONG m_iWidth;
    LONG m_iHeight;

    NET_SDK_NPQ_STATE m_struNPQStat;
    UINT_PTR m_pNpqTimer;

    DWORD m_dwLinkMode;
	
	CString m_csDeviceIP;
	//cal when arrange the out put windows
	int m_iXPrecision;
	int m_iYPrecision;
	double m_xScale;
	double m_yScale;
	BOOL m_bPauseDecoder;
	HANDLE m_hCardHandle;
	BOOL m_bRestart;
	void Restart();
	NET_DVR_DISPLAY_PARA m_struCardPlayParam;//m_struCardPlayPara
	LONG m_lPort;// play port
	void StopLocalRecord();
	void StartLocalRecord();
	void ChangeRecordFileName();
	void ChangeCurWinCfg();
	time_t m_lChangeFileNameTime;
	
	//draw the yellow line on window edge
    void DrawSensorValuText(HDC hDc, CString csDeciceIP, LONG lChannel);
	void DrawOutputBorder(void);
	void CancelSelectZoom();

	// start preview
	LONG StartPlayInsideDecode(PCHANNEL_INFO pChanInfo,HTREEITEM hChanItem);

	LONG StartPlay(PCHANNEL_INFO pChanInfo,HTREEITEM hChanItem);
	// stop preview
	BOOL StopPlay(void);
	void AddLog(int iLogType, const char* format, ...);
	void StopSound();
	void StartSound(WORD wVolumeValue);
	FILE *m_fp;
	char m_sHeader[40];
	BOOL m_bSaveHead;
	BOOL ZeroStopPlay(void);
	LONG ZeroStartPlay(PCHANNEL_INFO pChanInfo, HTREEITEM hChanItem);
    LONG ZeroStartPlayInsideDecode(PCHANNEL_INFO pChanInfo, HTREEITEM hChanItem);

    BOOL MirrorStopPlay(void);
    LONG MirrorStartPlay(PCHANNEL_INFO pChanInfo, HTREEITEM hChanItem);
    LONG MirrorStartPlayInsideDecode(PCHANNEL_INFO pChanInfo, HTREEITEM hChanItem);

public:
    LONG    m_lChannel;     // Í¨µÀºÅ

public:
	//{{AFX_DATA(CDlgOutput)
	enum { IDD = IDD_DLG_OUTPUT };
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CDlgOutput)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgOutput)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnMenuNextPage();
	afx_msg void OnMenuFrontPage();
	afx_msg void  OnMenuPauseCycle();
	afx_msg void OnMenuSound();
	afx_msg void  OnMenuMultiScreenLarge();
	afx_msg void OnMenuStopPlay();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMenuZeroFrontPage();
	afx_msg void OnMenuZeroNextPage();
    afx_msg void OnMenuShowOSD();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
public:
    NET_DVR_ZERO_ZOOMCFG m_struZeroZoomCfg;

public:
    CString GetSensorAlarmTypeStr(DWORD dwAlarmTye);
    CString GetSensorType(DWORD dwSensorType);
};
