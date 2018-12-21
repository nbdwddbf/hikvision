// DlgIPAddrFilterCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgIPAddrFilterCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIPAddrFilterCfg dialog


CDlgIPAddrFilterCfg::CDlgIPAddrFilterCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIPAddrFilterCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIPAddrFilterCfg)
	m_bChkIPAddrEn = FALSE;
	m_csIPAddr = _T("");
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_iDevIndex = -1;
	m_lChannel = -1;
	memset(&m_struIPAddrCfg, 0, sizeof(m_struIPAddrCfg));
}


void CDlgIPAddrFilterCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIPAddrFilterCfg)
	DDX_Control(pDX, IDC_COMBO_FILTER_TYPE, m_comboFilterType);
	DDX_Check(pDX, IDC_CHK_IPADDR_FILTER_EN, m_bChkIPAddrEn);
	DDX_Text(pDX, IDC_EDIT_IPADDR, m_csIPAddr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIPAddrFilterCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgIPAddrFilterCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIPAddrFilterCfg message handlers

void CDlgIPAddrFilterCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn;
	
	char szLan[1025] = {0};
	
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_IPADDR_FILTERCFG, 1, &m_struIPAddrCfg, sizeof(m_struIPAddrCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_IPADDR_FILTERCFG Fail");
 
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_IPADDR_FILTERCFG Success");
    }
	m_bChkIPAddrEn = m_struIPAddrCfg.byEnable;
	m_comboFilterType.SetCurSel(m_struIPAddrCfg.byFilterType);
	memcpy(szLan, m_struIPAddrCfg.byIPAddr,1024);
	m_csIPAddr.Format("%s",szLan);
	UpdateData(FALSE);
}

void CDlgIPAddrFilterCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struIPAddrCfg.dwSize = sizeof(m_struIPAddrCfg);
	m_struIPAddrCfg.byEnable = m_bChkIPAddrEn;
	m_struIPAddrCfg.byFilterType = m_comboFilterType.GetCurSel();
	memcpy(m_struIPAddrCfg.byIPAddr, m_csIPAddr, 1024);
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_IPADDR_FILTERCFG, 1, &m_struIPAddrCfg, sizeof(m_struIPAddrCfg)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_IPADDR_FILTERCFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_IPADDR_FILTERCFG");	
	}
}
