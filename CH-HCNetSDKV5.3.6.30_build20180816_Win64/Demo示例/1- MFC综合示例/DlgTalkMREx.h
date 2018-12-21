// DlgTalkMREx.h: interface for the CDlgTalkMREx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGTALKMREX_H__96392362_477E_4B9C_8643_B22855D4FEAF__INCLUDED_)
#define AFX_DLGTALKMREX_H__96392362_477E_4B9C_8643_B22855D4FEAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClientDemo.h"
#include "soundin.h"
#include "wavesound.h"

#define AUDENCSIZE			1280
#define AUDDECSIZE			80

#define G711_AUDENCSIZE		320
#define G711_AUDDECSIZE		160

#define G726_AUDENCSIZE     640
#define G726_AUDDECSIZE		80 

#define BITS_PER_SAMPLE		16
#define CHANNEL				1
#define SAMPLES_PER_SECOND	16000

#define BIT_RATE_16000		16000
#define AUDIOBUF			(80*40L)

#define MAX_SOUND_OUT		20

typedef struct  STRUCT_TALK_MR
{
	BYTE byFlag;
	BYTE byAudioType;
	BYTE byIndex;
	BYTE res;
	STRUCT_TALK_MR()
	{
		byFlag = 0;
		byAudioType = 0;
		byIndex = 0;
		res = 0;
	}
}TALK_MR,*LPTALK_MR;

class CDlgTalkMREx : public CDialog
{
// Construction
public:
	CDlgTalkMREx(CWnd* pParent = NULL);	// standard constructor

	BOOL SendDataToDVR(char *buf, DWORD dwSize);	
	BOOL PutIntoBuf(char *buf, int dwSize, LPTALK_MR lpTalkMR);
	BOOL CopyAudioData(PBYTE lpTemp, DWORD dwReadLength, int nIndex);
	void InputAudioData(LPTALK_MR lpTalkMR);
	void ExitPlayAudio(BYTE *lpeTmp, BYTE *lpPlayBuf, void *pDecoder, void *pG726Dec, void *pG726DecM, BYTE byIndex);
	BOOL CreateWaveFile(char* sFileName);
	int m_iDeviceIndex;
	static UINT PlayAudioThread(LPVOID pParam);
	BOOL m_bWaveDeal;
	void CreateTree(void);


	CImageList m_TreeImage;
	TALK_MR	m_talkMr[MAX_SOUND_OUT];
	int		m_talkIndex[MAX_DEVICES][MAX_AUDIO_V40];
	
	// select/ do not select all the devices 
	void CheckAllDevState(HTREEITEM hRoot, BOOL bCheck, int uFlag);

	void CheckAllAudioState(HTREEITEM hDev, BOOL bCheck, int uFlag);
	void LoadTreeImage(void);
	BOOL StartMR(int iDeviceIndex, int iAudioIndex, BOOL bCheck);

// Dialog Data
	//{{AFX_DATA(CDlgTalkMR)
	enum { IDD = IDD_DLG_TALK_MR };
	CComboBox	m_comAudioEncType;
	CTreeCtrl	m_treeBroadCast;
	CComboBox	m_combVoice;
	CButton	m_btTalk;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTalkMR)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	WAVEFORMATEX m_struWaveFormat;	
	CWaveSound	m_SoundOut[MAX_SOUND_OUT];
	CSoundIn	m_SoundIn;
	BOOL m_bOpenWavOut[MAX_SOUND_OUT];
	BOOL m_bOpenWavIn;

	HMMIO		m_hFile;
	MMCKINFO	m_MMCKInfoData;
	MMCKINFO	m_MMCKInfoParent;
	MMCKINFO	m_MMCKInfoChild;
	
	LPBYTE  m_pRenderBuf[MAX_SOUND_OUT];		//buffer
	int     m_rIndexRV[MAX_SOUND_OUT];			//data that has already been read
	int     m_ReceiveIndexRV[MAX_SOUND_OUT];		//received data for m_pRenderBuf
	int     m_nBufNo[MAX_SOUND_OUT];			
	BOOL	m_bOpenPlayThread[MAX_SOUND_OUT];
	
	void*	m_pEncoder;//g722 encoder
	void*	m_pG726Enc;//g726±àÂë¾ä±ú
	void*	m_pG726EncM;//g726±àÂëÄ£¿é¾ä±ú
	BOOL	m_bReset;//g726Ê×Ö¡ÖØÖÃ
		
	DWORD m_dwBufSize;
	DWORD m_dwBufNum;

	BYTE m_byG711DecBuf[G711_AUDDECSIZE*2];
	BYTE m_byDecBuf[AUDENCSIZE];
	BYTE m_byEncBuf[AUDDECSIZE];
	BYTE m_byEncBuf711[G711_AUDDECSIZE];
	UINT16 m_wG711AudioTemp[AUDENCSIZE/2];
	
	HANDLE m_hExitEvent;
	HANDLE m_hHaveRDataRV[MAX_SOUND_OUT];
	HANDLE m_hPlayHandle[MAX_SOUND_OUT];

	// Generated message map functions
	//{{AFX_MSG(CDlgTalkMR)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtalk();
	afx_msg void OnBtnExit();
	afx_msg void OnClickTreeDev(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void AudioBufDownScale(short const*in, short* out, int inbufLen) const;
};

#endif // !defined(AFX_DLGTALKMREX_H__96392362_477E_4B9C_8643_B22855D4FEAF__INCLUDED_)
