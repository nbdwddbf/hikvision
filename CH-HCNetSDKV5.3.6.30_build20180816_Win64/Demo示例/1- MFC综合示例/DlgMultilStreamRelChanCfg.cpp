// DlgMultilStreamRelChanCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMultilStreamRelChanCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMultilStreamRelChanCfg dialog


CDlgMultilStreamRelChanCfg::CDlgMultilStreamRelChanCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMultilStreamRelChanCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMultilStreamRelChanCfg)
	//}}AFX_DATA_INIT
}


void CDlgMultilStreamRelChanCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMultilStreamRelChanCfg)
	DDX_Control(pDX, IDC_CMB_REL_CHAN, m_cmbRelChan);
	DDX_Control(pDX, IDC_CMB_MULTISTREAM_NO, m_cmbMultiStreamNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMultilStreamRelChanCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgMultilStreamRelChanCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMultilStreamRelChanCfg message handlers

void CDlgMultilStreamRelChanCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here

	LONG lChannel = m_cmbMultiStreamNo.GetCurSel() + 1;
	
	char szLan[128] = {0};
	NET_DVR_MULTISTREAM_RELATION_CHAN_CFG struMultiStreamRelChanCfg = {0};
	memset(&struMultiStreamRelChanCfg, 0, sizeof(NET_DVR_MULTISTREAM_RELATION_CHAN_CFG));
	
	DWORD dwReturnedBytes = 0;
	
	if(NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_MULTISTREAM_RELATION_CHAN_CFG, lChannel, &struMultiStreamRelChanCfg, sizeof(NET_DVR_MULTISTREAM_RELATION_CHAN_CFG), &dwReturnedBytes))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_MULTISTREAM_RELATION_CHAN_CFG	");
		g_StringLanType(szLan, "获取附加码流关联通道配置成功!", "Success to get multi stream relation channel");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_MULTISTREAM_RELATION_CHAN_CFG	");
		g_StringLanType(szLan, "获取附加码流关联通道配置失败!", "Fail to get multi stream relation channel");
		AfxMessageBox(szLan);
		return;
	}
	
    for (int i= 0; i< m_cmbRelChan.GetCount();i++)
    {
        m_cmbRelChan.SetCurSel(i);

        if (m_cmbRelChan.GetItemData(m_cmbRelChan.GetCurSel()) == struMultiStreamRelChanCfg.dwChannel)
        {
            break;
        }
        else
        {
            m_cmbRelChan.SetCurSel(m_cmbRelChan.GetCount() - 1);
        }
    }
	
	UpdateData(FALSE);
}

void CDlgMultilStreamRelChanCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	
	LONG lChannel = m_cmbMultiStreamNo.GetCurSel() + 1;
	
	char szLan[128] = {0};
	NET_DVR_MULTISTREAM_RELATION_CHAN_CFG struMultiStreamRelChanCfg = {0};
	memset(&struMultiStreamRelChanCfg, 0, sizeof(NET_DVR_MULTISTREAM_RELATION_CHAN_CFG));
	
	struMultiStreamRelChanCfg.dwSize = sizeof(NET_DVR_MULTISTREAM_RELATION_CHAN_CFG);
	
	struMultiStreamRelChanCfg.dwChannel = m_cmbRelChan.GetItemData(m_cmbRelChan.GetCurSel());
	
	if(NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_MULTISTREAM_RELATION_CHAN_CFG, lChannel, &struMultiStreamRelChanCfg, sizeof(NET_DVR_MULTISTREAM_RELATION_CHAN_CFG)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MULTISTREAM_RELATION_CHAN_CFG");
		g_StringLanType(szLan, "设置附加码流关联通道配置成功!", "Success to set multi stream relation channel");
		//	AfxMessageBox(szLan);
	}
	else
	{ 
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MULTISTREAM_RELATION_CHAN_CFG");
		g_StringLanType(szLan, "设置附加码流关联通道配置失败!", "Fail to set multi stream relation channel");
		AfxMessageBox(szLan);
		return;
	}
}

BOOL CDlgMultilStreamRelChanCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	int iDeviceChanNum = g_struDeviceInfo[m_dwDevIndex].iDeviceChanNum;

	char szLan[128] = {0};
    m_cmbRelChan.ResetContent();

	int i;
	for ( i = 0; i < iDeviceChanNum; i++ )
	{	
		m_cmbRelChan.AddString(g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].chChanName);
		m_cmbRelChan.SetItemData(i, g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].iChannelNO);
    }
    m_cmbRelChan.AddString("UnRelate Channel");
    m_cmbRelChan.SetItemData(i, 0);

	m_cmbMultiStreamNo.SetCurSel(0);
	
	OnBtnGet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
