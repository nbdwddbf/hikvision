// PlayBackDlg.h : header file
//

#if !defined(AFX_PLAYBACKDLG_H__8D5598CC_904F_486A_ADFC_F4D19DF9E5C8__INCLUDED_)
#define AFX_PLAYBACKDLG_H__8D5598CC_904F_486A_ADFC_F4D19DF9E5C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PlayRemoteFile.h"
//#include "PlayLocalFile.h"
#include "PlayTimeFile.h"
#include "GeneralDef.h"


/////////////////////////////////////////////////////////////////////////////
// CPlayBackDlg dialog

class CPlayBackDlg : public CDialog
{
// Construction
public:
	CPlayBackDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPlayBackDlg)
	enum { IDD = IDD_PLAYBACK_DIALOG };
	CTreeCtrl	m_ctrlTreeChan;
	CTabCtrl	m_ctrlTab;
	CIPAddressCtrl	m_ctrlDevIp;
	UINT	m_nDevPort;
	CString	m_csUser;
	CString	m_csPWD;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayBackDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
public:
    CPropertySheet m_Playback;
	CPlayRemoteFile m_PageRemote;
//	CPlayLocalFile m_PageLocal;
	CPlayTimeFile m_PageTime;
//	int m_iCurDeviceIndex;        //当前选中设备索引
//	int m_iCurChanIndex;          //当前选中通道索引
//	int m_iCurChanIndex;          // 当前选中节点对应的通道索引
	HTREEITEM m_hCurDeviceItem;   //当前选中设备
	HTREEITEM m_hCurChanItem;     //当前选中通道
//	int m_nCurDevCount;           //当前设备总数


	BOOL m_bIsLogin;
	LOCAL_DEVICE_INFO m_struDeviceInfo;
	int m_iCurChanIndex;               //当前通道在数组中索引
	HTREEITEM m_hDevItem;
	BOOL DoLogin();
	void DoGetDeviceResoureCfg();
	void CreateDeviceTree();
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPlayBackDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTabPlayback(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonLogin();
	afx_msg void OnSelchangedTreeChan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYBACKDLG_H__8D5598CC_904F_486A_ADFC_F4D19DF9E5C8__INCLUDED_)
