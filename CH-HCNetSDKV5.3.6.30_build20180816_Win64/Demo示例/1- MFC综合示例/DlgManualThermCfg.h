#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "VcaCommonOperations.h"
#include "afxwin.h"
#include "atltime.h"
#include "afxcmn.h"


// CDlgManualThermCfg 对话框

class CDlgManualThermCfg : public CDialogEx, public CVcaCommonOperations
{
	DECLARE_DYNAMIC(CDlgManualThermCfg)

public:
	CDlgManualThermCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgManualThermCfg();

// 对话框数据
    enum { IDD = IDD_DLG_MANUALTHERM_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonGetCruise();
    afx_msg void OnBnClickedButtonGetTempHumi();
    afx_msg void OnBnClickedButtonGetManualthermInfo();
    afx_msg void OnBnClickedButtonSetManualthermInfo();
    afx_msg LRESULT OnMsgAddManualThermInfoToList(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMsgManualThermInfoFinish(WPARAM wParam, LPARAM lParam);

    virtual BOOL OnInitDialog();
    void DrawRgnFun(HDC hdc);
    void ProcessGetManualThermInfoCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
    void SaveParam();

    CComboBox m_comboCruiseMode;
    CTime m_ctCurrentDate;
    CTime m_ctCurrentTime;
    float m_fHumidity;
    int m_iRuleID;
    float m_fTemperture;
    CListCtrl m_listManualThermInfo;
    CRect   m_rcPlayWnd;
    NET_VCA_POLYGON m_struPolyGon;
    NET_VCA_LINE m_struLine;
    BOOL    m_bDrawEnd;
    int     m_nDrawPointNum;
    NET_SDK_MANUAL_THERMOMETRY m_struManualThermometry;

public:
    LONG    m_lManualThremInfoHandle;
    CComboBox m_comboBox;
    CEdit m_editTextBox;
    BOOL m_bSelectItem;
    int m_iRowCount;
    int m_iItem;
    int m_iSubItem;
    int m_iLastItem;
    afx_msg void OnNMClickListManualthermInfo(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMDblclkListManualthermInfo(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnEnKillfocusEditTextBox();
    afx_msg void OnCbnKillfocusComboBox();
    afx_msg void OnBnClickedButtonAdd();
    afx_msg void OnBnClickedButtonDelete();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    int m_iDistance;
    float m_fEmissivity;
    afx_msg void OnBnClickedButtonGetManualthermBasic();
    afx_msg void OnBnClickedButtonSetManualthermBasic();
    afx_msg void OnBnClickedButtonDeleteRule();
};


