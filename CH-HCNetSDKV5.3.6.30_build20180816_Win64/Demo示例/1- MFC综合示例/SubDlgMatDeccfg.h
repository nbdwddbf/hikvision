#if !defined(AFX_MATDECCFG_H__33BDD95C_A9E9_4AA5_9733_C79E223B70B9__INCLUDED_)
#define AFX_MATDECCFG_H__33BDD95C_A9E9_4AA5_9733_C79E223B70B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatDecCFG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatDecCFG dialog
#include <vector>
class CMatDecCFG : public CDialog
{
// Construction
public:
	CMatDecCFG(CWnd* pParent = NULL);   // standard constructor
	int		m_iChannelnumber;
	LONG	m_lServerID;
	LONG	m_lStartChan;
	void CurCfgUpdate();
	NET_DVR_MATRIX_DECCHAN_CONTROL m_struDecChanCtrl[64];
	DWORD m_dwDecSwitch[64];
	LONG	m_lDecoderStartNum;
// Dialog Data
	//{{AFX_DATA(CMatDecCFG)
	enum { IDD = IDD_SUB_DLG_MAT_DEC_CFG };
	CComboBox	m_DecodeDelayCtrl;
	CComboBox	m_ScaleStatusCtrl;
	CComboBox	m_DecodeChanCtrl;
	CComboBox	m_SwitchCombo;
	CComboBox	m_DecChanCombo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatDecCFG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMatDecCFG)
	afx_msg void OnBtnCenterSet();
	afx_msg void OnButcolumnset();
	afx_msg void OnButmanplay();
	afx_msg void OnButrowset();
	afx_msg void OnButtransset();
	virtual BOOL OnInitDialog();
	afx_msg void OnDispchancfg();
	afx_msg void OnButdynamictest();
	afx_msg void OnButcyclink();
	afx_msg void OnButtonget();
	afx_msg void OnButtonset();
	afx_msg void OnButremoteplayback();
	afx_msg void OnPassivedecode();
	afx_msg void OnDispchan();
	afx_msg void OnUploadlogo();
	afx_msg void OnButtonDecoderstatus();
	afx_msg void OnButtongetscalestatus();
	afx_msg void OnButtonsetscalestatus();
	afx_msg void OnSelchangeCombodecchan();
	afx_msg void OnSelchangeCombodecodechan();
	afx_msg void OnBtnVideocfg();
	afx_msg void OnBtnCodespitter();
	afx_msg void OnBtnBigscreensplice();
	afx_msg void OnBtnDecoderability();
	afx_msg void OnBtnWall();
	afx_msg void OnBtnJointChan();
	afx_msg void OnBtnTransDev();
	afx_msg void OnBtnLcd();
	afx_msg void OnButSdiSet();
	afx_msg void OnButMatdecCodesplitter();
	afx_msg void OnButSensorCfg();
	afx_msg void OnButIpViewCfg();
	afx_msg void OnButAudioUpdown();
	afx_msg void OnButSubSysMutilNetcard();
	afx_msg void OnButLcdScreenServer();
	afx_msg void OnBtnUniformInterface();
	afx_msg void OnButMatdecMerge();
	afx_msg void OnButFiberRingCfg();
	afx_msg void OnButDecChanControl();
	afx_msg void OnBtnModifyrecordTest();
	afx_msg void OnButMatdecFibre();
	afx_msg void OnButMatdecMcu();
	afx_msg void OnButtonDecorder();
	afx_msg void OnBtnLedScreen();

	afx_msg void OnBtnInteractiveCtrl();
	afx_msg void OnBtnInfoServer();

	afx_msg void OnBtnC10s21();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	std::vector<DWORD> m_Switch;

public:
    afx_msg void OnBnClickedBtnAlarmhostDong();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATDECCFG_H__33BDD95C_A9E9_4AA5_9733_C79E223B70B9__INCLUDED_)
