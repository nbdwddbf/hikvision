/**********************************************************
FileName:    DlgSerialTrans.cpp
Description: send serialportdata via transparent channel      
Date:        2008/06/03
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/06/03>       <created>
***********************************************************/

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSerialTrans.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransparentTrans dialog
CTransparentTrans *TransDlg = NULL;

/*********************************************************
  Function:	g_fSerialDataCallBack
  Desc:		handling of received data
  Input:	lSerialHandle,transmission handle;
			pRecvDataBuffer,received data buffer;
			dwBufSize,received data size;
			dwUser,user info;
  Output:	
  Return:	
**********************************************************/
void CALLBACK g_fSerialDataCallBack(LONG lSerialHandle, char *pRecvDataBuffer, DWORD dwBufSize, DWORD dwUser)
{
	CString tmp1;
	CString tmp2;
	CTime ct;
	int index = 0;
	char sString[1024] = {0};
	memcpy(sString, pRecvDataBuffer, (dwBufSize>1024)?1024:dwBufSize);

	if (TransDlg != NULL)
	{
		if (IsWindow(TransDlg->GetSafeHwnd()))
		{
			ct = CTime::GetCurrentTime();
			tmp1.Format("%d-%d-%d %d:%d:%d", ct.GetYear(), ct.GetMonth(), ct.GetDay(), ct.GetHour(),
				ct.GetMinute(), ct.GetSecond());
			index = TransDlg->m_RecvDataList.InsertItem(TransDlg->m_RecvDataList.GetItemCount(), tmp1, 0);
			
			TransDlg->m_RecvDataList.SetItemText(index, 1, sString);
			tmp1.Empty();
			for (int i=0; i<(int)dwBufSize; i++)
			{
				tmp2.Format("0x%x ", (BYTE)pRecvDataBuffer[i]);
				tmp1 += tmp2;
			}
			TransDlg->m_RecvDataList.SetItemText(index, 2, tmp1);
		}
	}
}

/*********************************************************
Function:	g_fSerialDataCallBack_V40
Desc:		handling of received data
Input:	lSerialHandle,transmission handle;
pRecvDataBuffer,received data buffer;
dwBufSize,received data size;
pUser,user info;
Output:	
Return:	
**********************************************************/
void CALLBACK g_fSerialDataCallBack_V40(LONG lSerialHandle, LONG lCHannel, char *pRecvDataBuffer, DWORD dwBufSize, void* pUser)
{
    CString tmp1;
    CString tmp2;
    CTime ct;
    int index = 0;
    char sString[1024] = {0};
    memcpy(sString, pRecvDataBuffer, (dwBufSize>1024)?1024:dwBufSize);
    
    if (TransDlg != NULL)
    {
        if (IsWindow(TransDlg->GetSafeHwnd()))
        {
            ct = CTime::GetCurrentTime();
            tmp1.Format("%d-%d-%d %d:%d:%d", ct.GetYear(), ct.GetMonth(), ct.GetDay(), ct.GetHour(),
                ct.GetMinute(), ct.GetSecond());
            index = TransDlg->m_RecvDataList.InsertItem(TransDlg->m_RecvDataList.GetItemCount(), tmp1, 0);
            
            TransDlg->m_RecvDataList.SetItemText(index, 1, sString);
            tmp1.Empty();
            for (int i=0; i<(int)dwBufSize; i++)
            {
                tmp2.Format("0x%x ", (BYTE)pRecvDataBuffer[i]);
                tmp1 += tmp2;
            }
            TransDlg->m_RecvDataList.SetItemText(index, 2, tmp1);
        }
	}
}

/*********************************************************
  Function:	DlgSerialTrans
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CTransparentTrans::CTransparentTrans(CWnd* pParent /*=NULL*/)
	: CDialog(CTransparentTrans::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransparentTrans)
	m_lSerialID = -1;
	m_lSerialChan = -1;
	m_csContent = _T("");
	m_dwSerialNo = 0;
	//}}AFX_DATA_INIT
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CTransparentTrans::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransparentTrans)
	DDX_Control(pDX, IDC_COMBO_SEND, m_comboSend);
	DDX_Control(pDX, IDC_COMBO_SERIAL_TYPE, m_comboSerialType);
	DDX_Control(pDX, IDC_COMBO_CHAN, m_comboChan);
	DDX_Control(pDX, IDC_LISTRECVDATA, m_RecvDataList);
	DDX_Text(pDX, IDC_EDIT_DATA, m_csContent);
	DDX_Text(pDX, IDC_EDIT_SERIAL_NO, m_dwSerialNo);
	//}}AFX_DATA_MAP
}

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CTransparentTrans, CDialog)
	//{{AFX_MSG_MAP(CTransparentTrans)
	ON_BN_CLICKED(IDC_CREATECHANNEL, OnCreatechannel)
	ON_BN_CLICKED(IDC_DESTROYCHANNEL, OnDestroychannel)
	ON_BN_CLICKED(IDC_BTN_SEND_DATA, OnSenddata)
	ON_CBN_SELCHANGE(IDC_COMBO_SERIAL_TYPE, OnSelchangeComboSerialType)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentTrans message handlers
/*********************************************************
  Function:	OnInitDialog
  Desc:		Initialize the dialog
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CTransparentTrans::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_comboSend.SetCurSel(0);
	m_RecvDataList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_RecvDataList.InsertColumn(0, "Time", LVCFMT_LEFT, 100, 0);
	m_RecvDataList.InsertColumn(1, "Content", LVCFMT_LEFT, 200, 0);
	m_RecvDataList.InsertColumn(2, "Hex", LVCFMT_LEFT, 450, 0);
	m_iChanCount = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
	m_lStartChannel = g_struDeviceInfo[m_iDeviceIndex].iStartChan;
	m_lServerID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_iSelSerialIndex = 1;
	m_comboSerialType.SetCurSel(m_iSelSerialIndex-1);
	m_comboChan.SetCurSel(0);
	
	OnSelchangeComboSerialType();
	m_iChanCount = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
	EnableControl(FALSE);
	
	memset(&m_struSystemInfo,0,sizeof(m_struSystemInfo));
    m_bIsTrial = FALSE;
    DWORD  dwRet = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID,NET_DVR_GET_TRIAL_SYSTEM_CFG,0,&m_struSystemInfo,sizeof(m_struSystemInfo),&dwRet))
    {
        m_bIsTrial = TRUE; 
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRIAL_SYSTEM_CFG");    
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRIAL_SYSTEM_CFG");      
    }
	
	TransDlg = this;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
  Function:	EnableControl
  Desc:		Serial Trans disable the control or not
  Input:	bEnable,TRUE/FALSE;
  Output:	
  Return:	
**********************************************************/
void CTransparentTrans::EnableControl(BOOL bEnable)
{
	//GetDlgItem(IDC_EDIT_DATA)->EnableWindow(bEnable);
	//GetDlgItem(IDC_BTN_SEND_DATA)->EnableWindow(bEnable);
	GetDlgItem(IDC_DESTROYCHANNEL)->EnableWindow(bEnable);
	GetDlgItem(IDC_CREATECHANNEL)->EnableWindow(!bEnable);
}

/*********************************************************
  Function:	OnCreatechannel
  Desc:		start direct transmission
  Input:	
  Output:	
  Return:	
**********************************************************/
void CTransparentTrans::OnCreatechannel() 
{
//	g_struDeviceInfo[m_iDeviceIndex].lTranHandle = NET_DVR_SerialStart(m_lServerID, m_iSelSerialIndex, g_fSerialDataCallBack, m_lServerID);
	UpdateData(TRUE);
    char szLan[128] = {0};
    NET_DVR_SERIALSTART_V40 struSerialStartV40 = {0};
    struSerialStartV40.dwSize = sizeof(NET_DVR_SERIALSTART_V40);
    struSerialStartV40.dwSerialType = m_iSelSerialIndex;
    if (m_iSelSerialIndex == 1)  //RS232
    {
        if (g_struDeviceInfo[m_iDeviceIndex].bySupport5 &0x20)
        {
            struSerialStartV40.bySerialNum = (BYTE)m_dwSerialNo;   
        }
    }
    else  //485
    {
        if (g_struDeviceInfo[m_iDeviceIndex].bySupport5 &0x40)
        {
            struSerialStartV40.bySerialNum = (BYTE)m_dwSerialNo;   
        }
    }
    
    g_struDeviceInfo[m_iDeviceIndex].lTranHandle = NET_DVR_SerialStart_V40(m_lServerID, &struSerialStartV40,sizeof(struSerialStartV40), g_fSerialDataCallBack_V40,NULL);
    
    if (g_struDeviceInfo[m_iDeviceIndex].lTranHandle  == -1)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SerialStart_V40 serial[%d]", m_iSelSerialIndex);
		AfxMessageBox("Start Direct Transmission Failed");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SerialStart_V40 serial[%d]", m_iSelSerialIndex);
	EnableControl(TRUE);
    g_StringLanType(szLan, "建立通明通道成功", "success to start!");
	MessageBox(szLan);
}

/*********************************************************
  Function:	OnDestroychannel
  Desc:		stop direct transmission
  Input:	
  Output:	
  Return:	
**********************************************************/
void CTransparentTrans::OnDestroychannel() 
{
	char szLan[128] = {0};
	if (g_struDeviceInfo[m_iDeviceIndex].lTranHandle < 0)
	{
		return;
	}
	if (!NET_DVR_SerialStop(g_struDeviceInfo[m_iDeviceIndex].lTranHandle))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SerialStop serial[%d]", m_iSelSerialIndex);
		g_StringLanType(szLan, "停止通明通道失败", "Stop Direct Transmission Failed");
		AfxMessageBox(szLan);
		return;
	}
	EnableControl(FALSE);
	g_struDeviceInfo[m_iDeviceIndex].lTranHandle = -1;
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SerialStop  serial[%d]", m_iSelSerialIndex);
	g_StringLanType(szLan, "停止通明通道成功", "Stop Direct Transmission Successfully");
	AfxMessageBox(szLan);
}

/*********************************************************
  Function:	OnSenddata
  Desc:		send data to device via transparent
  Input:	
  Output:	
  Return:	
**********************************************************/
void CTransparentTrans::OnSenddata() 
{
	UpdateData(TRUE);
	int iSendInterface = m_comboSend.GetCurSel();
	m_lSerialChan = m_comboChan.GetItemData(m_comboChan.GetCurSel());	
	char szSendBuf[1016] = {0};
	int iBufLen = m_csContent.GetLength()<1016?m_csContent.GetLength():1016;
	memcpy(szSendBuf, m_csContent.GetBuffer(iBufLen), iBufLen);
	m_csContent.ReleaseBuffer();
	char szLan[128] = {0};

	if (iSendInterface == 0)
	{
		if (!NET_DVR_SerialSend(g_struDeviceInfo[m_iDeviceIndex].lTranHandle, m_lSerialChan, szSendBuf, iBufLen))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SerialSend serial index[%d]", m_lSerialChan);
			g_StringLanType(szLan, "发送失败", "Send Failed");
			AfxMessageBox(szLan);
			return;
		}
	}
	else if (iSendInterface == 1)
	{//send to device without needing to establish transparent
		if (!NET_DVR_SendToSerialPort(m_lServerID, m_iSelSerialIndex, m_lSerialChan, szSendBuf, iBufLen))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SendToSerialPort serial[%d] chan[%d]", m_iSelSerialIndex, m_lSerialChan);
			g_StringLanType(szLan, "发送失败", "Send Failed");
			AfxMessageBox(szLan);
			return;
		}
	}
	else if (iSendInterface == 2)
	{//send to device 232 serial port without needing to establish transparent
		if (!NET_DVR_SendTo232Port(m_lServerID, szSendBuf, iBufLen))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SendTo232Port");
			AfxMessageBox("Send Failed!");
			return;
		}
	}

	MessageBox("success to send!");
}

/*********************************************************
  Function:	OnSelchangeComboSerialType
  Desc:		select the serial type
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CTransparentTrans::OnSelchangeComboSerialType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i = 0;
	CString csTemp;	
	m_iSelSerialIndex = m_comboSerialType.GetCurSel()+1;
	m_comboChan.ResetContent();
	DWORD dwIndex = 0;
	switch(m_iSelSerialIndex)
	{
	case 1:
		for (i=0;i<2;i++)
		{
			csTemp.Format("Serial%d", i+1);
			m_comboChan.AddString(csTemp);
			m_comboChan.SetItemData(dwIndex,(i+1));
            dwIndex++;
		}
        m_comboChan.EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_SERIAL_NO)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_CHAN)->EnableWindow(TRUE);
        break;
	case 2:
		if (m_bIsTrial)  //for trial host
        {
            for (int  i = 0; i<m_struSystemInfo.byVideoInTypeNum; i++)
            {
                if (m_struSystemInfo.struVideoIn[i].wInType == 0)  //only SDI support 485
                {
                    for (int j =0; j < m_struSystemInfo.struVideoIn[i].wInNum; j++)
                    {
                        csTemp.Format("SDI Chan%d", j+1);
                        m_comboChan.AddString(csTemp);
                        m_comboChan.SetItemData(dwIndex,m_struSystemInfo.struVideoIn[i].wStartNo+j);
                        dwIndex++;
                    }
                    break;
                }
            }
        }
        else
        {
            for (i=0;i<m_iChanCount;i++)
            {//only for analog channels
                csTemp.Format("Channel%d", i+m_lStartChannel);
                m_comboChan.AddString(csTemp);
                m_comboChan.SetItemData(dwIndex,(i+1));
                dwIndex++;
            }
        }
        m_comboChan.EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_SERIAL_NO)->EnableWindow(TRUE); 
        break;
	default:
	    break;
	}
	m_lSerialChan = 1;
	m_comboChan.SetCurSel(m_lSerialChan-1);
}

/*********************************************************
  Function:	OnBtnExit
  Desc:		exit the dialog
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CTransparentTrans::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
//	OnDestroychannel();
	CDialog::OnCancel();	
}
