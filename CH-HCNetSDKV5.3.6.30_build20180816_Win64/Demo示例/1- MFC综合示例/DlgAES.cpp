// DlgAES.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAES.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAES dialog


CDlgAES::CDlgAES(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAES::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAES)
	m_csKey = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAES::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAES)
	DDX_Control(pDX, IDC_COMBO_STATE, m_comboState);
	DDX_Text(pDX, IDC_EDIT_DEVICE_KEY, m_csKey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAES, CDialog)
	//{{AFX_MSG_MAP(CDlgAES)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_KEY, OnButtonUpdateKey)
	ON_BN_CLICKED(IDC_BUTTON_SET_SDK_KEY, OnButtonSetSdkKey)
	ON_BN_CLICKED(IDC_BUTTON_SET_STATE, OnButtonSetState)
	ON_BN_CLICKED(IDC_BUTTON_GET_STATE, OnButtonGetState)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BTN_SET_CODE_KEY, OnBtnSetCodeKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAES message handlers

void CDlgAES::OnButtonUpdateKey() 
{
	NET_DVR_AES_KEY_INFO strAes = {0};
	DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lUSerID, NET_DVR_GET_AES_KEY, 0xffffffff, &strAes, sizeof(strAes), &dwReturn))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_AES_KEY");
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_AES_KEY");
		m_csKey.Format("%s", strAes.sAESKey);

		UpdateData(FALSE);
	}
}

void CDlgAES::OnButtonSetSdkKey() 
{
	UpdateData(TRUE);
	memcpy(g_sSecretKey, m_csKey, sizeof(g_sSecretKey));
	
	//ÉèÖÃsdkÄÚ²¿½âÂëÃÜÔ¿
	NET_DVR_SetSDKSecretKey(m_lUSerID, g_sSecretKey);
}

void CDlgAES::OnButtonSetState() 
{
    if (!NET_DVR_InquestStreamEncrypt(m_lUSerID, 0xffffffff, m_comboState.GetCurSel()))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_InquestStreamEncrypt");
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_InquestStreamEncrypt");
	}
}

BOOL CDlgAES::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_comboState.SetCurSel(0);

	OnButtonGetState();
	OnButtonUpdateKey(); 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAES::OnButtonGetState() 
{
	BOOL bState = FALSE;

    if (!NET_DVR_InquestGetEncryptState(m_lUSerID, 0xffffffff, &bState))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_InquestGetEncryptState");
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_InquestGetEncryptState");
		m_comboState.SetCurSel(bState);
	}
}

void CDlgAES::OnButtonExit() 
{
	CDialog::OnCancel();
}

void CDlgAES::OnBtnSetCodeKey() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	char szLan[128] = {0};
	NET_DVR_INQUEST_SECRET_INFO strSecretInfo = {0};
	
    memcpy(strSecretInfo.sSecretKey, m_csKey, 16);
	if(!NET_DVR_InquestSetSecretKey(m_lUSerID, &strSecretInfo))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_InquestSetSecretKey");
		g_StringLanType(szLan, "ÉèÖÃÂëÁ÷¼ÓÃÜÃÜÔ¿Ê§°Ü", "Set stream encrypt secret key failed!");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_InquestSetSecretKey");
	}
}
