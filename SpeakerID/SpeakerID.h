// SpeakerID.h : main header file for the SPEAKERID application
//

#if !defined(AFX_SPEAKERID_H__46F16C09_99DF_4CE1_BFDF_D122A7A5B5B2__INCLUDED_)
#define AFX_SPEAKERID_H__46F16C09_99DF_4CE1_BFDF_D122A7A5B5B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSpeakerIDApp:
// See SpeakerID.cpp for the implementation of this class
//

class CSpeakerIDApp : public CWinApp
{
public:
	CSpeakerIDApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpeakerIDApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSpeakerIDApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPEAKERID_H__46F16C09_99DF_4CE1_BFDF_D122A7A5B5B2__INCLUDED_)
