// DlgAbilityAutoDetect.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAbilityAutoDetect.h"


#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAbilityAutoDetect dialog
#define XML_ABILITY_IN_LEN	1024
#define XML_ABILITY_OUT_LEN	3*1024*1024

CDlgAbilityAutoDetect::CDlgAbilityAutoDetect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAbilityAutoDetect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAbilityAutoDetect)
	m_strDevAbility = _T("");
	m_strLostAbility = _T("");
	m_dwLastError = 0;
	m_dwReturnValue = 0;
	m_lServerID = -1;
	m_pOutBuf = NULL;
	m_dwAbilityType = 0;
	m_strInputParam = _T("");
    m_bSTDAbility = FALSE;
	//}}AFX_DATA_INIT
	memset(&m_struSdkLocalCfg, 0, sizeof(m_struSdkLocalCfg));
}


void CDlgAbilityAutoDetect::DoDataExchange(CDataExchange* pDX)
{

    CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAbilityAutoDetect)
	DDX_Control(pDX, IDC_CMB_STREAM_TYPE, m_cmbStreamType);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
	DDX_Control(pDX, IDC_CMB_ABILITY_TYPE, m_cmbAbilityType);
	DDX_Text(pDX, IDC_EDT_ABILITY_SHOW, m_strDevAbility);
	DDX_Text(pDX, IDC_EDT_ABILITY_LOST, m_strLostAbility);
	DDX_Text(pDX, IDC_EDT_LAST_ERROR, m_dwLastError);
	DDX_Text(pDX, IDC_EDT_RETURN_VALUE, m_dwReturnValue);
	DDX_Text(pDX, IDC_EDT_INPUT_PARAM, m_strInputParam);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAbilityAutoDetect, CDialog)
	//{{AFX_MSG_MAP(CDlgAbilityAutoDetect)
	ON_BN_CLICKED(IDC_BTN_USE_SIM_ABILITY, OnBtnUseSimAbility)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_CMB_ABILITY_TYPE, OnSelchangeCmbAbilityType)
	//}}AFX_MSG_MAP
    ON_CBN_EDITCHANGE(IDC_CMB_ABILITY_TYPE, &CDlgAbilityAutoDetect::OnCbnEditchangeCmbAbilityType)
    ON_CBN_SETFOCUS(IDC_CMB_ABILITY_TYPE, &CDlgAbilityAutoDetect::OnCbnSetfocusCmbAbilityType)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAbilityAutoDetect message handlers

void CDlgAbilityAutoDetect::OnBtnUseSimAbility() 
{
	// TODO: Add your control notification handler code here
	memset(&m_struSdkLocalCfg, 0 ,sizeof(m_struSdkLocalCfg));
	NET_DVR_GetSDKLocalConfig(&m_struSdkLocalCfg);
	
	if (1 == m_struSdkLocalCfg.byEnableAbilityParse)
	{
		m_struSdkLocalCfg.byEnableAbilityParse = 0;
		GetDlgItem(IDC_BTN_USE_SIM_ABILITY)->SetWindowText("不使用模拟能力");
	} 
	else
	{
		m_struSdkLocalCfg.byEnableAbilityParse = 1;
		GetDlgItem(IDC_BTN_USE_SIM_ABILITY)->SetWindowText("使用模拟能力");
	}
	
	if (!NET_DVR_SetSDKLocalConfig(&m_struSdkLocalCfg))
	{
		AfxMessageBox("fail!");
	}
}

void CDlgAbilityAutoDetect::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    GetDlgItem(IDC_EDT_ABILITY_SHOW)->SetWindowText("");
    GetDlgItem(IDC_EDT_ABILITY_LOST)->SetWindowText("");
    UpdateData(TRUE);
    if (m_dwAbilityType == 0)
    {
        AfxMessageBox("请选择正确的能力集类型!");
        return ;
    }
    if (m_bSTDAbility == 1)
    {
        int nID = 0;
        NET_DVR_STD_ABILITY struSTDAbility = {0};
        NET_DVR_REGION_CLIP_COND struCond = {0};
        if(m_dwAbilityType == NET_DVR_GET_REGIONCLIP_CAPABILITIES)
        {
            struCond.dwSize = sizeof(struCond);
            struCond.dwChannel = m_cmbChannel.GetCurSel() + 1;
            struCond.dwStreamType = m_cmbStreamType.GetCurSel();
            struSTDAbility.lpCondBuffer = &struCond;
            struSTDAbility.dwCondSize = sizeof(struCond);
        }
		else if(m_dwAbilityType == NET_DVR_GET_RTMP_CFG_CAP)
        {
			NET_DVR_RTMP_COND struRTMPCond = {0};
            struRTMPCond.dwSize = sizeof(struRTMPCond);
            struRTMPCond.dwChannel = m_cmbChannel.GetCurSel() + 1;
            struRTMPCond.byStreamType = m_cmbStreamType.GetCurSel() + 1;
            struSTDAbility.lpCondBuffer = &struRTMPCond;
            struSTDAbility.dwCondSize = sizeof(struRTMPCond);
        }
        else if (m_dwAbilityType == NET_DVR_GET_INPUT_SOURCE_TEXT_CAP)
        {
            NET_DVR_INPUT_SOURCE_TEXT_COND struCond = { 0 };
            struCond.dwSize = sizeof(struCond);
            if (m_strInputParam.GetLength() != 0)
            {
                struCond.dwInputSourceNo = atoi(m_strInputParam.GetBuffer(0));
                m_strInputParam.ReleaseBuffer();
            }
            struSTDAbility.lpCondBuffer = &struCond;
            struSTDAbility.dwCondSize = sizeof(struCond);
        }
        else if (m_dwAbilityType == NET_DVR_GET_FACELIB_SCHEDULE_CAPABILITIES)
        {
            NET_DVR_FACELIB_GUARD_COND strFaceLibGuard = { 0 };
            strFaceLibGuard.dwSize = sizeof(strFaceLibGuard);
            strFaceLibGuard.dwChannel = m_cmbChannel.GetCurSel() + 1;;
            strncpy(strFaceLibGuard.szFDID, m_strInputParam.GetBuffer(m_strInputParam.GetLength()), 68);

            struSTDAbility.lpCondBuffer = &strFaceLibGuard;
            struSTDAbility.dwCondSize = sizeof(strFaceLibGuard);
        }
        else
        {
            if (m_strInputParam != "")
            {
                nID = atoi(m_strInputParam.GetBuffer(0));
                m_strInputParam.ReleaseBuffer();
            }
            struSTDAbility.lpCondBuffer = &nID;
            struSTDAbility.dwCondSize = sizeof(int);
        }        
        
        struSTDAbility.lpOutBuffer = m_pOutBuf;
        struSTDAbility.dwOutSize = XML_ABILITY_OUT_LEN;
        struSTDAbility.lpStatusBuffer = m_pOutBuf;
        struSTDAbility.dwStatusSize = XML_ABILITY_OUT_LEN;
        m_dwReturnValue = NET_DVR_GetSTDAbility(m_lServerID, m_dwAbilityType, &struSTDAbility);
    }
    else if (m_bSTDAbility == 2)
    {
        NET_DVR_XML_CONFIG_INPUT    struInput = {0};
        NET_DVR_XML_CONFIG_OUTPUT   struOuput = {0};
        struInput.dwSize = sizeof(struInput);
		struOuput.dwSize = sizeof(struOuput);
        struInput.lpRequestUrl = m_strInputParam.GetBuffer(0);
        struInput.dwRequestUrlLen = m_strInputParam.GetLength();
        struOuput.dwSize = sizeof(struOuput);
		memset(m_pOutBuf, 0, XML_ABILITY_OUT_LEN);
        struOuput.dwSize = sizeof(NET_DVR_XML_CONFIG_OUTPUT);
        struOuput.lpOutBuffer = m_pOutBuf;
        struOuput.dwOutBufferSize = XML_ABILITY_OUT_LEN;
        
        m_dwReturnValue = NET_DVR_STDXMLConfig(m_lServerID, &struInput, &struOuput);
    }
    else
    {
        m_dwReturnValue = NET_DVR_GetDeviceAbility(m_lServerID, m_dwAbilityType, m_strInputParam.GetBuffer(0), m_strInputParam.GetLength(), m_pOutBuf, XML_ABILITY_OUT_LEN);
        m_strInputParam.ReleaseBuffer();
    }	
    m_dwLastError = NET_DVR_GetLastError();
    if (m_dwReturnValue != 0)
    {
        CXmlBase xmlBase;
        xmlBase.Parse(m_pOutBuf);
        xmlBase.SetRoot();
        //m_strDevAbility = xmlBase.GetChildren().c_str();
        m_strDevAbility = m_pOutBuf;
        m_strDevAbility.Replace("\n", "\r\n");
        if (!m_bSTDAbility)
        {
            ParseAbility();
        }		
    }
    
	UpdateData(FALSE);
}

void CDlgAbilityAutoDetect::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if (m_pOutBuf != NULL)
	{
		delete []m_pOutBuf;
		m_pOutBuf = NULL;
	}
}

BOOL CDlgAbilityAutoDetect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	m_pOutBuf = new char[XML_ABILITY_OUT_LEN];
	memset(m_pOutBuf, 0, XML_ABILITY_OUT_LEN);
    m_cmbChannel.SetCurSel(0);
    m_cmbStreamType.SetCurSel(2);

    //只获取刚初始化时候的能力列表
    int iCount = ((CComboBox*)GetDlgItem(IDC_CMB_ABILITY_TYPE))->GetCount();
    for (int i = 0; i < iCount; ++i)
    {
        CString cstr;
        m_cmbAbilityType.GetLBText(i, cstr);
        m_vecAbilityType.push_back(cstr);
        m_vecCurAbilityType.push_back(cstr);
    }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAbilityAutoDetect::OnSelchangeCmbAbilityType() 
{
	// TODO: Add your control notification handler code here
	CXmlBase xmlInput;
    m_bSTDAbility = FALSE;
    GetDlgItem(IDC_STATIC_CHANNEL)->ShowWindow(FALSE);
    GetDlgItem(IDC_STATIC_STREAM_TYPE)->ShowWindow(FALSE);
    GetDlgItem(IDC_COMBO_CHANNEL)->ShowWindow(FALSE);
    GetDlgItem(IDC_CMB_STREAM_TYPE)->ShowWindow(FALSE);

    int iIndex = GetSelectedAbilityIndex();
    if (iIndex < 0)
    {
        return;
    }
    switch (iIndex)
	{
	case 0:	//软硬件能力
		m_dwAbilityType = DEVICE_SOFTHARDWARE_ABILITY;
		break;
	case 1:	//Wifi能力
		m_dwAbilityType = DEVICE_NETWORK_ABILITY;
		break;
	case 2: //编码能力
		m_dwAbilityType = DEVICE_ENCODE_ALL_ABILITY;
		break;
	case 3:	//当前编码能力
		m_dwAbilityType = DEVICE_ENCODE_CURRENT;
		xmlInput.Parse("<CurrentCompressInfo><ChannelNumber>1</ChannelNumber><VideoEncodeType>0</VideoEncodeType><VideoResolution>3</VideoResolution></CurrentCompressInfo>");
		break;
	case 4:	//前端参数能力
		m_dwAbilityType = IPC_FRONT_PARAMETER;
		break;
	case 5:	//鱼眼能力
		m_dwAbilityType = FISHEYE_ABILITY;
		break;
	case 6:	//Raid能力
		m_dwAbilityType = DEVICE_RAID_ABILITY;
		break;
	case 7: //编码能力2.0
		m_dwAbilityType = DEVICE_ENCODE_ALL_ABILITY_V20;
		xmlInput.Parse("<AudioVideoCompressInfo><AudioChannelNumber>1</AudioChannelNumber><VoiceTalkChannelNumber>1</VoiceTalkChannelNumber><VideoChannelNumber>1</VideoChannelNumber></AudioVideoCompressInfo>");
		break;
	case 8: //前段参数2.0
		m_dwAbilityType = IPC_FRONT_PARAMETER_V20;
		xmlInput.Parse("<CAMERAPARA><ChannelNumber>1</ChannelNumber></CAMERAPARA>");
		break;
	case 9: //解码器能力
		m_dwAbilityType = DECODER_ABILITY;
		xmlInput.Parse("<DecoderAbility version='2.0'></DecoderAbility>");
		break;
	case 10: //用户管理能力
		m_dwAbilityType = DEVICE_USER_ABILITY;
		xmlInput.Parse("<UserAbility version='2.0'></UserAbility>");
		break;
	case 11: //网络应用能力
        m_dwAbilityType = DEVICE_NETAPP_ABILITY;
        xmlInput.Parse("<NetAppAbility version='2.0'></NetAppAbility>");
		break;
	case 12: //视频图像能力
		m_dwAbilityType = DEVICE_VIDEOPIC_ABILITY;
		xmlInput.Parse("<VideoPicAbility version='2.0'>	<channelNO>1</channelNO></VideoPicAbility>");
		break;
	case 13: //JPEG抓图能力
		m_dwAbilityType = DEVICE_JPEG_CAP_ABILITY;
		xmlInput.Parse("<JpegCaptureAbility version='2.0'><channelNO>1</channelNO></JpegCaptureAbility>");
		break;
	case 14: //串口能力
		m_dwAbilityType = DEVICE_SERIAL_ABILITY;
		xmlInput.Parse("<SerialAbility version='2.0'></SerialAbility>");
		break;
	case 15: //视频综合平台能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		break;
	case 16: //解码子系统能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		break;
	case 17: //编码子系统能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		break;
	case 18: //级联输入子系统
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		break;
	case 19: //级联输出子系统
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		break;
	case 20: //码分子系统
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		break;
	case 21: //网络报警主机
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<AlarmHostAbility version=\"2.0\"></AlarmHostAbility>");
		break;
	case 22: //平台级联子系统
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		break;
	case 23: //录像参数能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<RecordAbility version='2.0'></RecordAbility>");
		break;
	case 24: //设备数字通道能力
		m_dwAbilityType = DEVICE_DYNCHAN_ABILITY;
		xmlInput.Parse("<DynChannelAbility version='2.0'><channelNO>1</channelNO></DynChanAbility>");
		break;
	case 25: //通道输入能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<ChannelInputAbility version='2.0'><channelNO>1</channelNO></ChannelInputAbility>");
		break;
	case 26: //审讯机能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<InquestAbility version='2.0'></InquestAbility>");
		break;
	case 27: //CVR能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<CVRAbility version='2.0'></CVRAbility>");
		break;
	case 28: //设备事件能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<EventAbility version='2.0'><channelNO>1</channelNO></EventAbility>");
		break;
	case 29: //前端接入通道能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<GetAccessDeviceChannelAbility version='2.0'></GetAccessDeviceChannelAbility>");
		break;
	case 30: //本地预览切换能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<PreviewSwitchAbility version='2.0'></PreviewSwitchAbility>");
		break;
	case 31: //ROI能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<ROIAbility version='2.0'><channelNO>1</channelNO></ROIAbility>");
		break;
	case 32: //云台能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<PTZAbility><channelNO>1</channelNO></PTZAbility>");
		break;
	case 33: //VQD能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<VQDAbility version='2.0'><channelNO>1</channelNO></VQDAbility>");
		break;
	case 34://智能交通能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<ITDeviceAbility version='2.0'><channelNO>1</channelNO></ITDeviceAbility>");
		break;
	case 35: //N+1能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<NPlusOneAbility  version='2.0'></NPlusOneAbility >");
		break;
	case 36://磁盘相关能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<HardDiskAbility version='2.0'></HardDiskAbility>");
		break;
	case 37://设备报警能力
		m_dwAbilityType = DEVICE_ALARM_ABILITY;
		xmlInput.Parse("<AlarmAbility version='2.0'><channelID>1</channelID></AlarmAbility>");
		break;
	case 38://IPC配置文件导入导出能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<IPAccessConfigFileAbility version='2.0'></IPAccessConfigFileAbility>");
		break;
	case 39://前端动态能力获取（曝光时间）
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<CameraParaDynamicAbility version='2.0'><channelNO>1</channelNO><ExposureSetDynamicLinkTo><WDR><WDREnable>0</WDREnable></WDR><IrisMode><IrisType>0</IrisType></IrisMode></ExposureSetDynamicLinkTo></CameraParaDynamicAbility>");
		break;
	case 40://前端动态能力获取（CaptureMode）
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<CameraParaDynamicAbility version='2.0'><channelNO>1</channelNO><AudioVideoCompressInfoDynamicLinkTo><captureMode opt='640*480@30fps'/></AudioVideoCompressInfoDynamicLinkTo></CameraParaDynamicAbility>");
		break;
	case 41://GBT28181协议
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<GBT28181AccessAbility version='2.0'><channelNO>1</channelNO></GBT28181AccessAbility>");
		break;
	case 42://日志搜索能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<SearchLogAbility version='2.0'><channelNO>1</channelNO></SearchLogAbility>");
		break;
	case 43://报警触发录像
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<AlarmTriggerRecordAbility version='2.0'><channelNO>1</channelNO></AlarmTriggerRecordAbility>");
		break;
	case 44://IP可视对讲分机能力
		m_dwAbilityType = IP_VIEW_DEV_ABILITY;
		break;
    case 45://矩阵能力
        m_dwAbilityType = MATRIX_ABILITY; 
        xmlInput.Parse("<MatrixAbility version='2.0'></MatrixAbility>"); 
        break; 
	case 46:
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<IOAbility version='2.0'><channelNO>1</channelNO></IOAbility>");
		break;
	case 47:
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<AccessProtocolAbility version='2.0'><channelNO>1</channelNO></AccessProtocolAbility>");
		break;
	case 48:
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<VcaDevAbility version='2.0'></VcaDevAbility>");
		break;
	case 49:
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<VcaCtrlAbility  version='2.0'><channelNO>1</channelNO></VcaCtrlAbility>");
		break;
	case 50:
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<VcaChanAbility  version='2.0'><channelNO>1</channelNO></VcaChanAbility>");
		break;
	case 51:
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<CameraMountAbility  version='2.0'><channelNO>1</channelNO></CameraMountAbility>");
		break;
	case 52:
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<RecordingHostAbility version='2.0'></RecordingHostAbility>");
		break;
	case 53://双目能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		xmlInput.Parse("<BinocularAbility  version='2.0'><channelNO>1</channelNO></BinocularAbility>");
		break;
    case 54: //Smart能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_SMART_CAPABILITIES;
        break;
    case 55: //事件触发能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_EVENT_TRIGGERS_CAPABILITIES;
        break;
    case 56: //进入区域侦测能力
        m_bSTDAbility = TRUE;    
        m_dwAbilityType = NET_DVR_GET_REGION_ENTRANCE_CAPABILITIES;
        m_strInputParam = "1";
        break;    
    case 57: //进入区域侦测布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_REGION_ENTRANCE_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 58: //离开区域侦测能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_REGION_EXITINT_CAPABILITIES;
        m_strInputParam = "1";
        break;    
    case 59: //离开区域侦测布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_REGION_EXITING_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;    
    case 60: //徘徊侦测能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_LOITERING_CAPABILITIES;
        m_strInputParam = "1";
        break;                
    case 61: //徘徊侦测布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_LOITERING_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;                            
    case 62: //人员聚集侦测能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_GROUPDETECTION_CAPABILITIES;
        m_strInputParam = "1";
        break;                                        
    case 63: //人员聚集侦测布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_GROUP_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;                                                    
    case 64: //快速运动侦测能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_RAPIDMOVE_CAPABILITIES;
        m_strInputParam = "1";
        break;                                                                
    case 65: //快速运动侦测布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_RAPIDMOVE_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;                                                                            
    case 66: //停车侦测能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_PATKING_CAPABILITIES;
        m_strInputParam = "1";
        break;                                                                                        
    case 67: //停车侦测布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_PARKING_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;                                                                                                    
    case 68: //物品遗留侦测能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_UNATTENDED_BAGGAGE_CAPABILITIES;
        m_strInputParam = "1";
        break;                                                                                                                
    case 69: //物品遗留侦测布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_UNATTENDEDBAGGAGE_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;            
    case 70: //物品拿取侦测能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_ATTENDEDBAGGAGE_CAPABILITIES;
        m_strInputParam = "1";
        break;                        
    case 71: //物品拿取侦测布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_ATTENDEDBAGGAGE_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;            
    case 72: //区域裁剪能力
        GetDlgItem(IDC_STATIC_CHANNEL)->ShowWindow(TRUE);
        GetDlgItem(IDC_STATIC_STREAM_TYPE)->ShowWindow(TRUE);
        GetDlgItem(IDC_COMBO_CHANNEL)->ShowWindow(TRUE);
        GetDlgItem(IDC_CMB_STREAM_TYPE)->ShowWindow(TRUE);
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_REGIONCLIP_CAPABILITIES;
        break;                        
    case 73: //Network能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_NETWORK_CAPABILITIES;
        break;            
    case 74: //无线拨号参数能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_WIRELESSDIAL_CAPABILITIES;
        m_strInputParam = "1";
        break;                        
    case 75: //拨号计划能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_WIRELESSDIAL_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 76:
        m_dwAbilityType = ACS_ABILITY;
        xmlInput.Parse("<AcsAbility version='2.0'></AcsAbility>");
		break;
    case 77:
        m_dwAbilityType = DEVICE_ABILITY_INFO;
        xmlInput.Parse("<ImageDisplayParamAbility version='2.0'><channelNO>1,2</channelNO></ImageDisplayParamAbility>");
		break;
	case 78:
		m_dwAbilityType = MERGEDEV_ABILITY;
		break; 
    case 79: //进入区域侦测能力
        m_bSTDAbility = TRUE;    
        m_dwAbilityType = NET_DVR_GET_REGION_ENTRANCE_CAPABILITIES;
        m_strInputParam = "1";
        break; 
    case 80:
        m_dwAbilityType = DEVICE_ABILITY_INFO;
        xmlInput.Parse("<SecurityAbility version='2.0'><channelNO>1</channelNO></SecurityAbility>");
		break;
    case 81:
        m_bSTDAbility = TRUE;    
        m_dwAbilityType = NET_DVR_GET_LITESTORAGE_CAPABILITIES;
        m_strInputParam = "1";
        break; 
    case 82:
        m_bSTDAbility = TRUE;    
        m_dwAbilityType = NET_DVR_GET_VEHICLE_CAPABILITIES;
        m_strInputParam = "1";
        break; 
    case 83:	//IPC升级能力
		m_dwAbilityType = IPC_UPGRADE_DESCRIPTION;
        break;
	case 84:
        m_bSTDAbility = TRUE;    
        m_dwAbilityType = NET_DVR_GET_SLAVECAMERA_CAPABILITIES;
        m_strInputParam = "1";
        break; 
    case 85:
        m_bSTDAbility = TRUE;    
        m_dwAbilityType = NET_DVR_GET_SLAVECAMERA_CALIB_CAPABILITIES;
        m_strInputParam = "1";
        break; 
	case 86:
        m_bSTDAbility = TRUE;    
        m_dwAbilityType = NET_DVR_GET_TRACKING_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 87:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_MASTERSLAVETRACKING_CAPABILITIES;
        break;
    case 88:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_DDNS_COUNTRY_ABILITY;
        break;
    case 89:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_FIREDETECTION_CAPABILITIES;
        m_strInputParam = "2";
        break;
    case 90:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_THERMAL_CAPABILITIES;
        //m_strInputParam = "";
        break;
    case 91:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_SENSOR_PORT_CAPABILITIES;
        //m_strInputParam = "";
        break;
    case 92://NVR激活IPC能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_ACTIVATE_IPC_ABILITY;
        break;
    case 93://集中布控能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_CENTRALIZEDCTRL_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 94://电力罗盘能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_COMPASS_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 95://视频流能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_STREAMING_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 96://视频刷新帧能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_REFRESHFRAME_CAPABILITIES;
        m_strInputParam = "1";
        break;
	case 97:
		m_dwAbilityType = STREAM_ABILITY;
		xmlInput.Parse("<StreamAbility version='2.0'></StreamAbility>");
		break;
	case 98:
		m_dwAbilityType = ACS_ABILITY;
		xmlInput.Parse("<AcsAbility version='2.0'></AcsAbility>");
		break;
	case 99:
		m_bSTDAbility = TRUE;
		m_dwAbilityType = NET_DVR_GET_GBT28181_SERVICE_CAPABILITIES;
		break;
    case 100:
        m_dwAbilityType = DEVICE_ABILITY_INFO;
        xmlInput.Parse("<POSAbility  version='2.0'></POSAbility>");
		break;
    case 101: //热点功能配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_WIRELESSSERVER_CAPABILITIES;
        m_strInputParam = "1";
		break;
    case 102: //连接设备列表
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_CONNECT_LIST_CAPABILITIES;
        m_strInputParam = "1";
		break;
    case 103:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_RECORDING_PUBLISH_FILE_CAP;
        m_strInputParam = "1";
		break;
    case 104:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_RECORD_VIDEO_CFG_CAP;
        m_strInputParam = "1";
		break;
    case 105:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_RECORD_HOST_CAP;
		break;
    case 106://外设能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_EXTERNALDEVICE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 107://内置补光灯能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_SUPPLEMENTLIGHT_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 108:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_LOWPOWER_CAPABILITIES;
		m_strInputParam = "1";
        break;
    case 109:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_ZOOMLINKAGE_CAPABILITIES;
		m_strInputParam = "1";
        break;
    case 110:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_ONLINEUPGRADE_ABILITY;
        break;
	case 111: //电池电量显示
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_OSD_BATTERY_POWER_CFG_CAPABILITIES;
        m_strInputParam = "1";
		break;
	case 112://终端会议区域能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_CONFERENCE_REGION_CAP;
        break;
    case 113://终端呼叫配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_TERMINAL_CALL_CFG_CAP;
        break;
    case 114://终端呼叫控制能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_TERMINAL_CTRL_CAP;
        break;
    case 115://呼叫查询能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_CALL_QUERY_CAP;
        break;
    case 116://VCS能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_VCS_CAP;
        break;
	case 117://会议输入参数能力
		m_bSTDAbility = TRUE;
		m_dwAbilityType = NET_DVR_GET_TERMINAL_INPUT_CFG_CAP;
		break;
	case 118://温湿度配置协议的能力
		m_bSTDAbility = TRUE;
		m_dwAbilityType = NET_DVR_GET_THSCREEN_CAPABILITIES;
		break;
    case 119://IPC全景相机图片参数能力
        m_bSTDAbility = TRUE;
		m_dwAbilityType = NET_DVR_GET_PANORAMAIMAGE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 120://码流加密
        m_bSTDAbility = TRUE;
		m_dwAbilityType = NET_DVR_GET_STREAMENCRYPTION_CAPABILITIES;
        break;
	case 121://校准GPS经纬度能力
        m_bSTDAbility = TRUE;
		m_dwAbilityType = NET_DVR_GET_REVISE_GPS_CAPABILITIES;
		m_strInputParam = "1";
        break;
    case 122:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_TME_CHARGERULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 123:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_PAPERCHARGEINFO_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 124:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_PARKINGSAPCE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 125:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_PXOFFLINE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 126:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_PXMULTICTRL_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 127:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_ILLEGALCARDFILTERING_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 128:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_CHARGEACCOUNT_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 129:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_TME_CAPABILITIES;
		// m_strInputParam = "1";
        break;
    case 130:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_LEDDISPLAY_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 131:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_VOICEBROADCAST_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 132:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_PAPERPRINTFORMAT_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 133:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_LOCkGATE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 134://获取客流量统计能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_COUNTING_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 135: //EPTZ参数能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_EPTZ_CFG_CAPABILITIES;
		break;
    case 136: //中心点参数能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_CENTER_POINT_CFG_CAPABILITIES;
		break;
    case 137: //STD鱼眼参数能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_FISHEYE_CAPABILITIES;
		break;
	case 138://RTMP配置能力
		GetDlgItem(IDC_STATIC_CHANNEL)->ShowWindow(TRUE);
        GetDlgItem(IDC_STATIC_STREAM_TYPE)->ShowWindow(TRUE);
        GetDlgItem(IDC_COMBO_CHANNEL)->ShowWindow(TRUE);
        GetDlgItem(IDC_CMB_STREAM_TYPE)->ShowWindow(TRUE);
		m_cmbStreamType.SetCurSel(0);
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_RTMP_CFG_CAP;
        m_strInputParam = "1";
        break;
    case 139://平均码率动态能力
        m_dwAbilityType = DEVICE_ABILITY_INFO;
        xmlInput.Parse("<CameraParaDynamicAbility version='2.0'><channelNO>1</channelNO><VbrAverageCapDynamicLinkTo><streamType>main</streamType><codeType>smart264</codeType><videoQualityControlType>CBR</videoQualityControlType><vbrUpperCap>512</vbrUpperCap></VbrAverageCapDynamicLinkTo></CameraParaDynamicAbility>");
		break;
    case 140://电影模式配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_FILM_MODE_CFG_CAP;
        break;
    case 141://导播策略配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_DIRECTED_STRATEGY_CFG_CAP;
        break;
    case 142://画面边框配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_FRAME_CFG_CAP;
        m_strInputParam = "1";
        break;
    case 143://音频效果优化配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_AUDIO_EFFECTIVE_CFG_CAP;
        m_strInputParam = "1";
        break;
    case 144://录制视频参数配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_RECORD_VIDEO_CFG_CAP;
        break;
    case 145://哪张图片作为背景图片配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_BACKGROUND_PIC_INFO_CAP;
        break;
	case 146:
		m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_LLDP_CAP;
		m_strInputParam = "1";
		break;
    case 147:
		m_bSTDAbility = TRUE;
		m_dwAbilityType = NET_DVR_GET_PORT_REMARKS_CAP;
		m_strInputParam = "1";
		break;
    case 148://云存储能力集
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口,NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/ContentMgmt/CloudStorageServer/capabilities";
        break;
	case 149://LED能力
		m_dwAbilityType = LED_ABILITY;
		xmlInput.Parse("<LedAbility  version='2.0'></LedAbility>");
		break;
    case 150://人脸抓拍布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_FACESNAP_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
		break;
    case 151://Smart健康布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_STORAGEDETECTION_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
		break;
    case 152://Smart读写锁配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_STORAGEDETECTION_RWLOCK_CAPABILITIES;
        m_strInputParam = "1";
		break;

    case 153://获取Sensor 调节参数的协议的能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_SENSOR_ADJUSTMENT_CAPABILITIES;
        break;
    case 154:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_MANUALRANGING_CAPABILITIES;
        m_strInputParam = "2";
        break;
    case 155://SD卡解锁配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_STORAGEDETECTION_UNLOCK_CAPABILITIES;
		break;
	case 156: //屏幕服务器能力
		m_bSTDAbility = TRUE;
		m_dwAbilityType = NET_DVR_GET_SCREEN_CONFIG_CAP;
		m_strInputParam = "1";
		break;
	case 157: //屏幕互动能力
		m_dwAbilityType = SCREEN_EXCHANGE_ABILITY;
		xmlInput.Parse("<ScreenExchangeAbility version=\"2.0\"></ScreenExchangeAbility>");
		break;
	case 158: //屏幕服务器登陆参数能力
		m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/DisplayDev/Auxiliary/ScreenServer/1/loginCfg/capabilities\r\n";
		break;
    case 159: //图像差分检测配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_IMAGE_DIFF_DETECTION_CFG_CAP;
        m_strInputParam = "5";
        break;
    case 160: //发布文件信息配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_RECORDING_PUBLISH_FILE_INFO_CAP;
        m_strInputParam = "1";
        break;        
    case 161: //手动课程录像控制能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_MANUAL_CURRICULUM_CONTROL_CAP;
		break;
    case 162: //语音配置信息能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_TMEVOICE_CAPABILITIES;
        m_strInputParam = "1";
		break;
	case 163://ftp上传信息规整能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_FTP_CAPABILITIES;
		break;
    case 164://获取ptz球机控制能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_PTZ_CAPABILITIES;
        m_strInputParam = "1";
		break;
    case 165:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_POSTRADAR_CAPABILITIES;
        m_strInputParam = "1";
		break;
	case 166://云存储URL能力
		m_bSTDAbility = TRUE;
		m_dwAbilityType = NET_DVR_GET_CLOUD_URL_CAP;
		break;
	case 167://云存储配置能力
		m_bSTDAbility = TRUE;
		m_dwAbilityType = NET_DVR_GET_CLOUD_CFG_CAP;
		break;
	case 168://云存储上传策略配置能力
		m_bSTDAbility = TRUE;
		m_dwAbilityType = NET_DVR_GET_CLOUDSTORAGE_UPLOADSTRATEGY_CAP;
		m_strInputParam = "1";
		break;
	case 169: //录播主机参数配置能力
		m_dwAbilityType = 0xffffffff;
		m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
		m_strInputParam = "GET /ISAPI/ContentMgmt/RecordingHost/hostParam/capabilities\r\n";
		break;
	case 170: //课堂大数据统计配置能力
		m_dwAbilityType = 0xffffffff;
		m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
		m_strInputParam = "GET /ISAPI/ContentMgmt/RecordingHost/ClassDataControl/capabilities\r\n";
		break;
	case 171: //获取统计数据列表的能力
		m_dwAbilityType = 0xffffffff;
		m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
		m_strInputParam = "GET /ISAPI/ContentMgmt/RecordingHost/ClassDataStatisticCfg/getStatisticData/capabilities\r\n";
		break;
	case 172: //导播高级参数配置能力
		m_dwAbilityType = 0xffffffff;
		m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
		m_strInputParam = "GET /ISAPI/ContentMgmt/RecordingHost/DirectedAdvanceCfg/commandID/<ID>/capabilities\r\n";
		break;
    case 173://获取船只检测布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_SHIPSDETECTION_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 174://船只检测参数配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_SHIPSDETECTION_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 175:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_THERMOMETRY_BASICPARAM_CAPABILITIES;
        m_strInputParam = "2";
        break;
    case 176:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_THERMOMETRY_SCENE_CAPABILITIES;
        m_strInputParam = "2";
        break;
    case 177:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_THERMOMETRY_ALARMRULE_CAPABILITIES;
        m_strInputParam = "2";
        break;
    case 178:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_BAREDATAOVERLAY_CAPABILITIES;
        m_strInputParam = "2";
        break;
    case 179: //协议透传能力集
        m_bSTDAbility = 1;
        m_dwAbilityType = NET_DVR_GET_PASSTHROUGH_CAP;
        break;
	case 180:
		m_bSTDAbility = TRUE;
		m_dwAbilityType = NET_DVR_GET_MANUALDEICING_CAPABILITIES;
		m_strInputParam = "2";
		break;
	case 181: //韦根配置能力
		m_dwAbilityType = 0xffffffff;
		m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
		m_strInputParam = "GET /ISAPI/AccessControl/WiegandCfg/capabilities\r\n";
		break;
	case 182: //门控安全模块在线状态能力
		m_dwAbilityType = 0xffffffff;
		m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
		m_strInputParam = "GET /ISAPI/AccessControl/DoorSecurityModule/moduleStatus/capabilities\r\n";
		break;
	case 183: //门禁总能力
		m_dwAbilityType = 0xffffffff;
		m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
		m_strInputParam = "GET /ISAPI/AccessControl/capabilities\r\n";
		break;
    case 184: //输入源字符叠加能力
        m_bSTDAbility = 1;
        m_dwAbilityType = NET_DVR_GET_INPUT_SOURCE_TEXT_CAP;
        m_strInputParam = "1";
        break;
    case 185: //输入源自定义分辨率能力
        m_bSTDAbility = 1;
        m_dwAbilityType = NET_DVR_GET_INPUT_SOURCE_RESOLUTION_CAP;
        m_strInputParam = "1";
        break;
    case 186://一键式紧急产品能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_EMERGENCE_ALARM_PRODUCT_CAP;
        break;
    case 187://呼叫等待参数配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_CALL_WAITTING_CFG_CAP;
        break;
    case 188://警灯参数配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_ALARM_LAMP_CFG_CAP;
        break;
    case 189://语音提示配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_VOICE_PROMPTION_CFG_CAP;
        break;
    case 190://紧急报警处理能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_EMERGENCE_ALARM_RESPONSE_CAP;
        break;
	case 191: //获取触发抓拍参数能力
		m_dwAbilityType = 0xffffffff;
		m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
		m_strInputParam = "GET /ISAPI/AccessControl/SnapConfig/capabilities\r\n";
		break;
    case 192://隐藏信息配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_HIDDEN_INFORMATION_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 193://部门参数配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口,NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/DepartmentParam/capabilities";
        break;
    case 194://排班计划配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口,NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/SchedulePlan/capabilities";
        break;
    case 195://考勤规则配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口,NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/AttendanceRule/capabilities";
        break;
    case 196://普通班配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口,NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/OrdinaryClass/capabilities";
        break;
    case 197://工时班配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口,NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/WorkingClass/capabilities";
        break;
    case 198://考勤假日组配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口,NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/AttendanceHolidayGroup/capabilities";
        break;
    case 199://考勤假日计划配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口,NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/AttendanceHolidayPlan/capabilities";
        break;
    case 200://门禁总能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口,NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/capabilities";
        break;
    case 201://考勤有效ID获取能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口,NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/AttendanceEffectiveID/capabilities";
        break;
    case 202: //获取配件板信息能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_ACCESSORY_CARD_INFO_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 203: //显示输入参数能力集
        m_bSTDAbility = 1;
        m_dwAbilityType = NET_DVR_GET_DISPINPUT_CFG_CAP;
        break;
    case 204: //EDID配置文件信息能力集
        m_bSTDAbility = 1;
        m_dwAbilityType = NET_DVR_GET_EDID_CFG_FILE_INFO_CAP;
        break;
    case 205: //热成像智能互斥能力
        m_bSTDAbility = 1;
        m_dwAbilityType = NET_DVR_GET_THERMINTELL_CAPABILITIES;
        break;
    case 206:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_FIREDETECTION_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 207:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_THERMOMETRY_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 208:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_TEMPERTURE_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 209:
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_SEARCH_LOG_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 210://光学防抖能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_OIS_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 211://MAC地址过滤配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_MACFILTER_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 212://鹰视聚焦标定配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_EAGLEFOCUS_CALCFG_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 213://鹰视聚焦配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_EAGLEFOCUSING_CFG_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 214://Smart行为标定过滤尺寸功能能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_SMARTCALIBRATION_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 215: //解码OSD能力
        m_bSTDAbility = 1;
        m_dwAbilityType = NET_DVR_GET_SUBWND_DECODE_OSD_CAP;
        m_strInputParam = "16842753";
        break;
    case 216://存储总能力（RACM能力）
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_RACM_CAP;
        break;
    case 217: //CVR回传功能基础能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_RECORD_PASSBACK_BASIC_CFG_CAP;
        break;
    case 218: //回传历史录像计划能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_RECORD_PASSBACK_HISTORY_PLAN_CFG_CAP;
        break;
    case 219://获取设备的系统能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_SYSTEM_CAPABILITIES;
        break;
    case 220: // 获取设备鹰眼能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_EAGLEEYE_CAPABILITIES;
        break;
    case 221://获取分辨率模式切换能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_RESOLUTION_SWITCH_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 222://教育服务器对接配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/ContentMgmt/RecordingHost/EducationServerConfiguration/capabilities\r\n";
        break;
    case 223://视频切换配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/ContentMgmt/RecordingHost/VideoSwitchConfiguration/capabilities\r\n";
        break;
    case 224://片头配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/ContentMgmt/RecordingHost/VideoTitleConfiguration/capabilities\r\n";
        break;
    case 225://片尾配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/ContentMgmt/RecordingHost/VideoTrailerConfiguration/capabilities\r\n";
        break;
    case 226: //就地控制器参数能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/localController/capabilities\r\n";
        break;
    case 227: //就地控制器控制能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/localController/control/capabilities\r\n";
        break;
    case 228: //获取USB设备状态能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/USBStatus/capabilities\r\n";
        break;
    case 229: //USB控制能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/USBControl/capabilities\r\n";
        break;
    case 230: //门禁总能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/capabilities\r\n";
        break;
    case 231: //获取USB控制进度能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/USBControlProgress/capabilities\r\n";
        break;
    case 232://获取获取车辆信息结果能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_VEHICLLE_RESULT_CAPABILITIES;
        break;
    case 233: //庭审主机能力
        m_dwAbilityType = DEVICE_ABILITY_INFO;
        xmlInput.Parse("<TrialHostAbility version='2.0'></TrialHostAbility>");
        break;
    case 234: //设备工作模式能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口,NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/VideoIntercom/workMode/capabilities";
        break;
    case 235: //获取火点区域屏蔽能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_FIRESHIELDMASK_CAPABILITIES;
        m_strInputParam = "2";
        break;
    case 236: //获取烟雾区域屏蔽能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_SMOKESHIELDMASK_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 237: //获取区域扫描能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_AREASCAN_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 238: //设备巡航模式能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_CRUISE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 239: //环境温湿度能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_TEMP_HUMI_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 240: //手动测温实时数据能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_MANUALTHERM_CAPABILITIES;
        m_strInputParam = "2";
        break;
    case 241: //获取手动测温基本参数配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_MANUALTHERM_BASIC_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 242: //高精度PTZ绝对位置配置扩展能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_PTZABSOLUTEEX_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 243://多路分组混音音频独立存储配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/System/Audio/Mixing/capabilities\r\n";
        break;
    case 244://音频配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/System/Audio/capabilities\r\n";
        break;
    case 245://单个串口服务配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/System/Serial/ports/1/capabilities";
        break;
    case 246://串口服务能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/System/Serial/capabilities\r\n";
        break;
    case 247: //梯控继电器配置
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/LadderControlRelay/capabilities\r\n";
        break;
    case 248: //获取软件服务能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_SOFTWARE_SERVICE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 249: //远端网管收发器能力
        m_dwAbilityType = REMOTE_NETMGR_FOT_ABILITY;
        xmlInput.Parse("<RemoteNetMgrFOTAbility version=\"2.0\"></RemoteNetMgrFOTAbility>");
        break;
    case 250: //门禁事件获取能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口,NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/GetAcsEvent/capabilities";
        break;
    case 251://获取黑名单人脸比对布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_BLACKLIST_FACECONTRAST_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 252://获取白名单人脸比对布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_WHITELIST_FACECONTRAST_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 253: //人脸比对配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/Intelligent/channels/1/faceContrast/capabilities\r\n";
        break;
    case 254: //人体参数配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/ContentMgmt/RecordingHost/HumanInformation/capabilities\r\n";
        break;
    case 255: //热成像画中画配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_THERMAL_PIP_CAPABILITIES;
        m_strInputParam = "2";
        break;
    case 256: //热成像OSD配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_THERMAL_INTELRULEDISPLAY_CAPABILITIES;
        m_strInputParam = "2";
        break;
    case 257: //测温配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_THERMOMETRY_MODE_CAPABILITIES;
        m_strInputParam = "2";
        break;
    case 258: //电流锁定配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_CURRENT_LOCK_CAPABILITIES;
        break;
    case 259://人体识别布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_HUMAN_RECOGNITION_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 260: //车辆二次识别检测能力
        m_dwAbilityType = DEVICE_ABILITY_INFO;
        xmlInput.Parse("<VehicleRecogAbility version='2.0'><channelNO>1</channelNO></VehicleRecogAbility>");
        break;
    case 261: //资源IP配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/System/Network/ResourceIPConfiguration/capabilities\r\n";
        break;
    case 262: //读写器基本参数配置
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/Traffic/UHFRFIDReader/basicInformation/capabilities\r\n";
        break;
    case 263: //盘存测试能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/Traffic/UHFRFIDReader/hardDiskStorageTest/capabilities\r\n";
        break;
    case 264: //获取预览模式配置能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_PREVIEW_MODE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 265: //获取架设标定能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_CALIB_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 266: //获取Pos叠加能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_POSINFO_OVERLAY_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 267://获取人脸比对布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_FACECONTRAST_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 268: //韦根规则配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/WiegandRuleCfg/capabilities\r\n";
        break;
    case 269: //M1卡加密验证功能配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/M1CardEncryptCfg/capabilities\r\n";
        break;
    case 270: //布防信息获取能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/DeployInfo/capabilities\r\n";
        break;
    case 271: //跨主机反潜回服务器配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/SubmarineBack/capabilities\r\n";
        break;
    case 272: //加入跨主机反潜回主机配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/SubmarineBackHostInfo/capabilities\r\n";
        break;
    case 273: //起始读卡器配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/StartReaderInfo/capabilities\r\n";
        break;
    case 274: //跨主机反潜回读卡器配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/SubmarineBackReader/capabilities\r\n";
        break;
    case 275: //服务器跨主机反潜回刷卡记录清除能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/ClearCardRecord/capabilities\r\n";
        break;
    case 276: //跨主机反潜回模式配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/SubmarineBackMode/capabilities\r\n";
        break;
    case 277: //跨主机反潜回信息清除能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/ClearSubmarineBack/capabilities\r\n";
        break;
    case 278: //加入跨主机反潜回配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/ServerDevice/capabilities\r\n";
        break;
    case 279: //读卡器跨主机反潜回配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/ReaderAcrossHost/capabilities\r\n";
        break;
    case 280: //门禁事件获取能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/GetAcsEvent/capabilities\r\n";
        break;
    case 281://区域人数统计布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_FRAMES_PEOPLE_COUNTING_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 282://学生起立检测布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_STUDENTS_STOODUP_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 283://获取人员密度检测的布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_PERSONDENSITY_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 284: //数据文件传输速率配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/ContentMgmt/FileData/TransferSpeedConfiguration/capabilities\r\n";
        break;
    case 285: //数据文件锁定配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/ContentMgmt/FileData/LockConfiguration/capabilities\r\n";
        break;
    case 286: //获取数据文件信息能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/ContentMgmt/FileData/SearchFile/capabilities\r\n";
        break;
    case 287: //异地备份备机信息配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/ContentMgmt/RemoteBackup/BackupMachineInfo/capabilities\r\n";
        break;
    case 288: //异地备份任务能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/ContentMgmt/RemoteBackup/Task/capabilities\r\n";
        break;
    case 289://获取人脸比对库布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_FACELIB_SCHEDULE_CAPABILITIES;
        m_strInputParam = "FDID";
        break;
    case 290: //可视对讲系统切换配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/VideoIntercom/SystemSwitchCfg/capabilities\r\n";
        break;
    case 291: //蓝牙通讯密钥设置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/VideoIntercom/BluetoothCommKey/capabilities\r\n";
        break;
    case 292: //人脸服务器配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/VideoIntercom/FaceServerCfg/capabilities\r\n";
        break;
    case 293: //车牌信息下发能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/VideoIntercom/PlateInfo/capabilities\r\n";
        break;
    case 294: //零通道编码能力
        m_dwAbilityType = DEVICE_ABILITY_INFO;
        xmlInput.Parse("<ZeroChanEncodeAbility></ZeroChanEncodeAbility>");
        break;
    case 295://获取安全帽检测的布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_SAFETY_HELMET_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 296: //权限控制器音频文件参数配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/RightControllerAudio/capabilities\r\n";
        break;
    case 297: //通道控制器配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/ChannelControllerCfg/capabilities\r\n";
        break;
    case 298: //闸机本地拨码及信息获取能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/GateDialAndInfo/capabilities\r\n";
        break;
    case 299: //闸机状态获取能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/GateStatus/capabilities\r\n";
        break;
    case 300: //闸机红外状态获取能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/GateIRStatus/capabilities\r\n";
        break;
    case 301: //闸机相关器件状态获取能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/GateRelatedPartsStatus/capabilities\r\n";
        break;
    case 302: //通道控制器报警联动配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/ChannelControllerAlarmLinkage/capabilities\r\n";
        break;
    case 303: //通道控制器报警输出配置能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/ChannelControllerAlarmOut/capabilities\r\n";
        break;
    case 304: //通道控制器报警输出控制能力
        m_dwAbilityType = 0xffffffff;
        m_bSTDAbility = 2; //透传接口，NET_DVR_STDXMLConfig
        m_strInputParam = "GET /ISAPI/AccessControl/ChannelControllerAlarmOutControl/capabilities\r\n";
        break;
    case 305://人脸测温布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_FACE_THERMOMETRY_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 306://获取SoftIO布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_SOFTIO_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 307://获取人员排队检测的布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_PERSONQUEUE_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    case 308://获取高频人员侦测布防时间能力
        m_bSTDAbility = TRUE;
        m_dwAbilityType = NET_DVR_GET_HFPD_SCHEDULE_CAPABILITIES;
        m_strInputParam = "1";
        break;
    default:
		m_dwAbilityType = 0;
		break;
	}
    if (!m_bSTDAbility)
    {
        xmlInput.SetRoot();
        m_strInputParam = xmlInput.GetChildren().c_str();
        m_strInputParam.Replace("\n", "\r\n");
    }	
	UpdateData(FALSE);
}

void CDlgAbilityAutoDetect::ParseAbility()
{
	CXmlBase xmlAll;
	char szPath[MAX_PATH] = {0};
	GetCurrentPath(szPath);
	sprintf(szPath, "%s\\SDK_ABILITY.xml", szPath);
	if(!xmlAll.LoadFile(szPath))
	{
		GetDlgItem(IDC_EDT_ABILITY_LOST)->SetWindowText("本地文件加载错误");
		return;
	}
	xmlAll.SetRoot();
	xmlAll.IntoElem();

    int iIndex = GetSelectedAbilityIndex();
    if (iIndex < 0)
    {
        return;
    }
    switch (iIndex)
	{
	case 0:	//软硬件能力
		m_dwAbilityType = DEVICE_SOFTHARDWARE_ABILITY;
		ParseSimpleAbility(xmlAll, "BasicCapability");
		break;
	case 1:	//Wifi能力
		m_dwAbilityType = DEVICE_NETWORK_ABILITY;
		ParseSimpleAbility(xmlAll, "NetworkSetting");
		break;
	case 2: //编码能力
		m_dwAbilityType = DEVICE_ENCODE_ALL_ABILITY;
		break;
	case 3:	//当前编码能力
		m_dwAbilityType = DEVICE_ENCODE_CURRENT;
		break;
	case 4:	//前端参数能力
		m_dwAbilityType = IPC_FRONT_PARAMETER;
		break;
	case 5:	//鱼眼能力
		m_dwAbilityType = FISHEYE_ABILITY;
		break;
	case 6:	//Raid能力
		m_dwAbilityType = DEVICE_RAID_ABILITY;
		ParseSimpleAbility(xmlAll, "RAID");
		break;
	case 7: //编码能力2.0
		m_dwAbilityType = DEVICE_ENCODE_ALL_ABILITY_V20;
		ParseSimpleAbility(xmlAll, "AudioVideoCompressInfo");
		break;
	case 8: //前段参数2.0
		m_dwAbilityType = IPC_FRONT_PARAMETER_V20;
		ParseSimpleAbility(xmlAll, "CAMERAPARA");
		break;
	case 9: //解码器能力
		m_dwAbilityType = DECODER_ABILITY;
		ParseSimpleAbility(xmlAll, "DecoderAbility");
		break;
	case 10: //用户管理能力
		m_dwAbilityType = DEVICE_USER_ABILITY;
		ParseSimpleAbility(xmlAll, "UserAbility");
		break;
	case 11: //网络应用能力
		m_dwAbilityType = DEVICE_NETAPP_ABILITY;
		ParseSimpleAbility(xmlAll, "NetAppAbility");
		break;
	case 12: //视频图像能力
		m_dwAbilityType = DEVICE_VIDEOPIC_ABILITY;
		ParseSimpleAbility(xmlAll, "VideoPicAbility");
		break;
	case 13: //JPEG抓图能力
		m_dwAbilityType = DEVICE_JPEG_CAP_ABILITY;
		ParseSimpleAbility(xmlAll, "JpegCaptureAbility");
		break;
	case 14: //串口能力
		m_dwAbilityType = DEVICE_SERIAL_ABILITY;
		ParseSimpleAbility(xmlAll, "SerialAbility");
		break;
	case 15: //视频综合平台能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		break;
	case 16: //解码子系统能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		break;
	case 17: //编码子系统能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		break;
	case 18: //级联输入子系统
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		break;
	case 19: //级联输出子系统
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		break;
	case 20: //码分子系统
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		break;
	case 21: //网络报警主机
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "AlarmHostAbility");
		break;
	case 22: //平台级联子系统
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		break;
	case 23:
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "RecordAbility");
		break;
	case 24:
		m_dwAbilityType = DEVICE_DYNCHAN_ABILITY;
		ParseSimpleAbility(xmlAll, "DynChannelAbility");
		break;
	case 25:
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "ChannelInputAbility");
		break;
	case 26: //审讯机能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "InquestAbility");
		break;
	case 27: //CVR能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "CVRAbility");
		break;
	case 28: //设备事件能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "EventAbility");
		break;
	case 29: //前端接入通道能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "GetAccessDeviceChannelAbility");
		break;
	case 30: //本地预览切换能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "PreviewSwitchAbility ");
		break;
	case 31: //ROI能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "ROIAbility");
		break;
	case 32: //云台能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "PTZAbility");
		break;
	case 33: //VQD能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "VQDAbility");
		break;
	case 34://智能交通
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "ITDeviceAbility");
		break;
	case 35: //N+1能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "NPlusOneAbility");
		break;
	case 36://磁盘相关能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "HardDiskAbility");
		break;
	case 37://设备报警能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "DeviceAlarmAbility");
		break;
	case 38://IPC配置文件导入导出能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "IPAccessConfigFileAbility");
		break;
	case 39://前端动态能力获取（曝光时间）
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "ExposureSetDynamicAbility");
		//xmlInput.Parse("<CameraParaDynamicAbility version='2.0'><channelNO>1</channelNO><ExposureSetDynamicLinkTo><WDR><WDREnable>0</WDREnable></WRD><IrisMode><IrisType>0</IrisType></IrisMode></ExposureSetDynamicLinkTo></CameraParaDynamicAbility>");
		break;
	case 40://前端动态能力获取（CaptureMode）
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "CaptureModeDynamicAbility");
		//xmlInput.Parse("<CameraParaDynamicAbility version='2.0'><channelNO>1</channelNO><AudioVideoCompressInfoDynamicLinkTo><captureMode opt='640*480@30fps'/></AudioVideoCompressInfoDynamicLinkTo></CameraParaDynamicAbility>");
		break;
	case 41://GBT28181协议
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "GBT28181AccessAbility");
		//xmlInput.Parse("<GBT28181AccessAbility version='2.0'><channelNO>1</channelNO></GBT28181AccessAbility>");
		break;
	case 42://日志搜索能力
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "SearchLogAbility");
		//xmlInput.Parse("<SearchLogAbility version='2.0'><channelNO>1</channelNO></SearchLogAbility>");
		break;
	case 43://报警触发录像
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "AlarmTriggerRecordAbility");
		//xmlInput.Parse("<AlarmTriggerRecordAbility version='2.0'><channelNO>1</channelNO></AlarmTriggerRecordAbility>");
		break;
	case 44:
		m_dwAbilityType = IP_VIEW_DEV_ABILITY;
		ParseSimpleAbility(xmlAll, "IpViewDevAbility");
		break;
	case 48:
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "VcaDevAbility");
		break;
	case 49:
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "VcaCtrlAbility");
		break;
	case 50:
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "VcaChanAbility");
		break;
	case 51:
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "CameraMountAbility");
		break;
	case 53:
		m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "BinocularAbility");
		break;
    case 76:
        m_dwAbilityType = ACS_ABILITY;
        ParseSimpleAbility(xmlAll, "AcsAbility");
		break;
    case 77:
        m_dwAbilityType = DEVICE_ABILITY_INFO;
        ParseSimpleAbility(xmlAll, "ImageDisplayParamAbility");
		break;
	case 78:
		m_dwAbilityType = MERGEDEV_ABILITY;
		break; 
    case 79:
        m_dwAbilityType = DEVICE_ABILITY_INFO;
        ParseSimpleAbility(xmlAll, "SecurityAbility");
		break;
    case 82:	//IPC升级能力
		m_dwAbilityType = IPC_UPGRADE_DESCRIPTION;
        break;
	case 97:
		m_dwAbilityType = STREAM_ABILITY;
		ParseSimpleAbility(xmlAll, "StreamAbility");
		break;
	case 98:
		m_dwAbilityType = ACS_ABILITY;
		ParseSimpleAbility(xmlAll, "AcsAbility");
		break;
    case 100:
        m_dwAbilityType = DEVICE_ABILITY_INFO;
		ParseSimpleAbility(xmlAll, "POSAbility");
        break;
    case 260: //车辆二次识别检测能力
        m_dwAbilityType = DEVICE_ABILITY_INFO;
        ParseSimpleAbility(xmlAll, "VehicleRecogAbility");
        break;
	default:
		m_dwAbilityType = 0;
		break;
	}
}

void CDlgAbilityAutoDetect::ParseSimpleAbility(CXmlBase &xmlAll, char* szAbilityName)
{	
	CXmlBase xmlDev;
	
	if (!xmlAll.FindElem(szAbilityName))
	{
		GetDlgItem(IDC_EDT_ABILITY_LOST)->SetWindowText("本地文件中没有当前能力");
		return ;
	}
	xmlAll.Parse(xmlAll.GetChildren().c_str());
	xmlAll.SetRoot();
	
	xmlDev.Parse(m_pOutBuf);
	if (!xmlDev.FindElem(szAbilityName))
	{
		GetDlgItem(IDC_EDT_ABILITY_LOST)->SetWindowText("数据格式错误,无法分析");
		return ;
	}

	ParseAbilityRecursive(xmlAll, xmlDev);

	UpdateData(FALSE);
}

void CDlgAbilityAutoDetect::ParseAbilityRecursive(CXmlBase &xmlAll, CXmlBase &xmlDev)
{
 	string strNode = xmlAll.GetNodeName();
 
 	if (!xmlDev.FindElem(strNode.c_str()))
 	{
 		m_strLostAbility += "LOST:";
		m_strLostAbility += strNode.c_str();
 		m_strLostAbility += "\r\n";
		if (xmlAll.NextSibElem())
		{
			ParseAbilityRecursive(xmlAll, xmlDev);
		}
		return;
 	}
 	
 	if (xmlAll.IntoElem())
	{
		if(xmlDev.IntoElem())
		{
			ParseAbilityRecursive(xmlAll, xmlDev);
			xmlDev.OutOfElem();
		}
		else
		{
			if (xmlDev.GetNodeName() == strNode && xmlDev.GetData() == "" && xmlDev.GetFirstAttributeValue() == "")
			{
				m_strLostAbility += "NULL:";
				m_strLostAbility += xmlDev.GetNodeName().c_str();
				m_strLostAbility += "\r\n";
			}			
			ParseAbilityRecursive(xmlAll, xmlDev);
		}
		xmlAll.OutOfElem();
	}
	else if (xmlDev.GetNodeName() == strNode && xmlDev.GetData() == "" && xmlDev.GetFirstAttributeValue() == "")
	{
		m_strLostAbility += "NULL:";
		m_strLostAbility += xmlDev.GetNodeName().c_str();
		m_strLostAbility += "\r\n";
	}

	if (xmlAll.NextSibElem())
	{
		if (!xmlDev.NextSibElem())	//加这个判断是为了处理相同名称节点存在多个的情况
		{
			do 
			{
				m_strLostAbility += "LOST:";
				m_strLostAbility += xmlAll.GetNodeName().c_str();
 				m_strLostAbility += "\r\n";
			} while (xmlAll.NextSibElem());
			return;
		}
		ParseAbilityRecursive(xmlAll, xmlDev);
	}
}


void CDlgAbilityAutoDetect::OnCbnEditchangeCmbAbilityType()
{
    int iCount = ((CComboBox*)GetDlgItem(IDC_CMB_ABILITY_TYPE))->GetCount();
    for (int i = 0; i < iCount; ++i)
    {
        m_cmbAbilityType.DeleteString(0);
    }
    m_vecCurAbilityType.clear();
    CString strTemp;
    ((CComboBox*)GetDlgItem(IDC_CMB_ABILITY_TYPE))->GetWindowText(strTemp);
    if (strTemp != "")
    {
        m_cmbAbilityType.ShowDropDown(TRUE);
    }
    for (std::vector<CString>::iterator iter = m_vecAbilityType.begin(); iter != m_vecAbilityType.end(); ++iter)
    {
        if (iter->Find(strTemp) >= 0)
        {
            m_cmbAbilityType.AddString(*iter);
            m_vecCurAbilityType.push_back(*iter);
        }
    }
}

int CDlgAbilityAutoDetect::GetSelectedAbilityIndex()
{
    int iSel = m_cmbAbilityType.GetCurSel();
    if (iSel < 0 || iSel >= m_vecCurAbilityType.size())
    {
        return -1;
    }

    CString strTemp = m_vecCurAbilityType[iSel];
    for (int iIndex = 0; iIndex < m_vecAbilityType.size(); ++iIndex)
    {
        if (strTemp == m_vecAbilityType[iIndex])
        {
            return iIndex;
        }
    }
    return -1;
}


void CDlgAbilityAutoDetect::OnCbnSetfocusCmbAbilityType()
{
    m_cmbAbilityType.ShowDropDown(TRUE);
}
