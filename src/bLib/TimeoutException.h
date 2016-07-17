#ifndef TimoutException_H_H
#define TimoutException_H_H
#include "RuntimeException.h"


namespace bluemei
{

class BLUEMEILIB_API TimeoutException : public RuntimeException
{
public:
	TimeoutException(long long time);
	virtual ~TimeoutException(void){};		
public:
	virtual String toString()const;
};


}//end of namespace bluemei
#endif