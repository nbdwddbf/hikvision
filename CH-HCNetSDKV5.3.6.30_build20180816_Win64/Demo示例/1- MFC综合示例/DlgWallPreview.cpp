// DlgWallPreview.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWallPreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void CALLBACK WallPictureDataCallback(LONG nScreenPicHandle, DWORD dwDataType, BYTE *pBuffer, DWORD nDataLen, void* pUser)
{
//     static int i=0; 
//     FILE *fp = NULL;  
//     char szFileName[128] = {0}; 
//     sprintf(szFileName, "./Jpeg/WinPreview_%d.jpeg", i); 
//     fp = fopen(szFileName, "wb"); 
//     fwrite(pBuffer, 1, nDataLen, fp); 
//     fclose(fp); 

    CDlgWallPreview *pPicPreview = static_cast<CDlgWallPreview*>(pUser);
    pPicPreview->DrawPicture(pBuffer, nDataLen);
}
/////////////////////////////////////////////////////////////////////////////
// CDlgWallPreview dialog


CDlgWallPreview::CDlgWallPreview(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWallPreview::IDD, pParent)
    ,m_lHandle(-1)
{
	//{{AFX_DATA_INIT(CDlgWallPreview)
	m_dwChannel = 0;
	m_csDeviceID = _T("");
	m_dwFrame = 0;
	m_dwLayerNo = 0;
	m_dwScreenNo = 0;
	m_dwSignalIndex = 0;
	m_dwWallNo = 1;
	m_dwSubWin = 0;
	m_dwWinNo = 1;
	m_iSourceType = -1;
	//}}AFX_DATA_INIT
}


void CDlgWallPreview::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWallPreview)
	DDX_Control(pDX, IDC_STATIC_VIDEOWALL_WINPREVIEW, m_StaPreview);
	DDX_Control(pDX, IDC_COMBO_VWP_RESOLUTION, m_CmResolution);
	DDX_Text(pDX, IDC_EDT_VWP_CHANNEL, m_dwChannel);
	DDV_MinMaxDWord(pDX, m_dwChannel, 0, 255);
	DDX_Text(pDX, IDC_EDT_VWP_DEVICEID, m_csDeviceID);
	DDX_Text(pDX, IDC_EDT_VWP_FRAME, m_dwFrame);
	DDV_MinMaxDWord(pDX, m_dwFrame, 0, 255);
	DDX_Text(pDX, IDC_EDT_VWP_LAYERNO, m_dwLayerNo);
	DDX_Text(pDX, IDC_EDT_VWP_SCREENNUM, m_dwScreenNo);
	DDX_Text(pDX, IDC_EDT_VWP_SIGNALINDEX, m_dwSignalIndex);
	DDX_Text(pDX, IDC_EDT_WINPREVIEW_WALLNO, m_dwWallNo);
	DDX_Text(pDX, IDC_EDT_WINPREVIEW_SUBWIN, m_dwSubWin);
	DDX_Text(pDX, IDC_EDT_WINPREVIEW_WINNO, m_dwWinNo);
	DDX_Radio(pDX, IDC_RAD_WINPREVIEW_SOURCETYPE, m_iSourceType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWallPreview, CDialog)
	//{{AFX_MSG_MAP(CDlgWallPreview)
	ON_BN_CLICKED(IDC_BUT_VIDEOWALL_WPICTURE_STOP, OnButWpictureStop)
	ON_BN_CLICKED(IDC_BUT_VIDEOWALL_WPICTURE_START, OnButWpictureStart)
	ON_BN_CLICKED(IDC_RAD_WINPREVIEW_SOURCETYPE, OnRadSourcetype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWallPreview message handlers

void CDlgWallPreview::OnButWpictureStop() 
{
	// TODO: Add your control notification handler code here
    if (m_lHandle == -1)              //没有开始回显
    {
        return ; 
    }
    char szLan[128] = {0}; 
    if (!NET_DVR_StopScreenPic(m_lHandle))
    {
        g_StringLanType(szLan, "停止回显失败", "Failed to stop preview picture"); 
        sprintf(szLan, "%s, Error code %d", szLan, NET_DVR_GetLastError());
        MessageBox(szLan); 
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "StopScreenPic");		
    }
    else
    {
        m_lHandle = -1;
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "StopScreenPic");
    }
    UpdateData(FALSE);   	
}

void CDlgWallPreview::OnButWpictureStart() 
{
	// TODO: Add your control notification handler code here
    if ( m_lHandle != -1)   //已经开始回显
    {
        OnButWpictureStop(); 
    }
    UpdateData(TRUE);
    char szLan[128]= {0}; 
    NET_DVR_START_PIC_VIEW_INFO struPicView={0};
    struPicView.dwSize = sizeof(struPicView);
//    struPicView.dwSignalIndex = m_dwSignalIndex; 
    struPicView.dwSignalIndex = m_dwWinNo + (m_dwSubWin<<16) + (m_dwWinNo<<24); 
    struPicView.byChanIndex = (BYTE)m_dwChannel; 
    struPicView.dwScreenNum = m_dwScreenNo; 
    struPicView.dwLayer = m_dwLayerNo; 
    struPicView.dwResolution = m_CmResolution.GetCurSel() + 1; 
    struPicView.byFrame = (BYTE)m_dwFrame; 
    m_lHandle = NET_DVR_StartPicPreview(m_lUserID, &struPicView, WallPictureDataCallback, this);
    if (m_lHandle == -1)
    {
        g_StringLanType(szLan, "回显图片失败", "Failed to Preview Picture"); 
        sprintf(szLan, "%s, Error Code %d", szLan, NET_DVR_GetLastError());
        MessageBox(szLan); 
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "start screen picture failed\n");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "start screen picture SUCC\n");
	}
}

void CDlgWallPreview::DrawPicture(BYTE* pBuffer, int nSize)
{
    CDC* pDC = m_StaPreview.GetDC();
    CRect struRect;
    m_StaPreview.GetClientRect(&struRect);	
    pDC->SetViewportOrg(0, struRect.bottom);
    struRect.bottom = -struRect.bottom;	
    if (m_Picture.m_pPict != NULL)
    {
        m_Picture.UnloadPicture();
    }
    m_Picture.LoadPictureData(pBuffer, nSize);
    m_Picture.Render(pDC, &struRect, NULL);
	m_StaPreview.ReleaseDC(pDC);  
}

void CDlgWallPreview::OnRadSourcetype() 
{
	// TODO: Add your control notification handler code here
// 	UpdateData(TRUE); 
//     if ( m_iSourceType )
//     {
//         GetDlgItem(IDC_EDT_WINPREVIEW_WALLNO)->EnableWindow()
//     }
//     else
//     {
// 
//     }
}

void CDlgWallPreview::OnCancel() 
{
	// TODO: Add extra cleanup here
    if (m_lHandle != -1)              //没有开始回显
    {
        OnButWpictureStop();
    }
	CDialog::OnCancel();
}
