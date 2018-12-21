#pragma once
#include "afxwin.h"


// CDlgRemoteAlarmInPtzInvoke dialog

class CDlgRemoteAlarmInPtzInvoke : public CDialog
{
	DECLARE_DYNAMIC(CDlgRemoteAlarmInPtzInvoke)

public:
	CDlgRemoteAlarmInPtzInvoke(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRemoteAlarmInPtzInvoke();

// Dialog Data
	


public:
	//{{AFX_DATA(CDlgRemoteAlarmInPtzInvoke)
	enum { IDD = IDD_DLG_REMOTE_ALARM_IN_PTZ_INVOKE };
	CComboBox m_comboChan;
	int	m_iPresetNo;
	int	m_iTrackNo;
	int	m_iCruiseNo;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CDlgRemoteAlarmInPtzInvoke)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteAlarmInPtzInvoke)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnPtzOk();
	afx_msg void OnBnClickedBtnPtzExit();
	afx_msg void OnCbnSelchangeComboPtzLinkage();	
	afx_msg void OnDeltaposSpinCruise(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinPreset(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinTrack(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadioCruise();
	afx_msg void OnRadioPreset();
	afx_msg void OnRadioTrack();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	LPNET_DVR_ALARMINCFG_V40 m_lpAlarmInV40;
	int m_nChannel;
	int		m_iChanCount;
	LONG	m_lStartChannel;
	int		m_iAnalogChanNum;
	int		m_iDStartChannel; //数字通道起始通道号
	BOOL m_bPreset;
	BOOL m_bCruise;
	BOOL m_bTrack;
	int m_iDeviceIndex;
	void EnableCtrl();

	void FindDataInPresetInfo(DWORD dwFindData);
    void FindDataInCruiseInfo(DWORD dwFindData);
    void FindDataInPtzInfo(DWORD dwFindData);
     void SaveLastInfoToCfg();
     int m_iPresetDurationTime;
};
