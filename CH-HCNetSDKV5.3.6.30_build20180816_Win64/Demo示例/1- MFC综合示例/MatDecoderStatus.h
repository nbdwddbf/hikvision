#if !defined(AFX_MATDECODERSTATUS_H__188141CC_6395_4466_8FE0_A60189DFDABF__INCLUDED_)
#define AFX_MATDECODERSTATUS_H__188141CC_6395_4466_8FE0_A60189DFDABF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatDecoderStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatDecoderStatus dialog

class CMatDecoderStatus : public CDialog
{
// Construction
public:
	CMatDecoderStatus(CWnd* pParent = NULL);   // standard constructor

    LONG m_lServerID;
    LONG m_lStartChan;
    int  m_iChannelNumber;
    int  m_iVGANums;
	int  m_iHDMINums;
	int  m_iDVINums;
    int  m_iBNCNums;
	int  m_iSDINums;
    NET_DVR_DECODER_WORK_STATUS_V41 m_DecoderWorkStatus;
	NET_DVR_MATRIX_ABILITY_V41 m_Ability;
	NET_DVR_DEVICECFG_V40 m_struDeviceCfg;

    int  m_iDeviceIndex;
    DWORD m_dwDecChanNum[256];
    DWORD m_dwDispCount;
    DWORD m_dwDispChanNUm[256];
    DWORD m_dwAlarmInNum[256];
    DWORD m_dwAlarmOutNum[256];
    NET_DVR_MATRIX_CHAN_STATUS m_struDecChanStatus[256];
    NET_DVR_DISP_CHAN_STATUS_V41 m_struDispChanStatus[256];
    DWORD m_dwAlarmInStatus[256];
    DWORD m_dwAlarmOutStatus[256];
	DWORD m_dwAudioInChanStatus[2];

// Dialog Data
	//{{AFX_DATA(CMatDecoderStatus)
	enum { IDD = IDD_DLG_MATDEVICESTATUS };
	CComboBox	m_Audio2Ctrl;
	CComboBox	m_Audio1Ctrl;
	CListCtrl	m_SubWndList;
	CComboBox	m_SubWndCtrl;
	CListCtrl	m_AlarmList;
	CListCtrl	m_DispList;
	CListCtrl	m_DecList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatDecoderStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMatDecoderStatus)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnSelchangeComboSubwnd();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void UseMatrixGetDeviceStatusV41(); 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATDECODERSTATUS_H__188141CC_6395_4466_8FE0_A60189DFDABF__INCLUDED_)
