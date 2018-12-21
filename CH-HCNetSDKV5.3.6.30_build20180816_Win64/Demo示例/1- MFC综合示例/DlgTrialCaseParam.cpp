// DlgTrialCaseParam.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTrialCaseParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTrialCaseParam dialog


CDlgTrialCaseParam::CDlgTrialCaseParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTrialCaseParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTrialCaseParam)
	m_sCaseLitigant1 = _T("");
	m_sCaseLitigant2 = _T("");
	m_sCaseName = _T("");
	m_sCaseNo = _T("");
	m_sChiefJudge = _T("");
	//}}AFX_DATA_INIT
}


void CDlgTrialCaseParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTrialCaseParam)
	DDX_Control(pDX, IDC_COMBO_CASE_TYPE, m_comboCaseType);
	DDX_Text(pDX, IDC_CASE_LITIGANT1, m_sCaseLitigant1);
	DDX_Text(pDX, IDC_CASE_LITIGANT2, m_sCaseLitigant2);
	DDX_Text(pDX, IDC_CASE_NAME, m_sCaseName);
	DDX_Text(pDX, IDC_CASE_NO, m_sCaseNo);
	DDX_Text(pDX, IDC_CHIEF_JUDGE, m_sChiefJudge);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTrialCaseParam, CDialog)
	//{{AFX_MSG_MAP(CDlgTrialCaseParam)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTrialCaseParam message handlers

void CDlgTrialCaseParam::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char caseName[SEARCH_CASE_NAME_LEN];
	sprintf(caseName,m_sCaseName);
	memcpy(g_caseInfo.byCaseName,caseName,SEARCH_CASE_NAME_LEN);

	char caseNo[SEARCH_CASE_NO_LEN];
	sprintf(caseNo,m_sCaseNo);
	memcpy(g_caseInfo.byCaseNo,caseNo,SEARCH_CASE_NO_LEN);

	char ChiefJudge[SEARCH_CHIEF_JUDGE_LEN];
	sprintf(ChiefJudge,m_sChiefJudge);
	memcpy(g_caseInfo.byChiefJudge,ChiefJudge,SEARCH_CHIEF_JUDGE_LEN);

	char litigant1[SEARCH_LITIGANT_LEN];
	sprintf(litigant1,m_sCaseLitigant1);
	memcpy(g_caseInfo.byLitigant1,litigant1,SEARCH_LITIGANT_LEN);

	char litigant2[SEARCH_LITIGANT_LEN];
	sprintf(litigant2,m_sCaseLitigant2);
	memcpy(g_caseInfo.byLitigant2,litigant2,SEARCH_LITIGANT_LEN);

	g_caseInfo.byCaseType = m_comboCaseType.GetCurSel();
	CDialog::OnOK();
}
