#if !defined(AFX_DLGSCREENCTRL_H__684AF421_54C0_4C49_A411_3A6077E77016__INCLUDED_)
#define AFX_DLGSCREENCTRL_H__684AF421_54C0_4C49_A411_3A6077E77016__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgScreenCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgScreenCtrl dialog

class CDlgScreenCtrl : public CDialog
{
// Construction
public:
	CDlgScreenCtrl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgScreenCtrl)
	enum { IDD = IDD_DLG_SCREEN_CTRL };
	CComboBox	m_cmbSerialProto;
	CComboBox	m_cmbAreaZoomY;
	CComboBox	m_cmbAreaZoomX;
	CComboBox	m_cmbAreaZoomWidth;
	CComboBox	m_cmbAreaZoomHeight;
	CComboBox	m_cmbAreaZoomCmd;
	CComboBox	m_cmbScreenCtrlY;
	CComboBox	m_cmbHeight;
	CComboBox	m_cmbWidth;
	CComboBox	m_cmbScreenCtrlX;
	CComboBox	m_comboInterface;
	CComboBox	m_comboCommand;
	BYTE	m_byWallNo;
	DWORD	m_dwHeight;
	DWORD	m_dwWidth;
	DWORD	m_dwX;
	DWORD	m_dwY;
	DWORD	m_dwAreaZoomH;
	DWORD	m_dwAreaZoomW;
	DWORD	m_dwAreaZoomX;
	DWORD	m_dwAreaZoomY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgScreenCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgScreenCtrl)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboCommand();
	afx_msg void OnBtnOperate();
	afx_msg void OnBtnBrightnessDec();
	afx_msg void OnBtnBrightnessInc();
	afx_msg void OnBtnSaturationDec();
	afx_msg void OnBtnSaturationInc();
	afx_msg void OnBtnContrastDec();
	afx_msg void OnBtnContrastInc();
	afx_msg void OnBtnHueDec();
	afx_msg void OnBtnHueInc();
	afx_msg void OnBtnHrozontalLeft();
	afx_msg void OnBtnHrozontalRight();
	afx_msg void OnBtnVeticalUp();
	afx_msg void OnBtnVeticalDown();
	afx_msg void OnBtnPowerOn();
	afx_msg void OnBtnPowerOff();
	afx_msg void OnBtnSignal();
	afx_msg void OnBtnMenu();
	afx_msg void OnBtnInfo();
	afx_msg void OnBtnReturn();
	afx_msg void OnBtnUp();
	afx_msg void OnBtnDown();
	afx_msg void OnBtnLeft();
	afx_msg void OnBtnRight();
	afx_msg void OnBtnOk();
	afx_msg void OnBtnZero();
	afx_msg void OnBtnOne();
	afx_msg void OnBtnTwo();
	afx_msg void OnBtnThree();
	afx_msg void OnBtnFour();
	afx_msg void OnBtnFive();
	afx_msg void OnBtnSix();
	afx_msg void OnBtnSeven();
	afx_msg void OnBtnEight();
	afx_msg void OnBtnNine();
	afx_msg void OnBtnEnable();
	afx_msg void OnBtnDisable();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
    int m_iDeviceIndex;
    int m_iCommandSel;
    NET_DVR_SCREEN_CONTROL_V41 m_struScreenCtrl;

private:
    void SendCommand();
    void UpdateBasicInfo();
    void ClearCtrlParam();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSCREENCTRL_H__684AF421_54C0_4C49_A411_3A6077E77016__INCLUDED_)
