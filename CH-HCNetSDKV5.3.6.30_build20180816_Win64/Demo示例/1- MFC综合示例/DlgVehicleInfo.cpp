// DLGGETVEHICLEINFO.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgVehicleInfo.h"
#include "afxdialogex.h"

#define LONG_CONFIG_GET_NEXT 0x2000
#define LONG_CONFIG_FINISH 0x2001

void CALLBACK g_fGetVehicleInfoCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
// CDlgVehicleInfo 对话框

IMPLEMENT_DYNAMIC(CDlgVehicleInfo, CDialogEx)

CDlgVehicleInfo::CDlgVehicleInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgVehicleInfo::IDD, pParent)
    , m_startdate(COleDateTime::GetCurrentTime())
    , m_starttime(COleDateTime::GetCurrentTime())
    , m_enddate(COleDateTime::GetCurrentTime())
    , m_endtime(COleDateTime::GetCurrentTime())
    , m_vehicleinfo(_T(""))
{
    m_lVehicleInfoCfgHandle = -1;
}

CDlgVehicleInfo::~CDlgVehicleInfo()
{
}

void CDlgVehicleInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_VECHICLE_INFO_CFG, m_vehicleinfolist);
    DDX_DateTimeCtrl(pDX, IDC_START_DATE, m_startdate);
    DDX_DateTimeCtrl(pDX, IDC_START_TIME, m_starttime);
    DDX_DateTimeCtrl(pDX, IDC_STOP_DATE, m_enddate);
    DDX_DateTimeCtrl(pDX, IDC_STOP_TIME, m_endtime);
    DDX_Text(pDX, IDC_EDIT_VEHICLE, m_vehicleinfo);
    DDX_Control(pDX, IDC_COMBO_REGION, m_region);
}


BEGIN_MESSAGE_MAP(CDlgVehicleInfo, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_GET, &CDlgVehicleInfo::OnBnClickedBtnGet)
    ON_MESSAGE(LONG_CONFIG_GET_NEXT, OnMsgAddVehicleInfoCfgToList)
    ON_MESSAGE(LONG_CONFIG_FINISH, OnMsgGetVehicleInfoCfgFinish)
END_MESSAGE_MAP()


// CDlgVehicleInfo 消息处理程序

LRESULT CDlgVehicleInfo::OnMsgGetVehicleInfoCfgFinish(WPARAM wParam, LPARAM lParam)
{
    if (!NET_DVR_StopRemoteConfig(m_lVehicleInfoCfgHandle))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VEHICLE_INFORMATION Get finish");
    }
    m_lVehicleInfoCfgHandle = -1;
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_VEHICLE_INFORMATION Get finish");

    return 0;
}
void CDlgVehicleInfo::AddToVehicleInfoList(const NET_DVR_VEHICLE_INFO_CFG& struVehicleInfoCfg)
{
    char szLan[1024] = { 0 };

    int nItemindx = 0;

    nItemindx = m_vehicleinfolist.GetItemCount();


    CString strItem = "";
    strItem.Format("%d", struVehicleInfoCfg.dwIndex);
    m_vehicleinfolist.InsertItem(nItemindx, strItem);

    sprintf(szLan, "%s", struVehicleInfoCfg.byDeviceID);
    m_vehicleinfolist.SetItemText(nItemindx, 1, szLan);

    sprintf(szLan, "%d", struVehicleInfoCfg.byBelieve);
    m_vehicleinfolist.SetItemText(nItemindx, 2, szLan);

    sprintf(szLan, "%d", struVehicleInfoCfg.byDir);
    m_vehicleinfolist.SetItemText(nItemindx, 3, szLan);

    sprintf(szLan, "%d", struVehicleInfoCfg.byLineID);
    m_vehicleinfolist.SetItemText(nItemindx, 4, szLan);

    sprintf(szLan, "%d%d%d%d-%d%d-%d%d %d%d:%d%d:%d%d", struVehicleInfoCfg.struSnapTime.wYear, struVehicleInfoCfg.struSnapTime.byMonth, struVehicleInfoCfg.struSnapTime.byDay, struVehicleInfoCfg.struSnapTime.byHour, struVehicleInfoCfg.struSnapTime.byMinute, struVehicleInfoCfg.struSnapTime.bySecond);
    m_vehicleinfolist.SetItemText(nItemindx, 5, szLan);

    sprintf(szLan, "%s", struVehicleInfoCfg.sLicense);
    m_vehicleinfolist.SetItemText(nItemindx, 6, szLan);

    sprintf(szLan, "%s", struVehicleInfoCfg.byMonitoringSiteID);
    m_vehicleinfolist.SetItemText(nItemindx, 7, szLan);

    sprintf(szLan, "%d", struVehicleInfoCfg.byCountry);
    m_vehicleinfolist.SetItemText(nItemindx, 8, szLan);

    //车牌黑白名单匹配结果
    if (struVehicleInfoCfg.byMatchingResult == 1)
    {
        sprintf(szLan, "%s", "whitelist");
    }
    else if (struVehicleInfoCfg.byMatchingResult == 2)
    {
        sprintf(szLan, "%s", "blacklist");
    }
    else if (struVehicleInfoCfg.byMatchingResult == 3)
    {
        sprintf(szLan, "%s", "temporarylist");
    }
    else
    {
        sprintf(szLan, "%d", struVehicleInfoCfg.byMatchingResult);
    }
    m_vehicleinfolist.SetItemText(nItemindx, 9, szLan);
	
    sprintf(szLan, "%d", struVehicleInfoCfg.byArea);
    m_vehicleinfolist.SetItemText(nItemindx, 10, szLan);

    sprintf(szLan, "%s", struVehicleInfoCfg.sDeviceName);
    m_vehicleinfolist.SetItemText(nItemindx, 11, szLan);

    sprintf(szLan, "%d", struVehicleInfoCfg.byPlateType);
    m_vehicleinfolist.SetItemText(nItemindx, 12, szLan);

    if (struVehicleInfoCfg.byPlateColor == 0)
    {
        sprintf(szLan, "%s", "bule");
    }
    else if (struVehicleInfoCfg.byPlateColor == 1)
    {
        sprintf(szLan, "%s", "yellow");
    }
    else if (struVehicleInfoCfg.byPlateColor == 2)
    {
        sprintf(szLan, "%s", "white");
    }
    else if (struVehicleInfoCfg.byPlateColor == 3)
    {
        sprintf(szLan, "%s", "black");
    }
    else if (struVehicleInfoCfg.byPlateColor == 4)
    {
        sprintf(szLan, "%s", "green");
    }
    else if (struVehicleInfoCfg.byPlateColor == 5)
    {
        sprintf(szLan, "%s", "BKAIR");
    }
    else if (struVehicleInfoCfg.byPlateColor == 6)
    {
        sprintf(szLan, "%s", "red");
    }
    else if (struVehicleInfoCfg.byPlateColor == 7)
    {
        sprintf(szLan, "%s", "orange");
    }
    else 
    {
        sprintf(szLan, "%s", "other");
    }
     m_vehicleinfolist.SetItemText(nItemindx, 13, szLan);

     if (struVehicleInfoCfg.byPlateSize == 0)
     {
         sprintf(szLan, "%s", "unknown");
     }
     else if (struVehicleInfoCfg.byPlateSize == 1)
     {
         sprintf(szLan, "%s", "long");
     }
     else if (struVehicleInfoCfg.byPlateSize == 2)
     {
         sprintf(szLan, "%s", "short");
     }
     m_vehicleinfolist.SetItemText(nItemindx, 14, szLan);

     sprintf(szLan, "%s", struVehicleInfoCfg.sPlateCategory);
     m_vehicleinfolist.SetItemText(nItemindx, 15, szLan);

     sprintf(szLan, "%s", struVehicleInfoCfg.sPlateImageURL);
     m_vehicleinfolist.SetItemText(nItemindx, 16, szLan);
     
     sprintf(szLan, "%s", struVehicleInfoCfg.sEffectiveTime);
     m_vehicleinfolist.SetItemText(nItemindx, 17, szLan);
}

LRESULT CDlgVehicleInfo::OnMsgAddVehicleInfoCfgToList(WPARAM wParam, LPARAM lParam)
{
    LPNET_DVR_VEHICLE_INFO_CFG lpVehicleInfoCfg = (LPNET_DVR_VEHICLE_INFO_CFG)wParam;
    if (lpVehicleInfoCfg->dwSize == 0)
    {
        return 0;
    }
    AddToVehicleInfoList(*lpVehicleInfoCfg);
    delete lpVehicleInfoCfg;
    return 0;
}

void CDlgVehicleInfo::OnBnClickedBtnGet()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_lVehicleInfoCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lVehicleInfoCfgHandle);
    }
    //清除所有卡项
    //    ClearList(); 
    m_vehicleinfolist.DeleteAllItems();
    UpdateData(TRUE);
    NET_DVR_VEHICLE_INFO_COND struCond = { 0 };
    struCond.dwSize = sizeof(struCond);
    struCond.strStartTime.wYear = m_startdate.GetYear();
    struCond.strStartTime.byMonth = m_startdate.GetMonth();
    struCond.strStartTime.byDay = m_startdate.GetDay();
    struCond.strStartTime.byHour = m_starttime.GetHour();
    struCond.strStartTime.byMinute = m_startdate.GetMinute();
    struCond.strStartTime.bySecond = m_startdate.GetSecond();

    struCond.strStopTime.wYear = m_enddate.GetYear();
    struCond.strStopTime.byMonth = m_enddate.GetMonth();
    struCond.strStopTime.byDay = m_enddate.GetDay();
    struCond.strStopTime.byHour = m_endtime.GetHour();
    struCond.strStopTime.byMinute = m_endtime.GetMinute();
    struCond.strStopTime.bySecond = m_endtime.GetSecond();

    memcpy(struCond.sLicense, m_vehicleinfo.GetBuffer(m_vehicleinfo.GetLength()), m_vehicleinfo.GetLength());
    struCond.dwChannel = m_lChannel;
    struCond.byRegion = m_region.GetCurSel();

    if (struCond.byRegion==4)
    {
        struCond.byRegion = 0xff;
    }
    m_lVehicleInfoCfgHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_VEHICLE_INFORMATION, &struCond, sizeof(struCond), g_fGetVehicleInfoCallback, this);
    if (m_lVehicleInfoCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VEHICLE_INFORMATION failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_VEHICLE_INFORMATION succ");
    }
}

void CALLBACK g_fGetVehicleInfoCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgVehicleInfo* pDlg = (CDlgVehicleInfo*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcessGetVehicleInfoCallbackData(dwType, lpBuffer, dwBufLen);
}

void CDlgVehicleInfo::ProcessGetVehicleInfoCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    CString strItem = "";
    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        LPNET_DVR_VEHICLE_INFO_CFG lpVehicleCfg = new NET_DVR_VEHICLE_INFO_CFG;
        memcpy(lpVehicleCfg, lpBuffer, sizeof(*lpVehicleCfg));

        PostMessage(LONG_CONFIG_GET_NEXT, (WPARAM)lpVehicleCfg, 0);
    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            PostMessage(LONG_CONFIG_FINISH, 0, 0);
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            DWORD dwErrCode = *(DWORD*)((char *)lpBuffer + 4);
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "GetVehicleInfo STATUS_FAILED, Error code %d", dwErrCode);
        }
//         else if (dwStatus == NET_SDK_CALLBACK_STATUS_NODATA)
//         {
//             g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "GetVehicleInfo STATUS_NODATA");
//             PostMessage(LONG_CONFIG_FINISH, 0, 0);
//         }
    }
}

BOOL CDlgVehicleInfo::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;

    char szLan[128] = { 0 };
    m_vehicleinfolist.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

    g_StringLanType(szLan, "序号", "Index");
    m_vehicleinfolist.InsertColumn(0, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "设备编号", "DeviceID");
    m_vehicleinfolist.InsertColumn(1, szLan, LVCFMT_LEFT, 80, -1);


    g_StringLanType(szLan, "置信度", "Believe");
    m_vehicleinfolist.InsertColumn(2, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "方向", "Dir");
    m_vehicleinfolist.InsertColumn(3, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "车道号", "LineID");
    m_vehicleinfolist.InsertColumn(4, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "抓拍时间", "SnapTime");
    m_vehicleinfolist.InsertColumn(5, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "车牌号码", "License");
    m_vehicleinfolist.InsertColumn(6, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "监测点编号", "DeviceName");
    m_vehicleinfolist.InsertColumn(7, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "国家", "Country");
    m_vehicleinfolist.InsertColumn(8, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "黑白名单匹配结果", "MatchResult");
    m_vehicleinfolist.InsertColumn(9, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "区域", "Area");
    m_vehicleinfolist.InsertColumn(10, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "设备名称", "DeviceName");
    m_vehicleinfolist.InsertColumn(11, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "车牌类型", "PlateType");
    m_vehicleinfolist.InsertColumn(12, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "车牌颜色", "PlateColor");
    m_vehicleinfolist.InsertColumn(13, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "车牌尺寸", "PlateSize");
    m_vehicleinfolist.InsertColumn(14, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "车牌附加信息", "PlateCategory");
    m_vehicleinfolist.InsertColumn(15, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "车牌小图URL", "PlateImageURL");
    m_vehicleinfolist.InsertColumn(16, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "车牌信息有效时间", "EffectiveTime");
    m_vehicleinfolist.InsertColumn(17, szLan, LVCFMT_LEFT, 80, -1);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}

