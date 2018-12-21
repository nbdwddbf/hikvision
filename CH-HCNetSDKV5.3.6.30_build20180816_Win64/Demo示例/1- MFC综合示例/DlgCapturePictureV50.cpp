// DlgCapturePictureV50.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgCapturePictureV50.h"
#include "afxdialogex.h"


// CDlgCapturePictureV50 对话框

IMPLEMENT_DYNAMIC(CDlgCapturePictureV50, CDialogEx)

CDlgCapturePictureV50::CDlgCapturePictureV50(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCapturePictureV50::IDD, pParent)
    , m_pChanInfo(NULL)
    , m_pCompresscfgAbility(NULL)
{
    m_pCompresscfgAbility = new NET_DVR_COMPRESSIONCFG_ABILITY;
    memset(m_pCompresscfgAbility, 0, sizeof(NET_DVR_COMPRESSIONCFG_ABILITY));
    m_dwPicLen = 400000 * 2;
}

CDlgCapturePictureV50::~CDlgCapturePictureV50()
{
    if (m_pChanInfo != NULL)
    {
        m_pChanInfo = NULL;
    }
    if (m_pCompresscfgAbility != NULL)
    {
        delete m_pCompresscfgAbility;
        m_pCompresscfgAbility = NULL;
    }
}

void CDlgCapturePictureV50::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_PICTURE_RESOLUTION, m_cmbPictureReslution);
    DDX_Control(pDX, IDC_COMBO_PICTURE_QUALITY, m_cmbPictureQuality);
    DDX_Control(pDX, IDC_COMBO_PICTURE_FORMAT, m_cmbPicutureFormat);
    DDX_Control(pDX, IDC_COMBO_CAPTURE_TYPE, m_cmbCaptureType);
}


BEGIN_MESSAGE_MAP(CDlgCapturePictureV50, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_CAPTURE_PICTURE_V50_EXIT, &CDlgCapturePictureV50::OnBnClickedBtnCapturePictureV50Exit)
    ON_BN_CLICKED(IDC_BTN_CAPTURE_PICTURE_V50, &CDlgCapturePictureV50::OnBnClickedBtnCapturePictureV50)
END_MESSAGE_MAP()


// CDlgCapturePictureV50 消息处理程序


void CDlgCapturePictureV50::OnCancel()
{
    // TODO:  在此添加专用代码和/或调用基类

    CDialogEx::OnCancel();
}


BOOL CDlgCapturePictureV50::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化

    m_iDeviceIndex = m_pChanInfo->iDeviceIndex;
    int iChanIndex = m_pChanInfo->iChannelNO; //m_pChanInfo->iChanIndex + g_struDeviceInfo[m_iDeviceIndex].iStartChan;

    m_cmbPictureReslution.ResetContent();
    m_cmbPictureReslution.AddString("CIF");
    m_cmbPictureReslution.SetItemData(0, 0);
    m_cmbPictureReslution.AddString("QCIF");
    m_cmbPictureReslution.SetItemData(1, 1);
    m_cmbPictureReslution.AddString("4CIF");
    m_cmbPictureReslution.SetItemData(2, 2);
    m_cmbPictureReslution.SetCurSel(0);

    if (m_iDeviceIndex >= 0)
    {
        if (GetCompressCfgAbility(iChanIndex))
        {
            GetResolutionAbility();
        }
    }

    m_cmbPictureQuality.SetCurSel(m_pChanInfo->iPicQuality);
    m_cmbPictureReslution.SetCurSel(m_pChanInfo->iPicResolution);
    m_cmbPicutureFormat.SetCurSel(0);
    m_cmbCaptureType.SetCurSel(0);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}

void CDlgCapturePictureV50::OnBnClickedBtnCapturePictureV50Exit()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_pCompresscfgAbility != NULL)
    {
        delete m_pCompresscfgAbility;
        m_pCompresscfgAbility = NULL;
    }
    OnCancel();
}

void CDlgCapturePictureV50::GetResolutionAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (MAIN_RESOLUTION_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_cmbPictureReslution.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_cmbPictureReslution.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_cmbPictureReslution.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

BOOL CDlgCapturePictureV50::GetCompressCfgAbility(DWORD dwIPChanIndex)
{
    if (!NET_DVR_GetDeviceAbility(g_struDeviceInfo[m_iDeviceIndex].lLoginID, PIC_CAPTURE_ABILITY, (char*)&dwIPChanIndex, sizeof(dwIPChanIndex), (char*)m_pCompresscfgAbility, sizeof(NET_DVR_COMPRESSIONCFG_ABILITY)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "PIC_CAPTURE_ABILITY");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "PIC_CAPTURE_ABILITY");
        return TRUE;
    }
}

void CDlgCapturePictureV50::OnBnClickedBtnCapturePictureV50()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    char cFilename[256] = { 0 };
    CString sTemp;
    int iDeviceIndex = m_pChanInfo->iDeviceIndex;
    int iChanIndex = m_pChanInfo->iChanIndex;
    int iChanShowNum = m_pChanInfo->iChannelNO;
    char *sPicBuffer = new char[m_dwPicLen];
    DWORD lpSizeReturned = 0;
    NET_DVR_PICPARAM_V50 struPara;
    memset(&struPara, 0, sizeof(NET_DVR_PICPARAM_V50));
    struPara.struParam.wPicQuality = (WORD)m_cmbPictureQuality.GetCurSel();
    struPara.struParam.wPicSize = (WORD)m_cmbPictureReslution.GetItemData(m_cmbPictureReslution.GetCurSel());
    struPara.byCapturePicType = m_cmbCaptureType.GetCurSel();
    DWORD dwPicSize = m_dwPicLen;
    CTime time = CTime::GetCurrentTime();
    m_pChanInfo->iPicResolution = m_cmbPictureReslution.GetCurSel();
    m_pChanInfo->iPicQuality = m_cmbPictureQuality.GetCurSel();



    if (NET_DVR_CapturePicture_V50(g_struDeviceInfo[iDeviceIndex].lLoginID, iChanShowNum, &struPara, sPicBuffer, dwPicSize, &lpSizeReturned))
    {
        CString sTemp;
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_CapturePicture_V50 file[%d]", lpSizeReturned);
    }
    else
    {
        if (sPicBuffer != NULL)
        {
            delete[] sPicBuffer;
            sPicBuffer = NULL;
        }
        if (NET_DVR_GetLastError() == 43)
        {
            m_dwPicLen = m_dwPicLen * 2;
            OnBnClickedBtnCapturePictureV50();
        }
        else
        {
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_CapturePicture_V50");
            AfxMessageBox("NET_DVR_CapturePicture_V50 capture failed!");
        }
        return;
    }

    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
    if (lpSizeReturned > 0 && sPicBuffer != NULL)
    {
        char cFilename[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "calib");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpeg", cFilename, chTime, rand() % GetTickCount());

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, sPicBuffer, lpSizeReturned, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < lpSizeReturned)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "ID Card Info Picture Wtite to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, lpSizeReturned, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }
    if (sPicBuffer != NULL)
    {
        delete[] sPicBuffer;
        sPicBuffer = NULL;
    }

    return;
}
