//------------------------------------------------------------------------
//		SoundPlayer.h:   Header file for HSoundPlayer class	 
//		By: Hamid Reza Mohammadi 
//		    Web Page:	http://mohammadi.netfirms.com 
//		    Email:	hamidreza_mo@hotmail.com
//		Written based on code provided by 
//		    Thomas Holme (thomas.holme@openmpeg4.org)
//		Date:	7/26/2002
//		Last Updated:	7/29/2002
//------------------------------------------------------------------------

#if !defined(__SOUNDPLAYER_H)
#define __SOUNDPLAYER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SoundRunner.h"

//		HSoundPlayer:
//			main class which can be used for playing a buffer
class HSoundPlayer:
	public HSoundRunner
{
public:
	HSoundPlayer();
	~HSoundPlayer();

	void SetData(int nSamples, short* pSamples);
	BOOL Start(WAVEFORMATEX* format=NULL);
	BOOL Start(int iSize, short* pData, WAVEFORMATEX* pwfex=NULL);
	BOOL Stop();
	BOOL IsPlaying();

	void AddBuffer();

	DECLARE_MESSAGE_MAP()	
	afx_msg void OnMM_WOM_DONE(UINT parm1, LONG parm2);

private:

	HWAVEOUT m_hWaveOut;
	int m_nSamplesPlayed;
};

#endif	//!defined(__SOUNDPLAYER_H)