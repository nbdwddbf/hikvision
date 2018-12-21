// DlgVcaAtmFace.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaAtmFace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaAtmFace dialog

CDlgVcaAtmFace *g_pDlgVcaAtmFace = NULL;

void CALLBACK DrawDetectRule(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    SetBkMode(hDc, TRANSPARENT);
    SetTextColor(hDc, RGB(255, 255, 255));
    
    if (g_pDlgVcaAtmFace != NULL)
    {
        g_pDlgVcaAtmFace->F_DrawDetectRule(lRealHandle, hDc, dwUser);
    }
    
}

CDlgVcaAtmFace::CDlgVcaAtmFace(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaAtmFace::IDD, pParent)
{
    
	//{{AFX_DATA_INIT(CDlgVcaAtmFace)
    m_iHour11 = 0;
    m_iHour12 = 0;
    m_iHour21 = 0;
    m_iHour22 = 0;
    m_iMin11 = 0;
    m_iMin12 = 0;
    m_iMin21 = 0;
	m_iMin22 = 0;
    m_bHandleType1 = FALSE;
    m_bHandleType2 = FALSE;
    m_bHandleType3 = FALSE;
    m_bHandleType4 = FALSE;
    m_bVcaEnable1 = FALSE;
	m_bHandleType5 = FALSE;
    m_bVcaEnable2 = FALSE;
    m_bVcaEnable3 = FALSE;
    m_bVcaEnable4 = FALSE;
	//}}AFX_DATA_INIT
    m_lServerID = -1;            
    m_iDevIndex = -1;           
    m_iStartChannel = -1;       
    m_iChannelNum   = -1;         
    memset(&m_struVcaCtrl, 0, sizeof(m_struVcaCtrl)); 
    
    m_lPlayHandle = -1; 
    
    memset(&m_struDetectRule, 0, sizeof(m_struDetectRule)); 

    m_lChannel = -1;      

    memset(&m_struAlarmTime, 0, sizeof(m_struAlarmTime));

    m_lDetectChannel = -1; 
   
    m_bMouseMove = FALSE;  
    m_bMaxRectNum = FALSE;
}


void CDlgVcaAtmFace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaAtmFace)
	DDX_Control(pDX, IDC_COMBO_DETECT_TYPE, m_comboDetectType);
	DDX_Control(pDX, IDC_COMBO_ATM_CHAN_MODE1, m_comboAtmChanMode1);
    DDX_Control(pDX, IDC_COMBO_ATM_CHAN_MODE2, m_comboAtmChanMode2);
    DDX_Control(pDX, IDC_COMBO_ATM_CHAN_MODE3, m_comboAtmChanMode3);
    DDX_Control(pDX, IDC_COMBO_ATM_CHAN_MODE4, m_comboAtmChanMode4);
	DDX_Control(pDX, IDC_COMBO_VCA_STREAM1, m_comboVcaStream1);
    DDX_Control(pDX, IDC_COMBO_VCA_STREAM2, m_comboVcaStream2);
    DDX_Control(pDX, IDC_COMBO_VCA_STREAM3, m_comboVcaStream3);
    DDX_Control(pDX, IDC_COMBO_VCA_STREAM4, m_comboVcaStream4);
	DDX_Control(pDX, IDC_COMBO_CHAN_TYPE1, m_comboChanType1);
    DDX_Control(pDX, IDC_COMBO_CHAN_TYPE2, m_comboChanType2);
    DDX_Control(pDX, IDC_COMBO_CHAN_TYPE3, m_comboChanType3);
    DDX_Control(pDX, IDC_COMBO_CHAN_TYPE4, m_comboChanType4);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_comboResolution);
    DDX_Control(pDX, IDC_COMBO_PRO_PIC_TYPE, m_comboProPicType);
	DDX_Control(pDX, IDC_COMBO_PIC_QUALITY, m_comboPicQuality);
    DDX_Text(pDX, IDC_EDITHOUR11, m_iHour11);
    DDX_Text(pDX, IDC_EDITHOUR12, m_iHour12);
    DDX_Text(pDX, IDC_EDITHOUR21, m_iHour21);
    DDX_Text(pDX, IDC_EDITHOUR22, m_iHour22);
    DDX_Text(pDX, IDC_EDITMIN11, m_iMin11);
    DDX_Text(pDX, IDC_EDITMIN12, m_iMin12);
    DDX_Text(pDX, IDC_EDITMIN21, m_iMin21);
	DDX_Text(pDX, IDC_EDITMIN22, m_iMin22);
    DDX_Control(pDX, IDC_COMBOWEEKDAY, m_comboWeekday);
    DDX_Control(pDX, IDC_COMBOCOPYTIME, m_comboCopyTime);
    DDX_Check(pDX, IDC_CHECKHANDLETYPE1, m_bHandleType1);
    DDX_Check(pDX, IDC_CHECKHANDLETYPE2, m_bHandleType2);
    DDX_Check(pDX, IDC_CHECKHANDLETYPE3, m_bHandleType3);
    DDX_Check(pDX, IDC_CHECKHANDLETYPE4, m_bHandleType4);
	DDX_Check(pDX, IDC_CHECKHANDLETYPE5, m_bHandleType5);
    DDX_Control(pDX, IDC_LIST_RECORD_CHAN, m_listRecordChan);
	DDX_Control(pDX, IDC_LIST_ALARM_OUT, m_listAlarmOut);
	DDX_Check(pDX, IDC_CHK_VCA_CTRL1, m_bVcaEnable1);
    DDX_Check(pDX, IDC_CHK_VCA_CTRL2, m_bVcaEnable2);
    DDX_Check(pDX, IDC_CHK_VCA_CTRL3, m_bVcaEnable3);
    DDX_Check(pDX, IDC_CHK_VCA_CTRL4, m_bVcaEnable4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaAtmFace, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaAtmFace)
	ON_BN_CLICKED(IDC_BTN_SET_DETECT_RULE, OnBtnSetDetectRule)
	ON_BN_CLICKED(IDC_TIME_OK, OnTimeOk)
	ON_BN_CLICKED(IDC_TIME_COPY, OnTimeCopy)
    ON_BN_CLICKED(IDC_CHECKHANDLETYPE4, OnCheckhandletype4)
	ON_BN_CLICKED(IDC_CHK_VCA_CTRL1, OnChkVcaCtrl1)
	ON_BN_CLICKED(IDC_CHK_VCA_CTRL2, OnChkVcaCtrl2)
	ON_BN_CLICKED(IDC_CHK_VCA_CTRL3, OnChkVcaCtrl3)
	ON_BN_CLICKED(IDC_CHK_VCA_CTRL4, OnChkVcaCtrl4)
	ON_BN_CLICKED(IDC_BTN_SET_CTRLCFG, OnBtnSetCtrlcfg)
	ON_BN_CLICKED(IDC_BTN_GET_CTRLCFG, OnBtnGetCtrlcfg)
	ON_CBN_SELCHANGE(IDC_COMBO_DETECT_TYPE, OnSelchangeComboDetectType)
	ON_CBN_SELCHANGE(IDC_COMBOWEEKDAY, OnSelchangeComboweekday)
	ON_CBN_SELCHANGE(IDC_COMBOCOPYTIME, OnSelchangeCombocopytime)
	ON_WM_RBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaAtmFace message handlers

void CDlgVcaAtmFace::OnBtnSetDetectRule() 
{
	UpdateData(TRUE);
    
    m_struDetectRule.struAlarmJpeg.byPicProType = (unsigned char)m_comboProPicType.GetCurSel();
    m_struDetectRule.struAlarmJpeg.struPicParam.wPicSize = (unsigned short)m_comboResolution.GetCurSel();
	m_struDetectRule.struAlarmJpeg.struPicParam.wPicQuality = (unsigned short)m_comboPicQuality.GetCurSel();
    
    SetAlarmPara(m_struDetectRule.struHandleType);
    
    SetAlarmTimePara();
    memcpy(&m_struDetectRule.struAlarmTime, &m_struAlarmTime, sizeof(m_struAlarmTime));

    SetRelRecordChan(m_struDetectRule, m_iChannelNum);
    
    memcpy(&m_struDetectRule.struDetectRectList, &m_struDetectRectList, sizeof(m_struDetectRectList));

    SetDetectRule(); 
    
}

// void CDlgVcaAtmFace::SetDetectRectList()
// {
//     memcpy(&m_struDetectRule.struDetectRectList, &m_struDetectRectList, sizeof(m_struDetectRectList));
// }

void CDlgVcaAtmFace::SetRelRecordChan(NET_DVR_DETECT_RULECFG &struDetectRule, int nChanNum)
{
    for (int i = 0; i < nChanNum; i++)
    {
        struDetectRule.byRelRecordChan[i] = (BYTE)m_listRecordChan.GetCheck(i);
    }
}

BOOL CDlgVcaAtmFace::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWndRect); 

    g_pDlgVcaAtmFace = this;
	
    m_dwAlarmOutNum = g_struDeviceInfo[m_iDevIndex].iAlarmOutNum;

    GetVcaCtrlShow(m_struVcaCtrl);

    for (int i = 0; i < 4; i++)
    {
        if (5 == m_struVcaCtrl.struCtrlInfo[i].byVCAType && 0 == m_struVcaCtrl.struCtrlInfo[i].byMode && m_struVcaCtrl.struCtrlInfo[i].byVCAEnable)
        {
            m_lDetectChannel = i + m_iStartChannel;  // 
        }
    }
    
    if (m_lDetectChannel != -1)
    {
        GetDetectRule(); 
        GetDetectRuleShow(m_struDetectRule);
        
        StartRealPlay();  
    }

    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVcaAtmFace::GetDetectRuleShow(NET_DVR_DETECT_RULECFG struDetectRule)
{
    m_comboWeekday.SetCurSel(0);
	m_comboCopyTime.SetCurSel(0); 
    memcpy(m_struAlarmTime, struDetectRule.struAlarmTime, sizeof(m_struAlarmTime));
    GetAlarmTimeShow();

    m_bHandleType1 = (struDetectRule.struHandleType.dwHandleType) &0x01;
    m_bHandleType2 = (struDetectRule.struHandleType.dwHandleType>>1)&0x01;
    m_bHandleType3 = (struDetectRule.struHandleType.dwHandleType>>2)&0x01;
    m_bHandleType4 = (struDetectRule.struHandleType.dwHandleType>>3)&0x01;
	m_bHandleType5 = (struDetectRule.struHandleType.dwHandleType>>4)&0x01;
    ShowAlarmNum(struDetectRule.struHandleType, m_dwAlarmOutNum);
	m_listAlarmOut.EnableWindow(m_bHandleType4);
  
	F_ShowRecordChan(struDetectRule, m_iChannelNum);

    m_comboProPicType.SetCurSel(m_struDetectRule.struAlarmJpeg.byPicProType); //获取报警时处理方式
    m_comboResolution.SetCurSel(m_struDetectRule.struAlarmJpeg.struPicParam.wPicSize);//图片格式 4cif等
	m_comboPicQuality.SetCurSel(m_struDetectRule.struAlarmJpeg.struPicParam.wPicQuality);//图片的质量 0 最好 1较好 2一般

    memcpy(&m_struDetectRectList, &m_struDetectRule.struDetectRectList, sizeof(m_struDetectRectList));
    
    m_comboDetectType.SetCurSel(0);
    return;
}


BOOL CDlgVcaAtmFace::F_ShowRecordChan(NET_DVR_DETECT_RULECFG struDetectRule, int nChanNum)
{
    m_listRecordChan.SetExtendedStyle(LVS_EX_CHECKBOXES);
    char szLan[128] = {0};
    char sbufCn[128] = {0};
    char sbufEn[128] = {0};
    int i;
    m_listRecordChan.DeleteAllItems();
    for (i = 0; i < nChanNum; i++)
    {
        sprintf(sbufCn, "通道%d", (i+1));
        sprintf(sbufEn, "Channel%d", (i+1));
        g_StringLanType(szLan, sbufCn, sbufEn);
        m_listRecordChan.InsertItem(i, szLan);
    }
    
    for (i = 0; i < nChanNum; i++ )
    {
        if (struDetectRule.byRelRecordChan[i])
        {
            m_listRecordChan.SetCheck(i);
        }
        
    }
    return TRUE;
}

void CDlgVcaAtmFace::ShowAlarmNum(NET_DVR_HANDLEEXCEPTION_V30 struHandleType, int nAlarmNum)
{
    m_listAlarmOut.DeleteAllItems();
    m_listAlarmOut.SetExtendedStyle(LVS_EX_CHECKBOXES);
    char szLan[128] = {0};
    char sbufCn[128] = {0};
    char sbufEn[128] = {0};
    int i;
    for (i = 0; i < nAlarmNum; i++)
    {
        sprintf(sbufCn, "输出%d", (i+1));
        sprintf(sbufEn, "Channel%d", (i+1));
        g_StringLanType(szLan, sbufCn, sbufEn);
        m_listAlarmOut.InsertItem(i, szLan);
    }
    for (i = 0; i < nAlarmNum; i++ )
    {
        if (struHandleType.byRelAlarmOut[i])
        {
            m_listAlarmOut.SetCheck(i);
        }
    }
    
}
 
void CDlgVcaAtmFace::InitlControls()
{
    int iIndex =0;
    m_comboChanType1.ResetContent();
    m_comboChanType1.InsertString(iIndex, "ATM");
    m_comboChanType1.SetItemData(iIndex, 5);
    
    iIndex = 0;
    m_comboChanType2.ResetContent();
    m_comboChanType2.InsertString(iIndex, "ATM");
    m_comboChanType2.SetItemData(iIndex, 5);
    
    iIndex = 0;
    m_comboChanType3.ResetContent();
    m_comboChanType3.InsertString(iIndex, "ATM");
    m_comboChanType3.SetItemData(iIndex, 5);
    
    iIndex = 0;
    m_comboChanType4.ResetContent();
    m_comboChanType4.InsertString(iIndex, "ATM");
    m_comboChanType4.SetItemData(iIndex, 5);
    
    iIndex = 0;
    m_comboAtmChanMode1.ResetContent();
    m_comboAtmChanMode1.InsertString(iIndex, "ATM Paste");
    m_comboAtmChanMode1.SetItemData(iIndex, 0);
    iIndex++;
    m_comboAtmChanMode1.InsertString(iIndex, "ATM Face");
    m_comboAtmChanMode1.SetItemData(iIndex, 2);

    iIndex = 0;
    m_comboAtmChanMode2.ResetContent();
    m_comboAtmChanMode2.InsertString(iIndex, "ATM paste");
    m_comboAtmChanMode2.SetItemData(iIndex, 0);
    iIndex++;
    m_comboAtmChanMode2.InsertString(iIndex, "ATM face");
    m_comboAtmChanMode2.SetItemData(iIndex, 2);

    iIndex = 0;
    m_comboAtmChanMode3.ResetContent();
    m_comboAtmChanMode3.InsertString(iIndex, "ATM paste");
    m_comboAtmChanMode3.SetItemData(iIndex, 0);
    iIndex++;
    m_comboAtmChanMode3.InsertString(iIndex, "ATM face");
    m_comboAtmChanMode3.SetItemData(iIndex, 2);

    iIndex = 0;
    m_comboAtmChanMode4.ResetContent();
    m_comboAtmChanMode4.InsertString(iIndex, "ATM paste");
    m_comboAtmChanMode4.SetItemData(iIndex, 0);
    iIndex++;
    m_comboAtmChanMode4.InsertString(iIndex, "ATM face");
    m_comboAtmChanMode4.SetItemData(iIndex, 2);

}

void CDlgVcaAtmFace::GetVcaCtrlShow(NET_VCA_CTRLCFG struVcaCtrl)
{
    InitlControls();
    int nIndex = 0;

    m_bVcaEnable1 = struVcaCtrl.struCtrlInfo[0].byVCAEnable;
    m_comboVcaStream1.SetCurSel(struVcaCtrl.struCtrlInfo[0].byStreamWithVCA);
    for (nIndex = 0; nIndex < 10; nIndex++)
    {
        if (m_comboChanType1.GetItemData(nIndex) == struVcaCtrl.struCtrlInfo[0].byVCAType)
        {
            m_comboChanType1.SetCurSel(nIndex);
            break;
        }
    }
    for (nIndex = 0; nIndex < 10; nIndex++)
    {
        if (m_comboAtmChanMode1.GetItemData(nIndex) == struVcaCtrl.struCtrlInfo[0].byMode)
        {
            m_comboAtmChanMode1.SetCurSel(nIndex);
            break;
        }
    }
    
    m_bVcaEnable2 = struVcaCtrl.struCtrlInfo[1].byVCAEnable;
    m_comboVcaStream2.SetCurSel(struVcaCtrl.struCtrlInfo[1].byStreamWithVCA);
    for (nIndex = 0; nIndex < 10; nIndex++)
    {
        if (m_comboChanType2.GetItemData(nIndex) == struVcaCtrl.struCtrlInfo[1].byVCAType)
        {
            m_comboChanType2.SetCurSel(nIndex);
            break;
        }
    }
    for (nIndex = 0; nIndex < 10; nIndex++)
    {
        if (m_comboAtmChanMode2.GetItemData(nIndex) == struVcaCtrl.struCtrlInfo[1].byMode)
        {
            m_comboAtmChanMode2.SetCurSel(nIndex);
            break;
        }
    }
    
    m_bVcaEnable3 = struVcaCtrl.struCtrlInfo[2].byVCAEnable;
    m_comboVcaStream3.SetCurSel(struVcaCtrl.struCtrlInfo[2].byStreamWithVCA);
    for (nIndex = 0; nIndex < 10; nIndex++)
    {
        if (m_comboChanType3.GetItemData(nIndex) == struVcaCtrl.struCtrlInfo[2].byVCAType)
        {
            m_comboChanType3.SetCurSel(nIndex);
            break;
        }
    }
    for (nIndex = 0; nIndex < 10; nIndex++)
    {
        if (m_comboAtmChanMode3.GetItemData(nIndex) == struVcaCtrl.struCtrlInfo[2].byMode)
        {
            m_comboAtmChanMode3.SetCurSel(nIndex);
            break;
        }
    }

    m_bVcaEnable4 = struVcaCtrl.struCtrlInfo[3].byVCAEnable;
    m_comboVcaStream4.SetCurSel(struVcaCtrl.struCtrlInfo[3].byStreamWithVCA);
    for (nIndex = 0; nIndex < 10; nIndex++)
    {
        if (m_comboChanType4.GetItemData(nIndex) == struVcaCtrl.struCtrlInfo[3].byVCAType)
        {
            m_comboChanType4.SetCurSel(nIndex);
            break;
        }
    }
    for (nIndex = 0; nIndex < 10; nIndex++)
    {
        if (m_comboAtmChanMode4.GetItemData(nIndex) == struVcaCtrl.struCtrlInfo[3].byMode)
        {
            m_comboAtmChanMode4.SetCurSel(nIndex);
            break;
        }
    }
   
    UpdateData(FALSE);
    OnChkVcaCtrl1();
    OnChkVcaCtrl2();
    OnChkVcaCtrl3();
    OnChkVcaCtrl4();
}


long CDlgVcaAtmFace::StartRealPlay()
{
    NET_DVR_CLIENTINFO struClientInfo;
    memset(&struClientInfo, 0, sizeof(NET_DVR_CLIENTINFO));
    struClientInfo.lChannel =  m_lDetectChannel;// m_comboChannel.GetCurSel() + m_iStartChannel;
    struClientInfo.hPlayWnd = GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
    m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struClientInfo, NULL, NULL, TRUE); 
    char szLan[128] ={0};
    if (m_lPlayHandle == -1) 
    {
        g_StringLanType(szLan, "预览失败", "Fail to preview");
        AfxMessageBox(szLan);
        return m_lPlayHandle;
    }
    else
    {
        if (!NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawDetectRule, 0))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RigisterDrawFun Fail");
            g_StringLanType(szLan, "设置预览画图回调失败", "Fail to set play draw callback");
            AfxMessageBox(szLan);
        }
        
    }
    return m_lPlayHandle;
}

BOOL CDlgVcaAtmFace::StopRealPlay()
{
    BOOL bRet;
    if (m_lPlayHandle >= 0)
    {
        bRet = NET_DVR_StopRealPlay(m_lPlayHandle);
        if (!bRet)
        {
            AfxMessageBox("Fail to stop realplay");
        }
    }
    return bRet;
}

void CDlgVcaAtmFace::F_DrawDetectRule(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    UNREFERENCED_PARAMETER(lRealHandle);
    UNREFERENCED_PARAMETER(dwUser);
    for (int i = 0; i < m_struDetectRectList.byDetectNum; i++ )
    {
        if ( m_struDetectRectList.struDetectRect[i].byDetectType == DETECTION_AREA)
        {
            F_DrawRect(hDc,  m_struDetectRectList.struDetectRect[i].struVcaRect, i, RGB(0,255,0));
        }
        else if ( m_struDetectRectList.struDetectRect[i].byDetectType  == ENTER_AREA)
        {
            F_DrawRect(hDc,  m_struDetectRectList.struDetectRect[i].struVcaRect, i, RGB(255,255,0));
        }
    }
    return;
}

void CDlgVcaAtmFace::F_DrawRect(HDC hDc, NET_VCA_RECT struRect, int iRectNo, COLORREF color)
{
    UNREFERENCED_PARAMETER(iRectNo);
    CBrush brTmp;
    brTmp.CreateSolidBrush(color);
    CRect rect;
    rect.left = (int)(struRect.fX*m_rcWndRect.Width());
    rect.top = (int)(struRect.fY*m_rcWndRect.Height());
    rect.right = (int)((struRect.fX+struRect.fWidth)*m_rcWndRect.Width());
    rect.bottom = (int)((struRect.fY+struRect.fHeight)*m_rcWndRect.Height());
    FrameRect(hDc, rect, brTmp);
    
    DeleteObject(brTmp);
}

BOOL CDlgVcaAtmFace::SetDetectRule()
{
    char szLan[128] = {0};
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_DETECT_RULECFG, m_lDetectChannel, &m_struDetectRule, sizeof(m_struDetectRule)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_DETECT_RULECFG");
        g_StringLanType(szLan, "设置异物粘贴失败", "Fail to set detect rule config");
        AfxMessageBox(szLan);
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_DETECT_RULECFG");
        g_StringLanType(szLan, "设置异物粘贴成功", "Succ to set detect rule config");
        AfxMessageBox(szLan);
        return TRUE;
    }
}

BOOL CDlgVcaAtmFace::GetDetectRule()
{
    DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_DETECT_RULECFG, m_lDetectChannel, &m_struDetectRule, sizeof(m_struDetectRule), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_DETECT_RULECFG");
        return FALSE;
    } 
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_DETECT_RULECFG");
        return TRUE;
    }
}


/*********************************************************
Function:	F_TimeTest
Desc:	    check time
Input:	
Output:	
Return:	BOOL
**********************************************************/
BOOL CDlgVcaAtmFace::F_TimeTest()
{
    int i, j;
    WORD wStartTime[4], wStopTime[4];
    
    UpdateData(TRUE);
    if( (m_iHour11 < 0) || (m_iHour11 > 24) || (m_iHour12 < 0) || (m_iHour12 > 24) ||	\
        (m_iHour21 < 0) || (m_iHour21 > 24) || (m_iHour22 < 0) || (m_iHour22 > 24) )
    {
        AfxMessageBox("Hours range 0 - 24 !");
        return FALSE;
    }
    if( (m_iMin11 < 0) || (m_iMin11 > 60) || (m_iMin12 < 0) || (m_iMin12 > 60) ||	\
        (m_iMin21 < 0) || (m_iMin21 > 60) || (m_iMin22 < 0) || (m_iMin22 > 60) )
    {
        AfxMessageBox("Minute range 0 - 60!");
        return FALSE;
    }
    wStartTime[0] = (WORD)(m_iHour11 * 100 + m_iMin11);
    wStartTime[1] = (WORD)(m_iHour21 * 100 + m_iMin21);
    wStopTime[0] = (WORD)(m_iHour12 * 100 + m_iMin12);
    wStopTime[1] = (WORD)(m_iHour22 * 100 + m_iMin22);
    for(i = 0; i < MAX_TIMESEGMENT_2; i++)
    {
        if( (wStartTime[i] > 2400) || (wStopTime[i] > 2400) )
        {
            char szLan[128] = {0};
            g_StringLanType(szLan, "布防时间不能超过24:00", "Fortify time can not be more than 24:00");
            AfxMessageBox(szLan);
            return FALSE;
        }
        if(wStartTime[i] > wStopTime[i])
        {
            char szLan[128] = {0};
            g_StringLanType(szLan, "布防起始时间不能大于停止时间", "Fortify start time can not be larger than the record to stop time");
            AfxMessageBox(szLan);
            return FALSE;
        }
        for(j = 0; j < MAX_TIMESEGMENT_2; j++)
        {
            if (i == j)
                continue;
            if( (wStartTime[i] > wStartTime[j]) && (wStartTime[i] < wStopTime[j]) ||	\
                (wStopTime[i] > wStartTime[j]) && (wStopTime[i] < wStopTime[j]) )
            {
                char szLan[128] = {0};
                g_StringLanType(szLan, "布防时间段不能重复!","Fortify time period can not be repeated!");
                AfxMessageBox(szLan);
                return FALSE;
            }
        }
    }
    return TRUE;
}

/*********************************************************
Function:	SetTimePara
Desc:	    set alarm time parameter
Input:	
Output:	
Return:	void 
**********************************************************/
void CDlgVcaAtmFace::SetAlarmTimePara()
{
    int i;
    i = m_comboWeekday.GetCurSel();	
    m_struAlarmTime[i][0].byStartHour   = (BYTE)m_iHour11;
    m_struAlarmTime[i][0].byStartMin    = (BYTE)m_iMin11;
    m_struAlarmTime[i][0].byStopHour    = (BYTE)m_iHour12;
    m_struAlarmTime[i][0].byStopMin     = (BYTE)m_iMin12;
    m_struAlarmTime[i][1].byStartHour   = (BYTE)m_iHour21;
    m_struAlarmTime[i][1].byStartMin    = (BYTE)m_iMin21;
    m_struAlarmTime[i][1].byStopHour    = (BYTE)m_iHour22;
    m_struAlarmTime[i][1].byStopMin     = (BYTE)m_iMin22;
}

void CDlgVcaAtmFace::OnTimeOk() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (!F_TimeTest())
    {
        return;
    }
    int	i = m_comboWeekday.GetCurSel();	
    m_struAlarmTime[i][0].byStartHour   = (BYTE)m_iHour11;
    m_struAlarmTime[i][0].byStartMin    = (BYTE)m_iMin11;
    m_struAlarmTime[i][0].byStopHour    =(BYTE) m_iHour12;
    m_struAlarmTime[i][0].byStopMin     = (BYTE)m_iMin12;
    m_struAlarmTime[i][1].byStartHour   = (BYTE)m_iHour21;
    m_struAlarmTime[i][1].byStartMin    = (BYTE)m_iMin21;
    m_struAlarmTime[i][1].byStopHour    = (BYTE)m_iHour22;
    m_struAlarmTime[i][1].byStopMin     = (BYTE)m_iMin22;
	GetDlgItem(IDC_TIME_COPY)->EnableWindow(TRUE);
}


void CDlgVcaAtmFace::OnTimeCopy() 
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
            for(k=0; k<MAX_TIMESEGMENT_2; k++)
            {
                memcpy(&(m_struAlarmTime[j][k]), &(m_struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
            }
        }
    }
    else
    {
        for(k=0; k<MAX_TIMESEGMENT_2; k++)
        {
            memcpy(&(m_struAlarmTime[m_nCopyTime][k]), &(m_struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
        }
	}
}


void  CDlgVcaAtmFace::GetAlarmTimeShow()
{
    m_iHour11   = m_struAlarmTime[0][0].byStartHour;
    m_iMin11    = m_struAlarmTime[0][0].byStartMin;
    m_iHour12   = m_struAlarmTime[0][0].byStopHour;
    m_iMin12    = m_struAlarmTime[0][0].byStopMin;
    m_iHour21   = m_struAlarmTime[0][1].byStartHour;
    m_iMin21    = m_struAlarmTime[0][1].byStartMin;
    m_iHour22   = m_struAlarmTime[0][1].byStopHour;
	m_iMin22    = m_struAlarmTime[0][1].byStopMin;
}

/*********************************************************
Function:	SetAlarmPara	
Desc:	    set alarm parameter
Input:	
Output:	
Return:	void 
**********************************************************/
void CDlgVcaAtmFace::SetAlarmPara(NET_DVR_HANDLEEXCEPTION_V30 &struHandleType)
{
    
    UpdateData(TRUE);
    struHandleType.dwHandleType = 0;
    struHandleType.dwHandleType |= (m_bHandleType1 << 0);
    struHandleType.dwHandleType |= (m_bHandleType2 << 1);
    struHandleType.dwHandleType |= (m_bHandleType3 << 2);
    struHandleType.dwHandleType |= (m_bHandleType4 << 3);
    struHandleType.dwHandleType |= (m_bHandleType5 << 4);
    
    for (DWORD i = 0; i < m_dwAlarmOutNum; i++)
    {
        struHandleType.byRelAlarmOut[i] = (BYTE)m_listAlarmOut.GetCheck(i);
    }
}

/*********************************************************
Function:	OnCheckhandletype4
Desc:		
Input:	
Output:	
Return:	void 
**********************************************************/
void CDlgVcaAtmFace::OnCheckhandletype4() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_listAlarmOut.EnableWindow(m_bHandleType4);
}

void CDlgVcaAtmFace::OnChkVcaCtrl1() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_comboChanType1.EnableWindow(m_bVcaEnable1);
    m_comboAtmChanMode1.EnableWindow(m_bVcaEnable1);
    m_comboVcaStream1.EnableWindow(m_bVcaEnable1);
    UpdateData(FALSE);
}

void CDlgVcaAtmFace::OnChkVcaCtrl2() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_comboChanType2.EnableWindow(m_bVcaEnable2);
    m_comboAtmChanMode2.EnableWindow(m_bVcaEnable2);
    m_comboVcaStream2.EnableWindow(m_bVcaEnable2);
    UpdateData(FALSE);
}

void CDlgVcaAtmFace::OnChkVcaCtrl3() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_comboChanType3.EnableWindow(m_bVcaEnable3);
    m_comboAtmChanMode3.EnableWindow(m_bVcaEnable3);
    m_comboVcaStream3.EnableWindow(m_bVcaEnable3);
    UpdateData(FALSE);
}

void CDlgVcaAtmFace::OnChkVcaCtrl4() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_comboChanType4.EnableWindow(m_bVcaEnable4);
    m_comboAtmChanMode4.EnableWindow(m_bVcaEnable4);
    m_comboVcaStream4.EnableWindow(m_bVcaEnable4);
    UpdateData(FALSE);
}

void CDlgVcaAtmFace::OnBtnSetCtrlcfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    // channel1 
    m_struVcaCtrl.struCtrlInfo[0].byVCAEnable = (BYTE)m_bVcaEnable1;
    m_struVcaCtrl.struCtrlInfo[0].byStreamWithVCA = (BYTE)m_comboVcaStream1.GetCurSel();
    m_struVcaCtrl.struCtrlInfo[0].byVCAType = (BYTE)m_comboChanType1.GetItemData(m_comboChanType1.GetCurSel());
    m_struVcaCtrl.struCtrlInfo[0].byMode = (BYTE)m_comboAtmChanMode1.GetItemData(m_comboAtmChanMode1.GetCurSel());

    // channel2
    m_struVcaCtrl.struCtrlInfo[1].byVCAEnable = (BYTE)m_bVcaEnable2;
    m_struVcaCtrl.struCtrlInfo[1].byStreamWithVCA = (BYTE)m_comboVcaStream2.GetCurSel();
    m_struVcaCtrl.struCtrlInfo[1].byVCAType = (BYTE)m_comboChanType2.GetItemData(m_comboChanType2.GetCurSel());
    m_struVcaCtrl.struCtrlInfo[1].byMode = (BYTE)m_comboAtmChanMode2.GetItemData(m_comboAtmChanMode2.GetCurSel());
    // channel3 
    m_struVcaCtrl.struCtrlInfo[2].byVCAEnable = (BYTE)m_bVcaEnable3;
    m_struVcaCtrl.struCtrlInfo[2].byStreamWithVCA = (BYTE)m_comboVcaStream3.GetCurSel();
    m_struVcaCtrl.struCtrlInfo[2].byVCAType = (BYTE)m_comboChanType3.GetItemData(m_comboChanType3.GetCurSel());
    m_struVcaCtrl.struCtrlInfo[2].byMode = (BYTE)m_comboAtmChanMode3.GetItemData(m_comboAtmChanMode3.GetCurSel());
    // channel4 
    m_struVcaCtrl.struCtrlInfo[3].byVCAEnable = (BYTE)m_bVcaEnable4;
    m_struVcaCtrl.struCtrlInfo[3].  byStreamWithVCA = (BYTE)m_comboVcaStream4.GetCurSel();
    m_struVcaCtrl.struCtrlInfo[3].byVCAType = (BYTE)m_comboChanType4.GetItemData(m_comboChanType4.GetCurSel());
    m_struVcaCtrl.struCtrlInfo[3].byMode = (BYTE)m_comboAtmChanMode4.GetItemData(m_comboAtmChanMode4.GetCurSel());

    char szLan[128] = {0};
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_VCA_CTRLCFG, 0, &m_struVcaCtrl, sizeof(m_struVcaCtrl)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VCA_CTRLCFG");
        g_StringLanType(szLan, "设置智能控制失败", "Fail to set VCA control");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VCA_CTRLCFG");
        g_StringLanType(szLan, "设置智能控制成功", "Succ to set VCA control");
        AfxMessageBox(szLan);
    }
}

void CDlgVcaAtmFace::OnBtnGetCtrlcfg() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgVcaAtmFace::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	StopRealPlay();

	CDialog::PostNcDestroy();
}

BOOL CDlgVcaAtmFace::PreTranslateMessage(MSG* pMsg) 
{
    CPoint pt(0,0);
    CRect  rcWnd(0,0,0,0);
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&rcWnd);
	GetCursorPos(&pt);
    char szLan[256] = {0};
    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if ( (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && (PtInRect(&rcWnd,pt)))
        {
            if (m_struDetectRectList.byDetectNum < 8)
            {
                memset(& m_struDetectRectList.struDetectRect[m_struDetectRectList.byDetectNum].struVcaRect, 0, sizeof( m_struDetectRectList.struDetectRect[m_struDetectRectList.byDetectNum].struVcaRect));
                m_struDetectRectList.struDetectRect[m_struDetectRectList.byDetectNum].struVcaRect.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                m_struDetectRectList.struDetectRect[m_struDetectRectList.byDetectNum].struVcaRect.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
                m_struDetectRectList.struDetectRect[m_struDetectRectList.byDetectNum].byDetectType = m_comboDetectType.GetCurSel();
                m_bMouseMove = TRUE;
                m_struDetectRectList.byDetectNum++;
            }
            else
            {
                m_bMaxRectNum = TRUE;
                g_StringLanType(szLan, "最多有8个监测区域", "Max 8 monitoring area");
                MessageBox(szLan);
            }
        }
        break;
    case WM_MOUSEMOVE:
        if ( (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && (PtInRect(&rcWnd,pt)) && m_bMouseMove)
        {
            if (m_bMaxRectNum != TRUE)
            {
                int iIndex = (int)m_struDetectRectList.byDetectNum - 1;
                m_struDetectRectList.struDetectRect[iIndex].struVcaRect.fWidth = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() -  m_struDetectRectList.struDetectRect[iIndex].struVcaRect.fX;
                m_struDetectRectList.struDetectRect[iIndex].struVcaRect.fHeight = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() -  m_struDetectRectList.struDetectRect[iIndex].struVcaRect.fY;
            }
        }
        break;
    case WM_LBUTTONUP:
        m_bMouseMove = FALSE;
        m_bMaxRectNum = FALSE;
        break;
    case WM_RBUTTONDOWN:
        if ( (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && (PtInRect(&rcWnd,pt)))
        {   
            memset(&m_struDetectRectList, 0, sizeof(m_struDetectRectList));
        }
        break;
    }
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgVcaAtmFace::OnSelchangeComboDetectType() 
{
	// TODO: Add your control notification handler code here
// 	int iDetectRect = m_comboDetectRect.GetCurSel();
 //   m_struDetectRectList.struDetectRect[iDetectRect].byDetectType = (BYTE)m_comboDetectType.GetCurSel();
}

void CDlgVcaAtmFace::OnSelchangeComboweekday() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int	i = m_comboWeekday.GetCurSel();	
    m_iHour11 = m_struAlarmTime[i][0].byStartHour;
    m_iMin11 = m_struAlarmTime[i][0].byStartMin;
    m_iHour12 = m_struAlarmTime[i][0].byStopHour;
    m_iMin12 = m_struAlarmTime[i][0].byStopMin;
    m_iHour21 = m_struAlarmTime[i][1].byStartHour;
    m_iMin21 = m_struAlarmTime[i][1].byStartMin;
    m_iHour22 = m_struAlarmTime[i][1].byStopHour;
    m_iMin22 = m_struAlarmTime[i][1].byStopMin;
	UpdateData(FALSE);
}

void CDlgVcaAtmFace::OnSelchangeCombocopytime() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgVcaAtmFace::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
// 
//     if ( (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && (PtInRect(&rcWnd,pt)))
//     {
//     }
//     memset(&m_struDetectRectList, 0, sizeof(m_struDetectRectList));
// 	CDialog::OnRButtonDblClk(nFlags, point);
}
