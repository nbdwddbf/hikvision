// DlgITSImageMergeCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgITSImageMergeCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgITSImageMergeCfg dialog


CDlgITSImageMergeCfg::CDlgITSImageMergeCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgITSImageMergeCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgITSImageMergeCfg)
	m_bChkMergeEn = FALSE;
	m_dwCloseupIndex = 0;
	m_dwJpegQuality = 0;
	m_dwMaxMergeSize = 0;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_iDevIndex = -1;
	m_lChannel = -1;
	memset(&m_struImgMerge, 0, sizeof(m_struImgMerge));
}


void CDlgITSImageMergeCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgITSImageMergeCfg)
	DDX_Control(pDX, IDC_COMBO_THREE_MERGE_TYPE, m_comboThreeMergeType);
	DDX_Control(pDX, IDC_COMBO_SINGLE_MERGE_TYPE, m_comboSingleMergeType);
	DDX_Control(pDX, IDC_COMBO_DOUBLE_MERGE_TYPE, m_comboDoubleMergeType);
	DDX_Check(pDX, IDC_CHK_MERGE_ENABLE, m_bChkMergeEn);
	DDX_Text(pDX, IDC_EDIT_CLOSEUP_INDEX, m_dwCloseupIndex);
	DDX_Text(pDX, IDC_EDIT_JPEG_QUALITY, m_dwJpegQuality);
	DDX_Text(pDX, IDC_EDIT_MERGE_MAX_SIZE, m_dwMaxMergeSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgITSImageMergeCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgITSImageMergeCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgITSImageMergeCfg message handlers
BOOL CDlgITSImageMergeCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    int index = 0;
    char szLan[128] = {0};

	m_comboDoubleMergeType.ResetContent();
    g_StringLanType(szLan, "201", "201");
    m_comboDoubleMergeType.InsertString(index, szLan);
    m_comboDoubleMergeType.SetItemData(index, 201);
    index++;
   
    g_StringLanType(szLan, "202", "202");
    m_comboDoubleMergeType.InsertString(index, szLan);
    m_comboDoubleMergeType.SetItemData(index, 202);
    index++;

	index = 0;
	m_comboThreeMergeType.ResetContent();
    g_StringLanType(szLan, "301", "301");
    m_comboThreeMergeType.InsertString(index, szLan);
    m_comboThreeMergeType.SetItemData(index, 301);
    index++;
	
    g_StringLanType(szLan, "302", "302");
    m_comboThreeMergeType.InsertString(index, szLan);
    m_comboThreeMergeType.SetItemData(index, 302);
    index++;

	g_StringLanType(szLan, "303", "303");
    m_comboThreeMergeType.InsertString(index, szLan);
    m_comboThreeMergeType.SetItemData(index, 303);
    index++;

	g_StringLanType(szLan, "304", "304");
    m_comboThreeMergeType.InsertString(index, szLan);
    m_comboThreeMergeType.SetItemData(index, 304);
    index++;

	g_StringLanType(szLan, "305", "305");
    m_comboThreeMergeType.InsertString(index, szLan);
    m_comboThreeMergeType.SetItemData(index, 305);
    index++;

	g_StringLanType(szLan, "306", "306");
    m_comboThreeMergeType.InsertString(index, szLan);
    m_comboThreeMergeType.SetItemData(index, 306);
    index++;

	g_StringLanType(szLan, "307", "307");
    m_comboThreeMergeType.InsertString(index, szLan);
    m_comboThreeMergeType.SetItemData(index, 307);
    index++;

	g_StringLanType(szLan, "308", "308");
    m_comboThreeMergeType.InsertString(index, szLan);
    m_comboThreeMergeType.SetItemData(index, 308);
    index++;

	return TRUE;
}

void CDlgITSImageMergeCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	int i;
	DWORD dwReturn = 0;

	memset(&m_struImgMerge, 0, sizeof(m_struImgMerge));
	if (NET_DVR_GetDVRConfig(m_lServerID, NET_ITS_GET_IMGMERGE_CFG, m_lChannel, &m_struImgMerge, sizeof(m_struImgMerge), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_ITS_GET_IMGMERGE_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_ITS_GET_IMGMERGE_CFG");
	}
	m_bChkMergeEn = m_struImgMerge.byIsMerge;
	for (i = 0; i < m_comboDoubleMergeType.GetCount(); i++)
    {
        if (m_comboDoubleMergeType.GetItemData(i) == m_struImgMerge.dwTwoMergeType)
        {
            m_comboDoubleMergeType.SetCurSel(i);
            break;
        }
    }
	for (i = 0; i < m_comboThreeMergeType.GetCount(); i++)
    {
        if (m_comboThreeMergeType.GetItemData(i) == m_struImgMerge.dwThreeMergeType)
        {
            m_comboThreeMergeType.SetCurSel(i);
            break;
        }
    }

	m_dwJpegQuality = m_struImgMerge.dwJpegQuality;
	m_dwCloseupIndex = m_struImgMerge.dwCloseupIndex;
	m_dwMaxMergeSize = m_struImgMerge.dwMerageMaxSize;

	UpdateData(FALSE);
}

void CDlgITSImageMergeCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_struImgMerge.byIsMerge = m_bChkMergeEn;
	m_struImgMerge.dwTwoMergeType = m_comboDoubleMergeType.GetItemData(m_comboDoubleMergeType.GetCurSel());
	m_struImgMerge.dwThreeMergeType = m_comboThreeMergeType.GetItemData(m_comboThreeMergeType.GetCurSel());
	m_struImgMerge.dwJpegQuality = m_dwJpegQuality;
	m_struImgMerge.dwCloseupIndex = m_dwCloseupIndex;
	m_struImgMerge.dwMerageMaxSize = m_dwMaxMergeSize;
	if (NET_DVR_SetDVRConfig(m_lServerID, NET_ITS_SET_IMGMERGE_CFG, m_lChannel, &m_struImgMerge, sizeof(m_struImgMerge)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_ITS_SET_IMGMERGE_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_ITS_SET_IMGMERGE_CFG");
	}
}
