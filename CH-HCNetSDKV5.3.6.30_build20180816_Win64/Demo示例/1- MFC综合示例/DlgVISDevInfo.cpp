// DlgVISDevInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVISDevInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVISDevInfo dialog


CDlgVISDevInfo::CDlgVISDevInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVISDevInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVISDevInfo)
	m_csDevID = _T("");
	//}}AFX_DATA_INIT
}


void CDlgVISDevInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVISDevInfo)
	DDX_Text(pDX, IDC_EDIT_DEVICE_ID, m_csDevID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVISDevInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgVISDevInfo)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVISDevInfo message handlers

void CDlgVISDevInfo::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    DWORD dwReturn = NET_DVR_NOERROR;
    if (!NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_VIS_DEVINFO,0,&m_struDevInfo,sizeof(m_struDevInfo),&dwReturn))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T,"NET_DVR_GET_VIS_DEVINFO");
        return;
	}
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T,"NET_DVR_GET_VIS_DEVINFO");
    }

    m_csDevID.Format("%s",m_struDevInfo.szDevNumber);

    UpdateData(FALSE);
}

BOOL CDlgVISDevInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	memset(&m_struDevInfo,0,sizeof(m_struDevInfo));
    OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
