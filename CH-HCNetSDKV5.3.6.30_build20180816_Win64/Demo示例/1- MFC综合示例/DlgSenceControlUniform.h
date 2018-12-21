#if !defined(AFX_DLGSENCECONTROL_H__D558880A_302E_4098_93FD_7113DBB57256__INCLUDED_)
#define AFX_DLGSENCECONTROL_H__D558880A_302E_4098_93FD_7113DBB57256__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSenceControl2.h : header file
//
#include "ModifyRecord.h"
//////////////////////////////
bool SceneIndexCmp (const void *ItemF, const void *ItemS);  //更新比较条件函数 场景号相等
class SceneBatchManage
{
public:
	BOOL Init(LPNET_DVR_WALLSCENECFG lpSrc, LPNET_DVR_VIDEO_WALL_INFO lpIndex, DWORD max);             //初始化资源
	int  GetModify(LPNET_DVR_WALLSCENECFG &lpModifySrc, LPNET_DVR_VIDEO_WALL_INFO &lpIndex);        //获取修改过资源, 返回个数
	BOOL Update(DWORD dwNum, const NET_DVR_WALLSCENECFG *lpSceneCfg, const NET_DVR_VIDEO_WALL_INFO &struIndex);    //刷新某一墙
	BOOL Update(const NET_DVR_WALLSCENECFG &SceneCfg, const NET_DVR_VIDEO_WALL_INFO &struIndex);   //刷新某一项 
	BOOL Modify(const NET_DVR_WALLSCENECFG &SceneCfg, const NET_DVR_VIDEO_WALL_INFO &struIndex);  
	BOOL Change(const NET_DVR_WALLSCENECFG &SceneCfg, const NET_DVR_VIDEO_WALL_INFO &struIndex);  //改变某一项，或更新 或修改
	int  GetNum(); 
	bool GetSrc(LPNET_DVR_VIDEO_WALL_INFO &lpIndex, LPNET_DVR_WALLSCENECFG &lpSrc);
	BOOL Del(int iSceneIndex);       //删除某一项场景

protected:
	

	bool ModifyCmp(const void *ItemF, const void *ItemS); //修改比较
private:
	ModRecord m_RecordInfo; 
	ModRecord m_RecordCfg;
};

#define SCENE_NUM  128
class CDlgSenceControlUniform : public CDialog
{
// Construction
public:
	CDlgSenceControlUniform(CWnd* pParent = NULL);   // standard constructor
	~CDlgSenceControlUniform();
// Dialog Data
	//{{AFX_DATA(CDlgSenceControlUniform)
	enum { IDD = IDD_DLG_SCENE_CONTROL_UNIFORM };
	CListCtrl	m_listScene;
	CComboBox	m_comboSceneOperate;
	DWORD	m_dwCopyScene;
	CString	m_csSceneName;
	DWORD	m_dwSceneNum;
	DWORD	m_dwSceneNumOperate;
	BOOL	m_chEnable;
	BYTE	m_bySceneIndex;
	DWORD	m_dwWallNo;
	DWORD	m_dwStructNum;
	DWORD	m_dwWinNo;
	DWORD	m_dwSceneControl;
	DWORD	m_dwWallNoControl;
	DWORD	m_dwSceneNoCur;
	DWORD	m_dwWallNoCur;
	CString	m_csConfigFilePath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSenceControlUniform)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSenceControlUniform)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnModeGet();
	afx_msg void OnBtnModeSet();
	afx_msg void OnBtnSave();
	afx_msg void OnClickListScene(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSceneGet();
	afx_msg void OnSelchangeComboSceneOperate();
	afx_msg void OnBtnControl();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnGetAllScene();
	afx_msg void OnButVwssRefresh();
	afx_msg void OnButBrowser();
	afx_msg void OnButSceneUpload();
	afx_msg void OnButSceneDownload();
#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	int m_iDeviceIndex;
	int m_iCurSel;

	DWORD m_dwStatus[SCENE_NUM];
	char* m_lpOutBuffer;
	void DrawList(BOOL bIndexType = TRUE);
    void UpdateInterface(const NET_DVR_WALLSCENECFG &Item);



private:
   
    DWORD m_dwCount; 
    NET_DVR_WALLSCENECFG m_struSenceCfg[SCENE_NUM];
    NET_DVR_VIDEO_WALL_INFO m_struWallInfo[SCENE_NUM]; 
    char * m_lpGetAllSenceBuf; 

    SceneBatchManage m_SceneCfgManage; 
    char m_szLan[128]; 

    LONG m_lUploadHandle; 
    LONG m_lDownloadHandle; 
   
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSENCECONTROL_H__D558880A_302E_4098_93FD_7113DBB57256__INCLUDED_)
