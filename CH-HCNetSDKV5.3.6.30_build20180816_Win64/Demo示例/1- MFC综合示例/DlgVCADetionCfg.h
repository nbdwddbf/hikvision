#if !defined(AFX_DLGVCADETIONCFG_H__B0E8E491_F954_4942_808C_B64CD67A01C3__INCLUDED_)
#define AFX_DLGVCADETIONCFG_H__B0E8E491_F954_4942_808C_B64CD67A01C3__INCLUDED_

#include <vector>

using namespace std;
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVCADetionCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgVCADetionCfg dialog

class DlgVCADetionCfg : public CDialog
{
// Construction
public:
	DlgVCADetionCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgVCADetionCfg)
	enum { IDD = IDD_DLG_VCA_DETION_CFG };
	CTreeCtrl	m_treeChan;
	CTreeCtrl	m_treeAlarmOut;
	CComboBox	m_comCount;
	CComboBox	m_comMaxDay;
	CComboBox	m_comChanNo;
	UINT	m_ChannelNo;
	BYTE	m_CuriseNo;
	BOOL	m_bEnable;
	BOOL	m_bEnableCurise;
	BOOL	m_bEnablePreset;
	BOOL	m_bEnablePTZTrack;
	UINT	m_GroupNo;
	UINT	m_MaxRelAlarmOutChanNum;
	UINT	m_MaxRelRecordChanNum;
	BYTE	m_PTZTrack;
	UINT	m_RelAlarmOutChanNum;
	UINT	m_RelRecordChanNum;
	UINT	m_Preset;
	BOOL	m_bMintorAlarm;
	BOOL	m_bNoResponse;
	BOOL	m_bUpCenter;
	BOOL	m_bVoiceAlarm;
	BOOL	m_bWirelessAlarm;
	BOOL	m_bLinkageMap;
	BOOL	m_bJpegCapture;
	BOOL	m_bAlarmOut;
	BOOL	m_bCaptureUploadFTP;
	UINT	m_iHour11;
	UINT	m_iHour12;
	UINT	m_iHour21;
	UINT	m_iHour22;
	UINT	m_iHour31;
	UINT	m_iHour32;
	UINT	m_iHour41;
	UINT	m_iHour42;
	UINT	m_iHour51;
	UINT	m_iHour52;
	UINT	m_iHour61;
	UINT	m_iHour62;
	UINT	m_iHour71;
	UINT	m_iHour72;
	UINT	m_iHour81;
	UINT	m_iHour82;
	UINT	m_iMin11;
	UINT	m_iMin12;
	UINT	m_iMin21;
	UINT	m_iMin22;
	UINT	m_iMin31;
	UINT	m_iMin32;
	UINT	m_iMin41;
	UINT	m_iMin42;
	UINT	m_iMin51;
	UINT	m_iMin52;
	UINT	m_iMin61;
	UINT	m_iMin62;
	UINT	m_iMin71;
	UINT	m_iMin72;
	UINT	m_iMin81;
	UINT	m_iMin82;
	UINT	m_Num;
	//}}AFX_DATA
	vector<NET_DVR_VCA_DETION_CFG> m_struVcaDetionCfg;
	vector<NET_DVR_CHANNEL_GROUP> m_struChannelGroup;
	DWORD m_dwAlarmOut[MAX_CHANNUM_V30];
	BOOL m_GetStru;
	void CreateTree(void);
	BOOL OnInitDialog();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgVCADetionCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgVCADetionCfg)
	afx_msg void OnSet();
	afx_msg void OnGet();
	afx_msg void OnChangeRelRecordChan();
	afx_msg void OnEnableCurise();
	afx_msg void OnEnablePtzTrack();
	afx_msg void OnChangeCuriseNo();
	afx_msg void OnChangePtzTrack();
	afx_msg void OnEnable();
	afx_msg void OnChangeMaxRelAlarmOutChanNum();
	afx_msg void OnChangeRelAlarmOutChanNum();
	afx_msg void OnChangeMaxRelRecordChanNum();
	afx_msg void OnChangeRelRecordChanNum();
	afx_msg void OnChangeChannelNo();
	afx_msg void OnChangeGroupNo();
	afx_msg void OnSelchangeComCount();
	afx_msg void OnSelchangeComRelAlarmOut();
	afx_msg void OnSelchangeComMaxDay();
	afx_msg void OnSelchangeComChanNo();
	afx_msg void OnEnablePreset();
	afx_msg void OnChangePreset();
	afx_msg void OnOk();
	afx_msg void OnBtnOk();
	afx_msg void OnPaint();
	afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeChan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnExceptionok();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCADETIONCFG_H__B0E8E491_F954_4942_808C_B64CD67A01C3__INCLUDED_)
