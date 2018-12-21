// DlgVcaITSCalibrate.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaITSCalibrate.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaITSCalibrate dialog
CDlgVcaITSCalibrate* g_pDlgItsCalibrate = NULL;

void CALLBACK g_DrawItsCalibrate(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    if (g_pDlgItsCalibrate != NULL)
    {
        g_pDlgItsCalibrate->F_DrawFun(lRealHandle, hDc, dwUser);
    }
    
}
CDlgVcaITSCalibrate::CDlgVcaITSCalibrate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaITSCalibrate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaITSCalibrate)
	m_bEnable = FALSE;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
	m_bVerify = FALSE;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_lChannel = -1;
    memset(&m_struCalibrateCfg, 0, sizeof(m_struCalibrateCfg));
    m_lPlayHandle = -1;
    memset(&m_rcWnd, 0, sizeof(m_rcWnd));
    m_bCloseIn = FALSE;
    m_bMouseMove = FALSE;
    m_bNeedRedraw = FALSE;   
    m_dwPosNum = 0;
    memset(&m_struVcaPolygon, 0, sizeof(m_struVcaPolygon));
}


void CDlgVcaITSCalibrate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaITSCalibrate)
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_fHeight);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_fWidth);
	DDX_Check(pDX, IDC_CHECK_VERIFY, m_bVerify);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaITSCalibrate, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaITSCalibrate)
	ON_BN_CLICKED(IDC_BTN_SET_ITS_CALIBRATE, OnBtnSetItsCalibrate)
	ON_BN_CLICKED(IDC_CHK_ENABLE, OnChkEnable)
	ON_BN_CLICKED(IDC_CHECK_VERIFY, OnCheckVerify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaITSCalibrate message handlers

BOOL CDlgVcaITSCalibrate::OnInitDialog() 
{
    CDialog::OnInitDialog();
    g_pDlgItsCalibrate = this;
    m_bNeedRedraw = TRUE;
    m_bCloseIn = TRUE;

    if (!GetCalibrateCfg())
    {
        AfxMessageBox("Fail to get calibration");
        return FALSE;
    }
     
    if (-1 == RealPlay())
    {
        AfxMessageBox("Fail to Preview");
    }

    m_bEnable = m_struCalibrateCfg.byEnable;
    m_fWidth = m_struCalibrateCfg.uCalibrateParam.struITSCalibration.fWidth;
    m_fHeight = m_struCalibrateCfg.uCalibrateParam.struITSCalibration.fHeight;
    m_struVcaPolygon.dwPointNum = m_struCalibrateCfg.uCalibrateParam.struITSCalibration.dwPointNum;
    memcpy(m_struVcaPolygon.struPos, m_struCalibrateCfg.uCalibrateParam.struITSCalibration.struPoint, CALIB_PT_NUM*sizeof(NET_VCA_POINT));
    UpdateData(FALSE);
    
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgVcaITSCalibrate::OnBtnSetItsCalibrate() 
{
    UpdateData(TRUE);
    m_struCalibrateCfg.byCalibrationType = ITS_CALBIRETE;
    m_struCalibrateCfg.byEnable = m_bEnable;
    m_struCalibrateCfg.uCalibrateParam.struITSCalibration.fHeight = m_fHeight;
    m_struCalibrateCfg.uCalibrateParam.struITSCalibration.fWidth = m_fWidth;
    m_struCalibrateCfg.uCalibrateParam.struITSCalibration.dwPointNum = m_struVcaPolygon.dwPointNum;
    memcpy(m_struCalibrateCfg.uCalibrateParam.struITSCalibration.struPoint, m_struVcaPolygon.struPos, CALIB_PT_NUM*sizeof(NET_VCA_POINT));

	if (!SetCalibrateCfg())
	{
        AfxMessageBox("Fail to set calibration");
	}
}

BOOL CDlgVcaITSCalibrate::SetCalibrateCfg()
{
    BOOL bRet = FALSE;
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_CALIBRATION, m_lChannel, &m_struCalibrateCfg, sizeof(m_struCalibrateCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CALIBRATION Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CALIBRATION Chan[%d]", m_lChannel);
        bRet = FALSE;
    }   
    return bRet;
}
BOOL CDlgVcaITSCalibrate::GetCalibrateCfg()
{
    BOOL bRet = FALSE;
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_CALIBRATION, m_lChannel, &m_struCalibrateCfg, sizeof(m_struCalibrateCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CALIBRATION Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CALIBRATION Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    return bRet;
}


BOOL CDlgVcaITSCalibrate::PreTranslateMessage(MSG* pMsg) 
{
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWnd);
    
    CPoint pt(0,0);
    GetCursorPos(&pt);

    if (PtInRect(m_rcWnd, pt))
    {
        if (m_bVerify)
        {
            PreDrawVerifyLine(pMsg, pt);
        }
        else
        {
            PreDrawPolygonMsg(pMsg, pt);
        }
    }
    
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDlgVcaITSCalibrate::PreDrawVerifyLine(MSG* pMsg, CPoint& pt)
{
    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        m_struVerifyLineSeg.byLineMode = HEIGHT_LINE;
        m_struVerifyLineSeg.fValue = 0;
        m_struVerifyLineSeg.struStartPoint.fX = (float)(pt.x - m_rcWnd.left) / m_rcWnd.Width();
        m_struVerifyLineSeg.struStartPoint.fY = (float)(pt.y - m_rcWnd.top) / m_rcWnd.Height();
        memcpy(&m_struVerifyLineSeg.struEndPoint, &m_struVerifyLineSeg.struStartPoint, sizeof(m_struVerifyLineSeg.struEndPoint));
        m_bMouseMove = TRUE;
        break;
    case WM_MOUSEMOVE:
        if (m_bMouseMove)
        {
            m_struVerifyLineSeg.struEndPoint.fX = (float)(pt.x - m_rcWnd.left) / m_rcWnd.Width();
            m_struVerifyLineSeg.struEndPoint.fY = (float)(pt.y - m_rcWnd.top) / m_rcWnd.Height();
            //GetDlgItem(IDC_STATIC_PIC_SHOW)->Invalidate(TRUE);
        }
        
        break;
    case WM_LBUTTONUP:
        {
            m_bMouseMove = FALSE;
            BOOL bResult =  FALSE;
            float fHeight = 0;
            char szLan[128] ;
                m_struVerifyLineSeg.byLineMode = HEIGHT_LINE;
                bResult = NET_DVR_VerifyCalibration(m_lServerID, NET_DVR_VERIFY_ITS_CALIBRATION, m_lChannel, &m_struVerifyLineSeg, sizeof(m_struVerifyLineSeg), &fHeight, sizeof(fHeight));
                if (!bResult)
                {
                    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_VERIFY_BEHAVIOR_CALIBRATION");
                    
                    g_StringLanType(szLan, "获取校验竖直高度失败!", "Fail to get height verify calibration");
                    AfxMessageBox(szLan);
                    
                    memset(&m_struVerifyLineSeg, 0, sizeof(m_struVerifyLineSeg));
                    //					delete lpCheckLine;
                    Invalidate(TRUE);
                }
                else
                {
                    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_VERIFY_BEHAVIOR_CALIBRATION");
                    m_struVerifyLineSeg.fValue = fHeight;
                }
        }
        break;
    case WM_RBUTTONDOWN:
        memset(&m_struVerifyLineSeg, 0, sizeof(m_struVerifyLineSeg));
        break;
    default:
        break;
    }
    return TRUE;
}

LONG CDlgVcaITSCalibrate::RealPlay()
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
        bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, g_DrawItsCalibrate, 0);//DC Draw callback
    }
    return m_lPlayHandle;
}

BOOL CDlgVcaITSCalibrate::StopPlay(LONG lPlayHandle)
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
    return bRet;
}

void CDlgVcaITSCalibrate::PostNcDestroy() 
{
    if (m_lPlayHandle >= 0)
    {
        StopPlay(m_lPlayHandle);
    }
	CDialog::PostNcDestroy();
}


void CDlgVcaITSCalibrate::F_DrawFun(long lRealHandle, HDC hDc, DWORD dwUser)
{
    if (m_bVerify)
    {
        DrawVerifyLine(hDc, &m_struVerifyLineSeg);
    }
    else
    {
        if (m_bEnable)
        {
            DrawFrame(hDc);
        }
    }
}

void CDlgVcaITSCalibrate::DrawFrame( HDC hDc)
{

    DRAW_POLYGON_PARAM struPolygonParam;
    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    
    struPolygonParam.bCloseIn = m_bCloseIn;
    struPolygonParam.bMouseMove = m_bMouseMove;
    struPolygonParam.color = RGB(255, 255, 0);
    memcpy(&struPolygonParam.rcWnd, &m_rcWnd, sizeof(m_rcWnd));
    memcpy(&struPolygonParam.struVcaPolygon, &m_struVcaPolygon, sizeof(struPolygonParam.struVcaPolygon));
    CDrawFun::DrawVcaPolygon(hDc, &struPolygonParam);

}

void CDlgVcaITSCalibrate::DrawVerifyLine(HDC hDC,  NET_DVR_LINE_SEGMENT const *lpLineSegment)
{
    DRAW_VCA_POINT_PARAM struVcaPointParam;
    memset(&struVcaPointParam, 0, sizeof(struVcaPointParam));
    struVcaPointParam.color = RGB(7, 24, 237);
    memcpy(&struVcaPointParam.rcWnd, &m_rcWnd, sizeof(struVcaPointParam.rcWnd));
    memcpy(&struVcaPointParam.struVcaPoint, &lpLineSegment->struStartPoint, sizeof(struVcaPointParam.struVcaPoint));
    CDrawFun::DrawVcaPoint(hDC, &struVcaPointParam);
    
    memcpy(&struVcaPointParam.struVcaPoint, &lpLineSegment->struEndPoint, sizeof(struVcaPointParam.struVcaPoint));
    CDrawFun::DrawVcaPoint(hDC, &struVcaPointParam); 
    
    DRAW_LINE_SEGMENT_PARAM struLineSegParam;
    memset(&struLineSegParam,0, sizeof(struLineSegParam));
    struLineSegParam.color = RGB(5, 239, 17);
    memcpy(&struLineSegParam.rcWnd, &m_rcWnd, sizeof(struLineSegParam.rcWnd));
    memcpy(&struLineSegParam.struLineSegment, lpLineSegment, sizeof(struLineSegParam.struLineSegment));
    
    CDrawFun::DrawLineSegment(hDC, &struLineSegParam);
}
void CDlgVcaITSCalibrate::OnChkEnable() 
{
    UpdateData(TRUE);
}

BOOL CDlgVcaITSCalibrate::PreDrawPolygonMsg(MSG* pMsg, CPoint &pt)
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
                        m_struVcaPolygon.dwPointNum = m_dwPosNum;		
                    }
                    if(m_dwPosNum>9)
                    {
                        char szLan[128] = {0};
                        g_StringLanType(szLan,"多边形顶点不能超过10个!","Apexes of polygon should less than 11");
                        AfxMessageBox(szLan);
                        return TRUE;
                    }
                    if((float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() <= m_struVcaPolygon.struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() >= m_struVcaPolygon.struPos[m_dwPosNum-1].fX-0.01\
                        && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() <= m_struVcaPolygon.struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() >= m_struVcaPolygon.struPos[m_dwPosNum-1].fY-0.01)
                    {
                        char szLan[128] = {0};
                        g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
                        AfxMessageBox(szLan);
                        return TRUE;
                    }
                    m_bCloseIn = FALSE;
                    m_bMouseMove = FALSE;
                    m_struVcaPolygon.struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                    m_struVcaPolygon.struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                    m_dwPosNum++;
                    m_struVcaPolygon.dwPointNum = m_dwPosNum;	
                    
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
                        m_struVcaPolygon.struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                        m_struVcaPolygon.struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                        m_struVcaPolygon.dwPointNum = m_dwPosNum+1;				
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
                    if(m_struVcaPolygon.struPos[i].fX != m_struVcaPolygon.struPos[i+1].fX)
                    {
                        bXOneLine = FALSE;
                        break;
                    }
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struVcaPolygon.struPos[i].fY != m_struVcaPolygon.struPos[i+1].fY)
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
                        m_struVcaPolygon.dwPointNum--;
                        m_struVcaPolygon.struPos[m_struVcaPolygon.dwPointNum].fX = 0;
                        m_struVcaPolygon.struPos[m_struVcaPolygon.dwPointNum].fY = 0;
                    }
                    m_bCloseIn = TRUE;
                }
		}
        break;
    }
    return TRUE;
}

void CDlgVcaITSCalibrate::OnCheckVerify() 
{
    UpdateData(TRUE);
}
