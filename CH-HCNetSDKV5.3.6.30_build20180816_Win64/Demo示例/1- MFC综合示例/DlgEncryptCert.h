#include "afxwin.h"
#include "kmssrvlib_ca.h"
#include "afxcmn.h"
#if !defined(AFX_DLGENCRYPTCERT_H__3A515A95_B052_4ACC_899E_26B23F214939__INCLUDED_)
#define AFX_DLGENCRYPTCERT_H__3A515A95_B052_4ACC_899E_26B23F214939__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEncryptCert.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEncryptCert dialog

class CDlgEncryptCert : public CDialog
{
// Construction
public:
	CDlgEncryptCert(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEncryptCert)
	enum { IDD = IDD_DLG_ENCRYPT_CERT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEncryptCert)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEncryptCert)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	CComboBox m_Com_Algorithm;
	CComboBox m_cmbAlgorithm;
	CComboBox m_cmbCertSaveLocation;
	CComboBox m_cmbModelLen;
	CString m_szChipID;
	CString m_szDevID;
	CString m_szCARootCert;
	CString m_szEncryptCert;
	CString m_szPulbicKey;
	UINT m_dwPublicKeyLen;
	CString m_szScertKeyPair;
	CString m_szSignCert;
	afx_msg void OnBnClickedBtnGetDeviceInfo();
	afx_msg void OnBnClickedBtnExit();
	virtual BOOL OnInitDialog();
public:
   	LONG    m_lUSerID;
    LONG    m_lChannel;
	afx_msg void OnBnClickedBtnGetCaRootCert();
	afx_msg void OnBnClickedBtnUploadCaRootCert();
	afx_msg void OnBnClickedBtnGetSigncert();
	afx_msg void OnBnClickedBtnUploadSigncert();
	afx_msg void OnBnClickedBtnGetEncryptCert();
	afx_msg void OnBnClickedBtnUploadEncryptCert();
    DWORD m_dwScertKeyPairLen;
    DWORD m_dwEncryptCertLen;
    DWORD m_dwCARootCertLen;
    DWORD m_dwSignCertLen;
    ECCrefPublicKey m_struPublicKey;
    char  m_ScertKeyPair[1024];
    DWORD m_dwCAPort;
    afx_msg void OnBnClickedBtnInitChip();
    CIPAddressCtrl m_ConCAIP;
    int InitCA();
    int GetUploadCARootCert();
    int GetUploadSignCert();
    int GetUploadEncryptCert();
	typedef int(*CALIB_CA_Init)(const char *IP_CA, int Port_CA);
	typedef int(*CALIB_CA_GetRootCert)(unsigned char *ucRootCert, unsigned int *uiRootCertLen);
	typedef	int (*CALIB_CA_GenUserCert)(int iReqType, int iAlgFlag, int iModLen, int iPriType,
		unsigned char *ucPubKey, unsigned int uiPubKeyLen,
		unsigned char *ucCertReqInfo, unsigned int uiCertReqInfoLen,
		unsigned char *ucUserCert, unsigned int *uiUserCertLen,
		unsigned char *ucUserKey, unsigned int *uiUserKeyLen);
		CALIB_CA_Init               m_fnCAInit;
		CALIB_CA_GetRootCert        m_fnCAGetRootCert;
		CALIB_CA_GenUserCert        m_fnCAGenUserCert;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGENCRYPTCERT_H__3A515A95_B052_4ACC_899E_26B23F214939__INCLUDED_)
