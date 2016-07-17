#pragma once
#include "FunctorManager.h"

namespace bluemei{

class BSContext : public Object
{
public:
	static BSContext* getInstance()
	{
		static BSContext ctx;
		return &ctx;
	}
protected:
	BSContext()
	{
		m_pFunctorManager=FunctorManager::getInstance();
	}
	virtual ~BSContext(){}
public:
	FunctorManager* getFunctorManager()
	{
		return m_pFunctorManager;
	}
protected:
	FunctorManager* m_pFunctorManager;
};


}//end of namespace bluemei