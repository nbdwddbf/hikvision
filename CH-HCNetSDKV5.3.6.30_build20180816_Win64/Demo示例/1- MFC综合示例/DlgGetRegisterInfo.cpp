// DlgGetRegisterInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgGetRegisterInfo.h"
#include "afxdialogex.h"

#define  WM_GET_REGISTER_INFO_FINISH 1001
// #define WM_GET_REGISTER_INFO_TOLIST 1002

// CDlgGetRegisterInfo 对话框

IMPLEMENT_DYNAMIC(CDlgGetRegisterInfo, CDialogEx)

CDlgGetRegisterInfo::CDlgGetRegisterInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgGetRegisterInfo::IDD, pParent)
{
    m_lRemoteHandle = -1;
    m_lLogNum = 0;
}

CDlgGetRegisterInfo::~CDlgGetRegisterInfo()
{
}

void CDlgGetRegisterInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_REGISTER_INFO_LOG, m_listRegisterInfoLog);
}


BEGIN_MESSAGE_MAP(CDlgGetRegisterInfo, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_GET_REGISTER_INFO, &CDlgGetRegisterInfo::OnBnClickedBtnGetRegisterInfo)
    ON_MESSAGE(WM_GET_REGISTER_INFO_FINISH, OnMsgGetRegisterInfoFinish)
    //ON_MESSAGE(WM_GET_REGISTER_INFO_TOLIST, OnMsgGetRegisterInfoToList)
    ON_BN_CLICKED(IDC_BTN_EXIT, &CDlgGetRegisterInfo::OnBnClickedBtnExit)
END_MESSAGE_MAP()


// CDlgGetRegisterInfo 消息处理程序
//LRESULT CDlgGetRegisterInfo::OnMsgGetRegisterInfoToList(WPARAM wParam, LPARAM lParam)
//{
//}

LRESULT CDlgGetRegisterInfo::OnMsgGetRegisterInfoFinish(WPARAM wParam, LPARAM lParam)
{
    DWORD dwType = (DWORD)wParam;
    char szLan[256] = { 0 };

    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        LPNET_DVR_ID_CARD_BLACK_LIST_CFG pStruGetRegisterInfo = (LPNET_DVR_ID_CARD_BLACK_LIST_CFG)lParam;

        CString csTmp;
        csTmp.Format("%d", m_lLogNum + 1);
        m_listRegisterInfoLog.InsertItem(m_lLogNum, csTmp, 0);
        char szName[129] = { 0 };
        char szAddress[281] = { 0 };
        char szIDNum[33] = { 0 };
        char szIssuingAuthority[129] = { 0 };
       
        memset(szName, 0, 129);
        memcpy(szName, pStruGetRegisterInfo->struIDCardCfg.byName, MAX_ID_NAME_LEN);
        csTmp.Format("%s", szName);
        m_listRegisterInfoLog.SetItemText(m_lLogNum, 1, csTmp);

        csTmp.Format("%04d-%02d-%02d", pStruGetRegisterInfo->struIDCardCfg.struBirth.wYear, pStruGetRegisterInfo->struIDCardCfg.struBirth.byMonth, pStruGetRegisterInfo->struIDCardCfg.struBirth.byDay);
        m_listRegisterInfoLog.SetItemText(m_lLogNum, 2, csTmp);

        memset(szAddress, 0, 281);
        memcpy(szAddress, pStruGetRegisterInfo->struIDCardCfg.byAddr, MAX_ID_ADDR_LEN);
        csTmp.Format("%s", szAddress);
        m_listRegisterInfoLog.SetItemText(m_lLogNum, 3, csTmp);

        memset(szIDNum, 0, 33);
        memcpy(szIDNum, pStruGetRegisterInfo->struIDCardCfg.byIDNum, MAX_ID_NUM_LEN);
        csTmp.Format("%s", szIDNum);
        m_listRegisterInfoLog.SetItemText(m_lLogNum, 4, csTmp);

        memset(szIssuingAuthority, 0, 129);
        memcpy(szIssuingAuthority, pStruGetRegisterInfo->struIDCardCfg.byIssuingAuthority, MAX_ID_ISSUING_AUTHORITY_LEN);
        csTmp.Format("%s", szIssuingAuthority);
        m_listRegisterInfoLog.SetItemText(m_lLogNum, 5, csTmp);

        csTmp.Format("%04d-%02d-%02d", pStruGetRegisterInfo->struIDCardCfg.struStartDate.wYear, pStruGetRegisterInfo->struIDCardCfg.struStartDate.byMonth, pStruGetRegisterInfo->struIDCardCfg.struStartDate.byDay);
        m_listRegisterInfoLog.SetItemText(m_lLogNum, 6, csTmp);

        csTmp.Format("%04d-%02d-%02d", pStruGetRegisterInfo->struIDCardCfg.struEndDate.wYear, pStruGetRegisterInfo->struIDCardCfg.struEndDate.byMonth, pStruGetRegisterInfo->struIDCardCfg.struEndDate.byDay);
        m_listRegisterInfoLog.SetItemText(m_lLogNum, 7, csTmp);

        switch (pStruGetRegisterInfo->struIDCardCfg.byTermOfValidity)
        {
            case 0:
                g_StringLanType(szLan, "否", "No");
                csTmp.Format("%s", szLan);
                break;
            case 1:
                g_StringLanType(szLan, "是", "Yes");
                csTmp.Format("%s", szLan);
                break;
            default:
                g_StringLanType(szLan, "/", "/");
                csTmp.Format("%s", szLan);
                break;
        }
        m_listRegisterInfoLog.SetItemText(m_lLogNum, 8, csTmp);

        switch (pStruGetRegisterInfo->struIDCardCfg.bySex)
        {
            case 1:
                g_StringLanType(szLan, "男", "Male");
                csTmp.Format("%s", szLan);
                break;
            case 2:
                g_StringLanType(szLan, "女", "Female");
                csTmp.Format("%s", szLan);
                break;
            default:
                g_StringLanType(szLan, "/", "/");
                csTmp.Format("%s", szLan);
                break;
        }
        m_listRegisterInfoLog.SetItemText(m_lLogNum, 9, csTmp);

        switch (pStruGetRegisterInfo->struIDCardCfg.byNation)
        {
            case 1:
                g_StringLanType(szLan, "汉", "Han");
                break;
            case 2:
                g_StringLanType(szLan, "蒙古", "Mongolia");
                break;
            case 3:
                g_StringLanType(szLan, "回", "Hui");
                break;
            case 4:
                g_StringLanType(szLan, "藏", "Tibetan");
                break;
            case 5:
                g_StringLanType(szLan, "维吾尔", "Uighur");
                break;
            case 6:
                g_StringLanType(szLan, "苗", "Miao");
                break;
            case 7:
                g_StringLanType(szLan, "彝", "Yi");
                break;
            case 8:
                g_StringLanType(szLan, "壮", "Zhuang");
                break;
            case 9:
                g_StringLanType(szLan, "布依", "Buyei");
                break;
            case 10:
                g_StringLanType(szLan, "朝鲜", "Korean");
                break;
            case 11:
                g_StringLanType(szLan, "满", "Manchu");
                break;
            case 12:
                g_StringLanType(szLan, "侗", "Dong");
                break;
            case 13:
                g_StringLanType(szLan, "瑶", "Yao");
                break;
            case 14:
                g_StringLanType(szLan, "白", "Bai");
                break;
            case 15:
                g_StringLanType(szLan, "土家", "Tujia");
                break;
            case 16:
                g_StringLanType(szLan, "哈尼", "Hani");
                break;
            case 17:
                g_StringLanType(szLan, "哈萨克", "Kazak");
                break;
            case 18:
                g_StringLanType(szLan, "傣", "Dai");
                break;
            case 19:
                g_StringLanType(szLan, "黎", "Li");
                break;
            case 20:
                g_StringLanType(szLan, "傈僳", "Lisu");
                break;
            case 21:
                g_StringLanType(szLan, "佤", "Va");
                break;
            case 22:
                g_StringLanType(szLan, "畲", "She");
                break;
            case 23:
                g_StringLanType(szLan, "高山", "Gaoshan");
                break;
            case 24:
                g_StringLanType(szLan, "拉祜", "Lahu");
                break;
            case 25:
                g_StringLanType(szLan, "水", "Sui");
                break;
            case 26:
                g_StringLanType(szLan, "东乡", "Dongxiang");
                break;
            case 27:
                g_StringLanType(szLan, "纳西", "Naxi");
                break;
            case 28:
                g_StringLanType(szLan, "景颇", "Jingpo");
                break;
            case 29:
                g_StringLanType(szLan, "柯尔克孜", "Kirgiz");
                break;
            case 30:
                g_StringLanType(szLan, "土", "Tu");
                break;
            case 31:
                g_StringLanType(szLan, "达斡尔", "Daur");
                break;
            case 32:
                g_StringLanType(szLan, "仫佬", "Mulao");
                break;
            case 33:
                g_StringLanType(szLan, "羌", "Qiang");
                break;
            case 34:
                g_StringLanType(szLan, "布朗", "Blang");
                break;
            case 35:
                g_StringLanType(szLan, "撒拉", "Salar");
                break;
            case 36:
                g_StringLanType(szLan, "毛南", "Maonan");
                break;
            case 37:
                g_StringLanType(szLan, "仡佬", "Gelao");
                break;
            case 38:
                g_StringLanType(szLan, "锡伯", "Xibe");
                break;
            case 39:
                g_StringLanType(szLan, "阿昌", "Achang");
                break;
            case 40:
                g_StringLanType(szLan, "普米", "Pumi");
                break;
            case 41:
                g_StringLanType(szLan, "塔吉克", "Tajik");
                break;
            case 42:
                g_StringLanType(szLan, "怒", "Nu");
                break;
            case 43:
                g_StringLanType(szLan, "乌孜别克", "Uzbek");
                break;
            case 44:
                g_StringLanType(szLan, "俄罗斯", "Russians");
                break;
            case 45:
                g_StringLanType(szLan, "鄂温克", "Ewenki");
                break;
            case 46:
                g_StringLanType(szLan, "德昂", "De'ang");
                break;
            case 47:
                g_StringLanType(szLan, "保安", "Baoan");
                break;
            case 48:
                g_StringLanType(szLan, "裕固", "Yugur");
                break;
            case 49:
                g_StringLanType(szLan, "京", "Gin");
                break;
            case 50:
                g_StringLanType(szLan, "塔塔尔", "Tatar");
                break;
            case 51:
                g_StringLanType(szLan, "独龙", "Derung");
                break;
            case 52:
                g_StringLanType(szLan, "鄂伦春", "Oroqen");
                break;
            case 53:
                g_StringLanType(szLan, "赫哲", "Hezhen");
                break;
            case 54:
                g_StringLanType(szLan, "门巴", "Monba");
                break;
            case 55:
                g_StringLanType(szLan, "珞巴", "Lhoba");
                break;
            case 56:
                g_StringLanType(szLan, "基诺", "Jino");
                break;
            default:
                g_StringLanType(szLan, "未知民族", "Unknown");
                break;
        }
        csTmp.Format("%s", szLan);
        m_listRegisterInfoLog.SetItemText(m_lLogNum, 10, csTmp);

        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        char cFingerPrintDataname[256] = { 0 };
        char cPicDataname[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
        if (pStruGetRegisterInfo->dwFingerPrintDataLen > 0 && pStruGetRegisterInfo->pFingerPrintData != NULL)
        {
            sprintf(cFingerPrintDataname, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIP);

            if (GetFileAttributes(cFingerPrintDataname) != FILE_ATTRIBUTE_DIRECTORY)
            {
                CreateDirectory(cFingerPrintDataname, NULL);
            }

            sprintf(cFingerPrintDataname, "%s\\LocalTime[%s]CertificateRegisterInfoFingerPrintData.txt", cFingerPrintDataname, chTime);

            HANDLE hFile = CreateFile(cFingerPrintDataname, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE)
            {
                return NULL;
            }
            DWORD dwRet = WriteFile(hFile, pStruGetRegisterInfo->pFingerPrintData, pStruGetRegisterInfo->dwFingerPrintDataLen, &dwWrittenBytes, NULL);
            if (dwRet == 0 || dwWrittenBytes < pStruGetRegisterInfo->dwFingerPrintDataLen)
            {
                DWORD dwError = GetLastError();
                g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "CertificateRegisterInfo FingerPrintData Write to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, pStruGetRegisterInfo->dwFingerPrintDataLen, dwWrittenBytes);
            }
            CloseHandle(hFile);
            hFile = NULL;
        }

        if (pStruGetRegisterInfo->dwPicDataLen > 0 && pStruGetRegisterInfo->pPicData != NULL)
        {
            sprintf(cPicDataname, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIP);

            if (GetFileAttributes(cPicDataname) != FILE_ATTRIBUTE_DIRECTORY)
            {
                CreateDirectory(cPicDataname, NULL);
            }

            sprintf(cPicDataname, "%s\\LocalTime[%s]CertificateRegisterInfoPicData.jpg", cPicDataname, chTime);

            HANDLE hFile = CreateFile(cPicDataname, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE)
            {
                return NULL;
            }
            DWORD dwRet = WriteFile(hFile, pStruGetRegisterInfo->pPicData, pStruGetRegisterInfo->dwPicDataLen, &dwWrittenBytes, NULL);
            if (dwRet == 0 || dwWrittenBytes < pStruGetRegisterInfo->dwPicDataLen)
            {
                DWORD dwError = GetLastError();
                g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "CertificateRegisterInfo PicData Write to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, pStruGetRegisterInfo->dwPicDataLen, dwWrittenBytes);
            }
            CloseHandle(hFile);
            hFile = NULL;
        }

		m_lLogNum++;
        if (pStruGetRegisterInfo->pFingerPrintData != NULL)
        {
            delete[](pStruGetRegisterInfo->pFingerPrintData);
            pStruGetRegisterInfo->pFingerPrintData = NULL;
        }
        if (pStruGetRegisterInfo->pPicData != NULL)
        {
            delete[](pStruGetRegisterInfo->pPicData);
            pStruGetRegisterInfo->pPicData = NULL;
        }

        if (pStruGetRegisterInfo != NULL)
        {
            delete pStruGetRegisterInfo;
            pStruGetRegisterInfo = NULL;
        }
    }
    else
    {
        if (!NET_DVR_StopRemoteConfig(m_lRemoteHandle))
        {
            m_lRemoteHandle = -1;
            m_lLogNum = 0;
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig NET_DVR_GET_REGISTER_INFO");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopRemoteConfig NET_DVR_GET_REGISTER_INFO finish");
            m_lRemoteHandle = -1;
        }

    }

    return NULL;
}

// CDlgGetRegisterInfo 消息处理程序

void CALLBACK g_fGetRegisterInfoCallBack(DWORD dwType, void *pRecvDataBuffer, DWORD dwBufSize, void* pUserData)
{
    CDlgGetRegisterInfo *pThis = (CDlgGetRegisterInfo*)pUserData;
    DWORD dwTemp = 0;
    char szLan[128] = { 0 };

    HWND hWnd = pThis->GetSafeHwnd();
    if (NULL == hWnd)
    {
        return;
    }

    switch (dwType)
    {
        case NET_SDK_CALLBACK_TYPE_STATUS:
        {
            dwTemp = *((DWORD*)pRecvDataBuffer);
            if (dwTemp == NET_SDK_CALLBACK_STATUS_SUCCESS)
            {
                g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_SUCC_T, "Get Register Information CallBack");
                g_StringLanType(szLan, "完成获取", "complete to get register information");
                pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
                ::PostMessage(hWnd, WM_GET_REGISTER_INFO_FINISH, (DWORD)dwTemp, dwType);
            }
            else if (dwTemp == NET_SDK_CALLBACK_STATUS_FAILED)
            {
                g_StringLanType(szLan, "获取失败", "NET_DVR_GET_REGISTER_INFO failed");
                pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
                g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_REGISTER_INFO failed");
            } 
        }
        break;
        case NET_SDK_CALLBACK_TYPE_PROGRESS:
            g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_SUCC_T, "Get Register Information CallBack Processing");
            g_StringLanType(szLan, "正在获取……", "getting register information.");
            pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            break;
        case NET_SDK_CALLBACK_TYPE_DATA:
        {
            char *pDataBuf = new char[sizeof(NET_DVR_ID_CARD_BLACK_LIST_CFG)];
            if (pDataBuf == NULL)
            {
                dwType = NET_SDK_CALLBACK_STATUS_FAILED;
                break;
            }
            memset(pDataBuf, 0, sizeof(NET_DVR_ID_CARD_BLACK_LIST_CFG));
            memcpy(pDataBuf, pRecvDataBuffer, sizeof(NET_DVR_ID_CARD_BLACK_LIST_CFG));

            LPNET_DVR_ID_CARD_BLACK_LIST_CFG pGetRegisterInfoTemp = (NET_DVR_ID_CARD_BLACK_LIST_CFG*)pDataBuf;
            pGetRegisterInfoTemp->pFingerPrintData = NULL;
            pGetRegisterInfoTemp->pPicData = NULL;
            LPNET_DVR_ID_CARD_BLACK_LIST_CFG pGetRegisterInfoCfg = (NET_DVR_ID_CARD_BLACK_LIST_CFG*)pRecvDataBuffer;

            if (pGetRegisterInfoCfg->dwFingerPrintDataLen != 0)
            {
                pGetRegisterInfoTemp->pFingerPrintData = new char[pGetRegisterInfoCfg->dwFingerPrintDataLen];
                if (pGetRegisterInfoTemp->pFingerPrintData == NULL)
                {
                    g_StringLanType(szLan, "资源分配不足，获取失败", "resource not enough，get failed");
                    pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
                    return;
                }
                memset(pGetRegisterInfoTemp->pFingerPrintData, 0, pGetRegisterInfoCfg->dwFingerPrintDataLen);
                memcpy(pGetRegisterInfoTemp->pFingerPrintData, pGetRegisterInfoCfg->pFingerPrintData, pGetRegisterInfoCfg->dwFingerPrintDataLen);
            }
            if (pGetRegisterInfoCfg->dwPicDataLen != 0)
            {
                pGetRegisterInfoTemp->pPicData = new char[pGetRegisterInfoCfg->dwPicDataLen];
                if (pGetRegisterInfoTemp->pPicData == NULL)
                {
                    g_StringLanType(szLan, "资源分配不足，获取失败", "resource not enough，get failed");
                    pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
                    return;
                }
                memset(pGetRegisterInfoTemp->pPicData, 0, pGetRegisterInfoCfg->dwPicDataLen);
                memcpy(pGetRegisterInfoTemp->pPicData, pGetRegisterInfoCfg->pPicData, pGetRegisterInfoCfg->dwPicDataLen);
            }

            sprintf(szLan, "Get Register Information Fingerprint Data Size[%d] Picture Size[%d]", pGetRegisterInfoTemp->dwFingerPrintDataLen, pGetRegisterInfoTemp->dwPicDataLen);
            pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_SUCC_T, szLan);
            ::PostMessage(hWnd, WM_GET_REGISTER_INFO_FINISH, NET_SDK_CALLBACK_TYPE_DATA, (LPARAM)pDataBuf);
        }
        break;
        default:
            break;
    }

}


void CDlgGetRegisterInfo::OnBnClickedBtnGetRegisterInfo()
{
    // TODO:  在此添加控件通知处理程序代码
    m_listRegisterInfoLog.DeleteAllItems();
	m_lLogNum = 0;
    UpdateData(TRUE);
    if (m_lRemoteHandle >= 0)
    {
        NET_DVR_StopRemoteConfig(m_lRemoteHandle);
    }

    NET_DVR_ID_CARD_BLACK_LIST_COND struGetRegisterInfoCond = { 0 };
    struGetRegisterInfoCond.dwSize = sizeof(struGetRegisterInfoCond);

    m_lRemoteHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_REGISTER_INFO, &struGetRegisterInfoCond, sizeof(struGetRegisterInfoCond), g_fGetRegisterInfoCallBack, this);
    if (m_lRemoteHandle < 0)
    {
        AfxMessageBox("NET_DVR_StartRemoteConfig with command NET_DVR_GET_REGISTER_INFO failed");
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_REGISTER_INFO");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_REGISTER_INFO");
    }
    UpdateData(FALSE);
	GetDlgItem(IDC_BTN_EXIT)->EnableWindow(TRUE);
    return;
}


BOOL CDlgGetRegisterInfo::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    char szLanTemp[128] = { 0 };
    m_listRegisterInfoLog.SetExtendedStyle(m_listRegisterInfoLog.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLanTemp, "序号", "No");
    m_listRegisterInfoLog.InsertColumn(0, szLanTemp, LVCFMT_CENTER, 80, -1);
    g_StringLanType(szLanTemp, "姓名", "Name");
    m_listRegisterInfoLog.InsertColumn(1, szLanTemp, LVCFMT_CENTER, 80, -1);
    g_StringLanType(szLanTemp, "出生日期", "Birthday");
    m_listRegisterInfoLog.InsertColumn(2, szLanTemp, LVCFMT_CENTER, 80, -1);
    g_StringLanType(szLanTemp, "地址", "Address");
    m_listRegisterInfoLog.InsertColumn(3, szLanTemp, LVCFMT_CENTER, 80, -1);
    g_StringLanType(szLanTemp, "身份证号码", "Id card number");
    m_listRegisterInfoLog.InsertColumn(4, szLanTemp, LVCFMT_CENTER, 80, -1);
    g_StringLanType(szLanTemp, "签发机关", "Issuing authority");
    m_listRegisterInfoLog.InsertColumn(5, szLanTemp, LVCFMT_CENTER, 80, -1);
    g_StringLanType(szLanTemp, "有效开始日期", "Effective start date");
    m_listRegisterInfoLog.InsertColumn(6, szLanTemp, LVCFMT_CENTER, 80, -1);
    g_StringLanType(szLanTemp, "有效截止日期", "Effective deadline");
    m_listRegisterInfoLog.InsertColumn(7, szLanTemp, LVCFMT_CENTER, 80, -1);
    g_StringLanType(szLanTemp, "是否长期有效", "Whether long-term effective");
    m_listRegisterInfoLog.InsertColumn(8, szLanTemp, LVCFMT_CENTER, 80, -1);
    g_StringLanType(szLanTemp, "性别", "Sex");
    m_listRegisterInfoLog.InsertColumn(9, szLanTemp, LVCFMT_CENTER, 80, -1);
    g_StringLanType(szLanTemp, "民族", "National");
    m_listRegisterInfoLog.InsertColumn(10, szLanTemp, LVCFMT_CENTER, 80, -1);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}


void CDlgGetRegisterInfo::OnBnClickedBtnExit()
{
    // TODO:  在此添加控件通知处理程序代码
    CDialogEx::OnCancel();
}
