// DlgVCARuleColorCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVCARuleColorCfg.h"
#include "Picture.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define WM_PROC_GET_COLORCFG		WM_USER + 1234

/////////////////////////////////////////////////////////////////////////////
// CDlgVCARuleColorCfg dialog
CPicture *pRuleColorPic= NULL;


CDlgVCARuleColorCfg::CDlgVCARuleColorCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVCARuleColorCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVCARuleColorCfg)
	m_bDrawPic1 = FALSE;
	m_lUserID = -1;
	m_iDevIndex = -1;
	m_bBtnDown = FALSE;
	m_strPic1Name = "";
	m_strPic2Name = "";
	m_strPic3Name = "";
	m_bEnable = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgVCARuleColorCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVCARuleColorCfg)
	DDX_Control(pDX, IDC_COMBO_SEQUENCE_NO, m_cmbColorBlockNo);
	DDX_Control(pDX, IDC_SHOWJPEG_1, m_showPicture1);
	DDX_Control(pDX, IDC_COMBO_RULE_ID, m_cmbRuleID);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
	DDX_Check(pDX, IDC_CHECK_PIC_1, m_bDrawPic1);
	DDX_Check(pDX, IDC_CHEC_ENABLE, m_bEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVCARuleColorCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVCARuleColorCfg)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_CHECK_PIC_1, OnCheckPic1)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
    ON_MESSAGE(WM_PROC_GET_COLORCFG, OnProcessVCARuleColorCBInfo)
	ON_BN_CLICKED(IDC_BTN_LOAD_PIC1, OnBtnLoadPic1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVCARuleColorCfg message handlers

void CALLBACK g_fGetColorDataCallBack(DWORD dwType, void *pRecvDataBuffer, DWORD dwBufSize, void* pUserData)
{
    CDlgVCARuleColorCfg *pThis = (CDlgVCARuleColorCfg*)pUserData;
    DWORD dwTemp = 0;
	char szLan[128] = {0};

	HWND hWnd = pThis->GetSafeHwnd();
	if (NULL == hWnd)
	{
		return;
	}
	
    switch (dwType)
    {
    case NET_SDK_CALLBACK_TYPE_STATUS:
		{
			dwTemp = *((DWORD*)pRecvDataBuffer);
			g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_FAIL_T, "Get Color Cfg CallBack");
			::PostMessage(hWnd,WM_PROC_GET_COLORCFG,(DWORD)dwTemp,dwType);
		}
		break;
    case  NET_SDK_CALLBACK_TYPE_PROGRESS:
        g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_SUCC_T, "Get Color Cfg CallBack Processing");
        break;
    case NET_SDK_CALLBACK_TYPE_DATA:
        {
            char *pDataBuf = new char[sizeof(NET_DVR_VCA_RULE_COLOR_CFG)];
            if (pDataBuf == NULL)
            {
                dwType = NET_SDK_CALLBACK_STATUS_FAILED;
            }
            memset(pDataBuf,0,sizeof(NET_DVR_VCA_RULE_COLOR_CFG));
            memcpy(pDataBuf,pRecvDataBuffer,sizeof(NET_DVR_VCA_RULE_COLOR_CFG));
			
			
			LPNET_DVR_VCA_RULE_COLOR_CFG pRuleColorTemp = (NET_DVR_VCA_RULE_COLOR_CFG*)pDataBuf;
			pRuleColorTemp->struPicInfo.byPicDataBuff = NULL;
            LPNET_DVR_VCA_RULE_COLOR_CFG pRuleColorCfg = (NET_DVR_VCA_RULE_COLOR_CFG*)pRecvDataBuffer;
			
            if (pRuleColorCfg->struPicInfo.dwPicDataLen != 0)
            {
				pRuleColorTemp->struPicInfo.byPicDataBuff = new char[pRuleColorCfg->struPicInfo.dwPicDataLen];
				if(pRuleColorTemp->struPicInfo.byPicDataBuff == NULL)
				{
					return ;
				}
				memset(pRuleColorTemp->struPicInfo.byPicDataBuff,0,pRuleColorCfg->struPicInfo.dwPicDataLen);
                memcpy(pRuleColorTemp->struPicInfo.byPicDataBuff,pRuleColorCfg->struPicInfo.byPicDataBuff,pRuleColorCfg->struPicInfo.dwPicDataLen);
            }
             		sprintf(szLan,"Recv Rule Color Data ColorBlockNo[%d] dataLen[%d]",pRuleColorTemp->byColorBlockNo,pRuleColorTemp->struPicInfo.dwPicDataLen);
 		g_pMainDlg->AddLog(pThis->m_iDevIndex,OPERATION_SUCC_T,szLan);
        ::PostMessage(hWnd, WM_PROC_GET_COLORCFG, NET_SDK_CALLBACK_TYPE_DATA, (LPARAM)pDataBuf);
        }
        break;
    default:
        break;
        
	}
    
}

void CDlgVCARuleColorCfg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bBtnDown = TRUE;
	char szLan[128]= {0};
	if (m_bDrawPic1)
	{
		if(m_strPic1Name.IsEmpty())
		{
			g_StringLanType(szLan,"请先加载图片","Please Load Picture First!");
			AfxMessageBox(szLan);
			m_bBtnDown = FALSE;
			return;
		}

		RECT rect; 
		m_showPicture1.GetClientRect(&rect) ;
		if((point. x<rect. right) && (point. x>rect. left) && (point. y<rect. bottom) && (point. y>rect. top) )
		{ 
			m_RegionLeftTop = point; 
		}
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgVCARuleColorCfg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	RECT rect = {0};   
	CPoint pt(0, 0);


	if (m_bBtnDown)
	{
		if (m_bDrawPic1)
		{
			m_showPicture1.GetClientRect( &rect );
			if( ( point.x<rect.right ) && ( point.x>rect.left ) && ( point.y<rect.bottom ) && ( point.y>rect.top ) )
			{          
				GetDlgItem(IDC_SHOWJPEG_1)->GetWindowRect(&m_rcWnd);
				GetCursorPos(&pt);
				ScreenToClient(&m_rcWnd);
				//ScreenToClient(&pt);
				//Invalidate(TRUE);
				m_RegionRightBottom = point;   
				CDC * pDC = m_showPicture1.GetWindowDC ();
				pDC->SetROP2(R2_NOT);
				CPen pen(PS_SOLID,2,RGB(0,255,0));//做一支红色粗细为1的笔
				pDC->SelectObject(&pen);
				pDC->SelectStockObject(NULL_BRUSH);  
				pDC->Rectangle( CRect(m_RegionLeftTop, m_RegionRightBottom ) ) ;
				/*m_struVCARuleColorCfg.struPicInfo[0].struColorRect.fX = m_RegionLeftTop.x;
				m_struVCARuleColorCfg.struPicInfo[0].struColorRect.fY = m_RegionLeftTop.y;
				m_struVCARuleColorCfg.struPicInfo[0].struColorRect.fHeight = m_RegionRightBottom.y- m_RegionLeftTop.y;
				m_struVCARuleColorCfg.struPicInfo[0].struColorRect.fWidth  = m_RegionRightBottom.x- m_RegionLeftTop.x;
			*/
			}
		} 
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CDlgVCARuleColorCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	if(m_lRemoteHandle >= 0)
	{
		NET_DVR_StopRemoteConfig(m_lRemoteHandle);
	}
	
	NET_DVR_VCA_RULE_COLOR_COND struColorCond = {0};
	struColorCond.dwSize = sizeof(struColorCond);
	struColorCond.dwChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
	struColorCond.byRuleID = m_cmbRuleID.GetCurSel()+1;
	
	m_lRemoteHandle = NET_DVR_StartRemoteConfig(m_lUserID,NET_DVR_GET_VCA_RULE_COLOR_CFG,&struColorCond,sizeof(struColorCond),g_fGetColorDataCallBack,this);
	if (m_lRemoteHandle < 0 )
	{
		g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_GET_VCA_RULE_COLOR_CFG");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_GET_VCA_RULE_COLOR_CFG");
	}
}

void CDlgVCARuleColorCfg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bBtnDown = FALSE;
	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgVCARuleColorCfg::OnCheckPic1() 
{
	// TODO: Add your control notification handler code here
	if (!m_bDrawPic1)
	{
		m_bDrawPic1 = TRUE;
	}
	else
	{
		m_bDrawPic1 = FALSE;
	}
}


void CDlgVCARuleColorCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here

	m_struVCARuleColorCfg.dwSize = sizeof(m_struVCARuleColorCfg);
	m_struVCARuleColorCfg.byEnable = m_bEnable;
	m_struVCARuleColorCfg.byRuleID = m_cmbRuleID.GetCurSel() + 1;
	m_struVCARuleColorCfg.byColorBlockNo = m_cmbColorBlockNo.GetCurSel() +1;

	DWORD dwChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
	m_struVCARuleColorCfg.struPicInfo.byPicType = 0;
	m_struVCARuleColorCfg.struPicInfo.dwPicHeight = 1024;
	m_struVCARuleColorCfg.struPicInfo.dwPicWidth = 768;

	CFile cFile;
	char szLan[128] = {0};

	if (!m_strPic1Name.IsEmpty())
	{
		if (!cFile.Open(m_strPic1Name, CFile::modeRead))
		{
			g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
			AfxMessageBox(szLan);
		}
		else
		{
			m_struVCARuleColorCfg.struPicInfo.dwPicDataLen = (DWORD)cFile.GetLength();
			if (m_struVCARuleColorCfg.struPicInfo.dwPicDataLen == 0)
			{
				g_StringLanType(szLan, "第图片为空", "Pic is empty");
				AfxMessageBox(szLan);
				return ;
			}          
			
			m_struVCARuleColorCfg.struPicInfo.byPicDataBuff = new char[m_struVCARuleColorCfg.struPicInfo.dwPicDataLen];
			cFile.Read(	m_struVCARuleColorCfg.struPicInfo.byPicDataBuff, m_struVCARuleColorCfg.struPicInfo.dwPicDataLen);
			cFile.Close();
		}
	}

	if (!NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_VCA_RULE_COLOR_CFG,dwChannel,&m_struVCARuleColorCfg,sizeof(m_struVCARuleColorCfg)))
	{
		g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_SET_VCA_RULE_COLOR_CFG");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_SET_VCA_RULE_COLOR_CFG");
	}

}

LRESULT CDlgVCARuleColorCfg::OnProcessVCARuleColorCBInfo(WPARAM wParam, LPARAM lParam)
{
    DWORD dwType = (DWORD)wParam;
    char szLan[256] = {0};

    if(dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        LPNET_DVR_VCA_RULE_COLOR_CFG pStruRuleColor = (LPNET_DVR_VCA_RULE_COLOR_CFG)lParam;
         
        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        char cFilename[256] = {0};
        DWORD dwWrittenBytes = 0;
// 		sprintf(szLan,"Recv Rule Color Data ColorBlockNo[%d]",pStruRuleColor->byColorBlockNo);
// 		g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,szLan);
        sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
        if (pStruRuleColor->struPicInfo.dwPicDataLen > 0 && pStruRuleColor->struPicInfo.byPicDataBuff != NULL)
        {
            sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIP);
            if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
            {
                CreateDirectory(cFilename, NULL);
            }
            
            sprintf(cFilename, "%s\\LocalTime[%s]Pic_ColorBlockNo%d.jpg",cFilename, chTime,pStruRuleColor->byColorBlockNo);
            
            HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE)
            {
                return NULL;
            }
            DWORD dwRet = WriteFile(hFile, pStruRuleColor->struPicInfo.byPicDataBuff, pStruRuleColor->struPicInfo.dwPicDataLen, &dwWrittenBytes, NULL);
            if (dwRet == 0 || dwWrittenBytes < pStruRuleColor->struPicInfo.dwPicDataLen )
            {
                DWORD dwError = GetLastError();
                g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Pic_ColorBlockNo[%d] Write to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ",pStruRuleColor->byColorBlockNo, dwError, pStruRuleColor->struPicInfo.dwPicDataLen, dwWrittenBytes);
            }
            CloseHandle(hFile);
            hFile = NULL;
            m_strPic1Name = cFilename;

            CRect rc;
            CDC* pDC = m_showPicture1.GetDC();
            m_showPicture1.GetClientRect(&rc);
            pDC->SetViewportOrg(rc.left, rc.top);
            rc.bottom = -rc.bottom;	
            if (!pRuleColorPic)
            {
                pRuleColorPic = new CPicture;	
            }	
            pRuleColorPic->LoadPicture(cFilename, pDC->m_hDC, abs(rc.Width()), abs(rc.Height()));
        }

      
        if (pStruRuleColor->struPicInfo.byPicDataBuff != NULL)
        {
            delete [] (pStruRuleColor->struPicInfo.byPicDataBuff);
            pStruRuleColor->struPicInfo.byPicDataBuff = NULL;
        }
		m_bEnable = pStruRuleColor->byEnable;

		if (pStruRuleColor != NULL)
		{
			delete pStruRuleColor;
			pStruRuleColor = NULL;
		}

    }
	else
	{
		if (!NET_DVR_StopRemoteConfig(m_lRemoteHandle))
		{
			g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_StopRemoteConfig");
		}
		else
		{
			g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_StopRemoteConfig");
			m_lRemoteHandle = -1;
		}
    
	}

    

    UpdateData(FALSE);
    return NULL;
}


BOOL CDlgVCARuleColorCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
		memset(&m_struVCARuleColorCfg,0,sizeof(m_struVCARuleColorCfg));
	// TODO: Add extra initialization here
	g_AddChanInfoToComBox(m_cmbChannel,m_iDevIndex,TRUE);
    m_cmbChannel.SetCurSel(0);
    m_cmbRuleID.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVCARuleColorCfg::OnBtnLoadPic1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	char szLan[128] = {0};
    OPENFILENAME ofn = {0};
	CRect struRect;
	
	m_strPic1Name = "";
	char chFileName[260] = {0};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner   = this->GetSafeHwnd();
    ofn.lpstrFilter = "All Files\0*.*\0\0";
    ofn.lpstrFile   = chFileName;
    ofn.nMaxFile    = MAX_PATH;
    ofn.Flags       = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
    
    if (GetOpenFileName(&ofn))
    {
        /*m_csFilePath.Format("%s", m_chFilename);*/
		m_strPic1Name = chFileName;
    }
	
	if (strlen(m_strPic1Name) == 0)
	{
		return;
	}

	if(!m_Pic.LoadPicture(m_strPic1Name.GetBuffer(0)))
	{
		AfxMessageBox("Fail to reload picture");
		return;
	}
	
	GetDlgItem(IDC_SHOWJPEG_1)->Invalidate(FALSE);
	GetDlgItem(IDC_SHOWJPEG_1)->GetClientRect(&struRect);
	CPaintDC dc2(GetDlgItem(IDC_SHOWJPEG_1));
    m_Pic.DrawPicture(dc2.m_hDC, struRect.left, struRect.top, struRect.Width(), struRect.Height());
	UpdateData(FALSE);
}

BOOL CDlgVCARuleColorCfg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	CPoint pt(0, 0);
	GetCursorPos(&pt);


// 	if (m_bDrawPic1)
// 	{
// 		GetDlgItem(IDC_SHOWJPEG_1)->GetWindowRect(&m_rcWnd);
// 		ScreenToClient(&m_rcWnd);
// 		ScreenToClient(&pt);
// 		PreDrawRectMsg(pMsg, pt, m_struVCARuleColorCfg.struPicInfo[0].struColorRect);
// 	}

	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDlgVCARuleColorCfg::PreDrawRectMsg(MSG* pMsg, CPoint &pt, NET_VCA_POLYGON &struRegion)
{
    int i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;
    UpdateData(TRUE);
    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && 
            PtInRect(&m_rcWnd,pt))
        {
			    // if(m_bNeedRedraw)
            {
				
                
            }
            
        }
        break;
    }
    return TRUE;
}
