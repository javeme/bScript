#ifndef _Log_h_ 
#define _Log_h_ 

#include "File.h"

namespace bluemei{


class BLUEMEILIB_API Log : public File
{
public:
	void printLine(const String& str);
};

}//end of namespace bluemei
#endif