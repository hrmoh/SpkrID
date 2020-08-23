// UserNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpeakerID.h"
#include "UserNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserNameDlg dialog


CUserNameDlg::CUserNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserNameDlg)
	m_sMsg = _T("");
	m_strName = _T("");
	//}}AFX_DATA_INIT
	CBitmap Bitmap;
	Bitmap.LoadBitmap(IDB_BK);
	m_bBk.CreatePatternBrush(&Bitmap);
}


void CUserNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserNameDlg)
	DDX_Control(pDX, IDC_NAME, m_ctlNames);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_MSGICON, m_ctlMsgIcon);
	DDX_Text(pDX, IDC_SMSG, m_sMsg);
	DDX_Text(pDX, IDC_NAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserNameDlg, CDialog)
	//{{AFX_MSG_MAP(CUserNameDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserNameDlg message handlers

CString CUserNameDlg::GetUserName()
{
	return m_strName;
}

void CUserNameDlg::OnOK() 
{
	UpdateData();
	m_strName.Remove(' ');	
	if(m_strName.GetLength()==0)
	{
		m_sMsg.LoadString(IDS_MSGINVALIDNAME);
		m_ctlMsgIcon.SetIcon(::LoadIcon(NULL, MAKEINTRESOURCE(IDI_ERROR)));
		UpdateData(FALSE);
		return;
	}
	CDialog::OnOK();
}

BOOL CUserNameDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_ctlMsgIcon.SetIcon(::LoadIcon(NULL, MAKEINTRESOURCE(IDI_INFORMATION)));
	m_sMsg.LoadString(IDS_MSGNAME);
	for(int i=0; i<m_saNames.GetSize(); i++)
		m_ctlNames.AddString(m_saNames[i]);
	UpdateData(FALSE);
	return TRUE;  
}

void CUserNameDlg::AddName(CString str)
{
	m_saNames.Add(str);
}
