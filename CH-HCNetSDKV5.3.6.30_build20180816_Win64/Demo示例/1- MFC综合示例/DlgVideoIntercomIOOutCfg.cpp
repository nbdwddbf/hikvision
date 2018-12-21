// DlgVideoIntercomIOOutCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVideoIntercomIOOutCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomIOOutCfg dialog


CDlgVideoIntercomIOOutCfg::CDlgVideoIntercomIOOutCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoIntercomIOOutCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVideoIntercomIOOutCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lServerID = -1;
	m_iDevIndex = -1;
	memset(&m_struIOOutCfg, 0, sizeof(m_struIOOutCfg));
}


void CDlgVideoIntercomIOOutCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVideoIntercomIOOutCfg)
	DDX_Control(pDX, IDC_COMBO_USETYPE, m_comboUseType);
	DDX_Control(pDX, IDC_COMBO_IOOUT, m_comboIOOut);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVideoIntercomIOOutCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVideoIntercomIOOutCfg)
	ON_CBN_SELCHANGE(IDC_COMBO_IOOUT, OnSelchangeComboIoout)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomIOOutCfg message handlers
BOOL CDlgVideoIntercomIOOutCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CString tmp;
	char szLan[128] = {0};

	m_comboIOOut.ResetContent();
	for (int i=0; i<4; i++)
	{
        tmp.Format("%d", i+1);
        m_comboIOOut.AddString(tmp);
		m_comboIOOut.SetItemData(i, i+1);
	}
	m_comboIOOut.SetCurSel(0);
	
	m_comboUseType.ResetContent();

	g_StringLanType(szLan, "禁用", "Disabled");
	m_comboUseType.AddString(szLan);
	m_comboUseType.SetItemData(0, 0);
	
	g_StringLanType(szLan, "电锁", "Door Lock");
	m_comboUseType.AddString(szLan);
	m_comboUseType.SetItemData(1, 1);
	
	g_StringLanType(szLan, "自定义", "Custom");
	m_comboUseType.AddString(szLan);
	m_comboUseType.SetItemData(2, 255);
	
	return TRUE;
}

void CDlgVideoIntercomIOOutCfg::OnSelchangeComboIoout() 
{
	// TODO: Add your control notification handler code here
	OnBtnGet();
}

void CDlgVideoIntercomIOOutCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn = 0;
	memset(&m_struIOOutCfg, 0, sizeof(m_struIOOutCfg));
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_VIDEO_INTERCOM_IOOUT_CFG, m_comboIOOut.GetItemData(m_comboIOOut.GetCurSel()), &m_struIOOutCfg, sizeof(m_struIOOutCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEO_INTERCOM_IOOUT_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VIDEO_INTERCOM_IOOUT_CFG");
    }
	
	//m_comboUseType.SetCurSel(m_struIOOutCfg.byIOUseType);

	int i = 0;
	for (i=0; i<m_comboUseType.GetCount(); i++)
	{
		if (m_comboUseType.GetItemData(i) == m_struIOOutCfg.byIOUseType)
		{
            m_comboUseType.SetCurSel(i);
			break;
		}
	}
	UpdateData(FALSE);
}

void CDlgVideoIntercomIOOutCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struIOOutCfg.dwSize = sizeof(m_struIOOutCfg);
	m_struIOOutCfg.byIOUseType = m_comboUseType.GetItemData(m_comboUseType.GetCurSel());
	
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_VIDEO_INTERCOM_IOOUT_CFG, m_comboIOOut.GetItemData(m_comboIOOut.GetCurSel()), &m_struIOOutCfg, sizeof(m_struIOOutCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VIDEO_INTERCOM_IOOUT_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VIDEO_INTERCOM_IOOUT_CFG");
    }
}
