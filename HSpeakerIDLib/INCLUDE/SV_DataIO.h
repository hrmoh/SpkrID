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
//    Disk input/output for SV_Data.
//
//
//    Author  : Jialong HE
//    Date    : April 27, 1999
//************************************************************************
#ifndef __SV_DataIO_H__
#define __SV_DataIO_H__

#include <fstream.h>
#include "SV_General.h"
#include "SV_Data.h"

//--------------------------------
// Open mode for data stream 
//--------------------------------
#define  WRITE_REC	1   // append
#define  READ_REC	2	// read


//===================================================================
//  This is the base class of loading speech file into memory.
//  It can be used to derive a class to load signal in specific format 
//  such as NIST format.
//===================================================================
class SV_DataIO {

private :
	fstream		DFile;

protected :

public :

	//------------------------------- 
	// Constructor / Destructor
	//-------------------------------
	SV_DataIO();
	virtual ~SV_DataIO();

	//------------------------------- 
	// Open / Close a data file
	//-------------------------------
	void CloseFile(void);
	void OpenFile(char *FName, int Mode);

	//------------------------------- 
	// Write a data record to current
	// opened file.
	//-------------------------------
	int  PutDataRec(SV_Data &Data);

	//------------------------------- 
	// Get data from opened file.
	//-------------------------------
	SV_Data *GetDataRec(void);					// get next record
	SV_Data *GetDataRec(int RecID);				// get next record with RecID
	SV_Data *GetAllRec(void);					// get all record
	SV_Data *GetAllRec(int RecID);				// get all with ID

};   // class SV_DataIO


#endif
