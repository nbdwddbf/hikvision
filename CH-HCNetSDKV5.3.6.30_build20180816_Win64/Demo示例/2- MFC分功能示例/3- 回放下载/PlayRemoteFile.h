#if !defined(AFX_PLAYREMOTEFILE_H__B24D222A_0E61_41C9_B462_5EF1F4F76443__INCLUDED_)
#define AFX_PLAYREMOTEFILE_H__B24D222A_0E61_41C9_B462_5EF1F4F76443__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayRemoteFile.h : header file
//
#include "GeneralDef.h"

#define PLAY_STOP   0
#define PLAY_NORMAL 1
#define PLAY_PAUSE  2
#define PLAY_FAST   3
#define PLAY_SLOW   4

/////////////////////////////////////////////////////////////////////////////
// CPlayRemoteFile dialog

class CPlayRemoteFile : public CPropertyPage
{
	DECLARE_DYNCREATE(CPlayRemoteFile)

// Construction
public:
	void SetPlayState(int iState);
	void InitUI();
	BOOL PausePlayBack(BOOL bPlayOrPause);
	BOOL StopPlayback();
	BOOL StartPlayback();
	void InsertFileList();
	CPlayRemoteFile();
	~CPlayRemoteFile();

	LONG m_hPlayHandle;
	BOOL m_IsDownloading;
	LONG m_lDownloadHandle;
	BOOL m_IsPlaying;
	BOOL m_IsPause;
	BOOL m_bChangeSpeed;
	BOOL m_bPlayStep;
    BOOL m_bSound;
	BOOL m_bRecord;
	DWORD m_CurPlayPos;  //当前播放进度
	DWORD m_TotalFrames;  //总帧数
	DWORD m_CurFrames;    //当前播放的帧数
	DWORD m_TotalTime;    //总时间
	DWORD m_CurTime;      //当前播放时间
	NET_DVR_FILECOND   m_FileCond;   //文件查找结构体
	int m_RecType;        //录像类型，0xff－全部；0－定时录像；1－移动侦测；2－报警触发；3-报警|移动侦测；4－报警&移动侦测；5－命令触发；6－手动录像
	int m_FileProperty;   //文件属性，0－正常文件；1－锁定文件；0xff表示所有文件
	CString m_csCurFile;  //当前播放文件名
// Dialog Data
	//{{AFX_DATA(CPlayRemoteFile)
	enum { IDD = IDD_PAGE_REMOTE };
	CSliderCtrl	m_sliderVolume;
	CSliderCtrl	m_sliderPlay;
	CProgressCtrl	m_progressDownload;
	CStatic	m_staticPlay;
	CListCtrl	m_ctrlFileList;
	CDateTimeCtrl	m_TimeStart;
	CDateTimeCtrl	m_TimeEnd;
	CDateTimeCtrl	m_DateEnd;
	CDateTimeCtrl	m_DateStart;
	CComboBox	m_coRecType;
	CComboBox	m_coFileProperty;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPlayRemoteFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
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
	// Generated message map functions
	//{{AFX_MSG(CPlayRemoteFile)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSearch();
	afx_msg void OnDblclkFileList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonDownload();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnButtonBack();
	afx_msg void OnButtonStep();
	afx_msg void OnSelchangeComboType();
	afx_msg void OnSelchangeComboFileProperty();
	afx_msg void OnReleasedcaptureSliderPlay(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonRemoteSlow();
	afx_msg void OnButtonRemoteFast();
	afx_msg void OnButtonRemotePic();
	afx_msg void OnButtonRemoteSound();
	afx_msg void OnReleasedcaptureSliderVolume(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonRemoteStopSave();
	afx_msg void OnButtonRemoteSave();
	afx_msg void OnClickFileList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonLockUnlock();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYREMOTEFILE_H__B24D222A_0E61_41C9_B462_5EF1F4F76443__INCLUDED_)
