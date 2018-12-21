// DlgMCUGetConfStatus.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMCUGetConfStatus.h"
#include "InfoDiffusionParamsConvert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CSTRING_TO_CHARS(str,sz) memcpy((sz),str.GetBuffer(str.GetLength()),str.GetLength())

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUGetConfStatus dialog


CDlgMCUGetConfStatus::CDlgMCUGetConfStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMCUGetConfStatus::IDD, pParent)
    , m_dwVFrame(0)
    , m_iRWidth(0)
    , m_iRHeight(0)
    , m_iVFrame(0)
    , m_iSample(0)
    , m_iAFrame(0)
    , m_dwAudioFrame(0)
    , m_dwResWidth(0)
    , m_dwResHeight(0)
    , m_strCVideoType(_T(""))
    , m_strCAudioType(_T(""))
{
	//{{AFX_DATA_INIT(CDlgMCUGetConfStatus)
		// NOTE: the ClassWizard will add member initialization here


	m_dwConfDuration = 0;

	m_dwJoinedDur = 0;
	m_dwVolume = 0;
	m_dwAudioInPackSize = 0;
	m_dwVideoInPackSize = 0;
	m_dwAudioInPackLoss = 0;
	m_dwVideoInPackLoss = 0;

	m_dwAudioOutPackSize = 0;
	m_dwVideoOutPackSize = 0;
	m_dwAudioOutPackLoss = 0;
	m_dwVideoOutPackLoss = 0;
	
	m_dwBitRate = 0;
	m_dwFrameRate = 0;


	m_dwTermCount = 0;
	for (int i = 0; i < MAX_TERM_COUNT; i++)
	{
		memset((char*)&m_TermStatusLst[i], 0, sizeof(TerminalStatus));
	}

    m_nIndex = 0;

	//}}AFX_DATA_INIT
}


void CDlgMCUGetConfStatus::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgMCUGetConfStatus)
    // NOTE: the ClassWizard will add DDX and DDV calls here

    DDX_Control(pDX, IDC_COM_CONF_STATUS, m_comConfStatus);
    DDX_Control(pDX, IDC_COM_CONN_STATUS, m_comTermConnStatus);
    DDX_Control(pDX, IDC_COM_AUDIO_IN_TYPE, m_comAudioInType);
    DDX_Control(pDX, IDC_COM_AUDIO_OUT_TYPE, m_comAudioOutType);
    DDX_Control(pDX, IDC_COM_VIDEO_IN_TYPE, m_comVideoInType);
    DDX_Control(pDX, IDC_COM_VIDEO_OUT_TYPE, m_comVideoOutType);

    DDX_Text(pDX, IDC_EDT_CONF_ID, m_csConfID);
    DDX_Text(pDX, IDC_COM_CONF_STATUS, m_strConfStatus);
    DDX_Text(pDX, IDC_STA_CREATOR, m_strCreatorName);
    DDX_Text(pDX, IDC_STA_CONF_DUR_TIME, m_dwConfDuration);
    DDX_Text(pDX, IDC_STA_CONF_CONTENT, m_strConfContent);

    DDX_Text(pDX, IDC_STA_TERM_JOINED_DUR_TIME, m_dwJoinedDur);
    DDX_Text(pDX, IDC_COM_CONN_STATUS, m_strConnState);
    DDX_Text(pDX, IDC_STA_MUTE_STATE, m_strMuteState);
    DDX_Text(pDX, IDC_STA_VOLUME, m_dwVolume);
    DDX_Text(pDX, IDC_STA_AUDIO_IN_STATE, m_strAudioInState);
    DDX_Text(pDX, IDC_STA_IMAGE_STATE, m_strImageState);
    DDX_Text(pDX, IDC_STA_VIDEO_IN_STATE, m_strVideoInState);

    DDX_Text(pDX, IDC_COM_AUDIO_IN_TYPE, m_strAudioInType);
    DDX_Text(pDX, IDC_COM_VIDEO_IN_TYPE, m_strVideoInType);
    DDX_Text(pDX, IDC_STA_AUDIO_IN_PACK_SIZE, m_dwAudioInPackSize);
    DDX_Text(pDX, IDC_STA_VIDEO_IN_PACK_SIZE, m_dwVideoInPackSize);
    DDX_Text(pDX, IDC_STA_AUDIO_IN_PACK_LOSS, m_dwAudioInPackLoss);
    DDX_Text(pDX, IDC_STA_VIDEO_IN_PACK_LOSS, m_dwVideoInPackLoss);

    DDX_Text(pDX, IDC_COM_AUDIO_OUT_TYPE, m_strAudioOutType);
    DDX_Text(pDX, IDC_COM_VIDEO_OUT_TYPE, m_strVideoOutType);
    DDX_Text(pDX, IDC_STA_AUDIO_OUT_PACK_SIZE, m_dwAudioOutPackSize);
    DDX_Text(pDX, IDC_STA_VIDEO_OUT_PACK_SIZE, m_dwVideoOutPackSize);
    DDX_Text(pDX, IDC_STA_AUDIO_OUT_PACK_LOSS, m_dwAudioOutPackLoss);
    DDX_Text(pDX, IDC_STA_VIDEO_OUT_PACK_LOSS, m_dwVideoOutPackLoss);

    DDX_Text(pDX, IDC_STA_BIT_RATE, m_dwBitRate);
    DDX_Text(pDX, IDC_STA_FRAME_RATE, m_dwFrameRate);

    //DDX_Control(pDX, IDC_COM_VIEW_MODE,        m_comViewMode);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_CVIDEO_TYPE, m_cVideoType);
    DDX_Text(pDX, IDC_EDIT_VIDEO_FRAME, m_dwVFrame);
    DDX_Text(pDX, IDC_EDIT_RWIDTH, m_iRWidth);
    DDX_Text(pDX, IDC_EDIT_RHIGHT, m_iRHeight);
    DDX_Text(pDX, IDC_EDIT_VFRAME, m_iVFrame);
    DDX_Control(pDX, IDC_COMBO_CVIDEO, m_cmbCAType);
    DDX_Text(pDX, IDC_EDIT_SAMPLE, m_iSample);
    DDX_Text(pDX, IDC_EDIT_ADIO_BIT, m_iAFrame);
    DDX_Text(pDX, IDC_STA_BIT_RATE2, m_dwAudioFrame);
    DDX_Text(pDX, IDC_STA_VIDEO_W, m_dwResWidth);
    DDX_Text(pDX, IDC_STA_VIDEO_H, m_dwResHeight);
    DDX_CBString(pDX, IDC_COMBO_CVIDEO_TYPE, m_strCVideoType);
    DDX_CBString(pDX, IDC_COMBO_CVIDEO, m_strCAudioType);
}


BEGIN_MESSAGE_MAP(CDlgMCUGetConfStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgMCUGetConfStatus)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_NOTIFY(NM_CLICK, IDC_TERM_STATE_LIST, OnClickList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUGetConfStatus message handlers


BOOL CDlgMCUGetConfStatus::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_szRequestURL = new char[ISAPI_DATA_LEN];  
    if (m_szRequestURL == NULL)
    {
        return FALSE;
    }
    memset(m_szRequestURL, '\0' , ISAPI_DATA_LEN);
    m_szXMLResultBuf = new char[ISAPI_DATA_LEN*2];
    if (m_szXMLResultBuf == NULL)
    {
        return FALSE;
    }
    memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN*2);
    m_dwXMLResultBufLen = ISAPI_DATA_LEN*2;
    m_szXMLStatus = new char[ISAPI_STATUS_LEN];
    if (m_szXMLStatus == NULL)
    {
        return FALSE;
    }
    memset(m_szXMLStatus, '\0', ISAPI_STATUS_LEN);

	m_pListTerm      = (CListCtrl*)GetDlgItem(IDC_TERM_STATE_LIST);
	
	LONG lStyle;
    lStyle = GetWindowLong(m_pListTerm->m_hWnd, GWL_STYLE);//获取当前窗口style
    lStyle &= ~LVS_TYPEMASK; //清除显示方式位
    lStyle |= LVS_REPORT;    //设置style
    SetWindowLong(m_pListTerm->m_hWnd, GWL_STYLE, lStyle);//设置style
    
    DWORD dwStyle = m_pListTerm->GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;    //网格线（只适用与report风格的listctrl）
    //dwStyle |= LVS_EX_CHECKBOXES;   //item前生成checkbox控件
    m_pListTerm->SetExtendedStyle(dwStyle); //设置扩展风格
	
	m_pListTerm->InsertColumn(0, "Index", LVCFMT_LEFT, 60);//插入列
    m_pListTerm->InsertColumn(1, "ID", LVCFMT_LEFT, 250);//插入列
    m_pListTerm->InsertColumn(2, "TerminalName", LVCFMT_LEFT, 150);

	UpdateData(FALSE);

	return TRUE;
}

void CDlgMCUGetConfStatus::OnBtnGet() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

    m_nIndex = 0;

    m_pListTerm->DeleteAllItems();

    memset(m_szRequestURL, '\0' , ISAPI_DATA_LEN);
    memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN*2);
    m_dwXMLResultBufLen = ISAPI_DATA_LEN*2;
	memset(m_szXMLStatus, '\0', sizeof(ISAPI_STATUS_LEN));


	//lpInputParam->lpRequestUrl为：GET /ISAPI/VCS/conferences/<ID>/status；
	//lpInputParam->lpInBuffer为NULL；
	//lpOutputParam->lpOutBuffer为ConferenceStatus；
	//lpOutputParam->lpStatusBuffer为ResponseStatus，获取成功时不返回。

    char szConfID[MAX_XML_ELEM_LEN] = {0};

    CSTRING_TO_CHARS(m_csConfID,szConfID);

	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
	sprintf((char*)m_szRequestURL, "GET /ISAPI/VCS/conferences/%s/status", szConfID);
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer = NULL;
	struXMLCfgInput.dwInBufferSize  = 0;
		
	NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = {0};
	struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
	struXMLCfgOutput.lpOutBuffer = (char*)m_szXMLResultBuf;
	struXMLCfgOutput.dwOutBufferSize = ISAPI_DATA_LEN*2;
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
		//ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);
        ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpOutBuffer);
		return;
    }
	
	//ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);

    ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpOutBuffer);


	char szConfState[MAX_XML_ELEM_LEN] = {0};
	char szCreatorName[MAX_XML_ELEM_LEN] = {0};
	char szConfContent[MAX_XML_ELEM_LEN] = {0};
    char szConfVideoType[MAX_XML_ELEM_LEN] = { 0 };
    char szConfAudioType[MAX_XML_ELEM_LEN] = { 0 };

	CXmlBase struXmlResult;

	if (struXmlResult.Parse((char*)struXMLCfgOutput.lpOutBuffer))
	{


		if (struXmlResult.FindElem("ConferenceStatus") && struXmlResult.IntoElem())
		{
            if (struXmlResult.FindElem("id"))
            {
                ConvertSingleNodeData(szConfID, struXmlResult, "id", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
                m_csConfID = szConfID;
            }
            if (struXmlResult.FindElem("conferenceState"))
            {
                ConvertSingleNodeData((char*)&szConfState, struXmlResult, "conferenceState", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
                m_strConfStatus = szConfState;
		    }
			
			if (struXmlResult.FindElem("creatorName"))
			{
				ConvertSingleNodeData((char*)&szCreatorName, struXmlResult, "creatorName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
				m_strCreatorName = szCreatorName;
			}

            if (struXmlResult.FindElem("duration"))
            {
                ConvertSingleNodeData(&m_dwConfDuration, struXmlResult, "duration", NODE_STRING_TO_INT);
			}

            if (struXmlResult.FindElem("ConferenceAVInfo") && struXmlResult.IntoElem())
            {
                ConvertSingleNodeData((char*)&szConfVideoType, struXmlResult, "videoType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
                m_strCVideoType = szConfVideoType;
                ConvertSingleNodeData(&m_dwVFrame, struXmlResult, "videoFrameRate", NODE_STRING_TO_INT);
                ConvertSingleNodeData(&m_iRWidth, struXmlResult, "resolutionWidth", NODE_STRING_TO_INT);
                ConvertSingleNodeData(&m_iRHeight, struXmlResult, "resolutionHeight", NODE_STRING_TO_INT);
                ConvertSingleNodeData(&m_iVFrame, struXmlResult, "videoBitRate", NODE_STRING_TO_INT);

                ConvertSingleNodeData((char*)&szConfAudioType, struXmlResult, "audioType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
                m_strCAudioType = szConfAudioType;
                ConvertSingleNodeData(&m_iSample, struXmlResult, "audioSamplingRate", NODE_STRING_TO_INT);
                ConvertSingleNodeData(&m_iAFrame, struXmlResult, "audioBitRate", NODE_STRING_TO_INT);
                struXmlResult.OutOfElem();
            }

			if (struXmlResult.FindElem("TerminalStatusList") && struXmlResult.IntoElem())
			{
				TerminalStatus struTermStatus = {0};
				int i = 0;

                do 
                {
				    if (struXmlResult.FindElem("TerminalStatus") && struXmlResult.IntoElem())
				    {
					    memset(&struTermStatus, 0, sizeof(struTermStatus));

					    if (struXmlResult.FindElem("id"))
					    {
						    ConvertSingleNodeData(&struTermStatus.szTermID, struXmlResult, "id", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);	
					    }
					    if (struXmlResult.FindElem("terminalName"))
					    {
						    ConvertSingleNodeData(&struTermStatus.szTermName, struXmlResult, "terminalName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);	
					    }
					    if (struXmlResult.FindElem("joinedDuration"))
					    {
						    ConvertSingleNodeData(&struTermStatus.dwJoinedDur, struXmlResult, "joinedDuration", NODE_STRING_TO_INT);	
					    }

					    if (struXmlResult.FindElem("AVInfo") && struXmlResult.IntoElem())
					    {
						    if (struXmlResult.FindElem("audioInType"))
						    {
							    ConvertSingleNodeData(&struTermStatus.struAVInfo.szAudioInType, struXmlResult, "audioInType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						    }
						    if (struXmlResult.FindElem("audioOutType"))
						    {
							    ConvertSingleNodeData(&struTermStatus.struAVInfo.szAudioOutType, struXmlResult, "audioOutType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						    }
						    if (struXmlResult.FindElem("audioInPackets"))
						    {
							    ConvertSingleNodeData(&struTermStatus.struAVInfo.dwAudioInPackets, struXmlResult, "audioInPackets", NODE_STRING_TO_INT);
						    }
						    if (struXmlResult.FindElem("audioInPacketsLoss"))
						    {
							    ConvertSingleNodeData(&struTermStatus.struAVInfo.dwAudioInPackLoss, struXmlResult, "audioInPacketsLoss", NODE_STRING_TO_INT);
						    }
						    if (struXmlResult.FindElem("audioOutPackets"))
						    {
							    ConvertSingleNodeData(&struTermStatus.struAVInfo.dwAudioOutPackets, struXmlResult, "audioOutPackets", NODE_STRING_TO_INT);
						    }
						    if (struXmlResult.FindElem("audioOutPacketsLoss"))
						    {
							    ConvertSingleNodeData(&struTermStatus.struAVInfo.dwAudioOutPackLoss, struXmlResult, "audioOutPacketsLoss", NODE_STRING_TO_INT);
						    }
                            if (struXmlResult.FindElem("audioBitRate"))
                            {
                                ConvertSingleNodeData(&struTermStatus.struAVInfo.dwAudioBitRate, struXmlResult, "audioBitRate", NODE_STRING_TO_INT);
                            }
						    if (struXmlResult.FindElem("videoInType"))
						    {
							    ConvertSingleNodeData(&struTermStatus.struAVInfo.szVideoInType, struXmlResult, "videoInType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						    }
						    if (struXmlResult.FindElem("videoOutType"))
						    {
							    ConvertSingleNodeData(&struTermStatus.struAVInfo.szVideoOutType, struXmlResult, "videoOutType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						    }
						    if (struXmlResult.FindElem("videoInPackets"))
						    {
							    ConvertSingleNodeData(&struTermStatus.struAVInfo.dwVideoInPackets, struXmlResult, "videoInPackets", NODE_STRING_TO_INT);
						    }
						    if (struXmlResult.FindElem("vidioInPacketsLoss"))
						    {
							    ConvertSingleNodeData(&struTermStatus.struAVInfo.dwVideoInPackLoss, struXmlResult, "vidioInPacketsLoss", NODE_STRING_TO_INT);
						    }
						    if (struXmlResult.FindElem("videoOutPackets"))
						    {
							    ConvertSingleNodeData(&struTermStatus.struAVInfo.dwVideoOutPackets, struXmlResult, "videoOutPackets", NODE_STRING_TO_INT);
						    }
						    if (struXmlResult.FindElem("vidioOutPacketsLoss"))
						    {
							    ConvertSingleNodeData(&struTermStatus.struAVInfo.dwVideoOutPackLoss, struXmlResult, "vidioOutPacketsLoss", NODE_STRING_TO_INT);
						    }
						    if (struXmlResult.FindElem("vidioOutPacketsLoss"))
						    {
							    ConvertSingleNodeData(&struTermStatus.struAVInfo.dwVideoOutPackLoss, struXmlResult, "vidioOutPacketsLoss", NODE_STRING_TO_INT);
						    }
                            if (struXmlResult.FindElem("videoFrameRate"))
                            {
                                ConvertSingleNodeData(&struTermStatus.struAVInfo.dwFrameRate, struXmlResult, "videoFrameRate", NODE_STRING_TO_INT);
                            }
						    if (struXmlResult.FindElem("videoBitRate"))
						    {
							    ConvertSingleNodeData(&struTermStatus.struAVInfo.dwAVBitRate, struXmlResult, "videoBitRate", NODE_STRING_TO_INT);
						    }
                            if (struXmlResult.FindElem("resolutionWidth"))
                            {
                                ConvertSingleNodeData(&struTermStatus.struAVInfo.dwResWidth, struXmlResult, "resolutionWidth", NODE_STRING_TO_INT);
                            }
                            if (struXmlResult.FindElem("resolutionHeight"))
                            {
                                ConvertSingleNodeData(&struTermStatus.struAVInfo.dwResHeight, struXmlResult, "resolutionHeight", NODE_STRING_TO_INT);
                            }
						    

						    struXmlResult.OutOfElem();
					    }//if (struXmlResult.FindElem("AVInfo") && struXmlResult.IntoElem())

					    if (struXmlResult.FindElem("connectState"))
					    {
						    ConvertSingleNodeData(&struTermStatus.szConnState, struXmlResult, "connectState", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
					    }
					    if (struXmlResult.FindElem("muteState"))
					    {
						    ConvertSingleNodeData(&struTermStatus.szMuteState, struXmlResult, "muteState", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
					    }
					    if (struXmlResult.FindElem("volume"))
					    {
						    ConvertSingleNodeData(&struTermStatus.dwVolume, struXmlResult, "volume", NODE_STRING_TO_INT);
					    }
					    if (struXmlResult.FindElem("muteState"))
					    {
						    ConvertSingleNodeData(&struTermStatus.szMuteState, struXmlResult, "muteState", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
					    }
					    if (struXmlResult.FindElem("audioInState"))
					    {
						    ConvertSingleNodeData(&struTermStatus.szAudioInState, struXmlResult, "audioInState", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
					    }
					    if (struXmlResult.FindElem("imageState"))
					    {
						    ConvertSingleNodeData(&struTermStatus.szImageState, struXmlResult, "imageState", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
					    }
					    if (struXmlResult.FindElem("videoInState"))
					    {
						    ConvertSingleNodeData(&struTermStatus.szVideoInState, struXmlResult, "videoInState", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
					    }

					    m_dwTermCount++;
					    InsertTermStateInfo(struTermStatus);
					    m_TermStatusLst[i] = struTermStatus;

					    i++;

					    struXmlResult.OutOfElem();
				    }// end if (struXmlResult.FindElem("TerminalStatus") && struXmlResult.IntoElem())

                } while (struXmlResult.NextSibElem());


				struXmlResult.OutOfElem();
			}// end if (struXmlResult.FindElem("TerminalStatusList") && struXmlResult.IntoElem())

			if (struXmlResult.FindElem("conferenceContent"))
			{
				ConvertSingleNodeData((char*)&szConfContent, struXmlResult, "conferenceContent", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
				m_strConfContent = szConfContent;
			}
			
			struXmlResult.OutOfElem();

		}//FindElem("ConferenceSearchResult")

	}// if (struXmlResult.Parse((char*)struXMLCfgOutput.lpOutBuffer))
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Status XML Parse Error");
	}
	
	UpdateData(FALSE);	
}

CString CDlgMCUGetConfStatus::ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf)
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

void CDlgMCUGetConfStatus::InsertTermStateInfo(const TerminalStatus& struTermInfo)
{
	//static int nIndex = 1;
    m_nIndex++;
	CString strTemp;

	strTemp.Format("%d", m_nIndex);
	int nHeadNum = m_pListTerm->GetItemCount();	
	int nRow = m_pListTerm->InsertItem(nHeadNum, strTemp);//插入行
	
	strTemp = struTermInfo.szTermID;
    m_pListTerm->SetItemText(nRow, 1, strTemp);//设置数据

	strTemp = struTermInfo.szTermName;
    m_pListTerm->SetItemText(nRow, 2, strTemp);//设置数据

}

void CDlgMCUGetConfStatus::OnClickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	LVHITTESTINFO info;
    info.pt  =  pNMItemActivate -> ptAction;
	
	if (m_pListTerm->SubItemHitTest(&info) != -1)
	{
		int hitRow = info.iItem;
        //int hitCol = info.iSubItem;

		m_dwJoinedDur = m_TermStatusLst[hitRow].dwJoinedDur;
		m_strConnState = m_TermStatusLst[hitRow].szConnState;
		m_strMuteState = m_TermStatusLst[hitRow].szMuteState;
		m_dwVolume     = m_TermStatusLst[hitRow].dwVolume;
		m_strAudioInState = m_TermStatusLst[hitRow].szAudioInState;
		m_strImageState  = m_TermStatusLst[hitRow].szImageState;
		m_strVideoInState = m_TermStatusLst[hitRow].szVideoInState;

		m_strAudioInType = m_TermStatusLst[hitRow].struAVInfo.szAudioInType;
		m_strVideoInType = m_TermStatusLst[hitRow].struAVInfo.szVideoInType;
		m_dwAudioInPackSize = m_TermStatusLst[hitRow].struAVInfo.dwAudioInPackets;
		m_dwVideoInPackSize	= m_TermStatusLst[hitRow].struAVInfo.dwVideoInPackets;
		m_dwAudioInPackLoss	= m_TermStatusLst[hitRow].struAVInfo.dwAudioInPackLoss;
		m_dwVideoInPackLoss	= m_TermStatusLst[hitRow].struAVInfo.dwVideoInPackLoss;
        m_dwAudioFrame = m_TermStatusLst[hitRow].struAVInfo.dwAudioBitRate;

		m_strAudioOutType	= m_TermStatusLst[hitRow].struAVInfo.szAudioOutType;
		m_strVideoOutType	= m_TermStatusLst[hitRow].struAVInfo.szVideoOutType;
		m_dwAudioOutPackSize = m_TermStatusLst[hitRow].struAVInfo.dwAudioOutPackets;
		m_dwVideoOutPackSize	= m_TermStatusLst[hitRow].struAVInfo.dwVideoOutPackets;
		m_dwAudioOutPackLoss	= m_TermStatusLst[hitRow].struAVInfo.dwAudioOutPackLoss;
		m_dwVideoOutPackLoss	= m_TermStatusLst[hitRow].struAVInfo.dwVideoOutPackLoss;

		m_dwBitRate	= m_TermStatusLst[hitRow].struAVInfo.dwAVBitRate;
		m_dwFrameRate	= m_TermStatusLst[hitRow].struAVInfo.dwFrameRate;

        m_dwResHeight = m_TermStatusLst[hitRow].struAVInfo.dwResHeight;
        m_dwResWidth = m_TermStatusLst[hitRow].struAVInfo.dwResWidth;
		
		UpdateData(FALSE);
	}
}
