// DlgCameraSetupCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCameraSetupCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCameraSetupCfg dialog


CDlgCameraSetupCfg::CDlgCameraSetupCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCameraSetupCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCameraSetupCfg)
	m_byDetailLens = 0;
	m_dwHorizontalDistance = 0;
	m_dwSetupHeight = 0;
	//}}AFX_DATA_INIT
	m_iDeviceIndex = -1;
	m_lChannel = -1;
	m_lLoginID = -1;
}


void CDlgCameraSetupCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCameraSetupCfg)
	DDX_Control(pDX, IDC_COMBO_HEIGHT_UNIT, m_comHeightUnit);
	DDX_Control(pDX, IDC_COMBO_CAMERA_ANGLE, m_comCameraAngle);
	DDX_Text(pDX, IDC_EDIT_DETAIL_LEN, m_byDetailLens);
	DDX_Text(pDX, IDC_EDIT_DISTANCE, m_dwHorizontalDistance);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_dwSetupHeight);
    DDX_Control(pDX, IDC_CMB_ERECT_MOTHOD, m_ErectMethod);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCameraSetupCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgCameraSetupCfg)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCameraSetupCfg message handlers

BOOL CDlgCameraSetupCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCameraSetupCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	NET_DVR_CAMERA_SETUPCFG struCameraSetup = {0};
	struCameraSetup.dwSize = sizeof(struCameraSetup);
	struCameraSetup.wSetupHeight = m_dwSetupHeight;
	struCameraSetup.bySetupHeightUnit = m_comHeightUnit.GetCurSel();
	struCameraSetup.byCameraViewAngle = m_comCameraAngle.GetCurSel();
	struCameraSetup.dwHorizontalDistance = m_dwHorizontalDistance;
	struCameraSetup.byDetailLensType = m_byDetailLens;
    struCameraSetup.byErectMethod = m_ErectMethod.GetCurSel();
	if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_CAMERA_SETUPCFG, m_lChannel, &struCameraSetup, sizeof(struCameraSetup)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_CAMERA_SETUPCFG");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_CAMERA_SETUPCFG");
	}
	
}

void CDlgCameraSetupCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_CAMERA_SETUPCFG struCameraSetup = {0};
	DWORD dwRet = 0;
	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_CAMERA_SETUPCFG, m_lChannel, &struCameraSetup, sizeof(struCameraSetup), &dwRet))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_CAMERA_SETUPCFG");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CAMERA_SETUPCFG");
	}
	
	m_dwSetupHeight = struCameraSetup.wSetupHeight;
	m_comHeightUnit.SetCurSel(struCameraSetup.bySetupHeightUnit);
	m_comCameraAngle.SetCurSel(struCameraSetup.byCameraViewAngle);
	m_dwHorizontalDistance = struCameraSetup.dwHorizontalDistance;
	m_byDetailLens = struCameraSetup.byDetailLensType;
    m_ErectMethod.SetCurSel(struCameraSetup.byErectMethod);
	UpdateData(FALSE);
}
