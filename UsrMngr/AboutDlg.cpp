// AboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpeakerID.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog


CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
	m_sMe.SetURL("http://www.mohammadi.netfirms.com");
	m_sDr.SetURL("http://eng.ui.ac.ir/nilchi/");
	m_sJHe.SetURL("http://tiger.la.asu.edu/jialong.htm");	
	m_sTH.SetURL("mailto:thomas.holme@openmpeg4.org");
	m_sFC.SetURL("mailto:fco_campos@tutopia.com");
	m_sDP.SetURL("mailto:ing.davide.pizzolato@libero.it");
	m_sCM.SetURL("mailto:chrismaunder@codeguru.com");
	m_sSB.SetURL("mailto:sam_blackburn@pobox.com");
	m_sFD.SetURL("mailto:f.deravi@ukc.ac.uk");
	m_sJM.SetURL("mailto:jmarkowitz@21stcentury.net");
	m_sCT.SetURL("mailto:ctilton@saflink.com");
}


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_JM, m_sJM);
	DDX_Control(pDX, IDC_CT, m_sCT);
	DDX_Control(pDX, IDC_FD, m_sFD);
	DDX_Control(pDX, IDC_SB, m_sSB);
	DDX_Control(pDX, IDOK, m_btnClose);
	DDX_Control(pDX, IDC_TH, m_sTH);
	DDX_Control(pDX, IDC_FC, m_sFC);
	DDX_Control(pDX, IDC_DP, m_sDP);
	DDX_Control(pDX, IDC_CM, m_sCM);
	DDX_Control(pDX, IDC_JHE, m_sJHe);
	DDX_Control(pDX, IDC_DR, m_sDr);
	DDX_Control(pDX, IDC_ME, m_sMe);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers
