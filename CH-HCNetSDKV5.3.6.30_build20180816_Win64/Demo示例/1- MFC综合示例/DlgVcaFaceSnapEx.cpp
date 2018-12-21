// DlgVcaFaceSnapEx.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgVcaFaceSnapEx.h"
#include "afxdialogex.h"
#include "DrawFun.h"


// CDlgVcaFaceSnapEx 对话框

IMPLEMENT_DYNAMIC(CDlgVcaFaceSnapEx, CDialogEx)

CDlgVcaFaceSnapEx::CDlgVcaFaceSnapEx(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgVcaFaceSnapEx::IDD, pParent)
{
    m_bChkFilterActive = FALSE;
    m_bDrawPolygon = FALSE;
    m_bChkEnable = FALSE;
    m_byRate = 0;
    m_bSetMiniFilter = FALSE;
    m_bSetMaxFilter = FALSE;
    m_bySnapInterval = 0;
    m_bySnapThreshold = 0;
    m_byReferBright = 0;
    m_byMatchThreshold = 0;
    m_dwFaceExposureMinDuration = 0;
    m_dwTerminalNo = 0;
    m_dwUploadInterval = 0;
    m_dwValidFaceMinDuration = 0;
    m_dwFaceFilteringTime = 0;
    m_lUserID = -1;
    m_lChannel = -1;
    m_lDeviceIndex = -1;
    m_bDrawEnd = FALSE;
    m_nDrawPointNum = 0;
    m_lPlayHandle = -1;
    memset(&m_struPolyGon, 0, sizeof(m_struPolyGon));
    memset(&m_struFaceSnapCfg, 0, sizeof(m_struFaceSnapCfg));
    memset(&m_struCond, 0, sizeof(m_struCond));

}

CDlgVcaFaceSnapEx::~CDlgVcaFaceSnapEx()
{
}

void CDlgVcaFaceSnapEx::DrawRgnFun(HDC hDc)
{
    DRAW_POLYGON_PARAM_EX struPolygonParam;

    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    struPolygonParam.color = RGB(255, 255, 0);
    memcpy(&struPolygonParam.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));
    struPolygonParam.pArryPt = m_struPolyGon.struPos;
    struPolygonParam.dwPtNum = m_struPolyGon.dwPointNum;
    CDrawFun::DrawPolygonEx(hDc, &struPolygonParam);

}

void CDlgVcaFaceSnapEx::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_LIST_FACESNAP_EX, m_lstFaceSnapEx);
    DDX_Control(pDX, IDC_COMBO_CHANNEL_EX, m_cmbChannel);
    DDX_Control(pDX, IDC_COMBO_ROI_EX, m_comROI);
    DDX_Control(pDX, IDC_COMBO_FACE_ENABLE_EX, m_comFaceEnable);
    DDX_Control(pDX, IDC_COMBO_BACK_GROUND_EX, m_comBackgroundPic);
    DDX_Control(pDX, IDC_COMBO_MATCH_ALATM_TYPE_EX, m_comboMatchType);
    DDX_Control(pDX, IDC_COMBO_SENSITIVE_EX, m_comboSensitive);
    DDX_Control(pDX, IDC_COMBO_SNAPTIMES_EX, m_comboSnapTimes);
    DDX_Control(pDX, IDC_COMBO_RULE_NUM_EX, m_comboRuleNum);
    DDX_Control(pDX, IDC_COMBO_PIC_QUALITY_EX, m_comboPicQuality);
    DDX_Control(pDX, IDC_COMBO_RESOLUTION_EX, m_comboPicResolution);
    DDX_Check(pDX, IDC_CHECK_FILTER_ACTIVE_EX, m_bChkFilterActive);
    DDX_Check(pDX, IDC_CHK_DRAW_POLYGON_EX, m_bDrawPolygon);
    DDX_Check(pDX, IDC_CHK_ENABLE_EX, m_bChkEnable);
    DDX_Text(pDX, IDC_EDIT_RATE_EX, m_byRate);
    DDX_Check(pDX, IDC_CHECK_SET_MINI_FILTER_EX, m_bSetMiniFilter);
    DDX_Check(pDX, IDC_CHECK_SET_MAX_FILTER_EX, m_bSetMaxFilter);
    DDX_Text(pDX, IDC_EDIT_SNAP_INTERVAL_EX, m_bySnapInterval);
    DDX_Text(pDX, IDC_EDIT_SNAP_THRESHOLD_EX, m_bySnapThreshold);
    DDX_Text(pDX, IDC_EDIT_REFERENCE_BRIGHT_EX, m_byReferBright);
    DDX_Text(pDX, IDC_EDIT_MATCH_THRESHOLD_EX, m_byMatchThreshold);
    DDX_Text(pDX, IDC_EDIT_FACE_MIN_DURA_EX, m_dwFaceExposureMinDuration);
    DDX_Text(pDX, IDC_EDIT_TERMINAL_NO_EX, m_dwTerminalNo);
    DDX_Text(pDX, IDC_EDIT_UPLOAD_INTERVAL_EX, m_dwUploadInterval);
    DDX_Text(pDX, IDC_EDIT_VALID_FACE_MIN_DURATION_EX, m_dwValidFaceMinDuration);
    DDX_Text(pDX, IDC_EDIT_FACEFILTER_TIME_EX, m_dwFaceFilteringTime);
    DDX_Control(pDX, IDC_COMBO_BOX, m_comboBox);
    DDX_Control(pDX, IDC_EDIT_TEXT_BOX, m_editTextBox);
}


BEGIN_MESSAGE_MAP(CDlgVcaFaceSnapEx, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_SET_FACESNAP_EX, &CDlgVcaFaceSnapEx::OnBnClickedBtnSetFacesnapEx)
    ON_BN_CLICKED(IDC_BTN_GET_FACESNAP, &CDlgVcaFaceSnapEx::OnBnClickedBtnGetFacesnap)
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    ON_BN_CLICKED(IDC_CHECK_SET_MINI_FILTER_EX, &CDlgVcaFaceSnapEx::OnBnClickedCheckSetMiniFilterEx)
    ON_BN_CLICKED(IDC_CHECK_SET_MAX_FILTER_EX, &CDlgVcaFaceSnapEx::OnBnClickedCheckSetMaxFilterEx)
    ON_BN_CLICKED(IDC_CHECK_FILTER_ACTIVE_EX, &CDlgVcaFaceSnapEx::OnBnClickedCheckFilterActiveEx)
    ON_NOTIFY(NM_CLICK, IDC_LIST_FACESNAP_EX, &CDlgVcaFaceSnapEx::OnNMClickListFacesnapEx)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_FACESNAP_EX, &CDlgVcaFaceSnapEx::OnNMDblclkListFacesnapEx)

    ON_EN_KILLFOCUS(IDC_EDIT_TEXT_BOX, &CDlgVcaFaceSnapEx::OnEnKillfocusEditTextBox)
//     ON_EN_CHANGE(IDC_EDIT_TEXT_BOX, &CDlgVcaFaceSnapEx::OnEnChangeEditTextBox)
    ON_CBN_KILLFOCUS(IDC_COMBO_BOX, &CDlgVcaFaceSnapEx::OnCbnKillfocusComboBox)
END_MESSAGE_MAP()



CDlgVcaFaceSnapEx *pDlg = NULL;
void CALLBACK g_DrawFaceSnapRgn(LONG lRealHandle, HDC hDc, DWORD dwUser)
{

    pDlg->DrawRgnFun(hDc);

}


BOOL CDlgVcaFaceSnapEx::Play(NET_DVR_CLIENTINFO* struClientInfo, LONG loginID, int index)
{
    char szLan[128] = { 0 };
    char szTemp[256] = { 0 };
    if (m_lPlayHandle >= 0)
    {
        NET_DVR_StopRealPlay(m_lPlayHandle);
        m_lPlayHandle = -1;
    }

    m_lPlayHandle = NET_DVR_RealPlay_V30(loginID, struClientInfo, NULL, NULL, TRUE);
    BOOL bRet = FALSE;
    if (m_lPlayHandle < 0)
    {
        g_StringLanType(szLan, "预览失败", "Realplay failed");
        sprintf(szTemp, "%s %s ErrCode:%d", szLan, NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());
        AfxMessageBox(szTemp);
        return FALSE;
    }
    UpdateData(FALSE);
    return TRUE;
}

BOOL CDlgVcaFaceSnapEx::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_pStruFaceSnapCond = new NET_VCA_FACESNAP_COND[64];
    memset(m_pStruFaceSnapCond, 0, sizeof(NET_VCA_FACESNAP_COND)* 64);  

    InitListCtrl();

    pDlg = this;
    GetDlgItem(IDC_FACESNAPEX_PLAYWND)->GetWindowRect(&m_rcPlayWnd);
    ScreenToClient(&m_rcPlayWnd);

    NET_DVR_CLIENTINFO struPlayInfo;
    memset(&struPlayInfo, 0, sizeof(NET_DVR_CLIENTINFO));

    struPlayInfo.hPlayWnd = GetDlgItem(IDC_FACESNAPEX_PLAYWND)->GetSafeHwnd();
    struPlayInfo.lChannel = m_lChannel;
    struPlayInfo.lLinkMode = 0;
    Play(&struPlayInfo, m_lUserID, 0);
          
    BOOL bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, g_DrawFaceSnapRgn, 0);


    return TRUE;  
}

void CDlgVcaFaceSnapEx::InitListCtrl()
{
    char szLan[128] = { 0 };
    m_lstFaceSnapEx.SetExtendedStyle(m_lstFaceSnapEx.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);
    
    g_StringLanType(szLan, "序号", "Serial No.");
    m_lstFaceSnapEx.InsertColumn(0, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "场景号", "Secne ID");
    m_lstFaceSnapEx.InsertColumn(1, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "通道", "channel");
    m_lstFaceSnapEx.InsertColumn(2, szLan, LVCFMT_LEFT, 50, -1);
  
    g_StringLanType(szLan, "状态", "Status");
    m_lstFaceSnapEx.InsertColumn(3, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "抓拍次数", "Snap Time");
    m_lstFaceSnapEx.InsertColumn(4, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "抓拍间隔", "Snap Interval");
    m_lstFaceSnapEx.InsertColumn(5, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "抓拍阈值", "Snap Threshold");
    m_lstFaceSnapEx.InsertColumn(6, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "生成速度", "Generate Rate");
    m_lstFaceSnapEx.InsertColumn(7, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "灵敏度", "Sensitive");
    m_lstFaceSnapEx.InsertColumn(8, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "参考亮度", "Reference Bright");
    m_lstFaceSnapEx.InsertColumn(9, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "报警模式", "Match Type");
    m_lstFaceSnapEx.InsertColumn(10, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "对比阈值", "Match Threshold");
    m_lstFaceSnapEx.InsertColumn(11, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "图片分辨率", "User name");
    m_lstFaceSnapEx.InsertColumn(12, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "图片质量", "User name");
    m_lstFaceSnapEx.InsertColumn(13, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "人脸曝光最短时间", "FaceExposureMinDuration");
    m_lstFaceSnapEx.InsertColumn(14, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "曝光模式", "FaceExposureMode");
    m_lstFaceSnapEx.InsertColumn(15, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "背景图上传", "BackgroundPic");
    m_lstFaceSnapEx.InsertColumn(16, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "有效人脸最短时间", "ValidFaceTime");
    m_lstFaceSnapEx.InsertColumn(17, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "抓拍间隔时间", "UploadInterval");
    m_lstFaceSnapEx.InsertColumn(18, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "停留时间过滤", "FaceFilteringTime");
    m_lstFaceSnapEx.InsertColumn(19, szLan, LVCFMT_LEFT, 50, -1);

    UpdateData(FALSE);
}

void CDlgVcaFaceSnapEx::OnBnClickedBtnSetFacesnapEx()
{
    UpdateData(TRUE);

    for (int i = 0; i < MAX_RULE_NUM; i++)
    {
        if (m_struFaceSnapCfg.struRule[i].struVcaPolygon.dwPointNum < 3 && m_struFaceSnapCfg.struRule[i].struVcaPolygon.dwPointNum >0)
        {
            AfxMessageBox("多边形区域不符合要求!");
            return;
        }
    }
    
    char szLan[128] = { 0 };
    int dwCount = m_dwTerminalNo;

    LPNET_VCA_FACESNAPCFG pFaceSnapCfg = &m_pstruFaceSnapCfg[0];
    LPNET_VCA_FACESNAPCFG pTempFaceSnapCfg = pFaceSnapCfg;

    LPNET_VCA_FACESNAP_COND pstruFaceSnapCond = NULL;
    LPNET_VCA_FACESNAP_COND pstruTempFaceSnapCond = NULL;

    

    if (0 == dwCount || 1 == dwCount)
    {
        m_struCond.dwSize = sizeof(NET_VCA_FACESNAP_COND);
        m_struCond.dwChannel = m_lChannel;
        m_struCond.wSecneID = (WORD)m_dwTerminalNo;

        m_struFaceSnapCfg.dwSize = sizeof(NET_VCA_FACESNAPCFG);

        m_struFaceSnapCfg.byGenerateRate = m_byRate;
        m_struFaceSnapCfg.struRule[m_comboRuleNum.GetCurSel()].byActive = m_bChkEnable;
        m_struFaceSnapCfg.struRule[m_comboRuleNum.GetCurSel()].byAutoROIEnable = m_comROI.GetCurSel();
        m_struFaceSnapCfg.bySnapTime = m_comboSnapTimes.GetCurSel();
        m_struFaceSnapCfg.bySensitive = m_comboSensitive.GetCurSel() + 1;
        m_struFaceSnapCfg.struRule[m_comboRuleNum.GetCurSel()].struSizeFilter.byActive = m_bChkFilterActive;
        m_struFaceSnapCfg.bySnapInterval = m_bySnapInterval;
        m_struFaceSnapCfg.bySnapThreshold = m_bySnapThreshold;
        m_struFaceSnapCfg.struPictureParam.wPicQuality = m_comboPicQuality.GetCurSel();
        m_struFaceSnapCfg.struPictureParam.wPicSize = m_comboPicResolution.GetCurSel();
        m_struFaceSnapCfg.byReferenceBright = m_byReferBright;
        m_struFaceSnapCfg.byMatchThreshold = m_byMatchThreshold;
        m_struFaceSnapCfg.byMatchType = m_comboMatchType.GetCurSel();

        m_struFaceSnapCfg.wFaceExposureMinDuration = m_dwFaceExposureMinDuration;
        m_struFaceSnapCfg.byFaceExposureMode = m_comFaceEnable.GetCurSel();
        m_struFaceSnapCfg.byBackgroundPic = m_comBackgroundPic.GetCurSel();
        
        m_struFaceSnapCfg.dwUploadInterval = m_dwUploadInterval;
        m_struFaceSnapCfg.dwValidFaceTime = m_dwValidFaceMinDuration;
        m_struFaceSnapCfg.dwFaceFilteringTime = m_dwFaceFilteringTime;

        DWORD dwStatus = 0;
        BOOL bRet = NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_FACESNAPCFG_V50, 1, &m_struCond, sizeof(NET_VCA_FACESNAP_COND), &dwStatus, &m_struFaceSnapCfg, sizeof(NET_VCA_FACESNAPCFG));

        if (bRet)
        {
            g_StringLanType(szLan, "设置成功", "Success");
            g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FACESNAPCFG_V50 Succ");
            AfxMessageBox(szLan);
        }
        else
        {
            g_StringLanType(szLan, "设置失败", "Fail");
            g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FACESNAPCFG_V50 Fail");
            AfxMessageBox(szLan);
        }       
    }  

    else
    {       
        pstruFaceSnapCond = new NET_VCA_FACESNAP_COND[dwCount];
        memset(pstruFaceSnapCond, 0, dwCount * sizeof(NET_VCA_FACESNAP_COND));
        pstruTempFaceSnapCond = pstruFaceSnapCond;

        pFaceSnapCfg = new NET_VCA_FACESNAPCFG[dwCount];
        memset(pFaceSnapCfg, 0, dwCount * sizeof(NET_VCA_FACESNAPCFG));
        pTempFaceSnapCfg = pFaceSnapCfg;
        pTempFaceSnapCfg->dwSize = dwCount * sizeof(NET_VCA_FACESNAPCFG);
       
        int i = 0;
        for (i = 0; i < dwCount; i++)
        {
            pstruTempFaceSnapCond->dwSize = sizeof(NET_VCA_FACESNAP_COND);
            pstruTempFaceSnapCond->dwChannel = m_lChannel;
            pstruTempFaceSnapCond->wSecneID = (WORD)m_dwTerminalNo;

            memcpy(pTempFaceSnapCfg, &m_struBatchFaceSnapCfg[i], sizeof(m_struFaceSnapCfg));
            pTempFaceSnapCfg++;         
        }        

        DWORD *pStatus = new DWORD[dwCount];
        memset(pStatus, 0, sizeof(DWORD)*dwCount);

        if (NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_FACESNAPCFG_V50, dwCount, pstruFaceSnapCond, dwCount*sizeof(NET_VCA_FACESNAP_COND), pStatus, pTempFaceSnapCfg, dwCount*sizeof(NET_VCA_FACESNAPCFG)))
        {
            g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FACESNAPCFG_V50 Succeed");
        }
        else
        {
            g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FACESNAPCFG_V50 Succeed");
        }

        for (i = 0; i < dwCount; i++)
        {
            strStatus.Format("%d", *pStatus);
            m_lstFaceSnapEx.SetItemText(i, 4, strStatus);
            pStatus++;
        }
    }
    UpdateData(FALSE);
}


void CDlgVcaFaceSnapEx::OnBnClickedBtnGetFacesnap()
{
    UpdateData(TRUE);
    DWORD  m_dwStatus[64];
    char szLan[64] = { 0 };
    int dwCount = m_dwTerminalNo;

    LPNET_VCA_FACESNAPCFG pFaceSnapCfg = NULL;


    LPNET_VCA_FACESNAP_COND pstruStreamID = NULL;
    LPNET_VCA_FACESNAP_COND pTempStreamID = NULL;


    if (0 == dwCount || 1 == dwCount)
    {

        NET_VCA_FACESNAP_COND  struCond = { 0 };
        struCond.dwSize = sizeof(NET_VCA_FACESNAP_COND);
        struCond.dwChannel = m_lChannel;
        struCond.wSecneID = m_dwTerminalNo;

        NET_VCA_FACESNAPCFG struCfg = { 0 };
        struCfg.dwSize = sizeof(NET_VCA_FACESNAPCFG);

        // 返回的状态
        DWORD dwStatus = 0;
        BOOL bRet = NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_FACESNAPCFG_V50, 1, &struCond, sizeof(NET_VCA_FACESNAP_COND), &dwStatus, &struCfg, sizeof(NET_VCA_FACESNAPCFG));
        if (bRet)
        {
            g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FACESNAPCFG_V50 SUCC");
        }
        else
        {
            g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FACESNAPCFG_V50 Fail");
            return;
        }

        m_bChkEnable = struCfg.struRule[m_comboRuleNum.GetCurSel()].byActive;
        m_bChkFilterActive = struCfg.struRule[m_comboRuleNum.GetCurSel()].struSizeFilter.byActive;
        m_comboSensitive.SetCurSel(struCfg.bySensitive - 1);
        m_comboSnapTimes.SetCurSel(struCfg.bySnapTime);
        m_byRate = struCfg.byGenerateRate;
        m_bySnapInterval = struCfg.bySnapInterval;
        m_bySnapThreshold = struCfg.bySnapThreshold;
        m_comboPicQuality.SetCurSel(struCfg.struPictureParam.wPicQuality);
        m_comboPicResolution.SetCurSel(struCfg.struPictureParam.wPicSize);
        m_byReferBright = struCfg.byReferenceBright;
        m_comboMatchType.SetCurSel(struCfg.byMatchType);
        m_byMatchThreshold = struCfg.byMatchThreshold;

        m_dwFaceExposureMinDuration = struCfg.wFaceExposureMinDuration;
        m_comFaceEnable.SetCurSel(struCfg.byFaceExposureMode);
        m_comBackgroundPic.SetCurSel(struCfg.byBackgroundPic);
        m_comROI.SetCurSel(struCfg.struRule[m_comboRuleNum.GetCurSel()].byAutoROIEnable);
        m_dwUploadInterval = struCfg.dwUploadInterval;
        m_dwValidFaceMinDuration = struCfg.dwValidFaceTime;
        m_dwFaceFilteringTime = struCfg.dwFaceFilteringTime;
        memcpy(&m_struPolyGon, &struCfg.struRule[m_comboRuleNum.GetCurSel()].struVcaPolygon, sizeof(NET_VCA_POLYGON));
        UpdateData(FALSE);
        return;

    }
    else
    {
        pstruStreamID = new NET_VCA_FACESNAP_COND[dwCount];
        if (NULL == pstruStreamID)
        {
            g_StringLanType(szLan, "申请内存失败", "new memory failed");
            AfxMessageBox(szLan);
            return;
        }
        memset(pstruStreamID, 0, dwCount*sizeof(NET_VCA_FACESNAP_COND));
        pTempStreamID = pstruStreamID;

        pFaceSnapCfg = new NET_VCA_FACESNAPCFG[dwCount];
        if (NULL == pFaceSnapCfg)
        {
            g_StringLanType(szLan, "申请内存失败", "new memory failed");
            AfxMessageBox(szLan);
            return;
        }
        memset(pFaceSnapCfg, 0, dwCount*sizeof(NET_VCA_FACESNAPCFG));

        DWORD *pStatus = new DWORD[dwCount];
        memset(pStatus, 0, sizeof(DWORD)*dwCount);

        int i = 0;
        for (i = 0; i < dwCount; i++)
        {
            pTempStreamID->dwSize = sizeof(NET_DVR_STREAM_INFO);
            pTempStreamID->dwChannel = m_lChannel;
            pTempStreamID->wSecneID = m_dwTerminalNo;

            pTempStreamID++;
        }

        if (NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_FACESNAPCFG_V50, dwCount, pstruStreamID, dwCount*sizeof(NET_VCA_FACESNAP_COND), pStatus, pFaceSnapCfg, dwCount*sizeof(NET_VCA_FACESNAPCFG)))
        {
            g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FACESNAPCFG_V50 SUCC");
        }
        else
        {
            g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FACESNAPCFG_V50 Fail");
            return;
        }


        if (NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_FACESNAPCFG_V50, dwCount, pstruStreamID, dwCount*sizeof(NET_VCA_FACESNAP_COND), pStatus, pFaceSnapCfg, dwCount*sizeof(NET_VCA_FACESNAPCFG)))
        {
            g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FACESNAPCFG_V50 Succeed");
        }
        else
        {
            g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FACESNAPCFG_V50 Fail");
        }

        m_lstFaceSnapEx.DeleteAllItems();
        CString strTemp;
        for (i = 0; i < dwCount; i++)
        {
            CString stridtemp;
            stridtemp.Format("%d", i + 1);
            m_lstFaceSnapEx.InsertItem(i, stridtemp);

            strTemp.Format("%d", pstruStreamID->wSecneID);
            m_lstFaceSnapEx.SetItemText(i, 1, strTemp);

            strTemp.Format("%d", pstruStreamID->dwChannel);
            m_lstFaceSnapEx.SetItemText(i, 2, strTemp);

            strTemp.Format("%d", *pStatus);
            m_lstFaceSnapEx.SetItemText(i, 3, strTemp);

            strTemp.Format("%d", pFaceSnapCfg->bySnapTime);
            m_lstFaceSnapEx.SetItemText(i, 4, strTemp);

            strTemp.Format("%d", pFaceSnapCfg->bySnapInterval);
            m_lstFaceSnapEx.SetItemText(i, 5, strTemp);

            strTemp.Format("%d", pFaceSnapCfg->bySnapThreshold);
            m_lstFaceSnapEx.SetItemText(i, 6, strTemp);

            strTemp.Format("%d", pFaceSnapCfg->byGenerateRate);
            m_lstFaceSnapEx.SetItemText(i, 7, strTemp);

            strTemp.Format("%d", pFaceSnapCfg->bySensitive);
            m_lstFaceSnapEx.SetItemText(i, 8, strTemp);

            strTemp.Format("%d", pFaceSnapCfg->byReferenceBright);
            m_lstFaceSnapEx.SetItemText(i, 9, strTemp);

            strTemp.Format("%d", pFaceSnapCfg->byMatchType);
            m_lstFaceSnapEx.SetItemText(i, 10, strTemp);

            strTemp.Format("%d", pFaceSnapCfg->byMatchThreshold);
            m_lstFaceSnapEx.SetItemText(i, 11, strTemp);

            strTemp.Format("%d", pFaceSnapCfg->struPictureParam.wPicQuality);
            m_lstFaceSnapEx.SetItemText(i, 12, strTemp);

            strTemp.Format("%d", pFaceSnapCfg->struPictureParam.wPicSize);
            m_lstFaceSnapEx.SetItemText(i, 13, strTemp);

            strTemp.Format("%d", pFaceSnapCfg->wFaceExposureMinDuration);
            m_lstFaceSnapEx.SetItemText(i, 14, strTemp);

            strTemp.Format("%d", pFaceSnapCfg->byFaceExposureMode);
            m_lstFaceSnapEx.SetItemText(i, 15, strTemp);

            strTemp.Format("%d", pFaceSnapCfg->byBackgroundPic);
            m_lstFaceSnapEx.SetItemText(i, 16, strTemp);

            strTemp.Format("%d", pFaceSnapCfg->dwValidFaceTime);
            m_lstFaceSnapEx.SetItemText(i, 17, strTemp);

            strTemp.Format("%d", pFaceSnapCfg->dwUploadInterval);
            m_lstFaceSnapEx.SetItemText(i, 18, strTemp);

            strTemp.Format("%d", pFaceSnapCfg->dwUploadInterval);
            m_lstFaceSnapEx.SetItemText(i, 19, strTemp);
             
            UpdateData(FALSE);

            pStatus++;
            pFaceSnapCfg++;

       }
                 
    }

    if (pstruStreamID != NULL)
    {
        delete[] pstruStreamID;
    }

    UpdateData(FALSE);   
}



void CDlgVcaFaceSnapEx::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值
    UpdateData(TRUE);
    CDialogEx::OnMouseMove(nFlags, point);

    if (m_bDrawEnd)
    {
        return;
    }

    if (!m_rcPlayWnd.PtInRect(point))
    {
        return;
    }

    NET_VCA_POLYGON&  struRegion = m_struFaceSnapCfg.struRule[m_comboRuleNum.GetCurSel() + 1].struVcaPolygon;

    struRegion.struPos[m_nDrawPointNum].fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
    struRegion.struPos[m_nDrawPointNum].fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
   struRegion.dwPointNum = m_nDrawPointNum + 1;

    memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));

    UpdateData(FALSE);



}


void CDlgVcaFaceSnapEx::OnLButtonDown(UINT nFlags, CPoint point)
{

    CDialogEx::OnLButtonDown(nFlags, point);

    UpdateData(TRUE);

    if (!m_rcPlayWnd.PtInRect(point))
    {
        return;
    }

    NET_VCA_POLYGON&  struRegion =  m_struFaceSnapCfg.struRule[m_comboRuleNum.GetCurSel() + 1].struVcaPolygon;
    if (m_bDrawEnd || m_nDrawPointNum >= 10)
    {
        m_bDrawEnd = FALSE;
        memset(&struRegion, 0, sizeof(struRegion));
        return;
    }
    struRegion.struPos[m_nDrawPointNum].fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
    struRegion.struPos[m_nDrawPointNum].fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
    m_nDrawPointNum++;

    memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
/*    m_nDrawPointNum = 0;*/

    UpdateData(FALSE);
}


void CDlgVcaFaceSnapEx::OnRButtonDown(UINT nFlags, CPoint point)
{

    CDialogEx::OnRButtonDown(nFlags, point);

    if (!m_rcPlayWnd.PtInRect(point))
    {
        return;
    }

     NET_VCA_POLYGON&  struRegion = m_struFaceSnapCfg.struRule[m_comboRuleNum.GetCurSel() + 1].struVcaPolygon;
    if (m_nDrawPointNum >= 20 || m_nDrawPointNum < 3)
    {
        memset(&struRegion, 0, sizeof(struRegion));
        return;
    }

    struRegion.dwPointNum = m_nDrawPointNum;

    memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
    m_nDrawPointNum = 0;
    m_bDrawEnd = TRUE;
}


void CDlgVcaFaceSnapEx::OnBnClickedCheckSetMiniFilterEx()
{
    UpdateData(TRUE);
    if (m_bSetMiniFilter)
    {
        m_bSetMaxFilter = FALSE;
        m_bDrawPolygon = FALSE;
        UpdateData(FALSE);
    }
}


void CDlgVcaFaceSnapEx::OnBnClickedCheckSetMaxFilterEx()
{
    UpdateData(TRUE);
    if (m_bSetMaxFilter)
    {
        m_bSetMiniFilter = FALSE;
        m_bDrawPolygon = FALSE;
        UpdateData(FALSE);
    }
}


void CDlgVcaFaceSnapEx::OnBnClickedCheckFilterActiveEx()
{
    UpdateData(TRUE);
    GetDlgItem(IDC_CHECK_SET_MAX_FILTER_EX)->EnableWindow(m_bChkFilterActive);
    GetDlgItem(IDC_CHECK_SET_MINI_FILTER_EX)->EnableWindow(m_bChkFilterActive);
}

void CDlgVcaFaceSnapEx::SaveParam()
{
    char  szListStr[128] = { 0 };

    for (int i = 0; i < m_dwTerminalNo; i++)
    {
        m_lstFaceSnapEx.GetItemText(m_iLastItem, 4, szListStr, 128);
        m_struBatchFaceSnapCfg[i].bySnapTime = atoi(szListStr);
        m_lstFaceSnapEx.GetItemText(m_iLastItem, 5, szListStr, 128);
        m_struBatchFaceSnapCfg[i].bySnapInterval = atoi(szListStr);
        m_lstFaceSnapEx.GetItemText(m_iLastItem, 6, szListStr, 128);
        m_struBatchFaceSnapCfg[i].bySnapThreshold = atoi(szListStr);
        m_lstFaceSnapEx.GetItemText(m_iLastItem, 7, szListStr, 128);
        m_struBatchFaceSnapCfg[i].byGenerateRate = atoi(szListStr);
        m_lstFaceSnapEx.GetItemText(m_iLastItem, 8, szListStr, 128);
        m_struBatchFaceSnapCfg[i].bySensitive = atoi(szListStr);
        m_lstFaceSnapEx.GetItemText(m_iLastItem, 9, szListStr, 128);
        m_struBatchFaceSnapCfg[i].byReferenceBright = atoi(szListStr);

        m_lstFaceSnapEx.GetItemText(m_iLastItem, 10, szListStr, 128);
        if (0 == strcmp(szListStr, "目标消失后报警") || 0 == strcmp(szListStr, "alarm after disapper"))
        {
            m_struFaceSnapCfg.byMatchType = 0;
        }
        else if (0 == strcmp(szListStr, "实时报警") || 0 == strcmp(szListStr, "alarm"))
        {
            m_struFaceSnapCfg.byMatchType = 1;
        }

        m_lstFaceSnapEx.GetItemText(m_iLastItem, 11, szListStr, 128);
        m_struFaceSnapCfg.byMatchThreshold = atoi(szListStr);

        m_lstFaceSnapEx.GetItemText(m_iLastItem, 12, szListStr, 128);
        if (0 == strcmp(szListStr, "CIF") || 0 == strcmp(szListStr, "CIF"))
        {
            m_struFaceSnapCfg.struPictureParam.wPicSize = 0;
        }
        else if (0 == strcmp(szListStr, "QCIF") || 0 == strcmp(szListStr, "QCIF"))
        {
            m_struFaceSnapCfg.struPictureParam.wPicSize = 1;
        }
        else if (0 == strcmp(szListStr, "D1") || 0 == strcmp(szListStr, "D1"))
        {
            m_struFaceSnapCfg.struPictureParam.wPicSize = 2;
        }
        else if (0 == strcmp(szListStr, "UXG") || 0 == strcmp(szListStr, "UXG"))
        {
            m_struFaceSnapCfg.struPictureParam.wPicSize = 3;
        }
        else if (0 == strcmp(szListStr, "SVGA") || 0 == strcmp(szListStr, "SVGA"))
        {
            m_struFaceSnapCfg.struPictureParam.wPicSize = 4;
        }
        else if (0 == strcmp(szListStr, "HD720p") || 0 == strcmp(szListStr, "HD720p"))
        {
            m_struFaceSnapCfg.struPictureParam.wPicSize = 5;
        }
        else if (0 == strcmp(szListStr, "VGA") || 0 == strcmp(szListStr, "VGA"))
        {
            m_struFaceSnapCfg.struPictureParam.wPicSize = 6;
        }

        m_lstFaceSnapEx.GetItemText(m_iLastItem, 13, szListStr, 128);
        if (0 == strcmp(szListStr, "最好") || 0 == strcmp(szListStr, "Best"))
        {
            m_struFaceSnapCfg.struPictureParam.wPicQuality = 0;
        }
        else if (0 == strcmp(szListStr, "较好") || 0 == strcmp(szListStr, "Better"))
        {
            m_struFaceSnapCfg.struPictureParam.wPicQuality = 1;
        }
        else if (0 == strcmp(szListStr, "一般") || 0 == strcmp(szListStr, "Good"))
        {
            m_struFaceSnapCfg.struPictureParam.wPicQuality = 2;
        }
    }
   

}

void CDlgVcaFaceSnapEx::OnNMClickListFacesnapEx(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

    m_iLastItem = pNMItemActivate->iItem;
    m_iSubItem = pNMItemActivate->iSubItem;
    m_bSelectItem = TRUE;

    *pResult = 0;
}


void CDlgVcaFaceSnapEx::OnNMDblclkListFacesnapEx(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    
    char szStr[128] = { 0 };

    CRect  EditRect;
    m_iItem = pNMItemActivate->iItem;
    m_iSubItem = pNMItemActivate->iSubItem;

    m_iRowCount = m_dwTerminalNo;

    if (m_iItem == -1)
    {
        return;
    }
    switch (m_iSubItem)
    {
    case 0:
    case 1:  //场景号
    case 2:  //通道号        
    case 3:  //状态
        break;

    case 4:  //抓拍次数
    case 5: //抓拍间隔
    case 6:
    case 7:
    case 8:
    case 9:  //参考亮度
    case 11: //对比阈值
        if (m_iItem < m_iRowCount)
        {
            m_lstFaceSnapEx.GetSubItemRect(m_iItem, m_iSubItem, LVIR_LABEL, EditRect);
            m_editTextBox.SetParent(&m_lstFaceSnapEx); //将list control设置为父窗口,生成的Edit才能正确定位

            EditRect.SetRect(EditRect.left, EditRect.top, EditRect.left + m_lstFaceSnapEx.GetColumnWidth(m_iSubItem), EditRect.bottom);

            //将选中的list控件中的内容copy到edit控件中
            CString strItem = m_lstFaceSnapEx.GetItemText(m_iItem, m_iSubItem);
            m_editTextBox.MoveWindow(&EditRect);
            m_editTextBox.SetWindowText(strItem);
            m_editTextBox.SetFocus();//设置为焦点
            m_editTextBox.SetSel(0, -1);  //0,-1表示单元格内容全选中
        }
        break;
    case 10:  //报警模式
        if (m_iItem < m_iRowCount)
        {
            m_comboBox.ResetContent();
            g_StringLanType(szStr, "目标消失后报警", "after gaol disapper");
            m_comboBox.InsertString(0, szStr);
            g_StringLanType(szStr, "实时报警", "now");
            m_comboBox.InsertString(1, szStr);
            m_comboBox.SetCurSel(0);

            m_lstFaceSnapEx.GetSubItemRect(m_iItem, m_iSubItem, LVIR_LABEL, EditRect);
            m_comboBox.SetParent(&m_lstFaceSnapEx); //将list control设置为父窗口,生成的ComboBox才能正确定位

            EditRect.SetRect(EditRect.left, EditRect.top, EditRect.left + m_lstFaceSnapEx.GetColumnWidth(m_iSubItem), EditRect.bottom);

            //将选中的list控件中的内容copy到edit控件中
            CString strItem = m_lstFaceSnapEx.GetItemText(m_iItem, m_iSubItem);
            m_comboBox.MoveWindow(&EditRect);
            m_comboBox.SetWindowText(strItem);
            m_comboBox.SetFocus();//设置为焦点
        }
        break;    
    case 12://图片分辨率
        if (m_iItem < m_iRowCount)
        {
            m_comboBox.ResetContent();
            g_StringLanType(szStr, "CIF", "CIF");
            m_comboBox.InsertString(0, szStr);
            g_StringLanType(szStr, "QCIF", "QCIF");
            m_comboBox.InsertString(1, szStr);
            g_StringLanType(szStr, "D1", "D1");
            m_comboBox.InsertString(2, szStr);
            g_StringLanType(szStr, "UXG", "UXG");
            m_comboBox.InsertString(3, szStr);
            g_StringLanType(szStr, "SVGA", "SVGA");
            m_comboBox.InsertString(4, szStr);
            g_StringLanType(szStr, "HD720p", "HD720p");
            m_comboBox.InsertString(5, szStr);
            g_StringLanType(szStr, "VGA", "VGA");
            m_comboBox.InsertString(6, szStr);
            m_comboBox.SetCurSel(0);

            m_lstFaceSnapEx.GetSubItemRect(m_iItem, m_iSubItem, LVIR_LABEL, EditRect);
            m_comboBox.SetParent(&m_lstFaceSnapEx); //将list control设置为父窗口,生成的ComboBox才能正确定位

            EditRect.SetRect(EditRect.left, EditRect.top, EditRect.left + m_lstFaceSnapEx.GetColumnWidth(m_iSubItem), EditRect.bottom);

            //将选中的list控件中的内容copy到edit控件中
            CString strItem = m_lstFaceSnapEx.GetItemText(m_iItem, m_iSubItem);
            m_comboBox.MoveWindow(&EditRect);
            m_comboBox.SetWindowText(strItem);
            m_comboBox.SetFocus();//设置为焦点
        }
        break;
    case 13://图片质量
        if (m_iItem < m_iRowCount)
        {
            m_comboBox.ResetContent();
            g_StringLanType(szStr, "最好", "Best");
            m_comboBox.InsertString(0, szStr);
            g_StringLanType(szStr, "较好", "Better");
            m_comboBox.InsertString(1, szStr);
            g_StringLanType(szStr, "一般", "Good");
            m_comboBox.InsertString(2, szStr);
            m_comboBox.SetCurSel(0);

            m_lstFaceSnapEx.GetSubItemRect(m_iItem, m_iSubItem, LVIR_LABEL, EditRect);
            m_comboBox.SetParent(&m_lstFaceSnapEx); //将list control设置为父窗口,生成的ComboBox才能正确定位

            EditRect.SetRect(EditRect.left, EditRect.top, EditRect.left + m_lstFaceSnapEx.GetColumnWidth(m_iSubItem), EditRect.bottom);

            //将选中的list控件中的内容copy到edit控件中
            CString strItem = m_lstFaceSnapEx.GetItemText(m_iItem, m_iSubItem);
            m_comboBox.MoveWindow(&EditRect);
            m_comboBox.SetWindowText(strItem);
            m_comboBox.SetFocus();//设置为焦点
        }
        break;
        //     case 14:
        //     case 15:
        //     case 16:
        //     case 17:
        //     case 18:
        //     case 19:
        //     case 20:
    default:
        break;
    }

    *pResult = 0;
}



void CDlgVcaFaceSnapEx::OnEnKillfocusEditTextBox()
{
    CString  csEditStr;
    char  szListStr[128] = { 0 };
    m_lstFaceSnapEx.GetItemText(m_iItem, m_iSubItem, szListStr, 128);
    m_editTextBox.GetWindowText(csEditStr);
    if (csEditStr.Compare(szListStr))
    {
        m_lstFaceSnapEx.SetItemText(m_iItem, m_iSubItem, csEditStr);
        m_iLastItem = m_iItem;
        SaveParam();
    }
    //m_editTextBox.ShowWindow(SW_HIDE);
}

void CDlgVcaFaceSnapEx::OnCbnKillfocusComboBox()
{
    CString  csComboBoxStr;
    char  szListStr[128] = { 0 };
    m_lstFaceSnapEx.GetItemText(m_iItem, m_iSubItem, szListStr, 128);
    m_comboBox.GetWindowText(csComboBoxStr);
    if (csComboBoxStr.Compare(szListStr))
    {
        m_comboBox.SetCurSel(m_comboBox.FindString(0, szListStr));
        m_lstFaceSnapEx.SetItemText(m_iItem, m_iSubItem, csComboBoxStr);
        m_iLastItem = m_iItem;
        SaveParam();
    }
    //m_comboBox.ShowWindow(SW_HIDE);
}
