/**********************************************************
FileName:    DlgPlayBack.cpp
Description: backplay main dialog box   
Date:        2008/05/17
Note: 		 <global>struct, refer to GeneralDef.h, global variants and functions refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgPlayBack.h"
#include ".\dlgplayback.h"


// CDlgPlayBack dialog
/*********************************************************
  Function:	CDlgPlayBack
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgPlayBack, CDialog)
CDlgPlayBack::CDlgPlayBack(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPlayBack::IDD, pParent)
	, m_iPlayBackType(0)
{
}
/*********************************************************
  Function:	~CDlgPlayBack
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgPlayBack::~CDlgPlayBack()
{
}
/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayBack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPlayBack)
	DDX_Control(pDX, IDC_TAB_PLAY_BACK, m_tabPlayBack);
        //}}AFX_DATA_MAP
	
}

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgPlayBack, CDialog)
	//{{AFX_MSG_MAP(CDlgPlayBack)	
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PLAY_BACK, OnTcnSelchangeTabPlayBack)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()


// CDlgPlayBack message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgPlayBack::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char szLan[1024] = {0};
	m_iPlayBackType = 0;
	g_StringLanType(szLan, "远程文件", "Remote file");
	m_tabPlayBack.InsertItem(0, szLan);
	m_dlgPlayRemoteFile.Create(IDD_DLG_PLAY_REMOTE_FILE,&m_tabPlayBack);
	m_dlgPlayRemoteFile.ShowWindow(SW_HIDE);

	g_StringLanType(szLan, "本地文件", "Local file");
	m_tabPlayBack.InsertItem(1, szLan);
	m_dlgPlayLocalFile.Create(IDD_DLG_PLAY_LOCAL_FILE,&m_tabPlayBack);
	m_dlgPlayLocalFile.ShowWindow(SW_HIDE);

	g_StringLanType(szLan, "时间回放", "By Time");
	m_tabPlayBack.InsertItem(2, szLan);
	m_dlgPlayRemoteTime.Create(IDD_DLG_PLAY_REMOTE_TIME, &m_tabPlayBack);
	m_dlgPlayRemoteTime.ShowWindow(SW_HIDE);
//2009-07-30

	g_StringLanType(szLan, "事件回放", "By Event");
	m_tabPlayBack.InsertItem(3, szLan);
	m_dlgPlayEvent.Create(IDD_DLG_PLAY_EVENT, &m_tabPlayBack);
	m_dlgPlayEvent.ShowWindow(SW_HIDE);

    g_StringLanType(szLan, "录像智能后检索", "By Motion");
    m_tabPlayBack.InsertItem(4, szLan);
    m_dlgPlayMotion.Create(IDD_DLG_PLAY_MOTION, &m_tabPlayBack);
    m_dlgPlayMotion.ShowWindow(SW_HIDE);

	g_StringLanType(szLan, "图片操作", "Pic Operate");
    m_tabPlayBack.InsertItem(5, szLan);
    m_dlgJpegPicDownload.Create(IDD_SUBDLG_PICTURE, &m_tabPlayBack);
    m_dlgJpegPicDownload.ShowWindow(SW_HIDE);

	g_StringLanType(szLan, "图片智能后检索", "Smart Pic Operate");
    m_tabPlayBack.InsertItem(6, szLan);
    m_dlgSmartSearchPic.Create(IDD_DLG_SMART_SEARCH_PIC, &m_tabPlayBack);
    m_dlgSmartSearchPic.ShowWindow(SW_HIDE);

    g_StringLanType(szLan, "录像标签", "Record label");
    m_tabPlayBack.InsertItem(7, szLan);
    m_dlgRecordLabel.Create(IDD_DLG_RECORD_LABEL, &m_tabPlayBack);
    m_dlgRecordLabel.ShowWindow(SW_HIDE);

	g_StringLanType(szLan,"录像段加锁","Lock File");
	m_tabPlayBack.InsertItem(8,szLan);
	m_dlgPlayLockFile.Create(IDD_DLG_PLAY_LOCK_FILE, &m_tabPlayBack);
    m_dlgPlayLockFile.ShowWindow(SW_HIDE);
	//2011-8-23

	g_StringLanType(szLan,"远程录像","Remote record");
	m_tabPlayBack.InsertItem(9,szLan);
	m_dlgPlayDvrRecord.Create(IDD_DLG_PLAY_DVR_RECORD,&m_tabPlayBack);
	m_dlgPlayDvrRecord.ShowWindow(SW_HIDE);
	//2011-8-25
	

	HWND hParentWnd[2]={m_hWnd,m_tabPlayBack.m_hWnd};
	m_dlgPlayRemoteFile.SetParentWnd(hParentWnd, 2);
	m_dlgPlayLocalFile.SetParentWnd(hParentWnd, 2);
	m_dlgPlayRemoteTime.SetParentWnd(hParentWnd, 2);
	m_dlgPlayEvent.SetParentWnd(hParentWnd, 2);
    m_dlgPlayMotion.SetParentWnd(hParentWnd, 2);
     m_dlgSmartSearchPic.SetParentWnd(hParentWnd, 2);
	m_dlgJpegPicDownload.SetParentWnd(hParentWnd, 2);
	m_dlgSmartSearchPic.SetParentWnd(hParentWnd, 2);
	m_dlgPlayLockFile.SetParentWnd(hParentWnd, 2);
	m_dlgPlayDvrRecord.SetParentWnd(hParentWnd,2);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
}

/*********************************************************
  Function:	PlayBackWinUpdate
  Desc:		updat playback window
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayBack::PlayBackWinUpdate()
{
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();

	switch (m_iPlayBackType)
	{
	case PLAY_REMOTE_FILE_T:
		m_dlgPlayRemoteFile.CheckInitParam();
		m_dlgPlayRemoteFile.ShowWindow(SW_SHOW);
		m_dlgPlayLocalFile.ShowWindow(SW_HIDE);
		m_dlgPlayRemoteTime.ShowWindow(SW_HIDE);
		m_dlgPlayEvent.ShowWindow(SW_HIDE);
        m_dlgPlayMotion.ShowWindow(SW_HIDE);
		m_dlgJpegPicDownload.ShowWindow(SW_HIDE);
        m_dlgRecordLabel.ShowWindow(SW_HIDE);
		m_dlgPlayLockFile.ShowWindow(SW_HIDE);
		m_dlgPlayDvrRecord.ShowWindow(SW_HIDE);
        m_dlgSmartSearchPic.ShowWindow(SW_HIDE);
		break;
	case PLAY_LOCAL_FILE_T:
		m_dlgPlayRemoteFile.ShowWindow(SW_HIDE);
		m_dlgPlayLocalFile.ShowWindow(SW_SHOW);
		m_dlgPlayEvent.ShowWindow(SW_HIDE);
		m_dlgPlayLocalFile.CheckInitParam();
		m_dlgPlayRemoteTime.ShowWindow(SW_HIDE);
        m_dlgPlayMotion.ShowWindow(SW_HIDE);
		m_dlgJpegPicDownload.ShowWindow(SW_HIDE);
        m_dlgRecordLabel.ShowWindow(SW_HIDE);
		m_dlgPlayLockFile.ShowWindow(SW_HIDE);
		m_dlgPlayDvrRecord.ShowWindow(SW_HIDE);
        m_dlgSmartSearchPic.ShowWindow(SW_HIDE);
		break;
	case PLAY_REMOTE_TIME_T:
		m_dlgPlayRemoteFile.ShowWindow(SW_HIDE);
		m_dlgPlayLocalFile.ShowWindow(SW_HIDE);
		m_dlgPlayEvent.ShowWindow(SW_HIDE);
        m_dlgPlayMotion.ShowWindow(SW_HIDE);
		m_dlgPlayRemoteTime.ShowWindow(SW_SHOW);
		m_dlgPlayRemoteTime.CheckInitParam();
		m_dlgJpegPicDownload.ShowWindow(SW_HIDE);
        m_dlgRecordLabel.ShowWindow(SW_HIDE);
		m_dlgPlayLockFile.ShowWindow(SW_HIDE);
		m_dlgPlayDvrRecord.ShowWindow(SW_HIDE);
        m_dlgSmartSearchPic.ShowWindow(SW_HIDE);
		break;
	case PLAY_REMOTE_EVENT_T:
		m_dlgPlayRemoteFile.ShowWindow(SW_HIDE);
		m_dlgPlayLocalFile.ShowWindow(SW_HIDE);
		m_dlgPlayRemoteTime.ShowWindow(SW_HIDE);
        m_dlgPlayMotion.ShowWindow(SW_HIDE);
		m_dlgPlayEvent.ShowWindow(SW_SHOW);
		m_dlgPlayEvent.CheckInitParam();
		m_dlgJpegPicDownload.ShowWindow(SW_HIDE);
        m_dlgRecordLabel.ShowWindow(SW_HIDE);
		m_dlgPlayLockFile.ShowWindow(SW_HIDE);
		m_dlgPlayDvrRecord.ShowWindow(SW_HIDE);
        m_dlgSmartSearchPic.ShowWindow(SW_HIDE);
		break;
    case PLAY_REMOTE_MOTION_T:
        m_dlgPlayRemoteFile.ShowWindow(SW_HIDE);
        m_dlgPlayLocalFile.ShowWindow(SW_HIDE);
        m_dlgPlayRemoteTime.ShowWindow(SW_HIDE);
        m_dlgPlayEvent.ShowWindow(SW_HIDE);
        m_dlgPlayMotion.ShowWindow(SW_SHOW);
		m_dlgJpegPicDownload.ShowWindow(SW_HIDE);
        m_dlgRecordLabel.ShowWindow(SW_HIDE);
		m_dlgPlayLockFile.ShowWindow(SW_HIDE);
		m_dlgPlayDvrRecord.ShowWindow(SW_HIDE);
        m_dlgPlayMotion.CheckInitParam();
        m_dlgSmartSearchPic.ShowWindow(SW_HIDE);
		break;
	case PLAY_REMOTE_PIC_T:
		m_dlgPlayRemoteFile.ShowWindow(SW_HIDE);
		m_dlgPlayLocalFile.ShowWindow(SW_HIDE);
		m_dlgPlayRemoteTime.ShowWindow(SW_HIDE);
        m_dlgPlayMotion.ShowWindow(SW_HIDE);
		m_dlgPlayEvent.ShowWindow(SW_HIDE);
        m_dlgJpegPicDownload.ShowWindow(SW_SHOW);
        m_dlgRecordLabel.ShowWindow(SW_HIDE);
		m_dlgPlayLockFile.ShowWindow(SW_HIDE);
		m_dlgPlayDvrRecord.ShowWindow(SW_HIDE);
        m_dlgJpegPicDownload.CheckInitParam();        
        m_dlgSmartSearchPic.ShowWindow(SW_HIDE);
        break;
    case PLAY_REMOTE_SMART_PIC_T:
        m_dlgPlayRemoteFile.ShowWindow(SW_HIDE);
        m_dlgPlayLocalFile.ShowWindow(SW_HIDE);
        m_dlgPlayRemoteTime.ShowWindow(SW_HIDE);
        m_dlgPlayMotion.ShowWindow(SW_HIDE);
        m_dlgPlayEvent.ShowWindow(SW_HIDE);
        m_dlgJpegPicDownload.ShowWindow(SW_HIDE);
        m_dlgRecordLabel.ShowWindow(SW_HIDE);
        m_dlgPlayLockFile.ShowWindow(SW_HIDE);
        m_dlgPlayDvrRecord.ShowWindow(SW_HIDE);
        m_dlgJpegPicDownload.ShowWindow(SW_HIDE);
        m_dlgSmartSearchPic.ShowWindow(SW_SHOW);
        m_dlgSmartSearchPic.CheckInitParam();
        break;
    case PLAY_RECORD_LABEL:
        m_dlgPlayRemoteFile.ShowWindow(SW_HIDE);
        m_dlgPlayLocalFile.ShowWindow(SW_HIDE);
        m_dlgPlayRemoteTime.ShowWindow(SW_HIDE);
        m_dlgPlayMotion.ShowWindow(SW_HIDE);
        m_dlgPlayEvent.ShowWindow(SW_HIDE);
        m_dlgJpegPicDownload.ShowWindow(SW_HIDE);
        m_dlgRecordLabel.ShowWindow(SW_SHOW);
        m_dlgPlayLockFile.ShowWindow(SW_HIDE);
		m_dlgPlayDvrRecord.ShowWindow(SW_HIDE);
        m_dlgRecordLabel.CheckInitParam();
        m_dlgSmartSearchPic.ShowWindow(SW_HIDE);
        break;
	case PLAY_LOCK_FILE_T:                         //2011-8-23
		m_dlgPlayRemoteFile.ShowWindow(SW_HIDE);
        m_dlgPlayLocalFile.ShowWindow(SW_HIDE);
        m_dlgPlayRemoteTime.ShowWindow(SW_HIDE);
        m_dlgPlayMotion.ShowWindow(SW_HIDE);
        m_dlgPlayEvent.ShowWindow(SW_HIDE);
        m_dlgJpegPicDownload.ShowWindow(SW_HIDE);
        m_dlgRecordLabel.ShowWindow(SW_HIDE);
		m_dlgPlayLockFile.ShowWindow(SW_SHOW);
		m_dlgPlayDvrRecord.ShowWindow(SW_HIDE);
        m_dlgPlayLockFile.CheckInitParam();
        m_dlgSmartSearchPic.ShowWindow(SW_HIDE);
        break;
	case PLAY_DVR_RECORD_T:                         //2011-8-25
		m_dlgPlayRemoteFile.ShowWindow(SW_HIDE);
        m_dlgPlayLocalFile.ShowWindow(SW_HIDE);
        m_dlgPlayRemoteTime.ShowWindow(SW_HIDE);
        m_dlgPlayMotion.ShowWindow(SW_HIDE);
        m_dlgPlayEvent.ShowWindow(SW_HIDE);
        m_dlgJpegPicDownload.ShowWindow(SW_HIDE);
        m_dlgRecordLabel.ShowWindow(SW_HIDE);
		m_dlgPlayLockFile.ShowWindow(SW_HIDE);
		m_dlgPlayDvrRecord.ShowWindow(SW_SHOW);
        m_dlgPlayDvrRecord.CheckInitParam();
        m_dlgSmartSearchPic.ShowWindow(SW_HIDE);
        break;
	default:
		break;
	}
}

/*********************************************************
  Function:	HideAll
  Desc:		hide all play back window when switch to other model
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgPlayBack::HideAll()
{
	m_dlgPlayRemoteFile.ShowWindow(SW_HIDE);
	m_dlgPlayLocalFile.ShowWindow(SW_HIDE);
	m_dlgPlayRemoteTime.ShowWindow(SW_HIDE);
	m_dlgPlayEvent.ShowWindow(SW_HIDE);
    m_dlgPlayMotion.ShowWindow(SW_HIDE);
	m_dlgJpegPicDownload.ShowWindow(SW_HIDE);
	m_dlgPlayLockFile.ShowWindow(SW_HIDE);//2011-8-23
	m_dlgPlayDvrRecord.ShowWindow(SW_HIDE);//2011-8-25
	m_dlgSmartSearchPic.ShowWindow(SW_HIDE);
	ShowWindow(SW_HIDE);
}


/*********************************************************
  Function:	FinishAll
  Desc:		close corresponding threads while exit playback dialog
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayBack::FinishAll()
{
	HideAll();
	m_dlgPlayRemoteFile.StopPlay();
	m_dlgPlayLocalFile.StopPlayBack();
	m_dlgPlayRemoteTime.StopPlay();
	m_dlgPlayEvent.StopPlay();
    m_dlgPlayEvent.StopPlay();
}

/*********************************************************
  Function:	OnTcnSelchangeTabPlayBack
  Desc:		playback model switch
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayBack::OnTcnSelchangeTabPlayBack(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);
	m_iPlayBackType =  m_tabPlayBack.GetCurSel();
	PlayBackWinUpdate();
	*pResult = 0;
}

//void CDlgPlayBack::OnMove(int x, int y) 
//{
//	CDialog::OnMove(x, y);
//
//	// TODO: Add your message handler code here
//	DWORD dwNewDeviceNum;
//	DWORD nVal;
//	int temp;
//
//	switch (m_iPlayBackType)
//	{
//	case 0:
//		if (m_dlgPlayRemoteFile.m_nPlayHandle == -1)
//		{
//			return;		
//		}	
//		GetWindowRect(&g_rcWindow);
//		if (g_rcWindow.left < 0)
//			return;
//		if (((DWORD)g_rcWindow.right + (DWORD)g_rcWindow.left > 2 * g_dwScreenWidth )||((DWORD)g_rcWindow.top + (DWORD)g_rcWindow.bottom > 2 * g_dwScreenHeight))
//		{
//			dwNewDeviceNum = 1;
//		}
//		else
//		{
//			dwNewDeviceNum = 0;	
//		}
//		if (dwNewDeviceNum != g_dwOldDeviceNum)
//		{
//#if (WINVER > 0x0400)
//			nVal = PlayM4_GetDDrawDeviceTotalNums();
//			//nVal = NET_DVR_GetDDrawDeviceTotalNums();
//			temp = NET_DVR_GetPlayBackPlayerIndex(m_dlgPlayRemoteFile.m_nPlayHandle);
//			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "temp is %d\n");
//			//NET_DVR_SetDDrawDevice(temp, dwNewDeviceNum + 1);
//			PlayM4_SetDDrawDevice(temp, dwNewDeviceNum + 1);
//#endif
//			g_dwOldDeviceNum = dwNewDeviceNum;		
//		}
//		break;
//	case 1:
//		GetWindowRect(&g_rcWindow);
//		if (g_rcWindow.left < 0)
//			return;
//		if (((DWORD)g_rcWindow.right + (DWORD)g_rcWindow.left > 2 * g_dwScreenWidth )||((DWORD)g_rcWindow.top + (DWORD)g_rcWindow.bottom > 2 * g_dwScreenHeight))
//		{
//			dwNewDeviceNum = 1;
//		}
//		else
//		{
//			dwNewDeviceNum = 0;	
//		}
//		if (dwNewDeviceNum != g_dwOldDeviceNum)
//		{
//#if (WINVER > 0x0400)
//			nVal = PlayM4_GetDDrawDeviceTotalNums();
//			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "nVal is %d\n", nVal);
//			PlayM4_SetDDrawDevice(99, dwNewDeviceNum + 1);	
//#endif
//			g_dwOldDeviceNum = dwNewDeviceNum;		
//		}
//		break;
//	case 2:
//		if (m_dlgPlayRemoteTime.m_lPlayHandle == -1)
//		{
//			return;
//		}
//		GetWindowRect(&g_rcWindow);
//		if (g_rcWindow.left < 0)
//			return;
//		if (((DWORD)g_rcWindow.right + (DWORD)g_rcWindow.left > 2 * g_dwScreenWidth )||((DWORD)g_rcWindow.top + (DWORD)g_rcWindow.bottom > 2 * g_dwScreenHeight))
//		{
//			dwNewDeviceNum = 1;
//		}
//		else
//		{
//			dwNewDeviceNum = 0;	
//		}
//		if (dwNewDeviceNum != g_dwOldDeviceNum)
//		{
//#if (WINVER > 0x0400)
//			//nVal = NET_DVR_GetDDrawDeviceTotalNums();
//			nVal = PlayM4_GetDDrawDeviceTotalNums();
//			temp = NET_DVR_GetPlayBackPlayerIndex(m_dlgPlayRemoteTime.m_lPlayHandle);
//			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "temp is %d\n");
//			//NET_DVR_SetDDrawDevice(temp, dwNewDeviceNum + 1);			
//			PlayM4_SetDDrawDevice(temp, dwNewDeviceNum + 1);			
//#endif
//			g_dwOldDeviceNum = dwNewDeviceNum;		
//		}
//		break;
//	default:
//		break;
//	}
//}

//void CDlgPlayBack::HideWnd()
//{
//	m_dlgPlayRemoteFile.StopPlay();
//	m_dlgPlayLocalFile.Stop();
//	m_dlgPlayRemoteTime.StopPlay();
//}
