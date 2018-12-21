// DlgVcaFaceSnapCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaFaceSnapCfg.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFaceSnapCfg dialog
CDlgVcaFaceSnapCfg *g_pDlgVcaFaceSnap = NULL;

void  CALLBACK g_DrawFaceSnap(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    SetBkMode(hDc, TRANSPARENT);
    SetTextColor(hDc, RGB(255, 255, 255));
    
    g_pDlgVcaFaceSnap->F_DrawFun(lRealHandle, hDc, dwUser);
}

void CDlgVcaFaceSnapCfg::F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser)
{
    F_DrawFrame(hDc);
}
void CDlgVcaFaceSnapCfg::F_DrawFrame(HDC hDc)
{
    DRAW_POLYGON_PARAM struPolygonParam;
    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    struPolygonParam.color = RGB(255, 255, 0);
    memcpy(&struPolygonParam.rcWnd, &m_rcWnd, sizeof(m_rcWnd));
    memcpy(&struPolygonParam.struVcaPolygon, &m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon, sizeof(struPolygonParam.struVcaPolygon));
    struPolygonParam.bCloseIn = m_bCloseIn;
    struPolygonParam.bMouseMove = m_bMouseMove;
    
    CDrawFun::DrawVcaPolygon(hDc, &struPolygonParam);
	
    if (m_bChkFilterActive)
    {
        DRAW_RECT_PARAM struDrawRect;
        memset(&struDrawRect, 0, sizeof(struDrawRect));
        struDrawRect.color = RGB(0, 255, 125);
        memcpy(&struDrawRect.rcWnd, &m_rcWnd, sizeof(struDrawRect.rcWnd));
        memcpy(&struDrawRect.struVcaRect, &m_struFaceSnap.struRule[m_dwRuleNum].struSizeFilter.struMaxRect, sizeof(struDrawRect.struVcaRect));
        CDrawFun::DrawVcaRect(hDc, &struDrawRect);
        
        memset(&struDrawRect, 0, sizeof(struDrawRect));
        struDrawRect.color = RGB(0, 255, 125);
        memcpy(&struDrawRect.rcWnd, &m_rcWnd, sizeof(struDrawRect.rcWnd));
        memcpy(&struDrawRect.struVcaRect, &m_struFaceSnap.struRule[m_dwRuleNum].struSizeFilter.struMiniRect, sizeof(struDrawRect.struVcaRect));
        CDrawFun::DrawVcaRect(hDc, &struDrawRect);
    }
}

CDlgVcaFaceSnapCfg::CDlgVcaFaceSnapCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaFaceSnapCfg::IDD, pParent)
    , m_FaceFilteringTime(0)
{
	//{{AFX_DATA_INIT(CDlgVcaFaceSnapCfg)
	m_bChkFilterActive = FALSE;
	m_bDrawPolygon = FALSE;
	m_bChkEnable = FALSE;
	m_byRate = 0;
	m_bSetMiniFilter = FALSE;
	m_bSetMaxFilter = FALSE;
	m_bySnapInterval = 0;
	m_bySnapThreshold = 0;
	m_byReferBright = 0;
	m_byMatchThreshold = 0;
	m_dwFaceExposureMinDuration = 0;
	m_dwTerminalNo = 0;
	m_dwUploadInterval = 0;
	m_dwValidFaceMinDuration = 0;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_lChannel  = -1;
    m_iDevIndex = -1;
    memset(&m_struFaceSnap, 0, sizeof(m_struFaceSnap));
    m_lPlayHandle = -1;
    memset(&m_rcWnd, 0, sizeof(m_rcWnd));
    m_bCloseIn = FALSE;
    m_bMouseMove = FALSE;
    m_bNeedRedraw = FALSE;
	m_dwRuleNum = 0;
    m_byInvalCapFilterThreshold = 0;
}


void CDlgVcaFaceSnapCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaFaceSnapCfg)
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
	DDX_Control(pDX, IDC_COMBO_ROI, m_comROI);
	DDX_Control(pDX, IDC_COMBO_FACE_ENABLE, m_comFaceEnable);
	DDX_Control(pDX, IDC_COMBO_BACK_GROUND, m_comBackgroundPic);
	DDX_Control(pDX, IDC_COMBO_MATCH_ALATM_TYPE, m_comboMatchType);
	DDX_Control(pDX, IDC_COMBO_SENSITIVE, m_comboSensitive);
	DDX_Control(pDX, IDC_COMBO_SNAPTIMES, m_comboSnapTimes);
	DDX_Control(pDX, IDC_COMBO_RULE_NUM, m_comboRuleNum);
	DDX_Control(pDX, IDC_COMBO_PIC_QUALITY, m_comboPicQuality);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_comboPicResolution);
	DDX_Check(pDX, IDC_CHECK_FILTER_ACTIVE, m_bChkFilterActive);
	DDX_Check(pDX, IDC_CHK_DRAW_POLYGON, m_bDrawPolygon);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bChkEnable);
	DDX_Text(pDX, IDC_EDIT_RATE, m_byRate);
	DDX_Check(pDX, IDC_CHECK_SET_MINI_FILTER, m_bSetMiniFilter);
	DDX_Check(pDX, IDC_CHECK_SET_MAX_FILTER, m_bSetMaxFilter);
	DDX_Text(pDX, IDC_EDIT_SNAP_INTERVAL, m_bySnapInterval);
	DDX_Text(pDX, IDC_EDIT_SNAP_THRESHOLD, m_bySnapThreshold);
	DDX_Text(pDX, IDC_EDIT_REFERENCE_BRIGHT, m_byReferBright);
	DDX_Text(pDX, IDC_EDIT_MATCH_THRESHOLD, m_byMatchThreshold);
	DDX_Text(pDX, IDC_EDIT_FACE_MIN_DURA, m_dwFaceExposureMinDuration);
	DDX_Text(pDX, IDC_EDIT_TERMINAL_NO, m_dwTerminalNo);
	DDX_Text(pDX, IDC_EDIT_UPLOAD_INTERVAL, m_dwUploadInterval);
	DDX_Text(pDX, IDC_EDIT_VALID_FACE_MIN_DURATION, m_dwValidFaceMinDuration);
	DDX_Text(pDX, IDC_EDIT_FACEFILTER_TIME, m_FaceFilteringTime);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_COMBO_SCENEID, m_comSceneID);
	DDX_Control(pDX, IDC_COMBO_INVALCAPFILTER, m_comInvalCapFilterEnable);
	DDX_Text(pDX, IDC_EDIT_INVALCAPFILTERTHRESHOLD, m_byInvalCapFilterThreshold);
}


BEGIN_MESSAGE_MAP(CDlgVcaFaceSnapCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaFaceSnapCfg)
	ON_BN_CLICKED(IDC_BTN_SURE, OnBtnSure)
	ON_BN_CLICKED(IDC_BTN_SET_FACESNAP, OnBtnSetFacesnap)
	ON_BN_CLICKED(IDC_CHECK_SET_MINI_FILTER, OnCheckSetMiniFilter)
	ON_BN_CLICKED(IDC_CHECK_SET_MAX_FILTER, OnCheckSetMaxFilter)
	ON_BN_CLICKED(IDC_CHECK_FILTER_ACTIVE, OnCheckFilterActive)
	ON_BN_CLICKED(IDC_CHK_DRAW_POLYGON, OnChkDrawPolygon)
	ON_CBN_SELCHANGE(IDC_COMBO_RULE_NUM, OnSelchangeComboRuleNum)
	ON_BN_CLICKED(IDC_BTN_GET_FACESNAP, OnBtnGetFacesnap)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnSelchangeComboChannel)
	ON_BN_CLICKED(IDC_BTN_EVENT_SEARCH_LIST, OnBtnEventSearchList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFaceSnapCfg message handlers
BOOL CDlgVcaFaceSnapCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (g_struDeviceInfo[m_iDevIndex].iDeviceType == DS_D60S) //信息发布服务器
	{
		GetDlgItem(IDC_EDIT_TERMINAL_NO)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_TERMINAL_NO)->EnableWindow(FALSE);
	}
    m_comSceneID.SetCurSel(0);
	g_AddChanInfoToComBox(m_cmbChannel, m_iDevIndex);
    m_lChannel = (LONG)(m_dwTerminalNo <<16 | (DWORD)m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel()));

    m_bNeedRedraw = TRUE;//Redraw polygon
    m_bCloseIn = TRUE;//Polygon is closed or not
	
    g_pDlgVcaFaceSnap = this;
	m_comboRuleNum.SetCurSel(0);
	m_dwRuleNum = 0;
	m_comboSnapTimes.SetCurSel(0);
	
    if (!GetFaceSnap())
    {
        AfxMessageBox("Fail to get face snap");
    }
	
    StartPlay();
	
    SetFaceSnapToWnd(m_struFaceSnap);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

LONG CDlgVcaFaceSnapCfg::StartPlay()
{
	UpdateData(TRUE);
    m_lChannel = (LONG)(m_dwTerminalNo <<16 | (DWORD)m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel()));
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
        bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, g_DrawFaceSnap, 0);//DC Draw callback
    }
    return m_lPlayHandle;
}

BOOL CDlgVcaFaceSnapCfg::GetFaceSnap()
{
	UpdateData(TRUE);
    m_lChannel = (LONG)(m_dwTerminalNo <<16 | (DWORD)m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel()));

    DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_FACESNAPCFG, m_lChannel, &m_struFaceSnap, sizeof(m_struFaceSnap), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_FACESNAPCFG Chan[%d]", m_lChannel);
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_FACESNAPCFG Chan[%d]", m_lChannel);
		SetFaceSnapToWnd(m_struFaceSnap);
        return TRUE;
    }
	
	UpdateData(FALSE);
}

void CDlgVcaFaceSnapCfg::SetFaceSnapToWnd(NET_VCA_FACESNAPCFG const &struFaceSnap)
{
    m_bChkEnable = struFaceSnap.struRule[m_dwRuleNum].byActive;
	m_bChkFilterActive = struFaceSnap.struRule[m_dwRuleNum].struSizeFilter.byActive;
	m_comboSensitive.SetCurSel(struFaceSnap.bySensitive - 1);
	m_comboSnapTimes.SetCurSel(struFaceSnap.bySnapTime);
	m_byRate = struFaceSnap.byGenerateRate;
	m_bySnapInterval = struFaceSnap.bySnapInterval;
	m_bySnapThreshold = struFaceSnap.bySnapThreshold;
	m_comboPicQuality.SetCurSel(struFaceSnap.struPictureParam.wPicQuality);
	m_comboPicResolution.SetCurSel(struFaceSnap.struPictureParam.wPicSize);
	m_byReferBright = struFaceSnap.byReferenceBright;
	m_comboMatchType.SetCurSel(struFaceSnap.byMatchType);
	m_byMatchThreshold = struFaceSnap.byMatchThreshold;
	//2014-03-21
	m_dwFaceExposureMinDuration = struFaceSnap.wFaceExposureMinDuration;
	m_comFaceEnable.SetCurSel(struFaceSnap.byFaceExposureMode);
	m_comBackgroundPic.SetCurSel(struFaceSnap.byBackgroundPic);
	m_comROI.SetCurSel(struFaceSnap.struRule[m_dwRuleNum].byAutoROIEnable);
	m_dwUploadInterval = struFaceSnap.dwUploadInterval;
	m_dwValidFaceMinDuration = struFaceSnap.dwValidFaceTime;
    m_FaceFilteringTime = struFaceSnap.dwFaceFilteringTime;
    m_comSceneID.SetCurSel(struFaceSnap.bySceneID);
    m_comInvalCapFilterEnable.SetCurSel(struFaceSnap.byInvalCapFilterEnable);
    m_byInvalCapFilterThreshold = struFaceSnap.byInvalCapFilterThreshold;
    UpdateData(FALSE);	
}

BOOL CDlgVcaFaceSnapCfg::PreDrawPolygonMsg(MSG* pMsg, CPoint &pt)
{
    int i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;

    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && 
            PtInRect(&m_rcWnd,pt))
        {

                if(m_bNeedRedraw)
                {			
                    if(m_bCloseIn)
                    {
                        m_dwPosNum = 0;
                        m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.dwPointNum = m_dwPosNum;		
                    }
                    if(m_dwPosNum>9)
                    {
                        char szLan[128] = {0};
                        g_StringLanType(szLan,"多边形顶点不能超过10个!","Apexes of polygon should less than 10");
                        AfxMessageBox(szLan);
                        return TRUE;
                    }
                    if((float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() <= m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() >= m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.struPos[m_dwPosNum-1].fX-0.01\
                        && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() <= m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() >= m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.struPos[m_dwPosNum-1].fY-0.01)
                    {
                        char szLan[128] = {0};
                        g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
                        AfxMessageBox(szLan);
                        return TRUE;
                    }
                    m_bCloseIn = FALSE;
                    m_bMouseMove = FALSE;
                    m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                    m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                    m_dwPosNum++;
                    m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.dwPointNum = m_dwPosNum;	
                    
            }
            
        }
        break;
    case WM_MOUSEMOVE:
        if ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && 
            PtInRect(&m_rcWnd,pt))
        {
                if(PtInRect(&m_rcWnd,pt))
                {
                    if(m_dwPosNum > 9)
                    {
                        return TRUE;
                    }
                    if( m_bNeedRedraw && !m_bCloseIn)
                    {
                        m_bMouseMove = TRUE;
                        m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                        m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                        m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.dwPointNum = m_dwPosNum+1;				
                    }
                }
        }

        break;
    case WM_RBUTTONDOWN:
        if((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) 
            && PtInRect(&m_rcWnd,pt))
        {
                if(m_dwPosNum > 9)
                {
                    return TRUE;
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.struPos[i].fX != m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.struPos[i+1].fX)
                    {
                        bXOneLine = FALSE;
                        break;
                    }
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.struPos[i].fY != m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.struPos[i+1].fY)
                    {
                        bYOneLine = FALSE;
                        break;
                    }
                }
                bOneLine = bXOneLine||bYOneLine;
                if(bOneLine)
                {
                    char szlan[128] = {0};
                    g_StringLanType(szlan, "所画点成一线，无法构成区域!","The points is on a line and can't create a rectangle!");
                    AfxMessageBox(szlan);
                    return TRUE;
                }
                if( m_bNeedRedraw && !m_bCloseIn)
                {
                    if(m_bMouseMove)
                    {
                        m_bMouseMove = FALSE;
                        m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.dwPointNum--;
                        m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.struPos[m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.dwPointNum].fX = 0;
                        m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.struPos[m_struFaceSnap.struRule[m_dwRuleNum].struVcaPolygon.dwPointNum].fY = 0;
                    }
                    m_bCloseIn = TRUE;
                }
		}
        break;
    }
    return TRUE;
}

BOOL CDlgVcaFaceSnapCfg::PreDrawSizeFilterMsg(MSG* pMsg, CPoint &pt)
{
    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if(m_bSetMiniFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                m_struFaceSnap.struRule[m_dwRuleNum].struSizeFilter.struMiniRect.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struFaceSnap.struRule[m_dwRuleNum].struSizeFilter.struMiniRect.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
            }
        }//First coordinate of Maximal Rectangle
        else if(m_bSetMaxFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                m_struFaceSnap.struRule[m_dwRuleNum].struSizeFilter.struMaxRect.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struFaceSnap.struRule[m_dwRuleNum].struSizeFilter.struMaxRect.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
            }
        }
        break;
    case WM_MOUSEMOVE:
        if(m_bSetMiniFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)) //尺寸过滤器
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                m_struFaceSnap.struRule[m_dwRuleNum].struSizeFilter.struMiniRect.fWidth = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() - m_struFaceSnap.struRule[m_dwRuleNum].struSizeFilter.struMiniRect.fX;
                m_struFaceSnap.struRule[m_dwRuleNum].struSizeFilter.struMiniRect.fHeight = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() - m_struFaceSnap.struRule[m_dwRuleNum].struSizeFilter.struMiniRect.fY;
            }
            
        }
        else if(m_bSetMaxFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)) //尺寸过滤器
        {
            if(PtInRect(&m_rcWnd,pt))
            {	
                m_struFaceSnap.struRule[m_dwRuleNum].struSizeFilter.struMaxRect.fWidth = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() - m_struFaceSnap.struRule[m_dwRuleNum].struSizeFilter.struMaxRect.fX;
                m_struFaceSnap.struRule[m_dwRuleNum].struSizeFilter.struMaxRect.fHeight = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() - m_struFaceSnap.struRule[m_dwRuleNum].struSizeFilter.struMaxRect.fY;
            }
        }
        break;
    }
    
    return TRUE;
}

BOOL CDlgVcaFaceSnapCfg::SetFaceSnap()
{
	for (int i=0; i<MAX_RULE_NUM; i++)
	{
		if (m_struFaceSnap.struRule[i].struVcaPolygon.dwPointNum < 3 && m_struFaceSnap.struRule[i].struVcaPolygon.dwPointNum >0)
		{
			AfxMessageBox("多边形区域不符合要求!");
			return FALSE;
		}
	}
	
	UpdateData(TRUE);
    m_lChannel = (LONG)(m_dwTerminalNo <<16 | (DWORD)m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel()));
	
	m_struFaceSnap.dwSize = sizeof(m_struFaceSnap);
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_FACESNAPCFG, m_lChannel, &m_struFaceSnap, sizeof(m_struFaceSnap)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_FACESNAPCFG Chan[%d]", m_lChannel);
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_FACESNAPCFG Chan[%d]", m_lChannel);
        return TRUE;
    }
}

void CDlgVcaFaceSnapCfg::GetFaceSnapFromWnd(NET_VCA_FACESNAPCFG& struFaceSnap)
{
    UpdateData(TRUE);
	m_dwRuleNum = m_comboRuleNum.GetCurSel();
    struFaceSnap.byGenerateRate = m_byRate;
	struFaceSnap.struRule[m_dwRuleNum].byActive = m_bChkEnable;
	struFaceSnap.bySnapTime = m_comboSnapTimes.GetCurSel();
	struFaceSnap.bySensitive = m_comboSensitive.GetCurSel()+1;
	struFaceSnap.struRule[m_dwRuleNum].struSizeFilter.byActive = m_bChkFilterActive;
	struFaceSnap.bySnapInterval = m_bySnapInterval;
	struFaceSnap.bySnapThreshold = m_bySnapThreshold;
	struFaceSnap.struPictureParam.wPicQuality = m_comboPicQuality.GetCurSel();
	struFaceSnap.struPictureParam.wPicSize = m_comboPicResolution.GetCurSel();
	struFaceSnap.byReferenceBright = m_byReferBright;
	struFaceSnap.byMatchThreshold = m_byMatchThreshold;
	struFaceSnap.byMatchType = m_comboMatchType.GetCurSel();
	//2014-03-21
	struFaceSnap.wFaceExposureMinDuration = m_dwFaceExposureMinDuration;
	struFaceSnap.byFaceExposureMode = m_comFaceEnable.GetCurSel();
	struFaceSnap.byBackgroundPic = m_comBackgroundPic.GetCurSel();
	struFaceSnap.struRule[m_dwRuleNum].byAutoROIEnable = m_comROI.GetCurSel();
	struFaceSnap.dwUploadInterval = m_dwUploadInterval;
	struFaceSnap.dwValidFaceTime = m_dwValidFaceMinDuration;
    struFaceSnap.dwFaceFilteringTime = m_FaceFilteringTime;

    struFaceSnap.bySceneID = m_comSceneID.GetCurSel();
    struFaceSnap.byInvalCapFilterEnable = m_comInvalCapFilterEnable.GetCurSel();
    struFaceSnap.byInvalCapFilterThreshold = m_byInvalCapFilterThreshold;
}

void CDlgVcaFaceSnapCfg::OnBtnSure() 
{
	// TODO: Add your control notification handler code here
	GetFaceSnapFromWnd(m_struFaceSnap);
}

void CDlgVcaFaceSnapCfg::OnBtnSetFacesnap() 
{
	// TODO: Add your control notification handler code here
	if (!SetFaceSnap())
    {
        AfxMessageBox("Fail to set face snap");
    }
    else
    {
        AfxMessageBox("Succ to set face snap");
    }
}

// BOOL CDlgVcaFaceSnapCfg::PreTranslateMessage(MSG* pMsg) 
// {
// 	// TODO: Add your specialized code here and/or call the base class
// 	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWnd);
//     
//     CPoint pt(0,0);
//     GetCursorPos(&pt);
//     
//     if (m_bDrawPolygon)
//     {
//         PreDrawPolygonMsg(pMsg, pt);
//     }
//     else if (m_bSetMiniFilter || m_bSetMaxFilter)
//     {
//         PreDrawSizeFilterMsg(pMsg, pt);
//     }
// 	
// 	return CDialog::PreTranslateMessage(pMsg);
// }

void CDlgVcaFaceSnapCfg::OnCheckSetMiniFilter() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    if (m_bSetMiniFilter)
    {
        m_bSetMaxFilter = FALSE;
        m_bDrawPolygon = FALSE;
        UpdateData(FALSE);
    }
}

void CDlgVcaFaceSnapCfg::OnCheckSetMaxFilter() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    if (m_bSetMaxFilter)
    {
        m_bSetMiniFilter = FALSE;
        m_bDrawPolygon = FALSE;
        UpdateData(FALSE);
    }
}

void CDlgVcaFaceSnapCfg::OnCheckFilterActive() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    GetDlgItem(IDC_CHECK_SET_MAX_FILTER)->EnableWindow(m_bChkFilterActive);
    GetDlgItem(IDC_CHECK_SET_MINI_FILTER)->EnableWindow(m_bChkFilterActive);
}

BOOL CDlgVcaFaceSnapCfg::StopPlay()
{
    if (m_lPlayHandle >= 0)
    {
        NET_DVR_StopRealPlay(m_lPlayHandle);
        m_lPlayHandle = -1;
    }
    return TRUE;
}

void CDlgVcaFaceSnapCfg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	StopPlay();
	CDialog::PostNcDestroy();
}

BOOL CDlgVcaFaceSnapCfg::PreTranslateMessage(MSG* pMsg) 
{
	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWnd);  
	CPoint pt(0,0);
	GetCursorPos(&pt);    
	if (m_bDrawPolygon)
	{
	    PreDrawPolygonMsg(pMsg, pt);
	}
    else if (m_bSetMiniFilter || m_bSetMaxFilter)
	{
		PreDrawSizeFilterMsg(pMsg, pt);
	}
		
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgVcaFaceSnapCfg::OnChkDrawPolygon() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CDlgVcaFaceSnapCfg::OnSelchangeComboRuleNum() 
{
	// TODO: Add your control notification handler code here
// 	m_bChkEnable = m_struFaceSnap.struRule[m_dwRuleNum].byActive;
// 	m_bChkFilterActive = m_struFaceSnap.struRule[m_dwRuleNum].struSizeFilter.byActive;
// 	m_comROI.SetCurSel(m_struFaceSnap.struRule[m_dwRuleNum].byAutoROIEnable);
}

void CDlgVcaFaceSnapCfg::OnBtnGetFacesnap() 
{
	// TODO: Add your control notification handler code here
	GetFaceSnap();
}

void CDlgVcaFaceSnapCfg::OnSelchangeComboChannel() 
{
	// TODO: Add your control notification handler code here
	StopPlay();
    StartPlay();
}

void CDlgVcaFaceSnapCfg::OnBtnEventSearchList() 
{
	// TODO: Add your control notification handler code here
	
}
