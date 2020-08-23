// HSoundRecorder.cpp : implementation file
//

#include "stdafx.h"
#include "SoundRecorder.h"

/////////////////////////////////////////////////////////////////////////////
// HSoundRecorder

HShortPocket::HShortPocket(int iSize, short* pBuffer)
{
	m_iSize=iSize;
	m_pBuffer=new short[m_iSize];
	pNext=NULL;
	pPrev=NULL;
	CopyMemory(m_pBuffer, pBuffer, m_iSize*sizeof(short));
}

HShortPocket::~HShortPocket()
{
	delete []m_pBuffer;
}

short* HShortPocket::GetBuffer()
{
	return m_pBuffer;
}

int HShortPocket::GetSize()
{
	return m_iSize;
}

HShortQueue::HShortQueue()
{
	pFront=pRear=NULL;
}

HShortQueue::~HShortQueue()
{
	while(pFront!=NULL)
	{
		pFront=pFront->pNext;
		delete pFront->pPrev;
	}
}

void HShortQueue::InsertItem(int iSize,short* pBuffer)
{
	if(pFront==NULL)
	{
		pFront=new HShortPocket(iSize, pBuffer);
		pRear=pFront;
	}
	else
	{
		pRear->pNext=new HShortPocket(iSize, pBuffer);
		pRear->pNext->pPrev=pRear;
		pRear=pRear->pNext;
	}
}

int HShortQueue::RemoveItem(short* pBuffer)
{
	if(pFront!=NULL)
	{
		int iSize=pFront->GetSize();
		CopyMemory(pBuffer, pFront->GetBuffer(), iSize*sizeof(short));
		pFront=pFront->pNext;
		if(pFront!=NULL)
			delete pFront->pPrev;
		return iSize;
	}
	return -1;
}

BOOL HShortQueue::Empty()
{
	return (pFront==NULL);
}

int HShortQueue::GetSize()
{
	HShortPocket* pTemp=pFront;
	int iSize=0;
	while(pTemp)
	{
		iSize+=pTemp->GetSize();
		pTemp=pTemp->pNext;
	}
	return iSize;
}

short* HShortQueue::ConvertToArray(int &iSize)
{
	iSize=GetSize();
	short* pBuffer=new short[iSize];
	int i=0;
	while(!Empty())
	{
		short* p=pBuffer+i;
		int iRange=RemoveItem(p);
		i+=iRange;
	}
	return pBuffer;
}

IMPLEMENT_DYNCREATE(HSoundRecorder, CWinThread)

HSoundRecorder::HSoundRecorder()
{
	m_hWaveIn	=NULL;
}

HSoundRecorder::~HSoundRecorder()
{
	if(m_pSamples)
		delete []m_pSamples;
}

void HSoundRecorder::AddBuffer()
{
	//new a buffer:
	char	*sBuf=new char[m_wfData.nBlockAlign*m_iBufferSize];

	//new a header:
	LPWAVEHDR	pHdr=new WAVEHDR;
	if(!pHdr)	return;
	ZeroMemory(pHdr,sizeof(WAVEHDR));

	pHdr->lpData=sBuf;
	pHdr->dwBufferLength=m_wfData.nBlockAlign*m_iBufferSize;

	//prepare it:
	::waveInPrepareHeader(m_hWaveIn, pHdr, sizeof(WAVEHDR));
	//add it:
	::waveInAddBuffer(m_hWaveIn, pHdr, sizeof(WAVEHDR));
	HSoundRunner::AddBuffer();
}

BOOL HSoundRecorder::Start(WAVEFORMATEX* pwfex)
{
	if(!HSoundRunner::Start(pwfex))
		return FALSE;
	m_pQueue=new HShortQueue;

	//Open the wave device:
	if(::waveInOpen(&m_hWaveIn, WAVE_MAPPER, &m_wfData, m_dwThreadID, 0L, CALLBACK_THREAD))
	{
		::AfxMessageBox("An error occured while trying to open input device!");
		return FALSE;
	}

	//Add several buffers to queue:
	for(int i=0;i<3;i++)
		AddBuffer();
	if(::waveInStart(m_hWaveIn))
	{
		::AfxMessageBox("An error occured while trying to open input device!");
		return FALSE;
	}

	m_bRunning=TRUE;
	return TRUE;
}

BOOL HSoundRecorder::Stop()
{
	if(!HSoundRunner::Stop())
		return FALSE;

	::waveInStop(m_hWaveIn);
	::waveInClose(m_hWaveIn);

	m_pSamples=m_pQueue->ConvertToArray(m_nSamples);
	delete m_pQueue;
	return TRUE;
}

void HSoundRecorder::OnDataReady(UINT uParm, LONG lWaveHdr)
{
	LPWAVEHDR	pHdr=(LPWAVEHDR)lWaveHdr;
	::waveInUnprepareHeader(m_hWaveIn, pHdr, sizeof(WAVEHDR));
	if(m_bRunning)
	{
		//Save Input Data:
		m_pQueue->InsertItem(pHdr->dwBytesRecorded/2,(short*)pHdr->lpData);

		//Draw Buffer:
		DrawBuffer(pHdr->dwBytesRecorded/2,(short*)pHdr->lpData);

		//reuse the header:
		::waveInPrepareHeader(m_hWaveIn, pHdr, sizeof(WAVEHDR));
		::waveInAddBuffer(m_hWaveIn, pHdr, sizeof(WAVEHDR));
		return;
	}
	//we are stopping:
	delete pHdr->lpData;
	delete pHdr;
	m_nBuffers--;
}

short* HSoundRecorder::GetSamples(int& nSamples)
{
	nSamples=m_nSamples;
	return m_pSamples;
}

BOOL HSoundRecorder::IsRecording()
{
	return m_bRunning;
}

BEGIN_MESSAGE_MAP(HSoundRecorder, CWinThread)
	//{{AFX_MSG_MAP(HSoundRecorder)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_THREAD_MESSAGE(MM_WIM_DATA, OnDataReady)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HSoundRecorder message handlers
