// VcaCommonOperations.cpp: implementation of the VcaCommonOperations class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "clientdemo.h"
#include "VcaCommonOperations.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVcaCommonOperations::CVcaCommonOperations()
{
    m_lServerID        = -1;
    m_lChannel         = -1;
    m_iDevIndex        = -1;
	m_lPUServerID      = -1;
	m_lPlayHandle      = -1;
	m_lRealPlayChannel = -1;
}

CVcaCommonOperations::~CVcaCommonOperations()
{

}

BOOL CVcaCommonOperations::StartRealPlay(HWND hWndPlay,fDrawFun pfnDrawFun,void* pUserData, LONG lChannel)
{  

	NET_DVR_PU_STREAM_CFG struPUStream = {0};
	if (GetPuStreamCfg(struPUStream))
    {
        NET_DVR_DEVICEINFO_V30 struDeviceInfo = {0};
        
        m_lPUServerID = NET_DVR_Login_V30(struPUStream.struDevChanInfo.struIP.sIpV4, struPUStream.struDevChanInfo.wDVRPort,
            (char*)struPUStream.struDevChanInfo.sUserName, (char*)struPUStream.struDevChanInfo.sPassword, &struDeviceInfo);
        if (m_lPUServerID < 0)
        {
            AfxMessageBox("Fail to login front device");
            return FALSE;
        }

		m_lRealPlayChannel = struPUStream.struDevChanInfo.byChannel; 
        
		NET_DVR_CLIENTINFO struPlay = {0};
        struPlay.hPlayWnd 	= hWndPlay;
        struPlay.lChannel 	= m_lRealPlayChannel;
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
            bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, pfnDrawFun, (DWORD)pUserData);//DC Draw callback
        }
        return bRet;
    }
    else
	{
		NET_DVR_CLIENTINFO struPlay = {0};
		struPlay.hPlayWnd 	= hWndPlay;
		struPlay.lChannel 	= m_lChannel; 
		struPlay.lLinkMode 	= 0;
		struPlay.sMultiCastIP = "";	
		if (lChannel)
		{
			struPlay.lChannel 	= lChannel;
		}
		else
		{
			struPlay.lChannel 	= m_lChannel;
		}
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
			bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, pfnDrawFun, (DWORD)pUserData);//DC Draw callback
		}
		return bRet;
    }
}

BOOL CVcaCommonOperations::StopRealPlay()
{
	BOOL bRet = FALSE;
    if (!NET_DVR_StopRealPlay(m_lPlayHandle))
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

BOOL CVcaCommonOperations::GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream)
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


BOOL CVcaCommonOperations::GetSceneCfg(NET_DVR_SCENE_CFG& struSceneCfg)
{
	memset(&struSceneCfg,0,sizeof(struSceneCfg));
	struSceneCfg.dwSize = sizeof(struSceneCfg);

	DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
    if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_SCENE_CFG, 1,(LPVOID)&m_lChannel, sizeof(m_lChannel),
		&dwStatus,&struSceneCfg, sizeof(struSceneCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCENE_CFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCENE_CFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}


BOOL CVcaCommonOperations::IsLineSegmentCross(CPoint pFirst1, CPoint pFirst2, CPoint pSecond1, CPoint pSecond2)
{
	long Linep1,Linep2;
	
	Linep1 =  pFirst1.x * (pSecond1.y - pFirst2.y) +
	    	  pFirst2.x * (pFirst1.y - pSecond1.y) +
		      pSecond1.x * (pFirst2.y - pFirst1.y);
	
	Linep2 =  pFirst1.x * (pSecond2.y - pFirst2.y) + 
		      pFirst2.x * (pFirst1.y - pSecond2.y) + 
		      pSecond2.x * (pFirst2.y - pFirst1.y);
    
	if ( ((Linep1 ^ Linep2) >= 0 ) && !(Linep1 == 0 && Linep2 == 0))
	{
		return FALSE;
	}
	
	Linep1 = pSecond1.x * (pFirst1.y - pSecond2.y) +
		     pSecond2.x * (pSecond1.y - pFirst1.y) +
		     pFirst1.x * (pSecond2.y - pSecond1.y);

	Linep2 = pSecond1.x * (pFirst2.y - pSecond2.y)  +
	     	 pSecond2.x * (pSecond1.y - pFirst2.y)      +
		     pFirst2.x * (pSecond2.y - pSecond1.y);
    
	if ( ((Linep1 ^ Linep2) >= 0 ) && !(Linep1==0 && Linep2==0))
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL CVcaCommonOperations::IsPolygonPointValid(const NET_VCA_POLYGON& struPolygon,const int& nWndWidth,const int& nWndHeight,const CPoint& pt)
{   
	DWORD dwPointNum = struPolygon.dwPointNum;

	if(dwPointNum < 2)
	{
		return TRUE;
	}
    
	int i = 0;

	CPoint arryPoints[VCA_MAX_POLYGON_POINT_NUM];

	for (i = 0; i < struPolygon.dwPointNum; i++)
	{
		arryPoints[i].x = struPolygon.struPos[i].fX * nWndWidth;
		arryPoints[i].y = struPolygon.struPos[i].fY * nWndHeight;
	}

	if(dwPointNum== 2)
	{
		int nXOffset1 = arryPoints[1].x - arryPoints[0].x;
		int nYOffset1 = arryPoints[1].y - arryPoints[0].y;
		int nXOffset2 = arryPoints[1].x - pt.x;
		int nYOffset2 = arryPoints[1].y - pt.y;
		
		if(nXOffset1*nYOffset2 == nXOffset2*nYOffset1) 
		{
			return FALSE;
		}
		else  
		{
			return TRUE;
		}
	}
	
	BOOL bCrossed = FALSE;
	for(i=0; i<dwPointNum - 2; i++)
	{
		bCrossed = IsLineSegmentCross(arryPoints[i],arryPoints[i+1],arryPoints[dwPointNum-1],pt);
		if(bCrossed) return FALSE;
	}
	
	int nXOffset1 = arryPoints[dwPointNum-1].x - arryPoints[dwPointNum-2].x;
	int nYOffset1 = arryPoints[dwPointNum-1].y - arryPoints[dwPointNum-2].y;
	int nXOffset2 = arryPoints[dwPointNum-1].x - pt.x;
	int nYOffset2 = arryPoints[dwPointNum-1].y - pt.y;
	
	if(nXOffset1*nYOffset2 == nXOffset2*nYOffset1)
		return FALSE;
	
	for(i=1;i<dwPointNum-1;i++)
	{
		bCrossed = IsLineSegmentCross(arryPoints[i],arryPoints[i+1],arryPoints[0],pt);
		if(bCrossed) 
		{   
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CVcaCommonOperations::ChangeScene(NET_DVR_PTZPOS& struPtzPos)
{
	BOOL bRet = FALSE;
	struPtzPos.wAction = 1;
    if (!NET_DVR_SetDVRConfig(m_lPUServerID, NET_DVR_SET_PTZPOS, m_lRealPlayChannel, &struPtzPos, sizeof(struPtzPos)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PTZPOS Chan[%d]", m_lRealPlayChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PTZPOS Chan[%d]", m_lRealPlayChannel);
        bRet = TRUE;
    }
    return bRet;
}
