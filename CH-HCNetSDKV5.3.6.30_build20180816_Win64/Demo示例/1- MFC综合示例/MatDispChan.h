#if !defined(AFX_MATDISPCHAN_H__B12A9342_F03D_4BC7_B3B3_060224F63241__INCLUDED_)
#define AFX_MATDISPCHAN_H__B12A9342_F03D_4BC7_B3B3_060224F63241__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatDispChan.h : header file
//
#include "vector"
#include "afxwin.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CMatDispChan dialog

class CMatDispChan : public CDialog
{
// Construction
public:
	CMatDispChan(CWnd* pParent = NULL);   // standard constructor
    void EnableStreamMedia(BOOL bUseStreamMedia);

	int m_lServerID;
	int m_lStartChan;
	int m_iChannelnumber;

    NET_DVR_IPC_PROTO_LIST m_struProtoList;
// Dialog Data
	//{{AFX_DATA(CMatDispChan)
	enum { IDD = IDD_DLG_MATDISPCHAN };
	CComboBox	m_comboDomainTransMode;
	CComboBox	m_comboDomainTransPro;
	CComboBox	m_comboDomainStreamMediaPro;
	CComboBox	m_comboDomainServerType;
	CComboBox	m_comboDomainFacType;
	CComboBox	m_comboDomainChannelType;
	CComboBox	m_comboChannelType;
	CComboBox	m_comboStreamMode;
	CComboBox	m_FacTypeCtrl;
	CComboBox	m_comboStreamType;
	CComboBox	m_ComboPassiveTransProtol;
	CComboBox	m_ComboStreamMediaPro;
	CComboBox	m_ComboGetStreamMode;
	CComboBox	m_IsLinkCombo;
	CComboBox	m_ChanCombo;
	CDateTimeCtrl	m_EndTime;
	CDateTimeCtrl	m_EndDate;
	CDateTimeCtrl	m_StartTime;
	CDateTimeCtrl	m_StartDate;
	CComboBox	m_DIModeCombo;
	CComboBox	m_DIProTypeCombo;
	CComboBox m_DecStateCombo;
	CString	m_DIIP;
	DWORD	m_DIChanNum;
	CString	m_DIUserName;
	CString	m_DIPwd;
	CString	m_FileName;
	DWORD	m_CopyRate;
	CString	m_strStreamMediaIp;
	DWORD	m_dwStreamMediaPort;
	BOOL	m_bUseStreamMedia;
	DWORD	m_dwPassivePort;
	DWORD	m_DIPort;
	BOOL	m_bUseUrl;
	CString	m_csUrl;
	CString	m_strIpStreamId;
	UINT	m_dwDomainChannelNum;
	CString	m_strDomainName;
	CString	m_strDomainRemoteName;
	CString	m_strDomainRemotePass;
	CString	m_strDomainServerIp;
	short	m_wDomainServerPort;
	CString	m_strDomainStreamID;
	CString	m_strDomainStreamMediaIp;
	short	m_wDomainStreamMediaPort;
	BOOL	m_bDomainUseStreamMedia;
	short	m_wDomainDevPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatDispChan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMatDispChan)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeChancombo();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	virtual void OnCancel();
	afx_msg void OnUsestreammedia();
	afx_msg void OnSelchangeComboStreamMode();
	afx_msg void OnChkDomainUsestreammedia();
	afx_msg void OnSelchangeCombogetstreammode();
	afx_msg void OnSelchangeCombodecstate();
	afx_msg void OnSelchangeComboChanType();
	afx_msg void OnSelchangeComboDomainChannelType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:	
	BOOL GetChanStatus(DWORD DispChanNum,int index);
	void ShowChanInfo(int index);

private:
	NET_DVR_MATRIX_DEC_CHAN_STATUS m_DecChanStatus[256];
	NET_DVR_MATRIX_DEC_CHAN_INFO_V41 m_DecChanInfo[256];

	int m_iChanSel;
	vector<BOOL> m_vGetStatus;
	vector<BOOL> m_vbGetInfo;

private:
	void EnableIpOrDomainGroup(BOOL IsEnable);
	void EnableURLGroup(BOOL IsEnable);
	void EnableDynamicDDNSGroup(BOOL IsEnable);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATDISPCHAN_H__B12A9342_F03D_4BC7_B3B3_060224F63241__INCLUDED_)
