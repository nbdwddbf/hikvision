// DlgVideoIntercomStreamCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVideoIntercomStreamCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomStreamCfg dialog


CDlgVideoIntercomStreamCfg::CDlgVideoIntercomStreamCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoIntercomStreamCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVideoIntercomStreamCfg)
	m_strDeviceID = _T("");
	m_strDeviceName = _T("");
	//}}AFX_DATA_INIT
	m_lServerID = -1;
	m_iDevIndex = -1;
	memset(&m_struStreamCfg, 0, sizeof(m_struStreamCfg));
}


void CDlgVideoIntercomStreamCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVideoIntercomStreamCfg)
	DDX_Control(pDX, IDC_COMBO_VIDEOTYPE, m_cmbVideoType);
	DDX_Control(pDX, IDC_COMBO_CHANNEL_ID, m_comboChannelID);
	DDX_Text(pDX, IDC_EDIT_DEVICE_ID, m_strDeviceID);
	DDX_Text(pDX, IDC_EDIT_DEVICE_NAME, m_strDeviceName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVideoIntercomStreamCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVideoIntercomStreamCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL_ID, OnSelchangeComboChannelId)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomStreamCfg message handlers
BOOL CDlgVideoIntercomStreamCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString tmp;
	m_comboChannelID.ResetContent();
	for (int i=0; i<100; i++)
	{
        tmp.Format("%d", i+1);
        m_comboChannelID.AddString(tmp);
		m_comboChannelID.SetItemData(i, i+1);
	}

    m_cmbVideoType.ResetContent();
    
    DWORD dwIndex = 0;
    tmp.Format("Meaningless");
    m_cmbVideoType.AddString(tmp);
    m_cmbVideoType.SetItemData(dwIndex++,0);

    tmp.Format("IPC");
    m_cmbVideoType.AddString(tmp);
    m_cmbVideoType.SetItemData(dwIndex++,1);

    tmp.Format("DVR/NVR");
    m_cmbVideoType.AddString(tmp);
    m_cmbVideoType.SetItemData(dwIndex++,2);

    tmp.Format("OutDoor");
    m_cmbVideoType.AddString(tmp);
    m_cmbVideoType.SetItemData(dwIndex++,3);

    tmp.Format("Fence");
    m_cmbVideoType.AddString(tmp);
    m_cmbVideoType.SetItemData(dwIndex++,4);

    tmp.Format("AgainDevice");
    m_cmbVideoType.AddString(tmp);
    m_cmbVideoType.SetItemData(dwIndex++,5);

    m_cmbVideoType.SetCurSel(0);

	m_comboChannelID.SetCurSel(0);
	return TRUE;
}

void CDlgVideoIntercomStreamCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_VIDEOINTERCOM_STREAM, m_comboChannelID.GetItemData(m_comboChannelID.GetCurSel()), &m_struStreamCfg, sizeof(m_struStreamCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEOINTERCOM_STREAM");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VIDEOINTERCOM_STREAM");
    }
	
	m_strDeviceID = m_struStreamCfg.byVisDevID;
	m_strDeviceName = m_struStreamCfg.byDeviceName;
    m_cmbVideoType.SetCurSel(m_struStreamCfg.bySourceType);
	UpdateData(FALSE);
}

void CDlgVideoIntercomStreamCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struStreamCfg.dwSize = sizeof(m_struStreamCfg);
	strncpy((char*)m_struStreamCfg.byVisDevID, m_strDeviceID.GetBuffer(0), sizeof(m_struStreamCfg.byVisDevID));
	strncpy((char*)m_struStreamCfg.byDeviceName, m_strDeviceName.GetBuffer(0), sizeof(m_struStreamCfg.byDeviceName));
    m_struStreamCfg.bySourceType = m_cmbVideoType.GetCurSel();
	
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_VIDEOINTERCOM_STREAM, m_comboChannelID.GetItemData(m_comboChannelID.GetCurSel()), &m_struStreamCfg, sizeof(m_struStreamCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VIDEOINTERCOM_STREAM");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VIDEOINTERCOM_STREAM");
    }
}

void CDlgVideoIntercomStreamCfg::OnSelchangeComboChannelId() 
{
	// TODO: Add your control notification handler code here
	OnBtnGet();
}
