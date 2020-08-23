#if !defined(AFX_OPTIONSDLG_H__8B75081F_70A0_4108_BA43_791EAEE419CE__INCLUDED_)
#define AFX_OPTIONSDLG_H__8B75081F_70A0_4108_BA43_791EAEE419CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\GuiLib\xShadeButton.h"

// OptionsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog
class COptionsDlg : public CDialog
{
// Construction
public:
	int GetSeclev();
	double GetMinPassLength();
	void SetSecLev(int nLevel);
	void SetMinLen(float fMinLen);
	int GetRepNum();
	void SetRepNum(int nRepNum);
	COptionsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionsDlg)
	enum { IDD = IDD_OPTIONS };
	CxShadeButton	m_btnOK;
	CxShadeButton	m_btnCancel;
	int		m_nRepNum;
	float	m_dMinLen;
	int		m_iSecurityLevelChoice;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBrush m_bBk;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDLG_H__8B75081F_70A0_4108_BA43_791EAEE419CE__INCLUDED_)
