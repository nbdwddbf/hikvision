// SubDlgWndSequence.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "SubDlgWndSequence.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubDlgWndSequence dialog


CSubDlgWndSequence::CSubDlgWndSequence(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgWndSequence::IDD, pParent)
	, m_pComboBox(NULL)
{
	//{{AFX_DATA_INIT(CSubDlgWndSequence)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSubDlgWndSequence::~CSubDlgWndSequence()
{
}

void CSubDlgWndSequence::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgWndSequence)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubDlgWndSequence, CDialog)
	//{{AFX_MSG_MAP(CSubDlgWndSequence)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDlgWndSequence message handlers

void CSubDlgWndSequence::OnSetCurSel(int nIndex)
{
    if (0xff == nIndex)
	{
		m_pComboBox->SetCurSel(m_pComboBox->GetCount()-1);
	}
	else
	{
        for (int i = 0; i < m_pComboBox->GetCount(); i++ )
        {
            if (m_pComboBox->GetItemData(i) == nIndex)
            {
                m_pComboBox->SetCurSel(i);
            }
        }
    }
}

int CSubDlgWndSequence::OnGetCurSel(void)
{
	int nReturn = m_pComboBox->GetItemData(m_pComboBox->GetCurSel());

	if (m_pComboBox->GetCurSel() == m_pComboBox->GetCount()-1)
	{
		nReturn = 0xff;
	}

	return nReturn;
}

void CSubDlgWndSequence::OnInitialize(int nChanNum, int nIPChanNum, int nStartNum)
{
	int i = -1;
	CString csTmp(_T(""));
    
	CRect rtComboBox(0, 0, 0, 0);
	CRect rtWnd(0, 0, 0, 0);


	if (NULL == m_pComboBox->m_hWnd)
	{
		GetWindowRect(&rtWnd);
		rtComboBox = CRect(rtWnd.Width()/6, rtWnd.Height()*3/8, rtWnd.Width()*5/6, rtWnd.Height()*5);
		m_pComboBox->Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST , rtComboBox, this, 1);
        //m_pComboBox->SetItemHeight(-1, 100);
    }

	for (;m_pComboBox->GetCount() > 0;)
	{
		m_pComboBox->DeleteString(0);
	}
    int nIndex = 0;
	for (i = 0; i < nChanNum; ++i, nIndex++)
	{
		csTmp.Format(_T("A%d"), i+1);
		m_pComboBox->AddString(csTmp);
        m_pComboBox->SetItemData(nIndex, i + nStartNum);
	}

    int iDevIndex = g_pMainDlg->GetCurDeviceIndex();
    for (i = 0; i < nIPChanNum; ++i)
    {
        
        if (g_struDeviceInfo[iDevIndex].pStruIPParaCfgV40[0].struStreamMode[i].uGetStream.struChanInfo.byIPID != 0 \
            && g_struDeviceInfo[iDevIndex].pStruIPParaCfgV40[0].struStreamMode[i].uGetStream.struChanInfo.byEnable == TRUE)
        {
            csTmp.Format(_T("D%d"), i+1);
            m_pComboBox->AddString(csTmp);
            m_pComboBox->SetItemData(nIndex, i + MAX_ANALOG_CHANNUM + nStartNum);
            nIndex++;
        }
    }

	m_pComboBox->AddString(_T("X"));
	m_pComboBox->SetCurSel(-1);
}

int CSubDlgWndSequence::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	m_pComboBox = new CComboBox;

	return 0;
}

void CSubDlgWndSequence::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here

	delete m_pComboBox;
}


