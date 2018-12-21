// DlgAcsCardUserInfoCfg1.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAcsCardUserInfoCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAcsCardUserInfoCfg dialog


CDlgAcsCardUserInfoCfg::CDlgAcsCardUserInfoCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAcsCardUserInfoCfg::IDD, pParent)
	, m_csUserNum(0)
{
	//{{AFX_DATA_INIT(CDlgAcsCardUserInfoCfg)
	m_csCardNo = _T("");
	m_csUserName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAcsCardUserInfoCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAcsCardUserInfoCfg)
	DDX_Text(pDX, IDC_EDIT_CARD_NO, m_csCardNo);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_csUserName);
	//DDX_Control(pDX, IDC_COMBO_INDEX, m_index);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_USER_NUM, m_csUserNum);
	DDV_MinMaxByte(pDX, m_csUserNum, 0, 255);
}


BEGIN_MESSAGE_MAP(CDlgAcsCardUserInfoCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAcsCardUserInfoCfg)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
    ON_BN_CLICKED(IDC_BUTTON_SURE, OnBtnSure)
    ON_CBN_SELCHANGE(IDC_COMBO_INDEX, OnSelchangeIndex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAcsCardUserInfoCfg message handlers

void CDlgAcsCardUserInfoCfg::OnButtonGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	memset(&m_struCond,0,sizeof(m_struCond));

	memcpy(m_struCond.byCardNo,m_csCardNo.GetBuffer(0),m_csCardNo.GetLength());
    m_struCond.dwSize = sizeof(m_struCond);

	DWORD dwStatus = 0;
	char szLan[128] = {0};

	if (!NET_DVR_GetDeviceConfig(m_lUserID,NET_DVR_GET_CARD_USERINFO_CFG,1,&m_struCond,sizeof(m_struCond),&dwStatus,\
		&m_struUserInfo,sizeof(m_struUserInfo)))
	{
		g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_GET_CARD_USERINFO_CFG");
		return;
	}
	else
	{
		if (dwStatus != NET_DVR_NOERROR)
		{
			sprintf(szLan,"NET_DVR_GET_CARD_USERINFO_CFG Error Status[%d]",dwStatus);
			g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,szLan);
			return;
		}

		g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_GET_CARD_USERINFO_CFG");
		m_csUserName = m_struUserInfo.sUsername;
		m_csUserNum = m_struUserInfo.byRes2[0];

	}
	UpdateData(FALSE);
}

void CDlgAcsCardUserInfoCfg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	memset(&m_struCond,0,sizeof(m_struCond));
	
	m_struCond.dwSize = sizeof(m_struCond);
    m_struUserInfo.dwSize = sizeof(m_struUserInfo);
    strncpy((char*)m_struCond.byCardNo,m_csCardNo.GetBuffer(0),ACS_CARD_NO_LEN);
	strncpy((char*)m_struUserInfo.sUsername,m_csUserName.GetBuffer(0),NAME_LEN);
	m_struUserInfo.byRes2[0] = m_csUserNum;
	DWORD dwStatus = 0;
	char szLan[128] = {0};
	
	if (!NET_DVR_SetDeviceConfig(m_lUserID,NET_DVR_SET_CARD_USERINFO_CFG,1,&m_struCond,sizeof(m_struCond),&dwStatus,\
		&m_struUserInfo,sizeof(m_struUserInfo)))
	{
		g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_SET_CARD_USERINFO_CFG");
		return;
	}
	else
	{
		if (dwStatus != NET_DVR_NOERROR)
		{
			sprintf(szLan,"NET_DVR_SET_CARD_USERINFO_CFG Error Status[%d]",dwStatus);
			g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,szLan);
			return;
		}
		
		g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_SET_CARD_USERINFO_CFG");
	}

}

void CDlgAcsCardUserInfoCfg::OnBtnSure() 
{
    // TODO: Add your control notification handler code here
//     UpdateData(TRUE);
//     DWORD dwReaderIndex = m_byHostNo.GetCurSel();
//     m_struAntiSneakCfg.struSneakHost[dwReaderIndex].byHostNo = dwReaderIndex;
//     m_struAntiSneakCfg.struSneakHost[dwReaderIndex].byIsStartAddr = m_byIsStartAddr;
//     m_struAntiSneakCfg.struSneakHost[dwReaderIndex].struDVRIP.wPort = m_Port;
//     sprintf(m_struAntiSneakCfg.struSneakHost[dwReaderIndex].struDVRIP.struIP.sIpV4,"%s",m_sIP.GetBuffer(m_sIP.GetLength()));    
//     UpdateData(FALSE);
}



void CDlgAcsCardUserInfoCfg::OnSelchangeIndex() 
{
    // TODO: Add your control notification handler code here
//     UpdateData(TRUE);
//     DWORD dwReaderIndex = m_byHostNo.GetCurSel();    
//     m_byIsStartAddr = m_struAntiSneakCfg.struSneakHost[dwReaderIndex].byIsStartAddr;
//     m_Port = m_struAntiSneakCfg.struSneakHost[dwReaderIndex].struDVRIP.wPort;
//     m_sIP.Format("%s",m_struAntiSneakCfg.struSneakHost[dwReaderIndex].struDVRIP.struIP.sIpV4);    
//     UpdateData(FALSE);
}
