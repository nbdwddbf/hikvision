// DlgVcaBlackList.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaBlackList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBlackList dialog
CDlgVcaBlackList *g_pVcaBlackList = NULL;
UINT GetBlackListThread(LPVOID pParam)
{
	
    UNREFERENCED_PARAMETER(pParam);
	
	LONG bRet = -1;
	NET_VCA_BLACKLIST_INFO struBlackListData;
    memset(&struBlackListData, 0, sizeof(struBlackListData));
	CString csTmp;
	char szLan[128] = {0};
	while (1) 
	{
		bRet = NET_DVR_FindNextBlackList(g_pVcaBlackList->m_lFindHandle, &struBlackListData);
        if (bRet == NET_DVR_FILE_SUCCESS)
		{
			csTmp.Format("%d", g_pVcaBlackList->m_lBlackListNum+1);
			g_pVcaBlackList->m_listBlackList.InsertItem(g_pVcaBlackList->m_lBlackListNum, csTmp,0);

			switch (struBlackListData.byType)
			{
			case 0:
				g_StringLanType(szLan, "全部", "ALL");
				break;
			case 1:
				g_StringLanType(szLan, "白名单", "White list");
				break;
			case 2:
				g_StringLanType(szLan, "黑名单", "Black list");
				break;
			default:
                g_StringLanType(szLan, "未知", "Unknow");
				break;
			}
            csTmp.Format("%s", szLan);
			g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 1, csTmp);

            csTmp.Format("%s", struBlackListData.struAttribute.byName);
			g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 2, csTmp);

			switch (struBlackListData.struAttribute.bySex)
			{
			case 0:
				g_StringLanType(szLan, "无", "No");
				break;
			case 1:
				g_StringLanType(szLan, "男", "Man");
				break;
			case 2:
				g_StringLanType(szLan, "女", "Woman");
				break;
			default:
                g_StringLanType(szLan, "未知", "Unknow");
				break;
			}
			csTmp.Format("%s", szLan);
			g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 3, csTmp);

			csTmp.Format("%s", struBlackListData.struAttribute.byBirthDate);
			g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 4, csTmp);

			csTmp.Format("%d", struBlackListData.struAttribute.struNativePlace.wCityID);
			g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 5, csTmp);

            csTmp.Format("%d", struBlackListData.dwRegisterID);
			g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 6, csTmp);

			csTmp.Format("%d", struBlackListData.dwGroupNo);
			g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 7, csTmp);

			switch (struBlackListData.struAttribute.byCertificateType)
			{
			case 0:
				g_StringLanType(szLan, "无", "No");
				break;
			case 1:
				g_StringLanType(szLan, "身份证", "identification card");
				break;
			case 2:
				g_StringLanType(szLan, "警官证", "Officers card");
				break;
			default:
                g_StringLanType(szLan, "未知", "Unknow");
				break;
			}
			csTmp.Format("%s", szLan);
			g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 8, csTmp);

			csTmp.Format("%s", struBlackListData.struAttribute.byCertificateNumber);
			g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 9, csTmp);

			csTmp.Format("%s", struBlackListData.byRemark);
			g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 10, csTmp);

			switch (struBlackListData.byLevel)
			{
			case 0:
				g_StringLanType(szLan, "全部", "ALL");
				break;
			case 1:
				g_StringLanType(szLan, "低", "LOW");
				break;
			case 2:
				g_StringLanType(szLan, "中", "Middle");
				break;
			case 3:
				g_StringLanType(szLan, "高", "High");
				break;
			default:
                g_StringLanType(szLan, "未知", "Unknow");
				break;
			}
			csTmp.Format("%s", szLan);
			g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 11, csTmp);
			
			g_pVcaBlackList->m_lBlackListNum++;
		}
		else
		{
			if (bRet == NET_DVR_ISFINDING)
			{
				g_pVcaBlackList->GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_SHOW);
				g_pVcaBlackList->GetDlgItem(IDC_STATIC_SEARCH)->SetWindowText("Searching......");
				Sleep(5);
				continue;
			}
			if ((bRet == NET_DVR_NOMOREFILE) || (bRet == NET_DVR_FILE_NOFIND))
			{
				g_StringLanType(szLan, "搜索", "search");
				g_pVcaBlackList->GetDlgItem(IDC_BTN_SEARCH)->SetWindowText(szLan);
				//				g_pPDCInfoSearch->m_bSearch = FALSE;
				g_pVcaBlackList->GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_HIDE);
				g_StringLanType(szLan, "搜索黑名单结束!", "Search blacklist Ending");
				AfxMessageBox(szLan);
				break;
			}
			else
			{
				g_StringLanType(szLan, "搜索", "Search");
				g_pVcaBlackList->GetDlgItem(IDC_BTN_SEARCH)->SetWindowText(szLan);
				//				g_pPDCInfoSearch->m_bSearch = FALSE;
				g_StringLanType(szLan, "由于服务器忙,或网络故障,搜索异常终止!",\
					"Since the server is busy, or network failure, search abnormal termination");
				AfxMessageBox(szLan);
				break;
			}
		}
	}
	CloseHandle(g_pVcaBlackList->m_hFindThread);
	g_pVcaBlackList->m_hFindThread = NULL;
	NET_DVR_FindBlackListClose(g_pVcaBlackList->m_lFindHandle);
	
	return 0;
}


CDlgVcaBlackList::CDlgVcaBlackList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaBlackList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaBlackList)
	m_csCertificateNumber = _T("");
	m_dwGroupID = 0;
	m_csName = _T("");
	m_csRemark = _T("");
	m_dwRegisterID = 0;
	m_csBirthDate = _T("");
	m_csFastRegPicPath = _T("");
	m_bChkImportPicModel = FALSE;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_lChannel  = -1;
    m_iDevIndex = -1;
	m_lFindHandle = -1;
	m_hFindThread = NULL;
	m_lBlackListNum = 0;
	memset(&m_struBlackListPara, 0, sizeof(m_struBlackListPara));
	memset(&m_struBlackListPic, 0, sizeof(m_struBlackListPic));
	memset(&m_struBlFastPara, 0, sizeof(m_struBlFastPara));
}


void CDlgVcaBlackList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaBlackList)
	DDX_Control(pDX, IDC_COMBO_LEVEL, m_comboLevel);
	DDX_Control(pDX, IDC_LIST_BLACKLIST, m_listBlackList);
	DDX_Control(pDX, IDC_COMBO_NATIVE_PLACE, m_comboNativePlace);
	DDX_Control(pDX, IDC_COMBO_CERFITICATE_TYPE, m_comboCerfiticateType);
	DDX_Control(pDX, IDC_COMBO_BLACKLIST_TYPE, m_comboBlackListType);
	DDX_Control(pDX, IDC_COMBO_SEX, m_comboSex);
	DDX_Text(pDX, IDC_EDIT_CERTIFICATE_NUMBER, m_csCertificateNumber);
	DDX_Text(pDX, IDC_EDIT_GROUP, m_dwGroupID);
	DDX_Text(pDX, IDC_EDIT_NAME, m_csName);
	DDX_Text(pDX, IDC_EDIT_REMARK, m_csRemark);
	DDX_Text(pDX, IDC_EDIT_REGISTER_ID, m_dwRegisterID);
	DDX_Text(pDX, IDC_EDIT_BIRTHDATE, m_csBirthDate);
	DDX_Text(pDX, IDC_EDIT_FASTREGISTER_PICPATH, m_csFastRegPicPath);
	DDX_Check(pDX, IDC_CHK_IMPORT_PIC_MODEL, m_bChkImportPicModel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaBlackList, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaBlackList)
	ON_BN_CLICKED(IDC_BTN_REGISTER, OnBtnRegister)
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BLACKLIST, OnDblclkListBlacklist)
	ON_BN_CLICKED(IDC_BTN_UPDATE, OnBtnUpdate)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	ON_BN_CLICKED(IDC_BTN_GET_BLACKLIST_PIC, OnBtnGetBlacklistPic)
	ON_BN_CLICKED(IDC_BTN_FAST_SCAN, OnBtnFastScan)
	ON_BN_CLICKED(IDC_BTN_FAST_REGISTER, OnBtnFastRegister)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBlackList message handlers
BOOL CDlgVcaBlackList::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_comboBlackListType.SetCurSel(0);
	m_comboCerfiticateType.SetCurSel(0);
	m_comboNativePlace.SetCurSel(0);
	m_comboSex.SetCurSel(0);
	m_comboLevel.SetCurSel(0);

	g_pVcaBlackList = this;

	char szLan[128] = {0};
    
    m_listBlackList.SetExtendedStyle(m_listBlackList.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLan, "序号", "NO.");
    m_listBlackList.InsertColumn(0, szLan, LVCFMT_RIGHT, 60, -1);
	g_StringLanType(szLan, "类型", "Type");
	m_listBlackList.InsertColumn(1, szLan, LVCFMT_LEFT, 80, -1);
	g_StringLanType(szLan, "姓名", "Name");
    m_listBlackList.InsertColumn(2, szLan, LVCFMT_LEFT, 80, -1);
	g_StringLanType(szLan, "性别", "Sex");
    m_listBlackList.InsertColumn(3, szLan, LVCFMT_LEFT,60, -1);
    g_StringLanType(szLan, "出生年月", "Age");
    m_listBlackList.InsertColumn(4, szLan, LVCFMT_LEFT, 80, -1);   
	g_StringLanType(szLan, "籍贯", "Native Place");
	m_listBlackList.InsertColumn(5, szLan, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLan, "黑名单ID", "BlackList ID");
    m_listBlackList.InsertColumn(6, szLan, LVCFMT_LEFT, 100, -1);
	g_StringLanType(szLan, "分组号", "BlackList Group");
    m_listBlackList.InsertColumn(7, szLan, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLan, "证件类型", "Certificate Type");
	m_listBlackList.InsertColumn(8, szLan, LVCFMT_LEFT, 80, -1);
	g_StringLanType(szLan, "证件号", "NO.");
	m_listBlackList.InsertColumn(9, szLan, LVCFMT_LEFT, 140, -1);
	g_StringLanType(szLan, "备注", "Remark");
	m_listBlackList.InsertColumn(10, szLan, LVCFMT_LEFT, 200, -1);
	g_StringLanType(szLan, "等级", "Level");
	m_listBlackList.InsertColumn(11, szLan, LVCFMT_LEFT, 80, -1);
/*
	CString csTmp;
//	char szLan[128] = {0};
	NET_VCA_BLACKLIST_INFO struBlackListData;
    memset(&struBlackListData, 0, sizeof(struBlackListData));

	csTmp.Format("%d", g_pVcaBlackList->m_lBlackListNum+1);
	g_pVcaBlackList->m_listBlackList.InsertItem(g_pVcaBlackList->m_lBlackListNum, csTmp,0);
	
	switch (struBlackListData.byType)
	{
	case 0:
		g_StringLanType(szLan, "黑名单", "White list");
		break;
	case 1:
		g_StringLanType(szLan, "黑名单", "Black list");
	default:
		g_StringLanType(szLan, "未知", "Unknow");
		break;
	}
	csTmp.Format("%s", szLan);
	g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 1, csTmp);
	
	csTmp.Format("%s", struBlackListData.struAttribute.byName);
	g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 2, csTmp);
	
	switch (struBlackListData.struAttribute.bySex)
	{
	case 0:
		g_StringLanType(szLan, "女", "Man");
		break;
	case 1:
		g_StringLanType(szLan, "女", "Woman");
		break;
	default:
		g_StringLanType(szLan, "未知", "Unknow");
		break;
	}
	csTmp.Format("%s", szLan);
	g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 3, csTmp);
	
	csTmp.Format("%d", 20);
	g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 4, csTmp);
	
	csTmp.Format("%d", struBlackListData.struAttribute.dwNativePlace);
	g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 5, csTmp);
	
	csTmp.Format("%d", 50);
	g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 6, csTmp);
	
	csTmp.Format("%d", 20);
	g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 7, csTmp);
	
	switch (struBlackListData.struAttribute.byCertificateType)
	{
	case 0:
		g_StringLanType(szLan, "警官证", "identification card");
		break;
	case 1:
		g_StringLanType(szLan, "警官证", "Officers card");
		break;
	default:
		g_StringLanType(szLan, "未知", "Unknow");
		break;
	}
	csTmp.Format("%s", szLan);
	g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 8, csTmp);
	
	csTmp.Format("%s", "33012001");
	g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 9, csTmp);
	
	csTmp.Format("%s", "");
	g_pVcaBlackList->m_listBlackList.SetItemText(g_pVcaBlackList->m_lBlackListNum, 10, csTmp);		
*/	
    UpdateData(FALSE);
	
	return TRUE;
}

void CDlgVcaBlackList::GetBlackListInfoFromWnd(NET_VCA_BLACKLIST_INFO& struBlackListInfo)
{
	UpdateData(TRUE);
	memcpy(struBlackListInfo.struAttribute.byBirthDate, m_csBirthDate, MAX_HUMAN_BIRTHDATE_LEN);
	struBlackListInfo.struAttribute.bySex = m_comboSex.GetCurSel();
	struBlackListInfo.struAttribute.byCertificateType = m_comboCerfiticateType.GetCurSel();
	struBlackListInfo.struAttribute.struNativePlace.wCityID = m_comboNativePlace.GetCurSel();
	memcpy(struBlackListInfo.struAttribute.byName, m_csName, NAME_LEN);
	memcpy(struBlackListInfo.struAttribute.byCertificateNumber, m_csCertificateNumber, NAME_LEN);
	struBlackListInfo.dwRegisterID = m_dwRegisterID;
	struBlackListInfo.dwGroupNo = m_dwGroupID;
	struBlackListInfo.byType = m_comboBlackListType.GetCurSel();
	struBlackListInfo.byLevel = m_comboLevel.GetCurSel();
	memcpy(struBlackListInfo.byRemark, m_csRemark, NAME_LEN);
}

void CDlgVcaBlackList::OnBtnRegister() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i=0;
	char szLan[128] = {0};
	memset(&m_struBlackListPara, 0, sizeof(m_struBlackListPara));
	for (i=0; i<MAX_HUMAN_PICTURE_NUM; i++)
	{
        m_struBlackListPara.struRegisterPic[i].pImage = new BYTE[10*1024];
		if (m_struBlackListPara.struRegisterPic[i].pImage == NULL)
		{
			return;
		}
		memset(m_struBlackListPara.struRegisterPic[i].pImage, 0, 10*1024);
		m_struBlackListPara.struRegisterPic[i].pModel = new BYTE[10*1024];
		if (m_struBlackListPara.struRegisterPic[i].pModel == NULL)
		{
			return;
		}
		memset(m_struBlackListPara.struRegisterPic[i].pModel, 0, 10*1024);
	}
	GetBlackListInfoFromWnd(m_struBlackListPara.struBlackListInfo);
	m_struBlackListPara.dwSize = sizeof(m_struBlackListPara);
	for (i=0; i<MAX_HUMAN_PICTURE_NUM; i++)
	{
		if (g_struFaceModel[i].dwFacePicLen>0 && g_struFaceModel[i].dwFaceModelLen>0)
		{
			m_struBlackListPara.struRegisterPic[i].dwImageLen = g_struFaceModel[i].dwFacePicLen;
			m_struBlackListPara.struRegisterPic[i].dwModelLen = g_struFaceModel[i].dwFaceModelLen;
			memcpy(m_struBlackListPara.struRegisterPic[i].pImage, g_struFaceModel[i].byFacePic, g_struFaceModel[i].dwFacePicLen);
			memcpy(m_struBlackListPara.struRegisterPic[i].pModel, g_struFaceModel[i].byModelData, g_struFaceModel[i].dwFaceModelLen);
			m_struBlackListPara.dwRegisterPicNum++;
		}
	}
	if (!NET_DVR_AddBlackList(m_lServerID, m_lChannel, &m_struBlackListPara))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AddBlackList m_lChannel[%d] ",m_lChannel);
        g_StringLanType(szLan, "注册黑名单失败", "Fail to register blacklist");
        AfxMessageBox(szLan);
    }
    else
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AddBlackList m_lChannel[%d] ",m_lChannel);
		g_StringLanType(szLan, "注册黑名单成功", "Succ to register blacklist");
        AfxMessageBox(szLan);
    }

	for (i=0; i<MAX_HUMAN_PICTURE_NUM; i++)
	{
		delete []m_struBlackListPara.struRegisterPic[i].pImage;
		m_struBlackListPara.struRegisterPic[i].pImage = NULL;
		delete []m_struBlackListPara.struRegisterPic[i].pModel;
		m_struBlackListPara.struRegisterPic[i].pModel = NULL;
	}
}

void CDlgVcaBlackList::OnBtnSearch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};

    NET_VCA_BLACKLIST_COND struFindCond = {0};
	struFindCond.dwGroupNo = m_dwGroupID;
	struFindCond.byLevel = m_comboLevel.GetCurSel();
	struFindCond.byType = m_comboBlackListType.GetCurSel();
	struFindCond.lChannel = m_lChannel;
	struFindCond.struAttribute.bySex = m_comboSex.GetCurSel();
	struFindCond.struAttribute.struNativePlace.wCityID = m_comboNativePlace.GetCurSel();
	struFindCond.struAttribute.byCertificateType = m_comboCerfiticateType.GetCurSel();
	memcpy(struFindCond.struAttribute.byCertificateNumber, m_csCertificateNumber, NAME_LEN);
	memcpy(struFindCond.struAttribute.byName, m_csName, NAME_LEN);
	memcpy(struFindCond.struAttribute.byBirthDate, m_csBirthDate, MAX_HUMAN_BIRTHDATE_LEN);

	m_lFindHandle = NET_DVR_FindBlackList(m_lServerID, &struFindCond);
	if (m_lFindHandle < 0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FindBlackList");
		
		g_StringLanType(szLan, "搜索黑名单失败", "Search blacklist failed");
		AfxMessageBox(szLan);
        return;
	}
	else
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_FindBlackList");
		
		g_StringLanType(szLan, "搜索黑名单成功", "Search blacklist successfully");
		AfxMessageBox(szLan);
	}

	m_lBlackListNum = 0;
	m_listBlackList.DeleteAllItems();
	DWORD dwThreadId = 0;
	if (m_hFindThread == NULL)
	{
		m_hFindThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetBlackListThread), this, 0, &dwThreadId);
	}

	if (m_hFindThread  == NULL)
	{
		g_StringLanType(szLan, "打开线程失败", "Open thread failed");
		AfxMessageBox(szLan);
		return;
    }

	g_StringLanType(szLan, "搜索", "search");
	g_pVcaBlackList->GetDlgItem(IDC_BTN_SEARCH)->SetWindowText(szLan);
    
}

void CDlgVcaBlackList::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	int i;
	if (m_hFindThread != NULL)
	{
		TerminateThread(m_hFindThread, 0);
		CloseHandle(m_hFindThread);
		m_hFindThread = NULL;
		NET_DVR_FindBlackListClose(m_lFindHandle);
	}

	for (i=0; i<MAX_HUMAN_PICTURE_NUM; i++)
	{
		g_struFacePic[i].dwImageID = 0;
		g_struFacePic[i].dwFaceScore = 0;
		memset(&g_struFacePic[i].struVcaRect, 0, sizeof(NET_VCA_RECT));
	}

	CDialog::OnCancel();
}

void CDlgVcaBlackList::OnDblclkListBlacklist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iItemSel = 0;
	CString csTxt;
//	CString csTemp;
	char szTemp[128] = {0};
//	DWORD dwDevPort;
	
	POSITION  iPos = m_listBlackList.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
	}
	iItemSel = m_listBlackList.GetNextSelectedItem(iPos);
	csTxt.Format("%s", m_listBlackList.GetItemText(iItemSel, 1));
    strcpy(szTemp, csTxt);
	if (!strcmp(szTemp, "白名单"))
	{
		m_comboBlackListType.SetCurSel(1);
	}
	else if (!strcmp(szTemp, "黑名单"))
	{
		m_comboBlackListType.SetCurSel(2);
	}

	m_csName.Format("%s", m_listBlackList.GetItemText(iItemSel, 2));
	
    csTxt.Format("%s", m_listBlackList.GetItemText(iItemSel, 3));
    strcpy(szTemp, csTxt);
	if (!strcmp(szTemp, "男"))
	{
		m_comboSex.SetCurSel(1);
	}
	else if (!strcmp(szTemp, "女"))
	{
		m_comboSex.SetCurSel(2);
	}
	else
	{
        m_comboSex.SetCurSel(0);
	}

	m_csBirthDate.Format("%s", m_listBlackList.GetItemText(iItemSel, 4));

	csTxt.Format("%s", m_listBlackList.GetItemText(iItemSel, 5));
	m_comboNativePlace.SetCurSel(CStringTodwIP(csTxt));

	csTxt.Format("%s", m_listBlackList.GetItemText(iItemSel, 6));
	m_dwRegisterID = CStringTodwIP(csTxt);

	csTxt.Format("%s", m_listBlackList.GetItemText(iItemSel, 7));
	m_dwGroupID = CStringTodwIP(csTxt);

    csTxt.Format("%s", m_listBlackList.GetItemText(iItemSel, 8));
    strcpy(szTemp, csTxt);
	if (!strcmp(szTemp, "身份证"))
	{
		m_comboCerfiticateType.SetCurSel(1);
	}
	else if (!strcmp(szTemp, "警官证"))
	{
		m_comboCerfiticateType.SetCurSel(2);
	}
	else
	{
        m_comboCerfiticateType.SetCurSel(0);
	}

    m_csCertificateNumber.Format("%s", m_listBlackList.GetItemText(iItemSel, 9));

	m_csRemark.Format("%s", m_listBlackList.GetItemText(iItemSel, 10));

	csTxt.Format("%s", m_listBlackList.GetItemText(iItemSel, 11));
    strcpy(szTemp, csTxt);
	if (!strcmp(szTemp, "高"))
	{
		m_comboLevel.SetCurSel(2);
	}
	else if (!strcmp(szTemp, "中"))
	{
		m_comboLevel.SetCurSel(1);
	}
	else
	{
        m_comboLevel.SetCurSel(0);
	}

	*pResult = 0;
	UpdateData(FALSE);
}

void CDlgVcaBlackList::OnBtnUpdate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i;
	char szLan[128] = {0};
	NET_VCA_BLACKLIST_PARA struBlackListPara = {0};
	for (i=0; i<MAX_HUMAN_PICTURE_NUM; i++)
	{
        struBlackListPara.struRegisterPic[i].pImage = new BYTE[10*1024];
		if (struBlackListPara.struRegisterPic[i].pImage == NULL)
		{
			return;
		}
		struBlackListPara.struRegisterPic[i].pModel = new BYTE[10*1024];
		if (struBlackListPara.struRegisterPic[i].pModel == NULL)
		{
			return;
		}
	}
	GetBlackListInfoFromWnd(struBlackListPara.struBlackListInfo);
	struBlackListPara.dwSize = sizeof(struBlackListPara);
	for (i=0; i<MAX_HUMAN_PICTURE_NUM; i++)
	{
		if (g_struFaceModel[i].dwFacePicLen > 0)
		{
			struBlackListPara.struRegisterPic[i].dwImageLen = g_struFaceModel[i].dwFacePicLen;
			struBlackListPara.struRegisterPic[i].dwModelLen = g_struFaceModel[i].dwFaceModelLen;
			memcpy(struBlackListPara.struRegisterPic[i].pImage, g_struFaceModel[i].byFacePic, g_struFaceModel[i].dwFacePicLen);
			memcpy(struBlackListPara.struRegisterPic[i].pModel, g_struFaceModel[i].byModelData, g_struFaceModel[i].dwFaceModelLen);
		    struBlackListPara.dwRegisterPicNum++;
		}
	}

	if (!NET_DVR_UpdateBlackList(m_lServerID, m_lChannel, &struBlackListPara))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_UpdateBlackList m_lChannel[%d] ",m_lChannel);
        g_StringLanType(szLan, "修改黑名单失败", "Fail to Update blacklist");
        AfxMessageBox(szLan);
    }
    else
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_UpdateBlackList m_lChannel[%d] ",m_lChannel);
		g_StringLanType(szLan, "修改黑名单成功", "Succ to Update blacklist");
        AfxMessageBox(szLan);
    }

	for (i=0; i<MAX_HUMAN_PICTURE_NUM; i++)
	{
		delete []struBlackListPara.struRegisterPic[i].pImage;
		struBlackListPara.struRegisterPic[i].pImage= NULL;
		delete []struBlackListPara.struRegisterPic[i].pModel;
		struBlackListPara.struRegisterPic[i].pModel = NULL;
	}
}

void CDlgVcaBlackList::OnBtnDelete() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	if (!NET_DVR_DelBlackList(m_lServerID, m_lChannel, m_dwRegisterID))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DelBlackList m_lChannel[%d] ",m_lChannel);
        g_StringLanType(szLan, "删除黑名单失败", "Fail to Delete blacklist");
        AfxMessageBox(szLan);
    }
    else
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DelBlackList m_lChannel[%d] ",m_lChannel);
		g_StringLanType(szLan, "删除黑名单成功", "Succ to Delete blacklist");
        AfxMessageBox(szLan);
    }
}

void CDlgVcaBlackList::OnBtnGetBlacklistPic() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[128] = {0};
	int i;
	NET_VCA_BLACKLIST_PIC struBlackListPic = {0};
	for (i=0; i<MAX_HUMAN_PICTURE_NUM; i++)
	{
		struBlackListPic.struBlackListPic[i].pImage = new BYTE[10 * 1024];
		memset(struBlackListPic.struBlackListPic[i].pImage, 0, 10*1024);
		struBlackListPic.struBlackListPic[i].pModel = new BYTE[10*1024];
		memset(struBlackListPic.struBlackListPic[i].pModel, 0, 10*1024);
	}
	
	if (!NET_DVR_GetBlackListPicture(m_lServerID, m_dwRegisterID, &struBlackListPic))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetBlackListPicture m_dwRegisterID[%d] ",m_dwRegisterID);
        g_StringLanType(szLan, "下载黑名单图片失败", "Fail to Get blacklist picture");
        AfxMessageBox(szLan);

		for (i=0; i<MAX_HUMAN_PICTURE_NUM;i++)
		{
			delete []struBlackListPic.struBlackListPic[i].pImage;
			struBlackListPic.struBlackListPic[i].pImage = NULL;
			delete []struBlackListPic.struBlackListPic[i].pModel;
			struBlackListPic.struBlackListPic[i].pModel = NULL;
		}
		return;
    }
    else
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetBlackListPicture m_dwRegisterID[%d] ",m_dwRegisterID);
		g_StringLanType(szLan, "下载黑名单图片成功", "Succ to Get blacklist picture");
        AfxMessageBox(szLan);
    }

    for (i=0; i<MAX_HUMAN_PICTURE_NUM;i++)
	{
		if (struBlackListPic.struBlackListPic[i].dwImageLen > 0 && struBlackListPic.struBlackListPic[i].pImage != NULL)
		{
			char cFilename[256] = {0};
			HANDLE hFile;
			DWORD dwReturn;
			
			SYSTEMTIME t;
			GetLocalTime(&t);
			
			sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIP);
			if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
			{
				CreateDirectory(cFilename, NULL);
			}
			
			sprintf(cFilename, "%s\\BlackList Pic[ID%d][No%d].jpg",cFilename, m_dwRegisterID,i);
			hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile == INVALID_HANDLE_VALUE)
			{
				return;
			}
			WriteFile(hFile, struBlackListPic.struBlackListPic[i].pImage, struBlackListPic.struBlackListPic[i].dwImageLen, &dwReturn, NULL);
			CloseHandle(hFile);
            hFile = NULL;
		}
	}

	for (i=0; i<MAX_HUMAN_PICTURE_NUM;i++)
	{
       
        delete []struBlackListPic.struBlackListPic[i].pImage;
		struBlackListPic.struBlackListPic[i].pImage = NULL;
	    delete []struBlackListPic.struBlackListPic[i].pModel;
		struBlackListPic.struBlackListPic[i].pModel = NULL;
	}

	UpdateData(FALSE);
}

void CDlgVcaBlackList::OnBtnFastScan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	char szLan[128] = {0};
    OPENFILENAME ofn = {0};
	CRect struRect;
	
    memset(m_chFilename, 0, MAX_PATH);
    
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner   = this->GetSafeHwnd();
    ofn.lpstrFilter = "All Files\0*.*\0\0";
    ofn.lpstrFile   = m_chFilename;
    ofn.nMaxFile    = MAX_PATH;
    ofn.Flags       = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
    
    if (GetOpenFileName(&ofn))
    {
        m_csFastRegPicPath.Format("%s", m_chFilename);
    }
	
	if (strlen(m_chFilename) == 0)
	{
		return;
	}
	
	UpdateData(FALSE);
}

void CDlgVcaBlackList::OnBtnFastRegister() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	CFile file;
	char *sFileBuf;
	BOOL bRet = TRUE;
	DWORD dwFileSize = 0;
	sFileBuf = NULL;
	if (!file.Open(m_chFilename, CFile::shareDenyNone))
	{
		file.Close();
		return;
	}
	file.Seek(0, CFile::begin);
	dwFileSize = (DWORD)(file.GetLength());
	if (dwFileSize == 0)
	{
		file.Close();
		return;
	}
    m_dwFileSize = dwFileSize;
	
	sFileBuf = new char[dwFileSize + 4];
	if (sFileBuf == NULL)
	{
		return;
	}
	file.Read(sFileBuf, dwFileSize);
	file.Close();
	
	m_struBlFastPara.pImage = new BYTE[m_dwFileSize];
	if (m_struBlFastPara.pImage == NULL)
	{
		return;
	}
	memset(m_struBlFastPara.pImage, 0, m_dwFileSize);
	memcpy(m_struBlFastPara.pImage, sFileBuf, m_dwFileSize);
	m_struBlFastPara.dwSize = sizeof(m_struBlFastPara);

	GetBlackListInfoFromWnd(m_struBlFastPara.struBlackListInfo);
	m_struBlFastPara.dwImageLen = m_dwFileSize;
	if (!NET_DVR_FastAddBlackList(m_lServerID, m_lChannel, &m_struBlFastPara))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FastAddBlackList m_lChannel[%d] ",m_lChannel);
        g_StringLanType(szLan, "快速注册黑名单失败", "Fail to register blacklist");
        AfxMessageBox(szLan);
    }
    else
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_FastAddBlackList m_lChannel[%d] ",m_lChannel);
		g_StringLanType(szLan, "快速注册黑名单成功", "Succ to register blacklist");
        AfxMessageBox(szLan);
    }

	delete []m_struBlFastPara.pImage;
	m_struBlFastPara.pImage = NULL;
}
