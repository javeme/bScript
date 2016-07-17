#pragma once
#include "Function.h"
#include "CriticalLock.h"
#include "DataBuffer.cpp"

namespace bluemei{

#define PUT_THIS(v) /*_asm push ecx*/	_asm mov ecx,dword ptr[v]
#define PUSH_INT4(v) _asm push v
#define PUSH_FLOAT4(v) _asm push v
#define PUSH_FLOAT8(v) _asm fld v	_asm sub esp,8	_asm fstp qword ptr[esp]
#define CALL_FUN(addr) _asm call addr
#define POP(v) _asm add esp,v
#define INT4_RESULT(v) _asm mov dword ptr[v],eax
#define INT8_RESULT(v) _asm mov dword ptr[v],eax	_asm mov dword ptr[v]+4,edx
#define FLOAT4_RESULT(v) _asm fstp dword ptr [v]
#define FLOAT8_RESULT(v) _asm fstp qword ptr [v]

template<typename DST,typename SRC>
DST getType(SRC src)
{
     union
     {
        DST dst;
        SRC src;
     }un_type;
     un_type.src = src;
     return un_type.dst;
}

//待改为:利用不依赖于本地编译器的模板函数对象,利用List<void*>来传递参数及返回值.
class NativeFunction : public Function
{
public:
	NativeFunction(const String& name="",void* funAddr=nullptr) : Function(name)
	{
		funAddres=funAddr;
		thisPtr=nullptr;
	}
	virtual void setNativeFunAddres(void* funAddr){ 
		funAddres=funAddr;
	}	
	virtual void* getNativeFunAddres(){ 
		return funAddres;
	}
	virtual bool belongToClass(const Class* pClass){		
		String thisClassName=this->funcName.getLeftSub(funcName.find("::"));
		return thisClassName==pClass->getName();
	}
	
	void* getThisPtr() const { return thisPtr; }
	void setThisPtrAndLock(void* val) { 
		m_lock.getLock();
		thisPtr = val; 
	}
	void resetThisPtrAndUnlock(){
		thisPtr=nullptr;
		m_lock.releaseLock();
	}
protected:
	void* funAddres;
	void* thisPtr;
	CriticalLock m_lock;
	DataBuffer<String> inStack;
	String returnValue;
public:
	void push(const String& v)
	{
		inStack.put(v);
	}
	String getResult()
	{
		return returnValue;
	}
	
	virtual void execute(){
		m_lock.getLock();
		__super::execute();

		Fun fun=(Fun)this->funAddres;
		int i4=0;
		long long li=0;
		float f=0;
		double df=0;

		if(callType==fastCall || callType==nakedCall)
			throw(Exception("not supported call type."));		
		
		//压栈
		int count=0;
		for(auto i=paraInTypes.rbegin();i!=paraInTypes.rend();i++)
		{
			auto& para=*i;
			switch(para.getType())
			{
				case INT1:
				case INT2:
				case INT4:
				case PTR4:{
					i4=BScriptUtil::str2Int(inStack.pop());
					PUSH_INT4(i4);
					count+=4;
					break;
				}
				case LONG8:{
					i4=BScriptUtil::str2Int(inStack.pop());
					PUSH_INT4(i4);
					i4=BScriptUtil::str2Int(inStack.pop());
					PUSH_INT4(i4);
					count+=8;
					break;	
			    }
				case FLOAT4:
				{
					f=BScriptUtil::str2Float(inStack.pop());
					PUSH_FLOAT4(f);
					count+=4;
					break;
				}
			
				case DOUBLE8:
				{
					df=BScriptUtil::str2Float(inStack.pop());
					PUSH_FLOAT8(df);
					count+=8;
					break;
				}
			}
		}
		if(callType==stdCall)
			count=0;
		else if(callType==thisCall){
			count=0;
			void *thisPtrTmp=thisPtr;
			PUT_THIS(thisPtrTmp);//直接使用thisPtr会被优化掉?奇怪!
		}
		//执行
		CALL_FUN(fun);
		//弹栈
		POP(count);
			
		//取返回值
		INT8_RESULT(li);
		switch(returnParaType.getType())
		{
			case INT1:
			case INT2:
			case INT4:
			case PTR4:{
				i4=li;
				returnValue=String::format("%d",i4);
				break;
			}
			case LONG8:{
				returnValue=String::format("%ld",li);
				break;	
			}
			case FLOAT4:
			{
				FLOAT4_RESULT(f);				
				returnValue=String::format("%f",f);
				break;
			}
			
			case DOUBLE8:
			{
				FLOAT8_RESULT(df);	
				returnValue=String::format("%lf",df);
				break;
			}

		}
		m_lock.releaseLock();
	}
};


}//end of namespace bluemei