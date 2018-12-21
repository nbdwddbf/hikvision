#if !defined(AFX_DLGAUDIOINVOLUMECFG1_H__751BC0CA_E8AE_4A0E_B0C7_42E497C1C9B8__INCLUDED_)
#define AFX_DLGAUDIOINVOLUMECFG1_H__751BC0CA_E8AE_4A0E_B0C7_42E497C1C9B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAudioInVolumeCfg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioInVolumeCfg dialog

class CDlgAudioInVolumeCfg : public CDialog
{
// Construction
public:
	CDlgAudioInVolumeCfg(CWnd* pParent = NULL);   // standard constructor

	LONG    m_lUserID;
    LONG    m_lChannel;
	DWORD   m_dwDevIndex;
    DWORD   m_dwLastIndex;

// Dialog Data
	//{{AFX_DATA(CDlgAudioInVolumeCfg)
	enum { IDD = IDD_DLG_AUDIOIN_VOLUME_CFG };
	CComboBox	m_cmbAudioOutType;
	CComboBox	m_cmbAudioInChan;
	CSliderCtrl	m_sliderVolume;
	CString	m_csVolume;
	BOOL	m_bEnableFBC;
	BOOL	m_bEnableAEC;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAudioInVolumeCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAudioInVolumeCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnCustomdrawSliderVolume(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeCmbAudiooutType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    NET_DVR_VOLUME_CFG m_struVolumeCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAUDIOINVOLUMECFG1_H__751BC0CA_E8AE_4A0E_B0C7_42E497C1C9B8__INCLUDED_)
