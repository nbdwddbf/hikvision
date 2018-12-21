// DlgVideoIntercomDeviceIDCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVideoIntercomDeviceIDCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomDeviceIDCfg dialog


CDlgVideoIntercomDeviceIDCfg::CDlgVideoIntercomDeviceIDCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoIntercomDeviceIDCfg::IDD, pParent)
    , m_nAgainOutDoorPeriod(0)
    , m_nAgainOutDoorBuildingNum(0)
    , m_nAgainOutDoorUnitNum(0)
    , m_nAgainOutDoorFloorNumber(0)
    , m_nAgainOutDoorDevIndex(0)
{
	//{{AFX_DATA_INIT(CDlgVideoIntercomDeviceIDCfg)
	m_nIndoorFloorNumber = 0;
	m_nIndoorRoomNumber = 0;
	m_nManageDevIndex = 0;
	m_nManagePeriod = 0;
	m_nOutdoorBuildingNumber = 0;
	m_nOutdoorDevIndex = 0;
	m_nOutdoorFloorNumber = 0;
	m_nOutdoorPeriod = 0;
	m_nOutdoorUnitNumber = 0;
	m_nDevIndex = 0;
	m_bChkAutoReg = FALSE;
	m_nFenceDevIndex = 0;
	m_nFencePeriod = 0;
	m_nVillaOutDoorDevIndex = 0;
	m_nVillaOutDoorBuildingNum = 0;
	m_nVillaOutDoorFloorNumber = 0;
	m_nVillaOutDoorPeriod = 0;
	m_nVillaOutDoorUnitNum = 0;
	//}}AFX_DATA_INIT
	m_nUnitType = 0;
	m_lServerID = -1;
	m_iDevIndex = -1;
}


void CDlgVideoIntercomDeviceIDCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgVideoIntercomDeviceIDCfg)
    DDX_Text(pDX, IDC_EDIT_INDOOR_FLOOR_NUMBER, m_nIndoorFloorNumber);
    DDX_Text(pDX, IDC_EDIT_INDOOR_ROOM_NUMBER, m_nIndoorRoomNumber);
    DDX_Text(pDX, IDC_EDIT_MANAGE_DEVINDEX, m_nManageDevIndex);
    DDX_Text(pDX, IDC_EDIT_MANAGE_PERIOD, m_nManagePeriod);
    DDX_Text(pDX, IDC_EDIT_OUTDOOR_BUILDING_NUMBER, m_nOutdoorBuildingNumber);
    DDX_Text(pDX, IDC_EDIT_OUTDOOR_DEVINDEX, m_nOutdoorDevIndex);
    DDX_Text(pDX, IDC_EDIT_OUTDOOR_FLOOR_NUMBER, m_nOutdoorFloorNumber);
    DDX_Text(pDX, IDC_EDIT_OUTDOOR_PERIOD, m_nOutdoorPeriod);
    DDX_Text(pDX, IDC_EDIT_OUTDOOR_UNIT_NUMBER, m_nOutdoorUnitNumber);
    DDX_Text(pDX, IDC_EDIT_DEVICE_INDEX, m_nDevIndex);
    DDX_Check(pDX, IDC_CHK_AUTO_REG, m_bChkAutoReg);
    DDX_Text(pDX, IDC_EDIT_FENCE_DEVINDEX, m_nFenceDevIndex);
    DDX_Text(pDX, IDC_EDIT_FENCE_PERIOD, m_nFencePeriod);
    DDX_Text(pDX, IDC_EDIT_VILLA_OUTDOOR_DEVINDEX, m_nVillaOutDoorDevIndex);
    DDX_Text(pDX, IDC_EDIT_VILLA_OUTDOOR_BUILDING_NUMBER, m_nVillaOutDoorBuildingNum);
    DDX_Text(pDX, IDC_EDIT_VILLA_OUTDOOR_FLOOR_NUMBER, m_nVillaOutDoorFloorNumber);
    DDX_Text(pDX, IDC_EDIT_VILLA_OUTDOOR_PERIOD, m_nVillaOutDoorPeriod);
    DDX_Text(pDX, IDC_EDIT_VILLA_OUTDOOR_UNIT_NUMBER, m_nVillaOutDoorUnitNum);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_AGAIN_OUTDOOR_PERIOD, m_nAgainOutDoorPeriod);
    DDX_Text(pDX, IDC_EDIT_AGAIN_OUTDOOR_BUILDING_NUMBER, m_nAgainOutDoorBuildingNum);
    DDX_Text(pDX, IDC_EDIT_AGAIN_OUTDOOR_UNIT_NUMBER, m_nAgainOutDoorUnitNum);
    DDX_Text(pDX, IDC_EDIT_AGAIN_OUTDOOR_FLOOR_NUMBER, m_nAgainOutDoorFloorNumber);
    DDX_Text(pDX, IDC_EDIT_AGAIN_OUTDOOR_DEVINDEX, m_nAgainOutDoorDevIndex);
}


BEGIN_MESSAGE_MAP(CDlgVideoIntercomDeviceIDCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVideoIntercomDeviceIDCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_RADIO_INDOOR_UNIT, OnRadioIndoorUnit)
	ON_BN_CLICKED(IDC_RADIO_MANAGE_UNIT, OnRadioManageUnit)
	ON_BN_CLICKED(IDC_RADIO_OUTDOOR_UNIT, OnRadioOutdoorUnit)
	ON_BN_CLICKED(IDC_RADIO_FENCE, OnRadioFence)
	ON_BN_CLICKED(IDC_RADIO_VILLA_OUTDOOR_UNIT, OnRadioVillaOutdoorUnit)
	ON_BN_CLICKED(IDC_RADIO_AGAIN_UNIT, OnRadioAgainUnit)
	//}}AFX_MSG_MAP
    ON_COMMAND(IDC_RADIO_OUTDOOR_UNIT2, &CDlgVideoIntercomDeviceIDCfg::OnRadioIDRegUnit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomDeviceIDCfg message handlers

void CDlgVideoIntercomDeviceIDCfg::OnRadioIndoorUnit() 
{   
	m_nUnitType = ENUM_INDOOR_UINT;
	CheckRaidoBtn();
}

void CDlgVideoIntercomDeviceIDCfg::OnRadioManageUnit() 
{    
	m_nUnitType = ENUM_MANAGE_UINT;
	CheckRaidoBtn();	
}

void CDlgVideoIntercomDeviceIDCfg::OnRadioOutdoorUnit() 
{    
	m_nUnitType = ENUM_OUTDOOR_UINT;
	CheckRaidoBtn();
}

void CDlgVideoIntercomDeviceIDCfg::CheckRaidoBtn()
{
    CheckDlgButton(IDC_RADIO_INDOOR_UNIT,m_nUnitType == ENUM_INDOOR_UINT);
    CheckDlgButton(IDC_RADIO_OUTDOOR_UNIT,m_nUnitType == ENUM_OUTDOOR_UINT);
    CheckDlgButton(IDC_RADIO_MANAGE_UNIT,m_nUnitType == ENUM_MANAGE_UINT);
    CheckDlgButton(IDC_RADIO_FENCE,m_nUnitType == ENUM_FENCE_UINT);
    CheckDlgButton(IDC_RADIO_VILLA_OUTDOOR_UNIT, m_nUnitType == ENUM_VILLA_OUTDOOR_UNIT);
    CheckDlgButton(IDC_RADIO_AGAIN_UNIT, m_nUnitType == ENUM_AGAIN_UINT);
    CheckDlgButton(IDC_RADIO_OUTDOOR_UNIT2, m_nUnitType == ENUM_ID_REG_DEVICE);
}

void CDlgVideoIntercomDeviceIDCfg::OnBtnGet() 
{
	char szError[64] = "\0";
	if (!GetVideoIntercomDeviceIDCfg())
	{   
		g_StringLanType(szError, "获取参数失败","Get parameters failed");
		AfxMessageBox(szError);
	}
}

void CDlgVideoIntercomDeviceIDCfg::OnBtnSave() 
{
	char szError[32] = "\0";
	if (SetVideoIntercomDeviceIDCfg())
	{   
		g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}

BOOL CDlgVideoIntercomDeviceIDCfg::GetVideoIntercomDeviceIDCfg()
{   
	DWORD dwReturn = 0;
	BOOL  bRst = FALSE;

	NET_DVR_VIDEO_INTERCOM_DEVICEID_CFG struDeviceIDCfg = {0};
	struDeviceIDCfg.dwSize = sizeof(struDeviceIDCfg);

	if (NET_DVR_GetDVRConfig(m_lServerID,NET_DVR_GET_VIDEO_INTERCOM_DEVICEID_CFG,0,&struDeviceIDCfg,sizeof(struDeviceIDCfg),&dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VIDEO_INTERCOM_DEVICEID_CFG");
		ShowParamToWnd(&struDeviceIDCfg);
		bRst = TRUE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEO_INTERCOM_DEVICEID_CFG");
		bRst = FALSE;
	}
	m_bChkAutoReg = struDeviceIDCfg.byIsAutoReg;

	UpdateData(FALSE);
	return bRst;
}

BOOL CDlgVideoIntercomDeviceIDCfg::SetVideoIntercomDeviceIDCfg()
{
	UpdateData(TRUE);
	BOOL  bRst = FALSE;
	
	NET_DVR_VIDEO_INTERCOM_DEVICEID_CFG struDeviceIDCfg = {0};
	struDeviceIDCfg.dwSize = sizeof(struDeviceIDCfg);
	struDeviceIDCfg.byIsAutoReg = m_bChkAutoReg;

	GetParamFromWnd(&struDeviceIDCfg);
	
	if (NET_DVR_SetDVRConfig(m_lServerID,NET_DVR_SET_VIDEO_INTERCOM_DEVICEID_CFG,0,&struDeviceIDCfg,sizeof(struDeviceIDCfg)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VIDEO_INTERCOM_DEVICEID_CFG");
		bRst = TRUE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VIDEO_INTERCOM_DEVICEID_CFG");
		bRst = FALSE;
	}
	
	return bRst;
}

void CDlgVideoIntercomDeviceIDCfg::GetParamFromWnd(NET_DVR_VIDEO_INTERCOM_DEVICEID_CFG* pDeviceIDCfg)
{
	UpdateData(TRUE);

    if (m_nUnitType == ENUM_OUTDOOR_UINT || m_nUnitType == ENUM_ID_REG_DEVICE)
	{
		pDeviceIDCfg->uVideoIntercomUnit.struOutdoorUnit.wPeriod = m_nOutdoorPeriod;
		pDeviceIDCfg->uVideoIntercomUnit.struOutdoorUnit.wBuildingNumber = m_nOutdoorBuildingNumber;
		pDeviceIDCfg->uVideoIntercomUnit.struOutdoorUnit.wUnitNumber = m_nOutdoorUnitNumber;
		pDeviceIDCfg->uVideoIntercomUnit.struOutdoorUnit.wFloorNumber = m_nOutdoorFloorNumber;
		pDeviceIDCfg->uVideoIntercomUnit.struOutdoorUnit.wDevIndex = m_nOutdoorDevIndex;
		
	}
	else if (m_nUnitType == ENUM_MANAGE_UINT)
	{
		pDeviceIDCfg->uVideoIntercomUnit.struManageUnit.wPeriod = m_nManagePeriod;
		pDeviceIDCfg->uVideoIntercomUnit.struManageUnit.wDevIndex = m_nManageDevIndex;
	}
	else if (m_nUnitType == ENUM_INDOOR_UINT)
	{
		pDeviceIDCfg->uVideoIntercomUnit.struIndoorUnit.wFloorNumber = m_nIndoorFloorNumber;
		pDeviceIDCfg->uVideoIntercomUnit.struIndoorUnit.wRoomNumber = m_nIndoorRoomNumber;
		pDeviceIDCfg->uVideoIntercomUnit.struIndoorUnit.wDevIndex = m_nDevIndex;
	}
	else if (m_nUnitType == ENUM_FENCE_UINT)
	{
        pDeviceIDCfg->uVideoIntercomUnit.struFenceUnit.wPeriod = m_nFencePeriod;
		pDeviceIDCfg->uVideoIntercomUnit.struFenceUnit.wDevIndex = m_nFenceDevIndex;
	}
    else if (m_nUnitType == ENUM_VILLA_OUTDOOR_UNIT)
    {
         pDeviceIDCfg->uVideoIntercomUnit.struVillaOutdoorUnit.wPeriod = m_nVillaOutDoorPeriod;
         pDeviceIDCfg->uVideoIntercomUnit.struVillaOutdoorUnit.wBuildingNumber = m_nVillaOutDoorBuildingNum;
         pDeviceIDCfg->uVideoIntercomUnit.struVillaOutdoorUnit.wUnitNumber = m_nVillaOutDoorUnitNum;
         pDeviceIDCfg->uVideoIntercomUnit.struVillaOutdoorUnit.wFloorNumber = m_nVillaOutDoorFloorNumber;
		 pDeviceIDCfg->uVideoIntercomUnit.struVillaOutdoorUnit.wDevIndex = m_nVillaOutDoorDevIndex;
    }
    else if (m_nUnitType == ENUM_AGAIN_UINT)
    {
        pDeviceIDCfg->uVideoIntercomUnit.struAgainConfirmUnit.wPeriod = m_nAgainOutDoorPeriod;
        pDeviceIDCfg->uVideoIntercomUnit.struAgainConfirmUnit.wBuildingNumber = m_nAgainOutDoorBuildingNum;
        pDeviceIDCfg->uVideoIntercomUnit.struAgainConfirmUnit.wUnitNumber = m_nAgainOutDoorUnitNum;
        pDeviceIDCfg->uVideoIntercomUnit.struAgainConfirmUnit.wFloorNumber = m_nAgainOutDoorFloorNumber;
        pDeviceIDCfg->uVideoIntercomUnit.struAgainConfirmUnit.wDevIndex = m_nAgainOutDoorDevIndex;
    }
	pDeviceIDCfg->byUnitType = m_nUnitType;
}

void CDlgVideoIntercomDeviceIDCfg::ShowParamToWnd(NET_DVR_VIDEO_INTERCOM_DEVICEID_CFG* pDeviceIDCfg)
{   
    if (pDeviceIDCfg->byUnitType == ENUM_OUTDOOR_UINT || pDeviceIDCfg->byUnitType == ENUM_ID_REG_DEVICE)
	{
		m_nOutdoorPeriod = pDeviceIDCfg->uVideoIntercomUnit.struOutdoorUnit.wPeriod;
		m_nOutdoorBuildingNumber = pDeviceIDCfg->uVideoIntercomUnit.struOutdoorUnit.wBuildingNumber;
		m_nOutdoorUnitNumber = pDeviceIDCfg->uVideoIntercomUnit.struOutdoorUnit.wUnitNumber;
		m_nOutdoorFloorNumber = pDeviceIDCfg->uVideoIntercomUnit.struOutdoorUnit.wFloorNumber;
		m_nOutdoorDevIndex = pDeviceIDCfg->uVideoIntercomUnit.struOutdoorUnit.wDevIndex;

	}
	else if (pDeviceIDCfg->byUnitType == ENUM_MANAGE_UINT)
	{
		m_nManagePeriod = pDeviceIDCfg->uVideoIntercomUnit.struManageUnit.wPeriod;
		m_nManageDevIndex = pDeviceIDCfg->uVideoIntercomUnit.struManageUnit.wDevIndex;
	}
	else if (pDeviceIDCfg->byUnitType == ENUM_INDOOR_UINT)
	{
		m_nIndoorFloorNumber = pDeviceIDCfg->uVideoIntercomUnit.struIndoorUnit.wFloorNumber;
		m_nIndoorRoomNumber = pDeviceIDCfg->uVideoIntercomUnit.struIndoorUnit.wRoomNumber;
		m_nDevIndex = pDeviceIDCfg->uVideoIntercomUnit.struIndoorUnit.wDevIndex;
	}
	else if (pDeviceIDCfg->byUnitType == ENUM_FENCE_UINT)
	{
        m_nFencePeriod = pDeviceIDCfg->uVideoIntercomUnit.struFenceUnit.wPeriod;
		m_nFenceDevIndex = pDeviceIDCfg->uVideoIntercomUnit.struFenceUnit.wDevIndex;
	}
    else if (pDeviceIDCfg->byUnitType == ENUM_VILLA_OUTDOOR_UNIT)
    {
        m_nVillaOutDoorPeriod = pDeviceIDCfg->uVideoIntercomUnit.struVillaOutdoorUnit.wPeriod;
        m_nVillaOutDoorBuildingNum = pDeviceIDCfg->uVideoIntercomUnit.struVillaOutdoorUnit.wBuildingNumber;
        m_nVillaOutDoorUnitNum = pDeviceIDCfg->uVideoIntercomUnit.struVillaOutdoorUnit.wUnitNumber;
        m_nVillaOutDoorFloorNumber = pDeviceIDCfg->uVideoIntercomUnit.struVillaOutdoorUnit.wFloorNumber;
		m_nVillaOutDoorDevIndex = pDeviceIDCfg->uVideoIntercomUnit.struVillaOutdoorUnit.wDevIndex;
    }
    else if (pDeviceIDCfg->byUnitType == ENUM_AGAIN_UINT)
    {
        m_nAgainOutDoorPeriod = pDeviceIDCfg->uVideoIntercomUnit.struAgainConfirmUnit.wPeriod;
        m_nAgainOutDoorBuildingNum = pDeviceIDCfg->uVideoIntercomUnit.struAgainConfirmUnit.wBuildingNumber;
        m_nAgainOutDoorUnitNum = pDeviceIDCfg->uVideoIntercomUnit.struAgainConfirmUnit.wUnitNumber;
        m_nAgainOutDoorFloorNumber = pDeviceIDCfg->uVideoIntercomUnit.struAgainConfirmUnit.wFloorNumber;
        m_nAgainOutDoorDevIndex = pDeviceIDCfg->uVideoIntercomUnit.struAgainConfirmUnit.wDevIndex;
    }

	m_nUnitType = pDeviceIDCfg->byUnitType;
	CheckRaidoBtn();
	UpdateData(FALSE);
}

void CDlgVideoIntercomDeviceIDCfg::OnRadioFence() 
{
	// TODO: Add your control notification handler code here
	m_nUnitType = ENUM_FENCE_UINT;
	CheckRaidoBtn();
}

void CDlgVideoIntercomDeviceIDCfg::OnRadioVillaOutdoorUnit() 
{
	// TODO: Add your control notification handler code here
    m_nUnitType = ENUM_VILLA_OUTDOOR_UNIT;
	CheckRaidoBtn();
}

void CDlgVideoIntercomDeviceIDCfg::OnRadioAgainUnit() 
{
	// TODO: Add your control notification handler code here
    m_nUnitType = ENUM_AGAIN_UINT;
	CheckRaidoBtn();
}


void CDlgVideoIntercomDeviceIDCfg::OnRadioIDRegUnit()
{
    // TODO:  在此添加命令处理程序代码
    m_nUnitType = ENUM_ID_REG_DEVICE;
    CheckRaidoBtn();
}
