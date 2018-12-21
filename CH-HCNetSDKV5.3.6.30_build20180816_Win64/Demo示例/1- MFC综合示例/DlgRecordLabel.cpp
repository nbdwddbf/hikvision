// DlgRecordLabel.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordLabel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordLabel dialog

DWORD  GetRecordLabelThread(LPVOID pParam)
{
    CDlgRecordLabel *pRecordLabel = (CDlgRecordLabel*)pParam;

    NET_DVR_FINDLABEL_DATA struFindData = {0};
    long nStatus = -1; 
    char szLan[128] = {0};

    pRecordLabel->m_listRecordLabel.DeleteAllItems();

    int nItemIndex = 0;
    BOOL bLoop = TRUE;
    while (bLoop)
    {
        nStatus = NET_DVR_FindNextLabel(pRecordLabel->m_lFindHandle, &struFindData);
        CString str = "";
          
        switch (nStatus)
        {
        case -1:
            g_StringLanType(szLan, "查找失败", "Fail to search");
            str = szLan;
            bLoop = FALSE;
        	break;
        case NET_DVR_FILE_SUCCESS: // 处理数据
            sprintf(szLan, "%d", nItemIndex+1);
            pRecordLabel->m_listRecordLabel.InsertItem(nItemIndex, szLan, 0);

            sprintf(szLan, "%04d%02d%02d%02d%02d%02d", struFindData.struTimeLabel.dwYear, 
                struFindData.struTimeLabel.dwMonth, struFindData.struTimeLabel.dwDay,
                struFindData.struTimeLabel.dwHour, struFindData.struTimeLabel.dwMinute, 
                struFindData.struTimeLabel.dwSecond);
            pRecordLabel->m_listRecordLabel.SetItemText(nItemIndex, 1, szLan);

            strncpy(szLan, (char *)struFindData.sLabelName, sizeof(szLan));
            pRecordLabel->m_listRecordLabel.SetItemText(nItemIndex, 2, szLan);

            strncpy(szLan, (char *)struFindData.struLabelIdentify.sLabelIdentify, sizeof(struFindData.struLabelIdentify.sLabelIdentify));
            pRecordLabel->m_listRecordLabel.SetItemText(nItemIndex, 3, szLan);

            nItemIndex++;
            break;
        case NET_DVR_ISFINDING:
            g_StringLanType(szLan, "正在查找", "searching");
            str = szLan;
            break;
        case NET_DVR_NOMOREFILE:
            g_StringLanType(szLan, "查找完成", "search end");
            str = szLan;
            bLoop = FALSE;
            AfxMessageBox(szLan);
            break;
        case NET_DVR_FILE_EXCEPTION:
            g_StringLanType(szLan, "查找文件时异常", "search exception");
            str = szLan;
            bLoop = FALSE;
            break;
        case NET_DVR_FILE_NOFIND:
            g_StringLanType(szLan, "没有查找到文件", "search nothing");
            str = szLan;
            bLoop = FALSE;
            AfxMessageBox(szLan);
            break;
        default:
            g_StringLanType(szLan, "查找错误", "search error");
            str = szLan;
            break;
        }

        pRecordLabel->GetDlgItem(IDC_STATIC_LABEL_SEARCH_STATE)->SetWindowText(str);
    }

    if (!NET_DVR_StopFindLabel(pRecordLabel->m_lFindHandle))
    {
        g_pMainDlg->AddLog(pRecordLabel->m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopFindLabel");
        g_StringLanType(szLan, "停止搜索失败", "Failed to stop the searching");
        AfxMessageBox(szLan);
    }
	else
	{
		pRecordLabel->GetDlgItem(IDC_STATIC_LABEL_SEARCH_STATE)->ShowWindow(SW_HIDE);	
	}
    return 1;
}

CDlgRecordLabel::CDlgRecordLabel(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecordLabel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRecordLabel)
	m_ctDateStart = 0;
	m_ctDateStop = 0;
	m_ctTimeStart = 0;
	m_ctTimeStop = 0;
	m_csRecordName = _T("");
	m_csDstLabelName = _T("");
	m_bDrawFrame = FALSE;
	//}}AFX_DATA_INIT
    m_lChannel = -1;
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_lFindHandle = -1;
    m_dwChanneNum = 0;
    m_hFindThread = NULL;
    memset(&m_struFindLabel, 0, sizeof(m_struFindLabel));
    memset(&m_struRecordLabel, 0, sizeof(m_struRecordLabel));
    memset(&m_struLabelIdentify, 0, sizeof(m_struLabelIdentify));
    memset(&m_struDelLabelParam, 0, sizeof(m_struDelLabelParam));
}


void CDlgRecordLabel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecordLabel)
	DDX_Control(pDX, IDC_STATIC_LABEL_SEARCH_STATE, m_staticSearchState);
	DDX_Control(pDX, IDC_LIST_RECORD_LABEL, m_listRecordLabel);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comboChannel);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_REMOTE_DATE_START, m_ctDateStart);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_REMOTE_DATE_STOP, m_ctDateStop);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_REMOTE_TIME_START, m_ctTimeStart);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_REMOTE_TIME_STOP, m_ctTimeStop);
	DDX_Text(pDX, IDC_EDIT_RECORD_NAME, m_csRecordName);
	DDX_Text(pDX, IDC_EDIT_DST_LABEL_NAME, m_csDstLabelName);
	DDX_Check(pDX, IDC_CHECK_DRAW_FRAME, m_bDrawFrame);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRecordLabel, CDialog)
	//{{AFX_MSG_MAP(CDlgRecordLabel)
	ON_BN_CLICKED(IDC_BTN_SEARCH_RECORD, OnBtnSearchRecord)
	ON_BN_CLICKED(IDC_BTN_DEL_LABEL, OnBtnDelLabel)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnButtonModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordLabel message handlers


BOOL CDlgRecordLabel::OnInitDialog() 
{
	CDialog::OnInitDialog();
    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);

    InitWnd();
    UpdateData(FALSE);
 
    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRecordLabel::InitWnd()
{
	m_bDrawFrame = FALSE;
    InitTimeControl();
    InitListRecordLabel();
}

void CDlgRecordLabel::InitComboChannel()
{
    int i = 0;
    char szLan[128] = {0};
    m_comboChannel.ResetContent();
    
    for (i = 0; i < m_dwChanneNum; i++)
    {
        sprintf(szLan, "Channel %d", i +1);
        m_comboChannel.InsertString(i,szLan);
        m_comboChannel.SetItemData(i, i+1);
    }
}

void CDlgRecordLabel::InitTimeControl()
{
    CTime timeCur = CTime::GetCurrentTime();
    CTime timeStart(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),0,0,0);
    CTime timeStop(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),23,59,59);
    m_ctDateStart = timeStart;
    m_ctTimeStart = timeStart;
    m_ctDateStop = timeStop;
    m_ctTimeStop = timeStop;
}

void CDlgRecordLabel::InitListRecordLabel()
{
    int nIndex = 0;
    m_listRecordLabel.SetExtendedStyle(m_listRecordLabel.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
    char szLan[128] = {0};
    g_StringLanType(szLan, "序号","Index");
    m_listRecordLabel.InsertColumn(nIndex, szLan,LVCFMT_LEFT, 40, -1);
    nIndex++;

    g_StringLanType(szLan, "时间","Time");
    m_listRecordLabel.InsertColumn(nIndex, szLan,LVCFMT_LEFT, 100, -1);
    nIndex++;
    
    g_StringLanType(szLan, "名称","Name");
    m_listRecordLabel.InsertColumn(nIndex, szLan,LVCFMT_LEFT, 200, -1);
    nIndex++;
    
    g_StringLanType(szLan, "标识","Identify");
    m_listRecordLabel.InsertColumn(nIndex, szLan,LVCFMT_LEFT, 200, -1);
    nIndex++;
}
    
void CDlgRecordLabel::OnBtnSearchRecord() 
{
	UpdateData(TRUE);
    GetSearchParamFromWnd(m_struFindLabel);

    m_lFindHandle = NET_DVR_FindRecordLabel(m_lServerID, &m_struFindLabel);
    if (m_lFindHandle >= 0)
    {
		GetDlgItem(IDC_STATIC_LABEL_SEARCH_STATE)->ShowWindow(SW_SHOW);	
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_FindRecordLabel");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FindRecordLabel");
    }


    if (m_hFindThread == NULL)
    {
        m_hFindThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetRecordLabelThread),this,0,NULL);
    }
    
    if (m_hFindThread != NULL)
    {
        CloseHandle(m_hFindThread);
        m_hFindThread = NULL;
    }
}

void CDlgRecordLabel::GetSearchParamFromWnd(NET_DVR_FIND_LABEL &struFindLabel)
{
    //struFindLabel.lChannel = m_comboChannel.GetItemData(m_comboChannel.GetCurSel());
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
    struFindLabel.lChannel = g_struDeviceInfo[m_iDevIndex].pStruChanInfo[iChanIndex].iChannelNO;

    struFindLabel.struStartTime.dwYear = m_ctDateStart.GetYear();
    struFindLabel.struStartTime.dwMonth = m_ctDateStart.GetMonth();
    struFindLabel.struStartTime.dwDay = m_ctDateStart.GetDay();
    struFindLabel.struStartTime.dwHour = m_ctTimeStart.GetHour();
    struFindLabel.struStartTime.dwMinute = m_ctTimeStart.GetMinute();
    struFindLabel.struStartTime.dwSecond = m_ctTimeStart.GetSecond();

    struFindLabel.struStopTime.dwYear = m_ctDateStop.GetYear();
    struFindLabel.struStopTime.dwMonth = m_ctDateStop.GetMonth();
    struFindLabel.struStopTime.dwDay = m_ctDateStop.GetDay();
    struFindLabel.struStopTime.dwHour = m_ctTimeStop.GetHour();
    struFindLabel.struStopTime.dwMinute = m_ctTimeStop.GetMinute();
    struFindLabel.struStopTime.dwSecond = m_ctTimeStop.GetSecond();
    struFindLabel.byISO8601 = g_bISO8601;
    struFindLabel.cStartTimeDifferenceH = g_iHourDiffWithUTC;
    struFindLabel.cStartTimeDifferenceM = g_iMinDiffWithUTC;
    struFindLabel.cStopTimeDifferenceH = g_iHourDiffWithUTC;
    struFindLabel.cStopTimeDifferenceM = g_iMinDiffWithUTC;

	struFindLabel.byDrawFrame = m_bDrawFrame;

    strncpy((char*)struFindLabel.sLabelName, m_csRecordName.GetBuffer(0), sizeof(struFindLabel.sLabelName));
}


BOOL CDlgRecordLabel::DelRecordLabel(NET_DVR_DEL_LABEL_PARAM &struDelLabelParam)
{
    if (NET_DVR_DelRecordLabel(m_lServerID,  &struDelLabelParam))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DelRecordLabel");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DelRecordLabel");
        return FALSE;
    }
}

BOOL CDlgRecordLabel::GetDelRecordLabelFrmWnd(NET_DVR_DEL_LABEL_PARAM &struDelLabelParam)
{
	struDelLabelParam.byMode = 1;
	struDelLabelParam.wLabelNum = 0;
	char szLan[128] = {0};
	
	CString str;
	POSITION pos = m_listRecordLabel.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		g_StringLanType(szLan, "请选择列表中的标签", "Please select a label item");
		AfxMessageBox(szLan);
		return FALSE;
	}
	else
	{
		while (pos)
		{
			if(struDelLabelParam.wLabelNum == MAX_DEL_LABEL_IDENTIFY)
			{
				return TRUE;
			}
            int nItem = m_listRecordLabel.GetNextSelectedItem(pos);
            str = m_listRecordLabel.GetItemText(nItem, 3);     
			strncpy((char*)struDelLabelParam.struIndentify[struDelLabelParam.wLabelNum].sLabelIdentify, str.GetBuffer(0), LABEL_IDENTIFY_LEN);
            struDelLabelParam.wLabelNum ++; 
		}
	}
	
	return TRUE;
}

void CDlgRecordLabel::OnBtnDelLabel() 
{
    if(GetDelRecordLabelFrmWnd(m_struDelLabelParam))
	{
		char szLan[128] = {0};
		if (!DelRecordLabel(m_struDelLabelParam))
		{
			g_StringLanType(szLan, "删除录像标签失败", "Fail to delete record label");
			AfxMessageBox(szLan);
		}
	}
}

BOOL CDlgRecordLabel::CheckInitParam()
{
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    
    m_iDevIndex = iDeviceIndex;
    m_dwChanneNum = g_struDeviceInfo[iDeviceIndex].iDeviceChanNum;
    m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	
    InitComboChannel();
    m_comboChannel.SetCurSel(0);
	
    return TRUE; 
}

void CDlgRecordLabel::OnButtonModify() 
{
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_MOD_LABEL_PARAM struModifyPara = {0};
	
	CString str;
	POSITION pos = m_listRecordLabel.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		g_StringLanType(szLan, "请选择列表中的标签", "Please select a label item");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
        int nItem = m_listRecordLabel.GetNextSelectedItem(pos);
        str = m_listRecordLabel.GetItemText(nItem, 3);     
		strncpy((char*)struModifyPara.struIndentify.sLabelIdentify, str.GetBuffer(0), LABEL_IDENTIFY_LEN);
		strncpy((char*)struModifyPara.sLabelName, m_csDstLabelName.GetBuffer(0), LABEL_NAME_LEN);
    }
	
	if (NET_DVR_ModifyRecordLabel(m_lServerID,  &struModifyPara))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_ModifyRecordLabel");
        return;
    }
    else
    {
		g_StringLanType(szLan, "修改录像标签信息失败", "Fail to modify record label info");
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_ModifyRecordLabel");
        return;
    }
}
