// DlgVcaFaceDetect.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaFaceDetect.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFaceDetect dialog
CDlgVcaFaceDetect *g_pDlgFaceDetect = NULL;

void  CALLBACK g_DrawFaceDetect(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    SetBkMode(hDc, TRANSPARENT);
    SetTextColor(hDc, RGB(255, 255, 255));
    
    g_pDlgFaceDetect->F_DrawFun(lRealHandle, hDc, dwUser);
}

void CDlgVcaFaceDetect::F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser)
{
    F_DrawFrame(hDc);
}
void CDlgVcaFaceDetect::F_DrawFrame(HDC hDc)
{
    DRAW_POLYGON_PARAM struPolygonParam;
    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    struPolygonParam.color = RGB(255, 255, 0);
    memcpy(&struPolygonParam.rcWnd, &m_rcWnd, sizeof(m_rcWnd));
    memcpy(&struPolygonParam.struVcaPolygon, &m_struFaceDetectRule.struVcaPolygon, sizeof(struPolygonParam.struVcaPolygon));
    struPolygonParam.bCloseIn = m_bCloseIn;
    struPolygonParam.bMouseMove = m_bMouseMove;
    
    CDrawFun::DrawVcaPolygon(hDc, &struPolygonParam);

    if (m_bFilterActive)
    {
        DRAW_RECT_PARAM struDrawRect;
        memset(&struDrawRect, 0, sizeof(struDrawRect));
        struDrawRect.color = RGB(0, 255, 125);
        memcpy(&struDrawRect.rcWnd, &m_rcWnd, sizeof(struDrawRect.rcWnd));
        memcpy(&struDrawRect.struVcaRect, &m_struFaceDetectRule.struSizeFilter.struMaxRect, sizeof(struDrawRect.struVcaRect));
        CDrawFun::DrawVcaRect(hDc, &struDrawRect);
        
        memset(&struDrawRect, 0, sizeof(struDrawRect));
        struDrawRect.color = RGB(0, 255, 125);
        memcpy(&struDrawRect.rcWnd, &m_rcWnd, sizeof(struDrawRect.rcWnd));
        memcpy(&struDrawRect.struVcaRect, &m_struFaceDetectRule.struSizeFilter.struMiniRect, sizeof(struDrawRect.struVcaRect));
        CDrawFun::DrawVcaRect(hDc, &struDrawRect);
    }

}

CDlgVcaFaceDetect::CDlgVcaFaceDetect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaFaceDetect::IDD, pParent)
    , m_bAbnormalFace(FALSE)
    , m_bCallingFace(FALSE)
    , m_bMultiFace(FALSE)
    , m_bNormalFace(FALSE)
    , m_bSunglassesFace(FALSE)
{
	//{{AFX_DATA_INIT(CDlgVcaFaceDetect)
	m_bFilterActive = FALSE;
	m_bSetMaxFilter = FALSE;
	m_bSetMiniFilter = FALSE;
	m_bHandleType1 = FALSE;
	m_bHandleType2 = FALSE;
	m_bHandleType3 = FALSE;
	m_bHandleType4 = FALSE;
	m_bHandleType5 = FALSE;
	m_bDrawPolygon = FALSE;
	m_bEnable = FALSE;
	m_csRuleName = _T("");
	m_iHour11 = 0;
	m_iHour12 = 0;
	m_iHour21 = 0;
	m_iHour22 = 0;
	m_iMin11 = 0;
	m_iMin12 = 0;
	m_iMin21 = 0;
	m_iMin22 = 0;
	m_iAlarmDuration = 0;
	m_bChkUploadFacePic = FALSE;
	m_bChkPicRecordEn = FALSE;
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
	m_bChkEnablePIP = FALSE;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_lChannel  = -1;
    m_iDevIndex = -1;
    memset(&m_struFaceDetectRule, 0, sizeof(m_struFaceDetectRule));
    m_lPlayHandle = -1;
    memset(&m_rcWnd, 0, sizeof(m_rcWnd));
    m_bCloseIn = FALSE;
    m_bMouseMove = FALSE;
    m_bNeedRedraw = FALSE;
    m_dwAlarmOutNum = 0;
	m_iChannelNum = 0;
    m_bACS = FALSE;
}


void CDlgVcaFaceDetect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaFaceDetect)
	DDX_Control(pDX, IDC_COMBO_RELSNAPCHAN3, m_comboRelSnapChan3);
	DDX_Control(pDX, IDC_COMBO_RELSNAPCHAN2, m_comboRelSnapChan2);
	DDX_Control(pDX, IDC_COMBO_RELSNAPCHAN1, m_comboRelSnapChan1);
	DDX_Control(pDX, IDC_COMBO_PIPDIV, m_comboPIPDiv);
	DDX_Control(pDX, IDC_COMBO_BACK_CHANNEL, m_comboBackChannel);
	DDX_Control(pDX, IDC_COMBO_POSITION, m_comboPosition);
	DDX_Control(pDX, IDC_COMBO_ALARM_DELAY, m_comboAlarmDelay);
	DDX_Control(pDX, IDC_COMBO_UP_LASTALARM, m_cmUpLastAlarm);
	DDX_Control(pDX, IDC_COMBO_SENSITIVE, m_comboSensitive);
	DDX_Control(pDX, IDC_LIST_RECORD_CHAN, m_listRecordChan);
	DDX_Control(pDX, IDC_LIST_ALARM_OUT, m_listAlarmOut);
	DDX_Control(pDX, IDC_COMBOWEEKDAY, m_comboWeekDay);
	DDX_Control(pDX, IDC_COMBOCOPYTIME, m_comboCopyTime);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_comboResolution);
	DDX_Control(pDX, IDC_COMBO_PRO_PIC_TYPE, m_comboProPicType);
	DDX_Control(pDX, IDC_COMBO_PIC_QUALITY, m_comboPicQuality);
	DDX_Check(pDX, IDC_CHECK_FILTER_ACTIVE, m_bFilterActive);
	DDX_Check(pDX, IDC_CHECK_SET_MAX_FILTER, m_bSetMaxFilter);
	DDX_Check(pDX, IDC_CHECK_SET_MINI_FILTER, m_bSetMiniFilter);
	DDX_Check(pDX, IDC_CHECKHANDLETYPE1, m_bHandleType1);
	DDX_Check(pDX, IDC_CHECKHANDLETYPE2, m_bHandleType2);
	DDX_Check(pDX, IDC_CHECKHANDLETYPE3, m_bHandleType3);
	DDX_Check(pDX, IDC_CHECKHANDLETYPE4, m_bHandleType4);
	DDX_Check(pDX, IDC_CHECKHANDLETYPE5, m_bHandleType5);
	DDX_Check(pDX, IDC_CHK_DRAW_POLYGON, m_bDrawPolygon);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_RULE_NAME, m_csRuleName);
	DDX_Text(pDX, IDC_EDITHOUR11, m_iHour11);
	DDX_Text(pDX, IDC_EDITHOUR12, m_iHour12);
	DDX_Text(pDX, IDC_EDITHOUR21, m_iHour21);
	DDX_Text(pDX, IDC_EDITHOUR22, m_iHour22);
	DDX_Text(pDX, IDC_EDITMIN11, m_iMin11);
	DDX_Text(pDX, IDC_EDITMIN12, m_iMin12);
	DDX_Text(pDX, IDC_EDITMIN21, m_iMin21);
	DDX_Text(pDX, IDC_EDITMIN22, m_iMin22);
	DDX_Text(pDX, IDC_EDIT_ALARM_DURATION, m_iAlarmDuration);
	DDX_Check(pDX, IDC_CHK_UPLOAD_FACE_PIC, m_bChkUploadFacePic);
	DDX_Check(pDX, IDC_CHK_PIC_RECORD_EN, m_bChkPicRecordEn);
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
	DDX_Check(pDX, IDC_CHK_ENABLE_PIP, m_bChkEnablePIP);
	//}}AFX_DATA_MAP
    DDX_Check(pDX, IDC_CHECK_ABNORMAL_FACE, m_bAbnormalFace);
    DDX_Check(pDX, IDC_CHECK_CALLING_FACE, m_bCallingFace);
    DDX_Check(pDX, IDC_CHECK_MULTI_FACE, m_bMultiFace);
    DDX_Check(pDX, IDC_CHECK_NORMAL_FACE, m_bNormalFace);
    DDX_Check(pDX, IDC_CHECK_SUNGLASSES_FACE, m_bSunglassesFace);
}


BEGIN_MESSAGE_MAP(CDlgVcaFaceDetect, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaFaceDetect)
	ON_BN_CLICKED(IDC_CHK_DRAW_POLYGON, OnChkDrawPolygon)
	ON_BN_CLICKED(IDC_TIME_OK, OnTimeOk)
	ON_BN_CLICKED(IDC_TIME_COPY, OnTimeCopy)
	ON_BN_CLICKED(IDC_BTN_SET_FACEDETECT, OnBtnSetFacedetect)
	ON_BN_CLICKED(IDC_CHECK_SET_MINI_FILTER, OnCheckSetMiniFilter)
	ON_BN_CLICKED(IDC_CHECK_SET_MAX_FILTER, OnCheckSetMaxFilter)
	ON_BN_CLICKED(IDC_CHECK_FILTER_ACTIVE, OnCheckFilterActive)
	ON_CBN_SELCHANGE(IDC_COMBOWEEKDAY, OnSelchangeComboweekday)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFaceDetect message handlers

BOOL CDlgVcaFaceDetect::OnInitDialog() 
{
    CDialog::OnInitDialog();
    char szLan[128] = {0};
	
    m_bNeedRedraw = TRUE;//Redraw polygon
    m_bCloseIn = TRUE;//Polygon is closed or not

    g_pDlgFaceDetect = this;

    m_dwAlarmOutNum =  g_struDeviceInfo[m_iDevIndex].iAlarmOutNum;
    m_iChannelnumber = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;

	m_comboBackChannel.ResetContent();
	m_comboRelSnapChan1.ResetContent();
	m_comboRelSnapChan2.ResetContent();
	m_comboRelSnapChan3.ResetContent();
    for (int i = 0; i < m_iChannelNum; i++)
    {
        sprintf(szLan, "Chan%d", i+1);
        m_comboBackChannel.InsertString(i,szLan);
		m_comboRelSnapChan1.InsertString(i,szLan);
		m_comboRelSnapChan2.InsertString(i,szLan);
		m_comboRelSnapChan3.InsertString(i,szLan);
		m_comboBackChannel.SetItemData(i, i + 1 );
		m_comboRelSnapChan1.SetItemData(i, i + 1);
		m_comboRelSnapChan2.SetItemData(i, i + 1);
		m_comboRelSnapChan3.SetItemData(i, i + 1);
    }

	g_StringLanType(szLan,"不使用","None");
	m_comboRelSnapChan1.InsertString(0,szLan);
	m_comboRelSnapChan2.InsertString(0,szLan);
	m_comboRelSnapChan3.InsertString(0,szLan);
	m_comboRelSnapChan1.SetItemData(0,0);
	m_comboRelSnapChan2.SetItemData(0,0);
	m_comboRelSnapChan3.SetItemData(0,0);

	m_comboBackChannel.SetCurSel(0);
	m_comboPIPDiv.SetCurSel(0);
	m_comboPosition.SetCurSel(0);
	m_comboRelSnapChan1.SetCurSel(0);
	m_comboRelSnapChan2.SetCurSel(0);
	m_comboRelSnapChan3.SetCurSel(0);

    if (!GetFaceDetectRule())
    {
        AfxMessageBox("Fail to get face detect rule");
    }
 
    if (!m_bACS)
    {
        StartPlay();
    }
    
    m_comboWeekDay.SetCurSel(0);
    OnSelchangeComboweekday();

    SetFaceDetectRuleToWnd(m_struFaceDetectRule);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgVcaFaceDetect::SetFaceDetectRule()
{
	m_struFaceDetectRule.dwSize = sizeof(m_struFaceDetectRule);
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_VCA_SET_FACEDETECT_RULECFG_V41, m_lChannel, &m_struFaceDetectRule, sizeof(m_struFaceDetectRule)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_VCA_SET_FACEDETECT_RULECFG_V41 Chan[%d]", m_lChannel);
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_VCA_SET_FACEDETECT_RULECFG_V41 Chan[%d]", m_lChannel);
        return TRUE;
    }
}

BOOL CDlgVcaFaceDetect::GetFaceDetectRule()
{
    DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_VCA_GET_FACEDETECT_RULECFG_V41, m_lChannel, &m_struFaceDetectRule, sizeof(m_struFaceDetectRule), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_VCA_GET_FACEDETECT_RULECFG_V41 Chan[%d]", m_lChannel);
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_VCA_GET_FACEDETECT_RULECFG_V41 Chan[%d]", m_lChannel);
        return TRUE;
    }
}

LONG CDlgVcaFaceDetect::StartPlay()
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
        bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, g_DrawFaceDetect, 0);//DC Draw callback
    }
    return m_lPlayHandle;
}

BOOL CDlgVcaFaceDetect::StopPlay()
{
    if (m_lPlayHandle >= 0)
    {
        NET_DVR_StopRealPlay(m_lPlayHandle);
        m_lPlayHandle = -1;
    }
    return TRUE;
}

void CDlgVcaFaceDetect::PostNcDestroy() 
{
	StopPlay();
    
	CDialog::PostNcDestroy();
}

void CDlgVcaFaceDetect::OnFinalRelease() 
{
	
	CDialog::OnFinalRelease();
}

BOOL CDlgVcaFaceDetect::PreTranslateMessage(MSG* pMsg) 
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

void CDlgVcaFaceDetect::OnChkDrawPolygon() 
{
	UpdateData(TRUE);
}

void CDlgVcaFaceDetect::OnTimeOk() 
{
    UpdateData(TRUE);
    if (!F_TimeTest())
    {
        return;
    }
    int	i = m_comboWeekDay.GetCurSel();	
    GetSchedTimeFromWnd(m_struFaceDetectRule.struAlarmTime[i]);	

}

void CDlgVcaFaceDetect::OnTimeCopy() 
{
    UpdateData(TRUE);
    int j,k;
    int i = m_comboWeekDay.GetCurSel();
    int m_nCopyTime = m_comboCopyTime.GetCurSel() - 1;
    
    if(m_nCopyTime == -1)
    {
        for(j=0; j<MAX_DAYS; j++)
        {
            if(j == i)
                continue;
            for(k=0; k<MAX_TIMESEGMENT_2; k++)
            {
                memcpy(&(m_struFaceDetectRule.struAlarmTime[j][k]), &(m_struFaceDetectRule.struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
            }
        }
    }
    else
    {
        for(k=0; k<MAX_TIMESEGMENT_2; k++)
        {
            memcpy(&(m_struFaceDetectRule.struAlarmTime[m_nCopyTime][k]), &(m_struFaceDetectRule.struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
        }
    }
	
}

void CDlgVcaFaceDetect::OnBtnSetFacedetect() 
{
    GetFaceDetectRuleFromWnd(m_struFaceDetectRule);
    if (!SetFaceDetectRule())
    {
        AfxMessageBox("Fail to set face detect rule");
    }
    else
    {
        AfxMessageBox("Succ to set face detect rule");
    }
}


BOOL CDlgVcaFaceDetect::PreDrawPolygonMsg(MSG* pMsg, CPoint &pt)
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
                        m_struFaceDetectRule.struVcaPolygon.dwPointNum = m_dwPosNum;		
                    }
                    if(m_dwPosNum>9)
                    {
                        char szLan[128] = {0};
                        g_StringLanType(szLan,"多边形顶点不能超过10个!","Apexes of polygon should less than 10");
                        AfxMessageBox(szLan);
                        return TRUE;
                    }
                    if((float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() <= m_struFaceDetectRule.struVcaPolygon.struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() >= m_struFaceDetectRule.struVcaPolygon.struPos[m_dwPosNum-1].fX-0.01\
                        && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() <= m_struFaceDetectRule.struVcaPolygon.struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() >= m_struFaceDetectRule.struVcaPolygon.struPos[m_dwPosNum-1].fY-0.01)
                    {
                        char szLan[128] = {0};
                        g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
                        AfxMessageBox(szLan);
                        return TRUE;
                    }
                    m_bCloseIn = FALSE;
                    m_bMouseMove = FALSE;
                    m_struFaceDetectRule.struVcaPolygon.struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                    m_struFaceDetectRule.struVcaPolygon.struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                    m_dwPosNum++;
                    m_struFaceDetectRule.struVcaPolygon.dwPointNum = m_dwPosNum;	
                    
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
                        m_struFaceDetectRule.struVcaPolygon.struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                        m_struFaceDetectRule.struVcaPolygon.struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                        m_struFaceDetectRule.struVcaPolygon.dwPointNum = m_dwPosNum+1;				
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
                    if(m_struFaceDetectRule.struVcaPolygon.struPos[i].fX != m_struFaceDetectRule.struVcaPolygon.struPos[i+1].fX)
                    {
                        bXOneLine = FALSE;
                        break;
                    }
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struFaceDetectRule.struVcaPolygon.struPos[i].fY != m_struFaceDetectRule.struVcaPolygon.struPos[i+1].fY)
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
                        m_struFaceDetectRule.struVcaPolygon.dwPointNum--;
                        m_struFaceDetectRule.struVcaPolygon.struPos[m_struFaceDetectRule.struVcaPolygon.dwPointNum].fX = 0;
                        m_struFaceDetectRule.struVcaPolygon.struPos[m_struFaceDetectRule.struVcaPolygon.dwPointNum].fY = 0;
                    }
                    m_bCloseIn = TRUE;
                }
		}
        break;
    }
    return TRUE;
}

BOOL CDlgVcaFaceDetect::PreDrawSizeFilterMsg(MSG* pMsg, CPoint &pt)
{
    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if(m_bSetMiniFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                m_struFaceDetectRule.struSizeFilter.struMiniRect.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struFaceDetectRule.struSizeFilter.struMiniRect.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
            }
        }//First coordinate of Maximal Rectangle
        else if(m_bSetMaxFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                m_struFaceDetectRule.struSizeFilter.struMaxRect.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struFaceDetectRule.struSizeFilter.struMaxRect.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
            }
        }
        break;
    case WM_MOUSEMOVE:
        if(m_bSetMiniFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)) //尺寸过滤器
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                m_struFaceDetectRule.struSizeFilter.struMiniRect.fWidth = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() - m_struFaceDetectRule.struSizeFilter.struMiniRect.fX;
                m_struFaceDetectRule.struSizeFilter.struMiniRect.fHeight = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() - m_struFaceDetectRule.struSizeFilter.struMiniRect.fY;
            }
            
        }
        else if(m_bSetMaxFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)) //尺寸过滤器
        {
            if(PtInRect(&m_rcWnd,pt))
            {	
                m_struFaceDetectRule.struSizeFilter.struMaxRect.fWidth = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() - m_struFaceDetectRule.struSizeFilter.struMaxRect.fX;
                m_struFaceDetectRule.struSizeFilter.struMaxRect.fHeight = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() - m_struFaceDetectRule.struSizeFilter.struMaxRect.fY;
            }
        }
        break;
    }
    
    return TRUE;
}

void CDlgVcaFaceDetect::GetFaceDetectRuleFromWnd(NET_DVR_FACEDETECT_RULECFG_V41& struFaceDetectRule)
{
    UpdateData(TRUE);
    struFaceDetectRule.byEnable = m_bEnable;
	struFaceDetectRule.byUpLastAlarm = m_cmUpLastAlarm.GetCurSel();
	struFaceDetectRule.byUpFacePic = m_bChkUploadFacePic;
	struFaceDetectRule.byPicRecordEnable = m_bChkPicRecordEn;
    strncpy((char*)struFaceDetectRule.byRuleName, m_csRuleName.GetBuffer(0), sizeof(struFaceDetectRule.byRuleName));
    struFaceDetectRule.byPicProType = m_comboProPicType.GetCurSel();
    struFaceDetectRule.bySensitivity = m_comboSensitive.GetCurSel() + 1;
    struFaceDetectRule.wDuration = m_iAlarmDuration;
    struFaceDetectRule.struPictureParam.wPicSize = m_comboResolution.GetCurSel();
    struFaceDetectRule.struPictureParam.wPicQuality = m_comboPicQuality.GetCurSel();
	struFaceDetectRule.wAlarmDelay = m_comboAlarmDelay.GetCurSel();

	struFaceDetectRule.struFacePIP.byEnable = m_bChkEnablePIP;
	struFaceDetectRule.struFacePIP.byBackChannel = m_comboBackChannel.GetItemData(m_comboBackChannel.GetCurSel());
	struFaceDetectRule.struFacePIP.byPosition = m_comboPosition.GetCurSel();
	struFaceDetectRule.struFacePIP.byPIPDiv = m_comboPIPDiv.GetCurSel();
    struFaceDetectRule.struSizeFilter.byActive = m_bFilterActive;
    GetRelRecordChanFromWnd(struFaceDetectRule.byRelRecordChan, g_struDeviceInfo[m_iDevIndex].iDeviceChanNum);
    int i = m_comboWeekDay.GetCurSel();	
    GetSchedTimeFromWnd(struFaceDetectRule.struAlarmTime[i]);	
    GetHandleFromWnd(struFaceDetectRule.struHandleType);

	struFaceDetectRule.wRelSnapChan[0] = m_comboRelSnapChan1.GetItemData(m_comboRelSnapChan1.GetCurSel());
	struFaceDetectRule.wRelSnapChan[1] = m_comboRelSnapChan2.GetItemData(m_comboRelSnapChan2.GetCurSel());
	struFaceDetectRule.wRelSnapChan[2] = m_comboRelSnapChan3.GetItemData(m_comboRelSnapChan3.GetCurSel());

    struFaceDetectRule.dwEventTypeEx = 0;
    struFaceDetectRule.dwEventTypeEx |= (m_bAbnormalFace << 0);
    struFaceDetectRule.dwEventTypeEx |= (m_bNormalFace << 1);
    struFaceDetectRule.dwEventTypeEx |= (m_bMultiFace << 2);
    struFaceDetectRule.dwEventTypeEx |= (m_bSunglassesFace << 3);
    struFaceDetectRule.dwEventTypeEx |= (m_bCallingFace << 4);
}

void CDlgVcaFaceDetect::SetFaceDetectRuleToWnd(NET_DVR_FACEDETECT_RULECFG_V41 const &struFaceDetectRule)
{
    m_bEnable = struFaceDetectRule.byEnable;
    m_csRuleName = struFaceDetectRule.byRuleName;
	int i;

	m_cmUpLastAlarm.SetCurSel(struFaceDetectRule.byUpLastAlarm); //2011-04-09
	m_bChkPicRecordEn = struFaceDetectRule.byPicRecordEnable;
	m_bChkUploadFacePic = struFaceDetectRule.byUpFacePic;
    m_comboProPicType.SetCurSel(struFaceDetectRule.byPicProType);
    m_comboSensitive.SetCurSel(struFaceDetectRule.bySensitivity - 1);
    m_iAlarmDuration = struFaceDetectRule.wDuration;
    m_comboResolution.SetCurSel(struFaceDetectRule.struPictureParam.wPicSize);
    m_comboPicQuality.SetCurSel(struFaceDetectRule.struPictureParam.wPicQuality);
	m_comboAlarmDelay.SetCurSel(struFaceDetectRule.wAlarmDelay);

	m_bChkEnablePIP = struFaceDetectRule.struFacePIP.byEnable;
	m_comboPIPDiv.SetCurSel(struFaceDetectRule.struFacePIP.byPIPDiv);
	m_comboPosition.SetCurSel(struFaceDetectRule.struFacePIP.byPosition);
	for (i=0; i<m_comboBackChannel.GetCount();i++)
	{
		if (struFaceDetectRule.struFacePIP.byBackChannel == m_comboBackChannel.GetItemData(i))
		{
			m_comboBackChannel.SetCurSel(i);
			break;
		}
	}

	for (i = 0; i < m_iChannelNum; i++)
	{
		if (m_comboRelSnapChan1.GetItemData(i) == struFaceDetectRule.wRelSnapChan[0])
		{
			m_comboRelSnapChan1.SetCurSel(i);
		}
		if (m_comboRelSnapChan2.GetItemData(i) == struFaceDetectRule.wRelSnapChan[1])
		{
			m_comboRelSnapChan2.SetCurSel(i);
		}
		if (m_comboRelSnapChan3.GetItemData(i) == struFaceDetectRule.wRelSnapChan[2])
		{
			m_comboRelSnapChan3.SetCurSel(i);
		}
	}

    m_bFilterActive = struFaceDetectRule.struSizeFilter.byActive;
    SetRelRecordChanToWnd(struFaceDetectRule.byRelRecordChan, g_struDeviceInfo[m_iDevIndex].iDeviceChanNum);
    
    i = m_comboWeekDay.GetCurSel();	

    m_bAbnormalFace = struFaceDetectRule.dwEventTypeEx & 0x01;
    m_bNormalFace = (struFaceDetectRule.dwEventTypeEx >> 1) & 0x01;
    m_bMultiFace = (struFaceDetectRule.dwEventTypeEx >> 2) & 0x01;
    m_bSunglassesFace = (struFaceDetectRule.dwEventTypeEx >> 3) & 0x01;
    m_bCallingFace = (struFaceDetectRule.dwEventTypeEx >> 4) & 0x01;
    
    SetSchedTimeToWnd(struFaceDetectRule.struAlarmTime[i]);	
    SetHandleToWnd(struFaceDetectRule.struHandleType);
    UpdateData(FALSE);
    

}

void CDlgVcaFaceDetect::SetRelRecordChanToWnd(BYTE const *byRelRecordChan, int ChanNum)
{
    m_listRecordChan.SetExtendedStyle(LVS_EX_CHECKBOXES);
    char szLan[128] = {0};
    int i;
    m_listRecordChan.DeleteAllItems();
    
	int nIndex = 0;
	for (i = g_struDeviceInfo[m_iDevIndex].iStartChan; i  <= g_struDeviceInfo[m_iDevIndex].iAnalogChanNum ; i++)
	{
		sprintf(szLan, "Analog Chan%d", i);
		m_listRecordChan.InsertItem(nIndex,szLan);
		m_listRecordChan.SetItemData(nIndex, i);
		nIndex++;
	}

    if (!m_bACS)
    {
        for (i = 0; i  < g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40->dwDChanNum ; i++)
        {
            sprintf(szLan, "IP Chan%d", i + 1);
            m_listRecordChan.InsertItem(nIndex,szLan);
            m_listRecordChan.SetItemData(nIndex, i + g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40->dwStartDChan);
            nIndex++;
        }
        
        for (i = 0; i < m_listRecordChan.GetItemCount(); i++)
        {   
            int nChanNumber = m_listRecordChan.GetItemData(i);
            int nAnalogChan = nChanNumber - g_struDeviceInfo[m_iDevIndex].iStartChan;
            if (nAnalogChan>=0 && byRelRecordChan[nAnalogChan])
            {
                m_listRecordChan.SetCheck(i);
            }
            else 
            {   
                int nIPChan = nChanNumber - g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40->dwStartDChan;
                if (nIPChan >= 0 && byRelRecordChan[nIPChan])
                {
                    m_listRecordChan.SetCheck(i);
                }
            }
	    }
    }
    
    
}

void CDlgVcaFaceDetect::GetRelRecordChanFromWnd(BYTE  *byRelRecordChan, int ChanNum)
{
	memset(byRelRecordChan,0,MAX_CHANNUM_V30);
	
    for (int i = 0; i < m_listRecordChan.GetItemCount(); i++)
    {   
		if (m_listRecordChan.GetCheck(i))
		{
			int nChanNumber = m_listRecordChan.GetItemData(i);
			byRelRecordChan[nChanNumber - 1] = TRUE;
		}
    }
}

void CDlgVcaFaceDetect::SetSchedTimeToWnd(const NET_DVR_SCHEDTIME *pSchedTime)
{
    m_iHour11 = pSchedTime[0].byStartHour;
    m_iMin11 = pSchedTime[0].byStartMin;
    m_iHour12 = pSchedTime[0].byStopHour;
    m_iMin12 = pSchedTime[0].byStopMin;
    m_iHour21 = pSchedTime[1].byStartHour;
    m_iMin21 = pSchedTime[1].byStartMin;
    m_iHour22 = pSchedTime[1].byStopHour;
    m_iMin22 = pSchedTime[1].byStopMin;

	m_iHour31 = pSchedTime[2].byStartHour;
    m_iMin31 = pSchedTime[2].byStartMin;
    m_iHour32 = pSchedTime[2].byStopHour;
    m_iMin32 = pSchedTime[2].byStopMin;

	m_iHour41 = pSchedTime[3].byStartHour;
    m_iMin41 = pSchedTime[3].byStartMin;
    m_iHour42 = pSchedTime[3].byStopHour;
    m_iMin42 = pSchedTime[3].byStopMin;

	m_iHour51 = pSchedTime[4].byStartHour;
    m_iMin51 = pSchedTime[4].byStartMin;
    m_iHour52 = pSchedTime[4].byStopHour;
    m_iMin52 = pSchedTime[4].byStopMin;

	m_iHour61 = pSchedTime[5].byStartHour;
    m_iMin61 = pSchedTime[5].byStartMin;
    m_iHour62 = pSchedTime[5].byStopHour;
    m_iMin62 = pSchedTime[5].byStopMin;

	m_iHour71 = pSchedTime[6].byStartHour;
    m_iMin71 = pSchedTime[6].byStartMin;
    m_iHour72 = pSchedTime[6].byStopHour;
    m_iMin72 = pSchedTime[6].byStopMin;

	m_iHour81 = pSchedTime[7].byStartHour;
    m_iMin81 = pSchedTime[7].byStartMin;
    m_iHour82 = pSchedTime[7].byStopHour;
    m_iMin82 = pSchedTime[7].byStopMin;
}

void CDlgVcaFaceDetect::GetSchedTimeFromWnd(NET_DVR_SCHEDTIME* pSchedTime)
{
    int i = m_comboWeekDay.GetCurSel();	
    pSchedTime[0].byStartHour = (BYTE)m_iHour11;
    pSchedTime[0].byStartMin = (BYTE)m_iMin11;
    pSchedTime[0].byStopHour = (BYTE)m_iHour12;
    pSchedTime[0].byStopMin = (BYTE)m_iMin12;
    pSchedTime[1].byStartHour = (BYTE)m_iHour21;
    pSchedTime[1].byStartMin = (BYTE)m_iMin21;
    pSchedTime[1].byStopHour = (BYTE)m_iHour22;
    pSchedTime[1].byStopMin = (BYTE)m_iMin22;

	pSchedTime[2].byStartHour = (BYTE)m_iHour31;
    pSchedTime[2].byStartMin = (BYTE)m_iMin31;
    pSchedTime[2].byStopHour = (BYTE)m_iHour32;
    pSchedTime[2].byStopMin = (BYTE)m_iMin32;

	pSchedTime[3].byStartHour = (BYTE)m_iHour41;
    pSchedTime[3].byStartMin = (BYTE)m_iMin41;
    pSchedTime[3].byStopHour = (BYTE)m_iHour42;
    pSchedTime[3].byStopMin = (BYTE)m_iMin42;

	pSchedTime[4].byStartHour = (BYTE)m_iHour51;
    pSchedTime[4].byStartMin = (BYTE)m_iMin51;
    pSchedTime[4].byStopHour = (BYTE)m_iHour52;
    pSchedTime[4].byStopMin = (BYTE)m_iMin52;

	pSchedTime[5].byStartHour = (BYTE)m_iHour61;
    pSchedTime[5].byStartMin = (BYTE)m_iMin61;
    pSchedTime[5].byStopHour = (BYTE)m_iHour62;
    pSchedTime[5].byStopMin = (BYTE)m_iMin62;

	pSchedTime[6].byStartHour = (BYTE)m_iHour71;
    pSchedTime[6].byStartMin = (BYTE)m_iMin71;
    pSchedTime[6].byStopHour = (BYTE)m_iHour72;
    pSchedTime[6].byStopMin = (BYTE)m_iMin72;

	pSchedTime[7].byStartHour = (BYTE)m_iHour81;
    pSchedTime[7].byStartMin = (BYTE)m_iMin81;
    pSchedTime[7].byStopHour = (BYTE)m_iHour82;
    pSchedTime[7].byStopMin = (BYTE)m_iMin82;
}

void CDlgVcaFaceDetect::SetHandleToWnd(NET_DVR_HANDLEEXCEPTION_V30 const &struHandleException)
{
    m_bHandleType1 = (struHandleException.dwHandleType) &0x01;
    m_bHandleType2 = (struHandleException.dwHandleType>>1)&0x01;
    m_bHandleType3 = (struHandleException.dwHandleType>>2)&0x01;
    m_bHandleType4 = (struHandleException.dwHandleType>>3)&0x01;
    m_bHandleType5 = (struHandleException.dwHandleType>>4)&0x01;
    
    m_listAlarmOut.DeleteAllItems();
    m_listAlarmOut.SetExtendedStyle(LVS_EX_CHECKBOXES);
    char szLan[128] = {0};
    char sbufCn[128] = {0};
    char sbufEn[128] = {0};
    int i;
    for (i = 0; i < g_struDeviceInfo[m_iDevIndex].iAlarmOutNum; i++)
    {
        sprintf(sbufCn, "输出%d", (i+1));
        sprintf(sbufEn, "Channel%d", (i+1));
        g_StringLanType(szLan, sbufCn, sbufEn);
        m_listAlarmOut.InsertItem(i, szLan);
    }
    for (i = 0; i < g_struDeviceInfo[m_iDevIndex].iAlarmOutNum; i++ )
    {
        if (struHandleException.byRelAlarmOut[i])
        {
            m_listAlarmOut.SetCheck(i);
        }
    }

}

void CDlgVcaFaceDetect::GetHandleFromWnd(NET_DVR_HANDLEEXCEPTION_V30 &struHandleException)
{
    struHandleException.dwHandleType = 0;
    struHandleException.dwHandleType |= (m_bHandleType1 << 0);
    struHandleException.dwHandleType |= (m_bHandleType2 << 1);
    struHandleException.dwHandleType |= (m_bHandleType3 << 2);
    struHandleException.dwHandleType |= (m_bHandleType4 << 3);
    struHandleException.dwHandleType |= (m_bHandleType5 << 4);
    
    for (DWORD i = 0; i < m_dwAlarmOutNum; i++)
    {
        struHandleException.byRelAlarmOut[i] = (BYTE)m_listAlarmOut.GetCheck(i);
    }
}

void CDlgVcaFaceDetect::OnCheckSetMiniFilter() 
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

void CDlgVcaFaceDetect::OnCheckSetMaxFilter() 
{
    UpdateData(TRUE);
    if (m_bSetMaxFilter)
    {
        m_bSetMiniFilter = FALSE;
        m_bDrawPolygon = FALSE;
        UpdateData(FALSE);
    }
}

void CDlgVcaFaceDetect::OnCheckFilterActive() 
{
    UpdateData(TRUE);
    GetDlgItem(IDC_CHECK_SET_MAX_FILTER)->EnableWindow(m_bFilterActive);
    GetDlgItem(IDC_CHECK_SET_MINI_FILTER)->EnableWindow(m_bFilterActive);
}


BOOL CDlgVcaFaceDetect::F_TimeTest()
{
    int i, j;
	char szLan[128] = {0};
    WORD wStartTime[MAX_TIMESEGMENT_V30], wStopTime[MAX_TIMESEGMENT_V30];
    
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
        AfxMessageBox("Hours range 0 - 24 !");
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
        AfxMessageBox("Minute range 0 - 60!");
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

void CDlgVcaFaceDetect::OnSelchangeComboweekday() 
{
    int i = m_comboWeekDay.GetCurSel();
    SetSchedTimeToWnd(m_struFaceDetectRule.struAlarmTime[i]);
}
