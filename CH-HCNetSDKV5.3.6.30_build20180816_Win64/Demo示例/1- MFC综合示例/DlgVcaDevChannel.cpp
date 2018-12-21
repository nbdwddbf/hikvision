// DlgVcaDevChannel.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaDevChannel.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDevChannel dialog


CDlgVcaDevChannel::CDlgVcaDevChannel(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaDevChannel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaDevChannel)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgVcaDevChannel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaDevChannel)
	DDX_Control(pDX, IDC_LIST_CHANNEL, m_listChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaDevChannel, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaDevChannel)
	ON_BN_CLICKED(IDC_BTN_SELECT, OnBtnSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDevChannel message handlers

BOOL CDlgVcaDevChannel::OnInitDialog()
{
	CDialog::OnInitDialog();
    
	InitCtrlState();

	return TRUE;
}

void CDlgVcaDevChannel::OnBtnSelect() 
{   
	m_vctChannel.clear();

	int nChanCount = m_listChannel.GetCount();
	for (int i = 0; i < nChanCount; i++)
	{   
		if (m_listChannel.GetCheck(i))
		{
			DWORD dwChannel = m_listChannel.GetItemData(i);
			m_vctChannel.push_back(dwChannel);
		}
	}
	OnOK();
}


void CDlgVcaDevChannel::InitCtrlState()
{   
	char szLan[64] = {0};
    char sbufCn[64] = {0};
    char sbufEn[64] = {0};

	int nChannelnumber = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
    m_listChannel.ResetContent();
    for (int i = 0; i < nChannelnumber; i++)
    {
        sprintf(sbufCn, "Í¨µÀ%d", (i+1));
        sprintf(sbufEn, "Channel%d", (i+1));
        g_StringLanType(szLan, sbufCn, sbufEn);
        m_listChannel.InsertString(i, szLan);
		m_listChannel.SetItemData(i,i + 1);
    }
    
	int nChanCount = m_listChannel.GetCount();
	for (int j = 0; j < nChanCount; j++)
	{   
		DWORD dwChannel = m_listChannel.GetItemData(j);
		if (find(m_vctChannel.begin(),m_vctChannel.end(),dwChannel) != m_vctChannel.end())
		{
			m_listChannel.SetCheck(j,TRUE);
		}
		else
		{
			m_listChannel.SetCheck(j,FALSE);
		}
	}
	
}

void CDlgVcaDevChannel::SetSelChannel(vector<DWORD> vctChannel)
{
	m_vctChannel = vctChannel;
}

void CDlgVcaDevChannel::GetSelChannel(vector<DWORD>& vctChannel)
{
	vctChannel = m_vctChannel;
}
