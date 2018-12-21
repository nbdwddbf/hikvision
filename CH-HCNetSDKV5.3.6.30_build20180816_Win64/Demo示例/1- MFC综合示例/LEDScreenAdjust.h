#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// LEDScreenAdjust 对话框

class LEDScreenAdjust : public CDialog
{
	DECLARE_DYNAMIC(LEDScreenAdjust)

public:
	LEDScreenAdjust(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LEDScreenAdjust();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DLG_SCREENADJUST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_CombOperateType;
	CComboBox m_CombRGBSync;
	long m_lHandle;
	long m_lUserID;
	long m_iDeviceIndex;
	long m_lRgbPermil;
	long m_lRedPermil;
	long m_lGreenPermil;
	long m_lBluePermil;
	BOOL m_bFreshed;
	BOOL  m_needSave; //用于保存标志,如果有过编写则为TURE,当下次编辑时会在原来的位置输入原来输入的内容
	CEdit m_Edit;
	int m_Item;  //行
	int m_SubItem; //列
	int m_rowCount;  //总行数
	int m_rowCountNew; //实际有效行数
	HWND m_hWnd;	//窗口句柄
	NET_SDK_LED_SCREEN_CHECK_PARAM m_struScreenCheck;
	CListCtrl m_List_ScreenArea;
	CProgressCtrl m_Progress_ScreenAdjust;
	void InitList();
	void OnFreshList();
	void OnScreenAdjust(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
	void Init(LONG lUserID, int iDeviceIndex){ m_lUserID = lUserID; m_iDeviceIndex = iDeviceIndex; };
	afx_msg LRESULT OnScreenAdjustMessageSucc(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnScreenAdjustMessageFail(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnScreenAdjustMessageFresh(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedBtnOperate();	
	afx_msg void OnNMClickListScreenarea(NMHDR *pNMHDR, LRESULT *pResult);
};
