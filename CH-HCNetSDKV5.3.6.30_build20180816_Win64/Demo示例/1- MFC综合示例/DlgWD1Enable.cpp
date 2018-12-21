// DlgWD1Enable.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWD1Enable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWD1Enable dialog


CDlgWD1Enable::CDlgWD1Enable(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWD1Enable::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWD1Enable)
	m_chkWd1Enable = FALSE;
	m_dwHighVersion = 0;
	m_dwLowerVersion = 0;
	//}}AFX_DATA_INIT
}


void CDlgWD1Enable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWD1Enable)
	DDX_Check(pDX, IDC_CHK_WD1ENABLE, m_chkWd1Enable);
	DDX_Text(pDX, IDC_EDIT_HIGHVERSION, m_dwHighVersion);
	DDX_Text(pDX, IDC_EDIT_LOWVERSION, m_dwLowerVersion);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWD1Enable, CDialog)
	//{{AFX_MSG_MAP(CDlgWD1Enable)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWD1Enable message handlers

void CDlgWD1Enable::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	//获取WD1使能信息
	NET_DVR_WD1_CFG struWD1Cfg ={0};
	DWORD dwReturned = 0 ;

	if (!NET_DVR_GetDVRConfig(m_lServerID,NET_DVR_GET_WD1_CFG,m_lChannel,&struWD1Cfg,sizeof(NET_DVR_WD1_CFG),&dwReturned))
	{
		char szLan[1024] = {0};
		sprintf(szLan,"Get WD1 failed [%d]",NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return ;
	}
	
	m_dwHighVersion = struWD1Cfg.struStruceHead.byVersion >> 4;
	m_dwLowerVersion= struWD1Cfg.struStruceHead.byVersion && 0xF;
	m_chkWd1Enable = struWD1Cfg.byWD1Enable;

	UpdateData(FALSE);

}

void CDlgWD1Enable::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_WD1_CFG struWD1Cfg ={0};
	 struWD1Cfg.struStruceHead.byVersion = ((m_dwHighVersion << 4 )& 0xf0) + (m_dwLowerVersion& 0xf);
	 if (m_chkWd1Enable)
	 {
		 struWD1Cfg.byWD1Enable = 1;
	 }
	 else
	 {
		 struWD1Cfg.byWD1Enable = 0;
	 }
 
	 struWD1Cfg.struStruceHead.wLength = sizeof(NET_DVR_WD1_CFG);

	if (!NET_DVR_SetDVRConfig(m_lServerID,NET_DVR_SET_WD1_CFG,m_lChannel,&struWD1Cfg,sizeof(NET_DVR_WD1_CFG)))
	{
		char szLan[1024] = {0};
		sprintf(szLan,"Set WD1 failed [%d]",NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return ;
	}
	AfxMessageBox("设置成功");

}
