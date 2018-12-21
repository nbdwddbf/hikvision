// DlgReaderAntiSneakHostCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgReaderAntiSneakHostCfg.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgReaderAntiSneakHostCfg dialog


DlgReaderAntiSneakHostCfg::DlgReaderAntiSneakHostCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgReaderAntiSneakHostCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgReaderAntiSneakHostCfg)
	m_byEnable = false;
    m_byAntiSnealHostNo = 0;
    m_wReaderID = 0;
    m_byAntiSnealHostNoNext = 0;
    m_wFollowUpCardReader = 0;
	//}}AFX_DATA_INIT
    memset(&m_struAntiSneakCfg, 0, sizeof(m_struAntiSneakCfg));
}


void DlgReaderAntiSneakHostCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgReaderAntiSneakHostCfg)
    DDX_Control(pDX, IDC_COMBO1, m_cmReaderCfg);
    DDX_Control(pDX, IDC_COMBO2, m_cmSneakReaderInfo);
    DDX_Check(pDX, IDC_CHECK_ENABLE, m_byEnable);
    DDX_Text(pDX, IDC_EDIT_ANTI_NO, m_byAntiSnealHostNo);
    DDX_Text(pDX, IDC_EDIT_READER_ID, m_wReaderID);
    DDX_Text(pDX, IDC_EDIT_ANTI_NEXT, m_byAntiSnealHostNoNext);
    DDX_Text(pDX, IDC_EDIT_READER_NEXT, m_wFollowUpCardReader);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgReaderAntiSneakHostCfg, CDialog)
	//{{AFX_MSG_MAP(DlgReaderAntiSneakHostCfg)
    ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeStruReaderCfg)
    ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeStruSneakReaderInfo)
    ON_BN_CLICKED(IDC_BUTTON_SURE, OnBtnSure)
    ON_BN_CLICKED(IDC_BUTTON_SURE2, OnBtnSure2)
    ON_BN_CLICKED(IDC_BUTTON_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgReaderAntiSneakHostCfg message handlers

BOOL DlgReaderAntiSneakHostCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;

    CString csStr;
    char szLan[128] = {0};
    for (int i=0; i<MAX_READER_ROUTE_NUM; i++)
    {
        g_StringLanType(szLan, "读卡器", "reader");
        csStr.Format("%s%d", szLan, i+1);
        m_cmReaderCfg.InsertString(i, csStr);
        //m_cmReaderCfg.AddString(csStr);
	}

    for (int j=0; j<MAX_SNEAK_PATH_NODE; j++)
    {
        g_StringLanType(szLan, "", "");
        csStr.Format("%s%d", szLan, j+1);
        m_cmSneakReaderInfo.InsertString(j, csStr);
        //m_cmSneakReaderInfo.AddString(csStr);
	}
	OnBtnGet();
 	return TRUE;  // return TRUE unless you set the focus to a control
 	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgReaderAntiSneakHostCfg::OnSelchangeStruReaderCfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReaderIndex = m_cmReaderCfg.GetCurSel();

    m_byEnable = m_struAntiSneakCfg.struReaderCfg[dwReaderIndex].byEnable;
    m_byAntiSnealHostNo = m_struAntiSneakCfg.struReaderCfg[dwReaderIndex].byAntiSnealHostNo;
    m_wReaderID = m_struAntiSneakCfg.struReaderCfg[dwReaderIndex].wReaderID;
	UpdateData(FALSE);
}

void DlgReaderAntiSneakHostCfg::OnSelchangeStruSneakReaderInfo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    DWORD dwReaderIndex = m_cmReaderCfg.GetCurSel();
    DWORD dwSneakReaderIndex = m_cmSneakReaderInfo.GetCurSel();
    m_byAntiSnealHostNoNext = m_struAntiSneakCfg.struReaderCfg[dwReaderIndex].struSneakReaderInfo[dwSneakReaderIndex].byAntiSnealHostNo;
    m_wFollowUpCardReader = m_struAntiSneakCfg.struReaderCfg[dwReaderIndex].struSneakReaderInfo[dwSneakReaderIndex].wFollowUpCardReader;
	UpdateData(FALSE);
}


void DlgReaderAntiSneakHostCfg::OnBtnSure() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReaderIndex = m_cmReaderCfg.GetCurSel();
    m_struAntiSneakCfg.struReaderCfg[dwReaderIndex].byEnable = m_byEnable;
    m_struAntiSneakCfg.struReaderCfg[dwReaderIndex].byAntiSnealHostNo = m_byAntiSnealHostNo;
    m_struAntiSneakCfg.struReaderCfg[dwReaderIndex].wReaderID = m_wReaderID;
    UpdateData(FALSE);
}

void DlgReaderAntiSneakHostCfg::OnBtnSure2() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    DWORD dwReaderIndex = m_cmReaderCfg.GetCurSel();
    DWORD dwSneakReaderIndex = m_cmSneakReaderInfo.GetCurSel();
    m_struAntiSneakCfg.struReaderCfg[dwReaderIndex].struSneakReaderInfo[dwSneakReaderIndex].byAntiSnealHostNo = m_byAntiSnealHostNoNext;
    m_struAntiSneakCfg.struReaderCfg[dwReaderIndex].struSneakReaderInfo[dwSneakReaderIndex].wFollowUpCardReader = m_wFollowUpCardReader;
    UpdateData(FALSE);
}

void DlgReaderAntiSneakHostCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
    char szLan[1024];
	m_struAntiSneakCfg.dwSize = sizeof(m_struAntiSneakCfg);
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_READER_ANTI_SNEAK_HOST_CFG, 0, &m_struAntiSneakCfg, sizeof(m_struAntiSneakCfg), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_READER_ANTI_SNEAK_HOST_CFG Failed");
		g_StringLanType(szLan, "获取主机组读卡器反潜回参数失败", "Get Net reader anti sneak host cfg Failed");
		MessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_READER_ANTI_SNEAK_HOST_CFG SUCC");
        //OnSelchangeStruReaderCfg();
        //OnSelchangeStruSneakReaderInfo();
		m_cmReaderCfg.SetCurSel(0);
        m_cmSneakReaderInfo.SetCurSel(0);

        DWORD dwReaderIndex = 0;        
        m_byEnable = m_struAntiSneakCfg.struReaderCfg[dwReaderIndex].byEnable;
        m_byAntiSnealHostNo = m_struAntiSneakCfg.struReaderCfg[dwReaderIndex].byAntiSnealHostNo;
        m_wReaderID = m_struAntiSneakCfg.struReaderCfg[dwReaderIndex].wReaderID;

        DWORD dwSneakReaderIndex = 0;
        m_byAntiSnealHostNoNext = m_struAntiSneakCfg.struReaderCfg[dwReaderIndex].struSneakReaderInfo[dwSneakReaderIndex].byAntiSnealHostNo;
        m_wFollowUpCardReader = m_struAntiSneakCfg.struReaderCfg[dwReaderIndex].struSneakReaderInfo[dwSneakReaderIndex].wFollowUpCardReader;

		UpdateData(FALSE);
	}
}

void DlgReaderAntiSneakHostCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	//OnBtnSure();
    char szLan[1024];
	m_struAntiSneakCfg.dwSize = sizeof(m_struAntiSneakCfg);
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_READER_ANTI_SNEAK_HOST_CFG, 0, &m_struAntiSneakCfg, sizeof(m_struAntiSneakCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_READER_ANTI_SNEAK_HOST_CFG Failed");
		g_StringLanType(szLan, "设置主机组读卡器反潜回参数失败", "Set Net reader anti sneak host cfg Failed");
		MessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_READER_ANTI_SNEAK_HOST_CFG SUCC");
	}
}
