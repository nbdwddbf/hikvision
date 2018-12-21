// DlgPosInfoctrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgPosInfoctrl.h"
#include "afxdialogex.h"


// CDlgPosInfoctrl 对话框

IMPLEMENT_DYNAMIC(CDlgPosInfoctrl, CDialog)

CDlgPosInfoctrl::CDlgPosInfoctrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPosInfoctrl::IDD, pParent)
    , m_bEnable(FALSE)
    , m_bHat(FALSE)
    , m_bGlasses(FALSE)
    , m_bBackpack(FALSE)
    , m_bHair(FALSE)
    , m_bMask(FALSE)
    , m_bRide(FALSE)
    , m_bCarry(FALSE)
    , m_bPant(FALSE)
    , m_bSex(FALSE)
    , m_bSleeve(FALSE)
    , m_bHeight(FALSE)
    , m_bAge(FALSE)
{

}

CDlgPosInfoctrl::~CDlgPosInfoctrl()
{
}

void CDlgPosInfoctrl::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
    DDX_Check(pDX, IDC_CHECK_HAT, m_bHat);
    DDX_Check(pDX, IDC_CHECK_GLASSES, m_bGlasses);
    DDX_Check(pDX, IDC_CHECK_BACKPACK, m_bBackpack);
    DDX_Check(pDX, IDC_CHECK_HAIR, m_bHair);
    DDX_Check(pDX, IDC_CHECK_MASK, m_bMask);
    DDX_Check(pDX, IDC_CHECK_RIDE, m_bRide);
    DDX_Check(pDX, IDC_CHECK_CARRY, m_bCarry);
    DDX_Check(pDX, IDC_CHECK_PANT, m_bPant);
    DDX_Check(pDX, IDC_CHECK_SEX, m_bSex);
    DDX_Check(pDX, IDC_CHECK_SLEEVE, m_bSleeve);
    DDX_Check(pDX, IDC_CHECK_HEIGHT, m_bHeight);
    DDX_Check(pDX, IDC_CHECK_AGE, m_bAge);
}


BEGIN_MESSAGE_MAP(CDlgPosInfoctrl, CDialog)
    ON_BN_CLICKED(IDC_BTN_SET, &CDlgPosInfoctrl::OnBnClickedBtnSet)
    ON_BN_CLICKED(IDC_BTN_GET, &CDlgPosInfoctrl::OnBnClickedBtnGet)
END_MESSAGE_MAP()


// CDlgPosInfoctrl 消息处理程序


void CDlgPosInfoctrl::OnBnClickedBtnSet()
{
    UpdateData(TRUE);
    NET_DVR_POSINFO_OVERLAY struposInfo = { 0 };
    struposInfo.dwSize = sizeof(struposInfo);
    struposInfo.byEnable = m_bEnable;
    struposInfo.byBackpackEnanble = m_bBackpack;
    struposInfo.bySexEnanble = m_bSex;
    struposInfo.byCarryEnanble = m_bCarry;
    struposInfo.byRideEnanble = m_bRide;
    struposInfo.byMaskEnanble = m_bMask;
    struposInfo.bySleeveEnanble = m_bSleeve;
    struposInfo.byHairEnanble = m_bHair;
    struposInfo.byGlassesEnanble = m_bGlasses;
    struposInfo.byPantsTypeEnanble = m_bPant;
    struposInfo.byHatEnanble = m_bHat;
    struposInfo.byAgeEnanble = m_bAge;
    struposInfo.byHeightEnanble = m_bHeight;
    NET_DVR_STD_CONFIG struStdConfig = { 0 };
    struStdConfig.lpInBuffer = (LPVOID)&struposInfo;
    struStdConfig.dwInSize = sizeof(struposInfo);
    struStdConfig.lpCondBuffer = &m_lChannel;
    struStdConfig.dwCondSize = sizeof(m_lChannel);

    if (!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_POSINFO_OVERLAY, &struStdConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_POSINFO_OVERLAY");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_POSINFO_OVERLAY");
    }
    UpdateData(FALSE);
     
}


void CDlgPosInfoctrl::OnBnClickedBtnGet()
{
    UpdateData(TRUE);
    NET_DVR_STD_CONFIG struCfg = { 0 };
    NET_DVR_POSINFO_OVERLAY struposInfo = { 0 };
    struposInfo.dwSize = sizeof(struposInfo);

    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struposInfo;
    struCfg.dwOutSize = sizeof(struposInfo);

    if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_POSINFO_OVERLAY, &struCfg))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WIRELESSDIAL_STATUS");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_WIRELESSDIAL_STATUS");
        m_bEnable = struposInfo.byEnable;
        m_bBackpack = struposInfo.byBackpackEnanble;
        m_bSex = struposInfo.bySexEnanble;
        m_bCarry = struposInfo.byCarryEnanble;
        m_bRide = struposInfo.byRideEnanble;
        m_bMask = struposInfo.byMaskEnanble;
        m_bSleeve = struposInfo.bySleeveEnanble;
        m_bHair = struposInfo.byHairEnanble;
        m_bGlasses = struposInfo.byGlassesEnanble;
        m_bPant = struposInfo.byPantsTypeEnanble;
        m_bHat = struposInfo.byHatEnanble;
        m_bAge = struposInfo.byAgeEnanble;
        m_bHeight = struposInfo.byHeightEnanble;
    }
    UpdateData(FALSE);
}



