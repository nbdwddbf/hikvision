/**********************************************************
FileName:    DlgVoiceTalk.cpp
Description: Voice Talk      
Date:        2008/06/03
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp  
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/06/03>       <created>
***********************************************************/

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVoiceTalk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern BYTE g_MatrixDecAudioStatus[32];//0 - not used;1 - used; 2 - not support
FILE* fp1 = NULL;
FILE* fp2 = NULL;
void CALLBACK fAudioTalkDataCallBack(LONG lVoiceComHandle,char *pRecvDataBuffer,DWORD dwBufSize,BYTE byAudioFlag,void* pUser)
{
 	

/*	if (!fp1)
   	{
		fp1 = fopen("C:\\local.264","wb");
	}
   	if (!fp2)
	{
 		fp2 = fopen("E:\\device.264","wb");
	}
  	
 	if (byAudioFlag == 0)
	{
 		fwrite(pRecvDataBuffer, 1, dwBufSize, fp1);
   	}
   	else if (byAudioFlag == 1)
	{
   		fwrite(pRecvDataBuffer, 1, dwBufSize, fp2);
   	}
*/
}

/////////////////////////////////////////////////////////////////////////////
// CDlgVoiceTalk dialog
/*********************************************************
  Function:	OnInitDialog
  Desc:		Initialize the dialog
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
CDlgVoiceTalk::CDlgVoiceTalk(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVoiceTalk::IDD, pParent)
{
	m_dwSel = 0;
	m_dwDeviceIndex = 0;
    m_bGetWorkStatusSucc = FALSE;
	//{{AFX_DATA_INIT(CDlgVoiceTalk)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		the map between control and variable
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgVoiceTalk::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVoiceTalk)
	DDX_Control(pDX, IDC_COMBO_DATA_TYPE, m_comboDataType);
	DDX_Control(pDX, IDC_COMBO_VOICE_CHAN, m_comboVoiceChan);
	//}}AFX_DATA_MAP
}

/*********************************************************
  Function:	BEGIN_MESSAGE_MAP
  Desc:		the map between control and function
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgVoiceTalk, CDialog)
	//{{AFX_MSG_MAP(CDlgVoiceTalk)
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_CBN_SELCHANGE(IDC_COMBO_VOICE_CHAN, OnSelchangeComboVoiceChan)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVoiceTalk message handlers
/*********************************************************
  Function:	OnInitDialog
  Desc:		Initialize the dialog
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
BOOL CDlgVoiceTalk::OnInitDialog()
{
    CDialog::OnInitDialog();
    EnableCtrl();
    char szLan[128] = {0};
    m_comboVoiceChan.ResetContent();
	char sTemp[20] = {0};
	
    NET_DVR_DIGITAL_CHANNEL_STATE struDigitalChanState = {0};
    
    DWORD dwReturnValue = 0; 
    if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_dwDeviceIndex].lLoginID, NET_DVR_GET_DIGITAL_CHANNEL_STATE, 0, &struDigitalChanState, sizeof(struDigitalChanState), &dwReturnValue))
    {
        char szLan[256] = {0};
        g_StringLanType(szLan, "获取失败!", "Fail to Get !");
        g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DIGITAL_CHANNEL_STATE");
        //AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_DIGITAL_CHANNEL_STATE");
	}
	
	for(int i = 1; i <= g_struDeviceInfo[m_dwDeviceIndex].iAudioNum+g_struDeviceInfo[m_dwDeviceIndex].iIPChanNum; i++)
	{
		if (i <= g_struDeviceInfo[m_dwDeviceIndex].iAudioNum)  //模拟语音对讲通道
		{
			sprintf(sTemp, "Audio%d", i);
			m_comboVoiceChan.AddString(sTemp);
		}
		else    // 数字语音对讲通道
		{
			
			if (i-g_struDeviceInfo[m_dwDeviceIndex].iAudioNum -1 <= MAX_CHANNUM_V40)
            {
                sprintf(sTemp, "DigitalAudio%d", i-g_struDeviceInfo[m_dwDeviceIndex].iAudioNum);
                m_comboVoiceChan.AddString(sTemp);
            }
			
			
			//             if (i-g_struDeviceInfo[m_dwDeviceIndex].iAudioNum -1 <= MAX_CHANNUM_V30)
			//             {
			//                 if (struDigitalChanState.byDigitalAudioChanTalkState[i-g_struDeviceInfo[m_dwDeviceIndex].iAudioNum -1])
			//                 {
			//                     sprintf(sTemp, "DigitalAudio%d", i-g_struDeviceInfo[m_dwDeviceIndex].iAudioNum);
			//                     m_comboVoiceChan.AddString(sTemp);
			//                 }
			//             }
			//             else if( (MAX_CHANNUM_V30 < (i-g_struDeviceInfo[m_dwDeviceIndex].iAudioNum -1))  && ((i-g_struDeviceInfo[m_dwDeviceIndex].iAudioNum -1) <= MAX_CHANNUM_V30 * 4))
			//             {
			//                 if (struDigitalChanState.byDigitalAudioChanTalkStateEx[i-g_struDeviceInfo[m_dwDeviceIndex].iAudioNum -1 -MAX_CHANNUM_V30])
			//                 {
			//                     sprintf(sTemp, "DigitalAudio%d", i-g_struDeviceInfo[m_dwDeviceIndex].iAudioNum);
			//                     m_comboVoiceChan.AddString(sTemp);
			//                 }
			//             }            
           
		}
	}

	
	m_comboVoiceChan.SetCurSel(0);
	m_comboDataType.SetCurSel(0);

	DWORD dwReturn = 0;
	
	memset(&m_struDigitalAudioState, 0, sizeof(NET_DVR_DIGITAL_CHANNEL_STATE));
	BOOL bRet = NET_DVR_GetDVRConfig(g_struDeviceInfo[m_dwDeviceIndex].lLoginID, NET_DVR_GET_DIGITAL_CHANNEL_STATE, 0, &m_struDigitalAudioState, sizeof(m_struDigitalAudioState), &dwReturn);
    if (!bRet)
    {
        g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DIGITAL_CHANNEL_STATE");
        g_StringLanType(szLan, "获取数字通道状态失败", "Fail to get digital channel config");
        //MessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_DIGITAL_CHANNEL_STATE");
    }


	memset(&m_struWorkState, 0, sizeof(NET_DVR_WORKSTATE_V30));
	if (!NET_DVR_GetDVRWorkState_V30(g_struDeviceInfo[m_dwDeviceIndex].lLoginID, &m_struWorkState))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDVRWorkState_V30 before Voice Talk");
		GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_HIDE);
        m_bGetWorkStatusSucc = FALSE;
        if (NET_DVR_GetLastError() == 23)
        {
            if (!NET_DVR_MatrixGetDeviceStatus(g_struDeviceInfo[m_dwDeviceIndex].lLoginID, &m_DecoderWorkStatus))
            {
                //tmp.Format("Error: NET_DVR_MatrixGetDeviceStatus = %d", NET_DVR_GetLastError());
                //AfxMessageBox(tmp);
            }
            else
            {
                for(int j = 0; j < 32; j++)
                {
                    g_MatrixDecAudioStatus[j] = (m_DecoderWorkStatus.byAudioInChanStatus >> j)&0x1;
                }
            }
        }
        //2009-8-29 matrix decode
        if (0 == g_MatrixDecAudioStatus[m_dwSel])
        {
            GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_SHOW);
            g_StringLanType(szLan, "状态:未使用", "Status: Unused");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
        else if (1 == g_MatrixDecAudioStatus[m_dwSel])
        {
            GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_SHOW);
            g_StringLanType(szLan, "状态:已使用", "Status: Used");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
        else if (0xff == g_MatrixDecAudioStatus[m_dwSel])
        {
            GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_HIDE);
        }
	}
	else
	{
        m_bGetWorkStatusSucc = TRUE;
		if (m_dwSel < g_struDeviceInfo[m_dwDeviceIndex].iAudioNum) // 模拟对讲通道
		{
		if (0 == m_struWorkState.byAudioChanStatus[m_dwSel])
		{
			GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_SHOW);
			g_StringLanType(szLan, "状态:未使用", "Status: Unused");
			GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
		}
		else if (1 == m_struWorkState.byAudioChanStatus[m_dwSel])
		{
			GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_SHOW);
			g_StringLanType(szLan, "状态:已使用", "Status: Used");
			GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
		}
		else if (0xff == m_struWorkState.byAudioChanStatus[m_dwSel])
		{
			GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_HIDE);
		}
	}
		else // 数字对讲通道
		{
			int iIndex = m_dwSel - g_struDeviceInfo[m_dwDeviceIndex].iAudioNum;
			if (0 == m_struDigitalAudioState.byDigitalAudioChanTalkState[iIndex])
			{
				GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_SHOW);
				g_StringLanType(szLan, "状态:未使用", "Status: Unused");
				GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			}
			else if (1 == m_struDigitalAudioState.byDigitalAudioChanTalkState[iIndex])
			{
				GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_SHOW);
				g_StringLanType(szLan, "状态:已使用", "Status: Used");
				GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			}
			else if (0xff == m_struDigitalAudioState.byDigitalAudioChanTalkState[iIndex])
			{
				GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_HIDE);
			}
		}
	}
	return TRUE;
}

/*********************************************************
  Function:	OnBtnStart
  Desc:		start to voice talk
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgVoiceTalk::OnBtnStart() 
{
	UpdateData(TRUE);
	char szLan[128] = {0};

	// 防止不选combox，而多次点击按钮，产生bug
    int nCount = m_comboVoiceChan.GetCount();
    if(0 == nCount)
    {
        m_dwSel = 0;
    }
    else
    {
        m_dwSel = m_comboVoiceChan.GetCurSel();
    }
	
	//m_dwSel = 32;
	DWORD dwVoiceChanNo = 0;
    if(m_dwSel < g_struDeviceInfo[m_dwDeviceIndex].iAudioNum)
    {
        dwVoiceChanNo = m_dwSel + 1;
    }   
    else
    { 
		dwVoiceChanNo = m_dwSel  - g_struDeviceInfo[m_dwDeviceIndex].iAudioNum + g_struDeviceInfo[m_dwDeviceIndex].byStartDTalkChan; //Digital voice talk Chan 
	}
	
	g_lVoiceHandle = NET_DVR_StartVoiceCom_V30(g_struDeviceInfo[m_dwDeviceIndex].lLoginID, dwVoiceChanNo, m_comboDataType.GetCurSel(), /*NULL*/fAudioTalkDataCallBack, /*NULL,*/ NULL);//fVoiceDataCallBack
    if (g_lVoiceHandle == -1)
    {
        g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartVoiceCom_V30 audio index[%d]", m_dwSel+1);
        
        if(m_dwSel < g_struDeviceInfo[m_dwDeviceIndex].iAudioNum)
        {
            g_StringLanType(szLan, "语音对讲失败", "Voice talk failed");
        }
        else
        {
            g_StringLanType(szLan, "数字语音对讲失败", "Digital voice talk failed");
        }
        
        AfxMessageBox(szLan);	
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartVoiceCom_V30 audio[%d]", m_dwSel+1);
    }

	EnableCtrl();
}

/*********************************************************
  Function:	OnBtnExit
  Desc:		exit the dialog
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgVoiceTalk::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDlgVoiceTalk::OnCancel();
}

/*********************************************************
  Function:	OnBtnStop
  Desc:		stop voice talk
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgVoiceTalk::OnBtnStop() 
{
	char szLan[128] = {0};
	if (g_lVoiceHandle >= 0)
	{
		if (NET_DVR_StopVoiceCom(g_lVoiceHandle))
		{
			g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopVoiceCom handle[%d]", g_lVoiceHandle);
			g_lVoiceHandle = -1;
		}
		else
		{
			g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopVoiceCom handle[%d]", g_lVoiceHandle);
			g_StringLanType(szLan, "关闭对讲失败", "Close Voice Talk failed");
			AfxMessageBox(szLan);	
		} 
	}
	EnableCtrl();	
}

/*********************************************************
  Function:	OnSelchangeComboVoiceChan
  Desc:		update state
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgVoiceTalk::OnSelchangeComboVoiceChan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_dwSel = m_comboVoiceChan.GetCurSel();
	char szLan[128] = {0};
    if (!m_bGetWorkStatusSucc)
    {
        //2009-8-29 matrix decode
        if (0 == g_MatrixDecAudioStatus[m_dwSel])
        {
            GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_SHOW);
            g_StringLanType(szLan, "状态:未使用", "Status: Unused");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
        else if (1 == g_MatrixDecAudioStatus[m_dwSel])
        {
            GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_SHOW);
            g_StringLanType(szLan, "状态:已使用", "Status: Used");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
        else if (0xff == g_MatrixDecAudioStatus[m_dwSel])
        {
            GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_HIDE);
        }
    }
    else
    {
		if (m_dwSel < g_struDeviceInfo[m_dwDeviceIndex].iAudioNum) // 模拟对讲通道
		{
			if (0 == m_struWorkState.byAudioChanStatus[m_dwSel])
			{
				GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_SHOW);
				g_StringLanType(szLan, "状态:未使用", "Status: Unused");
				GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			}
			else if (1 == m_struWorkState.byAudioChanStatus[m_dwSel])
			{
				GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_SHOW);
				g_StringLanType(szLan, "状态:已使用", "Status: Used");
				GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			}
			else if (0xff == m_struWorkState.byAudioChanStatus[m_dwSel])
			{
				GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_HIDE);
			}
		}
		else // 数字对讲通道
		{
			int iIndex = m_dwSel - g_struDeviceInfo[m_dwDeviceIndex].iAudioNum;
			if (0 == m_struDigitalAudioState.byDigitalAudioChanTalkState[iIndex])
			{
				GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_SHOW);
				g_StringLanType(szLan, "状态:未使用", "Status: Unused");
				GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			}
			else if (1 == m_struDigitalAudioState.byDigitalAudioChanTalkState[iIndex])
			{
				GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_SHOW);
				g_StringLanType(szLan, "状态:已使用", "Status: Used");
				GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			}
			else if (0xff == m_struDigitalAudioState.byDigitalAudioChanTalkState[iIndex])
			{
				GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_HIDE);
			}
		}
    }

}

/*********************************************************
  Function:	EnableCtrl
  Desc:		update the control status
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgVoiceTalk::EnableCtrl()
{
	BOOL bVoiceTalk = FALSE;
	char szLan[128] = {0};
	if (g_lVoiceHandle>=0)
	{
		bVoiceTalk = TRUE;
		g_StringLanType(szLan, "状态:已使用", "Status: Used");
		GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
	}
	else
	{
		bVoiceTalk = FALSE;
		g_StringLanType(szLan, "状态:未使用", "Status: Unused");
		GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
	}
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(bVoiceTalk);
	GetDlgItem(IDC_BTN_START)->EnableWindow(!bVoiceTalk);
	GetDlgItem(IDC_COMBO_VOICE_CHAN)->EnableWindow(!bVoiceTalk);
}

void CDlgVoiceTalk::OnBtnRefresh() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	memset(&m_struWorkState, 0, sizeof(NET_DVR_WORKSTATE_V30));
	if (!NET_DVR_GetDVRWorkState_V30(g_struDeviceInfo[m_dwDeviceIndex].lLoginID, &m_struWorkState))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDVRWorkState_V30 before Talk MR");
		GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_HIDE);
	}

	DWORD dwReturn = 0;
	char szLan[128] = {0};
	memset(&m_struDigitalAudioState, 0, sizeof(NET_DVR_DIGITAL_CHANNEL_STATE));
	BOOL bRet = NET_DVR_GetDVRConfig(g_struDeviceInfo[m_dwDeviceIndex].lLoginID, NET_DVR_GET_DIGITAL_CHANNEL_STATE, 0, &m_struDigitalAudioState, sizeof(m_struDigitalAudioState), &dwReturn);
    if (!bRet)
    {
        g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DIGITAL_CHANNEL_STATE");
        g_StringLanType(szLan, "获取数字通道状态失败", "Fail to get digital channel config");
        MessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_DIGITAL_CHANNEL_STATE");
    }

	OnSelchangeComboVoiceChan();
}
