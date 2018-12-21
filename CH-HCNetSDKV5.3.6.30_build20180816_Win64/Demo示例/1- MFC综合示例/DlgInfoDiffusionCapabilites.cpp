// DlgInfoDiffusionCapabilites.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionCapabilites.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionCapabilites dialog


CDlgInfoDiffusionCapabilites::CDlgInfoDiffusionCapabilites(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionCapabilites::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionCapabilites)
	m_szCapabilites = _T("");
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_szCommand = _T("");
	m_pOutputXmlBuffer = new char[MAX_LEN_XML];
	memset(m_pOutputXmlBuffer, 0, sizeof(char)*MAX_LEN_XML);
}


void CDlgInfoDiffusionCapabilites::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfoDiffusionCapabilites)
	DDX_Control(pDX, IDC_COMBO_CAPABILITES_TYPE, m_cmbCapablitesType);
	DDX_Text(pDX, IDC_EDIT_CAPABILITES, m_szCapabilites);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionCapabilites, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionCapabilites)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_GET_CAPABILITES, OnBtnGetCapabilites)
	ON_CBN_SELCHANGE(IDC_COMBO_CAPABILITES_TYPE, OnSelchangeComboCapabilitesType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionCapabilites message handlers

void CDlgInfoDiffusionCapabilites::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgInfoDiffusionCapabilites::OnBtnGetCapabilites() 
{
	// TODO: Add your control notification handler code here
	if (m_cmbCapablitesType.GetCurSel() == CB_ERR)
	{
		return;
	}

	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = m_szCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = m_szCommand.GetLength();
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	memset(m_pOutputXmlBuffer, 0, MAX_LEN_XML);
	struOutputParam.lpOutBuffer = m_pOutputXmlBuffer;
	struOutputParam.dwOutBufferSize = MAX_LEN_XML;
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");

	m_szCapabilites = m_pOutputXmlBuffer;

	UpdateData(FALSE);
}

void CDlgInfoDiffusionCapabilites::OnSelchangeComboCapabilitesType() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbCapablitesType.GetCurSel();
	switch (nSel)
	{
	case 0:
		m_szCommand = _T("GET /ISAPI/Publish/material/1/capabilities\r\n");
		break;
	case 1:
		m_szCommand = _T("GET /ISAPI/Publish/ProgramMgr/program/1/capabilities\r\n");
		break;
	case 2:
		m_szCommand = _T("GET /ISAPI/Publish/ProgramMgr/program/1/page/1/capabilities\r\n");
		break;
	case 3:
		m_szCommand = _T("GET /ISAPI/Publish/ScheduleMgr/playSchedule/1/capabilities\r\n");
		break;
	case 4:
		m_szCommand = _T("GET /ISAPI/Publish/TerminalMgr/terminals/1/capabilities\r\n");
		break;
	case 5:
		m_szCommand = _T("GET /ISAPI/Publish/TerminalMgr/terminals/config/1/capabilities\r\n");
		break;
	case 6:
		m_szCommand = _T("GET /ISAPI/Publish/TerminalMgr/terminals/control/capabilities\r\n");
		break;
	case 7:
		m_szCommand = _T("GET /ISAPI/Publish/TerminalMgr/terminalGroups/1/capabilities\r\n");
		break;
	case 8:
		m_szCommand = _T("GET /ISAPI/Publish/MaterialMgr/materialSearch/profile\r\n");
		break;
	case 9:
		m_szCommand = _T("GET /ISAPI/Publish/ProgramMgr/programSearch/profile\r\n");
		break;
	case 10:
		m_szCommand = _T("GET /ISAPI/Publish/ScheduleMgr/scheduleSearch/profile\r\n");
		break;
	case 11:
		m_szCommand = _T("GET /ISAPI/Publish/capabilities\r\n");
        break;
    case 12:
        m_szCommand = _T("GET /ISAPI/Publish/TerminalMgr/switchPlanCfg/capabilities\r\n");
        break;
    case 13:
        m_szCommand = _T("GET /ISAPI/Publish/TerminalMgr/volumePlanCfg/capabilities\r\n");
        break;
    case 14:
        m_szCommand = _T("GET /ISAPI/Publish/ScheduleMgr/release/capabilities\r\n");
        break;
    case 15:
        m_szCommand = _T("GET /ISAPI/Publish/ProgramMgr/program/page/windows/dynamicCap\r\n");
        break;
    case 16:
        m_szCommand = _T("GET /ISAPI/Publish/MaterialMgr/materialBatchInfo/capabilities\r\n");
        break;
    case 17:
        m_szCommand = _T("GET /ISAPI/Publish/ProgramMgr/programBatchInfo/capabilities\r\n");
        break;
    case 18:
        m_szCommand = _T("GET /ISAPI/Publish/TerminalMgr/inputPlanCfg/capabilities\r\n");
        break;
    case 19:
        m_szCommand = _T("GET /ISAPI/Publish/ProgramMgr/program/dynamicCap\r\n");
        break;
    case 20:
        m_szCommand = _T("GET /ISAPI/Publish/orgMgr/organization/1/capabilities\r\n");
        break;
    case 21:
        m_szCommand = _T("GET /ISAPI/Publish/TerminalMgr/terminalSearch/profile\r\n");
        break;
    case 22:
        m_szCommand = _T("GET /ISAPI/Publish/userRole/capabilities\r\n");
        break;
    case 23:
        m_szCommand = _T("GET /ISAPI/Publish/ProgramMgr/program/page/windows/touch/capabilities\r\n");
        break;
    case 24:
        m_szCommand = _T("GET /ISAPI/Publish/ScheduleMgr/playScheduleBatchInfo\r\n");
        break;
	default:
		m_szCommand = _T("");
	}
}


BOOL CDlgInfoDiffusionCapabilites::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_cmbCapablitesType.InsertString(18, ("定时切换HDMI和信息发布能力"));
    m_cmbCapablitesType.InsertString(19, ("节目动态能力"));
    m_cmbCapablitesType.InsertString(20, ("组织参数能力"));
    m_cmbCapablitesType.InsertString(21, ("终端查找能力"));
    m_cmbCapablitesType.InsertString(22, ("用户角色"));
    m_cmbCapablitesType.InsertString(23, ("触摸窗口素材能力"));
    m_cmbCapablitesType.InsertString(24, ("日程批量配置能力"));

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}
