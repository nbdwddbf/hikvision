// DlgTransCompression.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTransCompression.h"
#include "DlgPreviewWin.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTransCompression dialog


CDlgTransCompression::CDlgTransCompression(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTransCompression::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTransCompression)
	m_dwChannel = 0xffffffff;
	m_dwIInterval = 30;
	m_csStreamId = _T("");
	m_dwBitrate = 0;
	m_bChannel = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgTransCompression::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTransCompression)
	DDX_Control(pDX, IDC_COMBO_STREAMTYPE, m_comboStreamType);
	DDX_Control(pDX, IDC_LIST_SUB_CMP, m_listSubCmp);
	DDX_Control(pDX, IDC_LIST_MAIN_CMP, m_listMainCmp);
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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTransCompression, CDialog)
	//{{AFX_MSG_MAP(CDlgTransCompression)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_MOD, OnBtnMod)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MAIN_CMP, OnClickListMainCmp)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SUB_CMP, OnClickListSubCmp)
	ON_CBN_SELCHANGE(IDC_COMBO_CMP_TYPE, OnSelchangeComboCmpType)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_CHK_CHANNEL, OnChkChannel)
	ON_BN_CLICKED(IDC_BTN_PREVIEW, OnBtnPreview)
	ON_BN_CLICKED(IDC_BTN_COPY_ALL, OnBtnCopyAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTransCompression message handlers

BOOL CDlgTransCompression::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);

	char szLan[128] = {0};
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_iCurSelItem = -1;
	m_comboCmpType.SetCurSel(0);

	m_listMainCmp.SetExtendedStyle(m_listMainCmp.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listSubCmp.SetExtendedStyle(m_listSubCmp.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	
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

	g_StringLanType(szLan, "序号", "Serial No.");
	m_listMainCmp.InsertColumn(0, szLan, LVCFMT_LEFT, 50, -1);
	m_listSubCmp.InsertColumn(0, szLan, LVCFMT_LEFT, 50, -1);

	g_StringLanType(szLan, "流ID", "Stream ID");
	m_listMainCmp.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);
	m_listSubCmp.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);
	
	g_StringLanType(szLan, "通道号", "Related channel");
	m_listMainCmp.InsertColumn(2, szLan, LVCFMT_LEFT, 60, -1);
	m_listSubCmp.InsertColumn(2, szLan, LVCFMT_LEFT, 60, -1);

	g_StringLanType(szLan, "码流类型", "Stream type");
	m_listMainCmp.InsertColumn(3, szLan, LVCFMT_LEFT, 60, -1);
	m_listSubCmp.InsertColumn(3, szLan, LVCFMT_LEFT, 60, -1);

	g_StringLanType(szLan, "分辨率", "Resolution");
	m_listMainCmp.InsertColumn(4, szLan, LVCFMT_LEFT, 100, -1);
	m_listSubCmp.InsertColumn(4, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "码率类型", "Bitrate type");
	m_listMainCmp.InsertColumn(5, szLan, LVCFMT_LEFT, 60, -1);
	m_listSubCmp.InsertColumn(5, szLan, LVCFMT_LEFT, 60, -1);

	g_StringLanType(szLan, "图像质量", "Pic Quality");
	m_listMainCmp.InsertColumn(6, szLan, LVCFMT_LEFT, 60, -1);
	m_listSubCmp.InsertColumn(6, szLan, LVCFMT_LEFT, 60, -1);

	g_StringLanType(szLan, "位率上限", "Video bitrate");
	m_listMainCmp.InsertColumn(7, szLan, LVCFMT_LEFT, 60, -1);
	m_listSubCmp.InsertColumn(7, szLan, LVCFMT_LEFT, 60, -1);

	g_StringLanType(szLan, "帧率", "Frame rate");
	m_listMainCmp.InsertColumn(8, szLan, LVCFMT_LEFT, 60, -1);
	m_listSubCmp.InsertColumn(8, szLan, LVCFMT_LEFT, 60, -1);

	g_StringLanType(szLan, "I帧间隔", "I frame interval");
	m_listMainCmp.InsertColumn(9, szLan, LVCFMT_LEFT, 60, -1);
	m_listSubCmp.InsertColumn(9, szLan, LVCFMT_LEFT, 60, -1);

	g_StringLanType(szLan, "BP帧间隔", "BP frame interval");
	m_listMainCmp.InsertColumn(10, szLan, LVCFMT_LEFT, 60, -1);
	m_listSubCmp.InsertColumn(10, szLan, LVCFMT_LEFT, 60, -1);

	g_StringLanType(szLan, "视频编码类型", "Video encode type");
	m_listMainCmp.InsertColumn(11, szLan, LVCFMT_LEFT, 100, -1);
	m_listSubCmp.InsertColumn(11, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "音频编码类型", "Audio encode type");
	m_listMainCmp.InsertColumn(12, szLan, LVCFMT_LEFT, 100, -1);
	m_listSubCmp.InsertColumn(12, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "视频编码复杂度", "Video encode complexity");
	m_listMainCmp.InsertColumn(13, szLan, LVCFMT_LEFT, 100, -1);
	m_listSubCmp.InsertColumn(13, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "封转类型", "Format type");
	m_listMainCmp.InsertColumn(14, szLan, LVCFMT_LEFT, 60, -1);
	m_listSubCmp.InsertColumn(14, szLan, LVCFMT_LEFT, 60, -1);

	g_StringLanType(szLan, "状态", "Status");
	m_listMainCmp.InsertColumn(15, szLan, LVCFMT_LEFT, 50, -1);
	m_listSubCmp.InsertColumn(15, szLan, LVCFMT_LEFT, 50, -1);

	//OnChkChannel();
	OnSelchangeComboCmpType();

	//设一下控件的初始值
    m_comboStreamType.SetCurSel(0);
	m_comboResolution.SetCurSel(0);
	m_comboBitrateType.SetCurSel(0);
	m_comboPicQuality.SetCurSel(0);
	m_comboFormatType.SetCurSel(1);
	m_comboFrameRate.SetCurSel(0);
	m_comboBPFrame.SetCurSel(0);
	m_comboVEncType.SetCurSel(0);
	m_comboAEncType.SetCurSel(0);
	m_comboEncComplexity.SetCurSel(0);
	m_comboVideoBitrate.SetCurSel(5);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTransCompression::InsertMainResolution()
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

void CDlgTransCompression::InsertSubResolution()
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

void CDlgTransCompression::InsertFrame()
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

void CDlgTransCompression::InsertBitrateType()
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

void CDlgTransCompression::InsertBitrate()
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

void CDlgTransCompression::InsertStreamType()
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

void CDlgTransCompression::InsertPicQuality()
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
 
void CDlgTransCompression::InsertBpFrame()
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

void CDlgTransCompression::InsertVideoEnc()
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

void CDlgTransCompression::InsertAudioEnc()
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

void CDlgTransCompression::InsertVEncComplexity()
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

void CDlgTransCompression::InsertFormatType()
{
	//主动模式下不支持GB28281封装，结构体能力集不够扩展，这里手动插入一下
	char szLan[32] = {0};
	
	m_comboFormatType.ResetContent();
	m_comboFormatType.AddString("RTP");
	m_comboFormatType.SetItemData(0, 2);
	m_comboFormatType.AddString("PS");
	m_comboFormatType.SetItemData(1, 3);
	
// 	for (int nAbilityCount = 0; nAbilityCount < m_struCompressionCfgAblity.dwAbilityNum; nAbilityCount++)
// 	{
// 		if (FORMAT_ABILITY == m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwAbilityType)
// 		{
// 			m_comboFormatType.ResetContent();
// 			for (int i = 0; i < m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].dwNodeNum; i++)
// 			{
// 				m_comboFormatType.AddString((char*)m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
// 				m_comboFormatType.SetItemData(i, m_struCompressionCfgAblity.struAbilityNode[nAbilityCount].struDescNode[i].iValue);
// 			}
// 		}
// 	}
}

void CDlgTransCompression::AddDataToList(DWORD dwList, DWORD dwIndex)
{
	CString csTemp;
		
	switch (dwList)
	{
	case 0:		
// 		m_listMainCmp.SetItemText(dwIndex, 1, m_csStreamId);
// 		csTemp.Format("%d", m_dwChannel);
// 		m_listMainCmp.SetItemText(dwIndex, 2, csTemp);
		if (CB_ERR != m_comboStreamType.GetCurSel())
		{
			m_comboStreamType.GetLBText(m_comboStreamType.GetCurSel(), csTemp);			
			m_listMainCmp.SetItemText(dwIndex, 3, csTemp);
		}
		
		if (CB_ERR != m_comboResolution.GetCurSel())
		{
			m_comboResolution.GetLBText(m_comboResolution.GetCurSel(), csTemp);
			m_listMainCmp.SetItemText(dwIndex, 4, csTemp);
		}
		
		if (CB_ERR != m_comboBitrateType.GetCurSel())
		{
			m_comboBitrateType.GetLBText(m_comboBitrateType.GetCurSel(), csTemp);
			m_listMainCmp.SetItemText(dwIndex, 5, csTemp);
		}
		
		
		if (CB_ERR != m_comboPicQuality.GetCurSel())
		{
			m_comboPicQuality.GetLBText(m_comboPicQuality.GetCurSel(), csTemp);
			m_listMainCmp.SetItemText(dwIndex, 6, csTemp);
		}
		
		if (CB_ERR != m_comboVideoBitrate.GetCurSel())
		{
			m_comboVideoBitrate.GetLBText(m_comboVideoBitrate.GetCurSel(), csTemp);
			if (m_comboVideoBitrate.GetItemData(m_comboVideoBitrate.GetCurSel()) == 0x80000000)
			{
				csTemp.Format("%dKbps", m_dwBitrate);
			}			
			m_listMainCmp.SetItemText(dwIndex, 7, csTemp);
		}
		
		if (CB_ERR != m_comboFrameRate.GetCurSel())
		{
			m_comboFrameRate.GetLBText(m_comboFrameRate.GetCurSel(), csTemp);			
			m_listMainCmp.SetItemText(dwIndex, 8, csTemp);
		}		
		
		csTemp.Format("%d", m_dwIInterval);
		m_listMainCmp.SetItemText(dwIndex, 9, csTemp);
		
		if (CB_ERR != m_comboBPFrame.GetCurSel())
		{
			m_comboBPFrame.GetLBText(m_comboBPFrame.GetCurSel(), csTemp);
			m_listMainCmp.SetItemText(dwIndex, 10, csTemp);
		}
		
		if (CB_ERR != m_comboVEncType.GetCurSel())
		{
			m_comboVEncType.GetLBText(m_comboVEncType.GetCurSel(), csTemp);
			m_listMainCmp.SetItemText(dwIndex, 11, csTemp);
		}
		
		if (CB_ERR != m_comboAEncType.GetCurSel())
		{
			m_comboAEncType.GetLBText(m_comboAEncType.GetCurSel(), csTemp);
			m_listMainCmp.SetItemText(dwIndex, 12, csTemp);
		}		
		
		if (CB_ERR != m_comboEncComplexity.GetCurSel())
		{
			m_comboEncComplexity.GetLBText(m_comboEncComplexity.GetCurSel(), csTemp);
			m_listMainCmp.SetItemText(dwIndex, 13, csTemp);			
		}
		
		if (CB_ERR != m_comboFormatType.GetCurSel())
		{
			m_comboFormatType.GetLBText(m_comboFormatType.GetCurSel(), csTemp);
			m_listMainCmp.SetItemText(dwIndex, 14, csTemp);
		}		
		break;
	case 1:
// 		m_listSubCmp.SetItemText(dwIndex, 1, m_csStreamId);
// 		csTemp.Format("%d", m_dwChannel);
// 		m_listSubCmp.SetItemText(dwIndex, 2, csTemp);
		if (CB_ERR != m_comboStreamType.GetCurSel())
		{
			m_comboStreamType.GetLBText(m_comboStreamType.GetCurSel(), csTemp);			
			m_listSubCmp.SetItemText(dwIndex, 3, csTemp);
		}
		
		if (CB_ERR != m_comboResolution.GetCurSel())
		{
			m_comboResolution.GetLBText(m_comboResolution.GetCurSel(), csTemp);
			m_listSubCmp.SetItemText(dwIndex, 4, csTemp);
		}
		
		if (CB_ERR != m_comboBitrateType.GetCurSel())
		{
			m_comboBitrateType.GetLBText(m_comboBitrateType.GetCurSel(), csTemp);
			m_listSubCmp.SetItemText(dwIndex, 5, csTemp);
		}
		
		
		if (CB_ERR != m_comboPicQuality.GetCurSel())
		{
			m_comboPicQuality.GetLBText(m_comboPicQuality.GetCurSel(), csTemp);
			m_listSubCmp.SetItemText(dwIndex, 6, csTemp);
		}
		
		if (CB_ERR != m_comboVideoBitrate.GetCurSel())
		{
			m_comboVideoBitrate.GetLBText(m_comboVideoBitrate.GetCurSel(), csTemp);
			if (m_comboVideoBitrate.GetItemData(m_comboVideoBitrate.GetCurSel()) == 0x80000000)
			{
				csTemp.Format("%dKbps", m_dwBitrate);
			}
			m_listSubCmp.SetItemText(dwIndex, 7, csTemp);
		}
		
		if (CB_ERR != m_comboFrameRate.GetCurSel())
		{
			m_comboFrameRate.GetLBText(m_comboFrameRate.GetCurSel(), csTemp);			
			m_listSubCmp.SetItemText(dwIndex, 8, csTemp);
		}		
		
		csTemp.Format("%d", m_dwIInterval);
		m_listSubCmp.SetItemText(dwIndex, 9, csTemp);
		
		if (CB_ERR != m_comboBPFrame.GetCurSel())
		{
			m_comboBPFrame.GetLBText(m_comboBPFrame.GetCurSel(), csTemp);
			m_listSubCmp.SetItemText(dwIndex, 10, csTemp);
		}
		
		if (CB_ERR != m_comboVEncType.GetCurSel())
		{
			m_comboVEncType.GetLBText(m_comboVEncType.GetCurSel(), csTemp);
			m_listSubCmp.SetItemText(dwIndex, 11, csTemp);
		}
		
		if (CB_ERR != m_comboAEncType.GetCurSel())
		{
			m_comboAEncType.GetLBText(m_comboAEncType.GetCurSel(), csTemp);
			m_listSubCmp.SetItemText(dwIndex, 12, csTemp);
		}		
		
		if (CB_ERR != m_comboEncComplexity.GetCurSel())
		{
			m_comboEncComplexity.GetLBText(m_comboEncComplexity.GetCurSel(), csTemp);
			m_listSubCmp.SetItemText(dwIndex, 13, csTemp);			
		}
		
		if (CB_ERR != m_comboFormatType.GetCurSel())
		{
			m_comboFormatType.GetLBText(m_comboFormatType.GetCurSel(), csTemp);
			m_listSubCmp.SetItemText(dwIndex, 14, csTemp);
		}
		break;
	case 2:
		AddDataToList(0, dwIndex);
		AddDataToList(1, dwIndex);		
		break;
	default:
		break;
	}
}

void CDlgTransCompression::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	CString csTemp;

	if (m_listMainCmp.GetItemCount() > 64)
	{
		g_StringLanType(szLan, "项目条数超过64", "Item number is more than 64");
		AfxMessageBox(szLan);
		return;
	}
	if (m_csStreamId.GetLength() > 32)
	{
		g_StringLanType(szLan, "流ID长度超过最大长度", "Stream ID too long");
		AfxMessageBox(szLan);
		return;
	}

	if ((m_csStreamId.GetLength() != 0 && m_dwChannel != 0xffffffff) || (m_csStreamId.GetLength() == 0 && m_dwChannel == 0xffffffff))
	{
		g_StringLanType(szLan, "流ID和通道号有且仅有一个有效", "Stream ID and channel number is one and only one effective");
		AfxMessageBox(szLan);
		return;
	}

	csTemp.Format("%d", m_listMainCmp.GetItemCount() + 1);
	m_listMainCmp.InsertItem(m_listMainCmp.GetItemCount(), csTemp);
	m_listSubCmp.InsertItem(m_listSubCmp.GetItemCount(), csTemp);

	AddDataToList(2, m_listMainCmp.GetItemCount() - 1);	

	UpdateData(FALSE);
}

void CDlgTransCompression::OnBtnMod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	CString csTemp;
	
	POSITION ps = NULL;
	int sel = -1;
	int iCmpType = m_comboCmpType.GetCurSel();
	if (iCmpType == 0)
	{
		ps = m_listMainCmp.GetFirstSelectedItemPosition();
		//sel = m_listMainCmp.GetNextSelectedItem(ps);
	}
	else
	{
		ps = m_listSubCmp.GetFirstSelectedItemPosition();
	}	
	
	if (ps == NULL)
	{
		g_StringLanType(szLan, "未选中条目", "No item has been selected");
		AfxMessageBox(szLan);
		return;
	}
	
// 	if (m_iCurSelItem == -1)
// 	{
// 		g_StringLanType(szLan, "未选中条目", "No item has been selected");
// 		AfxMessageBox(szLan);
// 		return;
// 	}
// 	if (m_csStreamId.GetLength() > 32)
// 	{
// 		g_StringLanType(szLan, "流ID长度超过最大长度", "Stream ID too long");
// 		AfxMessageBox(szLan);
// 		return;
// 	}
// 	
// 	if ((m_csStreamId.GetLength() != 0 && m_dwChannel != 0xffffffff) || (m_csStreamId.GetLength() == 0 && m_dwChannel == 0xffffffff))
// 	{
// 		g_StringLanType(szLan, "流ID和通道号有且仅有一个有效", "Stream ID and channel number is one and only one effective");
// 		AfxMessageBox(szLan);
// 		return;
// 	}
 	
	if (iCmpType == 0)
	{
		while ((sel = m_listMainCmp.GetNextSelectedItem(ps)) != -1)
		{
			AddDataToList(0, sel);
		}		
	}
	else
	{
		while ((sel = m_listSubCmp.GetNextSelectedItem(ps)) != -1)
		{
			AddDataToList(1, sel);
		}		
	}
}

void CDlgTransCompression::OnBtnDelete() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	CString csTemp;
	int i = 0;

	if (m_iCurSelItem == -1)
	{
		g_StringLanType(szLan, "未选中条目", "No item has been selected");
		AfxMessageBox(szLan);
		return;
	}

	m_listMainCmp.DeleteItem(m_iCurSelItem);
	m_listSubCmp.DeleteItem(m_iCurSelItem);

	for (i = m_iCurSelItem; i < m_listMainCmp.GetItemCount(); i++)
	{
        csTemp.Format("%d", i + 1);
		m_listMainCmp.SetItemText(i, 0, csTemp);
		m_listSubCmp.SetItemText(i, 0, csTemp);
	}

}

void CDlgTransCompression::OnClickListMainCmp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION  iPos = m_listMainCmp.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
	}
	m_iCurSelItem = m_listMainCmp.GetNextSelectedItem(iPos);
	
	ListToControl(0);

	*pResult = 0;
}

void CDlgTransCompression::OnClickListSubCmp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION  iPos = m_listSubCmp.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
	}
	m_iCurSelItem = m_listSubCmp.GetNextSelectedItem(iPos);
	
	ListToControl(1);

	*pResult = 0;
}

void CDlgTransCompression::OnSelchangeComboCmpType() 
{
	// TODO: Add your control notification handler code here
	if (CB_ERR == m_comboCmpType.GetCurSel())
	{
		return;
	}

	int i = 0;
	if (0 == m_comboCmpType.GetCurSel())
	{
		m_listMainCmp.ShowWindow(SW_SHOW);
		m_listSubCmp.ShowWindow(SW_HIDE);
		InsertMainResolution();
		if (-1 != m_iCurSelItem)
		{
			ListToControl(0);
			//UINT flag = 0;
			for (i = 0; i < m_listMainCmp.GetItemCount(); i++)
			{
				if (i != m_iCurSelItem)
				{
					m_listMainCmp.SetItemState(i, 0, -1);
				}
				else
				{
					m_listMainCmp.SetItemState(m_iCurSelItem, LVIS_SELECTED, LVIS_SELECTED);
				}
			}	
		}
	}
	else if (1 == m_comboCmpType.GetCurSel())
	{
		m_listMainCmp.ShowWindow(SW_HIDE);
		m_listSubCmp.ShowWindow(SW_SHOW);
		InsertSubResolution();
		if (-1 != m_iCurSelItem)
		{
			ListToControl(1);		
			//UINT flag = 0;
			for (i = 0; i < m_listSubCmp.GetItemCount(); i++)
			{
				if (i != m_iCurSelItem)
				{
					m_listSubCmp.SetItemState(i, 0, -1);
				}
				else
				{
					m_listSubCmp.SetItemState(m_iCurSelItem, LVIS_SELECTED, LVIS_SELECTED);
				}
			}							
		}
	}
	else
	{
		return;
	}

	UpdateData(FALSE);
}

void CDlgTransCompression::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	CString csTemp;
	int i = 0;
	int j = 0;
	BOOL bAllSuccess = TRUE;

	if (0 == m_listMainCmp.GetItemCount())
	{
		g_StringLanType(szLan, "无项目", "No item");
		AfxMessageBox(szLan);
		return;
	}

	LPNET_DVR_STREAM_INFO lpStreamInfo = NULL;
	LPNET_DVR_COMPRESSIONCFG_V30 lpCmpCfg = NULL;
	DWORD *pStatus = NULL;
	int iItemCount = m_listMainCmp.GetItemCount();

	lpStreamInfo = new(std::nothrow) NET_DVR_STREAM_INFO[iItemCount];
	lpCmpCfg = new(std::nothrow) NET_DVR_COMPRESSIONCFG_V30[iItemCount];
	pStatus = new(std::nothrow) DWORD[iItemCount];

	if (lpStreamInfo == NULL || lpCmpCfg == NULL || pStatus == NULL)
	{
		g_StringLanType(szLan, "分配内存失败", "New memory fail");
		AfxMessageBox(szLan);
		return;
	}

	memset(lpStreamInfo, 0, sizeof(NET_DVR_STREAM_INFO) * iItemCount);
	memset(lpCmpCfg, 0, sizeof(NET_DVR_COMPRESSIONCFG_V30) * iItemCount);
	memset(pStatus, 0, sizeof(DWORD) * iItemCount);

	LPNET_DVR_STREAM_INFO lpStreamInfoKeep = lpStreamInfo;
	for (i = 0; i < m_listMainCmp.GetItemCount(); i++)
	{
		memset(lpStreamInfo, 0, sizeof(NET_DVR_STREAM_INFO));
		lpStreamInfo->dwSize = sizeof(NET_DVR_STREAM_INFO);		
		strncpy((char *)lpStreamInfo->byID, m_listMainCmp.GetItemText(i, 1), STREAM_ID_LEN);
		lpStreamInfo->dwChannel = atoi(m_listMainCmp.GetItemText(i, 2));
		lpStreamInfo++;
	}

	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_STREAM_DST_COMPRESSIONINFO, iItemCount, lpStreamInfoKeep, \
		sizeof(NET_DVR_STREAM_INFO) * iItemCount, pStatus, lpCmpCfg, sizeof(NET_DVR_COMPRESSIONCFG_V30) * iItemCount))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_STREAM_DST_COMPRESSIONINFO");
		g_StringLanType(szLan, "获取失败", "Get fail");
		AfxMessageBox(szLan);
		delete []lpStreamInfoKeep;
		lpStreamInfoKeep = NULL;
		delete []lpCmpCfg;
		lpCmpCfg = NULL;
		delete []pStatus;
		pStatus = NULL;
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_STREAM_DST_COMPRESSIONINFO");
		LPNET_DVR_COMPRESSIONCFG_V30 lpCmpKeep = lpCmpCfg;
		DWORD *pStatusKeep = pStatus;
		//主码流
		for (i = 0; i < iItemCount; i++)
		{
			if (*pStatus == 0)
			{
				csTemp.Empty();
				for (j = 0; j < m_comboStreamType.GetCount(); j++)
				{
					if (lpCmpCfg->struNormHighRecordPara.byStreamType == m_comboStreamType.GetItemData(j))
					{
						m_comboStreamType.GetLBText(j, csTemp);
						break;
					}
				}
				m_listMainCmp.SetItemText(i, 3, csTemp);
// 				switch (lpCmpCfg->struNormHighRecordPara.byStreamType)
// 				{
// 				case 0:
// 					g_StringLanType(szLan, "视频流", "Video");				
// 					break;
// 				case 1:
// 					g_StringLanType(szLan, "复合流", "Video&Audio");
// 					break;
// 				case 0xfe:
// 					g_StringLanType(szLan, "自动", "Auto");
// 					break;
// 				default:
// 					memset(szLan, 0, sizeof(szLan));
// 					break;
// 				}
// 				m_listMainCmp.SetItemText(i, 3, szLan);
				
				csTemp.Empty();
				for (j = 0; j < m_comboResolution.GetCount(); j++)
				{
					if (lpCmpCfg->struNormHighRecordPara.byResolution == m_comboResolution.GetItemData(j))
					{
						m_comboResolution.GetLBText(j, csTemp);
						break;
					}
				}
				m_listMainCmp.SetItemText(i, 4, csTemp);
				
				csTemp.Empty();
				
				
// 				if (lpCmpCfg->struNormHighRecordPara.byBitrateType == 0xfe)
// 				{
// 					g_StringLanType(szLan, "自动", "Auto");
// 					csTemp.Format("%s", szLan);
// 				}
// 				else
// 				{
					for (j = 0; j < m_comboBitrateType.GetCount(); j++)
					{
						if (lpCmpCfg->struNormHighRecordPara.byBitrateType == m_comboBitrateType.GetItemData(j))
						{
							m_comboBitrateType.GetLBText(j, csTemp);
							break;
						}
					}					
				/*}*/
				m_listMainCmp.SetItemText(i, 5, csTemp);
				
				csTemp.Empty();			
// 				if (lpCmpCfg->struNormHighRecordPara.byPicQuality == 0xfe)
// 				{
// 					g_StringLanType(szLan, "自动", "Auto");
// 					csTemp.Format("%s", szLan);
// 				}
// 				else
// 				{
					for (j = 0; j < m_comboPicQuality.GetCount(); j++)
					{
						if (lpCmpCfg->struNormHighRecordPara.byPicQuality == m_comboPicQuality.GetItemData(j))
						{
							m_comboPicQuality.GetLBText(j, csTemp);
							break;
						}
					}
				/*}*/
				m_listMainCmp.SetItemText(i, 6, csTemp);
				
				csTemp.Empty();
				for (j = 0; j < m_comboVideoBitrate.GetCount(); j++)
				{
					if (lpCmpCfg->struNormHighRecordPara.dwVideoBitrate == m_comboVideoBitrate.GetItemData(j))
					{
						m_comboVideoBitrate.GetLBText(j, csTemp);
						break;
					}
				}

				if (0xfffffffe == lpCmpCfg->struNormHighRecordPara.dwVideoBitrate)
				{
// 					g_StringLanType(szLan, "自动", "Auto");
// 					csTemp.Format("%s", szLan);
				}
				else if ((0x80000000 & lpCmpCfg->struNormHighRecordPara.dwVideoBitrate) != 0)
				{					
					csTemp.Format("%dKbps", (0x7fffffff & lpCmpCfg->struNormHighRecordPara.dwVideoBitrate));
				}
				m_listMainCmp.SetItemText(i, 7, csTemp);
				
				csTemp.Empty();
				for (j = 0; j < m_comboFrameRate.GetCount(); j++)
				{
					if (lpCmpCfg->struNormHighRecordPara.dwVideoFrameRate == m_comboFrameRate.GetItemData(j))
					{
						m_comboFrameRate.GetLBText(j, csTemp);
						break;
					}
				}
// 				if (0xfffffffe == lpCmpCfg->struNormHighRecordPara.dwVideoFrameRate)
// 				{
// 					g_StringLanType(szLan, "自动", "Auto");
// 					csTemp.Format("%s", szLan);
// 				}
				m_listMainCmp.SetItemText(i, 8, csTemp);
				
				csTemp.Format("%d", lpCmpCfg->struNormHighRecordPara.wIntervalFrameI);
				m_listMainCmp.SetItemText(i, 9, csTemp);
				
				csTemp.Empty();
				for (j = 0; j < m_comboBPFrame.GetCount(); j++)
				{
					if (lpCmpCfg->struNormHighRecordPara.byIntervalBPFrame == m_comboBPFrame.GetItemData(j))
					{
						m_comboBPFrame.GetLBText(j, csTemp);
						break;
					}
				}
// 				if (0xfe == lpCmpCfg->struNormHighRecordPara.byIntervalBPFrame)
// 				{
// 					g_StringLanType(szLan, "自动", "Auto");
// 					csTemp.Format("%s", szLan);
// 				}
// 				else if (lpCmpCfg->struNormHighRecordPara.byIntervalBPFrame < 3)				
// 				{
// 					m_comboBPFrame.GetLBText(lpCmpCfg->struNormHighRecordPara.byIntervalBPFrame, csTemp);
// 				}
				m_listMainCmp.SetItemText(i, 10, csTemp);
				
				csTemp.Empty();
// 				switch (lpCmpCfg->struNormHighRecordPara.byVideoEncType)
// 				{
// 				case 0:
// 					csTemp.Format("%s", "Private 264");
// 					break;
// 				case 1:
// 					csTemp.Format("%s", "Stardand H264");
// 					break;
// 				case 2:
// 					csTemp.Format("%s", "mpeg4");
// 					break;
// 				case 7:
// 					csTemp.Format("%s", "M-JPEG");
// 					break;			
// 				default:
// 					csTemp.Format("%s", "0xff");
// 					break;
// 				}
				for (j = 0; j < m_comboVEncType.GetCount(); j++)
				{
					if (lpCmpCfg->struNormHighRecordPara.byVideoEncType == m_comboVEncType.GetItemData(j))
					{
						m_comboVEncType.GetLBText(j, csTemp);
						break;
					}
				}
				m_listMainCmp.SetItemText(i, 11, csTemp);
				
				csTemp.Empty();
// 				switch (lpCmpCfg->struNormHighRecordPara.byAudioEncType)
// 				{
// 				case 0:
// 					csTemp.Format("%s", "G722");
// 					break;
// 				case 1:
// 					csTemp.Format("%s", "G711_U");
// 					break;
// 				case 2:
// 					csTemp.Format("%s", "G711_A");
// 					break;
// 				case 6:
// 					csTemp.Format("%s", "G726");
// 					break;
// 				case 7:
// 					csTemp.Format("%s", "AAC");
// 					break;
// 				case 8:
// 					csTemp.Format("%s", "MPEG2");
// 					break;
// 				default:
// 					csTemp.Format("%s", "0xff");
// 					break;				
// 				}
				for (j = 0; j < m_comboAEncType.GetCount(); j++)
				{
					if (lpCmpCfg->struNormHighRecordPara.byAudioEncType == m_comboAEncType.GetItemData(j))
					{
						m_comboAEncType.GetLBText(j, csTemp);
						break;
					}
				}
				m_listMainCmp.SetItemText(i, 12, csTemp);
				
				csTemp.Empty();
// 				if (0xfe == lpCmpCfg->struNormHighRecordPara.byVideoEncComplexity)
// 				{
// 					g_StringLanType(szLan, "自动", "Auto");
// 					csTemp.Format("%s", szLan);
// 				}
// 				else
// 				{
// 					m_comboEncComplexity.GetLBText(lpCmpCfg->struNormHighRecordPara.byVideoEncComplexity, csTemp);
// 				}
				for (j = 0; j < m_comboEncComplexity.GetCount(); j++)
				{
					if (lpCmpCfg->struNormHighRecordPara.byVideoEncComplexity == m_comboEncComplexity.GetItemData(j))
					{
						m_comboEncComplexity.GetLBText(j, csTemp);
						break;
					}
				}
				m_listMainCmp.SetItemText(i, 13, csTemp);
				
				csTemp.Empty();
// 				if (lpCmpCfg->struNormHighRecordPara.byFormatType > 0)
// 				{
// 					m_comboFormatType.GetLBText(lpCmpCfg->struNormHighRecordPara.byFormatType - 1, csTemp);
// 				}
				for (j = 0; j < m_comboFormatType.GetCount(); j++)
				{
					if (lpCmpCfg->struNormHighRecordPara.byFormatType == m_comboFormatType.GetItemData(j))
					{
						m_comboFormatType.GetLBText(j, csTemp);
						break;
					}
				}
				m_listMainCmp.SetItemText(i, 14, csTemp);				
				
				//子码流			
// 				switch (lpCmpCfg->struNetPara.byStreamType)
// 				{
// 				case 0:
// 					g_StringLanType(szLan, "视频流", "Video");				
// 					break;
// 				case 1:
// 					g_StringLanType(szLan, "复合流", "Video&Audio");
// 					break;
// 				case 0xfe:
// 					g_StringLanType(szLan, "自动", "Auto");
// 					break;
// 				default:
// 					memset(szLan, 0, sizeof(szLan));
// 					break;
// 				}
				csTemp.Empty();

				for (j = 0; j < m_comboStreamType.GetCount(); j++)
				{
					if (lpCmpCfg->struNetPara.byStreamType == m_comboStreamType.GetItemData(j))
					{
						m_comboStreamType.GetLBText(j, csTemp);
						break;
					}
				}
				m_listSubCmp.SetItemText(i, 3, csTemp);
				
				csTemp.Empty();
				for (j = 0; j < m_comboResolution.GetCount(); j++)
				{
					if (lpCmpCfg->struNetPara.byResolution == m_comboResolution.GetItemData(j))
					{
						m_comboResolution.GetLBText(j, csTemp);
						break;
					}
				}
				m_listSubCmp.SetItemText(i, 4, csTemp);
				
				csTemp.Empty();
				
				
// 				if (lpCmpCfg->struNetPara.byBitrateType == 0xfe)
// 				{
// 					g_StringLanType(szLan, "自动", "Auto");
// 					csTemp.Format("%s", szLan);
// 				}
// 				else
// 				{
					for (j = 0; j < m_comboBitrateType.GetCount(); j++)
					{
						if (lpCmpCfg->struNetPara.byBitrateType == m_comboBitrateType.GetItemData(j))
						{
							m_comboBitrateType.GetLBText(j, csTemp);
							break;
						}
					}					
				/*}*/
				m_listSubCmp.SetItemText(i, 5, csTemp);
				
				csTemp.Empty();			
// 				if (lpCmpCfg->struNetPara.byPicQuality == 0xfe)
// 				{
// 					g_StringLanType(szLan, "自动", "Auto");
// 					csTemp.Format("%s", szLan);
// 				}
// 				else
// 				{
					for (j = 0; j < m_comboPicQuality.GetCount(); j++)
					{
						if (lpCmpCfg->struNetPara.byPicQuality == m_comboPicQuality.GetItemData(j))
						{
							m_comboPicQuality.GetLBText(j, csTemp);
							break;
						}
					}					
				/*}*/
				m_listSubCmp.SetItemText(i, 6, csTemp);
				
				csTemp.Empty();
				for (j = 0; j < m_comboVideoBitrate.GetCount(); j++)
				{
					if (lpCmpCfg->struNetPara.dwVideoBitrate == m_comboVideoBitrate.GetItemData(j))
					{
						m_comboVideoBitrate.GetLBText(j, csTemp);
						break;
					}
				}
				if (0xfffffffe == lpCmpCfg->struNetPara.dwVideoBitrate)
				{
// 					g_StringLanType(szLan, "自动", "Auto");
// 					csTemp.Format("%s", szLan);
				}
				else if ((0x80000000 & lpCmpCfg->struNetPara.dwVideoBitrate) != 0)
				{
					csTemp.Format("%dKbps", (0x7ffffff & lpCmpCfg->struNetPara.dwVideoBitrate));
				}
				m_listSubCmp.SetItemText(i, 7, csTemp);
				
				csTemp.Empty();
				for (j = 0; j < m_comboFrameRate.GetCount(); j++)
				{
					if (lpCmpCfg->struNetPara.dwVideoFrameRate == m_comboFrameRate.GetItemData(j))
					{
						m_comboFrameRate.GetLBText(j, csTemp);
						break;
					}
				}
// 				if (0xfffffffe == lpCmpCfg->struNetPara.dwVideoFrameRate)
// 				{
// 					g_StringLanType(szLan, "自动", "Auto");
// 					csTemp.Format("%s", szLan);
// 				}
				m_listSubCmp.SetItemText(i, 8, csTemp);
				
				csTemp.Format("%d", lpCmpCfg->struNetPara.wIntervalFrameI);
				m_listSubCmp.SetItemText(i, 9, csTemp);
				
				csTemp.Empty();
// 				if (0xfe == lpCmpCfg->struNetPara.byIntervalBPFrame)
// 				{
// 					g_StringLanType(szLan, "自动", "Auto");
// 					csTemp.Format("%s", szLan);
// 				}
// 				else if (lpCmpCfg->struNetPara.byIntervalBPFrame < 3)				
// 				{
// 					m_comboBPFrame.GetLBText(lpCmpCfg->struNetPara.byIntervalBPFrame, csTemp);
// 				}

				for (j = 0; j < m_comboBPFrame.GetCount(); j++)
				{
					if (lpCmpCfg->struNetPara.byIntervalBPFrame == m_comboBPFrame.GetItemData(j))
					{
						m_comboBPFrame.GetLBText(j, csTemp);
						break;
					}
				}
				m_listSubCmp.SetItemText(i, 10, csTemp);
				
				csTemp.Empty();
// 				switch (lpCmpCfg->struNetPara.byVideoEncType)
// 				{
// 				case 0:
// 					csTemp.Format("%s", "Private 264");
// 					break;
// 				case 1:
// 					csTemp.Format("%s", "Stardand H264");
// 					break;
// 				case 2:
// 					csTemp.Format("%s", "mpeg4");
// 					break;
// 				case 7:
// 					csTemp.Format("%s", "M-JPEG");
// 					break;			
// 				default:
// 					csTemp.Format("%s", "0xff");
// 					break;
// 				}

				for (j = 0; j < m_comboVEncType.GetCount(); j++)
				{
					if (lpCmpCfg->struNetPara.byVideoEncType == m_comboVEncType.GetItemData(j))
					{
						m_comboVEncType.GetLBText(j, csTemp);
						break;
					}
				}
				m_listSubCmp.SetItemText(i, 11, csTemp);
				
				csTemp.Empty();
// 				switch (lpCmpCfg->struNetPara.byAudioEncType)
// 				{
// 				case 0:
// 					csTemp.Format("%s", "G722");
// 					break;
// 				case 1:
// 					csTemp.Format("%s", "G711_U");
// 					break;
// 				case 2:
// 					csTemp.Format("%s", "G711_A");
// 					break;
// 				case 6:
// 					csTemp.Format("%s", "G726");
// 					break;
// 				case 7:
// 					csTemp.Format("%s", "AAC");
// 					break;
// 				case 8:
// 					csTemp.Format("%s", "MPEG2");
// 					break;
// 				default:
// 					csTemp.Format("%s", "0xff");
// 					break;				
// 				}

				for (j = 0; j < m_comboAEncType.GetCount(); j++)
				{
					if (lpCmpCfg->struNetPara.byAudioEncType == m_comboAEncType.GetItemData(j))
					{
						m_comboAEncType.GetLBText(j, csTemp);
						break;
					}
				}
				m_listSubCmp.SetItemText(i, 12, csTemp);
				
				csTemp.Empty();
// 				if (0xfe == lpCmpCfg->struNetPara.byVideoEncComplexity)
// 				{
// 					g_StringLanType(szLan, "自动", "Auto");
// 					csTemp.Format("%s", szLan);
// 				}
// 				else
// 				{
// 					m_comboEncComplexity.GetLBText(lpCmpCfg->struNetPara.byVideoEncComplexity, csTemp);
// 				}
				for (j = 0; j < m_comboEncComplexity.GetCount(); j++)
				{
					if (lpCmpCfg->struNetPara.byVideoEncComplexity == m_comboEncComplexity.GetItemData(j))
					{
						m_comboEncComplexity.GetLBText(j, csTemp);
						break;
					}
				}
				m_listSubCmp.SetItemText(i, 13, csTemp);
				
				csTemp.Empty();
// 				if (lpCmpCfg->struNetPara.byFormatType > 0)
// 				{
// 					m_comboFormatType.GetLBText(lpCmpCfg->struNetPara.byFormatType - 1, csTemp);
// 				}
				for (j = 0; j < m_comboFormatType.GetCount(); j++)
				{
					if (lpCmpCfg->struNetPara.byFormatType == m_comboFormatType.GetItemData(j))
					{
						m_comboFormatType.GetLBText(j, csTemp);
						break;
					}
				}				
				m_listSubCmp.SetItemText(i, 14, csTemp);			
			}
			else
			{
				//如果某个节点失败就把各项清空
				bAllSuccess = FALSE;
				csTemp.Empty();
				for (int j = 3; j < 15; j++)
				{
					m_listMainCmp.SetItemText(i, j, csTemp);
					m_listSubCmp.SetItemText(i, j, csTemp);
				}
			}		
		
			csTemp.Format("%d", *pStatus);
			m_listMainCmp.SetItemText(i, 15, csTemp);
			m_listSubCmp.SetItemText(i, 15, csTemp);
		    lpCmpCfg++;
		    pStatus++;
		}
		
		if (!bAllSuccess)
		{
			g_StringLanType(szLan, "未完全成功，请查看状态值", "Not all success, please check status");
			AfxMessageBox(szLan);
		}
		delete []lpStreamInfoKeep;
		lpStreamInfoKeep = NULL;
		delete []lpCmpKeep;
		lpCmpKeep = NULL;
		delete []pStatusKeep;
	    pStatusKeep = NULL;
	}
	
	UpdateData(FALSE);
}

void CDlgTransCompression::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	BOOL bAllSuccess = TRUE;
	char szLan[128] = {0};
	CString csTemp;
	int i = 0;
	int j = 0;
	
	if (0 == m_listMainCmp.GetItemCount())
	{
		g_StringLanType(szLan, "无项目", "No item");
		AfxMessageBox(szLan);
		return;
	}
	
	LPNET_DVR_STREAM_INFO lpStreamInfo = NULL;
	LPNET_DVR_COMPRESSIONCFG_V30 lpCmpCfg = NULL;
	DWORD *pStatus = NULL;
	int iItemCount = m_listMainCmp.GetItemCount();
	
	lpStreamInfo = new(std::nothrow) NET_DVR_STREAM_INFO[iItemCount];
	lpCmpCfg = new(std::nothrow) NET_DVR_COMPRESSIONCFG_V30[iItemCount];
	pStatus = new(std::nothrow) DWORD[iItemCount];
	
	if (lpStreamInfo == NULL || lpCmpCfg == NULL || pStatus == NULL)
	{
		g_StringLanType(szLan, "分配内存失败", "New memory fail");
		AfxMessageBox(szLan);
		return;
	}

	memset(lpStreamInfo, 0, sizeof(NET_DVR_STREAM_INFO) * iItemCount);
	memset(lpCmpCfg, 0, sizeof(NET_DVR_COMPRESSIONCFG_V30) * iItemCount);
	memset(pStatus, 0, sizeof(DWORD) * iItemCount);

	LPNET_DVR_STREAM_INFO lpStreamInfoKeep = lpStreamInfo;
	LPNET_DVR_COMPRESSIONCFG_V30 lpCmpKeep = lpCmpCfg;
	DWORD *pStatusKeep = pStatus;
	//从列表中读数据至结构体
	//配置条件
	for (i = 0; i < m_listMainCmp.GetItemCount(); i++)
	{
		memset(lpStreamInfo, 0, sizeof(NET_DVR_STREAM_INFO));
		lpStreamInfo->dwSize = sizeof(NET_DVR_STREAM_INFO);		
		strncpy((char *)lpStreamInfo->byID, m_listMainCmp.GetItemText(i, 1), STREAM_ID_LEN);
		lpStreamInfo->dwChannel = atoi(m_listMainCmp.GetItemText(i, 2));
		lpStreamInfo++;
	}

	
	for (i = 0; i < m_listMainCmp.GetItemCount(); i++)
	{
		lpCmpCfg->dwSize = sizeof(*lpCmpCfg);
		int iIndex = -1;

		//主码流
		if (CB_ERR != (iIndex = m_comboStreamType.FindStringExact(0, m_listMainCmp.GetItemText(i, 3))))
		{		
			lpCmpCfg->struNormHighRecordPara.byStreamType = m_comboStreamType.GetItemData(iIndex);			
		}

		if (CB_ERR != (iIndex = m_comboResolution.FindStringExact(0, m_listMainCmp.GetItemText(i, 4))))
		{
			lpCmpCfg->struNormHighRecordPara.byResolution = m_comboResolution.GetItemData(iIndex);			
		}

		if (CB_ERR != (iIndex = m_comboBitrateType.FindStringExact(0, m_listMainCmp.GetItemText(i, 5))))
		{
			lpCmpCfg->struNormHighRecordPara.byBitrateType = m_comboBitrateType.GetItemData(iIndex);
		}

		if (CB_ERR != (iIndex = m_comboPicQuality.FindStringExact(0, m_listMainCmp.GetItemText(i, 6))))
		{
			lpCmpCfg->struNormHighRecordPara.byPicQuality = m_comboPicQuality.GetItemData(iIndex);						
		}

		if (CB_ERR != (iIndex = m_comboVideoBitrate.FindStringExact(0, m_listMainCmp.GetItemText(i, 7))))
		{
			lpCmpCfg->struNormHighRecordPara.dwVideoBitrate = m_comboVideoBitrate.GetItemData(iIndex);
		}
		else if ((m_listMainCmp.GetItemText(i,7)).GetLength() != 0)
		{
			strncpy(szLan, m_listMainCmp.GetItemText(i, 7), (m_listMainCmp.GetItemText(i, 7)).GetLength() - 4);
			lpCmpCfg->struNormHighRecordPara.dwVideoBitrate = (0x80000000 | atoi(szLan));
		}		

		if (CB_ERR != (iIndex = m_comboFrameRate.FindStringExact(0, m_listMainCmp.GetItemText(i, 8))))
		{
			lpCmpCfg->struNormHighRecordPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(iIndex);
		}

		lpCmpCfg->struNormHighRecordPara.wIntervalFrameI = atoi(m_listMainCmp.GetItemText(i, 9));

		if (CB_ERR != (iIndex = m_comboBPFrame.FindStringExact(0, m_listMainCmp.GetItemText(i, 10))))
		{			
			lpCmpCfg->struNormHighRecordPara.byIntervalBPFrame = m_comboBPFrame.GetItemData(iIndex);			
		}

		if (CB_ERR != (iIndex = m_comboVEncType.FindStringExact(0, m_listMainCmp.GetItemText(i, 11))))
		{
			lpCmpCfg->struNormHighRecordPara.byVideoEncType = m_comboVEncType.GetItemData(iIndex);			
		}

		if (CB_ERR != (iIndex = m_comboAEncType.FindStringExact(0, m_listMainCmp.GetItemText(i, 12))))
		{
			lpCmpCfg->struNormHighRecordPara.byAudioEncType = m_comboAEncType.GetItemData(iIndex);			
		}

		if (CB_ERR != (iIndex = m_comboEncComplexity.FindStringExact(0, m_listMainCmp.GetItemText(i, 13))))
		{
			lpCmpCfg->struNormHighRecordPara.byVideoEncComplexity = m_comboEncComplexity.GetItemData(iIndex);
		}

		if (CB_ERR != (iIndex = m_comboFormatType.FindStringExact(0, m_listMainCmp.GetItemText(i, 14))))
		{
			lpCmpCfg->struNormHighRecordPara.byFormatType = m_comboFormatType.GetItemData(iIndex);
		}

		//子码流
		if (CB_ERR != (iIndex = m_comboStreamType.FindStringExact(0, m_listSubCmp.GetItemText(i, 3))))
		{
			lpCmpCfg->struNetPara.byStreamType = m_comboStreamType.GetItemData(iIndex);			
		}

		if (CB_ERR != (iIndex = m_comboResolution.FindStringExact(0, m_listSubCmp.GetItemText(i, 4))))
		{
			lpCmpCfg->struNetPara.byResolution = m_comboResolution.GetItemData(iIndex);			
		}

		if (CB_ERR != (iIndex = m_comboBitrateType.FindStringExact(0, m_listSubCmp.GetItemText(i, 5))))
		{
			lpCmpCfg->struNetPara.byBitrateType = m_comboBitrateType.GetItemData(iIndex);
		}

		if (CB_ERR != (iIndex = m_comboPicQuality.FindStringExact(0, m_listSubCmp.GetItemText(i, 6))))
		{
			lpCmpCfg->struNetPara.byPicQuality = m_comboPicQuality.GetItemData(iIndex);						
		}

		if (CB_ERR != (iIndex = m_comboVideoBitrate.FindStringExact(0, m_listSubCmp.GetItemText(i, 7))))
		{
			lpCmpCfg->struNetPara.dwVideoBitrate = m_comboVideoBitrate.GetItemData(iIndex);
		}
		else if ((m_listSubCmp.GetItemText(i,7)).GetLength() != 0)
		{
			strncpy(szLan, m_listSubCmp.GetItemText(i, 7), (m_listSubCmp.GetItemText(i, 7)).GetLength() - 4);
			lpCmpCfg->struNetPara.dwVideoBitrate = (0x80000000 | atoi(szLan));
		}

		if (CB_ERR != (iIndex = m_comboFrameRate.FindStringExact(0, m_listSubCmp.GetItemText(i, 8))))
		{
			lpCmpCfg->struNetPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(iIndex);
		}

		lpCmpCfg->struNetPara.wIntervalFrameI = atoi(m_listSubCmp.GetItemText(i, 9));

		if (CB_ERR != (iIndex = m_comboBPFrame.FindStringExact(0, m_listSubCmp.GetItemText(i, 10))))
		{
			lpCmpCfg->struNetPara.byIntervalBPFrame = m_comboBPFrame.GetItemData(iIndex);
		}

		if (CB_ERR != (iIndex = m_comboVEncType.FindStringExact(0, m_listSubCmp.GetItemText(i, 11))))
		{
			lpCmpCfg->struNetPara.byVideoEncType = m_comboVEncType.GetItemData(iIndex);
		}

		if (CB_ERR != (iIndex = m_comboAEncType.FindStringExact(0, m_listSubCmp.GetItemText(i, 12))))
		{
			lpCmpCfg->struNetPara.byAudioEncType = m_comboAEncType.GetItemData(iIndex);			
		}

		if (CB_ERR != (iIndex = m_comboEncComplexity.FindStringExact(0, m_listSubCmp.GetItemText(i, 13))))
		{
			lpCmpCfg->struNetPara.byVideoEncComplexity = m_comboEncComplexity.GetItemData(iIndex);			
		}

		if (CB_ERR != (iIndex = m_comboFormatType.FindStringExact(0, m_listSubCmp.GetItemText(i, 14))))
		{
			lpCmpCfg->struNetPara.byFormatType = m_comboFormatType.GetItemData(iIndex);			
		}

		lpCmpCfg++;
	}

	if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_STREAM_DST_COMPRESSIONINFO, iItemCount, lpStreamInfoKeep, \
		iItemCount * sizeof(NET_DVR_STREAM_INFO), pStatusKeep, lpCmpKeep, iItemCount * sizeof(NET_DVR_COMPRESSIONCFG_V30)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_STREAM_DST_COMPRESSIONINFO");
		g_StringLanType(szLan, "设置失败", "Set fail");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_STREAM_DST_COMPRESSIONINFO");
		g_StringLanType(szLan, "设置成功", "Set success");
		AfxMessageBox(szLan);
		for (i = 0; i < m_listMainCmp.GetItemCount(); i++)
		{
			if (*pStatus != 0)
			{
				bAllSuccess = FALSE;
			}
			csTemp.Format("%d", *pStatus);
			m_listMainCmp.SetItemText(i, 15, csTemp);
			m_listSubCmp.SetItemText(i, 15, csTemp);
			pStatus++;
		}
	}

	if (!bAllSuccess)
	{
		g_StringLanType(szLan, "未完全成功，请检查状态", "Not all success, please check status");
		AfxMessageBox(szLan);
	}
	delete []lpCmpKeep;
	lpCmpKeep = NULL;
	delete []lpStreamInfoKeep;
	lpStreamInfoKeep = NULL;
	delete []pStatusKeep;
	pStatusKeep = NULL;
}

void CDlgTransCompression::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgTransCompression::OnChkChannel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_bChannel)
	{
		GetDlgItem(IDC_EDIT_ID)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CHANNEL)->EnableWindow(TRUE);
		m_csStreamId.Empty();
	}
	else
	{
		GetDlgItem(IDC_EDIT_CHANNEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_ID)->EnableWindow(TRUE);
		m_dwChannel = 0xffffffff;
	}

	UpdateData(FALSE);
}

void CDlgTransCompression::OnBtnPreview() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};

	if (m_listMainCmp.GetItemCount() == 0)
	{
		g_StringLanType(szLan, "无项目", "No item");
		AfxMessageBox(szLan);
		return;
	}
	if (m_iCurSelItem == -1)
	{
		g_StringLanType(szLan, "未选中项目", "No item has been selected");
		AfxMessageBox(szLan);
		return;
	}

	CDlgPreviewWin dlg;
	dlg.m_lUserID = m_lUserID;

	NET_DVR_STREAM_INFO struStreamInfo = {0};
	
	struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);		
	strncpy((char *)struStreamInfo.byID, m_listMainCmp.GetItemText(m_iCurSelItem, 1), STREAM_ID_LEN);
	struStreamInfo.dwChannel = atoi(m_listMainCmp.GetItemText(m_iCurSelItem, 2));

	memcpy(&(dlg.m_struStreamInfo), &struStreamInfo, sizeof(struStreamInfo));

	dlg.DoModal();
}

void CDlgTransCompression::ListToControl(BYTE byList)
{
	int iIndex = -1;
	char szLan[128] = {0};

	if (byList == 0)
	{
		m_csStreamId = m_listMainCmp.GetItemText(m_iCurSelItem, 1);
		m_dwChannel = atol(m_listMainCmp.GetItemText(m_iCurSelItem, 2));
		
		if (CB_ERR != (iIndex = m_comboStreamType.FindStringExact(0, m_listMainCmp.GetItemText(m_iCurSelItem, 3))))
		{
			m_comboStreamType.SetCurSel(iIndex);
		}
		else
		{
			m_comboStreamType.SetCurSel(-1);
		}
		
		if (CB_ERR != (iIndex = m_comboResolution.FindStringExact(0, m_listMainCmp.GetItemText(m_iCurSelItem, 4))))
		{
			m_comboResolution.SetCurSel(iIndex);
		}
		else
		{
			m_comboResolution.SetCurSel(-1);
		}
		
		if (CB_ERR != (iIndex = m_comboBitrateType.FindStringExact(0, m_listMainCmp.GetItemText(m_iCurSelItem, 5))))
		{
			m_comboBitrateType.SetCurSel(iIndex);
		}
		else
		{
			m_comboBitrateType.SetCurSel(-1);
		}
		
		if (CB_ERR != (iIndex = m_comboPicQuality.FindStringExact(0, m_listMainCmp.GetItemText(m_iCurSelItem, 6))))
		{
			m_comboPicQuality.SetCurSel(iIndex);
		}
		else
		{
			m_comboPicQuality.SetCurSel(-1);
		}
		
		if (CB_ERR != (iIndex = m_comboVideoBitrate.FindStringExact(0, m_listMainCmp.GetItemText(m_iCurSelItem, 7))))
		{
			m_comboVideoBitrate.SetCurSel(iIndex);
		}
		else if ((m_listMainCmp.GetItemText(m_iCurSelItem, 7)).GetLength() != 0)
		{
			strncpy(szLan, m_listMainCmp.GetItemText(m_iCurSelItem, 7), (m_listMainCmp.GetItemText(m_iCurSelItem, 7)).GetLength() - 4);
			m_dwBitrate = atol(szLan);
			m_comboVideoBitrate.SetCurSel(m_comboVideoBitrate.GetCount() - 1);
		}
		else
		{
			m_comboVideoBitrate.SetCurSel(-1);
		}
		
		if (CB_ERR != (iIndex = m_comboFrameRate.FindStringExact(0, m_listMainCmp.GetItemText(m_iCurSelItem, 8))))
		{
			m_comboFrameRate.SetCurSel(iIndex);
		}
		else
		{
			m_comboFrameRate.SetCurSel(-1);
		}
		
		if ((m_listMainCmp.GetItemText(m_iCurSelItem, 9)).GetLength() != 0)
		{
			m_dwIInterval = atoi(m_listMainCmp.GetItemText(m_iCurSelItem, 9));
		}
		else
		{
			m_dwIInterval = 0;
		}
		
		if (CB_ERR != (iIndex = m_comboBPFrame.FindStringExact(0, m_listMainCmp.GetItemText(m_iCurSelItem, 10))))
		{
			m_comboBPFrame.SetCurSel(iIndex);
		}
		else
		{
			m_comboBPFrame.SetCurSel(-1);
		}
		
		if (CB_ERR != (iIndex = m_comboVEncType.FindStringExact(0, m_listMainCmp.GetItemText(m_iCurSelItem, 11))))
		{
			m_comboVEncType.SetCurSel(iIndex);
		}
		else
		{
			m_comboVEncType.SetCurSel(-1);
		}
		
		if (CB_ERR != (iIndex = m_comboAEncType.FindStringExact(0, m_listMainCmp.GetItemText(m_iCurSelItem, 12))))
		{
			m_comboAEncType.SetCurSel(iIndex);
		}
		else
		{
			m_comboAEncType.SetCurSel(-1);
		}
		
		if (CB_ERR != (iIndex = m_comboEncComplexity.FindStringExact(0, m_listMainCmp.GetItemText(m_iCurSelItem, 13))))
		{
			m_comboEncComplexity.SetCurSel(iIndex);
		}
		else
		{
			m_comboEncComplexity.SetCurSel(-1);
		}
		
		if (CB_ERR != (iIndex = m_comboFormatType.FindStringExact(0, m_listMainCmp.GetItemText(m_iCurSelItem, 14))))
		{
			m_comboFormatType.SetCurSel(iIndex);
		}
		else
		{
			m_comboFormatType.SetCurSel(-1);
		}
	}
	else if (byList == 1)
	{
		m_csStreamId = m_listSubCmp.GetItemText(m_iCurSelItem, 1);
		m_dwChannel = atol(m_listSubCmp.GetItemText(m_iCurSelItem, 2));
		
		if (CB_ERR != (iIndex = m_comboStreamType.FindStringExact(0, m_listSubCmp.GetItemText(m_iCurSelItem, 3))))
		{
			m_comboStreamType.SetCurSel(iIndex);
		}
		else
		{
			m_comboStreamType.SetCurSel(-1);
		}
		
		if (CB_ERR != (iIndex = m_comboResolution.FindStringExact(0, m_listSubCmp.GetItemText(m_iCurSelItem, 4))))
		{
			m_comboResolution.SetCurSel(iIndex);
		}
		else
		{
			m_comboResolution.SetCurSel(-1);
		}
		
		if (CB_ERR != (iIndex = m_comboBitrateType.FindStringExact(0, m_listSubCmp.GetItemText(m_iCurSelItem, 5))))
		{
			m_comboBitrateType.SetCurSel(iIndex);
		}
		else
		{
			m_comboBitrateType.SetCurSel(-1);
		}
		
		if (CB_ERR != (iIndex = m_comboPicQuality.FindStringExact(0, m_listSubCmp.GetItemText(m_iCurSelItem, 6))))
		{
			m_comboPicQuality.SetCurSel(iIndex);
		}
		else
		{
			m_comboPicQuality.SetCurSel(-1);
		}
		
		if (CB_ERR != (iIndex = m_comboVideoBitrate.FindStringExact(0, m_listSubCmp.GetItemText(m_iCurSelItem, 7))))
		{
			m_comboVideoBitrate.SetCurSel(iIndex);
		}
		else if ((m_listSubCmp.GetItemText(m_iCurSelItem, 7)).GetLength() != 0)
		{
			strncpy(szLan, m_listSubCmp.GetItemText(m_iCurSelItem, 7), (m_listSubCmp.GetItemText(m_iCurSelItem, 7)).GetLength() - 4);
			m_dwBitrate = atol(szLan);
			m_comboVideoBitrate.SetCurSel(m_comboVideoBitrate.GetCount() - 1);
		}
		else
		{
			m_comboVideoBitrate.SetCurSel(-1);
			m_dwBitrate = 0;
		}
		
		if (CB_ERR != (iIndex = m_comboFrameRate.FindStringExact(0, m_listSubCmp.GetItemText(m_iCurSelItem, 8))))
		{
			m_comboFrameRate.SetCurSel(iIndex);
		}
		else
		{
			m_comboFrameRate.SetCurSel(-1);
		}
		
		if ((m_listSubCmp.GetItemText(m_iCurSelItem, 9)).GetLength() != 0)
		{
			m_dwIInterval = atoi(m_listSubCmp.GetItemText(m_iCurSelItem, 9));
		}
		else
		{
			m_dwIInterval = 0;
		}
		
		if (CB_ERR != (iIndex = m_comboBPFrame.FindStringExact(0, m_listSubCmp.GetItemText(m_iCurSelItem, 10))))
		{
			m_comboBPFrame.SetCurSel(iIndex);
		}
		else
		{
			m_comboBPFrame.SetCurSel(-1);
		}
		
		if (CB_ERR != (iIndex = m_comboVEncType.FindStringExact(0, m_listSubCmp.GetItemText(m_iCurSelItem, 11))))
		{
			m_comboVEncType.SetCurSel(iIndex);
		}
		else
		{
			m_comboVEncType.SetCurSel(-1);
		}
		
		if (CB_ERR != (iIndex = m_comboAEncType.FindStringExact(0, m_listSubCmp.GetItemText(m_iCurSelItem, 12))))
		{
			m_comboAEncType.SetCurSel(iIndex);
		}
		else
		{
			m_comboAEncType.SetCurSel(-1);
		}
		
		if (CB_ERR != (iIndex = m_comboEncComplexity.FindStringExact(0, m_listSubCmp.GetItemText(m_iCurSelItem, 13))))
		{
			m_comboEncComplexity.SetCurSel(iIndex);
		}
		else
		{
			m_comboEncComplexity.SetCurSel(-1);
		}
		
		if (CB_ERR != (iIndex = m_comboFormatType.FindStringExact(0, m_listSubCmp.GetItemText(m_iCurSelItem, 14))))
		{
			m_comboFormatType.SetCurSel(iIndex);
		}
		else
		{
			m_comboFormatType.SetCurSel(-1);
		}
	}
	else
	{
		return;
	}

	UpdateData(FALSE);
}

//同步流来源中添加的ID信息
void CDlgTransCompression::AddStreamInfoToList(LPNET_DVR_STREAM_INFO lpStreamInfo, DWORD dwNum)
{
	if (NULL == lpStreamInfo || dwNum == 0)
	{
		return;
	}

	CString csTemp;
	LPNET_DVR_STREAM_INFO lpTemp = lpStreamInfo;
	m_listMainCmp.DeleteAllItems();
	m_listSubCmp.DeleteAllItems();

	for (int i = 0; i < dwNum; i++)
	{
		csTemp.Format("%d", i + 1);
		m_listMainCmp.InsertItem(i, csTemp);
		m_listSubCmp.InsertItem(i, csTemp);
		strncpy((char *)csTemp.GetBuffer(0), (const char*)lpTemp->byID, STREAM_ID_LEN);
		m_listMainCmp.SetItemText(i, 1, csTemp);
		m_listSubCmp.SetItemText(i, 1, csTemp);
		itoa(lpTemp->dwChannel, csTemp.GetBuffer(0), 10);
		m_listMainCmp.SetItemText(i, 2, csTemp);
		m_listSubCmp.SetItemText(i, 2, csTemp);	
		
		lpTemp++;
	}

	OnBtnGet();
}
void CDlgTransCompression::OnBtnCopyAll() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i = 0;
	char szLan[128] = {0};

	if (m_listMainCmp.GetItemCount() == 0)
	{
		return;
	}

	if (m_iCurSelItem == -1)
	{
		g_StringLanType(szLan, "请选择一个条目", "Please select one item");
		AfxMessageBox(szLan);
		return;
	}

	ListToControl(0);

	for (i = 0; i < m_listMainCmp.GetItemCount(); i++)
	{
		AddDataToList(0, i);		
	}

	ListToControl(1);

	for (i = 0; i < m_listSubCmp.GetItemCount(); i++)
	{
		AddDataToList(1, i);
	}

	if (m_comboCmpType.GetCurSel() == 0)
	{
		ListToControl(0);
	}
	else if (m_comboCmpType.GetCurSel() == 1)
	{
		ListToControl(1);
	}
}
