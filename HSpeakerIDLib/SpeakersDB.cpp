#include "StdAfx.h"
#include "SpeakersDB.H"

double SpeakerPasses::Verify(HSpeaker* pAnotherSpeaker)
{
	return pSpeaker->Verify(pAnotherSpeaker);
}

double SpeakersPasses::Identify(HSpeaker* pSpeaker)
{
	double fMin=10;
	double d;
	int i=0;
	for(SpeakerPasses* p=pFirst; p!=NULL; p=p->pNext,i++)
		if((d=p->Verify(pSpeaker))<fMin)
			fMin=d;
	return fMin;
}

double SpeakersPasses::Find(HSpeaker* pSpeaker, int &Index)
{
	double fMin=10;
	double d;
	int i=0;
	for(SpeakerPasses* p=pFirst; p!=NULL; p=p->pNext,i++)
		if((d=p->Verify(pSpeaker))<fMin)
		{
			Index=i;
			fMin=d;
		}
	return fMin;
}

void HSpeakersTable::Insert(HSpeaker* pSpeaker)
{
	if(m_pFirst==NULL)
	{
		m_pFirst=new SpeakersPasses;
		m_pFirst->strName=pSpeaker->GetUserName();
		m_pFirst->pFirst=new SpeakerPasses;
		m_pFirst->pFirst->pSpeaker=pSpeaker;
		return;
	}
	else
	{
		int index;
		if((index=GetIndex(pSpeaker->GetUserName()))!=-1)
		{
			int i=0;
			for(SpeakersPasses* p=m_pFirst; i<index; p=p->pNext,i++);
			for(SpeakerPasses* q=p->pFirst; q->pNext!=NULL; q=q->pNext);
			q->pNext=new SpeakerPasses;
			q->pNext->pSpeaker=pSpeaker;
		}
		else
		{
			for(SpeakersPasses* p=m_pFirst; p->pNext!=NULL; p=p->pNext);
			p->pNext=new SpeakersPasses;
			p->pNext->strName=pSpeaker->GetUserName();
			p->pNext->pFirst=new SpeakerPasses;
			p->pNext->pFirst->pSpeaker=pSpeaker;
		}
	}
}

HSpeaker* HSpeakersTable::Get(int iMain, int iSub)
{
	int index=0;
	for(SpeakersPasses* p=m_pFirst; index<iMain; p=p->pNext,index++);
	index=0;
	for(SpeakerPasses* q=p->pFirst; index<iSub; q=q->pNext,index++);
	return q->pSpeaker;
}

int HSpeakersTable::GetSubsNum(int iMain)
{
	if(m_pFirst==NULL)
		return 0;
	int index=0;
	for(SpeakersPasses* p=m_pFirst; index<iMain; p=p->pNext,index++);
	index=1;
	for(SpeakerPasses* q=p->pFirst; q->pNext!=NULL; q=q->pNext,index++);
	return index;
}

int HSpeakersTable::GetIndex(CString str)
{
	int index=0;
	for(SpeakersPasses* p=m_pFirst; p!=NULL; p=p->pNext,index++)
	{
		if(str==p->strName)
			return index;
	}
	return -1;
}

int HSpeakersTable::GetNum()
{
	if(m_pFirst==NULL)
		return 0;
	int Num=1;
	for(SpeakersPasses* p=m_pFirst; p->pNext!=NULL; p=p->pNext,Num++);
	return Num;
}

int HSpeakersTable::Identify(HSpeaker* pSpeaker, double fThreshold)
{
	double fMin=10,d;
	int index;
	int i=0;
	for(SpeakersPasses* p=m_pFirst; p!=NULL; p=p->pNext,i++)
	{
		if((d=p->Identify(pSpeaker))<fMin)
		{
			fMin=d;
			index=i;
		}
	}
	if(fMin<=fThreshold)
		return index;
	return -1;
}

BOOL HSpeakersTable::RemPass(int nIndex, HSpeaker* pSpeaker,double fThreshold)
{
	int i=0;
	for(SpeakersPasses* p=m_pFirst;i<nIndex; p=p->pNext,i++);
	int Index=-1;
	if(p->Find(pSpeaker,Index)<=fThreshold)
	{
		if(Index==0)
		{
			SpeakerPasses *t=p->pFirst;
			p->pFirst=t->pNext;
			delete t;
		}
		else
		{
			int i=0;
			for(SpeakerPasses *q=p->pFirst; i<Index-1;q=q->pNext,i++);
			SpeakerPasses *t=q->pNext;
			q->pNext=t->pNext;
			delete t;
		}
		return TRUE;
	}
	return FALSE;
}

void HSpeakersTable::RemoveUser(int nIndex)
{
	if(nIndex==0)
	{
		SpeakersPasses *p=m_pFirst;
		m_pFirst=m_pFirst->pNext;
		SpeakerPasses* q=p->pFirst;
		for(SpeakerPasses* r=q->pNext;r!=NULL;r=r->pNext)
		{
			delete q;
			q=r;
		}
		delete p;
		return;
	}
	int i=1;
	for(SpeakersPasses* p=m_pFirst; i<nIndex; p=p->pNext,i++);
	SpeakersPasses *pp=p->pNext;
	p->pNext=pp->pNext;
	SpeakerPasses* q=pp->pFirst;
	for(SpeakerPasses* r=q->pNext;r!=NULL;r=r->pNext)
	{
		delete q;
		q=r;
	}
	delete pp;
}

HSpeakersDB::HSpeakersDB(BOOL bAutoLoad)
{
	m_pTable=new HSpeakersTable;
	m_strDBFileName="Users.db";
	if(bAutoLoad)
		LoadUsers();
}

void HSpeakersDB::LoadUsers()
{
	CFile UsersDB;
	m_nRepetitions=2;
	m_fMinPassLength=2.0;
	m_fThreshold=0.7;
	if(UsersDB.Open("USERS.DB",CFile::modeRead))
	{
		if(UsersDB.Read(&m_nRepetitions,sizeof(m_nRepetitions))==sizeof(m_nRepetitions))
			if(UsersDB.Read(&m_fMinPassLength,sizeof(m_fMinPassLength))==sizeof(m_fMinPassLength))
				UsersDB.Read(&m_fThreshold,sizeof(m_fThreshold));

		BOOL Finished=FALSE;
		while(!Finished)
		{
			HSpeaker* pSpeaker=new HSpeaker;
			if(pSpeaker->LoadFrom(&UsersDB))
				m_pTable->Insert(pSpeaker);
			else
			{
				delete pSpeaker;
				Finished=TRUE;
			}
		}

	}
	else
		CreateUsersDB();
}

void HSpeakersDB::CreateUsersDB()
{
	CFile UsersDB;
	UsersDB.Open("USERS.DB",CFile::modeCreate|CFile::modeWrite);
	UsersDB.Close();
}

int HSpeakersDB::GetUsersNum()
{
	return m_pTable->GetNum();
}

void HSpeakersDB::AddUser(HSpeaker *pSpeaker)
{
	m_pTable->Insert(pSpeaker);
}

CString HSpeakersDB::GetUserName(int index)
{
	return m_pTable->Get(index)->GetUserName();
}

void HSpeakersDB::StoreUsers()
{
	CFile UsersDB;
	if(UsersDB.Open("USERS.DB",CFile::modeWrite|CFile::modeCreate))
	{
		UsersDB.Write(&m_nRepetitions,sizeof(m_nRepetitions));
		UsersDB.Write(&m_fMinPassLength,sizeof(m_fMinPassLength));
		UsersDB.Write(&m_fThreshold,sizeof(m_fThreshold));
		int iNum=m_pTable->GetNum();
		for(int i=0; i<iNum; i++)
		{
			int iSubs=m_pTable->GetSubsNum(i);
			for(int j=0; j<iSubs; j++)
				m_pTable->Get(i,j)->SaveTo(&UsersDB);
		}
		UsersDB.Close();
	}
}

int HSpeakersDB::Identify(HSpeaker* pSpeaker)
{
	return m_pTable->Identify(pSpeaker, m_fThreshold);
}

int HSpeakersDB::GetPassesNum(int index)
{
	return m_pTable->GetSubsNum(index);
}

void HSpeakersDB::SetRepsNum(int iNum)
{
	m_nRepetitions=iNum;
}

void HSpeakersDB::SetMinPassLen(float fMin)
{
	m_fMinPassLength=fMin;
}

void HSpeakersDB::SetSecurityLevel(int nLevel)
{
	switch(nLevel)
	{
	case VERYHIGH:
		m_fThreshold=0.3;
		break;
	case HIGH:
		m_fThreshold=0.5;
		break;
	case MEDIUM:
		m_fThreshold=0.7;
		break;
	case LOW:
		m_fThreshold=0.9;
		break;
	case VERYLOW:
		m_fThreshold=1.1;
		break;
	}
}

int HSpeakersDB::GetSecurityLevel()
{
	int nLevel;
	switch(int(m_fThreshold*10))
	{
	case 3:
		nLevel=VERYHIGH;
		break;
	case 5:
		nLevel=HIGH;
		break;
	case 7:
		nLevel=MEDIUM;
		break;
	case 9:
		nLevel=LOW;
		break;
	case 11:
		nLevel=VERYLOW;
		break;
	}
	return nLevel;
}

int HSpeakersDB::GetRepsNum()
{
	return m_nRepetitions;
}

float HSpeakersDB::GetMinPassLen()
{
	return m_fMinPassLength;
}

void HSpeakersDB::RemoveUser(int nIndex)
{
	m_pTable->RemoveUser(nIndex);
}

BOOL HSpeakersDB::RemPass(int index, HSpeaker* pSpeaker)
{
	return m_pTable->RemPass(index, pSpeaker,m_fThreshold);
}
