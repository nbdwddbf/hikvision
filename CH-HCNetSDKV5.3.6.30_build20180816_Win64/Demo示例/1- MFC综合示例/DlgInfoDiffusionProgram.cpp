// DlgInfoDiffusionProgram.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionProgram.h"
#include "DlgInfoDiffusionContent.h"
#include "DlgInfoDiffusionContainer.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionProgram dialog


CDlgInfoDiffusionProgram::CDlgInfoDiffusionProgram(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionProgram::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionProgram)
	m_szProgramRemarks = _T("");
	m_szProgramName = _T("");
	m_dwProgramID = 0;
	m_dwPageID = 0;
	m_dwImageWidth = 0;
	m_dwImageHeight = 0;
	m_dwBlue = 0;
	m_dwGreen = 0;
	m_dwRed = 0;
	m_dwSwitchDuration = 0;
	m_dwPlayDuration = 0;
	m_tmStartTime = COleDateTime::GetCurrentTime();
	m_tmStartDate = COleDateTime::GetCurrentTime();
	m_tmEndTime = COleDateTime::GetCurrentTime();
	m_tmEndDate = COleDateTime::GetCurrentTime();
	m_sUploader = _T("");
	m_dwStartPosition = 0;
	m_sSearchID = _T("");
	m_dwProImageWitdth = 0;
	m_dwProImageHeight = 0;
	m_dwMaxResults = 0;
	m_sApproveRemarks = _T("");
	m_sPageName = _T("");
	m_dwBackgroundPic = 0;
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_lpProgram = new NET_DVR_PROGRAM;
	memset(m_lpProgram, 0, sizeof(*m_lpProgram));
	memset(&m_struDescription, 0, sizeof(m_struDescription));
	m_lpResult = new NET_DVR_PROGRAM_SEARCH_RESULT;
	memset(m_lpResult, 0, sizeof(*m_lpResult));
	m_nCurSelProgram = -1;
	m_nCurSelPage = -1;
	m_nCurContent = -1;
	m_pOutputXmlBuffer = new char[MAX_LEN_XML];
	memset(m_pOutputXmlBuffer, 0, sizeof(char)*MAX_LEN_XML);
}


void CDlgInfoDiffusionProgram::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgInfoDiffusionProgram)
    DDX_Control(pDX, IDC_COMBO_PLAY_MODE, m_cmbPlayMode);
    DDX_Control(pDX, IDC_COMBO_APPROVE_STATE, m_cmbApproveState);
    DDX_Control(pDX, IDC_COMBO_PRO_APPROVE_STATE, m_cmbProApproveState);
    DDX_Control(pDX, IDC_COMBO_PRO_SHARE_PROP, m_cmbProShareProp);
    DDX_Control(pDX, IDC_COMBO_SWITCH_EFFECT, m_cmbSwitchEffect);
    DDX_Control(pDX, IDC_COMBO_SHARE_PROP, m_cmbShareProp);
    DDX_Control(pDX, IDC_LIST_CONTENT, m_listContent);
    DDX_Control(pDX, IDC_LIST_PAGE, m_listPage);
    DDX_Control(pDX, IDC_LIST_PROGRAM, m_listProgram);
    DDX_Text(pDX, IDC_EDIT_PROGRAM_REMARKS, m_szProgramRemarks);
    DDX_Text(pDX, IDC_EDIT_PROGRAM_NAME, m_szProgramName);
    DDX_Text(pDX, IDC_EDIT_PROGRAM_ID, m_dwProgramID);
    DDX_Text(pDX, IDC_EDIT_PAGE_ID, m_dwPageID);
    DDX_Text(pDX, IDC_EDIT_IMAGE_WITDH, m_dwImageWidth);
    DDX_Text(pDX, IDC_EDIT_IMAGE_HEIGHT, m_dwImageHeight);
    DDX_Text(pDX, IDC_EDIT_BLUE, m_dwBlue);
    DDX_Text(pDX, IDC_EDIT_GREEN, m_dwGreen);
    DDX_Text(pDX, IDC_EDIT_RED, m_dwRed);
    DDX_Text(pDX, IDC_EDIT_SWITCH_DURATION, m_dwSwitchDuration);
    DDX_Text(pDX, IDC_EDIT_PLAY_DURATION, m_dwPlayDuration);
    DDX_DateTimeCtrl(pDX, IDC_START_TIME, m_tmStartTime);
    DDX_DateTimeCtrl(pDX, IDC_START_DATE, m_tmStartDate);
    DDX_DateTimeCtrl(pDX, IDC_END_TIME, m_tmEndTime);
    DDX_DateTimeCtrl(pDX, IDC_END_DATE, m_tmEndDate);
    DDX_Text(pDX, IDC_EDIT_UPLOADER, m_sUploader);
    DDX_Text(pDX, IDC_EDIT_PRO_START_POSITION, m_dwStartPosition);
    DDX_Text(pDX, IDC_EDIT_PRO_SEARCH_ID, m_sSearchID);
    DDX_Text(pDX, IDC_EDIT_PRO_IMAGE_WITDH, m_dwProImageWitdth);
    DDX_Text(pDX, IDC_EDIT_PRO_IMAGE_HEIGHT, m_dwProImageHeight);
    DDX_Text(pDX, IDC_EDIT_MAX_RESULTS, m_dwMaxResults);
    DDX_Text(pDX, IDC_EDIT_APPROVE_REMARKS, m_sApproveRemarks);
    DDX_Text(pDX, IDC_EDIT_PAGE_NAME, m_sPageName);
    DDX_Text(pDX, IDC_EDIT_BACKGROUND_PIC, m_dwBackgroundPic);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_OPERATOR_TYPE, m_comOperatorType);
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionProgram, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionProgram)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_PAGE_DEL, OnBtnPageDel)
	ON_BN_CLICKED(IDC_BTN_PAGE_GET, OnBtnPageGet)
	ON_BN_CLICKED(IDC_BTN_PAGE_GETALL, OnBtnPageGetall)
	ON_BN_CLICKED(IDC_BTN_PAGE_NEW, OnBtnPageNew)
	ON_BN_CLICKED(IDC_BTN_PAGE_SET, OnBtnPageSet)
	ON_BN_CLICKED(IDC_BTN_PROGRAM_DEL, OnBtnProgramDel)
	ON_BN_CLICKED(IDC_BTN_PROGRAM_GET, OnBtnProgramGet)
	ON_BN_CLICKED(IDC_BTN_PROGRAM_NEW, OnBtnProgramNew)
	ON_BN_CLICKED(IDC_BTN_PROGRAM_SET, OnBtnProgramSet)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CONTENT, OnRclickListContent)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CONTENT, OnDblclkListContent)
	ON_COMMAND(ID_MENUITEM_ADD, OnMenuitemAdd)
	ON_COMMAND(ID_MENUITEM_DEL, OnMenuitemDel)
	ON_COMMAND(ID_MENUITEM_MOD, OnMenuitemMod)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PAGE, OnClickListPage)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_PRO_SEARCH, OnBtnProSearch)
	ON_CBN_SELCHANGE(IDC_COMBO_PLAY_MODE, OnSelchangeComboPlayMode)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_DEL_MORE, &CDlgInfoDiffusionProgram::OnBnClickedBtnDelMore)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PAGE, &CDlgInfoDiffusionProgram::OnLvnItemchangedListPage)
    ON_BN_CLICKED(IDC_BTN_BATCG_SET, &CDlgInfoDiffusionProgram::OnBnClickedBtnBatcgSet)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionProgram message handlers

void CDlgInfoDiffusionProgram::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgInfoDiffusionProgram::OnBtnPageDel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_nCurSelPage < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请选择页面", "Please choose a page first.");
		g_StringLanType(szLan2, "节目管理", "Program Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	
	CString strCommand;
	strCommand.Format("DELETE /ISAPI/Publish/ProgramMgr/program/%d/page/%d\r\n", 
		m_lpProgram->dwProgramID,
		m_lpProgram->struPageList.struPageList[m_nCurSelPage].dwPageID);
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	
	for (int nPageCnt = m_nCurSelPage; nPageCnt < m_listPage.GetItemCount()-1; nPageCnt++)
	{
		m_listPage.SetItemText(nPageCnt, 1, m_listPage.GetItemText(nPageCnt+1, 1));
		m_listPage.SetItemText(nPageCnt, 2, m_listPage.GetItemText(nPageCnt+1, 2));
		memcpy(&m_lpProgram->struPageList.struPageList[nPageCnt], &m_lpProgram->struPageList.struPageList[nPageCnt+1], sizeof(NET_DVR_PAGE));
	}
	memset(&m_lpProgram->struPageList.struPageList[m_listPage.GetItemCount()-1], 0, sizeof(NET_DVR_PAGE));
	m_listPage.DeleteItem(m_listPage.GetItemCount()-1);
	m_nCurSelPage = -1;
	m_listContent.DeleteAllItems();

	UpdateData(FALSE);
}

void CDlgInfoDiffusionProgram::OnBtnPageGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_nCurSelPage < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请选择页面", "Please choose a page first.");
		g_StringLanType(szLan2, "节目管理", "Program Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	
	CString strCommand;
	strCommand.Format("GET /ISAPI/Publish/ProgramMgr/program/%d/page/%d\r\n", 
		m_lpProgram->dwProgramID,
		m_lpProgram->struPageList.struPageList[m_nCurSelPage].dwPageID);
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	
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
	
	LPNET_DVR_PAGE lpPage = &m_lpProgram->struPageList.struPageList[m_nCurSelPage];
	memset(lpPage, 0, sizeof(*lpPage));
	lpPage->dwSize = sizeof(*lpPage);
	ConvertPageParamsXmlToStru(m_pOutputXmlBuffer, lpPage);
	
	RefreshPageItem(m_nCurSelPage);
	RefreshContentList(m_nCurSelPage);
	m_dwPageID = lpPage->dwPageID;
	m_sPageName = lpPage->struBasicInfo.sPageName;
	m_cmbPlayMode.SetCurSel(m_cmbPlayMode.FindString(-1, lpPage->struBasicInfo.sPlayMode));
	OnSelchangeComboPlayMode();
	m_dwPlayDuration = lpPage->struBasicInfo.dwPlayDuration;
	m_dwSwitchDuration = lpPage->struBasicInfo.dwSwitchDuraton;
	m_cmbSwitchEffect.SetCurSel(m_cmbSwitchEffect.FindString(-1, lpPage->struBasicInfo.szSwitchEffect));
	m_dwRed = lpPage->struBasicInfo.struBkColor.dwRed;
	m_dwGreen = lpPage->struBasicInfo.struBkColor.dwGreen;
	m_dwBlue = lpPage->struBasicInfo.struBkColor.dwBlue;
	m_dwBackgroundPic = lpPage->struBasicInfo.dwBackgroundPic;

	UpdateData(FALSE);
}

void CDlgInfoDiffusionProgram::OnBtnPageGetall() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString strCommand;
	strCommand.Format("GET /ISAPI/Publish/ProgramMgr/program/%d/page\r\n", m_lpProgram->dwProgramID);
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	
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
	
	LPNET_DVR_PAGE_LIST lpPageList = &m_lpProgram->struPageList;
	memset(lpPageList, 0, sizeof(*lpPageList));
	lpPageList->dwSize = sizeof(*lpPageList);
	ConvertPageParamsXmlToStruList(m_pOutputXmlBuffer, lpPageList);
	
	RefreshPageList();
	m_listContent.DeleteAllItems();
	
	UpdateData(FALSE);
}

void CDlgInfoDiffusionProgram::OnBtnPageNew() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	int nPageIndex = -1;
	for (int nPageCnt = 0; nPageCnt < MAX_PAGES_A_PROGRAM; nPageCnt++)
	{
		if (0 == m_lpProgram->struPageList.struPageList[nPageCnt].dwPageID)
		{
			nPageIndex = nPageCnt;
			break;
		}
	}
	if (nPageIndex < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "页面数量已达上限", "The number of page is limited.");
		g_StringLanType(szLan2, "节目管理", "Program Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	LPNET_DVR_PAGE lpPage = &m_lpProgram->struPageList.struPageList[nPageIndex];
	memset(lpPage, 0, sizeof(*lpPage));
	lpPage->dwSize = sizeof(*lpPage);
	strcpy(lpPage->struBasicInfo.sPageName, m_sPageName);
	int nSel = m_cmbPlayMode.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "节目管理", "Program Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbPlayMode.GetLBText(nSel, lpPage->struBasicInfo.sPlayMode);
	if (0 == strcmp(lpPage->struBasicInfo.sPlayMode, "selfDefine"))
	{
		lpPage->struBasicInfo.dwPlayDuration = m_dwPlayDuration;
	}
	lpPage->struBasicInfo.dwSwitchDuraton = m_dwSwitchDuration;
	nSel = m_cmbSwitchEffect.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "节目管理", "Program Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbSwitchEffect.GetLBText(nSel, lpPage->struBasicInfo.szSwitchEffect);
	lpPage->struBasicInfo.struBkColor.dwRed = m_dwRed;
	lpPage->struBasicInfo.struBkColor.dwGreen = m_dwGreen;
	lpPage->struBasicInfo.struBkColor.dwBlue = m_dwBlue;
	lpPage->struBasicInfo.dwBackgroundPic = m_dwBackgroundPic;

	char* pInputBuff = NULL;
	DWORD dwInputSize = 0;
	ConvertPageParamsStruToXml(lpPage, &pInputBuff, dwInputSize);

	CString strCommand;
	strCommand.Format("POST /ISAPI/Publish/ProgramMgr/program/%d/page\r\n",
		m_lpProgram->dwProgramID);
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	struInputParam.lpInBuffer = pInputBuff;
	struInputParam.dwInBufferSize = dwInputSize;
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		delete[] pInputBuff;
		pInputBuff = NULL;
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	
	m_dwPageID = GetResponseStatusID(szStatusBuff);
	lpPage->dwPageID = m_dwPageID;
	CString str;
	str.Format("%d", nPageIndex+1);
	m_listPage.InsertItem(nPageIndex, str);
	m_listPage.SetItemState(m_nCurSelPage, 0, -1);
	m_listPage.SetItemState(nPageIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_listPage.SetFocus();
	m_nCurSelPage = nPageIndex;
	RefreshPageItem(nPageIndex);

	delete[] pInputBuff;
	pInputBuff = NULL;
	
	UpdateData(FALSE);
}

void CDlgInfoDiffusionProgram::OnBtnPageSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_nCurSelPage < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请选择页面", "Please choose a page first.");
		g_StringLanType(szLan2, "节目管理", "Program Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	
	LPNET_DVR_PAGE lpPage = &m_lpProgram->struPageList.struPageList[m_nCurSelPage];
	lpPage->dwSize = sizeof(*lpPage);
	lpPage->dwPageID = m_dwPageID;
	strcpy(lpPage->struBasicInfo.sPageName, m_sPageName);
	int nSel = m_cmbPlayMode.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "节目管理", "Program Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbPlayMode.GetLBText(nSel, lpPage->struBasicInfo.sPlayMode);
	if (0 == strcmp(lpPage->struBasicInfo.sPlayMode, "selfDefine"))
	{
		lpPage->struBasicInfo.dwPlayDuration = m_dwPlayDuration;
	}
	lpPage->struBasicInfo.dwSwitchDuraton = m_dwSwitchDuration;
	nSel = m_cmbSwitchEffect.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "节目管理", "Program Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbSwitchEffect.GetLBText(nSel, (char*)lpPage->struBasicInfo.szSwitchEffect);
	lpPage->struBasicInfo.struBkColor.dwRed = m_dwRed;
	lpPage->struBasicInfo.struBkColor.dwGreen = m_dwGreen;
	lpPage->struBasicInfo.struBkColor.dwBlue = m_dwBlue;
	lpPage->struBasicInfo.dwBackgroundPic = m_dwBackgroundPic;

	char* pInputBuff = NULL;
	DWORD dwInputSize = 0;
	ConvertPageParamsStruToXml(lpPage, &pInputBuff, dwInputSize);

	CString strCommand;
	strCommand.Format("PUT /ISAPI/Publish/ProgramMgr/program/%d/page/%d\r\n", 
		m_lpProgram->dwProgramID,
		m_lpProgram->struPageList.struPageList[m_nCurSelPage].dwPageID);
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	struInputParam.lpInBuffer = pInputBuff;
	struInputParam.dwInBufferSize = dwInputSize;
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		delete[] pInputBuff;
		pInputBuff = NULL;
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");

	RefreshPageItem(m_nCurSelPage);

	delete[] pInputBuff;
	pInputBuff = NULL;

	UpdateData(FALSE);
}

void CDlgInfoDiffusionProgram::OnBtnProgramDel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CString strCommand;
    m_lpProgram->dwProgramID = m_dwProgramID;
	strCommand.Format("DELETE /ISAPI/Publish/ProgramMgr/program/%d\r\n", m_lpProgram->dwProgramID);
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");

	m_listPage.DeleteAllItems();
	m_nCurSelPage = -1;
	m_listContent.DeleteAllItems();

	UpdateData(FALSE);
}

void CDlgInfoDiffusionProgram::OnBtnProgramGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString strCommand;
	strCommand.Format("GET /ISAPI/Publish/ProgramMgr/program/%d\r\n", m_dwProgramID);
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	
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

	memset(m_lpProgram, 0, sizeof(*m_lpProgram));
	m_lpProgram->dwSize = sizeof(*m_lpProgram);
	ConvertProgramParamsXmlToStru(m_pOutputXmlBuffer, m_lpProgram);

	UpdateProgramInfo();
	RefreshPageList();
	m_nCurSelPage = -1;
	m_listContent.DeleteAllItems();

	UpdateData(FALSE);
}

void CDlgInfoDiffusionProgram::OnBtnProgramNew() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	memset(m_lpProgram, 0, sizeof(*m_lpProgram));
	m_lpProgram->dwSize = sizeof(*m_lpProgram);
	strcpy(m_lpProgram->szProgramName, m_szProgramName);
	strcpy(m_lpProgram->szProgramRemarks, m_szProgramRemarks);
	int nSel = m_cmbShareProp.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "节目管理", "Program Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbShareProp.GetLBText(nSel, m_lpProgram->szShareProp);
	m_lpProgram->struResolution.dwImageWidth = m_dwImageWidth;
	m_lpProgram->struResolution.dwImageHeight = m_dwImageHeight;
	nSel = m_cmbApproveState.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "节目管理", "Program Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbApproveState.GetLBText(nSel, m_lpProgram->szApprove);
	strcpy(m_lpProgram->szApproveRemarks, m_sApproveRemarks);
	
	char* pInputBuff = NULL;
	DWORD dwInputSize = 0;
	ConvertProgramParamsStruToXml(m_lpProgram, &pInputBuff, dwInputSize);
	
	CString strCommand;
	strCommand.Format("POST /ISAPI/Publish/ProgramMgr/program\r\n");
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	struInputParam.lpInBuffer = pInputBuff;
	struInputParam.dwInBufferSize = dwInputSize;
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		delete[] pInputBuff;
		pInputBuff = NULL;
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	
	m_dwProgramID = GetResponseStatusID(szStatusBuff);
	m_lpProgram->dwProgramID = m_dwProgramID;
	
	delete[] pInputBuff;
	pInputBuff = NULL;
	
	UpdateData(FALSE);
}

void CDlgInfoDiffusionProgram::OnBtnProgramSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_lpProgram->dwProgramID = m_dwProgramID;
	memcpy(m_lpProgram->szProgramName, m_szProgramName, strlen(m_szProgramName));
	memcpy(m_lpProgram->szProgramRemarks, m_szProgramRemarks, strlen(m_szProgramRemarks));
	int nSel = m_cmbShareProp.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "节目管理", "Program Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbShareProp.GetLBText(nSel, m_lpProgram->szShareProp);
	m_lpProgram->struResolution.dwImageWidth = m_dwImageWidth;
	m_lpProgram->struResolution.dwImageHeight = m_dwImageHeight;
	nSel = m_cmbApproveState.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "节目管理", "Program Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbApproveState.GetLBText(nSel, m_lpProgram->szApprove);
	strcpy(m_lpProgram->szApproveRemarks, m_sApproveRemarks);

	char* pInputBuff = NULL;
	DWORD dwInputSize = 0;
	ConvertProgramParamsStruToXml(m_lpProgram, &pInputBuff, dwInputSize);

	CString strCommand;
	strCommand.Format("PUT /ISAPI/Publish/ProgramMgr/program/%d\r\n", m_dwProgramID);
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	struInputParam.lpInBuffer = pInputBuff;
	struInputParam.dwInBufferSize = dwInputSize;
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		delete[] pInputBuff;
		pInputBuff = NULL;
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");

	delete[] pInputBuff;
	pInputBuff = NULL;

	UpdateData(FALSE);
}

BOOL CDlgInfoDiffusionProgram::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitProgramListCtrl();
	InitPageListCtrl();
	InitContentListCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInfoDiffusionProgram::OnRclickListContent(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if (m_nCurSelPage < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请选择页面", "Please choose a page first.");
		g_StringLanType(szLan2, "节目管理", "Program Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}

	CMenu menu;
	menu.LoadMenu(IDR_MENU_CONTENT);
	if (!menu.m_hMenu)
	{
		return;
	}
	CMenu* pSubMenu = NULL;
	POSITION pos = m_listContent.GetFirstSelectedItemPosition();
	if (pos)
	{
		pSubMenu = menu.GetSubMenu(1);
	}
	else
	{
		pSubMenu = menu.GetSubMenu(0);
	}
	if (pSubMenu == NULL)
	{
		return;
	}
	CPoint ptCursor;
	::GetCursorPos(&ptCursor);
	pSubMenu->TrackPopupMenu(TPM_LEFTBUTTON, ptCursor.x, ptCursor.y, this);
	
	*pResult = 0;
}

void CDlgInfoDiffusionProgram::OnDblclkListContent(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnMenuitemMod();
	
	*pResult = 0;
}

void CDlgInfoDiffusionProgram::OnMenuitemAdd() 
{
	// TODO: Add your command handler code here
	if (m_nCurSelPage < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请选择页面", "Please choose a page first.");
		g_StringLanType(szLan2, "节目管理", "Program Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	CDlgInfoDiffusionContent dlg;
	if (IDOK != dlg.DoModal())
	{
		return;
	}
	LPNET_DVR_CONTENT lpContent = NULL;
	int nContentIndex = -1;
	for (int nContentCnt = 0; nContentCnt < MAX_CONTENTS_A_PAGE; nContentCnt++)
	{
		lpContent = &m_lpProgram->struPageList.struPageList[m_nCurSelPage].struContentList[nContentCnt];
		if (0 == lpContent->dwContentID)
		{
			nContentIndex = nContentCnt;
			break;
		}
	}
	if (nContentIndex < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "窗口数量已达上限", "The number of window is limited.");
		g_StringLanType(szLan2, "节目管理", "Program Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	dlg.GetContent(lpContent);
	lpContent->dwContentID = nContentIndex+1;
	CString str;
	str.Format("%d", nContentIndex+1);
	m_listContent.InsertItem(nContentIndex, str);
	m_listContent.SetItemState(m_nCurContent, 0, -1);
	m_listContent.SetItemState(nContentIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_listContent.SetFocus();
	RefreshContentItem(m_nCurSelPage, nContentIndex);
}

void CDlgInfoDiffusionProgram::OnMenuitemDel() 
{
	// TODO: Add your command handler code here
	if (m_nCurSelPage < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请选择页面", "Please choose a page first.");
		g_StringLanType(szLan2, "节目管理", "Program Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	POSITION pos = m_listContent.GetFirstSelectedItemPosition();
	if (pos)
	{
		int nCurContent = m_listContent.GetNextSelectedItem(pos);
		for (int nContentCnt = nCurContent; nContentCnt < m_listContent.GetItemCount()-1; nContentCnt++)
		{
			m_listContent.SetItemText(nContentCnt, 1, m_listContent.GetItemText(nContentCnt+1, 1));
			m_listContent.SetItemText(nContentCnt, 2, m_listContent.GetItemText(nContentCnt+1, 2));
			m_listContent.SetItemText(nContentCnt, 3, m_listContent.GetItemText(nContentCnt+1, 3));
			m_listContent.SetItemText(nContentCnt, 4, m_listContent.GetItemText(nContentCnt+1, 4));
			m_listContent.SetItemText(nContentCnt, 5, m_listContent.GetItemText(nContentCnt+1, 5));
			m_listContent.SetItemText(nContentCnt, 6, m_listContent.GetItemText(nContentCnt+1, 6));
			memcpy(&m_lpProgram->struPageList.struPageList[m_nCurSelPage].struContentList[nContentCnt],
				&m_lpProgram->struPageList.struPageList[m_nCurSelPage].struContentList[nCurContent+1], sizeof(NET_DVR_CONTENT));
			m_lpProgram->struPageList.struPageList[m_nCurSelPage].struContentList[nCurContent].dwContentID = nContentCnt+1;
		}
		memset(&m_lpProgram->struPageList.struPageList[m_nCurSelPage].struContentList[m_listContent.GetItemCount()-1], 0, sizeof(NET_DVR_CONTENT));
		m_listContent.DeleteItem(m_listContent.GetItemCount()-1);
		m_nCurContent = -1;
	}
}

void CDlgInfoDiffusionProgram::OnMenuitemMod() 
{
	// TODO: Add your command handler code here
	if (m_nCurSelPage < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请选择页面", "Please choose a page first.");
		g_StringLanType(szLan2, "节目管理", "Program Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	POSITION pos = m_listContent.GetFirstSelectedItemPosition();
	if (pos)
	{
		int nCurContent = m_listContent.GetNextSelectedItem(pos);
		CDlgInfoDiffusionContent dlg;
		dlg.SetContent(&m_lpProgram->struPageList.struPageList[m_nCurSelPage].struContentList[nCurContent]);
		if (IDOK != dlg.DoModal())
		{
			return;
		}
		dlg.GetContent(&m_lpProgram->struPageList.struPageList[m_nCurSelPage].struContentList[nCurContent]);
		RefreshContentItem(m_nCurSelPage, nCurContent);
	}
}

void CDlgInfoDiffusionProgram::OnClickListPage(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listPage.GetFirstSelectedItemPosition();
	if (pos)
	{
		m_nCurSelPage = m_listPage.GetNextSelectedItem(pos);
		m_dwPageID = m_lpProgram->struPageList.struPageList[m_nCurSelPage].dwPageID;
		m_sPageName = m_lpProgram->struPageList.struPageList[m_nCurSelPage].struBasicInfo.sPageName;
		m_cmbPlayMode.SetCurSel(m_cmbPlayMode.FindString(-1, m_lpProgram->struPageList.struPageList[m_nCurSelPage].struBasicInfo.sPlayMode));
		OnSelchangeComboPlayMode();
		m_dwPlayDuration = m_lpProgram->struPageList.struPageList[m_nCurSelPage].struBasicInfo.dwPlayDuration;
		m_dwSwitchDuration = m_lpProgram->struPageList.struPageList[m_nCurSelPage].struBasicInfo.dwSwitchDuraton;
		m_cmbSwitchEffect.SetCurSel(m_cmbSwitchEffect.FindString(-1, m_lpProgram->struPageList.struPageList[m_nCurSelPage].struBasicInfo.szSwitchEffect));
		m_dwRed = m_lpProgram->struPageList.struPageList[m_nCurSelPage].struBasicInfo.struBkColor.dwRed;
		m_dwGreen = m_lpProgram->struPageList.struPageList[m_nCurSelPage].struBasicInfo.struBkColor.dwGreen;
		m_dwBlue = m_lpProgram->struPageList.struPageList[m_nCurSelPage].struBasicInfo.struBkColor.dwBlue;
        m_dwBackgroundPic = m_lpProgram->struPageList.struPageList[m_nCurSelPage].struBasicInfo.dwBackgroundPic;
		RefreshContentList(m_nCurSelPage);
		UpdateData(FALSE);
	}
	
	*pResult = 0;
}

void CDlgInfoDiffusionProgram::InitProgramListCtrl()
{
	DWORD dwExStyle = m_listProgram.GetExtendedStyle();
	dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_listProgram.SetExtendedStyle(dwExStyle);
	
	char szLan[512] = {0};
	g_StringLanType(szLan, "序号", "Index");
	m_listProgram.InsertColumn(0, szLan);
	m_listProgram.SetColumnWidth(0, 40);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "节目编号", "Program No.");
	m_listProgram.InsertColumn(1, szLan);
	m_listProgram.SetColumnWidth(1, 60);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "节目名称", "Program Name");
	m_listProgram.InsertColumn(2, szLan);
	m_listProgram.SetColumnWidth(2, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "共享属性", "Share Property");
	m_listProgram.InsertColumn(3, szLan);
	m_listProgram.SetColumnWidth(3, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "审核状态", "Approve State");
	m_listProgram.InsertColumn(4, szLan);
	m_listProgram.SetColumnWidth(4, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "审核意见", "Approve Opinion");
	m_listProgram.InsertColumn(5, szLan);
	m_listProgram.SetColumnWidth(5, 200);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "图像宽度", "Image Width");
	m_listProgram.InsertColumn(6, szLan);
	m_listProgram.SetColumnWidth(6, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "图像高度", "Image Height");
	m_listProgram.InsertColumn(7, szLan);
	m_listProgram.SetColumnWidth(7, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "节目大小", "Program Size");
	m_listProgram.InsertColumn(8, szLan);
	m_listProgram.SetColumnWidth(8, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "节目时长", "Program Duration");
	m_listProgram.InsertColumn(9, szLan);
	m_listProgram.SetColumnWidth(9, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "备注", "Remarks");
	m_listProgram.InsertColumn(10, szLan);
	m_listProgram.SetColumnWidth(10, 400);
}

void CDlgInfoDiffusionProgram::InitPageListCtrl()
{
	DWORD dwExStyle = m_listPage.GetExtendedStyle();
	dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_listPage.SetExtendedStyle(dwExStyle);
	
	char szLan[512] = {0};
	g_StringLanType(szLan, "序号", "Index");
	m_listPage.InsertColumn(0, szLan);
	m_listPage.SetColumnWidth(0, 60);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "页面编号", "Page No.");
	m_listPage.InsertColumn(1, szLan);
	m_listPage.SetColumnWidth(1, 60);

	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "页面名称", "Page Name");
	m_listPage.InsertColumn(2, szLan);
	m_listPage.SetColumnWidth(2, 80);

	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "播放模式", "Play Mode");
	m_listPage.InsertColumn(3, szLan);
	m_listPage.SetColumnWidth(3, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "播放时间", "Play Duration");
	m_listPage.InsertColumn(4, szLan);
	m_listPage.SetColumnWidth(4, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "切换时间", "Switch Duration");
	m_listPage.InsertColumn(5, szLan);
	m_listPage.SetColumnWidth(5, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "切换效果", "Switch Effect");
	m_listPage.InsertColumn(6, szLan);
	m_listPage.SetColumnWidth(6, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "红色", "Red");
	m_listPage.InsertColumn(7, szLan);
	m_listPage.SetColumnWidth(7, 40);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "绿色", "Green");
	m_listPage.InsertColumn(8, szLan);
	m_listPage.SetColumnWidth(8, 40);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "蓝色", "Blue");
	m_listPage.InsertColumn(9, szLan);
	m_listPage.SetColumnWidth(9, 40);

	memset(szLan,0,sizeof(szLan));
	g_StringLanType(szLan,"背景图","BackGround Pic");
	m_listPage.InsertColumn(10,szLan);
	m_listPage.SetColumnWidth(10,40);
}

void CDlgInfoDiffusionProgram::InitContentListCtrl()
{
	DWORD dwExStyle = m_listContent.GetExtendedStyle();
	dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_listContent.SetExtendedStyle(dwExStyle);
	
	char szLan[512] = {0};
	g_StringLanType(szLan, "序号", "Index");
	m_listContent.InsertColumn(0, szLan);
	m_listContent.SetColumnWidth(0, 40);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "X坐标", "X");
	m_listContent.InsertColumn(1, szLan);
	m_listContent.SetColumnWidth(1, 60);

	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "Y坐标", "Y");
	m_listContent.InsertColumn(2, szLan);
	m_listContent.SetColumnWidth(2, 60);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "宽度", "Width");
	m_listContent.InsertColumn(3, szLan);
	m_listContent.SetColumnWidth(3, 60);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "高度", "Height");
	m_listContent.InsertColumn(4, szLan);
	m_listContent.SetColumnWidth(4, 80);

	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "图层号", "Layer No.");
	m_listContent.InsertColumn(5, szLan);
	m_listContent.SetColumnWidth(5, 60);

	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "窗口素材类型", "Window Material Type");
	m_listContent.InsertColumn(6, szLan);
	m_listContent.SetColumnWidth(6, 100);

	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "静态素材类型", "Static Material Type");
	m_listContent.InsertColumn(7, szLan);
	m_listContent.SetColumnWidth(7, 100);
}

void CDlgInfoDiffusionProgram::RefreshProgramItem(int nProgramIndex)
{
	if (nProgramIndex < 0 || nProgramIndex >= MAX_NUM_PROGRAM)
	{
		return;
	}
	CString str;
	str.Format("%d", m_lpResult->struProgramList[nProgramIndex].dwProgramID);
	m_listProgram.SetItemText(nProgramIndex ,1, str);
	m_listProgram.SetItemText(nProgramIndex, 2, m_lpResult->struProgramList[nProgramIndex].szProgramName);
	m_listProgram.SetItemText(nProgramIndex, 3, m_lpResult->struProgramList[nProgramIndex].szShareProp);
	m_listProgram.SetItemText(nProgramIndex, 4, m_lpResult->struProgramList[nProgramIndex].szApprove);
	m_listProgram.SetItemText(nProgramIndex, 5, m_lpResult->struProgramList[nProgramIndex].szApproveRemarks);
	str.Format("%d", m_lpResult->struProgramList[nProgramIndex].struResolution.dwImageWidth);
	m_listProgram.SetItemText(nProgramIndex, 6, str);
	str.Format("%d", m_lpResult->struProgramList[nProgramIndex].struResolution.dwImageHeight);
	m_listProgram.SetItemText(nProgramIndex, 7, str);
	str.Format("%d", m_lpResult->struProgramList[nProgramIndex].dwProgramSize);
	m_listProgram.SetItemText(nProgramIndex, 8, str);
	str.Format("%d", m_lpResult->struProgramList[nProgramIndex].dwProgramLength);
	m_listProgram.SetItemText(nProgramIndex, 9, str);
	m_listProgram.SetItemText(nProgramIndex, 10, m_lpResult->struProgramList[nProgramIndex].szProgramRemarks);
}

void CDlgInfoDiffusionProgram::RefreshProgramList()
{
	m_listProgram.DeleteAllItems();
	for (int nProgramCnt = 0; nProgramCnt < m_lpResult->dwNumOfMatches; nProgramCnt++)
	{
		if (0 == m_lpResult->struProgramList[nProgramCnt].dwProgramID)
		{
			break;
		}
		CString str;
		str.Format("%d", nProgramCnt+1);
		m_listProgram.InsertItem(nProgramCnt, str);
		RefreshProgramItem(nProgramCnt);
	}
}

void CDlgInfoDiffusionProgram::UpdateProgramInfo()
{
	m_dwProgramID = m_lpProgram->dwProgramID;
	m_szProgramName = m_lpProgram->szProgramName;
	m_szProgramRemarks = m_lpProgram->szProgramRemarks;
	m_cmbShareProp.SetCurSel(m_cmbShareProp.FindString(-1, m_lpProgram->szShareProp));
	m_dwImageWidth = m_lpProgram->struResolution.dwImageWidth;
	m_dwImageHeight = m_lpProgram->struResolution.dwImageHeight;
	m_cmbApproveState.SetCurSel(m_cmbApproveState.FindString(-1, m_lpProgram->szApprove));
	m_sApproveRemarks = m_lpProgram->szApproveRemarks;
	UpdateData(FALSE);
}

void CDlgInfoDiffusionProgram::RefreshPageItem(int nPageIndex)
{
	if (nPageIndex < 0 || nPageIndex >= MAX_PAGES_A_PROGRAM)
	{
		return;
	}
	LPNET_DVR_PAGE lpPage = &m_lpProgram->struPageList.struPageList[nPageIndex];
	CString str;
	str.Format("%d", lpPage->dwPageID);
	m_listPage.SetItemText(nPageIndex, 1, str);
	m_listPage.SetItemText(nPageIndex, 2, lpPage->struBasicInfo.sPageName);
	m_listPage.SetItemText(nPageIndex, 3, lpPage->struBasicInfo.sPlayMode);
	str.Format("%d", lpPage->struBasicInfo.dwPlayDuration);
	m_listPage.SetItemText(nPageIndex, 4, str);
	str.Format("%d", lpPage->struBasicInfo.dwSwitchDuraton);
	m_listPage.SetItemText(nPageIndex, 5, str);
	m_listPage.SetItemText(nPageIndex, 6, lpPage->struBasicInfo.szSwitchEffect);
	str.Format("%d", lpPage->struBasicInfo.struBkColor.dwRed);
	m_listPage.SetItemText(nPageIndex, 7, str);
	str.Format("%d", lpPage->struBasicInfo.struBkColor.dwGreen);
	m_listPage.SetItemText(nPageIndex, 8, str);
	str.Format("%d", lpPage->struBasicInfo.struBkColor.dwBlue);
	m_listPage.SetItemText(nPageIndex, 9, str);
	str.Format("%d",lpPage->struBasicInfo.dwBackgroundPic);
	m_listPage.SetItemText(nPageIndex,10,str);
}

void CDlgInfoDiffusionProgram::RefreshPageList()
{
	m_listPage.DeleteAllItems();
	for (int nPageCnt = 0; nPageCnt < MAX_PAGES_A_PROGRAM; nPageCnt++)
	{
		if (0 == m_lpProgram->struPageList.struPageList[nPageCnt].dwPageID)
		{
			break;
		}
		CString str;
		str.Format("%d", nPageCnt+1);
		m_listPage.InsertItem(nPageCnt, str);
		RefreshPageItem(nPageCnt);
	}
}

void CDlgInfoDiffusionProgram::RefreshContentItem(int nPageIndex, int nContentIndex)
{
	if (nPageIndex < 0 || nPageIndex >= MAX_PAGES_A_PROGRAM \
		|| nContentIndex < 0 || nContentIndex >= MAX_CONTENTS_A_PAGE)
	{
		return;
	}
	LPNET_DVR_CONTENT lpContent = &m_lpProgram->struPageList.struPageList[nPageIndex].struContentList[nContentIndex];
	CString str;
	str.Format("%d", lpContent->struPosition.dwPositionX);
	m_listContent.SetItemText(nContentIndex, 1, str);
	str.Format("%d", lpContent->struPosition.dwPositionY);
	m_listContent.SetItemText(nContentIndex, 2, str);
	str.Format("%d", lpContent->struPosition.dwWidth);
	m_listContent.SetItemText(nContentIndex, 3, str);
	str.Format("%d", lpContent->struPosition.dwHeight);
	m_listContent.SetItemText(nContentIndex, 4, str);
	str.Format("%d", lpContent->dwLayerID);
	m_listContent.SetItemText(nContentIndex, 5, str);
	m_listContent.SetItemText(nContentIndex, 6, lpContent->sWinMaterialType);
	m_listContent.SetItemText(nContentIndex, 7, lpContent->sStaticMaterialType);
}

void CDlgInfoDiffusionProgram::RefreshContentList(int nPageIndex)
{
	if (nPageIndex < 0 || nPageIndex >= MAX_PAGES_A_PROGRAM)
	{
		return;
	}
	
	m_listContent.DeleteAllItems();
	LPNET_DVR_CONTENT lpContent = NULL;
	for (int nContentCnt = 0; nContentCnt < MAX_CONTENTS_A_PAGE; nContentCnt++)
	{
		if (0 == m_lpProgram->struPageList.struPageList[nPageIndex].struContentList[nContentCnt].dwContentID)
		{
			break;
		}
		CString str;
		str.Format("%d", nContentCnt+1);
		m_listContent.InsertItem(nContentCnt, str);
		RefreshContentItem(m_nCurSelPage, nContentCnt);
	}
}

void CDlgInfoDiffusionProgram::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_lpProgram)
	{
		delete m_lpProgram;
		m_lpProgram = NULL;
	}
	if (m_lpResult)
	{
		delete m_lpResult;
		m_lpResult = NULL;
	}
	if (m_pOutputXmlBuffer)
	{
		delete[] m_pOutputXmlBuffer;
		m_pOutputXmlBuffer = NULL;
	}
}

void CDlgInfoDiffusionProgram::OnBtnProSearch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	strcpy(m_struDescription.sSearchID, m_sSearchID);
	int nSel = m_cmbProApproveState.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "节目查询", "Schedule Search");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbProApproveState.GetLBText(nSel, m_struDescription.sApproveState);
	nSel = m_cmbProShareProp.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "节目查询", "Schedule Search");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbProShareProp.GetLBText(nSel, m_struDescription.sShareProperty);
	strcpy(m_struDescription.sUploader, m_sUploader);
	m_struDescription.struResolution.dwImageWidth = m_dwProImageWitdth;
	m_struDescription.struResolution.dwImageHeight = m_dwProImageHeight;
	m_struDescription.struTimeRange.struBeginTime.dwYear = m_tmStartDate.GetYear();
	m_struDescription.struTimeRange.struBeginTime.dwMonth = m_tmStartDate.GetMonth();
	m_struDescription.struTimeRange.struBeginTime.dwDay = m_tmStartDate.GetDay();
	m_struDescription.struTimeRange.struBeginTime.dwHour = m_tmStartTime.GetHour();
	m_struDescription.struTimeRange.struBeginTime.dwMinute = m_tmStartTime.GetMinute();
	m_struDescription.struTimeRange.struBeginTime.dwSecond = m_tmStartTime.GetSecond();
	m_struDescription.struTimeRange.struEndTime.dwYear = m_tmEndDate.GetYear();
	m_struDescription.struTimeRange.struEndTime.dwMonth = m_tmEndDate.GetMonth();
	m_struDescription.struTimeRange.struEndTime.dwDay = m_tmEndDate.GetDay();
	m_struDescription.struTimeRange.struEndTime.dwHour = m_tmEndTime.GetHour();
	m_struDescription.struTimeRange.struEndTime.dwMinute = m_tmEndTime.GetMinute();
	m_struDescription.struTimeRange.struEndTime.dwSecond = m_tmEndTime.GetSecond();
	m_struDescription.dwMaxResults = m_dwMaxResults;
	m_struDescription.dwSearchResultsPosition = m_dwStartPosition;
	
	char* pInputBuff = NULL;
	DWORD dwInputSize = 0;
	ConvertProgramSearchDescriptionParamsStruToXml(&m_struDescription, &pInputBuff, dwInputSize);
	
	CString strCommand;
	strCommand.Format("POST /ISAPI/Publish/ProgramMgr/programSearch\r\n");
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	struInputParam.lpInBuffer = pInputBuff;
	struInputParam.dwInBufferSize = dwInputSize;
	
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	memset(m_pOutputXmlBuffer, 0, MAX_LEN_XML);
	struOutputParam.lpOutBuffer = m_pOutputXmlBuffer;
	struOutputParam.dwOutBufferSize = MAX_LEN_XML;
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		delete[] pInputBuff;
		pInputBuff = NULL;
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	memset(m_lpResult, 0, sizeof(*m_lpResult));
	ConvertProgramSearchResultParamsXmlToStru(m_pOutputXmlBuffer, m_lpResult);
	RefreshProgramList();
	
	delete[] pInputBuff;
	pInputBuff = NULL;
}

void CDlgInfoDiffusionProgram::OnSelchangeComboPlayMode() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbPlayMode.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	CString strPlayMode;
	m_cmbPlayMode.GetLBText(nSel, strPlayMode);
	if (0 == strPlayMode.Compare("selfDefine"))
	{
		GetDlgItem(IDC_EDIT_PLAY_DURATION)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_PLAY_DURATION)->EnableWindow(FALSE);
	}
}


void CDlgInfoDiffusionProgram::OnBnClickedBtnDelMore()
{
    // TODO:  在此添加控件通知处理程序代码
    
    POSITION pos = m_listProgram.GetFirstSelectedItemPosition();
    if (pos == NULL)
    {
        return;
    }
    else
    {
        m_nCountId = 0;
        memset(m_nArrayId, 0, MAX_ID);
        int arry[MAX_ID] = { 0 };
        while (pos)
        {
            int nItem = m_listProgram.GetNextSelectedItem(pos);
            CString strid = m_listProgram.GetItemText(nItem, 1);
            int intId = atoi(strid);
            m_nArrayId[m_nCountId] = intId;
            m_nCountId++;
            arry[m_nCountId] = nItem;
            //m_listProgram.DeleteItem(nItem);
        }
       
    }
    char* pInputBuff = NULL;
    DWORD dwInputSize = 0;
    if (!ConvertProgramIdToXml(m_nArrayId, m_nCountId, &pInputBuff, dwInputSize))
    {
        if (pInputBuff != NULL)
        {
            delete[] pInputBuff;
            pInputBuff = NULL;
        }
        return;
    }
    CString strCommand;
    strCommand.Format("DELETE /ISAPI/Publish/ProgramMgr/program\r\n");
    NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
    struInputParam.dwRequestUrlLen = strCommand.GetLength();
     struInputParam.lpInBuffer = pInputBuff;
    struInputParam.dwInBufferSize = dwInputSize;

    char szStatusBuff[1024] = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT struOutputParam = { 0 };
    struOutputParam.dwSize = sizeof(struOutputParam);
    struOutputParam.lpStatusBuffer = szStatusBuff;
    struOutputParam.dwStatusSize = sizeof(szStatusBuff);

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        if (pInputBuff != NULL)
        {
            delete[] pInputBuff;
            pInputBuff = NULL;
        }
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");


    if (pInputBuff != NULL)
    {
        delete[] pInputBuff;
        pInputBuff = NULL;
    }
    
    UpdateData(FALSE);
}



void CDlgInfoDiffusionProgram::OnLvnItemchangedListPage(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    // TODO:  在此添加控件通知处理程序代码
    *pResult = 0;
}


void CDlgInfoDiffusionProgram::OnBnClickedBtnBatcgSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    POSITION pos = m_listProgram.GetFirstSelectedItemPosition();
    if (pos == NULL)
    {
        return;
    }
    else
    {
        m_nCountId = 0;
        memset(m_nArrayId, 0, MAX_ID);
        int arry[MAX_ID] = { 0 };
        while (pos)
        {
            int nItem = m_listProgram.GetNextSelectedItem(pos);
            CString strid = m_listProgram.GetItemText(nItem, 1);
            int intId = atoi(strid);
            m_nArrayId[m_nCountId] = intId;
            m_nCountId++;
            arry[m_nCountId] = nItem;
        }
    }
    int nSel = m_comOperatorType.GetCurSel();
    if (nSel == CB_ERR)
    {
        char szLan1[512] = { 0 };
        char szLan2[512] = { 0 };
        g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
        g_StringLanType(szLan2, "节目管理", "Material Management");
        MessageBox(szLan1, szLan2, MB_ICONWARNING);
        return;
    }
    m_comOperatorType.GetLBText(nSel, m_lpProgram->szOperatorType);

    if (!strcmp(m_lpProgram->szOperatorType, "remark"))
    {
        strcpy(m_lpProgram->szProgramRemarks, m_szProgramRemarks);
    }
    else if (!strcmp(m_lpProgram->szOperatorType, "property"))
    {

        nSel = m_cmbShareProp.GetCurSel();
        if (nSel == CB_ERR)
        {
            char szLan1[512] = { 0 };
            char szLan2[512] = { 0 };
            g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
            g_StringLanType(szLan2, "节目管理", "Material Management");
            MessageBox(szLan1, szLan2, MB_ICONWARNING);
            return;
        }
        m_cmbShareProp.GetLBText(nSel, m_lpProgram->szShareProp);
    }
    else if (!strcmp(m_lpProgram->szOperatorType, "approve"))
    {

        nSel = m_cmbApproveState.GetCurSel();
        if (nSel == CB_ERR)
        {
            char szLan1[512] = { 0 };
            char szLan2[512] = { 0 };
            g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
            g_StringLanType(szLan2, "节目管理", "Material Management");
            MessageBox(szLan1, szLan2, MB_ICONWARNING);
            return;
        }
        m_cmbApproveState.GetLBText(nSel, m_lpProgram->szApprove);
        strcpy(m_lpProgram->szApproveRemarks, m_sApproveRemarks);
    }
    char* pInputBuff = NULL;
    DWORD dwInputSize = 0;
    if (!(ConvertProgramBatchInfoToXml(m_nArrayId, m_nCountId, m_lpProgram, &pInputBuff, dwInputSize)))
    {
        if (pInputBuff != NULL)
        {
            delete[] pInputBuff;
            pInputBuff = NULL;
        }
        return;
    }

    CString strCommand;
    strCommand.Format("PUT /ISAPI/Publish/ProgramMgr/programBatchInfo\r\n");
    NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
    struInputParam.dwRequestUrlLen = strCommand.GetLength();
    struInputParam.lpInBuffer = pInputBuff;
    struInputParam.dwInBufferSize = dwInputSize;

    char szStatusBuff[1024] = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT struOutputParam = { 0 };
    struOutputParam.dwSize = sizeof(struOutputParam);
    struOutputParam.lpStatusBuffer = szStatusBuff;
    struOutputParam.dwStatusSize = sizeof(szStatusBuff);

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        if (pInputBuff != NULL)
        {
            delete[] pInputBuff;
            pInputBuff = NULL;
        }
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");

    if (pInputBuff != NULL)
    {
        delete[] pInputBuff;
        pInputBuff = NULL;
    }
    return;
}
