// DlgSceneChangeUpdate.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSceneChangeUpdate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSceneChangeUpdate dialog


CDlgSceneChangeUpdate::CDlgSceneChangeUpdate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSceneChangeUpdate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSceneChangeUpdate)
	m_csStreamID = _T("");
	m_nStreamIDNum = 0;
	//}}AFX_DATA_INIT

	memset(&m_StruSceneChangeUpdateParam, 0, sizeof(NET_DVR_SCENE_CHANGE_UPDATE_PARAM));
}


void CDlgSceneChangeUpdate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSceneChangeUpdate)
	DDX_Control(pDX, IDC_CMB_STREAM_ID, m_cmbStreamID);
	DDX_Text(pDX, IDC_EDIT_STREAM_ID, m_csStreamID);
	DDX_Text(pDX, IDC_EDIT_STREAM_ID_NUM, m_nStreamIDNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSceneChangeUpdate, CDialog)
	//{{AFX_MSG_MAP(CDlgSceneChangeUpdate)
	ON_BN_CLICKED(IDC_BTN_CTRL, OnBtnCtrl)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSceneChangeUpdate message handlers


BOOL CDlgSceneChangeUpdate::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	int i;
	char szLan[16] = {0};

	for (i = 0; i < 30; i++)
	{
		sprintf(szLan, "%d", i+1);
		m_cmbStreamID.AddString(szLan);
	}
	m_cmbStreamID.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgSceneChangeUpdate::OnBtnCtrl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	int i = 0;

	NET_DVR_SCENE_CHANGE_UPDATE_PARAM struSceneChangeUpdateParam = {0};

	m_StruSceneChangeUpdateParam.dwSize = sizeof(NET_DVR_SCENE_CHANGE_UPDATE_PARAM);
	m_StruSceneChangeUpdateParam.byIDCount = m_nStreamIDNum;

	OnBtnSave();

	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_SCENE_CHANGE_UPDATE, &m_StruSceneChangeUpdateParam, sizeof(NET_DVR_SCENE_CHANGE_UPDATE_PARAM)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_SCENE_CHANGE_UPDATE ");
		g_StringLanType(szLan, "²Ù×÷Ê§°Ü", "control failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_SCENE_CHANGE_UPDATE");
	}
}

void CDlgSceneChangeUpdate::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	int iSel = m_cmbStreamID.GetCurSel();

	strncpy((char*)m_StruSceneChangeUpdateParam.byStreamID[iSel], m_csStreamID.GetBuffer(0), STREAM_ID_LEN);
}
