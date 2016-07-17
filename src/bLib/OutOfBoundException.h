#pragma once

#include "bluemeiLib.h"
#include "RuntimeException.h"

namespace bluemei{

class BLUEMEILIB_API OutOfBoundException :public RuntimeException
{
public:
	OutOfBoundException(cstring str):RuntimeException(str){};
	OutOfBoundException(int out,int size);
	virtual ~OutOfBoundException();
	virtual String toString()const;
};

}//end of namespace bluemei