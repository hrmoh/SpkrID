// SpeakerIDDlg.h : header file
//

#if !defined(AFX_SPEAKERIDDLG_H__2493FB06_98C7_11D6_8DAE_9311D378E42B__INCLUDED_)
#define AFX_SPEAKERIDDLG_H__2493FB06_98C7_11D6_8DAE_9311D378E42B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\HSpeakerIDLib\SpeakersDB.h"
#include "..\GuiLib\xShadeButton.h"
//#include "..\GuiLib\GuiHeaderCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CSpeakerIDDlg dialog
class CSpeakerIDDlg : public CDialog
{
// Construction
public:
	void UpdateList();
	void LoadUsers();
	CSpeakerIDDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSpeakerIDDlg)
	enum { IDD = IDD_SPEAKERID_DIALOG };
	CxShadeButton	m_btnAbout;
	CxShadeButton	m_btnOK;
	CxShadeButton	m_btnCancel;
	CxShadeButton	m_btnRemove;
	CxShadeButton	m_btnOptions;
	CxShadeButton	m_btnModify;
	CxShadeButton	m_btnNew;
	CListCtrl		m_ctlList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpeakerIDDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSpeakerIDDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnNewUser();
	virtual void OnOK();
	afx_msg void OnOptions();
	afx_msg void OnClickUserslist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRemoveUser();
	afx_msg void OnRemovePassphrase();
	afx_msg void OnAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	double m_fMinPassLength;
	int m_nSecurityLevel;
	CBrush m_bBk;
	int m_nUsers;
	int m_nRepeatsNum;
	HSpeakersDB m_SpeakersDB;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPEAKERIDDLG_H__2493FB06_98C7_11D6_8DAE_9311D378E42B__INCLUDED_)
