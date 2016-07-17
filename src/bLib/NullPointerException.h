#pragma once

#include "bluemeiLib.h"
#include "RuntimeException.h"

namespace bluemei{

class BLUEMEILIB_API NullPointerException : public RuntimeException
{
public:
	NullPointerException(cstring str):RuntimeException(str){};
	virtual ~NullPointerException(void){};
	virtual String toString()const{
		return "NullPointerException: "+m_strLastError;
	}
};

}//end of namespace bluemei