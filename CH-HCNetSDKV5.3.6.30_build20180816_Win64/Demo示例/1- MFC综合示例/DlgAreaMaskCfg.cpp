// DlgAreaMaskCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAreaMaskCfg.h"
#include "VcaCommonOperations.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAreaMaskCfg dialog


RECT g_rectAreaMaskShow;
RECT g_rectMaskSetArea;

#define MASK_AREA_LEFT 62
#define MASK_AREA_TOP 90
#define MASK_AREA_RIGHT 385
#define MASK_AREA_BOTTOM 315


void CALLBACK AreaMaskGetCallBack(LONG nPort,HDC hDc,DWORD nUser)
{
	CRect rect;
	CPoint point;
	rect.left = g_rectMaskSetArea.left;
	rect.top = g_rectMaskSetArea.top;
	rect.right = g_rectMaskSetArea.right;
	rect.bottom = g_rectMaskSetArea.bottom;
	::DrawEdge(hDc,&rect,BDR_SUNKENOUTER,BF_RECT);
	SetBkMode(hDc,TRANSPARENT);
}

void CALLBACK AreaMaskSetCallBack(LONG nPort,HDC hDc,DWORD nUser)
{
	::DrawEdge(hDc,&g_rectAreaMaskShow,BDR_SUNKENOUTER,BF_RECT);
	SetBkMode(hDc,TRANSPARENT);
}


CDlgAreaMaskCfg::CDlgAreaMaskCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAreaMaskCfg::IDD, pParent)
	, m_bDrawdetect(FALSE)
	, m_lPlayHandle(-1)
    , m_bAutoMask(FALSE)
{
	//{{AFX_DATA_INIT(CDlgAreaMaskCfg)
	m_bChkEnableMask = FALSE;
	m_bChkMaskShow = FALSE;
	m_bChkMaskSet = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgAreaMaskCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgAreaMaskCfg)
    DDX_Control(pDX, IDC_CMB_CHAN, m_cmbChan);
    DDX_Control(pDX, IDC_PLAYWND, m_picAreaMask);
    DDX_Control(pDX, IDC_CMB_MASK_THICK, m_cmbMaskThick);
    DDX_Check(pDX, IDC_CHK_ENABLE, m_bChkEnableMask);
    DDX_Check(pDX, IDC_CHK_MASK_SHOW, m_bChkMaskShow);
    DDX_Check(pDX, IDC_CHK_MASK_SET, m_bChkMaskSet);
    //}}AFX_DATA_MAP
    DDX_Check(pDX, IDC_CHECK_AUTO_MASK, m_bAutoMask);
}


BEGIN_MESSAGE_MAP(CDlgAreaMaskCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAreaMaskCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_CHK_MASK_SHOW, OnBnClickedChkMaskShow)
	ON_BN_CLICKED(IDC_CHK_MASK_SET, OnBnClickedChkMaskSet)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_CMB_CHAN, OnSelchangeCmbChan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAreaMaskCfg message handlers

void CDlgAreaMaskCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	
	char szLan[128] = {0};
	NET_DVR_AREA_MASK_CFG struAreaMaskCfg = {0};
	memset(&struAreaMaskCfg, 0, sizeof(NET_DVR_AREA_MASK_CFG));
	
	DWORD dwReturnedBytes = 0;

	int iChannel = m_cmbChan.GetItemData(m_cmbChan.GetCurSel());
	
	if(NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_AREA_MASK_CFG, iChannel, &struAreaMaskCfg, sizeof(NET_DVR_AREA_MASK_CFG), &dwReturnedBytes))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_AREA_MASK_CFG");
		g_StringLanType(szLan, "获取马赛克区域配置成功!", "Success to get mask area parameter config");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_AREA_MASK_CFG");
		g_StringLanType(szLan, "获取马赛克区域配置失败!", "Fail to get mask area parameter config");
		AfxMessageBox(szLan);
		return;
	}
	
	m_bChkEnableMask = struAreaMaskCfg.byEnable;
	m_cmbMaskThick.SetCurSel(struAreaMaskCfg.byMaskThick);
    m_bAutoMask = struAreaMaskCfg.byAutoMask;
    CRect rcWnd;
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&rcWnd);

	g_rectMaskSetArea.left = struAreaMaskCfg.struRegion[0].fX *rcWnd.Width();
	g_rectMaskSetArea.top = struAreaMaskCfg.struRegion[0].fY * rcWnd.Height();
	g_rectMaskSetArea.right = (struAreaMaskCfg.struRegion[0].fX + struAreaMaskCfg.struRegion[0].fWidth)*rcWnd.Width();
	g_rectMaskSetArea.bottom = (struAreaMaskCfg.struRegion[0].fY + struAreaMaskCfg.struRegion[0].fHeight)*rcWnd.Height();

	UpdateData(FALSE);
}

void CDlgAreaMaskCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);

	int iChannel = m_cmbChan.GetItemData(m_cmbChan.GetCurSel());
	
	char szLan[128] = {0};
	NET_DVR_AREA_MASK_CFG struAreaMaskCfg = {0};
	memset(&struAreaMaskCfg, 0, sizeof(NET_DVR_AREA_MASK_CFG));
	
	struAreaMaskCfg.dwSize = sizeof(NET_DVR_AREA_MASK_CFG);

	struAreaMaskCfg.byEnable = m_bChkEnableMask;
	struAreaMaskCfg.byMaskThick = m_cmbMaskThick.GetCurSel();
    struAreaMaskCfg.byAutoMask = m_bAutoMask;
	
    CRect rcWnd ;
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&rcWnd);
	struAreaMaskCfg.struRegion[0].fX = g_rectMaskSetArea.left/1.0/rcWnd.Width();
	struAreaMaskCfg.struRegion[0].fY = g_rectMaskSetArea.top/1.0/rcWnd.Height();
	struAreaMaskCfg.struRegion[0].fHeight = (g_rectMaskSetArea.bottom - g_rectMaskSetArea.top)/1.0/rcWnd.Height();
	struAreaMaskCfg.struRegion[0].fWidth = (g_rectMaskSetArea.right - g_rectMaskSetArea.left)/1.0/rcWnd.Width();
	
	if(NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_AREA_MASK_CFG, iChannel, &struAreaMaskCfg, sizeof(NET_DVR_AREA_MASK_CFG)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_AREA_MASK_CFG");
		g_StringLanType(szLan, "设置马赛克区域配置成功!", "Success to set mask area parameter config");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_AREA_MASK_CFG");
		g_StringLanType(szLan, "设置马赛克区域配置失败!", "Fail to set mask area parameter config");
		AfxMessageBox(szLan);
		return;
	}
}

BOOL CDlgAreaMaskCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

 
	
	char szLan[128] = {0};
    m_cmbChan.ResetContent();
	
	int i;
	for ( i = 0; i <  g_struDeviceInfo[m_dwDevIndex].iDeviceChanNum; i++ )
	{	
		m_cmbChan.AddString(g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].chChanName);
		m_cmbChan.SetItemData(i, g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].iChannelNO);
	}
	
    m_cmbChan.AddString("Error Channel");
    m_cmbChan.SetItemData(g_struDeviceInfo[m_dwDevIndex].iDeviceChanNum, 0xffff);


	m_cmbChan.SetCurSel(0);
    OnBtnGet();

	NET_DVR_CLIENTINFO struPlayInfo;
	struPlayInfo.hPlayWnd = m_picAreaMask.GetSafeHwnd();
	struPlayInfo.lChannel = m_cmbChan.GetItemData(m_cmbChan.GetCurSel());
	struPlayInfo.lLinkMode = 0;
	struPlayInfo.sMultiCastIP = "";	 
	
	m_lPlayHandle = NET_DVR_RealPlay(m_lUserID, &struPlayInfo);	
	if (m_lPlayHandle == -1)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "网络连接失败", "Network connection failure");
		AfxMessageBox(szLan);
	}	
	m_bDrawdetect = FALSE;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgAreaMaskCfg::OnDestroy()
{
	if (m_lPlayHandle >= 0)
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL, 0);
		NET_DVR_StopRealPlay(m_lPlayHandle);
		m_lPlayHandle = -1;
	}

	CDialog::OnDestroy();
}

void CDlgAreaMaskCfg::OnStopPlay()
{
    if (m_lPlayHandle >= 0)
    {
        NET_DVR_StopRealPlay(m_lPlayHandle);
        m_lPlayHandle = -1;
    }
}

void CDlgAreaMaskCfg::OnStartPlay()
{
    NET_DVR_CLIENTINFO struPlayInfo;
    struPlayInfo.hPlayWnd = m_picAreaMask.GetSafeHwnd();
    struPlayInfo.lChannel = m_cmbChan.GetItemData(m_cmbChan.GetCurSel());
    struPlayInfo.lLinkMode = 0;
    struPlayInfo.sMultiCastIP = "";	 
    
    if (m_lPlayHandle >= 0)
    {
        NET_DVR_StopRealPlay(m_lPlayHandle);
        m_lPlayHandle = -1;
    }
    else
    {
        m_lPlayHandle = NET_DVR_RealPlay(m_lUserID,&struPlayInfo);
    }
}
void CDlgAreaMaskCfg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_bDrawdetect)
	{
		if (MK_CONTROL&nFlags)
		{			
			NET_DVR_RigisterDrawFun(m_lPlayHandle, AreaMaskSetCallBack, 0);

// 			if (!m_rcPlayWnd.PtInRect(point))
// 			{
// 				return;
// 			}
// 			g_rectMaskSetArea.left = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
// 			g_rectMaskSetArea.top = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
// 			g_rectMaskSetArea.right = g_rectMaskSetArea.left;
// 			g_rectMaskSetArea.bottom = g_rectMaskSetArea.top;
// 
// 			g_rectAreaMaskShow.left = g_rectMaskSetArea.left;
// 			g_rectAreaMaskShow.top = g_rectMaskSetArea.top;
// 			g_rectAreaMaskShow.right = g_rectMaskSetArea.right + 1;
// 			g_rectAreaMaskShow.bottom = g_rectMaskSetArea.bottom + 1;


			point.x -= MASK_AREA_LEFT;
			point.y -= MASK_AREA_LEFT;
			if (point.x < 0)
			{
				point.x = 0;
			}
			g_rectMaskSetArea.left=point.x/16*16;
			if (point.y < 0)
			{
				point.y = 0;
			}
			g_rectMaskSetArea.top=point.y/16*16;
			g_rectMaskSetArea.right=g_rectMaskSetArea.left;
			g_rectMaskSetArea.bottom=g_rectMaskSetArea.top;

			POINT tPoint=point;
			g_rectAreaMaskShow.left=tPoint.x/16*16;
			g_rectAreaMaskShow.top=tPoint.y/16*16;
			g_rectAreaMaskShow.right=tPoint.x/16*16+1;
			g_rectAreaMaskShow.bottom=tPoint.y/16*16+1;
		}
	}	
	CDialog::OnLButtonDown(nFlags, point);
}


void CDlgAreaMaskCfg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bDrawdetect)
	{
		if (MK_CONTROL&nFlags&&MK_LBUTTON&nFlags)
		{
// 			if (!m_rcPlayWnd.PtInRect(point))
// 			{
// 				return;
// 			}
// 			g_rectMaskSetArea.right  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
// 			g_rectMaskSetArea.bottom  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
// 
// 			g_rectAreaMaskShow.right = g_rectMaskSetArea.right;
// 			g_rectAreaMaskShow.bottom = g_rectMaskSetArea.bottom;

			point.x -= MASK_AREA_LEFT;
			point.y -= MASK_AREA_TOP;
			if (point.x > MASK_AREA_RIGHT)
			{
				point.x = MASK_AREA_RIGHT;
			}
			g_rectMaskSetArea.right=point.x/16*16;
			if (point.y > MASK_AREA_BOTTOM)
			{
				point.y = MASK_AREA_BOTTOM;
			}
			g_rectMaskSetArea.bottom=point.y/16*16;
			POINT tPoint=point;
			g_rectAreaMaskShow.right=tPoint.x/16*16;
			g_rectAreaMaskShow.bottom=tPoint.y/16*16;
		}
	}	
	CDialog::OnMouseMove(nFlags, point);
}


void CDlgAreaMaskCfg::OnBnClickedChkMaskShow()
{
	if (m_lPlayHandle < 0)
	{
		return;
	}
	UpdateData(TRUE);
	if (m_bChkMaskSet)
	{
		m_bChkMaskSet = FALSE;
		m_bDrawdetect = FALSE;
		UpdateData(FALSE);
		GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
	}
	if (m_bChkMaskShow)
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL, 0);
		Sleep(200);
		NET_DVR_RigisterDrawFun(m_lPlayHandle,AreaMaskGetCallBack, 0);
	}
	else
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL, 0);
	}
}


void CDlgAreaMaskCfg::OnBnClickedChkMaskSet() 
{
	// TODO: Add your control notification handler code here
	
	if (m_lPlayHandle < 0)
	{
		return;
	}
	UpdateData(TRUE);
	if (m_bChkMaskShow)
	{
		m_bChkMaskShow = FALSE;
		UpdateData(FALSE);
	}
	if (m_bChkMaskSet)
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL,0);
		m_bDrawdetect = TRUE;
		GetDlgItem(IDC_BTN_SET)->EnableWindow(TRUE);
	}
	else
	{
		m_bDrawdetect = FALSE;
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL,0);
		GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
	}
}

void CDlgAreaMaskCfg::OnSelchangeCmbChan() 
{
	// TODO: Add your control notification handler code here
	OnStopPlay();
    OnStartPlay();
}
