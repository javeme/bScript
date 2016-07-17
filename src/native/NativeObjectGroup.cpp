#include "StdAfx.h"
#include "NativeObjectGroup.h"

namespace bluemei{


NativeObjectGroup::NativeObjectGroup(void)
{
	setAutoRelease(true);
}


NativeObjectGroup::~NativeObjectGroup(void)
{
	clearObjects();
	clearClasses();
}

bool NativeObjectGroup::registerClass( NativeClass* cls )
{
	if(cls!=nullptr)
	{
		if(m_nativeClassMap.get(cls->getClassName())!=nullptr)
			return true;
		return m_nativeClassMap.put(cls->getClassName(),cls);
	}
	return false;
}

NativeClass* NativeObjectGroup::getClass( const String& name )
{
	return dynamic_cast<NativeClass*>(m_nativeClassMap.get(name));
}

NativeClass* NativeObjectGroup::removeClass( const String& name )
{
	return dynamic_cast<NativeClass*>(m_nativeClassMap.remove(name));
}

bool NativeObjectGroup::removeClass( NativeClass* cls )
{
	return m_nativeClassMap.remove(cls);
}

void NativeObjectGroup::clearClasses()
{
	return m_nativeClassMap.clear(m_bAutoRelease);
}


bool NativeObjectGroup::registerLocalObj( const String& name,Object* pObject )
{
	//NativeClass* pNativeClass=new NativeClass(pObject->thisClass());
	//pNativeClass->addFunction("createObject()",Object::createObject());
	bool b=Object::thisClass()->isMyInstance(pObject);
	if(!pObject->getThisClass()->isMyObject(pObject))
		return false;
	NativeClass* pNativeClass=getClass(pObject->getThisClass()->getName());
	NativeObject* pNativeObject=new NativeObject(pNativeClass);
	pNativeObject->attachLocalObj(name,pObject);
	return putObject(pNativeObject);
}

bool NativeObjectGroup::putObject( NativeObject* obj )
{
	if(obj!=nullptr)
		return m_nativeObjMap.put(obj->getThisName(),obj);
	return false;
}

NativeObject* NativeObjectGroup::getObject( const String& name )
{
	return dynamic_cast<NativeObject*>(m_nativeObjMap.get(name));
}

NativeObject* NativeObjectGroup::removeObject( const String& name )
{
	return dynamic_cast<NativeObject*>(m_nativeObjMap.remove(name));
}

bool NativeObjectGroup::removeObject( NativeObject* obj )
{
	return m_nativeObjMap.remove(obj);
}

void NativeObjectGroup::clearObjects()
{
	m_nativeObjMap.clear(m_bAutoRelease);
}


}//end of namespace bluemei