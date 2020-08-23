// SpeakerIDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpeakerID.h"
#include "SpeakerIDDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpeakerIDDlg dialog

CSpeakerIDDlg::CSpeakerIDDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpeakerIDDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpeakerIDDlg)
	//}}AFX_DATA_INIT
}

void CSpeakerIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpeakerIDDlg)
	DDX_Control(pDX, IDC_RECDEV, m_btnRecDev);
	DDX_Control(pDX, IDC_OSIL, m_ctlColorFrame);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOK);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSpeakerIDDlg, CDialog)
	//{{AFX_MSG_MAP(CSpeakerIDDlg)
	ON_BN_CLICKED(IDC_RECDEV, OnRecDev)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpeakerIDDlg message handlers

BOOL CSpeakerIDDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CBitmap bmpBk;
	bmpBk.LoadBitmap(IDB_BACK);
	m_bBk.CreatePatternBrush(&bmpBk);
	m_SoundIn.SetOwner(GetDlgItem(IDC_OSIL));
	m_SpeakersDB.LoadUsers();
	return TRUE; 
}

void CSpeakerIDDlg::OnOK() 
{
	CString str;
	m_btnOK.GetWindowText(str);
	if(str=="Stop and Identify")
	{
		int index;
		int nSamples;

		m_SoundIn.Stop();
		short* pSamples=m_SoundIn.GetSamples(nSamples);
		HSpeaker Speaker;
		Speaker.SetPassphrase(nSamples, pSamples);
		if((index = m_SpeakersDB.Identify(&Speaker))!=-1)
		{
			MessageBox("You have been identified as "+m_SpeakersDB.GetUserName(index), "Result");
			CDialog::OnOK();
		}
		else
		{
			MessageBox("You haven't been identified.", "Result");
			m_btnOK.SetWindowText("Say Your Passphrase");
			UpdateData(FALSE);
		}
	}
	else
	{
		m_btnOK.SetWindowText("Stop and Identify");
		UpdateData(FALSE);
		if(!m_SoundIn.Start())
		{
			m_btnOK.SetWindowText("Say Your Passphrase");
			UpdateData(FALSE);
			return;
		}
	}
}

void CSpeakerIDDlg::OnRecDev() 
{
	WinExec("sndvol32.exe -recording" , SW_NORMAL);	
}
