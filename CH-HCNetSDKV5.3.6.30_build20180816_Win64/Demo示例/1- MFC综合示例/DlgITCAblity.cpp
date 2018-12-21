// DlgITCAblity.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgITCAblity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgITCAblity dialog


CDlgITCAblity::CDlgITCAblity(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgITCAblity::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgITCAblity)
	m_csITCAblity = _T("");
	//}}AFX_DATA_INIT
}


void CDlgITCAblity::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgITCAblity)
	DDX_Text(pDX, IDC_EDIT_ITC_ABLITY, m_csITCAblity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgITCAblity, CDialog)
	//{{AFX_MSG_MAP(CDlgITCAblity)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgITCAblity message handlers

void CDlgITCAblity::OnBtnGet() 
{
	// TODO: Add your control notification handler code here

	char szLan[128] = {0};
	char szTemp[256] = {0};

	char szLanEdit[1024] = {0};
	char *pTemp = szLanEdit;

	//能力集获取
	NET_DVR_SNAP_ABILITY m_Ability;
	memset(&m_Ability, 0, sizeof(NET_DVR_SNAP_ABILITY));
	if (!NET_DVR_GetDeviceAbility(m_lServerID, SNAPCAMERA_ABILITY, NULL, 0, (char*)&m_Ability, sizeof(NET_DVR_SNAP_ABILITY)))
	{
		g_StringLanType(szLan, "获取设备能力失败", "Get ability failed");
		sprintf(szTemp, "%s %s %d", szLan, NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());
		AfxMessageBox(szTemp);
		return;
    }
	else
	{
		sprintf(pTemp, "bySupport:%x", m_Ability.bySupport);
		m_csITCAblity.Format("%s", szLanEdit);
	}
	UpdateData(FALSE);
}
