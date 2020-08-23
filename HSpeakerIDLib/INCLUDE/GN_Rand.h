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
//    Generate uniform or normal distribution random numbers.
//
//
//    Author  : Jialong HE
//    Date    : April 27, 1999
//************************************************************************
#ifndef __GN_Rand_H__
#define __GN_Rand_H__

#include "SV_General.h"

class GN_Rand {

private :

	char * initstate(int seed, char *arg_state, int n);
public :

	//------------------------------- 
	// constructor/destructor
	//------------------------------- 
	GN_Rand();
	virtual ~GN_Rand();

	//------------------------------- 
	// public methods
	//------------------------------- 
	long getmax(void) {return (0x7fffffff);}    // maximum of uniform rand
	void srandom(int Seed);                     // set random seed
	long random(void);                          // uniform distribution
    double rand_gaus(double Mean, double Vari); // gaus distribution

};   // class GN_Rand

#endif   // GN_Rand