#pragma once
#include "Function.h"

class Method : public Function
{
protected:
	StackFrame stackFrame;
	List<Instruction*> instList;
public:
	Method(int localVarNum):stackFrame(localVarNum){
		stackFrame.setMethod(this);
	}
	virtual~ Method()
	{
		for(auto i=instList.begin();i!=instList.end();i++)
			delete (*i);
		instList.clear();
	}
	virtual void addIntInstruction(Instruction* p)
	{
		instList.push_back(p);
	}
	StackFrame* getStackFrame()
	{
		return &stackFrame;
	}
	virtual void execute(){
		__super::execute();
		for(auto i=instList.begin();i!=instList.end();i++)
			(*i)->execute();
	};
};