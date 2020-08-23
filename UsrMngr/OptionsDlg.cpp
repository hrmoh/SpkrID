// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpeakerID.h"
#include "OptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog


COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsDlg)
	m_nRepNum = 2;
	m_dMinLen = 2.0f;
	m_iSecurityLevelChoice = 0;
	//}}AFX_DATA_INIT
	CBitmap Bitmap;
	Bitmap.LoadBitmap(IDB_BK);
	m_bBk.CreatePatternBrush(&Bitmap);
}


void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDlg)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Text(pDX, IDC_REPNUM, m_nRepNum);
	DDV_MinMaxInt(pDX, m_nRepNum, 2, 6);
	DDX_Text(pDX, IDC_MINLEN, m_dMinLen);
	DDV_MinMaxFloat(pDX, m_dMinLen, 2.f, 20.f);
	DDX_CBIndex(pDX, IDC_SECURITY, m_iSecurityLevelChoice);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
	//{{AFX_MSG_MAP(COptionsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg message handlers

void COptionsDlg::SetRepNum(int nRepNum)
{
	m_nRepNum=nRepNum;
}

int COptionsDlg::GetRepNum()
{
	return m_nRepNum;
}

void COptionsDlg::SetMinLen(float fMinLen)
{
	m_dMinLen=fMinLen;
}

void COptionsDlg::SetSecLev(int nLevel)
{
	m_iSecurityLevelChoice=nLevel;
}

double COptionsDlg::GetMinPassLength()
{
	return (double)m_dMinLen;
}

int COptionsDlg::GetSeclev()
{
	return m_iSecurityLevelChoice;		
}
