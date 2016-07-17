#pragma once
#include "bluemeiLib.h"
#include "RuntimeException.h"

namespace bluemei{

class NotFoundException:public RuntimeException
{
public:
	NotFoundException(cstring msg);
	virtual ~NotFoundException(void);
	virtual String toString()const;
};



}//end of namespace bluemei