// DlgFacelibSearch.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgFacelibSearch.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgFacelibSearch 对话框

IMPLEMENT_DYNAMIC(CDlgFacelibSearch, CDialogEx)

#define WM_MSG_UPDATEDATA_INTERFACE   1003

CDlgFacelibSearch::CDlgFacelibSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgFacelibSearch::IDD, pParent)
    , m_strFilePath(_T(""))
    , m_strPicturePath(_T(""))
    , m_strModeData(_T(""))
    , m_lUserID(-1)
    , m_iDeviceIndex(-1)
    , m_ctDateStart(COleDateTime::GetCurrentTime())
    , m_ctDateEnd(COleDateTime::GetCurrentTime())
    , m_strSearchID(_T(""))
    , m_iMaxCountRet(0)
    , m_iCountStartRet(0)
    , m_strSearchResult(_T(""))
    , m_strSearchStatus(_T(""))
    , m_iCountResult(0)
    , m_bRegerateID(FALSE)
    , m_iStatusMaxCountRet(0)
    , m_bSearch(FALSE)
    , m_hSearchThread(NULL)
    , m_strSimilarity(_T(""))
    , m_bFDID(FALSE)
    , m_strCertificateNumber(_T(""))
    , m_strCity(_T(""))
    , m_strFDID(_T(""))
    , m_strName(_T(""))
    , m_strPhoneNumber(_T(""))
    , m_strProvince(_T(""))
    , m_iRecvTimeOut(5000)
    , m_bBirthTime(FALSE)
{

}

CDlgFacelibSearch::~CDlgFacelibSearch()
{
}

void CDlgFacelibSearch::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_PICTURE_PATH, m_strPicturePath);
    DDX_Text(pDX, IDC_EDIT_MODE_DATA, m_strModeData);
    DDX_Text(pDX, IDC_EDT_SEARCH_ID, m_strSearchID);
    DDX_Text(pDX, IDC_EDT_MAX_COUNT_RET, m_iMaxCountRet);
    DDX_Text(pDX, IDC_EDT_NUM_BEGIN_RET, m_iCountStartRet);
    DDX_Text(pDX, IDC_EDIT_SEARCH_RET, m_strSearchResult);
    DDX_Text(pDX, IDC_EDIT_SEARCH_STATUS, m_strSearchStatus);
    DDX_Text(pDX, IDC_STA_COUNT_RET, m_iCountResult);
    DDX_Check(pDX, IDC_CHECK_REGERATE_ID, m_bRegerateID);
    DDX_Text(pDX, IDC_STA_MAX_COUNT_RET, m_iStatusMaxCountRet);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATE_START, m_ctDateStart);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATE_END, m_ctDateEnd);
    DDX_Control(pDX, IDC_COMBO_SEARCH_TYPE, m_comboSearchType);
    DDX_Text(pDX, IDC_EDIT_SIMILARITY, m_strSimilarity);
    DDX_Control(pDX, IDC_LIST_SEARCH_RESULT, m_listSearchResult);
    DDX_Check(pDX, IDC_CHECK_FDID, m_bFDID);
    DDX_Control(pDX, IDC_COMBO_CERIFICATE_TYPE, m_comboCertficateType);
    DDX_Control(pDX, IDC_COMBO_MODEL_STATUS, m_comboModelStatus);
    DDX_Control(pDX, IDC_COMBO_SEX, m_comboSex);
    DDX_Text(pDX, IDC_EDIT_CERTIFICATE_NUMBER, m_strCertificateNumber);
    DDX_Text(pDX, IDC_EDIT_CITY, m_strCity);
    DDX_Text(pDX, IDC_EDIT_FDID, m_strFDID);
    DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
    DDX_Text(pDX, IDC_EDIT_PHONE_NUMBER, m_strPhoneNumber);
    DDX_Text(pDX, IDC_EDIT_PROVINCE, m_strProvince);
    DDX_Text(pDX, IDC_EDIT_RECV_TIME_OUT, m_iRecvTimeOut);
    DDX_Check(pDX, IDC_CHECK_BIRTH_TIME, m_bBirthTime);
}


BEGIN_MESSAGE_MAP(CDlgFacelibSearch, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CDlgFacelibSearch::OnBnClickedButtonBrowse)
    ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CDlgFacelibSearch::OnBnClickedButtonImport)
    ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgFacelibSearch::OnBnClickedButtonSearch)
    ON_MESSAGE(WM_MSG_UPDATEDATA_INTERFACE, OnMsgUpdateData)
    ON_NOTIFY(NM_CLICK, IDC_LIST_SEARCH_RESULT, &CDlgFacelibSearch::OnNMClickListSearchResult)
END_MESSAGE_MAP()


// CDlgFacelibSearch 消息处理程序
BOOL CDlgFacelibSearch::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化

    char szLan[128] = { 0 };

    m_listSearchResult.SetExtendedStyle(m_listSearchResult.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);

    char szGUID[MAX_XML_ELEM_LEN] = { 0 };
    if (!GenerateGUID(szGUID, MAX_XML_ELEM_LEN))
    {
        MessageBox("生成UUID失败!");
        return TRUE;
    }

    m_strSearchID = szGUID;

    m_comboSearchType.SetCurSel(0);
    m_comboCertficateType.SetCurSel(0);
    m_comboSex.SetCurSel(0);
    m_comboModelStatus.SetCurSel(0);

    m_ctDateStart.SetDate(1800, 1, 1);

    m_iMaxCountRet = 50;
    m_bRegerateID = TRUE;
    m_strSimilarity = "2";

    int iIndex = 0;

    m_listSearchResult.DeleteAllItems();

    g_StringLanType(szLan, "ID", "ID");
    m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
    iIndex++;

    g_StringLanType(szLan, "FDID", "FDID");
    m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 120, -1);
    iIndex++;

    g_StringLanType(szLan, "检测阈值", "thresholdValue");
    m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
    iIndex++;

    g_StringLanType(szLan, "出生日期", "bornTime");
    m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
    iIndex++;

    g_StringLanType(szLan, "姓名", "name");
    m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
    iIndex++;

    g_StringLanType(szLan, "性别", "sex");
    m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
    iIndex++;

    g_StringLanType(szLan, "省份", "province");
    m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
    iIndex++;

    g_StringLanType(szLan, "城市", "city");
    m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
    iIndex++;

    g_StringLanType(szLan, "证件类型", "certificateType");
    m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
    iIndex++;

    g_StringLanType(szLan, "证件号", "certificateNumber");
    m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
    iIndex++;

    g_StringLanType(szLan, "图片URL", "picURL");
    m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 120, -1);
    iIndex++;

    g_StringLanType(szLan, "PID", "PID");
    m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 120, -1);
    iIndex++;

    g_StringLanType(szLan, "人员扩展信息", "PersonInfoExtendList");
    m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 120, -1);
    iIndex++;

    g_StringLanType(szLan, "电话号码", "phoneNumber");
    m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
    iIndex++;

    g_StringLanType(szLan, "建模状态", "modelStatus");
    m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
    iIndex++;

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}

LRESULT CDlgFacelibSearch::OnMsgUpdateData(WPARAM wParam, LPARAM lParam)
{
    DWORD dwTrue = (DWORD)wParam;
    UpdateData(dwTrue);
    return 0;
}

void CDlgFacelibSearch::OnBnClickedButtonBrowse()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    char szLan[1024] = { 0 };
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_strFilePath = dlg.GetPathName();
        SetDlgItemText(IDC_EDIT_PICTURE_PATH, m_strFilePath);
    }
}


void CDlgFacelibSearch::OnBnClickedButtonImport()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    BYTE *pPicInfo = NULL;
    char szLan[128] = { 0 };

    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    char szUrl[256] = { 0 };
    sprintf(szUrl, "POST /ISAPI/Intelligent/analysisImage/face\r\n");

    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);

    CFile cPicFile;
    if (!cPicFile.Open(m_strFilePath, CFile::modeRead))
    {
        g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
        AfxMessageBox(szLan);
    }
    else
    {
        struInput.dwInBufferSize = (DWORD)cPicFile.GetLength();
        if (struInput.dwInBufferSize == 0)
        {
            g_StringLanType(szLan, "Pic文件为空", "Pic file is empty");
            AfxMessageBox(szLan);
        }

        pPicInfo = new BYTE[struInput.dwInBufferSize];
        cPicFile.Read(pPicInfo, struInput.dwInBufferSize);
        struInput.lpInBuffer = pPicInfo;

        cPicFile.Close();
    }
    struInput.dwRecvTimeOut = m_iRecvTimeOut;
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
    if (xmlBase.FindElem("FaceContrastTargetsList") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("FaceContrastTarget") && xmlBase.IntoElem())
        {
            if (xmlBase.FindElem("modeData"))
            {
                m_strModeData = xmlBase.GetData().c_str();
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

    if (pPicInfo != NULL)
    {
        delete[]pPicInfo;
        pPicInfo = NULL;
    }

    UpdateData(FALSE);
}

DWORD  GetSearchFacelibDataThread(LPVOID pParam)
{
    CDlgFacelibSearch *pThis = (CDlgFacelibSearch*)pParam;
    CString strTemp = _T("");
    long t1 = GetTickCount();
    while (pThis->m_bSearch)
    {
        pThis->SearchData();
    }
    long t2 = GetTickCount();
    strTemp.Format("%ld ms", t2 - t1);
    pThis->GetDlgItem(IDC_EDIT_SEARCH_TIME)->SetWindowText(strTemp);
    pThis->GetDlgItem(IDC_EDT_NUM_BEGIN_RET)->SetWindowText("0");
    return FALSE;
}

void CDlgFacelibSearch::SearchData()
{
    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;

    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    char szUrl[256] = { 0 };

    if (!CreateSearchFacelibCondition(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }
    sprintf(szUrl, "POST /ISAPI/Intelligent/FDLib/FDSearch\r\n");

    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    struInput.lpInBuffer = pBuf;
    struInput.dwInBufferSize = dwXmlLen;
    struInput.dwRecvTimeOut = m_iRecvTimeOut;
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
        m_strSearchResult = _T("");
        m_strSearchStatus = _T("");
        m_iCountResult = 0;
        m_iStatusMaxCountRet = 50;
        m_bSearch = FALSE;
        GetDlgItem(IDC_BUTTON_SEARCH)->SetWindowText("查找");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    BOOL bRet = FALSE;
    CXmlBase xmlBase;
    xmlBase.Parse(pOutBuf);

    GetFacelibSearchResult(xmlBase);

    if (m_strSearchResult == "false" || (m_strSearchResult == "true" && m_strSearchStatus != "MORE"))
    {
        m_bSearch = FALSE;
        GetDlgItem(IDC_BUTTON_SEARCH)->SetWindowText("查找");
    }
    PostMessage(WM_MSG_UPDATEDATA_INTERFACE, (WPARAM)FALSE, 0);

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
}

void CDlgFacelibSearch::OnBnClickedButtonSearch()
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
    if (!m_bSearch)
    {
        m_bSearch = TRUE;
        GetDlgItem(IDC_BUTTON_SEARCH)->SetWindowText("停止");
    }
    else
    {
        m_bSearch = FALSE;
        GetDlgItem(IDC_BUTTON_SEARCH)->SetWindowText("查找");
        return;
    }
    m_listSearchResult.DeleteAllItems();

    DWORD dwThreadId = 0;
    m_hSearchThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetSearchFacelibDataThread), this, 0, &dwThreadId);
    if (m_hSearchThread == NULL)
    {
        char szLan[256] = { 0 };
        m_bSearch = FALSE;
        GetDlgItem(IDC_BUTTON_SEARCH)->SetWindowText("查找");
        g_StringLanType(szLan, "打开长传文件线程失败!", "open UpLoad thread Fail!");
        AfxMessageBox(szLan);
        return;
    }

    UpdateData(FALSE);
}

BOOL CDlgFacelibSearch::CreateSearchFacelibCondition(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CString strParam = _T("");
    CXmlBase xmlBase;
    xmlBase.CreateRoot("FDSearchDescription");
    xmlBase.SetAttribute("version", "2.0");

    xmlBase.AddNode("searchID", m_strSearchID.GetBuffer(0));
    xmlBase.OutOfElem();

    strParam.Format("%d", m_iCountStartRet);
    xmlBase.AddNode("searchResultPosition", strParam.GetBuffer(0));
    xmlBase.OutOfElem();
    m_iCountStartRet += m_iMaxCountRet;//循环查找

    strParam.Format("%d", m_iMaxCountRet);
    xmlBase.AddNode("maxResults", strParam.GetBuffer(0));
    xmlBase.OutOfElem();

    if (m_bFDID)
    {
        xmlBase.AddNode("FDID", m_strFDID.GetBuffer(0));
        xmlBase.OutOfElem();
    }

    if (m_comboSearchType.GetCurSel() == 0)
    {
        if (m_bBirthTime)
        {
            strParam.Format("%04d-%02d-%02d", m_ctDateStart.GetYear(), m_ctDateStart.GetMonth(),
                m_ctDateStart.GetDay());

            xmlBase.AddNode("startTime", strParam.GetBuffer(0));
            xmlBase.OutOfElem();

            strParam.Format("%04d-%02d-%02d", m_ctDateEnd.GetYear(), m_ctDateEnd.GetMonth(),
                m_ctDateEnd.GetDay());

            xmlBase.AddNode("endTime", strParam.GetBuffer(0));
            xmlBase.OutOfElem();
        }

        if (m_strName != _T(""))
        {
            xmlBase.AddNode("name", m_strName.GetBuffer(0));
            xmlBase.OutOfElem();
        }

        if (m_comboSex.GetCurSel() == 1)
        {
            xmlBase.AddNode("sex", "male");
            xmlBase.OutOfElem();
        }
        else if (m_comboSex.GetCurSel() == 2)
        {
            xmlBase.AddNode("sex", "famale");
            xmlBase.OutOfElem();
        }

        if (m_strProvince != _T(""))
        {
            xmlBase.AddNode("province", m_strProvince.GetBuffer(0));
            xmlBase.OutOfElem();
        }

        if (m_strCity != _T(""))
        {
            xmlBase.AddNode("city", m_strCity.GetBuffer(0));
            xmlBase.OutOfElem();
        }

        if (m_comboCertficateType.GetCurSel() == 1)
        {
            xmlBase.AddNode("certificateType", "officerID");
            xmlBase.OutOfElem();
        }
        else if (m_comboCertficateType.GetCurSel() == 2)
        {
            xmlBase.AddNode("certificateType", "ID");
            xmlBase.OutOfElem();
        }
        else if (m_comboCertficateType.GetCurSel() == 3)
        {
            xmlBase.AddNode("certificateType", "passportID");
            xmlBase.OutOfElem();
        }
        else if (m_comboCertficateType.GetCurSel() == 4)
        {
            xmlBase.AddNode("certificateType", "other");
            xmlBase.OutOfElem();
        }

        if (m_comboCertficateType.GetCurSel() > 0)
        {
            xmlBase.AddNode("certificateNumber", m_strCertificateNumber.GetBuffer(0));
            xmlBase.OutOfElem();
        }

        if (m_strPhoneNumber != _T(""))
        {
            xmlBase.AddNode("phoneNumber", m_strPhoneNumber.GetBuffer(0));
            xmlBase.OutOfElem();
        }

        if (m_comboModelStatus.GetCurSel() == 1)
        {
            xmlBase.AddNode("modelStatus", "modeling");
            xmlBase.OutOfElem();
        }
        else if (m_comboModelStatus.GetCurSel() == 2)
        {
            xmlBase.AddNode("modelStatus", "unmodeled");
            xmlBase.OutOfElem();
        }
        else if (m_comboModelStatus.GetCurSel() == 3)
        {
            xmlBase.AddNode("modelStatus", "modelingFailed");
            xmlBase.OutOfElem();
        }
    }
    else if (m_comboSearchType.GetCurSel() == 1)
    {
        if (xmlBase.AddNode("FaceModeList"))
        {
            if (xmlBase.AddNode("FaceMode"))
            {
                if (xmlBase.AddNode("ModeInfo"))
                {
                    xmlBase.AddNode("similarity", m_strSimilarity.GetBuffer(0));
                    xmlBase.OutOfElem();

                    xmlBase.AddNode("modeData", m_strModeData.GetBuffer(0));
                    xmlBase.OutOfElem();

                    xmlBase.OutOfElem();
                }
                xmlBase.OutOfElem();
            }
            xmlBase.OutOfElem();
        }
    }

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

void CDlgFacelibSearch::GetFacelibSearchResult(CXmlBase xmlBase)
{
    if (xmlBase.FindElem("FDSearchResult") && xmlBase.IntoElem())
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

        if (xmlBase.FindElem("MatchList") && xmlBase.IntoElem())
        {
            do
            {
                if (xmlBase.FindElem("MatchElement") && xmlBase.IntoElem())
                {
                    int iRowCount = m_listSearchResult.GetItemCount();
                    CString strTemp = _T("");
                    strTemp.Format("%d", iRowCount);
                    m_listSearchResult.InsertItem(iRowCount, strTemp);

                    int iIndex = 1;

                    if (xmlBase.FindElem("FDID"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("thresholdValue"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("bornTime"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("name"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("sex"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("province"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("city"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("certificateType"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("certificateNumber"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("picURL"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("PID"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("PersonInfoExtendList"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetChildren().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("phoneNumber"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("modelStatus"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    xmlBase.OutOfElem();
                }
            } while (xmlBase.NextSibElem());

            xmlBase.OutOfElem();
        }

        xmlBase.OutOfElem();
    }
}


void CDlgFacelibSearch::OnNMClickListSearchResult(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO:  在此添加控件通知处理程序代码
    int iSelectItem = pNMItemActivate->iItem;
    int iSelectSubItem = pNMItemActivate->iSubItem;

    CString csTxt;
    csTxt.Format("%s", m_listSearchResult.GetItemText(iSelectItem, iSelectSubItem));
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

    UpdateData(FALSE);

    *pResult = 0;
}
