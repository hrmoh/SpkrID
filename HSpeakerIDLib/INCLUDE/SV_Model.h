//########################################################################
//  
// A C++ class library for automatic speech recognition and 
// speaker recognition (identification and verification). 
//
// This class library is provided "as is" without any express 
// or implied warranty of any kind with respect to this software. 
// In particular the author shall not be liable for any direct, 
// indirect, special, incidental or consequential damages arising 
// in any way from use of the software.
//
//
// Author   : Jialong He,  Copyright (C), all rights reserved. 
// Date     : May, 1999. 
//
// Contact  : Jialong_He@bigfoot.com, Jialong_He@homemail.com
// Web Page : www.bigfoot.com/~Jialong_He
//########################################################################

//************************************************************************
//    This is the base class of all model classes. It contais
//    commonly used functions.
//
//    Author  : Jialong HE
//    Date    : May 3, 1999
//
//************************************************************************
#ifndef __SV_Model_H__
#define __SV_Model_H__

#include <fstream.h>
#include "SV_General.h"
#include "SV_Data.h"

//----------------------------------------
// Open mode for model file 
//----------------------------------------
#define  WRITE_MODEL	1   // write
#define  APPEND_MODEL	2   // append
#define  READ_MODEL	    3	// read


//-------------------------
// Model Type
//-------------------------
#define  MT_GAUS	1
#define  MT_GMM		2
#define  MT_VQ		3
#define  MT_DHMM	4
#define  MT_CHMM	5

//-----------------------------
// Multivariate Gaussian Table
//-----------------------------
#define ITEMS     8000                    /* Exp or Log table items */
#define RANGE     1.0                     /* Table: 0.0 - RANGE */
#define STEPSIZE  (RANGE / ITEMS)

//--------------------------------------------------------- 
// Each record has 64 bytes RecHdr, followed by a matrix
//--------------------------------------------------------- 
#define  MHLen			64      // model header's length
typedef struct {
	char    Signature[8];		// identifying a valid model
	long    ByteOrder;			// init to 0x1, 0x02, 0x03, 0x04
	float	Version;			// e.g., 1.3
	long	ID;					// model's class ID
	long	ModelType;			// Model Type, Gaus, GMM, etc.
	char	Name[16];			// model's Name
	char	NotUsed[MHLen-40];	// for extension
} MODEL_HDR;

//===================================================================
// Base class of model
//===================================================================
class SV_Model {

private :
	//------------------------------------------
	// for speed up gaussian function
	//------------------------------------------
	int FirstCall;      
	double *LogTab;

	long ClassSig;        // class signature

protected :
	fstream		DFile;

	int  SaveHdr(void);  // save model header
	int  LoadHdr(void);  // called by Save/Load model

public :

	SV_Model *Next;    // point to next model in the chain
	MODEL_HDR Hdr;     // model's header

	//------------------------------- 
	// constructor/destructor
	//------------------------------- 
	SV_Model();
	virtual ~SV_Model();
	int Valid(void);              // test class signature

	//------------------------------- 
	// preprocessing training data
	//------------------------------- 
	SV_Data *MergeData(SV_Data *pData);  // form one huge pattern
	double **CovMatrix(SV_Data *pData);  // return covariance matrix
	double *MeanVec(SV_Data *pData);     // return mean vector
	int  CountPat(SV_Data *pData);       // return number of patterns in the linked list
	void OrthTrans(SV_Data *pData, double **TransMat); // orth trans linkedlist

	//------------------------------------------------
	// Commonly used methods
	//------------------------------------------------
	int nearest_code (float **CodeBook, float *testvector, int CodeNum, int Dim);
	double Gaussian (double *Mean, double *Vari, float *Vector, int Dim);
	int* RandSeq(int MaxNum, int Seed = 1999);

	//------------------------------- 
	// Open/Close model file
	//------------------------------- 
	void OpenFile(char *FName, int Mode);
	void CloseFile(void);

	//----------------------------------------------- 
	// model I/O, 
	// NOTE: must be overrided by derived class
	//----------------------------------------------- 
	virtual int SaveModel(void);
	virtual SV_Model *LoadModel(void);

	//---------------------------------------------------- 
	// train/test model
	// NOTE: must be overrided by derived class
	//---------------------------------------------------- 
	virtual void TrainModel(SV_Data *TrainData);
	virtual SV_Data *TestModel(SV_Data *TestData);

};   // class SV_Model


#endif

