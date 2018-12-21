#if !defined(AFX_DLGIPCSPECLALEX_H__3DA03C07_E37D_4191_BFDE_0F56ED83755A__INCLUDED_)
#define AFX_DLGIPCSPECLALEX_H__3DA03C07_E37D_4191_BFDE_0F56ED83755A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIPCSpeclalEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIPCSpeclalEx dialog

class CDlgIPCSpeclalEx : public CDialog
{
	// Construction
public:
	CDlgIPCSpeclalEx(CWnd* pParent = NULL);   // standard constructor
	
	//设备相关参数
	LONG    m_lLoginID;
	int     m_iDeviceIndex;
	LONG    m_lChannel;
	
	LONG	m_lPlayHandle;
	
	int		m_iChanCount;
	int		m_iAnaChanCount;
	int     m_iDStartChannel;
	LONG	m_lStartChannel;
	
	NET_DVR_AUDIOOUT_VOLUME m_struAudioVol;
	
	// Dialog Data
	//{{AFX_DATA(CDlgIPCSpeclalEx)
	enum { IDD = IDD_DLG_IPC_SPECIALEX };
	int		m_iAudioVol;
	DWORD	m_dwTerminalNo;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIPCSpeclalEx)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CDlgIPCSpeclalEx)
	afx_msg void OnBtnGetAudioVol();
	afx_msg void OnBtnSetAudioVol();
	afx_msg void OnBtnPdc();
	afx_msg void OnBtnHeatmap();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIPCSPECLALEX_H__3DA03C07_E37D_4191_BFDE_0F56ED83755A__INCLUDED_)
