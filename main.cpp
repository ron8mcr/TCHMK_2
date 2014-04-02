#include <stdio.h>
#include <stdlib.h>
#include "IbigInt.h"
#include <iostream>
#include <dlfcn.h>
using namespace std;


int main(int argc, char* argv[])
{
	// load the bigInt.so library
	void* bigIntSO = dlopen("./bigInt.so", RTLD_LAZY);
	if (!bigIntSO) 
	{
		cerr << "Cannot load library: " << dlerror() << '\n';
	        return 1;
	}

	// load the symbols
	PCreatebigInt crBI = (PCreatebigInt ) dlsym(bigIntSO, "CreatebigInt");
	PCreatebigIntString crBIString = (PCreatebigIntString ) dlsym(bigIntSO, "CreatebigIntString");
	PCreatebigIntVal crBIVal = (PCreatebigIntVal ) dlsym(bigIntSO, "CreatebigIntVal");
	if (!crBI || !crBIString || !crBIVal)
	{
		cerr << "Cannot load symbols: " << dlerror() << '\n';
		return 1;
	}

	// create an instance of the class
	IbigInt* A = crBI();
	IbigInt* B = crBIString("123456789");
	IbigInt* C = crBIVal(4294526);
	
	cout << A->getString() << endl;
	cout << B->getString() << endl;	
	cout << C->getString() << endl;	
	
	A->release();
	B->release();
	C->release();

	// unload the  library
	dlclose(bigIntSO);
	return 0;
}
