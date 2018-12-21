// DlgOneKeyBackupCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgOneKeyBackupCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgOneKeyBackupCfg dialog


DlgOneKeyBackupCfg::DlgOneKeyBackupCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgOneKeyBackupCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgOneKeyBackupCfg)
	m_bEnable = TRUE;
	m_bContinue = TRUE;
	//}}AFX_DATA_INIT
	m_lUserID = -1;
	m_iDeviceIndex = -1;
	memset(&m_struBackupCfg, 0 ,sizeof(m_struBackupCfg));
	m_iStartChannel = 0;
}


void DlgOneKeyBackupCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgOneKeyBackupCfg)
	DDX_Control(pDX, IDC_COMB_CHAN, m_comChan);
	DDX_Control(pDX, IDC_COMBO_STREAM_TYPE, m_comStreamType);
	DDX_Check(pDX, IDC_CHK_BACKUP_ENABLE, m_bEnable);
	DDX_Check(pDX, IDC_CHK_CONTINUE, m_bContinue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgOneKeyBackupCfg, CDialog)
	//{{AFX_MSG_MAP(DlgOneKeyBackupCfg)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_BACKUP_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_BACKUP_GET, OnBtnGet)
	ON_CBN_SELCHANGE(IDC_COMB_CHAN, OnSelchangeComboChan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgOneKeyBackupCfg message handlers

BOOL DlgOneKeyBackupCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//AddChanInfo 
    m_comChan.ResetContent();
    DWORD  dwIndex = 0;

	int i = 0;
    for (i = 0; i< g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)
    {
		if (g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].bEnable)
        {
            m_comChan.AddString(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
			m_comChan.SetItemData(dwIndex, g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO);
			dwIndex++;
        }
    }

	for(i = 0; i < g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum;i++)
	{
		if (i == 0)
		{
			m_comChan.AddString(g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].chChanName);
			m_comChan.SetItemData(dwIndex, g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].iChannelNO);
			dwIndex++;
		}
	}
	
    m_comChan.SetCurSel(0);
	OnBtnGet();
	return TRUE;
}

void DlgOneKeyBackupCfg::OnBtnOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iChannel = m_comChan.GetItemData(m_comChan.GetCurSel());
	if(iChannel < 0)
	{	
		iChannel = m_comChan.GetItemData(0);
	}

	if (iChannel == g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[0].iChannelNO)
	{
		m_struBackupCfg.struDirectedChanBackUp.byEnable = m_bEnable;
		m_struBackupCfg.struDirectedChanBackUp.dwStreamType = m_comStreamType.GetCurSel();
	} 
	else
	{
		m_struBackupCfg.struChanBackUp[iChannel -1].byEnable = m_bEnable;
		m_struBackupCfg.struChanBackUp[iChannel -1].dwStreamType = m_comStreamType.GetCurSel();
	}
}

void DlgOneKeyBackupCfg::OnBtnSet()
{
	// TODO: Add your control notification handler code here
	OnBtnOk();
	UpdateData(TRUE);
	char szLan[128] = {0};
	if(!NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_BACKUP_RECORD_CFG,m_iStartChannel,&m_struBackupCfg,sizeof(m_struBackupCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_BACKUP_RECORD_CFG,  %s", "Set Backup Record cfg faild");
		g_StringLanType(szLan, "设置一键备份参数配置失败", "Set Backup Record cfg failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_BACKUP_RECORD_CFG,  %s", "Set Backup Record cfg success");
		g_StringLanType(szLan, "设置一键备份参数配置成功", "Set Backup Record cfg success");
		AfxMessageBox(szLan);
	}
}

void DlgOneKeyBackupCfg::OnBtnGet()
{
	// TODO: Add your control notification handler code here
	DWORD dwReturned = 0;
	char szLan[128] = {0};
	if(!NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_BACKUP_RECORD_CFG,m_iStartChannel,&m_struBackupCfg,sizeof(m_struBackupCfg),&dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RECORDINGHOST_CFG,  %s", "Get Backup Record cfg faild");
		g_StringLanType(szLan, "获取一键备份参数配置失败", "Get Backup Record cfg failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORDINGHOST_CFG,  %s", "Get Backup Record cfg success");
		g_StringLanType(szLan, "获取一键备份参数配置成功", "Get Backup Record cfg success");
		AfxMessageBox(szLan);
	}

	m_comChan.SetCurSel(0);
	OnSelchangeComboChan();
	UpdateData(FALSE);
}

void DlgOneKeyBackupCfg::OnSelchangeComboChan()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iChannelNo  = m_comChan.GetItemData(m_comChan.GetCurSel());
	if (iChannelNo < 0)
	{
		iChannelNo = 1;
	}

	if (iChannelNo == g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[0].iChannelNO)
	{
		m_comStreamType.SetCurSel(m_struBackupCfg.struDirectedChanBackUp.dwStreamType);
		m_bEnable = m_struBackupCfg.struDirectedChanBackUp.byEnable;
	} 
	else
	{
		m_comStreamType.SetCurSel(m_struBackupCfg.struChanBackUp[iChannelNo -1].dwStreamType);
		m_bEnable = m_struBackupCfg.struChanBackUp[iChannelNo -1].byEnable;
	}
	UpdateData(FALSE);
}
