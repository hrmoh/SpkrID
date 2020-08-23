#if !defined(AFX_ABOUTDLG_H__66EC836A_6492_44BF_916A_A644FACD63B7__INCLUDED_)
#define AFX_ABOUTDLG_H__66EC836A_6492_44BF_916A_A644FACD63B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AboutDlg.h : header file
//

#include "..\GuiLib\HyperLink.h"
#include "..\GuiLib\xShadeButton.h"

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog

class CAboutDlg : public CDialog
{
// Construction
public:
	CAboutDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUT };
	CHyperLink	m_sJM;
	CHyperLink	m_sCT;
	CHyperLink	m_sFD;
	CHyperLink	m_sSB;
	CxShadeButton	m_btnClose;
	CHyperLink	m_sTH;
	CHyperLink	m_sFC;
	CHyperLink	m_sDP;
	CHyperLink	m_sCM;
	CHyperLink	m_sJHe;
	CHyperLink	m_sDr;
	CHyperLink	m_sMe;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAboutDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTDLG_H__66EC836A_6492_44BF_916A_A644FACD63B7__INCLUDED_)
