// DlgMCUSearchConference.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMCUSearchConference.h"
#include "InfoDiffusionParamsConvert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define CSTRING_TO_CHARS(str,sz) memcpy((sz),str.GetBuffer(str.GetLength()),str.GetLength())


//static char *gConfStatus[] = {"notYetStart" , "inProgress", "finished"};
//static char *gConfType[] = {"regular", "temporary"};

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUSearchConference dialog


CDlgMCUSearchConference::CDlgMCUSearchConference(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMCUSearchConference::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMCUSearchConference)
		// NOTE: the ClassWizard will add member initialization here
	//会议开始时间
    m_dwStartYear = 2015;
    m_dwStartMonth = 1;
    m_dwStartDay = 1;
    m_dwStartHour = 12;
    m_dwStartMinute = 0;
	
    //会议结束时间
    m_dwEndYear = 2015;
    m_dwEndMonth = 1;
    m_dwEndDay = 1;
    m_dwEndHour = 12;
    m_dwEndMinute = 0;
	
	//Ret会议开始时间
    m_dwStartYearRet = 0;
    m_dwStartMonthRet = 0;
    m_dwStartDayRet = 0;
    m_dwStartHourRet = 0;
    m_dwStartMinuteRet = 0;
	
    //Ret会议结束时间
    m_dwEndYearRet = 0;
    m_dwEndMonthRet = 0;
    m_dwEndDayRet = 0;
    m_dwEndHourRet = 0;
    m_dwEndMinuteRet = 0;
	
	m_dwCountRet  = 0;
	
	m_dwMaxCountRet = 32;
	m_dwCountStartRet = 0;

	m_dwMatchCount = 0;

	for (int i = 0; i < MAX_MATCH_COUNT; i++)
	{
		memset(&m_lstConfMatch[i], 0, sizeof(ConferenceMatchInfo));
	}

	memset(&m_struConfSearchDes, 0, sizeof(ConferenceSearchDes));

	//}}AFX_DATA_INIT
}


void CDlgMCUSearchConference::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMCUSearchConference)
		// NOTE: the ClassWizard will add DDX and DDV calls here

	DDX_Control(pDX, IDC_COM_CONF_TYPE,  m_comConfType);
	DDX_Control(pDX, IDC_COM_CONF_STATUS,  m_comConfStatus);

	//DDX_Control(pDX, IDC_COM_SEARCH_RET,  m_comSearchRet);
	//DDX_Control(pDX, IDC_COM_SEARCH_STATUS,  m_comSearchStatus);

	DDX_Control(pDX, IDC_COM_CONF_TYPE_RET,  m_comConfTypeRet);
	DDX_Control(pDX, IDC_COM_CONF_STATUS_RET,  m_comConfStatusRet);

    DDX_Text(pDX, IDC_COM_SEARCH_STATUS, m_strSearchStatusRet);

    DDX_Text(pDX, IDC_COM_CONF_TYPE_RET, m_strConfTypeRet);
	DDX_Text(pDX, IDC_COM_CONF_STATUS_RET, m_strConfStatusRet);

	DDX_Text(pDX, IDC_COM_SEARCH_RET,      m_strSearchRet);

    DDX_Text(pDX, IDC_COM_CONF_TYPE, m_strConfType);
	DDX_Text(pDX, IDC_COM_CONF_STATUS, m_strConfStatus);

	DDX_Text(pDX, IDC_COM_CONF_TYPE_RET, m_strConfTypeRet);

	DDX_Text(pDX, IDC_EDT_START_YEAR2,   m_dwStartYear);
    DDX_Text(pDX, IDC_EDT_START_MONTH2,  m_dwStartMonth);
    DDX_Text(pDX, IDC_EDT_START_DAY2,    m_dwStartDay);
    DDX_Text(pDX, IDC_EDT_START_HOUR2,   m_dwStartHour);
    DDX_Text(pDX, IDC_EDT_START_MINUTE2, m_dwStartMinute);

	DDX_Text(pDX, IDC_EDT_END_YEAR2,   m_dwEndYear);
    DDX_Text(pDX, IDC_EDT_END_MONTH2,  m_dwEndMonth);
    DDX_Text(pDX, IDC_EDT_END_DAY2,    m_dwEndDay);
    DDX_Text(pDX, IDC_EDT_END_HOUR2,   m_dwEndHour);
    DDX_Text(pDX, IDC_EDT_END_MINUTE2, m_dwEndMinute);

	DDX_Text(pDX, IDC_STA_START_YEAR_RET,   m_dwStartYearRet);
    DDX_Text(pDX, IDC_STA_START_MONTH_RET,  m_dwStartMonthRet);
    DDX_Text(pDX, IDC_STA_START_DAY_RET,    m_dwStartDayRet);
    DDX_Text(pDX, IDC_STA_START_HOUR_RET,   m_dwStartHourRet);
    DDX_Text(pDX, IDC_STA_START_MINUTE_RET, m_dwStartMinuteRet);
	
	DDX_Text(pDX, IDC_STA_END_YEAR_RET,   m_dwEndYearRet);
    DDX_Text(pDX, IDC_STA_END_MONTH_RET,  m_dwEndMonthRet);
    DDX_Text(pDX, IDC_STA_END_DAY_RET,    m_dwEndDayRet);
    DDX_Text(pDX, IDC_STA_END_HOUR_RET,   m_dwEndHourRet);
    DDX_Text(pDX, IDC_STA_END_MINUTE_RET, m_dwEndMinuteRet);

    


	DDX_Text(pDX, IDC_STA_COUNT_RET, m_dwCountRet);
	DDX_Text(pDX, IDC_EDT_MAX_COUNT_RET, m_dwMaxCountRet);
	DDX_Text(pDX, IDC_EDT_NUM_BEGIN_RET, m_dwCountStartRet);


    

	DDX_Text(pDX, IDC_EDT_SEARCH_ID, m_strSearchID);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMCUSearchConference, CDialog)
	//{{AFX_MSG_MAP(CDlgMCUSearchConference)
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
	ON_NOTIFY(NM_CLICK, IDC_LST_MATCH, OnClickList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUSearchConference message handlers


BOOL CDlgMCUSearchConference::OnInitDialog()
{
	CDialog::OnInitDialog();

    m_szRequestURL = new char[ISAPI_DATA_LEN];  
    if (m_szRequestURL == NULL)
    {
        return FALSE;
    }
    memset(m_szRequestURL, '\0' , ISAPI_DATA_LEN);

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

	m_pListConfInfoRet = (CListCtrl*)GetDlgItem(IDC_LST_MATCH);

	LONG lStyle;
    lStyle = GetWindowLong(m_pListConfInfoRet->m_hWnd, GWL_STYLE);//获取当前窗口style
    lStyle &= ~LVS_TYPEMASK; //清除显示方式位
    lStyle |= LVS_REPORT;    //设置style
    SetWindowLong(m_pListConfInfoRet->m_hWnd, GWL_STYLE, lStyle);//设置style
    SetWindowLong(m_pListConfInfoRet->m_hWnd, GWL_STYLE, lStyle);//设置style
    SetWindowLong(m_pListConfInfoRet->m_hWnd, GWL_STYLE, lStyle);//设置style
    SetWindowLong(m_pListConfInfoRet->m_hWnd, GWL_STYLE, lStyle);//设置style
    
    DWORD dwStyle = m_pListConfInfoRet->GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;    //网格线（只适用与report风格的listctrl）
    //dwStyle |= LVS_EX_CHECKBOXES;   //item前生成checkbox控件
    m_pListConfInfoRet->SetExtendedStyle(dwStyle); //设置扩展风格

	UpdateData(FALSE);

    m_pListConfInfoRet->InsertColumn(0, "Index", LVCFMT_LEFT, 50);//插入列
    m_pListConfInfoRet->InsertColumn(1, "会议ID.", LVCFMT_LEFT, 250);
    m_pListConfInfoRet->InsertColumn(2, "会议名称", LVCFMT_LEFT,100);


	m_comConfType.InsertString(0, _T("regular"));
	m_comConfType.InsertString(1, _T("temporary"));
	m_comConfType.SetCurSel(0);

	m_comConfStatus.InsertString(0, _T("notYetStart"));
	m_comConfStatus.InsertString(1, _T("inProgress"));
	m_comConfStatus.InsertString(2, _T("finished"));
	m_comConfStatus.SetCurSel(0);

    /*
	m_comSearchRet.InsertString(0, _T("false"));
	m_comSearchRet.InsertString(1, _T("true"));
	m_comSearchRet.SetCurSel(0);
    */

    /*
	m_comSearchStatus.InsertString(0, _T("OK"));
	m_comSearchStatus.InsertString(1, _T("FAILED"));
	m_comSearchStatus.InsertString(2, _T("MORE"));
	m_comSearchStatus.InsertString(3, _T("NO MATCH"));
	m_comSearchStatus.InsertString(4, _T("PARAM ERROR"));
	m_comSearchStatus.InsertString(5, _T("INVALID TIME"));
	m_comSearchStatus.InsertString(6, _T("TIMEOUT"));
	m_comSearchStatus.SetCurSel(0);
    */

	return TRUE;
}

void CDlgMCUSearchConference::OnBtnSearch() 
{
	// TODO: Add your control notification handler code here




	UpdateData(TRUE);

    m_pListConfInfoRet->DeleteAllItems();

	memset(m_szRequestURL, '\0' ,REQUEST_URL_LEN);
	memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN);
	m_dwXMLResultBufLen = ISAPI_DATA_LEN;
    memset(m_szXMLStatus, '\0', sizeof(ISAPI_STATUS_LEN));
    
	ConferenceMatchInfo struConfInfo = {0};

    memset(&m_struConfSearchDes, 0, sizeof(m_struConfSearchDes));

	//填充请求数据

    if (!GenerateGUID(m_struConfSearchDes.szSearchID, MAX_XML_ELEM_LEN))
    {
        MessageBox("生成UUID失败!");
        return;
    }

    m_strSearchID = m_struConfSearchDes.szSearchID;

	sprintf((char*)m_struConfSearchDes.struTimeSpain.szStartTime, "%04d-%02d-%02dT%02d:%02d:%02dZ", m_dwStartYear, m_dwStartMonth, m_dwStartDay, m_dwStartHour, m_dwStartMinute, 0);
	sprintf((char*)m_struConfSearchDes.struTimeSpain.szEndTime,   "%04d-%02d-%02dT%02d:%02d:%02dZ", m_dwEndYear, m_dwEndMonth, m_dwEndDay, m_dwEndHour, m_dwEndMinute, 0);
	
	CSTRING_TO_CHARS(m_strConfType, m_struConfSearchDes.szConfType);
	CSTRING_TO_CHARS(m_strConfStatus, m_struConfSearchDes.szConfState);

	m_struConfSearchDes.dwMaxResults = m_dwMaxCountRet;
	m_struConfSearchDes.dwSearchResultsPosition = m_dwCountStartRet;

	//生成XML数据流
	CXmlBase struXml;
	struXml.CreateRoot("ConferenceSearchDescription");
	struXml.SetAttribute("version", "2.0");
	struXml.SetAttribute("xmlns", "http://www.isapi.org/ver20/XMLSchema");

	ConvertSingleNodeData(&(m_struConfSearchDes.szSearchID), struXml, "searchID", NODE_ARRAY_TO_STRING);
	if (struXml.AddNode("TimeSpanList"))
	{
		if (struXml.AddNode("TimeSpan"))
		{
			ConvertSingleNodeData((char*)m_struConfSearchDes.struTimeSpain.szStartTime, struXml, "startTime", NODE_ARRAY_TO_STRING);
			ConvertSingleNodeData((char*)m_struConfSearchDes.struTimeSpain.szEndTime, struXml, "endTime", NODE_ARRAY_TO_STRING);
			struXml.OutOfElem();
		}
		struXml.OutOfElem();
	}
	ConvertSingleNodeData((char*)m_struConfSearchDes.szConfType, struXml, "conferenceType", NODE_ARRAY_TO_STRING);
	ConvertSingleNodeData((char*)m_struConfSearchDes.szConfState, struXml, "conferenceState", NODE_ARRAY_TO_STRING);
	ConvertSingleNodeData(&(m_struConfSearchDes.dwMaxResults), struXml, "maxResults", NODE_INT_TO_STRING);
	ConvertSingleNodeData(&(m_struConfSearchDes.dwSearchResultsPosition), struXml, "searchResultsPosition", NODE_INT_TO_STRING);

	//将XML转存到buffer中
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	
	if (!PrintXmlToNewBuffer(&m_pXMLParamBuf, m_dwXMLParamBufLen, struXml))
	{
		//g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "PrintXmlToNewBuffer Error");
        m_dwStartYearRet = 0;
        m_dwStartMonthRet = 0;
        m_dwStartDayRet = 0;
        m_dwStartHourRet = 0;
        m_dwStartMinuteRet = 0;
        
        //Ret会议结束时间
        m_dwEndYearRet = 0;
        m_dwEndMonthRet = 0;
        m_dwEndDayRet = 0;
        m_dwEndHourRet = 0;
        m_dwEndMinuteRet = 0;
        
	    UpdateData(FALSE);
		return;
	}
	
	//Debug
	//CString strMsg = m_pXMLParamBuf;
	//MessageBox(strMsg);

	//lpInputParam->lpRequestUrl为：GET /ISAPI/VCS/conferenceSearch；
	//lpInputParam->lpInBuffer为ConferenceSearchDescription；
	//lpOutputParam->lpOutBuffer为ConferenceSearchResult；
	//lpOutputParam->lpStatusBuffer为ResponseStatus，获取成功时不返回。

	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
	sprintf((char*)m_szRequestURL, "GET /ISAPI/VCS/conferenceSearch\r\n%s", m_pXMLParamBuf);
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer      = NULL;
	struXMLCfgInput.dwInBufferSize  = 0;
	
	NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = {0};
	struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
	struXMLCfgOutput.lpOutBuffer = (char*)m_szXMLResultBuf;
	struXMLCfgOutput.dwOutBufferSize = ISAPI_DATA_LEN;
	struXMLCfgOutput.lpStatusBuffer = (char*)m_szXMLStatus;
	struXMLCfgOutput.dwStatusSize = ISAPI_STATUS_LEN;

	LPNET_DVR_XML_CONFIG_OUTPUT lpXMLCfgOutput = &struXMLCfgOutput;

	if (NET_DVR_STDXMLConfig(m_lUserID, &struXMLCfgInput, lpXMLCfgOutput))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");			
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);
		
		delete[] m_pXMLParamBuf;
		m_pXMLParamBuf = NULL;
		m_dwXMLParamBufLen = 0;

        m_dwStartYearRet = 0;
        m_dwStartMonthRet = 0;
        m_dwStartDayRet = 0;
        m_dwStartHourRet = 0;
        m_dwStartMinuteRet = 0;
        
        //Ret会议结束时间
        m_dwEndYearRet = 0;
        m_dwEndMonthRet = 0;
        m_dwEndDayRet = 0;
        m_dwEndHourRet = 0;
        m_dwEndMinuteRet = 0;
        
	    UpdateData(FALSE);
		
		return;
    }
	
	//状态处理
	ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);
	
	{
        char szSearchID[MAX_XML_ELEM_LEN] = {0};
		BOOL  bResponseStatus = FALSE;
		char  szResponseStatusStrg[MAX_XML_ELEM_LEN] = {0};
		DWORD dwNumOfMatches = 0;

		//处理struXMLCfgOutput.lpOutBuffer
		CXmlBase struXmlResult;

        m_dwMatchCount = 0;

		if (struXmlResult.Parse((char*)struXMLCfgOutput.lpOutBuffer))
		{
			if (struXmlResult.FindElem("ConferenceSearchResult") && struXmlResult.IntoElem())
			{
				if (struXmlResult.FindElem("searchID"))
				{
					ConvertSingleNodeData(szSearchID, struXmlResult, "searchID", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
					m_strSearchID = szSearchID;
				}

				if (struXmlResult.FindElem("responseStatus"))
				{
					ConvertSingleNodeData(&bResponseStatus, struXmlResult, "responseStatus", NODE_STRING_TO_BOOL);
					if (bResponseStatus)
                    {
                        m_strSearchRet = _T("TRUE");
                    }
                    else
                    {
                        m_strSearchRet = _T("FALSE");
                    }
      
				}

				if (struXmlResult.FindElem("responseStatusStrg"))
				{
					ConvertSingleNodeData((char*)&szResponseStatusStrg, struXmlResult, "responseStatusStrg", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
					m_strSearchStatusRet = szResponseStatusStrg;
				}

				if (struXmlResult.FindElem("numOfMatches"))
				{
					ConvertSingleNodeData(&dwNumOfMatches, struXmlResult, "numOfMatches", NODE_STRING_TO_INT);
					m_dwCountRet = dwNumOfMatches;
				}

				if (struXmlResult.FindElem("MatchList") && struXmlResult.IntoElem())
				{
					ConferenceMatchInfo struConfMatchInfo = {0};

                    do 
                    {
					    if(struXmlResult.FindElem("MatchElement") && struXmlResult.IntoElem())
					    {
						    
						    if (struXmlResult.FindElem("conferenceId"))
						    {
							    ConvertSingleNodeData(&(struConfMatchInfo.szConfID), struXmlResult, "conferenceId", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						    }

						    if (struXmlResult.FindElem("conferenceName"))
						    {
							    ConvertSingleNodeData((char*)&struConfMatchInfo.szConfName, struXmlResult, "conferenceName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						    }

						    if (struXmlResult.FindElem("TimeSpan") && struXmlResult.IntoElem())
						    {
							    if (struXmlResult.FindElem("startTime"))
							    {
								    ConvertSingleNodeData((char*)&struConfMatchInfo.struTimeSpain.szStartTime, struXmlResult, "startTime", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							    }

							    if (struXmlResult.FindElem("endTime"))
							    {
								    ConvertSingleNodeData((char*)&struConfMatchInfo.struTimeSpain.szEndTime, struXmlResult, "endTime", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							    }

							    struXmlResult.OutOfElem();
						    }

						    if (struXmlResult.FindElem("conferenceType"))
						    {
							    ConvertSingleNodeData((char*)&struConfMatchInfo.szConfType, struXmlResult, "conferenceType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						    }

						    if (struXmlResult.FindElem("conferenceState"))
						    {
							    ConvertSingleNodeData((char*)&struConfMatchInfo.szConfState, struXmlResult, "conferenceState", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						    }
						    
						    m_lstConfMatch[m_dwMatchCount] = struConfMatchInfo;

                            m_dwMatchCount++;

						    //更新到ListCtrl中
						    InsertMatchConf(struConfMatchInfo);

						    struXmlResult.OutOfElem();
					    }

					
                    } while (struXmlResult.NextSibElem());

                    struXmlResult.OutOfElem();

				}//if (struXmlResult.FindElem("MatchList")

				struXmlResult.OutOfElem();
			}
			else
			{
			}//if (struXmlResult.FindElem("ConferenceSearchResult")
		}
		else
		{
		}// if (struXmlResult.Parse
	}

	delete[] m_pXMLParamBuf;
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;

    m_dwStartYearRet = 0;
    m_dwStartMonthRet = 0;
    m_dwStartDayRet = 0;
    m_dwStartHourRet = 0;
    m_dwStartMinuteRet = 0;
    
    //Ret会议结束时间
    m_dwEndYearRet = 0;
    m_dwEndMonthRet = 0;
    m_dwEndDayRet = 0;
    m_dwEndHourRet = 0;
    m_dwEndMinuteRet = 0;

	UpdateData(FALSE);
}

CString CDlgMCUSearchConference::ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf)
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

void CDlgMCUSearchConference::OnClickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	LVHITTESTINFO info;
    info.pt  =  pNMItemActivate -> ptAction;

	if (m_pListConfInfoRet->SubItemHitTest(&info) != -1)
	{
		int hitRow = info.iItem;
        //int hitCol = info.iSubItem;

		int length = strlen(m_lstConfMatch[hitRow].struTimeSpain.szStartTime);
		StringToTime(m_lstConfMatch[hitRow].struTimeSpain.szStartTime, length, m_dwStartYearRet, m_dwStartMonthRet, m_dwStartDayRet, m_dwStartHourRet, m_dwStartMinuteRet);

		length = strlen(m_lstConfMatch[hitRow].struTimeSpain.szEndTime);
		StringToTime(m_lstConfMatch[hitRow].struTimeSpain.szEndTime, length, m_dwEndYearRet, m_dwEndMonthRet, m_dwEndDayRet, m_dwEndHourRet, m_dwEndMinuteRet);

		m_strConfTypeRet    = m_lstConfMatch[hitRow].szConfType;
		m_strConfStatusRet  = m_lstConfMatch[hitRow].szConfState;

		UpdateData(FALSE);
	}
}

void CDlgMCUSearchConference::InsertMatchConf(const ConferenceMatchInfo& struConfInfo)
{
	static int nIndex = 1;

	CString strTemp;

	int nHeadNum = m_pListConfInfoRet->GetItemCount();

	strTemp.Format("%d", nIndex);
	int nRow = m_pListConfInfoRet->InsertItem(nHeadNum, strTemp);//插入行

	strTemp = struConfInfo.szConfID;
    m_pListConfInfoRet->SetItemText(nRow, 1, strTemp);//设置数据

	strTemp = struConfInfo.szConfName;
    m_pListConfInfoRet->SetItemText(nRow, 2, strTemp);//设置数据

	nIndex++;
}

BOOL CDlgMCUSearchConference::StringToTime(char* szTime, int length, DWORD& year, DWORD& month, DWORD& day, DWORD& hour, DWORD& minute)
{
	int pos = 0;
	int len = 4;

	if (length < len)
		return FALSE;

    //2015-09-06T12:00:00

	char szTemp[8] = {0};

	memcpy(szTemp, (char*)(szTime) + pos, 4);
	year = atoi(szTemp);
	memset(szTemp, '\0', sizeof(szTemp));

	pos = len+1;
	len += 3;
	if (length < len)
		return FALSE;

	memcpy(szTemp, (char*)(szTime) + pos, 2);
	month = atoi(szTemp);
	memset(szTemp, '\0', sizeof(szTemp));

	pos = len+1;
    len += 3;
	if (length < len)
		return FALSE;

	memcpy(szTemp, (char*)(szTime) + pos, 2);
	day = atoi(szTemp);
	memset(szTemp, '\0', sizeof(szTemp));

	pos = len+1;
	len += 3;
	if (length < len)
		return FALSE;

	memcpy(szTemp, (char*)(szTime) + pos, 2);
	hour = atoi(szTemp);
	memset(szTemp, '\0', sizeof(szTemp));

	pos = len+1;
	len += 3;
	if (length < len)
		return FALSE;

	memcpy(szTemp, (char*)(szTime) + pos, 2);
	minute = atoi(szTemp);
	memset(szTemp, '\0', sizeof(szTemp));

	return TRUE;
}
