// DlgWinPreview.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWinPreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWinPreview dialog


CDlgWinPreview::CDlgWinPreview(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWinPreview::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWinPreview)
	m_wChannel = 0;
	m_csPassword = _T("12345");
	m_wPort = 8000;
	m_csAddress = _T("172.9.129.118");
	m_dwSubWinNo = 0;
	m_csUserName = _T("admin");
	m_dwWinNo = 0;
	//}}AFX_DATA_INIT
}


void CDlgWinPreview::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWinPreview)
	DDX_Control(pDX, IDC_COMBO_RESOURCE_TYPE, m_comboResourceType);
	DDX_Control(pDX, IDC_STATIC_PREVIEW, m_staticPreview);
	DDX_Text(pDX, IDC_EDIT_CHANNEL, m_wChannel);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassword);
	DDX_Text(pDX, IDC_EDIT_PORT, m_wPort);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_csAddress);
	DDX_Text(pDX, IDC_EDIT_SUBWIN_NO, m_dwSubWinNo);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_csUserName);
	DDX_Text(pDX, IDC_EDIT_WIN_NO, m_dwWinNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWinPreview, CDialog)
	//{{AFX_MSG_MAP(CDlgWinPreview)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_LOGIN, OnBtnLogin)
	ON_BN_CLICKED(IDC_BTN_PRE_START, OnBtnPreStart)
	ON_BN_CLICKED(IDC_BTN_PRE_STOP, OnBtnPreStop)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWinPreview message handlers

void CALLBACK PictureDataCallback(LONG nScreenPicHandle, DWORD dwDataType, BYTE *pBuffer, DWORD nDataLen, void* pUser)
{
	CDlgWinPreview *pPicPreview = static_cast<CDlgWinPreview*>(pUser);
	pPicPreview->DrawPicture(pBuffer, nDataLen);
}

BOOL CDlgWinPreview::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_lDecID = -1;
	m_lHandle = -1;
	m_picture = NULL;
	m_iDeviceIndex = g_pMainDlg->GetCurChanIndex();
    memset(&m_struWinIndexInfo, 0 , sizeof(m_struWinIndexInfo));
	memset(&m_struDecChanInfo, 0, sizeof(m_struDecChanInfo));
	memset(&m_struPicPreviewInfo, 0, sizeof(m_struPicPreviewInfo));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgWinPreview::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    m_struWinIndexInfo.dwWinIndex = m_dwWinNo;
	m_struWinIndexInfo.dwSubWinIndex = m_dwSubWinNo;
	m_struWinIndexInfo.byType = m_comboResourceType.GetCurSel() + 1;

	if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_WINASSOCIATEDDEVINFO, 0, &m_struWinIndexInfo, sizeof(m_struWinIndexInfo), NULL, &m_struDecChanInfo, sizeof(m_struDecChanInfo)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WINASSOCIATEDDEVINFO");
		AfxMessageBox(NET_DVR_GetErrorMsg());		
	}
	else
	{
		m_csAddress.Format("%s", m_struDecChanInfo.sAddress);
		m_wPort = m_struDecChanInfo.wDVRPort;
		m_wChannel = m_struDecChanInfo.wChannel;
		m_csPassword.Format("%s", m_struDecChanInfo.sPassword);
		m_csUserName.Format("%s", m_struDecChanInfo.sUserName);
		UpdateData(FALSE);
	}
}

void CDlgWinPreview::OnBtnLogin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_lDecID != -1)
	{
		NET_DVR_Logout_V30(m_lDecID);
		m_lDecID = -1;
	}
	char sAddress[MAX_DOMAIN_NAME] = {0};
	char sUserName[NAME_LEN] = {0};
	char sPassword[PASSWD_LEN] = {0};
	NET_DVR_DEVICEINFO_V30 struDevInfo = {0};
	strncpy(sAddress, m_csAddress, m_csAddress.GetLength());
	strncpy(sUserName, m_csUserName, m_csUserName.GetLength());
	strncpy(sPassword, m_csPassword, m_csPassword.GetLength());

	m_lDecID = NET_DVR_Login_V30(sAddress, m_wPort, sUserName, sPassword, &struDevInfo);
	if (m_lDecID == -1)
	{
		AfxMessageBox(NET_DVR_GetErrorMsg());
	}
	else
	{
		AfxMessageBox("Success");
	}
}

void CDlgWinPreview::OnBtnPreStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_lDecID == -1)
	{
		AfxMessageBox("Î´µÇÂ¼");
		return;
	}
	if (m_lHandle != -1)
	{
		OnBtnPreStop();
	}
	try
	{
		m_picture = new CPicture_Ex;
	}
	catch(...)
	{
		AfxMessageBox("·ÖÅäÄÚ´æÊ§°Ü");
	}
	m_struPicPreviewInfo.dwSize = sizeof(m_struPicPreviewInfo);
	m_struPicPreviewInfo.dwSignalIndex = m_wChannel;

	m_lHandle = NET_DVR_StartPicPreview(m_lDecID, &m_struPicPreviewInfo, PictureDataCallback, this);
	if (m_lHandle == -1)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "start screen picture failed\n");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "start screen picture SUCC\n");
	}
}

void CDlgWinPreview::OnBtnPreStop() 
{
	// TODO: Add your control notification handler code here
	if (m_lHandle != -1)
	{
		if (!NET_DVR_StopScreenPic(m_lHandle))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "StopScreenPic");
			AfxMessageBox("Í£Ö¹Ê§°Ü");			
		}
		else
		{
			m_lHandle = -1;
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "StopScreenPic");
		}
		if (m_picture != NULL)
		{
			delete m_picture;
			m_picture = NULL;
		}
	}
	else
	{
		AfxMessageBox("Î´¿ªÊ¼»ØÏÔ");
	}
	Invalidate();
}

void CDlgWinPreview::DrawPicture(BYTE* pBuffer, int nSize)
{
	CDC* pDC = m_staticPreview.GetDC();
	CRect struRect;
	m_staticPreview.GetClientRect(&struRect);	
	pDC->SetViewportOrg(0, struRect.bottom);
	struRect.bottom = -struRect.bottom;	
	if (NULL == m_picture)
	{
		m_picture = new CPicture_Ex;	
	}
	if (m_picture->m_pPict != NULL)
	{
		m_picture->UnloadPicture();
	}
	m_picture->LoadPictureData(pBuffer, nSize);
	m_picture->Render(pDC, &struRect, NULL);
	m_staticPreview.ReleaseDC(pDC);
}

CDlgWinPreview::~CDlgWinPreview()
{
	if (m_lHandle != -1)
	{
		if (!NET_DVR_StopScreenPic(m_lHandle))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "StopScreenPic");						
		}
		else
		{
			m_lHandle = -1;
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "StopScreenPic");
		}
		if (m_picture != NULL)
		{
			delete m_picture;
			m_picture = NULL;
		}
	}
}

void CDlgWinPreview::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
