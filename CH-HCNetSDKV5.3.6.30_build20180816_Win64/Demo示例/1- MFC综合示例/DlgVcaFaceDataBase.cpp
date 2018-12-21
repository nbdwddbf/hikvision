// DlgVcaFaceDataBase.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaFaceDataBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFaceDataBase dialog
CDlgVcaFaceDataBase *g_pVcaFaceDataBase = NULL;

void CALLBACK FunInquireDBCallBack(LONG lHandle, DWORD dwType, DWORD dwResultNum, BYTE* pBuffer, DWORD dwBufSize,void *pUser)
{
	DWORD dwSearchType = 0;
	char *pRecordMsg = new char[dwBufSize];
	if (pRecordMsg == NULL)
	{
		return;
	}
	memcpy(pRecordMsg, pBuffer, dwBufSize);
	if (g_pVcaFaceDataBase->m_bInquiring)
	{
		dwSearchType = INQUIRE_FACE_DATABASE;
		((LPNET_VCA_INQUIRE_DATARECORD_RESULT)pRecordMsg)->pFacePic = new BYTE[((LPNET_VCA_INQUIRE_DATARECORD_RESULT)pRecordMsg)->dwFacePicLen];
		memset(((LPNET_VCA_INQUIRE_DATARECORD_RESULT)pRecordMsg)->pFacePic, 0, ((LPNET_VCA_INQUIRE_DATARECORD_RESULT)pRecordMsg)->dwFacePicLen);
		memcpy(((LPNET_VCA_INQUIRE_DATARECORD_RESULT)pRecordMsg)->pFacePic, ((LPNET_VCA_INQUIRE_DATARECORD_RESULT)pBuffer)->pFacePic, ((LPNET_VCA_INQUIRE_DATARECORD_RESULT)pRecordMsg)->dwFacePicLen);
	}
	
    ::PostMessage(g_pVcaFaceDataBase->m_hWnd, WM_PROC_FACECALLBACK, (WPARAM)dwSearchType, (LPARAM)pRecordMsg);
}

void CALLBACK FunSearchDBCallBack(LONG lHandle, DWORD dwType, DWORD dwResultNum, BYTE* pBuffer, DWORD dwBufSize,void *pUser)
{
	DWORD dwSearchType = 0;
	char *pRecordMsg = new char[dwBufSize];
	if (pRecordMsg == NULL)
	{
		return;
	}
	memcpy(pRecordMsg, pBuffer, dwBufSize);
	if (g_pVcaFaceDataBase->m_bSearching)
	{
		dwSearchType = SEARCH_FACE_DATABASE;
		((LPNET_VCA_SEARCH_DATARECORD_RESULT)pRecordMsg)->pFacePic = new BYTE[((LPNET_VCA_SEARCH_DATARECORD_RESULT)pRecordMsg)->dwFacePicLen];
		memset(((LPNET_VCA_SEARCH_DATARECORD_RESULT)pRecordMsg)->pFacePic, 0, ((LPNET_VCA_SEARCH_DATARECORD_RESULT)pRecordMsg)->dwFacePicLen);
		memcpy(((LPNET_VCA_SEARCH_DATARECORD_RESULT)pRecordMsg)->pFacePic, ((LPNET_VCA_SEARCH_DATARECORD_RESULT)pBuffer)->pFacePic, ((LPNET_VCA_SEARCH_DATARECORD_RESULT)pRecordMsg)->dwFacePicLen);
	}
	
    ::PostMessage(g_pVcaFaceDataBase->m_hWnd, WM_PROC_FACECALLBACK, (WPARAM)dwSearchType, (LPARAM)pRecordMsg);
}

CDlgVcaFaceDataBase::CDlgVcaFaceDataBase(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaFaceDataBase::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaFaceDataBase)
	m_csBirthDate = _T("");
	m_csName = _T("");
	m_csCertificateNumber = _T("");
	m_dwRecordID = 0;
	m_csRemark = _T("");
	m_csFastRegPicPath = _T("");
	m_iDataBaseID = 0;
	m_dwSearchNum = 0;
	m_dwThreld = 0;
	m_csUserInfo1 = _T("");
	m_csEndBirthDate = _T("");
	m_csStartBirthDate = _T("");
	m_dwTotalRecordNum = 0;
	m_dwAdvanceDBId = 0;
	m_dwAdvancePicId = 0;
	m_bChkAdvanceEn = FALSE;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_lChannel  = -1;
    m_iDevIndex = -1;
	m_lHandle = -1;
//	m_lDataBaseID = -1;
	m_bInquiring = FALSE;
	m_bSearching = FALSE;
	m_lRecordNum = 0;
	m_lTotalNum = 0;
	memset(&m_struDataRecordInfo, 0, sizeof(m_struDataRecordInfo));
	memset(m_chFilename, 0, sizeof(m_chFilename));
	memset(&m_struFastDataRecord, 0, sizeof(m_struFastDataRecord));
	memset(&m_struDeleteRecord, 0, sizeof(m_struDeleteRecord));
	memset(&m_struInquireCond, 0, sizeof(m_struInquireCond));
	memset(&m_struSearchCond, 0, sizeof(m_struSearchCond));
}


void CDlgVcaFaceDataBase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaFaceDataBase)
	DDX_Control(pDX, IDC_COMBO_ADVANCE_DATABASE_TYPE, m_comboAdvanceDBType);
	DDX_Control(pDX, IDC_LIST_DATABASE, m_listDataBase);
	DDX_Control(pDX, IDC_COMBO_CERFITICATE_TYPE, m_comboCerfiticateType);
	DDX_Control(pDX, IDC_COMBO_NATIVE_PLACE, m_comboNativePlace);
	DDX_Control(pDX, IDC_COMBO_SEX, m_comboSex);
	DDX_Text(pDX, IDC_EDIT_BIRTHDATE, m_csBirthDate);
	DDX_Text(pDX, IDC_EDIT_NAME, m_csName);
	DDX_Text(pDX, IDC_EDIT_CERTIFICATE_NUMBER, m_csCertificateNumber);
	DDX_Text(pDX, IDC_EDIT_RECORD_ID, m_dwRecordID);
	DDX_Text(pDX, IDC_EDIT_REMARK, m_csRemark);
	DDX_Text(pDX, IDC_EDIT_FASTREGISTER_PICPATH, m_csFastRegPicPath);
	DDX_Text(pDX, IDC_EDIT_DATABASE_ID, m_iDataBaseID);
	DDX_Text(pDX, IDC_EDIT_SEARCH_MAXNUM, m_dwSearchNum);
	DDX_Text(pDX, IDC_EDIT_THRESHOLD, m_dwThreld);
	DDX_Text(pDX, IDC_EDIT_USERID, m_csUserInfo1);
	DDX_Text(pDX, IDC_EDIT_END_BIRTHDATE, m_csEndBirthDate);
	DDX_Text(pDX, IDC_EDIT_START_BIRTHDATE, m_csStartBirthDate);
	DDX_Text(pDX, IDC_EDIT_RECORD_TOTAL_NUMBER, m_dwTotalRecordNum);
	DDX_Text(pDX, IDC_EDIT_ADVANCE_DB_ID, m_dwAdvanceDBId);
	DDX_Text(pDX, IDC_EDIT_ADVANCE_FACE_PIC_ID, m_dwAdvancePicId);
	DDX_Check(pDX, IDC_CHK_ADVANCE_SEARCH_EN, m_bChkAdvanceEn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaFaceDataBase, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaFaceDataBase)
	ON_BN_CLICKED(IDC_BTN_FAST_SCAN, OnBtnFastScan)
	ON_BN_CLICKED(IDC_BTN_FAST_REGISTER, OnBtnFastRegister)
	ON_BN_CLICKED(IDC_BTN_REGISTER, OnBtnRegister)
	ON_BN_CLICKED(IDC_BTN_DELETE_SINGLE, OnBtnDeleteSingle)
	ON_BN_CLICKED(IDC_BTN_DELETE_BATCH, OnBtnDeleteBatch)
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_GET_FACE_PIC, OnBtnGetFacePic)
	ON_BN_CLICKED(IDC_BTN_STOP_INQUIRE, OnBtnStopInquire)
	ON_BN_CLICKED(IDC_BTN_START_SEARCH, OnBtnStartSearch)
	ON_BN_CLICKED(IDC_BTN_STOP_SEARCH, OnBtnStopSearch)
	ON_BN_CLICKED(IDC_BTN_UPDATE_RECORD, OnBtnUpdateRecord)
	ON_MESSAGE(WM_PROC_FACECALLBACK, OnWMProcFaceCallback)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFaceDataBase message handlers
BOOL CDlgVcaFaceDataBase::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_comboCerfiticateType.SetCurSel(0);
	m_comboNativePlace.SetCurSel(0);
	m_comboSex.SetCurSel(0);

	g_pVcaFaceDataBase = this;

	char szLan[128] = {0};
    
    m_listDataBase.SetExtendedStyle(m_listDataBase.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLan, "序号", "NO.");
    m_listDataBase.InsertColumn(0, szLan, LVCFMT_RIGHT, 60, -1);
	g_StringLanType(szLan, "记录ID", "Record ID");
	m_listDataBase.InsertColumn(1, szLan, LVCFMT_LEFT, 80, -1);
	g_StringLanType(szLan, "姓名", "Name");
    m_listDataBase.InsertColumn(2, szLan, LVCFMT_LEFT, 80, -1);
	g_StringLanType(szLan, "性别", "Sex");
    m_listDataBase.InsertColumn(3, szLan, LVCFMT_LEFT,60, -1);
    g_StringLanType(szLan, "出生年月", "Age");
    m_listDataBase.InsertColumn(4, szLan, LVCFMT_LEFT, 80, -1);   
	g_StringLanType(szLan, "籍贯", "Native Place");
	m_listDataBase.InsertColumn(5, szLan, LVCFMT_LEFT, 80, -1);
	g_StringLanType(szLan, "证件类型", "Certificate Type");
	m_listDataBase.InsertColumn(6, szLan, LVCFMT_LEFT, 80, -1);
	g_StringLanType(szLan, "证件号", "NO.");
	m_listDataBase.InsertColumn(7, szLan, LVCFMT_LEFT, 140, -1);
	g_StringLanType(szLan, "备注", "Remark");
	m_listDataBase.InsertColumn(8, szLan, LVCFMT_LEFT, 200, -1);
	g_StringLanType(szLan, "相似度", "Similarity");
	m_listDataBase.InsertColumn(9, szLan, LVCFMT_LEFT, 200, -1);
/*
	CString csTmp;
//	char szLan[128] = {0};
	NET_VCA_BLACKLIST_INFO struBlackListData;
    memset(&struBlackListData, 0, sizeof(struBlackListData));

	csTmp.Format("%d", g_pVcaFaceDataBase->m_lBlackListNum+1);
	g_pVcaFaceDataBase->m_listDataBase.InsertItem(g_pVcaFaceDataBase->m_lBlackListNum, csTmp,0);
	
	switch (struBlackListData.byType)
	{
	case 0:
		g_StringLanType(szLan, "黑名单", "White list");
		break;
	case 1:
		g_StringLanType(szLan, "黑名单", "Black list");
	default:
		g_StringLanType(szLan, "未知", "Unknow");
		break;
	}
	csTmp.Format("%s", szLan);
	g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lBlackListNum, 1, csTmp);
	
	csTmp.Format("%s", struBlackListData.struAttribute.byName);
	g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lBlackListNum, 2, csTmp);
	
	switch (struBlackListData.struAttribute.bySex)
	{
	case 0:
		g_StringLanType(szLan, "女", "Man");
		break;
	case 1:
		g_StringLanType(szLan, "女", "Woman");
		break;
	default:
		g_StringLanType(szLan, "未知", "Unknow");
		break;
	}
	csTmp.Format("%s", szLan);
	g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lBlackListNum, 3, csTmp);
	
	csTmp.Format("%d", 20);
	g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lBlackListNum, 4, csTmp);
	
	csTmp.Format("%d", struBlackListData.struAttribute.dwNativePlace);
	g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lBlackListNum, 5, csTmp);
	
	csTmp.Format("%d", 50);
	g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lBlackListNum, 6, csTmp);
	
	csTmp.Format("%d", 20);
	g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lBlackListNum, 7, csTmp);
	
	switch (struBlackListData.struAttribute.byCertificateType)
	{
	case 0:
		g_StringLanType(szLan, "警官证", "identification card");
		break;
	case 1:
		g_StringLanType(szLan, "警官证", "Officers card");
		break;
	default:
		g_StringLanType(szLan, "未知", "Unknow");
		break;
	}
	csTmp.Format("%s", szLan);
	g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lBlackListNum, 8, csTmp);
	
	csTmp.Format("%s", "33012001");
	g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lBlackListNum, 9, csTmp);
	
	csTmp.Format("%s", "");
	g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lBlackListNum, 10, csTmp);		
*/	
    UpdateData(FALSE);
	
	return TRUE;
}

void CDlgVcaFaceDataBase::OnBtnFastScan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	char szLan[128] = {0};
    OPENFILENAME ofn = {0};
	CRect struRect;
	
    memset(m_chFilename, 0, MAX_PATH);
    
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner   = this->GetSafeHwnd();
    ofn.lpstrFilter = "All Files\0*.*\0\0";
    ofn.lpstrFile   = m_chFilename;
    ofn.nMaxFile    = MAX_PATH;
    ofn.Flags       = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
    
    if (GetOpenFileName(&ofn))
    {
        m_csFastRegPicPath.Format("%s", m_chFilename);
    }
	
	if (strlen(m_chFilename) == 0)
	{
		return;
	}
	
	UpdateData(FALSE);
}

void CDlgVcaFaceDataBase::OnBtnFastRegister() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	CFile file;
	char *sFileBuf;
	BOOL bRet = TRUE;
	DWORD dwFileSize = 0;
	sFileBuf = NULL;
	if (!file.Open(m_chFilename, CFile::shareDenyNone))
	{
		file.Close();
		return;
	}
	file.Seek(0, CFile::begin);
	dwFileSize = (DWORD)(file.GetLength());
	if (dwFileSize == 0)
	{
		file.Close();
		return;
	}
    m_dwFileSize = dwFileSize;
	
	sFileBuf = new char[dwFileSize + 4];
	if (sFileBuf == NULL)
	{
		return;
	}
	file.Read(sFileBuf, dwFileSize);
	file.Close();
	
	m_struFastDataRecord.pImage = new BYTE[m_dwFileSize];
	if (m_struFastDataRecord.pImage == NULL)
	{
		return;
	}
	memset(m_struFastDataRecord.pImage, 0, m_dwFileSize);
	memcpy(m_struFastDataRecord.pImage, sFileBuf, m_dwFileSize);
	m_struFastDataRecord.dwSize = sizeof(m_struFastDataRecord);
	
	GetDataRecordInfoFromWnd(m_struFastDataRecord.struAttribute);
	memcpy(m_struFastDataRecord.byRemark2, m_csRemark, 64);
	memcpy(m_struFastDataRecord.byRemark1, m_csUserInfo1, NAME_LEN);
	m_struFastDataRecord.dwImageLen = m_dwFileSize;
	if (!NET_DVR_FastAddFaceDBRecord(m_lServerID, m_iDataBaseID, &m_struFastDataRecord))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FastAddFaceDBRecord m_iDataBaseID[%d] ",m_iDataBaseID);
        g_StringLanType(szLan, "快速添加记录失败", "Fail to add record");
        AfxMessageBox(szLan);
    }
    else
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_FastAddFaceDBRecord m_iDataBaseID[%d] ",m_iDataBaseID);
		g_StringLanType(szLan, "快速添加记录成功", "Succ to add record");
        AfxMessageBox(szLan);
    }
	
	delete []m_struFastDataRecord.pImage;
	m_struFastDataRecord.pImage = NULL;
}

void CDlgVcaFaceDataBase::GetDataRecordInfoFromWnd(NET_VCA_HUMAN_ATTRIBUTE& struDataRecordInfo)
{
	UpdateData(TRUE);
	memcpy(struDataRecordInfo.byBirthDate, m_csBirthDate, MAX_HUMAN_BIRTHDATE_LEN);
	struDataRecordInfo.bySex = m_comboSex.GetCurSel();
	struDataRecordInfo.byCertificateType = m_comboCerfiticateType.GetCurSel();
	struDataRecordInfo.struNativePlace.wCityID = m_comboNativePlace.GetCurSel();
	memcpy(struDataRecordInfo.byName, m_csName, NAME_LEN);
	memcpy(struDataRecordInfo.byCertificateNumber, m_csCertificateNumber, NAME_LEN);
}

void CDlgVcaFaceDataBase::GetHumanAttrCondFromWnd(NET_VCA_HUMANATTRIBUTE_COND& struCond)
{
	UpdateData(TRUE);
	memcpy(struCond.byStartBirthDate, m_csStartBirthDate, MAX_HUMAN_BIRTHDATE_LEN);
	memcpy(struCond.byEndBirthDate, m_csEndBirthDate, MAX_HUMAN_BIRTHDATE_LEN);
	struCond.bySex = m_comboSex.GetCurSel();
	struCond.byCertificateType = m_comboCerfiticateType.GetCurSel();
	struCond.struNativePlace.wCityID = m_comboNativePlace.GetCurSel();
	memcpy(struCond.byName, m_csName, NAME_LEN);
	memcpy(struCond.byCertificateNumber, m_csCertificateNumber, NAME_LEN);
}

void CDlgVcaFaceDataBase::OnBtnRegister() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};

	GetDataRecordInfoFromWnd(m_struDataRecordInfo.struAttribute);
	m_struDataRecordInfo.dwSize = sizeof(m_struDataRecordInfo);
	memcpy(m_struDataRecordInfo.byRemark2, m_csRemark, 64);
	memcpy(m_struDataRecordInfo.byRemark1, m_csUserInfo1, NAME_LEN);
	m_struDataRecordInfo.struRegisterPic.dwImageID = g_struFacePic[0].dwImageID;
	m_struDataRecordInfo.struRegisterPic.dwFaceScore = g_struFacePic[0].dwFaceScore;
	memcpy(&m_struDataRecordInfo.struRegisterPic.struVcaRect, &g_struFacePic[0].struVcaRect, sizeof(NET_VCA_RECT));
	if (!NET_DVR_AddFaceDBRecord(m_lServerID, m_iDataBaseID, &m_struDataRecordInfo))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AddFaceDBRecord m_iDataBaseID[%d] ",m_iDataBaseID);
        g_StringLanType(szLan, "添加记录失败", "Fail to add record");
        AfxMessageBox(szLan);
    }
    else
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AddBlackList m_iDataBaseID[%d] ",m_iDataBaseID);
		g_StringLanType(szLan, "添加记录成功", "Succ to add record");
        AfxMessageBox(szLan);
    }
}

void CDlgVcaFaceDataBase::OnBtnDeleteSingle() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};

	m_struDeleteRecord.dwDeleteType = DELETE_RECORD_SINGLE;
	m_struDeleteRecord.uDeleteCond.dwRecordID = m_dwRecordID;
	if (!NET_DVR_DeleteFaceDBRecord(m_lServerID, m_iDataBaseID, &m_struDeleteRecord))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DeleteFaceDBRecord m_iDataBaseID[%d] ",m_iDataBaseID);
        g_StringLanType(szLan, "删除记录失败", "Fail to delete record");
        AfxMessageBox(szLan);
    }
    else
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DeleteFaceDBRecord m_iDataBaseID[%d] ",m_iDataBaseID);
		g_StringLanType(szLan, "删除记录成功", "Succ to delete record");
        AfxMessageBox(szLan);
    }
}

void CDlgVcaFaceDataBase::OnBtnDeleteBatch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	m_struDeleteRecord.dwDeleteType = DELETE_RECORD_BATCH;
	GetHumanAttrCondFromWnd(m_struDeleteRecord.uDeleteCond.struAttribute);
	if (!NET_DVR_DeleteFaceDBRecord(m_lServerID, m_iDataBaseID, &m_struDeleteRecord))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DeleteFaceDBRecord m_iDataBaseID[%d] ",m_iDataBaseID);
        g_StringLanType(szLan, "删除记录失败", "Fail to delete record");
        AfxMessageBox(szLan);
    }
    else
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DeleteFaceDBRecord m_iDataBaseID[%d] ",m_iDataBaseID);
		g_StringLanType(szLan, "删除记录成功", "Succ to delete record");
        AfxMessageBox(szLan);
    }
}

void CDlgVcaFaceDataBase::OnBtnSearch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	void *pUser = NULL;
	GetHumanAttrCondFromWnd(m_struInquireCond.struAttribute);
	m_struInquireCond.dwDataBaseID = m_iDataBaseID;
	m_lHandle = NET_DVR_InquireFaceDBRecord(m_lServerID, &m_struInquireCond, FunInquireDBCallBack, pUser);
	if (m_lHandle < 0)
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_InquireFaceDBRecord m_iDataBaseID[%d] ",m_iDataBaseID);
        g_StringLanType(szLan, "查询记录失败", "Fail to inquire record");
        AfxMessageBox(szLan);
		return;
    }
    else
    {
		m_lRecordNum = 0;
		m_lTotalNum = 0;
		m_listDataBase.DeleteAllItems();
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_InquireFaceDBRecord m_iDataBaseID[%d] ",m_iDataBaseID);
		m_bInquiring = TRUE;
		SetTimer(FACE_DATABASE_INQUIRE, 200, NULL);
//		g_StringLanType(szLan, "查询记录成功", "Succ to inquire record");
//      AfxMessageBox(szLan);
    }
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgVcaFaceDataBase::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgVcaFaceDataBase::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: Add your message handler code here and/or call default
	DWORD dwState = 0;
	char szLan[128] = {0};

	switch (nIDEvent)
	{
	case FACE_DATABASE_INQUIRE:
		if (m_bInquiring)
		{
            NET_DVR_GetInquireFaceDBProgress(m_lHandle, &dwState);
			if (dwState == 100)
			{
				m_bInquiring = FALSE;
				m_dwTotalRecordNum = m_lTotalNum;
				g_StringLanType(szLan, "查询结束", "Inquire complete");
				AfxMessageBox(szLan);
                if (!NET_DVR_StopSearchDB(m_lHandle))
				{
					g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopSearchDB m_lHandle[%d] ",m_lHandle);
					g_StringLanType(szLan, "停止查询失败", "Fail to inquire");
					AfxMessageBox(szLan);
				}
				else
				{
					g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopSearchDB m_lHandle[%d] ",m_lHandle);
//					g_StringLanType(szLan, "停止查询成功", "Succ to inquire");
//					AfxMessageBox(szLan);
					m_lHandle = -1;
				}
			}
		}

		if (m_bSearching)
		{
			NET_DVR_GetSearchFaceDBProgress(m_lSearchHandle, &dwState);
			if (dwState == 100)
			{
				m_bSearching = FALSE;
				m_dwTotalRecordNum = m_lTotalNum;
				g_StringLanType(szLan, "检索结束", "Search complete");
				AfxMessageBox(szLan);
                if (!NET_DVR_StopSearchDB(m_lSearchHandle))
				{
					g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopSearchDB m_lSearchHandle[%d] ",m_lSearchHandle);
					g_StringLanType(szLan, "停止检索失败", "Fail to search");
					AfxMessageBox(szLan);
				}
				else
				{
					g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopSearchDB m_lSearchHandle[%d] ",m_lSearchHandle);
//					g_StringLanType(szLan, "停止检索成功", "Succ to search");
//					AfxMessageBox(szLan);
					m_lSearchHandle = -1;
				}
			}
		}
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CDlgVcaFaceDataBase::OnDestroy() 
{
	KillTimer(FACE_DATABASE_INQUIRE);
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here	
}

void CDlgVcaFaceDataBase::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};

	m_bInquiring = FALSE;
	m_bSearching = FALSE;

	if (m_lHandle > 0)
	{
		if (!NET_DVR_StopSearchDB(m_lHandle))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopSearchDB m_lHandle[%d] ",m_lHandle);
			g_StringLanType(szLan, "停止查询失败", "Fail to inquire");
			AfxMessageBox(szLan);
		}
		else
		{
			m_lHandle = -1;
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopSearchDB m_lHandle[%d] ",m_lHandle);
//			g_StringLanType(szLan, "停止查询成功", "Succ to inquire");
//			AfxMessageBox(szLan);
		}
	}

	if (m_lSearchHandle > 0)
	{
        if (!NET_DVR_StopSearchDB(m_lSearchHandle))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopSearchDB m_lSearchHandle[%d] ",m_lSearchHandle);
			g_StringLanType(szLan, "停止检索失败", "Fail to search");
			AfxMessageBox(szLan);
		}
		else
		{
			m_lSearchHandle = -1;
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopSearchDB m_lSearchHandle[%d] ",m_lSearchHandle);
//			g_StringLanType(szLan, "停止检索成功", "Succ to search");
//			AfxMessageBox(szLan);
		}
	}	
	CDialog::OnCancel();
}

void CDlgVcaFaceDataBase::OnBtnGetFacePic() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CRect struRect; 
	char szLan[128] = {0};

	NET_VCA_FIND_MATCHPIC_COND struCond = {0};
	struCond.dwSize = sizeof(struCond);
	struCond.dwDataBaseType = DATABASE_FACE;
	struCond.dwDataBaseID = m_iDataBaseID;
	struCond.dwRecordID = m_dwRecordID;

	NET_VCA_FIND_MATCHPIC_RESULT struRecvBuf = {0};
	struRecvBuf.pPicBuffer = new BYTE[2*1024*1024];
	if (struRecvBuf.pPicBuffer == NULL)
	{
		return;
	}
	memset(struRecvBuf.pPicBuffer, 0, 2*1024*1024);

	if (!NET_DVR_FindMatchPicture(m_lServerID, &struCond, &struRecvBuf))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FindMatchPicture");
		g_StringLanType(szLan, "按条件查找背景图失败", "Fail to find match picture");
        AfxMessageBox(szLan);
		delete []struRecvBuf.pPicBuffer;
		struRecvBuf.pPicBuffer = NULL;
		return;
	}
	else
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_FindMatchPicture");
	}
	if (struRecvBuf.dwPicLen > 0)
    {       
        char cFilename[256] = {0};
        HANDLE hFile;
        DWORD dwReturn;
        
        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
        
        sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIP);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }
        
        sprintf(cFilename, "%s\\LocalTime[FaceDB][%s].jpg",cFilename, chTime);
        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struRecvBuf.pPicBuffer, struRecvBuf.dwPicLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
	}
	
	if (struRecvBuf.pPicBuffer != NULL)
	{
		delete []struRecvBuf.pPicBuffer;
		struRecvBuf.pPicBuffer = NULL;
	}
	UpdateData(FALSE);
}

void CDlgVcaFaceDataBase::OnBtnStartSearch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	void *pUser = NULL;
	GetHumanAttrCondFromWnd(m_struSearchCond.struAttribute);
	m_struSearchCond.dwDataBaseID = m_iDataBaseID;
	m_struSearchCond.dwMaxSearchNum = m_dwSearchNum;
	m_struSearchCond.wThreshold = m_dwThreld;

	if (m_bChkAdvanceEn)
	{
		m_struSearchCond.struSearchParam.dwSearchType = VCA_ADVANCE_SEARCH_DATABASE;
		m_struSearchCond.struSearchParam.uSearchCond.struAdvanceFind.dwDataBaseID = m_dwAdvanceDBId;
		m_struSearchCond.struSearchParam.uSearchCond.struAdvanceFind.dwDataBaseType = m_comboAdvanceDBType.GetCurSel()+1;
		m_struSearchCond.struSearchParam.uSearchCond.struAdvanceFind.dwFacePicID  = m_dwAdvancePicId;
	}
	else
	{
		m_struSearchCond.struSearchParam.dwSearchType = VCA_NORMAL_SEARCH_DATABASE;
		m_struSearchCond.struSearchParam.uSearchCond.struNormalFind.dwImageID = g_struFacePic[0].dwImageID;
		m_struSearchCond.struSearchParam.uSearchCond.struNormalFind.dwFaceScore = g_struFacePic[0].dwFaceScore;
		memcpy(&m_struSearchCond.struSearchParam.uSearchCond.struNormalFind.struVcaRect, &g_struFacePic[0].struVcaRect, sizeof(NET_VCA_RECT));
	}

#if 0
	m_struSearchCond.dwDataBaseID   = 3;
    m_struSearchCond.dwMaxSearchNum = 100;
    m_struSearchCond.struRegisterPic.dwImageID   = 20;
    m_struSearchCond.struRegisterPic.dwFaceScore = 27;
    m_struSearchCond.struRegisterPic.struVcaRect.fX = 0.74;
    m_struSearchCond.struRegisterPic.struVcaRect.fY = 0.594;
    m_struSearchCond.struRegisterPic.struVcaRect.fWidth  = 0.069;
    m_struSearchCond.struRegisterPic.struVcaRect.fHeight = 0.123;
#endif

	m_lSearchHandle = NET_DVR_SearchFaceDB(m_lServerID, &m_struSearchCond, FunSearchDBCallBack, pUser);
	if (m_lSearchHandle < 0)
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SearchFaceDB m_iDataBaseID[%d] ",m_iDataBaseID);
        g_StringLanType(szLan, "检索失败", "Fail to search record");
        AfxMessageBox(szLan);
		return;
    }
    else
    {
		m_lRecordNum = 0;
		m_lTotalNum = 0;
		m_listDataBase.DeleteAllItems();
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SearchFaceDB m_iDataBaseID[%d] ",m_iDataBaseID);
		m_bSearching = TRUE;
		SetTimer(FACE_DATABASE_INQUIRE, 200, NULL);
//		g_StringLanType(szLan, "检索成功", "Succ to search record");
//       AfxMessageBox(szLan);
    }
}

void CDlgVcaFaceDataBase::OnBtnStopSearch() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	m_bSearching = FALSE;
	m_dwTotalRecordNum = m_lTotalNum;
	if (m_lSearchHandle >= 0)
	{
        if (!NET_DVR_StopSearchDB(m_lSearchHandle))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopSearchDB m_lSearchHandle[%d] ",m_lSearchHandle);
			g_StringLanType(szLan, "停止检索失败", "Fail to search");
			AfxMessageBox(szLan);
		}
		else
		{
			m_lSearchHandle = -1;
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopSearchDB m_lSearchHandle[%d] ",m_lSearchHandle);
			//			g_StringLanType(szLan, "停止检索成功", "Succ to search");
			//			AfxMessageBox(szLan);
		}
	}
	UpdateData(FALSE);
}

void CDlgVcaFaceDataBase::OnBtnStopInquire() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	
	m_bInquiring = FALSE;
	m_dwTotalRecordNum = m_lTotalNum;
	if (m_lHandle >= 0)
	{
		if (!NET_DVR_StopSearchDB(m_lHandle))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopSearchDB m_lHandle[%d] ",m_lHandle);
			g_StringLanType(szLan, "停止查询失败", "Fail to inquire");
			AfxMessageBox(szLan);
		}
		else
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopSearchDB m_lHandle[%d] ",m_lHandle);
			//			g_StringLanType(szLan, "停止查询成功", "Succ to inquire");
			//			AfxMessageBox(szLan);
			m_lHandle = -1;
		}
	}
	UpdateData(FALSE);
}

LRESULT CDlgVcaFaceDataBase::OnWMProcFaceCallback(WPARAM wParam, LPARAM lParam)
{
	DWORD dwType = (DWORD)(wParam);
	char *pRecordInfo = (char *)(lParam);		
	
	char szLan[128] ={0};
	switch (dwType)
	{
	case INQUIRE_FACE_DATABASE:
		ProcInquireFaceCallback(wParam, lParam);
		break;
	case SEARCH_FACE_DATABASE:
		ProcSearchFaceCallback(wParam, lParam);
		break;
	default:
		break;
	}
	
	if (pRecordInfo != NULL)
	{
		delete[] pRecordInfo;
		pRecordInfo = NULL;
	}
	
	return NULL;
}

void CDlgVcaFaceDataBase::ProcInquireFaceCallback(WPARAM wParam, LPARAM lParam)
{
	CString csTmp;
	char szLan[128] = {0};
	char cFilename[256] = {0};
	char *pDataInfo = (char *)(lParam);

	g_pVcaFaceDataBase->m_lTotalNum++;
	NET_VCA_INQUIRE_DATARECORD_RESULT struInquireResult = {0};
	memcpy(&struInquireResult, pDataInfo, sizeof(struInquireResult));
		
	if (g_pVcaFaceDataBase->m_lRecordNum <= 2000)
	{
		csTmp.Format("%d", g_pVcaFaceDataBase->m_lTotalNum);
		g_pVcaFaceDataBase->m_listDataBase.InsertItem(g_pVcaFaceDataBase->m_lRecordNum, csTmp,0);
		
		csTmp.Format("%d", struInquireResult.dwRecordID);
		g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lRecordNum, 1, csTmp);
		
		csTmp.Format("%s", struInquireResult.struAttribute.byName);
		g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lRecordNum, 2, csTmp);
		
		switch (struInquireResult.struAttribute.bySex)
		{
		case 0:
			g_StringLanType(szLan, "无", "No");
			break;
		case 1:
			g_StringLanType(szLan, "男", "Man");
			break;
		case 2:
			g_StringLanType(szLan, "女", "Woman");
			break;
		default:
			g_StringLanType(szLan, "未知", "Unknow");
			break;
		}
		csTmp.Format("%s", szLan);
		g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lRecordNum, 3, csTmp);
		
		csTmp.Format("%s", struInquireResult.struAttribute.byBirthDate);
		g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lRecordNum, 4, csTmp);
		
		csTmp.Format("%d", struInquireResult.struAttribute.struNativePlace.wCityID);
		g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lRecordNum, 5, csTmp);
		
		switch (struInquireResult.struAttribute.byCertificateType)
		{
		case 0:
			g_StringLanType(szLan, "无", "No");
			break;
		case 1:
			g_StringLanType(szLan, "身份证", "identification card");
			break;
		case 2:
			g_StringLanType(szLan, "警官证", "Officers card");
			break;
		default:
			g_StringLanType(szLan, "未知", "Unknow");
			break;
		}
		csTmp.Format("%s", szLan);
		g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lRecordNum, 6, csTmp);
		
		csTmp.Format("%s", struInquireResult.struAttribute.byCertificateNumber);
		g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lRecordNum, 7, csTmp);
		
		csTmp.Format("%s", struInquireResult.byRemark1);
		g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lRecordNum, 8, csTmp);
		
		g_pVcaFaceDataBase->m_lRecordNum++;
		
		if (struInquireResult.dwFacePicLen > 0 && struInquireResult.pFacePic != NULL)
		{        
			char cFilename[256] = {0};
			HANDLE hFile;
			DWORD dwReturn;
			
			SYSTEMTIME t;
			GetLocalTime(&t);
			char chTime[128];
			sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
			
			sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[g_pVcaFaceDataBase->m_iDevIndex].chDeviceIP);
			if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
			{
				CreateDirectory(cFilename, NULL);
			}
			
			sprintf(cFilename, "%s\\INQUIRE_FACEDATA[%s]_database[%d]_record[%d].jpg",cFilename, chTime, struInquireResult.dwDataBaseID,struInquireResult.dwRecordID);
			hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile == INVALID_HANDLE_VALUE)
			{
				return;
			}
			WriteFile(hFile, struInquireResult.pFacePic, struInquireResult.dwFacePicLen, &dwReturn, NULL);
			CloseHandle(hFile);
			hFile = NULL;
		}
	}
	if (struInquireResult.pFacePic != NULL)
	{
		delete []struInquireResult.pFacePic;
		struInquireResult.pFacePic = NULL;
	}
}

void CDlgVcaFaceDataBase::ProcSearchFaceCallback(WPARAM wParam, LPARAM lParam)
{
	CString csTmp;
	char szLan[128] = {0};
	char *pDataInfo = (char *)(lParam);
	
	NET_VCA_SEARCH_DATARECORD_RESULT struSearchResult = {0};
	memcpy(&struSearchResult, pDataInfo, sizeof(NET_VCA_SEARCH_DATARECORD_RESULT));
	
	g_pVcaFaceDataBase->m_lTotalNum++;
	if (g_pVcaFaceDataBase->m_lRecordNum <= 2000)
    {
		csTmp.Format("%d", g_pVcaFaceDataBase->m_lTotalNum);
		g_pVcaFaceDataBase->m_listDataBase.InsertItem(g_pVcaFaceDataBase->m_lRecordNum, csTmp,0);
		
		csTmp.Format("%d", struSearchResult.dwRecordID);
		g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lRecordNum, 1, csTmp);
		
		csTmp.Format("%s", struSearchResult.struAttribute.byName);
		g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lRecordNum, 2, csTmp);
		
		switch (struSearchResult.struAttribute.bySex)
		{
		case 0:
			g_StringLanType(szLan, "无", "No");
			break;
		case 1:
			g_StringLanType(szLan, "男", "Man");
			break;
		case 2:
			g_StringLanType(szLan, "女", "Woman");
			break;
		default:
			g_StringLanType(szLan, "未知", "Unknow");
			break;
		}
		csTmp.Format("%s", szLan);
		g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lRecordNum, 3, csTmp);
		
		csTmp.Format("%s", struSearchResult.struAttribute.byBirthDate);
		g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lRecordNum, 4, csTmp);
		
		csTmp.Format("%d", struSearchResult.struAttribute.struNativePlace.wCityID);
		g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lRecordNum, 5, csTmp);
		
		switch (struSearchResult.struAttribute.byCertificateType)
		{
		case 0:
			g_StringLanType(szLan, "无", "No");
			break;
		case 1:
			g_StringLanType(szLan, "身份证", "identification card");
			break;
		case 2:
			g_StringLanType(szLan, "警官证", "Officers card");
			break;
		default:
			g_StringLanType(szLan, "未知", "Unknow");
			break;
		}
		csTmp.Format("%s", szLan);
		g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lRecordNum, 6, csTmp);
		
		csTmp.Format("%s", struSearchResult.struAttribute.byCertificateNumber);
		g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lRecordNum, 7, csTmp);
		
		csTmp.Format("%s", struSearchResult.byRemark1);
		g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lRecordNum, 8, csTmp);
		
		csTmp.Format("%f", struSearchResult.fSimilarity);
		g_pVcaFaceDataBase->m_listDataBase.SetItemText(g_pVcaFaceDataBase->m_lRecordNum, 9, csTmp);
		
		if (g_pVcaFaceDataBase->m_lRecordNum == 10000)
		{
			g_pVcaFaceDataBase->m_lRecordNum = 0;
		}
		else
		{
			g_pVcaFaceDataBase->m_lRecordNum++;
		}
		g_pVcaFaceDataBase->m_lTotalNum++;
		
		if (struSearchResult.dwFacePicLen > 0 && struSearchResult.pFacePic != NULL)
        {        
            char cFilename[256] = {0};
            HANDLE hFile;
            DWORD dwReturn;
            
            SYSTEMTIME t;
            GetLocalTime(&t);
            char chTime[128];
            sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
            
            sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[g_pVcaFaceDataBase->m_iDevIndex].chDeviceIP);
            if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
            {
                CreateDirectory(cFilename, NULL);
            }
            
            sprintf(cFilename, "%s\\SEARCH_FACEDATA[%s]_database[%d]_record[%d].jpg",cFilename, chTime, struSearchResult.dwDataBaseID,struSearchResult.dwRecordID);
            hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE)
            {
                return;
            }
            WriteFile(hFile, struSearchResult.pFacePic, struSearchResult.dwFacePicLen, &dwReturn, NULL);
            CloseHandle(hFile);
            hFile = NULL;
		}
    }
	if (struSearchResult.pFacePic != NULL)
	{
		delete []struSearchResult.pFacePic;
		struSearchResult.pFacePic = NULL;
	}
}

void CDlgVcaFaceDataBase::OnBtnUpdateRecord() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	GetDataRecordInfoFromWnd(m_struDataRecordInfo.struAttribute);
	m_struDataRecordInfo.dwSize = sizeof(m_struDataRecordInfo);
	m_struDataRecordInfo.dwRecordID = m_dwRecordID;
	memcpy(m_struDataRecordInfo.byRemark2, m_csRemark, 64);
	memcpy(m_struDataRecordInfo.byRemark1, m_csUserInfo1, NAME_LEN);
	m_struDataRecordInfo.struRegisterPic.dwImageID = g_struFacePic[0].dwImageID;
	m_struDataRecordInfo.struRegisterPic.dwFaceScore = g_struFacePic[0].dwFaceScore;
	memcpy(&m_struDataRecordInfo.struRegisterPic.struVcaRect, &g_struFacePic[0].struVcaRect, sizeof(NET_VCA_RECT));
	if (!NET_DVR_UpdateFaceDBRecord(m_lServerID, m_iDataBaseID, &m_struDataRecordInfo))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_UpdateFaceDBRecord m_iDataBaseID[%d] ",m_iDataBaseID);
        g_StringLanType(szLan, "修改记录失败", "Fail to update record");
        AfxMessageBox(szLan);
    }
    else
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_UpdateFaceDBRecord m_iDataBaseID[%d] ",m_iDataBaseID);
		g_StringLanType(szLan, "修改记录成功", "Succ to update record");
        AfxMessageBox(szLan);
    }
}
