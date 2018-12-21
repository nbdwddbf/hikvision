// DlgInfoGerenal.cpp : 实现文件
//

#include "stdafx.h"
#include "ParseXMLHelper.h"
#include "ClientDemo.h"
#include "DlgInfoGerenal.h"
#include "afxdialogex.h"

string GB2UTF(const char* gb2312)
{
    int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* sztr = new char[len + 1];
    memset(sztr, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, sztr, len, NULL, NULL);
    if (wstr) delete[] wstr;

    string str = sztr;
    delete[] sztr;
    sztr = NULL;
    return str;
}

string UTF2GB(const char* utf8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
    len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* sztr = new char[len + 1];
    memset(sztr, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, sztr, len, NULL, NULL);
    if (wstr) delete[] wstr;

    string str = sztr;
    delete[] sztr;
    sztr = NULL;
    return str;
}

// CDlgInfoGerenal 对话框

IMPLEMENT_DYNAMIC(CDlgInfoGerenal, CDialog)

CDlgInfoGerenal::CDlgInfoGerenal(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoGerenal::IDD, pParent)
    , m_dwId(0)
    , m_csType(_T(""))
    , m_dwTerminalNo(0)
    , m_csValue(_T(""))
    , m_csDataType(_T(""))
    , m_csCommand(_T(""))
    , m_csRefreshD(_T(""))
    , m_csMaterialName(_T(""))
{
    m_iTerminalCount = 0;
    m_iData = 0;
}

CDlgInfoGerenal::~CDlgInfoGerenal()
{
}

void CDlgInfoGerenal::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_MATERIAL_ID, m_dwId);
    DDX_CBString(pDX, IDC_COMBO_DEST_TYPE, m_csType);
    DDX_Text(pDX, IDC_EDIT_TER_ID, m_dwTerminalNo);
    DDX_Text(pDX, IDC_EDIT_VALUE, m_csValue);
    DDX_Control(pDX, IDC_LIST_TERMINAL, m_listTerminal);
    DDX_Control(pDX, IDC_LIST_GENERAL, m_listGeneral);
    DDX_CBString(pDX, IDC_COMBO_DEST_TYPE2, m_csDataType);
    DDX_CBString(pDX, IDC_COMBO_DEST_TYPE3, m_csCommand);
    DDX_CBString(pDX, IDC_COMBO_REFRESH_TYPE, m_csRefreshD);
    DDX_Text(pDX, IDC_EDIT_MATERIAL_NAME, m_csMaterialName);
}


BEGIN_MESSAGE_MAP(CDlgInfoGerenal, CDialog)
    ON_BN_CLICKED(IDC_BTN_TER_ADD, &CDlgInfoGerenal::OnBnClickedBtnTerAdd)
    ON_BN_CLICKED(IDC_BTN_GROUP_ADD, &CDlgInfoGerenal::OnBnClickedBtnGroupAdd)
    ON_BN_CLICKED(IDC_BTN_GROUP_LIST, &CDlgInfoGerenal::OnBnClickedBtnGroupList)
    ON_BN_CLICKED(IDC_BTN_CLEAN, &CDlgInfoGerenal::OnBnClickedBtnClean)
    ON_BN_CLICKED(IDC_BTN_CANCEL, &CDlgInfoGerenal::OnBnClickedBtnCancel)
    ON_BN_CLICKED(IDC_BTN_OK, &CDlgInfoGerenal::OnBnClickedBtnOk)
    ON_BN_CLICKED(IDC_BTN_TER_DEL, &CDlgInfoGerenal::OnBnClickedBtnTerDel)
    ON_BN_CLICKED(IDC_BTN_TER_MOD, &CDlgInfoGerenal::OnBnClickedBtnTerMod)
    ON_NOTIFY(NM_CLICK, IDC_LIST_TERMINAL, &CDlgInfoGerenal::OnNMClickListTerminal)
END_MESSAGE_MAP()


// CDlgInfoGerenal 消息处理程序


void CDlgInfoGerenal::OnBnClickedBtnTerAdd()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    CString str;
    int nIndex = m_listTerminal.GetItemCount();
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


BOOL CDlgInfoGerenal::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化

    DWORD dwExStyle = m_listTerminal.GetExtendedStyle();
    dwExStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    m_listTerminal.SetExtendedStyle(dwExStyle);

    char szLan[512] = { 0 };


    dwExStyle = m_listGeneral.GetExtendedStyle();
    dwExStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    m_listGeneral.SetExtendedStyle(dwExStyle);

    g_StringLanType(szLan, "序号", "Index");
    m_listGeneral.InsertColumn(0, szLan);
    m_listGeneral.SetColumnWidth(0, 60);

    memset(szLan, 0, sizeof(szLan));
    g_StringLanType(szLan, "值", "value");
    m_listGeneral.InsertColumn(1, szLan);
    m_listGeneral.SetColumnWidth(1, 100);

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

    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}


void CDlgInfoGerenal::OnBnClickedBtnGroupAdd()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    CString str;
    int nIndex = m_listGeneral.GetItemCount();
    str.Format("%d", nIndex + 1);
    m_listGeneral.InsertItem(nIndex, str);
    str.Format("%s", m_csValue);
    m_listGeneral.SetItemText(nIndex, 1, str);
    m_listGeneral.SetItemState(m_nCurSelGeneral, 0, -1);
    m_listGeneral.SetItemState(nIndex, LVIS_SELECTED, LVIS_SELECTED);
    m_listGeneral.SetFocus();
    m_nCurSelGeneral = nIndex;
    m_arrStr[m_iData] = m_csValue;
    m_iData++;
}


void CDlgInfoGerenal::OnBnClickedBtnGroupList()
{
    // TODO:  在此添加控件通知处理程序代码
    CString strTmp;
    m_csData += "<DataList>\r\n";
    for (int i = 0; i < m_iData; i++)
    {
        strTmp.Format("<Data>\r\n"
            "<id>%d</id>\r\n"
            "<value>%s</value>\r\n"
            "</Data>\r\n", i + 1, m_arrStr[i].GetBuffer(0));
        m_csData += strTmp;
    }
    m_csData += "</DataList>\r\n";
    m_iData=0;
    m_listGeneral.DeleteAllItems();
    UpdateData(FALSE);
}


void CDlgInfoGerenal::OnBnClickedBtnClean()
{
    // TODO:  在此添加控件通知处理程序代码
    m_listGeneral.DeleteAllItems();
    m_listTerminal.DeleteAllItems();
    m_csDataType = "";
    m_csType = "";
    m_csCommand = "";
    m_csRefreshD = "";
    m_dwId = 0;
    m_iData = 0;
    m_csData = "";
    m_iTerminalCount=0;
    UpdateData(FALSE);
}


void CDlgInfoGerenal::OnBnClickedBtnCancel()
{
    // TODO:  在此添加控件通知处理程序代码
    CDialog::OnCancel();
}


void CDlgInfoGerenal::OnBnClickedBtnOk()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (m_iData > 0)
    {
        m_csData += "<DataList>\r\n";
        CString strTmp;
        for (int i = 0; i < m_iData; i++)
        {
            strTmp.Format("<Data>\r\n"
                "<id>%d</id>\r\n"
                "<value>%s</value>\r\n"
                "</Data>\r\n", i + 1, m_arrStr[i].GetBuffer(0));
            m_csData += strTmp;
        }
        m_csData += "</DataList>\r\n";
    }
    
    CString strTerminal;
    if (strcmp(m_csType, "byTerminal") == 0)
    {
        strTerminal += "<TerminalNoList>\r\n";
        for (int i = 0; i < m_iTerminalCount; i++)
        {
            CString strTmp;
            strTmp.Format("<terminalNo>%d</terminalNo>\r\n", m_arrTerminal[i]);
            strTerminal += strTmp;
        }
        strTerminal += "</TerminalNoList>\r\n";
    }
    else if (strcmp(m_csType, "byGroup") == 0)
    {
        strTerminal += "<TerminalGroupNoList>\r\n";
        for (int i = 0; i < m_iTerminalCount; i++)
        {
            CString strTmp;
            strTmp.Format("<terminalGroupNo>%d</terminalGroupNo>\r\n", m_arrTerminal[i]);
            strTerminal += strTmp;
        }
        strTerminal += "</TerminalGroupNoList>\r\n";
    }
    else if (strcmp(m_csType, "byOrg") == 0)
    {
        strTerminal += "<OrgNoList>\r\n";
        for (int i = 0; i < m_iTerminalCount; i++)
        {
            CString strTmp;
            strTmp.Format("<orgNo>%d</orgNo>\r\n", m_arrTerminal[i]);
            strTerminal += strTmp;
        }
        strTerminal += "</OrgNoList>\r\n";
    }


    char szBuf[1024 * 5] = { 0 };
    sprintf(szBuf, "<TransData version=\"2.0\">\r\n"
        "<materialNo>%d</materialNo>\r\n"
        "<materialName>%s</materialName>\r\n"
        "<destType>%s</destType>\r\n"
        "%s"
        "<dataType>%s</dataType>\r\n"
        "<SendData>\r\n"
        "<refreshType>%s</refreshType>\r\n"
        "<ItemDataList>\r\n"
        "%s"
        "</ItemDataList>\r\n"
        "</SendData>\r\n"
        "<sendCommand>%s</sendCommand>\r\n"
        "</TransData>\r\n", m_dwId, m_csMaterialName,m_csType.GetBuffer(0), strTerminal.GetBuffer(0),m_csDataType.GetBuffer(0), m_csRefreshD.GetBuffer(0), m_csData.GetBuffer(0), m_csCommand.GetBuffer(0));

    string utf_8 = GB2UTF(szBuf);

    CString strCommand;
    strCommand.Format("POST /ISAPI/Publish/GerDataMgr/transData\r\n");
    NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
    struInputParam.dwRequestUrlLen = strCommand.GetLength();
    struInputParam.lpInBuffer = (void*)utf_8.c_str();
    struInputParam.dwInBufferSize = utf_8.length();

    NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = { 0 };
    char szXMLStatus[1024] = { 0 };
    memset(szXMLStatus, 0, 1024);
    struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
    struXMLCfgOutput.lpOutBuffer = NULL;
    struXMLCfgOutput.dwOutBufferSize = 0;
    struXMLCfgOutput.lpStatusBuffer = szXMLStatus;
    struXMLCfgOutput.dwStatusSize = 1024;


    if (NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struXMLCfgOutput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
    }
    m_csData = "";
}


void CDlgInfoGerenal::OnBnClickedBtnTerDel()
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


void CDlgInfoGerenal::OnBnClickedBtnTerMod()
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


void CDlgInfoGerenal::OnNMClickListTerminal(NMHDR *pNMHDR, LRESULT *pResult)
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
