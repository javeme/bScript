#pragma once
#include "bluemeiLib.h"
#include "NotFoundException.h"

namespace bluemei{

class ClassNotFoundException:public NotFoundException
{
public:
	ClassNotFoundException(cstring msg);
	virtual ~ClassNotFoundException(void);
	virtual String toString()const;
};



}//end of namespace bluemei