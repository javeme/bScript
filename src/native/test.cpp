#include "StdAfx.h"
#include "NativeObjectGroup.h"
#include "BSContext.h"

class TestObjectBase : public Object
{
public:
	DECLARE_DCLASS(TestObjectBase);
};
class TestObject : public TestObjectBase
{
public:
	DECLARE_DCLASS(TestObject);
public:
	virtual void test(){}
};

Object* test()
{
	return nullptr;
}
void testNativeObj()
{
	NativeClass* pNativeClass=new NativeClass(TestObject::thisClass());
	pNativeClass->addFunction("test()",FunctorRegister::buildNativeFunction("test()",test,typeid(test)));

	NativeObjectGroup *pNativeObjectGroup=new NativeObjectGroup();
	pNativeObjectGroup->registerClass(pNativeClass);

	NativeObject* pNativeObject=new NativeObject(pNativeClass);
	TestObject* tObj=new TestObject();
	pNativeObject->attachLocalObj("tObj",tObj);
	pNativeObjectGroup->putObject(pNativeObject);

	pNativeObjectGroup->registerLocalObj("tObj2",tObj);

	String objName="tObj";
	String funcName="test()";
	pNativeObjectGroup->getObject(objName)->invoke(funcName);

	pNativeObject->detachLocalObj();
	delete pNativeObjectGroup;
}