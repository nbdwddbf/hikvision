// DlgVcaVersionList.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgVcaVersionList.h"
#include "afxdialogex.h"


// CDlgVcaVersionList 对话框

IMPLEMENT_DYNAMIC(CDlgVcaVersionList, CDialogEx)

CDlgVcaVersionList::CDlgVcaVersionList(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgVcaVersionList::IDD, pParent)
{

}

CDlgVcaVersionList::~CDlgVcaVersionList()
{
}

void CDlgVcaVersionList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_VCA_VERSION_LIST, m_lstVcaVersionList);
}


BEGIN_MESSAGE_MAP(CDlgVcaVersionList, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_GET_VCA_VERSIONLIST, &CDlgVcaVersionList::OnBnClickedBtnGetVcaVersionlist)
END_MESSAGE_MAP()


// CDlgVcaVersionList 消息处理程序
BOOL CDlgVcaVersionList::OnInitDialog()
{
    CDialog::OnInitDialog();

//    m_cmbCommand.SetCurSel(0);
    char szLanTemp[128] = { 0 };
    m_lstVcaVersionList.SetExtendedStyle(m_lstVcaVersionList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);

    g_StringLanType(szLanTemp, "主版本号", "Major Version");
    m_lstVcaVersionList.InsertColumn(0, szLanTemp, LVCFMT_LEFT, 40, -1);
    g_StringLanType(szLanTemp, "次版本号", "Minor Version");
    m_lstVcaVersionList.InsertColumn(1, szLanTemp, LVCFMT_LEFT, 40, -1);
    g_StringLanType(szLanTemp, "修正号", "Revision Number");
    m_lstVcaVersionList.InsertColumn(2, szLanTemp, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLanTemp, "编译号", "Build Number");
    m_lstVcaVersionList.InsertColumn(3, szLanTemp, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLanTemp, "版本日期—年", "Version Year");
    m_lstVcaVersionList.InsertColumn(4, szLanTemp, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLanTemp, "版本日期—月", "Version Month");
    m_lstVcaVersionList.InsertColumn(5, szLanTemp, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLanTemp, "版本日期—日", "Version Day");
    m_lstVcaVersionList.InsertColumn(6, szLanTemp, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLanTemp, "算法库名称", "VCA Name");
    m_lstVcaVersionList.InsertColumn(7, szLanTemp, LVCFMT_LEFT, 100, -1);

    return TRUE;
}

void CDlgVcaVersionList::OnBnClickedBtnGetVcaVersionlist()
{
    UpdateData(TRUE);

    NET_DVR_VCA_VERSION_LIST struVcaVersionList = { 0 };
    struVcaVersionList.dwSize = sizeof(struVcaVersionList);

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpOutBuffer = &struVcaVersionList;
    struCfg.dwOutSize = sizeof(struVcaVersionList);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_VCA_VERSION_LIST, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VCA_VERSION_LIST");
    }
    else
    {
        g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_VCA_VERSION_LIST");
        AddVcaVersionListItem(struVcaVersionList);
    }
}

void CDlgVcaVersionList::AddVcaVersionListItem(const NET_DVR_VCA_VERSION_LIST &Item)
{
    BOOL bTemp = FALSE;

    int iItemCount = 0;
    int i = 0;
    char szStr[128] = { 0 };
    for (i = 0; i < 64; i++)
    {
        
        int iItemCount = m_lstVcaVersionList.GetItemCount();
        m_lstVcaVersionList.InsertItem(iItemCount, "");
        
        if ((Item.struVcaVersion[i].wMajorVersion == 0) && (Item.struVcaVersion[i].wMinorVersion == 0) && (Item.struVcaVersion[i].wRevisionNumber == 0) && (Item.struVcaVersion[i].wBuildNumber == 0)\
             && (Item.struVcaVersion[i].wVersionYear == 0) && (Item.struVcaVersion[i].byVersionMonth == 0) && (Item.struVcaVersion[i].byVersionDay == 0) && (Item.struVcaVersion[i].byType == 0))
        {
            return;
        }

        //主版本号
        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%d", Item.struVcaVersion[i].wMajorVersion);
        m_lstVcaVersionList.SetItemText(iItemCount, 0, szStr);

        //次版本号
        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%d", Item.struVcaVersion[i].wMinorVersion);
        m_lstVcaVersionList.SetItemText(iItemCount, 1, szStr);

        //修正号
        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%d", Item.struVcaVersion[i].wRevisionNumber);
        m_lstVcaVersionList.SetItemText(iItemCount, 2, szStr);

        //编译号
        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%d", Item.struVcaVersion[i].wBuildNumber);
        m_lstVcaVersionList.SetItemText(iItemCount, 3, szStr);

        //版本日期-年
        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%d", Item.struVcaVersion[i].wVersionYear);
        m_lstVcaVersionList.SetItemText(iItemCount, 4, szStr);

        //版本日期-月
        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%d", Item.struVcaVersion[i].byVersionMonth);
        m_lstVcaVersionList.SetItemText(iItemCount, 5, szStr);

        //版本日期-日
        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%d", Item.struVcaVersion[i].byVersionDay);
        m_lstVcaVersionList.SetItemText(iItemCount, 6, szStr);

        //算法库类型名称
        memset(szStr, 0, sizeof(szStr));
        switch (Item.struVcaVersion[i].byType)
        {
        case 0:
            sprintf(szStr, "%s", "设备发送错误");
            break;
        case 1:
            sprintf(szStr, "%s", "人脸属性");
            break;
        case 2:
            sprintf(szStr, "%s", "行为分析");
            break;
        case 3:
            sprintf(szStr, "%s", "人体属性");
            break;
        case 4:
            sprintf(szStr, "%s", "人脸抓拍");
            break;
        case 5:
            sprintf(szStr, "%s", "人脸识别");
            break;
        case 6:
            sprintf(szStr, "%s", "人脸对比");
            break;
        case 7:
            sprintf(szStr, "%s", "学生站立检测");
            break;
        case 8:
            sprintf(szStr, "%s", "区域人数统计");
            break;
        case 9:
            sprintf(szStr, "%s", "人脸评分库");
            break;
        case 10:
            sprintf(szStr, "%s", "安全帽检测");
            break;
        case 11:
            sprintf(szStr, "%s", "电梯检测算法库");
            break;
        case 12:
            sprintf(szStr, "%s", "客流量统计");
            break;
        case 13:
            sprintf(szStr, "%s", "(海康目标结构化算法)HMS");
            break;
        case 14:
            sprintf(szStr, "%s", "教师行为检测");
            break;
        case 15:
            sprintf(szStr, "%s", "人员密度");
            break;
        case 19:
            sprintf(szStr, "%s", "人脸抓拍建模");
            break;
        case 20:
            sprintf(szStr, "%s", "HMS建模");
            break;
        default:
            break;
        }
        m_lstVcaVersionList.SetItemText(iItemCount, 7, szStr);
    }

}


