#pragma once
#include "BeanContainer.h"
#include "NativeObject.h"

namespace bluemei{

class NativeObjectGroup : public Object
{
public:
	NativeObjectGroup(void);
	virtual ~NativeObjectGroup(void);
public:
	virtual bool registerClass(NativeClass* cls);
	virtual NativeClass* getClass(const String& name);
	virtual NativeClass* removeClass(const String& name);
	virtual bool removeClass(NativeClass* cls);
	virtual void clearClasses();

	virtual bool registerLocalObj(const String& name,Object* pObject);
	virtual bool putObject(NativeObject* obj);
	virtual NativeObject* getObject(const String& name);
	virtual NativeObject* removeObject(const String& name);
	virtual bool removeObject(NativeObject* obj);
	virtual void clearObjects();

	virtual bool isAutoRelease() const { return m_bAutoRelease; }
	virtual void setAutoRelease(bool val) { m_bAutoRelease = val; }
protected:
	BeanContainer m_nativeClassMap;
	BeanContainer m_nativeObjMap;
	bool m_bAutoRelease;
};


}//end of namespace bluemei