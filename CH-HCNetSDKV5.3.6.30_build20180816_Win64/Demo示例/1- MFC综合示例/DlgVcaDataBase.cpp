// DlgVcaDataBase.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaDataBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDataBase dialog
CDlgVcaDataBase *g_pVcaDataBase = NULL;
UINT GetDataBaseThread(LPVOID pParam)
{
    UNREFERENCED_PARAMETER(pParam);
	
	LONG bRet = -1;
	NET_VCA_DATABASE_PARAM struData;
    memset(&struData, 0, sizeof(struData));
	CString csTmp;
	char szLan[128] = {0};
	while (1) 
	{
		bRet = NET_DVR_FindNextDataBase(g_pVcaDataBase->m_lHandle, &struData);
        if (bRet == NET_DVR_FILE_SUCCESS)
		{
			csTmp.Format("%d", g_pVcaDataBase->m_lDataBaseNum+1);
			g_pVcaDataBase->m_listDataBase.InsertItem(g_pVcaDataBase->m_lDataBaseNum, csTmp,0);
			
			switch (struData.dwDataBaseType)
			{
			case 1:
				g_StringLanType(szLan, "抓拍数据库", "Snap Database");
				break;
			case 2:
				g_StringLanType(szLan, "人脸数据库", "Face Database");
				break;
			default:
                g_StringLanType(szLan, "未知", "Unknow");
				break;
			}
            csTmp.Format("%s", szLan);
			g_pVcaDataBase->m_listDataBase.SetItemText(g_pVcaDataBase->m_lDataBaseNum, 1, csTmp);

			csTmp.Format("%d", struData.dwDataBaseID);
			g_pVcaDataBase->m_listDataBase.SetItemText(g_pVcaDataBase->m_lDataBaseNum, 2, csTmp);

			csTmp.Format("%s", struData.byDataBaseName);
            g_pVcaDataBase->m_listDataBase.SetItemText(g_pVcaDataBase->m_lDataBaseNum, 3, csTmp);

			csTmp.Format("%s", struData.byAttribute);
            g_pVcaDataBase->m_listDataBase.SetItemText(g_pVcaDataBase->m_lDataBaseNum, 4, csTmp);

			g_pVcaDataBase->m_lDataBaseNum++;
		}
		else
		{
			if (bRet == NET_DVR_ISFINDING)
			{
				g_pVcaDataBase->GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_SHOW);
				g_pVcaDataBase->GetDlgItem(IDC_STATIC_SEARCH)->SetWindowText("Searching......");
				Sleep(5);
				continue;
			}
			if ((bRet == NET_DVR_NOMOREFILE) || (bRet == NET_DVR_FILE_NOFIND))
			{
				g_StringLanType(szLan, "查询", "search");
				g_pVcaDataBase->GetDlgItem(IDC_BTN_FIND_DATABASE)->SetWindowText(szLan);
				g_pVcaDataBase->GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_HIDE);
				g_StringLanType(szLan, "查询结束!", "Search Ending");
				AfxMessageBox(szLan);
				break;
			}
			else
			{
				g_StringLanType(szLan, "查询", "Search");
				g_pVcaDataBase->GetDlgItem(IDC_BTN_FIND_DATABASE)->SetWindowText(szLan);
				g_pVcaDataBase->GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_HIDE);
				g_StringLanType(szLan, "由于服务器忙,或网络故障,搜索异常终止!",\
					"Since the server is busy, or network failure, search abnormal termination");
				AfxMessageBox(szLan);
				break;
			}
		}
	}

	CloseHandle(g_pVcaDataBase->m_hThread);
	g_pVcaDataBase->m_hThread = NULL;
	NET_DVR_FindDataBaseClose(g_pVcaDataBase->m_lHandle);
	return 0;
}

CDlgVcaDataBase::CDlgVcaDataBase(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaDataBase::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaDataBase)
	m_dwDataBaseID = 0;
	m_csDataBaseName = _T("");
	m_csDataBaseAttr = _T("");
	//}}AFX_DATA_INIT
	m_hThread = NULL;
	m_lDataBaseNum = 0;
	memset(&m_struDataBaseParam, 0, sizeof(m_struDataBaseParam));
}


void CDlgVcaDataBase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaDataBase)
	DDX_Control(pDX, IDC_LIST_DATABASE, m_listDataBase);
	DDX_Control(pDX, IDC_COMBO_DATABASE_TYPE, m_comboDBType);
	DDX_Text(pDX, IDC_EDIT_DATABASE_ID, m_dwDataBaseID);
	DDX_Text(pDX, IDC_EDIT_DATABASE_NAME, m_csDataBaseName);
	DDX_Text(pDX, IDC_EDIT_DATABASE_ATTR, m_csDataBaseAttr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaDataBase, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaDataBase)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_UPDATE_DATABASE, OnBtnUpdateDatabase)
	ON_BN_CLICKED(IDC_BTN_DELETE_DATABASE, OnBtnDeleteDatabase)
	ON_BN_CLICKED(IDC_BTN_FIND_DATABASE, OnBtnFindDatabase)
	ON_BN_CLICKED(IDC_BTN_STOP_FIND, OnBtnStopFind)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDataBase message handlers
BOOL CDlgVcaDataBase::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_comboDBType.SetCurSel(0);
	
	g_pVcaDataBase = this;
	
	char szLan[128] = {0};
    
    m_listDataBase.SetExtendedStyle(m_listDataBase.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLan, "序号", "NO.");
    m_listDataBase.InsertColumn(0, szLan, LVCFMT_RIGHT, 60, -1);
	g_StringLanType(szLan, "数据库类型", "Type");
    m_listDataBase.InsertColumn(1, szLan, LVCFMT_RIGHT, 80, -1);
	g_StringLanType(szLan, "数据库ID", "ID");
	m_listDataBase.InsertColumn(2, szLan, LVCFMT_LEFT, 80, -1);
	g_StringLanType(szLan, "名称", "Name");
    m_listDataBase.InsertColumn(3, szLan, LVCFMT_LEFT, 100, -1);
	g_StringLanType(szLan, "属性", "Sex");
    m_listDataBase.InsertColumn(4, szLan, LVCFMT_LEFT,100, -1);

	UpdateData(FALSE);

	return TRUE;
}

void CDlgVcaDataBase::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	NET_VCA_DATABASE_PARAM struInBuf = {0};
	struInBuf.dwSize = sizeof(struInBuf);
	struInBuf.dwDataBaseID = m_dwDataBaseID;
	struInBuf.dwDataBaseType = m_comboDBType.GetCurSel()+1;
	memcpy(struInBuf.byDataBaseName, m_csDataBaseName, NAME_LEN);
	memcpy(struInBuf.byAttribute, m_csDataBaseAttr, 64);
	if (!NET_DVR_AddDataBase(m_lServerID, &struInBuf))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AddDataBase");
        g_StringLanType(szLan, "添加数据库失败", "Fail to add database");
        AfxMessageBox(szLan);
    }
    else
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AddDataBase");
		g_StringLanType(szLan, "添加数据库成功", "Succ to add database");
        AfxMessageBox(szLan);
    }
}

void CDlgVcaDataBase::OnBtnUpdateDatabase() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	NET_VCA_DATABASE_PARAM struInBuf = {0};
	struInBuf.dwSize = sizeof(struInBuf);
	struInBuf.dwDataBaseID = m_dwDataBaseID;
	struInBuf.dwDataBaseType = m_comboDBType.GetCurSel()+1;
	memcpy(struInBuf.byDataBaseName, m_csDataBaseName, NAME_LEN);
	memcpy(struInBuf.byAttribute, m_csDataBaseAttr, 64);
	if (!NET_DVR_UpdateDataBase(m_lServerID, &struInBuf))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_UpdateDataBase");
        g_StringLanType(szLan, "修改数据库失败", "Fail to update database");
        AfxMessageBox(szLan);
    }
    else
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_UpdateDataBase");
		g_StringLanType(szLan, "修改数据库成功", "Succ to update database");
        AfxMessageBox(szLan);
    }
}

void CDlgVcaDataBase::OnBtnDeleteDatabase() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	NET_VCA_DELETE_DATABASE_COND struCond = {0};
	struCond.dwSize = sizeof(struCond);
	struCond.dwDataBaseID = m_dwDataBaseID;
	struCond.dwDataBaseType = m_comboDBType.GetCurSel()+1;
	if (!NET_DVR_DeleteDataBase(m_lServerID, &struCond))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DeleteDataBase");
        g_StringLanType(szLan, "删除数据库失败", "Fail to delete database");
        AfxMessageBox(szLan);
    }
    else
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DeleteDataBase");
		g_StringLanType(szLan, "删除数据库成功", "Succ to delete database");
        AfxMessageBox(szLan);
    }
}

void CDlgVcaDataBase::OnBtnFindDatabase() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};

	NET_VCA_FIND_DATABASE_COND struFindCond = {0};
	struFindCond.dwDataBaseType = m_comboDBType.GetCurSel()+1;
	m_lHandle = NET_DVR_FindDataBase(m_lServerID, &struFindCond);
	if (m_lHandle < 0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FindDataBase");
		
		g_StringLanType(szLan, "查询失败", "Search database failed");
		AfxMessageBox(szLan);
        return;
	}
// 	else
// 	{
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_FindDataBase");
// 		
// 		g_StringLanType(szLan, "查询成功", "Search database successfully");
// 		AfxMessageBox(szLan);
// 	}
	
	m_lDataBaseNum = 0;
	m_listDataBase.DeleteAllItems();
	DWORD dwThreadId = 0;
	if (m_hThread == NULL)
	{
		m_hThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetDataBaseThread), this, 0, &dwThreadId);
	}
	
	if (m_hThread  == NULL)
	{
		g_StringLanType(szLan, "打开线程失败", "Open thread failed");
		AfxMessageBox(szLan);
		return;
    }
	
	g_StringLanType(szLan, "查询", "search");
	g_pVcaDataBase->GetDlgItem(IDC_BTN_FIND_DATABASE)->SetWindowText(szLan);
}

void CDlgVcaDataBase::OnBtnStopFind() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (m_hThread != NULL)
	{
		TerminateThread(m_hThread, 0);
		CloseHandle(m_hThread);
		m_hThread = NULL;
		NET_DVR_FindDataBaseClose(m_lHandle);
		g_StringLanType(szLan, "查询", "search");
		GetDlgItem(IDC_BTN_FIND_DATABASE)->SetWindowText(szLan);
	    GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_HIDE);
	}
}

void CDlgVcaDataBase::OnDestroy() 
{
	if (m_hThread != NULL)
	{
		TerminateThread(m_hThread, 0);
		CloseHandle(m_hThread);
		m_hThread = NULL;
		NET_DVR_FindDataBaseClose(m_lHandle);
	}

	CDialog::OnDestroy();
		// TODO: Add your message handler code here
	
}
