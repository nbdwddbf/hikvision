// DlgVcaLaneCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaLaneCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaLaneCfg dialog
CDlgVcaLaneCfg *g_pDlgVcaLancCfg;

typedef enum tagDRAW_TYPE
{
    DRAWPOLYGON = 1,
    DRAWDIRECTION
}DRAW_TYPE;
void CALLBACK g_DrawLane(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
//     SetBkMode(hDc, TRANSPARENT);
    //    if(g_pDlgVcaRuleCfg->m_bRuleActive)
    {
        g_pDlgVcaLancCfg->F_DrawFun(lRealHandle, hDc, dwUser); 
    }
    
}

CDlgVcaLaneCfg::CDlgVcaLaneCfg(CWnd* pParent /*=NULL*/)
: CDialog(CDlgVcaLaneCfg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgVcaLaneCfg)
	m_bEnbale = FALSE;
	m_csLaneName = _T("");
	//}}AFX_DATA_INIT
    m_dwDrawType = 0;
    m_lPlayHandle = -1;
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_lChannel = -1;
    memset(&m_struLaneCfg, 0, sizeof(m_struLaneCfg));
    memset(m_struVcaPolygon, 0, sizeof(m_struVcaPolygon));
    m_lPUServerID = -1;
    memset(&m_struPUStream, 0, sizeof(m_struPUStream));

    memset(m_bCloseIn, 0, sizeof(m_bCloseIn));
    memset(m_bNeedRedraw, 0, sizeof(m_bNeedRedraw));
    memset(m_bMouseMove, 0, sizeof(m_bMouseMove));
    m_dwPosNum = -1;
    m_iCurLaneID = -1;   
    memset(&m_rcWnd, 0, sizeof(m_rcWnd));
    m_bDirectMouseMove = FALSE;
    m_dwDrawType = -1;

}


void CDlgVcaLaneCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgVcaLaneCfg)
    DDX_Control(pDX, IDC_COMBO_LANE_INDEX, m_comboLaneIndex);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnbale);
	DDX_Text(pDX, IDC_EDIT_LANE_NAME, m_csLaneName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaLaneCfg, CDialog)
//{{AFX_MSG_MAP(CDlgVcaLaneCfg)
ON_BN_CLICKED(IDC_BTN_SET_LANECFG, OnBtnSetLanecfg)
ON_CBN_SELCHANGE(IDC_COMBO_LANE_INDEX, OnSelchangeComboLaneIndex)
	ON_BN_CLICKED(IDC_RADIO_DRAW_POLYGON, OnRadioDrawPolygon)
	ON_BN_CLICKED(IDC_RADIO_DRAW_DIRECTION, OnRadioDrawDirection)
	ON_BN_CLICKED(IDC_BTN_CONFIRM, OnBtnConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaLaneCfg message handlers

void CDlgVcaLaneCfg::F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser)
{
    F_DrawFrame(lPlayHandle, hDc, dwUser,  RGB(255, 255, 0)); 
    
}

void CDlgVcaLaneCfg::F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser,  COLORREF color)
{
    UNREFERENCED_PARAMETER(dwUser);
    UNREFERENCED_PARAMETER(lRealHandle);
    DRAW_POLYGON_PARAM struPolygonParam;
    memset(&struPolygonParam, 0, sizeof(struPolygonParam));

    DRAW_DIRECTION_PARAM struDirectionParam;
    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    
    for (int i = 0; i < MAX_LANE_NUM; i++)
    {
        if (i == m_iCurLaneID)
        {
            struPolygonParam.color = RGB(244,62,0);
            struDirectionParam.color = RGB(244,62,0);
        }
        else
        {
    struPolygonParam.color = RGB(255, 255, 0);
            struDirectionParam.color = RGB(255,255,0);
        }
        struPolygonParam.bCloseIn = m_bCloseIn[i];
        struPolygonParam.bMouseMove = m_bMouseMove[i];
    memcpy(&struPolygonParam.rcWnd, &m_rcWnd, sizeof(m_rcWnd));
        memcpy(&struPolygonParam.struVcaPolygon, &m_struVcaPolygon[i], sizeof(struPolygonParam.struVcaPolygon));
        strncpy(struPolygonParam.chName, (char*)m_struLaneCfg.struLane[i].byLaneName, sizeof(struPolygonParam.chName));
    CDrawFun::DrawVcaPolygon(hDc, &struPolygonParam);

    memcpy(&struDirectionParam.rcWnd, &m_rcWnd, sizeof(struDirectionParam.rcWnd));
        memcpy(&struDirectionParam.struDirection, &m_struLaneCfg.struLane[i].struFlowDirection, sizeof(struDirectionParam.struDirection));
    CDrawFun::DrawDirection(hDc, &struDirectionParam);
}
}

BOOL CDlgVcaLaneCfg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    g_pDlgVcaLancCfg = this;
    InitDrawParam();    
    
    InitWnd();
    
    StartPlay();
    
    if (!GetLaneCfg())
    {
        AfxMessageBox("Fail to get lane config");
    }
    for (int i = 0; i < ARRAY_SIZE(m_struVcaPolygon); i++)
    {
        memcpy(&m_struVcaPolygon[i], &m_struLaneCfg.struLane[i].struPolygon, sizeof(NET_VCA_POLYGON));
        m_dwPosNum = m_struVcaPolygon[i].dwPointNum;
    }
    
    
    SetLaneWnd();
    
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVcaLaneCfg::SetLaneWnd()
{
    m_bEnbale = m_struLaneCfg.struLane[m_iCurLaneID].byEnable;
    m_csLaneName = m_struLaneCfg.struLane[m_iCurLaneID].byLaneName;

}

void CDlgVcaLaneCfg::InitDrawParam()
{
    for(int i = 0; i< MAX_LANE_NUM; i++)
    {
        m_bNeedRedraw[i] = FALSE;//Redraw polygon
        m_bCloseIn[i] = TRUE;//Polygon is closed or not
    }
}

LONG CDlgVcaLaneCfg::StartPlay()
{
    if (GetPuStreamCfg(m_struPUStream))
    {
        NET_DVR_DEVICEINFO_V30 struDeviceInfo = {0};
        
        m_lPUServerID = NET_DVR_Login_V30(m_struPUStream.struDevChanInfo.struIP.sIpV4, m_struPUStream.struDevChanInfo.wDVRPort,
            (char*)m_struPUStream.struDevChanInfo.sUserName, (char*)m_struPUStream.struDevChanInfo.sPassword, &struDeviceInfo);
        if (m_lPUServerID < 0)
        {
            AfxMessageBox("Fail to login front device");
            return m_lPUServerID;
        }
        
        NET_DVR_CLIENTINFO struPlay;
        struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
        struPlay.lChannel 	= m_struPUStream.struDevChanInfo.byChannel; 
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
            bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, g_DrawLane, 0);//DC Draw callback
        }
        return m_lPlayHandle;

    }
    else
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
        bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, g_DrawLane, 0);//DC Draw callback
    }
    return m_lPlayHandle;
}
}

BOOL CDlgVcaLaneCfg::StopPlay(LONG lPlayHandle)
{
    BOOL bRet = FALSE;
    if (!NET_DVR_StopRealPlay(lPlayHandle))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRealPlay");
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopRealPlay");
        bRet = TRUE;
    }
    if (m_lPUServerID >= 0)
    {
        NET_DVR_Logout(m_lPUServerID);
    }
    return bRet;
}

void CDlgVcaLaneCfg::InitWnd()
{
    m_comboLaneIndex.ResetContent();
    m_comboLaneIndex.AddString("Lane 1");
    m_comboLaneIndex.AddString("Lane 2");
    m_comboLaneIndex.AddString("Lane 3");
    m_comboLaneIndex.AddString("Lane 4");
    m_comboLaneIndex.AddString("Lane 5");
    m_comboLaneIndex.AddString("Lane 6");
    m_comboLaneIndex.AddString("Lane 7");
    m_comboLaneIndex.AddString("Lane 8");
    
    m_comboLaneIndex.SetCurSel(0);
    OnSelchangeComboLaneIndex();
    
    m_dwDrawType = DRAWPOLYGON;
    ((CButton*)GetDlgItem(IDC_RADIO_DRAW_POLYGON))->SetCheck(TRUE);
    
}

BOOL CDlgVcaLaneCfg::SetLaneCfg()
{
    BOOL bRet = FALSE;
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_LANECFG, m_lChannel, &m_struLaneCfg, sizeof(m_struLaneCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_LANECFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_LANECFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}


BOOL CDlgVcaLaneCfg::GetLaneCfg()
{
    DWORD dwReturn = 0;
    BOOL bRet = FALSE;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_LANECFG, m_lChannel, &m_struLaneCfg, sizeof(m_struLaneCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_LANECFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_LANECFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

void CDlgVcaLaneCfg::OnBtnSetLanecfg() 
{
    if (!SetLaneCfg())
    {
        AfxMessageBox("Fail to set lane config");
    }
    
}

BOOL CDlgVcaLaneCfg::PreTranslateMessage(MSG* pMsg) 
{
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWnd);
    
    CPoint pt(0,0);
    GetCursorPos(&pt);


    if ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && PtInRect(m_rcWnd, pt))
    {
        if (m_dwDrawType == DRAWPOLYGON)
        {
            PreDrawPolygonMsg(pMsg, pt);
        }
        else if (m_dwDrawType == DRAWDIRECTION)
        {
            PreDrawDirectionMsg(pMsg, pt);
        }
        else
        {
            AfxMessageBox("Please select draw type");
        }
    }
    else if ((GetAsyncKeyState(VK_LSHIFT) < 0 || GetAsyncKeyState(VK_RSHIFT) < 0) && PtInRect(m_rcWnd, pt) && pMsg->message == WM_LBUTTONDOWN)
    {
        memset(&m_struVcaPolygon[m_iCurLaneID], 0, sizeof(m_struVcaPolygon[m_iCurLaneID]));
        memset(&m_struLaneCfg.struLane[m_iCurLaneID].struFlowDirection, 0, sizeof(NET_DVR_DIRECTION));
    }
    return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDlgVcaLaneCfg::PreDrawDirectionMsg(MSG* pMsg, CPoint &pt)
{
    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if(PtInRect(&m_rcWnd,pt) && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {		
            if(!m_bDirectMouseMove)
            {
                m_struLaneCfg.struLane[m_iCurLaneID].struFlowDirection.struStartPoint.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struLaneCfg.struLane[m_iCurLaneID].struFlowDirection.struStartPoint.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();		
                m_struLaneCfg.struLane[m_iCurLaneID].struFlowDirection.struEndPoint.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struLaneCfg.struLane[m_iCurLaneID].struFlowDirection.struEndPoint.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();			
                m_bDirectMouseMove = TRUE;
            }
            else
            {
                if ((float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() <= m_struLaneCfg.struLane[m_iCurLaneID].struFlowDirection.struStartPoint.fX+0.01 && (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() >= m_struLaneCfg.struLane[m_iCurLaneID].struFlowDirection.struStartPoint.fX-0.01\
                    && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() <= m_struLaneCfg.struLane[m_iCurLaneID].struFlowDirection.struStartPoint.fY+0.01 && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() >= m_struLaneCfg.struLane[m_iCurLaneID].struFlowDirection.struStartPoint.fY-0.01)
                {
                    char szLan[128] = {0};
                    g_StringLanType(szLan, "不能连续在同一点上画区域", "Region can not be painted in the same point");
                    AfxMessageBox(szLan);
                    return TRUE;
                }
                m_struLaneCfg.struLane[m_iCurLaneID].struFlowDirection.struEndPoint.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struLaneCfg.struLane[m_iCurLaneID].struFlowDirection.struEndPoint.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();			
                m_bDirectMouseMove = FALSE;
            }
        }
        break;
    case WM_MOUSEMOVE:
        if(PtInRect(&m_rcWnd,pt)&& (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if(m_bDirectMouseMove)
            {
                m_struLaneCfg.struLane[m_iCurLaneID].struFlowDirection.struEndPoint.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struLaneCfg.struLane[m_iCurLaneID].struFlowDirection.struEndPoint.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();			
            }
        }
        break;
    }

    return TRUE;
}

BOOL CDlgVcaLaneCfg::PreDrawPolygonMsg(MSG* pMsg, CPoint &pt)
{
        int i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;
    
    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && 
            PtInRect(&m_rcWnd,pt))
        {

                if(m_bNeedRedraw[m_iCurLaneID])
                {			
                    if(m_bCloseIn[m_iCurLaneID])
                    {
                        m_dwPosNum = 0;
                        m_struVcaPolygon[m_iCurLaneID].dwPointNum = m_dwPosNum;		
                    }
                    if(m_dwPosNum>9)
                    {
                        char szLan[128] = {0};
                        g_StringLanType(szLan,"多边形顶点不能超过10个!","Apexes of polygon should less than 11");
                        AfxMessageBox(szLan);
                        return TRUE;
                    }
                    if((float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() <= m_struVcaPolygon[m_iCurLaneID].struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() >= m_struVcaPolygon[m_iCurLaneID].struPos[m_dwPosNum-1].fX-0.01\
                        && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() <= m_struVcaPolygon[m_iCurLaneID].struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() >= m_struVcaPolygon[m_iCurLaneID].struPos[m_dwPosNum-1].fY-0.01)
                    {
                        char szLan[128] = {0};
                        g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
                        AfxMessageBox(szLan);
                        return TRUE;
                    }
                    m_bCloseIn[m_iCurLaneID] = FALSE;
                    m_bMouseMove[m_iCurLaneID] = FALSE;
                    m_struVcaPolygon[m_iCurLaneID].struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                    m_struVcaPolygon[m_iCurLaneID].struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                    m_dwPosNum++;
                    m_struVcaPolygon[m_iCurLaneID].dwPointNum = m_dwPosNum;	
                    
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
                    if( m_bNeedRedraw[m_iCurLaneID] && !m_bCloseIn[m_iCurLaneID])
                    {
                        m_bMouseMove[m_iCurLaneID] = TRUE;
                        m_struVcaPolygon[m_iCurLaneID].struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                        m_struVcaPolygon[m_iCurLaneID].struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                        m_struVcaPolygon[m_iCurLaneID].dwPointNum = m_dwPosNum+1;				
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
                    if(m_struVcaPolygon[m_iCurLaneID].struPos[i].fX != m_struVcaPolygon[m_iCurLaneID].struPos[i+1].fX)
                    {
                        bXOneLine = FALSE;
                        break;
                    }
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struVcaPolygon[m_iCurLaneID].struPos[i].fY != m_struVcaPolygon[m_iCurLaneID].struPos[i+1].fY)
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
                if( m_bNeedRedraw[m_iCurLaneID] && !m_bCloseIn[m_iCurLaneID])
                {
                    if(m_bMouseMove[m_iCurLaneID])
                    {
                        m_bMouseMove[m_iCurLaneID] = FALSE;
                        m_struVcaPolygon[m_iCurLaneID].dwPointNum--;
                        m_struVcaPolygon[m_iCurLaneID].struPos[m_struVcaPolygon[m_iCurLaneID].dwPointNum].fX = 0;
                        m_struVcaPolygon[m_iCurLaneID].struPos[m_struVcaPolygon[m_iCurLaneID].dwPointNum].fY = 0;
                    }
                    m_bCloseIn[m_iCurLaneID] = TRUE;
                }
		}
        break;
    }
    return TRUE;
}

void CDlgVcaLaneCfg::OnSelchangeComboLaneIndex() 
{
    m_iCurLaneID = m_comboLaneIndex.GetCurSel();
    
    m_bNeedRedraw[m_iCurLaneID] = TRUE;//Draw polygon

    SetLaneWnd();
    UpdateData(FALSE);
}

void CDlgVcaLaneCfg::OnRadioDrawPolygon() 
{
    m_dwDrawType = DRAWPOLYGON;	
}

void CDlgVcaLaneCfg::OnRadioDrawDirection() 
{
	m_dwDrawType = DRAWDIRECTION;
}

void CDlgVcaLaneCfg::OnBtnConfirm() 
{
	UpdateData(TRUE);
    memcpy(&m_struLaneCfg.struLane[m_iCurLaneID].struPolygon, &m_struVcaPolygon[m_iCurLaneID], sizeof(NET_VCA_POLYGON));
    strncpy((char*)m_struLaneCfg.struLane[m_iCurLaneID].byLaneName, m_csLaneName.GetBuffer(0), NAME_LEN);
    m_struLaneCfg.struLane[m_iCurLaneID].byEnable = m_bEnbale;
}

void CDlgVcaLaneCfg::PostNcDestroy() 
{
    StopPlay(m_lPlayHandle);
    g_pDlgVcaLancCfg = NULL;

	CDialog::PostNcDestroy();
}

BOOL CDlgVcaLaneCfg::GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream)
{
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PU_STREAMCFG, m_lChannel, &struPUStream, sizeof(struPUStream), &dwReturn))
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