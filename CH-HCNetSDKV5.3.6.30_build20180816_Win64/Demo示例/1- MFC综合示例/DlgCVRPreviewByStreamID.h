#pragma once
#include "afxcmn.h"

typedef struct tagSTREAMID_PREVIEWINFO
{
    BYTE byStatus;
    BYTE bSound;
    BYTE byRes[254];
    NET_DVR_PREVIEWINFO struPreviewInfo;
}STREAMID_PREVIEWINFO, *LPSTREAMID_PREVIEWINFO;

// CDlgCVRPreviewByStreamID 对话框

class CDlgCVRPreviewByStreamID : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCVRPreviewByStreamID)

public:
	CDlgCVRPreviewByStreamID(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCVRPreviewByStreamID();

// 对话框数据
	enum { IDD = IDD_DLG_CVR_PREVIEW_BY_STREAMID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
    void CreateTree(void);
    void GetStreamSrc();
    void PlayStreamID(int iTreeIndex, int iWinIndex);
    LONG    m_hLongCfgHandle;
    CTreeCtrl m_treeStreamIDList;
    LONG    m_lServerID;
    int     m_iDevIndex;
    CString m_strStreamID;
    LONG    m_szlPlayHandle[4];
    int     m_iWinIndex;
    CRect   m_rcPlayWnd1;
    CRect   m_rcPlayWnd2;
    CRect   m_rcPlayWnd3;
    CRect   m_rcPlayWnd4;
    afx_msg void OnNMDblclkTreeStreamId(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMClickTreeStreamId(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnClose();
};
