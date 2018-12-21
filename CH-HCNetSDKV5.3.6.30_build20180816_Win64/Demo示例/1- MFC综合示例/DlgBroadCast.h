#pragma once
#include "afxcmn.h"

// CBroadCast dialog

class CBroadCast : public CDialog
{
	DECLARE_DYNAMIC(CBroadCast)

public:
	CBroadCast(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBroadCast();

// Dialog Data

public:

	//{{AFX_DATA(CBroadCast)
	enum { IDD = IDD_DLG_BROAD_CAST };
	CTreeCtrl m_treeBroadCast;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CBroadCast)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CBroadCast)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnBroadCast();
	afx_msg void OnBnClickedBtnBroadCastExit();
	afx_msg void OnNMClickTreeall(NMHDR *pNMHDR, LRESULT *pResult);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	
	void CreateTree(void);
	
	CImageList m_TreeImage;
	
	// select or cancel all the devices in this area
	void CheckAllDevState(HTREEITEM hRoot, BOOL bCheck, int uFlag);

	void CheckAllAudioState(HTREEITEM hDev, BOOL bCheck, int uFlag);
	void LoadTreeImage(void);
	//  add or delete some device in multicast
	BOOL AddDVR(int iDeviceIndex, int iAudioIndex, BOOL bCheck);
};
