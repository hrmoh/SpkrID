#include "StdAfx.h"
#include "Speaker.h"
#include "include\SV_DataIO.h"

HSpeaker::HSpeaker()
{
	m_pModel=new SV_Model_DTW;
	m_pPassphrase=NULL;
	m_strName="";
}

HSpeaker::HSpeaker(SV_Model_DTW* pModel)
{
	m_pModel=pModel;
	m_pPassphrase=NULL;
	m_strName="";
}

HSpeaker::~HSpeaker()
{
	if(m_pPassphrase)
		delete m_pPassphrase;
}

void HSpeaker::SetUserName(CString strName)
{
	m_strName=strName;
}

void HSpeaker::SetPassphrase(int nSamples, short* pSamples)
{
	SV_Feature_MFCC Feature ;
//	SV_Feature_Pitch Feature ;
//	SV_Feature_LPCC Feature;
	PrepareFeature(Feature);
	Feature.CopySignal(pSamples, nSamples);
	m_pPassphrase=Feature.ExtractFeature();
}

double HSpeaker::Verify(int nSamples, short* pSamples)
{
	HSpeaker Temp(m_pModel);
	Temp.SetPassphrase(nSamples, pSamples);
	return Verify(&Temp);
}

double HSpeaker::Verify(HSpeaker* pSpeaker)
{
	return m_pModel->DTW_Comp(*m_pPassphrase, *pSpeaker->m_pPassphrase);
}

BOOL HSpeaker::LoadFrom(CFile* pFile)
{
	BYTE bNameLength;
	if(pFile->Read(&bNameLength,sizeof(BYTE))!=sizeof(BYTE))
		return FALSE;
	char* name=new char[bNameLength+1];
	pFile->Read(name,bNameLength*sizeof(char));
	name[bNameLength]='\0';
	m_strName=name;
	delete []name;

	int iSize;
	pFile->Read(&iSize, sizeof(int));
	CFile TempFile("temp.sv", CFile::modeWrite|CFile::modeCreate);
	BYTE byte;
	for(int i=0; i<iSize; i++)
	{
		pFile->Read(&byte,sizeof(byte));
		TempFile.Write(&byte, sizeof(byte));
	}
	TempFile.Close();
	SV_DataIO Temp;
	Temp.OpenFile("temp.sv", READ_REC);
	m_pPassphrase=Temp.GetDataRec();
	Temp.CloseFile();
	DeleteFile("temp.sv");
	return TRUE;
}

BOOL HSpeaker::SaveTo(CFile* pFile)
{	
	BYTE bNameLength=(BYTE)m_strName.GetLength();
	pFile->Write(&bNameLength,sizeof(BYTE));
	for(int bc=0;bc<bNameLength;bc++)
	{
		char c=m_strName[bc];
		pFile->Write(&c,sizeof(char));
	}
	SV_DataIO Temp;
	Temp.OpenFile("temp.sv",WRITE_REC);
	Temp.PutDataRec(*m_pPassphrase);
	Temp.CloseFile();
	CFile TempFile("temp.sv", CFile::modeRead);
	BYTE byte;
	int iSize=0;
	while(TempFile.Read(&byte, sizeof(byte))==sizeof(byte)) iSize++;
	TempFile.Close();
	pFile->Write(&iSize, sizeof(int));
	TempFile.Open("temp.sv", CFile::modeRead);
	int i=0;
	while(i<iSize) 
	{
		TempFile.Read(&byte, sizeof(byte));
		pFile->Write(&byte, sizeof(byte));
		i++;
	}
	TempFile.Close();
	DeleteFile("temp.sv");	
	return TRUE;
}

CString HSpeaker::GetUserName()
{
	return m_strName;
}

void HSpeaker::PrepareFeature(SV_Feature_MFCC &Feature)
{
	Feature.Para.MFCC_Order = 12;	     	// number of MFCC
	Feature.Para.NFilter    = 60;			// number of filters in Filter bank 
	Feature.Para.FFTSz      = 512;       	// FFT length 
	Feature.Para.DEnergy    = 1;	 		// 1: output delta value for first MFCC (energy)
	Feature.Para.WinSz = 512;
	Feature.Para.StpSz = 256;
        Feature.Para.Alpha = 0.97;			    // preemphesis, default=0.97
        Feature.Para.HammingWin = 1;	        // 1: Hamming window, 0: rect window (no window)
        Feature.Para.RmvSilence = 1;	        // 1: remove silence part, 0: intact
}

void HSpeaker::PrepareFeature(SV_Feature_Pitch &Feature)
{
    Feature.Para.WinSz = 512;
    Feature.Para.StpSz = 256;
    Feature.Para.RmvSilence = 1;
    Feature.Para.Smooth = 1;
}

void HSpeaker::PrepareFeature(SV_Feature_LPCC &Feature)
{
    Feature.Para.FType = Coef_LPCC;    
    Feature.Para.LPC_Order = 10;         
    Feature.Para.LPCC_Order = 12;

    Feature.Para.WinSz = 512;
    Feature.Para.StpSz = 256;
    Feature.Para.Alpha = 0.97;
    Feature.Para.HammingWin = 1;
    Feature.Para.RmvSilence = 1;
}