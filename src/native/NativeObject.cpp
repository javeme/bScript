#include "StdAfx.h"
#include "NativeObject.h"

namespace bluemei{


NativeObject::NativeObject(void)
{
}

NativeObject::NativeObject(NativeClass* pClass)
{
	setThisNativeClass(pClass);
}


NativeObject::~NativeObject(void)
{
	//delete m_pThisClassRef;//引用自NativeObjectGroup,无需这里释放
	delete m_pThisObject;
}

void NativeObject::attachLocalObj( const String& name,Object* pObject )
{
	this->m_strThisName=name;
	this->m_pThisObject=pObject;
}

Object* NativeObject::detachLocalObj()
{
	Object* pObject=m_pThisObject;
	m_strThisName="null";
	m_pThisObject=nullptr;
	return pObject;
}

void NativeObject::invoke( const String& func )
{
	typedef Object*(*Fun)();
	NativeFunction *pNativeFunction=getThisNativeClass()->findFunction(func);
	Fun f=(Fun)pNativeFunction->getNativeFunAddres();
	Object *result=f();
}


}//end of namespace bluemei