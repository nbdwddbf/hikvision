// DlgSnmpCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSnmpCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSnmpCfg dialog


CDlgSnmpCfg::CDlgSnmpCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSnmpCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSnmpCfg)
	m_csReadCommunity = _T("");
	m_iSnmpPort = 0;
	m_csTrapHostIP = _T("");
	m_csWriteCommunity = _T("");
	m_iTrapHostPort = 0;
	m_strAuthPWRO = _T("");
	m_strAuthPWRW = _T("");
	m_iAuthTypeRO = 0;
	m_iAuthTypeRW = 0;
	m_strPrivPWRO = _T("");
	m_strPrivPWRW = _T("");
	m_iSecLevelRO = 0;
	m_iSecLevelRW = 0;
	m_strUserNameRO = _T("");
	m_strUserNameRW = _T("");
	m_bSnmpV1 = FALSE;
	m_bSnmpV2 = FALSE;
	m_bSnmpV3 = FALSE;
	m_iPrivateTypeRO = 0;
	m_iPrivateTypeRW = 0;
	m_csTrapName = _T("");
	//}}AFX_DATA_INIT
    memset(&m_struSnmpCfg, 0, sizeof(m_struSnmpCfg));
}


void CDlgSnmpCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSnmpCfg)
	DDX_Text(pDX, IDC_EDIT_READ_COMMUNITY, m_csReadCommunity);
	DDX_Text(pDX, IDC_EDIT_SNMP_PORT, m_iSnmpPort);
	DDX_Text(pDX, IDC_EDIT_TRAP_HOST_IP, m_csTrapHostIP);
	DDX_Text(pDX, IDC_EDIT_WRITE_COMMUNITY, m_csWriteCommunity);
	DDX_Text(pDX, IDC_EDIT_TRAP_HOST_PORT, m_iTrapHostPort);
	DDX_Text(pDX, IDC_EDIT_AUTH_PASSWD_RO, m_strAuthPWRO);
	DDX_Text(pDX, IDC_EDIT_AUTH_PASSWD_RW, m_strAuthPWRW);
	DDX_Text(pDX, IDC_EDIT_AUTH_TYPE_RO, m_iAuthTypeRO);
	DDX_Text(pDX, IDC_EDIT_AUTH_TYPE_RW, m_iAuthTypeRW);
	DDX_Text(pDX, IDC_EDIT_PRIV_PASSWD_RO, m_strPrivPWRO);
	DDX_Text(pDX, IDC_EDIT_PRIV_PASSWD_RW, m_strPrivPWRW);
	DDX_Text(pDX, IDC_EDIT_SEC_LEVEL_RO, m_iSecLevelRO);
	DDX_Text(pDX, IDC_EDIT_SEC_LEVEL_RW, m_iSecLevelRW);
	DDX_Text(pDX, IDC_EDIT_USERNAME_RO, m_strUserNameRO);
	DDX_Text(pDX, IDC_EDIT_USERNAME_RW, m_strUserNameRW);
	DDX_Check(pDX, IDC_CHK_ENABLE_V1, m_bSnmpV1);
	DDX_Check(pDX, IDC_CHK_ENABLE_V2, m_bSnmpV2);
	DDX_Check(pDX, IDC_CHK_ENABLE_V3, m_bSnmpV3);
	DDX_Text(pDX, IDC_EDIT_PRIVATE_TYPE_RO, m_iPrivateTypeRO);
	DDX_Text(pDX, IDC_EDIT_PRIVATE_TYPE_RW, m_iPrivateTypeRW);
	DDX_Text(pDX, IDC_EDIT_TRAP_HOST_NAME, m_csTrapName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSnmpCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgSnmpCfg)
	ON_BN_CLICKED(IDC_BTN_SET_SNMP, OnBtnSetSnmp)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSnmpCfg message handlers

BOOL CDlgSnmpCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	OnButtonUpdate();

	return TRUE; 
}

void CDlgSnmpCfg::OnBtnSetSnmp() 
{
    UpdateData(TRUE);
    m_struSnmpCfg.byEnableV1 = m_bSnmpV1;
	m_struSnmpCfg.byEnableV2 = m_bSnmpV2;
	m_struSnmpCfg.byEnableV3 = m_bSnmpV3;
    m_struSnmpCfg.wServerPort = m_iSnmpPort;
    strncpy((char*)m_struSnmpCfg.byReadCommunity, m_csReadCommunity.GetBuffer(0), sizeof(m_struSnmpCfg.byReadCommunity));
    strncpy((char*)m_struSnmpCfg.byWriteCommunity, m_csWriteCommunity.GetBuffer(0), sizeof(m_struSnmpCfg.byWriteCommunity));
    strncpy((char*)m_struSnmpCfg.byTrapHostIP, m_csTrapHostIP, sizeof(m_struSnmpCfg.byTrapHostIP));
    m_struSnmpCfg.wTrapHostPort = m_iTrapHostPort;
	strncpy((char*)m_struSnmpCfg.byTrapName, m_csTrapName.GetBuffer(0), sizeof(m_struSnmpCfg.byTrapName));
	strncpy((char*)m_struSnmpCfg.struROUser.byUserName, m_strUserNameRO, NAME_LEN);
	strncpy((char*)m_struSnmpCfg.struROUser.byAuthpass, m_strAuthPWRO, PASSWD_LEN);
	strncpy((char*)m_struSnmpCfg.struROUser.byPrivpass, m_strPrivPWRO, PASSWD_LEN);
	m_struSnmpCfg.struROUser.byAuthtype = m_iAuthTypeRO;
	m_struSnmpCfg.struROUser.bySecLevel = m_iSecLevelRO;
	m_struSnmpCfg.struROUser.byPrivtype = m_iPrivateTypeRO;
	strncpy((char*)m_struSnmpCfg.struRWUser.byUserName, m_strUserNameRW, NAME_LEN);
	strncpy((char*)m_struSnmpCfg.struRWUser.byAuthpass, m_strAuthPWRW, PASSWD_LEN);
	strncpy((char*)m_struSnmpCfg.struRWUser.byPrivpass, m_strPrivPWRW, PASSWD_LEN);
	m_struSnmpCfg.struRWUser.byAuthtype = m_iAuthTypeRW;
	m_struSnmpCfg.struRWUser.bySecLevel = m_iSecLevelRW;
	m_struSnmpCfg.struRWUser.byPrivtype = m_iPrivateTypeRW;

    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_SNMPCFG_V30, -1, &m_struSnmpCfg, sizeof(m_struSnmpCfg)))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SNMPCFG_V30");
	}
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SNMPCFG_V30");
    }

	//NET_DVR_GET_SNMPCFGÖ¸Áî²âÊÔ
	// 	NET_DVR_SNMPCFG struSnmpCfgOld;
	// 	memset(&struSnmpCfgOld, 0, sizeof(struSnmpCfgOld));	
	// 	struSnmpCfgOld.dwSize = sizeof(NET_DVR_SNMPCFG);
	// 	struSnmpCfgOld.byEnable = 1;
	// 	struSnmpCfgOld.wVersion = 2;
	// 	struSnmpCfgOld.wServerPort = 160;
	// 	CString csReadCommunity;
	// 	csReadCommunity = _T("public");
	// 	strncpy((char*)struSnmpCfgOld.byReadCommunity, csReadCommunity.GetBuffer(0), sizeof(struSnmpCfgOld.byReadCommunity));
	// 	CString csWriteCommunity;
	// 	csWriteCommunity = _T("private");
	// 	strncpy((char*)struSnmpCfgOld.byWriteCommunity, csWriteCommunity.GetBuffer(0), sizeof(struSnmpCfgOld.byWriteCommunity));
	// 	strncpy((char*)struSnmpCfgOld.byTrapHostIP, _T("172.8.15.188"), sizeof(struSnmpCfgOld.byTrapHostIP));
	// 	strncpy((char*)struSnmpCfgOld.byTrapName, _T("Ãû×Ö1"), sizeof(struSnmpCfgOld.byTrapName));
	// 	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_SNMPCFG, -1, &struSnmpCfgOld, sizeof(struSnmpCfgOld)))
	// 	{
	//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SNMPCFG");
	// 	}
	//     else
	//     {
	//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SNMPCFG");
	//     }

}

void CDlgSnmpCfg::OnButtonExit() 
{
	CDialog::OnCancel();
}

void CDlgSnmpCfg::OnButtonUpdate() 
{
	DWORD dwReturn = 0;
	char strTmp[NAME_LEN+1] = {0};
	char strDesc[DESC_LEN_64+1] = {0};
	
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_SNMPCFG_V30, -1, &m_struSnmpCfg, sizeof(m_struSnmpCfg), &dwReturn))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SNMPCFG_V30");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SNMPCFG_V30");
    }
	
    m_bSnmpV1 = m_struSnmpCfg.byEnableV1;
	m_bSnmpV2 = m_struSnmpCfg.byEnableV2;
	m_bSnmpV3 = m_struSnmpCfg.byEnableV3;
    m_iSnmpPort = m_struSnmpCfg.wServerPort;
	
	memcpy(strTmp, m_struSnmpCfg.byReadCommunity, 32);
	m_csReadCommunity.Format("%s", strTmp);
	memset(strTmp, 0, 33);
	memcpy(strTmp, m_struSnmpCfg.byWriteCommunity, 32);
	m_csWriteCommunity.Format("%s", strTmp);
	
	memcpy(strDesc, m_struSnmpCfg.byTrapHostIP, 64);
	m_csTrapHostIP.Format("%s", strDesc);

	memcpy(strTmp, m_struSnmpCfg.byTrapName, 32);
	m_csTrapName.Format("%s", strTmp);

    m_iTrapHostPort = m_struSnmpCfg.wTrapHostPort;

	memset(strTmp, 0, 33);
	memcpy(strTmp, m_struSnmpCfg.struROUser.byUserName, 32);
	m_strUserNameRO.Format("%s", strTmp);
	memset(strTmp, 0, 33);
	memcpy(strTmp, m_struSnmpCfg.struROUser.byAuthpass, 16);
	m_strAuthPWRO.Format("%s", strTmp);
	memset(strTmp, 0, 33);
	memcpy(strTmp, m_struSnmpCfg.struROUser.byPrivpass, 16);
	m_strPrivPWRO.Format("%s", strTmp);
	m_iAuthTypeRO = m_struSnmpCfg.struROUser.byAuthtype;
	m_iSecLevelRO = m_struSnmpCfg.struROUser.bySecLevel;
	m_iPrivateTypeRO = m_struSnmpCfg.struROUser.byPrivtype;
	
	memset(strTmp, 0, 33);
	memcpy(strTmp, m_struSnmpCfg.struRWUser.byUserName, 32);
	m_strUserNameRW.Format("%s", strTmp);
	memset(strTmp, 0, 33);
	memcpy(strTmp, m_struSnmpCfg.struRWUser.byAuthpass, 16);
	m_strAuthPWRW.Format("%s", strTmp);
	memset(strTmp, 0, 33);
	memcpy(strTmp, m_struSnmpCfg.struRWUser.byPrivpass, 16);
	m_strPrivPWRW.Format("%s", strTmp);
	m_iAuthTypeRW = m_struSnmpCfg.struRWUser.byAuthtype;
	m_iSecLevelRW = m_struSnmpCfg.struRWUser.bySecLevel;
	m_iPrivateTypeRW = m_struSnmpCfg.struRWUser.byPrivtype;



	//NET_DVR_GET_SNMPCFGÖ¸Áî²âÊÔ
	// 	dwReturn = 0;
	// 	NET_DVR_SNMPCFG struSnmpCfgOld;
	// 	memset(&struSnmpCfgOld, 0, sizeof(struSnmpCfgOld));	
	// 	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_SNMPCFG, -1, &struSnmpCfgOld, sizeof(struSnmpCfgOld), &dwReturn))
	// 	{
	//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SNMPCFG");
	//         return;
	//     }
	//     else
	// 	{
	//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SNMPCFG");
	//     }
	// 	
	// 	int iTemp = 0;
	// 	iTemp = struSnmpCfgOld.byEnable;
	// 	iTemp = struSnmpCfgOld.wVersion;
	// 	iTemp = struSnmpCfgOld.wServerPort;
	// 	memcpy(strTmp, m_struSnmpCfg.byReadCommunity, 32);
	// 	memcpy(strTmp, m_struSnmpCfg.byWriteCommunity, 32);
	// 	memcpy(strDesc, m_struSnmpCfg.byTrapHostIP, 64);
	// 	iTemp = struSnmpCfgOld.wTrapHostPort;
	// 	memcpy(strTmp, m_struSnmpCfg.byTrapName, 32);

    UpdateData(FALSE);	
}

