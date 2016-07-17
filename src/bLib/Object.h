#ifndef Object_H_H
#define Object_H_H
#include "bluemeiLib.h"
#include "Class.h"


namespace bluemei{

class String;

//声明为可动态创建类
#define DECLARE_DCLASS(className) \
	static const Class* thisClass(){														   \
		static Class theClass(_T2STR(className),className::createObject,__super::thisClass()); \
		return &theClass;																	   \
	}																						   \
	static Object* createObject(){ return new className();}									   \
	virtual Object* clone()const{ return new className(*this);}								   \
	virtual const Class* getThisClass()const{ 												   \
		const Class* cls=thisClass();														   \
		static int checked=0;/*0: un checked, -1: checked failed, -1: checked success*/		   \
		if(checked==0)																		   \
		{																					   \
			checked=-1;																		   \
			cstring objClassName=typeid(*this).name();										   \
			const static size_t LEN=strlen("class ");										   \
			if(strlen(objClassName)>LEN)													   \
			{																				   \
				if(strcmp(objClassName+LEN,cls->getName())==0)								   \
					checked=1;																   \
			}																				   \
		}																					   \
		if(checked==-1)																		   \
		{																					   \
			Class::throwRuntimeException("Class not matched");								   \
			return Class::undefined();														   \
		}																					   \
		else																				   \
			return cls;																		   \
	}							   															   \
//end of DECLARE_DCLASS

//对象类
class BLUEMEILIB_API Object
{
public:
	class SuperObj{public: static const Class* thisClass(){return nullptr;}};
	#define __super SuperObj
	DECLARE_DCLASS(Object);
	#undef __super
public:
	Object();
	virtual ~Object();

	virtual void init(Object *pObj){
		;
	}
	//virtual string toString();
	virtual String toString()const;
};


}//end of namespace bluemei
#endif