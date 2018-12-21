// DlgNetraRecordPackage.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgNetraRecordPackage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNetraRecordPackage dialog


CDlgNetraRecordPackage::CDlgNetraRecordPackage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNetraRecordPackage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNetraRecordPackage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgNetraRecordPackage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNetraRecordPackage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNetraRecordPackage, CDialog)
	//{{AFX_MSG_MAP(CDlgNetraRecordPackage)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNetraRecordPackage message handlers

void CDlgNetraRecordPackage::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_RECORD_PACK struRecordPack = {0};
    DWORD dwReturned = 0 ;
	if (!NET_DVR_GetDVRConfig(m_lLoginID,NET_DVR_GET_RECORD_PACK,m_lChannel,&struRecordPack,sizeof(struRecordPack),&dwReturned))
	{
		DWORD dwRet = NET_DVR_GetLastError();
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_RECORD_PACK");

		goto WriteText ;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORD_PACK");	
	}
WriteText:
	char szTemp[128];
	sprintf(szTemp,"%d",struRecordPack.dwPackageInterval);
	GetDlgItem(IDC_EDIT_PACKAGE_INTERVAL)->SetWindowText(szTemp);
	
	sprintf(szTemp,"%d",struRecordPack.struStruceHead.byVersion>>4);
	GetDlgItem(IDC_EDIT_HIGHVERSION)->SetWindowText(szTemp);
	sprintf(szTemp,"%d",(struRecordPack.struStruceHead.byVersion<<4)>>4);
	GetDlgItem(IDC_EDIT_LOWVERSION)->SetWindowText(szTemp);

}

void CDlgNetraRecordPackage::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    //设置录像打包参数
	NET_DVR_RECORD_PACK struRecordPack = {0};
	CString strTemp;
	struRecordPack.struStruceHead.wLength = sizeof(NET_DVR_RECORD_PACK);
    GetDlgItem(IDC_EDIT_HIGHVERSION)->GetWindowText(strTemp);
	WORD wVersion = atoi((LPSTR)(LPCTSTR)strTemp);
	GetDlgItem(IDC_EDIT_LOWVERSION)->GetWindowText(strTemp);
	wVersion = (wVersion<<4)+atoi((LPSTR)(LPCTSTR)strTemp);
 	struRecordPack.struStruceHead.byVersion = wVersion ;

	GetDlgItem(IDC_EDIT_PACKAGE_INTERVAL)->GetWindowText(strTemp);
    struRecordPack.dwPackageInterval = atoi((LPSTR)(LPCTSTR)strTemp);
	if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_RECORD_PACK,NULL,&struRecordPack,sizeof(struRecordPack)))
	{
		DWORD dwRet = NET_DVR_GetLastError();
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_RECORD_PACK");
		return ;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_RECORD_PACK");	
	}
}

BOOL CDlgNetraRecordPackage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

   	OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
