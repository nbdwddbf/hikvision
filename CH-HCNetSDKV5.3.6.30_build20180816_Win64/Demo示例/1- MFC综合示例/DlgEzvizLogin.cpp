// EzvizLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgEzvizLogin.h"
#include "afxdialogex.h"


// CEzvizLogin 对话框

IMPLEMENT_DYNAMIC(CEzvizLogin, CDialogEx)

CEzvizLogin::CEzvizLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEzvizLogin::IDD, pParent)
{

}

CEzvizLogin::~CEzvizLogin()
{
}



void CEzvizLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_EzvizBrowser);
}


BEGIN_MESSAGE_MAP(CEzvizLogin, CDialogEx)
END_MESSAGE_MAP()


// CEzvizLogin 消息处理程序


BOOL CEzvizLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	string website = "https://openauth.ezvizlife.com/oauth/ddns/56bdd1135f9a11e7ae26fa163e8bac01?areaId="+strAreaID;
	m_EzvizBrowser.Navigate((CString)website.c_str(), NULL, NULL, NULL, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CEzvizLogin::setArea(string area)
{
	strAreaID = area;
}


BEGIN_EVENTSINK_MAP(CEzvizLogin, CDialogEx)
ON_EVENT(CEzvizLogin, IDC_EXPLORER1, 250, CEzvizLogin::BeforeNavigate2Explorer, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
END_EVENTSINK_MAP()


void CEzvizLogin::BeforeNavigate2Explorer(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel)
{
	// TODO:  在此处添加消息处理程序代码
	bstr_t ret = URL->bstrVal;
	string retInfo = ret;
	if (retInfo.find("success") != -1){
		accessToken = retInfo.substr(retInfo.find("access_token") + 13, retInfo.find("#") - retInfo.find("access_token") - 13);
		areaDomain = retInfo.substr(retInfo.find("areaDomain") + 11, retInfo.length() - retInfo.find("areaDoamin") + 1);
		EndDialog(0);
	}
}
