#if !defined(AFX_DLGLCDSPLICE_H__8751889A_7490_4760_8401_9110C76365A4__INCLUDED_)
#define AFX_DLGLCDSPLICE_H__8751889A_7490_4760_8401_9110C76365A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLcdSplice.h : header file
//
#define SPLICE_NUM 10 //拼接屏总数
/////////////////////////////////////////////////////////////////////////////
// CDlgLcdSplice dialog

class CDlgLcdSplice : public CDialog
{
// Construction
public:
	CDlgLcdSplice(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLcdSplice)
	enum { IDD = IDD_DLG_LCD_SPLICE };
	CStatic	m_csStatus;
	CComboBox	m_comboY;
	CComboBox	m_comboX;
	CComboBox	m_comboWidth;
	CComboBox	m_comboSpliceNo;
	CComboBox	m_comboHeight;
	BYTE	m_byWallNo;
	BOOL	m_bEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLcdSplice)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLcdSplice)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnExit();
	afx_msg void OnSelchangeComboSpliceNo();
    afx_msg LRESULT OnMessUpdateInterface(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
    int m_iDeviceIndex;
    int m_iLastSel;
    LONG m_lCfgHandle;
    NET_DVR_MSC_SPLICE_CFG m_struSpliceCond[SPLICE_NUM];
    NET_DVR_MSC_SPLICE_CFG m_struSpliceParam[SPLICE_NUM];
    HANDLE m_lHandle; //线程句柄
    DWORD m_dwCfgNo;
    BOOL m_bExitThread;
    int m_iConfigType; //参数配置类型，0-设置，1-获取

    void ShowDataNotToSave(BOOL BjustShow = TRUE); 

private:
    void SaveLastData();
    
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLCDSPLICE_H__8751889A_7490_4760_8401_9110C76365A4__INCLUDED_)
