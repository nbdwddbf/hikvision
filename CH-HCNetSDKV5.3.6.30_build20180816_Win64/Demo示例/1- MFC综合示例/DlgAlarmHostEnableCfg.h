#if !defined(AFX_DLGALARMHOSTENABLECFG_H__B7BA87F6_ADD5_4B6D_A8D3_478290268829__INCLUDED_)
#define AFX_DLGALARMHOSTENABLECFG_H__B7BA87F6_ADD5_4B6D_A8D3_478290268829__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostEnableCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostEnableCfg dialog

class CDlgAlarmHostEnableCfg : public CDialog
{
// Construction
public:
	CDlgAlarmHostEnableCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostEnableCfg)
	enum { IDD = IDD_DLG_ALARMHOST_ENABLECFG };
	CListCtrl	m_listSiren;
	CListCtrl	m_listMobileGate;
	CListCtrl	m_listElectorLock;
	CListCtrl	m_listAudioOut;
	CComboBox	m_comboSirenPurpose;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostEnableCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostEnableCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    NET_DVR_ALARMHOST_ABILITY m_struAbility;
    NET_DVR_ALARMHOST_ENABLECFG m_struEnableCfg;

public:  // fun
    void InitWnd();
    void InitAudioOutList();
    void InitElectroLockList();
    void InitMobileGateList();
    void InitSirenList();
    void InitSerialPurposr();

    BOOL GetAlarmHostEnable(NET_DVR_ALARMHOST_ENABLECFG &struEnableCfg);
    BOOL SetAlarmHostEnable(NET_DVR_ALARMHOST_ENABLECFG &struEnableCfg);

    void GetAlarmHostEnableFromWnd(NET_DVR_ALARMHOST_ENABLECFG &struEnableCfg);
    void SetAlarmHostEnableToWnd(NET_DVR_ALARMHOST_ENABLECFG &struEnableCfg);

    void GetAudioOutFromWnd(BYTE *byAudioOut, DWORD dwSize);
    void SetAudioOutToWnd(BYTE *byAudioOut, DWORD dwSize);
    void GetElectroLockFromWnd(BYTE *byElectroLock, DWORD dwSize);
    void SetElectroLockToWnd(BYTE *byElectroLock, DWORD dwSize);
    void GetMobileGateFromWnd(BYTE *byMobileGate, DWORD dwSize);
    void SetMobileGateToWnd(BYTE *byMobileGate, DWORD dwSize);
    void GetSirenFromWnd(BYTE *bySiren, DWORD dwSize);
    void SetSirenToWnd(BYTE *bySiren, DWORD dwSize);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTENABLECFG_H__B7BA87F6_ADD5_4B6D_A8D3_478290268829__INCLUDED_)
