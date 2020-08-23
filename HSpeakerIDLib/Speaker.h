#if !defined(__SPEAKER_H)
#define __SPEAKER_H

#include "include\SV_Model_DTW.h"
#include "include\SV_Feature_MFCC.h"
#include "include\SV_Feature_Pitch.h"
#include "include\SV_Feature_LPCC.h"

//security levels:
#define VERYHIGH 0
#define HIGH 1
#define MEDIUM 2
#define LOW 3
#define VERYLOW 4

class HSpeaker
{
public:
	HSpeaker();
	HSpeaker(SV_Model_DTW* pModel);
	~HSpeaker();

	BOOL LoadFrom(CFile* pFile);
	BOOL SaveTo(CFile* pFile);

	void SetUserName(CString strName);
	CString GetUserName();

	void SetPassphrase(int nSamples, short* pSamples);
	double Verify(int nSamples, short* pSamples);
	double Verify(HSpeaker* pSpeaker);

	void PrepareFeature(SV_Feature_MFCC &Feature);
	void PrepareFeature(SV_Feature_Pitch &Feature);
	void PrepareFeature(SV_Feature_LPCC &Feature);
private:
	CString m_strName;
	SV_Data* m_pPassphrase;

	SV_Model_DTW* m_pModel;
};
#endif