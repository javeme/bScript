#pragma once
#include "stdafx.h"
#include <stdlib.h>
#include "stdarg.h"
#include "Object.h"

namespace bluemei{

class Executeable : public Object
{
public:
	virtual void execute()=0;
};

}//end of namespace bluemei