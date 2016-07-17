#pragma once
#include "Object.h"
#include "BString.h"
#include "BeanContainer.h"
#include "NativeFunction.h"

namespace bluemei{

//typedef Object NativeFunction;

class NativeClass : public Object
{
public:
	NativeClass(void);
	NativeClass(const Class* thisClass);
	virtual ~NativeClass(void);
public:
	const Class* getLocalClass()const{ return m_pLocalClassRef; }
	void setLocalClass(const Class* val) { m_pLocalClassRef = val; }
	String getClassName() const { return m_pLocalClassRef->getName(); }

	bool addFunction(const String& name,NativeFunction* func);
	NativeFunction* findFunction(const String& name);
	void clearFunctions();
	int sizeOfFunctions();
protected:
	BeanContainer m_funcMap;//Map<String,NativeFunction*> Function Map
	//Map<String,Field*> m_fieldMap;
	const Class* m_pLocalClassRef;
};



}//end of namespace bluemei