// DlgPositionTrackCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPositionTrackCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPositionTrackCfg dialog


CDlgPositionTrackCfg::CDlgPositionTrackCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPositionTrackCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPositionTrackCfg)
	m_iDwell = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_lChannel = -1;
    m_iDevIndex = -1;
    memset(&m_struPositionTrack, 0, sizeof(m_struPositionTrack));
}


void CDlgPositionTrackCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPositionTrackCfg)
	DDX_Control(pDX, IDC_COMBO_INDEX, m_comboIndex);
	DDX_Control(pDX, IDC_COMBO_POSITION_ID, m_comboPositionID);
	DDX_Control(pDX, IDC_COMBO_POSITION_NUM, m_comboPositionNum);
	DDX_Text(pDX, IDC_EDIT_DWELL, m_iDwell);
	 DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comboChan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPositionTrackCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgPositionTrackCfg)
	ON_CBN_SELCHANGE(IDC_COMBO_POSITION_NUM, OnSelchangeComboPositionNum)
	ON_BN_CLICKED(IDC_BTN_SET_POSITION_TRACK, OnBtnSetPositionTrack)
	ON_BN_CLICKED(IDC_BTN_CONFIRM, OnBtnConfirm)
	ON_CBN_SELCHANGE(IDC_COMBO_INDEX, OnSelchangeComboIndex)
	ON_BN_CLICKED(IDC_BTN_GET_POSITION_TRACK, OnBtnGetPositionTrack)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPositionTrackCfg message handlers

void CDlgPositionTrackCfg::OnSelchangeComboPositionNum() 
{
    m_struPositionTrack.byNum = m_comboPositionNum.GetCurSel();
	InitComboIndex();
    if (m_struPositionTrack.byNum > 0)
    {
        m_comboIndex.SetCurSel(0);
        OnSelchangeComboIndex();
    }
}

void CDlgPositionTrackCfg::OnBtnSetPositionTrack() 
{
    UpdateData(TRUE);
    m_struPositionTrack.byNum = m_comboPositionNum.GetCurSel();
    m_struPositionTrack.struPositionIndex[m_comboIndex.GetCurSel()].byIndex = m_comboPositionID.GetCurSel()+1;
    m_struPositionTrack.struPositionIndex[m_comboIndex.GetCurSel()].wDwell = m_iDwell;
	m_lChannel = m_comboChan.GetItemData(m_comboChan.GetCurSel());

    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_POSITION_TRACK, m_lChannel, &m_struPositionTrack, sizeof(m_struPositionTrack)))
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_POSITION_TRACK Channel[%d]",m_lChannel);
		AfxMessageBox("fail to set position track");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_POSITION_TRACK Channel[%d]",m_lChannel);
		AfxMessageBox("Success to set position track");
	}
}

BOOL CDlgPositionTrackCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	g_AddChanInfoToComBox(m_comboChan, m_iDevIndex);
	OnBtnGetPositionTrack();
    SetPositionTrackWnd();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgPositionTrackCfg::SetPositionTrackWnd()
{
    m_comboPositionNum.SetCurSel(m_struPositionTrack.byNum);
    OnSelchangeComboPositionNum();
    return TRUE;
}

void CDlgPositionTrackCfg::InitComboIndex()
{
    m_comboIndex.ResetContent();
    char szLan[128] = {0};
    for (int i = 0; i < m_struPositionTrack.byNum; i++)
    {
        memset(szLan, 0, sizeof(szLan));
        sprintf(szLan, "%d", i+1);
        m_comboIndex.AddString(szLan);
    }
}



void CDlgPositionTrackCfg::OnBtnConfirm() 
{
    UpdateData(TRUE);
    m_struPositionTrack.byNum = m_comboPositionNum.GetCurSel();
    m_struPositionTrack.struPositionIndex[m_comboIndex.GetCurSel()].byIndex = m_comboPositionID.GetCurSel()+1;
    m_struPositionTrack.struPositionIndex[m_comboIndex.GetCurSel()].wDwell = m_iDwell;
}

void CDlgPositionTrackCfg::OnSelchangeComboIndex() 
{
    m_comboPositionID.SetCurSel(m_struPositionTrack.struPositionIndex[m_comboIndex.GetCurSel()].byIndex - 1);
    m_iDwell = m_struPositionTrack.struPositionIndex[m_comboIndex.GetCurSel()].wDwell;
    UpdateData(FALSE);
}


void CDlgPositionTrackCfg::OnBtnGetPositionTrack() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	DWORD dwReturn;
	m_lChannel = m_comboChan.GetItemData(m_comboChan.GetCurSel());
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_POSITION_TRACK, m_lChannel, &m_struPositionTrack, sizeof(m_struPositionTrack), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_POSITION_TRACK Channel[%]", m_lChannel);
		AfxMessageBox("Fail to get position track");
		return ;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_POSITION_TRACK Channel[%]", m_lChannel);
	}
}
