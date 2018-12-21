// DlgPdcRuleCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPdcRuleCfg.h"
#include <math.h>
#include "DlgPdcCalibration.h"
#include "DlgPDCSearch.h"
#include "DlgVcaResetCounterCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CDlgPdcRuleCfg *g_pDlgPdcRuleCfg;
/////////////////////////////////////////////////////////////////////////////
// CDlgPdcRuleCfg dialog
void CALLBACK DrawPDCShow(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    SetBkMode(hDc, TRANSPARENT);
    SetTextColor(hDc, RGB(255, 255, 255));
    
    if (g_pDlgPdcRuleCfg != NULL)
    {
        g_pDlgPdcRuleCfg->F_DrawPdcRule(lRealHandle, hDc, dwUser);
    }
    
}

CDlgPdcRuleCfg::CDlgPdcRuleCfg(CWnd* pParent /*=NULL*/)
: CDialog(CDlgPdcRuleCfg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgPdcRuleCfg)
	m_bEnableRule = FALSE;
	m_bVcaActive = FALSE;
	m_iDvrChannel = 0;
	m_iDvrPort = 0;
	m_csPassword = _T("");
	m_iStreamPort = 0;
	m_csUserName = _T("");
	m_bStreamValid = FALSE;
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
	m_byDayStartHour = 0;
	m_byDayStartMin = 0;
	m_byDayStartSec = 0;
	m_byNightStartHour = 0;
	m_byNightStartMin = 0;
	m_byNightStartSec = 0;
	//}}AFX_DATA_INIT
    memset(&m_struPdcRuleCfg, 0, sizeof(m_struPdcRuleCfg));
    m_lServerID = -1; 
    m_iDevIndex = -1; 
    m_lPlayHandle = -1; 
    memset(&m_rcWndRect, 0, sizeof(m_rcWndRect));   
    m_bMouseMove = FALSE;
    m_bCloseIn =   FALSE;
    
    m_dwPosNum = 0;  
    m_iDrawType = -1;
    m_iVcaChan = 0;     
    m_iChannelNum = 0;   
    m_iStartChannel = -1;   
	m_iCurChannel = -1;
    memset(&m_struVcaCtrl, 0, sizeof(m_struVcaCtrl));
    memset(&m_struPUStream, 0, sizeof(m_struPUStream));
	memset(&m_struVcaDevAbility, 0, sizeof(m_struVcaDevAbility));
	m_bSupportChanEx = FALSE;
}


void CDlgPdcRuleCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgPdcRuleCfg)
	DDX_Control(pDX, IDC_COMBOCOPYTIME, m_comboCopyTime);
	DDX_Control(pDX, IDC_COMBOWEEKDAY, m_comboWeekday);
	DDX_Control(pDX, IDC_COMBO_STREAM_TRANSTYPE, m_comboStreamTransType);
	DDX_Control(pDX, IDC_COMBO_DVR_TRANS_TYPE, m_comboDvrTransType);
	DDX_Control(pDX, IDC_IPADDRESS_STREAM, m_ipStream);
	DDX_Control(pDX, IDC_IPADDRESS_DVR, m_ipDvr);
	DDX_Control(pDX, IDC_COMBO_DVR_TRANS_PROTOCOL2, m_comboDvrTransProtocol);
	DDX_Control(pDX, IDC_COMBO_VCA_TYPE, m_comboVcaType);
	DDX_Control(pDX, IDC_COMBO_STREAM, m_comboStream);
	DDX_Control(pDX, IDC_COMBO_VCA_CHAN, m_comboVcaChan);
	DDX_Check(pDX, IDC_CHK_RULE, m_bEnableRule);
	DDX_Check(pDX, IDC_CHECK_VCA_ACTIVE, m_bVcaActive);
	DDX_Text(pDX, IDC_EDIT_DVR_CHANNEL2, m_iDvrChannel);
	DDX_Text(pDX, IDC_EDIT_DVR_PORT2, m_iDvrPort);
	DDX_Text(pDX, IDC_EDIT_PASSWORD2, m_csPassword);
	DDX_Text(pDX, IDC_EDIT_STREAM_PORT, m_iStreamPort);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_csUserName);
	DDX_Check(pDX, IDC_CHECK_STREAM_VALID2, m_bStreamValid);
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
	DDX_Text(pDX, IDC_DAY_START_TIME_HOUR, m_byDayStartHour);
	DDX_Text(pDX, IDC_DAY_START_TIME_MIN, m_byDayStartMin);
	DDX_Text(pDX, IDC_DAY_START_TIME_SEC, m_byDayStartSec);
	DDX_Text(pDX, IDC_NIGHT_START_TIME_HOUR, m_byNightStartHour);
	DDX_Text(pDX, IDC_NIGHT_START_TIME_MIN, m_byNightStartMin);
	DDX_Text(pDX, IDC_NIGHT_START_TIME_SEC, m_byNightStartSec);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPdcRuleCfg, CDialog)
    //{{AFX_MSG_MAP(CDlgPdcRuleCfg)
    ON_BN_CLICKED(IDC_BTN_PDC_RULECFG, OnBtnPdcRulecfg)
    ON_BN_CLICKED(IDC_RADIO_DRAW_POLYGON, OnRadioDrawPolygon)
    ON_BN_CLICKED(IDC_RADIO_DRAW_DIRECTION, OnRadioDrawDirection)
    ON_BN_CLICKED(IDC_BTN_CALIBRATION, OnBtnCalibration)
    ON_CBN_SELCHANGE(IDC_COMBO_VCA_CHAN, OnSelchangeComboVcaChan)
    ON_BN_CLICKED(ID_BTN_SET_VCA_CTRL, OnBtnSetVcaCtrl)
    ON_BN_CLICKED(IDC_BTN_SET_PU_STREAM, OnBtnSetPuStream)
    ON_BN_CLICKED(IDC_BTN_PDC_QUERY, OnBtnPdcQuery)
	ON_BN_CLICKED(IDC_BTN_RESET_COUNTE, OnBtnResetCounte)
	ON_BN_CLICKED(IDC_TIME_OK2, OnTimeOk2)
	ON_BN_CLICKED(IDC_TIME_COPY2, OnTimeCopy2)
	ON_CBN_SELCHANGE(IDC_COMBOWEEKDAY, OnSelchangeComboweekday)
	ON_BN_CLICKED(IDC_BTN_ADV_RESET_COUNTE, OnBtnAdvResetCounte)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPdcRuleCfg message handlers

BOOL CDlgPdcRuleCfg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    g_pDlgPdcRuleCfg = this;
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWndRect);
    m_bCloseIn = TRUE;

//    m_iVcaChan = m_iStartChannel + 0;
	char sbuf[128];
    m_comboVcaChan.ResetContent();
	for (int i = 0; i < m_iChannelNum; i++)
    {
        sprintf(sbuf, "VCA Chan%d", i+m_iStartChannel);
        m_comboVcaChan.InsertString(i,sbuf);
    }
//	m_comboVcaChan.SetCurSel(m_iVcaChan - m_iStartChannel);

	char szLan[128] = {0};
	
	memset(&m_struVcaDevAbility, 0, sizeof(NET_VCA_DEV_ABILITY));
	if(!NET_DVR_GetDeviceAbility(g_struDeviceInfo[m_iDevIndex].lLoginID,  VCA_DEV_ABILITY, NULL, 0, (char*)&m_struVcaDevAbility, sizeof(NET_VCA_DEV_ABILITY)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "VCA_DEV_ABILITY");
		g_StringLanType(szLan, "获取智能设备能力失败", "Device does not support");
		AfxMessageBox(szLan);
		return FALSE;
	}
	else 
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "VCA_DEV_ABILITY");
    }
	
	m_bSupportChanEx = (m_struVcaDevAbility.bySupport>>1)&1;

	switch (g_struDeviceInfo[m_iDevIndex].iDeviceType)
    {
	case IVMS_6200_C:
        m_comboVcaChan.SetCurSel(m_iCurChannel/*+m_iStartChannel*/);
		GetDlgItem(IDC_COMBO_VCA_CHAN)->EnableWindow(FALSE);
//		m_iVcaChan = m_iCurChannel+m_iStartChannel;
		break;
	default:
		m_comboVcaChan.SetCurSel(m_iVcaChan - m_iStartChannel);
		GetDlgItem(IDC_COMBO_VCA_CHAN)->EnableWindow(TRUE);
		break;
    }

    GetPdcRuleWnd();
    GetCtrlWnd();
	if (m_bSupportChanEx)
	{
	}
	else
	{
		GetPUStreamWnd();
	}
    
    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPdcRuleCfg::GetCtrlWnd() 
{
    m_bVcaActive = m_struVcaCtrl.struCtrlInfo[m_iVcaChan-1].byVCAEnable;
    m_comboVcaType.SetCurSel(0);
	m_comboStream.SetCurSel(m_struVcaCtrl.struCtrlInfo[m_iVcaChan-1].byStreamWithVCA);

}
void CDlgPdcRuleCfg::GetPdcRuleWnd()
{
    char szLan[128] = {0};
    DWORD dwReturn;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PDC_RULECFG_V41, m_iVcaChan, &m_struPdcRuleCfg, sizeof(m_struPdcRuleCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PDC_RULECFG_V41 Fail");
        g_StringLanType(szLan, "获取PDC配置失败", "Fail to get PDC rule config");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PDC_RULECFG_V41 Success");
    }
    if (m_lPlayHandle >= 0)
    {
        StopRealPlay();
    }
    StartRealPlay();
    
    m_bEnableRule = m_struPdcRuleCfg.byEnable;
    m_byDayStartHour = m_struPdcRuleCfg.struDayStartTime.byHour;
	m_byDayStartMin = m_struPdcRuleCfg.struDayStartTime.byMinute;
	m_byDayStartSec = m_struPdcRuleCfg.struDayStartTime.bySecond;
	m_byNightStartHour = m_struPdcRuleCfg.struNightStartTime.byHour;
	m_byNightStartMin = m_struPdcRuleCfg.struNightStartTime.byMinute;
	m_byNightStartSec = m_struPdcRuleCfg.struNightStartTime.bySecond;
	int nDay = 0;
	m_comboWeekday.SetCurSel(0);
	SetAlarmTimeToWnd(&m_struPdcRuleCfg.struAlarmTime[0][0], nDay);
    
    UpdateData(FALSE);

}
void CDlgPdcRuleCfg::GetPUStreamWnd()
{
 
    DWORD dwReturn = 0;
    char szLan[128] = {0};
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PU_STREAMCFG, m_iVcaChan, &m_struPUStream, sizeof(m_struPUStream), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PU_STREAMCFG fail");
        g_StringLanType(szLan, "获取前端取流设备信息失败", "Fail to get PU stream config");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PU_STREAMCFG Succ");
    }
        //Channel info
        DWORD ipDvr = CStringTodwIP(m_struPUStream.struDevChanInfo.struIP.sIpV4);
        m_ipDvr.SetAddress(ipDvr);
        m_iDvrPort = m_struPUStream.struDevChanInfo.wDVRPort;
        m_iDvrChannel = m_struPUStream.struDevChanInfo.byChannel;
        m_comboDvrTransType.SetCurSel(m_struPUStream.struDevChanInfo.byTransMode);
        m_comboDvrTransProtocol.SetCurSel(m_struPUStream.struDevChanInfo.byTransProtocol);
        m_csUserName = m_struPUStream.struDevChanInfo.sUserName;
        m_csPassword = m_struPUStream.struDevChanInfo.sPassword;
        
        //Stream server config
        m_bStreamValid = m_struPUStream.struStreamMediaSvrCfg.byValid;
       // EnableStream(m_bStreamValid);
        DWORD ipStream = CStringTodwIP(m_struPUStream.struStreamMediaSvrCfg.struDevIP.sIpV4);
        m_ipStream.SetAddress(ipStream);
        m_iStreamPort = m_struPUStream.struStreamMediaSvrCfg.wDevPort;
        m_comboStreamTransType.SetCurSel(m_struPUStream.struStreamMediaSvrCfg.byTransmitType);

}
BOOL CDlgPdcRuleCfg::PreTranslateMessage(MSG* pMsg) 
{
    // TODO: Add your specialized code here and/or call the base class
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
                            m_struPdcRuleCfg.struPolygon.dwPointNum = m_dwPosNum;		
                        }
                        if(m_dwPosNum>9)
                        {
                            char szLan[128] = {0};
                            g_StringLanType(szLan,"人数统计规则为4边形","Polygon vertex can not be over 4!");
                            AfxMessageBox(szLan);
                            return TRUE;
                        }
                        if((float)(pt.x-rcWnd.left)/(float)rcWnd.Width() <= m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() >= m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum-1].fX-0.01\
                            && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() <= m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() >= m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum-1].fY-0.01)
                        {
                            char szLan[128] = {0};
                            g_StringLanType(szLan, "不能连续在同一点上画区域", "Region can not be painted in the same point");
                            AfxMessageBox(szLan);
                            return TRUE;
                        }
                        m_bCloseIn = FALSE;
                        m_bMouseMove = FALSE;
                        m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
                        m_dwPosNum++;
                        m_struPdcRuleCfg.struPolygon.dwPointNum = m_dwPosNum;			
                }
                
            }
            else if (m_iDrawType == 2)
            {
                if(PtInRect(&rcWnd,pt))
                {		
                    if(!m_bMouseMove)
                    {
                        m_struPdcRuleCfg.struEnterDirection.struStartPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struEnterDirection.struStartPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();		
                        m_struPdcRuleCfg.struEnterDirection.struEndPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struEnterDirection.struEndPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
                        m_bMouseMove = TRUE;
                    }
                    else
                    {
                        if ((float)(pt.x-rcWnd.left)/(float)rcWnd.Width() <= m_struPdcRuleCfg.struEnterDirection.struStartPoint.fX+0.01 && (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() >= m_struPdcRuleCfg.struEnterDirection.struStartPoint.fX-0.01\
                            && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() <= m_struPdcRuleCfg.struEnterDirection.struStartPoint.fY+0.01 && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() >= m_struPdcRuleCfg.struEnterDirection.struStartPoint.fY-0.01)
                        {
                            char szLan[128] = {0};
                            g_StringLanType(szLan, "不能连续在同一点上画区域", "Region can not be painted in the same point");
                            AfxMessageBox(szLan);
                            return TRUE;
                        }
                        m_struPdcRuleCfg.struEnterDirection.struEndPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struEnterDirection.struEndPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
                        m_bMouseMove = FALSE;
                    }
				}
            }
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
                        m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
                        m_struPdcRuleCfg.struPolygon.dwPointNum = m_dwPosNum+1;				
                    }
                }
            }
            else if (m_iDrawType == 2)
            {
                if(PtInRect(&rcWnd,pt))
                {
                    if(m_bMouseMove)
                    {
                        m_struPdcRuleCfg.struEnterDirection.struEndPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struEnterDirection.struEndPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
                    }
                }

            }
        }
        break;
    case WM_LBUTTONUP:
        if((m_iDrawType == 1 )&&(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
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
                    if(m_struPdcRuleCfg.struPolygon.struPos[i].fX != m_struPdcRuleCfg.struPolygon.struPos[i+1].fX)
                    {
                        bXOneLine = FALSE;
                        break;
                    }
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struPdcRuleCfg.struPolygon.struPos[i].fY != m_struPdcRuleCfg.struPolygon.struPos[i+1].fY)
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
                        m_struPdcRuleCfg.struPolygon.dwPointNum--;
                        m_struPdcRuleCfg.struPolygon.struPos[m_struPdcRuleCfg.struPolygon.dwPointNum].fX = 0;
                        m_struPdcRuleCfg.struPolygon.struPos[m_struPdcRuleCfg.struPolygon.dwPointNum].fY = 0;
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
                    m_struPdcRuleCfg.struPolygon.dwPointNum--;
                    m_dwPosNum--;
                    m_struPdcRuleCfg.struPolygon.struPos[m_struPdcRuleCfg.struPolygon.dwPointNum].fX = 0;
                    m_struPdcRuleCfg.struPolygon.struPos[m_struPdcRuleCfg.struPolygon.dwPointNum].fY = 0;
                }
                else if( m_bCloseIn)
                {
                    m_struPdcRuleCfg.struPolygon.dwPointNum = 0;
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

void CDlgPdcRuleCfg::OnBtnPdcRulecfg() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_struPdcRuleCfg.byEnable = m_bEnableRule;
	m_struPdcRuleCfg.struDayStartTime.byHour = m_byDayStartHour;
	m_struPdcRuleCfg.struDayStartTime.byMinute = m_byDayStartMin;
	m_struPdcRuleCfg.struDayStartTime.bySecond = m_byDayStartSec;
	m_struPdcRuleCfg.struNightStartTime.byHour = m_byNightStartHour;
	m_struPdcRuleCfg.struNightStartTime.byMinute = m_byNightStartMin;
	m_struPdcRuleCfg.struNightStartTime.bySecond = m_byNightStartSec;
    char szLan[128] = {0};
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_PDC_RULECFG_V41, m_iVcaChan, &m_struPdcRuleCfg, sizeof(m_struPdcRuleCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PDC_RULECFG_V41");
        g_StringLanType(szLan, "设置PDC配置失败", "Fail to set PDC rule config");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PDC_RULECFG_V41");
    }
}

void CDlgPdcRuleCfg::PostNcDestroy() 
{
    // TODO: Add your specialized code here and/or call the base class
    StopRealPlay();
    CDialog::PostNcDestroy();
}

long CDlgPdcRuleCfg::StartRealPlay()
{
    NET_DVR_CLIENTINFO struClientInfo;
    memset(&struClientInfo, 0, sizeof(NET_DVR_CLIENTINFO));
    struClientInfo.lChannel = m_iVcaChan;
    struClientInfo.hPlayWnd = GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
    m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struClientInfo, NULL, NULL, TRUE); 
    if (m_lPlayHandle == -1) 
    {
        AfxMessageBox("Fail to Preview");
        return m_lPlayHandle;
    }
    else
    {
        if (!NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawPDCShow, 0)) 
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RigisterDrawFun Fail");
            AfxMessageBox("Fail to set DrawFun callback");
        }
        
    }
    return m_lPlayHandle;
}

BOOL CDlgPdcRuleCfg::StopRealPlay()
{
    BOOL bRet;
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

void CDlgPdcRuleCfg::F_DrawPdcRule(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    F_DrawFrame(lRealHandle, hDc, dwUser,  RGB(255, 255, 0));
    PDCDrawDirection(hDc, dwUser);
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
void CDlgPdcRuleCfg::F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser,  COLORREF color)
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
    MoveToEx(hDc, (int)(m_struPdcRuleCfg.struPolygon.struPos[0].fX*m_rcWndRect.Width()), \
        (int)(m_struPdcRuleCfg.struPolygon.struPos[0].fY*m_rcWndRect.Height()), NULL);
    
    for(i=1; i<m_struPdcRuleCfg.struPolygon.dwPointNum; i++)
    {
        
        LineTo(hDc, (int)(m_struPdcRuleCfg.struPolygon.struPos[i].fX*m_rcWndRect.Width()),\
            (int)(m_struPdcRuleCfg.struPolygon.struPos[i].fY*m_rcWndRect.Height()));
        //if cross, redraw
        if(i>=MIN_PNT_NUM && !m_bMouseMove && IsCrossLine(&m_struPdcRuleCfg.struPolygon))
        {
            char szLan[128] = {0};
            g_StringLanType(szLan,"多边形不相邻的边有相交情况存在,请重新输入!","Polygon edges are not adjacent is intersect");
            AfxMessageBox(szLan);
            m_dwPosNum--;
            m_struPdcRuleCfg.struPolygon.dwPointNum--;
            break;
        }

    }
    
    for (i=0; i<(int)m_struPdcRuleCfg.struPolygon.dwPointNum ; i++)
    {
        if (i == VCA_MAX_POLYGON_POINT_NUM)
        {
            break;
        }
        
        point[i].x = (int)(m_struPdcRuleCfg.struPolygon.struPos[i].fX*m_rcWndRect.Width());
        point[i].y = (int)(m_struPdcRuleCfg.struPolygon.struPos[i].fY*m_rcWndRect.Height());
    }
    
    if(VCA_MAX_POLYGON_POINT_NUM == i && !m_bMouseMove)
    {
        if (IsValidArea(&m_struPdcRuleCfg.struPolygon))
        {
            graphics.FillPolygon(&brush, (Point *)point, m_struPdcRuleCfg.struPolygon.dwPointNum);
            
            LineTo(hDc, (int)(m_struPdcRuleCfg.struPolygon.struPos[0].fX*m_rcWndRect.Width()), (int)(m_struPdcRuleCfg.struPolygon.struPos[0].fY*m_rcWndRect.Height()));	
            m_bCloseIn = TRUE;
        }else
        {
            m_bCloseIn = FALSE;
            m_struPdcRuleCfg.struPolygon.dwPointNum--;
            m_dwPosNum--;
        }
    }
    else if(m_struPdcRuleCfg.struPolygon.dwPointNum>2 && m_bCloseIn)
    {
        if (IsValidArea(&m_struPdcRuleCfg.struPolygon))
        {
            graphics.FillPolygon(&brush, (Point *)point, m_struPdcRuleCfg.struPolygon.dwPointNum);
            
            LineTo(hDc, (int)(m_struPdcRuleCfg.struPolygon.struPos[0].fX*m_rcWndRect.Width()),(int)(m_struPdcRuleCfg.struPolygon.struPos[0].fY*m_rcWndRect.Height()));
        }else
        {
            m_bCloseIn = FALSE;
        }
    }
    
    SelectObject(hDc, pOldPen);
    DeleteObject(DrawPen);
}

BOOL CDlgPdcRuleCfg::IsCrossLine(NET_VCA_POLYGON *alarm_region)
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

BOOL CDlgPdcRuleCfg::F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2)
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

BOOL CDlgPdcRuleCfg::IsValidArea(NET_VCA_POLYGON *alarm_region)
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

BOOL CDlgPdcRuleCfg::F_IsACrossLine(NET_VCA_POLYGON *alarm_region) // 
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

BOOL CDlgPdcRuleCfg::F_IsStraightLine(NET_VCA_POLYGON *alarm_region)  
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

void CDlgPdcRuleCfg::PDCDrawDirection(HDC hDc, DWORD dwUser)
{
    CPen cpDrawPen;
    
    int x1 = (int)(m_struPdcRuleCfg.struEnterDirection.struStartPoint.fX*m_rcWndRect.Width());
    int y1 = (int)(m_struPdcRuleCfg.struEnterDirection.struStartPoint.fY*m_rcWndRect.Height());
    
    int x2 = (int)(m_struPdcRuleCfg.struEnterDirection.struEndPoint.fX*m_rcWndRect.Width());
    int y2 = (int)(m_struPdcRuleCfg.struEnterDirection.struEndPoint.fY*m_rcWndRect.Height());
    
    if ((x1 == x2) && (y1 == y2))
    {
        return;
    }
    
    using namespace Gdiplus;
    Graphics graphics(hDc);
    
    Color color(80, 0, 0, 0);
    
    Pen pen(color, 7);
    
    pen.SetStartCap(LineCapFlat);
    
    Point pt1 = Point(0, -1);
    Point pt2 = Point(2, -1);
    Point pt3 = Point(0, 4);
    Point pt4 = Point(-2, -1);
    GraphicsPath fillPath;
    fillPath.AddLine(pt1, pt2);
    fillPath.AddLine(pt2, pt3);
    fillPath.AddLine(pt3, pt4);
    CustomLineCap custCap(&fillPath, NULL);
    pen.SetCustomEndCap(&custCap);
    cpDrawPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    color.SetValue(color.MakeARGB(100, 0, 255, 255));
    SetTextColor(hDc,RGB(225, 225, 225));
    
    int k = 0;
    
    if(x2 != x1)
        k = (y2 - y1) / (x2 - x1);
    
    pen.SetColor(color);
    
    if(k < 0)
        graphics.DrawLine(&pen, x1-2, y1-1, x2-2, y2-1);
    else
        graphics.DrawLine(&pen, x1+2, y1-1, x2+2, y2-1);
    
    HGDIOBJ cpOldPen = SelectObject(hDc, cpDrawPen);
    
    cpDrawPen.DeleteObject();
    SelectObject(hDc, cpOldPen);
    
    graphics.ReleaseHDC(hDc);
}

void CDlgPdcRuleCfg::OnRadioDrawPolygon() 
{
    // TODO: Add your control notification handler code here
    m_iDrawType = 1; 
    
}

void CDlgPdcRuleCfg::OnRadioDrawDirection() 
{
    // TODO: Add your control notification handler code here
	m_iDrawType = 2; 
}

void CDlgPdcRuleCfg::OnBtnCalibration() 
{
	// TODO: Add your control notification handler code here
    CDlgPdcCalibration dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel =    m_iVcaChan;
    dlg.m_lPlayHandle = m_lPlayHandle;
    dlg.DoModal();
}

void CDlgPdcRuleCfg::OnSelchangeComboVcaChan() 
{
	// TODO: Add your control notification handler code here
//	m_iVcaChan = m_comboVcaChan.GetCurSel() + m_iStartChannel;
   GetPdcRuleWnd();
   GetCtrlWnd();
   GetPUStreamWnd();
   UpdateData(FALSE);
}

void CDlgPdcRuleCfg::OnBtnSetVcaCtrl() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[128] = {0};
    char szCn[128] = {0};
    char szEn[128] = {0};
	DWORD dwStatus = 0xffffffff;
	if (m_bSupportChanEx)
	{
		NET_DVR_VCA_CTRLINFO_COND struCond = {0};
		struCond.dwSize = sizeof(struCond);
		struCond.struStreamInfo.dwChannel = m_iVcaChan;
		m_struVcaCtrlInfo.byVCAEnable = (unsigned char)m_bVcaActive;
		m_struVcaCtrlInfo.byVCAType = 6;
		m_struVcaCtrlInfo.byStreamWithVCA = (unsigned char)m_comboStream.GetCurSel();
		//m_struVcaCtrlInfo.byControlType
		BOOL bRet = NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_VCA_CTRLINFO_CFG, 1, &struCond,sizeof(struCond),&dwStatus, &m_struVcaCtrlInfo, sizeof(m_struVcaCtrlInfo));
		
		if (!(bRet && (0 == dwStatus)))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VCA_CTRLINFO_CFG");            
			bRet = FALSE;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VCA_CTRLINFO_CFG");            
			bRet = TRUE;
		}
	}
	else
	{
		m_struVcaCtrl.struCtrlInfo[m_iVcaChan-m_iStartChannel].byVCAEnable = (unsigned char)m_bVcaActive;
		m_struVcaCtrl.struCtrlInfo[m_iVcaChan-m_iStartChannel].byVCAType = 6;  // 目前只有6  该部分最好改动，改为动态增加和之前的智能行为做的一样
		m_struVcaCtrl.struCtrlInfo[m_iVcaChan-m_iStartChannel].byStreamWithVCA = (unsigned char)m_comboStream.GetCurSel();
		if(!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_VCA_CTRLCFG, 0 , &m_struVcaCtrl, sizeof(NET_VCA_CTRLCFG)))
		{	
			sprintf(szCn, "设置智能通道%d失败", m_iVcaChan);
			sprintf(szEn, "Fail to set vca channel%d", m_iVcaChan);
			g_StringLanType(szLan, szCn, szEn);
			AfxMessageBox(szLan);
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VCA_CTRLCFG");
		}
		else
		{
			sprintf(szCn, "设置智能通道%d成功", m_iVcaChan);
			sprintf(szCn, "Succ to set vca channel%d", m_iVcaChan);
			g_StringLanType(szLan, szCn, szEn);
			AfxMessageBox(szLan);
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VCA_CTRLCFG");
		}
	}
    
}

void CDlgPdcRuleCfg::OnBtnSetPuStream() 
{
	// TODO: Add your control notification handler code here
    SetPUStreamCfg();
}

void CDlgPdcRuleCfg::SetPUStreamCfg()
{
    UpdateData(TRUE);
   
    DWORD ipDvr = 0;
    m_ipDvr.GetAddress(ipDvr);
    CString csTemp;
    csTemp = IPToStr(ipDvr);
    sprintf(m_struPUStream.struDevChanInfo.struIP.sIpV4, "%s", csTemp.GetBuffer(0));
    
    m_struPUStream.struDevChanInfo.wDVRPort = (WORD)m_iDvrPort;
    m_struPUStream.struDevChanInfo.byChannel = (BYTE)m_iDvrChannel;
    m_struPUStream.struDevChanInfo.byTransProtocol = (BYTE)m_comboDvrTransProtocol.GetCurSel();
    m_struPUStream.struDevChanInfo.byTransMode = (BYTE)m_comboDvrTransType.GetCurSel();
    memset(m_struPUStream.struDevChanInfo.sUserName, 0, NAME_LEN*sizeof(BYTE));
    strncpy((char*)m_struPUStream.struDevChanInfo.sUserName, (char*)m_csUserName.GetBuffer(0), NAME_LEN-1);
    memset(m_struPUStream.struDevChanInfo.sPassword, 0, PASSWD_LEN*sizeof(BYTE));
    strncpy((char*)m_struPUStream.struDevChanInfo.sPassword, (char*)m_csPassword.GetBuffer(0), PASSWD_LEN-1);
    
    m_struPUStream.struStreamMediaSvrCfg.byValid = m_bStreamValid;
    
    DWORD ipStream = 0;
    m_ipStream.GetAddress(ipStream);
    csTemp = IPToStr(ipStream);
    sprintf(m_struPUStream.struStreamMediaSvrCfg.struDevIP.sIpV4, "%s", csTemp.GetBuffer(0));
    
    m_struPUStream.struStreamMediaSvrCfg.wDevPort = (WORD)m_iStreamPort;
    m_struPUStream.struStreamMediaSvrCfg.byTransmitType = m_comboStreamTransType.GetCurSel();
    

    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_PU_STREAMCFG, m_iVcaChan, &m_struPUStream, sizeof(m_struPUStream)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PU_STREAMCFG fail");
        AfxMessageBox("Fail to set PU stream config");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PU_STREAMCFG Succ");
    }

}

void CDlgPdcRuleCfg::OnBtnPdcQuery() 
{
	// TODO: Add your control notification handler code here
    CDlgPDCSearch dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_iVcaChan;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();

}

void CDlgPdcRuleCfg::OnBtnResetCounte() 
{
	// TODO: Add your control notification handler code here
	if (!NET_DVR_ResetCounter(m_lServerID, m_iVcaChan))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_ResetCounter");
        AfxMessageBox("Fail to reset counter");
	} 
	else
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_ResetCounter");
	}
}

/*********************************************************
Function:	F_TimeTest
Desc:		Check Fortify time
Input:	
Output:	
Return:	BOOL
**********************************************************/
BOOL CDlgPdcRuleCfg::F_TimeTest()
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

void CDlgPdcRuleCfg::SetAlarmTimeToWnd(NET_DVR_SCHEDTIME const *pAlarmTime, int nDay)
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

void CDlgPdcRuleCfg::GetAlarmTimeFromWnd(NET_DVR_SCHEDTIME *pAlarmTime, int nDay)
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
// 
// void CDlgPdcRuleCfg::OnSelchangeCombocopytime() 
// {
// 	// TODO: Add your control notification handler code here
// 	int	i = m_comboWeekday.GetCurSel();	
//     SetAlarmTimeToWnd(&m_struPdcRuleCfg.struAlarmTime[0][0], i);
//     UpdateData(FALSE);
// }

void CDlgPdcRuleCfg::OnTimeOk2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    if (!F_TimeTest())
    {
        return;
    }
    int	i = m_comboWeekday.GetCurSel();	
    GetAlarmTimeFromWnd(&m_struPdcRuleCfg.struAlarmTime[0][0], i);
}

void CDlgPdcRuleCfg::OnTimeCopy2() 
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
                memcpy(&(m_struPdcRuleCfg.struAlarmTime[j][k]), &(m_struPdcRuleCfg.struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
            }
        }
    }
    else
    {
        for(k=0; k<MAX_TIMESEGMENT_V30/*MAX_TIMESEGMENT_2*/; k++)
        {
            memcpy(&(m_struPdcRuleCfg.struAlarmTime[m_nCopyTime][k]), &(m_struPdcRuleCfg.struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
        }
    }
}

void CDlgPdcRuleCfg::OnSelchangeComboweekday() 
{
	// TODO: Add your control notification handler code here
	int	i = m_comboWeekday.GetCurSel();	
    SetAlarmTimeToWnd(&m_struPdcRuleCfg.struAlarmTime[0][0], i);
    UpdateData(FALSE);
}

void CDlgPdcRuleCfg::OnBtnAdvResetCounte() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaResetCounterCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
	dlg.m_iVcaChan = m_iVcaChan;
    dlg.DoModal();
}
