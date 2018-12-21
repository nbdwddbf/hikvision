#if !defined(AFX_DLGNETWORKABILITY_H__3C387E8C_32DA_4391_9396_1DDCD4BBBC7D__INCLUDED_)
#define AFX_DLGNETWORKABILITY_H__3C387E8C_32DA_4391_9396_1DDCD4BBBC7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNetworkAbility.h : header file
//
#include "Markup.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgNetworkAbility dialog

#define MAX_INTERFACE_MODE          32
#define MAX_NETWORK_MODE            32
#define MAX_AUTHENTICATION_TYPE     32
#define MAX_WEP_KEY                 32



typedef struct tagSECURITY_WEP
{
    BYTE    byAuthenticationType[MAX_AUTHENTICATION_TYPE];
    BYTE    byWepKeyLength[MAX_WEP_KEY];
}SECURITY_WEP, *LPSECURITY_WEP;

typedef struct tagSERCURITY_WPA_PSK
{
    BYTE    byMaxLength;
    BYTE    byMiniLength;
    BYTE    byRes[2];
}SERCURITY_WPA_PSK, *LPSERCURITY_WPA_PSK;

typedef struct tagSECURITY_MODE
{
    SECURITY_WEP struWep;
    SERCURITY_WPA_PSK struWpaPsk;
}SECURITY_MODE, *LPSECURITY_MODE;

typedef struct tagWIRELESS_ABILITY_PARAM
{
    BYTE    byInterfaceMode[MAX_INTERFACE_MODE];
    BYTE    byNetworkMode[MAX_NETWORK_MODE];
    SECURITY_MODE   struSecurityMode;
}WIRELESS_ABILITY_PARAM, *LPWIRELESS_ABILITY_PARAM;

typedef struct tagNETWORK_ABILITY_PARAM
{
    WIRELESS_ABILITY_PARAM struWireless;
}NETWORK_ABILITY_PARAM, *LPNETWORK_ABILITY_PARAM;

class CDlgNetworkAbility : public CDialog
{
// Construction
public:
	CDlgNetworkAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNetworkAbility)
	enum { IDD = IDD_DLG_NETWORK_ABILITY };
	CListBox	m_listWEPKeylength;
	CListBox	m_listNetworkMode;
	CListBox	m_listInterfaceMode;
	CListBox	m_listAuthType;
	int		m_iWPAMax;
	int		m_iWPAMin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNetworkAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNetworkAbility)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    char*   m_pRecvBuf;
    LONG    m_lServerID;
    int     m_iDevIndex;

    NETWORK_ABILITY_PARAM m_struNetworkAbility;
public:
    BOOL GetNetworkAbility();
    void ParseStrIndex(CString strIndex, byte* array, int iArrayLength);
    BOOL ParseNetworkAbility(char *pBuf, DWORD dwBufSize);
    BOOL ParseNetworkSettingXml(CMarkup &struMarkup);
    BOOL ParseWirelessSettingXml(CMarkup &struMarkup);
    BOOL ParseInterfaceModeXml(CMarkup &struMarkup);
    BOOL ParseNetworkModeXml(CMarkup &struMarkup);
    BOOL ParseSecurityModeXml(CMarkup &struMarkup);
    BOOL ParseSecurityNoneXml(CMarkup &struMarkup);
    BOOL ParseSecurityWEPXml(CMarkup &struMarkup);
    BOOL ParseSecurityWPAPSKXml(CMarkup &struMarkup);

    void SetNetworkAbilityToWnd(NETWORK_ABILITY_PARAM &struNetworkAbility);
    void SetWirelessToWnd(WIRELESS_ABILITY_PARAM &struWireless);
    void SetSecurityModeToWnd(SECURITY_MODE &struSecurity);
    void SetWEPToWnd(SECURITY_WEP &struWep);
    void SetWAPPSKToWnd(SERCURITY_WPA_PSK &struWpaPsk);

    BOOL WirteBufToFile(char *pBuf, DWORD dwBufSize);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNETWORKABILITY_H__3C387E8C_32DA_4391_9396_1DDCD4BBBC7D__INCLUDED_)
