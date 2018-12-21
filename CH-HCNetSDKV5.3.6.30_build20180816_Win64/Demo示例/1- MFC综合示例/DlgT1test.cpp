// DlgT1test.cpp : implementation file
//

#include "stdafx.h"

#include "clientdemo.h"
#include "DlgT1test.h"
#include "HCNetSDK.h"

#if _MSC_VER < 1500
#include "iphlpapi.h"
#include "ipifcons.h"
#else
#include <ifmib.h>
#endif

#ifdef _WIN64
DWORD WINAPI GetIfEntry(IN OUT PMIB_IFROW   pIfRow)
{
	return 0;
}

DWORD WINAPI GetIfTable(
		   OUT    PMIB_IFTABLE pIfTable,
		   IN OUT PULONG       pdwSize,
		   IN     BOOL         bOrder
		   )
{
	return 0;
}
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_PROC_T1TEST_CALLBACK_EVENT WM_USER +1

void CALLBACK /*DATADOWNLOAD*/T1TestDownloadCallBack(LONG nDownloadHandle, DWORD dwDataType, void* pBuffer, DWORD dwBufSize, void *pUser)
{
	CDlgT1test *pThis = static_cast<CDlgT1test*>(pUser);
	DWORD dwTemp = dwDataType *100000 + dwBufSize;
	HWND hWnd = pThis->GetSafeHwnd();
	if (hWnd == NULL)
	{
		return;
	}
	::PostMessage(hWnd,WM_PROC_T1TEST_CALLBACK_EVENT,(WPARAM)dwTemp,(LPARAM)pBuffer);

//	T1Test->m_fileDown.Write(pBuffer, dwBufSize);
}

/////////////////////////////////////////////////////////////////////////////
// CDlgT1test dialog

CDlgT1test::CDlgT1test(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgT1test::IDD, pParent)
	,m_lDownloadHandle(-1)
{
	memset(&m_struDownload, 0, sizeof(m_struDownload));
	//{{AFX_DATA_INIT(CDlgT1test)
	m_iChannelNum = 0;
	m_iPortNum = 0;
	//}}AFX_DATA_INIT
}


void CDlgT1test::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgT1test)
	DDX_Control(pDX, IDC_COMBO_T1TEST_STATUS, m_comT1TestStatus);
	DDX_Control(pDX, IDC_EDIT3, m_editNetSpeed);
	DDX_Control(pDX, IDC_EDIT2, m_editInfo);
	DDX_Text(pDX, IDC_EDIT_CHAN_PORT, m_iChannelNum);
	DDX_Text(pDX, IDC_EDIT_T1_PORT, m_iPortNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgT1test, CDialog)
	//{{AFX_MSG_MAP(CDlgT1test)
	ON_BN_CLICKED(IDOK, OnStartT1TestClick)
	ON_BN_CLICKED(IDC_BTN_DEDAULT_SHUTDOWN, OnDefaultShutdownClick)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_MESSAGE(WM_PROC_T1TEST_CALLBACK_EVENT, OnMessT1TestEvent)
	ON_BN_CLICKED(IDC_BTN_GET_T1_STATUS, OnBtnGetStatus)
	ON_BN_CLICKED(IDC_BTN_SET_T1_STATUS, OnBtnSetStatus)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_RE_ACTIVE, &CDlgT1test::OnBnClickedBtnReActive)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgT1test message handlers

void CDlgT1test::OnStartT1TestClick() 
{
	// TODO: Add your control notification handler code here
	GetNetWorkStatus();
	m_strTiTestInfo = "";
	CString csStr;
	m_struDownload.lpDataCallBack = T1TestDownloadCallBack;
	m_struDownload.pUserData = this;
	m_lDownloadHandle = NET_DVR_StartT1Test(g_struDeviceInfo[m_iDeviceIndex].lLoginID, &m_struDownload);
	if (m_lDownloadHandle == -1)
	{
		csStr.Format("%s", "NET_DVR_StartT1Test FAILED");
		MessageBox(csStr);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartT1Test FAILED");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartT1Test SUCC");
		GetDlgItem(IDOK)->EnableWindow(false);
	}
}

void CDlgT1test::OnDefaultShutdownClick()
{
	char *pContent = "<T1TestCmd type=\"0\"/>";
	if (NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_T1_TEST_CMD, 0, pContent, strlen(pContent)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_T1_TEST_CMD SUCC");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_T1_TEST_CMD FAILED");
	}
}

void CDlgT1test::appendInfo(void* pBuffer, DWORD dwBufSize)
{
	char *pTemp = NULL;

// 	LONG stats = 0;
// 	BOOL bRet = NET_DVR_GetT1TestStatus(m_lDownloadHandle, &stats);
// 	if (!bRet)
// 	{
// 		CString csStr;
// 		csStr.Format("%s", "NET_DVR_GetT1TestStatus FAILED");
// 		MessageBox(csStr);
// 		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetT1TestStatus FAILED");
// 		return;
// 	}
// 	if (stats != 2)
// 	{
// 		GetDlgItem(IDOK)->EnableWindow(true);
// 		return;
// 	}
//     char *pTemp = NULL;

    TRY 
    {
        pTemp = new char[dwBufSize];
    }
    CATCH (CMemoryException, e)
    {
    	return;
    }
    END_CATCH
    if (pTemp != NULL)
    {
        memset(pTemp,0,dwBufSize);
        memcpy(pTemp, pBuffer,dwBufSize);
    }
    else
    {
        return;
    }

	char szT1TestInfo[2048] = {0};

	int iStrTiTestInfoLen = m_strTiTestInfo.GetLength();

	strcpy(szT1TestInfo, m_strTiTestInfo);

	strncat(szT1TestInfo, pTemp, dwBufSize);
	m_strTiTestInfo = szT1TestInfo;

	iStrTiTestInfoLen = m_strTiTestInfo.GetLength();

	//m_strTiTestInfo += pTemp;
    m_editInfo.SetWindowText(GetLineAndReplace(m_strTiTestInfo));
//	GetDlgItem(IDC_EDIT2)->SetWindowText(GetLineAndReplace(m_strTiTestInfo));
	int rowCount = m_editInfo.GetLineCount();
	m_editInfo.LineScroll(rowCount);
    if (pTemp != NULL)
    {
        delete []pTemp;
        pTemp = NULL;
    }
}

CString CDlgT1test::GetLineAndReplace(CString csStr)
{
	CString csStrResult = "";
	for (int count = 0; count < csStr.GetLength(); count++)
	{
		TCHAR c = csStr.GetAt(count);
		if ('\n' == c)
		{
			csStrResult += '\r';
		}
		csStrResult += c;
	}
	return csStrResult;
}

void CDlgT1test::GetNetWorkStatus()
{
	// Declare and initialize variables.

    // Declare and initialize variables.
    DWORD dwSize = 0;
    DWORD dwRetVal = 0;

    int i;

    /* variables used for GetIfTable and GetIfEntry */
    MIB_IFTABLE *pIfTable;
    MIB_IFROW *pIfRow;

    // Allocate memory for our pointers.
    pIfTable = (MIB_IFTABLE *) malloc(sizeof (MIB_IFTABLE));
    if (pIfTable == NULL) {
        printf("Error allocating memory needed to call GetIfTable\n");
    }
    // Before calling GetIfEntry, we call GetIfTable to make
    // sure there are entries to get and retrieve the interface index.

    // Make an initial call to GetIfTable to get the
    // necessary size into dwSize
    dwSize = sizeof (MIB_IFTABLE);
    if (GetIfTable(pIfTable, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER) {
        free(pIfTable);
        pIfTable = (MIB_IFTABLE *) malloc(dwSize);
        if (pIfTable == NULL) {
            printf("Error allocating memory\n");
            return;
        }
    }
    // Make a second call to GetIfTable to get the actual
    // data we want.
    if ((dwRetVal = GetIfTable(pIfTable, &dwSize, 0)) == NO_ERROR) {
        if (pIfTable->dwNumEntries > 0) {
            pIfRow = (MIB_IFROW *) malloc(sizeof (MIB_IFROW));
            if (pIfRow == NULL) {
                printf("Error allocating memory\n");
                if (pIfTable != NULL) {
                    free(pIfTable);
                    pIfTable = NULL;
                }
				return;
            }

			int count =  (int) pIfTable->dwNumEntries;

            for (i = 0; i < (int) pIfTable->dwNumEntries; i++) {
                pIfRow->dwIndex = pIfTable->table[i].dwIndex;
                if ((dwRetVal = GetIfEntry(pIfRow)) == NO_ERROR) {
					//if(pIfRow->dwOperStatus == MIB_IF_OPER_STATUS_CONNECTED)
					//if(pIfRow->dwAdminStatus == 1)
					if(pIfRow->dwPhysAddrLen != 0)
					{
						int dwSpeed = (pIfRow->dwSpeed) / 1000 / 1000;
						CString strSpeed;
						strSpeed.Format("%d Mbps", dwSpeed);
						m_editNetSpeed.SetWindowText(strSpeed);
					}
                }
            }
        } 

    }
}

void CDlgT1test::OnButton1() 
{
	// TODO: Add your control notification handler code here
	char *pContent = "<T1TestCmd type=\"1\"/>";
	if (NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_T1_TEST_CMD, 0, pContent, strlen(pContent)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_T1_TEST_CMD SUCC");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_T1_TEST_CMD FAILED");
	}
}

void CDlgT1test::OnButton2() 
{
	// TODO: Add your control notification handler code here
	char *pContent = "<T1TestCmd type=\"2\"/>";
	if (NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_T1_TEST_CMD, 0, pContent, strlen(pContent)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_T1_TEST_CMD SUCC");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_T1_TEST_CMD FAILED");
	}
}

void CDlgT1test::OnBtnGetStatus() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_T1TEST_PARAMCFG struT1TestParamCfg = {0};
	DWORD dwReturn = 0;
	char szLan[128] = {0};
	if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_GET_T1TEST_CFG, m_iChannelNum, &struT1TestParamCfg, sizeof(NET_DVR_T1TEST_PARAMCFG), &dwReturn))
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_T1TEST_CFG");
		g_StringLanType(szLan, "»ñÈ¡T1²âÊÔ×´Ì¬Ê§°Ü", "Get T1 Test status failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_T1TEST_CFG");
		g_StringLanType(szLan, "³É¹¦»ñÈ¡T1²âÊÔ×´Ì¬", "Get T1 Test status success");
		AfxMessageBox(szLan);
	}
	m_iPortNum = struT1TestParamCfg.wPort;
	m_comT1TestStatus.SetCurSel(struT1TestParamCfg.byPortState);

	UpdateData(FALSE);

}

void CDlgT1test::OnBtnSetStatus() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_T1TEST_PARAMCFG struT1TestParamCfg = {0};
	struT1TestParamCfg.dwSize = sizeof(NET_DVR_T1TEST_PARAMCFG);
	struT1TestParamCfg.wPort = m_iPortNum;
	struT1TestParamCfg.byPortState = m_comT1TestStatus.GetCurSel();
	char szLan[128] = {0};
	if (!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_SET_T1TEST_CFG, m_iChannelNum, &struT1TestParamCfg, sizeof(NET_DVR_T1TEST_PARAMCFG)))
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_SET_T1TEST_CFG");
		g_StringLanType(szLan, "ÉèÖÃT1²âÊÔ×´Ì¬Ê§°Ü", "Set T1 Test status failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_SET_T1TEST_CFG");
		g_StringLanType(szLan, "³É¹¦ÉèÖÃT1²âÊÔ×´Ì¬", "Set T1 Test status success");
		AfxMessageBox(szLan);
	}
	
}

BOOL CDlgT1test::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_comT1TestStatus.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


LRESULT CDlgT1test::OnMessT1TestEvent(WPARAM wParam, LPARAM lParam)
{

	DWORD dwTemp = (DWORD)wParam;   
	DWORD dwDataType =  dwTemp/100000;
	DWORD dwBufSize = dwTemp%100000;
	char *pBuffer = NULL;
	char *pBufferTemp = (char*)lParam;
	if (dwBufSize != 0)
	{
		pBuffer = new char[dwBufSize];
		if (pBuffer == NULL)
		{
			return 0;
		}

		memset(pBuffer,0,dwBufSize);
		memcpy(pBuffer,pBufferTemp,dwBufSize);

	}
	if (dwDataType == 5)
	{
		NET_DVR_T1TEST_SEND_DATA struSendData = {0};
		struSendData.dwSize = sizeof(NET_DVR_T1TEST_SEND_DATA);
		struSendData.byDataType = 0;
		char szCn[128] = "";
		char szEn[128] = "";
		char szErrInfo[128] = "";
		sprintf(szCn,"%s","ÊÇ·ñÌýµ½·äÃùÆ÷ÏìÉù£¬ÇëÈ·ÈÏ?");
		sprintf(szEn,"%s","Note: Do you hear the buzzer sound, continue? ");
		g_StringLanType(szErrInfo,szCn,szEn);
		if (AfxMessageBox(szErrInfo,MB_OKCANCEL) != IDOK)
		{
			struSendData.uSendData.struBuzzer.byHearSound = 0;
		}
		else
		{
			struSendData.uSendData.struBuzzer.byHearSound = 1;
		}
		if (!NET_DVR_SendT1TestData(m_lDownloadHandle,0,(char*)&struSendData,sizeof(struSendData)))
		{
			sprintf(szErrInfo,"Send T1Test Data Failed Error[%d]",NET_DVR_GetLastError());
			AfxMessageBox(szErrInfo);
		}
	}   
	else if (dwDataType == 6)
	{
		CTime timeCur = CTime::GetCurrentTime();

		//
		NET_DVR_T1TEST_SEND_DATA struSendData = {0};
		struSendData.dwSize = sizeof(NET_DVR_T1TEST_SEND_DATA);
		struSendData.byDataType = 1;
		struSendData.uSendData.struCurTime.wYear = timeCur.GetYear();
		struSendData.uSendData.struCurTime.byMonth = timeCur.GetMonth();
		struSendData.uSendData.struCurTime.byDay   = timeCur.GetDay();
		struSendData.uSendData.struCurTime.byHour  = timeCur.GetHour();
		struSendData.uSendData.struCurTime.byMinute = timeCur.GetMinute();
		struSendData.uSendData.struCurTime.bySecond = timeCur.GetSecond();

		if (!NET_DVR_SendT1TestData(m_lDownloadHandle,0,(char*)&struSendData,sizeof(struSendData)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex,OPERATION_FAIL_T,"NET_DVR_SendT1TestData Pc Time ");
			return 0;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex,OPERATION_SUCC_T,"NET_DVR_SendT1TestData Pc Time ");
		}
	}
	else if (dwDataType == 4)
	{
		appendInfo(pBuffer, dwBufSize);
	}
	else if (dwDataType == 0)
	{
		LONG stats = 0;
		BOOL bRet = NET_DVR_GetT1TestStatus(m_lDownloadHandle, &stats);
		if (!bRet)
		{
			CString csStr;
			csStr.Format("%s", "NET_DVR_GetT1TestStatus FAILED");
			AfxMessageBox(csStr);
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetT1TestStatus FAILED");
			return 0;
		}

		if (stats == 1 || stats == 3)
		{
			NET_DVR_StopTT1Test(m_lDownloadHandle);
			m_lDownloadHandle = -1;
			GetDlgItem(IDOK)->EnableWindow(TRUE);
			g_pMainDlg->AddLog(m_iDeviceIndex,OPERATION_SUCC_T,"NET_DVR_StopTT1Test!");
		}
		else if (stats == 2)
		{
			appendInfo(pBuffer, dwBufSize);
		}

	}

	if (pBuffer != NULL)
	{
		delete[] pBuffer;
		pBuffer = NULL;
	}

	return 1;
}

typedef struct tagNET_DVR_RESTORE_INACTIVE_CFG
{
    DWORD  dwSize;
    DWORD  dwChannel; 
    BYTE   byRes[64];
}NET_DVR_RESTORE_INACTIVE_CFG, *LPNET_DVR_RESTORE_INACTIVE_CFG;

#define NET_DVR_RESTORE_INACTIVE 100000

void CDlgT1test::OnBnClickedBtnReActive()
{
    NET_DVR_RESTORE_INACTIVE_CFG struActive = { 0 };
    struActive.dwSize = sizeof(NET_DVR_RESTORE_INACTIVE_CFG);
    if (NET_DVR_RemoteControl(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_RESTORE_INACTIVE, &struActive, sizeof(struActive)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_RESTORE_INACTIVE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_RESTORE_INACTIVE");
    }

}
