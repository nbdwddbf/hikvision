// DlgEncodeJoint.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgEncodeJoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEncodeJoint dialog


CDlgEncodeJoint::CDlgEncodeJoint(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEncodeJoint::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEncodeJoint)
	m_iChannel = 0;
	m_iDevType = 0;
	m_csIPAddr = _T("");
	m_iPort = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_lChannel = -1;
    memset(&m_struEncodeJoint, 0, sizeof(m_struEncodeJoint));

}


void CDlgEncodeJoint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEncodeJoint)
	DDX_Control(pDX, IDC_COMBO_JOINT, m_comboJoint);
	DDX_Text(pDX, IDC_EDIT_CHANNEL, m_iChannel);
	DDX_Text(pDX, IDC_EDIT_DEV_TYPE, m_iDevType);
	DDX_Text(pDX, IDC_EDIT_IP_ADDR, m_csIPAddr);
	DDX_Text(pDX, IDC_EDIT_PORT, m_iPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEncodeJoint, CDialog)
	//{{AFX_MSG_MAP(CDlgEncodeJoint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEncodeJoint message handlers

BOOL CDlgEncodeJoint::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitWnd();
    GetEncodeJointParam(m_struEncodeJoint);
    SetEncodeJointParamToWnd(m_struEncodeJoint);
    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a  control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEncodeJoint::InitWnd()
{
    
    m_comboJoint.ResetContent();
    m_comboJoint.AddString("No joint");
    m_comboJoint.AddString("Joint");
}

BOOL CDlgEncodeJoint::GetEncodeJointParam(NET_DVR_ENCODE_JOINT_PARAM &struEncodeJoint)
{
    if (NET_DVR_MatrixGetEncodeJoint(m_lServerID, m_lChannel, &m_struEncodeJoint))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_MatrixGetEncodeJoint");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_MatrixGetEncodeJoint");
        return FALSE;
    }
}

void CDlgEncodeJoint::SetEncodeJointParamToWnd(NET_DVR_ENCODE_JOINT_PARAM &struEncodeJoint)
{
    m_comboJoint.SetCurSel(struEncodeJoint.byJointed);
    m_iDevType = struEncodeJoint.byDevType;
    m_csIPAddr = struEncodeJoint.struIP.sIpV4;
    m_iPort = struEncodeJoint.wPort;
    m_iChannel= struEncodeJoint.wChannel;
}
