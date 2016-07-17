#pragma once
#include "Executeable.h"
#include "OpValueType.h"
#include "BString.h"
#include "BScriptUtil.h"

namespace bluemei{

//template<int paraNum=0>
class Function : public Executeable
{	
public:
	Function(const String& name="")
	{
		exeCount=0;
		callType=CallType::cdeclCall;
		funcName=name;
	}
protected:
	String funcName;
	List<ValueTypeObject> paraInTypes;
	ValueTypeObject returnParaType;
	CallType callType;
	int exeCount;
public:
	virtual void execute(){
		exeCount++;
	};

public:
	String getFuncName() const { return funcName; }
	void setFuncName(String val) { funcName = val; }

	void setReturnType(const ValueTypeObject& t){ returnParaType=t; }
	ValueTypeObject getReturnType(){ return returnParaType; }

	void addParaType(const ValueTypeObject& t){ if(exeCount==0)paraInTypes.push_back(t);}
	List<ValueTypeObject> getParaTypes(){return paraInTypes;}

	CallType getCallType() const { return callType; }
	void setCallType(CallType val) { callType = val; }	
};

typedef void (*Fun)();
union DataValue{int i; long long li; float f; double df;};

}//end of namespace bluemei