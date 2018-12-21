// DlgCaseInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCaseInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCaseInfo dialog


CDlgCaseInfo::CDlgCaseInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCaseInfo::IDD, pParent)
    , m_sCaseTypeCustom(_T(""))
{
	//{{AFX_DATA_INIT(CDlgCaseInfo)
	m_nCaseShowTime = 0;
	m_sCaseLitigant1 = _T("");
	m_sCaseLitigant2 = _T("");
	m_sCaseName = _T("");
	m_sCaseNo = _T("");
	m_ChiefJudge = _T("");
	m_nCaseRealTimeShowTime = 0;
	//}}AFX_DATA_INIT
	memset(&m_struCaseInfo,0,sizeof(m_struCaseInfo));
}


void CDlgCaseInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgCaseInfo)
    DDX_Control(pDX, IDC_COMBO_CASE_TYPE, m_comboCaseType);
    DDX_Text(pDX, IDC_CASE_INFO_TIME, m_nCaseShowTime);
    DDX_Text(pDX, IDC_CASE_LITIGANT1, m_sCaseLitigant1);
    DDX_Text(pDX, IDC_CASE_LITIGANT2, m_sCaseLitigant2);
    DDX_Text(pDX, IDC_CASE_NAME, m_sCaseName);
    DDX_Text(pDX, IDC_CASE_NO, m_sCaseNo);
    DDX_Text(pDX, IDC_CHIEF_JUDGE, m_ChiefJudge);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_CASETYPE_CUSTOM, m_sCaseTypeCustom);
}


BEGIN_MESSAGE_MAP(CDlgCaseInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgCaseInfo)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCaseInfo message handlers

BOOL CDlgCaseInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCaseInfo::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[128] = {0};


	if(m_sCaseName.GetLength() > CASE_NAME_LEN)
	{
		AfxMessageBox("案件名称超过最大长度");
		return;
	}	
	char sCaseName[CASE_NAME_LEN] = {0};
	sprintf(sCaseName,m_sCaseName);
	memcpy(m_struCaseInfo.byCaseName,sCaseName,CASE_NAME_LEN);
	if(m_sCaseNo.GetLength() > CASE_NAME_LEN)
	{
		AfxMessageBox("案件名称超过最大长度");
		return;
	}
	char sCaseNo[CASE_NO_LEN] = {0};
	sprintf(sCaseNo,m_sCaseNo);
	memcpy(m_struCaseInfo.byCaseNo,sCaseNo,CASE_NO_LEN);

	if(m_ChiefJudge.GetLength() > CASE_NAME_LEN)
	{
		AfxMessageBox("案件名称超过最大长度");
		return;
	}
	char sChiefJudge[CHIEF_JUDGE_LEN] = {0};
	sprintf(sChiefJudge,m_ChiefJudge);
	memcpy(m_struCaseInfo.byChiefJudge,sChiefJudge,CHIEF_JUDGE_LEN);

	if(m_sCaseLitigant1.GetLength() > CASE_NAME_LEN)
	{
		AfxMessageBox("案件名称超过最大长度");
		return;
	}
	char sCaseLitigant1[LITIGANT_LEN] = {0};
	sprintf(sCaseLitigant1,m_sCaseLitigant1);
	memcpy(m_struCaseInfo.byLitigant1,sCaseLitigant1,LITIGANT_LEN);

	if(m_sCaseLitigant2.GetLength() > CASE_NAME_LEN)
	{
		AfxMessageBox("案件名称超过最大长度");
		return;
	}
	char sCaseLitigant2[LITIGANT_LEN] = {0};
	sprintf(sCaseLitigant2,m_sCaseLitigant2);
	memcpy(m_struCaseInfo.byLitigant2,sCaseLitigant2,LITIGANT_LEN);

	m_struCaseInfo.byCaseType = m_comboCaseType.GetCurSel() + 1;
    if (m_struCaseInfo.byCaseType == 3)
    {
        char sCaseTypeCustom[NET_SDK_CASETYPE_LEN] = { 0 };
        sprintf(sCaseTypeCustom, m_sCaseTypeCustom);
        memcpy(m_struCaseInfo.sCaseTypeCustom, sCaseTypeCustom, NET_SDK_CASETYPE_LEN);
    }
	m_struCaseInfo.byShowCaseInfoTime = m_nCaseShowTime;
	m_struCaseInfo.dwSize = sizeof(NET_DVR_CASE_INFO);

	if(!NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_CASE_INFO,0,&m_struCaseInfo,sizeof(NET_DVR_CASE_INFO)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_CASE_INFO");
		sprintf(szLan,"NET_DVR_SET_CASE_INFO failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
	}
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_CASE_INFO");
    }
	
}

void CDlgCaseInfo::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwRet = 0;
    char szLan[128] = {0};
	if (!NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_CASE_INFO,0,&m_struCaseInfo,sizeof(NET_DVR_CASE_INFO),&dwRet))
	{
	
		sprintf(szLan,"NET_DVR_GET_CASE_INFO failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CASE_INFO");
    }
	m_sCaseName.Format("%s",m_struCaseInfo.byCaseName);
	m_sCaseNo.Format("%s",m_struCaseInfo.byCaseNo);
	m_ChiefJudge.Format("%s",m_struCaseInfo.byChiefJudge);
	m_sCaseLitigant1.Format("%s",m_struCaseInfo.byLitigant1);
	m_sCaseLitigant2.Format("%s",m_struCaseInfo.byLitigant2);
	m_comboCaseType.SetCurSel(m_struCaseInfo.byCaseType - 1);
    if (m_struCaseInfo.byCaseType == 3)
    {
        m_sCaseTypeCustom.Format("%s", m_struCaseInfo.sCaseTypeCustom);
    }
    else
    {
        m_sCaseTypeCustom = "";
    }
	m_nCaseShowTime = m_struCaseInfo.byShowCaseInfoTime;
	UpdateData(FALSE);
}


