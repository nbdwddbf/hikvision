// DlgPosFilterEffect.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPosFilterEffect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void CALLBACK TestEffectPosDataCallBack(DWORD typeInfo,NET_DVR_NAKED_DATA_INFO *pStruNakedDataInfo, char *pInfo, DWORD dwInfoLen, void *pUser)
{
	UNREFERENCED_PARAMETER(pUser);
	char szLan[1024] = {0}; 
	HWND hWnd = ::FindWindow(NULL,"Filter Effect");//::GetDlgItem( ,IDD_DLG_POS_RECV_DATA);
	
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
	::SendMessage(hWnd,MSG_PULL_TEST_EFFECT_RECEIVEDATA_SHOW,(WPARAM)pStruNakedDataInfo, 0);
    ::SendMessage(hWnd,MSG_PULL_TEST_EFFECT_RECEIVEDATA_SHOW,(WPARAM)pInfo,1);
}

/////////////////////////////////////////////////////////////////////////////
// CDlgPosFilterEffect dialog


CDlgPosFilterEffect::CDlgPosFilterEffect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPosFilterEffect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPosFilterEffect)
	m_wPort = 7500;
	m_csRecvData = _T("");
	m_csFilterData = _T("");
	m_bStartListen = FALSE;
	m_iDevIndex = -1;
	//}}AFX_DATA_INIT
}


void CDlgPosFilterEffect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPosFilterEffect)
	DDX_Text(pDX, IDC_EDIT_PORT, m_wPort);
	DDX_Text(pDX, IDC_EDIT_RECVDATA, m_csRecvData);
	DDX_Text(pDX, IDC_EDIT_FILTER_DATA, m_csFilterData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPosFilterEffect, CDialog)
	ON_MESSAGE(MSG_PULL_TEST_EFFECT_RECEIVEDATA_SHOW, OnChangeEffectDataShow)
	//{{AFX_MSG_MAP(CDlgPosFilterEffect)
	ON_BN_CLICKED(IDC_BTN_START_RECVDATA, OnBtnStartRecvdata)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPosFilterEffect message handlers

void CDlgPosFilterEffect::OnBtnStartRecvdata() 
{
	// TODO: Add your control notification handler code here
/*	if (!m_bStartListen)
	{
		StartNetNakedDataListen();
	}
	else
	{
        StopNetNakedDataListen();
	}
	*/
}

void CDlgPosFilterEffect::StartNetNakedDataListen()
{
	UpdateData(TRUE);
	char szLan[256] = {0};
	/*if (m_wPort < 0 || m_wPort > 65535)
	{
		g_StringLanType(szLan,"请输入正确的端口号！","Please Input right port!");
		AfxMessageBox(szLan);
		return;
	}
	
	memset(&m_struNakedDataParam, 0,sizeof(m_struNakedDataParam));
    m_struNakedDataParam.wPort = m_wPort;
	
	//start listen
	m_lStartListenHandle = NET_DVR_StartRecvNakedDataListen(NAKED_DATA_TYPE_POS_INFO, &m_struNakedDataParam);
	
	if (m_lStartListenHandle < 0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StartRecvNakedDataListen");
		
		return;		
	}
	else
	{
		m_bStartListen = TRUE;
		g_StringLanType(szLan,"停止接受", "Stop Recv");
		GetDlgItem(IDC_BTN_START_RECVDATA)->SetWindowText(szLan);
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StartRecvNakedDataListen");
	}
	
	//clear data info 
	m_csFilterData = "";
	m_csRecvData = "";

	//Set Naked Data CallBack	
	NET_DVR_SetNakedDataRecvCallBack(m_lStartListenHandle,TestEffectPosDataCallBack,this);
	*/
	UpdateData(FALSE);
}


void CDlgPosFilterEffect::StopNetNakedDataListen()
{
	char szLan[256] = {0};
/*	if (m_lStartListenHandle < 0)
	{
		g_StringLanType(szLan,"开始接收", "Start Recv");
		GetDlgItem(IDC_BTN_START_RECVDATA)->SetWindowText(szLan);
		g_StringLanType(szLan, "监听端口已关闭！", "Listening port is closed!");
		AfxMessageBox(szLan);
		return;
	}
	
	//close Listen
	if (!NET_DVR_StopRecvNakedDataListen(m_lStartListenHandle))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRecvNakedDataListen");  
		return;		
	}
	else
	{
		m_bStartListen = FALSE;
		g_StringLanType(szLan,"开始接收", "Start Recv");
		GetDlgItem(IDC_BTN_START_RECVDATA)->SetWindowText(szLan);
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopRecvNakedDataListen");
	}
*/	
	
}


LRESULT CDlgPosFilterEffect::OnChangeEffectDataShow(WPARAM wParam, LPARAM lParam)
{
	/*UpdateData(TRUE);
	char *pReceiveData = (char*)wParam;
	
	int  iChOld = 0x0d0a;
	int  iChNew = 0x0a;
	
	if ((LONG)lParam == 1)
	{
		char *pReceiveData = (char*)wParam;
		
		int  iChOld = 0x0d0a;
		int  iChNew = 0x0a;
		
		int iTest = strlen(pReceiveData);
		m_csRecvData += pReceiveData;
		m_csRecvData.Replace((LPCTSTR)iChOld,LPCTSTR(iChNew));
		UpdateData(FALSE);

		//Parse Recv Data
		int i = 0;
		int iFindPosition = -1;
		CString strTemp = "";

	  // m_csFilterData = m_csRecvData;
		if (1 == m_struFilterCfg.struFilterCfg[0].dwProtocolType )
		{
			//Start Info
			if (m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struTransactionStart.byAnyCharacter)
			{
				m_csFilterData = m_csRecvData;
			}
			else
			{
				iFindPosition = m_csRecvData.Find((LPCTSTR)m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struTransactionStart.sData, 0);
				 if (  iFindPosition > -1)
				 {
					 m_csFilterData = m_csRecvData.Right(m_csRecvData.GetLength() - iFindPosition);
				 }
				 else
				 {
					 m_csFilterData = m_csRecvData;
				 }
			}

			//End info

			m_csFilterData = GenericEndStringInfo(m_csFilterData);

			//Ignore Info
            m_csFilterData = GenericIgnoreStringInfo(m_csFilterData);

			//new Line

			m_csFilterData = GenericNewLineInfo(m_csFilterData);

		}


		
		UpdateData(FALSE); 
		
// 		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_RECEIVED_DATA);
// 		int iAllLineNum = pEdit->GetLineCount();
// 		
// 		pEdit->LineScroll(iAllLineNum);
// 		UpdateData(FALSE);     
	}
	else
	{
// 		NET_DVR_NAKED_DATA_INFO *pStruNakedDataInfo = (NET_DVR_NAKED_DATA_INFO*)wParam;
// 		memcpy(m_szPosIp,pStruNakedDataInfo->sSocketIP,sizeof(pStruNakedDataInfo->sSocketIP));
// 		m_wSocketPort = pStruNakedDataInfo->wSocktPort;
	}
	*/
	return NULL;
}



CString CDlgPosFilterEffect::GenericIgnoreStringInfo(CString strData)
{

	char szLan[128] ="";
	CString strTemp;
	CString strTempReturn;
	CString strTempIgnore;
	int i =0 ;
	int j =0 ;
	int iIgnorePos = -1;
	if (strData.IsEmpty())
	{
		g_StringLanType(szLan,"数据不能为空！","Data can not be NULL");
		AfxMessageBox(szLan);
		return "";
	}

/*	strTemp = strData;
	strTempReturn =strTemp;
	for (i = 0 ; i < MAX_IGNORE_STRING_NUM; i++)
	{
	  while (j < strTemp.GetLength())
	  {
		  strTempIgnore = m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struIgnoreString[i].sData;
		  //sData is Null
		   
		  if (strTempIgnore.IsEmpty())
		  {
			  break;
		  }
         iIgnorePos = strTemp.Find((LPCTSTR)m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struIgnoreString[i].sData, j);
	
		 if (iIgnorePos > -1)
		 {
			strTempReturn = strTemp.Left(iIgnorePos);
			strTempReturn+= strTemp.Right(strTemp.GetLength() - iIgnorePos - strTempIgnore.GetLength());
			strTemp = strTempReturn;
		 }
		 else
		 {
			 break;
		 }
	  }
	}
*/
	return strTempReturn;
}

CString CDlgPosFilterEffect::GenericEndStringInfo(CString strData)
{
	CString strTemp;
	CString strReturn;
	char szLan[128]="";
	int iFindPosition = -1;
	int i =0;

	/*if (strData.IsEmpty())
	{
		g_StringLanType(szLan,"数据不能为空！","Data can not be NULL");
		AfxMessageBox(szLan);
		return "";
	}

	strTemp = strData;
	if (m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struTransactionEnd.dwMoreLine == 0)
	{
		iFindPosition = strTemp.Find((LPCTSTR)m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struTransactionEnd.sData, 0);
		if (iFindPosition > -1)
		{
		    strReturn = strTemp.Left(iFindPosition);
		}
		else
		{
			strReturn = strTemp;
		}
	}
	else
	{	
		CString strEndData ;
		CString strEndDataTemp = m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struTransactionEnd.sData;
	    iFindPosition =  strTemp.Find((LPCTSTR)m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struTransactionEnd.sData, 0);
		if (iFindPosition > -1)
		{
			strEndData = strTemp.Left(iFindPosition);
			strTemp = strTemp.Right(strTemp.GetLength() - iFindPosition - strEndDataTemp.GetLength());
		}
		else
		{
			strReturn = strTemp;
            return strReturn;
		}


		CString strNewLine = m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struLineDeli.sData;
		int iLastPosition = 0;
		strReturn = strTemp;
		while(i <= m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struTransactionEnd.dwMoreLine)
		{
			if (strNewLine.IsEmpty())
			{
				iFindPosition = strTemp.Find("\r\n",iLastPosition);		
			}
			else
			{
				iFindPosition = strTemp.Find(strNewLine,iLastPosition);	
			}
			if (iFindPosition > -1)
			{
				i++;
				

				if (strNewLine.GetLength() == 0)
				{
					iLastPosition = iFindPosition + 2;
					strReturn = strTemp.Left(iFindPosition + 2); 
				}
				else
				{
					iLastPosition = iFindPosition + strNewLine.GetLength();
					strReturn = strTemp.Left(iFindPosition + strNewLine.GetLength()); 
				}
			}
			else
			{
				strReturn = strTemp;
				break;
			}
		}//while

		strEndData += strReturn;
		strReturn = strEndData;
	
	}
	*/
	return strReturn;

}

CString CDlgPosFilterEffect::GenericNewLineInfo(CString strData)
{
   CString strTemp;
	CString strReturn;
 /*	char szLan[128]="";
	int iFindPosition = -1;
	int i =0;
	
	if (strData.IsEmpty())
	{
		g_StringLanType(szLan,"数据不能为空！","Data can not be NULL");
		AfxMessageBox(szLan);
		return "";
	}

	strTemp = strData;
	BOOL bStopWhile = FALSE;
	int iLastPosition = 0;
	CString strNewLine = m_struFilterCfg.struFilterCfg[0].struPosProtocol.struGeneric.struLineDeli.sData;
 
	int  iChNew = 0x0a;
	
 
 
	//	m_csReceivedData.Replace((LPCTSTR)iChOld,LPCTSTR(iChNew));
	if (strNewLine.GetLength() == 0)
	{
		//do nothing 
	}
	else
	{
		strTemp.Replace((LPCTSTR)strNewLine,(LPCTSTR)iChNew);
	}
*/
	return strTemp;
}
bool CDlgPosFilterEffect::ParseHexString(char *strHex, int &nLen)
{
/*	if (NULL == strHex)
	{
		return false;
	}
	
	int i = 0;
	
	for (i = 0; i < nLen; i++)
	{
		if ((0x0A == strHex[i]) || (0x0D == strHex[i]))
		{
			memcpy(strHex + i, strHex + i + 1, nLen - i - 1);
			nLen--;
			strHex[nLen] = '\0';
		}
	}
	
	for (i = 0; i < nLen; i++)
	{
		// find '<'
		bool bMatch = false;
		if (strHex[i] ==  '<')
		{
			bMatch = true;
		}
		if (bMatch)
		{
			int j = i;
			// find '>'
			while (strHex[j] != '>')
			{
				j++;
			}
			//convert hex to char
			char chHex = ConvertHexToChar(strHex + i + 1, j - i - 1);
			strHex[i] = chHex;
			memcpy(strHex + i + 1, strHex + j + 1, nLen - j - 1);
			strHex[i + nLen - j] = '\0';
			nLen = nLen - (j - i);
		}
	}
	*/
	return true;
}

char CDlgPosFilterEffect::ConvertHexToChar(char *strHex, int nLen)
{
	if ((NULL == strHex) || (0 >= nLen))
	{
		return '\0';
	}
	
	int nSum = 0;
	int i = 0;
	for (i = 0; i < nLen; i++)
	{
		// 把十六进制支付转化为数字
		int nNumber = 0;
		if (('a' <= strHex[i]) && ('f'>= strHex[i]))
		{
			nNumber = strHex[i] - 'a' + 10;
		}
		else if (('A' <= strHex[i]) && ('F'>= strHex[i]))
		{
			nNumber = strHex[i] - 'A' + 10;
		}
		else
		{
			nNumber = strHex[i] - '0';
		}
		
		nNumber *= GetHexNumber(nLen - i - 1);
		nSum += nNumber;
	}
	
	char chTemp = static_cast<char>(nSum);
	return chTemp;
}

int CDlgPosFilterEffect::GetHexNumber(int n)
{
	int i = 0;
	int sum = 1;
	for (i = 0; i < n; i++)
	{
		sum = sum * 16;
	}
	return sum;
}


void CDlgPosFilterEffect::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bStartListen)
	{
		StopNetNakedDataListen();
	}
	CDialog::OnClose();
}
