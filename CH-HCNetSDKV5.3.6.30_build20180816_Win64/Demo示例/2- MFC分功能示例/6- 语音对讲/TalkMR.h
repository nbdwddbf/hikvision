#if !defined(AFX_TALKMR_H__55F46AA7_76CA_4425_817A_50EAA89521F0__INCLUDED_)
#define AFX_TALKMR_H__55F46AA7_76CA_4425_817A_50EAA89521F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TalkMR.h : header file
//
#include <mmsystem.h>
#include "GeneralDef.h"
#include "SoundIn.h"
#include "WaveSound.h"
#include <vector>

using std::vector;
/////////////////////////////////////////////////////////////////////////////
// CTalkMR dialog

class CTalkMR : public CDialog
{
// Construction
public:
	void StopTalkMR();
	BOOL StartTalkMR();
    BOOL PutIntoBuf(char *lpTemp, int Bytes);
	static UINT PlayAudioThread(LPVOID pParam);
	void InputAudioData();
	BOOL CopyAudioData(PBYTE lpTemp, DWORD dwReadLength);
	CTalkMR(CWnd* pParent = NULL);   // standard constructor
public:
	BOOL SendDataToDVR(char *buf, DWORD dwSize);
	void CloseWave();
	void OpenWave();
	HTREEITEM m_ItemRoot;
	void CreateChannelTree(int iNum,BYTE *ChanStatus);
//	LONG m_lVoiceHandle;
	BOOL m_bIsTalkMR;
	WAVEFORMATEX m_struWaveFormat;	
	CWaveSound	m_SoundOut;
	CSoundIn	m_SoundIn;
	BOOL m_bOpenWavOut;
	BOOL m_bOpenWavIn;
	BOOL m_bWaveDeal;
	HMMIO		m_hFile;
	MMCKINFO	m_MMCKInfoData;
	MMCKINFO	m_MMCKInfoParent;
	MMCKINFO	m_MMCKInfoChild;
	
	LPBYTE  m_pRenderBuf;		//缓冲区
	int     m_rIndexRV;			//已经读取的数据
	int     m_ReceiveIndexRV;		//已接收的数据,针对缓冲区m_pRenderBuf而言
	int     m_nBufNo;			//读数据的阀值。第一次和后面任意次不同
	BOOL	m_bOpenPlayThread;
	
	void* m_pDecoder;//g722 decoder
	void* m_pEncoder;//g722 encoder
	
	DWORD m_dwBufSize;
	DWORD m_dwBufNum;
	
	BYTE m_byDecBuf[AUDENCSIZE];
	BYTE m_byEncBuf[AUDDECSIZE];
	
	HANDLE m_hExitEvent;
	HANDLE m_hHaveRDataRV;

	vector<VOICEMR_INFO> m_vecVoiceMR;


// Dialog Data
	//{{AFX_DATA(CTalkMR)
	enum { IDD = IDD_DIALOG_TALK_MR };
	CTreeCtrl	m_ctrlTreeChan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTalkMR)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTalkMR)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonTalkMr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TALKMR_H__55F46AA7_76CA_4425_817A_50EAA89521F0__INCLUDED_)
