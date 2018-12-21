// DlgPtzCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPtzCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPtzCtrl dialog


CDlgPtzCtrl::CDlgPtzCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPtzCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPtzCtrl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgPtzCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPtzCtrl)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPtzCtrl, CDialog)
	//{{AFX_MSG_MAP(CDlgPtzCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPtzCtrl message handlers

BOOL CDlgPtzCtrl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_btnPtzUp.SubclassDlgItem(IDC_BTN_PTZ_UP,this);
    m_btnPtzDown.SubclassDlgItem(IDC_BTN_PTZ_DOWN,this);
    m_btnPtzLeft.SubclassDlgItem(IDC_BTN_PTZ_LEFT,this);
    m_btnPtzRight.SubclassDlgItem(IDC_BTN_PTZ_RIGHT,this);	
    m_btnZoomOut.SubclassDlgItem(IDC_BTN_ZOOM_OUT,this);
    m_btnZoomIn.SubclassDlgItem(IDC_BTN_ZOOM_IN,this);
    m_btnFocusNear.SubclassDlgItem(IDC_BTN_FOCUS_NEAR,this);
    m_btnFocusFar.SubclassDlgItem(IDC_BTN_FOCUS_FAR,this);
    m_btnIrisOpen.SubclassDlgItem(IDC_BTN_IRIS_OPEN,this);
    m_btnIrisClose.SubclassDlgItem(IDC_BTN_IRIS_CLOSE,this);
	
	m_btnPtzUpZoomIn.SubclassDlgItem(IDC_BTN_PTZ_UP_ZOOM_IN,this);
	m_btnPtzUpZoomOut.SubclassDlgItem(IDC_BTN_PTZ_UP_ZOOM_OUT,this);
	m_btnPtzDownZoomIn.SubclassDlgItem(IDC_BTN_PTZ_DOWN_ZOOM_IN,this);
	m_btnPtzDownZoomOut.SubclassDlgItem(IDC_BTN_PTZ_DOWN_ZOOM_OUT,this);
	
	m_btnPtzLeftZoomIn.SubclassDlgItem(IDC_BTN_PTZ_LEFT_ZOOM_IN,this);
	m_btnPtzLeftZoomOut.SubclassDlgItem(IDC_BTN_PTZ_LEFT_ZOOM_OUT,this);
	m_btnPtzRightZoomIn.SubclassDlgItem(IDC_BTN_PTZ_RIGHT_ZOOM_IN,this);
	m_btnPtzRightZoomOut.SubclassDlgItem(IDC_BTN_PTZ_RIGHT_ZOOM_OUT,this);
	
	m_btnPtzUpLeftZoomIn.SubclassDlgItem(IDC_BTN_PTZ_UP_LEFT_ZOOM_IN,this);
	m_btnPtzUpLeftZoomOut.SubclassDlgItem(IDC_BTN_PTZ_UP_LEFT_ZOOM_OUT,this);
	m_btnPtzUpRightZoomIn.SubclassDlgItem(IDC_BTN_PTZ_UP_RIGHT_ZOOM_IN,this);
	m_btnPtzUpRightZoomOut.SubclassDlgItem(IDC_BTN_PTZ_UP_RIGHT_ZOOM_OUT,this);
	
	m_btnPtzDownLeftZoomIn.SubclassDlgItem(IDC_BTN_PTZ_DOWN_LEFT_ZOOM_IN,this);
	m_btnPtzDownLeftZoomOut.SubclassDlgItem(IDC_BTN_PTZ_DOWN_LEFT_ZOOM_OUT,this);
	m_btnPtzDownRightZoomIn.SubclassDlgItem(IDC_BTN_PTZ_DOWN_RIGHT_ZOOM_IN,this);
	m_btnPtzDownRightZoomOut.SubclassDlgItem(IDC_BTN_PTZ_DOWN_RIGHT_ZOOM_OUT,this);


    m_btnPtzUp.m_iPTZType = TILT_UP;
    m_btnPtzDown.m_iPTZType = TILT_DOWN;
    m_btnPtzLeft.m_iPTZType = PAN_LEFT;
    m_btnPtzRight.m_iPTZType = PAN_RIGHT;
    m_btnZoomOut.m_iPTZType = ZOOM_OUT;
    m_btnZoomIn.m_iPTZType = ZOOM_IN;
    m_btnFocusNear.m_iPTZType = FOCUS_NEAR;
    m_btnFocusFar.m_iPTZType = FOCUS_FAR;
    m_btnIrisOpen.m_iPTZType = IRIS_OPEN;
    m_btnIrisClose.m_iPTZType = IRIS_CLOSE;

	m_btnPtzUpZoomIn.m_iPTZType = TILT_UP_ZOOM_IN;
	m_btnPtzUpZoomOut.m_iPTZType = TILT_UP_ZOOM_OUT;
	m_btnPtzDownZoomIn.m_iPTZType = TILT_DOWN_ZOOM_IN;
	m_btnPtzDownZoomOut.m_iPTZType = TILT_DOWN_ZOOM_OUT;
	
	m_btnPtzLeftZoomIn.m_iPTZType = PAN_LEFT_ZOOM_IN;
	m_btnPtzLeftZoomOut.m_iPTZType = PAN_LEFT_ZOOM_OUT;
	m_btnPtzRightZoomIn.m_iPTZType = PAN_RIGHT_ZOOM_IN;
	m_btnPtzRightZoomOut.m_iPTZType = PAN_RIGHT_ZOOM_OUT;
	
	m_btnPtzUpLeftZoomIn.m_iPTZType = UP_LEFT_ZOOM_IN;
	m_btnPtzUpLeftZoomOut.m_iPTZType = UP_LEFT_ZOOM_OUT;
	m_btnPtzUpRightZoomIn.m_iPTZType = UP_RIGHT_ZOOM_IN;
	m_btnPtzUpRightZoomOut.m_iPTZType = UP_RIGHT_ZOOM_OUT;
	
	m_btnPtzDownLeftZoomIn.m_iPTZType = DOWN_LEFT_ZOOM_IN;
	m_btnPtzDownLeftZoomOut.m_iPTZType = DOWN_LEFT_ZOOM_OUT;
	m_btnPtzDownRightZoomIn.m_iPTZType = DOWN_RIGHT_ZOOM_IN;
	m_btnPtzDownRightZoomOut.m_iPTZType = DOWN_RIGHT_ZOOM_OUT;


    m_btnPtzUp.m_lPlayHandle = m_lPlayHandle;
    m_btnPtzDown.m_lPlayHandle = m_lPlayHandle;
    m_btnPtzLeft.m_lPlayHandle = m_lPlayHandle;
    m_btnPtzRight.m_lPlayHandle = m_lPlayHandle;
    m_btnZoomOut.m_lPlayHandle = m_lPlayHandle;
    m_btnZoomIn.m_lPlayHandle = m_lPlayHandle;	
    m_btnFocusNear.m_lPlayHandle = m_lPlayHandle;
    m_btnFocusFar.m_lPlayHandle = m_lPlayHandle;
    m_btnIrisOpen.m_lPlayHandle = m_lPlayHandle;
    m_btnIrisClose.m_lPlayHandle = m_lPlayHandle;


	m_btnPtzUpZoomIn.m_lPlayHandle = m_lPlayHandle;
	m_btnPtzUpZoomOut.m_lPlayHandle = m_lPlayHandle;
	m_btnPtzDownZoomIn.m_lPlayHandle = m_lPlayHandle;
	m_btnPtzDownZoomOut.m_lPlayHandle = m_lPlayHandle;
	
	m_btnPtzLeftZoomIn.m_lPlayHandle = m_lPlayHandle;
	m_btnPtzLeftZoomOut.m_lPlayHandle = m_lPlayHandle;
	m_btnPtzRightZoomIn.m_lPlayHandle = m_lPlayHandle;
	m_btnPtzRightZoomOut.m_lPlayHandle = m_lPlayHandle;
	
	m_btnPtzUpLeftZoomIn.m_lPlayHandle = m_lPlayHandle;
	m_btnPtzUpLeftZoomOut.m_lPlayHandle = m_lPlayHandle;
	m_btnPtzUpRightZoomIn.m_lPlayHandle = m_lPlayHandle;
	m_btnPtzUpRightZoomOut.m_lPlayHandle = m_lPlayHandle;
	
	m_btnPtzDownLeftZoomIn.m_lPlayHandle = m_lPlayHandle;
	m_btnPtzDownLeftZoomOut.m_lPlayHandle = m_lPlayHandle;
	m_btnPtzDownRightZoomIn.m_lPlayHandle = m_lPlayHandle;
	m_btnPtzDownRightZoomOut.m_lPlayHandle = m_lPlayHandle;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
