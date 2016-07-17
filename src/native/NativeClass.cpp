#include "StdAfx.h"
#include "NativeClass.h"

namespace bluemei{


NativeClass::NativeClass(void)
{
	setLocalClass(Class::undefined());
}

NativeClass::NativeClass(const Class* thisClass)
{
	setLocalClass(thisClass);
}


NativeClass::~NativeClass(void)
{
	m_funcMap.clear(true);
}

bool NativeClass::addFunction( const String& name,NativeFunction* func )
{
	return m_funcMap.put(name,func);
}

NativeFunction* NativeClass::findFunction( const String& name )
{
	String memfunName;
	if(name.find("::")<0)
		memfunName=this->getClassName()+"::"+name;
	else
		memfunName=name;
	return dynamic_cast<NativeFunction*>(m_funcMap.get(memfunName));
}

void NativeClass::clearFunctions()
{
	return m_funcMap.clear();
}

int NativeClass::sizeOfFunctions()
{
	return m_funcMap.size();
}


}//end of namespace bluemei