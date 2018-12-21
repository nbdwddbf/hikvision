// DlgMCUAbilityDetect.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMCUAbilityDetect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define XML_ABILITY_IN_LEN	1024
#define XML_ABILITY_OUT_LEN	3*1024*1024

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUAbilityDetect dialog


CDlgMCUAbilityDetect::CDlgMCUAbilityDetect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMCUAbilityDetect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMCUAbilityDetect)
		// NOTE: the ClassWizard will add member initialization here

	m_dwReturnValue = 0;
	m_dwLastError   = 0;

	m_pOutBuf = NULL;
		//}}AFX_DATA_INIT
}

void CDlgMCUAbilityDetect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMCUAbilityDetect)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_COM_ABILITY_TYPE, m_comAbilityType);
	DDX_Control(pDX, IDC_EDT_RETURN_VALUE, m_edtResult);

	DDX_Text(pDX, IDC_EDT_RETURN, m_strResult);
	DDX_Text(pDX, IDC_EDT_RETURN_VALUE, m_dwReturnValue);
	DDX_Text(pDX, IDC_EDT_ERROR_CODE,   m_dwLastError);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMCUAbilityDetect, CDialog)
	//{{AFX_MSG_MAP(CDlgMCUAbilityDetect)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUAbilityDetect message handlers

BOOL CDlgMCUAbilityDetect::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pOutBuf = new char[XML_ABILITY_OUT_LEN];
	memset(m_pOutBuf, 0, XML_ABILITY_OUT_LEN);

	m_comAbilityType.InsertString(0, _T("会议相关能力"));
    m_comAbilityType.InsertString(1, _T("会议查找能力"));
	m_comAbilityType.InsertString(2, _T("会议控制能力"));
	m_comAbilityType.InsertString(3, _T("MCU终端控制能力"));
	m_comAbilityType.InsertString(4, _T("终端分组能力"));
	m_comAbilityType.InsertString(5, _T("终端管理能力"));
    m_comAbilityType.InsertString(6, _T("终端注册GK能力"));
    m_comAbilityType.InsertString(7, _T("MCU注册GK能力"));
    m_comAbilityType.InsertString(8, _T("MCU开启GK服务能力"));
	m_comAbilityType.SetCurSel(0);

	UpdateData(FALSE);
	
	return TRUE;
}


DWORD CDlgMCUAbilityDetect::GetAbliltyType()
{
	DWORD dwAbilityType  = 0;
	BYTE  byAbilityIndex = m_comAbilityType.GetCurSel();
	
	switch (byAbilityIndex)
	{
	case 0:
		dwAbilityType = NET_DVR_GET_MCU_CONFERENCE_CAP;
		break;
	case 1:
		dwAbilityType = NET_DVR_GET_MCU_CONFERENCESEARCH_CAP;
		break;
	case 2:
		dwAbilityType = NET_DVR_GET_MCU_CONFERENCECONTROL_CAP;
		break;
	case 3:
		dwAbilityType = NET_DVR_GET_MCU_TERMINALCONTROL_CAP;
		break;
	case 4:
		dwAbilityType = NET_DVR_GET_MCU_TERIMINALGROUP_CAP;
		break;
	case 5:
		dwAbilityType = NET_DVR_GET_MCU_TERMINAL_CAP;
		break;
    case 6:
        dwAbilityType = NET_DVR_GET_TERMINAL_GK_CFG_CAP;
        break;
    case 7:
        dwAbilityType = NET_DVR_GET_MCU_GK_CFG_CAP;
        break;
    case 8:
        dwAbilityType = NET_DVR_GET_MCU_GK_SERVER_CAP;
        break;
	default:
		dwAbilityType = -1;
		break;
	}

	return dwAbilityType;
	
}


void CDlgMCUAbilityDetect::OnBtnGet() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	m_dwAbilityType = GetAbliltyType();

	//m_dwAbilityType = NET_DVR_GET_TERMINAL_CTRL_CAP;
	//NET_DVR_GET_TERMINAL_INPUT_CFG_CAP;
	//NET_DVR_GET_CONFERENCE_REGION_CAP;

	if (m_dwAbilityType == -1)
	{
		MessageBox(_T("请选择正确的能力类型!"));
	}


    int nID = 0;
    NET_DVR_STD_ABILITY struSTDAbility = {0};

    struSTDAbility.lpCondBuffer = NULL;
    struSTDAbility.dwCondSize = 0;   

    struSTDAbility.lpOutBuffer    = m_pOutBuf;
    struSTDAbility.dwOutSize      = XML_ABILITY_OUT_LEN;
    struSTDAbility.lpStatusBuffer = m_pOutBuf;
    struSTDAbility.dwStatusSize   = XML_ABILITY_OUT_LEN;

    m_dwReturnValue = NET_DVR_GetSTDAbility(m_lUserID, m_dwAbilityType, &struSTDAbility);

	m_dwLastError = NET_DVR_GetLastError();

    CXmlBase xmlBase;
    xmlBase.Parse(m_pOutBuf);
    xmlBase.SetRoot();
    m_strResult = xmlBase.GetChildren().c_str();
    m_strResult.Replace("\n", "\r\n"); 
  	
	UpdateData(FALSE);
}

void CDlgMCUAbilityDetect::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if (m_pOutBuf != NULL)
	{
		delete []m_pOutBuf;
		m_pOutBuf = NULL;
	}
}
