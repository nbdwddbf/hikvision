// DlgPlayMotion.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPlayMotion.h"
#include "DlgIPCSimpIntellCfg.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
int g_dwPrecision = 16;
CDlgPlayMotion *g_PlayMotion = NULL;
/////////////////////////////////////////////////////////////////////////////
// CDlgPlayMotion dialog
void CALLBACK DrawSearchMotionArea(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
   CDlgPlayMotion *lp = (CDlgPlayMotion *)dwUser;

    switch(lp->m_dwSearchType)
    {
    case 0:
//         {
//             CRect rect;
//             int i = 0,j = 0;
//             CPoint point;
//             for (i = 0;i<18;i++)
//             {
//                 for (j = 0;j<22;j++)
//                 {
//                     if (g_PlayMotion->m_struSmartSearch.uSmartSearchCond.byMotionScope[i][j] == 1)
//                     {
//                         point.x = j*g_dwPrecision;
//                         point.y = i*g_dwPrecision;
//                         rect.left = point.x;
		//                         rect.top = point.y;
		//                         rect.right = point.x + g_dwPrecision;
		//                         rect.bottom = point.y + g_dwPrecision;
		//                         ::DrawEdge(hDc, &rect, BDR_SUNKENOUTER, BF_RECT);
		//                     }
		//                 }
		//             }
		//         }
		//         break;
    case 1:
    case 2:
        lp->F_DrawFun(lRealHandle, hDc, dwUser);
        break;
    default:
        break;
        
    }

	SetBkMode(hDc,TRANSPARENT);
}


DWORD  GetMotionInfoThread(LPVOID pParam)
{
    CDlgPlayMotion *pPlayMotion = (CDlgPlayMotion*)pParam;

   
    NET_DVR_SMART_SEARCH_RET struSmartSearchRet = {0};
    long nStatus = -1; 
    char szLan[128] = {0};
    
    pPlayMotion->m_listMotionTime.DeleteAllItems();
    int nItemIndex = 0;
    while (1)
    {
        nStatus = NET_DVR_SearchNextInfo(pPlayMotion->m_lSearchHandle, &struSmartSearchRet);
        CString str = "";
    
        if (-1 == nStatus)
        {
            g_StringLanType(szLan, "查找失败", "Fail to search");
            str = szLan;
			g_PlayMotion->GetDlgItem(IDC_STATIC_MOTION_SEARCH_STATE)->SetWindowText(str);
            break;
        }
        else if (NET_DVR_FILE_SUCCESS == nStatus)
        {
            char chStartTime[128] = {0};
            char chStopTime[128] = {0};
            sprintf(chStartTime, "%04d%02d%02d%02d%02d%02d",struSmartSearchRet.struStartTime.dwYear, 
                struSmartSearchRet.struStartTime.dwMonth, struSmartSearchRet.struStartTime.dwDay,
                struSmartSearchRet.struStartTime.dwHour, struSmartSearchRet.struStartTime.dwMinute, 
                struSmartSearchRet.struStartTime.dwSecond);
            sprintf(chStopTime, "%04d%02d%02d%02d%02d%02d", struSmartSearchRet.struEndTime.dwYear, struSmartSearchRet.struEndTime.dwMonth, 
                struSmartSearchRet.struEndTime.dwDay, struSmartSearchRet.struEndTime.dwHour, struSmartSearchRet.struEndTime.dwMinute, 
                struSmartSearchRet.struEndTime.dwSecond);
            
            char chCount[256]= {0};
            sprintf(chCount, "%d", nItemIndex+1);
            pPlayMotion->m_listMotionTime.InsertItem(nItemIndex, chCount, 0);
            pPlayMotion->m_listMotionTime.SetItemText(nItemIndex, 1,chStartTime);
            pPlayMotion->m_listMotionTime.SetItemText(nItemIndex, 2, chStopTime );
            TRACE("StartTime:Y[%d]M[%d]D[%d]H[%d]M[%d]S[%d]  EndTime:Y[%d]M[%d]D[%d]H[%d]M[%d]S[%d]\n",
                struSmartSearchRet.struStartTime.dwYear, struSmartSearchRet.struStartTime.dwMonth, struSmartSearchRet.struStartTime.dwDay,
                struSmartSearchRet.struStartTime.dwHour, struSmartSearchRet.struStartTime.dwMinute, struSmartSearchRet.struStartTime.dwSecond,
                struSmartSearchRet.struEndTime.dwYear, struSmartSearchRet.struEndTime.dwMonth, struSmartSearchRet.struEndTime.dwDay,
                struSmartSearchRet.struEndTime.dwHour, struSmartSearchRet.struEndTime.dwMinute, struSmartSearchRet.struEndTime.dwSecond
                );
            g_StringLanType(szLan, "获取到文件信息", "Access to file information");
            str = szLan;
            nItemIndex++;
        }
        else if (NET_DVR_ISFINDING == nStatus)
        {
            g_StringLanType(szLan, "正在查找", "searching");
            str = szLan;
        }
        else if (NET_DVR_NOMOREFILE == nStatus)
        {
            g_StringLanType(szLan, "查找时没有更多文件", "search end");
            str = szLan;
			g_PlayMotion->GetDlgItem(IDC_STATIC_MOTION_SEARCH_STATE)->SetWindowText(str);
            AfxMessageBox(szLan);
            break;
        }
        else if (NET_DVR_FILE_EXCEPTION == nStatus)
        {
            g_StringLanType(szLan, "查找文件时异常", "search exception");
            str = szLan;
			g_PlayMotion->GetDlgItem(IDC_STATIC_MOTION_SEARCH_STATE)->SetWindowText(str);
            break;
        }
        else if (NET_DVR_FILE_NOFIND == nStatus)
        {
            g_StringLanType(szLan, "没有查找到文件", "search nothing");
            str = szLan;
            AfxMessageBox(szLan);
			g_PlayMotion->GetDlgItem(IDC_STATIC_MOTION_SEARCH_STATE)->SetWindowText(str);
            break;
        }
        else
        {
            g_StringLanType(szLan, "查找错误", "search error");
            str = szLan;
			g_PlayMotion->GetDlgItem(IDC_STATIC_MOTION_SEARCH_STATE)->SetWindowText(str);
            break;
        }
        g_PlayMotion->GetDlgItem(IDC_STATIC_MOTION_SEARCH_STATE)->SetWindowText(str);
        
    }
    
    if (!NET_DVR_StopSearch(pPlayMotion->m_lSearchHandle))
    {

    }
    return 1;
}

CDlgPlayMotion::CDlgPlayMotion(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPlayMotion::IDD, pParent)
	, m_csStreamID(_T(""))
{
	//{{AFX_DATA_INIT(CDlgPlayMotion)
	m_ctDateStart = 0;
	m_ctDateStop = 0;
	m_ctTimeStart = 0;
	m_ctTimeStop = 0;
	m_iTime = 0;
	m_dwIntrusionDuration = 0;
	m_dwIntrusionRate = 0;
	m_dwIntrusionSensitivity = 0;
	m_dwTravesePlaneSensitivity = 0;
	m_dwTraversePlanePreTime = 0;
	m_dwTraversePlaneDelayTime = 0;
	m_dwIntrusionPreTime = 0;
	m_dwIntrusionDelayTime = 0;
	m_fPanPos = 0.0f;
	m_fTitlePos = 0.0f;
	m_fZoomPos = 0.0f;
	//}}AFX_DATA_INIT
    m_hFindThread = NULL;
    m_lServerID = -1;
    m_lChannel = -1;
    m_iDevIndex = -1;
    memset(&m_struSmartSearchV40, 0, sizeof(m_struSmartSearchV40));
    m_lSearchHandle = -1;
    m_lRealPlayHandle = -1;
    m_lPlayBackHandle = -1;
    m_iDrawingIndex = -1;
    memset(m_bMouseMove, 0, sizeof(m_bMouseMove));
    memset(m_struRect, 0, sizeof(m_struRect));
    memset(m_bDrawed, 0, sizeof(m_bDrawed));
    memset(&m_struStartTime, 0, sizeof(m_struStartTime)) ;
    memset(&m_struStopTime, 0, sizeof(m_struStopTime));
    m_iItemSel = -1;
	m_dwSearchType = 0;
    m_iFieldNo = 0 ;
	m_iLineNo = 0;
    
    
}


void CDlgPlayMotion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPlayMotion)
	DDX_Control(pDX, IDC_COMBO_SEX, m_cmbSex);
	DDX_Control(pDX, IDC_COMBO_ADVANCE, m_cmbAdvance);
	DDX_Control(pDX, IDC_COMBO_EYEGLASS, m_cmbEyeGlass);
	DDX_Control(pDX, IDC_COMBO_COLOR_RATE, m_cmbColorRate);
	DDX_Control(pDX, IDC_COMBO_COLOR_R, m_cmbColorR);
	DDX_Control(pDX, IDC_COMBO_COLOR_G, m_cmbColorG);
	DDX_Control(pDX, IDC_COMBO_COLOR_B, m_cmbColorB);
	DDX_Control(pDX, IDC_COMBO_AGE, m_cmbAge);
	DDX_Control(pDX, IDC_COMBO_INTRUSION_CUR_AREA, m_cmbIntrusionCurArea);
	DDX_Control(pDX, IDC_COMBO_CUR_AREA, m_cmbCurArea);
	DDX_Control(pDX, IDC_COMBO_TRAVERSE_PLANE_DIRECTION, m_cmbTraversePlaneDirction);
	DDX_Control(pDX, IDC_COMBO_SEARCH_TYPE, m_cmbSearchType);
	DDX_Control(pDX, IDC_LIST_MOTION_TIME, m_listMotionTime);
	DDX_Control(pDX, IDC_COMBO_SEARCH_SENSE, m_comboSearchSense);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_REMOTE_DATE_START, m_ctDateStart);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_REMOTE_DATE_STOP, m_ctDateStop);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_REMOTE_TIME_START, m_ctTimeStart);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_REMOTE_TIME_STOP, m_ctTimeStop);
	DDX_Text(pDX, IDC_EDIT_TIME, m_iTime);
	DDX_Text(pDX, IDC_EDIT_INTRUSION_DURATION, m_dwIntrusionDuration);
	DDX_Text(pDX, IDC_EDIT_INTRUSION_RATE, m_dwIntrusionRate);
	DDX_Text(pDX, IDC_EDIT_INTRUSION_SENSITIVITY, m_dwIntrusionSensitivity);
	DDX_Text(pDX, IDC_EDIT_TRAVERSE_PLANE_SENSITIVITY, m_dwTravesePlaneSensitivity);
	DDX_Text(pDX, IDC_EDIT_TRAVERSE_PLANE_PRE_TIME, m_dwTraversePlanePreTime);
	DDX_Text(pDX, IDC_EDIT_TRAVERSE_PLANE_DELAY_TIME, m_dwTraversePlaneDelayTime);
	DDX_Text(pDX, IDC_EDIT_INTRUSION_PRE_TIME, m_dwIntrusionPreTime);
	DDX_Text(pDX, IDC_EDIT_INTRUSION_DELAY_TIME, m_dwIntrusionDelayTime);
	DDX_Text(pDX, IDC_EDIT_PAN_POS, m_fPanPos);
	DDX_Text(pDX, IDC_EDIT_TITLE_POS, m_fTitlePos);
	DDX_Text(pDX, IDC_EDIT_ZOOM_POS, m_fZoomPos);
	DDX_Text(pDX, IDC_EDIT_STREAM_ID2, m_csStreamID);
	DDX_Control(pDX, IDC_CMB_RELATED_CHANNEL, m_cmbRelatedChan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPlayMotion, CDialog)
	//{{AFX_MSG_MAP(CDlgPlayMotion)
	ON_BN_CLICKED(IDC_BTN_MOTION_SEARCH, OnBtnMotionSearch)
	ON_BN_CLICKED(IDC_BTN_PREVIEW, OnBtnPreview)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MOTION_TIME, OnClickListMotionTime)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MOTION_TIME, OnDblclkListMotionTime)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_SEARCH_TYPE, OnSelchangeComboSearchType)
	ON_BN_CLICKED(IDC_BTN_CLEARPIC, OnBtnClearpic)
	ON_BN_CLICKED(IDC_BTN_GET_PTZ, OnBtnGetPtz)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPlayMotion message handlers

void CDlgPlayMotion::OnBtnMotionSearch() 
{
    UpdateData(TRUE);
   	char szLan[128] = {0};
 
	m_struSmartSearchV40.dwSize = sizeof(m_struSmartSearchV40);

    m_struSmartSearchV40.struStartTime.wYear = (WORD)m_ctDateStart.GetYear();
    m_struSmartSearchV40.struStartTime.byMonth = (BYTE)m_ctDateStart.GetMonth();
    m_struSmartSearchV40.struStartTime.byDay = (BYTE)m_ctDateStart.GetDay();
    m_struSmartSearchV40.struStartTime.byHour = (BYTE)m_ctTimeStart.GetHour();
    m_struSmartSearchV40.struStartTime.byMinute = (BYTE)m_ctTimeStart.GetMinute();
    m_struSmartSearchV40.struStartTime.bySecond = (BYTE)m_ctTimeStart.GetSecond();
    m_struSmartSearchV40.struEndTime.wYear = (WORD)m_ctDateStop.GetYear();
    m_struSmartSearchV40.struEndTime.byMonth = (BYTE)m_ctDateStop.GetMonth();
    m_struSmartSearchV40.struEndTime.byDay = (BYTE)m_ctDateStop.GetDay();
    m_struSmartSearchV40.struEndTime.byHour = (BYTE)m_ctTimeStop.GetHour();
    m_struSmartSearchV40.struEndTime.byMinute = (BYTE)m_ctTimeStop.GetMinute();
    m_struSmartSearchV40.struEndTime.bySecond = (BYTE)m_ctTimeStop.GetSecond();
    m_struSmartSearchV40.byISO8601 = g_bISO8601;
    m_struSmartSearchV40.cStartTimeDifferenceH = g_iHourDiffWithUTC;
    m_struSmartSearchV40.cStartTimeDifferenceM = g_iMinDiffWithUTC;
    m_struSmartSearchV40.cStopTimeDifferenceH = g_iHourDiffWithUTC;
    m_struSmartSearchV40.cStopTimeDifferenceM = g_iMinDiffWithUTC;

    //m_struSmartSearch.byChan = (BYTE)m_lChannel;

	m_struSmartSearchV40.struIDInfo.dwChannel = m_cmbRelatedChan.GetItemData(m_cmbRelatedChan.GetCurSel());
	m_struSmartSearchV40.struIDInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
	strncpy((char*)m_struSmartSearchV40.struIDInfo.byID, m_csStreamID, STREAM_ID_LEN);
	   
    DWORD dwCurSearchType = m_cmbSearchType.GetCurSel();
	
    m_struSmartSearchV40.bySearchCondType = m_cmbSearchType.GetCurSel();
    DWORD dwTemp = 0;
 
    switch(dwCurSearchType)
    {
    case 0:
        break;
    case 1:
        dwTemp = m_cmbCurArea.GetCurSel();
        //m_struSmartSearch.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[dwTemp].dwCrossDirection = m_cmbTraversePlaneDirction.GetCurSel();
        m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[dwTemp].bySensitivity = (BYTE)m_dwTravesePlaneSensitivity;
        m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[dwTemp].dwCrossDirection = (VCA_CROSS_DIRECTION)m_cmbTraversePlaneDirction.GetCurSel();
        m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.dwPreTime  = m_dwTraversePlanePreTime;
        m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.dwDelayTime = m_dwTraversePlaneDelayTime;
        m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struPTZPosInfo.dwPanPos = m_fPanPos*10;
        m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struPTZPosInfo.dwTiltPos = m_fTitlePos*10;
        m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struPTZPosInfo.dwZoomPos = m_fZoomPos*10;
        m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.byAdvanceType = m_cmbAdvance.GetCurSel();
        if (m_cmbAdvance.GetCurSel() == 1)
        {
            m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.uAdvanceCond.struHumanFeature.byAgeGroup = m_cmbAge.GetItemData(m_cmbAge.GetCurSel());
            m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.uAdvanceCond.struHumanFeature.byEyeGlass = m_cmbEyeGlass.GetItemData(m_cmbEyeGlass.GetCurSel());
            m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.uAdvanceCond.struHumanFeature.bySex = m_cmbSex.GetItemData(m_cmbSex.GetCurSel());
        }
        else if (m_cmbAdvance.GetCurSel() == 2)
        {
            m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.uAdvanceCond.struObjectFeature.byColorRatel = m_cmbColorRate.GetCurSel();
            m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.uAdvanceCond.struObjectFeature.byRed  = m_cmbColorR.GetCurSel();
            m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.uAdvanceCond.struObjectFeature.byGreen = m_cmbColorG.GetCurSel();
            m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.uAdvanceCond.struObjectFeature.byBlue = m_cmbColorB.GetCurSel();
        }
        break;
    case 2:
        dwTemp = m_cmbIntrusionCurArea.GetCurSel();
        m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[dwTemp].byRate = (BYTE)m_dwIntrusionRate;
        m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[dwTemp].wDuration = m_dwIntrusionDuration;
        m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[dwTemp].bySensitivity = m_dwIntrusionSensitivity;
        m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.dwPreTime = m_dwIntrusionPreTime;
        m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.dwDelayTime = m_dwIntrusionDelayTime;
        m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struPTZPosInfo.dwPanPos = m_fPanPos*10;
        m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struPTZPosInfo.dwTiltPos = m_fTitlePos*10;
        m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struPTZPosInfo.dwZoomPos = m_fZoomPos*10;
        m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.byAdvanceType = m_cmbAdvance.GetCurSel();
        if (m_cmbAdvance.GetCurSel() == 1)
        {
            m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.uAdvanceCond.struHumanFeature.byAgeGroup = m_cmbAge.GetItemData(m_cmbAge.GetCurSel());
            m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.uAdvanceCond.struHumanFeature.byEyeGlass = m_cmbEyeGlass.GetItemData(m_cmbEyeGlass.GetCurSel());
            m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.uAdvanceCond.struHumanFeature.bySex = m_cmbSex.GetItemData(m_cmbSex.GetCurSel());
        }
        else if (m_cmbAdvance.GetCurSel() == 2)
        {
            m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.uAdvanceCond.struObjectFeature.byColorRatel = m_cmbColorRate.GetCurSel();
            m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.uAdvanceCond.struObjectFeature.byRed  = m_cmbColorR.GetCurSel();
            m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.uAdvanceCond.struObjectFeature.byGreen = m_cmbColorG.GetCurSel();
            m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.uAdvanceCond.struObjectFeature.byBlue = m_cmbColorB.GetCurSel();
        }
        break;
    case 3:
        memcpy(&m_struSmartSearchV40.uSmartSearchCond.struFaceSnapCond.struFacePolygon, &m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion, sizeof(NET_VCA_POLYGON));

        m_struSmartSearchV40.uSmartSearchCond.struFaceSnapCond.dwPreTime  = m_dwTraversePlanePreTime;
        m_struSmartSearchV40.uSmartSearchCond.struFaceSnapCond.dwDelayTime = m_dwTraversePlaneDelayTime;
        break;
    }
    m_struSmartSearchV40.bySensitivity = m_comboSearchSense.GetCurSel()+1;
    m_lSearchHandle =  NET_DVR_SmartSearch_V40(m_lServerID, &m_struSmartSearchV40);
    
    if (-1 == m_lSearchHandle)
    {
        int i = NET_DVR_GetLastError();
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SmartSearch");
        g_StringLanType(szLan, "获取文件列表失败!", "Fail to get file list");
        return;
    }
    
    if (m_hFindThread == NULL)
    {
        m_hFindThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetMotionInfoThread),this,0,NULL);
    }
    
    if (m_hFindThread != NULL)
    {
        CloseHandle(m_hFindThread);
        m_hFindThread = NULL;
    }
}

BOOL CDlgPlayMotion::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int i = -1; 
    for (i =0 ; i < MOTION_NUM; i++)
    {
        m_bMouseMove[i] = FALSE;
        m_bDrawed[i] = FALSE;
    }

    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
    MoveWindow(&rc);

    CRect rcMotion(0, 0, 0, 0);
    GetDlgItem(IDC_PIC_MOTION_DETECT)->GetWindowRect(&rcMotion);
    ScreenToClient(&rcMotion);
    rcMotion.right = rcMotion.left - 5 + 16*22;
    rcMotion.bottom = rcMotion.top - 12 + 16*18;
    GetDlgItem(IDC_PIC_MOTION_DETECT)->MoveWindow(rcMotion);

    CTime timeCur = CTime::GetCurrentTime();
    CTime timeStart(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),0,0,0);
    CTime timeStop(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),23,59,59);
    m_ctDateStart = timeStart;
    m_ctTimeStart = timeStart;
    m_ctDateStop = timeStop;
    m_ctTimeStop = timeStop;

    m_comboSearchSense.SetCurSel(1); 

    int nIndex = 0;
    m_listMotionTime.SetExtendedStyle(m_listMotionTime.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
    char szLan[128] = {0};
    g_StringLanType(szLan, "序号","Index");
    m_listMotionTime.InsertColumn(nIndex, szLan,LVCFMT_LEFT, 50, -1);
    nIndex++;
    g_StringLanType(szLan, "开始时间", "Start time");
    m_listMotionTime.InsertColumn(nIndex, szLan, LVCFMT_LEFT, 120, -1);
    nIndex++;
    g_StringLanType(szLan, "结束时间", "Stop Time");
    m_listMotionTime.InsertColumn(nIndex, szLan, LVCFMT_LEFT, 120, -1);
    nIndex++;

	int iChanIndex = g_pMainDlg->GetCurChanIndex();
    
	if (iChanIndex > -1)
    {
        m_lChannel = g_struDeviceInfo[m_iDevIndex].pStruChanInfo[iChanIndex].iChannelNO;
    }
	GetDlgItem(IDC_PIC_MOTION_DETECT)->GetWindowRect(&m_rcWnd);

	if (iChanIndex > -1)
	{
		m_cmbRelatedChan.ResetContent();
		for (i = 0; i < g_struDeviceInfo[m_iDevIndex].iDeviceChanNum; i++)
		{
			m_cmbRelatedChan.AddString(g_struDeviceInfo[m_iDevIndex].pStruChanInfo[iChanIndex].chChanName);
			m_cmbRelatedChan.SetItemData(i, g_struDeviceInfo[m_iDevIndex].pStruChanInfo[iChanIndex].iChannelNO);
		}
	}

    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

long CDlgPlayMotion::StartPlay()
{

    NET_DVR_PREVIEWINFO struPlayInfo = { 0 };
    
    struPlayInfo.lChannel = m_lChannel;
    //			struPlayInfo.sMultiCastIP = g_struDeviceInfo[iDeviceIndex].chDeviceMultiIP;
    struPlayInfo.dwLinkMode = 0;
    struPlayInfo.dwStreamType = 0;
    struPlayInfo.hPlayWnd = GetDlgItem(IDC_PIC_MOTION_DETECT)->GetSafeHwnd();
    strncpy((char*)struPlayInfo.byStreamID, m_csStreamID, STREAM_ID_LEN);

    m_lRealPlayHandle = NET_DVR_RealPlay_V40(m_lServerID, &struPlayInfo, NULL, NULL);

    if (-1 == m_lRealPlayHandle)
    {
        AfxMessageBox("Fail to preview");
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RealPlay_V40");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RealPlay_V40");
    }
     return m_lRealPlayHandle;
}

BOOL CDlgPlayMotion::StopPlay()
{
    BOOL bRet = TRUE;
    if (m_lRealPlayHandle >= 0)
    {
        bRet = NET_DVR_StopRealPlay(m_lRealPlayHandle);
        m_lRealPlayHandle = -1;

    }   
    return bRet;
}

void CDlgPlayMotion::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	StopPlay();
	CDialog::PostNcDestroy();
}

BOOL CDlgPlayMotion::PreTranslateMessage(MSG* pMsg) 
{
    /*CPoint pt(0,0);
    CRect  rcWnd(0,0,0,0);
    GetDlgItem(IDC_PIC_MOTION_DETECT)->GetWindowRect(&rcWnd);

	GetCursorPos(&pt);

    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if (PtInRect(&rcWnd, pt) && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            for (int nMotionIndex = 0; nMotionIndex < MOTION_NUM; nMotionIndex++)
            {
                if (m_bDrawed[nMotionIndex] == FALSE)
                {
                    //Get the Drawing Rect Index
                    m_iDrawingIndex = nMotionIndex;  
                    m_struRect[m_iDrawingIndex].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                    m_struRect[m_iDrawingIndex].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
                    m_bMouseMove[m_iDrawingIndex] = TRUE;
                    TRACE("m_struRect.fX =%f m_struRect.fY =%f\n", m_struRect[m_iDrawingIndex].fX,m_struRect[m_iDrawingIndex].fY);
                    break;
                }
            }
        }
        break;
    case WM_LBUTTONUP:
        if (PtInRect(&rcWnd, pt) && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            m_bMouseMove[m_iDrawingIndex] = FALSE;
            m_bDrawed[m_iDrawingIndex] = TRUE;
            break;
        }
        break;
    case WM_MOUSEMOVE:
        if (PtInRect(&rcWnd, pt)  && m_bMouseMove[m_iDrawingIndex] && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {   
            m_struRect[m_iDrawingIndex].fWidth = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() -  m_struRect[m_iDrawingIndex].fX;
            m_struRect[m_iDrawingIndex].fHeight = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() -  m_struRect[m_iDrawingIndex].fY;
            
            
            TRACE("WM_MOUSEMOVE  MotionIndex[%d] fWidth[%f] fHeight[%f]\n", m_iDrawingIndex, m_struRect[m_iDrawingIndex].fWidth, m_struRect[m_iDrawingIndex].fHeight);
            
            for(int i = int(m_struRect[m_iDrawingIndex].fX * 22); i <= int((m_struRect[m_iDrawingIndex].fX +m_struRect[m_iDrawingIndex].fWidth)*22); i++)
            {
                for (int j = int(m_struRect[m_iDrawingIndex].fY*18); j <= int((m_struRect[m_iDrawingIndex].fY + m_struRect[m_iDrawingIndex].fHeight)*18); j++)
                {
                    m_struSmartSearch.byMotionScope[j][i] = 1;
                }
            }
            break;
        }
        break;
    case WM_RBUTTONDOWN:
        if (PtInRect(&rcWnd, pt) && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            memset(&m_struRect, 0, sizeof(m_struRect));
            memset(m_struSmartSearch.byMotionScope, 0, sizeof(m_struSmartSearch.byMotionScope));
            for (int i = 0; i < MOTION_NUM; i++)
            {
                m_bDrawed[i] = FALSE;
                m_bMouseMove[i] = FALSE;
            }
        }
    }
	return CDialog::PreTranslateMessage(pMsg);*/
	CPoint pt(0, 0);
    GetDlgItem(IDC_PIC_MOTION_DETECT)->GetWindowRect(&m_rcWnd);
    GetCursorPos(&pt);
    ScreenToClient(&m_rcWnd);
    ScreenToClient(&pt);
    
    // 	if (m_bChkDrawPlate)
    // 	{
    // 		PreDrawPolygonMsg(pMsg, pt);
    // 	}
    if (m_cmbSearchType.GetCurSel() == 0)
    {
        PreDrawMotionMsg(pMsg,pt);
    }
    if (m_cmbSearchType.GetCurSel() == 1)
    {
        PreDrawLineMsg(pMsg, pt);
    }
    else if(m_cmbSearchType.GetCurSel() == 2 || m_cmbSearchType.GetCurSel() == 3)
    {
        PreDrawPolygonMsg(pMsg, pt);
    }
    
    
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgPlayMotion::SetParentWnd(HWND *hhWnd, int iParentNum)
{

}

BOOL CDlgPlayMotion::CheckInitParam()
{
    g_PlayMotion = this;

    m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
    if (m_iDevIndex >= 0)
    {
        m_lServerID = g_struDeviceInfo[m_iDevIndex].lLoginID;
        int iChanIndex = g_pMainDlg->GetCurChanIndex();
        if (iChanIndex == -1)
        {
            iChanIndex = 1;
        }
        m_lChannel = g_struDeviceInfo[m_iDevIndex].pStruChanInfo[iChanIndex].iChannelNO;
    }    

	ShowSetInfo(0);
    m_cmbAdvance.ResetContent();
    char szLan[128]= {0};
    g_StringLanType(szLan,"不带","No With");
    m_cmbAdvance.AddString(szLan);
    g_StringLanType(szLan,"人体属性","Human Feature");
    m_cmbAdvance.AddString(szLan);
    g_StringLanType(szLan,"物体颜色","Object Color");
    m_cmbAdvance.AddString(szLan);
    m_cmbAdvance.SetCurSel(0);
    AddObjectIFeatureInfo();
    AddHumanFeatureInfo();

    m_cmbSearchType.SetCurSel(0);
    m_cmbCurArea.SetCurSel(0);
    m_cmbIntrusionCurArea.SetCurSel(0);
    m_cmbTraversePlaneDirction.SetCurSel(0);
    
	if (m_iDevIndex >= 0)
	{
		m_cmbRelatedChan.ResetContent();
		int i = -1;
		for (i = 0; i < g_struDeviceInfo[m_iDevIndex].iDeviceChanNum; i++)
		{
			m_cmbRelatedChan.AddString(g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].chChanName);
			m_cmbRelatedChan.SetItemData(i, g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].iChannelNO);
		}
		m_cmbRelatedChan.SetCurSel(0);
	}
	
	UpdateData(FALSE);

    return TRUE;
}

void CDlgPlayMotion::OnBtnPreview() 
{
    if (m_lRealPlayHandle >= 0)
    {
		NET_DVR_RigisterDrawFun(m_lRealPlayHandle, NULL, (DWORD)this);
        StopPlay();
        Invalidate();
    }
    else
    {
		m_dwSearchType = m_cmbSearchType.GetCurSel();
        StartPlay();
        if (m_lRealPlayHandle >= 0)
        {
            NET_DVR_RigisterDrawFun(m_lRealPlayHandle, DrawSearchMotionArea, (DWORD)this);
        }
    }
}


void CDlgPlayMotion::OnClickListMotionTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    POSITION  iPos = m_listMotionTime.GetFirstSelectedItemPosition();
    if (iPos == NULL)
    {
        return;
    }
    char szTime[32] = {0};
    char szTmp[8] = {0};
    int iOffset = 0;
    m_iItemSel = m_listMotionTime.GetNextSelectedItem(iPos);
    sprintf(szTime, "%s", m_listMotionTime.GetItemText(m_iItemSel, 1));
    memcpy(szTmp, szTime, 4);
    m_struStartTime.dwYear = atoi(szTmp);
    
    iOffset+=4;
    memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);	
    m_struStartTime.dwMonth = atoi(szTmp);
    
    iOffset+=2;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);
    m_struStartTime.dwDay = atoi(szTmp);
    
    iOffset+=2;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);
    m_struStartTime.dwHour = atoi(szTmp);
    
    iOffset+=2;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);
    m_struStartTime.dwMinute = atoi(szTmp);
    
    iOffset+=2;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);
    m_struStartTime.dwSecond = atoi(szTmp);
    
    memset(szTime, 0, 32);
    sprintf(szTime, "%s", m_listMotionTime.GetItemText(m_iItemSel, 2));//stop time
    iOffset=0;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 4);
    m_struStopTime.dwYear = atoi(szTmp);
    
    iOffset+=4;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);
    m_struStopTime.dwMonth = atoi(szTmp);
    
    iOffset+=2;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);
    m_struStopTime.dwDay = atoi(szTmp);
    
    iOffset+=2;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);
    m_struStopTime.dwHour = atoi(szTmp);
    
    iOffset+=2;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);
    m_struStopTime.dwMinute = atoi(szTmp);
    
    iOffset+=2;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);
    m_struStopTime.dwSecond = atoi(szTmp);
	UpdateData(FALSE);
	*pResult = 0;
}

void CDlgPlayMotion::OnDblclkListMotionTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	BtnRemoteFileStop();
    BtnRemotFilePlay();

	*pResult = 0;
}

void CDlgPlayMotion::BtnRemoteFileStop()
{

}

void CDlgPlayMotion::BtnRemotFilePlay()
{
    StopPlay();
    if (m_lPlayBackHandle == -1)
    {
        PlayBack();
    }
}

extern BOOL ConvertTime(time_t *lpInBuf, LPNET_DVR_TIME pOutBuf, BOOL bInToOut);

void CDlgPlayMotion::PlayBack()
 {
    UpdateData(TRUE);
    
    int m_nVerifyret = -1;
    CString csFileName;
    int iFileSelPos = 0;
    HWND hPlayWnd=GetDlgItem(IDC_PIC_MOTION_DETECT)->GetSafeHwnd();
    POSITION  posItem = m_listMotionTime.GetFirstSelectedItemPosition();
    NET_DVR_TIME struStartTime,struStopTime;
    char szLan[128] = {0};
    
    //	remoteplay_info.srcfilename=m_szFileName;
    if (m_lPlayBackHandle >= 0)
    {
        if (NET_DVR_StopPlayBack(m_lPlayBackHandle))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopPlayBack");
        }
        m_lPlayBackHandle = -1;
        Sleep(400);
    }
    if (m_lPlayBackHandle == -1)
    {
        time_t tmp;
        m_iTime = 5;
        ConvertTime(&tmp, &m_struStartTime, FALSE);
        tmp -= m_iTime;
        ConvertTime(&tmp, &m_struStartTime, TRUE);
        ConvertTime(&tmp, &m_struStopTime, FALSE);
        tmp += m_iTime;
        ConvertTime(&tmp, &m_struStopTime, TRUE);
        memcpy(&struStartTime, &m_struStartTime, sizeof(NET_DVR_TIME));
        memcpy(&struStopTime, &m_struStopTime, sizeof(NET_DVR_TIME));	
        
        
        m_lPlayBackHandle = NET_DVR_PlayBackByTime(m_lServerID, m_lChannel, &struStartTime, &struStopTime, hPlayWnd);//NULL
        
        if (m_lPlayBackHandle== -1)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_PlayBackByTime ChanNum[%d]", m_lChannel);
            g_StringLanType(szLan, "远程回放失败", "Fail to play back remote");
            AfxMessageBox(szLan);
            return;
        }
        NET_DVR_GetPlayBackPlayerIndex(m_lPlayBackHandle);

        NET_DVR_PlayBackControl(m_lPlayBackHandle, NET_DVR_PLAYSTART, 0, NULL);

#if 1

        if (NET_DVR_PlayBackControl(m_lPlayBackHandle, NET_DVR_PLAYSTARTAUDIO, 0, NULL))
        {
//            m_bSound=TRUE;
            NET_DVR_PlayBackControl(m_lPlayBackHandle, NET_DVR_PLAYAUDIOVOLUME, (0xffff)/2, NULL);
  //          m_sliderVolume.SetPos(50);
//            ((CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SOUND))->SetIcon(m_hSoundStartIcon);
        }
        else
        {
//             m_bSound=FALSE;
//             ((CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SOUND))->SetIcon(m_hSoundStopIcon);
        }
#endif
        //SetPlayState();
        SetTimer(PLAYBYTIME_TIMER, 3000, NULL);
    }
    else
    {
//         if (m_bPause)
//         {
//             if (NET_DVR_PlayBackControl(m_lPlayBackHandle, NET_DVR_PLAYRESTART, 0, NULL))
//             {
//                 g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_PLAYRESTART");
//                 m_bPause=FALSE;
//                 SetPlayState();
//             }
//         }
//         else
//         {
//             if (NET_DVR_PlayBackControl(m_lPlayBackHandle, NET_DVR_PLAYPAUSE, 0, NULL))
//             {
//                 g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_PLAYPAUSE");
//                 m_bPause=TRUE;
//                 CButton *pButton;	
//                 pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_PLAY);
//                 pButton->SetIcon(m_hPlayEnableIcon);
//                 pButton->EnableWindow(TRUE);
//             }
//         }
    }
}


#if (_MSC_VER >= 1500)	//vs2008
void CDlgPlayMotion::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgPlayMotion::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: Add your message handler code here and/or call default
    DWORD nPos;
    char szLan[128] = {0};
    //	NET_DVR_TIME struOsdTime;
    if (nIDEvent == PLAYBYTIME_TIMER)
    {
        if (m_lPlayBackHandle >= 0)
        {
            if (NET_DVR_PlayBackControl(m_lPlayBackHandle, NET_DVR_PLAYGETPOS, 0, &nPos))
            {
                g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_PLAYGETPOS pos[%d]", nPos);
            }
            else
            {
                g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_PLAYGETPOS");
            }
            
            if (nPos > 100)
            {
                StopPlayBack();
                g_StringLanType(szLan, "由于网络原因或DVR忙,回放异常终止!", " Due to network reasons or DVR is busy, playback abnormal termination");
                AfxMessageBox(szLan);
            }
            if (nPos == 100)
            {				
                StopPlayBack();
                g_StringLanType(szLan, "按时间回放结束", "playback by time over");
                AfxMessageBox(szLan);
            }		
        }
        
    }

	CDialog::OnTimer(nIDEvent);
}

void CDlgPlayMotion::StopPlayBack()
{
    if (m_lPlayBackHandle >= 0)
    {
        if (!NET_DVR_StopPlayBack(m_lPlayBackHandle))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopPlayBack");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopPlayBack");
        
        }
        m_lPlayBackHandle = -1;
        //KillTimer(REMOTE_PLAY_STATE_TIMER);
        UpdateData(FALSE);
        Invalidate(TRUE);
    }
//     m_bPause = FALSE;
//     m_bSetFrame = FALSE;
//     
// 	SetStopState();
}

void CDlgPlayMotion::OnSelchangeComboSearchType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    int iCurSelect = m_cmbSearchType.GetCurSel();
    if (iCurSelect  < 0)
    {
        iCurSelect = 0;
    }
         memset(m_bDrawed,0, sizeof(m_bDrawed));
    ShowSetInfo(iCurSelect);
    if (iCurSelect != 0)
    {
        CleanMotionPic();
        m_dwPosNum = 0;
    }
    //OnBtnClearpic();
}

void CDlgPlayMotion::ShowSetInfo(DWORD dwSearchType)
{   
    //show Detectin
     switch(dwSearchType)
     {
     case 0:
         GetDlgItem(IDC_STATIC_SENSITIVITY)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_COMBO_SEARCH_SENSE)->ShowWindow(SW_SHOW);

         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_CUR_AREA)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_COMBO_CUR_AREA)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_SENSITIVITY)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_TRAVERSE_PLANE_SENSITIVITY)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_DIRECTION)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_COMBO_TRAVERSE_PLANE_DIRECTION)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_PRE_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_EDIT_TRAVERSE_PLANE_PRE_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_PRE_TIME_SECONDS)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_DELAY_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_EDIT_TRAVERSE_PLANE_DELAY_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_DELAY_TIME_SECONDS)->ShowWindow(SW_HIDE);


         GetDlgItem(IDC_STATIC_INTRUSION_CONF)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_DURATION)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_INTRUSION_DURATION)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_EDIT_INTRUSION_PRE_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_INTRUSION_PRE_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_INTRUSION_DELAY_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_INTRUSION_PRE_TIME_SECONDS)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_EDIT_INTRUSION_DELAY_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_INTRUSION_DELAY_TIME_SECONDS)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_SENSITIVITY)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_INTRUSION_SENSITIVITY)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_RATE)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_INTRUSION_RATE)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_CUR_AREA)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_COMBO_INTRUSION_CUR_AREA)->ShowWindow(SW_HIDE);

         GetDlgItem(IDC_BTN_CLEARPIC)->ShowWindow(SW_HIDE);
         
         GetDlgItem(IDC_BTN_GET_PTZ)->ShowWindow(SW_HIDE);
         
         GetDlgItem(IDC_EDIT_PAN_POS)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_TITLE_POS)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_ZOOM_POS)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_P)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_T)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_Z)->ShowWindow(SW_HIDE);
         break;
     case 1: //Travese Plane
         GetDlgItem(IDC_STATIC_SENSITIVITY)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_COMBO_SEARCH_SENSE)->ShowWindow(SW_HIDE);
         
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_CUR_AREA)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_COMBO_CUR_AREA)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_SENSITIVITY)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_EDIT_TRAVERSE_PLANE_SENSITIVITY)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_DIRECTION)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_COMBO_TRAVERSE_PLANE_DIRECTION)->ShowWindow(SW_SHOW);
		 GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_PRE_TIME)->ShowWindow(SW_SHOW);
		 GetDlgItem(IDC_EDIT_TRAVERSE_PLANE_PRE_TIME)->ShowWindow(SW_SHOW);
		 GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_PRE_TIME_SECONDS)->ShowWindow(SW_SHOW);
		 GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_DELAY_TIME)->ShowWindow(SW_SHOW);
		 GetDlgItem(IDC_EDIT_TRAVERSE_PLANE_DELAY_TIME)->ShowWindow(SW_SHOW);
		 GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_DELAY_TIME_SECONDS)->ShowWindow(SW_SHOW);
         
         
         GetDlgItem(IDC_STATIC_INTRUSION_CONF)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_DURATION)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_INTRUSION_DURATION)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_SENSITIVITY)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_INTRUSION_SENSITIVITY)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_RATE)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_INTRUSION_RATE)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_CUR_AREA)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_COMBO_INTRUSION_CUR_AREA)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_EDIT_INTRUSION_PRE_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_INTRUSION_PRE_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_INTRUSION_DELAY_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_INTRUSION_PRE_TIME_SECONDS)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_EDIT_INTRUSION_DELAY_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_INTRUSION_DELAY_TIME_SECONDS)->ShowWindow(SW_HIDE);

         GetDlgItem(IDC_BTN_CLEARPIC)->ShowWindow(SW_SHOW);

         GetDlgItem(IDC_BTN_GET_PTZ)->ShowWindow(SW_SHOW);
         
         GetDlgItem(IDC_EDIT_PAN_POS)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_EDIT_TITLE_POS)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_EDIT_ZOOM_POS)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_P)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_T)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_Z)->ShowWindow(SW_SHOW);
         break;
     case 2:    //Intrusion
         GetDlgItem(IDC_STATIC_SENSITIVITY)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_COMBO_SEARCH_SENSE)->ShowWindow(SW_HIDE);
         
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_CUR_AREA)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_COMBO_CUR_AREA)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_SENSITIVITY)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_TRAVERSE_PLANE_SENSITIVITY)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_DIRECTION)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_COMBO_TRAVERSE_PLANE_DIRECTION)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_PRE_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_EDIT_TRAVERSE_PLANE_PRE_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_PRE_TIME_SECONDS)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_DELAY_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_EDIT_TRAVERSE_PLANE_DELAY_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_DELAY_TIME_SECONDS)->ShowWindow(SW_HIDE);
		 
         GetDlgItem(IDC_STATIC_INTRUSION_CONF)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_INTRUSION_DURATION)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_EDIT_INTRUSION_DURATION)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_INTRUSION_SENSITIVITY)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_EDIT_INTRUSION_SENSITIVITY)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_INTRUSION_RATE)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_EDIT_INTRUSION_RATE)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_INTRUSION_CUR_AREA)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_COMBO_INTRUSION_CUR_AREA)->ShowWindow(SW_SHOW);
		 GetDlgItem(IDC_EDIT_INTRUSION_PRE_TIME)->ShowWindow(SW_SHOW);
		 GetDlgItem(IDC_STATIC_INTRUSION_PRE_TIME)->ShowWindow(SW_SHOW);
		 GetDlgItem(IDC_STATIC_INTRUSION_DELAY_TIME)->ShowWindow(SW_SHOW);
		 GetDlgItem(IDC_STATIC_INTRUSION_PRE_TIME_SECONDS)->ShowWindow(SW_SHOW);
		 GetDlgItem(IDC_EDIT_INTRUSION_DELAY_TIME)->ShowWindow(SW_SHOW);
		 GetDlgItem(IDC_STATIC_INTRUSION_DELAY_TIME_SECONDS)->ShowWindow(SW_SHOW);

         GetDlgItem(IDC_BTN_CLEARPIC)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_BTN_GET_PTZ)->ShowWindow(SW_SHOW);
         
         GetDlgItem(IDC_EDIT_PAN_POS)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_EDIT_TITLE_POS)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_EDIT_ZOOM_POS)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_P)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_T)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_Z)->ShowWindow(SW_SHOW);
         break;
     case 3:
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_PRE_TIME)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_EDIT_TRAVERSE_PLANE_PRE_TIME)->ShowWindow(SW_SHOW);

         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_DELAY_TIME)->ShowWindow(SW_SHOW);
		 GetDlgItem(IDC_EDIT_TRAVERSE_PLANE_DELAY_TIME)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_SENSITIVITY)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_COMBO_SEARCH_SENSE)->ShowWindow(SW_SHOW);
         
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_CUR_AREA)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_COMBO_CUR_AREA)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_SENSITIVITY)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_TRAVERSE_PLANE_SENSITIVITY)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_DIRECTION)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_COMBO_TRAVERSE_PLANE_DIRECTION)->ShowWindow(SW_HIDE);
         
         
         GetDlgItem(IDC_STATIC_INTRUSION_CONF)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_DURATION)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_INTRUSION_DURATION)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_SENSITIVITY)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_INTRUSION_SENSITIVITY)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_RATE)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_INTRUSION_RATE)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_CUR_AREA)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_COMBO_INTRUSION_CUR_AREA)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_INTRUSION_PRE_TIME)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_PRE_TIME)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_DELAY_TIME)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_PRE_TIME_SECONDS)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_INTRUSION_DELAY_TIME)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_DELAY_TIME_SECONDS)->ShowWindow(SW_HIDE);
         
         GetDlgItem(IDC_BTN_CLEARPIC)->ShowWindow(SW_HIDE);
         
         GetDlgItem(IDC_BTN_GET_PTZ)->ShowWindow(SW_SHOW);
         
         GetDlgItem(IDC_EDIT_PAN_POS)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_EDIT_TITLE_POS)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_EDIT_ZOOM_POS)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_P)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_T)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_Z)->ShowWindow(SW_SHOW);
         break;
     default:
         GetDlgItem(IDC_STATIC_SENSITIVITY)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_COMBO_SEARCH_SENSE)->ShowWindow(SW_SHOW);
         
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_CUR_AREA)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_COMBO_CUR_AREA)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_SENSITIVITY)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_TRAVERSE_PLANE_SENSITIVITY)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_TRAVERSE_PLANE_DIRECTION)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_COMBO_TRAVERSE_PLANE_DIRECTION)->ShowWindow(SW_HIDE);
         
         
         GetDlgItem(IDC_STATIC_INTRUSION_CONF)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_DURATION)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_INTRUSION_DURATION)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_SENSITIVITY)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_INTRUSION_SENSITIVITY)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_RATE)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_EDIT_INTRUSION_RATE)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_STATIC_INTRUSION_CUR_AREA)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_COMBO_INTRUSION_CUR_AREA)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_EDIT_INTRUSION_PRE_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_INTRUSION_PRE_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_INTRUSION_DELAY_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_INTRUSION_PRE_TIME_SECONDS)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_EDIT_INTRUSION_DELAY_TIME)->ShowWindow(SW_HIDE);
		 GetDlgItem(IDC_STATIC_INTRUSION_DELAY_TIME_SECONDS)->ShowWindow(SW_HIDE);

         GetDlgItem(IDC_BTN_CLEARPIC)->ShowWindow(SW_HIDE);

         GetDlgItem(IDC_BTN_GET_PTZ)->ShowWindow(SW_SHOW);
         
         GetDlgItem(IDC_EDIT_PAN_POS)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_EDIT_TITLE_POS)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_EDIT_ZOOM_POS)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_P)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_T)->ShowWindow(SW_SHOW);
         GetDlgItem(IDC_STATIC_Z)->ShowWindow(SW_SHOW);
         break;
     }
     UpdateData(FALSE);
}

void CDlgPlayMotion::OnBtnClearpic() 
{
    // TODO: Add your control notification handler code here
//     if (m_cmbSearchType.GetCurSel() == 0)
//     {
//         memset(&(m_struSmartSearch.uSmartSearchCond.byMotionScope), 0, sizeof(BYTE)*64*96);
//     }
    if (m_cmbSearchType.GetCurSel() == 1)
    {
        memset(&(m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[m_cmbTraversePlaneDirction.GetCurSel()]), 0, sizeof(NET_VCA_TRAVERSE_PLANE));
    }
    else if (m_cmbSearchType.GetCurSel() == 2 || m_cmbSearchType.GetCurSel() == 3)
    {
        memset(&m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion , 0, sizeof(NET_VCA_INTRUSION) * MAX_INTRUSIONREGION_NUM);
        m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.dwPointNum = 0;
        m_dwPosNum = 0;
       // OnBtnPreview();
       // OnInitDialog();
        //OnBtnPreview();

    }
}

void CDlgPlayMotion::CleanMotionPic()
{
    memset(&(m_struSmartSearchV40.uSmartSearchCond.byMotionScope), 0, sizeof(BYTE)*64*96);
}

void CDlgPlayMotion::F_DrawFun( long lPlayHandle, HDC hDc, DWORD dwUser)
{
    if (m_cmbSearchType.GetCurSel() == 0)
    {
        F_DrawMotion(hDc);
    }
    if (m_cmbSearchType.GetCurSel() == 1)
    {
        F_DrawLine(hDc);
    }
    else if (m_cmbSearchType.GetCurSel() == 2 || m_cmbSearchType.GetCurSel() == 3)
    {
        F_DrawPolygon(hDc);
    }
}

void CDlgPlayMotion::F_DrawMotion(HDC hDc )
{
    CRect rect;
    int i = 0,j = 0;
    CPoint point;
    for (i = 0;i<18;i++)
    {
        for (j = 0;j<22;j++)
        {
            if (m_struSmartSearchV40.uSmartSearchCond.byMotionScope[i][j] == 1)
            {
                point.x = j*g_dwPrecision;
                point.y = i*g_dwPrecision;
                rect.left = point.x;
                rect.top = point.y;
                rect.right = point.x + g_dwPrecision;
                rect.bottom = point.y + g_dwPrecision;
                ::DrawEdge(hDc, &rect, BDR_SUNKENOUTER, BF_RECT);
            }
        }
    }
}

void CDlgPlayMotion::F_DrawLine( HDC hDc )
{
    int iDirect = -1;
    m_iLineNo = m_cmbCurArea.GetCurSel(); 
    int i = m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[m_iLineNo].struPlaneBottom.struStart.fX;
    int x1 = (int)(m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[m_iLineNo].struPlaneBottom.struStart.fX*m_rcWnd.Width());
    int y1 = (int)(m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[m_iLineNo].struPlaneBottom.struStart.fY*m_rcWnd.Height());
    int x2 = (int)(m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[m_iLineNo].struPlaneBottom.struEnd.fX*m_rcWnd.Width());
    int y2 = (int)(m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[m_iLineNo].struPlaneBottom.struEnd.fY*m_rcWnd.Height());
    
    COLORREF color = RGB(0,255,0); 
    SetTextColor(hDc,color);
    
    using namespace Gdiplus;
    Graphics graphics(hDc);
    Color DrawColor;
    DrawColor.SetValue(DrawColor.MakeARGB(50,GetRValue(color) ,GetGValue(color),GetBValue(color)));
    
    Pen pen(color, 4);
    pen.SetStartCap(LineCapFlat);
    pen.SetEndCap(LineCapFlat);
    
    CPen DrawPen;
    DrawPen.CreatePen(PS_SOLID, 2, color);
    
 
    
    HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
    MoveToEx(hDc, x1, y1, NULL);
    LineTo(hDc, x2, y2);
    
    //Draw arrow
    //    F_DrawArrowhead(hDc, lpDrawTaversePlane);
    //Draw label
    
    SelectObject(hDc, pOldPen);
    DeleteObject(DrawPen);
}

void CDlgPlayMotion::F_DrawPolygon( HDC hDc)
{
    using namespace Gdiplus;
    Graphics graphics(hDc);
    SolidBrush  brush(Color(50, 0, 0, 0));
    COLORREF color = RGB(0,255,0); 
    brush.SetColor(Color(50, GetRValue(color), GetGValue(color), GetBValue(color)));
    
    POINT point[ITC_MAX_POLYGON_POINT_NUM] = {0};
    
    CPen DrawPen;
    unsigned int i;
    
    DrawPen.CreatePen(PS_SOLID, 2, color);
    SetTextColor(hDc,color);
    SetBkMode(hDc, TRANSPARENT);

    m_iFieldNo = m_cmbIntrusionCurArea.GetCurSel(); 
    HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
    MoveToEx(hDc, (int)(m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[0].fX*m_rcWnd.Width()), \
        (int)(m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[0].fY*m_rcWnd.Height()), NULL);
    
    for(i=1; i< m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.dwPointNum && i < VCA_MAX_POLYGON_POINT_NUM + 1; i++)
    {
        
        LineTo(hDc, (int)(m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[i].fX*m_rcWnd.Width()),\
                (int)(m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[i].fY*m_rcWnd.Height()));
        //Redraw the polygon if the lines are intersectant.
        
        if (i>=MIN_PNT_NUM)
        {
            if (!m_bMouseMove[0] && (m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.dwPointNum <10))
            {
                if (IsCrossLine(&(m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion)))
                {
                    {
                        char szLan[128] = {0};
                        g_StringLanType(szLan,"多边形不相邻的边有相交情况存在,请重新输入!","Edges of Polygon can be intersectant, please redraw.!");
                        //		AfxMessageBox(szLan);
                        m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.dwPointNum--;
                        m_dwPosNum = m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.dwPointNum;
                        memset(&m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.dwPointNum], 0, sizeof(NET_VCA_POINT));
                        break;
                    }
                }
            }
        }
//                if(i>=MIN_PNT_NUM && !lpDrawPolygon->bMouseMove && IsCrossLine(&lpDrawPolygon->struVcaPolygon))
//                {
//                      char szLan[128] = {0};
//                      g_StringLanType(szLan,"多边形不相邻的边有相交情况存在,请重新输入!","Edges of Polygon can be intersectant, please redraw.!");
//                       //AfxMessageBox(szLan);
//                       lpDrawPolygon->struVcaPolygon.dwPointNum--;
//                      break;
//                }
    }
    
    for (i=0; i<(int)m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.dwPointNum ; i++)
    {
        if (i == ITC_MAX_POLYGON_POINT_NUM)
        {
            break;
        }
        
        point[i].x = (int)(m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[i].fX*m_rcWnd.Width());
        point[i].y = (int)(m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[i].fY*m_rcWnd.Height());
    }
    //After drawing the 10th point, connect it with the 1st point.
    if(ITC_MAX_POLYGON_POINT_NUM == i && !m_bMouseMove[0] && (m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.dwPointNum < 10))
    {
        if (IsValidArea(&m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion))
        {
            graphics.FillPolygon(&brush, (Point *)point, m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.dwPointNum);
            
            LineTo(hDc, point[0].x, point[0].y);
            // TextOut(hDc, point[0].x, point[0].y, lpDrawPolygon->chName, strlen(lpDrawPolygon->chName));
            
            m_bCloseIn = TRUE;
        }else//redraw
        {
            
        }
        //check if the alarm region is intact
    }
    else if(m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.dwPointNum>2 && m_bCloseIn)
    {
        if (IsValidArea(&m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion))
        {
            graphics.FillPolygon(&brush, (Point *)point, m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.dwPointNum);
            
            LineTo(hDc, point[0].x, point[0].y);
            
            //   TextOut(hDc, point[0].x, point[0].y, lpDrawPolygon->chName, strlen(lpDrawPolygon->chName));
            //            F_AddLabel(hDc, AlarmArea, dwRuleID);
        }else
        {
            //             m_bNeedRedraw[dwRuleID] = TRUE;
            //             m_bCloseIn[dwRuleID] = FALSE;
        }
    }
    
    SelectObject(hDc, pOldPen);
    DeleteObject(DrawPen);
}


BOOL CDlgPlayMotion::PreDrawPolygonMsg( MSG* pMsg, CPoint &pt )
{
	int i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;

    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && 
            PtInRect(&m_rcWnd,pt))
        {
       //     if(m_bNeedRedraw)
            {
				if (m_dwPosNum > 9)
				{
					m_bCloseIn = TRUE;
				}
                if(m_bCloseIn)
                {
                    m_dwPosNum = 0;
					m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.dwPointNum = m_dwPosNum;
                    memset(&m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo], 0, sizeof(NET_VCA_POLYGON));
                }
                if(m_dwPosNum > 9)
                {
                    char szLan[128] = {0};
                    g_StringLanType(szLan,"多边形顶点不能超过10个!","Apexes of polygon should less than 10");
                    AfxMessageBox(szLan);
                    return TRUE;
                }
				if((float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() <= m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() >= m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[m_dwPosNum-1].fX-0.01\
                    && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() <= m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() >= m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[m_dwPosNum-1].fY-0.01)
                {
                    char szLan[128] = {0};
                    g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
                    AfxMessageBox(szLan);
                    return TRUE;
                }
                m_bCloseIn = FALSE;
                m_bMouseMovePolygon = FALSE;
                m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                m_dwPosNum++;
                m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.dwPointNum = m_dwPosNum;	
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
                    if( !m_bCloseIn)
                    {
                        m_bMouseMovePolygon = TRUE;
                        m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                        m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                        m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.dwPointNum = m_dwPosNum+1;				
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
                    if(m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[i].fX != m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[i+1].fX)
                    {
                        bXOneLine = FALSE;
                        break;
                    }
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[i].fY != m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[i+1].fY)
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
                if( !m_bCloseIn)
                {
                    if(m_bMouseMovePolygon)
                    {
                        m_bMouseMovePolygon = FALSE;
                        m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.dwPointNum--;
                        m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.dwPointNum].fX = 0;
                        m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.struPos[m_struSmartSearchV40.uSmartSearchCond.struIntrusionCond.struVcaIntrusion[m_iFieldNo].struRegion.dwPointNum].fY = 0;
                    }
                    m_bCloseIn = TRUE;
                }
		}
        break;
    }
     return TRUE;
}

BOOL CDlgPlayMotion::PreDrawLineMsg( MSG* pMsg, CPoint &pt )
{
    UpdateData(TRUE);
    CString strTemp = _T("");
    DWORD i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;
    int dwTest1 = GetAsyncKeyState(VK_LCONTROL);
    int dwTest2 = GetAsyncKeyState(VK_RCONTROL);
    switch(pMsg->message)  // Message of Draw
    {
    case WM_LBUTTONDOWN:
        if( (m_cmbSearchType.GetCurSel() == 1) &&
            ((dwTest1 < 0 ) || (GetAsyncKeyState(VK_RCONTROL) < 0)))//Press CTRL to draw
        {
            if(!m_bMouseMove[0]) 
            {
                m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[m_iLineNo].struPlaneBottom.struStart.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[m_iLineNo].struPlaneBottom.struStart.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();		
                m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[m_iLineNo].struPlaneBottom.struEnd.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[m_iLineNo].struPlaneBottom.struEnd.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();			
                m_bMouseMove[0] = TRUE;
            }
            else
            {
                if ((float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() <= m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[m_iLineNo].struPlaneBottom.struStart.fX+0.01 && (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() >= m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[m_iLineNo].struPlaneBottom.struStart.fX-0.01\
                    && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() <= m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[m_iLineNo].struPlaneBottom.struStart.fY+0.01 && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() >= m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[m_iLineNo].struPlaneBottom.struStart.fY-0.01)
                {
                    char szLan[128] = {0};
                    g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
                    AfxMessageBox(szLan);
                    return TRUE;
                }
                m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[m_iLineNo].struPlaneBottom.struEnd.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[m_iLineNo].struPlaneBottom.struEnd.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();			
                m_bMouseMove[0] = FALSE;
            }
        }
        break;
    case WM_MOUSEMOVE:
        if( (m_cmbSearchType.GetCurSel() == 1)  && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                if(m_bMouseMove[0])
                {
                    m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[m_iLineNo].struPlaneBottom.struEnd.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                    m_struSmartSearchV40.uSmartSearchCond.struTraversPlaneCond.struVcaTraversePlane[m_iLineNo].struPlaneBottom.struEnd.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();			
                }
            }
        }
        break;
    case WM_RBUTTONDOWN://Click right mouse to close the rectangle. 
        break;
    default:
        break;
    }
    return TRUE;
}

BOOL CDlgPlayMotion::PreDrawMotionMsg(MSG* pMsg, CPoint &pt1)
{
    CPoint pt(0,0);
    CRect  rcWnd(0,0,0,0);
    GetDlgItem(IDC_PIC_MOTION_DETECT)->GetWindowRect(&rcWnd);
    
    GetCursorPos(&pt);
    int i1 = PtInRect(&rcWnd, pt);
    int i2 = GetAsyncKeyState(VK_LCONTROL);
    int i3 = GetAsyncKeyState(VK_RCONTROL);
    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if (PtInRect(&rcWnd, pt) && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            for (int nMotionIndex = 0; nMotionIndex < MOTION_NUM; nMotionIndex++)
            {
                //AfxMessageBox("nim");
                if (m_bDrawed[nMotionIndex] == FALSE)
                {
                    //Get the Drawing Rect Index
                    m_iDrawingIndex = nMotionIndex;  
                    m_struRect[m_iDrawingIndex].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                    m_struRect[m_iDrawingIndex].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
                    m_bMouseMove[m_iDrawingIndex] = TRUE;
                    TRACE("m_struRect.fX =%f m_struRect.fY =%f\n", m_struRect[m_iDrawingIndex].fX,m_struRect[m_iDrawingIndex].fY);
                    break;
                }
            }
        }
        break;
    case WM_LBUTTONUP:
        if (PtInRect(&rcWnd, pt) && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            m_bMouseMove[m_iDrawingIndex] = FALSE;
            m_bDrawed[m_iDrawingIndex] = TRUE;
            break;
        }
        break;
    case WM_MOUSEMOVE:
        if (PtInRect(&rcWnd, pt)  && m_bMouseMove[m_iDrawingIndex] && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {   
            m_struRect[m_iDrawingIndex].fWidth = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() -  m_struRect[m_iDrawingIndex].fX;
            m_struRect[m_iDrawingIndex].fHeight = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() -  m_struRect[m_iDrawingIndex].fY;
            
            
            TRACE("WM_MOUSEMOVE  MotionIndex[%d] fWidth[%f] fHeight[%f]\n", m_iDrawingIndex, m_struRect[m_iDrawingIndex].fWidth, m_struRect[m_iDrawingIndex].fHeight);
            
            for(int i = int(m_struRect[m_iDrawingIndex].fX * 22); i <= int((m_struRect[m_iDrawingIndex].fX +m_struRect[m_iDrawingIndex].fWidth)*22); i++)
            {
                for (int j = int(m_struRect[m_iDrawingIndex].fY*18); j <= int((m_struRect[m_iDrawingIndex].fY + m_struRect[m_iDrawingIndex].fHeight)*18); j++)
                {
                    m_struSmartSearchV40.uSmartSearchCond.byMotionScope[j][i] = 1;
                }
            }
            break;
        }
        break;
    case WM_RBUTTONDOWN:
        if (PtInRect(&rcWnd, pt) && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            memset(&m_struRect, 0, sizeof(m_struRect));
            memset(m_struSmartSearchV40.uSmartSearchCond.byMotionScope, 0, sizeof(m_struSmartSearchV40.uSmartSearchCond.byMotionScope));
            for (int i = 0; i < MOTION_NUM; i++)
            {
                m_bDrawed[i] = FALSE;
                m_bMouseMove[i] = FALSE;
            }
        }
    }
	//return CDialog::PreTranslateMessage(pMsg);
    return TRUE;
}

void CDlgPlayMotion::OnBtnGetPtz() 
{
	// TODO: Add your control notification handler code here
	   char szLan[1024] = {0};
       g_StringLanType(szLan,"请先预览", "Please RealPlay First!");
    if (m_lRealPlayHandle < 0)
	{
        AfxMessageBox(szLan);
        return;
	}

    long lPlayPort = NET_DVR_GetRealPlayerIndex(m_lRealPlayHandle);
    LONG dwRetLen = 0;
    memset(&m_struPTZInfo,0,sizeof(m_struPTZInfo));
    BYTE*pRecvBuf = NULL;
    if (PlayM4_GetStreamAdditionalInfo(lPlayPort,1, NULL,&dwRetLen))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "PlayM4_GetStreamAdditionalInfo");
    }
    else
    {
        //g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "PlayM4_GetStreamAdditionalInfo");
        

        if (dwRetLen != 0)
        {
            pRecvBuf = new BYTE[dwRetLen];
            if (pRecvBuf != NULL)
            {
                memset(pRecvBuf,0,dwRetLen);
            }
            if (!PlayM4_GetStreamAdditionalInfo(lPlayPort,1, pRecvBuf,&dwRetLen))
            {
                g_StringLanType(szLan,"获取PTZ信息失败", "Get PTZ Info Failed!");
            }
        }
    }

    if (pRecvBuf != NULL && dwRetLen == sizeof(m_struPTZInfo))
    {
        memcpy(&m_struPTZInfo,pRecvBuf,sizeof(m_struPTZInfo));
        
        delete[] pRecvBuf;
        pRecvBuf = NULL;
    }

    m_fPanPos   = m_struPTZInfo.dwP/10.0;
    m_fTitlePos = m_struPTZInfo.dwT/10.0;
    m_fZoomPos  = m_struPTZInfo.dwZ/10.0;

    UpdateData(FALSE);
}

void CDlgPlayMotion::AddHumanFeatureInfo()
{    
    m_cmbAge.ResetContent();
    DWORD dwIndex = 0;
    char szTemp[128] = {0};
    g_StringLanType(szTemp,"不关注","NOT ATTENTION");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex,0xffffffff);
    dwIndex++;
    
    g_StringLanType(szTemp,"婴幼儿","INFANT");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex,ENUM_AGE_GROUP_INFANT);
    dwIndex++;
    
    g_StringLanType(szTemp,"儿童","CHILD");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex,ENUM_AGE_GROUP_CHILD);
    dwIndex++;
    
    g_StringLanType(szTemp,"少年","YOUNGSTER");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex,ENUM_AGE_GROUP_YOUNGSTER);
    dwIndex++;
    
    g_StringLanType(szTemp,"青少年","ADOLESCENT");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex,ENUM_AGE_GROUP_ADOLESCENT);
    dwIndex++;
    
    g_StringLanType(szTemp,"青年","YOUTH");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex,ENUM_AGE_GROUP_YOUTH);
    dwIndex++;
    
    g_StringLanType(szTemp,"壮年","PRIME");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex,ENUM_AGE_GROUP_PRIME);
    dwIndex++;
    
    g_StringLanType(szTemp,"中年","MIDLIFE");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex, ENUM_AGE_GROUP_MIDLIFE);
    dwIndex++;
    
    g_StringLanType(szTemp,"中老年","MIDAGE");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex,ENUM_AGE_GROUP_MIDAGE);
    dwIndex++;
    
    g_StringLanType(szTemp,"老年","OLD");
    m_cmbAge.AddString(szTemp);
    m_cmbAge.SetItemData(dwIndex,ENUM_AGE_GROUP_OLD);
    dwIndex++;
    
    m_cmbAge.SetCurSel(0);
    
    dwIndex = 0;
    
    
    m_cmbEyeGlass.ResetContent();
    
    g_StringLanType(szTemp,"不关注","No Attention");
    m_cmbEyeGlass.AddString(szTemp);
    m_cmbEyeGlass.SetItemData(dwIndex,0xff);
    dwIndex++;
    
    g_StringLanType(szTemp,"不带","NO");
    m_cmbEyeGlass.AddString(szTemp);
    m_cmbEyeGlass.SetItemData(dwIndex,1);
    dwIndex++;

    g_StringLanType(szTemp,"带","YES");
    m_cmbEyeGlass.AddString(szTemp);
    m_cmbEyeGlass.SetItemData(dwIndex,2);
    dwIndex++;
    

    m_cmbEyeGlass.SetCurSel(0);
    
    
    dwIndex = 0;
    m_cmbSex.ResetContent();
    
    g_StringLanType(szTemp,"不关注","No Attention");
    m_cmbSex.AddString(szTemp);
    m_cmbSex.SetItemData(dwIndex,0xff);
    dwIndex++;
    
    g_StringLanType(szTemp,"男","MAN");
    m_cmbSex.AddString(szTemp);
    m_cmbSex.SetItemData(dwIndex,1);
    dwIndex++;
    
    g_StringLanType(szTemp,"女","WOMEN");
    m_cmbSex.AddString(szTemp);
    m_cmbSex.SetItemData(dwIndex,2);
    dwIndex++;
    m_cmbSex.SetCurSel(0);
}

void CDlgPlayMotion::AddObjectIFeatureInfo()
{
    m_cmbColorR.ResetContent();
    m_cmbColorG.ResetContent();
    m_cmbColorB.ResetContent();
    DWORD dwIndex = 0;
    char szTemp[128] = {0};

   for (int i =0; i < 256;i++)
   {
       sprintf(szTemp,"%d",i);
       m_cmbColorR.AddString(szTemp) ;
       m_cmbColorG.AddString(szTemp) ;
       m_cmbColorB.AddString(szTemp) ;
   }
   m_cmbColorR.SetCurSel(255);
   m_cmbColorG.SetCurSel(0);
   m_cmbColorB.SetCurSel(0);

   m_cmbColorRate.ResetContent();
   for (int j = 0; j <= 100; j++)
   {
       sprintf(szTemp,"%d",j);
       m_cmbColorRate.AddString(szTemp) ;
   }
   m_cmbColorRate.SetCurSel(50);

   UpdateData(FALSE);

}
