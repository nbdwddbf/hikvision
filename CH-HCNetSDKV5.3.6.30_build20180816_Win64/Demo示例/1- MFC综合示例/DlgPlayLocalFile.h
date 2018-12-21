#pragma once
#include "afxwin.h"
#include "time.h"
#include "afxcmn.h"


// CDlgPlayLocalFile dialog

class CDlgPlayLocalFile : public CDialog
{
	DECLARE_DYNAMIC(CDlgPlayLocalFile)

public:
	CDlgPlayLocalFile(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPlayLocalFile();

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
	//{{AFX_DATA(CDlgPlayLocalFile)
	enum { IDD = IDD_DLG_PLAY_LOCAL_FILE };
	CComboBox m_comboFileType;
	CTime m_ctDateStart;
	CTime m_ctTimeStart;
	CTime m_ctDateStop;
	CTime m_ctTimeStop;
	CListCtrl m_listFile;
	CStatic m_staticPlayWnd;	
	CSliderCtrl m_sliderPlayProgress;
	CSliderCtrl m_sliderVolume;
	BOOL	m_bChkAll;	
	//}}AFX_DATA

	
	//{{AFX_VIRTUAL(CDlgPlayLocalFile)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPlayLocalFile)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSearchLocalList();
	afx_msg void OnBnClickedBtnDeleteLocalFile();
	afx_msg void OnBnClickedBtnDeleteAllLocalFile();
	afx_msg void OnBnClickedBtnLocalPlay();
	afx_msg void OnBnClickedBtnLocalStop();
	afx_msg void OnBnClickedBtnLocalSlow();
	afx_msg void OnBnClickedBtnLocalFast();
	afx_msg void OnBnClickedBtnLocalPicSnatch();
	afx_msg void OnBnClickedBtnLocalStepBack();
	afx_msg void OnBnClickedBtnLocalStepForward();
	afx_msg void OnBnClickedBtnLocalSound();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnReleasedcaptureSliderLocalPlayProgress(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderLocalVolume(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBtnUploadRecordfile();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:

	int m_iChanIndex;
	int m_iDeviceIndex;
	int m_iCurPlayChan;
	LONG m_lLoginID;
	LONG m_lStartChan;
	int m_iChanCount;//preview channel number of this device
	
	HWND m_hPareTabWnd;
	HWND m_hPareDlgWnd;
	BOOL m_bPlay;
	BOOL m_bPause;
	BOOL m_bSound;
	DWORD m_iTotalSeconds;
	BOOL m_bStep;
	BOOL m_bFileRefCreated;
	HWND m_hPlayWnd;
	BOOL m_bFullScreen;
	CRect m_rcScreen;
	CRect m_rcWnd;
	CRect m_rcPareDlg;
	CRect m_rcPareTab;
	CRect m_rcParent;
	int m_iFileIndex;//file index in the whole searching list
	CString m_csDeviceIP;
	
	void InitUI();
	void SetParentWnd(HWND *hhWnd, int iParentNum);
	void StopPlayBack();
	BOOL CheckDate(CTime tFrom, CTime tTo);
	int SearchLocalFile(int iFileType,int iChanShowIndex, CTime tFrom, CTime tTo);
	int ShowDownloadFile(int iChanShowIndex, CTime tFrom, CTime tTo);
	void SetStopState();
	void UpdateStepBackUI(BOOL bEnable);
	void SetPlayState();
	void Pause();
	void PlayBack();
	void SetPauseState();
	void Sound(BOOL bSound);
	void SetPlaySoundState();
	void SetStopSoundState();
	void ShowPlayBackState();
	BOOL IsInWnd(CPoint point);
	void PlayBackFullScreen();
	void PlayBackShowNormal();
	void EnableFlashWnd(BOOL bEnable);
	BOOL CheckInitParam();
};
