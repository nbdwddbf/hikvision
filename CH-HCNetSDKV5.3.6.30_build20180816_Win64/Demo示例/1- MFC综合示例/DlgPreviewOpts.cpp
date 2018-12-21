// CDlgPreviewOpts.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgPreviewOpts.h"
#include "afxdialogex.h"


// DlgPreviewOpts 对话框

IMPLEMENT_DYNAMIC(CDlgPreviewOpts, CDialogEx)

CDlgPreviewOpts::CDlgPreviewOpts(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPreviewOpts::IDD, pParent)
    , m_csURL(_T(""))
    , m_bEnable(FALSE)
{
    m_iDeviceIndex = -1;
}

CDlgPreviewOpts::~CDlgPreviewOpts()
{
}

void CDlgPreviewOpts::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_PREVIEW_URL, m_csURL);
    DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
}


BEGIN_MESSAGE_MAP(CDlgPreviewOpts, CDialogEx)
    ON_BN_CLICKED(IDOK, &CDlgPreviewOpts::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CDlgPreviewOpts::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgPreviewOpts 消息处理程序


void CDlgPreviewOpts::OnBnClickedOk()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    CDialogEx::OnOK();
}

BOOL CDlgPreviewOpts::GetEnableUrl()
{
    return m_bEnable;
}

CString & CDlgPreviewOpts::GetUrl()
{
    return m_csURL;
}

void CDlgPreviewOpts::OnBnClickedCancel()
{
    // TODO:  在此添加控件通知处理程序代码
    CDialogEx::OnCancel();
}

void CDlgPreviewOpts::SetEnableUrl(BOOL bEnable)
{
    m_bEnable = bEnable;
    return;
}
void CDlgPreviewOpts::SetUrl(CString szUrl)
{
    m_csURL = szUrl;
    return;
}

BOOL CDlgPreviewOpts::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    UpdateData(TRUE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}
