// DlgPlayConvert.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPlayConvert.h"
#include "xml/XmlBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char* g_szFrameRate[64] = {"All Frame","1/16","1/8","1/4","1/2","1","2","4","6","8","10","12","16","20","15","18","22","25","30","35","40","45","50","55","60","3","5","7","9","100","120","24","48"};
char* g_szBitRate[64] = {"Reserved","16K","32K","48K","64K","80K","96K","128K","160K","192K","224K","256K","320K","384K","448K","512K","640K","768K","896K","1024K","1280K","1536K","1792K","2048K","3072K","4096K","8192K","16384K"};
/////////////////////////////////////////////////////////////////////////////
// DlgPlayConvert dialog


DlgPlayConvert::DlgPlayConvert(CWnd* pParent /*=NULL*/)
	: CDialog(DlgPlayConvert::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgPlayConvert)
	m_IntervalFrameI = 0;
	m_bEnableSVC = FALSE;
	m_byENumber = 0;
	//}}AFX_DATA_INIT
	memset(&m_struCompressionInfoV30,0,sizeof(m_struCompressionInfoV30));
	m_pCompresscfgAbility = new NET_DVR_COMPRESSIONCFG_ABILITY;
	m_lPlayHandle = -1;
    m_dwCurChanNo = 1;
    m_pRecvBuf = new char[2*1024*1024];
    memset(m_pRecvBuf,0, 2*1024*1024);
	m_iResolutionNum = 0;
	memset(m_pConvert, 0, LPPLAYBACK_CONVERT_SIZE*sizeof(LPPLAYBACK_CONVERT));
}

DlgPlayConvert::~DlgPlayConvert()
{
    delete[] m_pRecvBuf;
	// 删除之前申请的结构体内存
	for (int i=0; i<LPPLAYBACK_CONVERT_SIZE; ++i)
	{
		if (m_pConvert[i] != NULL)
		{
			delete m_pConvert[i];
			m_pConvert[i] = NULL;
		}
	}
}


void DlgPlayConvert::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgPlayConvert)
	DDX_Control(pDX, IDC_STREAM_TYPE, m_StreamType);
	DDX_Control(pDX, IDC_COM_FORMAT_TYPE, m_comFormatType);
	DDX_Control(pDX, IDC_COM_VIDEO_ENC_COMPLEXITY, m_comVideoEncComplexity);
	DDX_Control(pDX, IDC_COM_VEDIO_FRAME_RATE, m_comVideoFrameRate);
	DDX_Control(pDX, IDC_COM_VEDIO_ENCTYPE, m_comVideoEnctype);
	DDX_Control(pDX, IDC_COM_VEDIO_BITRATE, m_comVideoBitrate);
	DDX_Control(pDX, IDC_COM_RESOLUTION, m_comResolution);
	DDX_Control(pDX, IDC_COM_INTERVAL_BP_FRAME, m_comIntervalBPFrame);
	DDX_Control(pDX, IDC_COM_BITRATE_TYPE, m_comBitrateType);
	DDX_Control(pDX, IDC_COM_PIC_QUALITY, m_comPicQuality);
	DDX_Control(pDX, IDC_COM_AUDIO_ENCTYPE, m_comAudioEnctype);
	DDX_Text(pDX, IDC_INTERVAL_FRAME_I, m_IntervalFrameI);
	DDX_Check(pDX, IDC_ENABLE_SVC, m_bEnableSVC);
	DDX_Text(pDX, IDC_E_NUMBER, m_byENumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgPlayConvert, CDialog)
	//{{AFX_MSG_MAP(DlgPlayConvert)
	ON_BN_CLICKED(IDC_SET, OnSet)
	ON_CBN_SELCHANGE(IDC_COM_VEDIO_FRAME_RATE, OnSelchangeComVedioFrameRate)
	ON_CBN_CLOSEUP(IDC_COM_RESOLUTION, OnCloseupComResolution)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgPlayConvert message handlers
void DlgPlayConvert::Init(LONG &lplayhandle)
{
	m_lPlayHandle = lplayhandle;
}

BOOL DlgPlayConvert::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	DWORD iCurChanIndex = g_pMainDlg->GetCurChanIndex();
	 
	if (GetRecordAbility())
    {

    }
    else
    {
        AfxMessageBox("Get compression ability failed");
    }

    m_comResolution.SetCurSel(0);
    m_comVideoBitrate.SetCurSel(0);
    m_comVideoFrameRate.SetCurSel(0);

	return TRUE; 
}


BOOL DlgPlayConvert::GetRecordAbility()
{
    
    char sSendBuf[256];
    memset(sSendBuf, 0, 256);

	strcpy(sSendBuf, "<RecordAbility version=\"2.0\"></RecordAbility>");
    if (NET_DVR_GetDeviceAbility(g_struDeviceInfo[m_iDeviceIndex].lLoginID, DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), m_pRecvBuf, 2*1024*1024))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "DEVICE_ABILITY_INFO RecordAbility");
		GetResolutionAbility();
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "DEVICE_ABILITY_INFO RecordAbility");
    }

    return TRUE;


}

BOOL DlgPlayConvert::GetResolutionAbility()
{
    
    CXmlBase xmlAbility;    
    if(!xmlAbility.Parse(m_pRecvBuf))
    {
        AfxMessageBox("Parse failed");
        return FALSE;
    }
    
    if (!xmlAbility.FindElem("RecordAbility"))
    {
        AfxMessageBox("FindElem RecordAbility failed");
        return FALSE;
    }
    
    xmlAbility.IntoElem();
    
    if (!xmlAbility.FindElem("PlayBack"))
    {
        AfxMessageBox("FindElem PlayBack failed");
        return FALSE;
    }
    
    xmlAbility.IntoElem();
    if (!xmlAbility.FindElem("PlayConvert"))
    {
        AfxMessageBox("FindElem PlayConvert failed");
        return FALSE;
    }
    
    xmlAbility.IntoElem();
    
    if (!xmlAbility.FindElem("VideoResolutionList"))
    {
        AfxMessageBox("FindElem VideoResolutionList failed");
        return FALSE;
    }
    
    xmlAbility.IntoElem();
    
    string sIndex;	// 分辨率索引
	string sName;	// 分辨率名称
	string sFramerate;	// 帧率
    string sBitrate;	// 码率
    while(xmlAbility.FindElem("VideoResolutionEntry"))
    {
        xmlAbility.IntoElem();
        if (!xmlAbility.FindElem("Index"))
        {
            AfxMessageBox("FindElem Index failed");
            return FALSE;
        }
		sIndex = xmlAbility.GetData();	// 获取分辨率索引

		if (!xmlAbility.FindElem("Name"))
        {
            AfxMessageBox("FindElem Name failed");
            return FALSE;
        }
		sName = xmlAbility.GetData();	// 获取分辨率名称
		m_comResolution.AddString(sName.c_str());

        if (!xmlAbility.FindElem("VideoFrameRate"))
        {
            AfxMessageBox("FindElem VideoFrameRate failed");
            return FALSE;
        }
		sFramerate = xmlAbility.GetData();	// 获取帧率

		if (!xmlAbility.FindElem("VideoBitrate"))
        {
            AfxMessageBox("FindElem VideoBitrate failed");
            return FALSE;
        }

		xmlAbility.IntoElem();

		if (!xmlAbility.FindElem("Range"))
        {
            AfxMessageBox("FindElem VideoBitrate failed");
            return FALSE;
        }

		sBitrate = xmlAbility.GetData();	// 获取码率

		m_iResolutionNum++;
		// 将获取到的分辨率、帧率、码率保存到一个结构体中
		m_pConvert[m_iResolutionNum-1] = new PLAYBACK_CONVERT();
		memset(m_pConvert[m_iResolutionNum-1], -1, sizeof(PLAYBACK_CONVERT));
		int iIndex = atoi(sIndex.c_str());
		m_pConvert[m_iResolutionNum-1]->byIndex = iIndex;
		sscanf(sName.c_str(), "%s", m_pConvert[m_iResolutionNum-1]->szName);

		char szFrameRate[FRAME_RATE_STRING_LENGTH];		// 存储帧率字符串数组
		char szBitRate[BIT_RATE_STRING_LENGTH];			// 存储码率字符串数组
		memset(szFrameRate, 0, FRAME_RATE_STRING_LENGTH*sizeof(char));
		memset(szBitRate, 0, BIT_RATE_STRING_LENGTH*sizeof(char));
		sscanf(sFramerate.c_str(), "%s", szFrameRate);
		sscanf(sBitrate.c_str(), "%s", szBitRate);
		
		int i = 0;
		
		int iFrameRate = 0;
		int iCurrentFrameRate = 0;
		// 帧率转换
		for (i=0; i<FRAME_RATE_STRING_LENGTH; ++i)
		{
			if ('\0' == szFrameRate[i])
			{
				m_pConvert[m_iResolutionNum-1]->dwFrameRate[iCurrentFrameRate] = iFrameRate;
				iCurrentFrameRate++;
				break;
			}
			if (','==szFrameRate[i])
			{
				// 进行结构体转换
				m_pConvert[m_iResolutionNum-1]->dwFrameRate[iCurrentFrameRate] = iFrameRate;
				iCurrentFrameRate++;
				iFrameRate = 0;
			}
			else
			{
				iFrameRate = 10*iFrameRate+int(szFrameRate[i]-48);
			}

		}

		int iBitRate = 0;
		int iCurrentBitRate = 0;
		// 码率转换
		for (i=0; i<BIT_RATE_STRING_LENGTH; ++i)
		{
			if ('\0' == szBitRate[i])
			{
				m_pConvert[m_iResolutionNum-1]->dwBitRate[iCurrentBitRate] = iBitRate;
				iCurrentBitRate++;
				break;
			}
			if (',' == szBitRate[i])
			{
				// 进行结构体转换
				m_pConvert[m_iResolutionNum-1]->dwBitRate[iCurrentBitRate] = iBitRate;
				iCurrentBitRate++;
				iBitRate = 0;
			}
			else
			{
				iBitRate = 10*iBitRate+int(szBitRate[i]-48);
			}
			
		}


		xmlAbility.OutOfElem();
		xmlAbility.OutOfElem();
		if(false == xmlAbility.NextSibElem())
		{
			break;
		}
    }
	
	int i = 0;
	for (i=0; i<FRAME_RATE_SIZE; ++i)
	{
		if((m_pConvert[0]->dwFrameRate)[i] != -1)
		{
			char* k = g_szFrameRate[(m_pConvert[0]->dwFrameRate)[i]];
			m_comVideoFrameRate.AddString(g_szFrameRate[(m_pConvert[0]->dwFrameRate)[i]]);
		}
		else
		{
			break;
		}
	}
	for (i=0; i<BIT_RATE_SIZE; ++i)
	{
		if((m_pConvert[0]->dwBitRate)[i] != -1)
		{
			m_comVideoBitrate.AddString(g_szBitRate[(m_pConvert[0]->dwBitRate)[i]]);
		}
		else
		{
			break;
		}
	}
	
    return TRUE;
    
}

void DlgPlayConvert::OnSet() 
{
	// TODO: Add your control notification handler code here
	
	/*m_struCompressionInfoV30.byAudioEncType = (BYTE)m_comAudioEnctype.GetCurSel();
	m_struCompressionInfoV30.byBitrateType = (BYTE)m_comBitrateType.GetCurSel();
	m_struCompressionInfoV30.byEnableSvc = m_bEnableSVC;
	
	if (m_comFormatType.GetCurSel() == 10)
	{
		m_struCompressionInfoV30.byFormatType = 0xff;
	}
	else
	{
		m_struCompressionInfoV30.byFormatType = (BYTE)m_comFormatType.GetCurSel();
	}
	if (m_comIntervalBPFrame.GetCurSel() == 3)
	{
		m_struCompressionInfoV30.byIntervalBPFrame = 0xfe;
	}
	else
	{
		m_struCompressionInfoV30.byIntervalBPFrame = (BYTE)m_comIntervalBPFrame.GetCurSel();
	}
	
	
	m_struCompressionInfoV30.byPicQuality = (BYTE)m_comPicQuality.GetCurSel();
	m_struCompressionInfoV30.byResolution = (BYTE)m_comResolution.GetItemData(m_comResolution.GetCurSel());
	m_struCompressionInfoV30.byStreamType = (BYTE)m_StreamType.GetCurSel();
	m_struCompressionInfoV30.byVideoEncComplexity = (BYTE)m_comVideoEncComplexity.GetCurSel();
	m_struCompressionInfoV30.byVideoEncType = (BYTE)m_comVideoEnctype.GetCurSel();
	m_struCompressionInfoV30.dwVideoBitrate = m_comVideoBitrate.GetItemData(m_comVideoBitrate.GetCurSel());
	m_struCompressionInfoV30.dwVideoFrameRate = m_iFrameIInterval;
	m_struCompressionInfoV30.wIntervalFrameI = (WORD)m_IntervalFrameI;
	*/

	int iCurSel = m_comResolution.GetCurSel();
	m_struCompressionInfoV30.byResolution = m_pConvert[iCurSel]->byIndex;
	m_struCompressionInfoV30.dwVideoFrameRate = (m_pConvert[iCurSel]->dwFrameRate)[m_comVideoFrameRate.GetCurSel()];
	m_struCompressionInfoV30.dwVideoBitrate = (m_pConvert[iCurSel]->dwBitRate)[m_comVideoBitrate.GetCurSel()];


	char szLan[128] = {0};

    CDialog::OnOK();
}

void DlgPlayConvert::getComPressionInfoV30(NET_DVR_COMPRESSION_INFO_V30 *struCompressionInfoV30)
{
	*struCompressionInfoV30 = m_struCompressionInfoV30;
}

void DlgPlayConvert::OnSelchangeComVedioFrameRate() 
{
	// TODO: Add your control notification handler code here
}

void DlgPlayConvert::OnCloseupComResolution() 
{
	// TODO: Add your control notification handler code here
	m_comVideoFrameRate.ResetContent();
	m_comVideoBitrate.ResetContent();
	int iCurSel = m_comResolution.GetCurSel();

	int i = 0;
	for (i=0; i<FRAME_RATE_SIZE; ++i)
	{
		if((m_pConvert[iCurSel]->dwFrameRate)[i] != -1)
		{
			m_comVideoFrameRate.AddString(g_szFrameRate[(m_pConvert[0]->dwFrameRate)[i]]);
		}
		else
		{
			break;
		}
	}
	for (i=0; i<BIT_RATE_SIZE; ++i)
	{
		if((m_pConvert[iCurSel]->dwBitRate)[i] != -1)
		{
			m_comVideoBitrate.AddString(g_szBitRate[(m_pConvert[0]->dwBitRate)[i]]);
		}
		else
		{
			break;
		}
	}
	m_comVideoFrameRate.SetCurSel(0);
	m_comVideoBitrate.SetCurSel(0);
}
