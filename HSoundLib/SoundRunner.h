//------------------------------------------------------------------------
//		SoundRunner.h:	Header file for HSoundRunner class	 
//		By: Hamid Reza Mohammadi 
//		    Web Page:	http://mohammadi.netfirms.com 
//		    Email:	hamidreza_mo@hotmail.com
//		Written based on code provided by 
//		    Thomas Holme (thomas.holme@openmpeg4.org)
//		Date:	7/26/2002
//		Last Updated:	7/29/2002
//------------------------------------------------------------------------

#if !defined(__SOUNDRUNNER_H)
#define __SOUNDRUNNER_H

#include "Sound.h"

//	HSoundRunner:
//		This class is derived from HSound and CWinThread, and acts
//		as the base class for HSoundRecorder and HSoundPlayer
//		classes.
class HSoundRunner:
	public CWinThread,
	public HSound
{
public:
	DECLARE_DYNCREATE(HSoundRunner)

	//constructor, destructor:
	HSoundRunner();
	~HSoundRunner();

	//setting buffer size, buffer size determines after what number of samples
	//multimedia messages would be called,
	//some bugs had been seen, running on low BufferSize values, and at high
	//buffer size values, while running methods a long time
	void	SetBufferSize(int nSamples);
	int		GetBufferSize();

	//main operational methods,
	//this metheods should be overriden:
	void AddBuffer();
	BOOL Start(WAVEFORMATEX* pwfex=NULL);
	BOOL Stop();

	//for graphical display:
	void SetOwner(CWnd* pWnd);
	void ClearOwner(COLORREF crBkColor=0x000000);

public:

	//{{AFX_VIRTUAL(HSoundRecorder)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

protected:
	DWORD m_dwThreadID;

	int m_iBufferSize;	// number of samples per each running period
	int m_nBuffers;		//number of buffers remained to be run

	int m_nSamples;		//number of samples stored, should be reffered before or after running
	short* m_pSamples;	//samples stored

	BOOL m_bRunning;	//indicated running or not	

	CWnd* m_pOwner;		//if graphical display is intended set this value
	void DrawBuffer(int nSamples, short* pSamples, COLORREF crBkColor=0x000000, COLORREF crLineColor=0x00FF00);	// automatically called inside message 
							//manipulators in derived classes
};

#endif