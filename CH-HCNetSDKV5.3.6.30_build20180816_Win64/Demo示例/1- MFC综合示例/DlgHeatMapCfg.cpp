// DlgHeatMapCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgHeatMapCfg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHeatMapCfg dialog
CDlgHeatMapCfg *g_pDlgHeatMapCfg;

void CALLBACK DrawHeatMapShow(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    SetBkMode(hDc, TRANSPARENT);
    SetTextColor(hDc, RGB(255, 255, 255));
    
    if (g_pDlgHeatMapCfg != NULL)
    {
        g_pDlgHeatMapCfg->F_DrawHeatMapRegion(lRealHandle, hDc, dwUser);
    }
    
}

CDlgHeatMapCfg::CDlgHeatMapCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHeatMapCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHeatMapCfg)
	m_bySensitivity = 0;
	m_bEnable = FALSE;
	m_bUploadCenter = FALSE;
	m_byBackgroundUpdateRate = 0;
	m_byMinTargetSize = 0;
	m_bySceneChangeLevel = 0;
	m_iHour11 = 0;
	m_iHour12 = 0;
	m_iHour21 = 0;
	m_iHour22 = 0;
	m_iHour31 = 0;
	m_iHour32 = 0;
	m_iHour41 = 0;
	m_iHour42 = 0;
	m_iHour51 = 0;
	m_iHour52 = 0;
	m_iHour61 = 0;
	m_iHour62 = 0;
	m_iHour71 = 0;
	m_iHour72 = 0;
	m_iHour81 = 0;
	m_iHour82 = 0;
	m_iMin11 = 0;
	m_iMin12 = 0;
	m_iMin21 = 0;
	m_iMin22 = 0;
	m_iMin31 = 0;
	m_iMin32 = 0;
	m_iMin41 = 0;
	m_iMin42 = 0;
	m_iMin51 = 0;
	m_iMin52 = 0;
	m_iMin61 = 0;
	m_iMin62 = 0;
	m_iMin71 = 0;
	m_iMin72 = 0;
	m_iMin81 = 0;
	m_iMin82 = 0;
	m_dwTimeSlot = 0;
	m_startDate = COleDateTime::GetCurrentTime();
	m_startTime = COleDateTime::GetCurrentTime();
	m_stopDate = COleDateTime::GetCurrentTime();
	m_stopTime = COleDateTime::GetCurrentTime();
	m_dwTerminalNo = 0;
	//}}AFX_DATA_INIT
	memset(&m_struHeatMapCond, 0, sizeof(m_struHeatMapCond));
	memset(&m_struHeatMapCfg, 0, sizeof(m_struHeatMapCfg));

	m_struHeatMapCond.dwSize = sizeof(m_struHeatMapCond);
	m_struHeatMapCond.dwChannel = 1/*m_lChannel*/;
	iAreaID = 0;
	m_iDrawType = 1;
	m_lHandle = -1;
	m_bGetNext = FALSE;
	//m_pStruHeatMapInfo = NULL;
	m_hGetInfoThread = NULL;
	m_iStruCount = 0;
	m_lPlayHandle = -1;
    m_fConfidence = 0;
}

CDlgHeatMapCfg::~CDlgHeatMapCfg()
{
	char szLan[128] = {0};
	
	if (m_lHandle >= 0)
	{
		if (!NET_DVR_StopRemoteConfig(m_lHandle))
		{
			g_StringLanType(szLan, "热度图查询停止失败", "Heat Map List Stop Failed");
			AfxMessageBox(szLan);
			return;
		}
	} 

	StopRealPlay();

// 	if (m_pStruHeatMapInfo != NULL)
// 	{
// 		delete [] m_pStruHeatMapInfo;
// 		m_pStruHeatMapInfo = NULL;
// 	}
}

void CDlgHeatMapCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgHeatMapCfg)
    DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
    DDX_Control(pDX, IDC_COMBO_REPORT_TYPE, m_comReportType);
    DDX_Control(pDX, IDC_COMBO_SCENEID, m_comSceneID);
    DDX_Control(pDX, IDC_COMBO_SCENEID2, m_comSceneID2);
    DDX_Control(pDX, IDC_LIST_HEATMAP, m_lstHeatMap);
    DDX_Control(pDX, IDC_COMBOCOPYTIME, m_comboCopyTime);
    DDX_Control(pDX, IDC_COMBOWEEKDAY, m_comboWeekday);
    DDX_Control(pDX, IDC_COMBO_AREAID, m_comboAreaID);
    DDX_Control(pDX, IDC_COMBO_TARGET_TRACK, m_comboTargetTrackEnable);
    DDX_Text(pDX, IDC_EDIT_SENSITIVITY, m_bySensitivity);
    DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
    DDX_Check(pDX, IDC_CHK_UPLOAD_CENTER, m_bUploadCenter);
    DDX_Text(pDX, IDC_EDIT_BGUPDATERATE, m_byBackgroundUpdateRate);
    DDX_Text(pDX, IDC_EDIT_MIN_TARGET_SIZE, m_byMinTargetSize);
    DDX_Text(pDX, IDC_EDIT_SCENE_CHANGE_LEVEL, m_bySceneChangeLevel);
    DDX_Text(pDX, IDC_EDITHOUR11, m_iHour11);
    DDX_Text(pDX, IDC_EDITHOUR12, m_iHour12);
    DDX_Text(pDX, IDC_EDITHOUR21, m_iHour21);
    DDX_Text(pDX, IDC_EDITHOUR22, m_iHour22);
    DDX_Text(pDX, IDC_EDITHOUR31, m_iHour31);
    DDX_Text(pDX, IDC_EDITHOUR32, m_iHour32);
    DDX_Text(pDX, IDC_EDITHOUR41, m_iHour41);
    DDX_Text(pDX, IDC_EDITHOUR42, m_iHour42);
    DDX_Text(pDX, IDC_EDITHOUR51, m_iHour51);
    DDX_Text(pDX, IDC_EDITHOUR52, m_iHour52);
    DDX_Text(pDX, IDC_EDITHOUR61, m_iHour61);
    DDX_Text(pDX, IDC_EDITHOUR62, m_iHour62);
    DDX_Text(pDX, IDC_EDITHOUR71, m_iHour71);
    DDX_Text(pDX, IDC_EDITHOUR72, m_iHour72);
    DDX_Text(pDX, IDC_EDITHOUR81, m_iHour81);
    DDX_Text(pDX, IDC_EDITHOUR82, m_iHour82);
    DDX_Text(pDX, IDC_EDITMIN11, m_iMin11);
    DDX_Text(pDX, IDC_EDITMIN12, m_iMin12);
    DDX_Text(pDX, IDC_EDITMIN21, m_iMin21);
    DDX_Text(pDX, IDC_EDITMIN22, m_iMin22);
    DDX_Text(pDX, IDC_EDITMIN31, m_iMin31);
    DDX_Text(pDX, IDC_EDITMIN32, m_iMin32);
    DDX_Text(pDX, IDC_EDITMIN41, m_iMin41);
    DDX_Text(pDX, IDC_EDITMIN42, m_iMin42);
    DDX_Text(pDX, IDC_EDITMIN51, m_iMin51);
    DDX_Text(pDX, IDC_EDITMIN52, m_iMin52);
    DDX_Text(pDX, IDC_EDITMIN61, m_iMin61);
    DDX_Text(pDX, IDC_EDITMIN62, m_iMin62);
    DDX_Text(pDX, IDC_EDITMIN71, m_iMin71);
    DDX_Text(pDX, IDC_EDITMIN72, m_iMin72);
    DDX_Text(pDX, IDC_EDITMIN81, m_iMin81);
    DDX_Text(pDX, IDC_EDITMIN82, m_iMin82);
    DDX_Text(pDX, IDC_EDIT_TIMESLOT, m_dwTimeSlot);
    DDX_DateTimeCtrl(pDX, IDC_START_DATE, m_startDate);
    DDX_DateTimeCtrl(pDX, IDC_START_TIME, m_startTime);
    DDX_DateTimeCtrl(pDX, IDC_STOP_DATE, m_stopDate);
    DDX_DateTimeCtrl(pDX, IDC_STOP_TIME, m_stopTime);
    DDX_Text(pDX, IDC_EDIT_TERMINAL_NO, m_dwTerminalNo);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_INFO_TYPE, m_comInfoType);
    DDX_Control(pDX, IDC_COMBO_STATISTICAL_MODEL, m_comboStatisticalModel);
    DDX_Text(pDX, IDC_EDIT_CONFIDENC, m_fConfidence);
    DDX_Control(pDX, IDC_COMBO_UPLOAD_HEAT_MAP_RESULT_TYPE, m_comboUploadHeatMapResultType);
}


BEGIN_MESSAGE_MAP(CDlgHeatMapCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgHeatMapCfg)
	ON_BN_CLICKED(IDC_BTN_PDC_RULECFG, OnBtnPdcRulecfg)
	ON_BN_CLICKED(IDC_TIME_OK2, OnTimeOk2)
	ON_BN_CLICKED(IDC_TIME_COPY2, OnTimeCopy2)
	ON_CBN_SELCHANGE(IDC_COMBO_AREAID, OnSelchangeComboAreaid)
	ON_BN_CLICKED(IDC_BTN_GET_HEATMAP_INFO, OnBtnGetHeatmapInfo)
	ON_BN_CLICKED(IDC_BTN_CLEAN_HEATMAP_INFO, OnBtnCleanHeatmapInfo)
	ON_BN_CLICKED(IDC_BTN_GET_HOTMAP, OnBtnGetHeatmap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHeatMapCfg message handlers

void CDlgHeatMapCfg::OnBtnPdcRulecfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struHeatMapCond.dwSize = sizeof(m_struHeatMapCond);
	m_struHeatMapCond.dwChannel = m_dwTerminalNo<<16 | (DWORD)m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
	m_struHeatMapCond.byDetSceneID = m_comSceneID.GetCurSel();

	char szLan[128] = {0};

	if(m_bySensitivity > 100 || m_bySensitivity < 1)
	{
		g_StringLanType(szLan, "灵敏度值超出限制范围[1~100]。", "Sensitivity exceeds the limit range [1~100].");
		AfxMessageBox(szLan);
		return;
	}

	if(m_byBackgroundUpdateRate > 100 || m_byBackgroundUpdateRate < 1)
	{
		g_StringLanType(szLan, "背景更新速度超出限制范围[1~100]。", "BackgroundUpdateRate exceeds the limit range [1~100].");
		AfxMessageBox(szLan);
		return;
	}

	if(m_byMinTargetSize > 100 || m_byMinTargetSize < 1)
	{
		g_StringLanType(szLan, "最小目标尺寸超出限制范围[1~100]。", "MinTargetSize exceeds the limit range [1~100].");
		AfxMessageBox(szLan);
		return;
	}

	if(m_bySceneChangeLevel > 100 || m_bySceneChangeLevel < 1)
	{
		g_StringLanType(szLan, "场景变化等级超出限制范围[1~100]。", "SceneChangeLevel exceeds the limit range [1~100].");
		AfxMessageBox(szLan);
		return;
	}

	DWORD  dwStatus = 0;
	m_struHeatMapCfg.dwSize = sizeof(m_struHeatMapCfg);
	m_struHeatMapCfg.byEnable = m_bEnable;
	m_struHeatMapCfg.struHeatMap.bySensitivity = m_bySensitivity;
	m_struHeatMapCfg.struHeatMap.byBackgroundUpdateRate = m_byBackgroundUpdateRate;
	m_struHeatMapCfg.struHeatMap.byMinTargetSize = m_byMinTargetSize;
	m_struHeatMapCfg.struHeatMap.bySceneChangeLevel = m_bySceneChangeLevel;
	m_struHeatMapCfg.struHeatMap.byTargetTrackEnable = m_comboTargetTrackEnable.GetCurSel();
    m_struHeatMapCfg.struHeatMap.byUploadHeatMapResultType = m_comboUploadHeatMapResultType.GetCurSel();
    m_struHeatMapCfg.struHeatMap.fConfidence = m_fConfidence;
	
	if (m_bUploadCenter)
	{
		m_struHeatMapCfg.struHandleException.dwHandleType = 0x04;
	}
    else
    {
        m_struHeatMapCfg.struHandleException.dwHandleType = 0x00;
    }
	
	BOOL bRet = NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_HEATMAP_CFG, 1, &m_struHeatMapCond, sizeof(m_struHeatMapCond), \
		&dwStatus, &m_struHeatMapCfg, (sizeof(m_struHeatMapCfg)));	
	if (bRet)
	{
		if (dwStatus != 0)
		{
			sprintf(szLan,"错误状态返回值:%d",dwStatus);
			AfxMessageBox(szLan);
		}
		g_StringLanType(szLan,"设置热度图参数配置成功","Success to Set Heat Map Param Info");
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Set Heat Map Param Info Success");
		AfxMessageBox(szLan);
	}
	else
	{        
		g_StringLanType(szLan,"设置热度图参数配置失败","Fail to Set Heat Map Param Info");
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Set Heat Map Param Info Fail");
		AfxMessageBox(szLan);
	}
	
}


long CDlgHeatMapCfg::StartRealPlay()
{
    NET_DVR_CLIENTINFO struClientInfo;
    memset(&struClientInfo, 0, sizeof(NET_DVR_CLIENTINFO));
    struClientInfo.lChannel = m_dwTerminalNo<<16 | (DWORD)m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    struClientInfo.hPlayWnd = GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
    m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struClientInfo, NULL, NULL, TRUE); 
    if (m_lPlayHandle == -1) 
    {
        AfxMessageBox("Fail to Preview");
        return m_lPlayHandle;
    }
    else
    {
        if (!NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawHeatMapShow, 0)) 
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RigisterDrawFun Fail");
            AfxMessageBox("Fail to set DrawFun callback");
        }
        
    }
    return m_lPlayHandle;
}

BOOL CDlgHeatMapCfg::StopRealPlay()
{
    BOOL bRet = FALSE;
    if (m_lPlayHandle >= 0)
    {
        bRet = NET_DVR_StopRealPlay(m_lPlayHandle);
        if (!bRet)
        {
            AfxMessageBox("Fail to stop preview");
        }
    }
    return bRet;
}

void CDlgHeatMapCfg::F_DrawHeatMapRegion(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    F_DrawFrame(lRealHandle, hDc, dwUser,  RGB(255, 255, 0));
}

BOOL CDlgHeatMapCfg::IsCrossLine(NET_VCA_POLYGON *alarm_region)
{
    if(alarm_region == NULL)
    {
        return FALSE;
    }
    unsigned int i, j;
    DWORD nPointTotal = 0;
    NET_VCA_POINT *pPointArray = NULL;
    NET_VCA_POINT *pPntArr = NULL;
    BOOL    bCrossLine;
    
    pPointArray = alarm_region->struPos;
    nPointTotal = alarm_region->dwPointNum;
    bCrossLine  = FALSE;
    
    if (nPointTotal >= 3)
    {
        bCrossLine = FALSE;
    }
    else
    {
        pPntArr = new NET_VCA_POINT[nPointTotal];
        if (pPntArr == NULL)
        {
            char szLan[128] = {0};
            g_StringLanType(szLan, "内存分配失败!","Memory allocation failure!");
            AfxMessageBox(szLan);
            exit(EXIT_FAILURE);
        }
        
        for (i = 0; i < nPointTotal; i++)
        {
            pPntArr[i] = pPointArray[i];
        }
        
        for(i = 0; i < nPointTotal - 3; i++)
        {
            for (j = i + 2; j < nPointTotal-1; j++)
            {
                
                if (F_LineCrossDetect(pPntArr[i], pPntArr[i + 1], pPntArr[j], pPntArr[j + 1]))
                {
                    bCrossLine = TRUE;
                }			
            }
        }
        if (pPntArr != NULL)
        {
            delete [] pPntArr;
        }
    }
    return bCrossLine;
}

BOOL CDlgHeatMapCfg::F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2)
{
    NET_VCA_POINT p1_q1, q2_q1, p2_q1, q1_p1, p2_p1, q2_p1;    
    float z1, z2, z3, z4;
    BOOL  line_cross = FALSE;
    
    // p1 - q1;
    p1_q1.fX = p1.fX - q1.fX;
    p1_q1.fY = p1.fY - q1.fY;
    
    // q2 - q1;
    q2_q1.fX = q2.fX - q1.fX;
    q2_q1.fY = q2.fY - q1.fY;
    
    // p2 - q1;
    p2_q1.fX = p2.fX - q1.fX;
    p2_q1.fY = p2.fY - q1.fY;
    
    // 叉积1 (p1 - q1) × (q2 - q1)；
    z1 = p1_q1.fX * q2_q1.fY - q2_q1.fX * p1_q1.fY; 
    
    // 叉积2 (q2 - q1) × (p2 - q1)；
    z2 = q2_q1.fX * p2_q1.fY - p2_q1.fX * q2_q1.fY;
    
    // q1 - p1;
    q1_p1.fX = q1.fX - p1.fX;
    q1_p1.fY = q1.fY - p1.fY;
    
    // p2 - p1;
    p2_p1.fX = p2.fX - p1.fX;
    p2_p1.fY = p2.fY - p1.fY;
    
    // q2 - p1;
    q2_p1.fX = q2.fX - p1.fX;
    q2_p1.fY = q2.fY - p1.fY;
    
    // 叉积3 (q1 - p1) × (p2 - p1)；
    z3 = q1_p1.fX * p2_p1.fY - p2_p1.fX * q1_p1.fY;
    
    // 叉积4 (p2 - p1) × (q2 - p1);
    z4 = p2_p1.fX * q2_p1.fY - q2_p1.fX * p2_p1.fY;
    
    if( ((z1 >= 0.0f && z2 >= 0.0f) || (z1 < 0.0f && z2 < 0.0f)) && 
        ((z3 >= 0.0f && z4 >= 0.0f) || (z3 < 0.0f && z4 < 0.0f)))
    {
        line_cross = TRUE;	
    }else
    {
        line_cross = FALSE;
    }
    
    return line_cross;
}

BOOL CDlgHeatMapCfg::IsValidArea(NET_VCA_POLYGON *alarm_region)
{
    if(alarm_region == NULL)
    {
        return FALSE;
    }
	
    if (F_IsStraightLine(alarm_region))
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "所有点在同一直线上，不能组成多边形!",\
            "All points have been in the same line, not able to form the polygon");
        MessageBox(szLan);
        return FALSE;
    }
	
    if (F_IsACrossLine(alarm_region))
    {
        char szLan[128] = {0};
        g_StringLanType(szLan,"终点和起点的连线与已有的直线相交，不能组成有效的多边形!", \
            "There are straight-line intersection, can not be composed of an effective polygon");
        MessageBox(szLan);
        return FALSE;
    }
    return TRUE;
}

/*********************************************************
Function:	F_DrawFrame
Desc:	
Input:	lPlayHandle, 播放窗口的播放句柄
hDc : 播放窗口的设备控制器句柄
dwUser: 用户数据，用于区分多路预览时都设置该回调函数
DWORD dwRuleID 当前规则ID
COLORREF color 划线颜色
Output:	
Return:	 void
**********************************************************/
/*********************************************************
  Function:	F_DrawFrame
  Desc:		Draw frame
  Input:	lRealHandle, player port;
            hDc,handle;
			dwUser, user data;
			color
  Output:	
  Return:	
**********************************************************/
void CDlgHeatMapCfg::F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser,  COLORREF color)
{
    using namespace Gdiplus;
    Graphics graphics(hDc);
    SolidBrush  brush(Color(50, 0, 0, 0));
    brush.SetColor(Color(50, GetRValue(color), GetGValue(color), GetBValue(color)));
    
    POINT point[VCA_MAX_POLYGON_POINT_NUM] = {0};
    
    CPen DrawPen;
    unsigned int i;
    
    DrawPen.CreatePen(PS_SOLID, 1, color);
    SetTextColor(hDc,color);
    
    HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);

    MoveToEx(hDc, (int)(m_struHeatMapCfg.struRegion[iAreaID].struPos[0].fX*m_rcWndRect.Width()), \
        (int)(m_struHeatMapCfg.struRegion[iAreaID].struPos[0].fY*m_rcWndRect.Height()), NULL);
    
    for(i=1; i<m_struHeatMapCfg.struRegion[iAreaID].dwPointNum; i++)
    { 
		
        LineTo(hDc, (int)(m_struHeatMapCfg.struRegion[iAreaID].struPos[i].fX*m_rcWndRect.Width()),\
            (int)(m_struHeatMapCfg.struRegion[iAreaID].struPos[i].fY*m_rcWndRect.Height()));
        //if cross, redraw
        if(i>=MIN_PNT_NUM && !m_bMouseMove && IsCrossLine(&m_struHeatMapCfg.struRegion[iAreaID]))
        {
            char szLan[128] = {0};
            g_StringLanType(szLan,"多边形不相邻的边有相交情况存在,请重新输入!","Polygon edges are not adjacent is intersect");
            AfxMessageBox(szLan);
            m_dwPosNum--;
            m_struHeatMapCfg.struRegion[iAreaID].dwPointNum--;
            break;
        }

    }
    
    for (i=0; i<(int)m_struHeatMapCfg.struRegion[iAreaID].dwPointNum; i++)
    {
        if (i == VCA_MAX_POLYGON_POINT_NUM)
        {
            break;
        }
        
        point[i].x = (int)(m_struHeatMapCfg.struRegion[iAreaID].struPos[i].fX*m_rcWndRect.Width());
        point[i].y = (int)(m_struHeatMapCfg.struRegion[iAreaID].struPos[i].fY*m_rcWndRect.Height());
    }
    
    if(VCA_MAX_POLYGON_POINT_NUM == i && !m_bMouseMove)
    {
        if (IsValidArea(&m_struHeatMapCfg.struRegion[iAreaID]))
        {
            graphics.FillPolygon(&brush, (Point *)point, m_struHeatMapCfg.struRegion[iAreaID].dwPointNum);
            
            LineTo(hDc, (int)(m_struHeatMapCfg.struRegion[iAreaID].struPos[0].fX*m_rcWndRect.Width()), \
				(int)(m_struHeatMapCfg.struRegion[iAreaID].struPos[0].fY*m_rcWndRect.Height()));	
            m_bCloseIn = TRUE;
        }else
        {
            m_bCloseIn = FALSE;
            m_struHeatMapCfg.struRegion[iAreaID].dwPointNum--;
            m_dwPosNum--;
        }
    }
    else if(m_struHeatMapCfg.struRegion[iAreaID].dwPointNum>2 && m_bCloseIn)
    {
        if (IsValidArea(&m_struHeatMapCfg.struRegion[iAreaID]))
        {
            graphics.FillPolygon(&brush, (Point *)point, m_struHeatMapCfg.struRegion[iAreaID].dwPointNum);
            
            LineTo(hDc, (int)(m_struHeatMapCfg.struRegion[iAreaID].struPos[0].fX*m_rcWndRect.Width()),\
				(int)(m_struHeatMapCfg.struRegion[iAreaID].struPos[0].fY*m_rcWndRect.Height()));
        }else
        {
            m_bCloseIn = FALSE;
        }
    }
    
    SelectObject(hDc, pOldPen);
    DeleteObject(DrawPen);
}

BOOL CDlgHeatMapCfg::F_IsACrossLine(NET_VCA_POLYGON *alarm_region) // 
{
    if(alarm_region == NULL)
    {
        return FALSE;
    }
    unsigned int i;
    DWORD	 nPointTotal;
    NET_VCA_POINT *pPointArray;
    NET_VCA_POINT *pPntArr;
    BOOL    bCrossLine;
    
    pPointArray = alarm_region->struPos;
    nPointTotal = alarm_region->dwPointNum;
    bCrossLine  = FALSE;
    
    if (nPointTotal == VCA_MAX_POLYGON_POINT_NUM)
    {
        bCrossLine = FALSE;
    }
    else
    {
        pPntArr = new NET_VCA_POINT[nPointTotal];
        if (pPntArr == NULL)
        {
            char szLan[128] = {0};
            g_StringLanType(szLan, "内存分配失败!","Memory allocation failure!");
            AfxMessageBox(szLan);
            exit(EXIT_FAILURE);
        }
        
        for (i = 0; i < nPointTotal; i++)
        {
            pPntArr[i] = pPointArray[i];
        }
        //      pPntArr[nPointTotal] = pPointArray[0];
        
        for(i = 0; i < nPointTotal - 1; i++)
        {
            
            if (F_LineCrossDetect(pPntArr[0], pPntArr[nPointTotal - 1], pPntArr[i], pPntArr[i + 1]))
            {
                bCrossLine = TRUE;
            }			
        } 
        delete [] pPntArr;
    }
    return bCrossLine;
}


BOOL CDlgHeatMapCfg::F_IsStraightLine(NET_VCA_POLYGON *alarm_region)  
{
    if(alarm_region == NULL)
    {
        return FALSE;
    }
    unsigned int i = 0;
    BOOL         bStraightLine;
    float        fSlope;
    float        fDistance;
    float        fCoefficient;
    float        fOffset;
    DWORD		 nPointTotal;
    NET_VCA_POINT *pPointArray;
    int          nXOffset;
    int          nYOffset;
    
    pPointArray = alarm_region->struPos;
    nPointTotal = alarm_region->dwPointNum;
    
    nXOffset = (int)(pPointArray[0].fX - pPointArray[1].fX);
    nYOffset = (int)(pPointArray[0].fY - pPointArray[1].fY);
    bStraightLine = TRUE;
    
    if (0 == nXOffset)
    {
        for (i = 2; i < nPointTotal; i++)
        {
            if (pPointArray[0].fX != pPointArray[i].fX)
            {
                bStraightLine = FALSE;
                break;
            }
        }
    }
    
    if (0 == nYOffset)
    {
        for (i = 2; i < nPointTotal; i++)
        {
            if (pPointArray[0].fY != pPointArray[i].fY)
            {
                bStraightLine = FALSE;
                break;
            }                 
        }
    }
    
    if ((0 != nXOffset) && (0 != nYOffset))
    {
        fSlope  = 1.0f * nYOffset / nXOffset;
        
        fOffset = pPointArray[0].fY - fSlope * pPointArray[1].fX;
        
        fCoefficient = (float)sqrt(1.0 + fSlope * fSlope);
        
        for (i = 2; i < nPointTotal; i ++)
        {
            fDistance = (float)fabs(fSlope * pPointArray[i].fX - pPointArray[i].fY + fOffset)/fCoefficient;
            
            if ((fDistance - 0.0f) > 0.000001f)
            {
                bStraightLine = FALSE;
                break;
            }
        }		
    }
    
    return bStraightLine;	
}


BOOL CDlgHeatMapCfg::PreTranslateMessage(MSG* pMsg) 
{
    // TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);
    CPoint pt(0,0);
    CRect  rcWnd(0,0,0,0);
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&rcWnd);
    GetCursorPos(&pt);
    CString strTemp = _T("");
    DWORD i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;
    switch(pMsg->message) 
    {
    case WM_LBUTTONDOWN:
        if((m_iDrawType == 1 || m_iDrawType == 2)&& (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))//按CTRL键 画图
        {
            if (m_iDrawType == 1)// Draw repolygon
            {
                if(PtInRect(&rcWnd,pt))
                {	
                        if(m_bCloseIn)
                        {
                            m_dwPosNum = 0;
                            m_struHeatMapCfg.struRegion[iAreaID].dwPointNum = m_dwPosNum;		
                        }
                        if(m_dwPosNum>9)
                        {
                            char szLan[128] = {0};
                            g_StringLanType(szLan,"人数统计规则为4边形","Polygon vertex can not be over 4!");
                            AfxMessageBox(szLan);
                            return TRUE;
                        }
                        if((float)(pt.x-rcWnd.left)/(float)rcWnd.Width() <= m_struHeatMapCfg.struRegion[iAreaID].struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() >= m_struHeatMapCfg.struRegion[iAreaID].struPos[m_dwPosNum-1].fX-0.01\
                            && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() <= m_struHeatMapCfg.struRegion[iAreaID].struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() >= m_struHeatMapCfg.struRegion[iAreaID].struPos[m_dwPosNum-1].fY-0.01)
                        {
                            char szLan[128] = {0};
                            g_StringLanType(szLan, "不能连续在同一点上画区域", "Region can not be painted in the same point");
                            AfxMessageBox(szLan);
                            return TRUE;
                        }
                        m_bCloseIn = FALSE;
                        m_bMouseMove = FALSE;
                        m_struHeatMapCfg.struRegion[iAreaID].struPos[m_dwPosNum].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struHeatMapCfg.struRegion[iAreaID].struPos[m_dwPosNum].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
                        m_dwPosNum++;
                        m_struHeatMapCfg.struRegion[iAreaID].dwPointNum = m_dwPosNum;			
                }
                
            }
//             else if (m_iDrawType == 2)
//             {
//                 if(PtInRect(&rcWnd,pt))
//                 {		
//                     if(!m_bMouseMove)
//                     {
//                         m_struPdcRuleCfg.struEnterDirection.struStartPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
//                         m_struPdcRuleCfg.struEnterDirection.struStartPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();		
//                         m_struPdcRuleCfg.struEnterDirection.struEndPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
//                         m_struPdcRuleCfg.struEnterDirection.struEndPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
//                         m_bMouseMove = TRUE;
//                     }
//                     else
//                     {
//                         if ((float)(pt.x-rcWnd.left)/(float)rcWnd.Width() <= m_struPdcRuleCfg.struEnterDirection.struStartPoint.fX+0.01 && (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() >= m_struPdcRuleCfg.struEnterDirection.struStartPoint.fX-0.01\
//                             && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() <= m_struPdcRuleCfg.struEnterDirection.struStartPoint.fY+0.01 && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() >= m_struPdcRuleCfg.struEnterDirection.struStartPoint.fY-0.01)
//                         {
//                             char szLan[128] = {0};
//                             g_StringLanType(szLan, "不能连续在同一点上画区域", "Region can not be painted in the same point");
//                             AfxMessageBox(szLan);
//                             return TRUE;
//                         }
//                         m_struPdcRuleCfg.struEnterDirection.struEndPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
//                         m_struPdcRuleCfg.struEnterDirection.struEndPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
//                         m_bMouseMove = FALSE;
//                     }
// 				}
//             }
            break;
        }
    case WM_MOUSEMOVE:
        if((m_iDrawType == 1 || m_iDrawType == 2)&&(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if (m_iDrawType == 1)
            {
                if(PtInRect(&rcWnd,pt))
                {
                    if(m_dwPosNum > 9)
                    {
                        return TRUE;
                    }
                    if( !m_bCloseIn)
                    {
                        m_bMouseMove = TRUE;
                        m_struHeatMapCfg.struRegion[iAreaID].struPos[m_dwPosNum].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struHeatMapCfg.struRegion[iAreaID].struPos[m_dwPosNum].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
                        m_struHeatMapCfg.struRegion[iAreaID].dwPointNum = m_dwPosNum+1;				
                    }
                }
            }
//             else if (m_iDrawType == 2)
//             {
//                 if(PtInRect(&rcWnd,pt))
//                 {
//                     if(m_bMouseMove)
//                     {
//                         m_struPdcRuleCfg.struEnterDirection.struEndPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
//                         m_struPdcRuleCfg.struEnterDirection.struEndPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
//                     }
//                 }
// 
//             }
        }
        break;
    case WM_LBUTTONUP:
        if((m_iDrawType == 1)&&(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            m_bMouseMove = FALSE;
        }
        break;

    case WM_RBUTTONDOWN:
        if(m_iDrawType == 1 && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if(PtInRect(&rcWnd,pt))
            {
                if(m_dwPosNum > 9)
                {
                    return TRUE;
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struHeatMapCfg.struRegion[iAreaID].struPos[i].fX !=m_struHeatMapCfg.struRegion[iAreaID].struPos[i+1].fX)
                    {
                        bXOneLine = FALSE;
                        break;
                    }
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struHeatMapCfg.struRegion[iAreaID].struPos[i].fY != m_struHeatMapCfg.struRegion[iAreaID].struPos[i+1].fY)
                    {
                        bYOneLine = FALSE;
                        break;
                    }
                }
                bOneLine = bXOneLine||bYOneLine;
                if(bOneLine)
                {
                    char szlan[128] = {0};
                    g_StringLanType(szlan, "所画点成一线，无法构成区域!","Can not constitute a regional");
                    AfxMessageBox(szlan);
                    return TRUE;
                }
                if( !m_bCloseIn)
                {
                    if(m_bMouseMove)
                    {
                        m_bMouseMove = FALSE;
                        m_struHeatMapCfg.struRegion[iAreaID].dwPointNum--;
                        m_struHeatMapCfg.struRegion[iAreaID].struPos[m_struHeatMapCfg.struRegion[iAreaID].dwPointNum].fX = 0;
                        m_struHeatMapCfg.struRegion[iAreaID].struPos[m_struHeatMapCfg.struRegion[iAreaID].dwPointNum].fY = 0;
                    }
                    m_bCloseIn = TRUE;
                }
            }
        }
        else if(m_iDrawType == 1)
        {
            if(PtInRect(&rcWnd,pt))
            {
                if(m_dwPosNum == 0)
                {
                    return TRUE;
                }
                if( !m_bCloseIn)
                {
                    m_struHeatMapCfg.struRegion[iAreaID].dwPointNum--;
                    m_dwPosNum--;
                    m_struHeatMapCfg.struRegion[iAreaID].struPos[m_struHeatMapCfg.struRegion[iAreaID].dwPointNum].fX = 0;
                    m_struHeatMapCfg.struRegion[iAreaID].struPos[m_struHeatMapCfg.struRegion[iAreaID].dwPointNum].fY = 0;
                }
                else if( m_bCloseIn)
                {
                    m_struHeatMapCfg.struRegion[iAreaID].dwPointNum = 0;
                    m_dwPosNum = 0;
                    m_bCloseIn = FALSE;
                }
            }
        }
        break;
    default:
        break;
    }
    return CDialog::PreTranslateMessage(pMsg);
}


BOOL CDlgHeatMapCfg::OnInitDialog() 
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
	
	g_pDlgHeatMapCfg = this;
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWndRect);
    m_bCloseIn = TRUE;
	// TODO: Add extra initialization here

	g_AddChanInfoToComBox(m_cmbChannel,m_iDevIndex);

	GetHeatMapRuleWnd();
	
	char szLanTemp[128] = {0};
	m_lstHeatMap.SetExtendedStyle(m_lstHeatMap.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
	g_StringLanType(szLanTemp, "热度图类型", "Heat Map Type");
    m_lstHeatMap.InsertColumn(0, szLanTemp, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLanTemp, "开始时间", "Start Time");
    m_lstHeatMap.InsertColumn(1, szLanTemp, LVCFMT_LEFT, 100, -1);
	g_StringLanType(szLanTemp, "结束时间", "Stop Time");
	m_lstHeatMap.InsertColumn(2, szLanTemp, LVCFMT_LEFT, 100, -1);
	g_StringLanType(szLanTemp, "空间热度图片长度", "Heat Map Len");
    m_lstHeatMap.InsertColumn(3, szLanTemp, LVCFMT_LEFT, 120, -1);
	g_StringLanType(szLanTemp, "时间热度值", "Time Heat Val");
    m_lstHeatMap.InsertColumn(4, szLanTemp, LVCFMT_LEFT, 80, -1);
	g_StringLanType(szLanTemp, "空间热度图片路径", "Time Heat Path");
    m_lstHeatMap.InsertColumn(5, szLanTemp, LVCFMT_LEFT, 500, -1);

    g_StringLanType(szLanTemp, "检测区域最高热度点人员活动时间(s)", "Time HeatMap Max Value");
    m_lstHeatMap.InsertColumn(6, szLanTemp, LVCFMT_LEFT, 500, -1);
    g_StringLanType(szLanTemp, "检测区域最低热度点人员活动时间(s)", "Time HeatMap Min Value");
    m_lstHeatMap.InsertColumn(7, szLanTemp, LVCFMT_LEFT, 500, -1);
	g_StringLanType(szLanTemp, "空间热度矩阵路径", "Array Path");
	m_lstHeatMap.InsertColumn(8, szLanTemp, LVCFMT_LEFT, 500, -1);
    g_StringLanType(szLanTemp, "矩阵信息长度", "Time Heat Path");
    m_lstHeatMap.InsertColumn(9, szLanTemp, LVCFMT_LEFT, 120, -1);
// 	if (m_pStruHeatMapInfo != NULL)
// 	{
// 		delete [] m_pStruHeatMapInfo;
// 		m_pStruHeatMapInfo = NULL;
// 	}
// 
// 	m_pStruHeatMapInfo = new NET_DVR_HEATMAP_INFO[MAX_ALARMHOST_ALARMOUT_NUM];
// 	memset(m_pStruHeatMapInfo, 0, MAX_ALARMHOST_ALARMOUT_NUM * sizeof(NET_DVR_HEATMAP_INFO));
	memset(&m_struHeatMapInfo, 0, sizeof(NET_DVR_HEATMAP_INFO));
	memset(&m_struHeatMapQueryCond, 0, sizeof(NET_DVR_HEATMAP_QUERY_COND));

	m_comReportType.SetCurSel(0);
	m_comboAreaID.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgHeatMapCfg::GetHeatMapRuleWnd()
{
    char szLan[128] = {0};
	DWORD dwStatus = 0;

    if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_HEATMAP_CFG, 1, &m_struHeatMapCond, sizeof(m_struHeatMapCond),\
		&dwStatus, &m_struHeatMapCfg, sizeof(m_struHeatMapCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_HEATMAP_CFG Fail");
        g_StringLanType(szLan, "获取热度图配置失败", "Fail to get HeatMap rule config");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_HEATMAP_CFG Success");
    }

    if (m_lPlayHandle >= 0)
    {
        StopRealPlay();
    }

    StartRealPlay();

    m_bEnable = m_struHeatMapCfg.byEnable;
	m_bySensitivity = m_struHeatMapCfg.struHeatMap.bySensitivity;
	m_byBackgroundUpdateRate = m_struHeatMapCfg.struHeatMap.byBackgroundUpdateRate;
	m_byMinTargetSize = m_struHeatMapCfg.struHeatMap.byMinTargetSize;
	m_bySceneChangeLevel = m_struHeatMapCfg.struHeatMap.bySceneChangeLevel;
	m_comboTargetTrackEnable.SetCurSel(m_struHeatMapCfg.struHeatMap.byTargetTrackEnable);
    m_comboUploadHeatMapResultType.SetCurSel(m_struHeatMapCfg.struHeatMap.byUploadHeatMapResultType);
    m_fConfidence = m_struHeatMapCfg.struHeatMap.fConfidence;

	if (m_struHeatMapCfg.struHandleException.dwHandleType == 0x04)
	{
		m_bUploadCenter = TRUE;
	}
	else
	{
		m_bUploadCenter = FALSE;
	}
	
	int nDay = 0;
	m_comboWeekday.SetCurSel(0);

	SetAlarmTimeToWnd(&m_struHeatMapCfg.struAlarmSched[0][0], nDay);

    UpdateData(FALSE);	
}

void CDlgHeatMapCfg::SetAlarmTimeToWnd(NET_DVR_SCHEDTIME const *pAlarmTime, int nDay)
{
    m_iHour11 = pAlarmTime[nDay*8+0].byStartHour;
    m_iMin11 = pAlarmTime[nDay*8+0].byStartMin;
    m_iHour12 = pAlarmTime[nDay*8+0].byStopHour;
    m_iMin12 = pAlarmTime[nDay*8+0].byStopMin;
    m_iHour21 = pAlarmTime[nDay*8+1].byStartHour;
    m_iMin21 = pAlarmTime[nDay*8+1].byStartMin;
    m_iHour22 = pAlarmTime[nDay*8+1].byStopHour;
    m_iMin22 = pAlarmTime[nDay*8+1].byStopMin;
	
	m_iHour31 = pAlarmTime[nDay*8+2].byStartHour;
	m_iMin31 = pAlarmTime[nDay*8+2].byStartMin;
	m_iHour32 = pAlarmTime[nDay*8+2].byStopHour;
	m_iMin32 = pAlarmTime[nDay*8+2].byStopMin;
	m_iHour41 = pAlarmTime[nDay*8+3].byStartHour;
	m_iMin41 = pAlarmTime[nDay*8+3].byStartMin;
	m_iHour42 = pAlarmTime[nDay*8+3].byStopHour;
	m_iMin42 = pAlarmTime[nDay*8+3].byStopMin;
	
	m_iHour51 = pAlarmTime[nDay*8+4].byStartHour;
	m_iMin51 = pAlarmTime[nDay*8+4].byStartMin;
	m_iHour52 = pAlarmTime[nDay*8+4].byStopHour;
	m_iMin52 = pAlarmTime[nDay*8+4].byStopMin;
	m_iHour61 = pAlarmTime[nDay*8+5].byStartHour;
	m_iMin61 = pAlarmTime[nDay*8+5].byStartMin;
	m_iHour62 = pAlarmTime[nDay*8+5].byStopHour;
	m_iMin62 = pAlarmTime[nDay*8+5].byStopMin;
	
	m_iHour71 = pAlarmTime[nDay*8+6].byStartHour;
	m_iMin71 = pAlarmTime[nDay*8+6].byStartMin;
	m_iHour72 = pAlarmTime[nDay*8+6].byStopHour;
	m_iMin72 = pAlarmTime[nDay*8+6].byStopMin;
	m_iHour81 = pAlarmTime[nDay*8+7].byStartHour;
	m_iMin81 = pAlarmTime[nDay*8+7].byStartMin;
	m_iHour82 = pAlarmTime[nDay*8+7].byStopHour;
	m_iMin82 = pAlarmTime[nDay*8+7].byStopMin;
}

void CDlgHeatMapCfg::GetAlarmTimeFromWnd(NET_DVR_SCHEDTIME *pAlarmTime, int nDay)
{
    pAlarmTime[nDay*8+0].byStartHour = (BYTE)m_iHour11;
    pAlarmTime[nDay*8+0].byStartMin = (BYTE)m_iMin11;
    pAlarmTime[nDay*8+0].byStopHour = (BYTE)m_iHour12;
    pAlarmTime[nDay*8+0].byStopMin = (BYTE)m_iMin12;
    pAlarmTime[nDay*8+1].byStartHour = (BYTE)m_iHour21;
    pAlarmTime[nDay*8+1].byStartMin = (BYTE)m_iMin21;
    pAlarmTime[nDay*8+1].byStopHour = (BYTE)m_iHour22;
    pAlarmTime[nDay*8+1].byStopMin = (BYTE)m_iMin22;
	
	pAlarmTime[nDay*8+2].byStartHour = (BYTE)m_iHour31;
    pAlarmTime[nDay*8+2].byStartMin = (BYTE)m_iMin31;
    pAlarmTime[nDay*8+2].byStopHour = (BYTE)m_iHour32;
    pAlarmTime[nDay*8+2].byStopMin = (BYTE)m_iMin32;
    pAlarmTime[nDay*8+3].byStartHour = (BYTE)m_iHour41;
    pAlarmTime[nDay*8+3].byStartMin = (BYTE)m_iMin41;
    pAlarmTime[nDay*8+3].byStopHour = (BYTE)m_iHour42;
    pAlarmTime[nDay*8+3].byStopMin = (BYTE)m_iMin42;
	
	pAlarmTime[nDay*8+4].byStartHour = (BYTE)m_iHour51;
    pAlarmTime[nDay*8+4].byStartMin = (BYTE)m_iMin51;
    pAlarmTime[nDay*8+4].byStopHour = (BYTE)m_iHour52;
    pAlarmTime[nDay*8+4].byStopMin = (BYTE)m_iMin52;
    pAlarmTime[nDay*8+5].byStartHour = (BYTE)m_iHour61;
    pAlarmTime[nDay*8+5].byStartMin = (BYTE)m_iMin61;
    pAlarmTime[nDay*8+5].byStopHour = (BYTE)m_iHour62;
    pAlarmTime[nDay*8+5].byStopMin = (BYTE)m_iMin62;
	
	pAlarmTime[nDay*8+6].byStartHour = (BYTE)m_iHour71;
    pAlarmTime[nDay*8+6].byStartMin = (BYTE)m_iMin71;
    pAlarmTime[nDay*8+6].byStopHour = (BYTE)m_iHour72;
    pAlarmTime[nDay*8+6].byStopMin = (BYTE)m_iMin72;
    pAlarmTime[nDay*8+7].byStartHour = (BYTE)m_iHour81;
    pAlarmTime[nDay*8+7].byStartMin = (BYTE)m_iMin81;
    pAlarmTime[nDay*8+7].byStopHour = (BYTE)m_iHour82;
    pAlarmTime[nDay*8+7].byStopMin = (BYTE)m_iMin82;
}

void CDlgHeatMapCfg::OnTimeOk2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    if (!F_TimeTest())
    {
        return;
    }
    int	i = m_comboWeekday.GetCurSel();	
    GetAlarmTimeFromWnd(&m_struHeatMapCfg.struAlarmSched[0][0], i);
}

void CDlgHeatMapCfg::OnTimeCopy2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int j,k;
    int i = m_comboWeekday.GetCurSel();
    int m_nCopyTime = m_comboCopyTime.GetCurSel() - 1;
    
    if(m_nCopyTime == -1)
    {
        for(j=0; j<MAX_DAYS; j++)
        {
            if(j == i)
                continue;
            for(k=0; k<MAX_TIMESEGMENT_V30/*MAX_TIMESEGMENT_2*/; k++)
            {
                memcpy(&(m_struHeatMapCfg.struAlarmSched[j][k]), &(m_struHeatMapCfg.struAlarmSched[i][k]), sizeof(NET_DVR_SCHEDTIME));
            }
        }
    }
    else
    {
        for(k=0; k<MAX_TIMESEGMENT_V30/*MAX_TIMESEGMENT_2*/; k++)
        {
            memcpy(&(m_struHeatMapCfg.struAlarmSched[m_nCopyTime][k]), &(m_struHeatMapCfg.struAlarmSched[i][k]), sizeof(NET_DVR_SCHEDTIME));
        }
    }
}

/*********************************************************
Function:	F_TimeTest
Desc:		Check Fortify time
Input:	
Output:	
Return:	BOOL
**********************************************************/
BOOL CDlgHeatMapCfg::F_TimeTest()
{
	int i = 0;
	int j = 0;
	WORD wStartTime[MAX_TIMESEGMENT_V30], wStopTime[MAX_TIMESEGMENT_V30];
	char szLan[128] = {0};
	UpdateData(TRUE);
	if ((m_iHour11 < 0) || (m_iHour11 > 24) || (m_iHour12 < 0) || (m_iHour12 > 24) ||	\
		(m_iHour21 < 0) || (m_iHour21 > 24) || (m_iHour22 < 0) || (m_iHour22 > 24) ||	\
		(m_iHour31 < 0) || (m_iHour31 > 24) || (m_iHour32 < 0) || (m_iHour32 > 24) ||	\
		(m_iHour41 < 0) || (m_iHour41 > 24) || (m_iHour42 < 0) || (m_iHour42 > 24) ||   \
		(m_iHour51 < 0) || (m_iHour51 > 24) || (m_iHour52 < 0) || (m_iHour52 > 24) ||	\
		(m_iHour61 < 0) || (m_iHour61 > 24) || (m_iHour62 < 0) || (m_iHour62 > 24) ||	\
		(m_iHour71 < 0) || (m_iHour71 > 24) || (m_iHour72 < 0) || (m_iHour72 > 24) ||	\
		(m_iHour81 < 0) || (m_iHour81 > 24) || (m_iHour82 < 0) || (m_iHour82 > 24))
	{
		g_StringLanType(szLan, "小时范围在0 -- 24之间", "Hour between 0 - 24 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	if ((m_iMin11 < 0) || (m_iMin11 > 60) || (m_iMin12 < 0) || (m_iMin12 > 60) ||	\
		(m_iMin21 < 0) || (m_iMin21 > 60) || (m_iMin22 < 0) || (m_iMin22 > 60) ||	\
		(m_iMin31 < 0) || (m_iMin31 > 60) || (m_iMin32 < 0) || (m_iMin32 > 60) ||	\
		(m_iMin41 < 0) || (m_iMin41 > 60) || (m_iMin42 < 0) || (m_iMin42 > 60) ||   \
		(m_iMin51 < 0) || (m_iMin51 > 60) || (m_iMin52 < 0) || (m_iMin52 > 60) ||	\
		(m_iMin61 < 0) || (m_iMin61 > 60) || (m_iMin62 < 0) || (m_iMin62 > 60) ||	\
		(m_iMin71 < 0) || (m_iMin71 > 60) || (m_iMin72 < 0) || (m_iMin72 > 60) ||	\
		(m_iMin81 < 0) || (m_iMin81 > 60) || (m_iMin82 < 0) || (m_iMin82 > 60))
	{
		g_StringLanType(szLan, "分钟范围在0 -- 60之间", "Minute between 0 - 60 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	wStartTime[0] = (WORD)(m_iHour11 * 100 + m_iMin11);
	wStartTime[1] = (WORD)(m_iHour21 * 100 + m_iMin21);
	wStartTime[2] = (WORD)(m_iHour31 * 100 + m_iMin31);
	wStartTime[3] = (WORD)(m_iHour41 * 100 + m_iMin41);
	wStopTime[0] = (WORD)(m_iHour12 * 100 + m_iMin12);
	wStopTime[1] = (WORD)(m_iHour22 * 100 + m_iMin22);
	wStopTime[2] = (WORD)(m_iHour32 * 100 + m_iMin32);
	wStopTime[3] = (WORD)(m_iHour42 * 100 + m_iMin42);
	wStartTime[4] = (WORD)(m_iHour51 * 100 + m_iMin51);
	wStartTime[5] = (WORD)(m_iHour61 * 100 + m_iMin61);
	wStartTime[6] = (WORD)(m_iHour71 * 100 + m_iMin71);
	wStartTime[7] = (WORD)(m_iHour81 * 100 + m_iMin81);
	wStopTime[4] = (WORD)(m_iHour52 * 100 + m_iMin52);
	wStopTime[5] = (WORD)(m_iHour62 * 100 + m_iMin62);
	wStopTime[6] = (WORD)(m_iHour72 * 100 + m_iMin72);
	wStopTime[7] = (WORD)(m_iHour82 * 100 + m_iMin82);
	for (i = 0; i < MAX_TIMESEGMENT_V30; i++)
	{
		if ((wStartTime[i] > 2400) || (wStopTime[i] > 2400))
		{
			g_StringLanType(szLan, "布防时间不能超过24:00", "Fortify time can not be more than 24:00");
			AfxMessageBox(szLan);
			return FALSE;
		}
		if (wStartTime[i] > wStopTime[i])
		{
			g_StringLanType(szLan, "布防起始时间不能大于停止时间", "Fortify start time can not be larger than the record to stop time");
			AfxMessageBox(szLan);
			return FALSE;
		}
		for (j = 0; j < MAX_TIMESEGMENT_V30; j++)
		{
			if (i == j)
			{
				continue;
			}
			if ((wStartTime[i] > wStartTime[j]) && (wStartTime[i] < wStopTime[j]) ||	\
				(wStopTime[i] > wStartTime[j]) && (wStopTime[i] < wStopTime[j]))
			{
				g_StringLanType(szLan, "时间段不能重复", "time can not be repeated");
				AfxMessageBox(szLan);
				return FALSE;
			}
		}
	}
	return TRUE;
}

void CDlgHeatMapCfg::OnSelchangeComboAreaid() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	iAreaID = m_comboAreaID.GetCurSel();
}

void CDlgHeatMapCfg::AddHeatMapDlg(char* lpInterBuff)
{
  
	BYTE*  sBuff = NULL;
	BYTE*  sArrayBuff = NULL;
	LPNET_DVR_HEATMAP_INFO lpInter = (LPNET_DVR_HEATMAP_INFO)lpInterBuff;

    int nArrayUnitLen = 0;
    if (1 == lpInter->byArrayUnitType)
    {
        nArrayUnitLen = sizeof(int);
    }
    else if (0 == lpInter->byArrayUnitType)
    {
        nArrayUnitLen = sizeof(BYTE);
    }

	if (lpInter->dwHeatMapPicLen > 0)
	{
	//	memcpy(lpInter->pBuffer, lpInterBuff+sizeof(NET_DVR_HEATMAP_INFO), lpInter->dwHeatMapPicLen);
		sBuff = new BYTE[lpInter->dwHeatMapPicLen];
		memset(sBuff, 0, sizeof(*sBuff));
		memcpy(sBuff, lpInterBuff + sizeof(NET_DVR_HEATMAP_INFO), lpInter->dwHeatMapPicLen);
		lpInter->pBuffer = sBuff;
	}

	if (lpInter->wArrayColumn > 0 && lpInter->wArrayLine > 0)
	{
        sArrayBuff = new BYTE[nArrayUnitLen*(lpInter->wArrayColumn*lpInter->wArrayLine)];
		memset(sArrayBuff, 0, sizeof(*sArrayBuff));
        memcpy(sArrayBuff, lpInterBuff + sizeof(NET_DVR_HEATMAP_INFO) + lpInter->dwHeatMapPicLen, nArrayUnitLen*(lpInter->wArrayColumn*lpInter->wArrayLine));
		lpInter->pArrayBuffer = sArrayBuff;
	}

	int iItemCount = m_lstHeatMap.GetItemCount();
	m_lstHeatMap.InsertItem(iItemCount, "");

	char szStr[128] = {0};
	//热度类型
    if (lpInter->dwHeatMapPicLen > 0 || (lpInter->wArrayColumn > 0 && lpInter->wArrayLine > 0))
	{
		g_StringLanType(szStr, "空间热度", "Space Heat");
	}
	else
	{
		g_StringLanType(szStr, "时间热度", "Time Heat");
	}
	m_lstHeatMap.SetItemText(iItemCount, 0, szStr);

	//开始时间
	memset(szStr, 0, sizeof(szStr));
	sprintf(szStr, "%d-%d-%d %d:%d:%d", lpInter->struStartTime.wYear, lpInter->struStartTime.byMonth, \
		lpInter->struStartTime.byDay, lpInter->struStartTime.byHour, lpInter->struStartTime.byMinute,\
		lpInter->struStartTime.bySecond);
	m_lstHeatMap.SetItemText(iItemCount, 1, szStr);

	//结束时间
	memset(szStr, 0, sizeof(szStr));
	sprintf(szStr, "%d-%d-%d %d:%d:%d", lpInter->struEndTime.wYear, lpInter->struEndTime.byMonth, \
		lpInter->struEndTime.byDay, lpInter->struEndTime.byHour, lpInter->struEndTime.byMinute,\
		lpInter->struEndTime.bySecond);
	m_lstHeatMap.SetItemText(iItemCount, 2, szStr);

	//空间热度图片长度
	memset(szStr, 0, sizeof(szStr));
	sprintf(szStr, "%u", lpInter->dwHeatMapPicLen);
	m_lstHeatMap.SetItemText(iItemCount, 3, szStr);

	//时间热度值
	memset(szStr, 0, sizeof(szStr));
	sprintf(szStr, "%d", lpInter->dwTimeHeatMapValue);
	m_lstHeatMap.SetItemText(iItemCount, 4, szStr);

    //检测区域最高热度点人员活动时间(s)(空间热度图时有效)
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", lpInter->dwHeatMapMaxValue);
	m_lstHeatMap.SetItemText(iItemCount, 6, szStr);

    //检测区域最低热度点人员活动时间(s) (空间热度图时有效)
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", lpInter->dwHeatMapMinValue);
	m_lstHeatMap.SetItemText(iItemCount, 7, szStr);

	char cFilename[256] = {0};
	sprintf(cFilename, "NULL");
	//热度图片
	if (lpInter->dwHeatMapPicLen > 0 && lpInter->pBuffer != NULL)
	{		
		HANDLE hFile;
		DWORD dwReturn;
        char chTime[128];
        sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d-%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d",lpInter->struStartTime.wYear, lpInter->struStartTime.byMonth, \
			lpInter->struStartTime.byDay, lpInter->struStartTime.byHour, lpInter->struStartTime.byMinute,lpInter->struStartTime.bySecond, \
			lpInter->struEndTime.wYear, lpInter->struEndTime.byMonth, lpInter->struEndTime.byDay, lpInter->struEndTime.byHour, lpInter->struEndTime.byMinute,\
			lpInter->struEndTime.bySecond);

		SYSTEMTIME t;
        GetLocalTime(&t);
        char chLocalTime[128];
        sprintf(chLocalTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
		
		sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIPInFileName, chTime);
		if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(cFilename, NULL);
		}
        
		sprintf(cFilename, "%s\\pic[%s].jpg",cFilename, chLocalTime);
		hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		WriteFile(hFile, lpInter->pBuffer, lpInter->dwHeatMapPicLen, &dwReturn, NULL);
		CloseHandle(hFile);
		hFile = NULL;
	}

	//空间热度图路径
	m_lstHeatMap.SetItemText(iItemCount, 5, cFilename);

	sprintf(cFilename, "NULL");
	//热度矩阵
	if (lpInter->wArrayColumn > 0 && lpInter->wArrayLine > 0 && lpInter->pArrayBuffer != NULL)
	{
		HANDLE hFile;
		DWORD dwReturn;
		char chTime[128];
		sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d-%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d", lpInter->struStartTime.wYear, lpInter->struStartTime.byMonth, \
			lpInter->struStartTime.byDay, lpInter->struStartTime.byHour, lpInter->struStartTime.byMinute, lpInter->struStartTime.bySecond, \
			lpInter->struEndTime.wYear, lpInter->struEndTime.byMonth, lpInter->struEndTime.byDay, lpInter->struEndTime.byHour, lpInter->struEndTime.byMinute, \
			lpInter->struEndTime.bySecond);

		SYSTEMTIME t;
		GetLocalTime(&t);
		char chLocalTime[128];
		sprintf(chLocalTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

		sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIPInFileName, chTime);
		if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(cFilename, NULL);
		}

		sprintf(cFilename, "%s\\Array[%s].txt", cFilename, chLocalTime);
		hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
        WriteFile(hFile, lpInter->pArrayBuffer, nArrayUnitLen*(lpInter->wArrayColumn*lpInter->wArrayLine), &dwReturn, NULL);
		CloseHandle(hFile);
		hFile = NULL;
	}

	//空间热度矩阵路径
	m_lstHeatMap.SetItemText(iItemCount, 8, cFilename);

    //空间热度矩阵信息长度
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%u", nArrayUnitLen*lpInter->wArrayColumn*lpInter->wArrayLine);
    m_lstHeatMap.SetItemText(iItemCount, 9, szStr);

	if (NULL != sBuff)
	{
		delete []sBuff;
		sBuff = NULL;
	}

	if (NULL != sArrayBuff)
	{
		delete[]sArrayBuff;
		sArrayBuff = NULL;
	}
}

DWORD WINAPI CDlgHeatMapCfg::GetHeatMapInfoThread(LPVOID lpVehInfo)
{
	CDlgHeatMapCfg* pThis = reinterpret_cast<CDlgHeatMapCfg*>(lpVehInfo);
	int iRet = 0;
	char szLan[128] = {0};
	char szInfoBuf[128] = {0};
	char* sBuffAll = NULL;
	char* sBuff = NULL;
	char* sArrayBuff = NULL;
	while (pThis->m_bGetNext)
	{
        iRet = NET_DVR_GetNextRemoteConfig(pThis->m_lHandle, &pThis->m_struHeatMapInfo, sizeof(NET_DVR_HEATMAP_INFO));
		if (iRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{
            int nArrayUnitLen = 0;
            if (1 == pThis->m_struHeatMapInfo.byArrayUnitType)
            {
                nArrayUnitLen = sizeof(int);
            }
            else if (0 == pThis->m_struHeatMapInfo.byArrayUnitType)
            {
                nArrayUnitLen = sizeof(BYTE);
            }
            int iBuffLen = pThis->m_struHeatMapInfo.dwHeatMapPicLen;
            int iArrayLen = nArrayUnitLen*(pThis->m_struHeatMapInfo.wArrayColumn*pThis->m_struHeatMapInfo.wArrayLine);
			sBuffAll = new char[iArrayLen + iBuffLen + sizeof(NET_DVR_HEATMAP_INFO)];
			memset(sBuffAll, 0, sizeof(*sBuffAll));	
			
            memcpy(sBuffAll, &pThis->m_struHeatMapInfo, sizeof(NET_DVR_HEATMAP_INFO));
            if (pThis->m_struHeatMapInfo.dwHeatMapPicLen > 0)
			{	
                sBuff = new char[pThis->m_struHeatMapInfo.dwHeatMapPicLen];
				memset(sBuff, 0, sizeof(*sBuff));
				iRet = NET_DVR_GetNextRemoteConfig(pThis->m_lHandle, sBuff, iBuffLen); 
				if (NULL != sBuff)
				{
			    	memcpy(sBuffAll + sizeof(NET_DVR_HEATMAP_INFO), sBuff, iBuffLen);	
				}
			}

            if (pThis->m_struHeatMapInfo.wArrayColumn>0 && pThis->m_struHeatMapInfo.wArrayLine>0)
			{
				sArrayBuff = new char[iArrayLen];
				memset(sArrayBuff, 0, sizeof(*sArrayBuff));
				iRet = NET_DVR_GetNextRemoteConfig(pThis->m_lHandle, sArrayBuff, iArrayLen);
                if (NULL != sArrayBuff)
				{
					memcpy(sBuffAll + sizeof(NET_DVR_HEATMAP_INFO) + iBuffLen, sArrayBuff, iArrayLen);
				}
			}


// 			HANDLE hFile;
// 			DWORD dwReturn;
// 
// 			hFile = CreateFile("C:\\Test.jpg", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
// 			if (hFile == INVALID_HANDLE_VALUE)
// 			{
// 				return 0;
// 			}
// 			WriteFile(hFile, sBuff, iBuffLen, &dwReturn, NULL);
// 			CloseHandle(hFile);
// 			hFile = NULL;

			pThis->AddHeatMapDlg(sBuffAll/*&pThis->m_pStruHeatMapInfo[pThis->m_iStruCount]*/);
			pThis->m_iStruCount++;

			
			if (NULL != sBuff)
			{
				delete []sBuff;
				sBuff = NULL;
			}
			
			if (NULL != sArrayBuff)
			{
				delete[]sArrayBuff;
				sArrayBuff = NULL;
			}
			
			if (NULL != sBuffAll)
			{
				delete []sBuffAll;
				sBuffAll = NULL;
			}

		}
		else
		{
			if (iRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
			{
				Sleep(5);
				continue;
			}
			if (iRet == NET_SDK_GET_NEXT_STATUS_FINISH)
			{
				g_StringLanType(szLan, "热度图查询结束!", "Get Heat Map List Finish");
				sprintf(szInfoBuf, "%s[Info Count:%d]", szLan, pThis->m_lstHeatMap.GetItemCount());
				AfxMessageBox(szInfoBuf);
				break;
			}
			else if(iRet == NET_SDK_GET_NEXT_STATUS_FAILED)
			{
				g_StringLanType(szLan, "长连接热度图查询失败", "Get Heat Map List failed");
				AfxMessageBox(szLan);
				break;
			}
			else
			{
				g_StringLanType(szLan, "未知状态", "Unknown status");
				AfxMessageBox(szLan);
				break;
			}
		}
	}

	return 0;
}

void CDlgHeatMapCfg::OnBtnGetHeatmapInfo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	m_struHeatMapQueryCond.dwSize = sizeof(m_struHeatMapQueryCond);
	m_struHeatMapQueryCond.dwChannel = m_dwTerminalNo<<16 | (DWORD)m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
	m_struHeatMapQueryCond.struStartTime.wYear = m_startDate.GetYear();
	m_struHeatMapQueryCond.struStartTime.byMonth = m_startDate.GetMonth();
	m_struHeatMapQueryCond.struStartTime.byDay = m_startDate.GetDay();
	m_struHeatMapQueryCond.struStartTime.byHour = m_startTime.GetHour();
	m_struHeatMapQueryCond.struStartTime.byMinute = m_startTime.GetMinute();
	m_struHeatMapQueryCond.struStartTime.bySecond = m_startTime.GetSecond();
	
	m_struHeatMapQueryCond.struEndTime.wYear = m_stopDate.GetYear();
	m_struHeatMapQueryCond.struEndTime.byMonth = m_stopDate.GetMonth();
	m_struHeatMapQueryCond.struEndTime.byDay = m_stopDate.GetDay();
	m_struHeatMapQueryCond.struEndTime.byHour = m_stopTime.GetHour();
	m_struHeatMapQueryCond.struEndTime.byMinute = m_stopTime.GetMinute();
	m_struHeatMapQueryCond.struEndTime.bySecond = m_stopTime.GetSecond();
	
	m_struHeatMapQueryCond.byReportType = m_comReportType.GetCurSel() + 1;
	m_struHeatMapQueryCond.byDetSceneID = m_comSceneID2.GetCurSel();

	m_struHeatMapQueryCond.byHeatMapInfoType = m_comInfoType.GetCurSel();
    m_struHeatMapQueryCond.byStatisticalModel = m_comboStatisticalModel.GetCurSel();

	if (m_lHandle >= 0)
	{
		if (!NET_DVR_StopRemoteConfig(m_lHandle))
		{
			m_bGetNext = FALSE;
			g_StringLanType(szLan, "热度图查询停止失败", "Heat Map List Stop Failed");
			AfxMessageBox(szLan);
			return;
		}
	} 

	m_lHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_HEATMAP_RESULT, &m_struHeatMapQueryCond, sizeof(m_struHeatMapQueryCond), NULL, NULL);
	if (m_lHandle >= 0)
	{
		m_bGetNext = TRUE;
		DWORD dwThreadId;
		m_lstHeatMap.DeleteAllItems();
		m_hGetInfoThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetHeatMapInfoThread), this, 0, &dwThreadId);
	}
	else
	{
		m_bGetNext = FALSE;
		g_StringLanType(szLan, "请求热度图查询失败", "Ask Get Heat Map List failed");
		AfxMessageBox(szLan);
		return;
	}


	UpdateData(FALSE);
}

void CDlgHeatMapCfg::OnBtnCleanHeatmapInfo() 
{
	// TODO: Add your control notification handler code here
	m_lstHeatMap.DeleteAllItems();
}

void CDlgHeatMapCfg::OnBtnGetHeatmap() 
{
	m_struHeatMapCond.dwSize = sizeof(m_struHeatMapCond);
	m_struHeatMapCond.dwChannel = m_dwTerminalNo<<16 | (DWORD)m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
	m_struHeatMapCond.byDetSceneID = m_comSceneID.GetCurSel();
	GetHeatMapRuleWnd();
}