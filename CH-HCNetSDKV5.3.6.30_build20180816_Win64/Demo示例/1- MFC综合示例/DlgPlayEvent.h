#if !defined(AFX_DLGPLAYEVENT_H__2A224512_DB48_4346_9BE2_C0E7FE3CA2B2__INCLUDED_)
#define AFX_DLGPLAYEVENT_H__2A224512_DB48_4346_9BE2_C0E7FE3CA2B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPlayEvent.h : header file
//
#include "afxwin.h"
#include "time.h"
#include "afxcmn.h"


// CDlgPlayEvent dialog

class CDlgPlayEvent : public CDialog
{
	DECLARE_DYNAMIC(CDlgPlayEvent)

public:
	CDlgPlayEvent(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPlayEvent();

// Dialog Data
	//{{AFX_DATA(CDlgPlayEvent)
	enum { IDD = IDD_DLG_PLAY_EVENT };
	CComboBox	m_comboRuleID;
	CListCtrl	m_listChan;
	CComboBox	m_comboMinorEvent;
	CComboBox m_comboMajorType;
	CTime m_ctDateStart;
	CTime m_ctTimeStart;
	CTime m_ctDateStop;
	CTime m_ctTimeStop;
	CListCtrl m_listRemoteFile;
	CStatic m_staticPlayWnd;
	CSliderCtrl m_sliderVolume;
	int		m_iTime;
	CString	m_strStreamID;
	int		m_iRelatedChannel;
	UINT	m_dwBackupVolume;
	BOOL	m_bDrawFrame;
	BOOL	m_bByValue;
	CString	m_csKeyWord1;
	CString	m_csKeyWord2;
	CString	m_csKeyWord3;
	BOOL	m_bCombinateMode;
	BOOL	m_bCaseSensitive;
    CComboBox m_cmbMajorType;
    CComboBox m_cmbMinorType;
    CString m_csCardNo;
    CString m_csName;
    CString	m_sMacAddr;
	//}}AFX_DATA
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


	//{{AFX_VIRTUAL(CDlgPlayEvent)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPlayEvent)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnRemoteSearchList();
	afx_msg void OnNMDblclkListRemoteFile(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnRemoteFilePlay();
	afx_msg void OnBnClickedBtnRemoteFileStop();
	afx_msg void OnBnClickedBtnRemoteFileStopSave();
	afx_msg void OnBnClickedBtnRemoteFileGotoBeginning();
	afx_msg void OnBnClickedBtnRemoteFileSlow();
	afx_msg void OnBnClickedBtnRemoteFileSnatchPic();
	afx_msg void OnBnClickedBtnRemoteFileStep();
	afx_msg void OnBnClickedBtnRemoteFileSound();
	afx_msg void OnBnClickedBtnRemoteFileFast();
	afx_msg void OnBnClickedBtnRemoteFileSave();	
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnClickListRemoteFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnReleasedcaptureSliderRemoteFileVolume(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListChan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboMajorEvent();
	afx_msg void OnSelchangeComboMinorEvent();
    afx_msg void OnSelchangeComboAcsMajorEvent();
	afx_msg void OnBtnEventFilePlayByIdAndTime();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	
	int m_iDeviceIndex;
	LONG m_lLoginID;
	BOOL CheckInitParam();
	void SetParentWnd(HWND *hhWnd, int iParentNum);
	void OnChkAllChan(BOOL bAll);
	void UpdateChanStatus();
	void UpdateMinorEvent();
	DWORD m_dwCurFileLen;
	LONG m_lDeviceType;
	BOOL m_bDownloading;
	BOOL m_bSearching;
	LONG m_lPlayHandle;
	BOOL m_bSound;
	BOOL m_bPause;
	BOOL m_bGetMaxTime;
	BOOL m_bFullScreen;
	HWND m_hPlayWnd;
	HWND m_hPareTabWnd;
	HWND m_hPareDlgWnd;
	CRect m_rcScreen;
	CRect m_rcWnd;
	CRect m_rcPareDlg;
	CRect m_rcPareTab;
	CRect m_rcParent;
	LONG  m_lDownloadHandle;
	HANDLE m_hFileThread;
	int m_iFileNum;
	int m_iIPAlarmIn;
	int m_iIPChanNum;
    NET_DVR_SEARCH_EVENT_PARAM_V50 m_struEventParamV50;
	int m_iItemSel;//当前选中文件的索引
	int m_iMinorType;
	int m_iChanShowNum;
	int m_iMajorType;
	LONG m_lFileHandle;
	DWORD m_nFileTime;
	DWORD m_nTotalFrames;
	int m_nTotalSecond;
	int m_nTotalMinute;
	int m_nTotalHour;
	LONG m_lStartChan;
	char m_szFileName[200];
	char m_szDownLoadFileName[256];
	BOOL m_bSaveFile;
	BOOL m_bSetFrame;
	int m_iChanNum;
	int m_iChanIndex;

	LONG m_lPort;
	BOOL m_bChangeSpeed;
	NET_DVR_TIME m_struStartTime;
	NET_DVR_TIME m_struStopTime;
	BOOL m_IsQuit;
	
	void ExitPlayBack();
	void InitUI();
	void SetStopState();
	void PlayBack();
	void PlayBackByIDAndTime();
	void SetPlayState();
	void SetPauseState();
	void StopPlay();
	void PlayBackShowNormal();
	void EnableFlashWnd(BOOL bEnable);
	void PlayBackFullScreen();
	BOOL IsInWnd(CPoint point);
	void SetStopStateIDTime();
	void SetPlayStateIDTime();
	void SetPauseStateIDTime();
    int AddMinorAllString(int iStartSel);
    int AddMinorDeviceString(int iStartSel);
    int AddMinorAlarmString(int iStartSel);
    int AddMinorDoorString(int iStartSel);
    int AddMinorCardReaderString(int iStartSel);
    UINT8 charToData(const char ch);
    bool StrToMac(const char * szMac, UINT8 * pMac);
    BOOL m_bQuickSearch;
    CString m_strArchiveLabel;
    CString m_strFileName;
    BOOL m_bSaveByPlay;
    CComboBox m_comboDeviceType;
    CComboBox m_comboFindSubType;
    afx_msg void OnCbnSelchangeComboDeviceType();
    int m_iPlaybackChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPLAYEVENT_H__2A224512_DB48_4346_9BE2_C0E7FE3CA2B2__INCLUDED_)
