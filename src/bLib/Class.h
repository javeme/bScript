#ifndef Class_H_H
#define Class_H_H
#include "bluemeiLib.h"

namespace bluemei{

#define null nullptr

typedef const char* cstring;
typedef unsigned char byte;

class Object;
class RuntimeException;

//创建对象函数声明
typedef Object* CreateFun(void);

//类描述类定义
class BLUEMEILIB_API Class
{
public:
	Class();
	Class(cstring name,CreateFun* pFun,const Class* superClass=nullptr);
	virtual ~Class(){};
public:
	Object* createObject()const;
	cstring getName()const;
	bool operator==(const Class& other)const;
	const Class* superClass() const { 
		return superClassRef; 
	}

	Object* getInitPara() const { 
		return m_pInitPara; 
	}
	void setInitPara(Object* val) { 
		m_pInitPara = val;
	}
	bool isMyObject(Object* pObj)const;//是否就是本类实例
	bool isMyInstance(Object* pObj)const;//是否属于本类实例
public:
	static const Class* undefined(){ static Class cls; return &cls; };
	static void throwRuntimeException(cstring msg) throw(RuntimeException);
protected:
	std::string name;
	CreateFun* m_pCreateFun;
	const Class* superClassRef;
	Object* m_pInitPara;
};

//字符串化
#define _T2STR(type) #type
//获取反射类
#define CLASS(className)\
	Class(_T2STR(className),className::createObject)
#define NEW_CLASS(className)\
	new Class(_T2STR(className),className::createObject)


}//end of namespace bluemei
#endif