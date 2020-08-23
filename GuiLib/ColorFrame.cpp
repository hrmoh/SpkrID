// ColorFrame.cpp : implementation file
//

#include "stdafx.h"
#include "ColorFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorFrame

CColorFrame::CColorFrame()
{
	m_crBkColor=RGB(0,0,0);
}

CColorFrame::~CColorFrame()
{
}


BEGIN_MESSAGE_MAP(CColorFrame, CStatic)
	//{{AFX_MSG_MAP(CColorFrame)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorFrame message handlers

void CColorFrame::SetBkColor(COLORREF crBkColor)
{
	m_crBkColor=crBkColor;
}

void CColorFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	CBrush Brush(m_crBkColor);
	dc.FillRect(&rect, &Brush);
}
