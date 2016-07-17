#pragma once
#include "BString.h"
#include "OpValueType.h"

namespace bluemei{

class Field : public Object
{
public:
	Field(){
		data=nullptr;;
	}
	Field(OpValueType t):type(t){
		data=new byte[type.size()];
	}
	virtual~Field()
	{
		delete[]data;
	}
protected:
	String name;
	ValueTypeObject type;
	byte* data;
public:
	byte* getDataAddress(){ return data;}
};


}//end of namespace bluemei