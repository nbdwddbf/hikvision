// DlgProductCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgProductCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProductCfg dialog


CDlgProductCfg::CDlgProductCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProductCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgProductCfg)
	//}}AFX_DATA_INIT
	m_lUserID = -1;
	m_lChannel = -1;
	m_iDevIndex = -1;
}


void CDlgProductCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProductCfg)
	DDX_Control(pDX, IDC_TAB_PRODUCT_TYPE, m_tabProductType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProductCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgProductCfg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PRODUCT_TYPE, OnSelchangeTabProductType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProductCfg message handlers
BOOL CDlgProductCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
    
	char szLan[100] = "\0";
	g_StringLanType(szLan,"智能产品","VCA");
	m_tabProductType.InsertItem(0,szLan);

	g_StringLanType(szLan,"网络报警主机","Alarm Host");
	m_tabProductType.InsertItem(1,szLan);
    g_StringLanType(szLan,"DVR/NVR/DVS","DVR/NVR/DVS");
    m_tabProductType.InsertItem(2,szLan);
    g_StringLanType(szLan,"CVR","CVR");
    m_tabProductType.InsertItem(3,szLan);
    g_StringLanType(szLan,"解码显示产品","Decode CFG");
	m_tabProductType.InsertItem(4,szLan);

	g_StringLanType(szLan,"前端设备","IPC/IPD CFG");
	m_tabProductType.InsertItem(5,szLan);
	
    g_StringLanType(szLan,"交通产品","ITC CFG");
	m_tabProductType.InsertItem(6,szLan);
 	m_subDlgVca.m_lUserID = m_lUserID;
	m_subDlgVca.m_lChannel = m_lChannel;
	m_subDlgVca.m_iDevIndex = m_iDevIndex;

    g_StringLanType(szLan, "门禁主机", "ACS");
    m_tabProductType.InsertItem(7, szLan);    

	g_StringLanType(szLan, "可视对讲", "VIS");
    m_tabProductType.InsertItem(8, szLan);

    g_StringLanType(szLan, "动环", "DH");
    m_tabProductType.InsertItem(9, szLan);

	m_subDlgVca.Create(CDlgProductVcaCfg::IDD,this);
	m_subdlgAlarmHost.Create(CDlgProductAlarmHostCfg::IDD,this);
    m_subDlgMatDecCfg.Create(CMatDecCFG::IDD, this);

	m_subDlgIpcCfg.m_lUserID = m_lUserID;
	m_subDlgIpcCfg.m_lChannel = m_lChannel;
	m_subDlgIpcCfg.m_lDeviceIndex = m_iDevIndex;

	m_subDlgIpcCfg.Create(CDlgSubIPCCfg::IDD,this);
	m_subDlgItsCfg.Create(CSubDlgITSCfg::IDD,this);

    m_subDVRNVRCfg.m_lUserID = m_lUserID;
    m_subDVRNVRCfg.m_lChanNo = m_lChannel;
    m_subDVRNVRCfg.m_iDevIndex = m_iDevIndex;
    m_subDVRNVRCfg.Create(CSubDlgDVRNVRCfg::IDD,this);
    
    m_subCVRCfg.m_lUserID = m_lUserID;
    m_subCVRCfg.m_lChanNo = m_lChannel;
    m_subCVRCfg.m_iDevIndex = m_iDevIndex;
    m_subCVRCfg.Create(CSubDlgCVRCfg::IDD,this);
   
    m_subDlgAcsCfg.m_lUserID = m_lUserID;
    m_subDlgAcsCfg.m_iDeviceIndex = m_iDevIndex;
    m_subDlgAcsCfg.Create(CDlgProductAcs::IDD,this);

    m_subDlgVISCfg.m_lServerID = m_lUserID;
    m_subDlgVISCfg.m_iDevIndex = m_iDevIndex;
    m_subDlgVISCfg.Create(CDlgVideoIntercomCfg::IDD,this);

    m_subDlgDH.Create(CDlgProductDH::IDD, this);

    CRect rcClient;
	GetClientRect(&rcClient);
	m_tabProductType.MoveWindow(rcClient);

	CRect rcChildRgn = rcClient;
	rcChildRgn.DeflateRect(0,30,0,0);

	m_subDlgVca.MoveWindow(rcChildRgn);
	m_subdlgAlarmHost.MoveWindow(rcChildRgn);
    m_subDVRNVRCfg.MoveWindow(rcChildRgn);
    m_subCVRCfg.MoveWindow(rcChildRgn);
    m_subDlgMatDecCfg.MoveWindow(rcChildRgn); 
	
	m_subDlgIpcCfg.MoveWindow(rcChildRgn);
    m_subDlgItsCfg.MoveWindow(rcChildRgn);
    m_subDlgAcsCfg.MoveWindow(rcChildRgn); 
	m_subDlgVISCfg.MoveWindow(rcChildRgn);
    m_subDlgDH.MoveWindow(rcChildRgn);
	m_tabProductType.SetCurSel(0);
	ShowChildWnd(SUB_WND_VCA);

	return TRUE;
}


void CDlgProductCfg::ShowChildWnd(int nChildWnd)
{
	m_subDlgVca.ShowWindow(nChildWnd == SUB_WND_VCA);
	m_subdlgAlarmHost.ShowWindow(nChildWnd == SUB_WND_ALARMHOST);
    m_subDVRNVRCfg.ShowWindow(nChildWnd == SUB_WND_NVR);
    m_subCVRCfg.ShowWindow(nChildWnd == SUB_WND_CVR);
    m_subDlgMatDecCfg.ShowWindow(nChildWnd == SUB_WND_MATDEC);

	m_subDlgIpcCfg.ShowWindow(nChildWnd == SUB_WND_IPCD);
    m_subDlgItsCfg.ShowWindow(nChildWnd == SUB_WND_ITS);
    m_subDlgAcsCfg.ShowWindow(nChildWnd == SUB_WND_ACS);
	m_subDlgVISCfg.ShowWindow(nChildWnd == SUB_WND_VIS);
    m_subDlgDH.ShowWindow(nChildWnd == SUB_WND_DH);
}


void CDlgProductCfg::OnSelchangeTabProductType(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int nCurSel = m_tabProductType.GetCurSel();
	if (nCurSel == -1)
	{
		return;
	}
    switch (nCurSel)
    {
    case SUB_WND_VCA:
        break; 
    case SUB_WND_ALARMHOST:
        m_subdlgAlarmHost.UpdatePapam(); 
        break; 
    case SUB_WND_NVR:
        break;
    case SUB_WND_MATDEC:
        m_subDlgMatDecCfg.CurCfgUpdate(); 
        break; 
	case SUB_WND_IPCD:
        m_subDlgIpcCfg.CurCfgUpdate(); 
        break; 
    case SUB_WND_ITS:
        m_subDlgItsCfg.CurCfgUpdate(); 
        break; 
    case SUB_WND_ACS:
        m_subDlgAcsCfg.CurCfgUpadate();
        break;
	case SUB_WND_VIS:
		m_subDlgVISCfg.CurCfgUpadate();
		break;
    case SUB_WND_DH:
        m_subDlgDH.UpdataParam();
    }
	ShowChildWnd(nCurSel);
	
	*pResult = 0;
}

void CDlgProductCfg::UpdateWindowParam(LONG lDevIndex,LONG lChanIndex)
{   
	if (lDevIndex < 0)
	{
		return;
	}
	m_lUserID = g_struDeviceInfo[lDevIndex].lLoginID;
    
	if (lChanIndex >= 0)
	{
		m_lChannel = g_struDeviceInfo[lDevIndex].pStruChanInfo[lChanIndex].iChannelNO;
	}
	else
	{
		m_lChannel = -1;
	}
	m_iDevIndex = lDevIndex;

	m_subDlgVca.UpdateWindowParam(m_iDevIndex,m_lChannel);
    m_subdlgAlarmHost.UpdatePapam(); 
    m_subDlgMatDecCfg.CurCfgUpdate();
	m_subDlgIpcCfg.CurCfgUpdate(); 
	m_subDlgItsCfg.CurCfgUpdate(); 
    m_subDVRNVRCfg.CurCfgUpdate();
    m_subCVRCfg.CurCfgUpdate();
    m_subDlgAcsCfg.CurCfgUpadate();
	m_subDlgVISCfg.CurCfgUpadate();
    m_subDlgDH.UpdataParam();
}
