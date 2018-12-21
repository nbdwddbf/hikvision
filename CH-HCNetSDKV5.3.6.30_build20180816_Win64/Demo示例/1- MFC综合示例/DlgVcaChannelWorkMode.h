#if !defined(AFX_DLGVCACHANNELWORKMODE_H__4FFEB0C7_DA02_4E89_9103_DEB931E41ED2__INCLUDED_)
#define AFX_DLGVCACHANNELWORKMODE_H__4FFEB0C7_DA02_4E89_9103_DEB931E41ED2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "VcaCommonOperations.h"
// DlgVcaChannelWorkMode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaChannelWorkMode dialog

class CDlgVcaChannelWorkMode : public CDialog,public CVcaCommonOperations
{
// Construction
public:
	CDlgVcaChannelWorkMode(CWnd* pParent = NULL);   // standard constructor
     
	struct SLAVE_CHANNEL_PARAM
	{
		BOOL    byLocal;
		CString strDevIP;
		CString strUserName;
		CString strPassword;
		DWORD   dwPort;
		DWORD   dwChannel;
	};

	enum
	{
		SLAVE_CHANNEL_LOCAL  = 1,
		SLAVE_CHANNEL_REMOTE = 2
	};
// Dialog Data
	//{{AFX_DATA(CDlgVcaChannelWorkMode)
	enum { IDD = IDD_DLG_VCA_CHANNEL_WORKMODE };
	CListCtrl	m_listSlaveChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaChannelWorkMode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaChannelWorkMode)
	afx_msg void OnBtnAddLocalChannel();
	afx_msg void OnBtnAddRemoteChannel();
	afx_msg void OnBtnModifySlaveChannel();
	afx_msg void OnBtnDelSlaveChannel();
	afx_msg void OnRadioIndependent();
	afx_msg void OnRadioMaster();
	afx_msg void OnRadioSlave();
	afx_msg void OnBtnGetChannelWorkmode();
	afx_msg void OnBtnSetChannelWorkmode();
	afx_msg void OnBtnGetSlaveChannel();
	afx_msg void OnBtnSetSlaveChannel();
	afx_msg void OnDeleteitemListSlaveChannel(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void InitCtrlState();
	void UpdateSlaveChanListIndex();
	void UpdateChanenlWorkModeRadio(DWORD dwChannelWorkMode);
	void AddSlaveChannel(SLAVE_CHANNEL_PARAM* pChannelParam);
	void UpdateSlaveChannel(int nIndex,SLAVE_CHANNEL_PARAM* pChannelParam);
protected:
	BOOL GetChannelWorkMode();
	BOOL SetChannelWorkMode();
	BOOL GetSlaveChannel();
	BOOL SetSlaveChannel();
	void LoadWorkModeWndContent();
	void SaveWorkModeWndContent();
	void LoadSlaveChannelWndContent();
	void SaveSlaveChannelWndContent();

private:
	NET_DVR_CHANNEL_WORKMODE  m_struChannelWorkMode;
	NET_DVR_SLAVE_CHANNEL_CFG m_struSlaveChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCACHANNELWORKMODE_H__4FFEB0C7_DA02_4E89_9103_DEB931E41ED2__INCLUDED_)
