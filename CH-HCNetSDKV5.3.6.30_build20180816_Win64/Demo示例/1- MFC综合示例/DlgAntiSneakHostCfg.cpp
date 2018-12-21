// DlgAntiSneakHostCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAntiSneakHostCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgAntiSneakHostCfg dialog


DlgAntiSneakHostCfg::DlgAntiSneakHostCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAntiSneakHostCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgAntiSneakHostCfg)
    m_byEnableAnti = FALSE;
    m_byIsStartAddr = FALSE;
    m_byAntiSnealHostNo = 0;
    m_wFollowUpCardReader = 0;
    m_Port = 0;
    m_sIP = _T("");
	//}}AFX_DATA_INIT
    memset(&m_struAntiSneakCfg, 0, sizeof(m_struAntiSneakCfg));
}


void DlgAntiSneakHostCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAntiSneakHostCfg)
    DDX_Control(pDX, IDC_COMBO1, m_byHostNo);
    DDX_Check(pDX, IDC_CHECK_ENABLE, m_byEnableAnti);
    DDX_Check(pDX, IDC_CHECK_START_ADDR, m_byIsStartAddr);
    DDX_Text(pDX, IDC_EDIT_ANTI_NO, m_byAntiSnealHostNo);
    DDX_Text(pDX, IDC_EDIT_CARD_READER, m_wFollowUpCardReader);
    DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
	DDX_Text(pDX, IDC_EDIT_IP, m_sIP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAntiSneakHostCfg, CDialog)
	//{{AFX_MSG_MAP(DlgAntiSneakHostCfg)
    ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeStruSneakHost)
    ON_BN_CLICKED(IDC_BUTTON_SURE, OnBtnSure)
    ON_BN_CLICKED(IDC_BUTTON_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAntiSneakHostCfg message handlers

BOOL DlgAntiSneakHostCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;

    CString csStr;
    char szLan[128] = {0};

    for (int i=0; i<MAX_SNEAK_PATH_NODE; i++)
    {
        g_StringLanType(szLan, "", "");
        csStr.Format("%s%d", szLan, i+1);
        m_byHostNo.InsertString(i, csStr);
	}
	//OnBtnGet();
 	return TRUE;  // return TRUE unless you set the focus to a control
 	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgAntiSneakHostCfg::OnSelchangeStruSneakHost() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReaderIndex = m_byHostNo.GetCurSel();    
    m_byIsStartAddr = m_struAntiSneakCfg.struSneakHost[dwReaderIndex].byIsStartAddr;
    m_Port = m_struAntiSneakCfg.struSneakHost[dwReaderIndex].struDVRIP.wPort;
    m_sIP.Format("%s",m_struAntiSneakCfg.struSneakHost[dwReaderIndex].struDVRIP.struIP.sIpV4);
	UpdateData(FALSE);
}

void DlgAntiSneakHostCfg::OnBtnSure() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReaderIndex = m_byHostNo.GetCurSel();
    m_struAntiSneakCfg.struSneakHost[dwReaderIndex].byHostNo = dwReaderIndex;
    m_struAntiSneakCfg.struSneakHost[dwReaderIndex].byIsStartAddr = m_byIsStartAddr;
    m_struAntiSneakCfg.struSneakHost[dwReaderIndex].struDVRIP.wPort = m_Port;
    sprintf(m_struAntiSneakCfg.struSneakHost[dwReaderIndex].struDVRIP.struIP.sIpV4,"%s",m_sIP.GetBuffer(m_sIP.GetLength()));    
    UpdateData(FALSE);
}

void DlgAntiSneakHostCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
    char szLan[1024];
	m_struAntiSneakCfg.dwSize = sizeof(m_struAntiSneakCfg);
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ANTI_SNEAK_HOST_CFG, 0, &m_struAntiSneakCfg, sizeof(m_struAntiSneakCfg), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ANTI_SNEAK_HOST_CFG Failed");
		g_StringLanType(szLan, "获取主机组反潜回参数失败", "get anti sneak host cfg Failed");
		MessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ANTI_SNEAK_HOST_CFG SUCC");
		m_byHostNo.SetCurSel(0);
        m_byEnableAnti = m_struAntiSneakCfg.byEnable;
        m_byAntiSnealHostNo = m_struAntiSneakCfg.struStartReader.byAntiSnealHostNo;
        m_wFollowUpCardReader = m_struAntiSneakCfg.struStartReader.wFollowUpCardReader;

        DWORD dwReaderIndex = 0;    
        m_byIsStartAddr = m_struAntiSneakCfg.struSneakHost[dwReaderIndex].byIsStartAddr;
        m_Port = m_struAntiSneakCfg.struSneakHost[dwReaderIndex].struDVRIP.wPort;
        m_sIP.Format("%s",m_struAntiSneakCfg.struSneakHost[dwReaderIndex].struDVRIP.struIP.sIpV4);
		UpdateData(FALSE);
	}
}

void DlgAntiSneakHostCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	//OnBtnSure();
    char szLan[1024];
	m_struAntiSneakCfg.dwSize = sizeof(m_struAntiSneakCfg);
    m_struAntiSneakCfg.byEnable = m_byEnableAnti;
    m_struAntiSneakCfg.struStartReader.byAntiSnealHostNo = m_byAntiSnealHostNo;
	m_struAntiSneakCfg.struStartReader.wFollowUpCardReader = m_wFollowUpCardReader;
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_ANTI_SNEAK_HOST_CFG, 0, &m_struAntiSneakCfg, sizeof(m_struAntiSneakCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ANTI_SNEAK_HOST_CFG Failed");
		g_StringLanType(szLan, "设置主机组反潜回参数失败", "set anti sneak host cfg Failed");
		MessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ANTI_SNEAK_HOST_CFG SUCC");
	}
}
