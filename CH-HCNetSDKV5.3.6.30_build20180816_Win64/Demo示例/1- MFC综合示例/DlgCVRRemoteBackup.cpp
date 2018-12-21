// DlgCVRRemoteBackup.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgCVRRemoteBackup.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgCVRRemoteBackup 对话框

IMPLEMENT_DYNAMIC(CDlgCVRRemoteBackup, CDialogEx)

CDlgCVRRemoteBackup::CDlgCVRRemoteBackup(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCVRRemoteBackup::IDD, pParent)
    , m_strDeleteTaskID(_T(""))
    , m_strIPV4Address(_T(""))
    , m_strIPV6Address(_T(""))
    , m_strPassword(_T(""))
    , m_strTaskFileIndex(_T(""))
    , m_strTaskID(_T(""))
    , m_strTaskURL(_T(""))
    , m_strUserName(_T(""))
    , m_strSearchID(_T(""))
    , m_iMaxCountRet(0)
    , m_iCountStartRet(0)
    , m_strSearchResult(_T(""))
    , m_strSearchStatus(_T(""))
    , m_iCountResult(0)
    , m_bRegerateID(FALSE)
    , m_iStatusMaxCountRet(0)
{
    m_iRowCount = 0;
    m_bSelectItem = FALSE;
    m_iSubItem = -1;
    m_iLastItem = -1;
}

CDlgCVRRemoteBackup::~CDlgCVRRemoteBackup()
{
}

void CDlgCVRRemoteBackup::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_DELETE_TYPE, m_comboDeleteType);
    DDX_Control(pDX, IDC_COMBO_IP_VERSION, m_comboIPVersion);
    DDX_Control(pDX, IDC_COMBO_SEARCH_TYPE, m_comboSearchType);
    DDX_Text(pDX, IDC_EDIT_DELETE_TASK_ID, m_strDeleteTaskID);
    DDX_Text(pDX, IDC_EDIT_IPV4_ADDRESS, m_strIPV4Address);
    DDX_Text(pDX, IDC_EDIT_IPV6_ADDRESS, m_strIPV6Address);
    DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
    DDX_Text(pDX, IDC_EDIT_TASK_FILE_INDEX, m_strTaskFileIndex);
    DDX_Text(pDX, IDC_EDIT_TASK_ID, m_strTaskID);
    DDX_Text(pDX, IDC_EDIT_TASK_URL, m_strTaskURL);
    DDX_Text(pDX, IDC_EDIT_USER_NAME, m_strUserName);
    DDX_Control(pDX, IDC_LIST_ADD_TASK, m_listAddTask);
    DDX_Control(pDX, IDC_LIST_SEARCH_TASK, m_listSearchTask);
    DDX_Text(pDX, IDC_EDT_SEARCH_ID, m_strSearchID);
    DDX_Text(pDX, IDC_EDT_MAX_COUNT_RET, m_iMaxCountRet);
    DDX_Text(pDX, IDC_EDT_NUM_BEGIN_RET, m_iCountStartRet);
    DDX_Text(pDX, IDC_EDIT_SEARCH_RET, m_strSearchResult);
    DDX_Text(pDX, IDC_EDIT_SEARCH_STATUS, m_strSearchStatus);
    DDX_Text(pDX, IDC_STA_COUNT_RET, m_iCountResult);
    DDX_Check(pDX, IDC_CHECK_REGERATE_ID, m_bRegerateID);
    DDX_Text(pDX, IDC_STA_MAX_COUNT_RET, m_iStatusMaxCountRet);
}


BEGIN_MESSAGE_MAP(CDlgCVRRemoteBackup, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgCVRRemoteBackup::OnBnClickedButtonGet)
    ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgCVRRemoteBackup::OnBnClickedButtonSet)
    ON_BN_CLICKED(IDC_BUTTON_ADD_TASK, &CDlgCVRRemoteBackup::OnBnClickedButtonAddTask)
    ON_BN_CLICKED(IDC_BUTTON_DELETE_TASK, &CDlgCVRRemoteBackup::OnBnClickedButtonDeleteTask)
    ON_BN_CLICKED(IDC_BUTTON_TASK_SET, &CDlgCVRRemoteBackup::OnBnClickedButtonTaskSet)
    ON_BN_CLICKED(IDC_BUTTON_SEARCH_TASK, &CDlgCVRRemoteBackup::OnBnClickedButtonSearchTask)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgCVRRemoteBackup::OnBnClickedButtonDelete)
    ON_NOTIFY(NM_CLICK, IDC_LIST_ADD_TASK, &CDlgCVRRemoteBackup::OnNMClickListAddTask)
    ON_BN_CLICKED(IDC_BUTTON_CLEAR_LIST, &CDlgCVRRemoteBackup::OnBnClickedButtonClearList)
END_MESSAGE_MAP()


// CDlgCVRRemoteBackup 消息处理程序

BOOL CDlgCVRRemoteBackup::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化

    char szLan[128] = { 0 };
    m_listAddTask.SetExtendedStyle(m_listAddTask.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);

    g_StringLanType(szLan, "序号", "Index");
    m_listAddTask.InsertColumn(0, szLan, LVCFMT_LEFT, 60, -1);

    g_StringLanType(szLan, "文件索引", "File index");
    m_listAddTask.InsertColumn(1, szLan, LVCFMT_LEFT, 120, -1);

    g_StringLanType(szLan, "url", "url");
    m_listAddTask.InsertColumn(2, szLan, LVCFMT_LEFT, 240, -1);

    g_StringLanType(szLan, "返回文件索引", "File index return");
    m_listAddTask.InsertColumn(3, szLan, LVCFMT_LEFT, 120, -1);

    g_StringLanType(szLan, "任务ID", "Task ID");
    m_listAddTask.InsertColumn(4, szLan, LVCFMT_LEFT, 180, -1);

    g_StringLanType(szLan, "出错原因", "Error description");
    m_listAddTask.InsertColumn(5, szLan, LVCFMT_LEFT, 200, -1);

    m_listSearchTask.SetExtendedStyle(m_listSearchTask.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);

    g_StringLanType(szLan, "序号", "Index");
    m_listSearchTask.InsertColumn(0, szLan, LVCFMT_LEFT, 60, -1);

    g_StringLanType(szLan, "文件索引", "File index");
    m_listSearchTask.InsertColumn(1, szLan, LVCFMT_LEFT, 120, -1);

    g_StringLanType(szLan, "任务ID", "Task ID");
    m_listSearchTask.InsertColumn(2, szLan, LVCFMT_LEFT, 60, -1);

    g_StringLanType(szLan, "url", "url");
    m_listSearchTask.InsertColumn(3, szLan, LVCFMT_LEFT, 240, -1);

    g_StringLanType(szLan, "异地备份状态", "Backup status");
    m_listSearchTask.InsertColumn(4, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "备机url", "Backup Machine url");
    m_listSearchTask.InsertColumn(5, szLan, LVCFMT_LEFT, 240, -1);

    char szGUID[MAX_XML_ELEM_LEN] = { 0 };
    if (!GenerateGUID(szGUID, MAX_XML_ELEM_LEN))
    {
        MessageBox("生成UUID失败!");
        return TRUE;
    }

    m_strSearchID = szGUID;

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}

BOOL CDlgCVRRemoteBackup::CreateBackupMachineInfo(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CXmlBase xmlBase;
    CString strParam = _T("");
    xmlBase.CreateRoot("BackupMachineInfo");
    xmlBase.SetAttribute("version", "2.0");
    if (m_comboIPVersion.GetCurSel() == 0)
    {
        xmlBase.AddNode("ipVersion", "v4");
        xmlBase.OutOfElem();

        xmlBase.AddNode("ipAddress", m_strIPV4Address.GetBuffer(0));
        xmlBase.OutOfElem();
    }
    else if (m_comboIPVersion.GetCurSel() == 1)
    {
        xmlBase.AddNode("ipVersion", "v6");
        xmlBase.OutOfElem();

        xmlBase.AddNode("ipv6Address", m_strIPV6Address.GetBuffer(0));
        xmlBase.OutOfElem();
    }
    else if (m_comboIPVersion.GetCurSel() == 2)
    {
        xmlBase.AddNode("ipVersion", "dual");
        xmlBase.OutOfElem();

        xmlBase.AddNode("ipAddress", m_strIPV4Address.GetBuffer(0));
        xmlBase.OutOfElem();

        xmlBase.AddNode("ipv6Address", m_strIPV6Address.GetBuffer(0));
        xmlBase.OutOfElem();
    }

    xmlBase.AddNode("userName", m_strUserName.GetBuffer(0));
    xmlBase.OutOfElem();

    xmlBase.AddNode("password", m_strPassword.GetBuffer(0));
    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}


void CDlgCVRRemoteBackup::OnBnClickedButtonGet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/ContentMgmt/RemoteBackup/BackupMachineInfo\r\n");
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
        if (pOutBuf != NULL)
        {
            delete[]pOutBuf;
            pOutBuf = NULL;
        }
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    CXmlBase xmlBase;
    xmlBase.Parse(pOutBuf);
    if (xmlBase.FindElem("BackupMachineInfo") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("ipVersion"))
        {
            if (xmlBase.GetData().compare("v4") == 0)
            {
                m_comboIPVersion.SetCurSel(0);

                if (xmlBase.FindElem("ipAddress"))
                {
                    m_strIPV4Address = xmlBase.GetData().c_str();
                }
            }
            else if (xmlBase.GetData().compare("v6") == 0)
            {
                m_comboIPVersion.SetCurSel(1);

                if (xmlBase.FindElem("ipv6Address"))
                {
                    m_strIPV6Address = xmlBase.GetData().c_str();
                }
            }
            else if (xmlBase.GetData().compare("dual") == 0)
            {
                m_comboIPVersion.SetCurSel(2);

                if (xmlBase.FindElem("ipAddress"))
                {
                    m_strIPV4Address = xmlBase.GetData().c_str();
                }

                if (xmlBase.FindElem("ipv6Address"))
                {
                    m_strIPV6Address = xmlBase.GetData().c_str();
                }
            }

            if (xmlBase.FindElem("userName"))
            {
                m_strUserName = xmlBase.GetData().c_str();
            }
        }
        xmlBase.OutOfElem();
    }

    if (pOutBuf != NULL)
    {
        delete[]pOutBuf;
        pOutBuf = NULL;
    }
    UpdateData(FALSE);

    return;
}


void CDlgCVRRemoteBackup::OnBnClickedButtonSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateBackupMachineInfo(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/ContentMgmt/RemoteBackup/BackupMachineInfo\r\n");
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    struInput.lpInBuffer = pBuf;
    struInput.dwInBufferSize = dwXmlLen;
    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    if (pBuf != NULL)
    {
        delete[]pBuf;
        pBuf = NULL;
    }

    UpdateData(FALSE);
}


void CDlgCVRRemoteBackup::OnBnClickedButtonAddTask()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    int iRowCount = m_listAddTask.GetItemCount();
    CString strTemp = _T("");
    strTemp.Format("%d", iRowCount);
    m_listAddTask.InsertItem(iRowCount, strTemp);
    m_listAddTask.SetItemText(iRowCount, 1, m_strTaskFileIndex);
    m_listAddTask.SetItemText(iRowCount, 2, m_strTaskURL);
    UpdateData(FALSE);
}


void CDlgCVRRemoteBackup::OnBnClickedButtonDeleteTask()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_iRowCount = m_listAddTask.GetItemCount();
    if (m_iLastItem >= 0 && m_iLastItem < m_iRowCount)
    {
        m_listAddTask.DeleteItem(m_iLastItem);
    }
    UpdateData(FALSE);
}

void CDlgCVRRemoteBackup::OnNMClickListAddTask(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO:  在此添加控件通知处理程序代码

    m_iLastItem = pNMItemActivate->iItem;
    m_iSubItem = pNMItemActivate->iSubItem;
    m_bSelectItem = TRUE;

    int iItemSel = 0;
    CString csTxt;

    POSITION  iPos = m_listAddTask.GetFirstSelectedItemPosition();
    if (iPos == NULL)
    {
        return;
    }
    iItemSel = m_listAddTask.GetNextSelectedItem(iPos);
    csTxt.Format("%s", m_listAddTask.GetItemText(iItemSel, 4));
    if (OpenClipboard())
    {
        HGLOBAL   clipbuffer;
        char   *   buffer;
        EmptyClipboard();
        clipbuffer = GlobalAlloc(GMEM_DDESHARE, csTxt.GetLength() + 1);
        buffer = (char*)GlobalLock(clipbuffer);
        strcpy(buffer, LPCSTR(csTxt));
        GlobalUnlock(clipbuffer);
        SetClipboardData(CF_TEXT, clipbuffer);
        CloseClipboard();
    }

    *pResult = 0;
}

BOOL CDlgCVRRemoteBackup::CreateAddTaskCondition(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    int iRowCount = m_listAddTask.GetItemCount();

    CString strParam = _T("");
    CXmlBase xmlBase;
    xmlBase.CreateRoot("RemoteBackupAddTask");
    xmlBase.SetAttribute("version", "2.0");
    xmlBase.AddNode("BackupList");

    for (int i = 0; i < iRowCount; i++)
    {
        xmlBase.AddNode("BackupInfo");
        strParam.Format("%s", m_listAddTask.GetItemText(i, 1));
        xmlBase.AddNode("fileIndex", strParam.GetBuffer(0));
        xmlBase.OutOfElem();
        strParam.Format("%s", m_listAddTask.GetItemText(i, 2));
        xmlBase.AddNode("url", strParam.GetBuffer(0));
        xmlBase.OutOfElem();
        xmlBase.OutOfElem();
    }
    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

void CDlgCVRRemoteBackup::OnBnClickedButtonTaskSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    char szLan[128] = { 0 };

    int iRowCount = m_listAddTask.GetItemCount();

    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateAddTaskCondition(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    char szUrl[256] = { 0 };
    sprintf(szUrl, "POST /ISAPI/ContentMgmt/RemoteBackup/addTask\r\n");

    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    struInput.lpInBuffer = pBuf;
    struInput.dwInBufferSize = dwXmlLen;
    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
        delete[]pOutBuf;
        pOutBuf = NULL;
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    BOOL bRet = FALSE;
    CXmlBase xmlBase;
    xmlBase.Parse(pOutBuf);
    if (xmlBase.FindElem("RemoteBackupTaskInfo") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("TaskList") && xmlBase.IntoElem())
        {
            for (int i = 0; i < iRowCount; i++)
            {
                if (xmlBase.FindElem("TaskInfo") && xmlBase.IntoElem())
                {
                    if (xmlBase.FindElem("fileIndex"))
                    {
                        m_listAddTask.SetItemText(i, 3, xmlBase.GetData().c_str());
                    }
                    if (xmlBase.FindElem("taskID"))
                    {
                        m_listAddTask.SetItemText(i, 4, xmlBase.GetData().c_str());
                    }
                    if (xmlBase.FindElem("errorDescription"))
                    {
                        m_listAddTask.SetItemText(i, 5, xmlBase.GetData().c_str());
                    }
                    xmlBase.OutOfElem();
                }
                xmlBase.NextSibElem();
            }
            xmlBase.OutOfElem();
        }
        xmlBase.OutOfElem();
    }

    if (pOutBuf != NULL)
    {
        delete[]pOutBuf;
        pOutBuf = NULL;
    }

    if (pBuf != NULL)
    {
        delete[]pBuf;
        pBuf = NULL;
    }

    UpdateData(FALSE);
}

BOOL CDlgCVRRemoteBackup::CreateSearchTaskCondition(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CString strParam = _T("");
    CXmlBase xmlBase;
    xmlBase.CreateRoot("RemoteBackupSearchTask");
    xmlBase.SetAttribute("version", "2.0");

    xmlBase.AddNode("searchID", m_strSearchID.GetBuffer(0));
    xmlBase.OutOfElem();

    strParam.Format("%d", m_iCountStartRet);
    xmlBase.AddNode("searchResultPosition", strParam.GetBuffer(0));
    xmlBase.OutOfElem();

    strParam.Format("%d", m_iMaxCountRet);
    xmlBase.AddNode("maxResults", strParam.GetBuffer(0));
    xmlBase.OutOfElem();

    if (m_comboSearchType.GetCurSel() == 0)
    {
        xmlBase.AddNode("searchType", "taskID");
        xmlBase.OutOfElem();

        xmlBase.AddNode("taskID", m_strTaskID.GetBuffer(0));
        xmlBase.OutOfElem();
    }
    else if (m_comboSearchType.GetCurSel() == 1)
    {
        xmlBase.AddNode("searchType", "noPerformTask");
        xmlBase.OutOfElem();
    }
    else if (m_comboSearchType.GetCurSel() == 2)
    {
        xmlBase.AddNode("searchType", "performTask");
        xmlBase.OutOfElem();
    }
    else if (m_comboSearchType.GetCurSel() == 3)
    {
        xmlBase.AddNode("searchType", "all");
        xmlBase.OutOfElem();
    }

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

void CDlgCVRRemoteBackup::OnBnClickedButtonSearchTask()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    char szLan[128] = { 0 };
    CString strTemp = _T("");

    char szGUID[MAX_XML_ELEM_LEN] = { 0 };

    if (m_bRegerateID)
    {
        if (!GenerateGUID(szGUID, MAX_XML_ELEM_LEN))
        {
            MessageBox("生成UUID失败!");
            return;
        }

        m_strSearchID = szGUID;
        UpdateData(FALSE);
    }

    int iRowCount = m_listSearchTask.GetItemCount();

    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateSearchTaskCondition(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    char szUrl[256] = { 0 };
    sprintf(szUrl, "POST /ISAPI/ContentMgmt/RemoteBackup/SearchTask\r\n");

    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    struInput.lpInBuffer = pBuf;
    struInput.dwInBufferSize = dwXmlLen;
    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
        delete[]pOutBuf;
        pOutBuf = NULL;
        m_strSearchID = _T("");
        m_strSearchResult = _T("");
        m_strSearchStatus = _T("");
        m_iCountResult = 0;
        m_iStatusMaxCountRet = 0;
        UpdateData(FALSE);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    BOOL bRet = FALSE;
    CXmlBase xmlBase;
    xmlBase.Parse(pOutBuf);
    if (xmlBase.FindElem("RemoteBackupTaskData") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("searchID"))
        {
            m_strSearchID = xmlBase.GetData().c_str();
        }
        if (xmlBase.FindElem("responseStatus"))
        {
            m_strSearchResult = xmlBase.GetData().c_str();
        }
        if (xmlBase.FindElem("responseStatusStrg"))
        {
            m_strSearchStatus = xmlBase.GetData().c_str();
        }
        if (xmlBase.FindElem("numOfMatches"))
        {
            m_iCountResult = atoi(xmlBase.GetData().c_str());
        }
        if (xmlBase.FindElem("totalMatches"))
        {
            m_iStatusMaxCountRet = atoi(xmlBase.GetData().c_str());
        }
        if (xmlBase.FindElem("TaskDataList") && xmlBase.IntoElem())
        {
            do
            {
                if (xmlBase.FindElem("TaskData") && xmlBase.IntoElem())
                {

                    strTemp.Format("%d", iRowCount);
                    m_listSearchTask.InsertItem(iRowCount, strTemp);
                    if (xmlBase.FindElem("fileIndex"))
                    {
                        m_listSearchTask.SetItemText(iRowCount, 1, xmlBase.GetData().c_str());
                    }
                    if (xmlBase.FindElem("taskID"))
                    {
                        m_listSearchTask.SetItemText(iRowCount, 2, xmlBase.GetData().c_str());
                    }
                    if (xmlBase.FindElem("url"))
                    {
                        m_listSearchTask.SetItemText(iRowCount, 3, xmlBase.GetData().c_str());
                    }
                    if (xmlBase.FindElem("backupStatus"))
                    {
                        if (xmlBase.GetData().compare("noBackup") == 0)
                        {
                            g_StringLanType(szLan, "未备份", "No backup");
                        }
                        else if (xmlBase.GetData().compare("backup") == 0)
                        {
                            g_StringLanType(szLan, "备份中", "Backup");
                        }
                        else if (xmlBase.GetData().compare("completeBackup") == 0)
                        {
                            g_StringLanType(szLan, "完成备份", "Complete backup");
                        }
                        else if (xmlBase.GetData().compare("backupFail") == 0)
                        {
                            g_StringLanType(szLan, "备份失败", "Backup fail");
                        }
                        m_listSearchTask.SetItemText(iRowCount, 4, szLan);
                    }
                    if (xmlBase.FindElem("backupMachineUrl"))
                    {
                        m_listSearchTask.SetItemText(iRowCount, 5, xmlBase.GetData().c_str());
                    }
                    xmlBase.OutOfElem();
                }
            } while (xmlBase.NextSibElem());
            xmlBase.OutOfElem();
        } 
        xmlBase.OutOfElem();
    }

    if (pOutBuf != NULL)
    {
        delete[]pOutBuf;
        pOutBuf = NULL;
    }

    if (pBuf != NULL)
    {
        delete[]pBuf;
        pBuf = NULL;
    }

    UpdateData(FALSE);
}

void CDlgCVRRemoteBackup::OnBnClickedButtonDelete()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    char szUrl[256] = { 0 };

    if (m_comboDeleteType.GetCurSel() == 0)
    {
        sprintf(szUrl, "DELETE /ISAPI/ContentMgmt/RemoteBackup/deleteTasks/%s\r\n", m_strDeleteTaskID);
    }
    else if (m_comboDeleteType.GetCurSel() == 1)
    {
        sprintf(szUrl, "DELETE /ISAPI/ContentMgmt/RemoteBackup/deleteTasks\r\n");
    }

    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    UpdateData(FALSE);
}



void CDlgCVRRemoteBackup::OnBnClickedButtonClearList()
{
    // TODO:  在此添加控件通知处理程序代码

    m_listSearchTask.DeleteAllItems();
}
