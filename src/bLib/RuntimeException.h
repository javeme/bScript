#pragma once

#include "bluemeiLib.h"
#include "Exception.h"

namespace bluemei{

class BLUEMEILIB_API RuntimeException :public Exception
{
public:
	RuntimeException(){}
	RuntimeException(cstring str);
	virtual ~RuntimeException();
	virtual String toString()const;
};

}//end of namespace bluemei