#if !defined(AFX_DLGEVENTCARDLINKAGECFG_H__B6999649_38C3_49EE_9B68_BD4F14C8A1A0__INCLUDED_)
#define AFX_DLGEVENTCARDLINKAGECFG_H__B6999649_38C3_49EE_9B68_BD4F14C8A1A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEventCardLinkageCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgEventCardLinkageCfg dialog

class DlgEventCardLinkageCfg : public CDialog
{
// Construction
public:
	DlgEventCardLinkageCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgEventCardLinkageCfg)
	enum { IDD = IDD_DIG_EVENT_CARD_LINKAGE_CFG };
    CTreeCtrl	m_treeDoorOpen;
    CTreeCtrl	m_treeDoorClose;
    CTreeCtrl	m_treeCardReaderBuzzer;
    CTreeCtrl   m_treeCardReaderStopBuzzer;
    CTreeCtrl	m_treeAlarmOut;
    CTreeCtrl	m_treeNormalOpen;
    CTreeCtrl	m_treeNormalClose;
    BOOL	m_byProMode;
    BOOL    m_byMacAddr;
    BOOL	byMainDevBuzzer;
    CComboBox	m_comboMainEventType;
    CComboBox	m_comboSubEventType;
	CString	m_sCardNo;
    CString	m_sMacAddr;
    int     m_dwEventSourceID;
    BOOL	m_bLinkCapPic;
    BOOL    m_bLinkRecordVideo;
    BOOL    m_bMainDevStopBuzzer;
    int     m_dwAudioDisplayID;
    CComboBox   m_cmbAudioDisplayMode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgEventCardLinkageCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgEventCardLinkageCfg)
    virtual BOOL OnInitDialog();
    afx_msg void OnBtnSet();
    afx_msg void OnBtnGet();
    afx_msg void OnClickTreeCardReaderBuzzer(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnClickTreeCardReaderStopBuzzer(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnClickTreeDoorOpen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeDoorClose(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnClickTreeNormalOpen(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnClickTreeNormalClose(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnSelchangeEventMainType();
    //}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
    int m_iDeviceIndex;
    NET_DVR_EVENT_CARD_LINKAGE_CFG_V51 m_struEventCardLinkageCfgV51;
    NET_DVR_EVENT_CARD_LINKAGE_COND m_struEventCardLinkageCond;
private:
    void CreateTree();
    void GetTreeSel(); 
    void InitMainEventType();
    void SubEventTypeDev();
    void SubEventTypeAlarm();
    void SubEventTypeDoor();
    void SubEventTypeCardReader();
    void InitChannel();
    UINT8 charToData(const char ch);
    bool StrToMac(const char * szMac, UINT8 * pMac);
public:
    int m_iLocalController;
    CTreeCtrl m_treeAlarmOutClose;
    CTreeCtrl m_treeAlarmInSetup;
    CTreeCtrl m_treeAlarmInClose;
    afx_msg void OnNMClickTreeAlarmOutClose(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMClickTreeAlarmInSetup(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMClickTreeAlarmInClose(NMHDR *pNMHDR, LRESULT *pResult);
    DWORD m_dwEventID;
    afx_msg void OnClickTreeReaderStopBuzzer(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEVENTCARDLINKAGECFG_H__B6999649_38C3_49EE_9B68_BD4F14C8A1A0__INCLUDED_)
