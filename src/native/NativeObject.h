#pragma once
#include "Object.h"
#include "BString.h"
#include "NativeClass.h"

namespace bluemei{

class NativeObject : public Object
{
public:
	DECLARE_DCLASS(NativeObject);
public:
	NativeObject(void);
	NativeObject(NativeClass* pClass);
	virtual ~NativeObject(void);
public:
	String getThisName() const { return m_strThisName; }
	void setThisName(const String& val) { m_strThisName = val; }
	
	Object* getThisObject() const { return m_pThisObject; }
	void setThisObject(Object* val) { m_pThisObject = val; }
	
	NativeClass* getThisNativeClass() const { return m_pThisClassRef; }
	void setThisNativeClass(NativeClass* val) { m_pThisClassRef = val; }

public:
	virtual void attachLocalObj(const String& name,Object* pObject);
	virtual Object* detachLocalObj();
	virtual void invoke(const String& func);
protected:
	String m_strThisName;
	Object* m_pThisObject;
	NativeClass* m_pThisClassRef;
};



}//end of namespace bluemei