// DlgPosSerialPortRecvData.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPosSerialPortRecvData.h"
//#include "SerialSDK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPosSerialPortRecvData dialog


void CALLBACK SerialNakedDataCallBack(LONG nSerialHandle, BYTE *pDataBuffer, DWORD dwBufLen, void* pUser)
{
   	UNREFERENCED_PARAMETER(pUser);
	char szLan[1024] = {0};
	
	HWND hWnd = ::FindWindow(NULL,"RS232 RecvData");//::GetDlgItem( ,IDD_DLG_POS_RECV_DATA);
	
	if (NULL == hWnd)
	{
		return;
	}
	
	::SendMessage(hWnd,MSG_PULL_CHANGE_COM_RECEIVEDATA_SHOW,(WPARAM)pDataBuffer, (LONG)dwBufLen);
}
CDlgPosSerialPortRecvData::CDlgPosSerialPortRecvData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPosSerialPortRecvData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPosSerialPortRecvData)
	m_csRecvData = _T("");
	m_iUserID  = -1;
	m_iDevIndex = -1 ;
	m_bOpenComm = FALSE;
	m_bStartRecv = FALSE;
    m_iComHandle = -1;
	m_csPosName = _T("");
	m_bUpLoading = FALSE;
	m_lUploadHandle = -1;
	m_hUpLoadThread = NULL;
	//}}AFX_DATA_INIT
}


void CDlgPosSerialPortRecvData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPosSerialPortRecvData)
	DDX_Control(pDX, IDC_COMBO_CONNECTMODE_SERIAL, m_comboConnectMode);
	DDX_Control(pDX, IDC_COMBOCHANNELNUM, m_comboChanNum);
	DDX_Control(pDX, IDC_COMBO_SERIALPORT_COM, m_comboSerialPortCom);
	DDX_Text(pDX, IDC_EDIT_RECEIVE_DATA, m_csRecvData);
	DDX_Text(pDX, IDC_EDIT_POSNAME, m_csPosName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPosSerialPortRecvData, CDialog)
	ON_MESSAGE(MSG_PULL_CHANGE_COM_RECEIVEDATA_SHOW, OnChangeDataShow)
	//{{AFX_MSG_MAP(CDlgPosSerialPortRecvData)
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	ON_BN_CLICKED(IDC_BTN_OPENCOM, OnBtnOpencom)
	ON_CBN_SELCHANGE(IDC_COMBOCHANNELNUM, OnSelchangeCombochannelnum)
	ON_BN_CLICKED(IDC_BTN_SAVE_DATA, OnBtnSaveData)
	ON_BN_CLICKED(IDC_BTN_UPLOAD, OnBtnUpload)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPosSerialPortRecvData message handlers

void CDlgPosSerialPortRecvData::OnBtnStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	char szLan[128] = {0};
	if (!m_bOpenComm)
	{
		g_StringLanType(szLan,"请先开启com口!","Please Open COM First!");
		AfxMessageBox(szLan);
		return ;    
	}

	//打开
	if (!m_bStartRecv)
	{
	/*	if (SERIAL_PORT_SetNakedDataCallBack(m_iComHandle,SerialNakedDataCallBack,NULL) < 0 )
		{
			g_StringLanType(szLan,"设置回调失败!","Please Open COM First!");
			AfxMessageBox(szLan);
			return ;    
		}
		else
		{
			m_bStartRecv = TRUE;
			g_StringLanType(szLan,"设置回调成功!","Please Open COM First!");
			AfxMessageBox(szLan);
		}
		*/
	}
	else
	{
		g_StringLanType(szLan,"已设置回调!","Already Set NakedDataCallBack!");
		AfxMessageBox(szLan);
	}
}

BOOL CDlgPosSerialPortRecvData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
/*	SERIAL_PORT_Init();
	InitSerialPortWnd();

	memset(&m_struIPParaCfgV40, 0, sizeof(m_struIPParaCfgV40));
	memset(&m_struPosFilterCfg, 0, sizeof(m_struPosFilterCfg));
	memset(&m_struConnPosCfg, 0, sizeof(m_struConnPosCfg));
	memset(&m_struChanFilterCfg, 0, sizeof(m_struChanFilterCfg));
	memset(&m_struNakedDataParam, 0, sizeof(m_struNakedDataParam));
	memset(&m_struPosInfo, 0, sizeof(m_struPosInfo));

	AddChanInfo();
	m_comboChanNum.SetCurSel(0);
	
	m_dwChanNum = 1;
	m_dwTheFilterNum = 0;
	GetChanAndRuleInfo(1);

*/	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPosSerialPortRecvData::InitSerialPortWnd()
{
  	CString csStr;
	m_comboSerialPortCom.Clear();
	for (int i=0; i < 10; i++)
	{
		csStr.Format("COM%d", i+1);
		m_comboSerialPortCom.AddString(csStr);
		
	}
	m_comboSerialPortCom.SetCurSel(0);
}

BOOL CDlgPosSerialPortRecvData::OpenComm()
{
/*	COM_PARAM struComParam = {0};
	int iIndex = m_comboSerialPortCom.GetCurSel();
	sprintf(struComParam.szDevice, "COM%d", m_comboSerialPortCom.GetCurSel() + 1);
	struComParam.cByteSize = SerialData8;
	struComParam.cParity = NOPARITY;
	struComParam.cStopBits = ONESTOPBIT;
	struComParam.iBaudRate = CBR_9600;
    struComParam.typeRecv = ENUM_SERIALPORT_NAKED_PROTOCOL;
	if (-1 != m_iComHandle)
	{
		return FALSE;
	}
	m_iComHandle = SERIAL_PORT_OpenComm(&struComParam, NULL, this);
	if (m_iComHandle != -1)
	{
        return TRUE;
	}
	else
	{
		return FALSE;
	}
*/	

		return FALSE;
}

void CDlgPosSerialPortRecvData::OnBtnOpencom() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
  /*  if (m_bOpenComm) //表示已经开启
    {
		SERIAL_PORT_CloseComm(m_iComHandle);
		m_bOpenComm = FALSE;
		g_StringLanType(szLan,"打开COM","Open COM");
		GetDlgItem(IDC_BTN_OPENCOM)->SetWindowText(szLan);
		return;
    }
	else
	{
		if (OpenComm())
		{
			m_bOpenComm = TRUE;
			g_StringLanType(szLan,"打开COM成功","Open the serial port successfully!");
			AfxMessageBox(szLan);
			g_StringLanType(szLan,"关闭COM","Close COM");
			GetDlgItem(IDC_BTN_OPENCOM)->SetWindowText(szLan);
		}
		else
		{
			g_StringLanType(szLan,"COM已经开启","Open the serial port failed!");
			AfxMessageBox(szLan);
			return;
		}
	}
	//开始
*/	
	UpdateData(FALSE);
}

LRESULT CDlgPosSerialPortRecvData::OnChangeDataShow(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);
	char *pReceiveData = (char*)wParam;
	
	int  iChOld = 0x0d0a;
	int  iChNew = 0x0a;
	char szLan[1024] = {0};
	

    memcpy(szLan, pReceiveData, (LPARAM)lParam);
	 m_csRecvData += szLan ;
	m_csRecvData.Replace((LPCTSTR)iChOld,LPCTSTR(iChNew));
	
	UpdateData(FALSE); 
	
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_RECEIVE_DATA);
	int iAllLineNum = pEdit->GetLineCount();
	
	pEdit->LineScroll(iAllLineNum);
	UpdateData(FALSE);     
	
	return NULL;
}


void CDlgPosSerialPortRecvData::AddChanInfo()
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

void CDlgPosSerialPortRecvData::GetChanAndRuleInfo(DWORD dwChanNum)
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
	DWORD dwGroupNum = 0;
	dwGroupNum = (m_struChanFilterCfg.byFilterID - 1) / FILTERRULE_NUM;
	
	//获取规则号
	DWORD dwRuleIndex = (m_struChanFilterCfg.byFilterID -1)%4;
	m_dwTheFilterNum = dwRuleIndex;
	
	
	//获取组号对应的过滤规则
	memset(&m_struPosFilterCfg, 0, sizeof(m_struPosFilterCfg));
	m_struPosFilterCfg.dwSize = sizeof(m_struPosFilterCfg);
	if (!NET_DVR_GetDVRConfig(m_iUserID, NET_DVR_GET_POS_FILTER_CFG,NULL, &m_struPosFilterCfg, sizeof(m_struPosFilterCfg), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "GroupNum[%d]NET_DVR_GET_POS_FILTER_CFG", dwGroupNum);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "GroupNum[%d]:NET_DVR_GET_POS_FILTER_CFG", dwGroupNum);
	}
	
	/*m_csPosName = m_struPosFilterCfg.struFilterCfg[dwRuleIndex].sPosName;
	
	
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
	
	m_comboConnectMode.SetCurSel(m_struConnPosCfg.dwConnectMode);
	
	if (m_struConnPosCfg.dwConnectMode != 2)
	{
		g_StringLanType(szLan,"该接串口方式接受！","Only Support RS232 Mode!");
		AfxMessageBox(szLan);
		return;
	}
	*/
	UpdateData(FALSE);
}



void CDlgPosSerialPortRecvData::OnSelchangeCombochannelnum() 
{
	// TODO: Add your control notification handler code here
	GetChanAndRuleInfo(m_comboChanNum.GetCurSel() + 1);
}

void CDlgPosSerialPortRecvData::OnBtnSaveData() 
{
	// TODO: Add your control notification handler code here

	char szLan[128] = {0};
	if (m_csRecvData.IsEmpty())
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
	myFile.WriteString(m_csRecvData);


	
	//关闭文件
	myFile.Close();
	m_csRecvData = "";
	UpdateData(FALSE);
}

DWORD  GetUpLoadRS232FileThread(LPVOID pParam)
{
	CDlgPosSerialPortRecvData *pThis = ( CDlgPosSerialPortRecvData*)pParam;
	
	DWORD dwState = 0;
	DWORD dwProgress = 0;
	char szLan[256] = {0};
	
	
	while (TRUE)
	{
		dwState = NET_DVR_GetUploadState(pThis->m_lUploadHandle,&dwProgress);
		if (dwState == 1)
		{
			g_StringLanType(szLan, "上传成功", "Upload successfully");
			pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			pThis->m_bUpLoading = FALSE;
			g_StringLanType(szLan,"上传","Upload");
			pThis->GetDlgItem(IDC_BTN_UPLOAD)->SetWindowText(szLan);
			pThis->m_bUpLoading = FALSE;
			break;
		}
		else if (dwState == 2)
		{
			g_StringLanType(szLan, "正在上传,已上传:%d", "Is uploading,progress:%d");
				pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
		}
		else if (dwState == 3)
		{
			g_StringLanType(szLan, "上传失败", "Upload failed");
				pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			break;
		}
		else if (dwState == 4)
		{
			if (dwProgress == 100)
			{
				g_StringLanType(szLan, "上传成功", "Upload successfully");
				pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
				g_StringLanType(szLan,"上传","UpLoad");
				pThis->GetDlgItem(IDC_BTN_UPLOAD)->SetWindowText(szLan);
				pThis->m_bUpLoading = FALSE;
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


void CDlgPosSerialPortRecvData::OnBtnUpload() 
{
	// TODO: Add your control notification handler code here

	if (m_bUpLoading == FALSE)
	{
		
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
		m_hUpLoadThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetUpLoadRS232FileThread),this,0,&dwThreadId);
		if (m_hUpLoadThread  == NULL)
		{
			char szLan[256] = {0};
			g_StringLanType(szLan, "打开长传文件线程失败!", "open UpLoad thread Fail!");
			AfxMessageBox(szLan);
			return;
		}
		g_StringLanType(szLan, "停止上传", "Stop UpLoad");
		GetDlgItem(IDC_BTN_UPLOAD)->SetWindowText(szLan);
		m_bUpLoading = TRUE;
		
	}
	else
	{
		NET_DVR_CloseUploadHandle(m_lUploadHandle);
		m_bUpLoading = FALSE;
	}
  UpdateData(FALSE);
	
}
