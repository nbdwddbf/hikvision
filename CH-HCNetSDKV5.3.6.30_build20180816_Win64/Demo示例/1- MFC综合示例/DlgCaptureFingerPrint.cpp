// DlgCaptureFingerPrint.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgCaptureFingerPrint.h"
#include "afxdialogex.h"

#define  WM_CAPTURE_FINGER_PRINT_FINISH 1001


// CDlgCaptureFingerPrint 对话框

IMPLEMENT_DYNAMIC(CDlgCaptureFingerPrint, CDialog)

CDlgCaptureFingerPrint::CDlgCaptureFingerPrint(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCaptureFingerPrint::IDD, pParent)
{
    m_iFingerNo = 0;
    m_iFingerPrintQuality = 0;
    m_iFingerNoReturn = 0;
}

CDlgCaptureFingerPrint::~CDlgCaptureFingerPrint()
{
}

void CDlgCaptureFingerPrint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_FINGER_PRINT_PIC_TYPE, m_cmbFingerPrintPicType);
    DDX_Text(pDX, IDC_EDIT_FINGER_NO, m_iFingerNo);
    DDX_Text(pDX, IDC_EDIT_FINGERPRINT_QUALITY, m_iFingerPrintQuality);
    DDX_Text(pDX, IDC_EDIT_FINGER_NO_RETURN, m_iFingerNoReturn);
}

BOOL CDlgCaptureFingerPrint::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_cmbFingerPrintPicType.SetCurSel(0);

    return TRUE;
}


BEGIN_MESSAGE_MAP(CDlgCaptureFingerPrint, CDialog)
    ON_BN_CLICKED(IDC_BTN_GET_FINGER_PRINT, &CDlgCaptureFingerPrint::OnBnClickedBtnGetFingerPrint)
    ON_MESSAGE(WM_CAPTURE_FINGER_PRINT_FINISH, OnMsgCaptureFingerPrintFinish)
END_MESSAGE_MAP()

LRESULT CDlgCaptureFingerPrint::OnMsgCaptureFingerPrintFinish(WPARAM wParam, LPARAM lParam)
{
    DWORD dwType = (DWORD)wParam;
    char szLan[256] = { 0 };

    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        LPNET_DVR_CAPTURE_FINGERPRINT_CFG pStruCaptureFingerPrint = (LPNET_DVR_CAPTURE_FINGERPRINT_CFG)lParam;

        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        char cFingerPicname[256] = { 0 };
        char cFingerDataname[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
        if (pStruCaptureFingerPrint->dwFingerPrintPicSize > 0 && pStruCaptureFingerPrint->pFingerPrintPicBuffer != NULL)
        {
            sprintf(cFingerPicname, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIP);
            
            if (GetFileAttributes(cFingerPicname) != FILE_ATTRIBUTE_DIRECTORY)
            {
                CreateDirectory(cFingerPicname, NULL);
            }

            sprintf(cFingerPicname, "%s\\LocalTime[%s]FingerPrintPicture.jpg", cFingerPicname, chTime);

            HANDLE hFile = CreateFile(cFingerPicname, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE)
            {
                return NULL;
            }
            DWORD dwRet = WriteFile(hFile, pStruCaptureFingerPrint->pFingerPrintPicBuffer, pStruCaptureFingerPrint->dwFingerPrintPicSize, &dwWrittenBytes, NULL);
            if (dwRet == 0 || dwWrittenBytes < pStruCaptureFingerPrint->dwFingerPrintPicSize)
            {
                DWORD dwError = GetLastError();
                g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Finger Print Write to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, pStruCaptureFingerPrint->dwFingerPrintPicSize, dwWrittenBytes);
            }
            CloseHandle(hFile);
            hFile = NULL;
        }

        if (pStruCaptureFingerPrint->dwFingerPrintDataSize > 0 && pStruCaptureFingerPrint->byFingerData != NULL)
        {
            sprintf(cFingerDataname, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIP);

            if (GetFileAttributes(cFingerDataname) != FILE_ATTRIBUTE_DIRECTORY)
            {
                CreateDirectory(cFingerDataname, NULL);
            }

            sprintf(cFingerDataname, "%s\\LocalTime[%s]FingerPrintData.txt", cFingerDataname, chTime);

            HANDLE hFile = CreateFile(cFingerDataname, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE)
            {
                return NULL;
            }
            DWORD dwRet = WriteFile(hFile, pStruCaptureFingerPrint->byFingerData, pStruCaptureFingerPrint->dwFingerPrintDataSize, &dwWrittenBytes, NULL);
            if (dwRet == 0 || dwWrittenBytes < pStruCaptureFingerPrint->dwFingerPrintDataSize)
            {
                DWORD dwError = GetLastError();
                g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Finger Print Write to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, pStruCaptureFingerPrint->dwFingerPrintDataSize, dwWrittenBytes);
            }
            CloseHandle(hFile);
            hFile = NULL;
        }

        m_iFingerNoReturn = pStruCaptureFingerPrint->byFingerNo;
        m_iFingerPrintQuality = pStruCaptureFingerPrint->byFingerPrintQuality;

        if (pStruCaptureFingerPrint->pFingerPrintPicBuffer != NULL)
        {
            delete[](pStruCaptureFingerPrint->pFingerPrintPicBuffer);
            pStruCaptureFingerPrint->pFingerPrintPicBuffer = NULL;
        }

        if (pStruCaptureFingerPrint != NULL)
        {
            delete pStruCaptureFingerPrint;
            pStruCaptureFingerPrint = NULL;
        }

        UpdateData(FALSE);
    }
    else
    {
        if (!NET_DVR_StopRemoteConfig(m_lRemoteHandle))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopRemoteConfig");
            m_lRemoteHandle = -1;
        }

    }

    return NULL;
}

// CDlgCaptureFingerPrint 消息处理程序

void CALLBACK g_fCaptureFingerPrintDataCallBack(DWORD dwType, void *pRecvDataBuffer, DWORD dwBufSize, void* pUserData)
{
    CDlgCaptureFingerPrint *pThis = (CDlgCaptureFingerPrint*)pUserData;
    DWORD dwTemp = 0;
	char szLan[128] = {0};

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
            g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_SUCC_T, "Capture Finger Print CallBack");
			::PostMessage(hWnd,WM_CAPTURE_FINGER_PRINT_FINISH,(DWORD)dwTemp,dwType);
		}
		break;
    case NET_SDK_CALLBACK_TYPE_PROGRESS:
        g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_SUCC_T, "Capture Finger Print CallBack Processing");
        break;
    case NET_SDK_CALLBACK_TYPE_DATA:
        {
            char *pDataBuf = new char[sizeof(NET_DVR_CAPTURE_FINGERPRINT_CFG)];
            if (pDataBuf == NULL)
            {
                dwType = NET_SDK_CALLBACK_STATUS_FAILED;
                break;
            }
            memset(pDataBuf, 0, sizeof(NET_DVR_CAPTURE_FINGERPRINT_CFG));
            memcpy(pDataBuf, pRecvDataBuffer, sizeof(NET_DVR_CAPTURE_FINGERPRINT_CFG));
						
            LPNET_DVR_CAPTURE_FINGERPRINT_CFG pCaptureFingerPrintTemp = (NET_DVR_CAPTURE_FINGERPRINT_CFG*)pDataBuf;
            pCaptureFingerPrintTemp->pFingerPrintPicBuffer = NULL;
            LPNET_DVR_CAPTURE_FINGERPRINT_CFG pCaptureFingerPrintCfg = (NET_DVR_CAPTURE_FINGERPRINT_CFG*)pRecvDataBuffer;
			
            if (pCaptureFingerPrintCfg->dwFingerPrintPicSize != 0)
            {
                pCaptureFingerPrintTemp->pFingerPrintPicBuffer = new char[pCaptureFingerPrintCfg->dwFingerPrintPicSize];
                if (pCaptureFingerPrintTemp->pFingerPrintPicBuffer == NULL)
				{
					return;
				}
                memset(pCaptureFingerPrintTemp->pFingerPrintPicBuffer, 0, pCaptureFingerPrintCfg->dwFingerPrintPicSize);
                memcpy(pCaptureFingerPrintTemp->pFingerPrintPicBuffer, pCaptureFingerPrintCfg->pFingerPrintPicBuffer, pCaptureFingerPrintCfg->dwFingerPrintPicSize);
            }
            sprintf(szLan, "Capture Finger Print Data Size[%d] Picture Size[%d]", pCaptureFingerPrintTemp->dwFingerPrintDataSize, pCaptureFingerPrintTemp->dwFingerPrintPicSize);
 		    g_pMainDlg->AddLog(pThis->m_iDevIndex,OPERATION_SUCC_T,szLan);
            ::PostMessage(hWnd, WM_CAPTURE_FINGER_PRINT_FINISH, NET_SDK_CALLBACK_TYPE_DATA, (LPARAM)pDataBuf);
        }
        break;
    default:
        break;
        
	}
    
}


void CDlgCaptureFingerPrint::OnBnClickedBtnGetFingerPrint()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (m_lRemoteHandle >= 0)
    {
        NET_DVR_StopRemoteConfig(m_lRemoteHandle);
    }

    NET_DVR_CAPTURE_FINGERPRINT_COND struCaptureFingerPrintCond = { 0 };
    struCaptureFingerPrintCond.dwSize = sizeof(struCaptureFingerPrintCond);
    struCaptureFingerPrintCond.byFingerPrintPicType = m_cmbFingerPrintPicType.GetCurSel();
    struCaptureFingerPrintCond.byFingerNo = m_iFingerNo;

    m_lRemoteHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_CAPTURE_FINGERPRINT_INFO, &struCaptureFingerPrintCond, sizeof(struCaptureFingerPrintCond), g_fCaptureFingerPrintDataCallBack, this);
    if (m_lRemoteHandle < 0)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_CAPTURE_FINGERPRINT_INFO");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_CAPTURE_FINGERPRINT_INFO");
    }
    UpdateData(FALSE);
    return;
}
