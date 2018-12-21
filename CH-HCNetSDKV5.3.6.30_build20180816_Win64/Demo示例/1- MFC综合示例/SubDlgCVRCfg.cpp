// SubDlgCVRCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "SubDlgCVRCfg.h"
//#include "DlgRecordPassBack.h"
#include "DlgRecPassBack.h"
#include "DlgDevStorageInfo.h"
#include "DlgCVRPassbackBasicCfg.h"
#include "DlgCVRPreviewByStreamID.h"
#include "DlgCVRResourceIPCfg.h"
#include "DlgCVRDataManage.h"
#include "DlgCVRRemoteBackup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubDlgCVRCfg dialog


CSubDlgCVRCfg::CSubDlgCVRCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgCVRCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubDlgCVRCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSubDlgCVRCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgCVRCfg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubDlgCVRCfg, CDialog)
	//{{AFX_MSG_MAP(CSubDlgCVRCfg)
	ON_BN_CLICKED(IDC_BTN_DEV_CFG, OnBtnDevCfg)
	ON_BN_CLICKED(IDC_BTM_STREAMID, OnBtmStreamid)
	ON_BN_CLICKED(IDC_BTN_RECORD_PASS_BACK, OnBtnRecordPassBack)
	ON_BN_CLICKED(IDC_BTN_DEV_STORAGE, OnBtnDevStorage)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_RECORD_PASSBACK_BASIC_CFG, &CSubDlgCVRCfg::OnBnClickedButtonRecordPassbackBasicCfg)
    ON_BN_CLICKED(IDC_BTN_PREVIEW_BY_STREAMID, &CSubDlgCVRCfg::OnBnClickedBtnPreviewByStreamid)
    ON_BN_CLICKED(IDC_BTN_RESOURCE_IP_CFG, &CSubDlgCVRCfg::OnBnClickedBtnResourceIpCfg)
    ON_BN_CLICKED(IDC_BTN_DATA_CONFIG, &CSubDlgCVRCfg::OnBnClickedBtnDataConfig)
    ON_BN_CLICKED(IDC_BTN_REMOTE_BACKUP_TASK_CFG, &CSubDlgCVRCfg::OnBnClickedBtnRemoteBackupTaskCfg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDlgCVRCfg message handlers

BOOL CSubDlgCVRCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    
//    char szLan[100] = "\0";
//     
//    g_StringLanType(szLan, "设备配置", "CVR Cfg");
//    m_tabStreamID.InsertItem(0, szLan);
//    m_dlgCVRCfg.m_lUserID = m_lUserID;
//    m_dlgCVRCfg.m_iDevIndex = m_iDevIndex;
//    m_dlgCVRCfg.Create(IDD_DLG_CVR, &m_tabStreamID);
//    m_dlgCVRCfg.ShowWindow(SW_HIDE);
// 
//    	g_StringLanType(szLan, "流来源", "Stream source");
//     m_tabStreamID.InsertItem(1, szLan);
//     m_dlgStreamSrc.Create(IDD_DLG_STREAM_SRC_CFG, &m_tabStreamID);
//     m_dlgStreamSrc.ShowWindow(SW_HIDE);
//     
//     g_StringLanType(szLan, "流录像状态", "Stream record status");
//     m_tabStreamID.InsertItem(2, szLan);
//     m_dlgStreamRecordStatus.Create(IDD_DLG_STREAM_RECORD_STATUS, &m_tabStreamID);
//     m_dlgStreamRecordStatus.ShowWindow(SW_HIDE);
//     
//     g_StringLanType(szLan, "流录像计划", "Stream record information");
//     m_tabStreamID.InsertItem(3, szLan);
//     m_dlgStreamRecordInfo.Create(IDD_DLG_STREAM_RECORD_INFO, &m_tabStreamID);
//     m_dlgStreamRecordInfo.ShowWindow(SW_HIDE);
//     
//     g_StringLanType(szLan, "流手动录像和录像段加锁", "Stream manual record and lock");
//     m_tabStreamID.InsertItem(4, szLan);
//     m_dlgStreamManualRecordAndLock.Create(IDD_DLG_STREAM_MANUAL_RECORD_AND_LOCK, &m_tabStreamID);
// 	m_dlgStreamManualRecordAndLock.ShowWindow(SW_HIDE);
// 
//    
//     
//     CRect rcClient;
//     GetClientRect(&rcClient);
//     m_tabStreamID.MoveWindow(rcClient);
//     
//     CRect rcChildRgn = rcClient;
//     rcChildRgn.DeflateRect(100,300,0,0);
//     
//     m_dlgCVRCfg.MoveWindow(rcChildRgn);
//     m_dlgStreamSrc.MoveWindow(rcChildRgn);    
//     m_dlgStreamRecordStatus.MoveWindow(rcChildRgn);    
//     m_dlgStreamRecordInfo.MoveWindow(rcChildRgn);    
//     m_dlgStreamManualRecordAndLock.MoveWindow(rcChildRgn); 
//     
//     ShowChildWnd(SUB_WND_CVR_CFG);

    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSubDlgCVRCfg::OnBtnDevCfg() 
{
    // TODO: Add your control notification handler code here
    CDlgCVR dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CSubDlgCVRCfg::OnBtmStreamid() 
{
	// TODO: Add your control notification handler code here
	CDlgStreamID dlg;
    dlg.DoModal();
}

void CSubDlgCVRCfg::CurCfgUpdate()
{
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        EnableWindow(FALSE);
        return;
    }
    
    EnableWindow(TRUE);
    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;//default to config channel one
    }
    m_iDevIndex = iDeviceIndex;
    m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
    m_lChanNo= iChanIndex+g_struDeviceInfo[iDeviceIndex].iStartChan;
}

// void CSubDlgCVRCfg::OnBtnRecordPassBack() 
// {
// 	// TODO: Add your control notification handler code here
// 	CDlgRecordPassBack dlg;
//     dlg.m_lUserID = m_lUserID;
//     dlg.m_iDevIndex = m_iDevIndex;
//     dlg.DoModal();
// }

void CSubDlgCVRCfg::OnBtnRecordPassBack() 
{
	// TODO: Add your control notification handler code here
	CDlgRecPassBack dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CSubDlgCVRCfg::OnBtnDevStorage() 
{
	// TODO: Add your control notification handler code here
	CDlgDevStorageInfo dlg;
	dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}


void CSubDlgCVRCfg::OnBnClickedButtonRecordPassbackBasicCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgCVRPassbackBasicCfg dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}


void CSubDlgCVRCfg::OnBnClickedBtnPreviewByStreamid()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgCVRPreviewByStreamID dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}


void CSubDlgCVRCfg::OnBnClickedBtnResourceIpCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgCVRResourceIPCfg dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDevIndex;
    dlg.DoModal();
}


void CSubDlgCVRCfg::OnBnClickedBtnDataConfig()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgCVRDataManage dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_lDeviceIndex = m_iDevIndex;
    dlg.DoModal();
}


void CSubDlgCVRCfg::OnBnClickedBtnRemoteBackupTaskCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgCVRRemoteBackup dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDevIndex;
    dlg.DoModal();
}
