// DLGCreateWall.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DLGCreateWall.h"


#include "DlgWallVirLED.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std; 
/////////////////////////////////////////////////////////////////////////////
// CDLGCreateWall dialog


CDLGCreateWall::CDLGCreateWall(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGCreateWall::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGCreateWall)
	m_BEnable = FALSE;
	m_csName = _T("");
	m_byWallNo = 0;
	m_dwWidth = 0;
	m_dwX = 0;
	m_dwY = 0;
	m_dwHeight = 0;
	//}}AFX_DATA_INIT
    m_pXMLBuf = NULL;
    m_byMaxWallNo = 0xff; 
    m_byMinWallNo = 1;   
}


void CDLGCreateWall::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGCreateWall)
	DDX_Check(pDX, IDC_CHK_VIDEOWALL_DISPLAY_ENABLE, m_BEnable);
	DDX_Text(pDX, IDC_EDT_VIDEOWALL_DISPALY_NAME, m_csName);
	DDX_Text(pDX, IDC_EDT_VIDEOWALL_DISPLAY_WALLNO, m_byWallNo);
	DDX_Text(pDX, IDC_EDT_VIDEOWALL_DISPLAY_WIDTH, m_dwWidth);
	DDX_Text(pDX, IDC_EDT_VIDEOWALL_DISPLAY_XCOORDIANTE, m_dwX);
	DDX_Text(pDX, IDC_EDT_VIDEOWALL_DISPLAY_YCOORDINATE, m_dwY);
	DDX_Text(pDX, IDC_EDT_VIDEOWALL_DISPLAY_HEIGHT, m_dwHeight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGCreateWall, CDialog)
	//{{AFX_MSG_MAP(CDLGCreateWall)
	ON_BN_CLICKED(IDC_BTN_VIDEOWALL_DISPLAY_CREATE_REFRESH, OnBtnWallRefresh)
	ON_BN_CLICKED(IDC_BTN_VIDEOWALL_DISPLAY_CREATE_SET, OnBtnWallSet)
	ON_BN_CLICKED(IDC_BTN_VIDEOWALL_S_OUTPUT_SET, OnBtnOutputSet)
	ON_BN_CLICKED(IDC_BTN_VIDEOWALL_S_WIN_SET, OnBtnWinSet)
	ON_BN_CLICKED(IDC_BTN_VIDEOWALL_S_VIRLED_SET, OnBtnVirLEDSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGCreateWall message handlers

void CDLGCreateWall::OnBtnWallRefresh() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    NET_DVR_VIDEOWALLDISPLAYMODE struDisplayMode = {0}; 
    struDisplayMode.dwSize = sizeof(struDisplayMode);
    
    DWORD dwRet;   
    char szLan[128] ={0}; 
    DWORD dwChannelEx = m_byWallNo; 
    dwChannelEx <<= 24; 
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_VIDEOWALLDISPLAYMODE, dwChannelEx, &struDisplayMode, sizeof(struDisplayMode), &dwRet))
    {
        g_StringLanType(szLan, "刷新墙失败", "Failed to refresh VideWall");
        sprintf(szLan, "%s Error Code %d", szLan, NET_DVR_GetLastError()); 
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEOWALLDISPLAYNO");
    }
    else
    {
        m_BEnable = struDisplayMode.byEnable; 
        m_csName.Format("%s", struDisplayMode.sName); 
        m_dwX = struDisplayMode.struRect.dwXCoordinate; 
        m_dwY= struDisplayMode.struRect.dwYCoordinate; 
        m_dwWidth= struDisplayMode.struRect.dwWidth; 
        m_dwHeight=  struDisplayMode.struRect.dwHeight; 
    }
    UpdateData(FALSE); 
}


void CDLGCreateWall::OnBtnWallSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    NET_DVR_VIDEOWALLDISPLAYMODE struDisplayMode = {0}; 
    struDisplayMode.dwSize = sizeof(struDisplayMode);
    struDisplayMode.byEnable = m_BEnable; 
    if ( m_csName.GetLength() == 0)
    {
        struDisplayMode.sName[0] = 0; 
    }
    else    
        strcpy((char*)struDisplayMode.sName, (LPCTSTR)m_csName); 

    struDisplayMode.struRect.dwXCoordinate = m_dwX; 
    struDisplayMode.struRect.dwYCoordinate = m_dwY; 
    struDisplayMode.struRect.dwWidth = m_dwWidth; 
    struDisplayMode.struRect.dwHeight = m_dwHeight; 
    char szLan[128] ={0}; 
    DWORD dwChannelEx = m_byWallNo; 
    dwChannelEx <<= 24; 
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_VIDEOWALLDISPLAYMODE, dwChannelEx, &struDisplayMode, sizeof(struDisplayMode)))
    {
        g_StringLanType(szLan, "创建墙失败", "Set fail");
        sprintf(szLan, "%s Error Code %d", szLan, NET_DVR_GetLastError()); 
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_VIDEOWALLDISPLAYMODE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_VIDEOWALLDISPLAYMODE");
        OnBtnWallRefresh(); 
	}
}

#include "DlgWallCfgUniform.h"
void CDLGCreateWall::OnBtnOutputSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    CDlgWallCfg_Uniform dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex; 
    dlg.m_byInitWallNo = m_byWallNo; 
	dlg.DoModal();
}

#include "DlgWallWinVideoWall.h"
void CDLGCreateWall::OnBtnWinSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    CDlgWallWinVideoWall dlg; 
    dlg.m_byWallNo = m_byWallNo; 
    dlg.m_lUserID = m_lUserID; 
    dlg.m_iDeviceIndex = m_iDeviceIndex; 
    dlg.DoModal(); 
}

void CDLGCreateWall::OnBtnVirLEDSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CDlgWallVirLED dlg; 
    dlg.m_lUserID = m_lUserID; 
    dlg.m_iDeviceIndex = m_iDeviceIndex; 
    dlg.m_byWallNo = m_byWallNo; 
    dlg.DoModal(); 
}


void CDLGCreateWall::GetXMLAbility()
{
    if ( m_pXMLBuf == NULL)
    {
        m_pXMLBuf = new char[XML_BUF]; 
    }  
    CString csError; 
    if ( !NET_DVR_GetDeviceAbility(m_lUserID, WALL_ABILITY, NULL, 0, m_pXMLBuf, XML_BUF))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDeviceAbility");
        csError.Format("获取墙能力集错误, Error Code %d", NET_DVR_GetLastError() ); 
    }
    else
    {
        CXmlBase xmlBase; 
        xmlBase.Parse(m_pXMLBuf);
        xmlBase.SetRoot();
        xmlBase.IntoElem();              // 跳过最外层<WallAbility version="2.0">
        stringstream  iTrans; 
        if (xmlBase.FindElem("wallNO"))
        {
            iTrans << xmlBase.GetAttributeValue("max"); 
            iTrans >> m_byMaxWallNo; 
            iTrans << xmlBase.GetAttributeValue("min"); 
            iTrans >> m_byMinWallNo; 
        }
    }
    delete [] m_pXMLBuf; 
    m_pXMLBuf = NULL; 
}