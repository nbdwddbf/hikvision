// DlgDecWinStatus2.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgDecWinStatusUniform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDecWinStatusUniform dialog


CDlgDecWinStatusUniform::CDlgDecWinStatusUniform(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDecWinStatusUniform::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDecWinStatusUniform)
	m_dwAFrameNum = 0;
	m_byAFrameRate = 0;
	m_wPicHeight = 0;
	m_wPicWidth = 0;
	m_dwSubWinNum = 0;
	m_dwVFrameNum = 0;
	m_byVFrameRate = 0;
	m_dwWinNum = 1;
	m_dwWallNo = 1;
	//}}AFX_DATA_INIT
}


void CDlgDecWinStatusUniform::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDecWinStatusUniform)
	DDX_Control(pDX, IDC_COMBO_STREAM_TYPE, m_comboStreamType);
	DDX_Control(pDX, IDC_COMBO_PACK_TYPE, m_comboPackType);
	DDX_Control(pDX, IDC_COMBO_DEC_ENABLE, m_comboDecEnable);
	DDX_Text(pDX, IDC_EDIT_AFRAME_NUM, m_dwAFrameNum);
	DDX_Text(pDX, IDC_EDIT_AFRAME_RATE, m_byAFrameRate);
	DDX_Text(pDX, IDC_EDIT_PIC_H, m_wPicHeight);
	DDX_Text(pDX, IDC_EDIT_PIC_W, m_wPicWidth);
	DDX_Text(pDX, IDC_EDIT_SUB_WIN_NUM, m_dwSubWinNum);
	DDX_Text(pDX, IDC_EDIT_VFRAME_NUM, m_dwVFrameNum);
	DDX_Text(pDX, IDC_EDIT_VFRAME_RATE, m_byVFrameRate);
	DDX_Text(pDX, IDC_EDIT_WIN_NUM, m_dwWinNum);
	DDX_Text(pDX, IDC_EDIT_WINSTATUS_WALLNO, m_dwWallNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDecWinStatusUniform, CDialog)
	//{{AFX_MSG_MAP(CDlgDecWinStatusUniform)
	ON_BN_CLICKED(IDC_BTN_UPDATE, OnBtnUpdate)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDecWinStatusUniform message handlers

BOOL CDlgDecWinStatusUniform::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	memset(&m_struWallWinInfo, 0, sizeof(m_struWallWinInfo));
	memset(&m_struWallWinStatus, 0, sizeof(m_struWallWinStatus));
	OnBtnUpdate();
//	SetTimer(20, 3000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgDecWinStatusUniform::OnBtnUpdate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struWallWinInfo.dwSize = sizeof(NET_DVR_WALLWIN_INFO);
	m_struWallWinInfo.dwWinNum = m_dwWinNum;
	m_struWallWinInfo.dwSubWinNum = m_dwSubWinNum;
    m_struWallWinInfo.dwWallNo = m_dwWallNo; 
	if (!NET_DVR_GetDeviceStatus(m_lUserID, NET_DVR_MATRIX_GETWINSTATUS, 0, &m_struWallWinInfo, sizeof(NET_DVR_WALLWIN_INFO), NULL, &m_struWallWinStatus, sizeof(m_struWallWinStatus)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MATRIX_GETWINSTATUS");
	}
	else
	{
		ShowData();
	}

}

void CDlgDecWinStatusUniform::ShowData()
{
	if (m_struWallWinStatus.byDecodeStatus)
	{
		m_comboDecEnable.SetCurSel(1);
	}
	else
	{
		m_comboDecEnable.SetCurSel(0);
	}

	switch (m_struWallWinStatus.byStreamType)
	{
	case NET_DVR_ENCODER_UNKOWN:
		m_comboStreamType.SetCurSel(0);
		break;
	case NET_DVR_ENCODER_H264:
		m_comboStreamType.SetCurSel(1);
		break;
	case NET_DVR_ENCODER_S264:
		m_comboStreamType.SetCurSel(2);
		break;
	case NET_DVR_ENCODER_MPEG4:
		m_comboStreamType.SetCurSel(3);
		break;
	case NET_DVR_ORIGINALSTREAM:
		m_comboStreamType.SetCurSel(4);
		break;
	case NET_DVR_PICTURE:
		m_comboStreamType.SetCurSel(5);
		break;
	case NET_DVR_ENCODER_MJPEG:
		m_comboStreamType.SetCurSel(6);
		break;
	case NET_DVR_ENCODER_MPEG2:
		m_comboStreamType.SetCurSel(7);
		break;
	default:
		break;
	}

	switch (m_struWallWinStatus.byPacketType)
	{
	case NET_DVR_STREAM_TYPE_UNKOWN:
		m_comboPackType.SetCurSel(0);
		break;
	case NET_DVR_STREAM_TYPE_PRIVT:
		m_comboPackType.SetCurSel(1);
		break;
	case NET_DVR_STREAM_TYPE_TS:
		m_comboPackType.SetCurSel(2);
		break;
    case NET_DVR_STREAM_TYPE_PS:
		m_comboPackType.SetCurSel(3);
	    break;
	case NET_DVR_STREAM_TYPE_RTP:
		m_comboPackType.SetCurSel(4);
		break;
	case NET_DVR_STREAM_TYPE_ORIGIN:
		m_comboPackType.SetCurSel(5);
		break;
	default:
		break;
	}

	m_byVFrameRate = m_struWallWinStatus.byFpsDecV;
	m_byAFrameRate = m_struWallWinStatus.byFpsDecA;
	m_dwVFrameNum = m_struWallWinStatus.dwDecodedV;
	m_dwAFrameNum = m_struWallWinStatus.dwDecodedA;
	m_wPicWidth = m_struWallWinStatus.wImgW;
	m_wPicHeight = m_struWallWinStatus.wImgH;

	UpdateData(FALSE);
}


#if (_MSC_VER >= 1500)	//vs2008
void CDlgDecWinStatusUniform::OnTimer(UINT_PTR nIDEvent) 
#else
void CDlgDecWinStatusUniform::OnTimer(UINT nIDEvent) 
#endif
{
// 	// TODO: Add your message handler code here and/or call default
// 	if (nIDEvent == WALL_WINSTATUS_TIMER)
// 	{
// 		OnBtnUpdate();
// 	}
// 	CDialog::OnTimer(nIDEvent);
}
