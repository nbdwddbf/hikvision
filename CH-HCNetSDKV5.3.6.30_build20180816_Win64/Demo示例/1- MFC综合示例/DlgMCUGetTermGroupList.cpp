// DlgMCUGetTermGroupList.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMCUGetTermGroupList.h"
#include "InfoDiffusionParamsConvert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUGetTermGroupList dialog


CDlgMCUGetTermGroupList::CDlgMCUGetTermGroupList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMCUGetTermGroupList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMCUGetTermGroupList)
		// NOTE: the ClassWizard will add member initialization here

	for (int i = 0; i < MAX_GROUP_COUNT; i++)
	{
		memset(&m_TermGroupInfoList[i], 0, sizeof(TermGroupInfo));
	}


	m_dwGroupNum = 0;
	
	//}}AFX_DATA_INIT
}


void CDlgMCUGetTermGroupList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMCUGetTermGroupList)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMCUGetTermGroupList, CDialog)
	//{{AFX_MSG_MAP(CDlgMCUGetTermGroupList)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_NOTIFY(NM_CLICK, IDC_LST_GROUP_INFO, OnClickLstGroupInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUGetTermGroupList message handlers


BOOL CDlgMCUGetTermGroupList::OnInitDialog()
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

	m_pListGroupInfo = (CListCtrl*)GetDlgItem(IDC_LST_GROUP_INFO);
    m_pListTermInfo  = (CListCtrl*)GetDlgItem(IDC_LST_TERM);

	LONG lStyle;
    lStyle = GetWindowLong(m_pListGroupInfo->m_hWnd, GWL_STYLE);//获取当前窗口style
    lStyle &= ~LVS_TYPEMASK; //清除显示方式位
    lStyle |= LVS_REPORT;    //设置style
    SetWindowLong(m_pListGroupInfo->m_hWnd, GWL_STYLE, lStyle);//设置style
	SetWindowLong(m_pListTermInfo->m_hWnd, GWL_STYLE, lStyle);//设置style
    
    DWORD dwStyle = m_pListGroupInfo->GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;    //网格线（只适用与report风格的listctrl）
    m_pListGroupInfo->SetExtendedStyle(dwStyle); //设置扩展风格
	m_pListTermInfo->SetExtendedStyle(dwStyle); //设置扩展风格

	m_pListGroupInfo->InsertColumn(0, "Index", LVCFMT_LEFT, 50);//插入列
	m_pListGroupInfo->InsertColumn(1, "ID", LVCFMT_LEFT, 80);
    m_pListGroupInfo->InsertColumn(2, "使能", LVCFMT_LEFT, 50);
	m_pListGroupInfo->InsertColumn(3, "分组名称", LVCFMT_LEFT, 105);
	m_pListGroupInfo->InsertColumn(4, "终端数目", LVCFMT_LEFT, 80);

	m_pListTermInfo->InsertColumn(0, "终端号", LVCFMT_LEFT, 250);//插入列
    

	return TRUE;
}

void CDlgMCUGetTermGroupList::OnBtnGet() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	memset(m_szRequestURL, '\0' ,REQUEST_URL_LEN);
	memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN);
	m_dwXMLResultBufLen = ISAPI_DATA_LEN;
	memset(m_szXMLStatus, '\0', sizeof(ISAPI_STATUS_LEN));

	//lpInputParam->lpRequestUrl为：GET /ISAPI/VCS/terminalGroups；
	//lpInputParam->lpInBuffer为NULL；
	//lpOutputParam->lpOutBuffer为TerminalGroupList；
	//lpOutputParam->lpStatusBuffer为ResponseStatus，获取成功时不返回。

	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
	sprintf((char*)m_szRequestURL, "GET /ISAPI/VCS/terminalGroups");
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer = NULL;
	struXMLCfgInput.dwInBufferSize = 0;
	
	NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = {0};
	struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
	struXMLCfgOutput.lpOutBuffer = (char*)m_szXMLResultBuf;
	struXMLCfgOutput.dwOutBufferSize = ISAPI_DATA_LEN;
	struXMLCfgOutput.lpStatusBuffer = (char*)m_szXMLStatus;
	struXMLCfgOutput.dwStatusSize = ISAPI_STATUS_LEN;
	
	LPNET_DVR_XML_CONFIG_OUTPUT lpXMLCfgOutput = &struXMLCfgOutput;
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struXMLCfgInput, lpXMLCfgOutput))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		//状态处理
		ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);
		return;
	}

	//状态处理
	ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);

	CXmlBase struXmlResult;
	
	if (struXmlResult.Parse((char*)struXMLCfgOutput.lpOutBuffer))
	{
		if (struXmlResult.FindElem("TerminalGroupList") && struXmlResult.IntoElem())
		{
            m_pListGroupInfo->DeleteAllItems();
            m_pListTermInfo->DeleteAllItems();

            TermGroupInfo struTermGroupInfo = {0};

			m_dwGroupNum = 0;

            do 
            {

			    if (struXmlResult.FindElem("TerminalGroup") && struXmlResult.IntoElem())
			    {
				    memset(&struTermGroupInfo, 0, sizeof(struTermGroupInfo));

				    if (struXmlResult.FindElem("id"))
				    {
					    ConvertSingleNodeData((char*)&struTermGroupInfo.szID, struXmlResult, "id", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
				    }

				    if (struXmlResult.FindElem("enabled"))
				    {
					    ConvertSingleNodeData(&struTermGroupInfo.bEnabled, struXmlResult, "enabled", NODE_STRING_TO_BOOL);
				    }

				    if (struXmlResult.FindElem("groupName"))
				    {
					    ConvertSingleNodeData((char*)&struTermGroupInfo.szGroupName, struXmlResult, "groupName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
				    }

				    if (struXmlResult.FindElem("terminalNum"))
				    {
					    ConvertSingleNodeData(&struTermGroupInfo.dwTermNum, struXmlResult, "terminalNum", NODE_STRING_TO_INT);
				    }

				    if (struXmlResult.FindElem("terminalNoList") && struXmlResult.IntoElem())
				    {
					    int nSubCount = 0;

                        do 
                        {
					        if (struXmlResult.FindElem("terminalNo"))
					        {
						        ConvertSingleNodeData(&(struTermGroupInfo.TermNOList[nSubCount][0]), struXmlResult, "terminalNo", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);

						        nSubCount++;
					        }
                            
                        } while (struXmlResult.NextSibElem());

					    struXmlResult.OutOfElem();
				    }

				    InsertGroupInfo(struTermGroupInfo);

				    m_TermGroupInfoList[m_dwGroupNum] = struTermGroupInfo;

				    m_dwGroupNum++;

				    struXmlResult.OutOfElem();

			    }

            }while (struXmlResult.NextSibElem());

			struXmlResult.OutOfElem();
		}
	}//if (struXmlResult.Parse((char*)struXMLCfgOutput.lpOutBuffer))


	UpdateData(FALSE);
	
}

CString CDlgMCUGetTermGroupList::ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf)
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

void CDlgMCUGetTermGroupList::OnClickLstGroupInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	LVHITTESTINFO info;
    info.pt  =  pNMItemActivate -> ptAction;
	
	if (m_pListGroupInfo->SubItemHitTest(&info) != -1)
	{
        m_pListTermInfo->DeleteAllItems();
		int hitRow = info.iItem;
        //int hitCol = info.iSubItem;
		for (int i = 0; i < (int)m_TermGroupInfoList[hitRow].dwTermNum; i++)
		{
			InsertTermInfo(m_TermGroupInfoList[hitRow].TermNOList[i]);
		}
	}
	
	*pResult = 0;
}

void CDlgMCUGetTermGroupList::InsertGroupInfo(const TermGroupInfo& struTermGroupInfo)
{
	static int nIndex = 1;
	CString strTemp;
	
	strTemp.Format("%d", nIndex);
	int nHeadNum = m_pListGroupInfo->GetItemCount();	
	int nRow = m_pListGroupInfo->InsertItem(nHeadNum, strTemp);//插入行&设置Index
	
	strTemp = struTermGroupInfo.szID;
    m_pListGroupInfo->SetItemText(nRow, 1, strTemp);//设置ID
	
	if (struTermGroupInfo.bEnabled)
	{
		strTemp = _T("是");
	}
	else
	{
		strTemp = _T("否");
	}
    m_pListGroupInfo->SetItemText(nRow, 2, strTemp);//设置使能

	strTemp = struTermGroupInfo.szGroupName;
    m_pListGroupInfo->SetItemText(nRow, 3, strTemp);//设置分组名称

	strTemp.Format("%d", struTermGroupInfo.dwTermNum);
	m_pListGroupInfo->SetItemText(nRow, 4, strTemp);//设置终端数目
}

void CDlgMCUGetTermGroupList::InsertTermInfo(char* pTermNO)
{
	static int nIndex = 1;
	CString strTemp;
	
    strTemp = pTermNO;
	//strTemp.Format("%d", nIndex);
	int nHeadNum = m_pListTermInfo->GetItemCount();	
	int nRow = m_pListTermInfo->InsertItem(nHeadNum, strTemp);//设置终端号
	
	
    //m_pListTermInfo->SetItemText(nRow, 1, strTemp);
}
