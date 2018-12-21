// MatPassive.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "MatPassive.h"
#ifdef SUPPORT_SCE
#include "SCE.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMatPassive *pClient = NULL;
/////////////////////////////////////////////////////////////////////////////
// CMatPassive dialog
DWORD dwReturn = 0;
int handle = 0;
#define COMMANDLEN 1024 


void CALLBACK DataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser)
{
	CString csStr;
	csStr.Format("data length = %d, PassiveHandlle = %d*************///**********\n", dwBufSize, g_struDeviceInfo[g_pMainDlg->GetCurDeviceIndex()].struPassiveDecode[dwUser].lPassiveHandle);
	OutputDebugString(csStr);
//	g_pMainDlg->AddLog(g_pMainDlg->GetCurDeviceIndex(), OPERATION_SUCC_T, csStr);
	if (!NET_DVR_MatrixSendData(g_struDeviceInfo[g_pMainDlg->GetCurDeviceIndex()].struPassiveDecode[dwUser].lPassiveHandle, (char*)pBuffer, dwBufSize))
	{
		//g_pMainDlg->AddLog(g_pMainDlg->GetCurDeviceIndex(), OPERATION_FAIL_T, csStr);
		csStr.Format("FAIL NET_DVR_MatrixSendData"); 
		OutputDebugString(csStr);
		return ; 
	}
	
}


#ifdef SUPPORT_SCE
void CALLBACK StreamCallBack(ENCODED_STREAM* pstStream, void* pUser)
{
	if (NULL == pstStream /*|| NULL == pUser*/)
	{
		return;
	}
	
	char *pMsg = new char[pstStream->nDataLen];
	if (NULL != pMsg)
	{
		memcpy(pMsg, pstStream->pData, pstStream->nDataLen);
	}

//	::PostMessage(pClient->m_hWnd, WM_DESKDATA, (DWORD)pstStream->nDataLen, (LONG)pMsg);
    Sleep(5);

	TRACE("pstStream->nDataLen = %d", pstStream->nDataLen);
// 	for(int i = 0; i < 16; i++)
// 	{
// 		if (pClient->m_lPassiveHandle[i] != -1)
// 		{
		    //NET_DVR_MatrixSendData(pClient->m_lPassiveHandle[0], (char*)pstStream->pData, pstStream->nDataLen);
			//OutputDebugString("desk~~~~~~~~~~~~~~~~~~~~~~~~~~");
// 		}
// 	}
#if 0
	DWORD dwReturn = 0;
//	WriteFile(pClient->m_hRecordHandle, (char*)pstStream->pData, pstStream->nDataLen, &dwReturn, NULL);
#endif
	//FILE *fp = (FILE *)pUser;
	//fwrite(pstStream->pData, 1, pstStream->nDataLen, fp);
}
#endif
int iStreamSize = 0;
BOOL bCycle = TRUE;
UINT GetFileStreamThread(LPVOID pParam)
{
    int *lpSel = (int *)pParam;
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    DWORD dwFileSize = GetFileSize(g_struDeviceInfo[iDeviceIndex].struPassiveDecode[*lpSel].hFileHandle, NULL);

    DWORD dwRealSize = 0;
	BOOL bReadFlag = TRUE;
    BOOL bNeedRead = TRUE;	
    BOOL bSendFlag = FALSE;
    
    char *tmpFile = new char[iStreamSize * COMMANDLEN];
    DWORD tmpSize = iStreamSize * COMMANDLEN;
    DWORD dwCount = 0;
	TRACE("100526---每次取流大小:%d,handle = %d\n", iStreamSize, *lpSel);
    
    while (1)
    {
        if (WaitForSingleObject(g_struDeviceInfo[iDeviceIndex].struPassiveDecode[*lpSel].hExitThread, 0) == WAIT_OBJECT_0)
        {
            break;
        }
        else if (bNeedRead)
        {
            if (!bSendFlag)
            {
                bReadFlag = ReadFile(g_struDeviceInfo[iDeviceIndex].struPassiveDecode[*lpSel].hFileHandle, tmpFile, tmpSize, &dwRealSize, NULL);
                dwCount += dwRealSize;
				//TRACE("100526---read size = %u\n", dwRealSize);
            }
            
            if (!bReadFlag)
            {
                //when bReadFlag id FALSE, that read file fail
                TRACE("100526---ReadFile failed!\n");
                break;
            }
            else if (dwRealSize > 0)
            {
                //when bReadFlag id TRUE and dwRealSize>0, that receive data
				if (!NET_DVR_MatrixSendData(g_struDeviceInfo[iDeviceIndex].struPassiveDecode[*lpSel].lPassiveHandle, tmpFile, dwRealSize))
				{				
					TRACE("1215---NET_DVR_MatrixSendData failed");
					bSendFlag = TRUE;
					Sleep(10);
				}
				else
				{
					bSendFlag = FALSE;
					Sleep(10);
				}
				
				Sleep(20);
            }
            else
            {
				dwCount = 0;
                CloseHandle(g_struDeviceInfo[iDeviceIndex].struPassiveDecode[*lpSel].hFileHandle);
                g_struDeviceInfo[iDeviceIndex].struPassiveDecode[*lpSel].hFileHandle = INVALID_HANDLE_VALUE;
                g_struDeviceInfo[iDeviceIndex].struPassiveDecode[*lpSel].hFileHandle = CreateFile(g_struDeviceInfo[iDeviceIndex].struPassiveDecode[*lpSel].strRecordFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                if (g_struDeviceInfo[iDeviceIndex].struPassiveDecode[*lpSel].hFileHandle == INVALID_HANDLE_VALUE)
                {
                    return 0;
                }
            }
            
            //TRACE("100526---count = %d, filesize = %d", dwCount, dwFileSize);
        }
    }//while (1)
        
	TRACE("100526---!!!!!!!!!!!!!!!over");
    CloseHandle(g_struDeviceInfo[iDeviceIndex].struPassiveDecode[*lpSel].hFileThread);
    g_struDeviceInfo[iDeviceIndex].struPassiveDecode[*lpSel].hFileThread = NULL;
    
    SetEvent(g_struDeviceInfo[iDeviceIndex].struPassiveDecode[*lpSel].hThreadExit);
	if (NULL != tmpFile)
	{
		delete []tmpFile;
		tmpFile = NULL;
	}
    return 0;
}
CMatPassive::CMatPassive(CWnd* pParent /*=NULL*/)
	: CDialog(CMatPassive::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatPassive)
	m_strMcastIp = _T("");
	m_dwPort = 9000;
	m_csUserName = _T("admin");
	m_csPsw = _T("12345");
	m_nLoginPort = 8000;
	m_strFilePath = _T("");
	m_bCycle = FALSE;
	m_iStreamSize = 0;
	//}}AFX_DATA_INIT
#ifdef SUPPORT_SCE
    m_lDevStartChan = -1; 
#endif
//     for(int i = 0; i < 32; i++)
//     {
//         m_lPassiveHandle[i] = -1;
//         m_lRealHandle[i] = -1;
//         m_lUserID[i] = -1;
//         m_lSel[i] = -1;
//         m_hFileThread[i] = NULL;
//         m_hFileHandle[i] = NULL;
//         m_hExitThread[i] = NULL;
//         m_hThreadExit[i] = NULL;
//         m_strRecordFilePath[i] = "";
//     }
}
#ifdef SUPPORT_SCE
HANDLE CMatPassive::m_hDeskHandle = NULL;
#endif
#if SUPPORT_WRITEFILE
HANDLE CMatPassive::m_hRecordHandle = NULL;
HANDLE CMatPassive::m_hRecordHandle1 = NULL;
#endif
// LONG CMatPassive::m_lPassiveHandle[32] = {-1};
// 
// LONG CMatPassive::m_lRealHandle[32] = {-1};
// LONG CMatPassive::m_lUserID[32] = {-1};
// LONG CMatPassive::m_lSel[32] = {-1};
// HANDLE CMatPassive::m_hFileThread[32] = {NULL};
// HANDLE CMatPassive::m_hFileHandle[32] = {NULL};
// HANDLE CMatPassive::m_hExitThread[32] = {NULL};
// HANDLE CMatPassive::m_hThreadExit[32] = {NULL};
// CString CMatPassive::m_strRecordFilePath[32] = {""};

void CMatPassive::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatPassive)
	DDX_Control(pDX, IDC_COMBOSTREAMTYPE, m_comboStreamType);
	DDX_Control(pDX, IDC_COMBOGETSTREAMMODE, m_GetStreamModeCtrl);
	DDX_Control(pDX, IDC_COMBODEVCHAN, m_DevChanCtrl);
	DDX_Control(pDX, IDC_DEVICE_IP, m_ctrlDeviceIP);
	DDX_Control(pDX, IDC_COMBOTRANPRO, m_ComboTranPro);
	DDX_Control(pDX, IDC_COMBODECCHAN, m_DecChanCombo);
	DDX_Text(pDX, IDC_PORT, m_dwPort);
	DDX_Text(pDX, IDC_DEVICE_USERNAME, m_csUserName);
	DDX_Text(pDX, IDC_DEVICE_PSW, m_csPsw);
	DDX_Text(pDX, IDC_DEVICE_PORT, m_nLoginPort);
	DDX_Text(pDX, IDC_EDIT_FILEPATH, m_strFilePath);
	DDX_Check(pDX, IDC_CHECK_CYCLE, m_bCycle);
	DDX_Text(pDX, IDC_EDIT_STREAMSIZE, m_iStreamSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMatPassive, CDialog)
	//{{AFX_MSG_MAP(CMatPassive)
	ON_CBN_SELCHANGE(IDC_COMBODECCHAN, OnSelchangeCombodecchan)
	ON_BN_CLICKED(IDC_SURE, OnSure)
	ON_CBN_SELCHANGE(IDC_COMBOTRANPRO, OnSelchangeCombotranpro)
	ON_BN_CLICKED(IDC_STOPPASSIVEDECODE, OnStoppassivedecode)
	ON_BN_CLICKED(IDC_SENDDATA, OnSenddata)
	ON_BN_CLICKED(IDC_STOPSENDDATA, OnStopsenddata)
	ON_BN_CLICKED(IDC_LOGIN, OnLogin)
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_PAUSE, OnBtnPause)
	ON_BN_CLICKED(IDC_BTN_RESUME, OnBtnResume)
	ON_BN_CLICKED(IDC_BTN_FAST, OnBtnFast)
	ON_BN_CLICKED(IDC_BTN_AUDIOOFF, OnBtnAudiooff)
	ON_BN_CLICKED(IDC_BTN_AUDIOON, OnBtnAudioon)
	ON_BN_CLICKED(IDC_BTN_NORMAL, OnBtnNormal)
	ON_BN_CLICKED(IDC_BTN_ONEBYONE, OnBtnOnebyone)
	ON_BN_CLICKED(IDC_BTN_SLOW, OnBtnSlow)
	ON_WM_TIMER()
	ON_MESSAGE(WM_DESKDATA, DeskDataSend)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatPassive message handlers
LRESULT CMatPassive::DeskDataSend(WPARAM wParam, LPARAM lParam)
{
    char *pStream = (char *)(lParam);
#if SUPPORT_WRITEFILE
    DWORD dwReturn = 0;
    WriteFile(m_hRecordHandle1, (char*)pStream, wParam, &dwReturn, NULL);
#endif
    BOOL bSendSucc = NET_DVR_MatrixSendData(g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[0].lPassiveHandle, pStream, (DWORD)wParam);
    
//     BOOL bSendFlag = TRUE;
//     int iTimes = 0;
//     while(bSendFlag)
//     {
//         if (iTimes++ > 5)
//         {
//             break;
//         }
//         if (!NET_DVR_MatrixSendData(pClient->m_lPassiveHandle[0], pStream, (DWORD)wParam))
//         {				
//             TRACE("1215---NET_DVR_MatrixSendData failed");
//             bSendFlag = TRUE;
//             Sleep(10);
//         }
//         else
//         {
//             bSendFlag = FALSE;
//             Sleep(10);
//         }
//     }
    CString tmp;
    tmp.Format("NET_DVR_MatrixSendData length:%d", wParam);
    OutputDebugString(tmp);
#if SUPPORT_WRITEFILE

    if (bSendSucc)
    {
        WriteFile(m_hRecordHandle, (char*)pStream, wParam, &dwReturn, NULL);
    }
    else
    {
        tmp.Format("NET_DVR_MatrixSendData failed!:%d", NET_DVR_GetLastError());
        OutputDebugString(tmp);
    }
#endif
    if (pStream != NULL)
    {
        delete []pStream;
		pStream =  NULL;
	}
	return 0;
}
BOOL CMatPassive::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    pClient = this;

	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    DWORD chanNum = 0;
    CString tmp;
    int i;
    m_ComboTranPro.InsertString(0, "TCP");
    m_ComboTranPro.InsertString(1, "UDP");
    for (i = 0; i < m_iChannelNumber; i++)
    {
        chanNum = i + m_lStartChan;
        tmp.Format("%d", chanNum);
        m_DecChanCombo.AddString(tmp);   
    }

	for (i = 0; i < 64; i++)
    {
        chanNum = i + m_lStartChan;
        tmp.Format("%d", chanNum); 
        m_DevChanCtrl.InsertString(i, tmp);
    }
    
    m_ctrlDeviceIP.SetAddress(172, 9, 6, 132);
    m_DecChanCombo.SetCurSel(0);
    m_DevChanCtrl.SetCurSel(0);
    m_GetStreamModeCtrl.SetCurSel(0);
    m_ComboTranPro.SetCurSel(0);
    m_comboStreamType.SetCurSel(0);
    SetTimer(NULL, 200, NULL);
    UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMatPassive::OnExit() 
{
//	OnStoppassivedecode();
    CDialog::OnCancel();
}

void CMatPassive::OnSelchangeCombodecchan() 
{
    
}

void CMatPassive::OnSure() 
{
    UpdateData(TRUE);    
	if ((m_dwPort < 1024 || m_dwPort > 65535) && m_ComboTranPro.GetCurSel() == 1)
    {
		AfxMessageBox("端口号错误");
		return;
    }

	int sel = m_DecChanCombo.GetCurSel();

    if (g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[sel].lPassiveHandle >= 0)
    {
        MessageBox("Passive decode already start, please stop firstly");
        return;
    }
    m_PassiveMode.wTransProtol = m_ComboTranPro.GetCurSel();
    m_PassiveMode.wPassivePort = m_dwPort;
#ifdef SUPPORT_SCE
	if (m_bDesk)
	{
		m_PassiveMode.byStreamType = 1;
	}
	else
#endif
	{
		m_PassiveMode.byStreamType = m_comboStreamType.GetCurSel() + 1;//码流类型，1-实时流，2-文件流
	}
    //int iChann=0x01010001;
#ifdef SUPPORT_SCE
	if (m_bDesk)
	{
        g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[0].lPassiveHandle = NET_DVR_MatrixStartPassiveDecode(m_lServerID, m_DecChanCombo.GetCurSel() + m_lStartChan, &m_PassiveMode);
	}
	else
#endif
	{
        g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[sel].lPassiveHandle = NET_DVR_MatrixStartPassiveDecode(m_lServerID, m_DecChanCombo.GetCurSel() + m_lStartChan, &m_PassiveMode);
	}
    if (g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[sel].lPassiveHandle >= 0)
    {
        MessageBox("Start Passive Decode Success");
    }
	else
	{
		MessageBox("Start Passive Decode Failed");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Start Passive Decode Failed");
	}
}

void CMatPassive::OnSelchangeCombotranpro() 
{
	// TODO: Add your control notification handler code here
}

void CMatPassive::OnStoppassivedecode() 
{
    UpdateData(TRUE);
	CString csStr;
	DWORD dwSelIndex = m_DecChanCombo.GetCurSel();
	csStr.Format("%s", "GET IN OnStoppassivedecode**********+++*************\n");
	OutputDebugString(csStr);
    if (g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lRealHandle >= 0)
    {
		NET_DVR_SetRealDataCallBack(g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lRealHandle, NULL, m_DecChanCombo.GetCurSel());
		csStr.Format("%s", "SetRealDataCallBack To NULL*********+++**************\n");
		OutputDebugString(csStr);
		if (!NET_DVR_StopRealPlay(g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lRealHandle))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopRealPlay FAILED");
			csStr.Format("NET_DVR_StopRealPlay FAILED, ERR=%d**********+++*********\n", NET_DVR_GetLastError());
			OutputDebugString(csStr);
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopRealPlay SUCC");
			csStr.Format("%s", "NET_DVR_StopRealPlay SUCC*********+++***********\n");
			OutputDebugString(csStr);
			g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lRealHandle = -1;
        }
    }
	if (g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lUserID >= 0)
	{
		if (!NET_DVR_Logout(g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lUserID))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_Logout FAILED");
			csStr.Format("NET_DVR_Logout FAILED ERR = %d*********+++***********\n", NET_DVR_GetLastError());
			OutputDebugString(csStr);
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_Logout SUCC");
			csStr.Format("%s", "NET_DVR_Logout SUCC**********+++**********\n");
			OutputDebugString(csStr);
			g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lUserID = -1;
		}
     }  
    if (g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].hFileThread != NULL)
    {
        SetEvent(g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].hExitThread);
        WaitForSingleObject(g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].hThreadExit, INFINITE);
		g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].hFileHandle = NULL;
        TRACE("### Wait for Thread Exit...\n");
    }
	int i = m_DecChanCombo.GetCurSel();
#ifdef SUPPORT_SCE
	if (m_bDesk)
	{
		i = 0;
	}
#endif
    if (!NET_DVR_MatrixStopPassiveDecode(g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[i].lPassiveHandle))
    {
		csStr.Format("NET_DVR_MatrixStopPassiveDecode FAILED, ERR = %d*********+++***************\n", NET_DVR_GetLastError());
		OutputDebugString(csStr);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MatrixStopPassiveDecode FAILED");
        //return;
    }
    else
    {
		AfxMessageBox("Stop Passive decode success");
		csStr.Format("%s", "NET_DVR_MatrixStopPassiveDecode SUCC***********+++*************\n");
		OutputDebugString(csStr);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MatrixStopPassiveDecode SUCC");
		g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lPassiveHandle = -1; 
	}    
#ifdef SUPPORT_SCE
	if (m_hDeskHandle != NULL)
	{
		
		int	ret = SCE_Stop(m_hDeskHandle);
		if (ret != SCE_OK)
		{
			MessageBox("SCE_Stop error\n");
		}
		
		SCE_DestroyHandle(m_hDeskHandle);
		m_hDeskHandle = NULL;
	}
#endif
#ifdef SUPPORT_WRITEFILE
    if (m_hRecordHandle != NULL)
    {
        CloseHandle(m_hRecordHandle);
        m_hRecordHandle = NULL;
    }
    if (m_hRecordHandle1 != NULL)
    {
        CloseHandle(m_hRecordHandle1);
        m_hRecordHandle1 = NULL;
    }
#endif
}
int user = 0;
void CMatPassive::OnSenddata() 
{	
    UpdateData(TRUE);
	DWORD dwSelIndex = m_DecChanCombo.GetCurSel();
    if (g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lPassiveHandle < 0)
    {
        MessageBox("Please start passive decode first!");
        return;
    }
    
    int sel = m_DecChanCombo.GetCurSel();
    int chan = m_DevChanCtrl.GetCurSel();

    if (m_comboStreamType.GetCurSel() == 0 /*&& !m_bDesk*/)
    {
		OnLogin();
        if (g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lRealHandle < 0)
        {
            
            NET_DVR_CLIENTINFO ClientInfo;
            memset(&ClientInfo, 0, sizeof(NET_DVR_CLIENTINFO));
            ClientInfo.lChannel = chan + m_lDevStartChan;
            ClientInfo.hPlayWnd = NULL;
            NET_DVR_NETCFG_V30 netcfg;
            DWORD dwReturn = 0;
            memset(&netcfg, 0, sizeof(netcfg));
            if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lUserID, NET_DVR_GET_NETCFG_V30, -1, &netcfg, sizeof(netcfg), &dwReturn))
            {
                MessageBox("Get Netcfg Failed!");
                return;
            }
            ClientInfo.sMultiCastIP = netcfg.struMulticastIpAddr.sIpV4;
            ClientInfo.lLinkMode = m_GetStreamModeCtrl.GetCurSel();
			user = sel;
            g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lRealHandle = NET_DVR_RealPlay_V30(g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lUserID, &ClientInfo, NULL/*DataCallBack*/, NULL/*&user*/, 1);
			//m_lPlayHandle = NET_DVR_RealPlay_V30(g_struDeviceInfo[iDeviceIndex].lLoginID, &struPlayInfo, g_RealDataCallBack_V30, &m_iSubWndIndex, g_struLocalParam.bPreviewBlock);
			
            if (g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lRealHandle < 0)
            {
                MessageBox("realplay failed");
            }
//			NET_DVR_SetStandardDataCallBack(g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lRealHandle, DataCallBack, sel);
			NET_DVR_SetRealDataCallBack(g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lRealHandle, DataCallBack, sel);
        }
    }
#ifdef SUPPORT_SCE
	else if (m_bDesk)
	{
		if (m_hDeskHandle != NULL)
		{
			return;
        }
#ifdef SUPPORT_WRITEFILE
        m_hRecordHandle = CreateFile("D:\\deskrecord_发送成功.mp4", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        m_hRecordHandle1 = CreateFile("D:\\deskrecord_原始桌面码流.mp4", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
#endif
        m_hDeskHandle = SCE_CreateHandle();
		if (NULL == m_hDeskHandle)
		{
			MessageBox("SCE_ERROR: failed to create handle\n");
			SCE_DestroyHandle(m_hDeskHandle);
		}

		int ret = SCE_RegisterStreamCallBack(m_hDeskHandle, StreamCallBack, &sel);
		if (ret != SCE_OK)
		{
			MessageBox("SCE_RegisterStreamCallBack ERROR\n");
		}
        ENCODED_STREAM_PARA stream_para = {0};
        stream_para.nFPSHigh = 0; 
        stream_para.nFPSLow  = m_iFrameRate;
        // capture the whole desktop
        stream_para.stRect.x = m_iX;
        stream_para.stRect.y = m_iY;
        stream_para.stRect.nWidth = m_iW;
        stream_para.stRect.nHeight = m_iH;
        // set resolution
        stream_para.nWidth = m_iRw;
        stream_para.nHeight = m_iRh;
        // rate control
        stream_para.nRateMin = m_iMiniRate;
        stream_para.nBitRate = m_iAveRate;
        stream_para.nRateMax = m_iMAxRate;
		
		ret = SCE_SetStreamPara(m_hDeskHandle, &stream_para);
		if (ret != SCE_OK)
		{
			MessageBox("SCE_SetStreamPara ERROR\n");
		}
		ret = SCE_Start(m_hDeskHandle);
		if (ret != SCE_OK)
		{
			MessageBox("SCE_Start ERROR\n");
		}
	}
#endif
    else if (m_comboStreamType.GetCurSel() == 1)
    {
		if (m_iStreamSize < 1 || m_iStreamSize > 150)
		{
			//MessageBox("请选择合适的大小");
			return;
		}
		iStreamSize = m_iStreamSize;
		bCycle = !m_bCycle;
        g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[sel].hExitThread = CreateEvent(NULL, TRUE, FALSE, NULL);
	    
		g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[sel].hThreadExit = CreateEvent(NULL, TRUE, FALSE, NULL);
        g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[sel].strRecordFilePath = m_strFilePath;
        g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[sel].hFileHandle = CreateFile(g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[sel].strRecordFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[sel].hFileHandle == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwThreadId;
        g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[sel].lSel = m_DecChanCombo.GetCurSel();
        if (g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[sel].hFileThread == NULL)
        {
            g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[sel].hFileThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetFileStreamThread), (LPVOID)&g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[sel].lSel, 0, &dwThreadId);		
        }
        if (g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[sel].hFileThread == NULL)
        {
            AfxMessageBox("Open thread failed!");
            return;
		}
    }
}

void CMatPassive::OnStopsenddata() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	DWORD dwSelIndex = m_DecChanCombo.GetCurSel();
    if (g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lRealHandle < 0)
    {
        MessageBox("Send data net started!");
        return;
    }

    if (m_comboStreamType.GetCurSel() == 0)
    {
        NET_DVR_SetRealDataCallBack(g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lRealHandle, NULL, 0);
        
        if (g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lRealHandle >= 0)
        {
            NET_DVR_StopRealPlay(g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lRealHandle);
            g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lRealHandle = -1;
        }
        
        if (g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lUserID >= 0)
        {
            NET_DVR_Logout(g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lUserID);
        }
        
        g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lUserID = -1;
    }

}

void CMatPassive::OnLogin() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	DWORD dwSelIndex = m_DecChanCombo.GetCurSel();
    if (g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lPassiveHandle < 0)
    {
        MessageBox("Please start passive decode first!");
        return;
    }
    
    if (g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lUserID < 0)
    {
        DWORD dwDeviceIP;
        char szDeviceIP[16] = {0};
        char cUserName[100] = {0};
        char cPassword[100] = {0};
        NET_DVR_DEVICEINFO_V30 struDeviceInfo;//the info gotten when login
        
        DWORD dwReturned = 0;
        CString csTemp;
        int nErr = 0;
        int i = 0;
        
        if (m_ctrlDeviceIP.IsBlank())
        {
            char szLan[1024] = {0};
            g_StringLanType(szLan, "请输入设备地址!", "please input the device ip!");
            AfxMessageBox(szLan);
            return;
        }
        
        if (m_nLoginPort <= 0)
        {
            char szLan[1024] = {0};
            g_StringLanType(szLan, "非法的端口号!", "illeage port!");
            AfxMessageBox(szLan);
            return;
        }
        
        if ((strlen(m_csUserName) > 16) || (strlen(m_csPsw) > 16))
        {
            char szLan[1024] = {0};
            g_StringLanType(szLan, "用户名和密码不能超过16位!", "user name and pwd should be shorter than 16 BYTES!");
            AfxMessageBox(szLan);
            return;
        }
        
        m_ctrlDeviceIP.GetAddress(dwDeviceIP);
        csTemp = IPToStr(dwDeviceIP);
        sprintf(szDeviceIP, "%s", csTemp.GetBuffer(0));
        strncpy(cUserName, m_csUserName, MAX_NAMELEN);
        strncpy(cPassword, m_csPsw, PASSWD_LEN);
        memset(&struDeviceInfo, 0, sizeof(NET_DVR_DEVICEINFO_V30));    
        
        g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lUserID = NET_DVR_Login_V30(szDeviceIP, m_nLoginPort, cUserName, cPassword, &struDeviceInfo);
        if (g_struDeviceInfo[pClient->m_iDeviceIndex].struPassiveDecode[dwSelIndex].lUserID < 0)
        {
            nErr = NET_DVR_GetLastError();
            g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_Login_V30[%s]", szDeviceIP);
            if (nErr == NET_DVR_PASSWORD_ERROR)
            {
                char szLan[1024] = {0};
                g_StringLanType(szLan, "用户名密码错误!", "user name or password error!");
                AfxMessageBox(szLan);
            }
            else
            {
                char szLan[1024] = {0};
                g_StringLanType(szLan, "由于网络原因或DVR忙, 注册失败!", "net error or dvr is busy!");
                AfxMessageBox(szLan);
            }
            return;
        }
        m_lDevStartChan = struDeviceInfo.byStartChan;

    }
    UpdateData(FALSE);
}

void CMatPassive::OnBtnBrowse() 
{
	UpdateData(TRUE);
    static char szFilter[] = "All File(*.mp4*)|*.mp4*||";
    CFileDialog dlg(TRUE,"*.mp4*","record.mp4",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
        szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_strFilePath = dlg.GetPathName();
        UpdateData(FALSE);
	}	
}

void CMatPassive::OnBtnPause() 
{
    UpdateData(TRUE);
    NET_DVR_PASSIVEDECODE_CONTROL tmp = {0};
    tmp.dwSize = sizeof(tmp);
    tmp.dwPlayCmd = PASSIVE_DEC_PAUSE;
	if (NET_DVR_MatrixPassiveDecodeControl(m_lServerID, m_DecChanCombo.GetCurSel() + m_lStartChan, &tmp))
	{
        MessageBox("Play Pause success!");
	}
    else
    {
        MessageBox("Play Pause failed!");
    }	
}

void CMatPassive::OnBtnResume() 
{
    UpdateData(TRUE);
    NET_DVR_PASSIVEDECODE_CONTROL tmp = {0};
    tmp.dwSize = sizeof(tmp);
    tmp.dwPlayCmd = PASSIVE_DEC_RESUME;
    if (NET_DVR_MatrixPassiveDecodeControl(m_lServerID, m_DecChanCombo.GetCurSel() + m_lStartChan, &tmp))
    {
        MessageBox("Play Resume success!");
    }
    else
    {
        MessageBox("Play Resume failed!");
    }
}

void CMatPassive::OnBtnFast() 
{
    UpdateData(TRUE);
    NET_DVR_PASSIVEDECODE_CONTROL tmp = {0};
    tmp.dwSize = sizeof(tmp);
    tmp.dwPlayCmd = PASSIVE_DEC_FAST;
    if (NET_DVR_MatrixPassiveDecodeControl(m_lServerID, m_DecChanCombo.GetCurSel() + m_lStartChan, &tmp))
    {
        MessageBox("Play Fast success!");
    }
    else
    {
        MessageBox("Play Fast failed!");
    }
}

void CMatPassive::OnBtnAudiooff() 
{
    UpdateData(TRUE);
    NET_DVR_PASSIVEDECODE_CONTROL tmp = {0};
    tmp.dwSize = sizeof(tmp);
    tmp.dwPlayCmd = PASSIVE_DEC_AUDIO_OFF;
    if (NET_DVR_MatrixPassiveDecodeControl(m_lServerID, m_DecChanCombo.GetCurSel() + m_lStartChan, &tmp))
    {
        MessageBox("Play Audio Off success!");
    }
    else
    {
        MessageBox("Play Audio Off failed!");
    }
}

void CMatPassive::OnBtnAudioon() 
{
    UpdateData(TRUE);
    NET_DVR_PASSIVEDECODE_CONTROL tmp = {0};
    tmp.dwSize = sizeof(tmp);
    tmp.dwPlayCmd = PASSIVE_DEC_AUDIO_ON;
    if (NET_DVR_MatrixPassiveDecodeControl(m_lServerID, m_DecChanCombo.GetCurSel() + m_lStartChan, &tmp))
    {
        MessageBox("Play Audio on success!");
    }
    else
    {
        MessageBox("Play Audio on Success!");
    }
}

void CMatPassive::OnBtnNormal() 
{
    UpdateData(TRUE);
    NET_DVR_PASSIVEDECODE_CONTROL tmp = {0};
    tmp.dwSize = sizeof(tmp);
    tmp.dwPlayCmd = PASSIVE_DEC_NORMAL;
    if (NET_DVR_MatrixPassiveDecodeControl(m_lServerID, m_DecChanCombo.GetCurSel() + m_lStartChan, &tmp))
    {
        MessageBox("PlayNormal success!");
    }
    else
    {
        MessageBox("PlayNormal failed!");
    }
}

void CMatPassive::OnBtnOnebyone() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_PASSIVEDECODE_CONTROL tmp = {0};
    tmp.dwSize = sizeof(tmp);
    tmp.dwPlayCmd = PASSIVE_DEC_RESETBUFFER;
    if (NET_DVR_MatrixPassiveDecodeControl(m_lServerID, m_DecChanCombo.GetCurSel() + m_lStartChan, &tmp))
    {
        MessageBox("ResetBuffer success!");
    }
    else
    {
        MessageBox("ResetBuffer failed!");
    }
}

void CMatPassive::OnBtnSlow() 
{
    UpdateData(TRUE);
    NET_DVR_PASSIVEDECODE_CONTROL tmp = {0};
    tmp.dwSize = sizeof(tmp);
    tmp.dwPlayCmd = PASSIVE_DEC_SLOW;
    if (NET_DVR_MatrixPassiveDecodeControl(m_lServerID, m_DecChanCombo.GetCurSel() + m_lStartChan, &tmp))
    {
        MessageBox("Slow play success!");
    }
    else
    {
        MessageBox("Slow play failed!");
    }
}

#if (_MSC_VER >= 1500)	//vs2008
void CMatPassive::OnTimer(UINT_PTR nIDEvent)
#else
void CMatPassive::OnTimer(UINT nIDEvent)
#endif
{
	CDialog::OnTimer(nIDEvent);
}


