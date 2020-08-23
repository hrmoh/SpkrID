#include "StdAfx.h"
#include "SoundRunner.h"

IMPLEMENT_DYNCREATE(HSoundRunner, CWinThread)

HSoundRunner::HSoundRunner()
{
	m_iBufferSize= 2048;
	m_nBuffers = 0;
	m_bRunning = FALSE;
	m_nSamples=0;
	m_pSamples=NULL;

	m_pOwner=NULL;

	CreateThread();
}

HSoundRunner::~HSoundRunner()
{
	if(m_bRunning)
		Stop();
}

void HSoundRunner::SetBufferSize(int nSamples)
{
	m_iBufferSize=nSamples;
}

int HSoundRunner::GetBufferSize()
{
	return m_iBufferSize;
}

BOOL HSoundRunner::InitInstance()
{
	m_dwThreadID = ::GetCurrentThreadId();
	return TRUE;
}

void HSoundRunner::AddBuffer()
{
	m_nBuffers++;
}

BOOL HSoundRunner::Start(WAVEFORMATEX* pwfex)
{
	if(m_bRunning)
		return FALSE;
	if(pwfex != NULL)		
		m_wfData = *pwfex;
	return TRUE;
}

BOOL HSoundRunner::Stop()
{
	if(m_bRunning)
	{
		m_bRunning=FALSE;
		Sleep(500);
		return TRUE;
	}
	return FALSE;
}

void HSoundRunner::SetOwner(CWnd* pOwner)
{
	m_pOwner=pOwner;
}

void HSoundRunner::DrawBuffer(int nSamples, short* pSamples, COLORREF crBkColor, COLORREF crLineColor)
{
	if(m_pOwner==NULL)
		return;

	CRect rc;
	m_pOwner->GetClientRect(&rc);
	int iWidth=rc.Width();
	int iHeight=rc.Height();

	CDC* pDC=m_pOwner->GetDC();

	CBitmap Bitmap;
	Bitmap.CreateCompatibleBitmap(pDC, iWidth, iHeight);

	CDC dc;
	dc.CreateCompatibleDC(pDC);

	dc.SelectObject(&Bitmap);
	CBrush Brush(crBkColor);
	dc.FillRect(&rc,&Brush);
	CPen Pen(PS_SOLID,1,crLineColor);
	dc.SelectObject(&Pen);
	dc.SetBkColor(crBkColor);
	if(GetBitsPerSample()==16)
	{
		float fx=iWidth/float(nSamples);
		float fy=float(iHeight/32767.0);
		dc.MoveTo(0, iHeight/2);
		int i=0;
		for(float f=0; f<iWidth&&i<nSamples; f+=fx, i++)
			dc.LineTo(int(f), int(iHeight/2+fy*pSamples[i]));
		pDC->BitBlt(0, 0, iWidth, iHeight, &dc, 0, 0, SRCCOPY);
	}
}

void HSoundRunner::ClearOwner(COLORREF crBkColor)
{
	DrawBuffer(0,NULL,crBkColor);
}

