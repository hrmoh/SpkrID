#if !defined(AFX_USEPASSWORD_H__D0D52E26_98DB_11D6_8DAE_C3AFC75A4E2A__INCLUDED_)
#define AFX_USEPASSWORD_H__D0D52E26_98DB_11D6_8DAE_C3AFC75A4E2A__INCLUDED_

#include "..\HSoundLib\SoundRecorder.h"
#include "..\HSoundLib\SoundPlayer.h"
#include "..\HSpeakerIDLib\Speaker.h"

#include "..\GuiLib\ColorFrame.h"

//#include "..\GuiLib\GuiButton.h"
#include "..\GuiLib\xShadeButton.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UsePassword.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserPasswordDlg dialog

class CUserPasswordDlg : public CDialog
{
// Construction
public:
	HSpeaker* GetSpeaker();
	void SetSpeaker(HSpeaker* pSpeaker);
	SV_Data* GetPattern();
	void SetStep(int iStep,int iLast);
	CUserPasswordDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserPasswordDlg)
	enum { IDD = IDD_USERPASS };
	CxShadeButton	m_btnCancel;
	CxShadeButton	m_btnOK;
	CxShadeButton	m_btnRecord;
	CxShadeButton	m_btnRecDev;
	CxShadeButton	m_btnPlay;
	CColorFrame	m_ctlOsil;
	CStatic	m_ctlMsgIcon;
	CButton	m_ctlStep;
	CString	m_sMsg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserPasswordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserPasswordDlg)
	afx_msg void OnRecord();
	afx_msg void OnPlay();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	afx_msg void OnRecDev();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HSpeaker* m_pSpeaker;
	CString m_sStep;
	HSoundRecorder	m_SoundIn;
	HSoundPlayer	m_SoundOut;
	BOOL		m_bIsLast, m_bIsRem;
	CObArray	m_oaBuffers;
	int			m_iIndex;

	int			m_iTimeRecorded;
	int			m_iMinPassLength;

private:
	CBrush m_bBk;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USEPASSWORD_H__D0D52E26_98DB_11D6_8DAE_C3AFC75A4E2A__INCLUDED_)
