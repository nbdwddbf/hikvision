#pragma once
#include "afxcmn.h"
#include "DlgPlayLocalFile.h"
#include "DlgPlayRemoteFile.h"
#include "DlgPlayRemoteTime.h"
#include "DlgPlayEvent.h"
#include "DlgPlayMotion.h"
#include "DlgPlayLockFile.h"//2011-8-23
#include "DlgPlayDvrRecord.h"//2011-8-25

#include "JPEGPicDownload.h"
#include "DlgRecordLabel.h"
#include "DlgSmartSearchPicture.h"
#include "DlgPlayRemoteFileMedical.h"
// CDlgPlayBack dialog

class CDlgPlayBack : public CDialog
{
	DECLARE_DYNAMIC(CDlgPlayBack)

public:
	CDlgPlayBack(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPlayBack();

// Dialog Data


public:
	//{{AFX_DATA(CDlgPlayBack)
	enum { IDD = IDD_DLG_PLAY_BACK };
	CTabCtrl m_tabPlayBack;
	//}}AFX_DATA
	
	
	//{{AFX_VIRTUAL(CDlgPlayBack)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPlayBack)
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTabPlayBack(NMHDR *pNMHDR, LRESULT *pResult);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	CDlgPlayEvent	m_dlgPlayEvent;//2009-07-30
	
	CDlgPlayRemoteTime	m_dlgPlayRemoteTime;
	CDlgPlayRemoteFile m_dlgPlayRemoteFile;
	CDlgPlayLocalFile m_dlgPlayLocalFile;
    CDlgPlayMotion      m_dlgPlayMotion;

	CJPEGPicDownload  m_dlgJpegPicDownload;
    CDlgRecordLabel     m_dlgRecordLabel;
	CDlgPlayLockFile m_dlgPlayLockFile;//2011-8-23
	CDlgPlayDvrRecord m_dlgPlayDvrRecord;//2011-8-25
	CDlgSmartSearchPicture m_dlgSmartSearchPic;

	int m_iPlayBackType;//playback type
	
	void PlayBackWinUpdate();
	void FinishAll();
	void HideAll();
    
};
