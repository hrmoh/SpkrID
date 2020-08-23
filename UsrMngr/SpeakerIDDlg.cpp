// SpeakerIDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpeakerID.h"
#include "SpeakerIDDlg.h"

#include "UserNameDlg.h"
#include "UserPasswordDlg.h"
#include "OptionsDlg.h"
#include "AboutDlg.h"

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
	m_nRepeatsNum=2;
	m_nUsers=0;
	CBitmap Bitmap;
	Bitmap.LoadBitmap(IDB_BK);
	m_bBk.CreatePatternBrush(&Bitmap);
}

void CSpeakerIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpeakerIDDlg)
	DDX_Control(pDX, IDC_ABOUT, m_btnAbout);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_REMOVEUSER, m_btnRemove);
	DDX_Control(pDX, IDC_OPTIONS, m_btnOptions);
	DDX_Control(pDX, IDC_MODIFYUSER, m_btnModify);
	DDX_Control(pDX, IDC_NEWUSER, m_btnNew);
	DDX_Control(pDX, IDC_USERSLIST, m_ctlList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSpeakerIDDlg, CDialog)
	//{{AFX_MSG_MAP(CSpeakerIDDlg)
	ON_BN_CLICKED(IDC_NEWUSER, OnNewUser)
	ON_BN_CLICKED(IDC_OPTIONS, OnOptions)
	ON_NOTIFY(NM_CLICK, IDC_USERSLIST, OnClickUserslist)
	ON_BN_CLICKED(IDC_REMOVEUSER, OnRemoveUser)
	ON_BN_CLICKED(IDC_MODIFYUSER, OnRemovePassphrase)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpeakerIDDlg message handlers

BOOL CSpeakerIDDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CRect rect;
    m_ctlList.GetClientRect(&rect);
	m_ctlList.InsertColumn(0,"Name", LVCFMT_LEFT,rect.Width()/2);
	m_ctlList.InsertColumn(1,"Passphrases", LVCFMT_LEFT,rect.Width()/2);

	LoadUsers();
	return TRUE;  
}

void CSpeakerIDDlg::OnNewUser() 
{
	CString strName;
	{
	CUserNameDlg UserNameDlg;
	int iNum=m_SpeakersDB.GetUsersNum();
	for(int iUser=0; iUser<iNum; iUser++)
		UserNameDlg.AddName(m_SpeakersDB.GetUserName(iUser));
	if(UserNameDlg.DoModal()==IDCANCEL)
		return;
	strName=UserNameDlg.GetUserName();
	}
	HSpeaker* pSpeaker=NULL;
	int i=0;
	while(i<m_nRepeatsNum)
	{
		CUserPasswordDlg UserPasswordDlg;
		UserPasswordDlg.SetSpeaker(pSpeaker);
		UserPasswordDlg.SetStep(i+2,m_nRepeatsNum+1);
		if(UserPasswordDlg.DoModal()==IDCANCEL)
			break;
		if(i==0)
			pSpeaker=UserPasswordDlg.GetSpeaker();
		i++;
	}
	if(i==m_nRepeatsNum)//not breaked, normal progress
	{
		pSpeaker->SetUserName(strName);
		m_SpeakersDB.AddUser(pSpeaker);
		UpdateList();
	}
}

void CSpeakerIDDlg::LoadUsers()
{
	m_SpeakersDB.LoadUsers();
	m_nSecurityLevel=m_SpeakersDB.GetSecurityLevel();
	m_fMinPassLength=m_SpeakersDB.GetMinPassLen();
	m_nRepeatsNum=m_SpeakersDB.GetRepsNum();
	UpdateList();
}

void CSpeakerIDDlg::OnOK() 
{
	m_SpeakersDB.StoreUsers();	
	CDialog::OnOK();
}

void CSpeakerIDDlg::UpdateList()
{
	m_btnRemove.EnableWindow(FALSE);
	m_btnModify.EnableWindow(FALSE);
	m_ctlList.DeleteAllItems();
	int nUsers=m_SpeakersDB.GetUsersNum();
	for(int i=0; i<nUsers; i++)
	{
		CString sName=m_SpeakersDB.GetUserName(i);
		m_ctlList.InsertItem(i, sName);
	}
	for(i=0; i<nUsers; i++)
	{
		CString sPassesNum;
		sPassesNum.Format("%d",m_SpeakersDB.GetPassesNum(i));
		m_ctlList.SetItemText(i,1,sPassesNum);
	}
}	

void CSpeakerIDDlg::OnOptions() 
{
	COptionsDlg OptionsDlg;
	OptionsDlg.SetRepNum(m_nRepeatsNum);
	OptionsDlg.SetSecLev(m_nSecurityLevel);
	OptionsDlg.SetMinLen(float(m_fMinPassLength));
	if(OptionsDlg.DoModal()==IDOK)
	{
		m_nRepeatsNum=OptionsDlg.GetRepNum();
		m_fMinPassLength=OptionsDlg.GetMinPassLength();
		m_nSecurityLevel=OptionsDlg.GetSeclev();
		m_SpeakersDB.SetRepsNum(m_nRepeatsNum);
		m_SpeakersDB.SetMinPassLen((float)m_fMinPassLength);
		m_SpeakersDB.SetSecurityLevel(m_nSecurityLevel);
	}
}

void CSpeakerIDDlg::OnClickUserslist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_ctlList.GetSelectionMark()!=-1)
	{
		m_btnRemove.EnableWindow();
		if(m_SpeakersDB.GetPassesNum(m_ctlList.GetSelectionMark())>1)
			m_btnModify.EnableWindow();
		else
			m_btnModify.EnableWindow(FALSE);
	}
	else
	{
		m_btnRemove.EnableWindow(FALSE);
		m_btnModify.EnableWindow(FALSE);
	}
	*pResult = 0;
}

void CSpeakerIDDlg::OnRemoveUser() 
{
	m_SpeakersDB.RemoveUser(m_ctlList.GetSelectionMark());	
	UpdateList();
}

void CSpeakerIDDlg::OnRemovePassphrase() 
{
	BOOL bDone=FALSE;
	while(!bDone)
	{
		HSpeaker *pSpeaker=NULL;
		CUserPasswordDlg UserPasswordDlg;
		UserPasswordDlg.SetSpeaker(pSpeaker);
		UserPasswordDlg.SetStep(-1,0);
		if(UserPasswordDlg.DoModal()==IDCANCEL)
			return;
		pSpeaker=UserPasswordDlg.GetSpeaker();
		if(m_SpeakersDB.RemPass(m_ctlList.GetSelectionMark(), pSpeaker))
			bDone=TRUE;
		else
			MessageBox("Passphrase Not Found!","Please Reenter",MB_OK|MB_ICONERROR);
		delete pSpeaker;
	}
	UpdateList();
}

void CSpeakerIDDlg::OnAbout() 
{
	CAboutDlg AboutDlg;
	AboutDlg.DoModal();
}
