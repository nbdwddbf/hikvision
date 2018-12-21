// DlgMCUAddConference.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMCUAddConference.h"
#include "./xml/XmlBase.h"
#include "InfoDiffusionParamsConvert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define CSTRING_TO_CHARS(str,sz) memcpy((sz),str.GetBuffer(str.GetLength()),str.GetLength())


/////////////////////////////////////////////////////////////////////////////
// CDlgMCUAddConference dialog

CDlgMCUAddConference::CDlgMCUAddConference(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMCUAddConference::IDD, pParent)
    , m_dwDuration(0)
    , m_szTimeType(_T(""))
{
	//{{AFX_DATA_INIT(CDlgMCUAddConference)
		// NOTE: the ClassWizard will add member initialization here
    //会议开始时间
    m_dwStartYear   = 2015;
    m_dwStartMonth  = 1;
    m_dwStartDay    = 1;
    m_dwStartHour   = 12;
    m_dwStartMinute = 0;

    m_dwEndYear   = 2015;
    m_dwEndMonth  = 1;
    m_dwEndDay    = 1;
    m_dwEndHour   = 12;
    m_dwEndMinute = 0;

    //m_dwMembTermNO = 0;

    m_bIsChairMan = FALSE;

    m_bConfTypeRegular  = TRUE;

    m_dwRepeatTime = 0;

    m_bEnableLoopTerm = TRUE;
    m_dwLoopTime = 10;
    //m_dwLoopTermID = 0;
    //m_dwLoopTermNO = 0;

    m_bEnableSoundPri = TRUE;
    m_dwSoundProWinNO = 1;

    m_dwWinTermWinNO = 0;
    //m_dwWinTermTermNO = 0;
    m_bFixed = FALSE;
    
    //MemberViewList
    m_dwMembViewMembNO = 0;
    m_dwMemberViewCount = 0;

    m_dwMemberCount     = 0;  //会议成员数目
    m_dwLoopTermCount   = 0;
    m_dwWinTermCount    = 0;


	memset(&m_struConf, 0, sizeof(m_struConf));



	//}}AFX_DATA_INIT
}


void CDlgMCUAddConference::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgMCUAddConference)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    DDX_Control(pDX, IDC_COM_AUTO_REMIND_TIME, m_comAutoRemindTime);
    DDX_Control(pDX, IDC_COM_SOUND_PST_TIME, m_comSoundPSTTime);
    DDX_Control(pDX, IDC_COM_REGULAR_TYPE, m_comRegularType);
    DDX_Control(pDX, IDC_COMB_WEEK_DATE, m_comWeekDate);
    DDX_Control(pDX, IDC_COM_MONTH_DATE, m_comMonthDate);
    DDX_Control(pDX, IDC_COM_WIN_MODE, m_comWinMode);
    DDX_Control(pDX, IDC_COM_VIEW_MODE, m_comViewMode);

    DDX_Control(pDX, IDC_EDT_LOOP_TIME, m_edtLoopTime);
    //DDX_Control(pDX, IDC_EDT_LOOP_TERM_ID,     m_edtLoopTermID);
    DDX_Control(pDX, IDC_EDT_LOOP_TREM_NO, m_edtLoopTermNO);

    DDX_Control(pDX, IDC_EDT_SOUND_PRO_WIN_NO, m_edtSoundProWinNO);
    DDX_Control(pDX, IDC_EDT_WIN_TERM_TERM_NO, m_edtWinTermTermNO);


    DDX_Control(pDX, IDC_BTN_ADD_MEMBER, m_btnAddMember);
    DDX_Control(pDX, IDC_BTN_ADD_TERMINAL, m_btnAddTerm);
    DDX_Control(pDX, IDC_BTN_ADD_WIN_TERM, m_btnAddWinTerm);
    DDX_Control(pDX, IDC_BTN_ADD_MEMBER_VIEW, m_btnMemberViewTerm);
    DDX_Control(pDX, IDC_CHK_LOOP_ENABLE, m_btnEnableLoopTerm);
    DDX_Control(pDX, IDC_CHK_SOUND_PRO_ENABLE, m_btnEnableSoundPro);
    DDX_Control(pDX, IDC_CHK_FIXED, m_comViewMode);//

    DDX_Text(pDX, IDC_COM_AUTO_REMIND_TIME, m_dwAutoRemindTime);
    DDX_Text(pDX, IDC_COM_SOUND_PST_TIME, m_dwSoundPSTTime);
    DDX_Text(pDX, IDC_COM_REGULAR_TYPE, m_strRegularType);
    DDX_Text(pDX, IDC_COMB_WEEK_DATE, m_strWeekDate);
    DDX_Text(pDX, IDC_COM_MONTH_DATE, m_dwMonthDate);
    DDX_Text(pDX, IDC_COM_WIN_MODE, m_strWinMode);
    DDX_Text(pDX, IDC_COM_VIEW_MODE, m_strViewMode);

    DDX_Text(pDX, IDC_EDT_MEMB_TERM_NO, m_csMembTermNO);
    DDX_Check(pDX, IDC_CHK_CHAIRMAN, m_bIsChairMan);
    DDX_Check(pDX, IDC_CHK_LOOP_ENABLE, m_bEnableLoopTerm);
    DDX_Check(pDX, IDC_CHK_SOUND_PRO_ENABLE, m_bEnableSoundPri);
    DDX_Check(pDX, IDC_CHK_FIXED, m_bFixed);

    DDX_Text(pDX, IDC_EDT_START_YEAR, m_dwStartYear);
    DDX_Text(pDX, IDC_EDT_SRATR_MONTH, m_dwStartMonth);
    DDX_Text(pDX, IDC_EDT_START_DAY, m_dwStartDay);
    DDX_Text(pDX, IDC_EDT_START_HOUR, m_dwStartHour);
    DDX_Text(pDX, IDC_EDT_START_MINUTE, m_dwStartMinute);

    DDX_Text(pDX, IDC_EDT_END_YEAR, m_dwEndYear);
    DDX_Text(pDX, IDC_EDT_END_MONTH, m_dwEndMonth);
    DDX_Text(pDX, IDC_EDT_END_DAY, m_dwEndDay);
    DDX_Text(pDX, IDC_EDT_END_HOUR, m_dwEndHour);
    DDX_Text(pDX, IDC_EDT_END_MINUTE, m_dwEndMinute);

    DDX_Text(pDX, IDC_EDT_CONF_TITLE, m_strConferTitle);
    DDX_Text(pDX, IDC_EDT_CONF_CONTENT, m_strConferContent);
    DDX_Text(pDX, IDC_EDT_NOTIFICATION, m_strNotification);

    DDX_Text(pDX, IDC_EDT_REPEAT_TIMES, m_dwRepeatTime);

    DDX_Text(pDX, IDC_EDT_LOOP_TIME, m_dwLoopTime);
    //DDX_Text(pDX, IDC_EDT_LOOP_TERM_ID, m_dwLoopTermID);
    DDX_Text(pDX, IDC_EDT_LOOP_TREM_NO, m_csLoopTermNO);
    DDX_Text(pDX, IDC_EDT_SOUND_PRO_WIN_NO, m_dwSoundProWinNO);

    DDX_Text(pDX, IDC_EDT_MEMBER_COUNT, m_dwMemberCount);

    DDX_Text(pDX, IDC_EDT_WIN_TERM_TERM_NO, m_csWinTermTermNO);
    DDX_Text(pDX, IDC_EDT_MEMB_VIEW_MEMB_NO, m_csMemberViewID);

    DDX_Text(pDX, IDC_EDT_CONF_ID, m_csConfID);

    DDX_Check(pDX, IDC_CHK_GLOB_ENABLE, m_bEnabled);

    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBOX_TIME_TYPE, m_cmbTimeType);
    DDX_Text(pDX, IDC_EDIT_TIME_DURATION, m_dwDuration);
    DDX_CBString(pDX, IDC_COMBOX_TIME_TYPE, m_szTimeType);
}


BEGIN_MESSAGE_MAP(CDlgMCUAddConference, CDialog)
	//{{AFX_MSG_MAP(CDlgMCUAddConference)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_RAD_DEFINITE, OnRadDefinite)
	ON_BN_CLICKED(IDC_RAD_TEMP, OnRadTemp)
	ON_BN_CLICKED(IDC_CHK_CHAIRMAN, OnChkChairman)
	ON_BN_CLICKED(IDC_BTN_ADD_MEMBER, OnBtnAddMember)
	ON_BN_CLICKED(IDC_CHK_LOOP_ENABLE, OnChkLoopEnable)
	ON_BN_CLICKED(IDC_BTN_ADD_TERMINAL, OnBtnAddTerminal)
	ON_BN_CLICKED(IDC_CHK_SOUND_PRO_ENABLE, OnChkSoundProEnable)
	ON_BN_CLICKED(IDC_CHK_FIXED, OnChkFixed)
	ON_BN_CLICKED(IDC_BTN_ADD_WIN_TERM, OnBtnAddWinTerm)
	ON_BN_CLICKED(IDC_BTN_ADD_MEMBER_VIEW, OnBtnAddMemberView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUAddConference message handlers


BOOL CDlgMCUAddConference::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_szRequestURL = new char[REQUEST_URL_LEN];  
    if (m_szRequestURL == NULL)
    {
        return FALSE;
    }
    memset(m_szRequestURL, '\0' , REQUEST_URL_LEN);
    m_szXMLResultBuf = new char[ISAPI_DATA_LEN];
    if (m_szXMLResultBuf == NULL)
    {
        return FALSE;
    }
    memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN);
    m_dwXMLResultBufLen = ISAPI_DATA_LEN;
    m_szXMLStatus = new char[ISAPI_STATUS_LEN];
    if (m_szXMLStatus == NULL)
    {
        return FALSE;
    }
    memset(m_szXMLStatus, '\0', ISAPI_STATUS_LEN);


    m_pListMember      = (CListCtrl*)GetDlgItem(IDC_LST_MEMBER_INFO);
    m_pListLoopTerm    = (CListCtrl*)GetDlgItem(IDC_LST_LOOP_TERM);
    m_pListWinTerm     = (CListCtrl*)GetDlgItem(IDC_LST_WIN_TERM);
    m_pListMemberView  = (CListCtrl*)GetDlgItem(IDC_LST_MEMBER_VIEW);


    UpdateData(FALSE);

    //Comb控件的初始化
    //5,10,15
    m_comAutoRemindTime.InsertString(0, _T("5"));
    m_comAutoRemindTime.InsertString(1, _T("10"));
    m_comAutoRemindTime.InsertString(1, _T("15"));
	m_comAutoRemindTime.SetCurSel(0);

    //5,10,15,20,30
    m_comSoundPSTTime.InsertString(0, _T("5"));
    m_comSoundPSTTime.InsertString(1, _T("10"));
    m_comSoundPSTTime.InsertString(2, _T("15"));
    m_comSoundPSTTime.InsertString(3, _T("20"));
    m_comSoundPSTTime.InsertString(3, _T("30"));
	m_comSoundPSTTime.SetCurSel(0);

    //daily,weekly,monthly
    m_comRegularType.InsertString(0, _T("daily"));
    m_comRegularType.InsertString(1, _T("weekly"));
    m_comRegularType.InsertString(2, _T("monthly"));
	m_comRegularType.SetCurSel(0);

    //Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday
    m_comWeekDate.InsertString(0, _T("Monday"));
    m_comWeekDate.InsertString(1, _T("Tuesday"));
    m_comWeekDate.InsertString(2, _T("Wednesday"));
    m_comWeekDate.InsertString(3, _T("Thursday"));
    m_comWeekDate.InsertString(4, _T("Friday"));
    m_comWeekDate.InsertString(5, _T("Saturday"));
    m_comWeekDate.InsertString(6, _T("Sunday"));
	m_comWeekDate.SetCurSel(0);

    //1-31
    m_comMonthDate.InsertString(0, _T("1"));
	m_comMonthDate.SetCurSel(0);

    //1*1,2*2,3*3,4*4,2*1,3*2,3*4,1+5,1+7,1+9,1+11,1+12
    m_comWinMode.InsertString(0, _T("1*1"));
    m_comWinMode.InsertString(1, _T("2*2"));
    m_comWinMode.InsertString(2, _T("3*3"));
    m_comWinMode.InsertString(3, _T("4*4"));
    m_comWinMode.InsertString(4, _T("2*1"));
    m_comWinMode.InsertString(5, _T("3*2"));
    m_comWinMode.InsertString(6, _T("3*4"));
    m_comWinMode.InsertString(7, _T("1+5"));
    m_comWinMode.InsertString(8, _T("1+7"));
    m_comWinMode.InsertString(9, _T("1+9"));
    m_comWinMode.InsertString(10, _T("1+11"));
    m_comWinMode.InsertString(11, _T("1+12"));
	m_comWinMode.SetCurSel(0);

    m_cmbTimeType.InsertString(0, _T("按时间会议"));
    m_cmbTimeType.InsertString(1, _T("及时会议"));
    m_cmbTimeType.SetCurSel(0);

    //singleMember,layout
    m_comViewMode.InsertString(0, _T("singleMember"));
    m_comViewMode.InsertString(1, _T("layout"));
	m_comViewMode.SetCurSel(0);

    ((CButton*)GetDlgItem(IDC_RAD_DEFINITE))->SetCheck(1);
    m_bConfTypeRegular = TRUE;

    ((CEdit*)GetDlgItem(IDC_EDT_MEMBER_COUNT))->EnableWindow(FALSE);


    LONG lStyle;
    lStyle = GetWindowLong(m_pListMember->m_hWnd, GWL_STYLE);//获取当前窗口style
    lStyle &= ~LVS_TYPEMASK; //清除显示方式位
    lStyle |= LVS_REPORT;    //设置style
    SetWindowLong(m_pListMember->m_hWnd, GWL_STYLE, lStyle);//设置style
    SetWindowLong(m_pListLoopTerm->m_hWnd, GWL_STYLE, lStyle);//设置style
    SetWindowLong(m_pListWinTerm->m_hWnd, GWL_STYLE, lStyle);//设置style
    SetWindowLong(m_pListMemberView->m_hWnd, GWL_STYLE, lStyle);//设置style
    
    DWORD dwStyle = m_pListMember->GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;    //网格线（只适用与report风格的listctrl）
    //dwStyle |= LVS_EX_CHECKBOXES;   //item前生成checkbox控件
    m_pListMember->SetExtendedStyle(dwStyle); //设置扩展风格
    m_pListLoopTerm->SetExtendedStyle(dwStyle); //设置扩展风格
    m_pListWinTerm->SetExtendedStyle(dwStyle); //设置扩展风格
    m_pListMemberView->SetExtendedStyle(dwStyle); //设置扩展风格

    m_pListMember->InsertColumn(0, "Index", LVCFMT_LEFT, 50);//插入列
    m_pListMember->InsertColumn(1, "TermNO.", LVCFMT_LEFT, 240);
    m_pListMember->InsertColumn(2, "主席", LVCFMT_LEFT, 50);

    m_pListLoopTerm->InsertColumn(0, "Index", LVCFMT_LEFT, 50);//插入列
    m_pListLoopTerm->InsertColumn(1, "TermNO.", LVCFMT_LEFT, 240);

    m_pListWinTerm->InsertColumn(0, "WinNO.", LVCFMT_LEFT, 50);
    m_pListWinTerm->InsertColumn(1, "TermNO.", LVCFMT_LEFT, 240);
    m_pListWinTerm->InsertColumn(2, "FIXED", LVCFMT_LEFT, 50);

    m_pListMemberView->InsertColumn(0, "Index", LVCFMT_LEFT, 50 );//插入列
    m_pListMemberView->InsertColumn(1, "ViewMode", LVCFMT_LEFT, 100);
    m_pListMemberView->InsertColumn(2, "终端ID", LVCFMT_LEFT, 240);

    return TRUE;
}

//添加会议
void CDlgMCUAddConference::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    memset(m_szRequestURL, '\0' ,REQUEST_URL_LEN);
    memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN);
    m_dwXMLResultBufLen = ISAPI_DATA_LEN;
	memset(m_szXMLStatus, '\0', sizeof(ISAPI_STATUS_LEN));

	//填充m_struConf
	CSTRING_TO_CHARS(m_strConferTitle, &(m_struConf.struBaseInfo.szConfName));

    if (strlen(m_struConf.struBaseInfo.szConfName) < 1)
    {
        MessageBox("请填写会议名称!");
        return;
    }
	sprintf(m_struConf.struBaseInfo.struConfTime.szStartTime, "%04d-%02d-%02dT%02d:%02d:%02dZ", m_dwStartYear, m_dwStartMonth, m_dwStartDay, m_dwStartHour, m_dwStartMinute, 0);
	sprintf(m_struConf.struBaseInfo.struConfTime.szEndTime,   "%04d-%02d-%02dT%02d:%02d:%02dZ", m_dwEndYear, m_dwEndMonth, m_dwEndDay, m_dwEndHour, m_dwEndMinute, 0);
	CSTRING_TO_CHARS(m_strConferContent, &(m_struConf.struBaseInfo.szConfContent));
	m_struConf.struBaseInfo.dwMemberNum = m_dwMemberCount;
    CSTRING_TO_CHARS(m_szTimeType,m_struConf.struBaseInfo.szTimeType);
    m_struConf.struBaseInfo.dwDuration = m_dwDuration;

	if (m_bConfTypeRegular)
	{
		sprintf((char*)&m_struConf.struBaseInfo.szConfType, "regular");
	}
	else
	{
		sprintf((char*)&m_struConf.struBaseInfo.szConfType, "temporary");
	}
	
	CSTRING_TO_CHARS(m_strRegularType, m_struConf.struBaseInfo.struRegular.szRegularType);
	CSTRING_TO_CHARS(m_strWeekDate, m_struConf.struBaseInfo.struRegular.szWeekDate);
	m_struConf.struBaseInfo.struRegular.dwMonthDate        = m_dwMonthDate;
	m_struConf.struBaseInfo.struRegular.dwRepeatTimes      = m_dwRepeatTime;

	CSTRING_TO_CHARS(m_strNotification, m_struConf.struBaseInfo.szNotification);
	m_struConf.struBaseInfo.dwAutoRemindTime = m_dwAutoRemindTime;
	m_struConf.struBaseInfo.dwTimeDelay = m_dwSoundPSTTime;

	CSTRING_TO_CHARS(m_strWinMode, m_struConf.struLayout.szWinMode);
	m_struConf.struLayout.bSoundIntensPriEnable  = m_bEnableSoundPri;
	m_struConf.struLayout.dwWinNO                = m_dwSoundProWinNO;
	m_struConf.struLayout.struLoop.bEnable       = m_bEnableLoopTerm;
	m_struConf.struLayout.struLoop.dwLoopInterval  = m_dwLoopTime;

    CSTRING_TO_CHARS(m_csConfID,m_struConf.szID);

	m_struConf.bEnabled = (int)m_bEnabled;

    if (m_struConf.struBaseInfo.dwMemberNum < 2 || m_struConf.struBaseInfo.dwMemberNum > 16)
    {
        MessageBox("会议成员数目为2-16!");
    }

    //填充并转换信息
    CXmlBase struXml;
	struXml.CreateRoot("Conference");
	struXml.SetAttribute("version", "2.0");
	struXml.SetAttribute("xmlns", "http://www.isapi.org/ver20/XMLSchema");

	char szTemp[256] = {0};

	ConvertSingleNodeData(m_struConf.szID, struXml, "id", NODE_ARRAY_TO_STRING, strlen(m_struConf.szID));

	ConvertSingleNodeData(&m_struConf.bEnabled, struXml, "enabled", NODE_BOOL_TO_STRING);

	if (struXml.AddNode("ConferenceBasicInfo"))
	{
		//会议Enabled
		ConvertSingleNodeData((char*)m_struConf.struBaseInfo.szConfName, struXml, "conferenceName", NODE_ARRAY_TO_STRING);
        ConvertSingleNodeData((char*)m_struConf.struBaseInfo.szTimeType, struXml, "conferenceTimeType", NODE_ARRAY_TO_STRING);
        if (strcmp(m_struConf.struBaseInfo.szTimeType, "byTime"))
        {
            //会议起始时间
            if (struXml.AddNode("ConferenceTime"))
            {
                //FMT 20140930T173008+08
                ConvertSingleNodeData(m_struConf.struBaseInfo.struConfTime.szStartTime, struXml, "startTime", NODE_ARRAY_TO_STRING, strlen(m_struConf.struBaseInfo.struConfTime.szStartTime));
                ConvertSingleNodeData(m_struConf.struBaseInfo.struConfTime.szEndTime, struXml, "endTime", NODE_ARRAY_TO_STRING, strlen(m_struConf.struBaseInfo.struConfTime.szEndTime));
                struXml.OutOfElem();
            }
        }
        else if (strcmp(m_struConf.struBaseInfo.szTimeType, "byNow"))
        {
            if (struXml.AddNode("ConferenceNow"))
            {
                ConvertSingleNodeData(&(m_struConf.struBaseInfo.dwDuration), struXml, "duration", NODE_INT_TO_STRING);
                struXml.OutOfElem();
            }
        }
		//会议内容
		ConvertSingleNodeData((char*)m_struConf.struBaseInfo.szConfContent, struXml, "conferenceContent", NODE_ARRAY_TO_STRING);
		//会议人数
		ConvertSingleNodeData(&(m_struConf.struBaseInfo.dwMemberNum), struXml, "memberNum", NODE_INT_TO_STRING);
		//MemberList
		if (struXml.AddNode("MemberList"))
		{
			for (int i = 0; i < (int)m_struConf.struBaseInfo.dwMemberNum; i++)
			{
				if (struXml.AddNode("Member"))
				{
					//ID
					ConvertSingleNodeData(&(m_struConf.struBaseInfo.lstMember[i].dwID), struXml, "id", NODE_INT_TO_STRING);
					//TermnalNO
					ConvertSingleNodeData(&(m_struConf.struBaseInfo.lstMember[i].szTermNO), struXml, "terminalNo", NODE_ARRAY_TO_STRING);
					//isChairman
					ConvertSingleNodeData((char*)&m_struConf.struBaseInfo.lstMember[i].szIsChairMan, struXml, "isChairman", NODE_ARRAY_TO_STRING);
					struXml.OutOfElem();
				}
			}
			struXml.OutOfElem();
		}
		//conferenceType
		ConvertSingleNodeData((char*)&m_struConf.struBaseInfo.szConfType, struXml, "conferenceType", NODE_ARRAY_TO_STRING);
		if (struXml.AddNode("Regular"))
		{
			//regularType
			ConvertSingleNodeData((char*)&m_struConf.struBaseInfo.struRegular.szRegularType, struXml, "regularType", NODE_ARRAY_TO_STRING);
            if (strcmp(m_struConf.struBaseInfo.struRegular.szRegularType, "daily") == 0)
            {
                
                     
            }
            else if (strcmp(m_struConf.struBaseInfo.struRegular.szRegularType, "weekly") == 0)
            {
                //weekDate
                ConvertSingleNodeData((char*)&m_struConf.struBaseInfo.struRegular.szWeekDate, struXml, "weekDate", NODE_ARRAY_TO_STRING);
            }
            else if (strcmp(m_struConf.struBaseInfo.struRegular.szRegularType, "monthly") == 0)
            {
                //monthDate
                ConvertSingleNodeData(&(m_struConf.struBaseInfo.struRegular.dwMonthDate), struXml, "monthDate", NODE_INT_TO_STRING);
            }

            //repeatTimes
			ConvertSingleNodeData(&(m_struConf.struBaseInfo.struRegular.dwRepeatTimes), struXml, "repeatTimes", NODE_INT_TO_STRING);
			
			struXml.OutOfElem();
		}
		//notification
		ConvertSingleNodeData((char*)m_struConf.struBaseInfo.szNotification, struXml, "notification", NODE_ARRAY_TO_STRING);
		//autoRemindTime
		ConvertSingleNodeData(&(m_struConf.struBaseInfo.dwAutoRemindTime), struXml, "autoRemindTime", NODE_INT_TO_STRING);
		if (struXml.AddNode("SoundIntensityPriority"))
		{
			//timeDelay
			ConvertSingleNodeData(&(m_struConf.struBaseInfo.dwTimeDelay), struXml, "timeDelay", NODE_INT_TO_STRING);
			struXml.OutOfElem();
		}
		struXml.OutOfElem();

	}//end ConferenceBasicInfo

	if (struXml.AddNode("ConferenceLayout"))
	{
		//windowMode
		ConvertSingleNodeData((char*)&m_struConf.struLayout.szWinMode, struXml, "windowMode", NODE_ARRAY_TO_STRING);
		//SoundIntensityPriority
		if (struXml.AddNode("SoundIntensityPriority"))
		{
			//enabled
			ConvertSingleNodeData(&m_struConf.struLayout.bSoundIntensPriEnable, struXml, "enabled", NODE_BOOL_TO_STRING);
			//winNo
			ConvertSingleNodeData(&(m_struConf.struLayout.dwWinNO), struXml, "winNo", NODE_INT_TO_STRING);

			struXml.OutOfElem();
		}
		//WinTerminalList
		if (struXml.AddNode("WinTerminalList"))
		{
			for (int i = 0; i < (int)m_dwWinTermCount; i++)
			{
				//WinTerminal
				if(struXml.AddNode("WinTerminal"))
				{
					//winNo
					ConvertSingleNodeData(&(m_struConf.struLayout.lstWinTerm[i].dwWinNO), struXml, "winNo", NODE_INT_TO_STRING);
					//terminalNo
					ConvertSingleNodeData(&(m_struConf.struLayout.lstWinTerm[i].szTermNO), struXml, "terminalNo", NODE_ARRAY_TO_STRING);
					//fixed
					ConvertSingleNodeData(&(m_struConf.struLayout.lstWinTerm[i].bFixed), struXml, "fixed", NODE_BOOL_TO_STRING);
					struXml.OutOfElem();	
				}
			}
			struXml.OutOfElem();
		}
		//Loop
		if (struXml.AddNode("Loop"))
		{
			//enabled
			ConvertSingleNodeData(&m_struConf.struLayout.struLoop.bEnable, struXml, "enabled", NODE_BOOL_TO_STRING);
			//winNo
			ConvertSingleNodeData(&(m_struConf.struLayout.struLoop.dwLoopInterval), struXml, "loopInterval", NODE_INT_TO_STRING);
			//LoopTerminalList
			if (struXml.AddNode("LoopTerminalList"))
			{
				for (int i = 0; i < (int)m_dwLoopTermCount; i++)
				{
					//LoopTerminal
					if (struXml.AddNode("LoopTerminal"))
					{
						//id
						ConvertSingleNodeData(&(m_struConf.struLayout.struLoop.lstLoopTerm[i].dwID), struXml, "id", NODE_INT_TO_STRING);
						//terminalNo
						ConvertSingleNodeData(&(m_struConf.struLayout.struLoop.lstLoopTerm[i].szTermNO), struXml, "terminalNo", NODE_ARRAY_TO_STRING);
						struXml.OutOfElem();
					}
				}
				struXml.OutOfElem();
			}
			struXml.OutOfElem();
		}
		struXml.OutOfElem();
	}//end ConferenceLayout

	//MemberViewList
	if (struXml.AddNode("MemberViewList"))
	{
		//MemberView
		for (int i = 0; i < (int)m_dwMemberViewCount; i++)
		{
			if (struXml.AddNode("MemberView"))
			{
				//id
				ConvertSingleNodeData(&(m_struConf.lstMembView[i].szID), struXml, "id", NODE_ARRAY_TO_STRING);
				//viewMode
				ConvertSingleNodeData((char*)&m_struConf.lstMembView[i].szViewMode, struXml, "viewMode", NODE_ARRAY_TO_STRING);
                if (strcmp(m_struConf.lstMembView[i].szViewMode, "layout") != 0)
                {
                    //memberNo
				    ConvertSingleNodeData(&(m_struConf.lstMembView[i].szTermNO), struXml, "terminalNo", NODE_ARRAY_TO_STRING);
                }
				struXml.OutOfElem();
			}	
		}
		struXml.OutOfElem();
	}// end MemberViewList

	//将XML转存到buffer中
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;

	if (!PrintXmlToNewBuffer(&m_pXMLParamBuf, m_dwXMLParamBufLen, struXml))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "PrintXmlToNewBuffer Error");
		return;
	}

	//Debug
	//CString strMsg = m_pXMLParamBuf;
	//MessageBox(strMsg);
	
	//lpInputParam->lpRequestUrl为：POST /ISAPI/VCS/conferences；
	//lpInputParam->lpInBuffer为Conference；
	//lpOutputParam->lpOutBuffer为NULL；
	//lpOutputParam->lpStatusBuffer为ResponseStatus

	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput  = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);	
	sprintf((char*)m_szRequestURL, "POST /ISAPI/VCS/conferences");
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer      = m_pXMLParamBuf;
	struXMLCfgInput.dwInBufferSize  = m_dwXMLParamBufLen;

	NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = {0};
	struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
	struXMLCfgOutput.lpOutBuffer    = NULL;
	struXMLCfgOutput.lpStatusBuffer = m_szXMLStatus;
	struXMLCfgOutput.dwStatusSize   = ISAPI_STATUS_LEN;

	LPNET_DVR_XML_CONFIG_OUTPUT lpXMLCfgOutput = &struXMLCfgOutput;

	if (NET_DVR_STDXMLConfig(m_lUserID, &struXMLCfgInput, lpXMLCfgOutput))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");			
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
    }
	
	//状态处理
	m_csConfID = ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);

    delete[] m_pXMLParamBuf;
    m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;

	UpdateData(FALSE);
}

CString CDlgMCUAddConference::ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf)
{
    DWORD dwStatusCode = 0;
    char  szStatusInfo  [256] = {0};
    char  szStatusString[128] = {0};
    char  szID          [256] = {0};
    
    CString csRet;
    
    CXmlBase struXmlStatus;
    if (struXmlStatus.Parse(lpStatusBuf))
    {
        if (struXmlStatus.FindElem("ResponseStatus") && struXmlStatus.IntoElem())
        {
            if (struXmlStatus.FindElem("statusCode"))
            {
                ConvertSingleNodeData(&dwStatusCode, struXmlStatus, "statusCode", NODE_STRING_TO_INT);
                
                sprintf((char*)szStatusInfo, "%s", GetStatusCodeInfo(dwStatusCode));
                if (dwStatusCode == 0 || dwStatusCode == 1)
                {
                    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szStatusInfo);
                }
                else
                {
                    if (struXmlStatus.FindElem("statusString"))
                    {
                        ConvertSingleNodeData((char*)&szStatusString, struXmlStatus, "statusString", NODE_STRING_TO_ARRAY, 128);
                        sprintf((char*)szStatusInfo, "StatusString: %s", szStatusString);
                        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szStatusInfo);
                        struXmlStatus.OutOfElem();
                    }	
                }
                if (struXmlStatus.FindElem("ID"))
                {
                    ConvertSingleNodeData(&szID, struXmlStatus, "ID", NODE_STRING_TO_ARRAY, 256);
                    csRet = szID;
                }	
            }
        }
    }
    else
    {
        //g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Status XML Parse Error");
    }
    return csRet;
}

void CDlgMCUAddConference::OnRadDefinite() 
{
	// TODO: Add your control notification handler code here
    m_bConfTypeRegular = TRUE;
}

void CDlgMCUAddConference::OnRadTemp() 
{
	// TODO: Add your control notification handler code here
	m_bConfTypeRegular = FALSE; 
}

void CDlgMCUAddConference::OnChkChairman() 
{
	// TODO: Add your control notification handler code here
}


void CDlgMCUAddConference::OnChkLoopEnable() 
{
	// TODO: Add your control notification handler code here
    if (m_btnEnableLoopTerm.GetCheck())
    {
        m_edtLoopTime.EnableWindow(TRUE);
    }
    else
    {
        m_edtLoopTime.EnableWindow(FALSE);
    }	
}


void CDlgMCUAddConference::OnChkSoundProEnable() 
{
	// TODO: Add your control notification handler code here
    if (m_btnEnableSoundPro.GetCheck())
    {
        m_edtSoundProWinNO.EnableWindow(TRUE);
    }
    else
    {
        m_edtSoundProWinNO.EnableWindow(FALSE);
    }
}

void CDlgMCUAddConference::OnChkFixed() 
{
	// TODO: Add your control notification handler code here	
}

void CDlgMCUAddConference::OnBtnAddMember() 
{
    // TODO: Add your control notification handler code here
    
    UpdateData(TRUE);
    
    m_dwMemberCount++;
    
    CString strChairMan; 
    if (m_bIsChairMan)
    {
        strChairMan = "Y";
    }
    else
    {
        strChairMan = "--";
    }
    
    CString strMemberID;
    strMemberID.Format("%d", m_dwMemberCount);
    
    CString strTermNO;
    GetDlgItem(IDC_EDT_MEMB_TERM_NO)->GetWindowText(strTermNO);
    
    int nRow = m_pListMember->InsertItem(m_dwMemberCount-1, strMemberID);//插入行
    
    m_pListMember->SetItemText(nRow, 1, strTermNO);//设置数据
    m_pListMember->SetItemText(nRow, 2, strChairMan);//设置数据
    
    //创建MemberInfo
    Member  struMemberInfo = {0};
    struMemberInfo.dwID     = m_dwMemberCount;
	CSTRING_TO_CHARS(m_csMembTermNO, struMemberInfo.szTermNO);
    //struMemberInfo.dwTermNO = m_dwMembTermNO;
	if (m_bIsChairMan)
	{
		sprintf((char*)&struMemberInfo.szIsChairMan, "true");
	}
	else
	{
		sprintf((char*)&struMemberInfo.szIsChairMan, "false");
	}

	m_struConf.struBaseInfo.lstMember[m_dwMemberCount-1] = struMemberInfo;

    m_csMembTermNO = _T("");
    m_bIsChairMan = FALSE;
    
    UpdateData(FALSE);	
}

void CDlgMCUAddConference::OnBtnAddWinTerm() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    m_dwWinTermCount++;


    CString strFixed; 
    if (m_bFixed)
    {
        strFixed = "Y";
    }
    else
    {
        strFixed = "--";
    }

    CString strWinTermWinNO;
    strWinTermWinNO.Format("%d", m_dwWinTermCount);

    int nRow = m_pListWinTerm->InsertItem(m_dwWinTermCount-1, strWinTermWinNO);//插入行
    m_pListWinTerm->SetItemText(nRow, 1, m_csWinTermTermNO);//设置数据
    m_pListWinTerm->SetItemText(nRow, 2, strFixed);//设置数据

    //创建WinTermInfo
    WinTerminal struWinTermInfo = {0};
    struWinTermInfo.dwWinNO     = m_dwWinTermCount;
	CSTRING_TO_CHARS(m_csWinTermTermNO, struWinTermInfo.szTermNO);
    struWinTermInfo.bFixed      = m_bFixed;

    m_struConf.struLayout.lstWinTerm[m_dwWinTermCount-1] = struWinTermInfo;

    m_bFixed = FALSE;
    m_csWinTermTermNO = _T("");

    UpdateData(FALSE);	
}


void CDlgMCUAddConference::OnBtnAddTerminal() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);

    m_dwLoopTermCount++;

    CString strIndex;
    strIndex.Format("%d", m_dwLoopTermCount);

    CString strTermNO;
    GetDlgItem(IDC_EDT_LOOP_TREM_NO)->GetWindowText(strTermNO);

    int nRow = m_pListLoopTerm->InsertItem(m_dwLoopTermCount-1, strIndex);//插入行
    m_pListLoopTerm->SetItemText(nRow, 1, strTermNO);//设置数据

    //创建LoopTermInfo
    LoopTerminal struLoopTermInfo = {0};
	struLoopTermInfo.dwID     = m_dwLoopTermCount;
    //struLoopTermInfo.dwTermNO     = m_dwLoopTermNO;
	CSTRING_TO_CHARS(m_csLoopTermNO,struLoopTermInfo.szTermNO);

	m_struConf.struLayout.struLoop.lstLoopTerm[m_dwLoopTermCount-1] = struLoopTermInfo;

    m_csLoopTermNO = _T("");
    UpdateData(FALSE);
}

void CDlgMCUAddConference::OnBtnAddMemberView() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    m_dwMemberViewCount++;
    CString strWinMode;
    GetDlgItem(IDC_COM_VIEW_MODE)->GetWindowText(strWinMode);

    CString strMembNO;
    strMembNO.Format("%d", m_dwMemberViewCount);
    
    int nRow = m_pListMemberView->InsertItem(m_dwMemberViewCount-1, strMembNO);//插入行
    m_pListMemberView->SetItemText(nRow, 1, strWinMode);//设置数据
    m_pListMemberView->SetItemText(nRow, 2, m_csMemberViewID);//设置数据

    //创建MemberViewInfo
    MemberView struMemberViewInfo = {0};
    
    CSTRING_TO_CHARS(m_csMemberViewID, struMemberViewInfo.szID);
    CSTRING_TO_CHARS(m_strViewMode, struMemberViewInfo.szViewMode);
    CSTRING_TO_CHARS(m_csMemberViewID, struMemberViewInfo.szTermNO);

	m_struConf.lstMembView[m_dwMemberViewCount-1] = struMemberViewInfo;

    m_csMemberViewID = _T("");

    UpdateData(FALSE);
}

