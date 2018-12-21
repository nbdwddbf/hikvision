// DlgPassiveTransCode.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPassiveTransCode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgOutput g_passiveWin;
//int test = 0;
BOOL bCycleRead = TRUE;
DWORD dwStreamSize = 0;
/////////////////////////////////////////////////////////////////////////////
// CDlgPassiveTransCode dialog

UINT PassiveTransFileThread(LPVOID pParam)
{
	CDlgPassiveTransCode *ptr = (CDlgPassiveTransCode *)pParam;

	DWORD dwRealSize = 0;
	BOOL bReadFlag = TRUE;
	BOOL bNeedRead = TRUE;	
    BOOL bSendFlag = FALSE;
	DWORD dwCount = 0;
    
    char *tmpFile = new char[dwStreamSize * 1024];
    DWORD tmpSize = dwStreamSize * 1024;

	while (WaitForSingleObject(ptr->m_hExitFileThread, 0) != WAIT_OBJECT_0)
	{
		if (WAIT_OBJECT_0 == WaitForSingleObject(ptr->m_hSendEvent, 0))
		{
			if (!bSendFlag)
			{
				if (ptr->m_bNeedSendAgain)
				{
					memcpy(tmpFile, ptr->m_pFileData, 40);
					dwCount += 40;
                    dwRealSize = 40;
					ptr->m_bNeedSendAgain = FALSE;
				}
				else
				{
					bReadFlag = ReadFile(ptr->m_hSrcFile, tmpFile, tmpSize, &dwRealSize, NULL);
					dwCount += dwRealSize;
				}				
			}
			
			if (!bReadFlag)
            {
                //when bReadFlag id FALSE, that read file fail
                TRACE("100526---ReadFile failed!\n");
                break;
            }
            else if (dwRealSize > 0)
            {
				if (!NET_DVR_TransCodeInputData(ptr->m_lPassiveTransHandle, (unsigned char*)tmpFile, tmpSize))
				{
					bSendFlag = TRUE;
					Sleep(10);
				}
				else
				{
					DWORD dwReturn = 0;
					if (ptr->m_bSavePreFile)
					{
						WriteFile(ptr->m_hFilePre, tmpFile, tmpSize, &dwReturn, NULL);
					}
					bSendFlag = FALSE;
					Sleep(10);
				}
				
				Sleep(20);
            }
            else if (bCycleRead)            
            {
				dwCount = 0;
                CloseHandle(ptr->m_hSrcFile);
                ptr->m_hSrcFile = INVALID_HANDLE_VALUE;
                ptr->m_hSrcFile = CreateFile(ptr->m_csFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                if (ptr->m_hSrcFile == INVALID_HANDLE_VALUE)
                {
					break;
                }
            }
			else
			{
				break;
			}
		}
		else
		{
			Sleep(20);
		}

	}

	if (NULL != tmpFile)
	{
		delete []tmpFile;
		tmpFile = NULL;
	}

	return 0;
}

void CALLBACK PassiveDataCallBack(LONG lPassiveHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void* pUser)
{
	CDlgPassiveTransCode *ptr = (CDlgPassiveTransCode *)pUser;
	
	DWORD dwReturn = 0;

	if (ptr->m_bSaveFile)
	{
		if (dwDataType == NET_DVR_SYSHEAD)
		{
			WriteFile(ptr->m_hFile, pBuffer, dwBufSize, &dwReturn, NULL);
		}
		else
		{
			if (ptr->m_bGbStream)
			{
				WriteFile(ptr->m_hFile, pBuffer + 12, dwBufSize - 12, &dwReturn, NULL);			
			}
			else
			{
				WriteFile(ptr->m_hFile, pBuffer, dwBufSize, &dwReturn, NULL);
			}
		}				
	}	

	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD:
		if (g_passiveWin.m_lPort == -1)
		{
			if (!PlayM4_GetPort(&g_passiveWin.m_lPort))
			{
				g_passiveWin.AddLog(PLAY_FAIL_T, "PlayM4_GetPort");
				break;
			}
			
		}
		if (!PlayM4_SetStreamOpenMode(g_passiveWin.m_lPort, STREAME_REALTIME))
		{
			g_passiveWin.AddLog(PLAY_FAIL_T, "PlayM4_SetStreamOpenMode err[%d]", PlayM4_GetLastError(g_passiveWin.m_lPort));
		}
		//start player
		if (!PlayM4_OpenStream(g_passiveWin.m_lPort, pBuffer, dwBufSize, 2*1024*1024))
		{
			g_passiveWin.m_lPort = -1;
			g_passiveWin.AddLog(PLAY_FAIL_T, "PlayM4_OpenStream err[%d]", PlayM4_GetLastError(g_passiveWin.m_lPort));
			break;
		}
		if (!PlayM4_Play(g_passiveWin.m_lPort, g_passiveWin.m_hWnd))
		{
			g_passiveWin.m_lPort = -1;
			g_passiveWin.AddLog(PLAY_FAIL_T, "PlayM4_Play err[%d]", PlayM4_GetLastError(g_passiveWin.m_lPort));
			break;
		}
		
		break;
	case NET_DVR_STD_VIDEODATA:
	case NET_DVR_STD_AUDIODATA:
	case NET_DVR_STREAMDATA:
		if (dwBufSize > 0 && g_passiveWin.m_lPort != -1)
		{
			if (ptr->m_bGbStream)
			{
				if (!PlayM4_InputData(g_passiveWin.m_lPort, pBuffer + 12, dwBufSize - 12))
				{
					g_passiveWin.AddLog(PLAY_FAIL_T, "PlayM4_InputData err[%d] length = %d", PlayM4_GetLastError(g_passiveWin.m_lPort), dwBufSize);
				}
			}
			else
			{
				if (!PlayM4_InputData(g_passiveWin.m_lPort, pBuffer, dwBufSize))
				{
					g_passiveWin.AddLog(PLAY_FAIL_T, "PlayM4_InputData err[%d] length = %d", PlayM4_GetLastError(g_passiveWin.m_lPort), dwBufSize);
				}
			}
			
// 			else
// 			{
// 				test += dwBufSize;
// 				g_passiveWin.AddLog(PLAY_SUCC_T, "PlayM4_InputData total len = %d", test);
// 			}
		}
		break;
	case NET_DVR_AUDIOSTREAMDATA:
		if (dwBufSize > 0 && g_passiveWin.m_lPort != -1)
		{
			if (ptr->m_bGbStream)
			{
				//国标码流偏移调rtp头再送播放库
				if (!PlayM4_InputVideoData(g_passiveWin.m_lPort, pBuffer + 12, dwBufSize - 12))
				{
					g_passiveWin.AddLog(PLAY_FAIL_T, "PlayM4_InputVideoData err[%d]", PlayM4_GetLastError(g_passiveWin.m_lPort));
				}
			}
			else
			{
				if (!PlayM4_InputVideoData(g_passiveWin.m_lPort, pBuffer, dwBufSize))
				{
					g_passiveWin.AddLog(PLAY_FAIL_T, "PlayM4_InputVideoData err[%d]", PlayM4_GetLastError(g_passiveWin.m_lPort));
				}
			}
			
		}
		break;
	default:
		if (dwBufSize > 0 && g_passiveWin.m_lPort != -1)
		{
			if (ptr->m_bGbStream)
			{
				if (!PlayM4_InputData(g_passiveWin.m_lPort, pBuffer + 12, dwBufSize - 12))
				{
					g_passiveWin.AddLog(PLAY_FAIL_T, "PlayM4_InputData err[%d]", PlayM4_GetLastError(g_passiveWin.m_lPort));
				}
			}
			else
			{
				if (!PlayM4_InputData(g_passiveWin.m_lPort, pBuffer, dwBufSize))
				{
					g_passiveWin.AddLog(PLAY_FAIL_T, "PlayM4_InputData err[%d]", PlayM4_GetLastError(g_passiveWin.m_lPort));
				}
			}			
		}
		break;
	}
}

void CALLBACK RealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void* pUser)
{
	CDlgPassiveTransCode *ptr = (CDlgPassiveTransCode *)pUser;
	//PassiveDataCallBack(lRealHandle, dwDataType, pBuffer, dwBufSize, pUser);
	CString csTemp;
	DWORD dwReturn = 0;
	if (dwDataType == NET_DVR_SYSHEAD)
	{
		ptr->m_struPassiveTransInfo.wDataLength = dwBufSize;
		memcpy(ptr->m_struPassiveTransInfo.pBuffer, pBuffer, dwBufSize);
		if (ptr->m_bSavePreFile)
		{
			WriteFile(ptr->m_hFilePre, pBuffer, dwBufSize, &dwReturn, NULL);
		}
		SetEvent(ptr->m_hHeadGetEvent);
	}
	else
	{
		if (WAIT_OBJECT_0 == WaitForSingleObject(ptr->m_hSendEvent, 0))
		{
			

			if (!NET_DVR_TransCodeInputData(ptr->m_lPassiveTransHandle, pBuffer, dwBufSize))
			{
				csTemp.Format("Send data fail, data len = %d", dwBufSize);
				g_pMainDlg->AddLog(ptr->m_iDeviceIndex, OPERATION_FAIL_T, csTemp);
			}
            else
            {
                if (ptr->m_bSavePreFile)
                {                                
                    WriteFile(ptr->m_hFilePre, pBuffer, dwBufSize, &dwReturn, NULL);
                }
            }
		}		
	}
}

// WORD dwSeq1 = 0;
// WORD dwSeq2 = 0;
	
void CALLBACK StdDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD pUser)
{
	CDlgPassiveTransCode *ptr = (CDlgPassiveTransCode *)pUser;
	CString csTemp;
	DWORD dwReturn = 0;

	if (dwDataType == NET_DVR_SDP)
	{
		ptr->m_struPassiveTransInfo.wDataLength = dwBufSize;
		memcpy(ptr->m_struPassiveTransInfo.pBuffer, pBuffer, dwBufSize);
		SetEvent(ptr->m_hHeadGetEvent);
	}
	else if (dwDataType == NET_DVR_SYSHEAD)
	{
		if (ptr->m_bSavePreFile)
		{
			WriteFile(ptr->m_hFilePre, pBuffer, dwBufSize, &dwReturn, NULL);
		}
	}
	else
	{
		if (WAIT_OBJECT_0 == WaitForSingleObject(ptr->m_hSendEvent, 0))
		{
// 			dwSeq2 = ntohs(*((WORD *)(pBuffer + 2)));
// 			if (dwSeq2 - dwSeq1 > 1)
// 			{
// 				g_pMainDlg->AddLog(ptr->m_iDeviceIndex, OPERATION_FAIL_T, "dwSeq1 = %d, dwSeq2 = %d", dwSeq1, dwSeq2);
// 			}
// 
// 			dwSeq1 = dwSeq2;

			if (!NET_DVR_TransCodeInputData(ptr->m_lPassiveTransHandle, pBuffer, dwBufSize))
			{
				csTemp.Format("Send data fail, data len = %d", dwBufSize);
				g_pMainDlg->AddLog(ptr->m_iDeviceIndex, OPERATION_FAIL_T, csTemp);
			}
            else
            {
                if (ptr->m_bSavePreFile)
                {
                    WriteFile(ptr->m_hFilePre, &dwBufSize, 4, &dwReturn, NULL);
                    WriteFile(ptr->m_hFilePre, pBuffer, dwBufSize, &dwReturn, NULL);
                }
            }
			g_pMainDlg->AddLog(ptr->m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_TransCodeInputData len = %d", dwBufSize);
		}
	}
}

CDlgPassiveTransCode::CDlgPassiveTransCode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPassiveTransCode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPassiveTransCode)
	m_dwChannel = 0xffffffff;
	m_dwIInterval = 25;
	m_csStreamId = _T("");
	m_dwBitrate = 0;
	m_bChannel = FALSE;
	m_csDevIP = _T("172.9.22.46");
	m_dwPort = 8000;
	m_csPassword = _T("12345");
	m_csUserName = _T("admin");
	m_csFilePath = _T("");
	m_dwStreamSize = 10;
	m_bCycleRead = TRUE;
	m_bSaveFile = FALSE;
	m_bSavePreFile = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgPassiveTransCode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPassiveTransCode)
	DDX_Control(pDX, IDC_COMBO_SRC_STREAM_TYPE, m_comboSrcStreamType);
	DDX_Control(pDX, IDC_COMBO_CALLBACK_TYPR, m_comboCallBackType);
	DDX_Control(pDX, IDC_COMBO_STREAM, m_comboStream);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL, m_comboProtocol);
	DDX_Control(pDX, IDC_COMBOGETSTREAMMODE, m_comboGetStreamMode);
	DDX_Control(pDX, IDC_COMBODEVCHAN, m_comboDevChan);
	DDX_Control(pDX, IDC_COMBO_STREAMTYPE, m_comboStreamType);	
	DDX_Control(pDX, IDC_COMBO_VIDEO_BITRATE, m_comboVideoBitrate);
	DDX_Control(pDX, IDC_COMBO_VENC_TYPE, m_comboVEncType);
	DDX_Control(pDX, IDC_COMBO_RESOLUSION, m_comboResolution);
	DDX_Control(pDX, IDC_COMBO_PIC_QUALITY, m_comboPicQuality);
	DDX_Control(pDX, IDC_COMBO_FRAME_RATE, m_comboFrameRate);
	DDX_Control(pDX, IDC_COMBO_FORMAT_TYPE, m_comboFormatType);
	DDX_Control(pDX, IDC_COMBO_ENC_COMPLEXITY, m_comboEncComplexity);
	DDX_Control(pDX, IDC_COMBO_CMP_TYPE, m_comboCmpType);
	DDX_Control(pDX, IDC_COMBO_BP_FRAME, m_comboBPFrame);
	DDX_Control(pDX, IDC_COMBO_BITRATE_TYPE, m_comboBitrateType);
	DDX_Control(pDX, IDC_COMBO_AENC_TYPE, m_comboAEncType);
	DDX_Text(pDX, IDC_EDIT_CHANNEL, m_dwChannel);
	DDX_Text(pDX, IDC_EDIT_I_INTERVAL, m_dwIInterval);
	DDX_Text(pDX, IDC_EDIT_ID, m_csStreamId);
	DDX_Text(pDX, IDC_EDIT_BITRATE, m_dwBitrate);
	DDX_Check(pDX, IDC_CHK_CHANNEL, m_bChannel);
	DDX_Text(pDX, IDC_DEVICE_IP, m_csDevIP);
	DDX_Text(pDX, IDC_DEVICE_PORT, m_dwPort);
	DDX_Text(pDX, IDC_DEVICE_PSW, m_csPassword);
	DDX_Text(pDX, IDC_DEVICE_USERNAME, m_csUserName);
	DDX_Text(pDX, IDC_EDIT_FILE_PATH, m_csFilePath);
	DDX_Text(pDX, IDC_EDIT_STREAM_SIZE, m_dwStreamSize);
	DDX_Check(pDX, IDC_CHECK_CYCLE_READ, m_bCycleRead);
	DDX_Check(pDX, IDC_CHK_SAVE_FILE, m_bSaveFile);
	DDX_Check(pDX, IDC_CHK_SAVE_FILE_PRE, m_bSavePreFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPassiveTransCode, CDialog)
	//{{AFX_MSG_MAP(CDlgPassiveTransCode)
	ON_BN_CLICKED(IDC_BTN_START_PASSIVE_TRANS, OnBtnStartPassiveTrans)
	ON_CBN_SELCHANGE(IDC_COMBO_CMP_TYPE, OnSelchangeComboCmpType)
	ON_BN_CLICKED(IDC_CHK_CHANNEL, OnChkChannel)
	ON_BN_CLICKED(IDC_BTN_SEND_DATA, OnBtnSendData)
	ON_BN_CLICKED(IDC_BTN_STOP_PASSIVE_TRANS, OnBtnStopPassiveTrans)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_DISP, OnBtnDisp)
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	ON_WM_DESTROY()
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPassiveTransCode message handlers

BOOL CDlgPassiveTransCode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);

	m_lDevUserID = -1;
	m_lPassiveTransHandle = -1;
	m_lRealPlayHandle = -1;	
	m_hSrcFile = INVALID_HANDLE_VALUE;
	m_bNeedSendAgain = FALSE;
	m_hFileThread = NULL;
	m_dwStreamType = 0;
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();

	int i = 0;
	char szLan[128] = {0};
	CString csTemp;

	for (i = 0; i < 64; i++)
	{
		csTemp.Format("%d", i + 1);
		m_comboDevChan.AddString(csTemp);
	}

	DWORD dwChanIndex = 1;
	if (!NET_DVR_GetDeviceAbility(m_lUserID, COMPRESSIONCFG_ABILITY, (char*)&dwChanIndex, sizeof(dwChanIndex), (char*)(&m_struCompressionCfgAblity), sizeof(NET_DVR_COMPRESSIONCFG_ABILITY)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "COMPRESSIONCFG_ABILITY");
		g_StringLanType(szLan, "获取编码压缩参数失败", "Get compression config fail");
		AfxMessageBox(szLan);          
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "COMPRESSIONCFG_ABILITY");
		InsertMainResolution();
		//InsertSubResolution();
		InsertFrame();
		InsertBitrateType();
		InsertBitrate();
		InsertStreamType();
		InsertPicQuality();
		InsertBpFrame();
		InsertVideoEnc();
		InsertAudioEnc();
		InsertVEncComplexity();
	    InsertFormatType();
    }

	m_comboSrcStreamType.SetCurSel(1);
	m_iSelCmpType = 0;
	m_comboCmpType.SetCurSel(0);
	m_comboGetStreamMode.SetCurSel(0);
	m_comboStream.SetCurSel(0);
	m_comboProtocol.SetCurSel(0);
	m_comboDevChan.SetCurSel(0);

	m_comboStreamType.SetCurSel(0);
	m_comboResolution.SetCurSel(3);
	m_comboVideoBitrate.SetCurSel(6);
	m_comboBitrateType.SetCurSel(0);
	m_comboPicQuality.SetCurSel(0);
	m_comboFrameRate.SetCurSel(7);
	m_comboBPFrame.SetCurSel(0);
	m_comboVEncType.SetCurSel(1);
	m_comboAEncType.SetCurSel(1);
	m_comboEncComplexity.SetCurSel(0);
	m_comboFormatType.SetCurSel(1);
	m_comboCallBackType.SetCurSel(0);

	m_hSendEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hHeadGetEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hFile = INVALID_HANDLE_VALUE;
	m_hFilePre = INVALID_HANDLE_VALUE;

	memset(&m_struCmpCfgV30, 0, sizeof(m_struCmpCfgV30));

	OnChkChannel();

	m_dlgDisp.Create(IDD_DLG_PASSIVE_WIN, this);
	m_dlgDisp.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPassiveTransCode::InsertMainResolution()
{
	for (int nAbilityCount = 0; nAbilityCount < m_struCompressionCfgAblity.dwAbilityNum; nAbilityCount++)
    {
        if (MAIN_RESOLUTION_ABILITY == m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboResolution.ResetContent();
            for (int i = 0; i < m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboResolution.AddString((char*)m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboResolution.SetItemData(i, m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

void CDlgPassiveTransCode::InsertSubResolution()
{
	for (int nAbilityCount = 0; nAbilityCount < m_struCompressionCfgAblity.dwAbilityNum; nAbilityCount++)
    {
        if (SUB_RESOLUTION_ABILITY == m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboResolution.ResetContent();
            for (int i = 0; i < m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboResolution.AddString((char*)m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboResolution.SetItemData(i, m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

void CDlgPassiveTransCode::InsertFrame()
{
	for (int nAbilityCount = 0; nAbilityCount < m_struCompressionCfgAblity.dwAbilityNum; nAbilityCount++)
    {
        if (FRAME_ABILITY == m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboFrameRate.ResetContent();
            for (int i = 0; i < m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboFrameRate.AddString((char*)m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboFrameRate.SetItemData(i, m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

void CDlgPassiveTransCode::InsertBitrateType()
{
	for (int nAbilityCount = 0; nAbilityCount < m_struCompressionCfgAblity.dwAbilityNum; nAbilityCount++)
    {
        if (BITRATE_TYPE_ABILITY == m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboBitrateType.ResetContent();
            for (int i = 0; i < m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboBitrateType.AddString((char*)m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboBitrateType.SetItemData(i, m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

void CDlgPassiveTransCode::InsertBitrate()
{
	for (int nAbilityCount = 0; nAbilityCount < m_struCompressionCfgAblity.dwAbilityNum; nAbilityCount++)
    {
        if (BITRATE_ABILITY == m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboVideoBitrate.ResetContent();
            for (int i = 0; i < m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboVideoBitrate.AddString((char*)m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboVideoBitrate.SetItemData(i, m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

void CDlgPassiveTransCode::InsertStreamType()
{
	for (int nAbilityCount = 0; nAbilityCount < m_struCompressionCfgAblity.dwAbilityNum; nAbilityCount++)
	{
		if (STREAM_TYPE_ABILITY == m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwAbilityType)
		{
			m_comboStreamType.ResetContent();
			for (int i = 0; i < m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwNodeNum; i++)
			{
				m_comboStreamType.AddString((char*)m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
				m_comboStreamType.SetItemData(i, m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].iValue);
			}
		}
	}
}

void CDlgPassiveTransCode::InsertPicQuality()
{
	for (int nAbilityCount = 0; nAbilityCount < m_struCompressionCfgAblity.dwAbilityNum; nAbilityCount++)
	{
		if (PIC_QUALITY_ABILITY == m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwAbilityType)
		{
			m_comboPicQuality.ResetContent();
			for (int i = 0; i < m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwNodeNum; i++)
			{
				m_comboPicQuality.AddString((char*)m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
				m_comboPicQuality.SetItemData(i, m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].iValue);
			}
		}
	}
}
 
void CDlgPassiveTransCode::InsertBpFrame()
{
	for (int nAbilityCount = 0; nAbilityCount < m_struCompressionCfgAblity.dwAbilityNum; nAbilityCount++)
	{
		if (INTERVAL_BPFRAME_ABILITY == m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwAbilityType)
		{
			m_comboBPFrame.ResetContent();
			for (int i = 0; i < m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwNodeNum; i++)
			{
				m_comboBPFrame.AddString((char*)m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
				m_comboBPFrame.SetItemData(i, m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].iValue);
			}
		}
	}
}

void CDlgPassiveTransCode::InsertVideoEnc()
{
	for (int nAbilityCount = 0; nAbilityCount < m_struCompressionCfgAblity.dwAbilityNum; nAbilityCount++)
	{
		if (VIDEO_ENC_ABILITY == m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwAbilityType)
		{
			m_comboVEncType.ResetContent();
			for (int i = 0; i < m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwNodeNum; i++)
			{
				m_comboVEncType.AddString((char*)m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
				m_comboVEncType.SetItemData(i, m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].iValue);
			}
		}
	}
}

void CDlgPassiveTransCode::InsertAudioEnc()
{
	for (int nAbilityCount = 0; nAbilityCount < m_struCompressionCfgAblity.dwAbilityNum; nAbilityCount++)
	{
		if (AUDIO_ENC_ABILITY == m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwAbilityType)
		{
			m_comboAEncType.ResetContent();
			for (int i = 0; i < m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwNodeNum; i++)
			{
				m_comboAEncType.AddString((char*)m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
				m_comboAEncType.SetItemData(i, m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].iValue);
			}
		}
	}
}

void CDlgPassiveTransCode::InsertVEncComplexity()
{
	for (int nAbilityCount = 0; nAbilityCount < m_struCompressionCfgAblity.dwAbilityNum; nAbilityCount++)
	{
		if (VIDEO_ENC_COMPLEXITY_ABILITY == m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwAbilityType)
		{
			m_comboEncComplexity.ResetContent();
			for (int i = 0; i < m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwNodeNum; i++)
			{
				m_comboEncComplexity.AddString((char*)m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
				m_comboEncComplexity.SetItemData(i, m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].iValue);
			}
		}
	}
}

void CDlgPassiveTransCode::InsertFormatType()
{	
	for (int nAbilityCount = 0; nAbilityCount < m_struCompressionCfgAblity.dwAbilityNum; nAbilityCount++)
	{
		if (FORMAT_ABILITY == m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwAbilityType)
		{
			m_comboFormatType.ResetContent();
			for (int i = 0; i < m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwNodeNum; i++)
			{
				m_comboFormatType.AddString((char*)m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
				m_comboFormatType.SetItemData(i, m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].iValue);
			}
		}
	}
}

void CDlgPassiveTransCode::OnBtnStartPassiveTrans() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);	
	char szLan[128] = {0};

	if (m_lPassiveTransHandle != -1)
	{
		g_StringLanType(szLan, "请先停止被动转码", "Please stop passive trans code first");
		AfxMessageBox(szLan);
		return;
	}

	memset(&m_struStreamInfo, 0, sizeof(m_struStreamInfo));
	memset(&m_struPassiveTransInfo, 0, sizeof(m_struPassiveTransInfo));
	memset(&m_pHead, 0, sizeof(m_pHead));
	memset(&m_pSdpInfo, 0, sizeof(m_pSdpInfo));
    memset(&m_pFileData, 0, sizeof(m_pFileData));

	CString csFilePath;
	CTime ctime = GetCurrentTime();
	csFilePath.Format("%s\\PassiveTransCode_%d%d%d%d%d%d.mp4", g_struLocalParam.chDownLoadPath, ctime.GetYear(), ctime.GetMonth(), ctime.GetDay(), ctime.GetHour(), ctime.GetMinute(), ctime.GetSecond());
	if (m_bSaveFile)
	{
		m_hFile = CreateFile(csFilePath, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (INVALID_HANDLE_VALUE == m_hFile)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Create transcode file fail");
        }
	}

	csFilePath.Format("%s\\PreviewFile_%d%d%d%d%d%d.mp4", g_struLocalParam.chDownLoadPath, ctime.GetYear(), ctime.GetMonth(), ctime.GetDay(), ctime.GetHour(), ctime.GetMinute(), ctime.GetSecond());
	if (m_bSavePreFile)
	{
		m_hFilePre = CreateFile(csFilePath, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (INVALID_HANDLE_VALUE == m_hFilePre)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Create pre file fail");
        }
	}
	//文件流
	if (m_comboSrcStreamType.GetCurSel() == 0)
	{
		if (m_csFilePath.GetLength() == 0)
		{
			g_StringLanType(szLan, "请选择文件路径", "please select file path");
			AfxMessageBox(szLan);
			return;			
		}

		if (m_dwStreamSize < 1 || m_dwStreamSize > 150)
		{
			g_StringLanType(szLan, "请选择合适发送大小", "please select appropriate send size");
			AfxMessageBox(szLan);
			return;
		}

		m_struPassiveTransInfo.pBuffer = m_pHead;
		m_hSrcFile = CreateFile(m_csFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == m_hSrcFile)
		{
			g_StringLanType(szLan, "打开文件失败", "Open file fail");
			AfxMessageBox(szLan);
            CloseHandle(m_hSrcFile);
            CloseHandle(m_hFile);
            m_hSrcFile = INVALID_HANDLE_VALUE;
            m_hFile = INVALID_HANDLE_VALUE;
			return;
		}

		DWORD dwRead = 0;
		ReadFile(m_hSrcFile, m_struPassiveTransInfo.pBuffer, 40, &dwRead, NULL);
		if (dwRead != 40)
		{			
			CloseHandle(m_hSrcFile);
			m_hSrcFile = INVALID_HANDLE_VALUE;
			g_StringLanType(szLan, "读取文件头失败", "Read file head fail");
			AfxMessageBox(szLan);
            CloseHandle(m_hSrcFile);
            CloseHandle(m_hFile);
            m_hSrcFile = INVALID_HANDLE_VALUE;
            m_hFile = INVALID_HANDLE_VALUE;
			return;
		}
			
		m_struPassiveTransInfo.wDataLength = 40;

		m_hExitFileThread = CreateEvent(NULL, TRUE, FALSE, NULL);
		if (*((DWORD *)m_struPassiveTransInfo.pBuffer) != 0x484b4d49)
		{
            m_bNeedSendAgain = TRUE;
            memcpy(m_pFileData, m_struPassiveTransInfo.pBuffer, 40);
			memset(m_struPassiveTransInfo.pBuffer, 0, 40);
		}
        else
        {
            m_bNeedSendAgain = FALSE;
        }

		dwStreamSize = m_dwStreamSize;
		bCycleRead = m_bCycleRead;

		DWORD dwThreadId;
		m_hFileThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(PassiveTransFileThread), this, 0, &dwThreadId);

		if (m_hFileThread == NULL)
		{
			g_StringLanType(szLan, "创建读文件线程失败", "Start file read thread fail");
			CloseHandle(m_hSrcFile);
			m_hSrcFile = INVALID_HANDLE_VALUE;			
			CloseHandle(m_hExitFileThread);
			m_hExitFileThread = INVALID_HANDLE_VALUE;
            CloseHandle(m_hSrcFile);
            CloseHandle(m_hFile);
            m_hSrcFile = INVALID_HANDLE_VALUE;
            m_hFile = INVALID_HANDLE_VALUE;
			return;
		}
	}
	//实时流
	else
	{		
		if (m_comboCallBackType.GetCurSel() == 0)
		{
			m_struPassiveTransInfo.pBuffer = m_pHead;
		}
		else
		{
			m_struPassiveTransInfo.pBuffer = m_pSdpInfo;
		}		
		
		NET_DVR_DEVICEINFO_V30 struDevInfo = {0};
		m_lDevUserID = NET_DVR_Login_V30(m_csDevIP.GetBuffer(0), m_dwPort, m_csUserName.GetBuffer(0), m_csPassword.GetBuffer(0), &struDevInfo);
		
		if (m_lDevUserID == -1)
		{
			g_StringLanType(szLan, "登陆前端设备失败", "Login device fail");
			AfxMessageBox(szLan);
            CloseHandle(m_hSrcFile);
            CloseHandle(m_hFile);
            m_hSrcFile = INVALID_HANDLE_VALUE;
            m_hFile = INVALID_HANDLE_VALUE;
			return;
		}	

		NET_DVR_PREVIEWINFO struPreViewInfo = {0};
		struPreViewInfo.lChannel = m_comboDevChan.GetCurSel() + 1;
		struPreViewInfo.hPlayWnd = NULL;
		struPreViewInfo.dwLinkMode = m_comboGetStreamMode.GetCurSel();
		struPreViewInfo.byProtoType = 1;		
		
		ResetEvent(m_hHeadGetEvent);
		if (m_comboCallBackType.GetCurSel() == 0)
		{
			m_lRealPlayHandle = NET_DVR_RealPlay_V40(m_lDevUserID, &struPreViewInfo, RealDataCallBack, this);
		}
		else
		{
			m_lRealPlayHandle = NET_DVR_RealPlay_V40(m_lDevUserID, &struPreViewInfo, NULL, NULL);
		}
		
		
		if (m_lRealPlayHandle == -1)
		{
			g_StringLanType(szLan, "前端取流失败", "Get real strem fail");
            CloseHandle(m_hSrcFile);
            CloseHandle(m_hFile);
            m_hSrcFile = INVALID_HANDLE_VALUE;
            m_hFile = INVALID_HANDLE_VALUE;
			return;
		}
		
		if (m_comboCallBackType.GetCurSel() == 1)
		{
			NET_DVR_SetStandardDataCallBack(m_lRealPlayHandle, StdDataCallBack, (DWORD)this);
		}		

		if (WAIT_OBJECT_0 != WaitForSingleObject(m_hHeadGetEvent, 5000))
		{
			NET_DVR_StopRealPlay(m_lRealPlayHandle);
			NET_DVR_Logout_V30(m_lDevUserID);
			g_StringLanType(szLan, "获取码流头超时", "Get stream head time out");
			AfxMessageBox(szLan);
            CloseHandle(m_hSrcFile);
            CloseHandle(m_hFile);
            m_hSrcFile = INVALID_HANDLE_VALUE;
            m_hFile = INVALID_HANDLE_VALUE;
			return;
		}
	}	

	m_struStreamInfo.dwSize = sizeof(m_struStreamInfo);
	m_struStreamInfo.dwChannel = m_dwChannel;
	strncpy((char *)m_struStreamInfo.byID, m_csStreamId, STREAM_ID_LEN);

	m_struPassiveTransInfo.dwSize = sizeof(m_struPassiveTransInfo);
	m_struPassiveTransInfo.byStreamType = m_comboStream.GetCurSel();
	m_struPassiveTransInfo.byLinkMode = m_comboProtocol.GetCurSel();
	if (m_comboSrcStreamType.GetCurSel() == 0)
	{
		m_struPassiveTransInfo.byPassiveTransMode = 2;
	}
	else
	{
		m_struPassiveTransInfo.byPassiveTransMode = 1;
	}

	if (m_comboSrcStreamType.GetCurSel() == 1)
	{
		if (m_comboCallBackType.GetCurSel() == 1)
		{
			m_struPassiveTransInfo.byDataType = 1;
		}
		else
		{
			m_struPassiveTransInfo.byDataType = 2;
		}		
	}
	else
	{
		m_struPassiveTransInfo.byDataType = 2;
	}
	
	OnSelchangeComboCmpType();
	if (m_comboCmpType.GetCurSel() == 0)
	{
		m_comboCmpType.SetCurSel(1);
		OnSelchangeComboCmpType();
		m_comboCmpType.SetCurSel(0);
	}
	else
	{
		m_comboCmpType.SetCurSel(0);
		OnSelchangeComboCmpType();
		m_comboCmpType.SetCurSel(1);
	}	

	if (m_struCmpCfgV30.struNormHighRecordPara.byFormatType == 9 && m_struPassiveTransInfo.byStreamType == 0 \
		|| m_struCmpCfgV30.struNetPara.byFormatType == 9 && m_struPassiveTransInfo.byStreamType == 1)
	{
		m_bGbStream = TRUE;
	}
	else
	{
		m_bGbStream = FALSE;
	}

	m_lPassiveTransHandle = NET_DVR_StartPassiveTransCode(m_lUserID, &m_struStreamInfo, &m_struCmpCfgV30, &m_struPassiveTransInfo, PassiveDataCallBack, this);
	if (-1 == m_lPassiveTransHandle)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartPassiveTransCode");

		if (m_comboSrcStreamType.GetCurSel() == 0)
		{
            SetEvent(m_hExitFileThread);
            WaitForSingleObject(m_hFileThread, INFINITE);
			CloseHandle(m_hExitFileThread);
			m_hExitFileThread = INVALID_HANDLE_VALUE;
            m_hFileThread = NULL;
			CloseHandle(m_hSrcFile);
			m_hSrcFile = INVALID_HANDLE_VALUE;
		}
		else
		{
			NET_DVR_StopRealPlay(m_lRealPlayHandle);
		    NET_DVR_Logout_V30(m_lDevUserID);            
		}
		
		if (m_hFile != INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_hFile);
			m_hFile = INVALID_HANDLE_VALUE;
		}
		
		if (m_hFilePre != INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_hFilePre);
			m_hFilePre = INVALID_HANDLE_VALUE;
		}
		
		g_StringLanType(szLan, "开始被动转码失败", "Strat passive trans code error");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartPassiveTransCode");
		g_StringLanType(szLan, "成功", "Success");
		m_dwStreamType = m_comboSrcStreamType.GetCurSel();
		AfxMessageBox(szLan);
	}	
}

void CDlgPassiveTransCode::OnSelchangeComboCmpType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struCmpCfgV30.dwSize = sizeof(m_struCmpCfgV30);
    m_iSelCmpType = m_comboCmpType.GetCurSel();

	if (m_iSelCmpType == 0)
	{
		int sel = m_comboResolution.GetCurSel();
		InsertMainResolution();
		m_comboResolution.SetCurSel(sel);
		m_struCmpCfgV30.struNormHighRecordPara.byStreamType = m_comboStreamType.GetItemData(m_comboStreamType.GetCurSel());
// 		if (m_comboStreamType.GetCurSel() == m_comboStreamType.GetCount() - 1)
// 		{
// 			m_struCmpCfgV30.struNormHighRecordPara.byStreamType = 0xfe;
// 		}
		m_struCmpCfgV30.struNormHighRecordPara.byResolution = m_comboResolution.GetItemData(m_comboResolution.GetCurSel());
		m_struCmpCfgV30.struNormHighRecordPara.byBitrateType = m_comboBitrateType.GetItemData(m_comboBitrateType.GetCurSel());
		m_struCmpCfgV30.struNormHighRecordPara.byPicQuality = m_comboPicQuality.GetItemData(m_comboPicQuality.GetCurSel());
// 		if (m_comboPicQuality.GetCurSel() == m_comboPicQuality.GetCount() - 1)
// 		{
// 			m_struCmpCfgV30.struNormHighRecordPara.byPicQuality = 0xfe;
// 		}
		if (m_comboVideoBitrate.GetItemData(m_comboVideoBitrate.GetCurSel()) != 0x80000000)
		{
			m_struCmpCfgV30.struNormHighRecordPara.dwVideoBitrate = m_comboVideoBitrate.GetItemData(m_comboVideoBitrate.GetCurSel());
		}
		else
		{
			m_struCmpCfgV30.struNormHighRecordPara.dwVideoBitrate = 0x80000000 | m_dwBitrate;
		}
		m_struCmpCfgV30.struNormHighRecordPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struCmpCfgV30.struNormHighRecordPara.wIntervalFrameI = m_dwIInterval;
		m_struCmpCfgV30.struNormHighRecordPara.byIntervalBPFrame = m_comboBPFrame.GetItemData(m_comboBPFrame.GetCurSel());
// 		if (m_comboBPFrame.GetCurSel() == m_comboBPFrame.GetCount() - 1)
// 		{
// 			m_struCmpCfgV30.struNormHighRecordPara.byIntervalBPFrame = 0xfe;
// 		}
		m_struCmpCfgV30.struNormHighRecordPara.byVideoEncType = m_comboVEncType.GetItemData(m_comboVEncType.GetCurSel());
// 		if (m_struCmpCfgV30.struNormHighRecordPara.byVideoEncType > 2)
// 		{
// 			m_struCmpCfgV30.struNormHighRecordPara.byVideoEncType += 4;
// 		}
		m_struCmpCfgV30.struNormHighRecordPara.byAudioEncType = m_comboAEncType.GetItemData(m_comboAEncType.GetCurSel());
// 		if (m_struCmpCfgV30.struNormHighRecordPara.byAudioEncType > 2)
// 		{
// 			m_struCmpCfgV30.struNormHighRecordPara.byAudioEncType += 3;
// 		}
		m_struCmpCfgV30.struNormHighRecordPara.byVideoEncComplexity = m_comboEncComplexity.GetItemData(m_comboEncComplexity.GetCurSel());
// 		if (m_comboEncComplexity.GetCurSel() == m_comboEncComplexity.GetCount() - 1)
// 		{
// 			m_struCmpCfgV30.struNormHighRecordPara.byVideoEncComplexity = 0xfe;
// 		}
		m_struCmpCfgV30.struNormHighRecordPara.byFormatType = m_comboFormatType.GetItemData(m_comboFormatType.GetCurSel());
	}
	else if (m_iSelCmpType == 1)
	{
		int sel = m_comboResolution.GetCurSel();
		InsertSubResolution();
		m_comboResolution.SetCurSel(sel);
		m_struCmpCfgV30.struNetPara.byStreamType = m_comboStreamType.GetItemData(m_comboStreamType.GetCurSel());
// 		if (m_comboStreamType.GetCurSel() == m_comboStreamType.GetCount() - 1)
// 		{
// 			m_struCmpCfgV30.struNetPara.byStreamType = 0xfe;
// 		}
		m_struCmpCfgV30.struNetPara.byResolution = m_comboResolution.GetItemData(m_comboResolution.GetCurSel());
		m_struCmpCfgV30.struNetPara.byBitrateType = m_comboBitrateType.GetItemData(m_comboBitrateType.GetCurSel());
		m_struCmpCfgV30.struNetPara.byPicQuality = m_comboPicQuality.GetItemData(m_comboPicQuality.GetCurSel());
// 		if (m_comboPicQuality.GetCurSel() == m_comboPicQuality.GetCount() - 1)
// 		{
// 			m_struCmpCfgV30.struNetPara.byPicQuality = 0xfe;
// 		}
		if (m_comboVideoBitrate.GetItemData(m_comboVideoBitrate.GetCurSel() == 0x80000000))
		{
			m_struCmpCfgV30.struNetPara.dwVideoBitrate = m_comboVideoBitrate.GetItemData(m_comboVideoBitrate.GetCurSel());
		}
		else
		{
			m_struCmpCfgV30.struNetPara.dwVideoBitrate = 0x80000000 | m_dwBitrate;
		}
		m_struCmpCfgV30.struNetPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struCmpCfgV30.struNetPara.wIntervalFrameI = m_dwIInterval;
		m_struCmpCfgV30.struNetPara.byIntervalBPFrame = m_comboBPFrame.GetItemData(m_comboBPFrame.GetCurSel());
// 		if (m_comboBPFrame.GetCurSel() == m_comboBPFrame.GetCount() - 1)
// 		{
// 			m_struCmpCfgV30.struNetPara.byIntervalBPFrame = 0xfe;
// 		}
		m_struCmpCfgV30.struNetPara.byVideoEncType = m_comboVEncType.GetItemData(m_comboVEncType.GetCurSel());
// 		if (m_struCmpCfgV30.struNetPara.byVideoEncType > 2)
// 		{
// 			m_struCmpCfgV30.struNetPara.byVideoEncType += 4;
// 		}
		m_struCmpCfgV30.struNetPara.byAudioEncType = m_comboAEncType.GetItemData(m_comboAEncType.GetCurSel());
// 		if (m_struCmpCfgV30.struNetPara.byAudioEncType > 2)
// 		{
// 			m_struCmpCfgV30.struNetPara.byAudioEncType += 3;
// 		}
		m_struCmpCfgV30.struNetPara.byVideoEncComplexity = m_comboEncComplexity.GetItemData(m_comboEncComplexity.GetCurSel());
// 		if (m_comboEncComplexity.GetCurSel() == m_comboEncComplexity.GetCount() - 1)
// 		{
// 			m_struCmpCfgV30.struNetPara.byVideoEncComplexity = 0xfe;
// 		}
		m_struCmpCfgV30.struNetPara.byFormatType = m_comboFormatType.GetItemData(m_comboFormatType.GetCurSel());
	}	
}

void CDlgPassiveTransCode::OnChkChannel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_bChannel)
	{
		GetDlgItem(IDC_EDIT_ID)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CHANNEL)->EnableWindow(TRUE);
		m_csStreamId = "";
	}
	else
	{
		GetDlgItem(IDC_EDIT_ID)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_CHANNEL)->EnableWindow(FALSE);
		m_dwChannel = 0xffffffff;
	}

	UpdateData(FALSE);
}

void CDlgPassiveTransCode::OnBtnSendData() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};

	if (m_lPassiveTransHandle == -1)
	{
		g_StringLanType(szLan, "未开始被动转码", "Passive trans code not strat");
		AfxMessageBox(szLan);
		return;		
	}

	if (WAIT_OBJECT_0 == WaitForSingleObject(m_hSendEvent, 0))
	{
		return;
	}

	SetEvent(m_hSendEvent);
}

void CDlgPassiveTransCode::OnBtnStopPassiveTrans() 
{
	// TODO: Add your control notification handler code here
	if (m_lPassiveTransHandle == -1)
	{
		return;
	}

	ResetEvent(m_hSendEvent);

	if (m_dwStreamType == 0)
	{
		
		if (m_hFileThread != NULL)
		{
			SetEvent(m_hExitFileThread);
			WaitForSingleObject(m_hFileThread, INFINITE);
			m_hFileThread = NULL;
			CloseHandle(m_hExitFileThread);					
		}
	}
	else
	{
		ResetEvent(m_hHeadGetEvent);
		if (m_lRealPlayHandle != -1)
		{
			NET_DVR_StopRealPlay(m_lRealPlayHandle);
			m_lRealPlayHandle = -1;
		}
		
		if (m_lDevUserID != -1)
		{
			NET_DVR_Logout_V30(m_lDevUserID);
			m_lDevUserID = -1;
		}
	}	
	

	if (g_passiveWin.m_lPort != -1)
	{
		if (!PlayM4_Stop(g_passiveWin.m_lPort))
		{
			g_passiveWin.AddLog(PLAY_FAIL_T, "PlayM4_Stop err[%d]", PlayM4_GetLastError(g_passiveWin.m_lPort));
		}
		
		if (!PlayM4_CloseStream(g_passiveWin.m_lPort))
		{
			g_passiveWin.AddLog(PLAY_FAIL_T, "PlayM4_CloseStream err[%d]", PlayM4_GetLastError(g_passiveWin.m_lPort));
		}
		
		if (!PlayM4_FreePort(g_passiveWin.m_lPort))
		{
			g_passiveWin.AddLog(PLAY_FAIL_T, "PlayM4_FreePort err[%d]", PlayM4_GetLastError(g_passiveWin.m_lPort));
		}		
		
		g_passiveWin.m_lPort = -1;
	}

	if (!NET_DVR_StopPassiveTransCode(m_lPassiveTransHandle))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopPassiveTransCode");
		AfxMessageBox("Fail");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopPassiveTransCode");
		AfxMessageBox("Success");
	}
	

	if (m_hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
	}

	if (m_hFilePre != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hFilePre);
		m_hFilePre = INVALID_HANDLE_VALUE;
	}

	if (m_hSrcFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hSrcFile);
		m_hSrcFile = INVALID_HANDLE_VALUE;
	}

	m_lPassiveTransHandle = -1;
    m_bNeedSendAgain = FALSE;
}

void CDlgPassiveTransCode::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	
	ResetEvent(m_hSendEvent);
	ResetEvent(m_hHeadGetEvent);
	
	if (m_lRealPlayHandle != -1)
	{
		NET_DVR_StopRealPlay(m_lRealPlayHandle);
		m_lRealPlayHandle = -1;
	}
	
	if (m_lDevUserID != -1)
	{
		NET_DVR_Logout_V30(m_lDevUserID);
		m_lDevUserID = -1;
	}

	if (m_lPassiveTransHandle != -1)
	{
		NET_DVR_StopPassiveTransCode(m_lPassiveTransHandle);
		m_lPassiveTransHandle = -1;
	}
	
	CloseHandle(m_hHeadGetEvent);
	CloseHandle(m_hSendEvent);

	CDialog::OnCancel();
}


void CDlgPassiveTransCode::OnBtnDisp() 
{
	// TODO: Add your control notification handler code here
	m_dlgDisp.ShowWindow(SW_SHOW);
	g_passiveWin.StartSound(0xffff);
}

void CDlgPassiveTransCode::OnBtnBrowse() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    static char szFilter[] = "All File(*.mp4*)|*.mp4*||";
    CFileDialog dlg(TRUE,"*.mp4*","record.mp4",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
        szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_csFilePath = dlg.GetPathName();
        UpdateData(FALSE);
	}	
}

void CDlgPassiveTransCode::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	OnBtnExit();	
}

void CDlgPassiveTransCode::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	OnBtnExit();	
}
