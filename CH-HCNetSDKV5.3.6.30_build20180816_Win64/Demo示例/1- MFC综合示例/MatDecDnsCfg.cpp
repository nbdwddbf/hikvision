// DlgRemoteMatDecDnsCfg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "MatDecDnsCfg.h"
#include ".\matdecdnscfg.h"
#include ".\matdecdnscfg.h"


// CDlgRemoteMatDecDnsCfg dialog
/*********************************************************
  Function:	CMatDecDnsCfg
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgRemoteMatDecDnsCfg, CDialog)
CDlgRemoteMatDecDnsCfg::CDlgRemoteMatDecDnsCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteMatDecDnsCfg::IDD, pParent)
	, m_lLoginID(0)
	, m_FirstDns(_T(""))
	, m_SecondDns(_T(""))
{
	memset(&m_NetCFGOther, 0, sizeof(m_NetCFGOther));
}

/*********************************************************
  Function:	~CMatDecDnsCfg
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgRemoteMatDecDnsCfg::~CDlgRemoteMatDecDnsCfg()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteMatDecDnsCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteMatDecDnsCfg)
	DDX_Text(pDX, IDC_EDIT_FIRST_DNS, m_FirstDns);
	DDX_Text(pDX, IDC_EDIT_SECOND_DNS, m_SecondDns);
        //}}AFX_DATA_MAP

}

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgRemoteMatDecDnsCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteMatDecDnsCfg)	
	ON_BN_CLICKED(ID_BTN_MAT_DEC_OK, OnBnClickedBtnMatDecOk)
	ON_BN_CLICKED(ID_BTN_MAT_DEC_EXIT, OnBnClickedBtnMatDecExit)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()


// CDlgRemoteMatDecDnsCfg message handlers
/*********************************************************
  Function:	OnInitDialog
  Desc:		Initialize the dialog
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgRemoteMatDecDnsCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	DWORD dwReturned = 0;
	char szFirstDns[32] = {0};
	char szSecondDns[32] = {0};
	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_NETCFG_OTHER, 0,&m_NetCFGOther, sizeof(NET_DVR_NETCFG_OTHER), &dwReturned))	
	{
		CString sTemp;
		sTemp.Format("ERROR: NET_DVR_GET_NETCFG_OTHER = %d \n", NET_DVR_GetLastError());
		g_pMainDlg->AddLog(g_pMainDlg->m_iCurDeviceIndex, OPERATION_SUCC_T, sTemp);	
		//return FALSE;
	}
	else
	{
		memcpy(szFirstDns, m_NetCFGOther.sFirstDNSIP, 16);
		memcpy(szSecondDns, m_NetCFGOther.sSecondDNSIP, 16);
		m_FirstDns.Format("%s", szFirstDns);
		m_SecondDns.Format("%s", szSecondDns);
	}

	UpdateData(FALSE);
	return TRUE; 
}

/*********************************************************
  Function:	OnBnClickedBtnMatDecOk
  Desc:		finish settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteMatDecDnsCfg::OnBnClickedBtnMatDecOk()
{
	UpdateData(TRUE);
	memcpy(m_NetCFGOther.sFirstDNSIP, m_FirstDns.GetBuffer(0), 16);
	memcpy(m_NetCFGOther.sSecondDNSIP, m_SecondDns.GetBuffer(0), 16);
	if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_NETCFG_OTHER, 0,&m_NetCFGOther, sizeof(NET_DVR_NETCFG_OTHER)))	
	{
		CString sTemp;
		sTemp.Format("ERROR: NET_DVR_SET_NETCFG_OTHER = %d \n", NET_DVR_GetLastError());
		AfxMessageBox(sTemp);	
	}
	CDialog::OnOK();
}

/*********************************************************
  Function:	OnBnClickedBtnMatDecExit
  Desc:	    exit settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteMatDecDnsCfg::OnBnClickedBtnMatDecExit()
{
	CDialog::OnCancel();
}
