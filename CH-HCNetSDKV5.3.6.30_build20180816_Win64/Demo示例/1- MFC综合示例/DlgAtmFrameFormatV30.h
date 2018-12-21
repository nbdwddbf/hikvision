#if !defined(AFX_DLGATMFrameFormatV30_H__AB49892A_9A01_4691_83E8_EA60AD24FBCE__INCLUDED_)
#define AFX_DLGATMFrameFormatV30_H__AB49892A_9A01_4691_83E8_EA60AD24FBCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAtmFrameFormatV30.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAtmFrameFormatV30 dialog

class CDlgAtmFrameFormatV30 : public CDialog
{
// Construction
public:
	CDlgAtmFrameFormatV30(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAtmFrameFormatV30)
	enum { IDD = IDD_DLG_ATM_FRAME_FROMAT_CFG };
	CListCtrl	m_listRecordChannel;
	CComboBox	m_comboStartMode;
	CComboBox	m_comboOsdMode;
	CComboBox	m_comboLocationOffsetMode;
	CComboBox	m_comboLocationCodeMode;
	CComboBox	m_comboLengthEndCode;
	CComboBox	m_comboLengthMode;
	CComboBox	m_comboInputMode;
	CComboBox	m_comboFrameType;
	CComboBox	m_comboFilterMode;
	CComboBox	m_comboEndMode;
	CComboBox	m_comboAtmType;
	CComboBox	m_comboActionType;
	CComboBox	m_comboActionCodeMode;
	BOOL	m_bEnableAtm;
	BOOL	m_bEnableDelayTime;
	BOOL	m_bEnableFilter;
	CString	m_csActionCode;
	CString	m_csAtmIP;
	int		m_iAtmPort;
	CString	m_csEndCode;
	CString	m_csFilterText;
	CString	m_csLengthEndCode;
	DWORD	m_dwDelayTime;
	DWORD	m_dwLengthFixLen;
	DWORD	m_dwLengthPos;
	BYTE	m_byLocationMultiplierValue;
	DWORD	m_dwLocationOffsetPos;
	DWORD	m_dwLocationRelativeOffset;
	CString	m_csLocationTokenCode;
	DWORD	m_dwMaxLength;
	DWORD	m_dwMinLength;
	DWORD	m_dwOsdPosX;
	DWORD	m_dwOsdPosY;
	CString	m_csPreCode;
	CString	m_csStartCode;
	DWORD	m_dwLengthLen;
	BYTE	m_byBeginPos;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAtmFrameFormatV30)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAtmFrameFormatV30)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnChkEnableAtm();
	afx_msg void OnSelchangeComboInputMode();
	afx_msg void OnSelchangeComboAtmType();
	afx_msg void OnSelchangeComboFrameType();
	afx_msg void OnSelchangeComboActionType();
	afx_msg void OnBtnPackageConfirm();
	afx_msg void OnCheckEnableFilter();
	afx_msg void OnCheckEnableDelaytime();
	afx_msg void OnSelchangeComboOsdMode();
	afx_msg void OnSelchangeComboLocationOffsetMode();
	afx_msg void OnSelchangeComboLengthMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    long    m_lServerID;
    int     m_iDevIndex;
    int     m_iChannelNum;
private:

    NET_DVR_ATM_FRAMEFORMAT_V30 m_struAtmFrameFormatV30;
    NET_DVR_ATM_PROTOCOL m_struAtmProtocol;

    BOOL GetFrameFormatSet(NET_DVR_ATM_FRAMEFORMAT_V30 struAtmFrameFormatV30);
    
    BOOL EnableAtmWnd(BOOL m_bEnableAtm);
    BOOL EnableAtmTypeWnd(BOOL bEnable);
    BOOL GetAtmPackageSet(NET_DVR_ATM_PACKAGE_OTHERS struAtmPackage);
    BOOL GetAtmPackageActionSet(NET_DVR_ATM_PACKAGE_ACTION struAtmPackageAction);
    BOOL GetLocationParaSet(NET_DVR_PACKAGE_LOCATION struPackageLocation);
    BOOL GetOsdPositionSet(NET_DVR_OSD_POSITION sturOsdPosition);
    BOOL GetPackageLengthSet(NET_DVR_PACKAGE_LENGTH struPackageLength);
    BOOL GetIdentificatSet(NET_DVR_IDENTIFICAT struIdentificat);
    BOOL GetFilterSet(NET_DVR_FILTER struFilter);
    BOOL SetAtmPackage(LPNET_DVR_ATM_PACKAGE_OTHERS lpAtmPackage);
    BOOL SetAtmPackageAction(LPNET_DVR_ATM_PACKAGE_ACTION lpAtmPackageAction);
    BOOL SetIdentificat(LPNET_DVR_IDENTIFICAT lpIdentificat);
    BOOL SetFilter(LPNET_DVR_FILTER lpFilter);
    BOOL SetPackageLength(LPNET_DVR_PACKAGE_LENGTH lpPackageLength);
    BOOL SetLocationParam(LPNET_DVR_PACKAGE_LOCATION lpPackageLocation);
    BOOL SetOsdPosition(LPNET_DVR_OSD_POSITION lpOsdPosition);
    
    BOOL GetOverlayChannelSet(NET_DVR_OVERLAY_CHANNEL struOverlayChannel);
    BOOL SetOverlayChannel(LPNET_DVR_OVERLAY_CHANNEL lpOverlayChannel);
 
    BOOL EnableFilterWnd(BOOL bEnable);
    BOOL EnableActionWnd(BOOL bActionWnd);
    void EnableAtmLocationWnd(BOOL bEnableToken);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGATMFrameFormatV30_H__AB49892A_9A01_4691_83E8_EA60AD24FBCE__INCLUDED_)
