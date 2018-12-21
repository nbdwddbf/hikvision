#if !defined(AFX_DLGCOMPRESSIONV30_H__BDEF4F43_AA8A_4D03_9854_D13C1032DF93__INCLUDED_)
#define AFX_DLGCOMPRESSIONV30_H__BDEF4F43_AA8A_4D03_9854_D13C1032DF93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCompressionV30.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCompressionV30 dialog

class CDlgCompressionV30 : public CDialog
{
// Construction
public:
	CDlgCompressionV30(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCompressionV30)
	enum { IDD = IDD_DLG_TEST_COMPRESSION_V30 };
	CComboBox	m_comboAudioBitRate3;
	CComboBox	m_comboAudioBitRate2;
	CComboBox	m_comboAudioType3;
	CComboBox	m_comboAudioType2;
	CComboBox	m_comboAudioBitRate;
	CComboBox	m_comboAudioType;
	BOOL	m_bEventSvcChk;
	BOOL	m_bMainSvcChk;
	BOOL	m_bSubSvcChk;
	int		m_iMainStreamSmooth;
	int		m_iSubStreamSmooth;
	int		m_iEventStreamSmooth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCompressionV30)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCompressionV30)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG    m_lLoginID;
	int     m_iDeviceIndex;
	LONG    m_lChannel;
	NET_DVR_COMPRESSIONCFG_V30 m_struCompressionCfgV30;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOMPRESSIONV30_H__BDEF4F43_AA8A_4D03_9854_D13C1032DF93__INCLUDED_)
