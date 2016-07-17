#ifndef TimoutException_H_H
#define TimoutException_H_H
#include "RuntimeException.h"


namespace bluemei
{

class BLUEMEILIB_API OutOfMemoryException : public RuntimeException
{
public:
	OutOfMemoryException(long long size);	
	virtual ~OutOfMemoryException(void){};
public:
	virtual String toString()const;
};


}//end of namespace bluemei
#endif