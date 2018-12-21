// DlgSerialCfg.cpp : implementation file
//
/**********************************************************
FileName:    DlgSerialCfg.cpp
Description: 232和485串口信息配置      
Date:        
Note: 		<全局>结构体,宏见GeneralDef.h, 全局变量,函数见config.cpp   
Modification History:      
<version>   <time>         <desc>

***********************************************************/

#include "stdafx.h"
#include "config.h"
#include "DlgSerialCfg.h"
#include "DlgPPPCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSerialCfg dialog


CDlgSerialCfg::CDlgSerialCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSerialCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSerialCfg)
	m_iDecodeAddr=0;
	//m_iChanNum=g_struDeviceInfo[0].iDeviceChanNum;//获取设备的通道数
	//}}AFX_DATA_INIT
}


void CDlgSerialCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSerialCfg)
	DDX_Control(pDX, IDC_COMBO_232_BAUD, m_combo232Baud);
	DDX_Control(pDX, IDC_COMBO_232_CHECK_BIT, m_combo232CheckBit);
	DDX_Control(pDX, IDC_COMBO_232_DATA_BIT, m_combo232DataBit);
	DDX_Control(pDX, IDC_COMBO_232_STOP_BIT, m_combo232StopBit);
	DDX_Control(pDX, IDC_COMBO_232_FLOW, m_combo232Flow);
	DDX_Control(pDX, IDC_COMBO_232_OPERATE_MODE, m_combo232OperateMode);	
	
	DDX_Control(pDX, IDC_COMBO_485_CHANNEL, m_comboChannel);
	DDX_Control(pDX, IDC_COMBO_485_BAUD, m_combo485Baud);
	DDX_Control(pDX, IDC_COMBO_485_DATA_BIT, m_combo485DataBit);
	DDX_Control(pDX, IDC_COMBO_485_STOP_BIT, m_combo485StopBit);
	DDX_Control(pDX, IDC_COMBO_485_CHECK_BIT, m_combo485CheckBit);
	DDX_Control(pDX, IDC_COMBO_485_FLOW, m_combo485Flow);
	DDX_Control(pDX, IDC_COMBO_DECODE_TYPE, m_combo485DecodeType);
	DDX_Text(pDX, IDC_EDIT_DECODE_ADDRESS, m_iDecodeAddr);
	DDX_Control(pDX, IDC_COMBO_485_COPY_CFG, m_combo485CfgCopy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSerialCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgSerialCfg)
	ON_CBN_SELCHANGE(IDC_COMBO_485_CHANNEL, OnCbnSelchangeCombo485Channel)
	ON_BN_CLICKED(IDC_BTN_485_OK, OnBnClickedBtn485Ok)
	ON_CBN_SELCHANGE(IDC_COMBO_232_OPERATE_MODE, OnCbnSelchangeCombo232OperateMode)
	ON_BN_CLICKED(ID_BTN_SERIAL_232_OK, OnBnClickedBtn232Ok)
	ON_BN_CLICKED(IDC_BTN_485_COPY, OnBnClickedBtn485Copy)
	ON_BN_CLICKED(IDC_BTN_PPP_SETUP, OnBnClickedBtnPppSetup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSerialCfg message handlers

/*********************************************************
Function:	GetRS232Cfg
Desc:		获得232串口的参数信息
Input:	
Output:	
Return:	
**********************************************************/
void CDlgSerialCfg::GetRS232Cfg()
{
	if (g_lUserID < 0)
	{
		return;
	}

	DWORD dwReturned = 0;
    if (!NET_DVR_GetDVRConfig(g_lUserID, NET_DVR_GET_RS232CFG_V30, 0,&m_struRS232Cfg, sizeof(NET_DVR_RS232CFG_V30), &dwReturned))
	{
		MessageBox("获取232串口配置参数失败!");
	}
	m_combo232Baud.SetCurSel(m_struRS232Cfg.struRs232[0].dwBaudRate);
	m_combo232DataBit.SetCurSel(m_struRS232Cfg.struRs232[0].byDataBit);
	m_combo232StopBit.SetCurSel(m_struRS232Cfg.struRs232[0].byStopBit);
	m_combo232CheckBit.SetCurSel(m_struRS232Cfg.struRs232[0].byParity);
	m_combo232Flow.SetCurSel(m_struRS232Cfg.struRs232[0].byFlowcontrol);
	m_combo232OperateMode.SetCurSel(m_struRS232Cfg.struRs232[0].dwWorkMode);
	if (m_struRS232Cfg.struRs232[0].dwWorkMode == 0)//串口1对应采用窄带
	{
		GetDlgItem(IDC_BTN_PPP_SETUP)->EnableWindow(TRUE);
	}
	else//控制台或透明通道模式
	{
		GetDlgItem(IDC_BTN_PPP_SETUP)->EnableWindow(FALSE);
	}
	GetDlgItem(ID_BTN_SERIAL_232_OK)->EnableWindow(TRUE);
	UpdateData(FALSE);//这句可有可无，因为combobox不用update就可以显示出来。这个函数里面只包含6个combobox。

}

/*********************************************************
Function:	GetRS485Cfg
Desc:		获得485串口的参数信息
Input:	
Output:	
Return:	
**********************************************************/
void CDlgSerialCfg::GetRS485Cfg()
{
	if (g_lUserID < 0)
	{
		return;
	}

	//解码器类型，9000设备减少了一些。下面这段代码是判断解码器类型的，考虑9000设备。
	char szPtz[DESC_LEN+1] = {0};
	memset(&m_struPtzCfg, 0, sizeof(NET_DVR_PTZCFG));
	if (!NET_DVR_GetPTZProtocol(g_lUserID, &m_struPtzCfg))
	{		
		MessageBox("解码器类型获取失败");
		//g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetPTZProtocol");
	}
	else
	{
		//g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetPTZProtocol");
		m_combo485DecodeType.ResetContent();
		for ( UINT i=0; i< m_struPtzCfg.dwPtzNum; i++)
		{
			memset(szPtz, 0, DESC_LEN);
			memcpy(szPtz, m_struPtzCfg.struPtz[i].byDescribe, DESC_LEN);
			m_combo485DecodeType.AddString(szPtz);		
		}
	}

	DWORD dwReturned = 0;
	int iCopyIndex = 0;
	m_iChanNum=g_struDeviceInfo[0].iDeviceChanNum;//获取设备的通道数

	m_comboChannel.ResetContent();//登陆不同设备时，删除combobox里面的上一轮的记录。不可或缺。
	m_combo485CfgCopy.ResetContent();//登陆不同设备时，删除combobox里面的上一轮的记录。

	m_combo485CfgCopy.AddString("全部通道");
	m_combo485CfgCopy.SetItemData(iCopyIndex, -1);	
	

	for (int i=0; i<m_iChanNum; i++)//目前只有模拟通道可以设置ptz参数
	{

		iChanShow = i+g_struDeviceInfo[0].iStartChan;
		CString sTemp;
		sTemp.Format("%s%d", "通道", iChanShow);


		if (g_struDeviceInfo[0].struChanInfo[i].bEnable)
		{
			m_comboChannel.AddString(sTemp);
		    m_comboChannel.SetItemData(iCopyIndex, i);
			
	        iCopyIndex++;
		    m_combo485CfgCopy.AddString(sTemp);
		    m_combo485CfgCopy.SetItemData(iCopyIndex, i);
		    if (!NET_DVR_GetDVRConfig(g_lUserID, NET_DVR_GET_DECODERCFG_V30, iChanShow, &m_stru485DecoderCfg[i], sizeof(NET_DVR_DECODERCFG_V30), &dwReturned))
			{
				AfxMessageBox("获取485串口参数失败！");	
			}
		}
        //直接将第一个使能通道（一般是通道1）的设置先显示出来，再进行for循环。否则从注册到显示出来会感觉有一段时间的延时。
		if(i==g_struDeviceInfo[0].lFirstEnableChanIndex)//从第一个使能通道开始先显示。
		{
			m_combo485Baud.SetCurSel(m_stru485DecoderCfg[i].dwBaudRate);
			m_combo485DataBit.SetCurSel(m_stru485DecoderCfg[i].byDataBit);
			m_combo485StopBit.SetCurSel(m_stru485DecoderCfg[i].byStopBit);
			m_combo485CheckBit.SetCurSel(m_stru485DecoderCfg[i].byParity);
			m_combo485Flow.SetCurSel(m_stru485DecoderCfg[i].byFlowcontrol);
			m_combo485DecodeType.SetCurSel(m_stru485DecoderCfg[i].wDecoderType);
			m_iDecodeAddr = (BYTE)m_stru485DecoderCfg[i].wDecoderAddress;
			GetDlgItem(IDC_BTN_485_COPY)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_485_OK)->EnableWindow(TRUE);	
			m_comboChannel.SetCurSel(0);
			m_combo485CfgCopy.SetCurSel(0);
	        UpdateData(FALSE);
		}
	}
}

/*********************************************************
  Function:	OnCbnSelchangeCombo485Channel
  Desc:		485串口对应通道的选择,并更新对应的参数
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgSerialCfg::OnCbnSelchangeCombo485Channel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iSel = m_comboChannel.GetCurSel();
	int m_iCurChanIndex = m_comboChannel.GetItemData(iSel);	
	
	m_combo485Baud.SetCurSel(m_stru485DecoderCfg[m_iCurChanIndex].dwBaudRate);
	m_combo485DataBit.SetCurSel(m_stru485DecoderCfg[m_iCurChanIndex].byDataBit);
	m_combo485StopBit.SetCurSel(m_stru485DecoderCfg[m_iCurChanIndex].byStopBit);
	m_combo485CheckBit.SetCurSel(m_stru485DecoderCfg[m_iCurChanIndex].byParity);
	m_combo485Flow.SetCurSel(m_stru485DecoderCfg[m_iCurChanIndex].byFlowcontrol);
	m_combo485DecodeType.SetCurSel(m_stru485DecoderCfg[m_iCurChanIndex].wDecoderType);
	m_iDecodeAddr = (BYTE)m_stru485DecoderCfg[m_iCurChanIndex].wDecoderAddress;
	UpdateData(FALSE);	
}

/*********************************************************
Function:	OnBnClickedBtn485Ok
Desc:		设置485串口参数
Input:	
Output:	
Return:	
**********************************************************/
void CDlgSerialCfg::OnBnClickedBtn485Ok() 
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}
	UpdateData(TRUE);

	int m_iCurChanIndex = m_comboChannel.GetItemData(m_comboChannel.GetCurSel());

	m_stru485DecoderCfg[m_iCurChanIndex].dwBaudRate = m_combo485Baud.GetCurSel();
	m_stru485DecoderCfg[m_iCurChanIndex].byDataBit = m_combo485DataBit.GetCurSel();
	m_stru485DecoderCfg[m_iCurChanIndex].byStopBit = m_combo485StopBit.GetCurSel();
	m_stru485DecoderCfg[m_iCurChanIndex].byParity = m_combo485CheckBit.GetCurSel();
	m_stru485DecoderCfg[m_iCurChanIndex].byFlowcontrol = m_combo485Flow.GetCurSel();
	m_stru485DecoderCfg[m_iCurChanIndex].wDecoderType = m_combo485DecodeType.GetCurSel();
	m_stru485DecoderCfg[m_iCurChanIndex].wDecoderAddress = m_iDecodeAddr;
	if (NET_DVR_SetDVRConfig(g_lUserID, NET_DVR_SET_DECODERCFG_V30, m_iCurChanIndex+1, &m_stru485DecoderCfg[m_iCurChanIndex], sizeof(NET_DVR_DECODERCFG_V30)))
	{
		AfxMessageBox("设置485串口参数成功！");	
	} 
	else
	{
		AfxMessageBox("设置485串口参数失败！");	
	}		
}

/*********************************************************
Function:	OnCbnSelchangeCombo232OperateMode
Desc:		232串口操作模式的选择,并刷新对应控件的状态
Input:	
Output:	
Return:	
**********************************************************/
void CDlgSerialCfg::OnCbnSelchangeCombo232OperateMode() 
{
	UpdateData(TRUE);
	int iOperateSel = 0;
	iOperateSel = m_combo232OperateMode.GetCurSel();
	if (0 == iOperateSel)
	{
		GetDlgItem(IDC_BTN_PPP_SETUP)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_PPP_SETUP)->EnableWindow(FALSE);
	}	
}

/*********************************************************
Function:	OnBnClickedBtn232Ok
Desc:		设置232串口参数
Input:	
Output:	
Return:	
**********************************************************/
void CDlgSerialCfg::OnBnClickedBtn232Ok() 
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}
	UpdateData(TRUE);
	m_struRS232Cfg.struRs232[0].dwBaudRate = m_combo232Baud.GetCurSel();
	m_struRS232Cfg.struRs232[0].byDataBit = m_combo232DataBit.GetCurSel();
	m_struRS232Cfg.struRs232[0].byStopBit = m_combo232StopBit.GetCurSel();
	m_struRS232Cfg.struRs232[0].byParity = m_combo232CheckBit.GetCurSel();
	m_struRS232Cfg.struRs232[0].byFlowcontrol = m_combo232Flow.GetCurSel();
	m_struRS232Cfg.struRs232[0].dwWorkMode = m_combo232OperateMode.GetCurSel();
	if(NET_DVR_SetDVRConfig(g_lUserID, NET_DVR_SET_RS232CFG_V30, 0,&m_struRS232Cfg, sizeof(NET_DVR_RS232CFG_V30)))
	{
		AfxMessageBox("设置232串口参数成功！");	
	} 
	else
	{
		AfxMessageBox("设置232串口参数失败！");	
	}
}

/*********************************************************
Function:	OnBnClickedBtn485Copy
Desc:		复制选中通道的485串口配置到对应的通道
Input:	
Output:	
Return:	
**********************************************************/
void CDlgSerialCfg::OnBnClickedBtn485Copy() 
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}
	
	UpdateData(TRUE);
	int m_iCurChanIndex = m_comboChannel.GetItemData(m_comboChannel.GetCurSel());
	int m_iCopyChanIndex = m_combo485CfgCopy.GetItemData(m_combo485CfgCopy.GetCurSel());
	if (m_iCopyChanIndex == m_iCurChanIndex)
	{
		AfxMessageBox("通道相同，不用复制！");
		return;
	}
	if (m_iCopyChanIndex == -1)
	{
		for (int i=0; i<m_iChanNum; i++)
		{
			m_stru485DecoderCfg[i].dwBaudRate = m_combo485Baud.GetCurSel();
			m_stru485DecoderCfg[i].byDataBit = m_combo485DataBit.GetCurSel();
			m_stru485DecoderCfg[i].byStopBit = m_combo485StopBit.GetCurSel();
			m_stru485DecoderCfg[i].byParity = m_combo485CheckBit.GetCurSel();
			m_stru485DecoderCfg[i].byFlowcontrol = m_combo485Flow.GetCurSel();
			m_stru485DecoderCfg[i].wDecoderType = m_combo485DecodeType.GetCurSel();
			m_stru485DecoderCfg[i].wDecoderAddress = m_iDecodeAddr;

			NET_DVR_SetDVRConfig(g_lUserID, NET_DVR_SET_DECODERCFG_V30, i+1, &m_stru485DecoderCfg[i], sizeof(NET_DVR_DECODERCFG_V30));

		}
		if (NET_DVR_SetDVRConfig(g_lUserID, NET_DVR_SET_DECODERCFG_V30, m_iChanNum, &m_stru485DecoderCfg[m_iChanNum-1], sizeof(NET_DVR_DECODERCFG_V30)))
		{
			AfxMessageBox("复制485参数到全部通道成功！");	
		} 
		else
		{
			AfxMessageBox("复制485参数到全部通道失败！");	
		}		
	}
	else
	{				
		m_stru485DecoderCfg[m_iCopyChanIndex].dwBaudRate = m_combo485Baud.GetCurSel();
		m_stru485DecoderCfg[m_iCopyChanIndex].byDataBit = m_combo485DataBit.GetCurSel();
		m_stru485DecoderCfg[m_iCopyChanIndex].byStopBit = m_combo485StopBit.GetCurSel();
		m_stru485DecoderCfg[m_iCopyChanIndex].byParity = m_combo485CheckBit.GetCurSel();
		m_stru485DecoderCfg[m_iCopyChanIndex].byFlowcontrol = m_combo485Flow.GetCurSel();
		m_stru485DecoderCfg[m_iCopyChanIndex].wDecoderType = m_combo485DecodeType.GetCurSel();
		m_stru485DecoderCfg[m_iCopyChanIndex].wDecoderAddress = m_iDecodeAddr;

		if (NET_DVR_SetDVRConfig(g_lUserID, NET_DVR_SET_DECODERCFG_V30, m_iCopyChanIndex+1, &m_stru485DecoderCfg[m_iCopyChanIndex], sizeof(NET_DVR_DECODERCFG_V30)))
		{
			AfxMessageBox("复制485串口参数成功！");	
		} 
		else
		{
			AfxMessageBox("复制485串口参数失败！");	
		}
	}
}

/*********************************************************
Function:	OnBnClickedBtnPppSetup
Desc:		PPP电话拨号配置
Input:	none
Output:	none
Return:	none	
**********************************************************/
void CDlgSerialCfg::OnBnClickedBtnPppSetup() 
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}
	CDlgPPPCfg dlg;
	memcpy(&(dlg.m_struPPPConfig), &(m_struRS232Cfg.struPPPConfig), sizeof(NET_DVR_PPPCFG_V30));
	if (dlg.DoModal() == IDOK)
	{
		memcpy(&(m_struRS232Cfg.struPPPConfig), &(dlg.m_struPPPConfig), sizeof(NET_DVR_PPPCFG_V30));
	
        m_struRS232Cfg.struRs232[0].dwWorkMode = m_combo232OperateMode.GetCurSel();

	    if(NET_DVR_SetDVRConfig(g_lUserID, NET_DVR_SET_RS232CFG_V30, 0,&m_struRS232Cfg, sizeof(NET_DVR_RS232CFG_V30)))
		{
		    AfxMessageBox("设置窄带参数成功！");	
		} 
	    else
		{
		    AfxMessageBox("设置窄带参数失败！");	
		}
	}
}
