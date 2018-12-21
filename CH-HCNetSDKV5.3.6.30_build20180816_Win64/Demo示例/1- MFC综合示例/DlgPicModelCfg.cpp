// DlgPicModelCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPicModelCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPicModelCfg dialog


CDlgPicModelCfg::CDlgPicModelCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPicModelCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPicModelCfg)
	m_bEnable = FALSE;
    m_lUserID = -1;
    m_iDevIndex = -1;
	//}}AFX_DATA_INIT
}


void CDlgPicModelCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPicModelCfg)
	DDX_Check(pDX, IDC_CHK_ENABLE_PIC, m_bEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPicModelCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgPicModelCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPicModelCfg message handlers

void CDlgPicModelCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	
    DWORD dwReturn = NET_DVR_NOERROR;

    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_PIC_MODEL_CFG,-1,&m_struPicModelCfg,sizeof(m_struPicModelCfg),&dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T, "NET_DVR_GET_PIC_MODEL_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T, "NET_DVR_GET_PIC_MODEL_CFG");
    }

    m_bEnable = m_struPicModelCfg.byEnable;

    UpdateData(FALSE);
}

BOOL CDlgPicModelCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    memset(&m_struPicModelCfg,0,sizeof(m_struPicModelCfg));
	OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPicModelCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code her   
    UpdateData(TRUE);
    m_struPicModelCfg.dwSize = sizeof(m_struPicModelCfg);
    m_struPicModelCfg.byEnable = m_bEnable;
    
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_PIC_MODEL_CFG,-1,&m_struPicModelCfg,sizeof(m_struPicModelCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T, "NET_DVR_SET_PIC_MODEL_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T, "NET_DVR_SET_PIC_MODEL_CFG");
    }
    

}
