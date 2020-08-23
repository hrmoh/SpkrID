#if !defined(AFX_COLORFRAME_H__88F4A397_6F72_475C_8B73_7A05E8E5444B__INCLUDED_)
#define AFX_COLORFRAME_H__88F4A397_6F72_475C_8B73_7A05E8E5444B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorFrame window

class CColorFrame : public CStatic
{
// Construction
public:
	CColorFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetBkColor(COLORREF crBkColor);
	virtual ~CColorFrame();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorFrame)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	COLORREF m_crBkColor;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORFRAME_H__88F4A397_6F72_475C_8B73_7A05E8E5444B__INCLUDED_)
