// UsePassword.cpp : implementation file
//

#include "stdafx.h"
#include "SpeakerID.h"
#include "UserPasswordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserPasswordDlg dialog


CUserPasswordDlg::CUserPasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserPasswordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserPasswordDlg)
	m_sMsg = _T("");
	//}}AFX_DATA_INIT
	m_sStep="Step 1 - Record Password";
	m_bIsLast=FALSE;
	m_bIsRem=FALSE;
	m_iMinPassLength=1;
	CBitmap Bitmap;
	Bitmap.LoadBitmap(IDB_BK);
	m_bBk.CreatePatternBrush(&Bitmap);
}


void CUserPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserPasswordDlg)
	DDX_Control(pDX, IDOK, m_btnCancel);
	DDX_Control(pDX, IDCANCEL, m_btnOK);
	DDX_Control(pDX, IDC_RECORD, m_btnRecord);
	DDX_Control(pDX, IDC_RECDEV, m_btnRecDev);
	DDX_Control(pDX, IDC_PLAY, m_btnPlay);
	DDX_Control(pDX, IDC_OSIL, m_ctlOsil);
	DDX_Control(pDX, IDC_SMSGICON, m_ctlMsgIcon);
	DDX_Control(pDX, IDC_STEP, m_ctlStep);
	DDX_Text(pDX, IDC_SMSG, m_sMsg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserPasswordDlg, CDialog)
	//{{AFX_MSG_MAP(CUserPasswordDlg)
	ON_BN_CLICKED(IDC_RECORD, OnRecord)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RECDEV, OnRecDev)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserPasswordDlg message handlers

void CUserPasswordDlg::OnRecord() 
{
	CString str;
	GetDlgItem(IDC_RECORD)->GetWindowText(str);
	if(str=="Rec&ord")
	{
		m_ctlMsgIcon.SetIcon(::LoadIcon(NULL, IDI_INFORMATION));
		if(!m_bIsRem)
			m_sMsg.LoadString(IDS_MSGRECORD);
		UpdateData(FALSE);
		if(!m_SoundIn.Start()) return;
		m_iTimeRecorded=0;
		SetTimer(IDT_RECORDERTIMER,1000,NULL);
		GetDlgItem(IDC_RECORD)->SetWindowText("St&op");
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	}
	else
	{
		m_SoundIn.Stop();
		GetDlgItem(IDCANCEL)->EnableWindow();
		GetDlgItem(IDC_RECORD)->SetWindowText("Rec&ord");
		if(m_iTimeRecorded<m_iMinPassLength)
		{
			m_ctlMsgIcon.SetIcon(::LoadIcon(NULL, IDI_ERROR));
			m_sMsg.LoadString(IDS_MSGTOOSHORT);
			UpdateData(FALSE);
		}
		else
		{
			GetDlgItem(IDOK)->EnableWindow();
			GetDlgItem(IDC_PLAY)->EnableWindow();
			GetDlgItem(IDOK)->EnableWindow();
		}
	}
}

void CUserPasswordDlg::OnPlay() 
{
	CString str;
	GetDlgItem(IDC_PLAY)->GetWindowText(str);
	if(str=="&Play")
	{
		m_iIndex=0;
		int iSize;
		short* p=m_SoundIn.GetSamples(iSize);
		if(!m_SoundOut.Start(iSize,p,NULL)) return;
		SetTimer(IDT_PLAYERTIMER,1000,NULL);
		GetDlgItem(IDC_PLAY)->SetWindowText("Sto&p");
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	}
	else
	{
		KillTimer(IDT_PLAYERTIMER);
		m_SoundOut.Stop();
		GetDlgItem(IDC_PLAY)->SetWindowText("&Play");
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
	}	
}

void CUserPasswordDlg::SetStep(int iStep,int iLast)
{
	if(iStep==-1)
	{
		m_sStep.Format("");
		m_bIsRem=TRUE;
	}
	else
	if(iStep==2)
		m_sStep.Format("Step %d - Record Password",iStep);
	else
		m_sStep.Format("Step %d - Password Confirmation",iStep);
	m_bIsLast=(iStep==iLast);
}

BOOL CUserPasswordDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_ctlMsgIcon.SetIcon(::LoadIcon(NULL, IDI_INFORMATION));	
	if(m_bIsRem)
		m_sMsg.LoadString(IDS_MSGPICK);
	else
		m_sMsg.LoadString(IDS_MSGRECORD);
	UpdateData(FALSE);
	m_ctlStep.SetWindowText(m_sStep);	
	if(m_bIsRem)
	{
		SetWindowText("Remove One Of Your Passphrases");
		m_btnCancel.SetWindowText("Do&ne");
	}
	if(m_bIsLast)
		GetDlgItem(IDOK)->SetWindowText("Fi&nish");
	m_SoundIn.SetOwner(GetDlgItem(IDC_OSIL));
	m_SoundOut.SetOwner(GetDlgItem(IDC_OSIL));
	return TRUE;                
}

void CUserPasswordDlg::OnOK() 
{
	if(m_SoundOut.IsPlaying())
		m_SoundOut.Stop();
	if(m_pSpeaker)
	{
		int nSamples;
		short* pSamples=m_SoundIn.GetSamples(nSamples);
		double d=m_pSpeaker->Verify(nSamples, pSamples);
		//CString str;
		//str.Format("%f",d);
		//MessageBox(str);
		if(d>0.7)
		{
			m_SoundIn.ClearOwner();
			m_sMsg.LoadString(IDS_MSGNOMATCH);
			m_ctlMsgIcon.SetIcon(::LoadIcon(NULL,IDI_ERROR));
			GetDlgItem(IDC_RECORD)->SetWindowText("Rec&ord");
			GetDlgItem(IDC_PLAY)->EnableWindow(FALSE);
			GetDlgItem(IDOK)->EnableWindow(FALSE);
			UpdateData(FALSE);
			return;
		}
	}
	CDialog::OnOK();
}

SV_Data* CUserPasswordDlg::GetPattern()
{
	SV_Feature_MFCC Feature ;
	Feature.Para.MFCC_Order = 12;	     	// number of MFCC
	Feature.Para.NFilter    = 24;			// number of filters in Filter bank 
	Feature.Para.FFTSz      = 256;  	   // FFT length 
	Feature.Para.DEnergy    = 1;	 		// 1: output delta value for first MFCC (energy)
	Feature.Para.WinSz = 256;
    Feature.Para.StpSz = 128;
    Feature.Para.Alpha = 0.97;			 // preemphesis, default=0.97
    Feature.Para.HammingWin = 1;	     // 1: Hamming window, 0: rect window (no window)
    Feature.Para.RmvSilence = 1;//0;	 // 1: remove silence part, 0: intact

    int nSamples;
	short* pSamples=m_SoundIn.GetSamples(nSamples);

	Feature.CopySignal(pSamples, nSamples);
	return Feature.ExtractFeature();
}

void CUserPasswordDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==IDT_PLAYERTIMER)
	{
		if(!m_SoundOut.IsPlaying())
			OnPlay();
	}
	if(nIDEvent==IDT_RECORDERTIMER)
	{
		m_iTimeRecorded++;
	}
	CDialog::OnTimer(nIDEvent);
}

void CUserPasswordDlg::SetSpeaker(HSpeaker *pSpeaker)
{
	m_pSpeaker=pSpeaker;
}

HSpeaker* CUserPasswordDlg::GetSpeaker()
{
	int nSamples;
	short* pSamples=m_SoundIn.GetSamples(nSamples);
	HSpeaker* pSpeaker=new HSpeaker;
	pSpeaker->SetPassphrase(nSamples, pSamples);
	return pSpeaker;
}

void CUserPasswordDlg::OnCancel() 
{
	if(m_SoundIn.IsRecording())
		m_SoundIn.Stop();
	if(m_SoundOut.IsPlaying())
		m_SoundOut.Stop();
	CDialog::OnCancel();
}

void CUserPasswordDlg::OnRecDev() 
{
	WinExec("sndvol32.exe -recording", SW_NORMAL);
}
