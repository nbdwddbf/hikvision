#pragma once


// CDlgPosInfoctrl 对话框

class CDlgPosInfoctrl : public CDialog
{
	DECLARE_DYNAMIC(CDlgPosInfoctrl)

public:
	CDlgPosInfoctrl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPosInfoctrl();

// 对话框数据
    enum { IDD = IDD_DLG_POSINFO_CTRL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnSet();
    afx_msg void OnBnClickedBtnGet();
    LONG  m_lChannel;
    LONG  m_lUserID;
    int   m_iDeviceIndex;
    BOOL m_bEnable;
    BOOL m_bHat;
    BOOL m_bGlasses;
    BOOL m_bBackpack;
    BOOL m_bHair;
    BOOL m_bMask;
    BOOL m_bRide;
    BOOL m_bCarry;
    BOOL m_bPant;
    BOOL m_bSex;
    BOOL m_bSleeve;
    BOOL m_bHeight;
    BOOL m_bAge;
};
