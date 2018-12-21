#pragma once
#include "afxwin.h"
#include "time.h"
#include "afxcmn.h"
#include"afxmt.h"
#include <deque>
#include "ATLComTime.h"
using std::deque;
// CDlgPlayRemoteFile dialog
#define MAX_DOWNLOAD_THREAN_NUM  5

typedef struct _OutResource
{
    LONG    lDLHandle;       // 下载句柄
    HANDLE  hThread;         // 线程句柄
    CString csDLFileN;       // 下载文件
    CString csSaveFileN;     // 保存文件
}OutResource;

//一次多个线程下载管理， 最多MAX_DOWNLOAD_THREAN_NUM个
class DownloadThread
{
private:
    const int m_iWaitTime ;                                  //GetResource 获取失败后等待时间 10ms
    const int m_iTryCount ;                                    //GetResource 尝试获取次数
private:
    deque<OutResource> m_ResourceQue;                             // 输出资源, 需要跟外界互斥
    CMutex  m_ResourceOpLock;                                     // 资源队列操作锁 
    BYTE    m_byResCount;                                         // 添加下载资源计数 只增不减 ， 一次最多MAX_DOWNLOAD_THREAN_NUM
    BYTE    m_startDlIndex;                                       // 开始下载线程下标
protected:
    BOOL    _Del(BYTE index);                                    //删除下标的线程和句柄
    BOOL    _CloseHandle(BYTE index);                            //关闭相关句柄
public:
    DownloadThread();
    BOOL    Init();                                              //初始化下载
    BOOL    AddResource(const OutResource &struRes);             //添加外部资源
    BOOL    Del(HANDLE hThread = NULL );                         //停止下载线程   默认停止所有
    BYTE    CountPos();                                          //计算总的进度
    BOOL    GetResource(OutResource &struRes);                           //弹出栈顶第一个资源  
    BOOL    isFull(){ return (m_ResourceQue.size()>=MAX_DOWNLOAD_THREAN_NUM)?TRUE:FALSE;  }                                            
                                                                   //是否到达一次下载最大数
}; 

class CDlgPlayRemoteFile : public CDialog
{
	DECLARE_DYNAMIC(CDlgPlayRemoteFile)

public:
	CDlgPlayRemoteFile(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPlayRemoteFile();

// Dialog Data
	
public:
	//{{AFX_DATA(CDlgPlayRemoteFile)
	enum { IDD = IDD_DLG_PLAY_REMOTE_FILE };
    CComboBox	m_comboUseCardType;
	CComboBox	m_comboATMTradeType;
	CComboBox	m_cmbFindType;
	CComboBox	m_comboStreamtype;
	CComboBox	m_comboDiskList;
	CComboBox	m_comboAttr;
	CComboBox	m_comboTransType;
	CString m_csCardNum;
	BOOL m_bChkCardNum;
	CComboBox m_comboFileType;
	CTime m_ctDateStart;
	CTime m_ctTimeStart;
	CTime m_ctDateStop;
	CTime m_ctTimeStop;
	CListCtrl m_listRemoteFile;
	CStatic m_staticPlayWnd;
	CSliderCtrl m_sliderPlayProgress;
	CSliderCtrl m_sliderVolume;
	CProgressCtrl m_progressDownload;
	CString m_csDownloadStat;
	int		m_iOffset;
	int		m_iSpeed;
	CString	m_csFileLen;
	CString	m_csName;
	CTime	m_ctDateSet;
	CTime	m_ctTimeSet;
	BOOL	m_bBackupPlayer;
	BOOL	m_bContinue;
	CString	m_csAddLabelName;
	BOOL	m_bDrawFrame;
	UINT	m_dwVolumeNum;
	BOOL	m_bQuickSearch;
	BYTE	m_byGuid1;
	BYTE	m_byGuid2;
	BYTE	m_byGuid3;
	BYTE	m_byGuid4;
	BYTE	m_byGuid5;
	BYTE	m_byGuid6;
	BYTE	m_byGuid7;
	BYTE	m_byGuid8;
	BYTE	m_byGuid9;
	BYTE	m_byGuid10;
	BYTE	m_byGuid11;
	BYTE	m_byGuid12;
	BYTE	m_byGuid13;
	BYTE	m_byGuid14;
	BYTE	m_byGuid15;
	BYTE	m_byGuid16;
	CString	m_csGuid;
    INT	m_iMoney;
	BOOL	m_bAudioFile;
    BOOL   m_bEsCallBack;
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


	//{{AFX_VIRTUAL(CDlgPlayRemoteFile)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPlayRemoteFile)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnRemoteSearchList();
	afx_msg void OnBnClickedBtnFileDownload();
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
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnChkCardNum();
	afx_msg void OnClickListRemoteFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnLock();
	afx_msg void OnBtnTimeLock();
	afx_msg void OnBtnTimeUnlock();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCustomdrawSliderRemoteFileProgress(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderRemoteFileProgress(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderRemoteFileVolume(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSetTime();
	afx_msg void OnBtnBackup();
	afx_msg void OnSelchangeComboDiskList();
	afx_msg void OnBtnInsertRecordLabel();
	afx_msg void OnRadioForward();
	afx_msg void OnRadioReverse();
	afx_msg void OnSelchangeComboFindType();
	afx_msg void OnButMutilthreadDownload();
    afx_msg void OnSelchangeCmbUsecardType();
    afx_msg void OnBtnShowOsdinfo();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	
	int m_iDeviceIndex;
	LONG m_lLoginID;
	BOOL CheckInitParam();
	void SetParentWnd(HWND *hhWnd, int iParentNum);
	DWORD m_dwCurFileLen;
	LONG m_lDeviceType;
	BOOL m_bDownloading;
	BOOL m_bSearching;
	int m_nPlayHandle;
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

	NET_DVR_FILECOND_V40 m_struFileCond;
    NET_DVR_FILECOND_V50 m_struFileCondV50;
	int m_iItemSel;//selected file index
	int m_iFileAttr;
	int m_iChanShowNum;
	int m_iFileType;
	LONG m_lFileHandle;
	DWORD m_nFileTime;
	DWORD m_nTotalFrames;
	int m_nTotalSecond;
	int m_nTotalMinute;
	int m_nTotalHour;
	LONG m_lStartChan;
	char m_szFileName[200];
	char m_szCurFileName[200];
	char m_szDownLoadFileName[256];
	BOOL m_bSaveFile;
	BOOL m_bSetFrame;
	int m_iChanNum;
	int m_iChanIndex;

	LONG m_lPort;
	BOOL m_bChangeSpeed;
	BOOL m_bQuit;
    //char *m_pBufferTemp;
    HANDLE m_hWriteHandle;

    NET_DVR_BACKUP_NAME_PARAM m_struBackupParam;
    NET_DVR_FINDDATA_V50 m_struFindData;
	NET_DVR_DISKABILITY_LIST m_struDiskList;
    HANDLE m_hBackupThread;
    LONG m_lBackupHandle;
    BOOL m_bBackuping;
	void ExitPlayBack();
	void InitUI();
	void SetStopState();
	void PlayBack();
	void SetPlayState();
	void SetPauseState();
	void StopPlay();
	void PlayBackShowNormal();
	void EnableFlashWnd(BOOL bEnable);
	void PlayBackFullScreen();
	BOOL IsInWnd(CPoint point);

    void GetDiskList();
    DWORD ProcessFileSize(CString csFileSize);
    BOOL InsertRecordLabel(NET_DVR_RECORD_LABEL* lpRecordLabel, NET_DVR_LABEL_IDENTIFY *lpLableIdentify);

protected: 
    static UINT SingleDownloadThread(LPVOID pParam); 

private:
    CMutex  m_DownloadLock;                                        //下载前期工作的锁  
  
    HANDLE  m_hMDThread[MAX_DOWNLOAD_THREAN_NUM];                  //多线程
    LONG    m_lMDHandle[MAX_DOWNLOAD_THREAN_NUM];                  //下载句柄, 跟线程对应
    BYTE    m_byCountMutilDownload; 
    int     m_iSelListItem; 
    CString m_csStartTime; 
    CString m_csStopTime; 
    char  m_csSaveFile[128]; 
    DownloadThread  m_MutilDowload;                                //多路下载 
public:
    CComboBox m_drawtype;
    COleDateTime m_drawdate;
    COleDateTime m_drawtime;
    afx_msg void OnBnClickedBtnStartDraw();
    afx_msg void OnBnClickedBtnEnddraw();
    BOOL m_bEnableUTC;
    afx_msg void OnBnClickedBtnMedical();
    BOOL m_bDownload;
};
