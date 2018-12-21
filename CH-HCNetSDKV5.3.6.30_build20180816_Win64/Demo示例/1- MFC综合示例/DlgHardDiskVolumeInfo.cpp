// DlgHardDiskVolumeInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgHardDiskVolumeInfo.h"
#include "afxdialogex.h"


// CDlgHardDiskVolumeInfo 对话框

IMPLEMENT_DYNAMIC(CDlgHardDiskVolumeInfo, CDialogEx)

CDlgHardDiskVolumeInfo::CDlgHardDiskVolumeInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgHardDiskVolumeInfo::IDD, pParent)
{

}

CDlgHardDiskVolumeInfo::~CDlgHardDiskVolumeInfo()
{
}

void CDlgHardDiskVolumeInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_HARD_DISK_VOLUME, m_listHardDiskVolume);
    DDX_Control(pDX, IDC_COMBO_BOX, m_comboBox);
}


BEGIN_MESSAGE_MAP(CDlgHardDiskVolumeInfo, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgHardDiskVolumeInfo::OnBnClickedButtonGet)
    ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgHardDiskVolumeInfo::OnBnClickedButtonSet)
    ON_CBN_KILLFOCUS(IDC_COMBO_BOX, &CDlgHardDiskVolumeInfo::OnCbnKillfocusComboBox)
    ON_NOTIFY(NM_CLICK, IDC_LIST_HARD_DISK_VOLUME, &CDlgHardDiskVolumeInfo::OnNMClickListHardDiskVolume)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_HARD_DISK_VOLUME, &CDlgHardDiskVolumeInfo::OnNMDblclkListHardDiskVolume)
END_MESSAGE_MAP()


// CDlgHardDiskVolumeInfo 消息处理程序


BOOL CDlgHardDiskVolumeInfo::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化

    char szLan[128] = { 0 };
    m_listHardDiskVolume.SetExtendedStyle(m_listHardDiskVolume.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);

    g_StringLanType(szLan, "序号", "Index");
    m_listHardDiskVolume.InsertColumn(0, szLan, LVCFMT_LEFT, 60, -1);

    g_StringLanType(szLan, "硬盘卷ID", "HD volume ID");
    m_listHardDiskVolume.InsertColumn(1, szLan, LVCFMT_LEFT, 60, -1);

    g_StringLanType(szLan, "硬盘卷类型", "Type");
    m_listHardDiskVolume.InsertColumn(2, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "硬盘卷容量", "Capacity");
    m_listHardDiskVolume.InsertColumn(3, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "硬盘卷剩余空间", "Free Space");
    m_listHardDiskVolume.InsertColumn(4, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "硬盘卷名称", "HD volume Name");
    m_listHardDiskVolume.InsertColumn(5, szLan, LVCFMT_LEFT, 120, -1);

    g_StringLanType(szLan, "是否循环覆盖", "Is loop cover");
    m_listHardDiskVolume.InsertColumn(6, szLan, LVCFMT_LEFT, 60, -1);

    m_iRowCount = m_listHardDiskVolume.GetItemCount();  //获取行数

    m_comboBox.ShowWindow(SW_HIDE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}

void CDlgHardDiskVolumeInfo::OnBnClickedButtonGet()
{
    // TODO:  在此添加控件通知处理程序代码

    m_listHardDiskVolume.DeleteAllItems();

    DWORD dwReturn = 0;
    m_struHardDiskVolumeInfo = { 0 };
    m_struHardDiskVolumeInfo.dwSize = sizeof(m_struHardDiskVolumeInfo);

    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_HDVOLUME_CFG, 0, &m_struHardDiskVolumeInfo, sizeof(m_struHardDiskVolumeInfo), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_HDVOLUME_CFG Failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_HDVOLUME_CFG SUCC");
        AddHardDiskVolumeInfoToList();

        UpdateData(FALSE);
    }
}


void CDlgHardDiskVolumeInfo::OnBnClickedButtonSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_HDVOLUME_CFG, 0, &m_struHardDiskVolumeInfo, sizeof(m_struHardDiskVolumeInfo)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_HDVOLUME_CFG Failed");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_HDVOLUME_CFG SUCC");
    }
}


void CDlgHardDiskVolumeInfo::OnCbnKillfocusComboBox()
{
    // TODO:  在此添加控件通知处理程序代码
    CString  csComboBoxStr;
    char  szListStr[128] = { 0 };
    m_listHardDiskVolume.GetItemText(m_iItem, m_iSubItem, szListStr, 128);
    m_comboBox.GetWindowText(csComboBoxStr);
    if (csComboBoxStr.Compare(szListStr))
    {
        m_comboBox.SetCurSel(m_comboBox.FindString(0, szListStr));
        m_listHardDiskVolume.SetItemText(m_iItem, m_iSubItem, csComboBoxStr);
        m_iLastItem = m_iItem;
        SaveParam();
    }
    m_comboBox.ShowWindow(SW_HIDE);
}

void CDlgHardDiskVolumeInfo::SaveParam()
{
    // TODO:  在此添加控件通知处理程序代码
    char  szListStr[128] = { 0 };
    int iIndex = 0;

    m_listHardDiskVolume.GetItemText(m_iLastItem, 0, szListStr, 128);
    iIndex = atoi(szListStr);

    if (iIndex < 0 || iIndex >= NET_SDK_DISK_VOLUME_LEN)
    {
        return;
    }

    m_listHardDiskVolume.GetItemText(m_iLastItem, 6, szListStr, 128);
    if (0 == strcmp(szListStr, "不启用") || 0 == strcmp(szListStr, "disable"))
    {
        m_struHardDiskVolumeInfo.struSingleVolumeInfo[iIndex].byLoopCover = 0;
    }
    else if (0 == strcmp(szListStr, "启用") || 0 == strcmp(szListStr, "enable"))
    {
        m_struHardDiskVolumeInfo.struSingleVolumeInfo[iIndex].byLoopCover = 1;
    }
}

void CDlgHardDiskVolumeInfo::AddHardDiskVolumeInfoToList()
{
    int iItemCount = 0;
    char szStr[512] = { 0 };

    for (int iIndex = 0; iIndex < m_struHardDiskVolumeInfo.dwHDVolumeCount; iIndex++)
    {
        iItemCount = m_listHardDiskVolume.GetItemCount();
        m_listHardDiskVolume.InsertItem(iItemCount, "");

        sprintf(szStr, "%d", iItemCount);
        m_listHardDiskVolume.SetItemText(iItemCount, 0, szStr);

        sprintf(szStr, "%d", m_struHardDiskVolumeInfo.struSingleVolumeInfo[iIndex].byHDVolumeNo);
        m_listHardDiskVolume.SetItemText(iItemCount, 1, szStr);

        switch (m_struHardDiskVolumeInfo.struSingleVolumeInfo[iIndex].byType)
        {
        case 0:
            g_StringLanType(szStr, "录像卷", "Video volume");
            m_listHardDiskVolume.SetItemText(iItemCount, 2, szStr);
            break;
        case 1:
            g_StringLanType(szStr, "存档卷", "Archiving volume");
            m_listHardDiskVolume.SetItemText(iItemCount, 2, szStr);
            break;
        case 2:
            g_StringLanType(szStr, "文件卷", "File volume");
            m_listHardDiskVolume.SetItemText(iItemCount, 2, szStr);
            break;
        case 3:
            g_StringLanType(szStr, "图片卷", "Picture volume");
            m_listHardDiskVolume.SetItemText(iItemCount, 2, szStr);
            break;
        default:
            break;
        }

        sprintf(szStr, "%d MB", m_struHardDiskVolumeInfo.struSingleVolumeInfo[iIndex].dwCapacity);
        m_listHardDiskVolume.SetItemText(iItemCount, 3, szStr);

        sprintf(szStr, "%d MB", m_struHardDiskVolumeInfo.struSingleVolumeInfo[iIndex].dwFreeSpace);
        m_listHardDiskVolume.SetItemText(iItemCount, 4, szStr);

        sprintf(szStr, "%s", m_struHardDiskVolumeInfo.struSingleVolumeInfo[iIndex].byHDVolumeName);
        m_listHardDiskVolume.SetItemText(iItemCount, 5, szStr);

        switch (m_struHardDiskVolumeInfo.struSingleVolumeInfo[iIndex].byLoopCover)
        {
        case 0:
            g_StringLanType(szStr, "不启用", "disable");
            m_listHardDiskVolume.SetItemText(iItemCount, 6, szStr);
            break;
        case 1:
            g_StringLanType(szStr, "启用", "enable");
            m_listHardDiskVolume.SetItemText(iItemCount, 6, szStr);
            break;
        default:
            break;
        }

    }
}

void CDlgHardDiskVolumeInfo::OnNMClickListHardDiskVolume(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO:  在此添加控件通知处理程序代码

    m_iLastItem = pNMItemActivate->iItem;
    m_iSubItem = pNMItemActivate->iSubItem;
    m_bSelectItem = TRUE;

    *pResult = 0;
}


void CDlgHardDiskVolumeInfo::OnNMDblclkListHardDiskVolume(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO:  在此添加控件通知处理程序代码

    char szStr[128] = { 0 };

    CRect  EditRect;
    m_iItem = pNMItemActivate->iItem;
    m_iSubItem = pNMItemActivate->iSubItem;

    if (m_iItem == -1)
    {
        return;
    }
    switch (m_iSubItem)
    {
    case 6://是否循环覆盖
        if (m_iItem <= m_iRowCount)
        {
            m_comboBox.ResetContent();
            g_StringLanType(szStr, "不启用", "disable");
            m_comboBox.InsertString(0, szStr);
            g_StringLanType(szStr, "启用", "enable");
            m_comboBox.InsertString(1, szStr);
            m_comboBox.SetCurSel(0);

            m_listHardDiskVolume.GetSubItemRect(m_iItem, m_iSubItem, LVIR_LABEL, EditRect);
            m_comboBox.SetParent(&m_listHardDiskVolume); //将list control设置为父窗口,生成的ComboBox才能正确定位

            EditRect.SetRect(EditRect.left, EditRect.top, EditRect.left + m_listHardDiskVolume.GetColumnWidth(m_iSubItem), EditRect.bottom);

            //将选中的list控件中的内容copy到edit控件中
            CString strItem = m_listHardDiskVolume.GetItemText(m_iItem, m_iSubItem);
            m_comboBox.MoveWindow(&EditRect);
            m_comboBox.ShowWindow(SW_SHOW);
            m_comboBox.SetWindowText(strItem);
            m_comboBox.SetFocus();//设置为焦点
        }
        else
        {
            m_comboBox.ShowWindow(SW_HIDE);
        }
        break;
    default:
        break;
    }

    *pResult = 0;
}
