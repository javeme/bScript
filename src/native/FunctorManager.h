#pragma once
#include "NativeObjectGroup.h"
#include "SmartPtr.h"

namespace bluemei{

bool operator<(const String& key1,const String& key2);

class FunctorManager : public Object
{
public:
	static FunctorManager* getInstance();
protected:
	FunctorManager(){}
	virtual ~FunctorManager(){ clearAll(); }
public:
	void addFunctor(NativeFunction* pFun);
	void removeFunctorByName(const String& name);
	void clearAll();

	NativeFunction* findFunctorByName(const String& name);
	void returnBackFunc(NativeFunction* fun);

	void addMemberFunctor(const Class* pClass,NativeFunction* pFun)throw(Exception);
	NativeObject* findObject(const String& name);
	NativeObjectGroup* getNativeObjectGroup(){ return &m_nativeObjectGroup; }
protected:
	Map<String,SmartPtr<NativeFunction>> m_nativeFunctionMap;
	NativeObjectGroup m_nativeObjectGroup;
};

class FunctorRegister : public Object
{
public:
	FunctorRegister(cstring name,void*p,const type_info& info,const Class* pClass=nullptr)
	{
		//m_strFunName=name;
		//m_pFun=p;
		NativeFunction* pFun=nullptr;
		try{
			pFun=(buildNativeFunction(name,p,info,pClass));

			auto pManager=FunctorManager::getInstance();
			if(pFun->getCallType()==CallType::thisCall){
				pManager->addMemberFunctor(pClass,pFun);
			}
			else
				pManager->addFunctor(pFun);
		}catch(...){
			delete pFun;
			throw;
		}
	}
public:
	static NativeFunction* buildNativeFunction(cstring name,void*p,const type_info& info,const Class* pClass=nullptr)
	{
		NativeFunction* pFun=new NativeFunction(name,p);
		
		try{
			String strFunInfo=info.name();//void __cdecl(class String,int)
			String strTmp;
			int start=0,end=0;
			//返回类型
			strFunInfo=strFunInfo.trim();
			end=strFunInfo.find("__",start);
			strTmp=strFunInfo.substring(start,end-start-1);
			//m_returnType=parseType(strTmp);
			pFun->setReturnType(parseType(strTmp));
			//调用方式
			start=end;
			end=strFunInfo.find("(",start);
			strTmp=strFunInfo.substring(start,end-start);
			//m_callType=parseCallType(strTmp);
			pFun->setCallType(parseCallType(strTmp));
			//参数类型
			while(true)
			{
				start=end+1;
				end=strFunInfo.find(",",start);
				if(end>0)
				{
					strTmp=strFunInfo.substring(start,end-start);
					//m_paraTypes.push_back(parseType(strTmp));
					pFun->addParaType(parseType(strTmp));
				}
				else
				{
					strTmp=strFunInfo.substring(start,strFunInfo.length()-start-1);
					//m_paraTypes.push_back(parseType(strTmp));
					pFun->addParaType(parseType(strTmp));
					break;
				}
			}
		}catch(...){
			delete pFun;
			throw;
		}
		return pFun;
	}
	static OpValueType parseType(String str)throw(Exception)
	{
		OpValueType t=OpValueType::OPT_UNKNOWN;

		if(str.contain("&") || str.contain("*"))
		{
			t=OpValueType::PTR4;
		}
		else if(str.contain("class"))//class String
		{
			throwpe(Exception("Not supported. Please pass the object by reference or pointer."));
		}
		else 
		{
			if(str.contain("void"))
				t=OpValueType::OPT_VOID;
			else if(str.contain("short") || str.contain("wchar_t"))
				t=OpValueType::INT2;
			else if(str.contain("char") || str.contain("bool") || str.contain("byte"))
				t=OpValueType::INT1;
			else if(str.contain("__int64"))
				t=OpValueType::LONG8;
			else if(str.contain("long double"))
				t=OpValueType::LONG_DOUBLE16;
			else if(str.contain("int") || str.contain("long"))
				t=OpValueType::INT4;
			else if(str.contain("float"))
				t=OpValueType::FLOAT4;
			else if(str.contain("double"))
				t=OpValueType::DOUBLE8;
		}

		return t;
	}
	static CallType parseCallType(String str)
	{
		CallType t=cdeclCall;
		if(str.contain("__cdecl"))
			t=cdeclCall;
		else if(str.contain("__stdcall"))
			t=stdCall;
		else if(str.contain("__fastcall"))
			t=fastCall;
		else if(str.contain("__thiscall"))
			t=thisCall;
		else if(str.contain("__nakedcall"))
			t=nakedCall;
		
		return t;
	}
/*
protected:
	String m_strFunName;
	void* m_pFun;
	OpValueType m_returnType;
	List<OpValueType> m_paraTypes;
	CallType m_callType;*/
};

#define functor(func) \
	/*void * p=func;decltype(func)*/\
	static FunctorRegister function_##func(CODE2STRING(func),func,typeid(func));

#define object(member_func)\
	static FunctorRegister memberfun_##member_func \
		(CODE2STRING(member_func),getType<Fun>(&member_func),typeid(&member_func));

#define mfunctor(cls,member_func)\
	static FunctorRegister memberfun_##cls##_##member_func \
		(CODE2STRING(cls::member_func),getType<Fun>(&cls::member_func),typeid(&cls::member_func),cls::thisClass());

}//end of namespace bluemei