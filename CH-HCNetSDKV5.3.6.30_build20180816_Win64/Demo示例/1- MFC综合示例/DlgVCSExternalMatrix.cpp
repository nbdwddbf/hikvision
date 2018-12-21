// DlgVCSExternalMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVCSExternalMatrix.h"
#include "DlgLcdMatrixRelation.h"
#include "DlgLcdMatrixSwitch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVCSExternalMatrix dialog

CDlgVCSExternalMatrix::CDlgVCSExternalMatrix(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVCSExternalMatrix::IDD, pParent)
	, m_iDeviceIndex(-1)
	, m_lUserID(-1)
	, m_iCurMatirx(0)
	, m_pAllMatrixCfgBuf(NULL)	
{
	//{{AFX_DATA_INIT(CDlgVCSExternalMatrix)
	m_bValid = FALSE;
	m_dwInputNum = 0;
	m_csMatrixName = _T("");
	m_dwOutputNum = 0;
	m_dwPort = 0;
	m_dwMatrixID = 0;
	m_dwSerialNum = 0;
	m_BLoop = FALSE;
	//}}AFX_DATA_INIT
}

CDlgVCSExternalMatrix::~CDlgVCSExternalMatrix()
{	
	if (NULL != m_pAllMatrixCfgBuf)
	{
		delete[] m_pAllMatrixCfgBuf;
		m_pAllMatrixCfgBuf = NULL;
	}
}

void CDlgVCSExternalMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVCSExternalMatrix)
	DDX_Control(pDX, IDC_COMBO_EXTERNAL_MATRIX_INDEX, m_cmMatrixIndex);
	DDX_Control(pDX, IDC_COMBO_MATRIX_TYPE, m_cmMatrixType);
	DDX_Control(pDX, IDC_COMBO_MATRIX_CHAN_TYPE, m_cmMatrixChanType);
	DDX_Control(pDX, IDC_IPADDRESS_DIGITAL_MATRIX, m_IPDigtalMatrix);
	DDX_Control(pDX, IDC_COMBO_WORK_TYPE, m_cmWorkType);
	DDX_Control(pDX, IDC_COMBO_STOP_BIT, m_cmStopBit);
	DDX_Control(pDX, IDC_COMBO_PARITY, m_cmParity);
	DDX_Control(pDX, IDC_COMBO_MATRIX_PROTOCOL, m_cmProtocol);
	DDX_Control(pDX, IDC_COMBO_FLOW_CONTROL, m_cmFlowControl);
	DDX_Control(pDX, IDC_COMBO_DATA_BIT, m_cmDataBit);
	DDX_Control(pDX, IDC_COMBO_BAUD_RATE, m_cmBaudRate);
	DDX_Check(pDX, IDC_CHECK_VALID, m_bValid);
	DDX_Text(pDX, IDC_EDIT_INPUT_NUM, m_dwInputNum);
	DDX_Text(pDX, IDC_EDIT_MATRIX_NAME, m_csMatrixName);
	DDX_Text(pDX, IDC_EDIT_OUTPUT_NUM, m_dwOutputNum);
	DDX_Text(pDX, IDC_EDIT_PORT, m_dwPort);
	DDV_MinMaxDWord(pDX, m_dwPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_MATRIX_ID, m_dwMatrixID);
	DDX_Text(pDX, IDC_EDT_232_SERIALNUM, m_dwSerialNum);
	DDX_Check(pDX, IDC_CHK_232LOOP, m_BLoop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVCSExternalMatrix, CDialog)
	//{{AFX_MSG_MAP(CDlgVCSExternalMatrix)
	ON_BN_CLICKED(IDC_BTN_GET_ALL_MATRIX, OnBtnGetAllMatrix)
	ON_BN_CLICKED(IDC_BTN_GET_SINGLE_MATRIX, OnBtnGetSingleMatrix)
	ON_BN_CLICKED(IDC_BTN_SET_MATRIX, OnBtnSetMatrix)
	ON_CBN_SELCHANGE(IDC_COMBO_MATRIX_TYPE, OnSelchangeComboMatrixType)
	ON_CBN_SELCHANGE(IDC_COMBO_EXTERNAL_MATRIX_INDEX, OnSelchangeComboExternalMatrixIndex)
	ON_BN_CLICKED(IDC_BTN_RELATION, OnBtnRelation)
	ON_BN_CLICKED(IDC_BTN_MATRIX_SWITCH, OnBtnMatrixSwitch)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_CHK_232LOOP, OnChk232loop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVCSExternalMatrix message handlers

BOOL CDlgVCSExternalMatrix::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	DWORD nLen = sizeof(m_strMatrixCfg)+4;
	m_pAllMatrixCfgBuf = new char[nLen];
	memset(m_pAllMatrixCfgBuf, 0, nLen);
	
	memset(&m_strMatrixCfg, 0, sizeof(m_strMatrixCfg));
	
	m_cmMatrixIndex.ResetContent();
	int iMatrixCount = 0;
	for (int i=0; i<4; i++)
	{
		sprintf(m_szLan, "Matrix%d", i+1);
		m_cmMatrixIndex.AddString(m_szLan);
	}

	m_iCurMatirx = 0;
	m_cmMatrixIndex.SetCurSel(0);

	//InitListWnd();
	InitComboWnd();
	OnBtnGetAllMatrix();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVCSExternalMatrix::InitListWnd() 
{
// 	UpdateData(TRUE);
// 	int iMatrixIndex = m_cmMatrixIndex.GetCurSel();
// 	m_listAssociateOutput.DeleteAllItems();
// 	char sTemp[128] = {0};
// 
// 	GetInputSignalList();
// 	m_dwInputNum = m_struInputSignalList.dwInputSignalNums;
// 	m_dwFreeSignal = 0;
// 	for (int i=0; i<m_dwInputNum; i++)
// 	{
// 		//输入类型
// 		if (NET_DVR_CAM_BNC == m_lpInputSignal[i].byCamMode)
// 		{
// 			sprintf(sTemp, "BNC");
// 		}
// 		else if(NET_DVR_CAM_VGA == m_lpInputSignal[i].byCamMode)
// 		{
// 			sprintf(sTemp, "VGA");
// 		}
// 		else if(NET_DVR_CAM_HDMI  == m_lpInputSignal[i].byCamMode)
// 		{
// 			sprintf(sTemp, "HDMI");
// 		}
// 		else if(NET_DVR_CAM_DVI == m_lpInputSignal[i].byCamMode)
// 		{
// 			sprintf(sTemp, "DVI");
// 		}
// 		else
// 		{
// 			continue;
// 		}
// 		//输入索引
// 		sprintf(m_szLan, "%d", m_lpInputSignal[i].wInputNo + 1);
// 		m_listAssociateOutput.InsertItem(m_dwFreeSignal, m_szLan, 0);
// 
// 		m_listAssociateOutput.SetItemText(m_dwFreeSignal, 1, sTemp);
// 
// 		sprintf(sTemp, "%d", 0);
// 		m_listAssociateOutput.SetItemText(m_dwFreeSignal, 2, sTemp);
// 		m_dwFreeSignal ++;
// 	}
// 
// 	int iItemNum = m_listAssociateOutput.GetItemCount() + 1;
// 	//显示已经被绑定的信号源
// 	for (i=0; i<MAX_CAM_COUNT; i++)
// 	{
// 		//找到输入源序号
// 		if(m_strMatrixCfg[iMatrixIndex].wMatrixOutputChanRef[i]>0)
// 		{
// 			sprintf(m_szLan, "%d", i + 1);
// 			m_listAssociateOutput.InsertItem(iItemNum, m_szLan, 0);
// 			
// 			sprintf(sTemp, "绑定矩阵");
// 			m_listAssociateOutput.SetItemText(iItemNum, 1, sTemp);
// 			
// 			sprintf(sTemp, "%s%d, %s%d", "Matrix", iMatrixIndex, "Channel", m_strMatrixCfg[iMatrixIndex].wMatrixOutputChanRef[i]);
// 			m_listAssociateOutput.SetItemText(iItemNum, 2, sTemp);
// 			iItemNum ++;
// 		}
// 	}
}

void CDlgVCSExternalMatrix::InitComboWnd() 
{
	m_cmMatrixChanType.ResetContent();
	//矩阵通道类型
	m_cmMatrixChanType.AddString("BNC");
	m_cmMatrixChanType.AddString("VGA");
	m_cmMatrixChanType.AddString("RGB");
	m_cmMatrixChanType.AddString("DVI");
	//矩阵协议	
	m_cmProtocol.ResetContent();
	m_cmProtocol.AddString("ZT1.0");
	m_cmProtocol.AddString("ZT2.0");
	m_cmProtocol.AddString("Extron");
	m_cmProtocol.AddString("Creator");
}


void CDlgVCSExternalMatrix::OnBtnGetAllMatrix() 
{
	// TODO: Add your control notification handler code here
	//获取所有外接矩阵信息
	DWORD dwGetCount = 0;
	int i = 0;
	for (i=0; i<4; i++)
	{
		m_strMatrixCfg[i].dwSize = sizeof(NET_DVR_EXTERNAL_MATRIX_CFG);
	}
	if(!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_EXTERNAL_MATRIX_CFG, 0xffffffff, NULL, 0, NULL , m_pAllMatrixCfgBuf, 4+4*sizeof(NET_DVR_EXTERNAL_MATRIX_CFG)))
	{
		g_StringLanType(m_szLan, "获取所有矩阵配置失败", "Get All Matrix Config failed");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, m_szLan);
		return;
	}
	else
	{
		g_StringLanType(m_szLan, "获取所有矩阵配置成功", "Get All Matrix Config successful");
		dwGetCount = *(DWORD*)m_pAllMatrixCfgBuf;
		memcpy(&m_strMatrixCfg, m_pAllMatrixCfgBuf+4, dwGetCount*sizeof(NET_DVR_EXTERNAL_MATRIX_CFG));
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, m_szLan);
	}

	//m_cmMatrixIndex.ResetContent();
	for (i=0; i<dwGetCount; i++)
	{
// 		sprintf(m_szLan, "Matrix%d", i+1);
// 		m_cmMatrixIndex.AddString(m_szLan);
		m_cmMatrixIndex.SetItemData(i, m_strMatrixCfg[i].dwMatrixID);
	}
	m_cmMatrixIndex.SetCurSel(0);
	UpdateData(FALSE);
	InitListWnd();
	SetMatrixToDlg();
}

void CDlgVCSExternalMatrix::OnBtnGetSingleMatrix() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iIndex = m_cmMatrixIndex.GetCurSel();
	DWORD dwStatus = 0;
	m_strMatrixCfg[iIndex].dwSize = sizeof(NET_DVR_EXTERNAL_MATRIX_CFG);
//	DWORD dwMatrixID = m_cmMatrixIndex.GetItemData(iIndex);
    DWORD dwMatrixID = m_dwMatrixID; 
	if(!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_EXTERNAL_MATRIX_CFG, 1, &dwMatrixID, 4, &dwStatus , &m_strMatrixCfg[iIndex], sizeof(NET_DVR_EXTERNAL_MATRIX_CFG)))
	{
		g_StringLanType(m_szLan, "获取矩阵配置失败", "Get Matrix Config failed");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, m_szLan);
		return;
	}
	else
	{
		g_StringLanType(m_szLan, "获取矩阵配置成功", "Get Matrix Config successful");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, m_szLan);
	}
	SetMatrixToDlg();
	UpdateData(FALSE);
}

void CDlgVCSExternalMatrix::GetMatrixFromDlg()
{
	UpdateData(TRUE);
	int iIndex = m_iCurMatirx;
	int iMatrixType = m_cmMatrixType.GetCurSel();
	m_strMatrixCfg[iIndex].byValid = m_bValid;
	sprintf((char*)m_strMatrixCfg[iIndex].sMatrixName, "%s", m_csMatrixName);
	m_strMatrixCfg[iIndex].wMatrixInputChanNum = m_dwInputNum;
	m_strMatrixCfg[iIndex].wMatrixOutputChanNum = m_dwOutputNum;
	m_strMatrixCfg[iIndex].byMatrixChanType = m_cmMatrixChanType.GetCurSel() + 1;
	m_strMatrixCfg[iIndex].byMatrixProtocol= m_cmProtocol.GetCurSel() + 1;
	m_strMatrixCfg[iIndex].dwMatrixID = m_dwMatrixID;
	if (0 == iMatrixType)
	{
		m_strMatrixCfg[iIndex].byMatrixType = 1;
        memset(&m_strMatrixCfg[iIndex].struMatrixUnion.struAnalogMatrix, 0, sizeof(m_strMatrixCfg[iIndex].struMatrixUnion.struAnalogMatrix)); 
        if ( m_BLoop )
        {
            m_strMatrixCfg[iIndex].struMatrixUnion.struAnalogMatrix.bySerPortNum = 0xff; 
        }
        else
        {
            m_strMatrixCfg[iIndex].struMatrixUnion.struAnalogMatrix.bySerPortNum = m_dwSerialNum; 
            m_strMatrixCfg[iIndex].struMatrixUnion.struAnalogMatrix.struRS232.dwBaudRate = m_cmBaudRate.GetCurSel();
            m_strMatrixCfg[iIndex].struMatrixUnion.struAnalogMatrix.struRS232.byDataBit= m_cmDataBit.GetCurSel();
            m_strMatrixCfg[iIndex].struMatrixUnion.struAnalogMatrix.struRS232.byStopBit = m_cmStopBit.GetCurSel();
            m_strMatrixCfg[iIndex].struMatrixUnion.struAnalogMatrix.struRS232.byParity = m_cmParity.GetCurSel();
            m_strMatrixCfg[iIndex].struMatrixUnion.struAnalogMatrix.struRS232.byFlowcontrol = m_cmFlowControl.GetCurSel();
		    m_strMatrixCfg[iIndex].struMatrixUnion.struAnalogMatrix.struRS232.dwWorkMode = m_cmWorkType.GetCurSel();    	
        }
	
	}
	else if(1 == iMatrixType)
	{
		m_strMatrixCfg[iIndex].byMatrixType = 2;
		DWORD dwIP;
		m_IPDigtalMatrix.GetAddress(dwIP);
		sprintf((char*)m_strMatrixCfg[iIndex].struMatrixUnion.struDigitalMatrix.struAddress.sIpV4,  "%s", IPToStr(dwIP));
		m_strMatrixCfg[iIndex].struMatrixUnion.struDigitalMatrix.wPort = m_dwPort;
	}
}

void CDlgVCSExternalMatrix::OnBtnSetMatrix() 
{
	// TODO: Add your control notification handler code here
	//int iIndex = m_cmMatrixID.GetCurSel();
	GetMatrixFromDlg();
	int i=0;
	int iIndex = m_cmMatrixIndex.GetCurSel();
	m_strMatrixCfg[m_iCurMatirx].dwSize = sizeof(NET_DVR_EXTERNAL_MATRIX_CFG);
	//DWORD dwMatrixID = m_cmMatrixIndex.GetItemData(iIndex);
	if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_EXTERNAL_MATRIX_CFG, 1, &m_dwMatrixID, sizeof(DWORD), &m_lpStatusList, &m_strMatrixCfg[m_iCurMatirx], sizeof(NET_DVR_EXTERNAL_MATRIX_CFG)))
	{
		g_StringLanType(m_szLan, "修改矩阵配置失败", "set matrix config failed");
		for (i=0; i<1; i++)
		{
			sprintf(m_szLan, "m_lpStatusList[%d] = %d", i, m_lpStatusList[i]);
		}
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, m_szLan);
		return;
	}
	else
	{
		g_StringLanType(m_szLan, "修改矩阵配置成功", "set matrix config successful");
		for (i=0; i<1; i++)
		{
			sprintf(m_szLan, "m_lpStatusList[%d] = %d", i, m_lpStatusList[i]);
		}
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, m_szLan);
	}
}

void CDlgVCSExternalMatrix::OnSelchangeComboMatrixType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iIndex = m_cmMatrixIndex.GetCurSel();
	int iMatrixType = m_cmMatrixType.GetCurSel();
	if (0 == iMatrixType)
	{
		GetDlgItem(IDC_IPADDRESS_DIGITAL_MATRIX)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_COMBO_WORK_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_STOP_BIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_PARITY)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_FLOW_CONTROL)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DATA_BIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_BAUD_RATE)->EnableWindow(TRUE);
		
        if (m_strMatrixCfg[iIndex].struMatrixUnion.struAnalogMatrix.bySerPortNum == 0xff)
        {
            m_BLoop = TRUE;     
        }
        else
        {
            m_BLoop = FALSE; 
            m_dwSerialNum = m_strMatrixCfg[iIndex].struMatrixUnion.struAnalogMatrix.bySerPortNum; 
            UpdateData(FALSE); 
            m_cmBaudRate.SetCurSel(m_strMatrixCfg[iIndex].struMatrixUnion.struAnalogMatrix.struRS232.dwBaudRate);
            m_cmDataBit.SetCurSel(m_strMatrixCfg[iIndex].struMatrixUnion.struAnalogMatrix.struRS232.byDataBit);
            m_cmStopBit.SetCurSel(m_strMatrixCfg[iIndex].struMatrixUnion.struAnalogMatrix.struRS232.byStopBit);
            m_cmParity.SetCurSel(m_strMatrixCfg[iIndex].struMatrixUnion.struAnalogMatrix.struRS232.byParity);
            m_cmFlowControl.SetCurSel(m_strMatrixCfg[iIndex].struMatrixUnion.struAnalogMatrix.struRS232.byFlowcontrol);
		    m_cmWorkType.SetCurSel(m_strMatrixCfg[iIndex].struMatrixUnion.struAnalogMatrix.struRS232.dwWorkMode);
        }
        ChangeAnlogLoopDlg(); 
       
	}
	else if (1 == iMatrixType)
	{
		GetDlgItem(IDC_IPADDRESS_DIGITAL_MATRIX)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_COMBO_WORK_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_STOP_BIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PARITY)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_FLOW_CONTROL)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DATA_BIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_BAUD_RATE)->EnableWindow(FALSE);
		
		DWORD dwIpAddr = ntohl(inet_addr(m_strMatrixCfg[iIndex].struMatrixUnion.struDigitalMatrix.struAddress.sIpV4));
		m_IPDigtalMatrix.SetAddress(dwIpAddr);
		m_dwPort = m_strMatrixCfg[iIndex].struMatrixUnion.struDigitalMatrix.wPort;
	}
	UpdateData(FALSE);
}

void CDlgVCSExternalMatrix::OnSelchangeComboExternalMatrixIndex() 
{
	// TODO: Add your control notification handler code here
	GetMatrixFromDlg();
	SetMatrixToDlg();
}

void CDlgVCSExternalMatrix::SetMatrixToDlg() 
{
	UpdateData(TRUE);
	int iIndex = m_cmMatrixIndex.GetCurSel();
	m_dwMatrixID = m_strMatrixCfg[iIndex].dwMatrixID;
	m_bValid = m_strMatrixCfg[iIndex].byValid;
	m_csMatrixName.Format("%s", m_strMatrixCfg[iIndex].sMatrixName);
	m_dwInputNum = m_strMatrixCfg[iIndex].wMatrixInputChanNum;
	m_dwOutputNum = m_strMatrixCfg[iIndex].wMatrixOutputChanNum;
	m_cmMatrixChanType.SetCurSel(m_strMatrixCfg[iIndex].byMatrixChanType - 1);
	m_cmProtocol.SetCurSel(m_strMatrixCfg[iIndex].byMatrixProtocol - 1);
	m_cmMatrixType.SetCurSel(m_strMatrixCfg[iIndex].byMatrixType - 1);
// 	for (int i=0; i<m_dwFreeSignal; i++)
// 	{
// 		sprintf(m_szLan, "%d", m_strMatrixCfg[iIndex].wMatrixOutputChanRef[i]);
// 		m_listAssociateOutput.SetItemText(i, 2, m_szLan);
// 	}
	UpdateData(FALSE);
	OnSelchangeComboMatrixType();
	m_iCurMatirx = iIndex;
}

void CDlgVCSExternalMatrix::OnBtnRelation() 
{
	// TODO: Add your control notification handler code here
	CDlgLcdMatrixRelation dlg;
    int iMatrixSel = m_cmMatrixIndex.GetCurSel();
    if (iMatrixSel == CB_ERR)
    {
        g_StringLanType(m_szLan, "请选择一个矩阵", "Please select a matrix");
        return;
    }

    dlg.m_lpMatrixInfo = &m_strMatrixCfg[iMatrixSel];
    dlg.DoModal();
}

void CDlgVCSExternalMatrix::OnBtnMatrixSwitch() 
{
	// TODO: Add your control notification handler code here
	CDlgLcdMatrixSwitch dlg;
    dlg.m_lUserId = m_lUserID;
    dlg.m_dwMatrixId = m_cmMatrixIndex.GetItemData(m_cmMatrixIndex.GetCurSel());

    dlg.DoModal();
}

void CDlgVCSExternalMatrix::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
    CDialog::OnCancel();
}

void CDlgVCSExternalMatrix::ChangeAnlogLoopDlg()
{
    
    // TODO: Add your control notification handler code here
    GetDlgItem(IDC_EDT_232_SERIALNUM)->EnableWindow(FALSE); 
    GetDlgItem(IDC_COMBO_BAUD_RATE)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_DATA_BIT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_STOP_BIT)->EnableWindow(FALSE); 
    GetDlgItem(IDC_COMBO_PARITY)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_FLOW_CONTROL)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_WORK_TYPE)->EnableWindow(FALSE);
    if (! m_BLoop )
    {
        GetDlgItem(IDC_EDT_232_SERIALNUM)->EnableWindow(TRUE); 
        GetDlgItem(IDC_COMBO_BAUD_RATE)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_DATA_BIT)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_STOP_BIT)->EnableWindow(TRUE); 
        GetDlgItem(IDC_COMBO_PARITY)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_FLOW_CONTROL)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_WORK_TYPE)->EnableWindow(TRUE); 
    }
}

void CDlgVCSExternalMatrix::OnChk232loop() 
{
   UpdateData(TRUE);
   ChangeAnlogLoopDlg(); 
}
