// DlgCaptureFace.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgCaptureFace.h"
#include "afxdialogex.h"

#define  WM_CAPTURE_FACE_FINISH 1001

// CDlgCaptureFace 对话框

IMPLEMENT_DYNAMIC(CDlgCaptureFace, CDialog)

CDlgCaptureFace::CDlgCaptureFace(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCaptureFace::IDD, pParent)
{
    m_iFaceQuality = 0;
    m_iFaceQuality2 = 0;
}

CDlgCaptureFace::~CDlgCaptureFace()
{
}

void CDlgCaptureFace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_FACE_QUALITY, m_iFaceQuality);
    DDX_Text(pDX, IDC_EDIT_FACE_QUALITY2, m_iFaceQuality2);
}


BEGIN_MESSAGE_MAP(CDlgCaptureFace, CDialog)
    ON_BN_CLICKED(IDC_BTN_GET_FACE, &CDlgCaptureFace::OnBnClickedBtnGetFace)
    ON_MESSAGE(WM_CAPTURE_FACE_FINISH, OnMsgCaptureFaceFinish)
END_MESSAGE_MAP()

LRESULT CDlgCaptureFace::OnMsgCaptureFaceFinish(WPARAM wParam, LPARAM lParam)
{
    DWORD dwType = (DWORD)wParam;
    char szLan[256] = { 0 };

    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        LPNET_DVR_CAPTURE_FACE_CFG pStruCaptureFace = (LPNET_DVR_CAPTURE_FACE_CFG)lParam;

        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        char cFaceTem1name[256] = { 0 };
        char cFaceTem2name[256] = { 0 };
        char cFacePicname[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
        if (pStruCaptureFace->dwFaceTemplate1Size > 0 && pStruCaptureFace->pFaceTemplate1Buffer != NULL)
        {
            sprintf(cFaceTem1name, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIP);

            if (GetFileAttributes(cFaceTem1name) != FILE_ATTRIBUTE_DIRECTORY)
            {
                CreateDirectory(cFaceTem1name, NULL);
            }

            sprintf(cFaceTem1name, "%s\\LocalTime[%s]FaceTemplate1.dat", cFaceTem1name, chTime);

            HANDLE hFile = CreateFile(cFaceTem1name, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE)
            {
                return NULL;
            }
            DWORD dwRet = WriteFile(hFile, pStruCaptureFace->pFaceTemplate1Buffer, pStruCaptureFace->dwFaceTemplate1Size, &dwWrittenBytes, NULL);
            if (dwRet == 0 || dwWrittenBytes < pStruCaptureFace->dwFaceTemplate1Size)
            {
                DWORD dwError = GetLastError();
                g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Face Write to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, pStruCaptureFace->dwFaceTemplate1Size, dwWrittenBytes);
            }
            CloseHandle(hFile);
            hFile = NULL;
        }

        if (pStruCaptureFace->dwFaceTemplate2Size > 0 && pStruCaptureFace->pFaceTemplate2Buffer != NULL)
        {
            sprintf(cFaceTem2name, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIP);

            if (GetFileAttributes(cFaceTem2name) != FILE_ATTRIBUTE_DIRECTORY)
            {
                CreateDirectory(cFaceTem2name, NULL);
            }

            sprintf(cFaceTem2name, "%s\\LocalTime[%s]FaceTemplate2.dat", cFaceTem2name, chTime);

            HANDLE hFile = CreateFile(cFaceTem2name, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE)
            {
                return NULL;
            }
            DWORD dwRet = WriteFile(hFile, pStruCaptureFace->pFaceTemplate2Buffer, pStruCaptureFace->dwFaceTemplate2Size, &dwWrittenBytes, NULL);
            if (dwRet == 0 || dwWrittenBytes < pStruCaptureFace->dwFaceTemplate2Size)
            {
                DWORD dwError = GetLastError();
                g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Face Write to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, pStruCaptureFace->dwFaceTemplate2Size, dwWrittenBytes);
            }
            CloseHandle(hFile);
            hFile = NULL;
        }

        if (pStruCaptureFace->dwFacePicSize > 0 && pStruCaptureFace->pFacePicBuffer != NULL)
        {
            sprintf(cFacePicname, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIP);

            if (GetFileAttributes(cFacePicname) != FILE_ATTRIBUTE_DIRECTORY)
            {
                CreateDirectory(cFacePicname, NULL);
            }

            sprintf(cFacePicname, "%s\\LocalTime[%s]FacePicture.jpg", cFacePicname, chTime);

            HANDLE hFile = CreateFile(cFacePicname, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE)
            {
                return NULL;
            }
            DWORD dwRet = WriteFile(hFile, pStruCaptureFace->pFacePicBuffer, pStruCaptureFace->dwFacePicSize, &dwWrittenBytes, NULL);
            if (dwRet == 0 || dwWrittenBytes < pStruCaptureFace->dwFacePicSize)
            {
                DWORD dwError = GetLastError();
                g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Face Write to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, pStruCaptureFace->dwFacePicSize, dwWrittenBytes);
            }
            CloseHandle(hFile);
            hFile = NULL;
        }

        m_iFaceQuality = pStruCaptureFace->byFaceQuality1;
        m_iFaceQuality2 = pStruCaptureFace->byFaceQuality2;

        if (pStruCaptureFace->pFaceTemplate1Buffer != NULL)
        {
            delete[](pStruCaptureFace->pFaceTemplate1Buffer);
            pStruCaptureFace->pFaceTemplate1Buffer = NULL;
        }

        if (pStruCaptureFace->pFaceTemplate2Buffer != NULL)
        {
            delete[](pStruCaptureFace->pFaceTemplate2Buffer);
            pStruCaptureFace->pFaceTemplate2Buffer = NULL;
        }

        if (pStruCaptureFace->pFacePicBuffer != NULL)
        {
            delete[](pStruCaptureFace->pFacePicBuffer);
            pStruCaptureFace->pFacePicBuffer = NULL;
        }

        if (pStruCaptureFace != NULL)
        {
            delete pStruCaptureFace;
            pStruCaptureFace = NULL;
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

// CDlgCaptureFace 消息处理程序

void CALLBACK g_fCaptureFaceDataCallBack(DWORD dwType, void *pRecvDataBuffer, DWORD dwBufSize, void* pUserData)
{
    CDlgCaptureFace *pThis = (CDlgCaptureFace*)pUserData;
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
            g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_SUCC_T, "Capture Face CallBack");
			::PostMessage(hWnd,WM_CAPTURE_FACE_FINISH,(DWORD)dwTemp,dwType);
		}
		break;
    case NET_SDK_CALLBACK_TYPE_PROGRESS:
        g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_SUCC_T, "Capture Face CallBack Processing");
        break;
    case NET_SDK_CALLBACK_TYPE_DATA:
        {
            char *pDataBuf = new char[sizeof(NET_DVR_CAPTURE_FACE_CFG)];
            if (pDataBuf == NULL)
            {
                dwType = NET_SDK_CALLBACK_STATUS_FAILED;
                break;
            }
            memset(pDataBuf, 0, sizeof(NET_DVR_CAPTURE_FACE_CFG));
            memcpy(pDataBuf, pRecvDataBuffer, sizeof(NET_DVR_CAPTURE_FACE_CFG));
						
            LPNET_DVR_CAPTURE_FACE_CFG pCaptureFaceTemp = (NET_DVR_CAPTURE_FACE_CFG*)pDataBuf;
            pCaptureFaceTemp->pFaceTemplate1Buffer = NULL;
            pCaptureFaceTemp->pFaceTemplate2Buffer = NULL;
            pCaptureFaceTemp->pFacePicBuffer = NULL;
            LPNET_DVR_CAPTURE_FACE_CFG pCaptureFaceCfg = (NET_DVR_CAPTURE_FACE_CFG*)pRecvDataBuffer;
			
            if (pCaptureFaceTemp->byCaptureProgress != 100)
            {
                sprintf(szLan, "Device capture face progress is:[%d]", pCaptureFaceTemp->byCaptureProgress);
                g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_SUCC_T, szLan);
                return;
            }
            sprintf(szLan, "Device capture face progress is:[%d]", pCaptureFaceTemp->byCaptureProgress);

            if (pCaptureFaceCfg->dwFaceTemplate1Size != 0)
            {
                pCaptureFaceTemp->pFaceTemplate1Buffer = new char[pCaptureFaceCfg->dwFaceTemplate1Size];
                if (pCaptureFaceTemp->pFaceTemplate1Buffer == NULL)
				{
					return;
				}
                memset(pCaptureFaceTemp->pFaceTemplate1Buffer, 0, pCaptureFaceCfg->dwFaceTemplate1Size);
                memcpy(pCaptureFaceTemp->pFaceTemplate1Buffer, pCaptureFaceCfg->pFaceTemplate1Buffer, pCaptureFaceCfg->dwFaceTemplate1Size);
            }
            if (pCaptureFaceCfg->dwFaceTemplate2Size != 0)
            {
                pCaptureFaceTemp->pFaceTemplate2Buffer = new char[pCaptureFaceCfg->dwFaceTemplate2Size];
                if (pCaptureFaceTemp->pFaceTemplate2Buffer == NULL)
                {
                    return;
                }
                memset(pCaptureFaceTemp->pFaceTemplate2Buffer, 0, pCaptureFaceCfg->dwFaceTemplate2Size);
                memcpy(pCaptureFaceTemp->pFaceTemplate2Buffer, pCaptureFaceCfg->pFaceTemplate2Buffer, pCaptureFaceCfg->dwFaceTemplate2Size);
            }
            if (pCaptureFaceCfg->dwFacePicSize != 0)
            {
                pCaptureFaceTemp->pFacePicBuffer = new char[pCaptureFaceCfg->dwFacePicSize];
                if (pCaptureFaceTemp->pFacePicBuffer == NULL)
                {
                    return;
                }
                memset(pCaptureFaceTemp->pFacePicBuffer, 0, pCaptureFaceCfg->dwFacePicSize);
                memcpy(pCaptureFaceTemp->pFacePicBuffer, pCaptureFaceCfg->pFacePicBuffer, pCaptureFaceCfg->dwFacePicSize);
            }
            sprintf(szLan, "Capture Face Template1 Size[%d] Template2 Size[%d] Picture Size[%d]", pCaptureFaceCfg->dwFaceTemplate1Size, pCaptureFaceCfg->dwFaceTemplate2Size, pCaptureFaceCfg->dwFacePicSize);
 		    g_pMainDlg->AddLog(pThis->m_iDevIndex,OPERATION_SUCC_T,szLan);
            ::PostMessage(hWnd, WM_CAPTURE_FACE_FINISH, NET_SDK_CALLBACK_TYPE_DATA, (LONG)pDataBuf);
        }
        break;
    default:
        break;
        
	}
    
}

void CDlgCaptureFace::OnBnClickedBtnGetFace()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (m_lRemoteHandle >= 0)
    {
        NET_DVR_StopRemoteConfig(m_lRemoteHandle);
    }

    NET_DVR_CAPTURE_FACE_COND struCaptureFaceCond = { 0 };
    struCaptureFaceCond.dwSize = sizeof(struCaptureFaceCond);

    m_lRemoteHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_CAPTURE_FACE_INFO, &struCaptureFaceCond, sizeof(struCaptureFaceCond), g_fCaptureFaceDataCallBack, this);
    if (m_lRemoteHandle < 0)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_CAPTURE_FACE_INFO");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_CAPTURE_FACE_INFO");
    }
    UpdateData(FALSE);
    return;
}
