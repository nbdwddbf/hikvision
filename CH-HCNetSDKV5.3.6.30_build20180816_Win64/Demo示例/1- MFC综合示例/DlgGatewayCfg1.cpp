// DlgGatewayCfg1.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgGatewayCfg1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGatewayCfg dialog


CDlgGatewayCfg::CDlgGatewayCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGatewayCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGatewayCfg)
	m_bEnable = FALSE;
	m_iDelayTime = 0;
	m_csName = _T("");
	m_bLocalEnable = FALSE;
	//}}AFX_DATA_INIT
    m_lServerID = -1;        
    m_iDevIndex = -1;
    m_dwGatawayNum = 0;     // 门禁个数 
    m_lGatewayIndex = -1;    // 门禁索引
    memset(&m_struGateway, 0, sizeof(m_struGateway));

}


void CDlgGatewayCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGatewayCfg)
	DDX_Control(pDX, IDC_COMBO_LOCKWORKMODE, m_LockWorkModeCtrl);
	DDX_Control(pDX, IDC_COMBO_GATEWAY_INDEX, m_comboGatewayIndex);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_DELAY_TIME, m_iDelayTime);
	DDX_Text(pDX, IDC_EDIT_NAME, m_csName);
	DDX_Check(pDX, IDC_CHK_LOCAL_ENABLE, m_bLocalEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGatewayCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgGatewayCfg)
	ON_CBN_SELCHANGE(IDC_COMBO_GATEWAY_INDEX, OnSelchangeComboGatewayIndex)
	ON_BN_CLICKED(IDC_BTN_SET_GATEWAY, OnBtnSetGateway)
	ON_BN_CLICKED(IDC_BNT_OPEN, OnBntOpen)
	ON_BN_CLICKED(IDC_BNT_OPEN_ALL, OnBntOpenAll)
	ON_BN_CLICKED(IDC_BNT_CLOSE, OnBntClose)
	ON_BN_CLICKED(IDC_BNT_CLOSE_ALL, OnBntCloseAll)
	ON_BN_CLICKED(IDC_BNT_NORMALLY_OPEN, OnBntNormallyOpen)
	ON_BN_CLICKED(IDC_BNT_NORMALLY_OPEN_ALL, OnBntNormallyOpenAll)
	ON_BN_CLICKED(IDC_BNT_NORMALLY_CLOSE, OnBntNormallyClose)
	ON_BN_CLICKED(IDC_BNT_NORMALLY_CLOSE_ALL, OnBntNormallyCloseAll)
	ON_BN_CLICKED(IDC_BNT_RETURN_NORMAL, OnBntReturnNormal)
	ON_BN_CLICKED(IDC_BNT_RETURN_NORMAL_ALL, OnBntReturnNormalAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGatewayCfg message handlers

BOOL CDlgGatewayCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    m_dwGatawayNum = (m_dwGatawayNum == 0)?8:m_dwGatawayNum; 
    InitWnd();	
	
    m_comboGatewayIndex.SetCurSel(0);
    OnSelchangeComboGatewayIndex();
    
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgGatewayCfg::InitWnd()
{
    InitGatewayIndexCombo();
	InitLockModeCombo();
}

void CDlgGatewayCfg::InitGatewayIndexCombo()
{
    char szLan[128] = {0};

    m_comboGatewayIndex.ResetContent();
    for (int i = 0; i < m_dwGatawayNum; i++)
    {
        sprintf(szLan, "Gateway %d", i+1);
        m_comboGatewayIndex.InsertString(i, szLan);
        m_comboGatewayIndex.SetItemData(i, i+1);
    }
}

void CDlgGatewayCfg::InitLockModeCombo()
{
	char szLan[128] = {0};
	m_LockWorkModeCtrl.ResetContent();
	g_StringLanType(szLan, "通电开锁", "Power to unlock");
	m_LockWorkModeCtrl.AddString(szLan);
	g_StringLanType(szLan, "断电开锁", "Power Lock");
	m_LockWorkModeCtrl.AddString(szLan);
}

void CDlgGatewayCfg::SetGatewayCfgToWnd(NET_DVR_GATEWAY_CFG &struGateway)
{    
	char strTemp[33] = {0};
    m_bEnable = struGateway.byEnable;
    m_iDelayTime = struGateway.wDelayTime;
    memcpy(strTemp, struGateway.byName, NAME_LEN);
	m_csName.Format("%s", strTemp);
    m_bLocalEnable = struGateway.byLocalEnable;
    m_LockWorkModeCtrl.SetCurSel(struGateway.byLockWorkMode);
}

void CDlgGatewayCfg::GetGatewatCfgFromWnd(NET_DVR_GATEWAY_CFG &struGateway)
{
    struGateway.byEnable = m_bEnable;
    struGateway.wDelayTime = m_iDelayTime;
    struGateway.byLocalEnable = m_bLocalEnable;
    strncpy((char *)struGateway.byName, m_csName.GetBuffer(0), sizeof(struGateway.byName));
    struGateway.byLockWorkMode = m_LockWorkModeCtrl.GetCurSel();
}

BOOL CDlgGatewayCfg::GetGateWayCfg(NET_DVR_GATEWAY_CFG &struGateway)
{
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_GATEWAY_CFG, m_lGatewayIndex, &struGateway, sizeof(struGateway), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_GATEWAY_CFG");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_GATEWAY_CFG");
        return FALSE;
    }
}

BOOL CDlgGatewayCfg::SetGateWayCfg(NET_DVR_GATEWAY_CFG &struGateway)
{
    DWORD dwReturn = 0;
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_GATEWAY_CFG, m_lGatewayIndex, &struGateway, sizeof(struGateway)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_GATEWAY_CFG");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_GATEWAY_CFG");
        return FALSE;
    }
}

void CDlgGatewayCfg::OnSelchangeComboGatewayIndex() 
{
//     m_lGatewayIndex = m_comboGatewayIndex.GetItemData(m_comboGatewayIndex.GetCurSel());	
// 
//     if (!GetGateWayCfg(m_struGateway))
//     {
//         AfxMessageBox("Fail to get gateway config");
//     }
// 
//     SetGatewayCfgToWnd(m_struGateway);
    UpdateData(FALSE);
}

void CDlgGatewayCfg::OnBtnSetGateway() 
{
    UpdateData(TRUE);
    GetGatewatCfgFromWnd(m_struGateway);
    if (!SetGateWayCfg(m_struGateway))
    {
        AfxMessageBox("Fail to set gateway config");
    }
}

BOOL CDlgGatewayCfg::ControlGateway(LONG lGatewayIndex, DWORD dwStaic)
{
    if (NET_DVR_ControlGateway(m_lServerID, lGatewayIndex, dwStaic))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_ControlGateway");
        return TRUE;
    } 
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_ControlGateway");
        return FALSE;
    }
}

void CDlgGatewayCfg::OnBntOpen() 
{
    int nIndex = m_comboGatewayIndex.GetItemData(m_comboGatewayIndex.GetCurSel());
    if (!ControlGateway(nIndex , 1))
    {
        AfxMessageBox("Fail to control gateway");
    }
}

void CDlgGatewayCfg::OnBntOpenAll() 
{
    if (!ControlGateway(-1, 1))
    {
        AfxMessageBox("Fail to control gateway");
    }
    
}

void CDlgGatewayCfg::OnBntClose() 
{
    int nIndex = m_comboGatewayIndex.GetItemData(m_comboGatewayIndex.GetCurSel());
    if (!ControlGateway(nIndex , 0))
    {
        AfxMessageBox("Fail to control gateway");
    }
    
}

void CDlgGatewayCfg::OnBntCloseAll() 
{
    if (!ControlGateway(-1, 0))
    {
        AfxMessageBox("Fail to control gateway");
    }
}

void CDlgGatewayCfg::OnBntNormallyOpen() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_comboGatewayIndex.GetItemData(m_comboGatewayIndex.GetCurSel());
    if (!ControlGateway(nIndex , 2))
    {
        AfxMessageBox("Fail to control gateway");
    }
}

void CDlgGatewayCfg::OnBntNormallyOpenAll() 
{
	// TODO: Add your control notification handler code here
	if (!ControlGateway(-1 , 2))
    {
        AfxMessageBox("Fail to control gateway");
    }
}

void CDlgGatewayCfg::OnBntNormallyClose() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_comboGatewayIndex.GetItemData(m_comboGatewayIndex.GetCurSel());
    if (!ControlGateway(nIndex , 3))
    {
        AfxMessageBox("Fail to control gateway");
    }
}

void CDlgGatewayCfg::OnBntNormallyCloseAll() 
{
	// TODO: Add your control notification handler code here
	if (!ControlGateway(-1 , 3))
    {
        AfxMessageBox("Fail to control gateway");
    }
}

void CDlgGatewayCfg::OnBntReturnNormal() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_comboGatewayIndex.GetItemData(m_comboGatewayIndex.GetCurSel());
    if (!ControlGateway(nIndex , 4))
    {
        AfxMessageBox("Fail to control gateway");
    }
}

void CDlgGatewayCfg::OnBntReturnNormalAll() 
{
	// TODO: Add your control notification handler code here
	if (!ControlGateway(-1 , 4))
    {
        AfxMessageBox("Fail to control gateway");
    }
}
