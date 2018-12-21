// DlgSDIMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSDIMatrix.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSDIMatrix dialog


CDlgSDIMatrix::CDlgSDIMatrix(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSDIMatrix::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSDIMatrix)
	m_dwInputNum = 0;
	m_dwOutputNum = 0;
	m_dwOutputChannel = 0;
	m_dwInputChannel = 0;
	m_csUserPassword = _T("");
	//}}AFX_DATA_INIT
}


void CDlgSDIMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSDIMatrix)
	DDX_Control(pDX, IDC_CHK_SDI_CHANGEPASSWORD, m_btnChangePassword);
	DDX_Control(pDX, IDC_CHK_SDI_ONESWITCHALL, m_btnOneSwitchAll);
	DDX_Control(pDX, IDC_LST_SDI_IORELATION_DISPLAY, m_ctrRelationDisplay);
	DDX_Text(pDX, IDC_EDT_SDI_VAILDINPUT, m_dwInputNum);
	DDV_MinMaxDWord(pDX, m_dwInputNum, 1, 256);
	DDX_Text(pDX, IDC_EDT_SDI_VAILDOUTPUT, m_dwOutputNum);
	DDV_MinMaxDWord(pDX, m_dwOutputNum, 1, 64);
	DDX_Text(pDX, IDC_EDT_SDI_OUTPUT_CHANNEL, m_dwOutputChannel);
	DDX_Text(pDX, IDC_EDT_SDI_INPUT_CHANNEL, m_dwInputChannel);
	DDX_Text(pDX, IDC_EDT_SDI_PASSWORD, m_csUserPassword);
	DDV_MaxChars(pDX, m_csUserPassword, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSDIMatrix, CDialog)
	//{{AFX_MSG_MAP(CDlgSDIMatrix)
	ON_BN_CLICKED(IDC_BTN_SDI_REFRESH, OnBtnSdiRefresh)
	ON_BN_CLICKED(IDC_BTN_SDI_DELALLRELATION, OnBtnSdiDelallrelation)
	ON_BN_CLICKED(IDC_BTN_SDI_BASECFG_REFRESH, OnBtnSdiBasecfgRefresh)
	ON_BN_CLICKED(IDC_BTN_SDI_BASECFG_SET, OnBtnSdiBasecfgSet)
	ON_BN_CLICKED(IDC_BTN_SDI_SWITCH, OnBtnSdiSwitch)
	ON_BN_CLICKED(IDC_CHK_SDI_ONESWITCHALL, OnChkSdiOneswitchall)
	ON_BN_CLICKED(IDC_BTN_SDI_CHANGEPASSWORD, OnBtnSdiChangepassword)
	ON_BN_CLICKED(IDC_CHK_SDI_CHANGEPASSWORD, OnChkSdiChangepassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSDIMatrix message handlers

void CDlgSDIMatrix::OnBtnSdiRefresh() 
{
	// TODO: Add your control notification handler code here
    char szLan[128]; 
	m_ctrRelationDisplay.ResetContent(); 
    g_StringLanType(szLan, "输入 --> 输出", "input --> output" ); 
    m_ctrRelationDisplay.AddString(szLan); 
    NET_DVR_IO_RELATION_INFO struRelationInfo = {0}; 
    DWORD   dwReturned; 
    CString csNum; 
    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_MATRIX_IO_RELATION, 0, &struRelationInfo, sizeof(struRelationInfo), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_MATRIX_IO_RELATION");
        CString csDisplay;
        for (int i=0; i<MATRIX_MAX_OUTPUT_NUM; i++)
        {
            if ( struRelationInfo.dwIORelation[i] != 0 )
            {
                csDisplay.Format("%4d --> %4d", struRelationInfo.dwIORelation[i], i+1); 
                m_ctrRelationDisplay.AddString(csDisplay);
            }                     
        }
    }
    else 
    {
        CString csError; 
        csError.Format(_T("Failed to get relation, Error Code %d"),NET_DVR_GetLastError()); 
        MessageBox(csError);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_MATRIX_IO_RELATION");
    }
    m_ctrRelationDisplay.UpdateData(FALSE); 
}

void CDlgSDIMatrix::OnBtnSdiDelallrelation() 
{
	// TODO: Add your control notification handler code here
	SwitchIO(0, 0xffffffff); 
}

void CDlgSDIMatrix::OnBtnSdiBasecfgRefresh() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_MATRIX_BASE_CFG struBaseCfg = {0}; 
    DWORD   dwReturned; 
    CString csInputNum, csOutputNum;
    char szLan[128] = {0}; 
    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_MATRIX_BASE_CFG, 0, &struBaseCfg, sizeof(struBaseCfg), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_MATRIX_BASE_CFG");
        m_dwInputNum = struBaseCfg.dwValidInputNum; 
        m_dwOutputNum = struBaseCfg.dwValidOutputNum; 
        csInputNum.Format("[1, %d]", m_dwInputNum); 
        csOutputNum.Format("[1, %d]", m_dwOutputNum); 
    }
    else 
    {
        CString csError; 
        csError.Format(_T("Failed to refresh, Error Code %d"),NET_DVR_GetLastError()); 
        MessageBox(csError);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_MATRIX_BASE_CFG");
        g_StringLanType(szLan, "无输入路数", "No Input Num" ); 
        csInputNum.Format(szLan); 
        g_StringLanType(szLan, "无输出路数", "No Output Num" ); 
        csOutputNum.Format(szLan); 
        m_dwInputNum = 0; 
        m_dwOutputNum = 0; 
    }
    GetDlgItem(IDC_STATIC_SDI_INPUT_CHANNEL)->SetWindowText(csInputNum);
    GetDlgItem(IDC_STATIC_SDI_OUTPUT_CHANNEL)->SetWindowText(csOutputNum);
    UpdateData(FALSE); 
}

void CDlgSDIMatrix::OnBtnSdiBasecfgSet() 
{
	// TODO: Add your control notification handler code here
    if ( !UpdateData(TRUE) )
    {
        return ; 
    }
    NET_DVR_MATRIX_BASE_CFG struBaseCfg = {0}; 
    struBaseCfg.dwSize = sizeof(NET_DVR_MATRIX_BASE_CFG); 
    struBaseCfg.dwValidInputNum = m_dwInputNum; 
    struBaseCfg.dwValidOutputNum = m_dwOutputNum; 
    if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_MATRIX_BASE_CFG, 0, &struBaseCfg, sizeof(struBaseCfg)))
    {       
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MATRIX_BASE_CFG");
        OnBtnSdiBasecfgRefresh(); 
    }
    else
    {
        CString csError; 
        csError.Format(_T("Failed to Set, Error Code %d"),NET_DVR_GetLastError()); 
        AfxMessageBox(csError);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MATRIX_BASE_CFG");
    }
    
}

void CDlgSDIMatrix::OnBtnSdiSwitch() 
{
	// TODO: Add your control notification handler code here
    if ( !UpdateData(TRUE) )
    {
        return ; 
    }
    CString csError; 
    if ( m_dwInputChannel > m_dwInputNum )
    {
        csError.Format("Error, %d out of the input channel range", m_dwInputChannel); 
        MessageBox(csError); 
        return ; 
    }
    DWORD dwOutputChannel; 
    if ( m_btnOneSwitchAll.GetCheck() == BST_CHECKED)
    {
        dwOutputChannel = 0xffffffff; 
    } 
    else
    {
        if ( m_dwOutputChannel >  m_dwOutputNum )
        {
            csError.Format("Error, %d out of the output channel range", m_dwOutputChannel); 
            MessageBox(csError); 
            return ; 
        }
        dwOutputChannel = m_dwOutputChannel; 
    }
    SwitchIO(m_dwInputChannel, dwOutputChannel); 
}

BOOL CDlgSDIMatrix::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	OnBtnSdiBasecfgRefresh(); 
    OnBtnSdiRefresh();  
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDlgSDIMatrix::SwitchIO(DWORD input, DWORD output)
{
    NET_DVR_MATRIX_SWITCH_INFO struSwitchInfo = {0};
    struSwitchInfo.dwSize = sizeof(struSwitchInfo);
    struSwitchInfo.dwInputChan = input; 
    struSwitchInfo.dwOutputChan = output; 

    if (NET_DVR_RemoteControl(m_lUserID, NET_DVR_SWITCH_MATRIX_IO, &struSwitchInfo, sizeof(NET_DVR_MATRIX_SWITCH_INFO)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SWITCH_MATRIX_IO");
        OnBtnSdiRefresh(); 
        return true; 
    }
    else
    {
        CString csError; 
        csError.Format(_T("Failed to switch, Error Code %d"), NET_DVR_GetLastError()); 
        MessageBox(csError);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_SWITCH_MATRIX_IO");
        return false; 
	}   
}

void CDlgSDIMatrix::OnChkSdiOneswitchall() 
{
	// TODO: Add your control notification handler code here
	if ( m_btnOneSwitchAll.GetCheck() == BST_CHECKED )
	{
        GetDlgItem(IDC_EDT_SDI_OUTPUT_CHANNEL)->EnableWindow(FALSE); 
	} 
	else
	{
        GetDlgItem(IDC_EDT_SDI_OUTPUT_CHANNEL)->EnableWindow(TRUE); 
	}
}

void CDlgSDIMatrix::OnBtnSdiChangepassword() 
{
	// TODO: Add your control notification handler code here
    
    UpdateData(TRUE); 
    NET_DVR_VCS_USER_INFO struUserInfo = {0}; 
    struUserInfo.dwSize = sizeof(struUserInfo); 
    struUserInfo.byPriority = 1;  // 1 - admin 
    strcpy((char *)struUserInfo.sUserName, "admin"); 
    strcpy((char *)struUserInfo.sPassWord, (LPCTSTR)m_csUserPassword); //修改密码
 //   struUserInfo.sPassWord[m_csUserPassword.GetLength()] = '\0'; 
    struUserInfo.dwRight = 0xffffffff;     // 所有权限都有
    char szLan[128]; 
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_VCS_USER_CFG, 0, &struUserInfo, sizeof(struUserInfo)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VCS_USER_CFG failed");
        g_StringLanType(szLan, "修改密码失败", "Failed to modify the password" ); 
        AfxMessageBox(szLan); 
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VCS_USER_CFG success");
        g_StringLanType(szLan, "修改成功，之后登录需要用新密码", "Success to modify the password, Login need the new password" ); 
        AfxMessageBox(szLan);
        m_csUserPassword = ""; 
	}
    UpdateData(FALSE); 
}

void CDlgSDIMatrix::OnChkSdiChangepassword() 
{
	// TODO: Add your control notification handler code here
    m_btnChangePassword.UpdateData(TRUE); 
    if ( m_btnChangePassword.GetCheck() == BST_CHECKED)
    {
        GetDlgItem(IDC_STATIC_SDI_PASSWORD)->EnableWindow(TRUE); 
        GetDlgItem(IDC_EDT_SDI_PASSWORD)->EnableWindow(TRUE);
        GetDlgItem(IDC_BTN_SDI_CHANGEPASSWORD)->EnableWindow(TRUE);
    } 
    else
    {
        GetDlgItem(IDC_STATIC_SDI_PASSWORD)->EnableWindow(FALSE); 
        GetDlgItem(IDC_EDT_SDI_PASSWORD)->EnableWindow(FALSE);
        GetDlgItem(IDC_BTN_SDI_CHANGEPASSWORD)->EnableWindow(FALSE);
    }
}
