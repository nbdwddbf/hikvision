// DlgDevStorageInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgDevStorageInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDevStorageInfo dialog


CDlgDevStorageInfo::CDlgDevStorageInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDevStorageInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDevStorageInfo)
	m_nCapacityTotal = 0;
	m_nFreeSpaceTotal = 0;
	m_nLockedRecordSpace = 0;
	m_nUnLockedSpace = 0;
	//}}AFX_DATA_INIT
}


void CDlgDevStorageInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDevStorageInfo)
	DDX_Text(pDX, IDC_EDIT_CAPACITY_TOTAL, m_nCapacityTotal);
	DDX_Text(pDX, IDC_EDIT_FREE_SPACE_TOTAL, m_nFreeSpaceTotal);
	DDX_Text(pDX, IDC_EDIT_LOACKED_REC_SPACE, m_nLockedRecordSpace);
	DDX_Text(pDX, IDC_EDIT_OTHER_SPACE, m_nUnLockedSpace);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDevStorageInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgDevStorageInfo)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDevStorageInfo message handlers

void CDlgDevStorageInfo::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
    char szLan[128];

	NET_DVR_DEV_STORAGE_CFG struDevStorage = {0};
    struDevStorage.dwSize = sizeof(NET_DVR_DEV_STORAGE_CFG);

    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_DEV_STORAGE_CFG, 0, &struDevStorage, sizeof(NET_DVR_DEV_STORAGE_CFG), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_DEV_STORAGE_CFG Failed");
        g_StringLanType(szLan, "»ñÈ¡Ê§°Ü", "get Failed");
        MessageBox(szLan);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_DEV_STORAGE_CFG SUCC");
		
		m_nCapacityTotal = struDevStorage.dwCapacityTotal;
		m_nFreeSpaceTotal = struDevStorage.dwFreeSpaceTotal;
		m_nLockedRecordSpace = struDevStorage.dwLockedRecordSpace;
		m_nUnLockedSpace = struDevStorage.dwUnLockedSpace;

        UpdateData(FALSE);
    }
}
