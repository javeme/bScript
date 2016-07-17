#pragma once
#include "Object.h"

namespace bluemei{

enum OpValueType{
	OPT_UNKNOWN,OPT_VOID,
	INT1,INT2,INT4,LONG8,
	FLOAT4,DOUBLE8,LONG_DOUBLE16,
	PTR4,REF4
};
static const int opValueTypeSize[]={
	0,0,
	1,2,4,8,
	4,8,sizeof(long double),
	sizeof(void*),4
};


typedef enum CallType{
	stdCall,
	cdeclCall,
	fastCall,
	thisCall,
	nakedCall,
}call_type_t;

class ValueTypeObject : public Object
{
protected:
	OpValueType type;
public:
	ValueTypeObject(){
		setType(OPT_UNKNOWN);
	}
	ValueTypeObject(OpValueType t)
	{
		setType(t);
	}
	void setType(OpValueType t)
	{
		if(t<0 || t>sizeof(opValueTypeSize)/sizeof(int))
			t=OPT_UNKNOWN;
		type=t;
	}
	OpValueType getType()
	{
		return type;
	}
	int size()
	{
		return opValueTypeSize[type];
	}
};

}//end of namespace bluemei