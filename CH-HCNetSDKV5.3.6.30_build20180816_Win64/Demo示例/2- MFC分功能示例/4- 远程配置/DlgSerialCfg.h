#if !defined(AFX_DLGSERIALCFG_H__CCDCA7B3_FF8E_4965_83CC_CA70610F8BA3__INCLUDED_)
#define AFX_DLGSERIALCFG_H__CCDCA7B3_FF8E_4965_83CC_CA70610F8BA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSerialCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSerialCfg dialog

class CDlgSerialCfg : public CDialog
{
// Construction
public:
	CDlgSerialCfg(CWnd* pParent = NULL);   // standard constructor

	int	iChanShow;//
	int m_iChanNum;//设备通道数
	/*int m_iCurChanIndex;*/
	void GetRS485Cfg();
	void GetRS232Cfg();
	
	NET_DVR_DEVICEINFO_V30  DeviceInfo;
	NET_DVR_RS232CFG_V30 m_struRS232Cfg;
	NET_DVR_PTZCFG	m_struPtzCfg;		//云台解码器协议
	NET_DVR_DECODERCFG_V30	m_stru485DecoderCfg[MAX_CHANNUM_V30]; //485串口,云台解码器参数,不同通道的解码器参数可能不一样。要用数组存储多通道数据。

// Dialog Data
	//{{AFX_DATA(CDlgSerialCfg)
	enum { IDD = IDD_DIALOG_SERIAL_CFG };
	//CComboBox m_combo232Chan;
	CComboBox m_combo232Baud;
	CComboBox m_combo232DataBit;
	CComboBox m_combo232StopBit;
	CComboBox m_combo232CheckBit;
	CComboBox m_combo232Flow;
	CComboBox m_combo232OperateMode;
	CComboBox m_comboChannel;
	CComboBox m_combo485Baud;
	CComboBox m_combo485DataBit;
	CComboBox m_combo485StopBit;
	CComboBox m_combo485CheckBit;
	CComboBox m_combo485Flow;
	CComboBox m_combo485DecodeType;
	int m_iDecodeAddr;
	CComboBox m_combo485CfgCopy;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSerialCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSerialCfg)
	afx_msg void OnCbnSelchangeCombo485Channel();
	afx_msg void OnBnClickedBtn485Ok();
	afx_msg void OnCbnSelchangeCombo232OperateMode();
	afx_msg void OnBnClickedBtn232Ok();
	afx_msg void OnBnClickedBtn485Copy();
	afx_msg void OnBnClickedBtnPppSetup();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSERIALCFG_H__CCDCA7B3_FF8E_4965_83CC_CA70610F8BA3__INCLUDED_)
