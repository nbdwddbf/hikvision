// DlgPosManage.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPosManage.h"
#include "DlgPosFilterRule.h"
#include "DlgPosChanFilter.h"
#include "DlgPosConnectMode.h"
#include "DlgPosRecvData.h"
#include "DlgPosSerialPortRecvData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPosManage dialog


CDlgPosManage::CDlgPosManage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPosManage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPosManage)
		// NOTE: the ClassWizard will add member initialization here
	m_iUserID = -1;
	m_iDevIndex = -1;
	//}}AFX_DATA_INIT
}


void CDlgPosManage::DoDataExchange(CDataExchange* pDX)

{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPosManage)
		// NOTE: the ClassWizard will add DDX and DDV calls here

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPosManage, CDialog)
	//{{AFX_MSG_MAP(CDlgPosManage)
	ON_BN_CLICKED(IDC_BTN_FILTERRULE_CFG, OnBtnFilterruleCfg)
	ON_BN_CLICKED(IDC_BTN_CHAN_FILTER_CFG, OnBtnChanFilterCfg)
	ON_BN_CLICKED(IDC_BTN_POS_CONNECT_CFG, OnBtnPosConnectCfg)
	ON_BN_CLICKED(IDC_BTN_RECEIVE_DATA, OnBtnReceiveData)
	ON_BN_CLICKED(IDC_BTN_COM_RECVDATA, OnBtnComRecvdata)
    ON_BN_CLICKED(IDC_BTN_HIDDEN_INFO, OnBnClickedBtnHiddenInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPosManage message handlers

void CDlgPosManage::OnBtnFilterruleCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgPosFilterRule dlg;
	dlg.m_iUserID = m_iUserID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();	
}

BOOL CDlgPosManage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_iUserID < 0)
	{
		GetDlgItem(IDC_BTN_COM_RECVDATA)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_POS_CONNECT_CFG)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_RECEIVE_DATA)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_CHAN_FILTER_CFG)->EnableWindow(FALSE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPosManage::OnBtnChanFilterCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgPosChanFilter dlg;
	dlg.m_iUserID = m_iUserID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();	
}

void CDlgPosManage::OnBtnPosConnectCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgPosConnectMode dlg;
	dlg.m_iUserID = m_iUserID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgPosManage::OnBtnReceiveData() 
{
	// TODO: Add your control notification handler code here
	CDlgPosRecvData dlg;
	dlg.m_iUserID = m_iUserID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgPosManage::OnBtnComRecvdata() 
{
	// TODO: Add your control notification handler code here
	CDlgPosSerialPortRecvData dlg;
	dlg.m_iUserID = m_iUserID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}


#include "DlgHiddenInfo.h"
void CDlgPosManage::OnBnClickedBtnHiddenInfo()
{
    // TODO:  Add your control notification handler code here
    CDlgHiddenInfo dlg;
    dlg.m_iUserID = m_iUserID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_iChanNO = m_lChanNo;
    dlg.DoModal();
}

