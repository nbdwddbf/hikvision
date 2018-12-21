// DlgVideoIntercomIOInCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVideoIntercomIOInCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgVideoIntercomIOInCfg dialog


DlgVideoIntercomIOInCfg::DlgVideoIntercomIOInCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgVideoIntercomIOInCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgVideoIntercomIOInCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lServerID = -1;
	m_iDevIndex = -1;
	memset(&m_struIOInCfg, 0, sizeof(m_struIOInCfg));
}


void DlgVideoIntercomIOInCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgVideoIntercomIOInCfg)
	DDX_Control(pDX, IDC_COMBO_IOIN, m_comboIO);
	DDX_Control(pDX, IDC_COMBO_USETYPR, m_comboUseType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgVideoIntercomIOInCfg, CDialog)
	//{{AFX_MSG_MAP(DlgVideoIntercomIOInCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_COMBO_IOIN, OnSelchangeComboIoin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgVideoIntercomIOInCfg message handlers
BOOL DlgVideoIntercomIOInCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString tmp;
	char szLan[128] = {0};

	m_comboIO.ResetContent();
	for (int i=0; i<4; i++)
	{
        tmp.Format("%d", i+1);
        m_comboIO.AddString(tmp);
	    m_comboIO.SetItemData(i, i+1);
	}
	m_comboIO.SetCurSel(0);

	m_comboUseType.ResetContent();

	g_StringLanType(szLan, "禁用", "Disabled");
	//tmp.Format("%s", szLan);
	m_comboUseType.AddString(szLan);
	m_comboUseType.SetItemData(0, 0);

	g_StringLanType(szLan, "开门按钮", "Open door");
	//tmp.Format("%s", szLan);
	m_comboUseType.AddString(szLan);
	m_comboUseType.SetItemData(1, 1);

	g_StringLanType(szLan, "门状态", "Door status");
	//tmp.Format("%s", szLan);
	m_comboUseType.AddString(szLan);
	m_comboUseType.SetItemData(2, 2);

	g_StringLanType(szLan, "自定义", "Custom");
	//tmp.Format("%s", szLan);
	m_comboUseType.AddString(szLan);
	m_comboUseType.SetItemData(3, 255);

	return TRUE;
}

void DlgVideoIntercomIOInCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn = 0;
	memset(&m_struIOInCfg, 0, sizeof(m_struIOInCfg));
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_VIDEO_INTERCOM_IOIN_CFG, m_comboIO.GetItemData(m_comboIO.GetCurSel()), &m_struIOInCfg, sizeof(m_struIOInCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEO_INTERCOM_IOIN_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VIDEO_INTERCOM_IOIN_CFG");
    }
	
	int i = 0;
	for (i=0; i<m_comboUseType.GetCount(); i++)
	{
		if (m_comboUseType.GetItemData(i) == m_struIOInCfg.byIOUseType)
		{
            m_comboUseType.SetCurSel(i);
			break;
		}
	}
	UpdateData(FALSE);
}

void DlgVideoIntercomIOInCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struIOInCfg.dwSize = sizeof(m_struIOInCfg);
	m_struIOInCfg.byIOUseType = m_comboUseType.GetItemData(m_comboUseType.GetCurSel());
	
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_VIDEO_INTERCOM_IOIN_CFG, m_comboIO.GetItemData(m_comboIO.GetCurSel()), &m_struIOInCfg, sizeof(m_struIOInCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VIDEO_INTERCOM_IOIN_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VIDEO_INTERCOM_IOIN_CFG");
    }
}

void DlgVideoIntercomIOInCfg::OnSelchangeComboIoin() 
{
	// TODO: Add your control notification handler code here
	OnBtnGet();
}
