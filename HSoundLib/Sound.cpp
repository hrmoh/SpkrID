// Sound.cpp: implementation of the HSound class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Sound.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HSound::HSound()
{
	m_wfData.wFormatTag	= WAVE_FORMAT_PCM;
	m_wfData.cbSize		= 0;
	SetBitsPerSample(16);
	SetSamplesPerSecond(44100);
	SetNumberOfChannels(1);
}

HSound::~HSound()
{

}

void HSound::SetBitsPerSample(int bps)
{
	m_wfData.wBitsPerSample = bps;
	Update();
}

int HSound::GetBitsPerSample()
{
	return m_wfData.wBitsPerSample;	
}

void HSound::SetSamplesPerSecond(int sps)
{
	m_wfData.nSamplesPerSec = sps;
	Update();
}

int HSound::GetSamplesPerSecond()
{
	return m_wfData.nSamplesPerSec;
}

void HSound::SetNumberOfChannels(int nchan)
{
	m_wfData.nChannels = nchan;
	Update();
}

int HSound::GetNumberOfChannels()
{
	return m_wfData.nChannels;
}

void HSound::Update()
{
	m_wfData.nBlockAlign		= m_wfData.nChannels     *(m_wfData.wBitsPerSample/8);
	m_wfData.nAvgBytesPerSec	= m_wfData.nSamplesPerSec*m_wfData.nBlockAlign;	
}

WAVEFORMATEX* HSound::GetFormat()
{
	return &m_wfData;
}


