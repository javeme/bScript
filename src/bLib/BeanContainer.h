#pragma once
#include "bluemeiLib.h"
#include "Object.h"

namespace bluemei{

using std::string;
typedef std::map<string,Object*> ObjectMap;

class BLUEMEILIB_API BeanContainer : public Object
{
public:
	BeanContainer(void);
	virtual ~BeanContainer(void);
protected:
	BeanContainer(const BeanContainer& other){
		*this=other;
	};
	BeanContainer& operator=(const BeanContainer& other){
		__super::operator=(other);
		m_beanMap=other.m_beanMap;
		return *this;
	};
public:
	bool put(const string& key,Object* pBean);
	/*bool put(const char* key,Object* pBean){
		return put(string(key),pBean);
	}*/
	Object* get(const string& key)const;
	Object* remove(const string& key);
	bool remove(Object* pBean);
	
	int size()const{ return m_beanMap.size(); };

	virtual void clear(bool autoRelease=true);
protected:
	ObjectMap m_beanMap;
};

}//end of namespace bluemei