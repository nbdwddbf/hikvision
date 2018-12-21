#pragma once
#include "afxwin.h"
#include "DlgPPPCfg.h"

// CSubDlgSerialCfg dialog

class CSubDlgSerialCfg : public CDialog
{
	DECLARE_DYNAMIC(CSubDlgSerialCfg)

public:
	CSubDlgSerialCfg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgSerialCfg();

// Dialog Data
	

protected:
	BOOL CheckInitParam();

public:


	//{{AFX_DATA(CSubDlgSerialCfg)
	enum { IDD = IDD_SUB_DLG_SERIAL_CFG };
	CComboBox	m_cmbPortRS485;
	CComboBox	m_combo232Chan;
	CComboBox m_combo232Baud;
	CComboBox m_combo232CheckBit;
	CComboBox m_combo232DataBit;
	CComboBox m_combo232StopBit;
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
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CSubDlgSerialCfg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CSubDlgSerialCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo232OperateMode();
	afx_msg void OnBnClickedBtnTransparentTransport();
	afx_msg void OnBnClickedBtnPppSetup();
	afx_msg void OnCbnSelchangeCombo485Channel();
	afx_msg void OnBnClickedBtn485Ok();
	afx_msg void OnBnClickedBtn485Copy();
	afx_msg void OnBnClickedBtn232Ok();
	afx_msg void OnEditchangeCombo232Channel();
	afx_msg void OnSelchangeCombo232Channel();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	int	m_iChanCount;//device preview channel number
	LONG	m_lLoginID;
	LONG	m_lStartChannel;//NET_DVR_DECODERCFG
	NET_DVR_DECODERCFG_V40*	m_pStru485DecoderCfg; //485 port PTZ parameter
	int *m_pi485ChannelNO; 
	NET_DVR_RS232CFG_V30	m_struRS232Cfg;		//232 port parameter
	NET_DVR_PTZCFG	m_struPtzCfg;		//PTZ
	BOOL m_bGet232Serial;
	BOOL *m_pbGet485Serial;	
	BOOL *m_pbSet485Serial;
	BOOL m_bSetSerial232;
	int m_iCurChanIndex;
	int m_iCopyChanIndex;
	int m_iChanShowNum;//display channel number(usually start from 1)
	LONG m_lSerial;
	int m_iDeviceIndex;
	int m_iSel232;
	void CurCfgUpdate();
	BOOL CfgSetup();
private:
    void SetRS485SerialInfo();
    BOOL m_bTrialDev;
    NET_DVR_TRIAL_SYSTEM_INFO m_struSysInfo ;
};
