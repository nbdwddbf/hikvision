// DlgDeviceAudioTalkCode.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgDeviceAudioTalkCode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceAudioTalkCode dialog


CDlgDeviceAudioTalkCode::CDlgDeviceAudioTalkCode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDeviceAudioTalkCode::IDD, pParent)
	, m_iDeviceIndex(-1)
{
	//{{AFX_DATA_INIT(CDlgDeviceAudioTalkCode)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(&m_struCodeType, 0, sizeof(NET_DVR_COMPRESSION_AUDIO));
}


void CDlgDeviceAudioTalkCode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDeviceAudioTalkCode)
	DDX_Control(pDX, IDC_COMBO_AUDIOTALK_CODETYPE, m_AudioTalkCodeType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDeviceAudioTalkCode, CDialog)
	//{{AFX_MSG_MAP(CDlgDeviceAudioTalkCode)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceAudioTalkCode message handlers
BOOL CDlgDeviceAudioTalkCode::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	DWORD dwReturned;
	if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_GET_COMPRESSCFG_AUD, 0, &m_struCodeType, sizeof(NET_DVR_COMPRESSION_AUDIO), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_COMPRESSCFG_AUD");
		AfxMessageBox("Get Device Code Type Err!");
		GetDlgItem(IDC_BTN_SAVE)->EnableWindow(FALSE);
		return FALSE;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_COMPRESSCFG_AUD");
    int iAudioEncType = 0;
    if ((m_struCodeType.byAudioEncType >= 0) && (m_struCodeType.byAudioEncType <= 2))
    {
        iAudioEncType = m_struCodeType.byAudioEncType;
    }
    else if (m_struCodeType.byAudioEncType == 6)
    {
        iAudioEncType = 3;
    }
    else if (m_struCodeType.byAudioEncType == 5)
    {
        iAudioEncType = 4;
    }
    else if (m_struCodeType.byAudioEncType == 8)
    {
        iAudioEncType = 5;
    }
    else if (m_struCodeType.byAudioEncType == 9)
    {
        iAudioEncType = 6;
    }
    else if (m_struCodeType.byAudioEncType == 10)
    {
        iAudioEncType = 7;
    }
    else if (m_struCodeType.byAudioEncType == 11)
    {
        iAudioEncType = 8;
    }
    else if (m_struCodeType.byAudioEncType == 7)
    {
        iAudioEncType = 9;
    }
    else if (m_struCodeType.byAudioEncType == 12)
    {
        iAudioEncType = 10;
    }
    else if (m_struCodeType.byAudioEncType == 13)
    {
        iAudioEncType = 11;
    }
    else if (m_struCodeType.byAudioEncType == 14)
    {
        iAudioEncType = 12;
    }
    m_AudioTalkCodeType.SetCurSel(iAudioEncType);
	UpdateData(FALSE);
	return TRUE;
}


void CDlgDeviceAudioTalkCode::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int iAudioEncType = (BYTE)m_AudioTalkCodeType.GetCurSel();
    if ((iAudioEncType >= 0) && (iAudioEncType <= 2))
    {
        m_struCodeType.byAudioEncType = (BYTE)iAudioEncType;
    }
    else if (iAudioEncType == 3)
    {
        m_struCodeType.byAudioEncType = 6;
    }
    else if (iAudioEncType == 4)
    {
        m_struCodeType.byAudioEncType = 5;
    }
    else if (iAudioEncType == 5)
    {
        m_struCodeType.byAudioEncType = 8;
    }
    else if (iAudioEncType == 6)
    {
        m_struCodeType.byAudioEncType = 9;
    }
    else if (iAudioEncType == 7)
    {
        m_struCodeType.byAudioEncType = 10;
    }
    else if (iAudioEncType == 8)
    {
        m_struCodeType.byAudioEncType = 11;
    }
    else if (iAudioEncType == 9)
    {
        m_struCodeType.byAudioEncType = 7;
    }
    else if (iAudioEncType == 10)
    {
        m_struCodeType.byAudioEncType = 12;
    }
    else if (iAudioEncType == 11)
    {
        m_struCodeType.byAudioEncType = 13;
    }
    else if (iAudioEncType == 12)
    {
        m_struCodeType.byAudioEncType = 14;
    }
    else
    {
        return;
    }


	if (NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_SET_COMPRESSCFG_AUD, 0, &m_struCodeType, sizeof(NET_DVR_COMPRESSION_AUDIO)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_COMPRESSCFG_AUD");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_COMPRESSCFG_AUD");
	}
}
