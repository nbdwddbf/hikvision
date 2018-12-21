#pragma once


// CDlgCaptureFace 对话框

class CDlgCaptureFace : public CDialog
{
	DECLARE_DYNAMIC(CDlgCaptureFace)

public:
	CDlgCaptureFace(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCaptureFace();

// 对话框数据
	enum { IDD = IDD_DLG_CAPTURE_FACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnGetFace();
    afx_msg LRESULT OnMsgCaptureFaceFinish(WPARAM wParam, LPARAM lParam);
    int m_iDevIndex;
    long m_lServerID;
    LONG m_lRemoteHandle;
    int m_iFaceQuality;
    int m_iFaceQuality2;
};
