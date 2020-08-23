#if !defined(AFX_USERNAMEDLG_H__D0D52E25_98DB_11D6_8DAE_C3AFC75A4E2A__INCLUDED_)
#define AFX_USERNAMEDLG_H__D0D52E25_98DB_11D6_8DAE_C3AFC75A4E2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "..\GuiLib\ComboBoxCtl.h"
#include "..\GuiLib\xShadeButton.h"

// UserNameDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserNameDlg dialog

class CUserNameDlg : public CDialog
{
// Construction
public:
	CStringArray m_saNames;
	void AddName(CString str);
	CString GetUserName();
	CUserNameDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserNameDlg)
	enum { IDD = IDD_USERINFO };
	CComboBox	m_ctlNames;
	CxShadeButton	m_btnOK;
	CxShadeButton	m_btnCancel;
	CStatic	m_ctlMsgIcon;
	CString	m_sMsg;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserNameDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBrush m_bBk;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERNAMEDLG_H__D0D52E25_98DB_11D6_8DAE_C3AFC75A4E2A__INCLUDED_)
