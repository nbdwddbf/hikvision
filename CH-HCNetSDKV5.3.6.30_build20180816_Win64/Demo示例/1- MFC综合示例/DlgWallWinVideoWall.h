#if !defined(AFX_DLGWALLWIN_H__8F3BD38D_2336_418E_A8BB_0087F145475F__INCLUDED_)
#define AFX_DLGWALLWIN_H__8F3BD38D_2336_418E_A8BB_0087F145475F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWallWin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWallWin dialog
#define MAX_WALL_WIN_COUNT     256
class CDlgWallWinVideoWall : public CDialog
{
// Construction
public:
	CDlgWallWinVideoWall (CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWallWinVideoWall)
	enum { IDD = IDD_DLG_WALLWIN_VIDEOWALL };
	CComboBox	m_cmbWinType;
	CComboBox	m_CombWallNo;
	CComboBox	m_CombScaleStatus;
	CComboBox	m_CombDelayDelay;
	CListCtrl	m_listWinCfg;
	BOOL	m_bEnable;
	DWORD	m_dwLayer;
	short	m_wH;
	short	m_wW;
	short	m_wX;
	short	m_wY;
	BYTE	m_byTransparency;
	BYTE	m_byWinMode;
	BOOL	m_bTransparency;
	DWORD	m_dwWinNo;
	DWORD	m_dwSubwinNo;
	BOOL	m_BEnableSpartan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWallWinVideoWall)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWallWinVideoWall)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListWincfg(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSave();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnSetPro();
	afx_msg void OnBtnGetPro();
	afx_msg void OnBtnGetAll();
	afx_msg void OnBtnSetWallCfg();
	afx_msg void OnBtnGetWallCfg();
	afx_msg void OnBtnWinTop();
	afx_msg void OnBtnWinBottom();
	afx_msg void OnBtnCloseAllWin();
	afx_msg void OnBtnSubwinSet();
	afx_msg void OnBtnSubwinRefresh();
	afx_msg void OnSelchangeWinWallNo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG  m_lUserID;
	LONG  m_iDeviceIndex;

	int   m_iCurSel;
    BYTE  m_byWallNo; 
	DWORD m_dwWinCount;
    DWORD m_dwModifyRecord[MAX_WALL_WIN_COUNT];         //修改记录，记录修改项下标， 发送时只将修改过内容发送
    DWORD m_dwModifyNum;                                // 修改数目
	DWORD m_dwStatus[MAX_WALL_WIN_COUNT];
	DWORD m_dwWinNum[MAX_WALL_WIN_COUNT];      //4字节窗口号
    DWORD m_dwWinNumEx[MAX_WALL_WIN_COUNT];    //1字节墙号 + 1字节保留 + 2字节窗口
    DWORD m_dwRetWinNum[MAX_WALL_WIN_COUNT];   //返回的窗口号
	NET_DVR_VIDEOWALLWINDOWPOSITION m_struList[MAX_WALL_WIN_COUNT];
//	DWORD m_dwWinNumSet[MAX_WALL_WIN_COUNT];   //

	NET_DVR_WALLWINPARAM m_struWallWinParam;
	NET_DVR_WALL_CFG m_struWallCfg;
	void DrawList();

protected:
    LPDWORD WinNumtoEx(); 
    BOOL    UpdateWinList(NET_DVR_VIDEOWALLWINDOWPOSITION &WinPos); 
    BOOL    UpdateRecord(DWORD index);
    LPNET_DVR_VIDEOWALLWINDOWPOSITION GetModify(); 
    BOOL    HasModify(); 
    BOOL    DelModifyRecord(DWORD WinNo); 
    void    SetWallRange(BYTE byMax, BYTE byMin); 
    void    InitVaildWallNo();                //初始化有效的墙号范围

private:
    NET_DVR_VIDEOWALLWINDOWPOSITION m_struModifyList[MAX_WALL_WIN_COUNT];
    BYTE m_byMaxWallNo; 
    BYTE m_byMinWallNo; 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWALLWIN_H__8F3BD38D_2336_418E_A8BB_0087F145475F__INCLUDED_)
