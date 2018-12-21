#if !defined(AFX_DLGVIDEOINTERCOMCALL_H__F40DE5CD_E347_4383_A2F8_DAB4A919B723__INCLUDED_)
#define AFX_DLGVIDEOINTERCOMCALL_H__F40DE5CD_E347_4383_A2F8_DAB4A919B723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVideoIntercomCall.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomCall dialog

class CDlgVideoIntercomCall : public CDialog
{
// Construction
public:
	CDlgVideoIntercomCall(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVideoIntercomCall)
	enum { IDD = IDD_DLG_VIDEO_INTERCOM_CALL };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVideoIntercomCall)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVideoIntercomCall)
	afx_msg void OnBtnInquest();
	afx_msg void OnBtnAnswer();
	afx_msg void OnBtnHangUp();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnBtnCancel();
#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif	
	afx_msg void OnBtnRefuse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
    int  m_iDevIndex;
    BYTE m_byRequestType; 
    LONG m_lRemoteHandle;
private:
    NET_DVR_VIDEO_CALL_COND  m_struVideoCallCond;
    NET_DVR_VIDEO_CALL_PARAM m_struVideoCallParam;
    LONG m_lRealPlayHandle;
    LONG m_lVoiceTalkHandle;
    BOOL m_bClientCall;

private:
    void ChangeBtnStates();
    DWORD m_dwCallStatus;

    DWORD m_dwPeriod;
    DWORD m_dwBuildingNumber;
    DWORD m_dwUnitNumber;
    int m_dwFloorNumber;
    DWORD m_dwRoomNumber;
    DWORD m_dwDevIndex;
    CComboBox m_cmbUnitType;

public:
    void StartRemoteCfg();
    void StopRemoteCfg();
    void StartPlay();
    void StartVoiceTalk();
    void StopPlay();
    void StopAudioIntercom();
    void SendByeCmd();
    void SendBellTimeoutCmd();    
    void SendAcceptCmd();
    void SendRefuseCmd();
    void SendCancellCmd();
    void SendCallCmd();

    LRESULT OnVideoCallProcess(WPARAM wParam, LPARAM lParam);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIDEOINTERCOMCALL_H__F40DE5CD_E347_4383_A2F8_DAB4A919B723__INCLUDED_)
