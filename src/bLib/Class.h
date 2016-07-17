#ifndef Class_H_H
#define Class_H_H
#include "bluemeiLib.h"

namespace bluemei{

#define null nullptr

typedef const char* cstring;
typedef unsigned char byte;

class Object;
class RuntimeException;

//��������������
typedef Object* CreateFun(void);

//�������ඨ��
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
	bool isMyObject(Object* pObj)const;//�Ƿ���Ǳ���ʵ��
	bool isMyInstance(Object* pObj)const;//�Ƿ����ڱ���ʵ��
public:
	static const Class* undefined(){ static Class cls; return &cls; };
	static void throwRuntimeException(cstring msg) throw(RuntimeException);
protected:
	std::string name;
	CreateFun* m_pCreateFun;
	const Class* superClassRef;
	Object* m_pInitPara;
};

//�ַ�����
#define _T2STR(type) #type
//��ȡ������
#define CLASS(className)\
	Class(_T2STR(className),className::createObject)
#define NEW_CLASS(className)\
	new Class(_T2STR(className),className::createObject)


}//end of namespace bluemei
#endif