#if !defined(AFX_DLGWALLCFG_H__E39FB209_F61B_43EB_A4EE_547DCB33027B__INCLUDED_)
#define AFX_DLGWALLCFG_H__E39FB209_F61B_43EB_A4EE_547DCB33027B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWallCfg_Uniform.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWallCfg_Uniform dialog
#define MAX_COUNT    256

#define HEIGHT 1920
#define WIDTH  1920

class CDlgWallCfg_Uniform : public CDialog
{
// Construction
public:
	CDlgWallCfg_Uniform(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWallCfg_Uniform)
	enum { IDD = IDD_DLG_WALL_CFG_UNIFORM };
	CComboBox	m_CmChanTypeC;
	CButton	m_btnCWEnable;
	CComboBox	m_combVideoFormat;
	CComboBox	m_combBackGround;
	CComboBox	m_combDisplayMode;
	CComboBox	m_comboResolution;
	CComboBox	m_comboOutput;
	CComboBox	m_comboLevel;
	CListCtrl	m_listScreen;
	CComboBox	m_comboY;
	CComboBox	m_comboX;
	BOOL	m_bEnable;
	BOOL	m_bDzd;
	BOOL	m_bFgb;
	BOOL	m_bQgyz;
	BYTE	m_byBrightness;
	BYTE	m_byContrast;
	BYTE	m_byGray;
	BYTE	m_byHue;
	BYTE	m_bySaturation;
	BYTE	m_bySharpness;
	BYTE	m_byWallNo;
	DWORD	m_dwOutputNum;
	DWORD	m_dwDisplayNoC;
	BOOL	m_BShowC;
	BOOL	m_BAllDisplayNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWallCfg_Uniform)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWallCfg_Uniform)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnExit();		
	afx_msg void OnClickListScreen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnGetAll();
	afx_msg void OnBtnSaveCfg();
	afx_msg void OnBtnSetCfg();
	afx_msg void OnBtnGetCfg();
	afx_msg void OnSelchangeComboOutput();
	afx_msg void OnBtnUpdateOutput();
	afx_msg void OnBtnGet();
	afx_msg void OnButVideowallControl();
	afx_msg void OnButVwscSend();
	afx_msg void OnChkVwsAlldisplayno();
	afx_msg void OnButDispParamAllSame();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG m_lUserID;
	LONG m_iDeviceIndex;
    BYTE m_byInitWallNo;                                            //初始化墙号
	DWORD m_dwCount;                                                //修改个数
	DWORD m_dwDispNum;                                              //显示个数
	int m_iCurSel;                                                      
	LONG  m_ModifyChan[MAX_COUNT];                                    //修改过显示输出号数组                              
	LONG m_lDispChanSet[MAX_COUNT];                                  //记录m_struWallParam修改项下标
    DWORD m_dwStatus[MAX_COUNT];                                     //状态数
	NET_DVR_VIDEOWALLDISPLAYPOSITION m_struWallParam[MAX_COUNT];      //
	NET_DVR_VIDEOWALLDISPLAYPOSITION m_struWallParamSet[MAX_COUNT];   //修改过项， 用于设置
	NET_DVR_MATRIX_ABILITY_V41 m_struAblity;
    LONG    m_lDispChan[MAX_COUNT];                                   //显示输出号数组    与m_struOutput一一对应
    
    LONG m_lPapamCount;                                               //输出参数计数    获取输入位置参数后不会变化
    LONG m_lRecordCount;                                              //输出参数修改计数
    LONG m_dwRecordPapam[MAX_COUNT];                                  //记录修改过参数下标
    NET_DVR_WALLOUTPUTPARAM m_struOutput[MAX_COUNT];
	NET_DVR_WALLOUTPUTPARAM m_struOutputSet[MAX_COUNT];
    
    NET_DVR_VIDEOWALLDISPLAYMODE m_struDisplayMode;                   // 显示模式
  

	LONG m_lDispOutputSet[MAX_COUNT];
	DWORD m_dwOutputSet;
	void DrawList();


protected:
    BOOL UpdateOutputNum(const NET_DVR_VIDEOWALLDISPLAYPOSITION &struDisplayPos); 
    BOOL UpdateDisplayPos(NET_DVR_VIDEOWALLDISPLAYPOSITION &struDisplayPos);
    BOOL NewOutputNum(const NET_DVR_VIDEOWALLDISPLAYPOSITION &struDisplayPos);            //新获取项
    LPNET_DVR_VIDEOWALLDISPLAYPOSITION GetModifyDisplayPos();                             //获取修改过项
    LONG *GetModifyChan();                                                                //获取修改过显示输出号数组
    BOOL ClearModify();                                                                   //清零修改记录

    BOOL UpdateOutputPapam(NET_DVR_WALLOUTPUTPARAM &struOutputPapam); 
    BOOL UpdatePapams(DWORD dwOutputNO, NET_DVR_WALLOUTPUTPARAM &struOutputPapam);        //更新内存该项内容
    BOOL RemovePapamRecord(DWORD dwOutputNO);                                             //消除该修改记录 
    LPNET_DVR_WALLOUTPUTPARAM GetModifyPapam();                                           //获取修改过的配置参数
    LONG *GetModifyPapamChan();                                                           //获取修改过配置参数的显示输出号数组

    void InitOutputLinkMode();

private:
    NET_DVR_DISPLAYCFG m_struDisplayCfg;                              //显示输出号状态
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWALLCFG_H__E39FB209_F61B_43EB_A4EE_547DCB33027B__INCLUDED_)
