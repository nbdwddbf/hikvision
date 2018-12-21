// DlgVcaFindSnapData.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaFindSnapData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFindSnapData dialog
CDlgVcaFindSnapData *g_pVcaFindSnapPic = NULL;
UINT GetFindSnapPicThread(LPVOID pParam)
{
	
    UNREFERENCED_PARAMETER(pParam);
	
	LONG bRet = -1;
	NET_VCA_SUB_SNAPPIC_DATA struSnapPicData;
    memset(&struSnapPicData, 0, sizeof(struSnapPicData));
	CString csTmp;
	char szLan[256] = {0};
	while (1) 
	{
		bRet = NET_DVR_FindNextSnapPic(g_pVcaFindSnapPic->m_lFindHandle, &struSnapPicData);
        if (bRet == NET_DVR_FILE_SUCCESS)
		{
			csTmp.Format("%d", g_pVcaFindSnapPic->m_lFacePicNum+1);
			g_pVcaFindSnapPic->m_listFindData.InsertItem(g_pVcaFindSnapPic->m_lFacePicNum, csTmp,0);

            csTmp.Format("%04d-%02d-%02d %02d:%02d:%02d", struSnapPicData.struSnapTime.dwYear, struSnapPicData.struSnapTime.dwMonth, struSnapPicData.struSnapTime.dwDay, \
				struSnapPicData.struSnapTime.dwHour,struSnapPicData.struSnapTime.dwMinute, struSnapPicData.struSnapTime.dwSecond);
			g_pVcaFindSnapPic->m_listFindData.SetItemText(g_pVcaFindSnapPic->m_lFacePicNum, 1, csTmp);	


            csTmp.Format("%d", struSnapPicData.dwFacePicID);
			g_pVcaFindSnapPic->m_listFindData.SetItemText(g_pVcaFindSnapPic->m_lFacePicNum, 2, csTmp);

			csTmp.Format("%d", struSnapPicData.dwFacePicLen);
			g_pVcaFindSnapPic->m_listFindData.SetItemText(g_pVcaFindSnapPic->m_lFacePicNum, 3, csTmp);

			if (struSnapPicData.dwFacePicLen > 0)
			{
				char cFilename[256] = {0};
				HANDLE hFile;
				DWORD dwReturn;
				
				SYSTEMTIME t;
				GetLocalTime(&t);
				char chTime[128];
				sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds/*struSnapPicData.struSnapTime.dwYear,struSnapPicData.struSnapTime.dwMonth,struSnapPicData.struSnapTime.dwDay,struSnapPicData.struSnapTime.dwHour,struSnapPicData.struSnapTime.dwMinute,struSnapPicData.struSnapTime.dwSecond*/);
				
				sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[g_pVcaFindSnapPic->m_iDevIndex].chDeviceIP);
				if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
				{
					CreateDirectory(cFilename, NULL);
				}
				
				sprintf(cFilename, "%s\\FindPic[%s][%d].jpg",cFilename, chTime, struSnapPicData.dwFacePicID);
				hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				if (hFile == INVALID_HANDLE_VALUE)
				{
					return 0;
				}
				WriteFile(hFile, struSnapPicData.sPicBuf, struSnapPicData.dwFacePicLen, &dwReturn, NULL);
				CloseHandle(hFile);
				hFile = NULL;
			}

			g_pVcaFindSnapPic->m_lFacePicNum++;
		}
		else
		{
			if (bRet == NET_DVR_ISFINDING)
			{
				g_pVcaFindSnapPic->GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_SHOW);
				g_pVcaFindSnapPic->GetDlgItem(IDC_STATIC_SEARCH)->SetWindowText("Searching......");
				Sleep(5);
				continue;
			}
			if ((bRet == NET_DVR_NOMOREFILE) || (bRet == NET_DVR_FILE_NOFIND))
			{
				g_StringLanType(szLan, "ËÑË÷", "search snap picture");
				if (g_pVcaFindSnapPic->m_bChkSearch)
				{
					g_pVcaFindSnapPic->GetDlgItem(IDC_BTN_ADV_FIND)->SetWindowText(szLan);
				}
				else
				{
                    g_pVcaFindSnapPic->GetDlgItem(IDC_BTN_FIND)->SetWindowText(szLan);
				}
				
				g_pVcaFindSnapPic->GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_HIDE);
				g_StringLanType(szLan, "ËÑË÷ÈËÁ³Í¼Æ¬½áÊø!", "Search snap picture Ending");
				AfxMessageBox(szLan);
				break;
			}
			else
			{
				g_StringLanType(szLan, "ËÑË÷", "Search snap picture");
				if (g_pVcaFindSnapPic->m_bChkSearch)
				{
					g_pVcaFindSnapPic->GetDlgItem(IDC_BTN_ADV_FIND)->SetWindowText(szLan);
				}
				else
				{
                    g_pVcaFindSnapPic->GetDlgItem(IDC_BTN_FIND)->SetWindowText(szLan);
				}
				g_StringLanType(szLan, "ÓÉÓÚ·þÎñÆ÷Ã¦,»òÍøÂç¹ÊÕÏ,ËÑË÷Òì³£ÖÕÖ¹!",\
					"Since the server is busy, or network failure, search abnormal termination");
				AfxMessageBox(szLan);
				break;
			}
		}
	}
	CloseHandle(g_pVcaFindSnapPic->m_hFindThread);
	g_pVcaFindSnapPic->m_hFindThread = NULL;
	NET_DVR_FindSnapPicClose(g_pVcaFindSnapPic->m_lFindHandle);
	
	return 0;
}

CDlgVcaFindSnapData::CDlgVcaFindSnapData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaFindSnapData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaFindSnapData)
	m_ctDateEnd = 0;
	m_ctDateStart = 0;
	m_ctTimeEnd = 0;
	m_ctTimeStart = 0;
	m_byThreshold = 0;
	m_dwFacePicID = 0;
	m_bChkSearch = FALSE;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_lChannel  = -1;
    m_iDevIndex = -1;
	m_lFindHandle = -1;
	m_hFindThread = NULL;
	m_lFacePicNum = 0;
	memset(&m_struNormalFind, 0, sizeof(m_struNormalFind));
}


void CDlgVcaFindSnapData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaFindSnapData)
	DDX_Control(pDX, IDC_LIST_FIND_DATA, m_listFindData);
	DDX_Control(pDX, IDC_COMBO_FIND_TYPE, m_comboFindType);
	DDX_DateTimeCtrl(pDX, IDC_DATE_END, m_ctDateEnd);
	DDX_DateTimeCtrl(pDX, IDC_DATE_START, m_ctDateStart);
	DDX_DateTimeCtrl(pDX, IDC_TIME_END, m_ctTimeEnd);
	DDX_DateTimeCtrl(pDX, IDC_TIME_START, m_ctTimeStart);
	DDX_Text(pDX, IDC_EDIT_THRESHOLD, m_byThreshold);
	DDX_Text(pDX, IDC_EDIT_FACE_PIC_ID, m_dwFacePicID);
	DDX_Check(pDX, IDC_CHK_SEARCH, m_bChkSearch);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaFindSnapData, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaFindSnapData)
	ON_BN_CLICKED(IDC_BTN_IMPORT_PIC, OnBtnImportPic)
	ON_BN_CLICKED(IDC_BTN_ADV_FIND, OnBtnAdvFind)
	ON_BN_CLICKED(IDC_BTN_FIND, OnBtnFind)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_CHK_SEARCH, OnChkSearch)
	ON_CBN_SELCHANGE(IDC_COMBO_FIND_TYPE, OnSelchangeComboFindType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFindSnapData message handlers
BOOL CDlgVcaFindSnapData::OnInitDialog()
{
	CDialog::OnInitDialog();
	g_pVcaFindSnapPic = this;
	GetDlgItem(IDC_BTN_IMPORT_PIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_ADV_FIND)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_FIND_TYPE)->EnableWindow(FALSE);
	
	m_listFindData.SetExtendedStyle(m_listFindData.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
	
	char szLan[128] = {0};
	g_StringLanType(szLan, "ÐòºÅ", "NO.");
	m_listFindData.InsertColumn(0, szLan,LVCFMT_LEFT,50,-1);
	g_StringLanType(szLan, "×¥ÅÄÊ±¼ä", "Snap Time");
	m_listFindData.InsertColumn(1, szLan,LVCFMT_LEFT,100,-1);
	g_StringLanType(szLan, "ID", "Face Pic ID");
	m_listFindData.InsertColumn(2, szLan, LVCFMT_LEFT, 120, -1);	
	g_StringLanType(szLan, "Í¼Æ¬´óÐ¡", "Picture Size");
	m_listFindData.InsertColumn(3, szLan, LVCFMT_LEFT, 120, -1);
	
	CTime timeCur = CTime::GetCurrentTime();
	CTime timeStart(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),0,0,0);
	CTime timeStop(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),23,59,59);
	m_ctDateStart = timeStart;
	m_ctTimeStart = timeStart;
	m_ctDateEnd = timeStop;
	m_ctTimeEnd = timeStop;
	
	m_comboFindType.SetCurSel(0);
	UpdateData(FALSE);
	return TRUE;
}

void CDlgVcaFindSnapData::OnBtnImportPic() 
{
	// TODO: Add your control notification handler code here
	int i;
	for (i=0; i<MAX_HUMAN_PICTURE_NUM; i++)
	{
		if (g_struFacePic[i].dwImageID > 0)
		{
			m_struNormalFind.dwImageID = g_struFacePic[i].dwImageID;
			m_struNormalFind.dwFaceScore = g_struFacePic[i].dwFaceScore;
			memcpy(&m_struNormalFind.struVcaRect, &g_struFacePic[i].struVcaRect, sizeof(NET_VCA_RECT));
			break;
		}
	}
}

void CDlgVcaFindSnapData::OnBtnAdvFind() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	NET_VCA_FIND_PICTURECOND_ADVANCE struFindAdv = {0};
	struFindAdv.lChannel = m_lChannel;
	struFindAdv.byThreshold = m_byThreshold;
	struFindAdv.dwFindType = (VCA_FIND_SNAPPIC_TYPE)m_comboFindType.GetCurSel();
	struFindAdv.struStartTime.dwYear = (WORD)m_ctDateStart.GetYear();
	struFindAdv.struStartTime.dwMonth = (WORD)m_ctDateStart.GetMonth();
	struFindAdv.struStartTime.dwDay = (WORD)m_ctDateStart.GetDay();
	struFindAdv.struStartTime.dwHour = (char)m_ctTimeStart.GetHour();
	struFindAdv.struStartTime.dwMinute = (char)m_ctTimeStart.GetMinute();
	struFindAdv.struStartTime.dwSecond = (char)m_ctTimeStart.GetSecond();
	struFindAdv.struStopTime.dwYear = (WORD)m_ctDateEnd.GetYear();
	struFindAdv.struStopTime.dwMonth = (WORD)m_ctDateEnd.GetMonth();
	struFindAdv.struStopTime.dwDay = (WORD)m_ctDateEnd.GetDay();
	struFindAdv.struStopTime.dwHour = (char)m_ctTimeEnd.GetHour();
	struFindAdv.struStopTime.dwMinute = (char)m_ctTimeEnd.GetMinute();
	struFindAdv.struStopTime.dwSecond = (char)m_ctTimeEnd.GetSecond();
	if (m_comboFindType.GetCurSel() == 0)
	{
        memcpy(&struFindAdv.uFindParam.struNormalFind, &m_struNormalFind, sizeof(m_struNormalFind));
	}
	else
	{
        struFindAdv.uFindParam.struAdvanceFind.dwFacePicID = m_dwFacePicID;
	}
	
    m_lFindHandle = NET_DVR_AdvanceFindSnapPicture(m_lServerID, &struFindAdv);
	if (m_lFindHandle < 0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AdvanceFindSnapPicture");
		
		g_StringLanType(szLan, "¼ìË÷×¥ÅÄÍ¼Æ¬Ê§°Ü", "Search snap picture failed");
		AfxMessageBox(szLan);
        return;
	}
	else
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AdvanceFindSnapPicture");
		
		g_StringLanType(szLan, "¼ìË÷×¥ÅÄÍ¼Æ¬³É¹¦", "Search snap picture succ");
		AfxMessageBox(szLan);
	}
	
	m_lFacePicNum = 0;
	m_listFindData.DeleteAllItems();
	DWORD dwThreadId = 0;
	if (m_hFindThread != NULL)
	{
		TerminateThread(m_hFindThread, 0);
		CloseHandle(m_hFindThread);
		m_hFindThread = NULL;
		NET_DVR_FindSnapPicClose(m_lFindHandle);
	}
	
	if (m_hFindThread == NULL)
	{
		m_hFindThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetFindSnapPicThread), this, 0, &dwThreadId);
	}
	
	if (m_hFindThread  == NULL)
	{
		g_StringLanType(szLan, "´ò¿ªÏß³ÌÊ§°Ü", "Open thread failed");
		AfxMessageBox(szLan);
		return;
    }
	
	g_StringLanType(szLan, "Í£Ö¹ËÑË÷", "Stop Searching");
	GetDlgItem(IDC_BTN_ADV_FIND)->SetWindowText(szLan);
}

void CDlgVcaFindSnapData::OnBtnFind() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
    NET_VCA_FIND_PICTURECOND struFindCond = {0};
	struFindCond.struStartTime.dwYear = (WORD)m_ctDateStart.GetYear();
	struFindCond.struStartTime.dwMonth = (WORD)m_ctDateStart.GetMonth();
	struFindCond.struStartTime.dwDay = (WORD)m_ctDateStart.GetDay();
	struFindCond.struStartTime.dwHour = (char)m_ctTimeStart.GetHour();
	struFindCond.struStartTime.dwMinute = (char)m_ctTimeStart.GetMinute();
	struFindCond.struStartTime.dwSecond = (char)m_ctTimeStart.GetSecond();
	struFindCond.struStopTime.dwYear = (WORD)m_ctDateEnd.GetYear();
	struFindCond.struStopTime.dwMonth = (WORD)m_ctDateEnd.GetMonth();
	struFindCond.struStopTime.dwDay = (WORD)m_ctDateEnd.GetDay();
	struFindCond.struStopTime.dwHour = (char)m_ctTimeEnd.GetHour();
	struFindCond.struStopTime.dwMinute = (char)m_ctTimeEnd.GetMinute();
	struFindCond.struStopTime.dwSecond = (char)m_ctTimeEnd.GetSecond();
	struFindCond.lChannel = m_lChannel;
	
	m_lFindHandle = NET_DVR_FindSnapPicture(m_lServerID, &struFindCond);
	if (m_lFindHandle < 0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FindSnapPicture");
		
		g_StringLanType(szLan, "ËÑË÷ÈËÁ³Í¼Æ¬Ê§°Ü", "Search snap picture failed");
		AfxMessageBox(szLan);
        return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_FindSnapPicture");
		
		g_StringLanType(szLan, "ËÑË÷ÈËÁ³Í¼Æ¬³É¹¦", "Search snap picture succ");
		AfxMessageBox(szLan);
	}
	
	m_lFacePicNum = 0;
	m_listFindData.DeleteAllItems();
	DWORD dwThreadId = 0;
	if (m_hFindThread == NULL)
	{
		m_hFindThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetFindSnapPicThread), this, 0, &dwThreadId);
	}
	
	if (m_hFindThread  == NULL)
	{
		g_StringLanType(szLan, "´ò¿ªÏß³ÌÊ§°Ü", "Open thread failed");
		AfxMessageBox(szLan);
		return;
    }
	
	g_StringLanType(szLan, "Í£Ö¹ËÑË÷", "Stop Searching");
	GetDlgItem(IDC_BTN_FIND)->SetWindowText(szLan);
}

void CDlgVcaFindSnapData::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	if (m_hFindThread != NULL)
	{
		TerminateThread(m_hFindThread, 0);
		CloseHandle(m_hFindThread);
		m_hFindThread = NULL;
		NET_DVR_FindSnapPicClose(m_lFindHandle);
	}
	CDialog::OnCancel();
}

void CDlgVcaFindSnapData::OnChkSearch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_bChkSearch)
	{
        GetDlgItem(IDC_BTN_IMPORT_PIC)->EnableWindow(TRUE);
        GetDlgItem(IDC_BTN_ADV_FIND)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_FIND_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_FIND)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BTN_IMPORT_PIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ADV_FIND)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_FIND_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_FIND)->EnableWindow(TRUE);
	}
}

void CDlgVcaFindSnapData::OnSelchangeComboFindType() 
{
	// TODO: Add your control notification handler code here
	if (m_comboFindType.GetCurSel() == 1)
	{
		GetDlgItem(IDC_BTN_IMPORT_PIC)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BTN_IMPORT_PIC)->EnableWindow(TRUE);
	}
}
