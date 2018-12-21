#if !defined(AFX_DLGAREAMONITORCFG_H__D692C9BB_9C86_4E0B_922A_77796E59C237__INCLUDED_)
#define AFX_DLGAREAMONITORCFG_H__D692C9BB_9C86_4E0B_922A_77796E59C237__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAreaMonitorCfg.h : header file
//

#include "./xml/XmlBase.h"
#include "XMLParamsConvert.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgAreaMonitorCfg dialog

typedef enum
{
	INTERFACE_STD_GET		= 0,
	INTERFACE_STD_SET		= 1,
	INTERFACE_STD_CTRL		= 2,
	INTERFACE_REMOTE_CONFIG =3

};
class CDlgAreaMonitorCfg : public CDialog
{
// Construction
public:
	CDlgAreaMonitorCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAreaMonitorCfg)
	enum { IDD = IDD_DLG_AREAMONITOR };
	CComboBox	m_cmbType;
	CString	m_csInputCond;
	CString	m_csConfigParam;
	CString	m_csLastError;
	CString	m_csReturnValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAreaMonitorCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAreaMonitorCfg)
	afx_msg void OnBtnSet();
	afx_msg void OnBtnProcess();
	afx_msg void OnSelchangeCmbCfgType();
	afx_msg void OnBtnDetect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG m_lUserID;
    int m_iDevIndex;
protected:
    char m_szStatusBuf[ISAPI_STATUS_LEN];
	char	*m_pOutBuf;
	DWORD	m_dwCfgType;
public:
	//void	ParseAbility();
	//void	ParseSimpleAbility(CXmlBase &xmlAll, char* szAbilityName);
	//void	ParseAbilityRecursive(CXmlBase &xmlAll, CXmlBase &xmlDev);
	BOOL    ParseAreaMonitorCond(NET_DVR_AREA_MONITOR_COND* pStruCond);
	BOOL    ConvertSingleNodeData(void *pStructVale, CXmlBase &struXml, const char* pNodeName, BYTE byDataType, DWORD nArrayLen = 0);
	BOOL	ConvertSingleNodeStringData(void *pStructVale, CXmlBase &struXml, const char* pNodeName, BYTE byDataType);
	BOOL    ParseSetAreaMonitorCond(DWORD* pData);
	BOOL    ParseSetAreaMonitorParam();
	BOOL    ParseGetStorageResourceCond(NET_DVR_STORAGE_RESOURCE_COND* pData);
	BOOL    ParseGetBlackListGroupInfoCond(NET_DVR_BLACKLIST_GROUP_COND* pData);
	BOOL    LoadRetrievalSnapRecordPicData(DWORD* dwAllDataLen, char* &pAllData);
	BOOL    LoadDetectImagePicData(DWORD* dwAllDataLen, char* &pAllData);
	DWORD  m_dwInterfaceType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAREAMONITORCFG_H__D692C9BB_9C86_4E0B_922A_77796E59C237__INCLUDED_)
