// DlgRegionList.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRegionList.h"
#include "DrawFun.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRegionList dialog
CDlgRegionList *g_pDlgRegionList = NULL;

void CALLBACK g_DrawRegionList(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    g_pDlgRegionList->F_DrawFun(lRealHandle, hDc, dwUser);
}


CDlgRegionList::CDlgRegionList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRegionList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRegionList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_dwRegionType = 0;
    m_lServerID = -1;
    m_lChannel = -1;
    m_iDevIndex = -1;
    memset(&m_struRegionList, 0, sizeof(m_struRegionList));
    memset(&m_struPUStream, 0, sizeof(m_struPUStream));
    m_lPUServerID = -1;
    m_lPlayHandle = -1;
    memset(&m_rcWnd, 0, sizeof(m_rcWnd));
    m_iCurRegion = -1;
    memset(m_bCloseIn, 0, sizeof(m_bCloseIn));
    memset(m_bNeedRedraw, 0, sizeof(m_bNeedRedraw));
    memset(m_bMouseMove, 0, sizeof(m_bMouseMove));
    m_dwPosNum = 0;
}


void CDlgRegionList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRegionList)
	DDX_Control(pDX, IDC_COMBO_REGION_INDEX, m_comboRegionIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRegionList, CDialog)
	//{{AFX_MSG_MAP(CDlgRegionList)
	ON_BN_CLICKED(IDC_BTN_SETUP, OnBtnSetup)
	ON_CBN_SELCHANGE(IDC_COMBO_REGION_INDEX, OnSelchangeComboRegionIndex)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRegionList message handlers

BOOL CDlgRegionList::OnInitDialog() 
{
    CDialog::OnInitDialog();
    g_pDlgRegionList = this;

    InitDrawParam();
    if (MASK_REGION == m_dwRegionType)
    {
        if (!GetMaskRegion())
        {
            AfxMessageBox("Fail to get mask region");
            return FALSE;
        }
    }
    else if (REFERENCE_REGION == m_dwRegionType)
    {
        if (!GetReferenceRegion())
        {
            AfxMessageBox("Fail to get reference region");
            return FALSE;
        }
    }
    
    m_comboRegionIndex.SetCurSel(0);
    OnSelchangeComboRegionIndex();
    StartPlay();
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRegionList::OnBtnSetup() 
{
    
    m_struRegionList.byNum = 0;
    for (int i = 0; i < MAX_REGION_NUM; i++)
    {
        if (m_struRegionList.struPolygon[i].dwPointNum >= 3)
        {
            m_struRegionList.byNum++;
        }
    }
    if (MASK_REGION == m_dwRegionType)
    {
        if (!SetMaskRegion())
        {
            AfxMessageBox("Fail to set mask region");
        }
    }
    else if (REFERENCE_REGION == m_dwRegionType)
    {
        if (!SetReferenceRegion())
        {
            AfxMessageBox("Fail to set reference region");
        }
    }
}

BOOL CDlgRegionList::SetMaskRegion()
{
    BOOL bRet = FALSE;
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_TRAFFIC_MASK_REGION, m_lChannel, &m_struRegionList, sizeof(m_struRegionList)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_TRAFFIC_MASK_REGION Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_TRAFFIC_MASK_REGION Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}
BOOL CDlgRegionList::GetMaskRegion()
{
    DWORD dwReturn = 0;
    BOOL bRet = FALSE;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_TRAFFIC_MASK_REGION, m_lChannel, &m_struRegionList, sizeof(m_struRegionList), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRAFFIC_MASK_REGION Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRAFFIC_MASK_REGION Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgRegionList::SetReferenceRegion()
{
    BOOL bRet = FALSE;
    
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_REFERENCE_REGION, m_lChannel, &m_struRegionList, sizeof(m_struRegionList)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_REFERENCE_REGION Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_REFERENCE_REGION Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgRegionList::GetReferenceRegion()
{
    DWORD dwReturn = 0;
    BOOL bRet = FALSE;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_REFERENCE_REGION, m_lChannel, &m_struRegionList, sizeof(m_struRegionList), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_REFERENCE_REGION Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_REFERENCE_REGION Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

LONG CDlgRegionList::StartPlay()
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
            bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, g_DrawRegionList, 0);//DC Draw callback
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
        g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
        bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, g_DrawRegionList, 0);//DC Draw callback
    }
    return m_lPlayHandle;
    }
   
}

BOOL CDlgRegionList::StopPlay(LONG lPlayHandle)
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


void CDlgRegionList::PostNcDestroy() 
{

    StopPlay(m_lPlayHandle);

    g_pDlgRegionList = NULL;
	CDialog::PostNcDestroy();
}

BOOL CDlgRegionList::PreTranslateMessage(MSG* pMsg) 
{

    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWnd);
    
    CPoint pt(0,0);
    GetCursorPos(&pt);
    
    
    if ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && PtInRect(m_rcWnd, pt))
    {
            PreDrawPolygonMsg(pMsg, pt);
    }
	
	return CDialog::PreTranslateMessage(pMsg);
}


void CDlgRegionList::F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser)
{
    DRAW_POLYGON_PARAM struPolygonParam;
    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    char szLan[32];
    for (int i = 0; i < MAX_REGION_NUM; i++)
    {
        sprintf(szLan, "%d", i + 1);
        memcpy(&struPolygonParam.rcWnd, &m_rcWnd, sizeof(m_rcWnd));
        memcpy(&struPolygonParam.struVcaPolygon, &m_struRegionList.struPolygon[i], sizeof(struPolygonParam.struVcaPolygon));
        struPolygonParam.bCloseIn = m_bCloseIn[i];
        struPolygonParam.bMouseMove = m_bMouseMove[i];
        memcpy(struPolygonParam.chName, szLan, sizeof(struPolygonParam.chName));
        if (i == m_iCurRegion)
        {
            struPolygonParam.color = RGB(255, 0, 0);
        }
        else
        {
             struPolygonParam.color = RGB(255, 255, 0);
        }
        CDrawFun::DrawVcaPolygon(hDc, &struPolygonParam);
    }
}

// g_pDlgRegionList->F_DrawFun(lRealHandle, hDc, dwUser);

BOOL CDlgRegionList::PreDrawPolygonMsg(MSG* pMsg, CPoint &pt)
{
    int i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;

    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && 
            PtInRect(&m_rcWnd,pt))
        {
                if(m_bNeedRedraw[m_iCurRegion])
                {			
                    if(m_bCloseIn[m_iCurRegion])
                    {
                        m_dwPosNum = 0;
                        m_struRegionList.struPolygon[m_iCurRegion].dwPointNum = m_dwPosNum;		
                    }
                    if(m_dwPosNum>9)
                    {
                        char szLan[128] = {0};
                        g_StringLanType(szLan,"多边形顶点不能超过10个!","Apexes of polygon should less than 11");
                        AfxMessageBox(szLan);
                        return TRUE;
                    }
                    if((float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() <= m_struRegionList.struPolygon[m_iCurRegion].struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() >= m_struRegionList.struPolygon[m_iCurRegion].struPos[m_dwPosNum-1].fX-0.01\
                        && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() <= m_struRegionList.struPolygon[m_iCurRegion].struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() >= m_struRegionList.struPolygon[m_iCurRegion].struPos[m_dwPosNum-1].fY-0.01)
                    {
                        char szLan[128] = {0};
                        g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
                        AfxMessageBox(szLan);
                        return TRUE;
                    }
                    m_bCloseIn[m_iCurRegion] = FALSE;
                    m_bMouseMove[m_iCurRegion] = FALSE;
                    m_struRegionList.struPolygon[m_iCurRegion].struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                    m_struRegionList.struPolygon[m_iCurRegion].struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                    m_dwPosNum++;
                    m_struRegionList.struPolygon[m_iCurRegion].dwPointNum = m_dwPosNum;	
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
                    if( m_bNeedRedraw[m_iCurRegion] && !m_bCloseIn[m_iCurRegion])
                    {
                        m_bMouseMove[m_iCurRegion] = TRUE;
                        m_struRegionList.struPolygon[m_iCurRegion].struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                        m_struRegionList.struPolygon[m_iCurRegion].struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                        m_struRegionList.struPolygon[m_iCurRegion].dwPointNum = m_dwPosNum+1;				
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
                    if(m_struRegionList.struPolygon[m_iCurRegion].struPos[i].fX != m_struRegionList.struPolygon[m_iCurRegion].struPos[i+1].fX)
                    {
                        bXOneLine = FALSE;
                        break;
                    }
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struRegionList.struPolygon[m_iCurRegion].struPos[i].fY != m_struRegionList.struPolygon[m_iCurRegion].struPos[i+1].fY)
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
                if( m_bNeedRedraw[m_iCurRegion] && !m_bCloseIn[m_iCurRegion])
                {
                    if(m_bMouseMove[m_iCurRegion])
                    {
                        m_bMouseMove[m_iCurRegion] = FALSE;
                        m_struRegionList.struPolygon[m_iCurRegion].dwPointNum--;
                        m_struRegionList.struPolygon[m_iCurRegion].struPos[m_struRegionList.struPolygon[m_iCurRegion].dwPointNum].fX = 0;
                        m_struRegionList.struPolygon[m_iCurRegion].struPos[m_struRegionList.struPolygon[m_iCurRegion].dwPointNum].fY = 0;
                    }
                    m_bCloseIn[m_iCurRegion] = TRUE;
                }
		}
        break;
    }
    return TRUE;
}

void CDlgRegionList::OnSelchangeComboRegionIndex() 
{
    m_iCurRegion = m_comboRegionIndex.GetCurSel();
    m_bNeedRedraw[m_iCurRegion] = TRUE; 

}

void CDlgRegionList::InitDrawParam()
{
    for(int i = 0; i< MAX_LANE_NUM; i++)
    {
        m_bNeedRedraw[i] = FALSE;//Redraw polygon
        m_bCloseIn[i] = TRUE;//Polygon is closed or not
    }
}

void CDlgRegionList::OnBtnClear() 
{
    memset(&m_struRegionList, 0, sizeof(m_struRegionList));
}

BOOL CDlgRegionList::GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream)
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