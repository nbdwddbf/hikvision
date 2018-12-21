// DlgVcaFindBackgroundPic.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaFindBackgroundPic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFindBackgroundPic dialog


CDlgVcaFindBackgroundPic::CDlgVcaFindBackgroundPic(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaFindBackgroundPic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaFindBackgroundPic)
	m_dwFacePicID = 0;
	m_csPicPath = _T("");
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_iDevIndex = -1;
}


void CDlgVcaFindBackgroundPic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaFindBackgroundPic)
	DDX_Control(pDX, IDC_PIC, m_PicWnd);
	DDX_Text(pDX, IDC_EDIT_FACEPIC_ID, m_dwFacePicID);
	DDX_Text(pDX, IDC_EDIT_PIC_PATH, m_csPicPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaFindBackgroundPic, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaFindBackgroundPic)
	ON_BN_CLICKED(IDC_BTN_FIND, OnBtnFind)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFindBackgroundPic message handlers

void CDlgVcaFindBackgroundPic::OnBtnFind() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CRect struRect; 
	DWORD dwPicLen = 0;
	BYTE *pRecvBuf = NULL;
	pRecvBuf = new BYTE[2*1024*1024];
	memset(pRecvBuf, 0, 2*1024*1024);
	if (!NET_DVR_FindBackgroundPic(m_lServerID, m_dwFacePicID, pRecvBuf, &dwPicLen))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FindBackgroundPic");
		delete []pRecvBuf;
		pRecvBuf = NULL;
		return;
	}
	else
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_FindBackgroundPic");
	}
	if (dwPicLen > 0)
    {       
        char cFilename[256] = {0};
        HANDLE hFile;
        DWORD dwReturn;
        
        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
        
        sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIP);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }
        
        sprintf(cFilename, "%s\\LocalTime[BG][%s].jpg",cFilename, chTime);
		m_csPicPath.Format("%s", cFilename);
        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, pRecvBuf, dwPicLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;

		if(!m_picture.LoadPicture(cFilename))
		{
			AfxMessageBox("Fail to reload picture");
            return;
		}
		GetDlgItem(IDC_PIC)->Invalidate(FALSE);

		GetDlgItem(IDC_PIC)->GetClientRect(&struRect);
		CPaintDC dc2(GetDlgItem(IDC_PIC));
        m_picture.DrawPicture(dc2.m_hDC, struRect.left, struRect.top, struRect.Width(), struRect.Height());
	}

	if (pRecvBuf != NULL)
	{
		delete []pRecvBuf;
		pRecvBuf = NULL;
	}
	UpdateData(FALSE);
}
