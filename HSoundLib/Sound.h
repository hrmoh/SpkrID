//------------------------------------------------------------------------
//		Sound.h:	Header file for HSound class	 
//		By: Hamid Reza Mohammadi 
//		    Web Page:	http://mohammadi.netfirms.com 
//		    Email:	hamidreza_mo@hotmail.com
//		Rewritten based on code provided by 
//		    Thomas Holme (thomas.holme@openmpeg4.org)
//		Date:	5/1/2002
//		Last Updated:	7/29/2002
//------------------------------------------------------------------------

#if !defined(__SOUND_H)
#define __SOUND_H

#if _MSC_VER > 1000
#pragma once
#endif 

#include <mmsystem.h>

//	HSound:
//		This class encapsulates the WAVEFORMATEX structure,
//		and is used as the base	class for other classes.
//
class HSound
{
public:

	//constructor and destructor:
	HSound();
	virtual ~HSound();

	//setting wave data:
	void SetBitsPerSample(int bps);
	void SetSamplesPerSecond(int sps);
	void SetNumberOfChannels(int nchan);

	//retrieving wave data:
	WAVEFORMATEX* GetFormat();
	int GetSamplesPerSecond();
	int GetBitsPerSample();
	int GetNumberOfChannels();

protected:

	WAVEFORMATEX m_wfData;

private:

	void Update();
};

#endif // !defined(__SOUND_H)
