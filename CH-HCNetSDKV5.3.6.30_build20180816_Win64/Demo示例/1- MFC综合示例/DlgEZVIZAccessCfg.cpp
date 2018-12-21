// DlgEZVIZAccessCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgEZVIZAccessCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEZVIZAccessCfg dialog


CDlgEZVIZAccessCfg::CDlgEZVIZAccessCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEZVIZAccessCfg::IDD, pParent)
	, m_csVerificationCode(_T(""))
    , m_strOfflineStatus(_T(""))
{
	//{{AFX_DATA_INIT(CDlgEZVIZAccessCfg)
	m_csDomainName = _T("");
    m_csOperateCode = _T("");
	//}}AFX_DATA_INIT
}


void CDlgEZVIZAccessCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgEZVIZAccessCfg)
    DDX_Control(pDX, IDC_COMBO_REDIRECT, m_cmbRedirect);
    DDX_Control(pDX, IDC_COMBO_ENABLE, m_cbEnable);
    DDX_Control(pDX, IDC_COMBO_DEV_STATUS, m_cbDeviceStatus);
    DDX_Text(pDX, IDC_EDIT_DOMAINNAME, m_csDomainName);
    DDX_Control(pDX, IDC_COMBO_NET_MODE, m_cmbNetMode);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_CODE_VV, m_csVerificationCode);
    DDX_Text(pDX, IDC_EDIT_OPERATE_CODE, m_csOperateCode);
    DDX_Text(pDX, IDC_STATIC_OFFLINE_STATUS, m_strOfflineStatus);
}


BEGIN_MESSAGE_MAP(CDlgEZVIZAccessCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgEZVIZAccessCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEZVIZAccessCfg message handlers

void CDlgEZVIZAccessCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	char szLan[64]={0};
	g_StringLanType(szLan,"通道非法","channel invalid");
	if (m_iCurChanNO>1024)
	{
		g_StringLanType(szLan,"通道非法","channel invalid");
		MessageBox(szLan);
		return;
	}
	
	DWORD dwRet=0;
	NET_DVR_EZVIZ_ACCESS_CFG struEZVIZCfg={0};
	struEZVIZCfg.dwSize = sizeof(struEZVIZCfg);
	CString strErr;
    if (!NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_EZVIZ_ACCESS_CFG,m_iCurChanNO,&struEZVIZCfg,sizeof(struEZVIZCfg),&dwRet))
    {
        strErr.Format("NET_DVR_GET_EZVIZ_ACCESS_CFG chan[%d] failed! error code[%d]", m_iCurChanNO, NET_DVR_GetLastError());
        MessageBox(strErr);
	       g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_GET_EZVIZ_ACCESS_CFG");
           return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_GET_EZVIZ_ACCESS_CFG");
    }
	
	m_cbEnable.SetCurSel(struEZVIZCfg.byEnable);
	if (struEZVIZCfg.byDeviceStatus > 0) //2014-03-21
	{
		m_cbDeviceStatus.SetCurSel(struEZVIZCfg.byDeviceStatus - 1);
	}
    m_cmbRedirect.SetCurSel(struEZVIZCfg.byAllowRedirect);
    if (struEZVIZCfg.byAllowRedirect == 1)
    {
        m_csDomainName = struEZVIZCfg.byDomainName;
    }
	m_csVerificationCode = struEZVIZCfg.byVerificationCode;
    m_csOperateCode = struEZVIZCfg.byOperateCode;
    if (struEZVIZCfg.byNetMode > 0)
    {
        m_cmbNetMode.SetCurSel(struEZVIZCfg.byNetMode - 1);
    }
    switch (struEZVIZCfg.byOfflineStatus)
    {
    case 0:
        g_StringLanType(szLan, "保留", "reserve");
        m_strOfflineStatus.Format("%s", szLan);
        break;
    case 1:
        g_StringLanType(szLan, "萤石注册验证码无效", "EZVIZ registration verification code is invalid");
        m_strOfflineStatus.Format("%s", szLan);
        break;
    default:
        break;
    }

	UpdateData(FALSE);

}

BOOL CDlgEZVIZAccessCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	int iCurChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iCurChanIndex < 0)
    {
        iCurChanIndex = 0;
    }
	m_iCurChanNO = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iCurChanIndex].iChannelNO; 
    char szLan[128] = {0};

    m_cmbRedirect.ResetContent();
    g_StringLanType(szLan,"保留","reserve");
    m_cmbRedirect.AddString(szLan);
    g_StringLanType(szLan,"启用","Enable");
    m_cmbRedirect.AddString(szLan);
    g_StringLanType(szLan,"不启用","Disable");
    m_cmbRedirect.AddString(szLan);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEZVIZAccessCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here

	char szLan[64]={0};
	if (m_iCurChanNO>1024)
	{
		g_StringLanType(szLan,"通道非法","channel invalid");
		MessageBox(szLan);
		return;
	}

	UpdateData(TRUE);

	DWORD dwRet=0;
	NET_DVR_EZVIZ_ACCESS_CFG struEZVIZCfg={0};
	struEZVIZCfg.dwSize = sizeof(struEZVIZCfg);
	struEZVIZCfg.byEnable = m_cbEnable.GetCurSel();
	struEZVIZCfg.byDeviceStatus = m_cbDeviceStatus.GetCurSel()+1;//2014-03-21
    struEZVIZCfg.byAllowRedirect = m_cmbRedirect.GetCurSel();
    strncpy((char*)struEZVIZCfg.byDomainName,m_csDomainName.GetBuffer(0),MAX_DOMAIN_NAME);
	strncpy((char*)struEZVIZCfg.byVerificationCode, m_csVerificationCode.GetBuffer(0), 32);
    strncpy((char*)struEZVIZCfg.byOperateCode, m_csOperateCode.GetBuffer(0), 64);
    struEZVIZCfg.byNetMode = m_cmbNetMode.GetCurSel() + 1;
	CString strErr;

	if (!NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_EZVIZ_ACCESS_CFG,m_iCurChanNO,&struEZVIZCfg,sizeof(struEZVIZCfg)))
	{
		strErr.Format("NET_DVR_SET_EZVIZ_ACCESS_CFG chan[%d] failed! error code[%d]", m_iCurChanNO, NET_DVR_GetLastError());
		MessageBox(strErr);
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_SET_EZVIZ_ACCESS_CFG");
		return;
	}
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_SET_EZVIZ_ACCESS_CFG");
    }
	
	MessageBox("NET_DVR_SET_EZVIZ_ACCESS_CFG suss!");	
}
