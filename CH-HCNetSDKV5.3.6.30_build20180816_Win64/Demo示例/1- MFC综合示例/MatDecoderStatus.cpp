// MatDecoderStatus.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "MatDecoderStatus.h"
#include <new.h>
#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define DEVICESTATUS_TIMER	WM_USER + 1
/////////////////////////////////////////////////////////////////////////////
// CMatDecoderStatus dialog

BYTE g_MatrixDecAudioStatus[32] = {0xff};//0 - not used;1 - used; 0xff - not support

CMatDecoderStatus::CMatDecoderStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CMatDecoderStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatDecoderStatus)
	//}}AFX_DATA_INIT
}


void CMatDecoderStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatDecoderStatus)
	DDX_Control(pDX, IDC_COMBOAUDIO2, m_Audio2Ctrl);
	DDX_Control(pDX, IDC_COMBOAUDIO1, m_Audio1Ctrl);
	DDX_Control(pDX, IDC_LIST_SUBWND, m_SubWndList);
	//DDX_Control(pDX, IDC_COMBOAUDIO, m_comboAudio);
	DDX_Control(pDX, IDC_COMBO_SUBWND, m_SubWndCtrl);
	DDX_Control(pDX, IDC_LIST_ALARMSTATUS, m_AlarmList);
	DDX_Control(pDX, IDC_LIST_DISPCHANSTATUS, m_DispList);
	DDX_Control(pDX, IDD_DECODECHANSTATUS, m_DecList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMatDecoderStatus, CDialog)
	//{{AFX_MSG_MAP(CMatDecoderStatus)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_CBN_SELCHANGE(IDC_COMBO_SUBWND, OnSelchangeComboSubwnd)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatDecoderStatus message handlers

BOOL CMatDecoderStatus::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    CString tmp;
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    
	memset(&m_Ability, 0, sizeof(NET_DVR_MATRIX_ABILITY_V41));
    if (!NET_DVR_GetDeviceAbility(m_lServerID, MATRIXDECODER_ABILITY_V41, NULL, 0, (char*)&m_Ability, sizeof(NET_DVR_MATRIX_ABILITY_V41)))
    {
        tmp.Format("Error code:%d", NET_DVR_GetLastError());
        AfxMessageBox(tmp);
        return FALSE;
    }
    else
    {        
        m_lStartChan = m_Ability.byStartChan;
        m_iChannelNumber = m_Ability.byDecChanNums;
        m_iVGANums = m_Ability.struVgaInfo.byChanNums;
        m_iBNCNums = m_Ability.struBncInfo.byChanNums;
		m_iHDMINums = m_Ability.struHdmiInfo.byChanNums;
		m_iDVINums = m_Ability.struDviInfo.byChanNums;
		m_iSDINums = m_Ability.struSDIInfo.byChanNums; 
    }
    
	memset(&m_struDeviceCfg, 0, sizeof(m_struDeviceCfg));
	m_struDeviceCfg.dwSize = sizeof(m_struDeviceCfg);
	DWORD dwReturned = 0;
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_DEVICECFG_V40, -1, &m_struDeviceCfg, sizeof(m_struDeviceCfg), &dwReturned))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return FALSE;
	}
    char szLan[128] = {0};
	int ChanNo = 0;
    int i;

	for(i = 0; i < m_iVGANums; i++)
    {
        //ChanNo = m_lStartChan + i;
        g_StringLanType(szLan, "VGA", "VGA");
        //tmp.Format("%s %d", szLan, ChanNo);
		tmp.Format("%s %d", szLan, i+1);
        m_SubWndCtrl.InsertString(i, tmp);
    }    

	for(i = 0; i < m_iBNCNums; i++)
    {
        //ChanNo = m_lStartChan + i;
        g_StringLanType(szLan, "BNC", "BNC");
        //tmp.Format("%s %d", szLan, ChanNo - m_iVGANums);
        tmp.Format("%s %d", szLan, i+1);
		m_SubWndCtrl.InsertString(i+m_iVGANums, tmp);
    }	
    

	for(i = 0; i < m_iHDMINums; i++)
    {
        ChanNo = m_lStartChan + i;
        g_StringLanType(szLan, "HDMI", "HDMI");
        //tmp.Format("%s %d", szLan, ChanNo - m_iVGANums - m_iBNCNums);
        tmp.Format("%s %d", szLan, i+1);
		m_SubWndCtrl.InsertString(i+m_iVGANums+m_iBNCNums, tmp);
    }

	for(i = 0; i < m_iDVINums; i++)
    {
        ChanNo = m_lStartChan + i;
        g_StringLanType(szLan, "DVI", "DVI");
        //tmp.Format("%s %d", szLan, ChanNo - m_iVGANums - m_iBNCNums - m_iHDMINums);
        tmp.Format("%s %d", szLan, i+1);
		m_SubWndCtrl.InsertString(i+m_iVGANums+m_iBNCNums+m_iHDMINums, tmp);
    }
	for(i = 0; i < m_iSDINums; i++)
    {
        ChanNo = m_lStartChan + i;
        g_StringLanType(szLan, "SDI", "SDI");
        //tmp.Format("%s %d", szLan, ChanNo - m_iVGANums - m_iBNCNums - m_iHDMINums);
        tmp.Format("%s %d", szLan, i+1);
		m_SubWndCtrl.InsertString(i+m_iVGANums+m_iBNCNums+m_iHDMINums+m_iDVINums, tmp);
    }
    m_SubWndCtrl.SetCurSel(0);
    
    m_DecList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "解码通道", "Decoder Chan");
    m_DecList.InsertColumn(0, szLan, LVCFMT_LEFT, 70, -1);
    g_StringLanType(szLan, "解码状态", "Dec Status");
    m_DecList.InsertColumn(1, szLan, LVCFMT_LEFT, 70, -1);
    g_StringLanType(szLan, "码流类型", "StreamType");
    m_DecList.InsertColumn(2, szLan, LVCFMT_LEFT, 70, -1);
    g_StringLanType(szLan, "打包方式", "PacketType");
    m_DecList.InsertColumn(3, szLan, LVCFMT_LEFT, 70, -1);
    g_StringLanType(szLan, "DSP CPU利用率", "Cpu Use");
    m_DecList.InsertColumn(4, szLan, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLan, "视频帧率", "Vedio Frame");
    m_DecList.InsertColumn(5, szLan, LVCFMT_LEFT, 70, -1);
    g_StringLanType(szLan, "音频帧率", "Audio Frame");
    m_DecList.InsertColumn(6, szLan, LVCFMT_LEFT, 70, -1);
    g_StringLanType(szLan, "已解视频帧", "Passed Vedio");
    m_DecList.InsertColumn(7, szLan, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLan, "已解音频帧", "Passed Audio");
    m_DecList.InsertColumn(8, szLan, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLan, "图像宽", "ImageW");
    m_DecList.InsertColumn(9, szLan, LVCFMT_LEFT, 50, -1);
    g_StringLanType(szLan, "图像高", "ImageH");
    m_DecList.InsertColumn(10, szLan, LVCFMT_LEFT, 50, -1);
    g_StringLanType(szLan, "视频制式", "PAL/NTSC");
    m_DecList.InsertColumn(11, szLan, LVCFMT_LEFT, 50, -1);
    
    m_DispList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "显示通道", "Disp Chan");
    m_DispList.InsertColumn(0, szLan, LVCFMT_LEFT, 70, -1);
    g_StringLanType(szLan, "显示状态", "Disp Status");
    m_DispList.InsertColumn(1, szLan, LVCFMT_LEFT, 70, -1);
    g_StringLanType(szLan, "通道类型", "Chan Type");
    m_DispList.InsertColumn(2, szLan, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLan, "视频制式", "PAL/NTSC");
    m_DispList.InsertColumn(3, szLan, LVCFMT_LEFT, 70, -1);
    g_StringLanType(szLan, "当前画面模式", "Sub Window");
    m_DispList.InsertColumn(4, szLan, LVCFMT_LEFT, 90, -1);
    g_StringLanType(szLan, "屏幕模式", "Screen Mode");
    m_DispList.InsertColumn(5, szLan, LVCFMT_LEFT, 70, -1);
    
    m_AlarmList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "报警输入号", "AlarmIn Chan");
    m_AlarmList.InsertColumn(0, szLan, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLan, "报警输入状态", "AlarmIn Chan Status");
    m_AlarmList.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLan, "报警输出号", "AlarmOut Chan");
    m_AlarmList.InsertColumn(2, szLan, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLan, "报警输出状态", "AlarmOut Chan Status");
    m_AlarmList.InsertColumn(3, szLan, LVCFMT_LEFT, 100, -1);

    m_SubWndList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "子画面号", "Disp Chan");
    m_SubWndList.InsertColumn(0, szLan, LVCFMT_LEFT, 90, -1);
    g_StringLanType(szLan, "关联解码通道", "Join DecChan");
    m_SubWndList.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLan, "显示帧率", "Disp Frame");
    m_SubWndList.InsertColumn(2, szLan, LVCFMT_LEFT, 80, -1);
    

	switch (m_struDeviceCfg.byDVRType)
	{
	//B10 系列调用NET_DVR_DECODER_WORK_STATUS_V41接口
	case DS_B10_XY:
	case DS_B11_M_CLASS:
	case DS_B12_M_CLASS:
		UseMatrixGetDeviceStatusV41();  
		break; 
	default :
	OnButton1();
	}

	
	SetTimer(NULL, 10000, NULL);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMatDecoderStatus::OnButton1() 
{
	// TODO: Add your control notification handler code here
    CString tmp;
    char szLan[128] = {0};
    m_SubWndList.DeleteAllItems();
    m_AlarmList.DeleteAllItems();
    m_DecList.DeleteAllItems();
    m_DispList.DeleteAllItems();

	BYTE byVGA = 1;
	BYTE byDVI = 1;
	BYTE byHDMI = 1;
	BYTE byBNC = 1;

	DWORD dwDecChanNum = 0;
	DWORD dwDispChanNum = 0;
	DWORD dwAlarmInNum = 0;
	DWORD dwAlarmOutNum = 0;	

	memset(m_struDecChanStatus, 0 ,sizeof(m_struDecChanStatus));
	memset(m_struDispChanStatus, 0, sizeof(m_struDispChanStatus));
	memset(m_dwAlarmInStatus, 0, sizeof(m_dwAlarmInStatus));
	memset(m_dwAlarmOutStatus, 0, sizeof(m_dwAlarmOutStatus));
	m_dwAudioInChanStatus[0] = 0;
	m_dwAudioInChanStatus[1] = 0;

	char *pTemp = new/*(std::nothrow)*/ char[1024 * 1024];
	if (pTemp == NULL)
	{
		AfxMessageBox("Alloc memory error");
		return;
	}	

// 测试单个
// 	NET_DVR_MATRIX_CHAN_STATUS struTempStatus = { 0 };
// 	int iDecChan = 1;
// 	int iStatus = 0;
// 	if (!NET_DVR_GetDeviceStatus(m_lServerID, NET_DVR_GET_DEC_CHAN_STATUS, 1, &iDecChan, 4, &iStatus, &struTempStatus, sizeof(struTempStatus)))
// 	{
// 		int iError = NET_DVR_GetLastError();
// 		//qDebug("[DisplayCtrl][TvwallCtrl][GetDecoderStatus] faild:[NET_DVR_GetDeviceStatus],lastError:%d", iError);
// 		return;
// 	}
	
	int iStatus = 0;
	NET_DVR_DISP_CHAN_STATUS_V41 struTempStatus = { 0 };
	int iDispChan = 1;
	if (!NET_DVR_GetDeviceStatus(m_lServerID, NET_DVR_GET_DISP_CHAN_STATUS, 1, &iDispChan, 4, &iStatus, &struTempStatus, sizeof(struTempStatus)))
	{
		int iError = NET_DVR_GetLastError();
		//qDebug("[DisplayCtrl][TvwallCtrl][GetDecoderStatus] faild:[NET_DVR_GetDeviceStatus],lastError:%d", iError);
		return;
    }
	

	if (!NET_DVR_GetDeviceStatus(m_lServerID, NET_DVR_GET_DEC_CHAN_STATUS, 0xffffffff, NULL, 0, NULL, pTemp, 1024*1024))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DEC_CHAN_STATUS");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_DEC_CHAN_STATUS");		
		memcpy(m_struDecChanStatus, pTemp + 4, g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum * sizeof(NET_DVR_MATRIX_CHAN_STATUS));
	}

	if (!NET_DVR_GetDeviceStatus(m_lServerID, NET_DVR_GET_DISP_CHAN_STATUS, 0xffffffff, NULL, 0, NULL, pTemp, 1024*1024))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DISP_CHAN_STATUS");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_DISP_CHAN_STATUS");
		m_dwDispCount = *((DWORD *)pTemp);
		memcpy(m_struDispChanStatus, pTemp + 4, m_dwDispCount * sizeof(NET_DVR_DISP_CHAN_STATUS_V41));
	}

	if (!NET_DVR_GetDeviceStatus(m_lServerID, NET_DVR_GET_ALARMIN_STATUS, 0xffffffff, NULL, 0, NULL, pTemp, 1024 * 1024))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMIN_STATUS");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMIN_STATUS");
		memcpy(m_dwAlarmInStatus, pTemp + 4, g_struDeviceInfo[m_iDeviceIndex].iAlarmInNum * 4);
	}

	if (!NET_DVR_GetDeviceStatus(m_lServerID, NET_DVR_GET_ALARMOUT_STATUS, 0xffffffff, NULL, 0, NULL, pTemp, 1024 * 1024))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMOUT_STATUS");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMOUT_STATUS");
		memcpy(m_dwAlarmOutStatus, pTemp + 4, g_struDeviceInfo[m_iDeviceIndex].iAlarmOutNum * 4);
	}

	DWORD dwAudioChan = 1;
	if (!NET_DVR_GetDeviceStatus(m_lServerID, NET_DVR_GET_AUDIO_CHAN_STATUS, 1, &dwAudioChan, 4, NULL, &m_dwAudioInChanStatus[0], 4))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_AUDIO_CHAN_STATUS");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_AUDIO_CHAN_STATUS");
	}
	dwAudioChan = 2;
	if (!NET_DVR_GetDeviceStatus(m_lServerID, NET_DVR_GET_AUDIO_CHAN_STATUS, 1, &dwAudioChan, 4, NULL, &m_dwAudioInChanStatus[1], 4))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_AUDIO_CHAN_STATUS");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_AUDIO_CHAN_STATUS");
	}

// 	memset(&m_DecoderWorkStatus, 0, sizeof(NET_DVR_DECODER_WORK_STATUS_V41));
//     if (!NET_DVR_MatrixGetDeviceStatus_V41(m_lServerID, &m_DecoderWorkStatus))
//     {
//         tmp.Format("Error: NET_DVR_MatrixGetDeviceStatus = %d", NET_DVR_GetLastError());
//         AfxMessageBox(tmp);
//     }
//     else
//     {
        m_Audio1Ctrl.SetCurSel(m_dwAudioInChanStatus[0]);
        m_Audio2Ctrl.SetCurSel(m_dwAudioInChanStatus[1]);
		int j = 0;
        for(j = 0; j < 2; j++)
        {
            g_MatrixDecAudioStatus[j] = m_dwAudioInChanStatus[j];
        }
		int i = 0;
        for(i = 0;i < m_iChannelNumber; i++)
        {
            tmp.Empty();
            tmp.Format("%d", i + m_lStartChan);
            m_DecList.InsertItem(i, tmp, 0);
            
            tmp.Empty();
            if (m_struDecChanStatus[i].byDecodeStatus == 0)
            {
                g_StringLanType(szLan, "未启动", "not started");
                tmp.Format("%s", szLan);
            }
            else
            {
                g_StringLanType(szLan, "已启动", "already started");
                tmp.Format("%s", szLan);
            }
            m_DecList.SetItemText(i, 1, szLan);
            
            tmp.Empty();
            if (m_struDecChanStatus[i].byStreamType == 0)
            {
                tmp = "Unknown";
            }
            else if (m_struDecChanStatus[i].byStreamType == 1)
            {
                tmp = "Private H264";
            }
            else if (m_struDecChanStatus[i].byStreamType == 2)
            {
                tmp = "Standard H264";
            }
            else if (m_struDecChanStatus[i].byStreamType == 3)
            {
                tmp = "MPEG4";
            }
			else if (m_struDecChanStatus[i].byStreamType == 4)
            {
                tmp = "Original Stream";
            }
            else if (m_struDecChanStatus[i].byStreamType == 5)
            {
                tmp = "Picture";
            }
			else if (m_struDecChanStatus[i].byStreamType == 6)
			{
				tmp = "MJPEG";
			}
			else if (m_struDecChanStatus[i].byStreamType == 7)
			{
				tmp = "MPEG2";
			}
            m_DecList.SetItemText(i, 2, tmp);

            tmp.Empty();
            if (m_struDecChanStatus[i].byPacketType == 0)
            {
                tmp = "Unknown";
            }
            else if (m_struDecChanStatus[i].byPacketType == 1)
            {
                tmp = "PRIVT";
            }
            else if (m_struDecChanStatus[i].byPacketType == 7)
            {
                tmp = "TS";
            }
            else if (m_struDecChanStatus[i].byPacketType == 8)
            {
                tmp = "PS";
            }
            else if (m_struDecChanStatus[i].byPacketType == 9)
            {
                tmp = "RTP";
            }
			else if (m_struDecChanStatus[i].byPacketType == 10)
			{
				tmp = "Origin";
			}
            m_DecList.SetItemText(i, 3, tmp);

            tmp.Empty();
            tmp.Format("%d", m_struDecChanStatus[i].byCpuLoad);
            m_DecList.SetItemText(i, 4, tmp);

			tmp.Empty();
			switch(m_struDecChanStatus[i].byFpsDecV)
			{
			case LOW_DEC_FPS_1_2:
				tmp.Format("1/2");
				break;
				
			case LOW_DEC_FPS_1_4:
				tmp.Format("1/4");
				break;
				
			case LOW_DEC_FPS_1_8:
				tmp.Format("1/8");
				break;
				
			case LOW_DEC_FPS_1_16:
				tmp.Format("1/16");
				break;
				
			default:
				tmp.Format("%d", m_struDecChanStatus[i].byFpsDecV);
				break;
			}   
            m_DecList.SetItemText(i, 5, tmp);
            
			tmp.Empty();
			switch(m_struDecChanStatus[i].byFpsDecA)
			{
			case LOW_DEC_FPS_1_2:
				tmp.Format("1/2");
				break;
				
			case LOW_DEC_FPS_1_4:
				tmp.Format("1/4");
				break;
				
			case LOW_DEC_FPS_1_8:
				tmp.Format("1/8");
				break;
				
			case LOW_DEC_FPS_1_16:
				tmp.Format("1/16");
				break;
				
			default:
				tmp.Format("%d", m_struDecChanStatus[i].byFpsDecA);
				break;
			}   
            m_DecList.SetItemText(i, 6, tmp);
           
            
            tmp.Empty();
            tmp.Format("%d", m_struDecChanStatus[i].dwDecodedV);
            m_DecList.SetItemText(i, 7, tmp);
            
            tmp.Empty();
            tmp.Format("%d", m_struDecChanStatus[i].dwDecodedA);
            m_DecList.SetItemText(i, 8, tmp);     
            
            tmp.Empty();
            tmp.Format("%d", m_struDecChanStatus[i].wImgW);
            m_DecList.SetItemText(i, 9, tmp);
            
            tmp.Empty();
            tmp.Format("%d", m_struDecChanStatus[i].wImgH);
            m_DecList.SetItemText(i, 10, tmp);
            
            tmp.Empty();
            if (m_struDecChanStatus[i].byVideoFormat == 2)
            {
                tmp = "PAL";
            }
            else if(m_struDecChanStatus[i].byVideoFormat == 1)
            {
                tmp = "NTSC";
            }
            else
            {
                tmp = "NULL";
            }
            m_DecList.SetItemText(i, 11, tmp);

			tmp.Empty();

        }
        
// 		if (DS630X_D == m_struDeviceCfg.byDVRType || DS_6504D_B10 == m_struDeviceCfg.byDVRType)
// 		{
// 			for (i = 0; i < m_iVGANums; i++)
// 			{
// 				tmp.Empty();
// 				tmp.Format("VGA%d", i + 1);
// 				m_DispList.InsertItem(i, tmp, 0);
// 				
// 				tmp.Empty();
// 				if (m_DecoderWorkStatus.struDispChanStatus[i].byDispStatus == 0)
// 				{
// 					g_StringLanType(szLan, "未显示", "not displayed");
// 					tmp = "未显示";
// 				}
// 				else
// 				{
// 					g_StringLanType(szLan, "已显示", "already displayed");
// 					tmp = "已显示";
// 				}
// 				m_DispList.SetItemText(i, 1, szLan);
// 				
// 				tmp.Empty();
// 				if (m_DecoderWorkStatus.struDispChanStatus[i].byBVGA == 0)
// 				{
// 					tmp = "BNC";
// 				}
// 				else
// 				{
// 					tmp = "VGA";
// 				}
// 				m_DispList.SetItemText(i, 2, tmp);
// 				
// 				tmp.Empty();
// 				if (m_DecoderWorkStatus.struDispChanStatus[i].byVideoFormat == 1)
// 				{
// 					tmp = "NTSC";
// 				}
// 				else if(m_DecoderWorkStatus.struDispChanStatus[i].byVideoFormat == 2)
// 				{
// 					tmp = "PAL";
// 				}
// 				else
// 				{
// 					tmp = "NULL";
// 				}
// 				m_DispList.SetItemText(i, 3, tmp);
// 				
// 				tmp.Empty();
// 				TRACE("lk---- %d ----- i %d", m_DecoderWorkStatus.struDispChanStatus[i].byWindowMode, i);
// 				tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[i].byWindowMode);
// 				m_DispList.SetItemText(i, 4, tmp);
// 			}
// 			
// 			for (i = m_iVGANums; i < m_iVGANums + m_iBNCNums; i++)
// 			{
// 				tmp.Empty();
// 				tmp.Format("BNC%d", i - m_iVGANums + 1);
// 				m_DispList.InsertItem(i, tmp, 0);
// 				
// 				tmp.Empty();
// 				if (m_DecoderWorkStatus.struDispChanStatus[i + 8 - m_iVGANums].byDispStatus == 0)
// 				{
// 					g_StringLanType(szLan, "未显示", "not displayed");
// 					tmp = "未显示";
// 				}
// 				else
// 				{
// 					g_StringLanType(szLan, "已显示", "already displayed");
// 					tmp = "已显示";
// 				}
// 				m_DispList.SetItemText(i, 1, szLan);
// 				
// 				tmp.Empty();
// 				if (m_DecoderWorkStatus.struDispChanStatus[i + 8 - m_iVGANums].byBVGA == 0)
// 				{
// 					tmp = "BNC";
// 				}
// 				else
// 				{
// 					tmp = "VGA";
// 				}
// 				m_DispList.SetItemText(i, 2, tmp);
// 				
// 				tmp.Empty();
// 				if (m_DecoderWorkStatus.struDispChanStatus[i + 8 - m_iVGANums].byVideoFormat == 1)
// 				{
// 					tmp = "NTSC";
// 				}
// 				else if(m_DecoderWorkStatus.struDispChanStatus[i + 8 - m_iVGANums].byVideoFormat == 2)
// 				{
// 					tmp = "PAL";
// 				}
// 				else
// 				{
// 					tmp = "NULL";
// 				}
// 				m_DispList.SetItemText(i, 3, tmp);
// 				
// 				tmp.Empty();
// 				tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[i + 8 - m_iVGANums].byWindowMode);
// 				m_DispList.SetItemText(i, 4, tmp);
// 			}
// 		}
// 		else if (DS610X_D ==m_struDeviceCfg.byDVRType || DS640X_HD == m_struDeviceCfg.byDVRType || DS64XXHD_T == m_struDeviceCfg.wDevType ||DS63XXD_T == m_struDeviceCfg.wDevType ||DS_65XXD == m_struDeviceCfg.wDevType)
// 		{    
			for (i = 0; i < m_iBNCNums + m_iVGANums + m_iHDMINums + m_iDVINums; i++)
			{
				tmp.Empty();
				if (m_struDispChanStatus[i].byBVGA == 0)
				{
					tmp.Format("BNC%d", byBNC);
					m_DispList.InsertItem(i, tmp, 0);
					tmp = "BNC";
					byBNC++;
				}
				else if (m_struDispChanStatus[i].byBVGA == 1)
				{
					tmp.Format("VGA%d", byVGA);
					m_DispList.InsertItem(i, tmp, 0);
					tmp = "VGA";
					byVGA++;
				}
				else if (m_struDispChanStatus[i].byBVGA == 2)
				{
					tmp.Format("HDMI%d", byHDMI);
					m_DispList.InsertItem(i, tmp, 0);
					tmp = "HDMI";
					byHDMI++;
				}
				else if (m_struDispChanStatus[i].byBVGA == 3)
				{
					tmp.Format("DVI%d", byDVI);
					m_DispList.InsertItem(i, tmp, 0);
					tmp = "DVI";
					byDVI++;
				}
				m_DispList.SetItemText(i, 2, tmp);
				
				tmp.Empty();
				if (m_struDispChanStatus[i].byDispStatus == 0)
				{
					g_StringLanType(szLan, "未显示", "not displayed");
					tmp.Format("%s", szLan);
				}
				else
				{
					g_StringLanType(szLan, "已显示", "already displayed");
					tmp.Format("%s", szLan);
				}
				m_DispList.SetItemText(i, 1, szLan);
				
				tmp.Empty();
				if (m_struDispChanStatus[i].byVideoFormat == 1)
				{
					tmp = "NTSC";
				}
				else if(m_struDispChanStatus[i].byVideoFormat == 2)
				{
					tmp = "PAL";
				}
				else
				{
					tmp = "NULL";
				}
				m_DispList.SetItemText(i, 3, tmp);
				
				tmp.Empty();
				tmp.Format("%d", m_struDispChanStatus[i].byWindowMode);
				m_DispList.SetItemText(i, 4, tmp);

				tmp.Empty();
				if (m_struDispChanStatus[i].byScreenMode == 1)
				{
					g_StringLanType(szLan, "大屏", "Big screen");
					tmp.Format("%s", szLan);
				}
				else
				{
					g_StringLanType(szLan, "普通", "Ordinary");
					tmp.Format("%s", szLan);
				}
				m_DispList.SetItemText(i, 5, tmp);
			}
	/*	}*/
       
        for (i = 0; i < 32; i++)
        {
            tmp.Empty();
            tmp.Format("%d", i + m_lStartChan);
            m_AlarmList.InsertItem(i, tmp, 0);
            
            tmp.Empty();
            tmp.Format("%d", m_dwAlarmInStatus[i]);
            m_AlarmList.SetItemText(i, 1, tmp);
            
            tmp.Empty();
            tmp.Format("%d", i + m_lStartChan);
            m_AlarmList.SetItemText(i, 2, tmp);
            
            tmp.Empty();
            tmp.Format("%d", m_dwAlarmOutStatus[i]);
            m_AlarmList.SetItemText(i, 3, tmp);
        }
    
		OnSelchangeComboSubwnd();
		/*int iSubWnd = m_SubWndCtrl.GetCurSel();
        for (i = 0; i < MAX_WINDOWS; i++)
        {
            tmp.Empty();
            tmp.Format("%d", i + m_lStartChan);
            m_SubWndList.InsertItem(i, tmp, 0);
            
            tmp.Empty();
            tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[iSubWnd].byJoinDecChan[i]);
            m_SubWndList.SetItemText(i, 1, tmp);
            
            tmp.Empty();
            tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[iSubWnd].byFpsDisp[i]);
            m_SubWndList.SetItemText(i, 2, tmp);
        }*/
      //}
    
      UpdateData(FALSE);
      //OnSelchangeComboSubwnd();

	  if (NULL != pTemp)
	  {
		  delete []pTemp;
	  }
}

void CMatDecoderStatus::OnSelchangeComboSubwnd() 
{
	UpdateData(TRUE);
    CString tmp;
    m_SubWndList.DeleteAllItems();
	if (DS630X_D == m_struDeviceCfg.byDVRType)
	{
		if (m_SubWndCtrl.GetCurSel() < m_iVGANums)
		{
			for (int i = 0; i < 16; i++)
			{
				tmp.Empty();
				tmp.Format("%d", i + m_lStartChan);
				m_SubWndList.InsertItem(i, tmp, 0);
				
				tmp.Empty();
				tmp.Format("%d", m_struDispChanStatus[m_SubWndCtrl.GetCurSel()].byJoinDecChan[i]);
				m_SubWndList.SetItemText(i, 1, tmp);
				
				tmp.Empty();
				tmp.Format("%d", m_struDispChanStatus[m_SubWndCtrl.GetCurSel()].byFpsDisp[i]);
				m_SubWndList.SetItemText(i, 2, tmp);
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				tmp.Empty();
				tmp.Format("%d", i + m_lStartChan);
				m_SubWndList.InsertItem(i, tmp, 0);
				
				tmp.Empty();
				tmp.Format("%d", m_struDispChanStatus[m_SubWndCtrl.GetCurSel()].byJoinDecChan[i]);
				m_SubWndList.SetItemText(i, 1, tmp);
				
				tmp.Empty();
				tmp.Format("%d", m_struDispChanStatus[m_SubWndCtrl.GetCurSel()].byFpsDisp[i]);
				m_SubWndList.SetItemText(i, 2, tmp);
			}
		}
	}
	else
	{
		/*if (m_SubWndCtrl.GetCurSel() < m_iVGANums)
		{
			for (int i = 0; i < 16; i++)
			{
				tmp.Empty();
				tmp.Format("%d", i + m_lStartChan);
				m_SubWndList.InsertItem(i, tmp, 0);
				
				tmp.Empty();
				tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[m_SubWndCtrl.GetCurSel()].byJoinDecChan[i]);
				m_SubWndList.SetItemText(i, 1, tmp);
				
				tmp.Empty();
				tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[m_SubWndCtrl.GetCurSel()].byFpsDisp[i]);
				m_SubWndList.SetItemText(i, 2, tmp);
			}
		}
		else
		{
			for (int i = 0; i < 16; i++)
			{
				tmp.Empty();
				tmp.Format("%d", i + m_lStartChan);
				m_SubWndList.InsertItem(i, tmp, 0);
				
				tmp.Empty();
				tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[m_SubWndCtrl.GetCurSel()].byJoinDecChan[i]);
				m_SubWndList.SetItemText(i, 1, tmp);
				
				tmp.Empty();
				tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[m_SubWndCtrl.GetCurSel()].byFpsDisp[i]);
				m_SubWndList.SetItemText(i, 2, tmp);
			}
		}*/
		LPNET_DVR_DISP_CHAN_STATUS_V41  struDispChanStatus = NULL; 
		switch (m_struDeviceCfg.byDVRType)
		{
		//B10 系列调用NET_DVR_DECODER_WORK_STATUS_V41接口
		case DS_B10_XY:
		case DS_B11_M_CLASS:
		case DS_B12_M_CLASS:
			struDispChanStatus = m_DecoderWorkStatus.struDispChanStatus; 
			break; 
		default :
			struDispChanStatus =  m_struDispChanStatus;
		}
		for (int i = 0; i < MAX_WINDOWS; i++)
		{
			tmp.Empty();
			tmp.Format("%d", i + m_lStartChan);
			m_SubWndList.InsertItem(i, tmp, 0);
			
			tmp.Empty();
			tmp.Format("%d", struDispChanStatus[m_SubWndCtrl.GetCurSel()].byJoinDecChan[i]);
			m_SubWndList.SetItemText(i, 1, tmp);
			
			tmp.Empty();
			tmp.Format("%d", struDispChanStatus[m_SubWndCtrl.GetCurSel()].byFpsDisp[i]);
			m_SubWndList.SetItemText(i, 2, tmp);
		}	
	}	
    UpdateData(FALSE);
}

#if (_MSC_VER >= 1500)	//vs2008
void CMatDecoderStatus::OnTimer(UINT_PTR nIDEvent)
#else
void CMatDecoderStatus::OnTimer(UINT nIDEvent) 
#endif
{
	// TODO: Add your message handler code here and/or call default
	switch (m_struDeviceCfg.byDVRType)
	{
		//B10 系列调用NET_DVR_DECODER_WORK_STATUS_V41接口
	case DS_B10_XY:
	case DS_B11_M_CLASS:
	case DS_B12_M_CLASS:
		UseMatrixGetDeviceStatusV41();  
		break; 
	default :
	OnButton1();
	}
	CDialog::OnTimer(nIDEvent);
}

void CMatDecoderStatus::OnExit() 
{
	// TODO: Add your control notification handler code here
    CDialog::OnCancel();
}



void CMatDecoderStatus::UseMatrixGetDeviceStatusV41()
{
	memset(&m_DecoderWorkStatus, 0, sizeof(NET_DVR_DECODER_WORK_STATUS_V41));
	if (!NET_DVR_MatrixGetDeviceStatus_V41(m_lServerID, &m_DecoderWorkStatus))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MatrixGetDeviceStatus_V41" );
		return ; 
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MatrixGetDeviceStatus_V41");

	char szLan[128]; 
	char *pStreamType[] = {"Unknown", "Private H264", "Standard H264", "MPEG4", "Original Stream", "Picture", "MJPEG", "MPEG2"}; 
	CString tmp; 
	int i = 0; 
	LPNET_DVR_MATRIX_CHAN_STATUS struDecChanStatus = m_DecoderWorkStatus.struDecChanStatus; 
	for(i = 0;i < MAX_DECODECHANNUM; i++)
    {
		tmp.Format("%d", i + m_lStartChan);
        m_DecList.InsertItem(i, tmp, 0);

        if (struDecChanStatus[i].byDecodeStatus == 0)
        {
			g_StringLanType(szLan, "未启动", "not started");   
        }
        else
        {
			g_StringLanType(szLan, "已启动", "already started");         
        }
        m_DecList.SetItemText(i, 1, szLan);

        if (struDecChanStatus[i].byStreamType <= 7)
        {
			tmp = pStreamType[struDecChanStatus[i].byStreamType];
			m_DecList.SetItemText(i, 2, tmp);
        }
		switch (struDecChanStatus[i].byPacketType)
		{
		case 0:
			tmp = "Unknown";
			break; 
		case 1:
			tmp = "PRIVT";
			break; 
		case 7:
			tmp = "TS";
			break; 
		case 8:
			tmp = "PS";
			break; 
		case 9:
			tmp = "RTP";
			break; 
		case 10:
			tmp = "Origin";
			break; 
		default:
			tmp = ""; 
		}
        m_DecList.SetItemText(i, 3, tmp);
        tmp.Format("%d", struDecChanStatus[i].byCpuLoad);
        m_DecList.SetItemText(i, 4, tmp);
		switch(struDecChanStatus[i].byFpsDecV)
		{
		case LOW_DEC_FPS_1_2:
			tmp.Format("1/2");
			break;		
		case LOW_DEC_FPS_1_4:
			tmp.Format("1/4");
			break;
		case LOW_DEC_FPS_1_8:
			tmp.Format("1/8");
			break;			
		case LOW_DEC_FPS_1_16:
			tmp.Format("1/16");
			break;		
		default:
			tmp.Format("%d", struDecChanStatus[i].byFpsDecV);
			break;
		}   
        m_DecList.SetItemText(i, 5, tmp);          
		switch(struDecChanStatus[i].byFpsDecA)
		{
		case LOW_DEC_FPS_1_2:
			tmp.Format("1/2");
			break;
			
		case LOW_DEC_FPS_1_4:
			tmp.Format("1/4");
			break;
			
		case LOW_DEC_FPS_1_8:
			tmp.Format("1/8");
			break;
			
		case LOW_DEC_FPS_1_16:
			tmp.Format("1/16");
			break;
			
		default:
			tmp.Format("%d", struDecChanStatus[i].byFpsDecA);
			break;
		}   
		m_DecList.SetItemText(i, 6, tmp);  
		
		tmp.Format("%d", struDecChanStatus[i].dwDecodedV);
		m_DecList.SetItemText(i, 7, tmp);
		
		tmp.Format("%d", struDecChanStatus[i].dwDecodedA);
		m_DecList.SetItemText(i, 8, tmp);     
		
		tmp.Format("%d", struDecChanStatus[i].wImgW);
		m_DecList.SetItemText(i, 9, tmp);
		
		tmp.Format("%d", struDecChanStatus[i].wImgH);
		m_DecList.SetItemText(i, 10, tmp);
            
        if (struDecChanStatus[i].byVideoFormat == 2)
		{
			tmp = "PAL";
		}
		else if(struDecChanStatus[i].byVideoFormat == 1)
		{
			tmp = "NTSC";
		}
		else
		{
			tmp = "NULL";
		}
        m_DecList.SetItemText(i, 11, tmp);
	}

	BYTE byVGA = 1;
	BYTE byDVI = 1;
	BYTE byHDMI = 1;
	BYTE byBNC = 1;
	BYTE bySDI = 1; 
	LPNET_DVR_DISP_CHAN_STATUS_V41  struDispChanStatus = m_DecoderWorkStatus.struDispChanStatus; 
	for (i = 0; i < m_iBNCNums + m_iVGANums + m_iHDMINums + m_iDVINums + m_iSDINums; i++)
	{
		if (struDispChanStatus[i].byBVGA == 0)
		{
			tmp.Format("BNC%d", byBNC);
			m_DispList.InsertItem(i, tmp, 0);
			tmp = "BNC";
			byBNC++;
		}
		else if (struDispChanStatus[i].byBVGA == 1)
		{
			tmp.Format("VGA%d", byVGA);
			m_DispList.InsertItem(i, tmp, 0);
			tmp = "VGA";
			byVGA++;
		}
		else if (struDispChanStatus[i].byBVGA == 2)
		{
			tmp.Format("HDMI%d", byHDMI);
			m_DispList.InsertItem(i, tmp, 0);
			tmp = "HDMI";
			byHDMI++;
		}
		else if (struDispChanStatus[i].byBVGA == 3)
		{
			tmp.Format("DVI%d", byDVI);
			m_DispList.InsertItem(i, tmp, 0);
			tmp = "DVI";
			byDVI++;
		}
		else if (struDispChanStatus[i].byBVGA == 4)
		{
			tmp.Format("SDI%d", bySDI);
			m_DispList.InsertItem(i, tmp, 0);
			tmp = "SDI";
			bySDI++;
		}
		m_DispList.SetItemText(i, 2, tmp);
		
		if (struDispChanStatus[i].byDispStatus == 0)
		{
			g_StringLanType(szLan, "未显示", "not displayed");
			tmp.Format("%s", szLan);
		}
		else
		{
			g_StringLanType(szLan, "已显示", "already displayed");
			tmp.Format("%s", szLan);
		}
		m_DispList.SetItemText(i, 1, szLan);
		
		if (struDispChanStatus[i].byVideoFormat == 1)
		{
			tmp = "NTSC";
		}
		else if(struDispChanStatus[i].byVideoFormat == 2)
		{
			tmp = "PAL";
		}
		else
		{
			tmp = "NULL";
		}
		m_DispList.SetItemText(i, 3, tmp);
		
		tmp.Format("%d", struDispChanStatus[i].byWindowMode);
		m_DispList.SetItemText(i, 4, tmp);
		
		if (struDispChanStatus[i].byScreenMode == 1)
		{
			g_StringLanType(szLan, "大屏", "Big screen");
			tmp.Format("%s", szLan);
		}
		else
		{
			g_StringLanType(szLan, "普通", "Ordinary");
			tmp.Format("%s", szLan);
		}
		m_DispList.SetItemText(i, 5, tmp);
	}

	DWORD * dwAlarmInStatus = (LPDWORD)m_DecoderWorkStatus.byAlarmInStatus; 
	DWORD * dwAlarmOutStatus = (LPDWORD)m_DecoderWorkStatus.byAlarmOutStatus ; 
	for (i = 0; i < MAX_ANALOG_ALARMIN; i++)
	{
		tmp.Format("%d", i + m_lStartChan);
		m_AlarmList.InsertItem(i, tmp, 0);
		
		tmp.Format("%d", m_dwAlarmInStatus[i]);
		m_AlarmList.SetItemText(i, 1, tmp);
		
		tmp.Format("%d", i + m_lStartChan);
		m_AlarmList.SetItemText(i, 2, tmp);
		
		tmp.Format("%d", m_dwAlarmOutStatus[i]);
		m_AlarmList.SetItemText(i, 3, tmp);
    }
	DWORD dwAudioInChanStatus  =  m_DecoderWorkStatus.byAudioInChanStatus; 
	m_Audio1Ctrl.SetCurSel(dwAudioInChanStatus);
	OnSelchangeComboSubwnd();
	UpdateData(FALSE); 
}