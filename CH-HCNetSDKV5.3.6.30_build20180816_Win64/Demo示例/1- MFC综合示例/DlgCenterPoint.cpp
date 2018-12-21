// DlgCenterPoint.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCenterPoint.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_POLYGON_POINT_NUM ITC_MAX_POLYGON_POINT_NUM
#define MIN_POLYGON_POINT_NUM 3

/////////////////////////////////////////////////////////////////////////////
// DlgCenterPoint dialog

//DlgCenterPoint *g_pDlgVcaITCTriggerCfg = NULL;

void CALLBACK g_DrawCenterPointRgn(LONG lRealHandle, HDC hDc, DWORD dwUser)
{  
 	DlgCenterPoint* pDlg = (DlgCenterPoint*)dwUser;

 	if (pDlg != NULL)
 	{
 		pDlg->DrawRgnFun(hDc);
 	}
}

DlgCenterPoint::DlgCenterPoint(CWnd* pParent /*=NULL*/)
	: CDialog(DlgCenterPoint::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgCenterPoint)

	//}}AFX_DATA_INIT

	memset(&m_struCenterPointCfg,0,sizeof(m_struCenterPointCfg));
	memset(&m_struCalibration,0,sizeof(m_struCalibration));
	memset(&m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    m_nCurDrawType         =     DRAW_TYPE_NONE;
	m_bFirstDrawLaneBoundary = FALSE;
	m_bFirstDrawLaneLine = FALSE;
	m_nCurLaneIndex = 0;
	m_nDrawPointNum = 0;
	m_lPlayHandle = -1;
	m_iTriggerMode = 0;
}

DlgCenterPoint::~DlgCenterPoint()
{
//	StopRealPlay();
}

void DlgCenterPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgCenterPoint)
	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgCenterPoint, CDialog)
	//{{AFX_MSG_MAP(DlgCenterPoint)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_DRAW_PLATE_RECOG_RGN, OnBtnDrawPlateRecogRgn)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BTN_END_DRAW, OnBtnEndDraw)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgCenterPoint message handlers
BOOL DlgCenterPoint::OnInitDialog()
{
	CDialog::OnInitDialog();

	//g_pDlgVcaITCTriggerCfg = this;
	//g_AddChanInfoToComBox(m_comChan,m_iDevIndex);
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcPlayWnd);
	ScreenToClient(&m_rcPlayWnd);
//	m_comTriggerMode.SetCurSel(0);
//	OnSelchangeComboTriggerMode();
//	m_comSourceType.SetCurSel(0);
//	OnSelchangeComboSourceType();
//	StartRealPlay(GetDlgItem(IDC_PLAYWND)->GetSafeHwnd(),g_DrawITCTriggerRgn,this);
// 	NET_DVR_CURTRIGGERMODE struTrigCfg = {0};
// 	DWORD dwReturn = 0;
// 	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_CURTRIGGERMODE, m_lChannel, &struTrigCfg, sizeof(struTrigCfg), &dwReturn))
//     {
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_ITC_GET_TRIGGERCFG Chan[%d]", m_lChannel);
//         return FALSE;
//     }
// 
// 	if (struTrigCfg.dwTriggerType == ITC_POST_MPR_TYPE )
// 	{
// 		m_comTriggerMode.SetCurSel(1);
// 	} 
// 	else if (struTrigCfg.dwTriggerType == IPC_POST_HVT_TYPE)
// 	{
//         m_comTriggerMode.SetCurSel(2);
// 	}
//     else
// 	{
// 		m_comTriggerMode.SetCurSel(0);
// 	}

    //OnBtnGetCurtriggermode();

	//OnSelchangeComboTriggerMode();

	//StartRealPlay();
	StartRealPlay(GetDlgItem(IDC_PLAYWND)->GetSafeHwnd(),g_DrawCenterPointRgn,this);

	InitCtrlState();
	LoadWndContent();

	return TRUE;
}

void DlgCenterPoint::OnDestroy()
{   
	//StopRealPlay();
	CDialog::OnDestroy();
}

// long DlgCenterPoint::StartRealPlay()
// {
// 	NET_DVR_CLIENTINFO struPlay;
// 	struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
// 	struPlay.lChannel 	= m_lChannel; 
// 	struPlay.lLinkMode 	= 0;
// 	struPlay.sMultiCastIP = "";	
// 	if (m_lPlayHandle >= 0)
//     {
//         NET_DVR_StopRealPlay(m_lPlayHandle);
//     }
// 	m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struPlay, NULL, NULL, TRUE); 
// 	BOOL bRet = FALSE;
// 	if (m_lPlayHandle < 0)
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
// 		AfxMessageBox("NET_DVR_RealPlay_V30 FAIL");		
// 	}
// 	else
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
// 		bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, g_DrawITCTriggerRgn, 0);//DC Draw callback
// 	}
// 
//     return m_lPlayHandle;
// }
// 
// BOOL DlgCenterPoint::StopRealPlay()
// {
//     BOOL bRet;
//     if (m_lPlayHandle >= 0)
//     {
//         bRet = NET_DVR_StopRealPlay(m_lPlayHandle);
//         if (!bRet)
//         {
//             AfxMessageBox("Fail to stop preview");
//         }
//     }
//     return bRet;
// }

void DlgCenterPoint::OnBtnDrawPlateRecogRgn() 
{   
	if (0 == m_iTriggerMode)
	{
		NET_VCA_POLYGON&  struPlateRecog = m_struCenterPointCfg.struRegion;
		memset(&struPlateRecog,0,sizeof(struPlateRecog));
		m_nCurDrawType = DRAW_TYPE_PLATE_RECOG_RGN;
		m_nDrawPointNum = 0;
	}
	else if (1 == m_iTriggerMode)
	{
		NET_VCA_POLYGON&  struPlateRecog = m_struCenterPointCfg.struRegion;
		memset(&struPlateRecog,0,sizeof(struPlateRecog));
		m_nCurDrawType = DRAW_TYPE_PLATE_RECOG_RGN;
		m_nDrawPointNum = 0;
	}
    else if (2 == m_iTriggerMode)
    {
        NET_VCA_POLYGON&  struPlateRecog = m_struCenterPointCfg.struRegion;
        memset(&struPlateRecog,0,sizeof(struPlateRecog));
        m_nCurDrawType = DRAW_TYPE_PLATE_RECOG_RGN;
		m_nDrawPointNum = 0;
    }
}

void DlgCenterPoint::OnBtnEndDraw() 
{   
	if (m_nCurDrawType == DRAW_TYPE_PLATE_RECOG_RGN)
	{
		
		if (0 == m_iTriggerMode)
		{
			NET_VCA_POLYGON&  struPlateRecog = m_struCenterPointCfg.struRegion;
			if (m_nDrawPointNum >= MIN_POLYGON_POINT_NUM)
			{
				struPlateRecog.dwPointNum = m_nDrawPointNum;
			}
			else
			{
				
				memset(&struPlateRecog,0,sizeof(struPlateRecog));
			}
			m_nCurDrawType = DRAW_TYPE_NONE;
		}
		else if (1 == m_iTriggerMode)
		{
			NET_VCA_POLYGON&  struPlateRecog = m_struCenterPointCfg.struRegion;
			if (m_nDrawPointNum >= MIN_POLYGON_POINT_NUM)
			{
				struPlateRecog.dwPointNum = m_nDrawPointNum;
			}
			else
			{
				
				memset(&struPlateRecog,0,sizeof(struPlateRecog));
			}
			m_nCurDrawType = DRAW_TYPE_NONE;
		}
        else if (2 == m_iTriggerMode)
		{
            NET_VCA_POLYGON&  struPlateRecog = m_struCenterPointCfg.struRegion;
            if (m_nDrawPointNum >= MIN_POLYGON_POINT_NUM)
            {
                struPlateRecog.dwPointNum = m_nDrawPointNum;
            }
            else
            {
                
                memset(&struPlateRecog,0,sizeof(struPlateRecog));
            }
			m_nCurDrawType = DRAW_TYPE_NONE;
        }
	}
}

void DlgCenterPoint::OnBtnSave() 
{
	SaveWndContent();
    
	char szError[32] = "\0";
	if (SetITCTriggerCfg())
	{
		g_StringLanType(szError, "±£´æ³É¹¦","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "±£´æÊ§°Ü","Save failed");
	}
	AfxMessageBox(szError);
}


void DlgCenterPoint::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags,point);

	if (!m_rcPlayWnd.PtInRect(point))
	{
		return;
	}
	if (m_nCurDrawType == DRAW_TYPE_NONE)
	{
		return;
	}
	
	if (m_nCurDrawType == DRAW_TYPE_LANE_LINE)
	{
// 		if (0 == m_iTriggerMode)
// 		{
// 			NET_VCA_POLYGON& struLaneLine = m_struCenterPointCfg.struRegion.struPos[m_nCurLaneIndex].struLaneLine;
// 			if (m_bFirstDrawLaneLine)
// 			{
// 				struLaneLine.struLine.struStart.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
// 				struLaneLine.struLine.struStart.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
// 				struLaneLine.struLine.struEnd.fX   = struLaneLine.struLine.struStart.fX;
// 				struLaneLine.struLine.struEnd.fY   = struLaneLine.struLine.struStart.fY;
// 				m_bFirstDrawLaneLine= FALSE;
// 			}
// 			else
// 			{   
// 				struLaneLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
// 				struLaneLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
// 				m_nCurDrawType = DRAW_TYPE_NONE;
// 			}
// 		}
// 		else if (1 == m_iTriggerMode)
// 		{
// 			NET_VCA_POLYGON& struLaneLine = m_struCenterPointCfg.struRegion.struPos[m_nCurLaneIndex].struLaneLine;
// 			if (m_bFirstDrawLaneLine)
// 			{
// 				struLaneLine.struLine.struStart.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
// 				struLaneLine.struLine.struStart.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
// 				struLaneLine.struLine.struEnd.fX   = struLaneLine.struLine.struStart.fX;
// 				struLaneLine.struLine.struEnd.fY   = struLaneLine.struLine.struStart.fY;
// 				m_bFirstDrawLaneLine= FALSE;
// 			}
// 			else
// 			{   
// 				struLaneLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
// 				struLaneLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
// 				m_nCurDrawType = DRAW_TYPE_NONE;
// 			}
// 		}
// 		else if (2 == m_iTriggerMode)
//         {
//             NET_VCA_POLYGON& struLaneLine = m_struCenterPointCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneParam[m_nCurLaneIndex].struLaneLine;
//             if (m_bFirstDrawLaneLine)
//             {
//                 struLaneLine.struLine.struStart.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
//                 struLaneLine.struLine.struStart.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
//                 struLaneLine.struLine.struEnd.fX   = struLaneLine.struLine.struStart.fX;
//                 struLaneLine.struLine.struEnd.fY   = struLaneLine.struLine.struStart.fY;
//                 m_bFirstDrawLaneLine= FALSE;
//             }
//             else
//             {   
//                 struLaneLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
//                 struLaneLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
//                 m_nCurDrawType = DRAW_TYPE_NONE;
// 			}
//         }
	
	}
	else if (m_nCurDrawType == DRAW_TYPE_LANE_BOUNDARY_LINE)
	{   
// 		if (0 == m_iTriggerMode)
// 		{
// 			NET_VCA_POLYGON& struLaneBoundaryLine = m_struCenterPointCfg.struRegion;
// 			if (m_bFirstDrawLaneBoundary)
// 			{
// 				struLaneBoundaryLine.struLine.struStart.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
// 				struLaneBoundaryLine.struLine.struStart.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
// 				struLaneBoundaryLine.struLine.struEnd.fX   = struLaneBoundaryLine.struLine.struStart.fX;
// 				struLaneBoundaryLine.struLine.struEnd.fY   = struLaneBoundaryLine.struLine.struStart.fY;
// 				m_bFirstDrawLaneBoundary = FALSE;
// 			}
// 			else
// 			{   
// 				struLaneBoundaryLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
// 				struLaneBoundaryLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
// 				m_nCurDrawType = DRAW_TYPE_NONE;
// 			}
// 		}
// 		else if (1 == m_iTriggerMode)
// 		{
// 			NET_VCA_POLYGON& struLaneBoundaryLine = m_struCenterPointCfg.struRegion;
// 			if (m_bFirstDrawLaneBoundary)
// 			{
// 				struLaneBoundaryLine.struLine.struStart.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
// 				struLaneBoundaryLine.struLine.struStart.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
// 				struLaneBoundaryLine.struLine.struEnd.fX   = struLaneBoundaryLine.struLine.struStart.fX;
// 				struLaneBoundaryLine.struLine.struEnd.fY   = struLaneBoundaryLine.struLine.struStart.fY;
// 				m_bFirstDrawLaneBoundary = FALSE;
// 			}
// 			else
// 			{   
// 				struLaneBoundaryLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
// 				struLaneBoundaryLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
// 				m_nCurDrawType = DRAW_TYPE_NONE;
// 			}
// 		}
//         else if (2 == m_iTriggerMode)
//         {
//             NET_VCA_POLYGON& struLaneBoundaryLine = m_struCenterPointCfg.struRegion;
//             if (m_bFirstDrawLaneBoundary)
//             {
//                 struLaneBoundaryLine.struLine.struStart.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
//                 struLaneBoundaryLine.struLine.struStart.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
//                 struLaneBoundaryLine.struLine.struEnd.fX   = struLaneBoundaryLine.struLine.struStart.fX;
//                 struLaneBoundaryLine.struLine.struEnd.fY   = struLaneBoundaryLine.struLine.struStart.fY;
//                 m_bFirstDrawLaneBoundary = FALSE;
//             }
//             else
//             {   
//                 struLaneBoundaryLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
//                 struLaneBoundaryLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
//                 m_nCurDrawType = DRAW_TYPE_NONE;
// 			}
//         }
	}
	else if (m_nCurDrawType == DRAW_TYPE_PLATE_RECOG_RGN)
	{
		if (m_nDrawPointNum >= MAX_POLYGON_POINT_NUM)
		{
			m_nCurDrawType = DRAW_TYPE_NONE;
		}
		else
		{   
			if (0 == m_iTriggerMode)
			{
				NET_VCA_POLYGON&  struPlateRecog = m_struCenterPointCfg.struRegion;
				if(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)//°´CTRL¼ü »­¾ØÐÎÍ¼
				{
					if (m_nDrawPointNum == 1)
					{
						struPlateRecog.struPos[m_nDrawPointNum].fX = struPlateRecog.struPos[m_nDrawPointNum-1].fX;
						struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
						
						struPlateRecog.struPos[m_nDrawPointNum+1].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
						struPlateRecog.struPos[m_nDrawPointNum+1].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
						
						struPlateRecog.struPos[m_nDrawPointNum+2].fX = struPlateRecog.struPos[m_nDrawPointNum+1].fX;
						struPlateRecog.struPos[m_nDrawPointNum+2].fY = struPlateRecog.struPos[0].fY;
						
						m_nDrawPointNum = 4;
					}
					else if (m_nDrawPointNum == 0)
					{
						struPlateRecog.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
						struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
						m_nDrawPointNum = 1;
					}
				}
				else
				{
					struPlateRecog.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
					struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
					m_nDrawPointNum++;
				}
			}
			else if (1 == m_iTriggerMode)
			{
				NET_VCA_POLYGON&  struPlateRecog = m_struCenterPointCfg.struRegion;
				if(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)//°´CTRL¼ü »­¾ØÐÎÍ¼
				{
					if (m_nDrawPointNum == 1)
					{
						struPlateRecog.struPos[m_nDrawPointNum].fX = struPlateRecog.struPos[m_nDrawPointNum-1].fX;
						struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
						
						struPlateRecog.struPos[m_nDrawPointNum+1].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
						struPlateRecog.struPos[m_nDrawPointNum+1].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
						
						struPlateRecog.struPos[m_nDrawPointNum+2].fX = struPlateRecog.struPos[m_nDrawPointNum+1].fX;
						struPlateRecog.struPos[m_nDrawPointNum+2].fY = struPlateRecog.struPos[0].fY;
						
						m_nDrawPointNum = 4;
					}
					else if (m_nDrawPointNum == 0)
					{
						struPlateRecog.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
						struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
						m_nDrawPointNum = 1;
					}
				}
				else
				{
					struPlateRecog.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
					struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
					m_nDrawPointNum++;
				}
			}
            else if (2 == m_iTriggerMode)
            {
                NET_VCA_POLYGON&  struPlateRecog = m_struCenterPointCfg.struRegion;
                if(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)//°´CTRL¼ü »­¾ØÐÎÍ¼
                {
                    if (m_nDrawPointNum == 1)
                    {
                        struPlateRecog.struPos[m_nDrawPointNum].fX = struPlateRecog.struPos[m_nDrawPointNum-1].fX;
                        struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
                        
                        struPlateRecog.struPos[m_nDrawPointNum+1].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                        struPlateRecog.struPos[m_nDrawPointNum+1].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
                        
                        struPlateRecog.struPos[m_nDrawPointNum+2].fX = struPlateRecog.struPos[m_nDrawPointNum+1].fX;
                        struPlateRecog.struPos[m_nDrawPointNum+2].fY = struPlateRecog.struPos[0].fY;
                        
                        m_nDrawPointNum = 4;
                    }
                    else if (m_nDrawPointNum == 0)
                    {
                        struPlateRecog.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                        struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
                        m_nDrawPointNum = 1;
                    }
                }
                else
                {
                    struPlateRecog.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                    struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
                    m_nDrawPointNum++;
				}
            }
		}
	}
}

void DlgCenterPoint::OnRButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnRButtonDown(nFlags,point);
	
	if (!m_rcPlayWnd.PtInRect(point))
	{
		return;
	}
	if (m_nCurDrawType == DRAW_TYPE_NONE)
	{
		return;
	}
	
	if (m_nCurDrawType == DRAW_TYPE_LANE_BOUNDARY_LINE)
	{   
		m_bFirstDrawLaneBoundary = FALSE;
	}
	else if (m_nCurDrawType == DRAW_TYPE_LANE_LINE)
	{
		m_bFirstDrawLaneLine = FALSE;
	}
	else if (m_nCurDrawType == DRAW_TYPE_PLATE_RECOG_RGN)
	{  
		if (0 == m_iTriggerMode)
		{
			NET_VCA_POLYGON& struPlateRecog = m_struCenterPointCfg.struRegion;
			if (m_nDrawPointNum < MIN_POLYGON_POINT_NUM)
			{
				memset(&struPlateRecog,0,sizeof(struPlateRecog));
			}
			else
			{   
				struPlateRecog.dwPointNum = m_nDrawPointNum;
			}
		}
		else if (1 == m_iTriggerMode)
		{
			NET_VCA_POLYGON& struPlateRecog = m_struCenterPointCfg.struRegion;
			if (m_nDrawPointNum < MIN_POLYGON_POINT_NUM)
			{
				memset(&struPlateRecog,0,sizeof(struPlateRecog));
			}
			else
			{   
				struPlateRecog.dwPointNum = m_nDrawPointNum;
			}
		}
        else if (2 == m_iTriggerMode)
        {
            NET_VCA_POLYGON& struPlateRecog = m_struCenterPointCfg.struRegion;
            if (m_nDrawPointNum < MIN_POLYGON_POINT_NUM)
            {
                memset(&struPlateRecog,0,sizeof(struPlateRecog));
            }
            else
            {   
                struPlateRecog.dwPointNum = m_nDrawPointNum;
			}
        }
	}
	m_nCurDrawType = DRAW_TYPE_NONE;	
}

void DlgCenterPoint::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialog::OnMouseMove(nFlags,point);
	
	if (!m_rcPlayWnd.PtInRect(point))
	{
		return;
	}
	if (m_nCurDrawType == DRAW_TYPE_NONE)
	{
		return;
	}

	if (m_nCurDrawType == DRAW_TYPE_LANE_BOUNDARY_LINE)
	{   
// 		if (0 == m_iTriggerMode)
// 		{
// 			NET_VCA_POLYGON& struLaneBoundaryLine = m_struCenterPointCfg.struRegion;
// 			if (!m_bFirstDrawLaneBoundary)
// 			{
// 				struLaneBoundaryLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
// 				struLaneBoundaryLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
// 			}
// 		}
// 		else if (1 == m_iTriggerMode)
// 		{
// 			NET_VCA_POLYGON& struLaneBoundaryLine = m_struCenterPointCfg.struRegion;
// 			if (!m_bFirstDrawLaneBoundary)
// 			{
// 				struLaneBoundaryLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
// 				struLaneBoundaryLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
// 			}
// 		}
//         else if (2 == m_iTriggerMode)
//         {
//             NET_VCA_POLYGON& struLaneBoundaryLine = m_struCenterPointCfg.struRegion;
//             if (!m_bFirstDrawLaneBoundary)
//             {
//                 struLaneBoundaryLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
//                 struLaneBoundaryLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
//             }
// 		}
	}
	else if (m_nCurDrawType == DRAW_TYPE_LANE_LINE)
	{
// 		if (0 == m_iTriggerMode)
// 		{
// 			NET_VCA_POLYGON& struLaneLine = m_struCenterPointCfg.struRegion.struPos[m_nCurLaneIndex].struLaneLine;
// 			if (!m_bFirstDrawLaneLine)
// 			{
// 				struLaneLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
// 				struLaneLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
// 			}
// 		}
// 		else if (1 == m_iTriggerMode)
// 		{
// 			NET_VCA_POLYGON& struLaneLine = m_struCenterPointCfg.struRegion.struPos[m_nCurLaneIndex].struLaneLine;
// 			if (!m_bFirstDrawLaneLine)
// 			{
// 				struLaneLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
// 				struLaneLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
// 			}
// 		}
//         else if (2 == m_iTriggerMode)
//         {
//             NET_VCA_POLYGON& struLaneLine = m_struCenterPointCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneParam[m_nCurLaneIndex].struLaneLine;
//             if (!m_bFirstDrawLaneLine)
//             {
//                 struLaneLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
//                 struLaneLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
//             }
// 		}
	}
	else if (m_nCurDrawType == DRAW_TYPE_PLATE_RECOG_RGN)
	{   
		if (m_nDrawPointNum >= MAX_POLYGON_POINT_NUM || m_nDrawPointNum < 1)
		{
			return;
		}

		NET_VCA_POLYGON& struPlateRecog = m_struCenterPointCfg.struRegion;
		if(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)//°´CTRL¼ü »­¾ØÐÎÍ¼
		{
			if (m_nDrawPointNum == 1)
			{
				struPlateRecog.struPos[m_nDrawPointNum].fX = struPlateRecog.struPos[m_nDrawPointNum-1].fX;
				struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
				
				struPlateRecog.struPos[m_nDrawPointNum+1].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
				struPlateRecog.struPos[m_nDrawPointNum+1].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
				
				struPlateRecog.struPos[m_nDrawPointNum+2].fX = struPlateRecog.struPos[m_nDrawPointNum+1].fX;
				struPlateRecog.struPos[m_nDrawPointNum+2].fY = struPlateRecog.struPos[0].fY;
				
				struPlateRecog.dwPointNum = 4;
			}
		}
		else
		{
			struPlateRecog.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
			struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
			struPlateRecog.dwPointNum = m_nDrawPointNum + 1;
		}
	}
}

void DlgCenterPoint::InitCtrlState()
{   
	char szText[32] = "\0";

	
}

void DlgCenterPoint::DrawRgnFun(HDC hdc)
{   
    for (int i = 0; i < MAX_ITC_LANE_NUM; i++)
    {   
		DRAW_POLYGON_PARAM_EX struPolygonParam;
		memset(&struPolygonParam,0,sizeof(struPolygonParam));
		memcpy(&struPolygonParam.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));

		DRAW_LINE_PARAM  struLaneLineParam;
        if (i == m_nCurLaneIndex) 
        {
			struLaneLineParam.color = RGB(255,0,0);
			struPolygonParam.color = RGB(255,0,0);
			
        }
        else
        {  
			struLaneLineParam.color = RGB(0,255,0);
			struPolygonParam.color = RGB(85,170,255);
        }

		NET_VCA_POLYGON& struPlateRecog = m_struCenterPointCfg.struRegion;
		struPolygonParam.pArryPt = struPlateRecog.struPos;
		struPolygonParam.dwPtNum = struPlateRecog.dwPointNum;

		CDrawFun::DrawPolygonEx(hdc,&struPolygonParam);
	}
    
	DRAW_LINE_PARAM  struLaneBoundaryParam;
	
	if (0 == m_iTriggerMode)
	{
		NET_VCA_POLYGON&  struLaneBoundaryLine = m_struCenterPointCfg.struRegion;
		struLaneBoundaryParam.color = RGB(255,255,0);
		memcpy(&struLaneBoundaryParam.rcWnd, &m_rcPlayWnd, sizeof(struLaneBoundaryParam.rcWnd));
	}

    CDrawFun::DrawLine(hdc, &struLaneBoundaryParam);
}

void DlgCenterPoint::LoadViaLaneWndContent(int nLaneIndex)
{
	if (0 == m_iTriggerMode)
	{
// 		NET_DVR_VIA_LANE_PARAM& struViaLaneParam = m_struCenterPointCfg.struRegion;
// 		
// 		const NET_ITC_LANE_LOGIC_PARAM& struLaneLogicParam = struViaLaneParam.struLogicParam;
// 		
// 		m_nAssociateLaneNO = struViaLaneParam.byLaneNO;
// 		
// 		int i = 0;
// 		for (i = 0; i < m_comboLaneNumber.GetCount(); i++)
// 		{
// 			if (m_comboLaneNumber.GetItemData(i) == nLaneIndex)
// 			{
// 				m_comboLaneNumber.SetCurSel(i);
// 				break;
// 			}
// 		}
// 		
// 		for (i = 0; i < m_comboLaneUseageType.GetCount(); i++)
// 		{
// 			if (m_comboLaneUseageType.GetItemData(i) == struLaneLogicParam.byUseageType)
// 			{
// 				m_comboLaneUseageType.SetCurSel(i);
// 				break;
// 			}
// 		}
// 		
// 		for (i = 0; i < m_comboLaneDirection.GetCount(); i++)
// 		{
// 			if (m_comboLaneDirection.GetItemData(i) == struLaneLogicParam.byDirectionType)
// 			{
// 				m_comboLaneDirection.SetCurSel(i);
// 				break;
// 			}
// 		}
// 		
// 		for (i = 0; i < m_comboDriveDirection.GetCount(); i++)
// 		{
// 			if (m_comboDriveDirection.GetItemData(i) == struLaneLogicParam.byCarDriveDirect)
// 			{
// 				m_comboDriveDirection.SetCurSel(i);
// 				break;
// 			}
// 		}
	}
	else if (1 == m_iTriggerMode)
	{
// 		NET_ITC_LANE_MPR_PARAM& struMprLaneParam = m_struCenterPointCfg.struRegion;
// 		m_nAssociateLaneNO = struMprLaneParam.byLaneNO;
// 		if (1 == m_comSourceType.GetCurSel())
// 		{
// 			m_comIONo.SetCurSel(struMprLaneParam.uTssParamInfo.struIO.byIONo - 1);
// 			m_comTriggerType.SetCurSel(struMprLaneParam.uTssParamInfo.struIO.byTriggerType);
// 		}
// 		else if (2 == m_comSourceType.GetCurSel())
// 		{
// 			m_comRelateChan.SetCurSel(struMprLaneParam.uTssParamInfo.struRS485.byRelateChan);
// 		}
// 		//m_szSceneName.Format(_T("%s"), struMprLaneParam.szSceneName);
// 		int i = 0;
// 		for (i = 0; i < m_comboDriveDirection.GetCount(); i++)
// 		{
// 			if (m_comboDriveDirection.GetItemData(i) == struMprLaneParam.byCarDriveDirect)
// 			{
// 				m_comboDriveDirection.SetCurSel(i);
// 				break;
// 			}
// 		}
	}
    else if (2 == m_iTriggerMode)
    {
//         NET_IPC_LANE_HVT_PARAM& struIpcHvtLaneParam = m_struCenterPointCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneParam[nLaneIndex];
//         m_nAssociateLaneNO = struIpcHvtLaneParam.byLaneNO;
// 		int i = 0;
// 		for (i = 0; i < m_comboDriveDirection.GetCount(); i++)
// 		{
// 			if (m_comboDriveDirection.GetItemData(i) == struIpcHvtLaneParam.byCarDriveDirect)
// 			{
// 				m_comboDriveDirection.SetCurSel(i);
// 				break;
// 			}
// 		}
    }
}

void DlgCenterPoint::SaveViaLaneWndContent(int nLaneIndex)
{
// 	if (0 == m_iTriggerMode)
// 	{
// 		NET_DVR_VIA_LANE_PARAM& struViaLaneParam = m_struCenterPointCfg.struRegion;
// 		struViaLaneParam.byLaneNO = m_nAssociateLaneNO;
// 		NET_ITC_LANE_LOGIC_PARAM& struLaneLogicParam = struViaLaneParam.struLogicParam;
// 		struLaneLogicParam.byUseageType = m_comboLaneUseageType.GetItemData(m_comboLaneUseageType.GetCurSel());
// 		struLaneLogicParam.byDirectionType = m_comboLaneDirection.GetItemData(m_comboLaneDirection.GetCurSel());
// 		struLaneLogicParam.byCarDriveDirect = m_comboDriveDirection.GetItemData(m_comboDriveDirection.GetCurSel());
// 	}
// 	else if(1 == m_iTriggerMode)
// 	{
// 		NET_ITC_LANE_MPR_PARAM& struMprLaneParam = m_struCenterPointCfg.struRegion;
// 		struMprLaneParam.byLaneNO = m_nAssociateLaneNO;
// 		if (1 == m_comSourceType.GetCurSel())
// 		{
// 			struMprLaneParam.uTssParamInfo.struIO.byIONo = m_comIONo.GetCurSel() + 1;
// 			struMprLaneParam.uTssParamInfo.struIO.byTriggerType = m_comTriggerType.GetCurSel();
// 		}
// 		else if (2 == m_comSourceType.GetCurSel())
// 		{
// 			struMprLaneParam.uTssParamInfo.struRS485.byRelateChan = m_comRelateChan.GetCurSel();
// 		}
// 		struMprLaneParam.byCarDriveDirect = m_comboDriveDirection.GetItemData(m_comboDriveDirection.GetCurSel());
// 	}
//     else if(2 == m_iTriggerMode)
//     {
//         NET_IPC_LANE_HVT_PARAM& struIpcHvtLaneParam = m_struCenterPointCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneParam[nLaneIndex];
// 		struIpcHvtLaneParam.byLaneNO = m_nAssociateLaneNO;
// 		struIpcHvtLaneParam.byCarDriveDirect = m_comboDriveDirection.GetItemData(m_comboDriveDirection.GetCurSel());
//     }
}

void DlgCenterPoint::LoadWndContent()
{
// 	const NET_ITC_SINGLE_TRIGGERCFG&  struTriggerParam = m_struCenterPointCfg.struTriggerParam;
// 	m_bTriggerCfg = struTriggerParam.byEnable;
// 	
//  	if (0 == m_iTriggerMode)
// 	{
// 		const NET_DVR_VIA_VTCOIL_PARAM& struViaVtcoiParam = struTriggerParam.uTriggerParam.struViaVtCoil;
// 		m_bViaVtcoil = struViaVtcoiParam.byEnable;
// 		m_nLaneNum = struViaVtcoiParam.byLaneNum;
// 
// 		const NET_ITC_PLATE_RECOG_PARAM& struPlateRecogParam = struViaVtcoiParam.struPlateRecog;
// 		m_strProvinceName = struPlateRecogParam.byDefaultCHN;
// 		m_bPlateRecog = struPlateRecogParam.byEnable;
// 		m_bVehicleLogoRecog = struPlateRecogParam.byVehicleLogoRecog;
// 		
// 		DWORD dwRecogMode = struPlateRecogParam.dwRecogMode;
// 		
// 		m_comboRecogPos.SetCurSel(dwRecogMode & 0x00000001 ? 1 : 0);
// 		m_comboVehicleType.SetCurSel(dwRecogMode & 0x00000002 ? 1 : 0);
// 		m_bVehicleColorRecog = (dwRecogMode & 0x00000004) ? TRUE : FALSE;
// 		m_bFarmVehicleRecog = (dwRecogMode & 0x00000008) ? TRUE : FALSE;
// 		m_bFuzzyRecog = (dwRecogMode & 0x00000010) ? TRUE : FALSE;
// 		m_comboLocateType.SetCurSel(dwRecogMode & 0x00000020 ? 1 : 0);
// 		m_comboRecogType.SetCurSel(dwRecogMode & 0x00000040 ? 1 : 0);
// 		m_comboTimeType.SetCurSel(dwRecogMode & 0x00000080 ? 1 : 0);
// 		m_bMotocarRecog = (dwRecogMode & 0x00000100) ? TRUE : FALSE;
// 		m_comboSceneType.SetCurSel(dwRecogMode & 0x00000200 ? 1 : 0);
// 		m_bMicroPlateRecog = (dwRecogMode & 0x00000400)? TRUE : FALSE;
// 		
// 		if (struPlateRecogParam.byProvince == 0xff)
// 		{
// 			m_comProvince.SetCurSel(35);
// 		} 
// 		else
// 		{
// 			m_comProvince.SetCurSel(struPlateRecogParam.byProvince);
// 		}
// 
// 	    m_comRegion.SetCurSel(struPlateRecogParam.byRegion);
// //		m_comboCarDriveDirect.SetCurSel(struPlateRecogParam.byCarDriveDirect);
// 
//         m_dwPlatePixelWidthMin = struPlateRecogParam.wPlatePixelWidthMin;
//         m_dwPlatePixelWidthMax = struPlateRecogParam.wPlatePixelWidthMax;
// 	}
// 	else if (1 == m_iTriggerMode)
// 	{
// 		const NET_ITC_POST_MPR_PARAM& struMprParam = struTriggerParam.uTriggerParam.struPostMpr;
// 		m_nLaneNum = struMprParam.byLaneNum;
// 		m_comSourceType.SetCurSel(struMprParam.bySourceType);
// 		m_szSceneName.Format(_T("%s"), struMprParam.szSceneName);
// 		OnSelchangeComboSourceType();
// 		const NET_ITC_PLATE_RECOG_PARAM& struPlateRecogParam = struMprParam.struPlateRecog;
// 		m_strProvinceName = struPlateRecogParam.byDefaultCHN;
// 		m_bPlateRecog = struPlateRecogParam.byEnable;
// 		m_bVehicleLogoRecog = struPlateRecogParam.byVehicleLogoRecog;
// 		
// 		DWORD dwRecogMode = struPlateRecogParam.dwRecogMode;
// 		
// 		m_comboRecogPos.SetCurSel(dwRecogMode & 0x00000001 ? 1 : 0);
// 		m_comboVehicleType.SetCurSel(dwRecogMode & 0x00000002 ? 1 : 0);
// 		m_bVehicleColorRecog = (dwRecogMode & 0x00000004) ? TRUE : FALSE;
// 		m_bFarmVehicleRecog = (dwRecogMode & 0x00000008) ? TRUE : FALSE;
// 		m_bFuzzyRecog = (dwRecogMode & 0x00000010) ? TRUE : FALSE;
// 		m_comboLocateType.SetCurSel(dwRecogMode & 0x00000020 ? 1 : 0);
// 		m_comboRecogType.SetCurSel(dwRecogMode & 0x00000040 ? 1 : 0);
// 		m_comboTimeType.SetCurSel(dwRecogMode & 0x00000080 ? 1 : 0);
// 		m_bMotocarRecog = (dwRecogMode & 0x00000100) ? TRUE : FALSE;
// 		m_comboSceneType.SetCurSel(dwRecogMode & 0x00000200 ? 1 : 0);
// 		m_bMicroPlateRecog = (dwRecogMode & 0x00000400)? TRUE : FALSE;
// 		
// 		if (struPlateRecogParam.byProvince == 0xff)
// 		{
// 			m_comProvince.SetCurSel(35);
// 		} 
// 		else
// 		{
// 			m_comProvince.SetCurSel(struPlateRecogParam.byProvince);
// 		}
// 
// 
// 		m_comRegion.SetCurSel(struPlateRecogParam.byRegion);
// //		m_comboCarDriveDirect.SetCurSel(struPlateRecogParam.byCarDriveDirect);
//         m_dwPlatePixelWidthMin = struPlateRecogParam.wPlatePixelWidthMin;
//         m_dwPlatePixelWidthMax = struPlateRecogParam.wPlatePixelWidthMax;
// 	}
//     else if (2 == m_iTriggerMode)
//     {
//         const NET_IPC_POST_HVT_PARAM& struIpcHvtParam = struTriggerParam.uTriggerParam.struIpcHvt;
//         m_bTriggerCfg = struIpcHvtParam.byEnable;
//         m_nLaneNum = struIpcHvtParam.byLaneNum;
//         m_szSceneName.Format(_T("%s"), struIpcHvtParam.szSceneName);
//       
//         const NET_ITC_PLATE_RECOG_PARAM& struPlateRecogParam = struIpcHvtParam.struPlateRecog;
//         m_strProvinceName = struPlateRecogParam.byDefaultCHN;
//         m_bPlateRecog = struPlateRecogParam.byEnable;
//         m_bVehicleLogoRecog = struPlateRecogParam.byVehicleLogoRecog;
//         
//         DWORD dwRecogMode = struPlateRecogParam.dwRecogMode;
//         
//         m_comboRecogPos.SetCurSel(dwRecogMode & 0x00000001 ? 1 : 0);
//         m_comboVehicleType.SetCurSel(dwRecogMode & 0x00000002 ? 1 : 0);
//         m_bVehicleColorRecog = (dwRecogMode & 0x00000004) ? TRUE : FALSE;
//         m_bFarmVehicleRecog = (dwRecogMode & 0x00000008) ? TRUE : FALSE;
//         m_bFuzzyRecog = (dwRecogMode & 0x00000010) ? TRUE : FALSE;
//         m_comboLocateType.SetCurSel(dwRecogMode & 0x00000020 ? 1 : 0);
//         m_comboRecogType.SetCurSel(dwRecogMode & 0x00000040 ? 1 : 0);
//         m_comboTimeType.SetCurSel(dwRecogMode & 0x00000080 ? 1 : 0);
//         m_bMotocarRecog = (dwRecogMode & 0x00000100) ? TRUE : FALSE;
//         m_comboSceneType.SetCurSel(dwRecogMode & 0x00000200 ? 1 : 0);
//         m_bMicroPlateRecog = (dwRecogMode & 0x00000400)? TRUE : FALSE;
//         
//         if (struPlateRecogParam.byProvince == 0xff)
//         {
//             m_comProvince.SetCurSel(35);
//         } 
//         else
//         {
//             m_comProvince.SetCurSel(struPlateRecogParam.byProvince);
//         }
// 		
// 		m_comRegion.SetCurSel(struPlateRecogParam.byRegion);
// 		
// //		m_comboCarDriveDirect.SetCurSel(struPlateRecogParam.byCarDriveDirect);
//         m_dwPlatePixelWidthMin = struPlateRecogParam.wPlatePixelWidthMin;
//         m_dwPlatePixelWidthMax = struPlateRecogParam.wPlatePixelWidthMax;
// 	}
// 	
// 
// 	LoadViaLaneWndContent(m_nCurLaneIndex);
// 
// 	UpdateData(FALSE);
}

void DlgCenterPoint::SaveWndContent()
{
// 	UpdateData(TRUE);
//     
//     m_struCenterPointCfg.dwSize = sizeof(m_struCenterPointCfg);
// 
// 	
// 	NET_ITC_SINGLE_TRIGGERCFG&  struTriggerParam = m_struCenterPointCfg.struTriggerParam;
// 	struTriggerParam.byEnable = m_bTriggerCfg;
// 
// 	if (0 == m_iTriggerMode)
// 	{
// 		struTriggerParam.dwTriggerType = ITC_VIA_VIRTUALCOIL_TYPE;
// 		NET_DVR_VIA_VTCOIL_PARAM& struViaVtcoiParam = struTriggerParam.uTriggerParam.struViaVtCoil;
// 		
// 		struViaVtcoiParam.byEnable = m_bTriggerCfg/* m_bViaVtcoil*/;
// 		struViaVtcoiParam.byLaneNum = m_nLaneNum;
// 		
// 		NET_ITC_PLATE_RECOG_PARAM& struPlateRecogParam = struViaVtcoiParam.struPlateRecog;
// 
// 		strncpy((char*)struPlateRecogParam.byDefaultCHN,m_strProvinceName,MAX_CHJC_NUM);
// 		struPlateRecogParam.byEnable = m_bTriggerCfg/*m_bPlateRecog*/;
// 		struPlateRecogParam.byVehicleLogoRecog = m_bVehicleLogoRecog;
// 		if (35 == m_comProvince.GetCurSel())
// 		{
// 			struPlateRecogParam.byProvince = 0xff;
// 		} 
// 		else
// 		{
// 			struPlateRecogParam.byProvince = m_comProvince.GetCurSel();
// 		}
// 
// 		struPlateRecogParam.byRegion = m_comRegion.GetCurSel();
// 		
//         struPlateRecogParam.wPlatePixelWidthMin = m_dwPlatePixelWidthMin;
//         struPlateRecogParam.wPlatePixelWidthMax = m_dwPlatePixelWidthMax;
// 		
// //		struPlateRecogParam.byCarDriveDirect = m_comboCarDriveDirect.GetCurSel();
// 
// 		struPlateRecogParam.dwRecogMode = 0;
// 		struPlateRecogParam.dwRecogMode |= (m_comboRecogPos.GetItemData(m_comboRecogPos.GetCurSel())       == 0 ? 0x00000000 : 0x00000001);
// 		struPlateRecogParam.dwRecogMode |= (m_comboVehicleType.GetItemData(m_comboVehicleType.GetCurSel()) == 0 ? 0x00000000 : 0x00000002);
// 		struPlateRecogParam.dwRecogMode |= m_bVehicleColorRecog ? 0x00000004 : 0x00000000;
// 		struPlateRecogParam.dwRecogMode |= m_bFarmVehicleRecog  ? 0x00000008 : 0x00000000;
// 		struPlateRecogParam.dwRecogMode |= m_bFuzzyRecog        ? 0x00000010 : 0x00000000;
// 		struPlateRecogParam.dwRecogMode |= (m_comboLocateType.GetItemData(m_comboLocateType.GetCurSel())   == 0 ? 0x00000000 : 0x00000020);
// 		struPlateRecogParam.dwRecogMode |= (m_comboRecogType.GetItemData(m_comboRecogType.GetCurSel())     == 0 ? 0x00000000 : 0x00000040);
// 		struPlateRecogParam.dwRecogMode |= (m_comboTimeType.GetItemData(m_comboTimeType.GetCurSel())       == 0 ? 0x00000000 : 0x00000080);
// 		struPlateRecogParam.dwRecogMode |= m_bMotocarRecog      ? 0x00000100 : 0x00000000;
// 		struPlateRecogParam.dwRecogMode |= (m_comboSceneType.GetItemData(m_comboSceneType.GetCurSel())     == 0 ? 0x00000000 : 0x00000200);
// 		struPlateRecogParam.dwRecogMode |= m_bMicroPlateRecog   ? 0x00000400 : 0x00000000;
// 	}
// 	else if (1 == m_iTriggerMode)
// 	{
// 		struTriggerParam.dwTriggerType = ITC_POST_MPR_TYPE;
// 		NET_ITC_POST_MPR_PARAM& struMprParam = struTriggerParam.uTriggerParam.struPostMpr;
// 		struMprParam.byEnable = m_bTriggerCfg;
// 		struMprParam.byLaneNum = m_nLaneNum;
// 		struMprParam.bySourceType = m_comSourceType.GetCurSel();
// 		memcpy(struMprParam.szSceneName, m_szSceneName, m_szSceneName.GetLength());
// 		NET_ITC_PLATE_RECOG_PARAM& struPlateRecogParam = struMprParam.struPlateRecog;
// 
// 		strncpy((char*)struPlateRecogParam.byDefaultCHN,m_strProvinceName,MAX_CHJC_NUM);
// 		struPlateRecogParam.byEnable = m_bTriggerCfg/*m_bPlateRecog*/;
// 		struPlateRecogParam.byVehicleLogoRecog = m_bVehicleLogoRecog;
// 		if (35 == m_comProvince.GetCurSel())
// 		{
// 			struPlateRecogParam.byProvince = 0xff;
// 		} 
// 		else
// 		{
// 			struPlateRecogParam.byProvince = m_comProvince.GetCurSel();
// 		}
// 
// 		struPlateRecogParam.byRegion = m_comRegion.GetCurSel();
// 		
//         struPlateRecogParam.wPlatePixelWidthMin = m_dwPlatePixelWidthMin;
//         struPlateRecogParam.wPlatePixelWidthMax = m_dwPlatePixelWidthMax;
// 		
// //		struPlateRecogParam.byCarDriveDirect = m_comboCarDriveDirect.GetCurSel();
// 
// 		struPlateRecogParam.dwRecogMode = 0;
// 		struPlateRecogParam.dwRecogMode |= (m_comboRecogPos.GetItemData(m_comboRecogPos.GetCurSel())       == 0 ? 0x00000000 : 0x00000001);
// 		struPlateRecogParam.dwRecogMode |= (m_comboVehicleType.GetItemData(m_comboVehicleType.GetCurSel()) == 0 ? 0x00000000 : 0x00000002);
// 		struPlateRecogParam.dwRecogMode |= m_bVehicleColorRecog ? 0x00000004 : 0x00000000;
// 		struPlateRecogParam.dwRecogMode |= m_bFarmVehicleRecog  ? 0x00000008 : 0x00000000;
// 		struPlateRecogParam.dwRecogMode |= m_bFuzzyRecog        ? 0x00000010 : 0x00000000;
// 		struPlateRecogParam.dwRecogMode |= (m_comboLocateType.GetItemData(m_comboLocateType.GetCurSel())   == 0 ? 0x00000000 : 0x00000020);
// 		struPlateRecogParam.dwRecogMode |= (m_comboRecogType.GetItemData(m_comboRecogType.GetCurSel())     == 0 ? 0x00000000 : 0x00000040);
// 		struPlateRecogParam.dwRecogMode |= (m_comboTimeType.GetItemData(m_comboTimeType.GetCurSel())       == 0 ? 0x00000000 : 0x00000080);
// 		struPlateRecogParam.dwRecogMode |= m_bMotocarRecog      ? 0x00000100 : 0x00000000;
// 		struPlateRecogParam.dwRecogMode |= (m_comboSceneType.GetItemData(m_comboSceneType.GetCurSel())     == 0 ? 0x00000000 : 0x00000200);
// 		struPlateRecogParam.dwRecogMode |= m_bMicroPlateRecog   ? 0x00000400 : 0x00000000;
// 	}
//     else if (2 == m_iTriggerMode)
//     {
//         struTriggerParam.dwTriggerType = IPC_POST_HVT_TYPE;
//         NET_IPC_POST_HVT_PARAM& struIpcHvtParam = struTriggerParam.uTriggerParam.struIpcHvt;
//         struIpcHvtParam.byEnable = m_bTriggerCfg;
//         struIpcHvtParam.byLaneNum = m_nLaneNum;
//         memcpy(struIpcHvtParam.szSceneName, m_szSceneName, m_szSceneName.GetLength());
//         NET_ITC_PLATE_RECOG_PARAM& struPlateRecogParam = struIpcHvtParam.struPlateRecog;
//         
//         strncpy((char*)struPlateRecogParam.byDefaultCHN,m_strProvinceName,MAX_CHJC_NUM);
//         struPlateRecogParam.byEnable = m_bTriggerCfg/*m_bPlateRecog*/;
//         struPlateRecogParam.byVehicleLogoRecog = m_bVehicleLogoRecog;
//         if (35 == m_comProvince.GetCurSel())
//         {
//             struPlateRecogParam.byProvince = 0xff;
//         } 
//         else
//         {
//             struPlateRecogParam.byProvince = m_comProvince.GetCurSel();
//         }
//  
// 
// 		struPlateRecogParam.byRegion = m_comRegion.GetCurSel();
// 		
//         struPlateRecogParam.wPlatePixelWidthMin = m_dwPlatePixelWidthMin;
//         struPlateRecogParam.wPlatePixelWidthMax = m_dwPlatePixelWidthMax;
// 		
// //		struPlateRecogParam.byCarDriveDirect = m_comboCarDriveDirect.GetCurSel();
// 		
//         struPlateRecogParam.dwRecogMode = 0;
//         struPlateRecogParam.dwRecogMode |= (m_comboRecogPos.GetItemData(m_comboRecogPos.GetCurSel())       == 0 ? 0x00000000 : 0x00000001);
//         struPlateRecogParam.dwRecogMode |= (m_comboVehicleType.GetItemData(m_comboVehicleType.GetCurSel()) == 0 ? 0x00000000 : 0x00000002);
//         struPlateRecogParam.dwRecogMode |= m_bVehicleColorRecog ? 0x00000004 : 0x00000000;
//         struPlateRecogParam.dwRecogMode |= m_bFarmVehicleRecog  ? 0x00000008 : 0x00000000;
//         struPlateRecogParam.dwRecogMode |= m_bFuzzyRecog        ? 0x00000010 : 0x00000000;
//         struPlateRecogParam.dwRecogMode |= (m_comboLocateType.GetItemData(m_comboLocateType.GetCurSel())   == 0 ? 0x00000000 : 0x00000020);
//         struPlateRecogParam.dwRecogMode |= (m_comboRecogType.GetItemData(m_comboRecogType.GetCurSel())     == 0 ? 0x00000000 : 0x00000040);
//         struPlateRecogParam.dwRecogMode |= (m_comboTimeType.GetItemData(m_comboTimeType.GetCurSel())       == 0 ? 0x00000000 : 0x00000080);
//         struPlateRecogParam.dwRecogMode |= m_bMotocarRecog      ? 0x00000100 : 0x00000000;
//         struPlateRecogParam.dwRecogMode |= (m_comboSceneType.GetItemData(m_comboSceneType.GetCurSel())     == 0 ? 0x00000000 : 0x00000200);
//         struPlateRecogParam.dwRecogMode |= m_bMicroPlateRecog   ? 0x00000400 : 0x00000000;
// 	}
// 	SaveViaLaneWndContent(m_nCurLaneIndex);
}

BOOL DlgCenterPoint::SetITCTriggerCfg()
{
    UpdateData(TRUE);
    char szLan[512] = {0};
    
    m_struCenterPointCfg.dwSize = sizeof(m_struCenterPointCfg);

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpInBuffer = &m_struCenterPointCfg;
    struCfg.dwInSize = sizeof(m_struCenterPointCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_CENTER_POINT_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CENTER_POINT_CFG");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CENTER_POINT_CFG");

    }
    return TRUE;
}


void DlgCenterPoint::OnButtonGet() 
{
	// TODO: Add your control notification handler code here

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpOutBuffer = &m_struCenterPointCfg;
    struCfg.dwOutSize = sizeof(m_struCenterPointCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_CENTER_POINT_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CENTER_POINT_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CENTER_POINT_CFG");
    }
    
    UpdateData(FALSE);
	
}
