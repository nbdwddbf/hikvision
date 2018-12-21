#pragma once
#include "afxwin.h"


// CDLGTrialAudioMix 对话框

class CDLGTrialAudioMix : public CDialogEx
{
	DECLARE_DYNAMIC(CDLGTrialAudioMix)

public:
	CDLGTrialAudioMix(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDLGTrialAudioMix();

// 对话框数据
	enum { IDD = IDD_DLG_TRIAL_AUTIO_MIX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnGetSingleAudiomixcfg();
    LONG    m_lUserID;
    LONG    m_lChannel;
    DWORD   m_dwDevIndex;
    CComboBox m_AudioMixID;

    afx_msg void OnBnClickedBtnSetSingleAudiomixcfg();
    CString m_AudioMixInfo;
    afx_msg void OnBnClickedBtnGetAudiomixcfg();
    afx_msg void OnBnClickedBtnSetAudiomixcfg();
    CComboBox m_SerialPortID;
    afx_msg void OnBnClickedBtnGetSingleSerialportCfg();
    afx_msg void OnBnClickedBtnSetSingleSerialportCfg();
    afx_msg void OnBnClickedBtnGetSerialportCfg();
    afx_msg void OnBnClickedBtnSetSerialportCfg();
};
