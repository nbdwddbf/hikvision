// DlgUploadFaceLib.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgUploadFaceLib.h"
#include "afxdialogex.h"


// CDlgUploadFaceLib 对话框

IMPLEMENT_DYNAMIC(CDlgUploadFaceLib, CDialogEx)

CDlgUploadFaceLib::CDlgUploadFaceLib(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgUploadFaceLib::IDD, pParent)
    , m_csFDID(_T("1"))
    , m_csPicPath(_T("H:\\工作目录\\基线项目\\前端产线\\人脸库图片导入\\testPic.jpg"))
    , m_csXmlPath(_T("H:\\工作目录\\基线项目\\前端产线\\人脸库图片导入\\test.xml"))
    , m_bConcurrent(FALSE)
    , m_csPID(_T(""))
    , m_bCover(FALSE)
    , m_bCustomID(FALSE)
    , m_bPicURL(FALSE)
    , m_strIdentityKey(_T(""))
{
    m_lUserID = -1;
    m_iDeviceIndex = -1;
    m_lUploadHandle = -1;
    m_hUpLoadThread = NULL;
    m_bStopUpload = FALSE;
    memset(&m_struSendParam, 0, sizeof(m_struSendParam));
    pSendAppendData = NULL;
    pSendPicData = NULL;
    m_iNum = 0;
    memset(&m_struPicRet, 0, sizeof(m_struPicRet));
    m_bClose = false;
}

CDlgUploadFaceLib::~CDlgUploadFaceLib()
{
   // stopUploadData();
}

void CDlgUploadFaceLib::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDT_FDID, m_csFDID);
    DDX_Text(pDX, IDC_EDT_PIC_PATH, m_csPicPath);
    DDX_Text(pDX, IDC_EDT_XML_PATH, m_csXmlPath);
    DDX_Check(pDX, IDC_CHK_CONCURRENT, m_bConcurrent);
    DDX_Control(pDX, IDC_COMBO_NUM, m_comNum);
    DDX_Text(pDX, IDC_EDT_PID, m_csPID);
    DDX_Check(pDX, IDC_CHECK1, m_bCover);
    DDX_Check(pDX, IDC_CHECK2, m_bCustomID);
    DDX_Check(pDX, IDC_CHECK3, m_bPicURL);
    DDX_Text(pDX, IDC_EDT_INDENTITY_KEY, m_strIdentityKey);
}


BEGIN_MESSAGE_MAP(CDlgUploadFaceLib, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_XML_IMPORT, &CDlgUploadFaceLib::OnBnClickedBtnXmlImport)
    ON_BN_CLICKED(IDC_BTN_PIC_IMPORT, &CDlgUploadFaceLib::OnBnClickedBtnPicImport)
    ON_BN_CLICKED(IDC_BTN_UPLOAD, &CDlgUploadFaceLib::OnBnClickedBtnUpload)
    ON_BN_CLICKED(IDC_BTN_STOP, &CDlgUploadFaceLib::OnBnClickedBtnStop)
    ON_WM_CLOSE()
    ON_CBN_SELCHANGE(IDC_COMBO_NUM, &CDlgUploadFaceLib::OnCbnSelchangeComboNum)
END_MESSAGE_MAP()


// CDlgUploadFaceLib 消息处理程序


BOOL CDlgUploadFaceLib::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_comNum.SetCurSel(0);
    OnCbnSelchangeComboNum();
    startControlShow(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}


void CDlgUploadFaceLib::OnBnClickedBtnXmlImport()
{
    // TODO:  在此添加控件通知处理程序代码
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_csXmlPath = dlg.GetPathName();
        UpdateData(FALSE);
    }
}


void CDlgUploadFaceLib::OnBnClickedBtnPicImport()
{
    // TODO:  在此添加控件通知处理程序代码
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_csPicPath = dlg.GetPathName();
        UpdateData(FALSE);
    }
}

void CDlgUploadFaceLib::readFileData()
{
    if (NULL != pSendAppendData)
    {
        delete[] pSendAppendData;
        pSendAppendData = NULL;
    }

    if (NULL != pSendPicData)
    {
        delete[] pSendPicData;
        pSendPicData = NULL;
    }

    memset(&m_struSendParam, 0, sizeof(m_struSendParam));

    char szLan[1280] = { 0 };
    char szFileName[MAX_PATH] = { 0 };
    DWORD dwFileSize = 0;
    //读XML文件
    strcpy(szFileName, m_csXmlPath);
    CFile cFile;
    if (!cFile.Open(szFileName, NULL))
    {
        g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
        AfxMessageBox(szLan);
        return;
    }
    dwFileSize = (DWORD)cFile.GetLength();
    if (dwFileSize == 0)
    {
        g_StringLanType(szLan, "配置文件为空", "Configure file is empty");
        AfxMessageBox(szLan);
    }

    pSendAppendData = new BYTE[dwFileSize];
    cFile.Read(pSendAppendData, dwFileSize);
    m_struSendParam.pSendAppendData = pSendAppendData;
    m_struSendParam.dwSendAppendDataLen = dwFileSize;
    cFile.Close();



    //读图片文件
    strcpy(szFileName, m_csPicPath);
    if (!cFile.Open(szFileName, NULL))
    {
        g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
        AfxMessageBox(szLan);
        return;
    }
    dwFileSize = (DWORD)cFile.GetLength();
    if (dwFileSize == 0)
    {
        g_StringLanType(szLan, "配置文件为空", "Configure file is empty");
        AfxMessageBox(szLan);
    }

    pSendPicData = new BYTE[dwFileSize];
    cFile.Read(pSendPicData, dwFileSize);
    m_struSendParam.pSendData = pSendPicData;
    m_struSendParam.dwSendDataLen = dwFileSize;
    m_struSendParam.byPicType = 1;
    m_struSendParam.byPicURL = m_bPicURL;
    cFile.Close();

}

BOOL CDlgUploadFaceLib::sendUploadData()
{
    if (NET_DVR_UploadSend(m_lUploadHandle, &m_struSendParam, NULL) < 0)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadSend");
        return FALSE;
    }
    return TRUE;
}

LONG CDlgUploadFaceLib::getUploadState()
{
    DWORD dwProgress = 0;
    LONG iStatus = -1;
    char szStatus[256] = { 0 };

    memset(szStatus, 0, 256);
    iStatus = NET_DVR_GetUploadState(m_lUploadHandle, &dwProgress);
    if (iStatus == -1)  //即入口返回失败
    {
        sprintf(szStatus, "上传失败!status[%d]", iStatus);
        SetDlgItemText(IDC_STATIC_UPLOAD_INFO, szStatus);
        Sleep(100);
    }
    else if (iStatus == 2) //正在上传
    {
        sprintf(szStatus, "正在上传!status[%d],progress[%d]", iStatus, dwProgress);
        SetDlgItemText(IDC_STATIC_UPLOAD_INFO, szStatus);
        Sleep(100);
    }
    else if (iStatus == 1) //上传成功
    {
        sprintf(szStatus, "上传成功!status[%d],progress[%d]", iStatus, dwProgress);
        SetDlgItemText(IDC_STATIC_UPLOAD_INFO, szStatus);
        Sleep(100); //这个sleep只是为了addlog能够有时间执行
    }
    else if (iStatus == 35)
    {
        g_StringLanType(szStatus, "图片URL未开始下载", "URL Download Not Start");
        SetDlgItemText(IDC_STATIC_UPLOAD_INFO, szStatus);
        Sleep(100); //这个sleep只是为了addlog能够有时间执行
    }
    else if (iStatus == 36)
    {
        g_StringLanType(szStatus, "customHumanID重复", "customHumanID Repeat");
        SetDlgItemText(IDC_STATIC_UPLOAD_INFO, szStatus);
        Sleep(100); //这个sleep只是为了addlog能够有时间执行
    }
    else if (iStatus == 38)
    {
        g_StringLanType(szStatus, "建模失败,设备内部错误", "Modeling failed. Device internal error.");
        SetDlgItemText(IDC_STATIC_UPLOAD_INFO, szStatus);
        Sleep(100); //这个sleep只是为了addlog能够有时间执行
    }
    else if (iStatus == 39)
    {
        g_StringLanType(szStatus, "建模失败,人脸建模错误", "Modeling failed. Face modeling error.");
        SetDlgItemText(IDC_STATIC_UPLOAD_INFO, szStatus);
        Sleep(100); //这个sleep只是为了addlog能够有时间执行
    }
    else if (iStatus == 40)
    {
        g_StringLanType(szStatus, "建模失败,人脸质量评分错误", "Modeling failed. Face grading error.");
        SetDlgItemText(IDC_STATIC_UPLOAD_INFO, szStatus);
        Sleep(100); //这个sleep只是为了addlog能够有时间执行
    }
    else if (iStatus == 41)
    {
        g_StringLanType(szStatus, "建模失败,特征点提取错误", "Modeling failed. Facial feature points extracting error.");
        SetDlgItemText(IDC_STATIC_UPLOAD_INFO, szStatus);
        Sleep(100); //这个sleep只是为了addlog能够有时间执行
    }
    else if (iStatus == 42)
    {
        g_StringLanType(szStatus, "建模失败,属性提取错误", "Modeling failed. Feature analyzing error.");
        SetDlgItemText(IDC_STATIC_UPLOAD_INFO, szStatus);
        Sleep(100); //这个sleep只是为了addlog能够有时间执行
    }
    else if (iStatus == 43)
    {
        g_StringLanType(szStatus, "图片数据错误", "Picture data error.");
        SetDlgItemText(IDC_STATIC_UPLOAD_INFO, szStatus);
        Sleep(100); //这个sleep只是为了addlog能够有时间执行
    }
    else if (iStatus == 44)
    {
        g_StringLanType(szStatus, "图片附加信息错误", "Attached picture information error.");
        SetDlgItemText(IDC_STATIC_UPLOAD_INFO, szStatus);
        Sleep(100); //这个sleep只是为了addlog能够有时间执行
    }
    else //上传失败,显示状态
    {
        sprintf(szStatus, "上传失败!status[%d]", iStatus);
        SetDlgItemText(IDC_STATIC_UPLOAD_INFO, szStatus);
        Sleep(100); //这个sleep只是为了addlog能够有时间执行
    }

    return iStatus;
}

void CDlgUploadFaceLib::timeShow(BOOL bBegin)
{
    char szTimeShow[256] = { 0 };
    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128] = {0};
    sprintf(chTime, "%2.2d:%2.2d:%2.2d   %3.3d", t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

    if (bBegin)
    {
        sprintf(szTimeShow, "start time: %s", chTime);
        SetDlgItemText(IDC_STATIC_TIME_BEGIN, szTimeShow);
    } 
    else
    {
        sprintf(szTimeShow, "end time: %s", chTime);
        SetDlgItemText(IDC_STATIC_TIME_STOP, szTimeShow);
    }
}

DWORD WINAPI CDlgUploadFaceLib::FaceLibUpLoadThread(LPVOID pParam)
{
    CDlgUploadFaceLib *pThis = (CDlgUploadFaceLib*)pParam;
    
    pThis->timeShow(TRUE);

    pThis->sendUploadData();

    LONG iStatus = -1;

    int n = pThis->m_iNum -1;

    while (1)
    {
        if (-1 == pThis->m_lUploadHandle || pThis->m_bClose)
        {
            return 0;
        }

        iStatus = pThis->getUploadState();
        if (1 == iStatus)
        {
            NET_DVR_GetUploadResult(pThis->m_lUploadHandle, &pThis->m_struPicRet, sizeof(pThis->m_struPicRet));
            pThis->SetDlgItemText(IDC_EDT_PID, (char*)pThis->m_struPicRet.sUrl);
            if (n>0)
            {
                pThis->sendUploadData();
                n--;
            }
            
            
        }
        else if ((iStatus >= 3 && iStatus <= 10) || iStatus == 31 || iStatus == -1)
        {
            pThis->stopUploadData();
            break;
        }
    }

    pThis->timeShow(FALSE);

//     if (-1 != pThis->m_lUploadHandle)
//     {
//         pThis->stopUploadData();
//     }

    return 0;
}

void CDlgUploadFaceLib::OnBnClickedBtnUpload()
{
    // TODO:  在此添加控件通知处理程序代码

    UpdateData(TRUE);

    if (m_lUploadHandle != -1)
    {
        NET_DVR_UploadClose(m_lUploadHandle);
        m_lUploadHandle = -1;
    }

    NET_DVR_FACELIB_COND struFaceLibCond = { 0 };
    struFaceLibCond.dwSize = sizeof(NET_DVR_FACELIB_COND);
    memcpy(struFaceLibCond.szFDID, m_csFDID.GetBuffer(0), m_csFDID.GetLength());
    struFaceLibCond.byConcurrent = m_bConcurrent;
    struFaceLibCond.byCover = m_bCover;
    struFaceLibCond.byCustomFaceLibID = m_bCustomID;
    memcpy(struFaceLibCond.byIdentityKey, m_strIdentityKey.GetBuffer(0), m_strIdentityKey.GetLength());

    m_lUploadHandle = NET_DVR_UploadFile_V40(m_lUserID, IMPORT_DATA_TO_FACELIB, &struFaceLibCond, sizeof(NET_DVR_FACELIB_COND), NULL, NULL, 0);
    if (m_lUploadHandle < 0)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "IMPORT_DATA_TO_FACELIB");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "IMPORT_DATA_TO_FACELIB");
    }

    readFileData();

    DWORD dwThreadID = 0;
    m_hUpLoadThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(FaceLibUpLoadThread), this, 0, &dwThreadID);
    if (m_hUpLoadThread == NULL)
    {
        char szLan[128] = { 0 };
        g_StringLanType(szLan, "打开上传视图库数据线程失败!", "open UpLoad face lib data thread Fail!");
        AfxMessageBox(szLan);
        return;
    }

    startControlShow(TRUE);
    
}

void CDlgUploadFaceLib::stopUploadData()
{
    if (m_lUploadHandle != -1)
    {
        NET_DVR_UploadClose(m_lUploadHandle);
        m_lUploadHandle = -1;
    }

    if (NULL != pSendAppendData)
    {
        delete[] pSendAppendData;
        pSendAppendData = NULL;
    }

    if (NULL != pSendPicData)
    {
        delete[] pSendPicData;
        pSendPicData = NULL;
    }

    startControlShow(FALSE);
}


void CDlgUploadFaceLib::OnBnClickedBtnStop()
{
    // TODO:  在此添加控件通知处理程序代码
    stopUploadData();
}

void CDlgUploadFaceLib::OnClose()
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值
    m_bClose = true;

    Sleep(500);

    if (m_lUploadHandle != -1)
    {
        NET_DVR_UploadClose(m_lUploadHandle);
        m_lUploadHandle = -1;
    }

    if (NULL != pSendAppendData)
    {
        delete[] pSendAppendData;
        pSendAppendData = NULL;
    }

    if (NULL != pSendPicData)
    {
        delete[] pSendPicData;
        pSendPicData = NULL;
    }

    CDialogEx::OnClose();
}


void CDlgUploadFaceLib::OnCbnSelchangeComboNum()
{
    // TODO:  在此添加控件通知处理程序代码
    if (0 == m_comNum.GetCurSel())
    {
        m_iNum = 1;
    } 
    else if (1 == m_comNum.GetCurSel())
    {
        m_iNum = 10;
    }
    else if (2 == m_comNum.GetCurSel())
    {
        m_iNum = 30;
    }
    else if (3 == m_comNum.GetCurSel())
    {
        m_iNum = 50;
    }
    else if (4 == m_comNum.GetCurSel())
    {
        m_iNum = 100;
    }
    else if (5 == m_comNum.GetCurSel())
    {
        m_iNum = 500;
    }
    else if (6 == m_comNum.GetCurSel())
    {
        m_iNum = 1000;
    }

    
}

void CDlgUploadFaceLib::startControlShow(BOOL bstart)
{
    if (bstart)
    {
        GetDlgItem(IDC_EDT_FDID)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHK_CONCURRENT)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_NUM)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDT_XML_PATH)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDT_PIC_PATH)->EnableWindow(FALSE);
        GetDlgItem(IDC_BTN_XML_IMPORT)->EnableWindow(FALSE);
        GetDlgItem(IDC_BTN_PIC_IMPORT)->EnableWindow(FALSE);
        GetDlgItem(IDC_BTN_UPLOAD)->EnableWindow(FALSE);
        GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
    } 
    else
    {
        GetDlgItem(IDC_EDT_FDID)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHK_CONCURRENT)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_NUM)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDT_XML_PATH)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDT_PIC_PATH)->EnableWindow(TRUE);
        GetDlgItem(IDC_BTN_XML_IMPORT)->EnableWindow(TRUE);
        GetDlgItem(IDC_BTN_PIC_IMPORT)->EnableWindow(TRUE);
        GetDlgItem(IDC_BTN_UPLOAD)->EnableWindow(TRUE);
        GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
    }
    
}
