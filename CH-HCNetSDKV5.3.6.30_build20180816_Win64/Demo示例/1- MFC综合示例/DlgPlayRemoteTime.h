#pragma once
#include "time.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "ATLComTime.h"


// CDlgPlayRemoteTime dialog

class CDlgPlayRemoteTime : public CDialog
{
	DECLARE_DYNAMIC(CDlgPlayRemoteTime)

public:
	CDlgPlayRemoteTime(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPlayRemoteTime();

// Dialog Data
protected:
	HICON m_hSoundStartIcon;
	HICON m_hSoundStopIcon;

	HICON m_hPlayEnableIcon;
	HICON m_hPlayDisableIcon;

	HICON m_hPauseEnableIcon;
	HICON m_hPauseDisableIcon;

	HICON m_hStopEnableIcon;
	HICON m_hStopDisableIcon;

	HICON m_hGotoHeadDisableIcon;
	HICON m_hGotoHeadEnableIcon;

	HICON m_hGotoTailEnableIcon;
	HICON m_hGotoTailDisableIcon;

	HICON m_hFastDisableIcon;
	HICON m_hFastEnableIcon;

	HICON m_hSlowDisableIcon;
	HICON m_hSlowEnableIcon;

	HICON m_hStepEnableIcon;
	HICON m_hStepDisableIcon;

	HICON m_hStepBackEnableIcon;
	HICON m_hStepBackDisableIcon;

	HICON m_hCaptureIcon;
public:
	//{{AFX_DATA(CDlgPlayRemoteTime)
	enum { IDD = IDD_DLG_PLAY_REMOTE_TIME };
	CComboBox	m_comboTransType;
	CComboBox	m_comboStreamsType;
	CComboBox	m_cmbDecodeFrameType;
	CComboBox	m_comboVolumeType;
	CSliderCtrl	m_SliderTimeProgress;
	CComboBox	m_comboDiskList;
	CTime m_ctDateStart;
	CTime m_ctTimeStart;
	CTime m_ctDateStop;
	CTime m_ctTimeStop;
	CStatic m_staticWnd;
	CSliderCtrl m_sliderVolume;
	CString	m_csTotalLen;
	CTime	m_ctTimeSet;
	BOOL	m_bBackupPlayer;
	int		m_iDownloadSpeed;
	BOOL	m_bDrawFrame;
	UINT	m_dwFileIndex;
	BOOL	m_bDownLoad;
	UINT	m_dwVolumeNum;
	CTime	m_ctDateSet;
	BOOL	m_bCheck1;
	BOOL	m_bCheck10;
	BOOL	m_bCheck11;
	BOOL	m_bCheck12;
	BOOL	m_bCheck13;
	BOOL	m_bCheck14;
	BOOL	m_bCheck15;
	BOOL	m_bCheck16;
	BOOL	m_bCheck17;
	BOOL	m_bCheck18;
	BOOL	m_bCheck19;
	BOOL	m_bCheck2;
	BOOL	m_bCheck20;
	BOOL	m_bCheck21;
	BOOL	m_bCheck22;
	BOOL	m_bCheck23;
	BOOL	m_bCheck24;
	BOOL	m_bCheck25;
	BOOL	m_bCheck26;
	BOOL	m_bCheck27;
	BOOL	m_bCheck28;
	BOOL	m_bCheck29;
	BOOL	m_bCheck3;
	BOOL	m_bCheck30;
	BOOL	m_bCheck31;
	BOOL	m_bCheck4;
	BOOL	m_bCheck5;
	BOOL	m_bCheck6;
	BOOL	m_bCheck7;
	BOOL	m_bCheck8;
	BOOL	m_bCheck9;
	BOOL	m_bECheck1;
	BOOL	m_bECheck10;
	BOOL	m_bECheck11;
	BOOL	m_bECheck12;
	BOOL	m_bECheck13;
	BOOL	m_bECheck14;
	BOOL	m_bECheck16;
	BOOL	m_bECheck18;
	BOOL	m_bECheck19;
	BOOL	m_bECheck2;
	BOOL	m_bECheck20;
	BOOL	m_bECheck21;
	BOOL	m_bECheck22;
	BOOL	m_bECheck23;
	BOOL	m_bECheck24;
	BOOL	m_bECheck25;
	BOOL	m_bECheck26;
	BOOL	m_bECheck27;
	BOOL	m_bECheck28;
	BOOL	m_bECheck29;
	BOOL	m_bECheck3;
	BOOL	m_bECheck30;
	BOOL	m_bECheck31;
	BOOL	m_bECheck4;
	BOOL	m_bECheck5;
	BOOL	m_bECheck6;
	BOOL	m_bECheck7;
	BOOL	m_bECheck8;
	BOOL	m_bECheck9;
	BOOL	m_bECheck15;
	BOOL	m_bECheck17;
	CString	m_sStreamID;
    BOOL	m_bUserBackUpCfgParam;
    BOOL    m_bEsCallBack;
	//}}AFX_DATA
	BOOL	m_PlayConvert;

	//{{AFX_VIRTUAL(CDlgPlayRemoteTime)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPlayRemoteTime)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnBnClickedBtnTimePlay();
	afx_msg void OnBnClickedBtnTimeStop();
	afx_msg void OnBnClickedBtnTimeSlow();
	afx_msg void OnBnClickedBtnTimeFast();
	afx_msg void OnBnClickedBtnTimePicSnatch();
	afx_msg void OnBnClickedBtnTimeSound();
	afx_msg void OnBnClickedBtnRtDownload();
	afx_msg void OnBnClickedBtnRtPlaySave();	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtnSetTime();
	afx_msg void OnBtnBackup();
	afx_msg void OnSelchangeComboDiskList();
	afx_msg void OnBtnDownloadSpeed();
	afx_msg void OnRadioForward();
	afx_msg void OnRadioReverse();
	afx_msg void OnSelchangeComboVolumeType();
	afx_msg void OnButtonMdrSearch();
	afx_msg void OnBtnSetDecodeframeType();
	afx_msg void OnSelchangeCmbDecodeframeType();
	afx_msg void OnPlayConvert();
    afx_msg void OnGetFigure();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	int m_iChanIndex;
	int m_iDeviceIndex;
	LONG m_lStartChan;
	int m_iChanShowNum;
	LONG m_lLoginID;
	
	HWND m_hPareTabWnd;
	HWND m_hPareDlgWnd;
	LONG m_lPlayHandle;
	BOOL m_bFullScreen;
	CRect m_rcScreen;
	CRect m_rcParent;
	CRect m_rcPareDlg;
	CRect m_rcPareTab;
	CRect m_rcWnd;
	BOOL m_bSound;
	BOOL m_bPause;
	BOOL m_bDown;
	LONG m_lLoadHandle;
	BOOL m_bTimeSave;

    LONG m_lRemoteHandle;
    NET_DVR_FIGURE_INFO m_struFigInfo;
	
    NET_SDK_NPQ_STATE m_struNPQStat;
    int m_dwLinkMode;
    int m_iPort;
    LONG m_iWidth;
    LONG m_iHeight;
	
    NET_DVR_BACKUP_TIME_PARAM m_struBackupTimeParam;
    NET_DVR_DISKABILITY_LIST m_struDiskList;
    HANDLE m_hBackupThread;
    LONG m_lBackupHandle;
    BOOL m_bBackuping;
    void GetDiskList();
    
	void SetParentWnd(HWND *hhWnd, int iParentNum);
	void StopPlay();
	void InitUI();
	void EnableFlashWnd(BOOL bEnable);
	void ShowNormal();
	void ShowFullScreen();
	BOOL IsInWnd(CPoint point);
	void SetPlayState();
	BOOL CheckInitParam();
	void ShowVolumeNumInfo(BOOL bShow);

    LRESULT OnProcessFigure(WPARAM wParam, LPARAM lParam);
    CComboBox m_drawtype;
    COleDateTime m_drawdate;
    COleDateTime m_drawtime;
    afx_msg void OnBnClickedBtnStartDraw();
    afx_msg void OnBnClickedBtnEnddraw();
    BOOL m_bCourseFile;
    BOOL m_bOptimalStreamType;
    CComboBox m_cmbLinkMode;
};
