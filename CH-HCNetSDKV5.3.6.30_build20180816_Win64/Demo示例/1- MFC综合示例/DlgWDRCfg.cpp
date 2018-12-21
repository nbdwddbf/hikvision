// DlgWDRCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWDRCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWDRCfg dialog


CDlgWDRCfg::CDlgWDRCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWDRCfg::IDD, pParent)

{
	//{{AFX_DATA_INIT(CDlgWDRCfg)
	m_bEnable = FALSE;
    m_lUserID = -1;
    m_iDevIndex = -1;
    m_byLevel1 = 0;
    m_byLevel2 = 0;
    m_byContrastLevel = 0;
    
	//}}AFX_DATA_INIT
}


void CDlgWDRCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWDRCfg)
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
    DDX_Text(pDX, IDC_EDIT_LEVEL1, m_byLevel1);
    DDX_Text(pDX, IDC_EDIT_LEVEL2, m_byLevel2);
    DDX_Text(pDX, IDC_EDIT_CONTRST, m_byContrastLevel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWDRCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgWDRCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWDRCfg message handlers

void CDlgWDRCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    memset(&m_struWDRCfg, 0,sizeof(m_struWDRCfg));
    m_struWDRCfg.dwSize = sizeof(m_struWDRCfg);

    DWORD dwChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    DWORD dwRet = 0;
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_WDR_CFG,dwChannel,&m_struWDRCfg,sizeof(m_struWDRCfg), &dwRet))
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_GET_WDR_CFG  Channel[%d]",dwChannel);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_GET_WDR_CFG  Channel[%d]",dwChannel);

    }

    m_bEnable = m_struWDRCfg.struWDR.byWDREnabled;
    m_byLevel1 = m_struWDRCfg.struWDR.byWDRLevel1;
    m_byLevel2 = m_struWDRCfg.struWDR.byWDRLevel2;
    m_byContrastLevel = m_struWDRCfg.struWDR.byWDRContrastLevel;


    UpdateData(FALSE);
    
}

BOOL CDlgWDRCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    m_cmbChannel.ResetContent();
    DWORD dwIndex = 0;

    for (int i = 0; i< g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;i++)
    {
        m_cmbChannel.AddString(g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].chChanName);
        m_cmbChannel.SetItemData(dwIndex++,g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].iChannelNO);
    }

    m_cmbChannel.SetCurSel(0);

    OnBtnGet();
	// TODO: Add extra initialization here
	    memset(&m_struWDRCfg,0,sizeof(m_struWDRCfg));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgWDRCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    
    memset(&m_struWDRCfg, 0,sizeof(m_struWDRCfg));
    m_struWDRCfg.dwSize = sizeof(m_struWDRCfg);
    m_struWDRCfg.struWDR.byWDREnabled = m_bEnable;
    m_struWDRCfg.struWDR.byWDREnabled = m_bEnable;
    m_struWDRCfg.struWDR.byWDRLevel1 = m_byLevel1;
    m_struWDRCfg.struWDR.byWDRLevel2 = m_byLevel2;
     m_struWDRCfg.struWDR.byWDRContrastLevel =m_byContrastLevel;
    DWORD dwChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    DWORD dwRet = 0;
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_WDR_CFG,dwChannel,&m_struWDRCfg,sizeof(m_struWDRCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_SET_WDR_CFG  Channel[%d]",dwChannel);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_SET_WDR_CFG  Channel[%d]",dwChannel); 
    } 

    UpdateData(FALSE);
}
