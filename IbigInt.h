// интерфейсный класс для bigInt
#ifndef IBIGINT
#define IBIGINT
#include "stdio.h"

class IbigInt 
{
protected:
    virtual ~IbigInt();
public:
	virtual void release() = 0;
	virtual char* getString() = 0;
	// можно сделать так, чтобы все операторы возвращали ссылку на объект,
	// как это сделано с "++"
	virtual IbigInt* operator++() = 0;
	// но это как-то "некрасиво"
};




// the types of the class factories
typedef IbigInt* ( * PCreatebigInt )();
typedef IbigInt* ( * PCreatebigIntString )(const char*);
typedef IbigInt* ( * PCreatebigIntVal )(long long int);

#endif
