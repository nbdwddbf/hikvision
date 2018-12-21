// DlgVideoIntercomRelateDevCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVideoIntercomRelateDevCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomRelateDevCfg dialog


CDlgVideoIntercomRelateDevCfg::CDlgVideoIntercomRelateDevCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoIntercomRelateDevCfg::IDD, pParent)
    , m_csManagedID(_T(""))
{
	//{{AFX_DATA_INIT(CDlgVideoIntercomRelateDevCfg)
	m_strManageUnitIP = _T("");
	m_strOutdoorUnitIP = _T("");
	m_strSIPServerIP = _T("");
	m_csAgainIPAddr = _T("");
	m_csCentralIP = _T("");
	m_wCentralPort = 0;
	m_struIndoorUnit = _T("");
	//}}AFX_DATA_INIT
	m_nUnitType = ENUM_MANAGE_UINT;
	m_lServerID = -1;
	m_iDevIndex = -1;
}


void CDlgVideoIntercomRelateDevCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgVideoIntercomRelateDevCfg)
    DDX_Control(pDX, IDC_COMBO_INDOOR, m_byIndoorConnectMode);
    DDX_Control(pDX, IDC_COMBO_INOUT, m_byOutInConnectMode);
    DDX_Control(pDX, IDC_COMBO_OUTDOOR_TYPE, m_cmbOutDoorType);
    DDX_Text(pDX, IDC_EDIT_MANAGE_UINT_IP, m_strManageUnitIP);
    DDX_Text(pDX, IDC_EDIT_OUTDOOR_UNIT_IP, m_strOutdoorUnitIP);
    DDX_Text(pDX, IDC_EDIT_SIP_SERVER_IP, m_strSIPServerIP);
    DDX_Text(pDX, IDC_EDIT_AGAIN_IPADDR, m_csAgainIPAddr);
    DDX_Text(pDX, IDC_EDIT_CENTRAL_IP, m_csCentralIP);
    DDX_Text(pDX, IDC_EDIT_CENTRAL_PORT, m_wCentralPort);
    DDX_Text(pDX, IDC_EDIT_INDOOR_UNIT_IP, m_struIndoorUnit);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_MANAGED_ID, m_csManagedID);
}


BEGIN_MESSAGE_MAP(CDlgVideoIntercomRelateDevCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVideoIntercomRelateDevCfg)
	ON_BN_CLICKED(IDC_RADIO_INDOOR_UNIT, OnRadioIndoorUnit)
	ON_BN_CLICKED(IDC_RADIO_MANAGE_UNIT, OnRadioManageUnit)
	ON_BN_CLICKED(IDC_RADIO_OUTDOOR_UNIT, OnRadioOutdoorUnit)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_RADIO_FENCE_UNIT, OnRadioFenceUnit)
	ON_BN_CLICKED(IDC_RADIO_AGAIN_UNIT, OnRadioAgainUnit)
	ON_BN_CLICKED(IDC_RADIO_VILLA_OUTDOOR_UNIT, OnRadioVillaOutdoorUnit)
	//}}AFX_MSG_MAP
    ON_COMMAND(IDC_RADIO_ID_REG_UNIT, &CDlgVideoIntercomRelateDevCfg::OnRadioIdRegUnit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomRelateDevCfg message handlers

void CDlgVideoIntercomRelateDevCfg::OnRadioIndoorUnit() 
{
	m_nUnitType = ENUM_INDOOR_UINT;
	CheckRaidoBtn();
}

void CDlgVideoIntercomRelateDevCfg::OnRadioManageUnit() 
{
	m_nUnitType = ENUM_MANAGE_UINT;
	CheckRaidoBtn();
}

void CDlgVideoIntercomRelateDevCfg::OnRadioOutdoorUnit() 
{
	m_nUnitType = ENUM_OUTDOOR_UINT;
	CheckRaidoBtn();
}

void CDlgVideoIntercomRelateDevCfg::OnBtnSet() 
{
	char szError[32] = "\0";
	if (SetVideoIntercomRelateDevCfg())
	{   
		g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}

void CDlgVideoIntercomRelateDevCfg::OnBtnGet() 
{
	char szError[64] = "\0";
	if (!GetVideoIntercomRelateDevCfg())
	{   
		g_StringLanType(szError, "获取参数失败","Get parameters failed");
		AfxMessageBox(szError);
	}
}

void CDlgVideoIntercomRelateDevCfg::CheckRaidoBtn()
{
    CheckDlgButton(IDC_RADIO_INDOOR_UNIT,m_nUnitType == ENUM_INDOOR_UINT);
    CheckDlgButton(IDC_RADIO_OUTDOOR_UNIT,m_nUnitType == ENUM_OUTDOOR_UINT);
    CheckDlgButton(IDC_RADIO_ID_REG_UNIT, m_nUnitType == ENUM_ID_REG_DEVICE);
    CheckDlgButton(IDC_RADIO_MANAGE_UNIT,m_nUnitType == ENUM_MANAGE_UINT);
    CheckDlgButton(IDC_RADIO_FENCE_UNIT, m_nUnitType == ENUM_FENCE_UINT);
    CheckDlgButton(IDC_RADIO_VILLA_OUTDOOR_UNIT, m_nUnitType == ENUM_VILLA_OUTDOOR_UNIT);
    CheckDlgButton(IDC_RADIO_AGAIN_UNIT, m_nUnitType == ENUM_AGAIN_UNIT);
    
    GetDlgItem(IDC_EDIT_MANAGE_UINT_IP)->EnableWindow(m_nUnitType == ENUM_INDOOR_UINT || m_nUnitType == ENUM_OUTDOOR_UINT || m_nUnitType == ENUM_ID_REG_DEVICE || m_nUnitType == ENUM_FENCE_UINT || m_nUnitType == ENUM_VILLA_OUTDOOR_UNIT);
    GetDlgItem(IDC_EDIT_OUTDOOR_UNIT_IP)->EnableWindow(m_nUnitType == ENUM_INDOOR_UINT || m_nUnitType == ENUM_OUTDOOR_UINT || m_nUnitType == ENUM_ID_REG_DEVICE || m_nUnitType == ENUM_FENCE_UINT || m_nUnitType == ENUM_VILLA_OUTDOOR_UNIT);
    GetDlgItem(IDC_EDIT_SIP_SERVER_IP)->EnableWindow(m_nUnitType == ENUM_INDOOR_UINT || m_nUnitType == ENUM_OUTDOOR_UINT || m_nUnitType == ENUM_ID_REG_DEVICE || m_nUnitType == ENUM_MANAGE_UINT || m_nUnitType == ENUM_FENCE_UINT || m_nUnitType == ENUM_VILLA_OUTDOOR_UNIT || m_nUnitType == ENUM_AGAIN_UNIT);
    GetDlgItem(IDC_EDIT_AGAIN_IPADDR)->EnableWindow(m_nUnitType == ENUM_INDOOR_UINT || m_nUnitType == ENUM_AGAIN_UNIT);
    GetDlgItem(IDC_COMBO_OUTDOOR_TYPE)->EnableWindow(m_nUnitType == ENUM_INDOOR_UINT);
    GetDlgItem(IDC_EDIT_CENTRAL_IP)->EnableWindow(m_nUnitType == ENUM_AGAIN_UNIT);
    GetDlgItem(IDC_EDIT_CENTRAL_PORT)->EnableWindow(m_nUnitType == ENUM_AGAIN_UNIT);
    GetDlgItem(IDC_EDIT_INDOOR_UNIT_IP)->EnableWindow(m_nUnitType == ENUM_INDOOR_UINT || m_nUnitType == ENUM_AGAIN_UNIT);
    GetDlgItem(IDC_COMBO_INDOOR)->EnableWindow(m_nUnitType == ENUM_INDOOR_UINT);
    GetDlgItem(IDC_COMBO_INOUT)->EnableWindow(m_nUnitType == ENUM_INDOOR_UINT);
    GetDlgItem(IDC_EDIT_MANAGED_ID)->EnableWindow(m_nUnitType == ENUM_INDOOR_UINT || m_nUnitType == ENUM_OUTDOOR_UINT || m_nUnitType == ENUM_VILLA_OUTDOOR_UNIT || m_nUnitType == ENUM_ID_REG_DEVICE);
}


BOOL CDlgVideoIntercomRelateDevCfg::GetVideoIntercomRelateDevCfg()
{
	DWORD dwReturn = 0;
	BOOL  bRst = FALSE;
	
	NET_DVR_VIDEO_INTERCOM_RELATEDEV_CFG struRelateDevCfg = {0};
	struRelateDevCfg.dwSize = sizeof(struRelateDevCfg);
	
	if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_VIDEO_INTERCOM_RELATEDEV_CFG,0,&struRelateDevCfg,sizeof(struRelateDevCfg),&dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VIDEO_INTERCOM_RELATEDEV_CFG");
		ShowParamToWnd(&struRelateDevCfg);
		bRst = TRUE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEO_INTERCOM_RELATEDEV_CFG");
		bRst = FALSE;
	}
	
	return bRst;
}

BOOL CDlgVideoIntercomRelateDevCfg::SetVideoIntercomRelateDevCfg()
{
	BOOL  bRst = FALSE;
	
	NET_DVR_VIDEO_INTERCOM_RELATEDEV_CFG struRelateDevCfg = {0};
	struRelateDevCfg.dwSize = sizeof(struRelateDevCfg);
	
	GetParamFromWnd(&struRelateDevCfg);
	
	if (NET_DVR_SetDVRConfig(m_lServerID,NET_DVR_SET_VIDEO_INTERCOM_RELATEDEV_CFG,0,&struRelateDevCfg,sizeof(struRelateDevCfg)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VIDEO_INTERCOM_RELATEDEV_CFG");
		bRst = TRUE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VIDEO_INTERCOM_RELATEDEV_CFG");
		bRst = FALSE;
	}
	
	return bRst;
}

void CDlgVideoIntercomRelateDevCfg::ShowParamToWnd(NET_DVR_VIDEO_INTERCOM_RELATEDEV_CFG* pRelateDevCfg)
{   
    m_nUnitType =  pRelateDevCfg->byUnitType;
    m_strOutdoorUnitIP = "";
    m_strManageUnitIP = "";
    m_strSIPServerIP = "";
    m_struIndoorUnit = "";
    if (m_nUnitType == ENUM_OUTDOOR_UINT || m_nUnitType == ENUM_FENCE_UINT ||  m_nUnitType == ENUM_ID_REG_DEVICE)
    {
        m_strOutdoorUnitIP = pRelateDevCfg->uVideoIntercomUnit.struMainOutdoorUnit.struMainOutdoorUnit.sIpV4;
        m_strManageUnitIP = pRelateDevCfg->uVideoIntercomUnit.struMainOutdoorUnit.struManageUnit.sIpV4;
        m_strSIPServerIP = pRelateDevCfg->uVideoIntercomUnit.struMainOutdoorUnit.struSIPServer.sIpV4;
        m_csManagedID = pRelateDevCfg->uVideoIntercomUnit.struMainOutdoorUnit.byManageCenterID;
    }
    else if (m_nUnitType == ENUM_MANAGE_UINT)
    {
        m_strSIPServerIP = pRelateDevCfg->uVideoIntercomUnit.struManageUnit.struSIPServer.sIpV4;
    }
    else if (m_nUnitType == ENUM_INDOOR_UINT)
    {
        m_strOutdoorUnitIP = pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.struOutdoorUnit.sIpV4;
        m_strManageUnitIP = pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.struManageUnit.sIpV4;
        m_strSIPServerIP = pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.struSIPServer.sIpV4;
        m_csAgainIPAddr = pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.struAgainUnit.sIpV4;
        m_cmbOutDoorType.SetCurSel(pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.byOutDoorType);
        m_struIndoorUnit = pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.struIndoorUnit.sIpV4;

        if (g_ValidIPv6(pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.struIndoorUnit.byIPv6))
        {
            m_struIndoorUnit.Format("%s",pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.struIndoorUnit.byIPv6);
        }
        else
        {
            m_struIndoorUnit.Format("%s", pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.struIndoorUnit.sIpV4);
        }

        m_byOutInConnectMode.SetCurSel(pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.byOutInConnectMode);
        m_byIndoorConnectMode.SetCurSel(pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.byIndoorConnectMode);
        m_csManagedID = pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.byManageCenterID;
    }
    else if (m_nUnitType == ENUM_VILLA_OUTDOOR_UNIT)
    {
        m_strOutdoorUnitIP = pRelateDevCfg->uVideoIntercomUnit.struVillaUnit.struMainOutdoorUnit.sIpV4;
        m_strManageUnitIP = pRelateDevCfg->uVideoIntercomUnit.struVillaUnit.struManageUnit.sIpV4;
        m_strSIPServerIP = pRelateDevCfg->uVideoIntercomUnit.struVillaUnit.struSIPServer.sIpV4;
        m_csManagedID = pRelateDevCfg->uVideoIntercomUnit.struVillaUnit.byManageCenterID;
    }
    else if (m_nUnitType == ENUM_AGAIN_UNIT)
    {
        m_strSIPServerIP = pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.struSIPServer.sIpV4;
        m_wCentralPort = pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.wCenterPort;
        
        if (g_ValidIPv6(pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.struCenterAddr.byIPv6))
        {
            m_csCentralIP.Format("%s",pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.struCenterAddr.byIPv6);
        }
        else
        {
            m_csCentralIP.Format("%s", pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.struCenterAddr.sIpV4);
        }

        if (g_ValidIPv6(pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.struIndoorUnit.byIPv6))
        {
            m_struIndoorUnit.Format("%s",pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.struIndoorUnit.byIPv6);
        }
        else
        {
            m_struIndoorUnit.Format("%s", pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.struIndoorUnit.sIpV4);
        }


        if (g_ValidIPv6(pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.struAgainAddr.byIPv6))
        {
            m_csAgainIPAddr.Format("%s", pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.struAgainAddr.byIPv6);
        }
        else
        {
            m_csAgainIPAddr.Format("%s", pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.struAgainAddr.sIpV4);
        }

    }
	CheckRaidoBtn();
	
	UpdateData(FALSE);
}

void CDlgVideoIntercomRelateDevCfg::GetParamFromWnd(NET_DVR_VIDEO_INTERCOM_RELATEDEV_CFG* pRelateDevCfg)
{
	UpdateData(TRUE);
	
    if (m_nUnitType == ENUM_OUTDOOR_UINT || m_nUnitType == ENUM_FENCE_UINT || m_nUnitType == ENUM_ID_REG_DEVICE)
	{
		strncpy(pRelateDevCfg->uVideoIntercomUnit.struMainOutdoorUnit.struMainOutdoorUnit.sIpV4,m_strOutdoorUnitIP,16);
		strncpy(pRelateDevCfg->uVideoIntercomUnit.struMainOutdoorUnit.struManageUnit.sIpV4,m_strManageUnitIP,16);
		strncpy(pRelateDevCfg->uVideoIntercomUnit.struMainOutdoorUnit.struSIPServer.sIpV4,m_strSIPServerIP,16);
        strncpy((char*)pRelateDevCfg->uVideoIntercomUnit.struMainOutdoorUnit.byManageCenterID, m_csManagedID, 32);
	}
	else if (m_nUnitType == ENUM_MANAGE_UINT)
	{
		strncpy(pRelateDevCfg->uVideoIntercomUnit.struManageUnit.struSIPServer.sIpV4,m_strSIPServerIP,16);
	}
	else if (m_nUnitType == ENUM_INDOOR_UINT)
	{
		strncpy(pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.struOutdoorUnit.sIpV4,m_strOutdoorUnitIP,16);
		strncpy(pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.struManageUnit.sIpV4,m_strManageUnitIP,16);
		strncpy(pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.struSIPServer.sIpV4,m_strSIPServerIP,16);
        strncpy((char*)pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.byManageCenterID, m_csManagedID, 32);
        if (g_ValidIPv6( (BYTE*)(LPSTR)(LPCTSTR)m_csAgainIPAddr))
        {
            strncpy((char*)pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.struAgainUnit.byIPv6,m_csAgainIPAddr,128);
        }
        else
        {
            strncpy(pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.struAgainUnit.sIpV4,m_csAgainIPAddr,16);
        }

        if (g_ValidIPv6( (BYTE*)(LPSTR)(LPCTSTR)m_struIndoorUnit))
        {
            strncpy((char*)pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.struIndoorUnit.byIPv6,m_struIndoorUnit,128);
        }
        else
        {
            strncpy(pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.struIndoorUnit.sIpV4,m_struIndoorUnit,16);
        }

        pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.byOutDoorType = m_cmbOutDoorType.GetItemData(m_cmbOutDoorType.GetCurSel());
        pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.byOutInConnectMode = m_byOutInConnectMode.GetItemData(m_byOutInConnectMode.GetCurSel());
        pRelateDevCfg->uVideoIntercomUnit.struIndoorUnit.byIndoorConnectMode = m_byIndoorConnectMode.GetItemData(m_byIndoorConnectMode.GetCurSel());
	}
	else if (m_nUnitType == ENUM_VILLA_OUTDOOR_UNIT)
	{
        strncpy(pRelateDevCfg->uVideoIntercomUnit.struVillaUnit.struMainOutdoorUnit.sIpV4,m_strOutdoorUnitIP,16);
        strncpy(pRelateDevCfg->uVideoIntercomUnit.struVillaUnit.struManageUnit.sIpV4,m_strManageUnitIP,16);
		strncpy(pRelateDevCfg->uVideoIntercomUnit.struVillaUnit.struSIPServer.sIpV4,m_strSIPServerIP,16);
        strncpy((char*)pRelateDevCfg->uVideoIntercomUnit.struVillaUnit.byManageCenterID, m_csManagedID, 32);
	}
    else if (m_nUnitType == ENUM_AGAIN_UNIT)
    {
        strncpy(pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.struSIPServer.sIpV4,m_strSIPServerIP,16);


        if (g_ValidIPv6( (BYTE*)(LPSTR)(LPCTSTR)m_csCentralIP))
        {
            strncpy((char*)pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.struCenterAddr.byIPv6,m_csCentralIP,128);
        }
        else
        {
            strncpy(pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.struCenterAddr.sIpV4,m_csCentralIP,16);
        }

        if (g_ValidIPv6( (BYTE*)(LPSTR)(LPCTSTR)m_struIndoorUnit))
        {
            strncpy((char*)pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.struIndoorUnit.byIPv6,m_struIndoorUnit,128);
        }
        else
        {
            strncpy(pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.struIndoorUnit.sIpV4,m_struIndoorUnit,16);
        }

        if (g_ValidIPv6((BYTE*)(LPSTR)(LPCTSTR)m_csAgainIPAddr))
        {
            strncpy((char*)pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.struAgainAddr.byIPv6, m_csAgainIPAddr, 128);
        }
        else
        {
            strncpy(pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.struAgainAddr.sIpV4, m_csAgainIPAddr, 16);
        }

        pRelateDevCfg->uVideoIntercomUnit.struAgainUnit.wCenterPort = m_wCentralPort;
    }
	pRelateDevCfg->byUnitType = m_nUnitType;
}
void CDlgVideoIntercomRelateDevCfg::OnRadioFenceUnit() 
{
	// TODO: Add your control notification handler code here
	m_nUnitType = ENUM_FENCE_UINT;
	CheckRaidoBtn();
}

void CDlgVideoIntercomRelateDevCfg::OnRadioAgainUnit() 
{
	// TODO: Add your control notification handler code here
    m_nUnitType = ENUM_AGAIN_UNIT;
	CheckRaidoBtn();	
}

void CDlgVideoIntercomRelateDevCfg::OnRadioVillaOutdoorUnit() 
{
	// TODO: Add your control notification handler code here
    m_nUnitType = ENUM_VILLA_OUTDOOR_UNIT;
	CheckRaidoBtn();
}

BOOL CDlgVideoIntercomRelateDevCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    char szLan[128] = {0};
    DWORD  dwIndex = 0;
    m_cmbOutDoorType.ResetContent();
    g_StringLanType(szLan,"保留","Reserved");
    m_cmbOutDoorType.AddString(szLan);
    m_cmbOutDoorType.SetItemData(dwIndex,0);
    dwIndex++;

  
    g_StringLanType(szLan,"单元门口机","OutDoor Unit");
    m_cmbOutDoorType.AddString(szLan);
    m_cmbOutDoorType.SetItemData(dwIndex,1);
    dwIndex++;

    g_StringLanType(szLan,"别墅门口机","Villa OutDoor Unit");
    m_cmbOutDoorType.AddString(szLan);
    m_cmbOutDoorType.SetItemData(dwIndex,2);

    m_cmbOutDoorType.SetCurSel(0);


    dwIndex = 0;
    m_byOutInConnectMode.ResetContent();
    g_StringLanType(szLan,"无效","invalid");
    m_byOutInConnectMode.AddString(szLan);
    m_byOutInConnectMode.SetItemData(dwIndex,0);
    dwIndex++;
    
    g_StringLanType(szLan,"同一局域网","same lan");
    m_byOutInConnectMode.AddString(szLan);
    m_byOutInConnectMode.SetItemData(dwIndex,1);
    dwIndex++;    
    
    g_StringLanType(szLan,"不同局域网","different lan");
    m_byOutInConnectMode.AddString(szLan);
    m_byOutInConnectMode.SetItemData(dwIndex,2);
        
    m_byOutInConnectMode.SetCurSel(0);


    dwIndex = 0;
    m_byIndoorConnectMode.ResetContent();
    g_StringLanType(szLan,"无效","invalid");
    m_byIndoorConnectMode.AddString(szLan);
    m_byIndoorConnectMode.SetItemData(dwIndex,0);
    dwIndex++;

    g_StringLanType(szLan,"无线网","wireless");
    m_byIndoorConnectMode.AddString(szLan);
    m_byIndoorConnectMode.SetItemData(dwIndex,1);
    dwIndex++;    
    
    g_StringLanType(szLan,"有线网","wired");
    m_byIndoorConnectMode.AddString(szLan);
    m_byIndoorConnectMode.SetItemData(dwIndex,2);
    
    m_byIndoorConnectMode.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgVideoIntercomRelateDevCfg::OnRadioIdRegUnit()
{
    // TODO:  在此添加命令处理程序代码
    m_nUnitType = ENUM_ID_REG_DEVICE;
    CheckRaidoBtn();
}
