// DlgPosFilterRule.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPosFilterRule.h"
#include "DlgPosFilterEffect.h"
#include <fstream>
#include <iostream>
#include "DlgPOSRegion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

RECT g_rectSetArea;
void CALLBACK SetOSDRegionCallBack(LONG nPort,HDC hDc,DWORD nUser)
{
 	::DrawEdge(hDc,&g_rectSetArea,BDR_SUNKENOUTER,BF_RECT);
	SetBkMode(hDc,TRANSPARENT);
}

void CALLBACK  GetOSDCallBack(LONG nPort,HDC hDc,DWORD nUser)
{
	CRect rect;
	CPoint point;
	rect.left = g_rectSetArea.left;
	rect.top = g_rectSetArea.top;
	rect.right = g_rectSetArea.right;
	rect.bottom = g_rectSetArea.bottom;
	::DrawEdge(hDc,&rect,BDR_SUNKENOUTER,BF_RECT);
	SetBkMode(hDc,TRANSPARENT);
}

/////////////////////////////////////////////////////////////////////////////
// CDlgPosFilterRule dialog


CDlgPosFilterRule::CDlgPosFilterRule(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPosFilterRule::IDD, pParent)
    , m_szEmployeeNo(_T(""))
    , m_szTerminalNo(_T(""))
    , m_szShiftNo(_T(""))
{
	//{{AFX_DATA_INIT(CDlgPosFilterRule)
	m_bEnable = TRUE;
	m_bGenericCaseSensitive = FALSE;
    m_bGenericCaseStartFlag = FALSE;
    m_bGenericCaseEndFlag = FALSE;
	m_bGenericEndHex = FALSE;
	m_bGenericNewLineHex = FALSE;
	m_bGenericStartAnyChar = FALSE;
	m_bGenericStartHex = FALSE;
	m_bOverlayOsd = FALSE;
	m_dwActionDelayTime = 0;
	m_dwAveDisAppearTime = 0;
	m_csGenericEndData = _T("");
	m_dwGenericEndLine = 0;
	m_csGenericNewlineData = _T("");
	m_csGenericStartData = _T("");
	m_csGenericIgnore1 = _T("");
	m_csGenericIgnore2 = _T("");
	m_csGenericIgnore3 = _T("");
	m_csGenericIgnore4 = _T("");
	m_dwGenericDispearTime = 0;
	m_dwRegionY = 0;
	m_dwRegionX = 0;
	m_dwRegionHeight = 0;
	m_dwRegionWidth = 0;
	m_dwAveAddr = 0;
	m_dwCurselectIndx = 0;
	m_iUserID = -1;
	m_iDevIndex = -1;
	m_lPlayHandle = NULL;
	m_bSetDraw = FALSE;
	m_bShowOSD = FALSE;


	//}}AFX_DATA_INIT
}


void CDlgPosFilterRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPosFilterRule)
	DDX_Control(pDX, IDC_COMBO_CHAR_SET_TYPE, m_cmbCharSetType);
	DDX_Control(pDX, IDC_PIC_OSD_REGION, m_picOsdRegion);
	DDX_Control(pDX, IDC_COMBO_FILTERID, m_cmbFilterID);
	DDX_Control(pDX, IDC_LIST_RULE, m_listRule);
	DDX_Control(pDX, IDC_COMBO_PROTOCAL_TYPE, m_comboProtocalType);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Check(pDX, IDC_CHK_GENERIC_CASE_SENSITIVE, m_bGenericCaseSensitive);
    DDX_Check(pDX, IDC_CHK_GENERIC_CASE_START_FLAG, m_bGenericCaseStartFlag);
    DDX_Check(pDX, IDC_CHK_GENERIC_CASE_END_FLAG, m_bGenericCaseEndFlag);
	DDX_Check(pDX, IDC_CHK_GENERIC_END_HEX, m_bGenericEndHex);
	DDX_Check(pDX, IDC_CHK_GENERIC_NEWLINE_HEX, m_bGenericNewLineHex);
	DDX_Check(pDX, IDC_CHK_GENERIC_START_ANYCHAR, m_bGenericStartAnyChar);
	DDX_Check(pDX, IDC_CHK_GENERIC_START_HEX, m_bGenericStartHex);
	DDX_Check(pDX, IDC_CHK_OVERLAY_OSD, m_bOverlayOsd);
	DDX_Text(pDX, IDC_EDIT_ACTION_DELAYTIME, m_dwActionDelayTime);
	DDX_Text(pDX, IDC_EDIT_AVE_DISAPPERTIME, m_dwAveDisAppearTime);
	DDX_Text(pDX, IDC_EDIT_GENERIC_END, m_csGenericEndData);
	DDX_Text(pDX, IDC_EDIT_GENERIC_NEWLINE, m_csGenericNewlineData);
	DDX_Text(pDX, IDC_EDIT_GENERIC_START, m_csGenericStartData);
	DDX_Text(pDX, IDC_EDIT_GENERIC_IGNORE1, m_csGenericIgnore1);
	DDX_Text(pDX, IDC_EDIT_GENERIC_IGNORE2, m_csGenericIgnore2);
	DDX_Text(pDX, IDC_EDIT_GENERIC_IGNORE3, m_csGenericIgnore3);
	DDX_Text(pDX, IDC_EDIT_GENERIC_IGNORE4, m_csGenericIgnore4);
	DDX_Text(pDX, IDC_EDIT_GENERIC_DISPEARTIME, m_dwGenericDispearTime);
	DDX_Text(pDX, IDC_EDIT_REGION_Y, m_dwRegionY);
	DDX_Text(pDX, IDC_EDIT_REGION_X, m_dwRegionX);
	DDX_Text(pDX, IDC_EDIT_REGION_LENTH, m_dwRegionHeight);
	DDX_Text(pDX, IDC_EDIT_REGION_WIGHT, m_dwRegionWidth);
	DDX_Text(pDX, IDC_EDIT_ADDR_AVE, m_dwAveAddr);
	DDX_Check(pDX, IDC_CHK_SET, m_bSetDraw);
	DDX_Check(pDX, IDC_CHK_SHOW, m_bShowOSD);
    DDX_Text(pDX, IDC_EDIT_E, m_szEmployeeNo);
    DDX_Text(pDX, IDC_EDIT_T, m_szTerminalNo);
    DDX_Text(pDX, IDC_EDIT_S, m_szShiftNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPosFilterRule, CDialog)
	//{{AFX_MSG_MAP(CDlgPosFilterRule)
	ON_BN_CLICKED(IDC_BTN_EXPORT, OnBtnExport)
	ON_CBN_SELCHANGE(IDC_COMBO_PROTOCAL_TYPE, OnSelchangeComboProtocalType)
	ON_NOTIFY(NM_CLICK, IDC_LIST_RULE, OnClickListRule)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_IMPORT, OnBtnImport)
	ON_BN_CLICKED(IDC_CHK_GENERIC_START_ANYCHAR, OnChkGenericStartAnychar)
	ON_BN_CLICKED(IDC_BTN_DEFAULT, OnBtnDefault)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_TEST_EFFECT, OnBtnTestEffect)
	ON_EN_KILLFOCUS(IDC_EDIT_GENERIC_START, OnKillfocusEditGenericStart)
	ON_EN_KILLFOCUS(IDC_EDIT_GENERIC_DISPEARTIME, OnKillfocusEditGenericDispeartime)
	ON_BN_CLICKED(IDC_CHK_GENERIC_START_HEX, OnChkGenericStartHex)
	ON_EN_KILLFOCUS(IDC_EDIT_AVE_DISAPPERTIME, OnKillfocusEditAveDisappertime)
	ON_EN_KILLFOCUS(IDC_EDIT_GENERIC_END, OnKillfocusEditGenericEnd)
	ON_BN_CLICKED(IDC_CHK_GENERIC_END_HEX, OnChkGenericEndHex)
	ON_WM_CLOSE()
	ON_EN_KILLFOCUS(IDC_EDIT_ADDR_AVE, OnKillfocusEditAddrAve)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_CHK_SET, OnChkSet)
	ON_BN_CLICKED(IDC_CHK_SHOW, OnChkShow)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPosFilterRule message handlers

void CDlgPosFilterRule::OnBtnExport() 
{
	// TODO: Add your control notification handler code here
	CString csFileName;
	CTime time;
	char szLan[256] = {0};
	
	time = CTime::GetCurrentTime();

	csFileName.Format("c:\\FilterRule_%4d%02d%02d_%02d%02d.bin",\
	       time.GetYear(), time.GetMonth(),\
			time.GetDay(), time.GetHour(), time.GetMinute());
	
	if (!WriteDataToFile((LPSTR)(LPCTSTR)csFileName))
	{
		g_StringLanType(szLan, "导出失败！","Export Filter Rule Failed!");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_StringLanType(szLan, "导出成功！","Export Filter Rule success!");
		AfxMessageBox(szLan);
	}	
}

BOOL CDlgPosFilterRule::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ClientX = 0;
	m_ClientY = 0;
	m_ptStart.x = 0;
	m_ptStart.y = 0;
	m_ptEnd.x = 0;
	m_ptEnd.y = 0;
	m_bDrawdetect = FALSE;
	m_dwVedioWidth = 704;
	m_dwVedioLength = 480;

	// TODO: Add extra initialization here
    memset(&m_struPosFilterCfg, 0, sizeof(m_struPosFilterCfg));
	m_cmbCharSetType.SetCurSel(0);

 	m_listRule.SetExtendedStyle(m_listRule.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
	char szLan[128] = {0};
	g_StringLanType(szLan, "序号", "Serial No.");
	m_listRule.InsertColumn(0, szLan,LVCFMT_LEFT,40,-1);
	g_StringLanType(szLan, "启用", "Enable");
	m_listRule.InsertColumn(1,szLan,LVCFMT_LEFT,80,-1);
	
	g_StringLanType(szLan, "过滤规则名称", "RuleName");
	m_listRule.InsertColumn(2, szLan,LVCFMT_LEFT,160,-1);
	g_StringLanType(szLan, "协议类型", "Protocol type");
	m_listRule.InsertColumn(3, szLan,LVCFMT_LEFT,120,-1);
	g_StringLanType(szLan, "延迟时间", "Delay Show");
	m_listRule.InsertColumn(4, szLan,LVCFMT_LEFT,80,-1);
	g_StringLanType(szLan, "覆盖OSD", "Overlay OSD");
	m_listRule.InsertColumn(5, szLan,LVCFMT_LEFT,80,-1);

	//默认显示为Generic协议
	m_comboProtocalType.SetCurSel(0);
	m_cmbFilterID.SetCurSel(0);
	m_bEnable = TRUE;

	m_bkBrush.CreateSolidBrush(RGB(85,90,204));
	m_bOverBrush.CreateSolidBrush(RGB(255,0,0));
    GetDlgItem(IDC_STATIC_NUCLEUS)->ShowWindow(FALSE);
    GetDlgItem(IDC_STATIC_E)->ShowWindow(FALSE);
    GetDlgItem(IDC_STATIC_T)->ShowWindow(FALSE);
    GetDlgItem(IDC_STATIC_S)->ShowWindow(FALSE);
    GetDlgItem(IDC_EDIT_E)->ShowWindow(FALSE);
    GetDlgItem(IDC_EDIT_T)->ShowWindow(FALSE);
    GetDlgItem(IDC_EDIT_S)->ShowWindow(FALSE);
	//
// 	CRect rc(0, 0, 0, 0);
// 	GetDlgItem(IDC_BTN_ADD)->GetWindowRect(&rc);
// 	ScreenToClient(&rc);
//  
// 	rc.left += 613;
// 	rc.top  -= 98;
// 	rc.bottom += 127;
// 	rc.right += 858;
// 
// 	m_dlgRegion.Create(IDD_DLG_POS_REGION, this);
// 	m_dlgRegion.MoveWindow(&rc);
// 	m_dlgRegion.ShowWindow(SW_SHOW);
//	m_picOsdRegion.MoveWindow(405,95, 327, 245);

 
	this->GetWindowRect(&m_rcClientOSDRegion);
	m_picOsdRegion.GetWindowRect(&m_rcWindowOSDRegion); 

	m_ClientX = m_rcWindowOSDRegion.left - m_rcClientOSDRegion.left - 3;
	m_ClientY = m_rcWindowOSDRegion.top - m_rcClientOSDRegion.top - 23;

  if (m_iUserID < 0)
  {
	  ShowDrawOSDRegionInfo(FALSE);
  }
  else
  {
	  ShowDrawOSDRegionInfo(TRUE);
  }
   
  GetVideoInfo();
  
 	PreviewVedio();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPosFilterRule::OnSelchangeComboProtocalType() 
{
	// TODO: Add your control notification handler code here
	int iSelectProtocal = m_comboProtocalType.GetCurSel();
    if (0 == iSelectProtocal || 5 == iSelectProtocal || 6 == iSelectProtocal)
	{
		SetGenericInfoShow(TRUE);
		GetDlgItem(IDC_EDIT_GENERIC_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_TEST_EFFECT)->ShowWindow(TRUE);
        GetDlgItem(IDC_STATIC_NUCLEUS)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_E)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_T)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_S)->ShowWindow(FALSE);
        GetDlgItem(IDC_EDIT_E)->ShowWindow(FALSE);
        GetDlgItem(IDC_EDIT_T)->ShowWindow(FALSE);
        GetDlgItem(IDC_EDIT_S)->ShowWindow(FALSE);
	}
	else if (3 == iSelectProtocal) //ESPON
	{
		HideAllWindows();
	}
    else if (4 == iSelectProtocal)
    {
        HideAllWindows();
        GetDlgItem(IDC_STATIC_NUCLEUS)->ShowWindow(TRUE);
        GetDlgItem(IDC_STATIC_E)->ShowWindow(TRUE);
        GetDlgItem(IDC_STATIC_T)->ShowWindow(TRUE);
        GetDlgItem(IDC_STATIC_S)->ShowWindow(TRUE);
        GetDlgItem(IDC_EDIT_E)->ShowWindow(TRUE);
        GetDlgItem(IDC_EDIT_T)->ShowWindow(TRUE);
        GetDlgItem(IDC_EDIT_S)->ShowWindow(TRUE);
    }
	else
	{
		SetGenericInfoShow(FALSE);
		GetDlgItem(IDC_BTN_TEST_EFFECT)->ShowWindow(FALSE);
	}
	
}

void CDlgPosFilterRule::SetGenericInfoShow(BOOL bShow)
{
	//Generic协议对应的信息
	GetDlgItem(IDC_STATIC_GENERIC)->ShowWindow(bShow);
	GetDlgItem(IDC_CHK_GENERIC_CASE_SENSITIVE)->ShowWindow(bShow);
    GetDlgItem(IDC_CHK_GENERIC_CASE_START_FLAG)->ShowWindow(bShow);
    GetDlgItem(IDC_CHK_GENERIC_CASE_END_FLAG)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_GENERIC_DISAPPEAR_TIME)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_GENERIC_DISPEARTIME)->ShowWindow(FALSE);	
	GetDlgItem(IDC_STATIC_GENERIC_SECOND)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_GENERIC_START)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_GENERIC_START)->ShowWindow(bShow);
	GetDlgItem(IDC_CHK_GENERIC_START_ANYCHAR)->ShowWindow(FALSE);
	GetDlgItem(IDC_CHK_GENERIC_START_HEX)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_GENERIC_END)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_GENERIC_END)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_GENERIC_END_LINE)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_GENERIC_END_LINE)->ShowWindow(FALSE);
	GetDlgItem(IDC_CHK_GENERIC_END_HEX)->ShowWindow(bShow);	
	GetDlgItem(IDC_STATIC_GENERIC_NEWLINE)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_GENERIC_NEWLINE)->ShowWindow(bShow);
	GetDlgItem(IDC_CHK_GENERIC_NEWLINE_HEX)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_IGNORE)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_GENERIC_IGNORE1)->ShowWindow(bShow);				
	GetDlgItem(IDC_EDIT_GENERIC_IGNORE2)->ShowWindow(bShow);		
	GetDlgItem(IDC_EDIT_GENERIC_IGNORE3)->ShowWindow(bShow);		
	GetDlgItem(IDC_EDIT_GENERIC_IGNORE4)->ShowWindow(bShow);
    //NUCLEUS
    GetDlgItem(IDC_STATIC_NUCLEUS)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_E)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_T)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_S)->ShowWindow(bShow);
    GetDlgItem(IDC_EDIT_E)->ShowWindow(bShow);
    GetDlgItem(IDC_EDIT_T)->ShowWindow(bShow);
    GetDlgItem(IDC_EDIT_S)->ShowWindow(bShow);
	//AVE信息
	GetDlgItem(IDC_STATIC_AVE)->ShowWindow(!bShow);		
	GetDlgItem(IDC_STATIC_AVE_IPADDR)->ShowWindow(!bShow);	
	GetDlgItem(IDC_EDIT_ADDR_AVE)->ShowWindow(!bShow);	
	GetDlgItem(IDC_STATIC_AVE_DISAPPEAR_TIME)->ShowWindow(!bShow);
	GetDlgItem(IDC_EDIT_AVE_DISAPPERTIME)->ShowWindow(!bShow);	
	GetDlgItem(IDC_STATIC_AVE_SECOND)->ShowWindow(!bShow);		
	
}

void CDlgPosFilterRule::HideAllWindows()
{
	//Generic协议对应的信息
	GetDlgItem(IDC_STATIC_GENERIC)->ShowWindow(FALSE);
	GetDlgItem(IDC_CHK_GENERIC_CASE_SENSITIVE)->ShowWindow(FALSE);
    GetDlgItem(IDC_CHK_GENERIC_CASE_START_FLAG)->ShowWindow(FALSE);
    GetDlgItem(IDC_CHK_GENERIC_CASE_END_FLAG)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_GENERIC_DISAPPEAR_TIME)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_GENERIC_DISPEARTIME)->ShowWindow(FALSE);	
	GetDlgItem(IDC_STATIC_GENERIC_SECOND)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_GENERIC_START)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_GENERIC_START)->ShowWindow(FALSE);
	GetDlgItem(IDC_CHK_GENERIC_START_ANYCHAR)->ShowWindow(FALSE);
	GetDlgItem(IDC_CHK_GENERIC_START_HEX)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_GENERIC_END)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_GENERIC_END)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_GENERIC_END_LINE)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_GENERIC_END_LINE)->ShowWindow(FALSE);
	GetDlgItem(IDC_CHK_GENERIC_END_HEX)->ShowWindow(FALSE);	
	GetDlgItem(IDC_STATIC_GENERIC_NEWLINE)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_GENERIC_NEWLINE)->ShowWindow(FALSE);
	GetDlgItem(IDC_CHK_GENERIC_NEWLINE_HEX)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_IGNORE)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_GENERIC_IGNORE1)->ShowWindow(FALSE);				
	GetDlgItem(IDC_EDIT_GENERIC_IGNORE2)->ShowWindow(FALSE);		
	GetDlgItem(IDC_EDIT_GENERIC_IGNORE3)->ShowWindow(FALSE);		
	GetDlgItem(IDC_EDIT_GENERIC_IGNORE4)->ShowWindow(FALSE);
	
    //NUCLEUS
    GetDlgItem(IDC_STATIC_NUCLEUS)->ShowWindow(FALSE);
    GetDlgItem(IDC_STATIC_E)->ShowWindow(FALSE);
    GetDlgItem(IDC_STATIC_T)->ShowWindow(FALSE);
    GetDlgItem(IDC_STATIC_S)->ShowWindow(FALSE);
    GetDlgItem(IDC_EDIT_E)->ShowWindow(FALSE);
    GetDlgItem(IDC_EDIT_T)->ShowWindow(FALSE);
	//AVE信息
	GetDlgItem(IDC_STATIC_AVE)->ShowWindow(FALSE);		
	GetDlgItem(IDC_STATIC_AVE_IPADDR)->ShowWindow(FALSE);	
	GetDlgItem(IDC_EDIT_ADDR_AVE)->ShowWindow(FALSE);	
	GetDlgItem(IDC_STATIC_AVE_DISAPPEAR_TIME)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_AVE_DISAPPERTIME)->ShowWindow(FALSE);	
	GetDlgItem(IDC_STATIC_AVE_SECOND)->ShowWindow(FALSE);		
	
}

void CDlgPosFilterRule::OnClickListRule(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int iIndex = 0;
	POSITION  iPos = m_listRule.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
	}
	iIndex = m_listRule.GetNextSelectedItem(iPos);
	m_dwCurselectIndx = iIndex;
    
	showFilterRuleInfoByIndex(m_dwCurselectIndx);

	*pResult = 0;
}

void CDlgPosFilterRule::showFilterRuleInfoByIndex(UINT iIndex )
{
	UpdateData(TRUE);
	m_bEnable = m_struPosFilterCfg.byEnable ;
		m_comboProtocalType.SetCurSel(m_struPosFilterCfg.byProtocolType - 1);
		m_cmbCharSetType.SetCurSel(m_struPosFilterCfg.byCharSetType);
	
	if ((MODE_AVE_VSI_ADD == m_struPosFilterCfg.byProtocolType) || (MODE_AVE_VNET == m_struPosFilterCfg.byProtocolType) )//AVE协议
	{
		//显示
		SetGenericInfoShow(FALSE);
		m_dwAveAddr = m_struPosFilterCfg.uPosProtocol.struAve.dwPosAddr;
	}
	else if (MODE_EPOSN == m_struPosFilterCfg.byProtocolType)
	{
		HideAllWindows();
	}
    else if (MODE_NUCLEUS == m_struPosFilterCfg.byProtocolType)
    {
        HideAllWindows();
        GetDlgItem(IDC_STATIC_NUCLEUS)->ShowWindow(TRUE);
        GetDlgItem(IDC_STATIC_E)->ShowWindow(TRUE);
        GetDlgItem(IDC_STATIC_T)->ShowWindow(TRUE);
        GetDlgItem(IDC_STATIC_S)->ShowWindow(TRUE);
        GetDlgItem(IDC_EDIT_E)->ShowWindow(TRUE);
        GetDlgItem(IDC_EDIT_T)->ShowWindow(TRUE);
        GetDlgItem(IDC_EDIT_S)->ShowWindow(TRUE);

        m_szEmployeeNo = m_struPosFilterCfg.uPosProtocol.struNUCLEUS.szEmployeeNo;
        m_szTerminalNo = m_struPosFilterCfg.uPosProtocol.struNUCLEUS.szTerminalNo;
        m_szShiftNo = m_struPosFilterCfg.uPosProtocol.struNUCLEUS.szShiftNo;
    }
	else
	{
		SetGenericInfoShow(TRUE);
		m_comboProtocalType.SetCurSel(0);
        GetDlgItem(IDC_STATIC_NUCLEUS)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_E)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_T)->ShowWindow(FALSE);
        GetDlgItem(IDC_STATIC_S)->ShowWindow(FALSE);
        GetDlgItem(IDC_EDIT_E)->ShowWindow(FALSE);
        GetDlgItem(IDC_EDIT_T)->ShowWindow(FALSE);
        GetDlgItem(IDC_EDIT_S)->ShowWindow(FALSE);
		m_bGenericCaseSensitive = m_struPosFilterCfg.uPosProtocol.struGeneric.byCaseSensitive ;
        m_bGenericCaseStartFlag = m_struPosFilterCfg.uPosProtocol.struGeneric.struTransactionStart.byExclusive;
        m_bGenericCaseEndFlag = m_struPosFilterCfg.uPosProtocol.struGeneric.struTransactionEnd.byExclusive;
        m_bGenericStartHex = m_struPosFilterCfg.uPosProtocol.struGeneric.struTransactionStart.byFlagType;
        m_bGenericEndHex = m_struPosFilterCfg.uPosProtocol.struGeneric.struTransactionEnd.byFlagType;
        m_bGenericNewLineHex = m_struPosFilterCfg.uPosProtocol.struGeneric.struLineDeli.byFlagType;
		//开始信息
		m_csGenericStartData.Format("%s", m_struPosFilterCfg.uPosProtocol.struGeneric.struTransactionStart.sData);
		//结束信息
		m_csGenericEndData.Format("%s", m_struPosFilterCfg.uPosProtocol.struGeneric.struTransactionEnd.sData);
		
		//换行
		m_csGenericNewlineData.Format("%s", m_struPosFilterCfg.uPosProtocol.struGeneric.struLineDeli.sData);
		
		//忽略
		m_csGenericIgnore1.Format("%s", m_struPosFilterCfg.uPosProtocol.struGeneric.struIgnoreString[0].sData);
		m_csGenericIgnore2.Format("%s", m_struPosFilterCfg.uPosProtocol.struGeneric.struIgnoreString[1].sData);
		m_csGenericIgnore3.Format("%s", m_struPosFilterCfg.uPosProtocol.struGeneric.struIgnoreString[2].sData);
		m_csGenericIgnore4.Format("%s", m_struPosFilterCfg.uPosProtocol.struGeneric.struIgnoreString[3].sData);
	}
	 
	UpdateData(FALSE);
	return ;
}

//Set Filter Rule Info to CFG
BOOL  CDlgPosFilterRule::SetFilterRuleInfo()
{
	UpdateData(TRUE);
	char cGruopNum[2] = {0};
	char szLan[128] = {0};

	m_struPosFilterCfg.byEnable = m_bEnable;

	//验证数据是否有重复
	CString strTemp;
 
 
	m_struPosFilterCfg.byProtocolType = m_comboProtocalType.GetCurSel() + 1;
	m_struPosFilterCfg.byCharSetType = m_cmbCharSetType.GetCurSel();
	
    if (MODE_GENERIC == m_comboProtocalType.GetCurSel() + 1 ||
        MODE_GILBRARCO == m_comboProtocalType.GetCurSel() + 1 ||
        MODE_NCR == m_comboProtocalType.GetCurSel() + 1) //使用的是Generic协议
	{
		m_struPosFilterCfg.uPosProtocol.struGeneric.byCaseSensitive = m_bGenericCaseSensitive;
        m_struPosFilterCfg.uPosProtocol.struGeneric.struTransactionStart.byExclusive = m_bGenericCaseStartFlag;
        m_struPosFilterCfg.uPosProtocol.struGeneric.struTransactionEnd.byExclusive = m_bGenericCaseEndFlag;
        m_struPosFilterCfg.uPosProtocol.struGeneric.struTransactionStart.byFlagType = m_bGenericStartHex;
        m_struPosFilterCfg.uPosProtocol.struGeneric.struTransactionEnd.byFlagType = m_bGenericEndHex;
        m_struPosFilterCfg.uPosProtocol.struGeneric.struLineDeli.byFlagType = m_bGenericNewLineHex;
		//开始信息
		memcpy(m_struPosFilterCfg.uPosProtocol.struGeneric.struTransactionStart.sData, m_csGenericStartData, m_csGenericStartData.GetLength());
		//结束信息
		if (m_csGenericEndData.GetLength() > MAX_POS_FILTER_DATA_LEN)
		{
			g_StringLanType(szLan, "结束标志长度不能超过32！","The length of End Data  can not more than 32 !" );
			AfxMessageBox(szLan);
			return FALSE;
		}
		memcpy(m_struPosFilterCfg.uPosProtocol.struGeneric.struTransactionEnd.sData, m_csGenericEndData, m_csGenericEndData.GetLength());
		
		//换行
		if (m_csGenericNewlineData.GetLength() > MAX_POS_FILTER_DATA_LEN)
		{
			g_StringLanType(szLan, "换行标志长度不能超过32！","The length of New Line Data can not more than 32 !" );
			AfxMessageBox(szLan);
			return FALSE;
		}
		memcpy(m_struPosFilterCfg.uPosProtocol.struGeneric.struLineDeli.sData, m_csGenericNewlineData, m_csGenericNewlineData.GetLength());
		
		//忽略
		if (m_csGenericIgnore1.GetLength() > MAX_POS_FILTER_DATA_LEN,\
			m_csGenericIgnore2.GetLength() > MAX_POS_FILTER_DATA_LEN,\
			m_csGenericIgnore3.GetLength() > MAX_POS_FILTER_DATA_LEN,\
			m_csGenericIgnore4.GetLength() > MAX_POS_FILTER_DATA_LEN) 
		{
			g_StringLanType(szLan, "忽略的数据长度不能超过32！","The length of Ignore Data can not more than 32 !" );
			AfxMessageBox(szLan);
			return FALSE;
		}
		memcpy(m_struPosFilterCfg.uPosProtocol.struGeneric.struIgnoreString[0].sData, m_csGenericIgnore1, m_csGenericIgnore1.GetLength());
		memcpy(m_struPosFilterCfg.uPosProtocol.struGeneric.struIgnoreString[1].sData, m_csGenericIgnore2, m_csGenericIgnore2.GetLength());
		memcpy(m_struPosFilterCfg.uPosProtocol.struGeneric.struIgnoreString[2].sData, m_csGenericIgnore3, m_csGenericIgnore3.GetLength());
		memcpy(m_struPosFilterCfg.uPosProtocol.struGeneric.struIgnoreString[3].sData, m_csGenericIgnore4, m_csGenericIgnore4.GetLength());
	}
    else if (MODE_NUCLEUS == m_comboProtocalType.GetCurSel() + 1) //使用的是NUCLEUS协议
    {
        memcpy(m_struPosFilterCfg.uPosProtocol.struNUCLEUS.szEmployeeNo, m_szEmployeeNo, SERIAL_NUM_LEN);
        memcpy(m_struPosFilterCfg.uPosProtocol.struNUCLEUS.szTerminalNo, m_szTerminalNo, SERIAL_NUM_LEN);
        memcpy(m_struPosFilterCfg.uPosProtocol.struNUCLEUS.szShiftNo, m_szShiftNo, SERIAL_NUM_LEN);
    }
	else   //AVE协议
	{
		m_struPosFilterCfg.uPosProtocol.struAve.dwPosAddr = m_dwAveAddr;
	}
	

	return TRUE;	
}

//add Filter Rule To List
void CDlgPosFilterRule::AddFilterRuleInfoToList(UINT dwTheFileterNum, BOOL bModify )
{
	int iIndex = 0;
	if (!bModify)
	{
		iIndex = m_listRule.GetItemCount();
		CString strTemp = _T("");
		strTemp.Format("%02d", iIndex+1);
		m_listRule.InsertItem(iIndex, strTemp, 0);
	}
	else
	{
		iIndex = m_dwCurselectIndx;
	}


	char szLan[128] = {0};
	
	if (0 != m_struPosFilterCfg.byEnable)
	{
		g_StringLanType(szLan, "是", "yes");
	}
	else
	{
		g_StringLanType(szLan, "否", "no");
	}
	m_listRule.SetItemText(iIndex,1,szLan );
	

	if (MODE_GENERIC == m_struPosFilterCfg.byProtocolType)
	{
		sprintf(szLan, "%s","Generic");
	}
	else if (MODE_AVE_VSI_ADD == m_struPosFilterCfg.byProtocolType)
	{
		sprintf(szLan,"%s", "AVE VSI-ADD");
	}
	else if (MODE_AVE_VNET == m_struPosFilterCfg.byProtocolType)
	{
		sprintf(szLan,"%s", "AVE Vnet");
	}
	m_listRule.SetItemText(iIndex,3,szLan );
}

void CDlgPosFilterRule::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};

	if (m_iUserID < 0)
	{
		g_StringLanType(szLan, "请先登录！","please login device");
		AfxMessageBox(szLan);
		return;
	}

	if (SetFilterRuleInfo() == FALSE)
	{
		g_StringLanType(szLan, "设置过滤规则", "Set Filter Rule failed!");
		AfxMessageBox(szLan);
		return;
	}

	DWORD dwFilterID = m_cmbFilterID.GetCurSel() +1;
	m_struPosFilterCfg.dwSize = sizeof(m_struPosFilterCfg);
	//Set Filter To DVR
	if (!NET_DVR_SetDVRConfig(m_iUserID,NET_DVR_SET_POS_FILTER_CFG,dwFilterID,&m_struPosFilterCfg,sizeof(m_struPosFilterCfg)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_POS_FILTER_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_POS_FILTER_CFG");
	}
}

void CDlgPosFilterRule::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	memset(&m_struPosFilterCfg,0,sizeof(m_struPosFilterCfg));
	m_struPosFilterCfg.dwSize = sizeof(m_struPosFilterCfg);

	char szLan[128] = {0};

	if (m_iUserID < 0)
	{
		g_StringLanType(szLan, "请先登录！","please login device");
		AfxMessageBox(szLan);
	}
    
	DWORD dwReturn  = 0 ;
	DWORD dwFilterID = m_cmbFilterID.GetCurSel() +1;
	if (!NET_DVR_GetDVRConfig(m_iUserID, NET_DVR_GET_POS_FILTER_CFG,dwFilterID,&m_struPosFilterCfg, sizeof(m_struPosFilterCfg), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_POS_FILTER_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_POS_FILTER_CFG");
	}

	//default Show Frist Info
	showFilterRuleInfoByIndex(0);
}

void CDlgPosFilterRule::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgPosFilterRule::OnBtnImport() 
{
	// TODO: Add your control notification handler code here
	/*CString csFileName;
	CTime time;
	CString sTemp;
	char szLan[256]= {0};

	static char szFilter[] = "All File(*.*)|*.*||";
	CFileDialog dlg(TRUE,"*.*", NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);
	if (dlg.DoModal() == IDOK)
	{
		csFileName = dlg.GetPathName();
		UpdateData(FALSE);
	}

	if (!ReadDataFromFile((LPSTR)(LPCTSTR)csFileName))
	{
		g_StringLanType(szLan, "导入失败！","import Filter Rule Failed!");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_StringLanType(szLan, "导入成功！","import Filter Rule success!");
		AfxMessageBox(szLan);
	}

	//将数据写入到list表中
	m_listRule.DeleteAllItems();
	for (int i = 0; i< m_struPosFilterCfg.dwMaxRuleNum; i++)
	{
	   AddFilterRuleInfoToList(i);	
	}
	//默认显示第一个信息
	m_dwTheRuleNum = m_struPosFilterCfg.dwMaxRuleNum;
	showFilterRuleInfoByIndex(0);
	*/
}


BOOL CDlgPosFilterRule::WriteDataToFile(char* szFileName)
{
	/*if (szFileName == NULL)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "文件名不能为空", "please input file Name!");
		AfxMessageBox(szLan);
		return FALSE;
	}

	CStdioFile myFile;
	if (myFile.Open(szFileName, CFile::modeCreate|CFile::modeWrite) == FALSE)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "文件创建失败", "create file failed");
		AfxMessageBox(szLan);
		return FALSE;
	}
	
	myFile.Write((char*)&m_struPosFilterCfg,sizeof(m_struPosFilterCfg));
	myFile.Close();

*/
	return TRUE;
}

void CDlgPosFilterRule::PreviewVedio()
{
	NET_DVR_CLIENTINFO struPlayInfo;
	struPlayInfo.hPlayWnd = m_picOsdRegion.GetSafeHwnd();
	struPlayInfo.lChannel = 1;
	struPlayInfo.lLinkMode = 0;
	struPlayInfo.sMultiCastIP = "";	 
	
	//m_lPlayHandle = NET_DVR_RealPlay(m_iUserID, &struPlayInfo); 	 
}

void CDlgPosFilterRule::GetVideoInfo()
{
  //
}
BOOL CDlgPosFilterRule::ReadDataFromFile(char* szFileName)
{
	CStdioFile myFile;
	CString csFilename;
	CString csDir;
	
	if (myFile.Open(szFileName, CFile::modeRead) == FALSE)
	{
		myFile.Open(szFileName, CFile::modeCreate);
		return FALSE;
	}

	memset(&m_struPosFilterCfg, 0,sizeof(m_struPosFilterCfg));
	if (!myFile.ReadString((char*)&m_struPosFilterCfg,sizeof(m_struPosFilterCfg)))//1
	{
		myFile.Close();
		return FALSE;
	}
	myFile.Close();
	return TRUE;
}

void CDlgPosFilterRule::OnChkGenericStartAnychar() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_bGenericStartAnyChar)
	{
		GetDlgItem(IDC_EDIT_GENERIC_START)->EnableWindow(FALSE);
		m_csGenericStartData = "";
	}
	else
	{
		GetDlgItem(IDC_EDIT_GENERIC_START)->EnableWindow(TRUE);
	}

	UpdateData(FALSE);
	
}

void CDlgPosFilterRule::OnBtnDefault() 
{
	// TODO: Add your control notification handler code here

	CRect rcClient;
// 	m_dlgRegion.GetClientRect(&rcClient);
// 	m_DefaultRegion = rcClient;
// 	m_DefaultRegion.top = m_DefaultRegion.top + m_DefaultRegion.Height() / 2;
// 	m_dlgRegion.m_rcRegion = m_DefaultRegion;
// 	m_dlgRegion.m_rcRegion.DeflateRect(1, 0, 3, 3);
// 	int nIndex = 0;
 

	 
//	CWnd *pWnd = GetDlgItem(IDC_STATIC_OVER_REGION);
	CRect rectBtn;
	//pWnd->GetWindowRect(&rectBtn); 
	//ScreenToClient(&rectBtn);

    
}

HBRUSH CDlgPosFilterRule::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO: Change any attributes of the DC here
   
// 	if (pWnd->GetDlgCtrlID() == IDC_STATIC_DPREVIEW_REGION)  
// 	{   
// 		pDC->SetBkColor(RGB(255,0,0));//字体背景色
// 		return m_bkBrush;  
// 	} 
// 	if (pWnd->GetDlgCtrlID() == IDC_STATIC_OVER_REGION)  
// 	{   
// 		pDC->SetBkColor(RGB(255,0,0));//字体背景色
// 		return m_bOverBrush;  
// 	} 
   
// 	switch ()
// 	{
// 	case:
// 		break;
// 	case:
// 		break;
// 	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CDlgPosFilterRule::OnBtnTestEffect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	char szLan[128] ="";

	if (m_csFilterRuleName.IsEmpty())
	{
		g_StringLanType(szLan,"请设置过滤规则！","Please Set Filter Rule First!");
		AfxMessageBox(szLan);
		return;
	}

/*	CDlgPosFilterEffect dlg;
	dlg.m_lUserId = m_iUserID;
    dlg.m_dwTheFilterNum = 0;
	//Get Pos Filyer Info
	memset(&dlg.m_struFilterCfg, 0, sizeof(dlg.m_struFilterCfg));
	dlg.m_struFilterCfg.struVerHead.wLength = sizeof(dlg.m_struFilterCfg);
	//not add Group Num & Filter Num 
	dlg.m_struFilterCfg.struFilterCfg[0].byEnable = m_bEnable;
	dlg.m_struFilterCfg.struFilterCfg[0].dwProtocolType = m_comboProtocalType.GetCurSel() + 1;
	memcpy(dlg.m_struFilterCfg.struFilterCfg[0].sPosName,m_csFilterRuleName, m_csFilterRuleName.GetLength());
	dlg.m_struFilterCfg.struFilterCfg[0].struAction.byPrevOsd = m_bOverlayOsd;
	dlg.m_struFilterCfg.struFilterCfg[0].struAction.dwDelayTime = m_dwActionDelayTime;
	dlg.m_struFilterCfg.struFilterCfg[0].struAction.struOsdPosInfo.wStartX = m_dwRegionX;
	dlg.m_struFilterCfg.struFilterCfg[0].struAction.struOsdPosInfo.wStartY = m_dwRegionY;
	dlg.m_struFilterCfg.struFilterCfg[0].struAction.struOsdPosInfo.wRectWidth = m_dwRegionWidth;
	dlg.m_struFilterCfg.struFilterCfg[0].struAction.struOsdPosInfo.wRectHeight = m_dwRegionHeight;

	switch(dlg.m_struFilterCfg.struFilterCfg[0].dwProtocolType)
	{
	case MODE_GENERIC:
		dlg.m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.byCaseSensitive = m_bGenericCaseSensitive;
		dlg.m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.dwTimeout = m_dwGenericDispearTime;
		dlg.m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struTransactionStart.byAnyCharacter = m_bGenericStartAnyChar;
		//start
		if (m_bGenericStartAnyChar == FALSE)
		{
			memcpy(dlg.m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struTransactionStart.sData, m_csGenericStartData, m_csGenericStartData.GetLength());
		}
		dlg.m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struTransactionStart.byHex = m_bGenericStartHex;
		
		//new line
		dlg.m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struLineDeli.byHex = m_bGenericNewLineHex;
		memcpy(dlg.m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struLineDeli.sData,m_csGenericNewlineData,m_csGenericNewlineData.GetLength()); 

		//end
		memcpy(dlg.m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struTransactionEnd.sData,m_csGenericEndData, m_csGenericEndData.GetLength());
		dlg.m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struTransactionEnd.dwMoreLine = m_dwGenericEndLine;
		dlg.m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struTransactionEnd.byHex = m_bGenericEndHex;


		//ignore
		memcpy(dlg.m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struIgnoreString[0].sData, m_csGenericIgnore1, m_csGenericIgnore1.GetLength());
		memcpy(dlg.m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struIgnoreString[1].sData, m_csGenericIgnore1, m_csGenericIgnore2.GetLength());
		memcpy(dlg.m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struIgnoreString[2].sData, m_csGenericIgnore1, m_csGenericIgnore3.GetLength());
		memcpy(dlg.m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struIgnoreString[3].sData, m_csGenericIgnore1, m_csGenericIgnore4.GetLength());
		break;
	case MODE_AVE_VSI_ADD:
	case MODE_AVE_VNET:
		dlg.m_struFilterCfg.struFilterCfg[0].struPosProtocol.struAve.dwAddress = m_dwAveAddr;
		dlg.m_struFilterCfg.struFilterCfg[0].struPosProtocol.struAve.dwTimeout = m_dwAveDisAppearTime;
		break;
	default:
		g_StringLanType(szLan,"请选择协议类型!","Please select Protocal Type First!");
		AfxMessageBox(szLan);
		return;
	}

	dlg.m_iDevIndex = m_iDevIndex;

	
	dlg.DoModal();
	*/
}

void CDlgPosFilterRule::OnKillfocusEditGenericStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	char szLan[128]={0};
	if (m_bGenericStartHex)
	{
		if (m_csGenericStartData.GetLength() > MAX_POS_FILTER_DATA_LEN || (m_csGenericStartData.GetLength()%2 ==1))
		{
			g_StringLanType(szLan, "开始标志长度不能超过32且不能为奇数！","The length of Start Data can not more than 32 or odd number!" );
			AfxMessageBox(szLan);
			return;
		}
	}	
}

void CDlgPosFilterRule::OnKillfocusEditGenericDispeartime() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (m_dwGenericDispearTime < 5 || m_dwGenericDispearTime >3600)
	{

		g_StringLanType(szLan,"延迟消失时间为5--3600s!","The Delay disappear time between 5 and 3600 s!");
		AfxMessageBox(szLan);
		return;
	}	
}

void CDlgPosFilterRule::OnChkGenericStartHex() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (m_bGenericStartHex)
	{
		if (m_csGenericStartData.GetLength() > MAX_POS_FILTER_DATA_LEN || (m_csGenericStartData.GetLength()%2 ==1))
		{
			g_StringLanType(szLan, "开始标志长度不能超过32且不能为奇数！","The length of Start Data can not more than 32 or odd number!" );
			AfxMessageBox(szLan);
			return;
		}
	}	
}

void CDlgPosFilterRule::OnKillfocusEditAveDisappertime() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (m_dwAveDisAppearTime < 5 || m_dwAveDisAppearTime >3600)
	{
		
		g_StringLanType(szLan,"延迟消失时间为5--3600s!","The Delay disappear time between 5 and 3600 s!");
		AfxMessageBox(szLan);
		return;
	}	
}

void CDlgPosFilterRule::OnKillfocusEditGenericEnd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (m_bGenericEndHex)
	{
		if (m_csGenericEndData.GetLength() > MAX_POS_FILTER_DATA_LEN || (m_csGenericEndData.GetLength()%2 ==1))
		{
			g_StringLanType(szLan, "结束标志长度不能超过32且不能为奇数！","The length of End Data can not more than 32 or odd number!" );
			AfxMessageBox(szLan);
			return;
		}
	}
}

void CDlgPosFilterRule::OnChkGenericEndHex() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (m_bGenericEndHex)
	{
		if (m_csGenericEndData.GetLength() > MAX_POS_FILTER_DATA_LEN || (m_csGenericEndData.GetLength()%2 ==1))
		{
			g_StringLanType(szLan, "结束标志长度不能超过32且不能为奇数！","The length of End Data can not more than 32 or odd number!" );
			AfxMessageBox(szLan);
			return;
		}
	}
}

void CDlgPosFilterRule::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
 
	CDialog::OnClose();
}

void CDlgPosFilterRule::OnKillfocusEditAddrAve() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (m_dwAveAddr > 99)
	{
		g_StringLanType(szLan, "AVE地址编号为0~99！","AVE address number from 0 to 99!" );
		AfxMessageBox(szLan);
		return;
	}
}

void CDlgPosFilterRule::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

   
	if (m_bDrawdetect)
	{
		if (MK_CONTROL&nFlags)
		{
			if (point.x < m_ClientX || point.y < m_ClientY )
			{
				return;
			}

		
			NET_DVR_RigisterDrawFun(m_lPlayHandle, SetOSDRegionCallBack, 0);
// 			point.x -= 1;
// 			point.y -= 1;
// 			if (point.x < 0)
// 			{
// 				point.x = 0;
// 			}
// 			g_rectSetArea.left=point.x/16*16;
// 			if (point.y < 0)
// 			{
// 				point.y = 0;
// 			}
// 			g_rectSetArea.top=point.y/16*16;
// 			g_rectSetArea.right=g_rectSetArea.left;  
// 			g_rectSetArea.bottom=g_rectSetArea.top;
			POINT tPoint=point;
    		g_rectSetArea.left=tPoint.x - m_ClientX;
			g_rectSetArea.top=tPoint.y -m_ClientY;
			g_rectSetArea.right=tPoint.x  - m_ClientX;
			g_rectSetArea.bottom=tPoint.y   -m_ClientY;

			if (tPoint.x - m_ClientX < 0)
			{
				m_ptStart.x = 0;
			}
			else
			{
				m_ptStart.x = tPoint.x;
			}
		    
			if (tPoint.y - m_ClientY< 0)
			{
				m_ptStart.y = 0;
			}
			else
			{
				m_ptStart.y = tPoint.y;
			}
		}
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgPosFilterRule::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bDrawdetect)
	{
		if (MK_CONTROL&nFlags&&MK_LBUTTON&nFlags)
		{
			if (point.x > 727)
			{
				point.x = 727;
			}
 
			if (point.y > 337)
			{
				point.y = 337;
			}
 
			POINT tPoint=point;
			g_rectSetArea.right=tPoint.x - m_ClientX;
			g_rectSetArea.bottom=tPoint.y - m_ClientY;
		}
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CDlgPosFilterRule::OnChkSet() 
{
	// TODO: Add your control notification handler code here
	if (m_lPlayHandle < 0)
	{
		return;
	}
	UpdateData(TRUE);
	if (m_bSetDraw)
	{
		m_bShowOSD = FALSE;
		UpdateData(FALSE);
	}
	if (m_bSetDraw)
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL,0);
		m_bDrawdetect = TRUE;
	}
	else
	{
		m_bDrawdetect = FALSE;
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL,0);
	}
	
}

void CDlgPosFilterRule::OnChkShow() 
{
	// TODO: Add your control notification handler code here

	if (m_lPlayHandle < 0)
	{
		return;
	}
	UpdateData(TRUE);
	if (m_bSetDraw)
	{
		m_bSetDraw = FALSE;
		m_bDrawdetect = FALSE;
		UpdateData(FALSE);
		GetDlgItem(ID_BTN_HIDE_ALARM_OK)->EnableWindow(FALSE);
	}
	if (m_bShowOSD)
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL, 0);
		Sleep(200);
		NET_DVR_RigisterDrawFun(m_lPlayHandle,GetOSDCallBack, 0);
	}
	else
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL, 0);
	}
}

void CDlgPosFilterRule::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	m_ptEnd.x = point.x;
	m_ptEnd.y = point.y;
	CDialog::OnLButtonUp(nFlags, point);
}


void CDlgPosFilterRule::ShowDrawOSDRegionInfo(BOOL bShow)
{
	
	//显示坐标信息
	GetDlgItem(IDC_STATIC_X)->ShowWindow(!bShow);
	GetDlgItem(IDC_EDIT_REGION_X)->ShowWindow(!bShow);
	GetDlgItem(IDC_STATIC_Y)->ShowWindow(!bShow);
	GetDlgItem(IDC_EDIT_REGION_Y)->ShowWindow(!bShow);
	GetDlgItem(IDC_STATIC_WIDTH)->ShowWindow(!bShow);
	GetDlgItem(IDC_EDIT_REGION_WIGHT)->ShowWindow(!bShow);
	GetDlgItem(IDC_STATIC_LENGTH)->ShowWindow(!bShow);
	GetDlgItem(IDC_EDIT_REGION_LENTH)->ShowWindow(!bShow);

	//显示绘图区域
	GetDlgItem(IDC_PIC_OSD_REGION)->ShowWindow(bShow);
	GetDlgItem(IDC_CHK_SHOW)->ShowWindow(bShow);
	GetDlgItem(IDC_CHK_SET)->ShowWindow(bShow);

	UpdateData(FALSE);
}
