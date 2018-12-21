// DlgDeviceLanguageEncode.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgDeviceLanguageEncode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceLanguageEncode dialog


CDlgDeviceLanguageEncode::CDlgDeviceLanguageEncode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDeviceLanguageEncode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDeviceLanguageEncode)
	m_strEncodeFormat = _T("");
	m_iDeviceIndex = -1;
	m_lChannel = -1;
	m_lLoginID = -1;
	//}}AFX_DATA_INIT
}


void CDlgDeviceLanguageEncode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDeviceLanguageEncode)
	DDX_Text(pDX, IDC_EDIT_DEVICE_LANGUAGE_ENCODE, m_strEncodeFormat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDeviceLanguageEncode, CDialog)
	//{{AFX_MSG_MAP(CDlgDeviceLanguageEncode)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceLanguageEncode message handlers

void CDlgDeviceLanguageEncode::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_DEVICE_LAN_ENCODE struEncode = {0};
	DWORD dwRet = 0;
	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_DEVICE_LAN_ENCODE, 0, &struEncode, sizeof(struEncode), &dwRet))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DEVICE_LAN_ENCODE");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_DEVICE_LAN_ENCODE");
	}
	m_strEncodeFormat = struEncode.byLanEncode;
	UpdateData(FALSE);
}

BOOL CDlgDeviceLanguageEncode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
