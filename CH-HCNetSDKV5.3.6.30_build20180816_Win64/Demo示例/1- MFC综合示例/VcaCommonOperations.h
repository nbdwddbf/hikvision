// VcaCommonOperations.h: interface for the VcaCommonOperations class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VCACOMMONOPERATIONS_H__D6ECC76E_0C8A_474D_A876_6F3907D0E023__INCLUDED_)
#define AFX_VCACOMMONOPERATIONS_H__D6ECC76E_0C8A_474D_A876_6F3907D0E023__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef void(CALLBACK *fDrawFun)(
								 LONG      lRealHandle,
								 HDC       hDc,
								 DWORD     dwUser
								 );
class CVcaCommonOperations  
{
public:
	CVcaCommonOperations();
	virtual ~CVcaCommonOperations();
protected:
	
protected:
	BOOL StartRealPlay(HWND hWndPlay,fDrawFun pfnDrawFun,void* pUserData, LONG lChannel = 0);
	BOOL StopRealPlay();
	BOOL GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream);
	BOOL IsLineSegmentCross(CPoint pFirst1, CPoint pFirst2, CPoint pSecond1, CPoint pSecond2);
	BOOL IsPolygonPointValid(const NET_VCA_POLYGON& struPolygon,const int& nWndWidth,const int& nWndHeight,const CPoint& pt);
    BOOL GetSceneCfg(NET_DVR_SCENE_CFG& struSceneCfg);
	BOOL ChangeScene(NET_DVR_PTZPOS& struPtzPos);
public:
	LONG  m_lServerID;
    LONG  m_lChannel;
    LONG  m_iDevIndex;
	LONG  m_lPUServerID;
	LONG  m_lPlayHandle;
private:
	LONG  m_lRealPlayChannel;
};

#endif // !defined(AFX_VCACOMMONOPERATIONS_H__D6ECC76E_0C8A_474D_A876_6F3907D0E023__INCLUDED_)
