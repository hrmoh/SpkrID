//------------------------------------------------------------------------
//		SoundRecorder.h:   Header file for HSoundRecorder class	 
//		By: Hamid Reza Mohammadi 
//		    Web Page:	http://mohammadi.netfirms.com 
//		    Email:	hamidreza_mo@hotmail.com
//		Written based on code provided by 
//		    Thomas Holme (thomas.holme@openmpeg4.org)
//		Date:	7/26/2002
//		Last Updated:	7/29/2002
//------------------------------------------------------------------------

#if !defined(__SOUNDRECORDER_H)
#define __SOUNDRECORDER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SoundRunner.h"

//HShortPocket:
//	a small stucture, used in storing recordings:
class HShortPocket
{
public:
	HShortPocket(int iSize, short* pBuffer);
	~HShortPocket();
	int GetSize();
	short* GetBuffer();

	HShortPocket* pNext;
	HShortPocket* pPrev;
private:
	int		m_iSize;
	short	*m_pBuffer;
};

//HShortQueue:
//	a queue of HShortPocket elements:

class HShortQueue
{
public:
	HShortQueue();
	~HShortQueue();
	void	InsertItem(int iSize, short* pBuffer);
	int		RemoveItem(short* pBuffer);//returns size of front element and fills pBuffer with the buffer
	BOOL	Empty();
	int GetSize();
	short* ConvertToArray(int& iSize);
private:
	HShortPocket* pFront;
	HShortPocket* pRear;
};

//	HSoundRecorder:
//		This class is derived from HSoundRunner, and acts as
//		the class you can use for recording:

class HSoundRecorder : 
	public HSoundRunner
{
	DECLARE_DYNCREATE(HSoundRecorder)

public:
	HSoundRecorder();           
	virtual ~HSoundRecorder();

protected:
	void AddBuffer();

	//Message Map For WM_WIM_DATA:
	afx_msg void OnDataReady(UINT uParm, LONG lWaveHdr);

private:
	HWAVEIN m_hWaveIn;
	HShortQueue* m_pQueue;

public:	

	BOOL Start(WAVEFORMATEX* pwfex=NULL);
	BOOL Stop();
	short* GetSamples(int& nSamples);
	BOOL IsRecording();

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__SOUNDRECORDER_H
