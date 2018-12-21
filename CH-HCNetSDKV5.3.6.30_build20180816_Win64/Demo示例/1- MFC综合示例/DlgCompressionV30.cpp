// DlgCompressionV30.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCompressionV30.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCompressionV30 dialog


CDlgCompressionV30::CDlgCompressionV30(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCompressionV30::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCompressionV30)
	m_bEventSvcChk = FALSE;
	m_bMainSvcChk = FALSE;
	m_bSubSvcChk = FALSE;
	m_iMainStreamSmooth = 0;
	m_iSubStreamSmooth = 0;
	m_iEventStreamSmooth = 0;
	//}}AFX_DATA_INIT
	memset(&m_struCompressionCfgV30, 0, sizeof(m_struCompressionCfgV30));
	m_struCompressionCfgV30.dwSize = sizeof(m_struCompressionCfgV30);
}


void CDlgCompressionV30::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCompressionV30)
	DDX_Control(pDX, IDC_COMBO_AUDIOBITARTE3, m_comboAudioBitRate3);
	DDX_Control(pDX, IDC_COMBO_AUDIOBITARTE2, m_comboAudioBitRate2);
	DDX_Control(pDX, IDC_COMBO_AUDIO_TYPE3, m_comboAudioType3);
	DDX_Control(pDX, IDC_COMBO_AUDIO_TYPE2, m_comboAudioType2);
	DDX_Control(pDX, IDC_COMBO_AUDIOBITARTE, m_comboAudioBitRate);
	DDX_Control(pDX, IDC_COMBO_AUDIO_TYPE, m_comboAudioType);
	DDX_Check(pDX, IDC_CHK_EVENT_SVC, m_bEventSvcChk);
	DDX_Check(pDX, IDC_CHK_MAIN_SVC, m_bMainSvcChk);
	DDX_Check(pDX, IDC_CHK_SUB_SVC, m_bSubSvcChk);
	DDX_Text(pDX, IDC_EDIT_MAIN_STREAMSMOOTH, m_iMainStreamSmooth);
	DDX_Text(pDX, IDC_EDIT_SUB_STREAMSMOOTH, m_iSubStreamSmooth);
	DDX_Text(pDX, IDC_EDIT_EVENT_STREAMSMOOTH, m_iEventStreamSmooth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCompressionV30, CDialog)
	//{{AFX_MSG_MAP(CDlgCompressionV30)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCompressionV30 message handlers

void CDlgCompressionV30::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	DWORD dwReturned = 0;
	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_COMPRESSCFG_V30, m_lChannel, &m_struCompressionCfgV30, sizeof(NET_DVR_COMPRESSIONCFG_V30), &dwReturned))
	{
	 	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_COMPRESSCFG_V30 chan[%d]", m_lChannel);
		g_StringLanType(szLan, "参数获取失败", "Get failed");
	 	AfxMessageBox(szLan);
	 	//return FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_COMPRESSCFG_V30 chan[%d]", m_lChannel);	
	}
	m_bMainSvcChk = m_struCompressionCfgV30.struNormHighRecordPara.byEnableSvc;
	m_bSubSvcChk = m_struCompressionCfgV30.struNetPara.byEnableSvc;
	m_bEventSvcChk = m_struCompressionCfgV30.struEventRecordPara.byEnableSvc;

	m_comboAudioBitRate.SetCurSel(m_struCompressionCfgV30.struNormHighRecordPara.byAudioBitRate);
	m_comboAudioBitRate2.SetCurSel(m_struCompressionCfgV30.struNetPara.byAudioBitRate);
	m_comboAudioBitRate3.SetCurSel(m_struCompressionCfgV30.struEventRecordPara.byAudioBitRate);

	m_comboAudioType.SetCurSel(m_struCompressionCfgV30.struNormHighRecordPara.byAudioEncType);
	m_comboAudioType2.SetCurSel(m_struCompressionCfgV30.struNetPara.byAudioEncType);
	m_comboAudioType3.SetCurSel(m_struCompressionCfgV30.struEventRecordPara.byAudioEncType);
	m_iMainStreamSmooth = m_struCompressionCfgV30.struNormHighRecordPara.byStreamSmooth;
	m_iSubStreamSmooth = m_struCompressionCfgV30.struNetPara.byStreamSmooth;
	m_iEventStreamSmooth = m_struCompressionCfgV30.struEventRecordPara.byStreamSmooth;
	UpdateData(FALSE);
}

void CDlgCompressionV30::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	m_struCompressionCfgV30.struNormHighRecordPara.byEnableSvc = m_bMainSvcChk;
	m_struCompressionCfgV30.struNetPara.byEnableSvc = m_bSubSvcChk;
	m_struCompressionCfgV30.struEventRecordPara.byEnableSvc = m_bEventSvcChk;

	m_struCompressionCfgV30.struNormHighRecordPara.byAudioBitRate = m_comboAudioBitRate.GetCurSel();
	m_struCompressionCfgV30.struNetPara.byAudioBitRate = m_comboAudioBitRate2.GetCurSel();
	m_struCompressionCfgV30.struEventRecordPara.byAudioBitRate = m_comboAudioBitRate3.GetCurSel();

	m_struCompressionCfgV30.struNormHighRecordPara.byAudioEncType = m_comboAudioType.GetCurSel();
	m_struCompressionCfgV30.struNetPara.byAudioEncType = m_comboAudioType2.GetCurSel();
	m_struCompressionCfgV30.struEventRecordPara.byAudioEncType = m_comboAudioType3.GetCurSel();
	m_struCompressionCfgV30.struNormHighRecordPara.byStreamSmooth = m_iMainStreamSmooth;
	m_struCompressionCfgV30.struNetPara.byStreamSmooth = m_iSubStreamSmooth;
	m_struCompressionCfgV30.struEventRecordPara.byStreamSmooth = m_iEventStreamSmooth;

	if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_COMPRESSCFG_V30, m_lChannel,&m_struCompressionCfgV30, sizeof(NET_DVR_COMPRESSIONCFG_V30)))
	{
	 	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_COMPRESSCFG_V30 chan[%d]", m_lChannel);
	 	g_StringLanType(szLan, "参数保存失败", "Save failed");
	 	AfxMessageBox(szLan);
	 	//return FALSE;
	}
	else
	{
	 	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_COMPRESSCFG_V30 chan[%d]", m_lChannel);	
	}	
}
