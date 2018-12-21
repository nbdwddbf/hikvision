#if !defined(AFX_DLGAUDIOCHANCFG_H__7B6BF9AE_5C4C_4FE7_B55F_B3CD4531D05F__INCLUDED_)
#define AFX_DLGAUDIOCHANCFG_H__7B6BF9AE_5C4C_4FE7_B55F_B3CD4531D05F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAudioChanCfg.h : header file
//
#include "DlgUpStreamCfg.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgAudioChanCfg dialog


class CDlgAudioChanCfg : public CDialog
{
// Construction
public:
	CDlgAudioChanCfg(CWnd* pParent = NULL);   // standard constructor
    ~CDlgAudioChanCfg(); 
// Dialog Data
	//{{AFX_DATA(CDlgAudioChanCfg)
	enum { IDD = IDD_DLG_VM_AUDIOCHANCFG };
	CComboBox	m_cmbAudioCfgSwitch;
	CComboBox	m_cmbSubBoardNo;
	CComboBox	m_cmbChanNo;
	DWORD	m_dwDeviceNO;
	CString	m_csChanName;
	BOOL	m_BEanble;
	DWORD	m_dwSubWinNo;
	DWORD	m_dwWallNo;
	DWORD	m_dwWinNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAudioChanCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAudioChanCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSubboardNo();
	afx_msg void OnButSave();
	afx_msg void OnButSet();
	afx_msg void OnButGetall();
	afx_msg void OnButStreamcfgSet();
	afx_msg void OnSelchangeAudiocfgSwitch();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

protected:
    DWORD m_dwAudioChanNum; 
    DWORD m_dwAudioStartNo; 
    DWORD m_dwTotalAudioChan; 
    NET_DVR_ALLSUBSYSTEMINFO_V40 m_struAllSystemInfo; 

    LPNET_DVR_AUDIO_CHAN_CFG m_lpChanCfgArray;
    LPNET_DVR_AUDIO_CHAN_INFO m_lpChanInfoArray; 
    DWORD  m_dwRecord[MAX_ID_COUNT]; 
	DWORD  m_dwAudioChan[MAX_ID_COUNT]; 
    DWORD  m_dwStatus[MAX_ID_COUNT]; 
    CDlgUpStreamCfg m_DlgUpStreamCfg; 

    BOOL GetAudioChanNum(); 
    LPNET_DVR_AUDIO_CHAN_CFG GetChanCfg(); 
    LPNET_DVR_AUDIO_CHAN_CFG GetChanCfgSend(BOOL BAll = FALSE); 
    DWORD GetChangeItemNum(); 
    LPNET_DVR_AUDIO_CHAN_INFO GetChanInfo(); 
    LPNET_DVR_AUDIO_CHAN_INFO GetInitChanInfo(); //获取某个子板的所有音频号 
    LPNET_DVR_AUDIO_CHAN_INFO GetInitChanInfo(DWORD dwChanNo);   //获取某个音频通道号
    LPNET_DVR_AUDIO_CHAN_INFO GetInitChanInfo(bool BMod);  //获取修改过的音频通道号
    BOOL UpdateCfg(); 
	int  GetRecordIndex(DWORD dwSubIndex, DWORD dwChan); 
public:
    LONG m_lServerID;
    int  m_iDeviceIndex;
//     int  m_iChannelnumber;
// 	LONG m_lStartChan;

    BOOL GetAll(); 
    BOOL Save(); 
    BOOL Refresh(); 
    BOOL Set(); 
	afx_msg void OnSelChannelChange();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAUDIOCHANCFG_H__7B6BF9AE_5C4C_4FE7_B55F_B3CD4531D05F__INCLUDED_)

