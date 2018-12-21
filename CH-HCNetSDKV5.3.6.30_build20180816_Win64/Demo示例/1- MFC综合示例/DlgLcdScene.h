#if !defined(AFX_DLGLCDSCENE_H__FE13EF23_6A85_4E57_8E24_F18128B48B5D__INCLUDED_)
#define AFX_DLGLCDSCENE_H__FE13EF23_6A85_4E57_8E24_F18128B48B5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLcdScene.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdScene dialog
#define LCD_SCENE_NUM    8 //LCD服务器支持的场景数

class CDlgLcdScene : public CDialog
{
// Construction
public:
	CDlgLcdScene(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLcdScene)
	enum { IDD = IDD_DLG_LCD_SCENE };
	CListCtrl	m_listScene;
	CComboBox	m_comboSceneOperate;
	DWORD	m_dwCopyScene;
	CString	m_csSceneName;
	DWORD	m_dwSceneNum;
	DWORD	m_dwSceneNumOperate;
	DWORD	m_dwWallNo;
	BOOL	m_bEnable;
	DWORD	m_dwWallNoOperate;
	DWORD	m_dwSceneNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLcdScene)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLcdScene)
	virtual BOOL OnInitDialog();	
	afx_msg void OnBtnSave();
	afx_msg void OnBtnModeSet();
	afx_msg void OnBtnModeGet();
	afx_msg void OnBtnSceneGet();
	afx_msg void OnBtnControl();
	afx_msg void OnSelchangeComboSceneOperate();
	afx_msg void OnClickListScene(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
    int m_iDeviceIndex;
    int m_iCurSel;
    DWORD m_dwSetCount;
    NET_DVR_VIDEO_WALL_INFO m_struSceneNo[LCD_SCENE_NUM];
    NET_DVR_WALLSCENECFG m_struSenceName[LCD_SCENE_NUM];
    NET_DVR_SCENE_CONTROL_INFO m_struSceneControlInfo;
    DWORD m_dwStatus[LCD_SCENE_NUM];
    
	void DrawList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLCDSCENE_H__FE13EF23_6A85_4E57_8E24_F18128B48B5D__INCLUDED_)
