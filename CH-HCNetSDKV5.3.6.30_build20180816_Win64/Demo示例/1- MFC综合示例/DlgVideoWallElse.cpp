// DlgVideoWallElse.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVideoWallElse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoWallElse dialog


CDlgVideoWallElse::CDlgVideoWallElse(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoWallElse::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVideoWallElse)
	m_dwSubWinNo = 0;
	m_dwWallNo = 0;
	m_dwWinNo = 0;
	//}}AFX_DATA_INIT
}


void CDlgVideoWallElse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVideoWallElse)
	DDX_Control(pDX, IDC_COMB_CUTPICTUREMODE, m_CmCutPictureMode);
	DDX_Text(pDX, IDC_EDT_SUBWINNO, m_dwSubWinNo);
	DDV_MinMaxDWord(pDX, m_dwSubWinNo, 0, 255);
	DDX_Text(pDX, IDC_EDT_WALLNO, m_dwWallNo);
	DDV_MinMaxDWord(pDX, m_dwWallNo, 0, 255);
	DDX_Text(pDX, IDC_EDT_WINNO, m_dwWinNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVideoWallElse, CDialog)
	//{{AFX_MSG_MAP(CDlgVideoWallElse)
	ON_BN_CLICKED(IDC_BUT_CUTPICTUREMODE_REFRESH, OnButCPMRefresh)
	ON_BN_CLICKED(IDC_BUT_CUTPICTUREMODE_SET, OnButCPMSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoWallElse message handlers

BOOL CDlgVideoWallElse::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_CmCutPictureMode.SetCurSel(-1); 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVideoWallElse::OnButCPMRefresh() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    char szLan[128] = {0}; 
    NET_DVR_IMAGE_CUT_MODE struImageCut ={0};
    DWORD dwChannelEx, dwRet; 
    dwChannelEx = (WORD)m_dwWinNo + ((m_dwSubWinNo&0xff) << 16) + (m_dwWallNo << 24);    
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_IMAGE_CUT_MODE, dwChannelEx, &struImageCut, sizeof(struImageCut), &dwRet))
    {
        g_StringLanType(szLan, "图像分割模式刷新失败", "Failed to refresh Image cut mode");
        sprintf(szLan, "%s. Error Code %d", NET_DVR_GetLastError());
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_IMAGE_CUT_MODE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_IMAGE_CUT_MODE");
        m_CmCutPictureMode.SetCurSel(struImageCut.byCutMode-1 ); 
        UpdateData(FALSE); 
	}
}

void CDlgVideoWallElse::OnButCPMSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    char szLan[128] = {0}; 
    NET_DVR_IMAGE_CUT_MODE struImageCut ={0};
    struImageCut.dwSize = sizeof(struImageCut); 
    struImageCut.byCutMode = m_CmCutPictureMode.GetCurSel() + 1; 
    DWORD dwChannelEx; 
    dwChannelEx = (WORD)m_dwWinNo + ((m_dwSubWinNo&0xff) << 16) + (m_dwWallNo << 24);    
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_IMAGE_CUT_MODE, dwChannelEx, &struImageCut, sizeof(struImageCut)))
    {
        g_StringLanType(szLan, "图像分割模式设置失败", "Failed to Set Image cut mode");
        sprintf(szLan, "%s. Error Code %d", NET_DVR_GetLastError());
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_IMAGE_CUT_MODE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_IMAGE_CUT_MODE");
        OnButCPMRefresh(); 
	}

}
