// SpeakerIDDlg.h : header file
//

#if !defined(AFX_SPEAKERIDDLG_H__C5AF617F_859C_48ED_80FA_878AF0EEAD38__INCLUDED_)
#define AFX_SPEAKERIDDLG_H__C5AF617F_859C_48ED_80FA_878AF0EEAD38__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\HSoundLib\SoundRecorder.h"	// Added by ClassView
//#include "..\GuiLib\GuiButton.h"
#include "..\GuiLib\xShadeButton.h"
#include "..\HSpeakerIDLib\SpeakersDB.h"	// Added by ClassView
#include "..\GuiLib\ColorFrame.h"

/////////////////////////////////////////////////////////////////////////////
// CSpeakerIDDlg dialog

class CSpeakerIDDlg : public CDialog
{
// Construction
public:
	CSpeakerIDDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSpeakerIDDlg)
	enum { IDD = IDD_SPEAKERID_DIALOG };
	CxShadeButton	m_btnRecDev;
	CColorFrame	m_ctlColorFrame;
	CxShadeButton m_btnCancel;
	CxShadeButton m_btnOK;
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
	virtual void OnOK();
	afx_msg void OnRecDev();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HSpeakersDB m_SpeakersDB;
	HSoundRecorder m_SoundIn;
	CBrush m_bBk;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPEAKERIDDLG_H__C5AF617F_859C_48ED_80FA_878AF0EEAD38__INCLUDED_)
