// DlgUHFRFIDReaderCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgUHFRFIDReaderCfg.h"
#include "afxdialogex.h"
#include "DlgUHFBasicInfo.h"
#include "DlgHardDiskStorageTest.h"


// CDlgUHFRFIDReaderCfg 对话框

IMPLEMENT_DYNAMIC(CDlgUHFRFIDReaderCfg, CDialogEx)

CDlgUHFRFIDReaderCfg::CDlgUHFRFIDReaderCfg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgUHFRFIDReaderCfg::IDD, pParent)
    , m_lUserID(-1)
    , m_iDeviceIndex(-1)
{

}

CDlgUHFRFIDReaderCfg::~CDlgUHFRFIDReaderCfg()
{
}

void CDlgUHFRFIDReaderCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgUHFRFIDReaderCfg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_BASIC_CFG, &CDlgUHFRFIDReaderCfg::OnBnClickedButtonBasicCfg)
    ON_BN_CLICKED(IDC_BUTTON_HARD_DISK_STORAGE_TEST, &CDlgUHFRFIDReaderCfg::OnBnClickedButtonHardDiskStorageTest)
END_MESSAGE_MAP()


// CDlgUHFRFIDReaderCfg 消息处理程序


void CDlgUHFRFIDReaderCfg::OnBnClickedButtonBasicCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgUHFBasicInfo dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}


void CDlgUHFRFIDReaderCfg::OnBnClickedButtonHardDiskStorageTest()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgHardDiskStorageTest dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}
