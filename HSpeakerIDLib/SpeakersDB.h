#if !defined(__SPEAKERSDB_H)
#define __SPEAKERSDB_H

#include "Speaker.h"

struct SpeakerPasses
{
	SpeakerPasses(){pNext=NULL;}
	HSpeaker* pSpeaker;
	SpeakerPasses* pNext;
	double Verify(HSpeaker* pSpeaker);
};

struct SpeakersPasses
{
	CString strName;
	SpeakersPasses(){pNext=NULL;}
	SpeakerPasses* pFirst;
	SpeakersPasses* pNext;
	double Identify(HSpeaker* pSpeaker);
	double Find(HSpeaker* pSpeaker,int &Index);
};

class HSpeakersTable
{
public:
	HSpeakersTable(){m_pFirst=NULL;}
	void Insert(HSpeaker* pSpeaker);
	HSpeaker* Get(int iMain, int iSub=0);
	int GetSubsNum(int iMain);
	int GetIndex(CString str);
	int GetNum();
	int Identify(HSpeaker* pSpeaker, double fThreshold);
	void RemoveUser(int nIndex);
	BOOL RemPass(int nIndex, HSpeaker* pSpeaker, double fThreshold);
private:
	SpeakersPasses* m_pFirst;
};

class HSpeakersDB
{
public:
	HSpeakersDB(BOOL bAutoLoad=FALSE);

	void LoadUsers();
	void StoreUsers();

	int GetUsersNum();
	void AddUser(HSpeaker* pSpeaker);
	CString GetUserName(int index);
	int Identify(HSpeaker* pSpeaker);
	int GetPassesNum(int index);
	void RemoveUser(int nIndex);

private:
	void CreateUsersDB();

private:
	HSpeakersTable* m_pTable;
	CString m_strDBFileName;

private:	//user identification options:
	int m_nRepetitions;
	float m_fMinPassLength;
	double m_fThreshold;

public:
	void SetRepsNum(int iNum);
	int GetRepsNum();

	void SetMinPassLen(float fMin);
	float GetMinPassLen();

	void SetSecurityLevel(int nLevel);
	int GetSecurityLevel();

public:
	BOOL RemPass(int index, HSpeaker* pSpeaker);
};

#endif