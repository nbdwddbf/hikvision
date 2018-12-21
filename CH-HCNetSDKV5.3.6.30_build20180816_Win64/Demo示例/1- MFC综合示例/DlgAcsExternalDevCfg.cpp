// DlgAcsExternalDevCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAcsExternalDevCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgAcsExternalDevCfg dialog


DlgAcsExternalDevCfg::DlgAcsExternalDevCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAcsExternalDevCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgAcsExternalDevCfg)
	//}}AFX_DATA_INIT
}


void DlgAcsExternalDevCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAcsExternalDevCfg)
	DDX_Control(pDX, IDC_COMBO_DEV_DETAIL_TYPE, m_wDevDetailType);
	DDX_Control(pDX, IDC_COMBO_QRCODE, m_byQRCodeVerifyMode);
	DDX_Control(pDX, IDC_COMBO_PORT, m_channel);
	DDX_Control(pDX, IDC_COMBO_IDCARD_UP_MODE, m_byIDCardUpMode);
	DDX_Control(pDX, IDC_COMBO_DOOR_MODE, m_byDoorMode);
	DDX_Control(pDX, IDC_COMBO_DEV_TYPE, m_byACSDevType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAcsExternalDevCfg, CDialog)
	//{{AFX_MSG_MAP(DlgAcsExternalDevCfg)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAcsExternalDevCfg message handlers

BOOL DlgAcsExternalDevCfg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
    
    CString csStr;
    char szLan[128] = {0};
    
    m_channel.ResetContent();
    for (int i=0; i<9; i++)
    {
        g_StringLanType(szLan, "", "");
        csStr.Format("%s%d", szLan, i);
        m_channel.InsertString(i, csStr);
    }
    m_channel.SetCurSel(0);

    m_byIDCardUpMode.ResetContent();    
    g_StringLanType(szLan, "仅18位身份证号", "only ID card number");
    m_byIDCardUpMode.InsertString(0, szLan);
    g_StringLanType(szLan, "上传全部信息", "all info");
    m_byIDCardUpMode.InsertString(1, szLan);
    m_byIDCardUpMode.SetCurSel(0);

    m_byQRCodeVerifyMode.ResetContent();    
    g_StringLanType(szLan, "远程中心认证", "remote center");
    m_byQRCodeVerifyMode.InsertString(0, szLan);
    g_StringLanType(szLan, "客户端平台认证", "client");
    m_byQRCodeVerifyMode.InsertString(1, szLan);
    g_StringLanType(szLan, "刷卡开门", "card open door");
    m_byQRCodeVerifyMode.InsertString(2, szLan);
    m_byQRCodeVerifyMode.SetCurSel(0);

    m_byACSDevType.ResetContent();    
    g_StringLanType(szLan, "默认配置", "default");
    m_byACSDevType.InsertString(0, szLan);
    g_StringLanType(szLan, "身份证读卡器", "IDCard reader");
    m_byACSDevType.InsertString(1, szLan);
    g_StringLanType(szLan, "IC读卡器", "IC reader");
    m_byACSDevType.InsertString(2, szLan);
    g_StringLanType(szLan, "二维码读卡器", "QRCode reader");
    m_byACSDevType.InsertString(3, szLan);
    g_StringLanType(szLan, "指纹读卡器", "fingerprint reader");
    m_byACSDevType.InsertString(4, szLan);
    g_StringLanType(szLan, "字符屏和二维码", "QRCodeReader and Screen");
    m_byACSDevType.InsertString(5, szLan);
    g_StringLanType(szLan, "收卡器", "recycle Card");
    m_byACSDevType.InsertString(6, szLan);
    g_StringLanType(szLan, "字符屏", "character screen");
    m_byACSDevType.InsertString(7, szLan);
	g_StringLanType(szLan, "指纹头", "fingerprint head");
    m_byACSDevType.InsertString(8, szLan);
	g_StringLanType(szLan, "语音模块", "voice module");
    m_byACSDevType.InsertString(9, szLan);
    g_StringLanType(szLan, "人证设备", "people and id card");
    m_byACSDevType.InsertString(10, szLan);
    m_byACSDevType.SetCurSel(0);

    m_byDoorMode.ResetContent();    
    g_StringLanType(szLan, "进门", "in door");
    m_byDoorMode.InsertString(0, szLan);
    g_StringLanType(szLan, "出门", "out door");
    m_byDoorMode.InsertString(1, szLan);
    m_byDoorMode.SetCurSel(0);

	m_wDevDetailType.ResetContent();    
    g_StringLanType(szLan, "iDR210", "iDR210");
    m_wDevDetailType.InsertString(0, szLan);
    g_StringLanType(szLan, "iIDM10", "iIDM10");
    m_wDevDetailType.InsertString(1, szLan);
    g_StringLanType(szLan, "海康身份证阅读器", "HikIDCardReader");
    m_wDevDetailType.InsertString(2, szLan);
    m_wDevDetailType.SetCurSel(0);
	
		

    //OnBtnGet();
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgAcsExternalDevCfg::OnButtonGet()
{
	// TODO: Add your control notification handler code here
    DWORD dwReturn = 0;
    NET_DVR_ACS_EXTERNAL_DEV_CFG struAcsDevCfg = {0};
    struAcsDevCfg.dwSize = sizeof(struAcsDevCfg);
    
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ACS_EXTERNAL_DEV_CFG, m_channel.GetCurSel(), &struAcsDevCfg, sizeof(struAcsDevCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ACS_EXTERNAL_DEV_CFG Failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ACS_EXTERNAL_DEV_CFG SUCC");
        m_byIDCardUpMode.SetCurSel(struAcsDevCfg.byIDCardUpMode);
        m_byQRCodeVerifyMode.SetCurSel(struAcsDevCfg.byCardVerifyMode);
        m_byACSDevType.SetCurSel(struAcsDevCfg.byACSDevType);
        m_byDoorMode.SetCurSel(struAcsDevCfg.byDoorMode);
        m_wDevDetailType.SetCurSel(struAcsDevCfg.wDevDetailType);
        UpdateData(FALSE);
	}
	
}

void DlgAcsExternalDevCfg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_ACS_EXTERNAL_DEV_CFG struAcsDevCfg = {0};
    struAcsDevCfg.dwSize = sizeof(struAcsDevCfg);
    
    struAcsDevCfg.byIDCardUpMode = m_byIDCardUpMode.GetCurSel();
    struAcsDevCfg.byCardVerifyMode = m_byQRCodeVerifyMode.GetCurSel();
    struAcsDevCfg.byACSDevType = m_byACSDevType.GetCurSel();
    struAcsDevCfg.byDoorMode = m_byDoorMode.GetCurSel();
	struAcsDevCfg.wDevDetailType = m_wDevDetailType.GetCurSel();
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_ACS_EXTERNAL_DEV_CFG, m_channel.GetCurSel(), &struAcsDevCfg, sizeof(struAcsDevCfg)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ACS_EXTERNAL_DEV_CFG Failed");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ACS_EXTERNAL_DEV_CFG SUCC");
	}
	
}
