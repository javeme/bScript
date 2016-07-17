#pragma once
#include "Exception.h"

namespace bluemei{


class BLUEMEILIB_API ThreadException : public Exception
{
public:
	ThreadException(int error=0);
	ThreadException(cstring strError);
	~ThreadException(void);

public:
	virtual String getMessage()const;
	virtual String toString()const;
private:
	int m_nError;
};

}//end of namespace bluemei