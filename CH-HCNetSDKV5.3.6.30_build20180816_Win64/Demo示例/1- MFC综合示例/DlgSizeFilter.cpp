// DlgSizeFilter.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSizeFilter.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSizeFilter dialog
CDlgSizeFilter *g_pDlgSizeFilter = NULL;

void  CALLBACK g_DrawSizeFilter(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    g_pDlgSizeFilter->F_DrawFun(lRealHandle, hDc, dwUser);
}

CDlgSizeFilter::CDlgSizeFilter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSizeFilter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSizeFilter)
	m_bActive = FALSE;
	m_fMaxHeight = 0.0f;
	m_fMaxWidth = 0.0f;
	m_fMinHeight = 0.0f;
	m_fMinWidth = 0.0f;
	m_bSetMaxFilter = FALSE;
	m_bSetMiniFilter = FALSE;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_lChannel = -1;
    m_iDevIndex = -1;
    memset(&m_struSizeFilter, 0, sizeof(m_struSizeFilter));
    m_bPreview = FALSE;
    m_lPlayHandle = -1;
    memset(&m_rcWnd, 0, sizeof(m_rcWnd));
    m_lPUServerID = -1;
    memset(&m_struPuStream, 0, sizeof(m_struPuStream));
    m_nFilterMode = -1;
}


void CDlgSizeFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSizeFilter)
	DDX_Control(pDX, IDC_COMBO_MODE, m_comboMode);
	DDX_Check(pDX, IDC_CHK_ACTIVE, m_bActive);
	DDX_Text(pDX, IDC_EDIT_MAX_HEIGHT, m_fMaxHeight);
	DDX_Text(pDX, IDC_EDIT_MAX_WIDTH, m_fMaxWidth);
	DDX_Text(pDX, IDC_EDIT_MIN_HEIGHT, m_fMinHeight);
	DDX_Text(pDX, IDC_EDIT_MIN_WIDTH, m_fMinWidth);
	DDX_Check(pDX, IDC_CHECK_SET_MAX_FILTER, m_bSetMaxFilter);
	DDX_Check(pDX, IDC_CHECK_SET_MINI_FILTER, m_bSetMiniFilter);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgSizeFilter, CDialog)
	//{{AFX_MSG_MAP(CDlgSizeFilter)
	ON_BN_CLICKED(IDC_BTN_SET_SIZE_FILTER, OnBtnSetSizeFilter)
	ON_CBN_SELCHANGE(IDC_COMBO_MODE, OnSelchangeComboMode)
	ON_BN_CLICKED(IDC_CHK_ACTIVE, OnChkActive)
	ON_BN_CLICKED(IDC_CHECK_SET_MINI_FILTER, OnCheckSetMiniFilter)
	ON_BN_CLICKED(IDC_CHECK_SET_MAX_FILTER, OnCheckSetMaxFilter)
	ON_BN_CLICKED(IDC_BTN_PREVIEW, OnBtnPreview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSizeFilter message handlers

void CDlgSizeFilter::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlgSizeFilter::OnBtnSetSizeFilter() 
{
    char szLan[256] ={0};
    UpdateData(TRUE);
    m_struSizeFilter.byActive = m_bActive;
    m_struSizeFilter.byMode = m_comboMode.GetCurSel();
    if (IMAGE_PIX_MODE == m_comboMode.GetCurSel())
    {
    }
    else if (REAL_WORLD_MODE == m_comboMode.GetCurSel())
    {
        m_struSizeFilter.struMaxRect.fHeight = m_fMaxHeight;
        m_struSizeFilter.struMaxRect.fWidth= m_fMaxWidth;
        
        m_struSizeFilter.struMiniRect.fHeight = m_fMinHeight;
        m_struSizeFilter.struMiniRect.fWidth= m_fMinWidth;
    }

    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_VCA_SET_SIZE_FILTER, m_lChannel, &m_struSizeFilter, sizeof(m_struSizeFilter)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_VCA_SET_SIZE_FILTER");
        g_StringLanType(szLan, "设置尺寸过滤器失败", "Fail to set size filter");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_VCA_SET_SIZE_FILTER");
        g_StringLanType(szLan, "设置尺寸过滤器成功", "Success to set size filter");
        AfxMessageBox(szLan);
    }
    	
}

BOOL CDlgSizeFilter::OnInitDialog() 
{
	CDialog::OnInitDialog();
    g_pDlgSizeFilter = this;

    InitWnd();

    DWORD dwReturn = 0;
    char szLan[256] = {0};
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_VCA_GET_SIZE_FILTER, m_lChannel, &m_struSizeFilter, sizeof(m_struSizeFilter), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_VCA_GET_SIZE_FILTER");
        g_StringLanType(szLan, "获取尺寸过滤器失败", "Fail to get size filter");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_VCA_GET_SIZE_FILTER");
    }

    m_bActive = m_struSizeFilter.byActive;
    m_fMaxHeight = m_struSizeFilter.struMaxRect.fHeight;
    m_fMaxWidth = m_struSizeFilter.struMaxRect.fWidth;

    m_fMinHeight = m_struSizeFilter.struMiniRect.fHeight;
    m_fMinWidth = m_struSizeFilter.struMiniRect.fWidth;

    m_comboMode.SetCurSel(m_struSizeFilter.byMode);
    OnSelchangeComboMode();

    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSizeFilter::InitWnd()
{
    char szLan[128] = {0};
    m_comboMode.ResetContent();

    g_StringLanType(szLan, "像素模式", "Image pix mode");
    m_comboMode.AddString(szLan);

    g_StringLanType(szLan, "实际模式", "Real word mode");
    m_comboMode.AddString(szLan);
}

void CDlgSizeFilter::OnSelchangeComboMode() 
{
    m_nFilterMode = m_comboMode.GetCurSel();
    GetDlgItem(IDC_EDIT_MAX_HEIGHT)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_MAX_WIDTH)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_MIN_HEIGHT)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_MIN_WIDTH)->EnableWindow(FALSE);
    GetDlgItem(IDC_CHECK_SET_MAX_FILTER)->EnableWindow(FALSE);
    GetDlgItem(IDC_CHECK_SET_MINI_FILTER)->EnableWindow(FALSE);
    int iFilterMode = m_comboMode.GetCurSel();

    if (IMAGE_PIX_MODE == iFilterMode)
    {
        GetDlgItem(IDC_CHECK_SET_MAX_FILTER)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHECK_SET_MINI_FILTER)->EnableWindow(TRUE);
    }
    else if (REAL_WORLD_MODE == iFilterMode)
    {
        GetDlgItem(IDC_EDIT_MAX_HEIGHT)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_MAX_WIDTH)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_MIN_HEIGHT)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_MIN_WIDTH)->EnableWindow(TRUE);
    }
}



void CDlgSizeFilter::OnChkActive() 
{
	UpdateData(TRUE);
}

void CDlgSizeFilter::OnCheckSetMiniFilter() 
{
    UpdateData(TRUE);
    if (m_bSetMiniFilter)
    {
        m_bSetMaxFilter = FALSE;
        UpdateData(FALSE);
    }
}

void CDlgSizeFilter::OnCheckSetMaxFilter() 
{
	UpdateData(TRUE);
    if (m_bSetMaxFilter)
    {
        m_bSetMiniFilter = FALSE;
        UpdateData(FALSE);
    }
}

void CDlgSizeFilter::OnBtnPreview() 
{
	if (m_bPreview)
	{
        StopPlay();
        GetDlgItem(IDC_BTN_PREVIEW)->SetWindowText("Preview");
        m_bPreview = FALSE;
	}
    else
    {
        if (-1 != StartPlay())
        {
            GetDlgItem(IDC_BTN_PREVIEW)->SetWindowText("Stop");
            m_bPreview = TRUE;
        }
        else
        {
            AfxMessageBox("Fail to preview");
        }
    }
    Invalidate(TRUE);
}

LONG CDlgSizeFilter::StartPlay()
{
    if (GetPuStreamCfg(m_struPuStream))
    {
        NET_DVR_DEVICEINFO_V30 struDeviceInfo = {0};
        
        m_lPUServerID = NET_DVR_Login_V30(m_struPuStream.struDevChanInfo.struIP.sIpV4, m_struPuStream.struDevChanInfo.wDVRPort,
            (char*)m_struPuStream.struDevChanInfo.sUserName, (char*)m_struPuStream.struDevChanInfo.sPassword, &struDeviceInfo);
        if (m_lPUServerID < 0)
        {
            AfxMessageBox("Fail to login front device");
            return m_lPUServerID;
        }
        
        NET_DVR_CLIENTINFO struPlay;
        struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
        struPlay.lChannel 	= m_struPuStream.struDevChanInfo.byChannel; 
        struPlay.lLinkMode 	= 0;
        struPlay.sMultiCastIP = "";	
        
        m_lPlayHandle = NET_DVR_RealPlay_V30(m_lPUServerID, &struPlay, NULL, NULL, TRUE); 
        
        BOOL bRet = FALSE;
        if (m_lPlayHandle < 0)
        {
            g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
            AfxMessageBox("NET_DVR_RealPlay_V30 FAIL");		
        }
        else
        {
            g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
            bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, g_DrawSizeFilter, 0);//DC Draw callback
        }
        return m_lPlayHandle;
    }
    else // 到设备去取流预览
    {
    NET_DVR_CLIENTINFO struPlay;
    struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
    struPlay.lChannel 	= m_lChannel; 
    struPlay.lLinkMode 	= 0;
    struPlay.sMultiCastIP = "";	
    
    m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struPlay, NULL, NULL, TRUE); 
    BOOL bRet = FALSE;
    if (m_lPlayHandle < 0)
    {
        g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
        AfxMessageBox("NET_DVR_RealPlay_V30 FAIL");		
    }
    else
    {
        g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
            g_pDlgSizeFilter = this;
        bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, g_DrawSizeFilter, 0);//DC Draw callback
            
    }
    return m_lPlayHandle;
}
}

BOOL CDlgSizeFilter::StopPlay()
{
    if (m_lPlayHandle >= 0)
    {
        NET_DVR_StopRealPlay(m_lPlayHandle);
        m_lPlayHandle = -1;
    }
    
    if (m_lPUServerID >= 0)
    {
        NET_DVR_Logout_V30(m_lPUServerID);
        m_lPUServerID = -1;
    }
    return TRUE;
}

void CDlgSizeFilter::PostNcDestroy() 
{
    StopPlay();	
	CDialog::PostNcDestroy();
}

BOOL CDlgSizeFilter::PreTranslateMessage(MSG* pMsg) 
{
	
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWnd);
    
    CPoint pt(0,0);
    GetCursorPos(&pt);

    PreDrawSizeFilterMsg(pMsg, pt);
    return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDlgSizeFilter::PreDrawSizeFilterMsg(MSG* pMsg, CPoint &pt)
{
    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if(m_bSetMiniFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                m_struSizeFilter.struMiniRect.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struSizeFilter.struMiniRect.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
            }
        }//First coordinate of Maximal Rectangle
        else if(m_bSetMaxFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                m_struSizeFilter.struMaxRect.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struSizeFilter.struMaxRect.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
            }
        }
        break;
    case WM_MOUSEMOVE:
        if(m_bSetMiniFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)) //尺寸过滤器
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                m_struSizeFilter.struMiniRect.fWidth = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() - m_struSizeFilter.struMiniRect.fX;
                m_struSizeFilter.struMiniRect.fHeight = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() - m_struSizeFilter.struMiniRect.fY;
            }
            
        }
        else if(m_bSetMaxFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)) //尺寸过滤器
        {
            if(PtInRect(&m_rcWnd,pt))
            {	
                m_struSizeFilter.struMaxRect.fWidth = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() - m_struSizeFilter.struMaxRect.fX;
                m_struSizeFilter.struMaxRect.fHeight = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() - m_struSizeFilter.struMaxRect.fY;
            }
        }
        break;
    }
    return TRUE;
}

void CDlgSizeFilter::F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser)
{
    if (IMAGE_PIX_MODE == m_nFilterMode)
    {
        DRAW_RECT_PARAM struDrawRect;
        memset(&struDrawRect, 0, sizeof(struDrawRect));
        struDrawRect.color = RGB(0, 255, 125);
        memcpy(&struDrawRect.rcWnd, &m_rcWnd, sizeof(struDrawRect.rcWnd));
        memcpy(&struDrawRect.struVcaRect, &m_struSizeFilter.struMaxRect, sizeof(struDrawRect.struVcaRect));
        CDrawFun::DrawVcaRect(hDc, &struDrawRect);
        
        memset(&struDrawRect, 0, sizeof(struDrawRect));
        struDrawRect.color = RGB(0, 255, 125);
        memcpy(&struDrawRect.rcWnd, &m_rcWnd, sizeof(struDrawRect.rcWnd));
		memcpy(&struDrawRect.struVcaRect, &m_struSizeFilter.struMiniRect, sizeof(struDrawRect.struVcaRect));
        CDrawFun::DrawVcaRect(hDc, &struDrawRect);
    }
}

BOOL CDlgSizeFilter::GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream)
{
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PU_STREAMCFG,m_lChannel, &struPUStream, sizeof(struPUStream), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PU_STREAMCFG");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PU_STREAMCFG");
        return FALSE;
    }
}