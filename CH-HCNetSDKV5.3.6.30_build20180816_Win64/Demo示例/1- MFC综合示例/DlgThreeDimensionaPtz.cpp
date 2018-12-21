// DlgThreeDimensionaPtz.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgThreeDimensionaPtz.h"
#include "HCNetSDK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgThreeDimensionaPtz dialog


CDlgThreeDimensionaPtz::CDlgThreeDimensionaPtz(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgThreeDimensionaPtz::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgThreeDimensionaPtz)
	m_byXSpeed = 0;
	m_byYSpeed = 0;
	//}}AFX_DATA_INIT
}


void CDlgThreeDimensionaPtz::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgThreeDimensionaPtz)
	DDX_Control(pDX, IDC_COMBO_Z_DIRECTION, m_cmbZDirection);
	DDX_Control(pDX, IDC_COMBO_T_DIRECTION, m_cmbTDirection);
	DDX_Control(pDX, IDC_COMBO_P_DIRECTION, m_cmbPDirection);
	DDX_Text(pDX, IDC_EDIT_X_Speed, m_byXSpeed);
	DDX_Text(pDX, IDC_EDIT_Y_Speed, m_byYSpeed);
    DDX_Text(pDX, IDC_EDIT_CHANNEL, m_lChannel);
	//}}AFX_DATA_MAP
}

BOOL CDlgThreeDimensionaPtz::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    char szLan[128] = {0};
    m_cmbPDirection.ResetContent();
    int nIndex = 0;
   
    g_StringLanType(szLan, "No Operation", "No Operation");
    m_cmbPDirection.InsertString(nIndex, szLan);
    m_cmbPDirection.SetItemData(nIndex, 1);
    nIndex++;
    g_StringLanType(szLan, "Left", "Left");
    m_cmbPDirection.InsertString(nIndex, szLan);
    m_cmbPDirection.SetItemData(nIndex, 2);
    nIndex++;
    g_StringLanType(szLan, "Right", "Right");
    m_cmbPDirection.InsertString(nIndex, szLan);
    m_cmbPDirection.SetItemData(nIndex, 3);
    nIndex++;
    m_cmbPDirection.SetCurSel(0);

    nIndex = 0;
    m_cmbTDirection.ResetContent();
    g_StringLanType(szLan, "No Operation", "No Operation");
    m_cmbTDirection.InsertString(nIndex, szLan);
    m_cmbTDirection.SetItemData(nIndex, 1);
    nIndex++;
    g_StringLanType(szLan, "Up", "Up");
    m_cmbTDirection.InsertString(nIndex, szLan);
    m_cmbTDirection.SetItemData(nIndex, 2);
    nIndex++;
    g_StringLanType(szLan, "Down", "Down");
    m_cmbTDirection.InsertString(nIndex, szLan);
    m_cmbTDirection.SetItemData(nIndex, 3);
    nIndex++;
    m_cmbTDirection.SetCurSel(0);

    nIndex = 0;
    m_cmbZDirection.ResetContent();
    g_StringLanType(szLan, "No Operation", "No Operation");
    m_cmbZDirection.InsertString(nIndex, szLan);
    m_cmbZDirection.SetItemData(nIndex, 1);
    nIndex++;
    g_StringLanType(szLan, "ZOOM+", "ZOOM+");
    m_cmbZDirection.InsertString(nIndex, szLan);
    m_cmbZDirection.SetItemData(nIndex, 2);
    nIndex++;
    g_StringLanType(szLan, "ZOOM-", "ZOOM-");
    m_cmbZDirection.InsertString(nIndex, szLan);
    m_cmbZDirection.SetItemData(nIndex, 3);
    nIndex++;
    m_cmbZDirection.SetCurSel(0);

    m_byYSpeed = 1;
    m_byXSpeed = 1;
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CDlgThreeDimensionaPtz, CDialog)
	//{{AFX_MSG_MAP(CDlgThreeDimensionaPtz)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgThreeDimensionaPtz message handlers

void CDlgThreeDimensionaPtz::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_PTZ_3D_SPEED_CONTROL strPTZ3DSpeed = {0};
    
    char szLan[128] = {0};
    strPTZ3DSpeed.dwSize = sizeof(NET_DVR_PTZ_3D_SPEED_CONTROL);
    strPTZ3DSpeed.dwChannel = m_lChannel;
    strPTZ3DSpeed.byPSpeed = m_byXSpeed;
    strPTZ3DSpeed.byTSpeed = m_byYSpeed;
    strPTZ3DSpeed.byPDirect = m_cmbPDirection.GetCurSel();
    strPTZ3DSpeed.byTDirect = m_cmbTDirection.GetCurSel();
    strPTZ3DSpeed.byZDirect = m_cmbZDirection.GetCurSel();
    
    if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_PTZ_3D_SPEED, &strPTZ3DSpeed, sizeof(NET_DVR_PTZ_3D_SPEED_CONTROL)))
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_PTZ_3D_SPEED FAIL");
	}
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_PTZ_3D_SPEED SUCC");
	}
    return;
}
