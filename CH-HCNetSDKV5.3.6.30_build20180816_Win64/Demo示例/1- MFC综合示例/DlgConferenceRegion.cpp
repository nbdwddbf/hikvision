// DlgConferenceRegion.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgConferenceRegion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgConferenceRegion dialog


CDlgConferenceRegion::CDlgConferenceRegion(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConferenceRegion::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgConferenceRegion)
	m_dwOuputHeight = 0;
	m_dwOutputWidth = 0;
	m_dwX1 = 0;
	m_dwX2 = 0;
	m_dwX3 = 0;
	m_dwX4 = 0;
	m_dwY1 = 0;
	m_dwY2 = 0;
	m_dwY3 = 0;
	m_dwY4 = 0;
	m_BEnable = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgConferenceRegion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConferenceRegion)
	DDX_Text(pDX, IDC_EDT_MCU_REGION_OUTPUTHEIGHT, m_dwOuputHeight);
	DDX_Text(pDX, IDC_EDT_MCU_REGION_OUTPUTWIDTH, m_dwOutputWidth);
	DDX_Text(pDX, IDC_EDT_MCU_REGION_X1, m_dwX1);
	DDX_Text(pDX, IDC_EDT_MCU_REGION_X2, m_dwX2);
	DDX_Text(pDX, IDC_EDT_MCU_REGION_X3, m_dwX3);
	DDX_Text(pDX, IDC_EDT_MCU_REGION_X4, m_dwX4);
	DDX_Text(pDX, IDC_EDT_MCU_REGION_Y1, m_dwY1);
	DDX_Text(pDX, IDC_EDT_MCU_REGION_Y2, m_dwY2);
	DDX_Text(pDX, IDC_EDT_MCU_REGION_Y3, m_dwY3);
	DDX_Text(pDX, IDC_EDT_MCU_REGION_Y4, m_dwY4);
	DDX_Check(pDX, IDC_CHK_ENABLE_CONFERENCE, m_BEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgConferenceRegion, CDialog)
	//{{AFX_MSG_MAP(CDlgConferenceRegion)
	ON_BN_CLICKED(IDC_BUT_MCU_GET, OnButMCUGet)
	ON_BN_CLICKED(IDC_BUT_MCU_SET, OnButMCUSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgConferenceRegion message handlers

void CDlgConferenceRegion::OnButMCUGet() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_CONFERENCE_REGION struconfereceRgion = {0}; 
	struconfereceRgion.dwSize = sizeof(struconfereceRgion);
	NET_DVR_STD_CONFIG struConfig = {0}; 
	struConfig.lpOutBuffer = &struconfereceRgion; 
	struConfig.dwOutSize = sizeof(struconfereceRgion);
	if ( ! NET_DVR_GetSTDConfig(m_lUserID,NET_DVR_GET_CONFERENCE_REGION, &struConfig) )
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_CONFERENCE_REGION");
		return ; 
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CONFERENCE_REGION");
	
	m_BEnable = struconfereceRgion.byEnabled; 
	m_dwX1 = struconfereceRgion.struRegion[0].dwX;
	m_dwY1 = struconfereceRgion.struRegion[0].dwY; 
	m_dwX2 = struconfereceRgion.struRegion[1].dwX;
	m_dwY2 = struconfereceRgion.struRegion[1].dwY; 
	m_dwX3 = struconfereceRgion.struRegion[2].dwX;
	m_dwY3 = struconfereceRgion.struRegion[2].dwY; 
	m_dwX4 = struconfereceRgion.struRegion[3].dwX;
	m_dwY4 = struconfereceRgion.struRegion[3].dwY; 
	m_dwOuputHeight = struconfereceRgion.dwOutputHeight; 
	m_dwOutputWidth = struconfereceRgion.dwOutputWidth; 
	UpdateData(FALSE); 
}

void CDlgConferenceRegion::OnButMCUSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	NET_DVR_CONFERENCE_REGION struconfereceRgion = {0}; 
	struconfereceRgion.dwSize = sizeof(struconfereceRgion);
	struconfereceRgion.byEnabled = 	m_BEnable ; 
	struconfereceRgion.struRegion[0].dwX = 	m_dwX1 ;
	struconfereceRgion.struRegion[0].dwY = 	m_dwY1 ; 
	struconfereceRgion.struRegion[1].dwX = 	m_dwX2 ;
	struconfereceRgion.struRegion[1].dwY = 	m_dwY2 ; 
	struconfereceRgion.struRegion[2].dwX = 	m_dwX3 ;
	struconfereceRgion.struRegion[2].dwY = 	m_dwY3 ; 
	struconfereceRgion.struRegion[3].dwX = 	m_dwX4 ;
	struconfereceRgion.struRegion[3].dwY = 	m_dwY4 ; 
	struconfereceRgion.dwOutputHeight = m_dwOuputHeight ; 
	struconfereceRgion.dwOutputWidth = 	m_dwOutputWidth ; 
	NET_DVR_STD_CONFIG struConfig = {0}; 
	struConfig.lpInBuffer = &struconfereceRgion; 
	struConfig.dwInSize = sizeof(struconfereceRgion);
	if ( ! NET_DVR_SetSTDConfig(m_lUserID,NET_DVR_SET_CONFERENCE_REGION, &struConfig))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_CONFERENCE_REGION");
		return ; 
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_CONFERENCE_REGION");
}

BOOL CDlgConferenceRegion::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex(); 
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID; 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
