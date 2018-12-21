// DlgAcsCheckFacePicture.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAcsCheckFacePicture.h"
#include "afxdialogex.h"


// CDlgAcsCheckFacePicture 对话框
#define MAX_PICTURE_LEN 200 * 1024
#define MAX_TEMPLATE_LEN 4 * 1024
#define WM_MSG_UPLOAD_PICTURE_FINISH 1002

IMPLEMENT_DYNAMIC(CDlgAcsCheckFacePicture, CDialog)

CDlgAcsCheckFacePicture::CDlgAcsCheckFacePicture(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAcsCheckFacePicture::IDD, pParent)
    , m_bEnableTemplate(FALSE)
    , m_dwTemplateLen(0)
    , m_csTemplatePath(_T(""))
{
    m_dwPictureLen = 0;
    m_szPictureName = _T("");
    m_dwPictureNo = 0;
    m_dwLen = 0;
    m_lUploadPicCfgHandle = -1;
    m_dwSendIndex = 0;
}

CDlgAcsCheckFacePicture::~CDlgAcsCheckFacePicture()
{
}

void CDlgAcsCheckFacePicture::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_CHECK_FACE_PICTURE_CFG, m_listPicture);
    DDX_Text(pDX, IDC_EDIT_PICTURE_LEN, m_dwPictureLen);
    DDX_Text(pDX, IDC_EDIT_PICTURE_ADDRESS, m_szPictureName);
    DDX_Text(pDX, IDC_EDIT_PICTURE_NO, m_dwPictureNo);
    DDX_Check(pDX, IDC_CHECK_ENABLE_TEMPLATE, m_bEnableTemplate);
    DDX_Text(pDX, IDC_EDIT_TEMPLATE_LEN, m_dwTemplateLen);
    DDX_Text(pDX, IDC_EDIT_TEMPLATE_ADDRESS, m_csTemplatePath);
}


BEGIN_MESSAGE_MAP(CDlgAcsCheckFacePicture, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgAcsCheckFacePicture::OnBnClickedButtonAdd)
    ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CDlgAcsCheckFacePicture::OnBnClickedButtonClear)
    ON_BN_CLICKED(IDC_BUTTON_UPLOAD, &CDlgAcsCheckFacePicture::OnBnClickedButtonUpload)
    ON_BN_CLICKED(IDOK, &CDlgAcsCheckFacePicture::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CDlgAcsCheckFacePicture::OnBnClickedButtonBrowse)
    ON_MESSAGE(WM_MSG_UPLOAD_PICTURE_FINISH, OnMsgCheckFacePictureCfgFinish)
    ON_BN_CLICKED(IDC_BUTTON_BROWSE2, &CDlgAcsCheckFacePicture::OnBnClickedButtonBrowse2)
END_MESSAGE_MAP()

LRESULT CDlgAcsCheckFacePicture::OnMsgCheckFacePictureCfgFinish(WPARAM wParam, LPARAM lParam)
{
    if (!NET_DVR_StopRemoteConfig(m_lUploadPicCfgHandle))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig failed");
        return 0;
    }
    m_lUploadPicCfgHandle = -1;
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_BULK_CHECK_FACE_PICTURE finished");
    return 0;
}

// CDlgAcsCheckFacePicture 消息处理程序
BOOL CDlgAcsCheckFacePicture::OnInitDialog()
{
    CDialog::OnInitDialog();

    char szLan[128] = { 0 };

    m_listPicture.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "编号", "No");
    m_listPicture.InsertColumn(0, szLan, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLan, "图片编号", "Picture No");
    m_listPicture.InsertColumn(1, szLan, LVCFMT_LEFT, 150, -1);
    return TRUE;
}

void CALLBACK g_fCheckFacePictureCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgAcsCheckFacePicture* pDlg = (CDlgAcsCheckFacePicture*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcessCheckFacePictureCallbackData(dwType, lpBuffer, dwBufLen);
}

void CDlgAcsCheckFacePicture::ProcessCheckFacePictureCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_PROCESSING)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Check PROCESSING %d", m_dwSendIndex);

            SendNextPicture();
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Check Err:NET_SDK_CALLBACK_STATUS_FAILED %d", m_dwSendIndex);

            SendNextPicture();
        }
        //下面两个关闭长连接
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Check SUCCESS");
            PostMessage(WM_MSG_UPLOAD_PICTURE_FINISH, 0, 0);
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_EXCEPTION)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Check Exception");
            PostMessage(WM_MSG_UPLOAD_PICTURE_FINISH, 0, 0);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Check SUCCESS");
            PostMessage(WM_MSG_UPLOAD_PICTURE_FINISH, 0, 0);
        }
    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        NET_DVR_CHECK_FACE_PICTURE_STATUS struCfg = { 0 };
        memcpy(&struCfg, lpBuffer, sizeof(struCfg));

        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Check PROCESSING,Check Status:%d", struCfg.byCheckStatus);

        SendNextPicture();
    }
}

void CDlgAcsCheckFacePicture::OnBnClickedButtonAdd()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    //1.get data from control
    NET_DVR_CHECK_FACE_PICTURE_CFG struCheckFacePictureCfg = { 0 };

    struCheckFacePictureCfg.dwSize = sizeof(struCheckFacePictureCfg);
    struCheckFacePictureCfg.dwPictureNo = m_dwPictureNo;
    struCheckFacePictureCfg.pPictureBuffer = ReadPictureFromFile(m_szPictureName);
    struCheckFacePictureCfg.dwPictureLen = m_dwLen;

    if (m_bEnableTemplate)
    {
        struCheckFacePictureCfg.pFaceTemplateBuffer = ReadTemplateFromFile(m_csTemplatePath);
        struCheckFacePictureCfg.dwFaceTemplateLen = m_dwTemplateLen;
        if (struCheckFacePictureCfg.pFaceTemplateBuffer == NULL)
        {
            return;
        }
    }

    if (struCheckFacePictureCfg.pPictureBuffer == NULL)
    {
        return;
    }

    //2.is duplicated?
    LPNET_DVR_CHECK_FACE_PICTURE_CFG pCheckFacePictureInfo = NULL;
    int iItemIndex = GetExistItem(&struCheckFacePictureCfg);
    if (iItemIndex == -1)
    {
        pCheckFacePictureInfo = new NET_DVR_CHECK_FACE_PICTURE_CFG;
        if (pCheckFacePictureInfo == NULL)
        {
            return;
        }
        int iSize = sizeof(NET_DVR_CHECK_FACE_PICTURE_CFG);
        int nItemCount = m_listPicture.GetItemCount();

        CString strItem = "";
        strItem.Format("%d", nItemCount + 1);
        iItemIndex = m_listPicture.InsertItem(nItemCount, strItem);
        m_listPicture.SetItemData(nItemCount, (DWORD)pCheckFacePictureInfo);
    }
    else
    {
        pCheckFacePictureInfo = (LPNET_DVR_CHECK_FACE_PICTURE_CFG)m_listPicture.GetItemData(iItemIndex);
    }
    memcpy(pCheckFacePictureInfo, &struCheckFacePictureCfg, sizeof(struCheckFacePictureCfg));

    //3.set to list
    char szLan[1024] = { 0 };

    sprintf(szLan, "%d", iItemIndex);
    sprintf(szLan, "%d", pCheckFacePictureInfo->dwPictureNo);
    m_listPicture.SetItemText(iItemIndex, 1, szLan);
    UpdateData(FALSE);

    return;
}


void CDlgAcsCheckFacePicture::OnBnClickedButtonClear()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    Clear();    
    m_listPicture.DeleteAllItems();
    UpdateData(FALSE);
}


void CDlgAcsCheckFacePicture::OnBnClickedButtonUpload()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_lUploadPicCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lUploadPicCfgHandle);
    }
    UpdateData(TRUE);

    NET_DVR_CHECK_FACE_PICTURE_COND struCond = { 0 };
    struCond.dwSize = sizeof(struCond);
    struCond.dwPictureNum = m_listPicture.GetItemCount();

    if (m_bEnableTemplate)
    {
        struCond.byCheckTemplate = 1;
    }

    m_lUploadPicCfgHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_BULK_CHECK_FACE_PICTURE, &struCond, sizeof(struCond), g_fCheckFacePictureCallback, this);
    if (m_lUploadPicCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_BULK_CHECK_FACE_PICTURE failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_BULK_CHECK_FACE_PICTURE success");
    }

    //校验第一张人脸图片, 失败时关闭连接
    m_dwSendIndex = 0;
    if (!SendFirstPicture())
    {
        NET_DVR_StopRemoteConfig(m_lUploadPicCfgHandle);
        m_lUploadPicCfgHandle = -1;
    }
}


void CDlgAcsCheckFacePicture::OnBnClickedOk()
{
    // TODO:  在此添加控件通知处理程序代码
    Clear();
    CDialog::OnOK();
}


void CDlgAcsCheckFacePicture::OnBnClickedButtonBrowse()
{
    // TODO:  在此添加控件通知处理程序代码
    CString strFilter = _T("All Files(*.*)|*.*||");
    CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
    if (dlg.DoModal() != IDOK)
    {
        return;
    }
    m_szPictureName = dlg.GetPathName();
    GetDlgItem(IDC_EDIT_PICTURE_ADDRESS)->SetWindowText(m_szPictureName);
}

/** @fn  char * CDlgAcsCheckFacePicture::ReadTemplateFromFile(CString fileName)
*  @brief
*  @param(IN)
*  @return  char * -- success, NULL --fail.
*/
char * CDlgAcsCheckFacePicture::ReadTemplateFromFile(CString fileName)
{
    char *pTemplateBuffer = new char[MAX_TEMPLATE_LEN];
    if (pTemplateBuffer == NULL)
    {
        AfxMessageBox("allocate resource failed!");
        return NULL;
    }

    if (m_csTemplatePath == "")
    {
        AfxMessageBox("need input picture filename with full path at first!");
        return NULL;
    }

    FILE* fp = NULL;
    fp = fopen(m_csTemplatePath.GetBuffer(), "rb"); //只供读取
    if (fp == NULL)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "HPR_ReadFile failed");
        return NULL;
    }
    fseek(fp, 0L, SEEK_END);
    int len = ftell(fp);

    m_dwTemplateLen = len;

    if (len > MAX_TEMPLATE_LEN)
    {
        AfxMessageBox("The picture is too big than 512 build-in sdk!");
        return NULL;
    }

    rewind(fp);
    fread(pTemplateBuffer, 1, m_dwTemplateLen, fp);
    fclose(fp);
    return pTemplateBuffer;
}

/** @fn  char * CDlgAcsCheckFacePicture::ReadPictureFromFile(CString fileName)
*  @brief
*  @param(IN)
*  @return  char * -- success, NULL --fail.
*/
char * CDlgAcsCheckFacePicture::ReadPictureFromFile(CString fileName)
{
    //
    char *pFaceBuffer = new char[MAX_PICTURE_LEN];
    if (pFaceBuffer == NULL)
    {
        AfxMessageBox("allocate resource failed!");
        return NULL;
    }

    if (m_szPictureName == "")
    {
        AfxMessageBox("need input picture filename with full path at first!");
        return NULL;
    }

    FILE* fp = NULL;
    fp = fopen(m_szPictureName.GetBuffer(), "rb"); //只供读取
    if (fp == NULL)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "HPR_ReadFile failed");
        return NULL;
    }
    fseek(fp, 0L, SEEK_END);
    int len = ftell(fp);

    m_dwLen = len;
    m_dwPictureLen = len / 1024;

    if (len > MAX_PICTURE_LEN)
    {
        AfxMessageBox("The picture is too big than 200K build-in sdk!");
        return NULL;
    }

    rewind(fp);
    fread(pFaceBuffer, 1, m_dwLen, fp);
    fclose(fp);
    return pFaceBuffer;
}

/** @fn  CDlgAcsCheckFacePicture::GetExistItem(const NET_DVR_CHECK_FACE_PICTURE_CFG *lpCheckFacePictureCfg)
*  @brief 从列表中查找是否存在相同的实例
*  @param(IN) NET_DVR_CHECK_FACE_PICTURE_CFG *lpCheckFacePictureCfg
*  @return  index--the index, -1--no duplicate.
*/
int CDlgAcsCheckFacePicture::GetExistItem(const NET_DVR_CHECK_FACE_PICTURE_CFG *lpCheckFacePictureCfg)
{
    int nItemCount = m_listPicture.GetItemCount();
    int i = 0;
    LPNET_DVR_CHECK_FACE_PICTURE_CFG lpTemp = NULL;
    for (i = 0; i < nItemCount; i++)
    {
        lpTemp = (LPNET_DVR_CHECK_FACE_PICTURE_CFG)m_listPicture.GetItemData(i);
        if (!lpCheckFacePictureCfg)
        {
            continue;
        }
        if (lpCheckFacePictureCfg->dwPictureNo == lpTemp->dwPictureNo)
        {
            return i;
        }
    }
    return -1;
}

/** @fn  void CDlgAcsCheckFacePicture::Clear()
*  @brief 资源释放
*  @return  void
*/
void CDlgAcsCheckFacePicture::Clear()
{
    int nItemCount = m_listPicture.GetItemCount();
    for (int i = 0; i < nItemCount; i++)
    {
        LPNET_DVR_CHECK_FACE_PICTURE_CFG pCheckFacePictureInfo = (LPNET_DVR_CHECK_FACE_PICTURE_CFG)m_listPicture.GetItemData(i);
        if (pCheckFacePictureInfo != NULL && pCheckFacePictureInfo->pPictureBuffer != NULL)
        {
            delete[] pCheckFacePictureInfo->pPictureBuffer;
            pCheckFacePictureInfo->pPictureBuffer = NULL;
        }

        if (pCheckFacePictureInfo != NULL && pCheckFacePictureInfo->pFaceTemplateBuffer != NULL)
        {
            delete[] pCheckFacePictureInfo->pFaceTemplateBuffer;
            pCheckFacePictureInfo->pFaceTemplateBuffer = NULL;
        }

        if (pCheckFacePictureInfo != NULL)
        {
            delete pCheckFacePictureInfo;
            pCheckFacePictureInfo = NULL;
        }
    }
    m_dwPictureLen = 0;
    return;
}

/** @fn BOOL SendFirstPicture()
*  @brief 校验第一张人脸图片
*  @return  HPR_TRUE--success, HPR_FALSE--fail.
*/
BOOL CDlgAcsCheckFacePicture::SendFirstPicture()
{
    int nItemCount = m_listPicture.GetItemCount();

    if (nItemCount <= 0)
    {
        AfxMessageBox("Please add info to list at first");
        return FALSE;
    }
    m_dwSendIndex = 0;
    //获取第一个人脸图片配置数据
    LPNET_DVR_CHECK_FACE_PICTURE_CFG pPictureInfo = (LPNET_DVR_CHECK_FACE_PICTURE_CFG)m_listPicture.GetItemData(m_dwSendIndex);

    if (pPictureInfo == NULL)
    {
        return FALSE;
    }

    if (!NET_DVR_SendRemoteConfig(m_lUploadPicCfgHandle, ENUM_ACS_SEND_DATA, (char *)pPictureInfo, sizeof(*pPictureInfo)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Send Fail,Picture No: %d", pPictureInfo->dwPictureNo);
        return FALSE;
    }

    return TRUE;
}

/** @fn BOOL SendNextPicture()
*  @brief 校验下一张人脸图片
*  @return  HPR_TRUE--success, HPR_FALSE--fail.
*/
BOOL CDlgAcsCheckFacePicture::SendNextPicture()
{
    int nItemCount = m_listPicture.GetItemCount();

    if (nItemCount < 0)
    {
        AfxMessageBox("Please add info to list at first");
    }

    m_dwSendIndex++;
    //已经发完了
    if (m_dwSendIndex >= nItemCount)
    {
        return TRUE;
    }

    LPNET_DVR_CHECK_FACE_PICTURE_CFG pPictureInfo = (LPNET_DVR_CHECK_FACE_PICTURE_CFG)m_listPicture.GetItemData(m_dwSendIndex);

    if (pPictureInfo == NULL)
    {
        return FALSE;
    }

    if (!NET_DVR_SendRemoteConfig(m_lUploadPicCfgHandle, ENUM_ACS_SEND_DATA, (char *)pPictureInfo, sizeof(*pPictureInfo)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Send Fail,Picture No: %d", pPictureInfo->dwPictureNo);
        PostMessage(WM_MSG_UPLOAD_PICTURE_FINISH, 0, 0);
        return FALSE;
    }

    return TRUE;
}

void CDlgAcsCheckFacePicture::OnBnClickedButtonBrowse2()
{
    // TODO:  在此添加控件通知处理程序代码
    CString strFilter = _T("All Files(*.*)|*.*||");
    CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
    if (dlg.DoModal() != IDOK)
    {
        return;
    }
    m_csTemplatePath = dlg.GetPathName();
    GetDlgItem(IDC_EDIT_TEMPLATE_ADDRESS)->SetWindowText(m_csTemplatePath);
}
