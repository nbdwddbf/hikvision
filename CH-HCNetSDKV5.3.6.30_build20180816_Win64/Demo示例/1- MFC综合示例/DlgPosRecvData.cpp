// DlgPosRecvData.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPosRecvData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgPosRecvData* g_pPosRecvData;

/////////////////////////////////////////////////////////////////////////////
// CDlgPosRecvData dialog


CDlgPosRecvData::CDlgPosRecvData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPosRecvData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPosRecvData)
	m_csStatusInfo = _T("");
	m_wPort = 7500;
	m_csReceivedData = _T("");
	m_iUserID = -1;
	m_iDevIndex = -1;
	m_lUploadHandle = -1;
	m_hUpLoadThread = NULL;
	m_bUpLoading = FALSE;
	m_bStartListen = FALSE;
	m_iStartListenHandle = -1;
	m_csPosName = _T("");
	m_dwTheGroupNum = 0;
	m_dwChanNum = 1;
	m_dwTheFilterNum = 0;

	//}}AFX_DATA_INIT
}


void CDlgPosRecvData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPosRecvData)
	DDX_Control(pDX, IDC_COMBO_CONNECTMODE, m_comboConnectMode);
	DDX_Control(pDX, IDC_COMBOCHANNELNUM, m_comboChanNum);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_csStatusInfo);
	DDX_Text(pDX, IDC_EDIT_PORT, m_wPort);
	DDX_Text(pDX, IDC_EDIT_RECEIVED_DATA, m_csReceivedData);
	DDX_Text(pDX, IDC_EDIT_POSNAME, m_csPosName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPosRecvData, CDialog)
	ON_MESSAGE(MSG_PULL_CHANGE_RECEIVEDATA_SHOW, OnChangeDataShow)
	//{{AFX_MSG_MAP(CDlgPosRecvData)	
	ON_BN_CLICKED(IDC_BTN_UPLOAD, OnBtnUpload)
	ON_BN_CLICKED(IDC_BTN_START_LISTEN, OnBtnStartListen)
	ON_BN_CLICKED(IDC_BTN_SAVE_DATA, OnBtnSaveData)
	ON_CBN_SELCHANGE(IDC_COMBOCHANNELNUM, OnSelchangeCombochannelnum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPosRecvData message handlers

void CALLBACK NakedPosDataCallBack(DWORD typeInfo,NET_DVR_NAKED_DATA_INFO *pStruNakedDataInfo, char *pInfo, DWORD dwInfoLen, void *pUser)
{
	UNREFERENCED_PARAMETER(pUser);
	char szLan[1024] = {0}; 
	HWND hWnd = ::FindWindow(NULL,"Net RecvData");//::GetDlgItem( ,IDD_DLG_POS_RECV_DATA);

	if (NULL == hWnd)
	{
		return;
	}

//	memcpy(pStruNakedDataInfo->sSocketIP,)
	//校验发送的数据方是否和对应规则的IP一致，一致则继续发送数据，否则不投递
// 	if (strcmp(g_pPosRecvData->m_struConnPosCfg.struPosConnMode.struNetMonitorSet.struNetIp.sIpV4,pStruNakedDataInfo->sSocketIP) != 0)
// 	{
// 		return;
// 	}
	::SendMessage(hWnd,MSG_PULL_CHANGE_RECEIVEDATA_SHOW,(WPARAM)pStruNakedDataInfo, 0);
    ::SendMessage(hWnd,MSG_PULL_CHANGE_RECEIVEDATA_SHOW,(WPARAM)pInfo,1);
}


DWORD  GetUpLoadFileThread(LPVOID pParam)
{
	 CDlgPosRecvData *pThis = ( CDlgPosRecvData*)pParam;
	 
	 DWORD dwState = 0;
	 DWORD dwProgress = 0;
	 char szLan[256] = {0};

//	 dwState = NET_DVR_GetUploadState(pThis->m_lUploadHandle,&dwProgress)

	 while (1)
	 {
		 dwState = NET_DVR_GetUploadState(pThis->m_lUploadHandle,&dwProgress);
		 if (dwState == 1)
		 {
			 g_StringLanType(szLan, "上传成功", "Upload successfully");
			 //pThis->m_csStatusInfo.Format(szLan);
			 pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			 pThis->m_bUpLoading = FALSE;
			 g_StringLanType(szLan,"上传","Upload");
			 pThis->GetDlgItem(IDC_BTN_UPLOAD)->SetWindowText(szLan);
			 break;
		 }
		 else if (dwState == 2)
		 {
			 g_StringLanType(szLan, "正在上传,已上传:%d", "Is uploading,progress:%d");
			 pThis->m_csStatusInfo.Format(szLan, dwProgress);
		 }
		 else if (dwState == 3)
		 {
			 g_StringLanType(szLan, "上传失败", "Upload failed");
			 pThis->m_csStatusInfo.Format(szLan);
			 break;
		 }
		 else if (dwState == 4)
		 {
			 if (dwProgress == 100)
			 {
				 g_StringLanType(szLan, "上传成功", "Upload successfully");
				 pThis->m_csStatusInfo.Format(szLan);
				 pThis->m_bUpLoading = FALSE;
				 g_StringLanType(szLan,"上传","Upload");
				 pThis->GetDlgItem(IDC_BTN_UPLOAD)->SetWindowText(szLan);
				 pThis->UpdateData(FALSE);
				 break; 
			 }
			 else
			 {
				 g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
				 pThis->m_csStatusInfo.Format(szLan);
				 break;
			 }
		
		 }
		 
		 if (dwState != 2 && dwState != 5)
		 {        
			 NET_DVR_UploadClose(pThis->m_lUploadHandle);
		 		pThis->m_bUpLoading = FALSE;
		 }
	 }
	 return FALSE;
}


BOOL CDlgPosRecvData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	memset(&m_struNakedDataParam, 0,sizeof(m_struNakedDataParam));
	memset(&m_struChanFilterCfg, 0, sizeof(m_struChanFilterCfg));
	memset(&m_struPosFilterCfg, 0, sizeof(m_struPosFilterCfg));
	memset(&m_struIPParaCfgV40, 0, sizeof(m_struIPParaCfgV40)); 
	memset(&m_struConnPosCfg, 0, sizeof(m_struConnPosCfg));
	memset(&m_struPosInfo,0,sizeof(m_struPosInfo));
	m_wSocketPort = 0;
	memset(m_szPosIp,0,sizeof(m_szPosIp));

	AddChanInfo();
	m_comboChanNum.SetCurSel(0);
 
	m_dwChanNum = 1;
	m_dwTheFilterNum = 0;
	GetChanAndRuleInfo(1);
	g_pPosRecvData = this;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPosRecvData::OnBtnStartListen() 
{
	// TODO: Add your control notification handler code here
	g_pPosRecvData = this;

	UpdateData(TRUE);
    char szLan[128] = {0};

	if (m_csPosName.IsEmpty())
	{
       g_StringLanType(szLan,"请先选择网络接收方式的通道！","Please Select a Channel with Network!");
	   AfxMessageBox(szLan);
	   return;
	}

	//是否已经开启了监听
	if (!m_bStartListen) 
	{
       StartNetNakedDataListen();
	}
	else
	{
		StopNetNakedDataListen();
	}
}

void CDlgPosRecvData::StartNetNakedDataListen()
{
	UpdateData(TRUE);
	char szLan[256] = {0};
	if (m_wPort < 0 || m_wPort > 65535)
	{
		g_StringLanType(szLan,"请输入正确的端口号！","Please Input right port!");
		AfxMessageBox(szLan);
		return;
	}
	
	memset(&m_struNakedDataParam, 0,sizeof(m_struNakedDataParam));
    m_struNakedDataParam.wPort = m_wPort;
	
	//start listen
	m_iStartListenHandle = NET_DVR_StartRecvNakedDataListen(NAKED_DATA_TYPE_POS_INFO, &m_struNakedDataParam);
	
	if (m_iStartListenHandle < 0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StartRecvNakedDataListen");
		
		return;		
	}
	else
	{
		m_bStartListen = TRUE;
		g_StringLanType(szLan,"停止监听", "Stop Listen");
		GetDlgItem(IDC_BTN_START_LISTEN)->SetWindowText(szLan);
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StartRecvNakedDataListen");
	}
	
	//设置数据回调
	
	NET_DVR_SetNakedDataRecvCallBack(m_iStartListenHandle,NakedPosDataCallBack,this);
	UpdateData(FALSE);
} 

void CDlgPosRecvData::StopNetNakedDataListen()
{
	char szLan[256] = {0};
   if (m_iStartListenHandle < 0)
   {
	   g_StringLanType(szLan,"开始监听", "Start Listen");
	   GetDlgItem(IDC_BTN_START_LISTEN)->SetWindowText(szLan);
       g_StringLanType(szLan, "监听端口已关闭！", "Listening port is closed!");
	   AfxMessageBox(szLan);
	   return;
   }

   //close Listen
   if (!NET_DVR_StopRecvNakedDataListen(m_iStartListenHandle))
   {
	   g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRecvNakedDataListen");  
	   return;		
   }
   else
   {
	   m_bStartListen = FALSE;
	   g_StringLanType(szLan,"开始监听", "Start Listen");
	   GetDlgItem(IDC_BTN_START_LISTEN)->SetWindowText(szLan);
	   g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopRecvNakedDataListen");
	}


}

LRESULT CDlgPosRecvData::OnChangeDataShow(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);
	if ((LONG)lParam == 1)
	{
		char *pReceiveData = (char*)wParam;
		
		int  iChOld = 0x0d0a;
		int  iChNew = 0x0a;
		
		int iTest = strlen(pReceiveData);
		m_csReceivedData += pReceiveData + (LONG)lParam;
		m_csReceivedData.Replace((LPCTSTR)iChOld,LPCTSTR(iChNew));
		
		UpdateData(FALSE); 
		
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_RECEIVED_DATA);
		int iAllLineNum = pEdit->GetLineCount();
		
		pEdit->LineScroll(iAllLineNum);
	    UpdateData(FALSE);     
	}
	else
	{
		NET_DVR_NAKED_DATA_INFO *pStruNakedDataInfo = (NET_DVR_NAKED_DATA_INFO*)wParam;
		memcpy(m_szPosIp,pStruNakedDataInfo->sSocketIP,sizeof(pStruNakedDataInfo->sSocketIP));
		m_wSocketPort = pStruNakedDataInfo->wSocktPort;
	}
	
	return NULL;
}

void CDlgPosRecvData::OnBtnSaveData() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (m_csReceivedData.IsEmpty())
	{
        g_StringLanType(szLan,"没有数据！","No Data!");
		AfxMessageBox(szLan);
		return;
	}

	//保存文件
	CString csFileName ;
	CTime time;

	CStdioFile myFile;
	
	//获取当前时间
	time = CTime::GetCurrentTime();
	DWORD dwTheRuleNum = 0;
	dwTheRuleNum = m_dwTheFilterNum + m_dwTheGroupNum * FILTERRULE_NUM +1;
	csFileName.Format("C:\\rule%2d_posInfo%4d%02d%02d_%02d%02d%02d.txt",\
		dwTheRuleNum,time.GetYear(), time.GetMonth(),\
		time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	
	//打开文件
	if (myFile.Open(csFileName, CFile::modeCreate|CFile::modeWrite) == FALSE)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "文件创建失败", "create file failed");
		AfxMessageBox(szLan);
		return;
	}

	//写入数据
	myFile.WriteString(m_csReceivedData);

	//关闭文件
	myFile.Close();
	m_csReceivedData = "";
	
   g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Save Data in %s",csFileName);
}

void CDlgPosRecvData::OnSelchangeCombochannelnum() 
{
	// TODO: Add your control notification handler code here
	//获取通道号
	GetChanAndRuleInfo(m_comboChanNum.GetCurSel() + 1);

	
}

void CDlgPosRecvData::AddChanInfo()
{
	UpdateData(TRUE);
	DWORD dwReturn = 0;
	CString strTemp =_T("");
	DWORD dwChanNum = 0;
	int iIndex = 0;
	DWORD dwIPChanIndex = 0;
	int i = 0;
	
	int iMaxSimulateChannelNO =  g_struDeviceInfo[m_iDevIndex].iAnalogChanNum;
	//***模拟通道***//
	for (i = 0; i < g_struDeviceInfo[m_iDevIndex].iAnalogChanNum; i++)
	{
		dwChanNum = i +1;
		if ((dwChanNum) > iMaxSimulateChannelNO)
		{
			break;
		}
		
		strTemp.Format(ANALOG_C_FORMAT, dwChanNum);
		m_comboChanNum.AddString(strTemp);
	}
	
	//***IP channel***//
	int iMaxIPChannelNO =  g_struDeviceInfo[m_iDevIndex].iIPChanNum;
	for (i = 0; i < iMaxIPChannelNO; i++)
	{
		dwChanNum = i + m_struIPParaCfgV40.dwStartDChan + 1;
		if ((dwChanNum ) > iMaxIPChannelNO)
		{
			break;
		}
		
		strTemp.Format(IP_CAMERA_NAME, dwChanNum);
		m_comboChanNum.AddString(strTemp);		
	}	
	
	UpdateData(FALSE);
}
void CDlgPosRecvData::GetChanAndRuleInfo(DWORD dwChanNum)
{
	UpdateData(TRUE);
	char szLan[128] = {0};
	memset(&m_struChanFilterCfg,0, sizeof(m_struChanFilterCfg));
	m_struChanFilterCfg.dwSize = sizeof(m_struChanFilterCfg);

	DWORD dwReturn = 0;
	if (!NET_DVR_GetDVRConfig(m_iUserID,NET_DVR_GET_CHAN_FILTER_CFG,dwChanNum, &m_struChanFilterCfg, sizeof(m_struChanFilterCfg),&dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "chan[%d]:NET_DVR_GET_CHAN_FILTER_CFG", dwChanNum);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "chan[%d]:NET_DVR_GET_CHAN_FILTER_CFG", dwChanNum);
	}


	//获取组号
/*	DWORD dwGroupNum = 0;
	dwGroupNum = (m_struChanFilterCfg.dwFilterID - 1) / FILTERRULE_NUM;

	//获取规则号
	DWORD dwRuleIndex = (m_struChanFilterCfg.dwFilterID -1)%4;
	m_dwTheFilterNum = dwRuleIndex;
	

	//获取组号对应的过滤规则
	memset(&m_struPosFilterCfg, 0, sizeof(m_struPosFilterCfg));
	m_struPosFilterCfg.struVerHead.wLength = sizeof(m_struPosFilterCfg);
	m_struPosFilterCfg.dwMaxGroupNum = dwGroupNum;
	if (!NET_DVR_GetDVRConfig(m_iUserID, NET_DVR_GET_POS_FILTER_CFG,NULL, &m_struPosFilterCfg, sizeof(m_struPosFilterCfg), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "GroupNum[%d]NET_DVR_GET_POS_FILTER_CFG", dwGroupNum);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "GroupNum[%d]:NET_DVR_GET_POS_FILTER_CFG", dwGroupNum);
	}

	m_csPosName = m_struPosFilterCfg.struFilterCfg[dwRuleIndex].sPosName;

 
	//获取该posName对应的连接模式
	memset(&m_struConnPosCfg, 0, sizeof(m_struConnPosCfg));
	m_struConnPosCfg.struVerHead.wLength = sizeof(m_struConnPosCfg);
	memcpy(&m_struConnPosCfg.sPosName, m_csPosName, m_csPosName.GetLength());

	if (!NET_DVR_GetDVRConfig(m_iUserID, NET_DVR_GET_CONNECT_POS_CFG,NULL, &m_struConnPosCfg, sizeof(m_struConnPosCfg), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CONNECT_POS_CFGG", dwGroupNum);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CONNECT_POS_CFG", dwGroupNum);
	}

	m_comboConnectMode.SetCurSel(m_struConnPosCfg.dwConnectMode);//m_struConnPosCfg.dwConnectMode
	UpdateData(FALSE);
	if (m_struConnPosCfg.dwConnectMode == 2)
	{
      g_StringLanType(szLan,"该接收方方式只支持网络模式！","Only Support NetWork!");
	  AfxMessageBox(szLan);
	  return;
	}
*/
	
}

void CDlgPosRecvData::OnBtnUpload() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	CString csFileName;
	CString sTemp;
	char szLan[256]= {0};
	
	static char szFilter[] = "All File(*.*)|*.*||";
	CFileDialog dlg(TRUE,"*.*", NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);
	if (dlg.DoModal() == IDOK)
	{
		csFileName = dlg.GetPathName();
		UpdateData(FALSE);
	}
	
	char strFileName[129] = {0};
    strncpy(strFileName, csFileName, 128);
	
	HANDLE hFileHandle = NULL;
	hFileHandle = CreateFile((LPCSTR)strFileName,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_READONLY,0);
	if (hFileHandle ==  INVALID_HANDLE_VALUE)
	{
		g_StringLanType(szLan,"打开文件失败！", "Open file failed!");
		AfxMessageBox(szLan);
		return;
	}
	
	//初始化请求结构体
	memset(&m_struPosInfo, 0 ,sizeof(m_struPosInfo));
	m_struPosInfo.struVerHead.wLength = sizeof(m_struPosInfo);
	
	//上传文件信息
    m_lUploadHandle = NET_DVR_UploadFile(m_iUserID,UPLOAD_POS_INFO,&m_struPosInfo, sizeof(m_struPosInfo),strFileName);
	if ( m_lUploadHandle < 0)
	{
		NET_DVR_StopUploadFile(m_lUploadHandle);
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "UPLOAD_POS_INFO");
		g_StringLanType(szLan,"失败！","Failed!");
		m_csStatusInfo = szLan;
		return;		
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "UPLOAD_POS_INFO");
	}
	
	DWORD dwThreadId = 0;
	m_hUpLoadThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetUpLoadFileThread),this,0,&dwThreadId);
	if (m_hUpLoadThread  == NULL)
	{
		char szLan[256] = {0};
		g_StringLanType(szLan, "打开备份线程失败!", "Fail to open backup thread!");
		AfxMessageBox(szLan);
		return;
	}
	g_StringLanType(szLan, "停止上传", "Stop Upload");
	GetDlgItem(IDC_BTN_UPLOAD)->SetWindowText(szLan);
	m_bUpLoading = TRUE;
	
	
	UpdateData(FALSE);
}