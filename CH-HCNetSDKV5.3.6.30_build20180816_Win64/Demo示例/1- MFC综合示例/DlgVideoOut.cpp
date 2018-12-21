// DlgVideoOut.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVideoOut.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoOut dialog


CDlgVideoOut::CDlgVideoOut(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoOut::IDD, pParent)
	,m_iDeviceIndex(-1)
	,m_lUserID(-1)
	, m_iCurBNCChan(-1)
{
	//{{AFX_DATA_INIT(CDlgVideoOut)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgVideoOut::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVideoOut)
	DDX_Control(pDX, IDC_COMBO_BNC_CHANNEL, m_cmBNCChan);
	DDX_Control(pDX, IDC_COMBO_VIDEO_FORMAT, m_cmVideoFormat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVideoOut, CDialog)
	//{{AFX_MSG_MAP(CDlgVideoOut)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_CBN_SELCHANGE(IDC_COMBO_BNC_CHANNEL, OnSelchangeComboBncChannel)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoOut message handlers

BOOL CDlgVideoOut::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
	char szStr[128] = {0};
	m_cmBNCChan.ResetContent();
	for (int i=0; i<MAX_VIDEOOUT_V30; i++)
	{
		sprintf(szStr, "%d", i+1);
		m_cmBNCChan.AddString(szStr);
	}
	OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVideoOut::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	memset((char*)&m_struVideoOut, 0, sizeof(m_struVideoOut));
	m_struVideoOut.dwSize = sizeof(m_struVideoOut);
	DWORD dwReturn = 0;
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_VIDEOOUTCFG_V30, 0, &m_struVideoOut, sizeof(m_struVideoOut), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Get video out parameter failed");
		GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Get video out parameter successful");
		GetDlgItem(IDC_BTN_SET)->EnableWindow(TRUE);
		m_cmBNCChan.SetCurSel(0);
		m_cmVideoFormat.SetCurSel(m_struVideoOut.struVOOut[0].byVideoFormat);
		m_iCurBNCChan = 0;
	}
	UpdateData(FALSE);
}

void CDlgVideoOut::OnSelchangeComboBncChannel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struVideoOut.struVOOut[m_iCurBNCChan].byVideoFormat = m_cmVideoFormat.GetCurSel();
	int iIndex = m_cmBNCChan.GetCurSel();
	m_cmVideoFormat.SetCurSel(m_struVideoOut.struVOOut[iIndex].byVideoFormat);
	m_iCurBNCChan = iIndex;
	UpdateData(FALSE);
}

void CDlgVideoOut::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struVideoOut.struVOOut[m_cmBNCChan.GetCurSel()].byVideoFormat = m_cmVideoFormat.GetCurSel();
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_VIDEOOUTCFG_V30, 0, &m_struVideoOut, sizeof(m_struVideoOut)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Set video out parameter failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set video out parameter successful");
	}
}
