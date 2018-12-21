#pragma once


// CDlgAsynloginWait 对话框

class CDlgAsynloginWait : public CDialog
{
	DECLARE_DYNAMIC(CDlgAsynloginWait)

public:
	CDlgAsynloginWait(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAsynloginWait();

// 对话框数据
	enum { IDD = IDD_DIG_ASYNLOGIN_WAIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
