// DlgSuperBrainFunctionTest.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgSuperBrainFunctionTest.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgSuperBrainFunctionTest 对话框

IMPLEMENT_DYNAMIC(CDlgSuperBrainFunctionTest, CDialogEx)

#define WM_MSG_UPDATEDATA_INTERFACE   1003

const char *szAgeGroup[] = { "unknown", "child", "young", "middle", "old", "infant", "kid", "teenager" };
const char *szBasic[] = { "unknown", "no", "yes"};
const char *szJacketColor[] = { "unknown", "white", "silver", "gray", "black", "deepBlue", "blue", "yellow", "green", "brown", "pink", "purple", "deepGray", "cyan", "orange", "mixture" };
const char *szVehicleColor[] = { "unknown", "white", "silver", "gray", "black", "deepBlue", "blue", "yellow", "green", "brown", "pink", "purple", "deepGray", "cyan", "orange" };
const char *szVehicleType[] = { "unknown", "largeBus", "truck", "vehicle", "van", "buggy", "pedestrian", "twoWheelVehicle", "threeWheelVehicle", "SUVMPV", "mediumBus", "motorVehicle", "nonmotorVehicle", "smallCar", "miniCar", "pickupTruck" };

CDlgSuperBrainFunctionTest::CDlgSuperBrainFunctionTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSuperBrainFunctionTest::IDD, pParent)
    , m_strFilePath(_T(""))
    , m_strPicturePath(_T(""))
    , m_strModeData(_T(""))
    , m_lUserID(-1)
    , m_iDeviceIndex(-1)
    , m_ctDateStart(COleDateTime::GetCurrentTime())
    , m_ctTimeStart(COleDateTime::GetCurrentTime())
    , m_ctDateEnd(COleDateTime::GetCurrentTime())
    , m_ctTimeEnd(COleDateTime::GetCurrentTime())
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
    , m_lChannel(-1)
    , m_strSimilarity(_T(""))
    , m_bMutiChannel(FALSE)
    , m_bLimitSearchChannel(FALSE)
    , m_strFDIDFace(_T(""))
    , m_strLisencePlateVehicle(_T(""))
    , m_strLogVehicle(_T(""))
    , m_strModelVehicle(_T(""))
    , m_strPIDFace(_T(""))
    , m_strSubLogoVehicle(_T(""))
    , m_iTotalSearchResult(0)
    , m_strSimilarityFace(_T("2"))
    , m_iRecvTimeOut(5000)
{
    m_iRowCount = 0;
    m_bSelectItem = FALSE;
    m_iSubItem = -1;
    m_iLastItem = -1;
}

CDlgSuperBrainFunctionTest::~CDlgSuperBrainFunctionTest()
{
}

void CDlgSuperBrainFunctionTest::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_PICTURE_PATH, m_strPicturePath);
    DDX_Text(pDX, IDC_EDIT_MODE_DATA, m_strModeData);
    DDX_Control(pDX, IDC_COMBO_IMPORT_TYPE, m_comboImportType);
    DDX_Text(pDX, IDC_EDT_SEARCH_ID, m_strSearchID);
    DDX_Text(pDX, IDC_EDT_MAX_COUNT_RET, m_iMaxCountRet);
    DDX_Text(pDX, IDC_EDT_NUM_BEGIN_RET, m_iCountStartRet);
    DDX_Text(pDX, IDC_EDIT_SEARCH_RET, m_strSearchResult);
    DDX_Text(pDX, IDC_EDIT_SEARCH_STATUS, m_strSearchStatus);
    DDX_Text(pDX, IDC_STA_COUNT_RET, m_iCountResult);
    DDX_Check(pDX, IDC_CHECK_REGERATE_ID, m_bRegerateID);
    DDX_Text(pDX, IDC_STA_MAX_COUNT_RET, m_iStatusMaxCountRet);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATE_START, m_ctDateStart);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TIME_START, m_ctTimeStart);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATE_END, m_ctDateEnd);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TIME_END, m_ctTimeEnd);
    DDX_Control(pDX, IDC_COMBO_SEARCH_TYPE, m_comboSearchType);
    DDX_Control(pDX, IDC_LIST_MODE_DATA, m_listModeData);
    DDX_Text(pDX, IDC_EDIT_SIMILARITY, m_strSimilarity);
    DDX_Check(pDX, IDC_CHECK_MUTI_CHANNEL, m_bMutiChannel);
    DDX_Control(pDX, IDC_LIST_CHAN, m_listChan);
    DDX_Check(pDX, IDC_CHECK_LIMIT_SEARCH_RESULT, m_bLimitSearchChannel);
    DDX_Control(pDX, IDC_COMBO_AGE_GROUP_HUMAN, m_comboAgeGroupHuman);
    DDX_Control(pDX, IDC_COMBO_BAG_HUMAN, m_comboBagHuman);
    DDX_Control(pDX, IDC_COMBO_EVENT_TYPE_FACE, m_comboEventTypeFace);
    DDX_Control(pDX, IDC_COMBO_EVENT_TYPE_HUMAN, m_comboEventTypeHuman);
    DDX_Control(pDX, IDC_COMBO_EVENT_TYPE_VEHICLE, m_comboEventTypeVehicle);
    DDX_Control(pDX, IDC_COMBO_GENDER_HUMAN, m_comboGenderHuman);
    DDX_Control(pDX, IDC_COMBO_GLASS_HUMAN, m_comboGlassHuman);
    DDX_Control(pDX, IDC_COMBO_JACKET_COLOR_HUMAN, m_comboJacketColorHuman);
    DDX_Control(pDX, IDC_COMBO_RIDE_HUMAN, m_comboRideHuman);
    DDX_Control(pDX, IDC_COMBO_SEARCH_TYPE_HUMAN, m_comboSearchTypeHuman);
    DDX_Control(pDX, IDC_COMBO_COLOR_VEHICLE, m_comboColorVehicle);
    DDX_Control(pDX, IDC_COMBO_SEARCH_TYPE_FACE, m_comboSearchTypeFace);
    DDX_Control(pDX, IDC_COMBO_TYPE_VEHICLE, m_comboTypeVehicle);
    DDX_Text(pDX, IDC_EDIT_FDID_FACE, m_strFDIDFace);
    DDX_Text(pDX, IDC_EDIT_LICENSE_PLATE_VEHICLE, m_strLisencePlateVehicle);
    DDX_Text(pDX, IDC_EDIT_LOG_VEHICLE, m_strLogVehicle);
    DDX_Text(pDX, IDC_EDIT_MODEL_VEHICLE, m_strModelVehicle);
    DDX_Text(pDX, IDC_EDIT_PID_FACE, m_strPIDFace);
    DDX_Text(pDX, IDC_EDIT_SUB_LOGO_VEHICLE, m_strSubLogoVehicle);
    DDX_Text(pDX, IDC_EDIT_TOTAL_SEARCH_RESULT, m_iTotalSearchResult);
    DDX_Control(pDX, IDC_LIST_SEARCH_RESULT, m_listSearchResult);
    DDX_Text(pDX, IDC_EDIT_SIMILARITY_FACE, m_strSimilarityFace);
    DDX_Text(pDX, IDC_EDIT_RECV_TIME_OUT, m_iRecvTimeOut);
}


BEGIN_MESSAGE_MAP(CDlgSuperBrainFunctionTest, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CDlgSuperBrainFunctionTest::OnBnClickedButtonBrowse)
    ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CDlgSuperBrainFunctionTest::OnBnClickedButtonImport)
    ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgSuperBrainFunctionTest::OnBnClickedButtonSearch)
    ON_BN_CLICKED(IDC_BUTTON_ADD_LIST, &CDlgSuperBrainFunctionTest::OnBnClickedButtonAddList)
    ON_BN_CLICKED(IDC_BUTTON_DELETE_LIST, &CDlgSuperBrainFunctionTest::OnBnClickedButtonDeleteList)
    ON_NOTIFY(NM_CLICK, IDC_LIST_MODE_DATA, &CDlgSuperBrainFunctionTest::OnNMClickListModeData)
    ON_MESSAGE(WM_MSG_UPDATEDATA_INTERFACE, OnMsgUpdateData)
    ON_BN_CLICKED(IDC_BUTTON_FACE_SEARCH_EXPORT, &CDlgSuperBrainFunctionTest::OnBnClickedButtonFaceSearchExport)
    ON_NOTIFY(NM_CLICK, IDC_LIST_CHAN, &CDlgSuperBrainFunctionTest::OnNMClickListChan)
    ON_CBN_SELCHANGE(IDC_COMBO_SEARCH_TYPE, &CDlgSuperBrainFunctionTest::OnCbnSelchangeComboSearchType)
    ON_NOTIFY(NM_CLICK, IDC_LIST_SEARCH_RESULT, &CDlgSuperBrainFunctionTest::OnNMClickListSearchResult)
END_MESSAGE_MAP()


// CDlgSuperBrainFunctionTest 消息处理程序

BOOL CDlgSuperBrainFunctionTest::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化

    char szLan[128] = { 0 };

    m_listSearchResult.SetExtendedStyle(m_listSearchResult.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);
    m_listModeData.SetExtendedStyle(m_listModeData.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);

    g_StringLanType(szLan, "序号", "Index");
    m_listModeData.InsertColumn(0, szLan, LVCFMT_LEFT, 60, -1);

    g_StringLanType(szLan, "建模数据", "Mode data");
    m_listModeData.InsertColumn(1, szLan, LVCFMT_LEFT, 120, -1);

    char szGUID[MAX_XML_ELEM_LEN] = { 0 };
    if (!GenerateGUID(szGUID, MAX_XML_ELEM_LEN))
    {
        MessageBox("生成UUID失败!");
        return TRUE;
    }

    m_strSearchID = szGUID;

    m_comboImportType.SetCurSel(0);
    m_comboSearchType.SetCurSel(0);

    m_ctTimeStart.SetTime(0, 0, 0);
    m_ctTimeEnd.SetTime(23, 59, 59);

    m_iMaxCountRet = 50;
    m_bRegerateID = TRUE;
    m_strSimilarity = "2";

    m_listChan.SetExtendedStyle(m_listChan.GetExtendedStyle() | LVS_EX_CHECKBOXES);

    m_comboSearchTypeHuman.SetCurSel(0);
    m_comboSearchTypeFace.SetCurSel(0);

    m_comboEventTypeHuman.SetCurSel(0);
    m_comboEventTypeFace.SetCurSel(0);
    m_comboEventTypeVehicle.SetCurSel(0);

    m_comboAgeGroupHuman.SetCurSel(0);
    m_comboGenderHuman.SetCurSel(0);
    m_comboJacketColorHuman.SetCurSel(0);
    m_comboBagHuman.SetCurSel(0);
    m_comboRideHuman.SetCurSel(0);
    m_comboGlassHuman.SetCurSel(0);

    m_comboColorVehicle.SetCurSel(0);
    m_comboTypeVehicle.SetCurSel(0);

    UpdateChanStatus();
    UpadateSearchResultList();

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}

LRESULT CDlgSuperBrainFunctionTest::OnMsgUpdateData(WPARAM wParam, LPARAM lParam)
{
    DWORD dwTrue = (DWORD)wParam;
    UpdateData(dwTrue);
    return 0;
}

void CDlgSuperBrainFunctionTest::OnBnClickedButtonBrowse()
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


void CDlgSuperBrainFunctionTest::OnBnClickedButtonImport()
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
    if (m_comboImportType.GetCurSel() == 0)
    {
        sprintf(szUrl, "POST /ISAPI/Intelligent/analysisImage/human\r\n");
    } 
    else if(m_comboImportType.GetCurSel() == 1)
    {
        sprintf(szUrl, "POST /ISAPI/Intelligent/analysisImage/face\r\n");
    }

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
    if (m_comboImportType.GetCurSel() == 0)
    {
        if (xmlBase.FindElem("HumanRecognitionTargetsList") && xmlBase.IntoElem())
        {
            if (xmlBase.FindElem("HumanRecognitionTarget") && xmlBase.IntoElem())
            {
                if (xmlBase.FindElem("modeData"))
                {
                    m_strModeData = xmlBase.GetData().c_str();
                }
                xmlBase.OutOfElem();
            }
            xmlBase.OutOfElem();
        }
    }
    else if (m_comboImportType.GetCurSel() == 1)
    {
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

BOOL CDlgSuperBrainFunctionTest::CreateSearchHumanCondition(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CString strParam = _T("");
    CXmlBase xmlBase;
    xmlBase.CreateRoot("HumanRecognitionSearchDescription");
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

    if (xmlBase.AddNode("timeSpanList"))
    {
        if (xmlBase.AddNode("timeSpan"))
        {
            strParam.Format("%04d-%02d-%02dT%02d:%02d:%02d", m_ctDateStart.GetYear(), m_ctDateStart.GetMonth(),
                m_ctDateStart.GetDay(), m_ctTimeStart.GetHour(), m_ctTimeStart.GetMinute(), m_ctTimeStart.GetSecond());

            xmlBase.AddNode("startTime", strParam.GetBuffer(0));
            xmlBase.OutOfElem();

            strParam.Format("%04d-%02d-%02dT%02d:%02d:%02d", m_ctDateEnd.GetYear(), m_ctDateEnd.GetMonth(),
                m_ctDateEnd.GetDay(), m_ctTimeEnd.GetHour(), m_ctTimeEnd.GetMinute(), m_ctTimeEnd.GetSecond());

            xmlBase.AddNode("endTime", strParam.GetBuffer(0));
            xmlBase.OutOfElem();

            xmlBase.OutOfElem();
        }
        xmlBase.OutOfElem();
    }

    if (m_comboEventTypeHuman.GetCurSel() == 2)
    {
        xmlBase.AddNode("positive", "true");
        xmlBase.OutOfElem();
    }
    else
    {
        xmlBase.AddNode("positive", "false");
        xmlBase.OutOfElem();
    }

    if (m_comboSearchTypeHuman.GetCurSel() == 0)
    {
        xmlBase.AddNode("HumanModeList");

        if (xmlBase.AddNode("HumanMode"))
        {
            if (xmlBase.AddNode("HumanInfo"))
            {
                xmlBase.AddNode("age_group", szAgeGroup[m_comboAgeGroupHuman.GetCurSel()]);
                xmlBase.OutOfElem();

                xmlBase.AddNode("gender", szBasic[m_comboGenderHuman.GetCurSel()]);
                xmlBase.OutOfElem();

                xmlBase.AddNode("jacet_color", szJacketColor[m_comboJacketColorHuman.GetCurSel()]);
                xmlBase.OutOfElem();

                xmlBase.AddNode("glass", szBasic[m_comboGlassHuman.GetCurSel()]);
                xmlBase.OutOfElem();

                xmlBase.AddNode("bag", szBasic[m_comboBagHuman.GetCurSel()]);
                xmlBase.OutOfElem();

                xmlBase.AddNode("ride", szBasic[m_comboRideHuman.GetCurSel()]);
                xmlBase.OutOfElem();

                xmlBase.OutOfElem();
            }

            xmlBase.OutOfElem();
        }

        xmlBase.OutOfElem();
    }
    else if (m_comboSearchTypeHuman.GetCurSel() == 1)
    {
        int iRowCount = m_listModeData.GetItemCount();
        if (iRowCount > 0)
        {
            xmlBase.AddNode("HumanModeList");

            for (int i = 0; i < iRowCount; i++)
            {
                if (xmlBase.AddNode("HumanMode"))
                {
                    if (xmlBase.AddNode("ModeInfo"))
                    {
                        xmlBase.AddNode("similarity", m_strSimilarity.GetBuffer(0));
                        xmlBase.OutOfElem();

                        xmlBase.AddNode("modeData", m_listModeData.GetItemText(i, 1).GetBuffer(0));
                        xmlBase.OutOfElem();

                        xmlBase.OutOfElem();
                    }
                    xmlBase.OutOfElem();
                }
            }

            xmlBase.OutOfElem();
        }
    }

    if (m_comboEventTypeHuman.GetCurSel() == 0)
    {
        xmlBase.AddNode("eventType", "unlimit");
        xmlBase.OutOfElem();
    }
    else if (m_comboEventTypeHuman.GetCurSel() == 1)
    {
        xmlBase.AddNode("eventType", "humanRecognition");
        xmlBase.OutOfElem();
    }

    if (m_bMutiChannel)
    {
        xmlBase.AddNode("ChannelList");

        for (int i = 0; i < m_listChan.GetItemCount(); i++)
        {
            if (m_listChan.GetCheck(i))
            {
                if (xmlBase.AddNode("Channel"))
                {
                    int iChannel = -1;
                    iChannel = NET_DVR_SDKChannelToISAPI(m_lUserID, m_listChan.GetItemData(i), TRUE);
                    strParam.Format("%d", iChannel);
                    xmlBase.AddNode("channelID", strParam.GetBuffer(0));
                    xmlBase.OutOfElem();

                    xmlBase.OutOfElem();
                }
            }
        }

        xmlBase.OutOfElem();
    }

    if (m_bLimitSearchChannel)
    {
        strParam.Format("%d", m_iTotalSearchResult);
        xmlBase.AddNode("totalSearchResults", strParam.GetBuffer(0));
        xmlBase.OutOfElem();
    }

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

BOOL CDlgSuperBrainFunctionTest::CreateSearchFaceCondition(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CString strParam = _T("");
    CXmlBase xmlBase;
    xmlBase.CreateRoot("FCSearchDescription");
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

    strParam.Format("%04d-%02d-%02dT%02d:%02d:%02d", m_ctDateStart.GetYear(), m_ctDateStart.GetMonth(), 
        m_ctDateStart.GetDay(), m_ctTimeStart.GetHour(), m_ctTimeStart.GetMinute(), m_ctTimeStart.GetSecond());

    xmlBase.AddNode("snapStartTime", strParam.GetBuffer(0));
    xmlBase.OutOfElem();

    strParam.Format("%04d-%02d-%02dT%02d:%02d:%02d", m_ctDateEnd.GetYear(), m_ctDateEnd.GetMonth(),
        m_ctDateEnd.GetDay(), m_ctTimeEnd.GetHour(), m_ctTimeEnd.GetMinute(), m_ctTimeEnd.GetSecond());

    xmlBase.AddNode("snapEndTime", strParam.GetBuffer(0));
    xmlBase.OutOfElem();

    if (m_comboSearchTypeFace.GetCurSel() == 0)
    {
        xmlBase.AddNode("similarity", m_strSimilarityFace.GetBuffer(0));
        xmlBase.OutOfElem();
    }

    if (m_comboEventTypeFace.GetCurSel() == 0)
    {
        xmlBase.AddNode("eventType", "unlimit");
        xmlBase.OutOfElem();
    }
    else if (m_comboEventTypeFace.GetCurSel() == 1)
    {
        xmlBase.AddNode("eventType", "faceContrast");
        xmlBase.OutOfElem();
    }
    else if (m_comboEventTypeFace.GetCurSel() == 2)
    {
        xmlBase.AddNode("eventType", "whiteFaceContrast");
        xmlBase.OutOfElem();
    }

    if (m_comboSearchTypeFace.GetCurSel() == 1)
    {
        int iRowCount = m_listModeData.GetItemCount();
        if (iRowCount > 0)
        {
            if (xmlBase.AddNode("FaceModeList"))
            {
                for (int i = 0; i < iRowCount; i++)
                {
                    if (xmlBase.AddNode("FaceMode"))
                    {
                        if (xmlBase.AddNode("ModeInfo"))
                        {
                            xmlBase.AddNode("similarity", m_strSimilarity.GetBuffer(0));
                            xmlBase.OutOfElem();

                            xmlBase.AddNode("modeData", m_listModeData.GetItemText(i, 1).GetBuffer(0));
                            xmlBase.OutOfElem();

                            xmlBase.OutOfElem();
                        }
                        xmlBase.OutOfElem();
                    }
                }
                xmlBase.OutOfElem();
            }
        }
    }
    else if (m_comboSearchTypeFace.GetCurSel() == 2)
    {
        if (xmlBase.AddNode("PictureInfoList"))
        {
            if (xmlBase.AddNode("PictureInfo"))
            {
                xmlBase.AddNode("FDID", m_strFDIDFace.GetBuffer(0));
                xmlBase.OutOfElem();

                xmlBase.AddNode("PID", m_strPIDFace.GetBuffer(0));
                xmlBase.OutOfElem();

                xmlBase.OutOfElem();
            }
            xmlBase.OutOfElem();
        }
    }

    if (m_bMutiChannel)
    {
        xmlBase.AddNode("ChannelList");

        for (int i = 0; i < m_listChan.GetItemCount(); i++)
        {
            if (m_listChan.GetCheck(i))
            {
                if (xmlBase.AddNode("Channel"))
                {
                    int iChannel = -1;
                    iChannel = NET_DVR_SDKChannelToISAPI(m_lUserID, m_listChan.GetItemData(i), TRUE);
                    strParam.Format("%d", iChannel);
                    xmlBase.AddNode("channelID", strParam.GetBuffer(0));
                    xmlBase.OutOfElem();

                    xmlBase.OutOfElem();
                }
            }
        }

        xmlBase.OutOfElem();
    }

    if (m_bLimitSearchChannel)
    {
        strParam.Format("%d", m_iTotalSearchResult);
        xmlBase.AddNode("totalSearchResults", strParam.GetBuffer(0));
        xmlBase.OutOfElem();
    }

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

BOOL CDlgSuperBrainFunctionTest::CreateSearchVehicleCondition(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CString strParam = _T("");
    CXmlBase xmlBase;
    xmlBase.CreateRoot("VehicleRecognitionSearchDescription");
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

    if (xmlBase.AddNode("timeSpanList"))
    {
        if (xmlBase.AddNode("timeSpan"))
        {
            strParam.Format("%04d-%02d-%02dT%02d:%02d:%02d", m_ctDateStart.GetYear(), m_ctDateStart.GetMonth(),
                m_ctDateStart.GetDay(), m_ctTimeStart.GetHour(), m_ctTimeStart.GetMinute(), m_ctTimeStart.GetSecond());

            xmlBase.AddNode("startTime", strParam.GetBuffer(0));
            xmlBase.OutOfElem();

            strParam.Format("%04d-%02d-%02dT%02d:%02d:%02d", m_ctDateEnd.GetYear(), m_ctDateEnd.GetMonth(),
                m_ctDateEnd.GetDay(), m_ctTimeEnd.GetHour(), m_ctTimeEnd.GetMinute(), m_ctTimeEnd.GetSecond());

            xmlBase.AddNode("endTime", strParam.GetBuffer(0));
            xmlBase.OutOfElem();

            xmlBase.OutOfElem();
        }
        xmlBase.OutOfElem();
    }

    if (m_comboEventTypeVehicle.GetCurSel() == 0)
    {
        xmlBase.AddNode("eventType", "unlimit");
        xmlBase.OutOfElem();
    }
    else if (m_comboEventTypeVehicle.GetCurSel() == 1)
    {
        xmlBase.AddNode("eventType", "vehicleBlackList");
        xmlBase.OutOfElem();
    }
    else if (m_comboEventTypeVehicle.GetCurSel() == 2)
    {
        xmlBase.AddNode("eventType", "vehicleWhiteList");
        xmlBase.OutOfElem();
    }

    xmlBase.AddNode("VehicleModeList");

    if (xmlBase.AddNode("VehicleMode"))
    {
        if (xmlBase.AddNode("VehicleInfo"))
        {
            if (m_strLisencePlateVehicle != _T(""))
            {
                xmlBase.AddNode("licensePlate", m_strLisencePlateVehicle.GetBuffer(0));
                xmlBase.OutOfElem();
            }

            if (m_strLogVehicle != _T(""))
            {
                xmlBase.AddNode("vehicleLogoRecog", m_strLogVehicle.GetBuffer(0));
                xmlBase.OutOfElem();
            }

            if (m_strSubLogoVehicle != _T(""))
            {
                xmlBase.AddNode("vehicleSubLogoRecog", m_strSubLogoVehicle.GetBuffer(0));
                xmlBase.OutOfElem();
            }

            if (m_strModelVehicle != _T(""))
            {
                xmlBase.AddNode("vehicleModel", m_strModelVehicle.GetBuffer(0));
                xmlBase.OutOfElem();
            }

            xmlBase.AddNode("vehicleColor", szVehicleColor[m_comboColorVehicle.GetCurSel()]);
            xmlBase.OutOfElem();

            xmlBase.AddNode("vehicleType", szVehicleType[m_comboTypeVehicle.GetCurSel()]);
            xmlBase.OutOfElem();

            xmlBase.OutOfElem();
        }

        xmlBase.OutOfElem();
    }

    xmlBase.OutOfElem();

    if (m_bMutiChannel)
    {
        xmlBase.AddNode("ChannelList");

        for (int i = 0; i < m_listChan.GetItemCount(); i++)
        {
            if (m_listChan.GetCheck(i))
            {
                if (xmlBase.AddNode("Channel"))
                {
                    int iChannel = -1;
                    iChannel = NET_DVR_SDKChannelToISAPI(m_lUserID, m_listChan.GetItemData(i), TRUE);
                    strParam.Format("%d", iChannel);
                    xmlBase.AddNode("channelID", strParam.GetBuffer(0));
                    xmlBase.OutOfElem();

                    xmlBase.OutOfElem();
                }
            }
        }

        xmlBase.OutOfElem();
    }

    if (m_bLimitSearchChannel)
    {
        strParam.Format("%d", m_iTotalSearchResult);
        xmlBase.AddNode("totalSearchResults", strParam.GetBuffer(0));
        xmlBase.OutOfElem();
    }

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

DWORD  GetSearchDataThread(LPVOID pParam)
{
    CDlgSuperBrainFunctionTest *pThis = (CDlgSuperBrainFunctionTest*)pParam;
    pThis->GetDlgItem(IDC_COMBO_SEARCH_TYPE)->EnableWindow(FALSE);
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
    pThis->GetDlgItem(IDC_COMBO_SEARCH_TYPE)->EnableWindow(TRUE);
    return FALSE;
}

void CDlgSuperBrainFunctionTest::SearchData()
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

    if (m_comboSearchType.GetCurSel() == 0)
    {
        if (!CreateSearchHumanCondition(pBuf, dwBufLen, dwXmlLen))
        {
            delete[]pBuf;
            pBuf = NULL;
            return;
        }
        if (m_bMutiChannel)
        {
            sprintf(szUrl, "POST /ISAPI/Intelligent/humanRecognition/Search/channels\r\n");
        }
        else
        {
            sprintf(szUrl, "POST /ISAPI/Intelligent/humanRecognition/Search/channels/%d\r\n", m_lChannel);
        }
    }
    else if (m_comboSearchType.GetCurSel() == 1)
    {
        if (!CreateSearchFaceCondition(pBuf, dwBufLen, dwXmlLen))
        {
            delete[]pBuf;
            pBuf = NULL;
            return;
        }
        if (m_bMutiChannel)
        {
            sprintf(szUrl, "POST /ISAPI/Intelligent/FDLib/FCSearch\r\n");
        }
        else
        {
            sprintf(szUrl, "POST /ISAPI/Intelligent/FDLib/FCSearch/channels/%d\r\n", m_lChannel);
        }
    }
    else if (m_comboSearchType.GetCurSel() == 2)
    {
        if (!CreateSearchVehicleCondition(pBuf, dwBufLen, dwXmlLen))
        {
            delete[]pBuf;
            pBuf = NULL;
            return;
        }
        if (m_bMutiChannel)
        {
            sprintf(szUrl, "POST /ISAPI/Intelligent/vehicleRecognition/Search/channels\r\n");
        }
        else
        {
            sprintf(szUrl, "POST /ISAPI/Intelligent/vehicleRecognition/Search/channels/%d\r\n", m_lChannel);
        }
    }

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

    if (m_comboSearchType.GetCurSel() == 0)
    {
        GetHumanSearchResult(xmlBase);
    }
    else if (m_comboSearchType.GetCurSel() == 1)
    {
        GetFaceSearchResult(xmlBase);
    }
    else if (m_comboSearchType.GetCurSel() == 2)
    {
        GetVehicleSearchResult(xmlBase);
    }
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

void CDlgSuperBrainFunctionTest::OnBnClickedButtonSearch()
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
    UpadateSearchResultList();

    DWORD dwThreadId = 0;
    m_hSearchThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetSearchDataThread), this, 0, &dwThreadId);
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


void CDlgSuperBrainFunctionTest::OnBnClickedButtonAddList()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    int iRowCount = m_listModeData.GetItemCount();
    CString strTemp = _T("");
    strTemp.Format("%d", iRowCount);
    m_listModeData.InsertItem(iRowCount, strTemp);
    m_listModeData.SetItemText(iRowCount, 1, m_strModeData);
    UpdateData(FALSE);
}


void CDlgSuperBrainFunctionTest::OnBnClickedButtonDeleteList()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_iRowCount = m_listModeData.GetItemCount();
    if (m_iLastItem >= 0 && m_iLastItem < m_iRowCount)
    {
        m_listModeData.DeleteItem(m_iLastItem);
    }
    UpdateData(FALSE);
}


void CDlgSuperBrainFunctionTest::OnNMClickListModeData(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO:  在此添加控件通知处理程序代码
    m_iLastItem = pNMItemActivate->iItem;
    m_iSubItem = pNMItemActivate->iSubItem;
    m_bSelectItem = TRUE;

    *pResult = 0;
}

CString OpenBrowseFolder(HWND hWnd, LPCTSTR lpTitle)
{

    char szPath[MAX_PATH] = { 0 };
    BROWSEINFO m_bi;

    m_bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
    m_bi.hwndOwner = hWnd;
    m_bi.pidlRoot = NULL;
    m_bi.lpszTitle = lpTitle;
    m_bi.lpfn = NULL;
    m_bi.lParam = NULL;
    m_bi.pszDisplayName = szPath;

    LPITEMIDLIST pidl = ::SHBrowseForFolder(&m_bi);
    if (pidl)
    {
        if (!::SHGetPathFromIDList(pidl, szPath))
        {
            szPath[0] = 0;
        }

        IMalloc * pMalloc = NULL;
        if (SUCCEEDED(::SHGetMalloc(&pMalloc)))  // 取得IMalloc分配器接口
        {
            pMalloc->Free(pidl);    // 释放内存
            pMalloc->Release();       // 释放接口
        }
    }
    return szPath;
}

void CDlgSuperBrainFunctionTest::OnBnClickedButtonFaceSearchExport()
{
    // TODO:  在此添加控件通知处理程序代码

    UpdateData(TRUE);

    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;

    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    char szUrl[256] = { 0 };

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

    if (!CreateSearchFaceCondition(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }
    if (m_bMutiChannel)
    {
        sprintf(szUrl, "POST /ISAPI/Intelligent/FDLib/FCSearch/dataPackage\r\n");
    }
    else
    {
        sprintf(szUrl, "POST /ISAPI/Intelligent/FDLib/FCSearch/channels/%d/dataPackage\r\n", m_lChannel);
    }

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
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);

        UpdateData(TRUE);
        char szFile[MAX_PATH] = { 0 };
        CString strFilePath = _T("");
        strFilePath = OpenBrowseFolder(this->m_hWnd, "选择目录");
        if (strFilePath.IsEmpty())
        {
            MessageBox("保存文件路径不能为空");
        }
        else
        {
            CTime ctime = CTime::GetCurrentTime();

            sprintf(szFile, "%s\\%d_%d_%d_%d_%d_%d_%d_FaceSearchExport.xls", strFilePath, ctime.GetYear(),
                ctime.GetMonth(), ctime.GetDay(), ctime.GetHour(), ctime.GetMinute(), ctime.GetSecond(), ctime.GetTickCount);

            CFile cfile;

            if (cfile.Open(szFile, CFile::modeCreate | CFile::modeWrite))
            {
                cfile.Write(struOuput.lpOutBuffer, struOuput.dwReturnedXMLSize);
                cfile.Close();
            }
        }

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


void CDlgSuperBrainFunctionTest::OnNMClickListChan(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO:  在此添加控件通知处理程序代码

    //LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
    //DWORD dwPos = GetMessagePos();
    //CPoint point(LOWORD(dwPos), HIWORD(dwPos));

    //m_listChan.ScreenToClient(&point);

    //UINT uFlag = 0;
    //int iSel = m_listChan.HitTest(point, &uFlag);//
    //if (iSel < 0)
    //{
    //    return;
    //}

    *pResult = 0;

}

void CDlgSuperBrainFunctionTest::UpdateChanStatus()
{
    int iIndex = 0;
    int i = 0;
    CString csTemp;
    m_listChan.DeleteAllItems();
    //get the whole state of all channels

    for (i = 0; i < g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)
    {
        if (i < g_struDeviceInfo[m_iDeviceIndex].iAnalogChanNum)
        {
            csTemp.Format(ANALOG_C_FORMAT, g_struDeviceInfo[m_iDeviceIndex].iStartChan + i);
            m_listChan.InsertItem(iIndex, csTemp);
            m_listChan.SetItemData(iIndex, i + g_struDeviceInfo[m_iDeviceIndex].iStartChan);
            iIndex++;
        }
        else
        {
            csTemp.Format(DIGITAL_C_FORMAT, i + 1 - g_struDeviceInfo[m_iDeviceIndex].iAnalogChanNum/*g_struDeviceInfo[m_iDeviceIndex].iStartChan-g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40[0].dwStartDChan*/);
            m_listChan.InsertItem(iIndex, csTemp);
            m_listChan.SetItemData(iIndex, i - g_struDeviceInfo[m_iDeviceIndex].iAnalogChanNum + g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40[0].dwStartDChan);
            iIndex++;
        }
    }
}

void CDlgSuperBrainFunctionTest::UpadateSearchResultList()
{
    char szLan[128] = { 0 };
    int iIndex = 0;

    m_listSearchResult.DeleteAllItems();

    CHeaderCtrl* pHeaderCtrl = m_listSearchResult.GetHeaderCtrl();

    if (pHeaderCtrl != NULL)
    {
        int  nColumnCount = pHeaderCtrl->GetItemCount();
        for (int i = 0; i < nColumnCount; i++)
        {
            m_listSearchResult.DeleteColumn(0);
        }
    }

    if (m_comboSearchType.GetCurSel() == 0)
    {
        g_StringLanType(szLan, "ID", "ID");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "匹配图片的URL", "imageURL");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 120, -1);
        iIndex++;

        g_StringLanType(szLan, "抓图时间", "captureTime");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "图片名称", "imageName");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "年龄段", "age_group");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "性别", "gender");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "上衣颜色", "jacet_color");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "戴眼镜", "glass");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "背包", "bag");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "骑车", "ride");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "相似度", "similarity");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "坐标", "Rect");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 120, -1);
        iIndex++;

        g_StringLanType(szLan, "通道号", "channelID");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

    }
    else if (m_comboSearchType.GetCurSel() == 1)
    {
        g_StringLanType(szLan, "ID", "ID");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "抓拍背景图URL", "snapPicURL");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 120, -1);
        iIndex++;

        g_StringLanType(szLan, "抓图时间", "snapTime");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "人脸子图URL", "facePicURL");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "FDID", "FDID");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "人脸库名称", "FDname");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "检测阀值", "thresholdValue");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 120, -1);
        iIndex++;

        g_StringLanType(szLan, "出生日期", "bornTime");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "名称", "name");
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
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 120, -1);
        iIndex++;

        g_StringLanType(szLan, "证件号", "certificateNumber");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "图片URL", "picURL");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "PID", "PID");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "自定义标签", "PersonInfoExtendList");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "电话号码", "phoneNumber");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 120, -1);
        iIndex++;

        g_StringLanType(szLan, "案件描述", "caseInfo");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "人脸匹配程度", "similarity");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "建模状态", "modelStatus");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "监控点信息", "monitorName");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "戴眼镜", "glass");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "微笑", "smile");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "高危人群", "high_risk_group");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "相似度", "similarity");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "坐标", "Rect");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "通道号", "channelID");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "抓拍图片的名称", "name");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 120, -1);
        iIndex++;

        g_StringLanType(szLan, "性别", "sex");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "年龄段", "ageGroup");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

    }
    else if (m_comboSearchType.GetCurSel() == 2)
    {
        g_StringLanType(szLan, "ID", "ID");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "匹配图片的URL", "imageURL");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 120, -1);
        iIndex++;

        g_StringLanType(szLan, "抓图时间", "captureTime");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "图片名称", "imageName");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "车牌号", "licensePlate");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "车辆主品牌", "vehicleLogoRecog");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "车辆子品牌", "vehicleSubLogoRecog");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "车辆子品牌年款", "vehicleModel");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "车身颜色", "vehicleColor");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "车型", "vehicleType");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "相似度", "similarity");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "坐标", "Rect");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 120, -1);
        iIndex++;

        g_StringLanType(szLan, "车辆行驶方向", "vehicle_direction");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "主驾驶员安全带", "host_safe_belt");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "主驾驶遮阳板", "host_sun_board");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "打电话", "user_phone");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "副驾驶员安全带", "vice_safe_belt");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "副驾驶遮阳板", "vice_sun_board");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;

        g_StringLanType(szLan, "通道号", "channelID");
        m_listSearchResult.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 60, -1);
        iIndex++;
    }
}

void CDlgSuperBrainFunctionTest::GetHumanSearchResult(CXmlBase xmlBase)
{
    if (xmlBase.FindElem("HumanRecognitionSearchResult") && xmlBase.IntoElem())
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

        if (xmlBase.FindElem("HumanModeList") && xmlBase.IntoElem())
        {
            do 
            {
                if (xmlBase.FindElem("HumanMode") && xmlBase.IntoElem())
                {
                    int iRowCount = m_listSearchResult.GetItemCount();
                    CString strTemp = _T("");
                    strTemp.Format("%d", iRowCount);
                    m_listSearchResult.InsertItem(iRowCount, strTemp);

                    int iIndex = 1;

                    if (xmlBase.FindElem("imageURL"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("captureTime"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("imageName"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("age_group"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("gender"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("jacet_color"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("glass"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("bag"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("ride"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("similarity"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("Rect"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetChildren().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("channelID"))
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

void CDlgSuperBrainFunctionTest::GetFaceSearchResult(CXmlBase xmlBase)
{
    if (xmlBase.FindElem("FCSearchResult") && xmlBase.IntoElem())
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

                    if (xmlBase.FindElem("snapPicURL"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("snapTime"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("facePicURL"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("FaceMatchInfoList") && xmlBase.IntoElem())
                    {
                        BOOL bAddLine = FALSE;
                        do
                        {
                            if (xmlBase.FindElem("FaceMatchInfo") && xmlBase.IntoElem())
                            {
                                iRowCount = m_listSearchResult.GetItemCount();
                                CString strTemp = _T("");
                                strTemp.Format("%d", iRowCount);
                                if (bAddLine)
                                {
                                    m_listSearchResult.InsertItem(iRowCount, strTemp);
                                }
                                else
                                {
                                    bAddLine = TRUE;//第一次不用插入行
                                }

                                iIndex = 4;

                                if (xmlBase.FindElem("FDID"))
                                {
                                    m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                                }
                                else
                                {
                                    m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                                }
                                iIndex++;

                                if (xmlBase.FindElem("FDname"))
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

                                if (xmlBase.FindElem("caseInfo"))
                                {
                                    m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                                }
                                else
                                {
                                    m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                                }
                                iIndex++;

                                if (xmlBase.FindElem("similarity"))
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
                    
                    iIndex = 21;

                    if (xmlBase.FindElem("monitorName"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("glass"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("smile"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("high_risk_group"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("similarity"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("Rect"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetChildren().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("channelID"))
                    {
                        int iChannel = -1;
                        iChannel = NET_DVR_SDKChannelToISAPI(m_lUserID, atoi(xmlBase.GetData().c_str()), FALSE);
                        CString strParam = _T("");
                        strParam.Format("%d", iChannel);
                        m_listSearchResult.SetItemText(iRowCount, iIndex, strParam);
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

                    if (xmlBase.FindElem("ageGroup"))
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

void CDlgSuperBrainFunctionTest::GetVehicleSearchResult(CXmlBase xmlBase)
{
    if (xmlBase.FindElem("VehicleRecognitionSearchResult") && xmlBase.IntoElem())
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

        if (xmlBase.FindElem("VehicleModeList") && xmlBase.IntoElem())
        {
            do
            {
                if (xmlBase.FindElem("VehicleMode") && xmlBase.IntoElem())
                {
                    int iRowCount = m_listSearchResult.GetItemCount();
                    CString strTemp = _T("");
                    strTemp.Format("%d", iRowCount);
                    m_listSearchResult.InsertItem(iRowCount, strTemp);

                    int iIndex = 1;

                    if (xmlBase.FindElem("imageURL"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("captureTime"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("imageName"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("licensePlate"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("vehicleLogoRecog"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("vehicleSubLogoRecog"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("vehicleModel"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("vehicleColor"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("vehicleType"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("similarity"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("Rect"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetChildren().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("vehicle_direction"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("host_safe_belt"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("host_sun_board"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("user_phone"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("vice_safe_belt"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("vice_sun_board"))
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listSearchResult.SetItemText(iRowCount, iIndex, "unknown");
                    }
                    iIndex++;

                    if (xmlBase.FindElem("channelID"))
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


void CDlgSuperBrainFunctionTest::OnCbnSelchangeComboSearchType()
{
    // TODO:  在此添加控件通知处理程序代码
    UpadateSearchResultList();
}


void CDlgSuperBrainFunctionTest::OnNMClickListSearchResult(NMHDR *pNMHDR, LRESULT *pResult)
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
