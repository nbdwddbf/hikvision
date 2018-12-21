// DlgPtzCfgCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPtzCfgCtrl.h"
#include "DlgIPCSimpIntellCfg.h"
#include <math.h>
#include ".\dlgptzpreset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgPtzCfgCtrl *lpPtzCfgCtrlDlg = NULL;
extern BOOL PTZControlAll(LONG lRealHandle, int iDevIndex, int iChanIndex, DWORD dwPTZCommand,DWORD dwStop, char *szCmdString);

/////////////////////////////////////////////////////////////////////////////
// CDlgPtzCfgCtrl dialog

CDlgPtzCfgCtrl::CDlgPtzCfgCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPtzCfgCtrl::IDD, pParent)
	, m_dwPosNum(0)
	, m_bCloseIn(FALSE)
	, m_bMouseMove(FALSE)
	, m_bMouseMovePolygon(FALSE)
	, m_dwRegionID(0)
	, m_hRegisterDrawThread(NULL)
{
	//{{AFX_DATA_INIT(CDlgPtzCfgCtrl)
	m_bChkProportionalPan = FALSE;
	m_bChkPresetFreezing = FALSE;
	m_bChkEnable = FALSE;
	m_bAllPatterms = FALSE;
	m_bAllPreset = FALSE;
	m_bAllPrivacyMasks = FALSE;
	m_bAllPTZLimited = FALSE;
	m_bAllScheduledTasks = FALSE;
	m_bAllParkAction = FALSE;
	m_bAllPatrols = FALSE;
	m_iDelay = 0;
	m_bChkSmartTrackEnable = FALSE;
	m_iDuration = 0;
	m_bChkPrivacyMaskEnable = FALSE;
	m_bChkSinglePrivacyMaskEnable = FALSE;
	m_bChkSinglePrivacyMaskClear = FALSE;
	m_csPrivacyMaskName = _T("");
	m_bChkPrivacyMasksRect = FALSE;
	m_bChkPrivacyMasksRectClean = FALSE;
	m_bDrawRectangular = FALSE;
	//}}AFX_DATA_INIT
	memset(&m_struPtzBasicParamCfg, 0, sizeof(m_struPtzBasicParamCfg));
	memset(&m_struPtzOsdCfg, 0, sizeof(m_struPtzOsdCfg));
	memset(&m_struPoweroffmemCfg, 0, sizeof(m_struPoweroffmemCfg));
	memset(&m_struLimitCfg, 0, sizeof(m_struLimitCfg));
	memset(&m_struLimitCtrl, 0, sizeof(m_struLimitCtrl));
	memset(&m_struClearCtrl, 0, sizeof(m_struClearCtrl));
	memset(&m_struPrioritizeCfg, 0, sizeof(m_struPrioritizeCfg));
	memset(&m_struInitialPositionCtrl, 0, sizeof(m_struInitialPositionCtrl));
	memset(&m_struSmartTrackCfg, 0, sizeof(m_struSmartTrackCfg));
	memset(&m_strZoomRatioCtrl, 0, sizeof(m_strZoomRatioCtrl));
	memset(&m_struPrivacyMasksEnableCfg, 0, sizeof(m_struPrivacyMasksEnableCfg));
	memset(&m_struPrivacyMasksCond, 0, sizeof(m_struPrivacyMasksCond));
	memset(&m_struPrivacyMasksCfg, 0, sizeof(m_struPrivacyMasksCfg));
	memset(&m_struLimitCond, 0, sizeof(m_struLimitCond));
}


void CDlgPtzCfgCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPtzCfgCtrl)
	DDX_Control(pDX, IDC_COMBO_FORMAT_DISPLAY, m_comboPositionDisplayFormat);
	DDX_Control(pDX, IDC_COMBO_PTZ_MOTIONTRACK, m_comboPTZMotionTrack);
	DDX_Control(pDX, IDC_COMBO_REGIONALID, m_comboRegionalID);
	DDX_Control(pDX, IDC_COMBO_COLORTYPE, m_comboColorType);
	DDX_Control(pDX, IDC_COMBO_ACTIVE_ZOOMRATIO, m_comboActiveZoomRatio);
	DDX_Control(pDX, IDC_COMBO_PTZ_PRIORITIZE, m_comboPTZPrioritize);
	DDX_Control(pDX, IDC_COMBO_LIMITSTATUS, m_comboLimitStatus);
	DDX_Control(pDX, IDC_COMBO_LIMITMODE, m_comboLimitMode);
	DDX_Control(pDX, IDC_COMBO_RESUME_TIME_POINT, m_comboResumeTimePoint);
	DDX_Control(pDX, IDC_COMBO_ZOOM_STATUS, m_comboZoomStatus);
	DDX_Control(pDX, IDC_COMBO_PT_STATUS, m_comboPtStatus);
	DDX_Control(pDX, IDC_COMBO_PRESET_STATUS, m_comboPresetStatus);
	DDX_Control(pDX, IDC_COMBO_ZOOMINGSPEED, m_comboZoomingSpeed);
	DDX_Control(pDX, IDC_COMBO_SCANSPEED, m_comboAutoScanSpeed);
	DDX_Control(pDX, IDC_COMBO_PRESET_SPEED, m_comboPresetSpeed);
	DDX_Control(pDX, IDC_COMBO_KEYBOARD_CTRL_SPEED, m_comboKeyboardCtrlSpeed);
	DDX_Check(pDX, IDC_CHK_PROPORTIONALPAN, m_bChkProportionalPan);
	DDX_Check(pDX, IDC_CHK_PRESET_FREEZING, m_bChkPresetFreezing);
	DDX_Check(pDX, IDC_CHK_PTZLIMIT, m_bChkEnable);
	DDX_Check(pDX, IDC_CHK_ALLPATTERMS, m_bAllPatterms);
	DDX_Check(pDX, IDC_CHK_ALLPRESET, m_bAllPreset);
	DDX_Check(pDX, IDC_CHK_ALLPRIVACYMASKS, m_bAllPrivacyMasks);
	DDX_Check(pDX, IDC_CHK_ALLPTZLIMIT, m_bAllPTZLimited);
	DDX_Check(pDX, IDC_CHK_ALLSCHEDULEDTASKS, m_bAllScheduledTasks);
	DDX_Check(pDX, IDC_CHK_ALLPARKACTION, m_bAllParkAction);
	DDX_Check(pDX, IDC_CHK_ALLPATROLS, m_bAllPatrols);
	DDX_Check(pDX, IDC_CHK_DRAW_RECT, m_bDrawRectangular);
	DDX_Text(pDX, IDC_EDIT_DELAY, m_iDelay);
	DDX_Check(pDX, IDC_CHK_SMARTTRACK_ENABLE, m_bChkSmartTrackEnable);
	DDX_Text(pDX, IDC_EDIT_SMARTTRACK_DURATION, m_iDuration);
	DDX_Check(pDX, IDC_CHK_PRIVACY_MASKS_ENABLE, m_bChkPrivacyMaskEnable);
	DDX_Check(pDX, IDC_CHK_SINGLE_PRIVACYMASKS_ENABLE, m_bChkSinglePrivacyMaskEnable);
	DDX_Check(pDX, IDC_CHK_SINGLE_PRIVACYMASKS_CLEAR, m_bChkSinglePrivacyMaskClear);
	DDX_Text(pDX, IDC_EDIT_PRIVACY_MASK_NAME, m_csPrivacyMaskName);
	DDX_Check(pDX, IDC_CHK_PRIVACY_MASKS_RECT, m_bChkPrivacyMasksRect);
	DDX_Check(pDX, IDC_CHK_PRIVACY_MASKS_RECT_CLEAN, m_bChkPrivacyMasksRectClean);
	DDX_Text(pDX, IDC_EDIT_ZOOMRATIO, m_fActiveZoomRatio);
	DDX_Check(pDX, IDC_CHECK_FLOAT_RATIO, m_bChkRatioFloatEnable);
	DDX_Control(pDX, IDC_COMBO_MANUAL_TRACKING_TRAGET, m_comboManualTrackingTraget);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPtzCfgCtrl, CDialog)
	//{{AFX_MSG_MAP(CDlgPtzCfgCtrl)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_OSDGET, OnBtnOsdget)
	ON_BN_CLICKED(IDC_BTN_OSDSAVE, OnBtnOsdsave)
	ON_BN_CLICKED(IDC_BTN_GET_POWEROFFMEMCFG, OnBtnGetPoweroffmemcfg)
	ON_BN_CLICKED(IDC_BTN_SET_POWEROFFMEMCFG, OnBtnSetPoweroffmemcfg)
	ON_BN_CLICKED(IDC_BTN_GET_LIMITCFG, OnBtnGetLimitcfg)
	ON_BN_CLICKED(IDC_BTN_SET_LIMITCFG, OnBtnSetLimitcfg)
	ON_BN_CLICKED(IDC_BTN_LIMITSET, OnBtnLimitset)
	ON_BN_CLICKED(IDC_BTN_LIMITCLEAR, OnBtnLimitclear)
	ON_BN_CLICKED(IDC_BTN_CLEARCTRL, OnBtnClearctrl)
	ON_BN_CLICKED(IDC_BTN_GET_PTZ_PRIORITIZECFG, OnBtnGetPtzPrioritizecfg)
	ON_BN_CLICKED(IDC_BTN_SET_PTZ_PRIORITIZECFG, OnBtnSetPtzPrioritizecfg)
	ON_BN_CLICKED(IDC_BTN_SET_INITIALPOSITIONCTRL, OnBtnSetInitialpositionctrl)
	ON_BN_CLICKED(IDC_BTN_GOTO_INITIALPOSITIONCTRL, OnBtnGotoInitialpositionctrl)
	ON_BN_CLICKED(IDC_BTN_CLEAR_INITIALPOSITIONCTRL, OnBtnClearInitialpositionctrl)
	ON_BN_CLICKED(IDC_BTN_GET_SMARTTRACK, OnBtnGetSmarttrack)
	ON_BN_CLICKED(IDC_BTN_SAVE_SMARTTRACK, OnBtnSaveSmarttrack)
	ON_BN_CLICKED(IDC_BTN_ZOOMRATIOCTRL, OnBtnZoomratioctrl)
	ON_BN_CLICKED(IDC_CHK_PRIVACY_MASKS_ENABLE, OnChkPrivacyMasksEnable)
	ON_BN_CLICKED(IDC_BTN_GET_PRIVACY_MASKS, OnBtnGetPrivacyMasks)
	ON_BN_CLICKED(IDC_BTN_GOTO_REGIONALID, OnBtnGotoRegionalid)
	ON_BN_CLICKED(IDC_BTN_GET_ALL_PRIVACY_MASKSCFG, OnBtnGetAllPrivacyMaskscfg)
	ON_BN_CLICKED(IDC_BTN_SAVESINGKE_REGIONINFO, OnBtnSavesingkeRegioninfo)
	ON_BN_CLICKED(IDC_BTN_SAVE_ALL_PRIVACY_MASKSCFG, OnBtnSaveAllPrivacyMaskscfg)
	ON_CBN_SELCHANGE(IDC_COMBO_REGIONALID, OnSelchangeComboRegionalid)
	ON_BN_CLICKED(IDC_CHK_PRIVACY_MASKS_RECT, OnChkPrivacyMasksRect)
	ON_BN_CLICKED(IDC_CHK_PRIVACY_MASKS_RECT_CLEAN, OnChkPrivacyMasksRectClean)
	ON_BN_CLICKED(IDC_BTN_GET_SET_SINGLEREGION, OnBtnGetSetSingleregion)
	ON_BN_CLICKED(IDC_BTN_GET_DET_REGIONCFG, OnBtnGetDetRegioncfg)
	ON_BN_CLICKED(IDC_CHECK_FLOAT_RATIO, OnCheckFloatRatio)
	ON_BN_CLICKED(IDC_CHK_DRAW_RECT, OnChkDrawRect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPtzCfgCtrl message handlers

BOOL CDlgPtzCfgCtrl::OnInitDialog() 
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWnd);
    m_bCloseIn = TRUE;
	lpPtzCfgCtrlDlg = this;
	CString tmp;
	int i = 0;
	m_comboAutoScanSpeed.ResetContent();
	for(i = 0; i < 40; i++)
    {
        tmp.Format("%d", i+1);
        m_comboAutoScanSpeed.AddString(tmp);
    }
	m_comboAutoScanSpeed.SetCurSel(0);

	m_comboRegionalID.ResetContent();
	for(i = 0; i < MAX_PRIVACY_MASKS_REGION_NUM; i++)
    {
        tmp.Format("%d", i+1);
        m_comboRegionalID.AddString(tmp);

		m_struPrivacyMasksCond[i].byRegionalID = i+1;
		m_struPrivacyMasksCond[i].dwChan = m_lChannel;
		m_struPrivacyMasksCond[i].dwSize = sizeof(NET_DVR_PRIVACY_MASKS_COND);

		m_struPrivacyMasksCfg[i].dwSize = sizeof(NET_DVR_PRIVACY_MASKS_CFG);
    }
	m_comboRegionalID.SetCurSel(0);

	m_comboActiveZoomRatio.ResetContent();
	for(i = 0; i < 100; i++)
    {
        tmp.Format("%d", i+1);
        m_comboActiveZoomRatio.AddString(tmp);
    }
	m_comboActiveZoomRatio.SetCurSel(0);

	// TODO: Add extra initialization here
	play();

	m_btnPtzUp.SubclassDlgItem(IDC_BTN_PTZUP,this);
    m_btnPtzDown.SubclassDlgItem(IDC_BTN_PTZDOWN,this);
    m_btnPtzLeft.SubclassDlgItem(IDC_BTN_PTZLEFT,this);
    m_btnPtzRight.SubclassDlgItem(IDC_BTN_PTZRIGHT,this);	
//     m_btnZoomOut.SubclassDlgItem(IDC_BTN_ZOOM_OUT,this);
//     m_btnZoomIn.SubclassDlgItem(IDC_BTN_ZOOM_IN,this);
    
    m_btnPtzUp.m_iPTZType = TILT_UP;
    m_btnPtzDown.m_iPTZType = TILT_DOWN;
    m_btnPtzLeft.m_iPTZType = PAN_LEFT;
    m_btnPtzRight.m_iPTZType = PAN_RIGHT;
//     m_btnZoomOut.m_iPTZType = ZOOM_OUT;
//     m_btnZoomIn.m_iPTZType = ZOOM_IN;

	m_btnPtzUp.m_lPlayHandle = m_lPlayHandle;
    m_btnPtzDown.m_lPlayHandle = m_lPlayHandle;
    m_btnPtzLeft.m_lPlayHandle = m_lPlayHandle;
    m_btnPtzRight.m_lPlayHandle = m_lPlayHandle;



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPtzCfgCtrl::F_DrawPrivacyMasksRegion(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    F_DrawFrame(lRealHandle, hDc, dwUser,  RGB(255, 255, 0));
}

BOOL CDlgPtzCfgCtrl::IsCrossLine(NET_VCA_POLYGON *alarm_region)
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

BOOL CDlgPtzCfgCtrl::F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2)
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

BOOL CDlgPtzCfgCtrl::IsValidArea(NET_VCA_POLYGON *alarm_region)
{
    if(alarm_region == NULL)
    {
        return FALSE;
    }
	
    if (F_IsStraightLine(alarm_region))
    {
		int iTest = m_dwRegionID;
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

void CDlgPtzCfgCtrl::F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser,  COLORREF color)
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

    MoveToEx(hDc, (int)(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[0].fX*m_rcWnd.Width()), \
        (int)(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[0].fY*m_rcWnd.Height()), NULL);
    
    for(i=1; i<m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum; i++)
    { 
		
        LineTo(hDc, (int)(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[i].fX*m_rcWnd.Width()),\
            (int)(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[i].fY*m_rcWnd.Height()));
        //if cross, redraw
        if(i>=MIN_PNT_NUM && !m_bMouseMove && IsCrossLine(&m_struPrivacyMasksCfg[m_dwRegionID].struRegion))
        {
            char szLan[128] = {0};
            g_StringLanType(szLan,"多边形不相邻的边有相交情况存在,请重新输入!","Polygon edges are not adjacent is intersect");
            AfxMessageBox(szLan);
            m_dwPosNum--;
            m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum--;
            break;
        }

    }
    
    for (i=0; i<(int)m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum; i++)
    {
        if (i == VCA_MAX_POLYGON_POINT_NUM)
        {
            break;
        }
        
        point[i].x = (int)(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[i].fX*m_rcWnd.Width());
        point[i].y = (int)(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[i].fY*m_rcWnd.Height());
    }
    
    if(VCA_MAX_POLYGON_POINT_NUM == i && !m_bMouseMove)
    {
        if (IsValidArea(&m_struPrivacyMasksCfg[m_dwRegionID].struRegion))
        {
            graphics.FillPolygon(&brush, (Point *)point, m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum);
            
            LineTo(hDc, (int)(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[0].fX*m_rcWnd.Width()), \
				(int)(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[0].fY*m_rcWnd.Height()));	
            m_bCloseIn = TRUE;
        }else
        {
            m_bCloseIn = FALSE;
            m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum--;
            m_dwPosNum--;
        }
    }
    else if(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum>2 && m_bCloseIn)
    {
        if (IsValidArea(&m_struPrivacyMasksCfg[m_dwRegionID].struRegion))
        {
            graphics.FillPolygon(&brush, (Point *)point, m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum);
            
            LineTo(hDc, (int)(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[0].fX*m_rcWnd.Width()),\
				(int)(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[0].fY*m_rcWnd.Height()));
        }else
        {
            m_bCloseIn = FALSE;
        }
    }
    
    SelectObject(hDc, pOldPen);
    DeleteObject(DrawPen);
}


void CDlgPtzCfgCtrl::F_DrawPolygon(HDC hDc)
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
    
    HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
    MoveToEx(hDc, (int)(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[0].fX*m_rcWnd.Width()), \
        (int)(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[0].fY*m_rcWnd.Height()), NULL);
    
    for(i=1; i<m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum && i < VCA_MAX_POLYGON_POINT_NUM + 1; i++)
    {
        
        LineTo(hDc, (int)(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[i].fX*m_rcWnd.Width()),\
            (int)(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[i].fY*m_rcWnd.Height()));
        //Redraw the polygon if the lines are intersectant.
		
		if (i>=MIN_PNT_NUM)
		{
			if (!m_bMouseMove)
			{
				if (IsCrossLine(&(m_struPrivacyMasksCfg[m_dwRegionID].struRegion)))
				{
					{
						char szLan[128] = {0};
						g_StringLanType(szLan,"多边形不相邻的边有相交情况存在,请重新输入!","Edges of Polygon can be intersectant, please redraw.!");
						//		AfxMessageBox(szLan);
						m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum--;
						m_dwPosNum = m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum;
						memset(&m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum], 0, sizeof(NET_VCA_POINT));
						break;
					}
				}
			}
		}
		//        if(i>=MIN_PNT_NUM && !lpDrawPolygon->bMouseMove && IsCrossLine(&lpDrawPolygon->struVcaPolygon))
		//         {
		//             char szLan[128] = {0};
		//             g_StringLanType(szLan,"多边形不相邻的边有相交情况存在,请重新输入!","Edges of Polygon can be intersectant, please redraw.!");
		//             //AfxMessageBox(szLan);
		//             lpDrawPolygon->struVcaPolygon.dwPointNum--;
		//             break;
		//         }
    }
    
    for (i=0; i<(int)m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum ; i++)
    {
        if (i == ITC_MAX_POLYGON_POINT_NUM)
        {
            break;
        }
        
        point[i].x = (int)(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[i].fX*m_rcWnd.Width());
        point[i].y = (int)(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[i].fY*m_rcWnd.Height());
    }
    //After drawing the 10th point, connect it with the 1st point.
    if(ITC_MAX_POLYGON_POINT_NUM == i && !m_bMouseMove)
    {
        if (IsValidArea(&m_struPrivacyMasksCfg[m_dwRegionID].struRegion))
        {
            graphics.FillPolygon(&brush, (Point *)point, m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum);
            
            LineTo(hDc, point[0].x, point[0].y);
           // TextOut(hDc, point[0].x, point[0].y, lpDrawPolygon->chName, strlen(lpDrawPolygon->chName));
			
            m_bCloseIn = TRUE;
        }else//redraw
        {
			
        }
        //check if the alarm region is intact
    }
    else if(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum>2 && m_bCloseIn)
    {
        if (IsValidArea(&m_struPrivacyMasksCfg[m_dwRegionID].struRegion))
        {
            graphics.FillPolygon(&brush, (Point *)point, m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum);
            
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


BOOL CDlgPtzCfgCtrl::F_IsACrossLine(NET_VCA_POLYGON *alarm_region) // 
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


BOOL CDlgPtzCfgCtrl::F_IsStraightLine(NET_VCA_POLYGON *alarm_region)  
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

void CDlgPtzCfgCtrl::F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser)
{
    if (m_bChkPrivacyMasksRect)
    {
		F_DrawFrame(lPlayHandle, hDc, dwUser,  RGB(0, 255, 0));
		//F_DrawPolygon(hDc);
    }
}

void CALLBACK DrawRectShow(LONG lRealHandle, HDC hDc,DWORD dwUser)
{
    SetBkMode(hDc, TRANSPARENT);
    SetTextColor(hDc, RGB(255, 255, 255));
	
    lpPtzCfgCtrlDlg->F_DrawFun(lRealHandle, hDc, dwUser);
}

BOOL CDlgPtzCfgCtrl::play()
{
	char szLan[128] = {0};
	char szTemp[256] = {0};
	NET_DVR_CLIENTINFO struPlayInfo; 
	memset(&struPlayInfo, 0, sizeof(NET_DVR_CLIENTINFO));
    struPlayInfo.hPlayWnd = GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
	struPlayInfo.lChannel = m_lChannel;
	struPlayInfo.lLinkMode = 0;
	
    if (struPlayInfo.lChannel < 1)
    {
        struPlayInfo.lChannel = 1;
	}
	
	if (m_lPlayHandle >= 0)
	{
		NET_DVR_StopRealPlay(m_lPlayHandle);
		m_lPlayHandle = -1;
	}
	
	m_lPlayHandle =  NET_DVR_RealPlay_V30(m_lLoginID, &struPlayInfo, NULL, NULL, TRUE); 
	
	if (m_lPlayHandle < 0)
	{
		g_StringLanType(szLan, "预览失败", "Realplay failed");
		sprintf(szTemp, "%s ErrCode: %d", szLan, NET_DVR_GetLastError());
		return FALSE;
	}
	else
	{
		if (!NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawRectShow, 0)) 
        {
            g_pMainDlg->AddLog(m_lLoginID, OPERATION_FAIL_T, "NET_DVR_RigisterDrawFun Fail");
            AfxMessageBox("Fail to set DrawFun callback");
			return FALSE;
        }
		
	}

	return TRUE;
}

void CDlgPtzCfgCtrl::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	
	DWORD dwReturn = 0;
	char szLan[128] = {0};
	m_struPtzBasicParamCfg.dwSize = sizeof(m_struPtzBasicParamCfg);
    if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_BASICPARAMCFG, m_lChannel, &m_struPtzBasicParamCfg,sizeof(m_struPtzBasicParamCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_BASICPARAMCFG %d",NET_DVR_GetLastError());
		g_StringLanType(szLan, "参数获取失败", "Get failed");
		AfxMessageBox(szLan);
    }
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_BASICPARAMCFG Success!");
	}

	m_bChkProportionalPan = m_struPtzBasicParamCfg.byProportionalPan;
	m_bChkPresetFreezing = m_struPtzBasicParamCfg.byPresetFreezing;
	m_comboPresetSpeed.SetCurSel(m_struPtzBasicParamCfg.byPresetSpeed-1);
	m_comboKeyboardCtrlSpeed.SetCurSel(m_struPtzBasicParamCfg.byKeyboardCtrlSpeed);
	m_comboAutoScanSpeed.SetCurSel(m_struPtzBasicParamCfg.byAutoScanSpeed-1);
	m_comboZoomingSpeed.SetCurSel(m_struPtzBasicParamCfg.byZoomingSpeed-1);
	m_comboManualTrackingTraget.SetCurSel(m_struPtzBasicParamCfg.byManualControlSpeed);
    m_comboPTZMotionTrack.SetCurSel(m_struPtzBasicParamCfg.byPTZMotionTrack);

	UpdateData(FALSE);
}

void CDlgPtzCfgCtrl::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};

	m_struPtzBasicParamCfg.dwSize = sizeof(m_struPtzBasicParamCfg);
	m_struPtzBasicParamCfg.byProportionalPan = m_bChkProportionalPan;
	m_struPtzBasicParamCfg.byPresetFreezing = m_bChkPresetFreezing;
	m_struPtzBasicParamCfg.byPresetSpeed = m_comboPresetSpeed.GetCurSel()+1;
	m_struPtzBasicParamCfg.byKeyboardCtrlSpeed = m_comboKeyboardCtrlSpeed.GetCurSel();
	m_struPtzBasicParamCfg.byAutoScanSpeed = m_comboAutoScanSpeed.GetCurSel()+1;
	m_struPtzBasicParamCfg.byZoomingSpeed = m_comboZoomingSpeed.GetCurSel()+1;
	m_struPtzBasicParamCfg.byManualControlSpeed = m_comboManualTrackingTraget.GetCurSel();
	m_struPtzBasicParamCfg.byPTZMotionTrack = m_comboPTZMotionTrack.GetCurSel();

	if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_BASICPARAMCFG, m_lChannel, &m_struPtzBasicParamCfg, sizeof(m_struPtzBasicParamCfg)))	
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_BASICPARAMCFG %d",NET_DVR_GetLastError());
		g_StringLanType(szLan, "参数保存失败", "Save failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_BASICPARAMCFG Success!");
	}
}

void CDlgPtzCfgCtrl::OnBtnOsdget() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	char szLan[128] = {0};
	m_struPtzOsdCfg.dwSize = sizeof(m_struPtzOsdCfg);
    if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_PTZOSDCFG, m_lChannel, &m_struPtzOsdCfg, sizeof(m_struPtzOsdCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZOSDCFG %d",NET_DVR_GetLastError());
		g_StringLanType(szLan, "参数获取失败", "Get failed");
		AfxMessageBox(szLan);
    }
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PTZOSDCFG Success!");
	}

	if (0xff == m_struPtzOsdCfg.byZoomStatus)
	{
		m_comboZoomStatus.SetCurSel(4);
	}
	else
	{
		m_comboZoomStatus.SetCurSel(m_struPtzOsdCfg.byZoomStatus);
	}
	

	if (0xff == m_struPtzOsdCfg.byPtStatus)
	{
		m_comboPtStatus.SetCurSel(4);
	}
	else
	{
		m_comboPtStatus.SetCurSel(m_struPtzOsdCfg.byPtStatus);
	}
	

	if (0xff == m_struPtzOsdCfg.byPresetStatus)
	{
		m_comboPresetStatus.SetCurSel(4);
	}
	else
	{
		m_comboPresetStatus.SetCurSel(m_struPtzOsdCfg.byPresetStatus);
	}

    m_comboPositionDisplayFormat.SetCurSel(m_struPtzOsdCfg.byPositionDisplayFormat);
	
	
	UpdateData(FALSE);
}

void CDlgPtzCfgCtrl::OnBtnOsdsave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	m_struPtzOsdCfg.dwSize = sizeof(m_struPtzOsdCfg);
	if (m_comboZoomStatus.GetCurSel() == 4)
	{
		m_struPtzOsdCfg.byZoomStatus = 0xff;
	}
	else
	{
		m_struPtzOsdCfg.byZoomStatus = m_comboZoomStatus.GetCurSel();
	}
	

	if (m_comboPtStatus.GetCurSel() == 4)
	{
		m_struPtzOsdCfg.byPtStatus = 0xff;
	}
	else
	{
		m_struPtzOsdCfg.byPtStatus = m_comboPtStatus.GetCurSel();
	}
	
	
	if (m_comboPresetStatus.GetCurSel() == 4)
	{
		m_struPtzOsdCfg.byPresetStatus = 0xff;
	}
	else
	{
		m_struPtzOsdCfg.byPresetStatus = m_comboPresetStatus.GetCurSel();
	}
	
    m_struPtzOsdCfg.byPositionDisplayFormat = m_comboPositionDisplayFormat.GetCurSel();

	if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_PTZOSDCFG, m_lChannel, &m_struPtzOsdCfg, sizeof(m_struPtzOsdCfg)))	
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PTZOSDCFG %d",NET_DVR_GetLastError());
		g_StringLanType(szLan, "参数保存失败", "Save failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PTZOSDCFG Success!");
	}
}

void CDlgPtzCfgCtrl::OnBtnGetPoweroffmemcfg() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	char szLan[128] = {0};
	m_struPoweroffmemCfg.dwSize = sizeof(m_struPoweroffmemCfg);
    if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_POWEROFFMEMCFG, m_lChannel, &m_struPoweroffmemCfg,sizeof(m_struPoweroffmemCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_POWEROFFMEMCFG %d",NET_DVR_GetLastError());
		g_StringLanType(szLan, "参数获取失败", "Get failed");
		AfxMessageBox(szLan);
    }
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_POWEROFFMEMCFG Success!");
	}

	if (m_struPoweroffmemCfg.byResumeTimePoint == 0xff)
	{
		m_comboResumeTimePoint.SetCurSel(5);
	}
	else
	{
		m_comboResumeTimePoint.SetCurSel(m_struPoweroffmemCfg.byResumeTimePoint);
	}
	

	UpdateData(FALSE);
}

void CDlgPtzCfgCtrl::OnBtnSetPoweroffmemcfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	m_struPoweroffmemCfg.dwSize = sizeof(m_struPoweroffmemCfg);
	if (m_comboResumeTimePoint.GetCurSel() == 5)
	{
		m_struPoweroffmemCfg.byResumeTimePoint = 0xff;
	}
	else
	{
		m_struPoweroffmemCfg.byResumeTimePoint = m_comboResumeTimePoint.GetCurSel();
	}
	
	
	if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_POWEROFFMEMCFG, m_lChannel, &m_struPoweroffmemCfg, sizeof(m_struPoweroffmemCfg)))	
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_POWEROFFMEMCFG %d",NET_DVR_GetLastError());
		g_StringLanType(szLan, "参数保存失败", "Save failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_POWEROFFMEMCFG Success!");
	}
}

void CDlgPtzCfgCtrl::OnBtnGetLimitcfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	char szTemp[256] = {0};
	int iCount = 1;
	m_struLimitCond.dwSize = sizeof(m_struLimitCond);
	m_struLimitCond.byLimitMode = m_comboLimitMode.GetCurSel();
	m_struLimitCond.dwChan = m_lChannel;
	m_struLimitCfg.dwSize = sizeof(m_struLimitCfg);

	DWORD *pStatus = new DWORD[iCount];
	memset(pStatus, 0, sizeof(DWORD)*iCount);
	
	BOOL bRet = NET_DVR_GetDeviceConfig(m_lLoginID, NET_DVR_GET_LIMITCFG, 1, &m_struLimitCond, \
		sizeof(m_struLimitCond)*iCount, pStatus, &m_struLimitCfg, \
		sizeof(m_struLimitCfg)*iCount);
	if (bRet)
	{
		DWORD *pStatusTmp = pStatus;
		for (int i = 0; i < iCount; i++)
		{
			if (*pStatusTmp != 0)
			{
				g_StringLanType(szLan, "获取参数失败", "Get Param configuration failed");
				sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
				AfxMessageBox(szTemp);
				delete [] pStatus;
				return;
			}
			pStatusTmp++;			 
		}
		
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LIMITCFG");
    }
    else
    {
		delete [] pStatus;
		g_StringLanType(szLan, "获取参数失败", "Get Param configuration failed");
		sprintf(szTemp, "%s %s %d", szLan, NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());
		AfxMessageBox(szTemp);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LIMITCFG");
		return;	
    }

//     if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_LIMITCFG, m_lChannel, &m_struLimitCfg,sizeof(m_struLimitCfg), &dwReturn))
//     {
//         g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LIMITCFG %d",NET_DVR_GetLastError());
// 		g_StringLanType(szLan, "参数获取失败", "Get failed");
// 		AfxMessageBox(szLan);
//     }
// 	else
// 	{
// 		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LIMITCFG Success!");
// 	}
	
	m_bChkEnable = m_struLimitCfg.byEnable;
	//m_comboLimitMode.SetCurSel(m_struLimitCfg.byLimitMode);
	m_comboLimitStatus.SetCurSel(m_struLimitCfg.byLimitStatus);
	
	UpdateData(FALSE);
}

void CDlgPtzCfgCtrl::OnBtnSetLimitcfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	char szTemp[256] = {0};
	int iConut = 1;
	m_struLimitCond.dwSize = sizeof(m_struLimitCond);
	m_struLimitCond.byLimitMode = m_comboLimitMode.GetCurSel();
	m_struLimitCond.dwChan = m_lChannel;

	m_struLimitCfg.dwSize = sizeof(m_struLimitCfg);
	m_struLimitCfg.byEnable = m_bChkEnable;
	m_struLimitCfg.byLimitStatus = m_comboLimitStatus.GetCurSel();
	
	DWORD *pStatus = new DWORD[iConut];
	memset(pStatus, 0, sizeof(DWORD)*iConut);
	if (!NET_DVR_SetDeviceConfig(m_lLoginID, NET_DVR_SET_LIMITCFG, 1, &m_struLimitCond, iConut*sizeof(m_struLimitCond), \
		pStatus, &m_struLimitCfg, iConut*sizeof(m_struLimitCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LIMITCFG");
		g_StringLanType(szLan, "设置参数失败", "Set Param configuration failed");
		sprintf(szTemp, "%s %s %d", szLan, NET_DVR_GetErrorMsg(),NET_DVR_GetLastError());
		AfxMessageBox(szTemp);
		delete [] pStatus;
		return;
	}
	else
	{
		DWORD *pStatusTmp = pStatus;
		for (int i = 0; i < iConut; i++)
		{
			
			if (*pStatusTmp != 0)
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LIMITCFG");
				g_StringLanType(szLan, "设置参数失败", "Set Param configuration failed");
				sprintf(szTemp, "%s ErrCode:%d", szLan, *pStatusTmp);
				AfxMessageBox(szTemp);
				delete [] pStatus;
				return;
			}
			pStatusTmp++;
		}
	}

	delete [] pStatus;
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LIMITCFG");
}

void CDlgPtzCfgCtrl::OnBtnLimitset() 
{
	UpdateData(TRUE);
	m_struLimitCtrl.dwSize = sizeof(m_struLimitCtrl);
	m_struLimitCtrl.dwChan = m_lChannel;
	m_struLimitCtrl.byWorkMode = 0;
	m_struLimitCtrl.byLimitMode = m_comboLimitMode.GetCurSel();
	if (!NET_DVR_RemoteControl(m_lLoginID, NET_DVR_PTZLIMIT_CTRL, &m_struLimitCtrl, sizeof(m_struLimitCtrl)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_PTZLIMIT_CTRL Err:%d", NET_DVR_GetLastError());
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_PTZLIMIT_CTRL");
	}
}

void CDlgPtzCfgCtrl::OnBtnLimitclear() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struLimitCtrl.dwSize = sizeof(m_struLimitCtrl);
	m_struLimitCtrl.dwChan = m_lChannel;
	m_struLimitCtrl.byWorkMode = 1;
	m_struLimitCtrl.byLimitMode = m_comboLimitMode.GetCurSel();
	if (!NET_DVR_RemoteControl(m_lLoginID, NET_DVR_PTZLIMIT_CTRL, &m_struLimitCtrl, sizeof(m_struLimitCtrl)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_PTZLIMIT_CTRL Err:%d", NET_DVR_GetLastError());
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_PTZLIMIT_CTRL");
	}	
}

void CDlgPtzCfgCtrl::OnBtnClearctrl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_struClearCtrl.dwSize = sizeof(m_struClearCtrl);
	m_struClearCtrl.dwChan = m_lChannel;
	m_struClearCtrl.byAllPreset = m_bAllPreset;
	m_struClearCtrl.byAllPatrols = m_bAllPatrols;
	m_struClearCtrl.byAllPatterms = m_bAllPatterms;
	m_struClearCtrl.byAllPrivacyMasks = m_bAllPrivacyMasks;
	m_struClearCtrl.byAllPTZLimited = m_bAllPTZLimited;
	m_struClearCtrl.byAllScheduledTasks = m_bAllScheduledTasks;
	m_struClearCtrl.byAllParkAction = m_bAllParkAction;
	if (!NET_DVR_RemoteControl(m_lLoginID, NET_DVR_PTZ_CLEARCTRL, &m_struClearCtrl, sizeof(m_struClearCtrl)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_PTZ_CLEARCTRL Err:%d", NET_DVR_GetLastError());
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_PTZ_CLEARCTRL size is :%d", m_struClearCtrl.dwSize);
	}
	
}

void CDlgPtzCfgCtrl::OnBtnGetPtzPrioritizecfg() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	char szLan[128] = {0};
	m_struPrioritizeCfg.dwSize = sizeof(m_struPrioritizeCfg);
    if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_PRIORITIZECFG, m_lChannel, &m_struPrioritizeCfg,sizeof(m_struPrioritizeCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PRIORITIZECFG %d",NET_DVR_GetLastError());
		g_StringLanType(szLan, "参数获取失败", "Get failed");
		AfxMessageBox(szLan);
    }
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PRIORITIZECFG Success!");
	}
	
	m_comboPTZPrioritize.SetCurSel(m_struPrioritizeCfg.byPTZPrioritize);
	m_iDelay = m_struPrioritizeCfg.dwDelay;
	
	UpdateData(FALSE);
}

void CDlgPtzCfgCtrl::OnBtnSetPtzPrioritizecfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	m_struPrioritizeCfg.dwSize = sizeof(m_struPrioritizeCfg);
	m_struPrioritizeCfg.byPTZPrioritize = m_comboPTZPrioritize.GetCurSel();
	m_struPrioritizeCfg.dwDelay = m_iDelay;
	
	if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_PRIORITIZECFG, m_lChannel, &m_struPrioritizeCfg, sizeof(m_struPrioritizeCfg)))	
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PRIORITIZECFG %d", NET_DVR_GetLastError());
		g_StringLanType(szLan, "参数保存失败", "Save failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PRIORITIZECFG Success!");
	}
}

void CDlgPtzCfgCtrl::OnBtnSetInitialpositionctrl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_struInitialPositionCtrl.dwSize = sizeof(m_struInitialPositionCtrl);
	m_struInitialPositionCtrl.dwChan = m_lChannel;
	m_struInitialPositionCtrl.byWorkMode = 0;

	if (!NET_DVR_RemoteControl(m_lLoginID, NET_DVR_PTZ_INITIALPOSITIONCTRL, &m_struInitialPositionCtrl, sizeof(m_struInitialPositionCtrl)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_PTZ_INITIALPOSITIONCTRL Err:%d", NET_DVR_GetLastError());
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_PTZ_INITIALPOSITIONCTRL");
	}
}

void CDlgPtzCfgCtrl::OnBtnGotoInitialpositionctrl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_struInitialPositionCtrl.dwSize = sizeof(m_struInitialPositionCtrl);
	m_struInitialPositionCtrl.dwChan = m_lChannel;
	m_struInitialPositionCtrl.byWorkMode = 1;
	
	if (!NET_DVR_RemoteControl(m_lLoginID, NET_DVR_PTZ_INITIALPOSITIONCTRL, &m_struInitialPositionCtrl, sizeof(m_struInitialPositionCtrl)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_PTZ_INITIALPOSITIONCTRL Err:%d", NET_DVR_GetLastError());
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_PTZ_INITIALPOSITIONCTRL");
	}
}

void CDlgPtzCfgCtrl::OnBtnClearInitialpositionctrl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_struInitialPositionCtrl.dwSize = sizeof(m_struInitialPositionCtrl);
	m_struInitialPositionCtrl.dwChan = m_lChannel;
	m_struInitialPositionCtrl.byWorkMode = 2;
	
	if (!NET_DVR_RemoteControl(m_lLoginID, NET_DVR_PTZ_INITIALPOSITIONCTRL, &m_struInitialPositionCtrl, sizeof(m_struInitialPositionCtrl)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_PTZ_INITIALPOSITIONCTRL Err:%d", NET_DVR_GetLastError());
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_PTZ_INITIALPOSITIONCTRL");
	}
}

void CDlgPtzCfgCtrl::OnBtnGetSmarttrack() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	char szLan[128] = {0};
	m_struSmartTrackCfg.dwSize = sizeof(m_struSmartTrackCfg);
    if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_SMARTTRACKCFG, m_lChannel, &m_struSmartTrackCfg, sizeof(m_struSmartTrackCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SMARTTRACKCFG %d",NET_DVR_GetLastError());
		g_StringLanType(szLan, "参数获取失败", "Get failed");
		AfxMessageBox(szLan);
    }
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SMARTTRACKCFG Success!");
	}
	
	m_iDuration = m_struSmartTrackCfg.dwDuration;
	m_bChkSmartTrackEnable = m_struSmartTrackCfg.byEnable;
	
	UpdateData(FALSE);
}

void CDlgPtzCfgCtrl::OnBtnSaveSmarttrack() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	m_struSmartTrackCfg.dwSize = sizeof(m_struSmartTrackCfg);
	m_struSmartTrackCfg.dwDuration = m_iDuration;
	m_struSmartTrackCfg.byEnable = m_bChkSmartTrackEnable;
	
	if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_SMARTTRACKCFG, m_lChannel, &m_struSmartTrackCfg, sizeof(m_struSmartTrackCfg)))	
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SMARTTRACKCFG %d", NET_DVR_GetLastError());
		g_StringLanType(szLan, "参数保存失败", "Save failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SMARTTRACKCFG Success!");
	}
}

void CDlgPtzCfgCtrl::OnBtnZoomratioctrl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_strZoomRatioCtrl.dwSize = sizeof(m_struInitialPositionCtrl);
	m_strZoomRatioCtrl.dwChan = m_lChannel;

	if (!NET_DVR_RemoteControl(m_lLoginID, NET_DVR_PTZ_ZOOMRATIOCTRL, &m_strZoomRatioCtrl, sizeof(m_strZoomRatioCtrl)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_PTZ_ZOOMRATIOCTRL Err:%d", NET_DVR_GetLastError());
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_PTZ_ZOOMRATIOCTRL");
	}
}

void CDlgPtzCfgCtrl::OnChkPrivacyMasksEnable() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	m_struPrivacyMasksEnableCfg.dwSize = sizeof(m_struPrivacyMasksEnableCfg);
	m_struPrivacyMasksEnableCfg.byEnable = m_bChkPrivacyMaskEnable;
	
	if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_PRIVACY_MASKS_ENABLECFG, m_lChannel, &m_struPrivacyMasksEnableCfg, sizeof(m_struPrivacyMasksEnableCfg)))	
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PRIVACY_MASKS_ENABLECFG %d", NET_DVR_GetLastError());
		g_StringLanType(szLan, "参数保存失败", "Save failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PRIVACY_MASKS_ENABLECFG Success!");
	}
}

void CDlgPtzCfgCtrl::OnChkDrawRect()
{
	memset(&m_struPrivacyMasksCfg[m_dwRegionID].struRegion, 0, sizeof(NET_VCA_POLYGON));		
}

void CDlgPtzCfgCtrl::OnBtnGetPrivacyMasks() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	char szLan[128] = {0};
	m_struPrivacyMasksEnableCfg.dwSize = sizeof(m_struPrivacyMasksEnableCfg);
    if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_PRIVACY_MASKS_ENABLECFG, m_lChannel, &m_struPrivacyMasksEnableCfg, sizeof(m_struPrivacyMasksEnableCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PRIVACY_MASKS_ENABLECFG %d",NET_DVR_GetLastError());
		g_StringLanType(szLan, "参数获取失败", "Get failed");
		AfxMessageBox(szLan);
    }
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PRIVACY_MASKS_ENABLECFG Success!");
	}
	
	m_bChkPrivacyMaskEnable = m_struPrivacyMasksEnableCfg.byEnable;
	
	UpdateData(FALSE);
}

void CDlgPtzCfgCtrl::ShowPrivacyMasksInfo(NET_DVR_PRIVACY_MASKS_CFG *pPrivacyMasksCfg)
{
	char cTemp[64] = {0};
	m_bChkSinglePrivacyMaskEnable = pPrivacyMasksCfg->byEnable;
	if (0xff == pPrivacyMasksCfg->byColorType)
	{
		m_comboColorType.SetCurSel(7);
	}
	else
	{
		m_comboColorType.SetCurSel(pPrivacyMasksCfg->byColorType);
	}
	m_fActiveZoomRatio = pPrivacyMasksCfg->fActiveZoomRatio;
	m_comboActiveZoomRatio.SetCurSel(pPrivacyMasksCfg->byActiveZoomRatio - 1);
	m_bChkSinglePrivacyMaskClear = pPrivacyMasksCfg->byPrivacyMaskCfgEnable;

	memcpy(cTemp, pPrivacyMasksCfg->sPrivacyMaskName, 32);
	m_csPrivacyMaskName = cTemp;
}

void CDlgPtzCfgCtrl::OnBtnGotoRegionalid() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iCount = 1;
	int pStatus = 0;
    char szLan[128] = {0};

	NET_DVR_PRIVACY_MASKS_COND struPrivacyMaskCond = {0};
	struPrivacyMaskCond.dwSize = sizeof(struPrivacyMaskCond);
	struPrivacyMaskCond.dwChan = m_lChannel;
	struPrivacyMaskCond.byRegionalID = m_comboRegionalID.GetCurSel()+1;

	NET_DVR_PRIVACY_MASKS_CFG struPrivacyMaskCfg = {0};

	BOOL bRet = NET_DVR_GetDeviceConfig(m_lLoginID, NET_DVR_GET_PRIVACY_MASKSCFG, iCount, &struPrivacyMaskCond, \
		sizeof(struPrivacyMaskCond), &pStatus, &struPrivacyMaskCfg, sizeof(struPrivacyMaskCfg));
	if (bRet && pStatus == 0)
	{
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PRIVACY_MASKSCFG");
    }
    else
    {
        sprintf(szLan,"err %d",pStatus);
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PRIVACY_MASKSCFG");
    }

	ShowPrivacyMasksInfo(&struPrivacyMaskCfg);

	UpdateData(FALSE);
}

void CDlgPtzCfgCtrl::OnBtnGetAllPrivacyMaskscfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iCount = MAX_PRIVACY_MASKS_REGION_NUM;
	DWORD *pStatus = new DWORD[MAX_PRIVACY_MASKS_REGION_NUM];
	memset(pStatus, 0, sizeof(DWORD)*MAX_PRIVACY_MASKS_REGION_NUM);

    char szLan[128] = {0};
	char szTemp[256] = {0};

	BOOL bRet = NET_DVR_GetDeviceConfig(m_lLoginID, NET_DVR_GET_PRIVACY_MASKSCFG, iCount, &m_struPrivacyMasksCond, \
		sizeof(NET_DVR_PRIVACY_MASKS_COND)*MAX_PRIVACY_MASKS_REGION_NUM, pStatus, &m_struPrivacyMasksCfg, \
		sizeof(NET_DVR_PRIVACY_MASKS_CFG)*MAX_PRIVACY_MASKS_REGION_NUM);
	if (bRet)
	{
		DWORD *pStatusTmp = pStatus;
		for (int i = 0; i < MAX_PRIVACY_MASKS_REGION_NUM; i++)
		{
			if (*pStatusTmp != 0)
			{
				g_StringLanType(szLan, "获取参数失败", "Get Param configuration failed");
				sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
				AfxMessageBox(szTemp);
				delete [] pStatus;
				return;
			}
			pStatusTmp++;			 
		}

        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PRIVACY_MASKSCFG");
    }
    else
    {
		delete [] pStatus;
		g_StringLanType(szLan, "获取参数失败", "Get Param configuration failed");
		sprintf(szTemp, "%s %s %d", szLan, NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());
		AfxMessageBox(szTemp);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PRIVACY_MASKSCFG");
		return;	
    }
	m_comboRegionalID.SetCurSel(0);	
	ShowPrivacyMasksInfo(&m_struPrivacyMasksCfg[0]);
	
	UpdateData(FALSE);
}

void CDlgPtzCfgCtrl::OnBtnSavesingkeRegioninfo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_dwRegionID = m_comboRegionalID.GetCurSel();
	m_struPrivacyMasksCfg[m_dwRegionID].byEnable = m_bChkSinglePrivacyMaskEnable;
	if (7 == m_comboColorType.GetCurSel())
	{
		m_struPrivacyMasksCfg[m_dwRegionID].byColorType = 0xff;
	}
	else
	{
		m_struPrivacyMasksCfg[m_dwRegionID].byColorType = m_comboColorType.GetCurSel();
	}
	
	m_struPrivacyMasksCfg[m_dwRegionID].fActiveZoomRatio = m_fActiveZoomRatio;
	m_struPrivacyMasksCfg[m_dwRegionID].byActiveZoomRatio = m_comboActiveZoomRatio.GetCurSel()+1;
	//m_struPrivacyMasksCfg[m_dwRegionID].byClearPrivacyMaskCfg = m_bChkSinglePrivacyMaskClear;
	memcpy(m_struPrivacyMasksCfg[m_dwRegionID].sPrivacyMaskName, m_csPrivacyMaskName, 16);
// 
// 	m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum = 4;
// 	m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[0].fX = 
}

void CDlgPtzCfgCtrl::OnBtnSaveAllPrivacyMaskscfg() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	char szTemp[256] = {0};

	if (m_bChkPrivacyMasksRect)
	{
		m_dwRegionID = m_comboRegionalID.GetCurSel();
		m_struPrivacyMasksCfg[m_dwRegionID].byCurrentRegionEnable = 1;
	}
	
	DWORD *pStatus = new DWORD[MAX_PRIVACY_MASKS_REGION_NUM];
	memset(pStatus, 0, sizeof(DWORD)*MAX_PRIVACY_MASKS_REGION_NUM);
	if (!NET_DVR_SetDeviceConfig(m_lLoginID, NET_DVR_SET_PRIVACY_MASKSCFG, MAX_PRIVACY_MASKS_REGION_NUM, m_struPrivacyMasksCond, \
		MAX_PRIVACY_MASKS_REGION_NUM*sizeof(NET_DVR_PRIVACY_MASKS_COND), \
		pStatus, m_struPrivacyMasksCfg, MAX_PRIVACY_MASKS_REGION_NUM*sizeof(NET_DVR_PRIVACY_MASKS_CFG)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PRIVACY_MASKSCFG");
		g_StringLanType(szLan, "设置参数失败", "Set Param configuration failed");
		sprintf(szTemp, "%s %s %d", szLan, NET_DVR_GetErrorMsg(),NET_DVR_GetLastError());
		AfxMessageBox(szTemp);
		delete [] pStatus;
		return;
	}
	else
	{
		DWORD *pStatusTmp = pStatus;
		for (int i = 0; i < MAX_PRIVACY_MASKS_REGION_NUM; i++)
		{
			
			if (*pStatusTmp != 0)
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PRIVACY_MASKSCFG");
				g_StringLanType(szLan, "设置参数失败", "Set Param configuration failed");
				sprintf(szTemp, "%s ErrCode:%d", szLan, *pStatusTmp);
				AfxMessageBox(szTemp);
				delete [] pStatus;
				return;
			}
			pStatusTmp++;
		}
	}
	delete [] pStatus;
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PRIVACY_MASKSCFG");
}

void CDlgPtzCfgCtrl::OnSelchangeComboRegionalid() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_dwRegionID = m_comboRegionalID.GetCurSel();
	ShowPrivacyMasksInfo(&m_struPrivacyMasksCfg[m_dwRegionID]);
	UpdateData(FALSE);
}

void CDlgPtzCfgCtrl::OnChkPrivacyMasksRect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_dwRegionID = m_comboRegionalID.GetCurSel();
}

void CDlgPtzCfgCtrl::OnChkPrivacyMasksRectClean() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_dwRegionID = m_comboRegionalID.GetCurSel();
	memset(&m_struPrivacyMasksCfg[m_dwRegionID].struRegion, 0, sizeof(NET_VCA_POLYGON));
}

BOOL CDlgPtzCfgCtrl::PreDrawPolygonMsg( MSG* pMsg, CPoint &pt )
{
	UpdateData(TRUE);
	int i=0;
	
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;

	if (m_bDrawRectangular)
	{
		switch(pMsg->message)  // Message of Draw
		{
		case WM_LBUTTONDOWN:
			if(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)//Press CTRL to draw
			{
				if(PtInRect(&m_rcWnd,pt))
				{				
					m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[0].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
					m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[0].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
					
					m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum = 1;
					
					m_bMouseMove = TRUE;
					m_bCloseIn = TRUE;
				}
			}
			break;
		case WM_MOUSEMOVE:
			if (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)
			{
				if (PtInRect(&m_rcWnd,pt) && m_bMouseMove)
				{
					
					m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[1].fX = m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[0].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
					m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[1].fY = m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[2].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
					
					m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[3].fX = m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[2].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
					m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[3].fY = m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[0].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
					
					m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[2].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
					m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[2].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
					
					m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum = 4;
					
				}
			}
			
			break;
			
		case WM_LBUTTONUP:
			if(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)//Press CTRL to draw
			{
				m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[1].fX = m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[0].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
				m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[1].fY = m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[2].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
				
				m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[3].fX = m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[2].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
				m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[3].fY = m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[0].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
				
				m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[2].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
				m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[2].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
				
			}
			m_bMouseMove = FALSE;
			break;
		default:
			break;
		}
	}	
	else
	{
		switch (pMsg->message)
		{
	case WM_LBUTTONDOWN:
		  if ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && 
            PtInRect(&m_rcWnd,pt))
			{
       //     if(m_bNeedRedraw)
			{
				if (m_dwPosNum > 19)
				{
					m_bCloseIn = TRUE;
				}
                if(m_bCloseIn)
                {
                    m_dwPosNum = 0;
                    m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum = m_dwPosNum;
					memset(&m_struPrivacyMasksCfg[m_dwRegionID].struRegion, 0, sizeof(NET_VCA_POLYGON));
                }
                if(m_dwPosNum > 19)
                {
                    char szLan[128] = {0};
                    g_StringLanType(szLan,"多边形顶点不能超过20个!","Apexes of polygon should less than 20");
                    AfxMessageBox(szLan);
                    return TRUE;
                }
				if((float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() <= m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() >= m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[m_dwPosNum-1].fX-0.01\
                    && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() <= m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() >= m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[m_dwPosNum-1].fY-0.01)
                {
                    char szLan[128] = {0};
                    g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
                    AfxMessageBox(szLan);
                    return TRUE;
                }
                m_bCloseIn = FALSE;
                m_bMouseMovePolygon = FALSE;
                m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                m_dwPosNum++;
                m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum = m_dwPosNum;	
            }
            
        }
        break;
    case WM_MOUSEMOVE:
        if ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && 
            PtInRect(&m_rcWnd,pt))
        {
                if(PtInRect(&m_rcWnd,pt))
                {
                    if(m_dwPosNum > 19)
                    {
                        return TRUE;
                    }
                    if( !m_bCloseIn)
                    {
                        m_bMouseMovePolygon = TRUE;
                        m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                        m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                        m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum = m_dwPosNum+1;				
                    }
                }
        }

        break;
    case WM_RBUTTONDOWN:
        if((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) 
            && PtInRect(&m_rcWnd,pt))
        {
                if(m_dwPosNum > 19)
                {
                    return TRUE;
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[i].fX != m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[i+1].fX)
                    {
                        bXOneLine = FALSE;
                        break;
                    }
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[i].fY != m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[i+1].fY)
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
                        m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum--;
                        m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum].fX = 0;
                        m_struPrivacyMasksCfg[m_dwRegionID].struRegion.struPos[m_struPrivacyMasksCfg[m_dwRegionID].struRegion.dwPointNum].fY = 0;
                    }
                    m_bCloseIn = TRUE;
                }
		}
        break;
	  }
	}

    
     return TRUE;
}


BOOL CDlgPtzCfgCtrl::PreTranslateMessage( MSG* pMsg )
{
	CPoint pt(0, 0);
	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWnd);
	GetCursorPos(&pt);
	ScreenToClient(&m_rcWnd);
	ScreenToClient(&pt);
	
	PreDrawPolygonMsg(pMsg, pt);
	
	return CDialog::PreTranslateMessage(pMsg);
}
/*
void CDlgPtzCfgCtrl::OnBtnPtzleft() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	
	PTZControlAll(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, PAN_LEFT, 0, "PAN_LEFT");
}

void CDlgPtzCfgCtrl::OnBtnPtzright() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	
	PTZControlAll(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, PAN_RIGHT, 0, "PAN_RIGHT");
}


void CDlgPtzCfgCtrl::OnBtnPtzup() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	
	PTZControlAll(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, TILT_UP, 0, "TILT_UP");
}

void CDlgPtzCfgCtrl::OnBtnPtzdown() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	
	PTZControlAll(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, TILT_DOWN, 0, "TILT_DOWN");
}
*/

CDlgPtzCfgCtrl::~CDlgPtzCfgCtrl()
{
	if (m_lPlayHandle > -1)
	{
		NET_DVR_StopRealPlay(m_lPlayHandle);
	}
}

void CDlgPtzCfgCtrl::OnBtnGetSetSingleregion() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_dwRegionID = m_comboRegionalID.GetCurSel();
	m_struPrivacyMasksCfg[m_dwRegionID].byCurrentRegionEnable = 1;
	m_struPrivacyMasksCond[m_dwRegionID].byDelPrivacyMaskCfg = 0;
	char szLan[128] = {0};
	char szTemp[256] = {0};
	int iCount = 1;
	DWORD *pStatus = new DWORD[iCount];
	memset(pStatus, 0, sizeof(DWORD)*iCount);
	if (!NET_DVR_SetDeviceConfig(m_lLoginID, NET_DVR_SET_PRIVACY_MASKSCFG, iCount, &m_struPrivacyMasksCond[m_dwRegionID], \
		iCount*sizeof(NET_DVR_PRIVACY_MASKS_COND), \
		pStatus, &m_struPrivacyMasksCfg[m_dwRegionID], iCount*sizeof(NET_DVR_PRIVACY_MASKS_CFG)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PRIVACY_MASKSCFG");
		g_StringLanType(szLan, "设置参数失败", "Set Param configuration failed");
		sprintf(szTemp, "%s %s %d", szLan, NET_DVR_GetErrorMsg(),NET_DVR_GetLastError());
		AfxMessageBox(szTemp);
		delete [] pStatus;
		return;
	}
	else
	{
		DWORD *pStatusTmp = pStatus;
		for (int i = 0; i < iCount; i++)
		{
			
			if (*pStatusTmp != 0)
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PRIVACY_MASKSCFG");
				g_StringLanType(szLan, "设置参数失败", "Set Param configuration failed");
				sprintf(szTemp, "%s ErrCode:%d", szLan, *pStatusTmp);
				AfxMessageBox(szTemp);
				delete [] pStatus;
				return;
			}
			pStatusTmp++;
		}
	}
	delete [] pStatus;
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PRIVACY_MASKSCFG");
}

void CDlgPtzCfgCtrl::OnBtnGetDetRegioncfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_dwRegionID = m_comboRegionalID.GetCurSel();
	m_struPrivacyMasksCond[m_dwRegionID].byDelPrivacyMaskCfg = 1;
	OnBtnGetSetSingleregion();
}

void CDlgPtzCfgCtrl::OnCheckFloatRatio() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_dwRegionID = m_comboRegionalID.GetCurSel();
	if (m_bChkRatioFloatEnable)
	{
		m_struPrivacyMasksCfg[m_dwRegionID].byCurZoomRatio = 1;
	}
	else
	{
		m_struPrivacyMasksCfg[m_dwRegionID].byCurZoomRatio = 0;
	}	
}
