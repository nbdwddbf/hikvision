// DlgInquestCaseInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInquestCaseInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInquestCaseInfo dialog


CDlgInquestCaseInfo::CDlgInquestCaseInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInquestCaseInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInquestCaseInfo)
	m_nCaseShowTime = 0;
	m_sCustomInfo1 = _T("");
	m_sCustomInfo2 = _T("");
	m_sCustomInfo3 = _T("");
	m_sCaseName = _T("");
	m_sCaseNo = _T("");
	m_nCaseRealTimeShowTime = 0;
	m_bShowCaseInfo = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgInquestCaseInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInquestCaseInfo)
	DDX_Control(pDX, IDC_CMB_POSITION, m_cmbPosition);
	DDX_Control(pDX, IDC_CMB_INQ_ROOM_NO, m_cmbInqRoomNo);
	DDX_Control(pDX, IDC_COMBO_INQ_ROOM_NO, m_cmbInqRoomNo2);
	DDX_Text(pDX, IDC_CASE_INFO_TIME, m_nCaseShowTime);
	DDX_Text(pDX, IDC_CASE_CUSTOM_INFO1, m_sCustomInfo1);
	DDX_Text(pDX, IDC_CASE_CUSTOM_INFO2, m_sCustomInfo2);
	DDX_Text(pDX, IDC_CASE_CUSTOM_INFO3, m_sCustomInfo3);
	DDX_Text(pDX, IDC_CASE_NAME, m_sCaseName);
	DDX_Text(pDX, IDC_CASE_NO, m_sCaseNo);
	DDX_Text(pDX, IDC_CASE_INFO_TIME2, m_nCaseRealTimeShowTime);
	DDX_Check(pDX, IDC_CHK_SHOW_CASE_INFO, m_bShowCaseInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInquestCaseInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgInquestCaseInfo)
		// NOTE: the ClassWizard will add message map macros here
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_CONTROL, OnBtnControl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInquestCaseInfo message handlers

BOOL CDlgInquestCaseInfo::OnInitDialog() 
{  
	// TODO: Add extra initialization here
	CDialog::OnInitDialog();
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_cmbInqRoomNo.SetCurSel(0);
	m_cmbPosition.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInquestCaseInfo::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[128] = {0};

	if(m_sCaseName.GetLength() > INQUEST_CASE_NAME_LEN)
	{
		AfxMessageBox("案件名称超过最大长度");
		return;
	}	
	char sCaseName[INQUEST_CASE_NAME_LEN] = {0};
	sprintf(sCaseName, m_sCaseName);
	memcpy(m_struInqCaseInfo.sCaseName,sCaseName,INQUEST_CASE_NAME_LEN);

	if(m_sCaseNo.GetLength() > INQUEST_CASE_NO_LEN)
	{
		AfxMessageBox("案件编号超过最大长度");
		return;
	}
	char sCaseNo[INQUEST_CASE_NO_LEN] = {0};
	sprintf(sCaseNo,m_sCaseNo);
	memcpy(m_struInqCaseInfo.sCaseNo,sCaseNo,INQUEST_CASE_NO_LEN);

	if(m_sCustomInfo1.GetLength() > CUSTOM_INFO_LEN)
	{
		AfxMessageBox("自定义信息1超过最大长度");
		return;
	}
	char sCustomInfo1[CUSTOM_INFO_LEN] = {0};
	sprintf(sCustomInfo1, m_sCustomInfo1);
	memcpy(m_struInqCaseInfo.sCustomInfo1, sCustomInfo1, CUSTOM_INFO_LEN);

	if(m_sCustomInfo2.GetLength() > CUSTOM_INFO_LEN)
	{
		AfxMessageBox("自定义信息2超过最大长度");
		return;
	}
	char sCustomInfo2[CUSTOM_INFO_LEN] = {0};
	sprintf(sCustomInfo2, m_sCustomInfo2);
	memcpy(m_struInqCaseInfo.sCustomInfo2, sCustomInfo2, CUSTOM_INFO_LEN);

	if(m_sCustomInfo3.GetLength() > CUSTOM_INFO_LEN)
	{
		AfxMessageBox("自定义信息3超过最大长度");
		return;
	}
	char sCustomInfo3[CUSTOM_INFO_LEN] = {0};
	sprintf(sCustomInfo3, m_sCustomInfo3);
	memcpy(m_struInqCaseInfo.sCustomInfo3, sCustomInfo3, CUSTOM_INFO_LEN);

	LONG lInqRoomNo = m_cmbInqRoomNo.GetCurSel() + 1;
	m_struInqCaseInfo.byShowCaseInfoTime = m_nCaseShowTime;
	m_struInqCaseInfo.byShowCaseInfo = m_bShowCaseInfo;
	m_struInqCaseInfo.byPosition = m_cmbPosition.GetCurSel();
	
	m_struInqCaseInfo.dwSize = sizeof(NET_DVR_INQUEST_CASE_INFO);

	if(!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_INQUEST_CASE_INFO, lInqRoomNo, &m_struInqCaseInfo,sizeof(NET_DVR_INQUEST_CASE_INFO)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_INQUEST_CASE_INFO");
		sprintf(szLan,"NET_DVR_SET_INQUEST_CASE_INFO failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
	}
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_INQUEST_CASE_INFO");
    }
	
}

void CDlgInquestCaseInfo::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwRet = 0;
    char szLan[128] = {0};

	LONG lInqRoomNo = m_cmbInqRoomNo.GetCurSel() + 1;

	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_INQUEST_CASE_INFO, lInqRoomNo, &m_struInqCaseInfo, sizeof(NET_DVR_INQUEST_CASE_INFO), &dwRet))
	{
	
		sprintf(szLan,"NET_DVR_GET_INQUEST_CASE_INFO failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_INQUEST_CASE_INFO");
    }

	m_sCaseName.Format("%s", m_struInqCaseInfo.sCaseName);
	m_sCaseNo.Format("%s",m_struInqCaseInfo.sCaseNo);
	m_sCustomInfo1.Format("%s",m_struInqCaseInfo.sCustomInfo1);
	m_sCustomInfo2.Format("%s",m_struInqCaseInfo.sCustomInfo2);
	m_sCustomInfo3.Format("%s",m_struInqCaseInfo.sCustomInfo3);
	m_nCaseShowTime = m_struInqCaseInfo.byShowCaseInfoTime;
	m_bShowCaseInfo = m_struInqCaseInfo.byShowCaseInfo;
	m_cmbPosition.SetCurSel(m_struInqCaseInfo.byPosition);
	UpdateData(FALSE);
}

void CDlgInquestCaseInfo::OnBtnControl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[128] = {0};

	NET_DVR_CASE_INFO_CTRL_PARAM struCaseInfoCtrlParam = {0};

	struCaseInfoCtrlParam.dwSize = sizeof(NET_DVR_CASE_INFO_CTRL_PARAM);
	struCaseInfoCtrlParam.dwChannel = m_cmbInqRoomNo2.GetCurSel() + 1;
	struCaseInfoCtrlParam.byShowCaseInfoTime = m_nCaseRealTimeShowTime;

	if(!NET_DVR_RemoteControl(m_lUserID, NET_DVR_CASE_INFO_CTRL, &struCaseInfoCtrlParam, sizeof(NET_DVR_CASE_INFO_CTRL_PARAM)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_CASE_INFO_CTRL");
		sprintf(szLan,"NET_DVR_CASE_INFO_CTRL failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
	}
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_CASE_INFO_CTRL");
    }
}
