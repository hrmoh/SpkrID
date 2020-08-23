#include "stdafx.h"
#include "SoundPlayer.h"

HSoundPlayer::HSoundPlayer()
{
	m_hWaveOut = NULL;
}

HSoundPlayer::~HSoundPlayer()
{
}

BEGIN_MESSAGE_MAP(HSoundPlayer, CWinThread)
	//{{AFX_MSG_MAP(HSoundPlayer)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_THREAD_MESSAGE(MM_WOM_DONE, OnMM_WOM_DONE)
END_MESSAGE_MAP()

void HSoundPlayer::SetData(int iSize, short* pData)
{
	m_nSamples=iSize;
	m_pSamples=pData;
}

BOOL HSoundPlayer::Start(WAVEFORMATEX* format)
{
	if(m_pSamples==NULL)
		return FALSE;
	if(!HSoundRunner::Start(format))
		return FALSE;
	else
	{
		// open wavein device
		MMRESULT mmReturn = 0;
		mmReturn = ::waveOutOpen( &m_hWaveOut, WAVE_MAPPER, &m_wfData, m_dwThreadID, NULL, CALLBACK_THREAD);
		if(mmReturn)
		{
			::AfxMessageBox("An error occured while trying to open output device.");
			return FALSE;
		}
		else
		{
			m_bRunning = TRUE;
			
			// we need at least 2 -> one for playing, one for refilling (3 is better)
			m_nSamplesPlayed=0;
			for(int i=0; i<3; i++)
				AddBuffer();
		}
	}
	return TRUE;	
}
BOOL HSoundPlayer::Start(int iSize, short* pData, WAVEFORMATEX* format)
{
	SetData(iSize, pData);
	return Start(format);
}

BOOL HSoundPlayer::Stop()
{
	if(HSoundRunner::Stop())
		return (::waveOutReset(m_hWaveOut)!=0);
	return FALSE;
}

void HSoundPlayer::OnMM_WOM_DONE(UINT parm1, LONG parm2)
{	

	LPWAVEHDR pHdr = (LPWAVEHDR) parm2;
	//Draw Buffer:
	DrawBuffer(pHdr->dwBufferLength/2,(short*)pHdr->lpData);

	if(::waveOutUnprepareHeader(m_hWaveOut, pHdr, sizeof(WAVEHDR)))
		return;

	m_nBuffers--;

	if(m_bRunning)
	{		

		if(!(m_nSamplesPlayed+m_iBufferSize/2>=m_nSamples))
		{
			AddBuffer();
			// delete old header
			delete pHdr;
			return;			
		}
		else
		{
			Stop();
		}
	}

	// we are closing the waveOut handle, 
	// all data must be deleted
	// this buffer was allocated in Start()
	delete pHdr;

	if(m_nBuffers == 0 && m_bRunning == false)
	{
		if (::waveOutClose(m_hWaveOut))
			 return;
	}
}

void HSoundPlayer::AddBuffer()
{
	MMRESULT mmReturn = 0;
	
	// create the header
	LPWAVEHDR pHdr = new WAVEHDR;
	if(pHdr == NULL) return;

	// new a buffer
	pHdr->lpData = (char*)(m_pSamples+m_nSamplesPlayed);//buffer;
	pHdr->dwBufferLength = m_iBufferSize;
	pHdr->dwFlags = 0;
	
	// prepare it
	mmReturn = ::waveOutPrepareHeader(m_hWaveOut,pHdr, sizeof(WAVEHDR));
	// write the buffer to output queue
	mmReturn = ::waveOutWrite(m_hWaveOut, pHdr, sizeof(WAVEHDR));
	if(mmReturn) return;
	// increment the number of waiting buffers
	m_nSamplesPlayed+=m_iBufferSize/2;

	HSoundRunner::AddBuffer();
}

BOOL HSoundPlayer::IsPlaying()
{
	return m_bRunning;
}

