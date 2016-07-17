#pragma once
#include "StdAfx.h"
#include "FunctorManager.h"

namespace bluemei{

bool operator<(const String& key1,const String& key2)
{	
	if(strcmp(key1.c_str(),key2.c_str())<0)  
		return true;  
	else  
		return false;  
} 

void FunctorManager::returnBackFunc( NativeFunction* fun )
{
	if(fun!=nullptr && fun->getCallType()==thisCall)
		fun->resetThisPtrAndUnlock();
}

void FunctorManager::addFunctor( NativeFunction* pFun )
{
	if(pFun!=nullptr)
	{
		m_nativeFunctionMap.insert(std::make_pair(pFun->getFuncName(),pFun));
	}
}

void FunctorManager::removeFunctorByName( const String& name )
{
	auto itor=m_nativeFunctionMap.find(name);
	if(itor!=m_nativeFunctionMap.end())
	{
		m_nativeFunctionMap.erase(itor);
	}
}

void FunctorManager::clearAll()
{
	m_nativeFunctionMap.clear();
}

NativeFunction* FunctorManager::findFunctorByName( const String& name )
{
	int pos=name.find(".");//obj.test()
	if(pos>0)
	{
		String objName=name.getLeftSub(pos);
		String funName=name.getRightSub(name.length()-pos-1);
		NativeObject* pNativeObject=this->m_nativeObjectGroup.getObject(objName);
		NativeFunction* fun=pNativeObject->getThisNativeClass()->findFunction(funName);

		if(fun->getCallType()!=thisCall)//对象调用
			throwpe(Exception("can't call by object"));
		fun->setThisPtrAndLock(pNativeObject->getThisObject());

		return fun;
	}
	else
	{			
		auto itor=m_nativeFunctionMap.find(name);
		if(itor!=m_nativeFunctionMap.end())
		{
			return itor->second;
		}
		return nullptr;
	}
}

void FunctorManager::addMemberFunctor( const Class* pClass,NativeFunction* pFun ) throw(Exception)
{
	if(pClass==nullptr || pFun==nullptr)
	{
		throwpe(Exception("class or function is null."));
	}
	else if(!pFun->belongToClass(pClass))
	{
		throwpe(Exception("the function does not belong to the class."));
	}
	NativeClass* pNativeClass=m_nativeObjectGroup.getClass(pClass->getName());
	if(pNativeClass==nullptr)
	{
		pNativeClass=new NativeClass(pClass);
		m_nativeObjectGroup.registerClass(pNativeClass);
	}
	pNativeClass->addFunction(pFun->getFuncName(),pFun);
}

NativeObject* FunctorManager::findObject( const String& name )
{
	int pos=name.find(".");//obj.test()
	String objName;
	if(pos>0)
	{
		objName=name.getLeftSub(pos);
	}
	else
		objName=name;
	return this->m_nativeObjectGroup.getObject(objName);
}

FunctorManager* FunctorManager::getInstance()
{
	static FunctorManager fm;
	return &fm;
}

}//end of namespace bluemei