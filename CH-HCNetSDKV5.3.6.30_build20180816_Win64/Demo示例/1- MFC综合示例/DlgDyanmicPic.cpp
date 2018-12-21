// DlgDyanmicPic.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgDyanmicPic.h"
#include "afxdialogex.h"
#include "DlgInfoGerenal.h"


// CDlgDyanmicPic 对话框

IMPLEMENT_DYNAMIC(CDlgDyanmicPic, CDialog)

CDlgDyanmicPic::CDlgDyanmicPic(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDyanmicPic::IDD, pParent)
    , m_csCancelType(_T(""))
    , m_csDisplayType(_T(""))
    , m_csFileType(_T(""))
    , m_csPicType(_T(""))
    , m_dwDuration(0)
    , m_dwFileSize(0)
    , m_dwMaterialId(0)
    , m_dwTerminalNo(0)
    , m_csFilePath(_T(""))
    , m_csMaterialName(_T(""))
    , m_iOrgNo(0)
{
    m_iTerminalCount = 0;
    m_iOrgCount = 0;
    m_bUploading = FALSE;
    memset(m_arrTerminal, 0, sizeof(m_arrTerminal));
    memset(m_arrOrg, 0, sizeof(m_arrOrg));
}

CDlgDyanmicPic::~CDlgDyanmicPic()
{
}

void CDlgDyanmicPic::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_CBString(pDX, IDC_COMBO_CANCEL_TYPE, m_csCancelType);
    DDX_CBString(pDX, IDC_COMBO_DISPLAY_TYPE, m_csDisplayType);
    DDX_CBString(pDX, IDC_COMBO_FILE_TYPE, m_csFileType);
    DDX_CBString(pDX, IDC_COMBO_PIC_TYPE, m_csPicType);
    DDX_Text(pDX, IDC_EDIT_DURATION, m_dwDuration);
    DDX_Text(pDX, IDC_EDIT_MATERIAL_SIZE, m_dwFileSize);
    DDX_Text(pDX, IDC_EDIT_MATERIL_ID, m_dwMaterialId);
    DDX_Text(pDX, IDC_EDIT_TER_ID, m_dwTerminalNo);
    DDX_Control(pDX, IDC_LIST_TERMINAL, m_listTerminal);
    DDX_Text(pDX, IDC_EDIT_MATERIAL_PATH, m_csFilePath);
    DDX_Control(pDX, IDC_PROGRESS, m_ctrlProgress);
    DDX_Control(pDX, IDC_STATIC_PROGRESS, m_statProgress);
    DDX_Text(pDX, IDC_EDIT_MATERIL_NAME, m_csMaterialName);
    DDX_Control(pDX, IDC_LIST_ORG, m_listOrg);
    DDX_Text(pDX, IDC_EDIT_ORG, m_iOrgNo);
}


BEGIN_MESSAGE_MAP(CDlgDyanmicPic, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_OK, &CDlgDyanmicPic::OnBnClickedButtonOk)
    ON_BN_CLICKED(IDC_BTN_TER_ADD, &CDlgDyanmicPic::OnBnClickedBtnTerAdd)
    ON_BN_CLICKED(IDC_BTN_MATERIAL_CHOOSE, &CDlgDyanmicPic::OnBnClickedBtnMaterialChoose)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BTN_TER_DEL, &CDlgDyanmicPic::OnBnClickedBtnTerDel)
    ON_BN_CLICKED(IDC_BTN_TER_MOD, &CDlgDyanmicPic::OnBnClickedBtnTerMod)
    ON_NOTIFY(NM_CLICK, IDC_LIST_TERMINAL, &CDlgDyanmicPic::OnNMClickListTerminal)
    ON_BN_CLICKED(IDC_BTN_TER_ADD2, &CDlgDyanmicPic::OnBnClickedBtnTerAdd2)
END_MESSAGE_MAP()


// CDlgDyanmicPic 消息处理程序


void CDlgDyanmicPic::OnBnClickedButtonOk()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    CString str;
    if (strcmp(m_csDisplayType, "byTerminal") == 0)
    {
        str += "<TerminalNoList>\r\n";
        for (int i = 0; i < m_iTerminalCount; i++)
        {
            CString strTmp;
            strTmp.Format("<terminalNo>%d</terminalNo>\r\n", m_arrTerminal[i]);
            str += strTmp;
        }
        str += "</TerminalNoList>\r\n";
    }
    else if(strcmp(m_csDisplayType, "byGroup") == 0)
    {
        str += "<TerminalGroupNoList>\r\n";
        for (int i = 0; i < m_iTerminalCount; i++)
        {
            CString strTmp;
            strTmp.Format("<terminalGroupNo>%d</terminalGroupNo>\r\n", m_arrTerminal[i]);
            str += strTmp;
        }
        str += "</TerminalGroupNoList>\r\n";
    }
    else if (strcmp(m_csDisplayType, "byOrg") == 0)
    {
        str += "<OrgNoList>\r\n";
        for (int i = 0; i < m_iTerminalCount; i++)
        {
            CString strTmp;
            strTmp.Format("<orgNo>%d</orgNo>\r\n", m_arrTerminal[i]);
            str += strTmp;
        }
        str += "</OrgNoList>\r\n";
    }
    else if (strcmp(m_csDisplayType, "byTerminalOrg") == 0)
    {
        str += "<TerminalNoList>\r\n";
        for (int i = 0; i < m_iTerminalCount; i++)
        {
            CString strTmp;
            strTmp.Format("<terminalNo>%d</terminalNo>\r\n", m_arrTerminal[i]);
            str += strTmp;
        }
        str += "</TerminalNoList>\r\n";
        str += "<OrgNoList>\r\n";
        for (int i = 0; i < m_iOrgCount; i++)
        {
            CString strTmp;
            strTmp.Format("<orgNo>%d</orgNo>\r\n", m_arrOrg[i]);
            str += strTmp;
        }
        str += "</OrgNoList>\r\n";
    }
    char szTerminal[512] = { 0 };
    memcpy(szTerminal, str.GetBuffer(0), str.GetLength());
    char szBuf[1024 * 5] = { 0 };
    sprintf(szBuf, "<ThridPartyFile version=\"2.0\">\r\n"\
        "<materialNo>%d</materialNo>\r\n"\
        "<materialName>%s</materialName>\r\n"\
        "<fileType>picture</fileType>\r\n"\
        "<picFormat>%s</picFormat>\r\n"\
        "<fileSize>%d</fileSize>\r\n"\
        "<cancelType>%s</cancelType>\r\n"\
        "<duration>%d</duration>\r\n"\
        "<destType>%s</destType>\r\n"\
        "%s"
        "</ThridPartyFile>\r\n", m_dwMaterialId, m_csMaterialName, m_csPicType, m_dwFileSize, m_csCancelType, m_dwDuration, m_csDisplayType, str.GetBuffer(0));
    char szOutputBuff[1024*2] = { 0 };
    string utf_8 = GB2UTF(szBuf);
    m_lHandle = NET_DVR_UploadFile_V40(m_lUserID, UPLOAD_PUBLISH_THIRD_PARTY_FILE, (char*)utf_8.c_str(), utf_8.length(), m_csFilePath.GetBuffer(0), szOutputBuff, sizeof(szOutputBuff));
    if (m_lHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadFile_V40 UPLOAD_PUBLISH_THIRD_PARTY_FILE");
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadFile_V40 UPLOAD_PUBLISH_THIRD_PARTY_FILE");

    m_bUploading = TRUE;
    m_ctrlProgress.SetPos(0);
    m_statProgress.SetWindowText(_T("0%"));
    SetTimer(TIMER_UPDOWNLOAD_THIRD_PROGRESS, 100, NULL);
}


void CDlgDyanmicPic::OnBnClickedBtnTerAdd()
{
    // TODO:  在此添加控件通知处理程序代码

    UpdateData(TRUE);
    CString str;
    int nIndex = nIndex = m_listTerminal.GetItemCount();
    str.Format("%d", nIndex + 1);
    m_listTerminal.InsertItem(nIndex, str);
    str.Format("%d", m_dwTerminalNo);
    m_listTerminal.SetItemText(nIndex, 1, str);
    m_listTerminal.SetItemState(m_nCurSelTerminal, 0, -1);
    m_listTerminal.SetItemState(nIndex, LVIS_SELECTED, LVIS_SELECTED);
    m_listTerminal.SetFocus();
    m_nCurSelTerminal = nIndex;

    m_arrTerminal[m_iTerminalCount] = m_dwTerminalNo;
    m_iTerminalCount++;
}


void CDlgDyanmicPic::OnBnClickedBtnMaterialChoose()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    CString strFilter;
    if (0 == strcmp(m_csFileType, "picture")) //图片
    {
        strFilter.Format("Picture(*.");
        strFilter += m_csPicType;
        strFilter += _T(")|*.");
        strFilter += m_csPicType;
        strFilter += _T("|All Files(*.*)|*.*||");
    }

    CFileDialog fileChose(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
    if (fileChose.DoModal() != IDOK)
    {
        return;
    }
    m_csFilePath = fileChose.GetPathName();
    CFile file;
    if (!file.Open(m_csFilePath, CFile::modeRead))
    {
        char szLan1[512] = { 0 };
        char szLan2[512] = { 0 };
        g_StringLanType(szLan1, "打开文件失败", "Open file failed.");
        g_StringLanType(szLan2, "素材管理", "Material Management");
        MessageBox(szLan1, szLan2, MB_ICONWARNING);
        return;
    }
    m_dwFileSize = file.GetLength();
    file.Close();
    UpdateData(FALSE);
}


void CDlgDyanmicPic::OnTimer(UINT_PTR nIDEvent)
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值

    if (nIDEvent == TIMER_UPDOWNLOAD_THIRD_PROGRESS)
    {
        DWORD dwProgress = 0;
        LONG lStatus = -1;

        lStatus = NET_DVR_GetUploadState(m_lHandle, &dwProgress);
        if (lStatus == -1)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetUploadState");
            if (!NET_DVR_UploadClose(m_lHandle))
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
            }
            else
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
            }
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetUploadState");
        }
        switch (lStatus)
        {
        case 1: //下载成功
        {
                    m_ctrlProgress.SetPos(dwProgress);
                    CString str;
                    str.Format("%d", dwProgress);
                    str += _T("%");
                    m_statProgress.SetWindowText(str);
                    if (!NET_DVR_UploadClose(m_lHandle))
                    {
                        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
                    }
                    else
                    {
                        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
                    }
                    m_bUploading = FALSE;
                    m_lHandle = -1;
                    KillTimer(TIMER_UPDOWNLOAD_THIRD_PROGRESS);
                    char sTitle[64] = { 0 };
                    char sMsg[64] = { 0 };
                    g_StringLanType(sTitle, "日程管理", "Schedule Management");
                    g_StringLanType(sMsg, "导出完成", "Download finished.");
                    MessageBox(sMsg, sTitle, MB_OK | MB_ICONWARNING);
                    break;
        }
        case 2: //正在下载
        {
                    m_ctrlProgress.SetPos(dwProgress);
                    CString str;
                    str.Format("%d", dwProgress);
                    str += _T("%");
                    m_statProgress.SetWindowText(str);
                    break;
        }
        case 3://下载失败
        {
                   if (!NET_DVR_UploadClose(m_lHandle))
                   {
                       g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
                   }
                   else
                   {
                       g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
                   }
                   m_bUploading = FALSE;
                   m_lHandle = -1;
                   KillTimer(TIMER_UPDOWNLOAD_THIRD_PROGRESS);
                   char sTitle[64] = { 0 };
                   char sMsg[64] = { 0 };
                   g_StringLanType(sTitle, "日程管理", "Schedule Management");
                   g_StringLanType(sMsg, "导出失败", "Download fail.");
                   MessageBox(sMsg, sTitle, MB_OK | MB_ICONWARNING);
                   break;

        }
        case 4: //网络断开
        {
                    if (!NET_DVR_UploadClose(m_lHandle))
                    {
                        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
                    }
                    else
                    {
                        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
                    }
                    m_bUploading = FALSE;
                    m_lHandle = -1;
                    KillTimer(TIMER_UPDOWNLOAD_THIRD_PROGRESS);
                    char sTitle[64] = { 0 };
                    char sMsg[64] = { 0 };
                    g_StringLanType(sTitle, "日程管理", "Schedule Management");
                    g_StringLanType(sMsg, "网络断开", "network disconnect");
                    MessageBox(sMsg, sTitle, MB_OK | MB_ICONWARNING);
                    break;
        }
        }
    }
        CDialog::OnTimer(nIDEvent);
}




void CDlgDyanmicPic::OnBnClickedBtnTerDel()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_nCurSelTerminal < 0)
    {
        char szLan1[512] = { 0 };
        char szLan2[512] = { 0 };
        g_StringLanType(szLan1, "请选择终端/终端组", "Please choose a terminal/group first.");
        g_StringLanType(szLan2, "播放控制", "Play Control");
        MessageBox(szLan1, szLan2, MB_ICONWARNING);
        return;
    }
   

        for (int nTerCnt = m_nCurSelTerminal; nTerCnt < m_listTerminal.GetItemCount() - 1; nTerCnt++)
        {
            m_listTerminal.SetItemText(nTerCnt, 1, m_listTerminal.GetItemText(nTerCnt + 1, 1));
            m_arrTerminal[nTerCnt] = m_arrTerminal[nTerCnt + 1];
        }
        m_arrTerminal[m_listTerminal.GetItemCount() - 1] = 0;
        m_iTerminalCount--; //数量-1;

   
    m_listTerminal.DeleteItem(m_listTerminal.GetItemCount() - 1);
    m_nCurSelTerminal = -1;
}


void CDlgDyanmicPic::OnBnClickedBtnTerMod()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    if (m_nCurSelTerminal < 0)
    {
        char szLan1[512] = { 0 };
        char szLan2[512] = { 0 };
        g_StringLanType(szLan1, "请选择终端/终端组", "Please choose a terminal/group first.");
        g_StringLanType(szLan2, "播放控制", "Play Control");
        MessageBox(szLan1, szLan2, MB_ICONWARNING);
        return;
    }

    m_arrTerminal[m_nCurSelTerminal] = m_dwTerminalNo;
    CString str;
    str.Format("%d", m_dwTerminalNo);
    m_listTerminal.SetItemText(m_nCurSelTerminal, 1, str);
}


void CDlgDyanmicPic::OnNMClickListTerminal(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO:  在此添加控件通知处理程序代码
    POSITION pos = m_listTerminal.GetFirstSelectedItemPosition();
    if (pos)
    {
        m_nCurSelTerminal = m_listTerminal.GetNextSelectedItem(pos);
       
        m_dwTerminalNo = m_arrTerminal[m_nCurSelTerminal];
       
        UpdateData(FALSE);
    }
    *pResult = 0;
}


BOOL CDlgDyanmicPic::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
    DWORD dwExStyle = m_listTerminal.GetExtendedStyle();
    dwExStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    m_listTerminal.SetExtendedStyle(dwExStyle);

    char szLan[512] = { 0 };

    dwExStyle = m_listTerminal.GetExtendedStyle();
    dwExStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    m_listTerminal.SetExtendedStyle(dwExStyle);
    g_StringLanType(szLan, "序号", "Index");
    m_listTerminal.InsertColumn(0, szLan);
    m_listTerminal.SetColumnWidth(0, 60);

    memset(szLan, 0, sizeof(szLan));
    g_StringLanType(szLan, "终端（组）编号", "Terminal No.");
    m_listTerminal.InsertColumn(1, szLan);
    m_listTerminal.SetColumnWidth(1, 100);

    dwExStyle = m_listOrg.GetExtendedStyle();
    dwExStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    m_listOrg.SetExtendedStyle(dwExStyle);



    dwExStyle = m_listOrg.GetExtendedStyle();
    dwExStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    m_listOrg.SetExtendedStyle(dwExStyle);
    g_StringLanType(szLan, "序号", "Index");
    m_listOrg.InsertColumn(0, szLan);
    m_listOrg.SetColumnWidth(0, 60);

    memset(szLan, 0, sizeof(szLan));
    g_StringLanType(szLan, "组织编号", "Org No.");
    m_listOrg.InsertColumn(1, szLan);
    m_listOrg.SetColumnWidth(1, 100);

    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}


void CDlgDyanmicPic::OnBnClickedBtnTerAdd2()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    CString str;
    int nIndex = nIndex = m_listOrg.GetItemCount();
    str.Format("%d", nIndex + 1);
    m_listOrg.InsertItem(nIndex, str);
    str.Format("%d", m_iOrgNo);
    m_listOrg.SetItemText(nIndex, 1, str);
    m_listOrg.SetItemState(m_nCurSelOrg, 0, -1);
    m_listOrg.SetItemState(nIndex, LVIS_SELECTED, LVIS_SELECTED);
    m_listOrg.SetFocus();
    m_nCurSelOrg = nIndex;

    m_arrOrg[m_iOrgCount] = m_iOrgNo;
    m_iOrgCount++;
}
