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
//    a class to hold a data pattern (matrix). 
//
//
//    Author  : Jialong HE
//    Date    : April 27, 1999
//************************************************************************
#ifndef __SV_Data_H__
#define __SV_Data_H__
#include <iostream.h>

#include "SV_General.h"

#define DHLen 64         // data pattern header length

//--------------------------------------------------------- 
// Each record has 64 bytes RecHdr, followed by a matrix
//--------------------------------------------------------- 
typedef struct {
	char    Signature[8];		// identifying a data record
	long    ByteOrder;			// init to 0x1, 0x02, 0x03, 0x04
	float	Version;			// e.g., 1.3
	long	ID;					// record's class ID
	char	Name[16];			// record's Label (Name)
	char	NotUsed[DHLen-36];	// for extension
} REC_HDR;

//--------------------------------------------------------- 
// Data Record class
//--------------------------------------------------------- 
class SV_Data {

private :

	long ClassSig;              // Class Signature

public :
	REC_HDR	Hdr;				// header info
	float	**Mat;				// data matrix
	int		Row;				// Row of matrix
	int		Col;				// Col of matrix
	SV_Data *Next;				// point to next DataRec

	//----------------------------------
	// Constructor/Destructor
	//----------------------------------
	SV_Data();					// constructor
	SV_Data(int M, int N);		// automatic allocate Matrix

	SV_Data(const SV_Data& Src); // COPY constructor

	virtual ~SV_Data();			// destructor
	void Alloc(void);			// allocate memory for Mat
	int  Valid(void);			// 1: yes, 0: no. Test Class's Signature

	//----------------------------------
	// overload <<, dump Data in ASCII
	//----------------------------------
	friend ostream& operator<< (ostream& os, SV_Data& Data);

	//----------------------------------
	// overload assignment operator =
	//----------------------------------
	SV_Data &operator= (const SV_Data &Src);

};

#endif;
