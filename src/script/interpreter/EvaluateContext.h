#pragma once
#include "BSContext.h"
#include "Expression.h"
#include "InstructionVisitor.h"
#include "StackFrame.h"

namespace bluemei{

class EvaluateVisitor;

class EvaluateContext : public BSContext
{
public:
	EvaluateContext(){
		visitor=nullptr;
		stackFrame=nullptr;
	}
	virtual ~EvaluateContext(){
		delete visitor;
		delete stackFrame;
	}
public:
	EvaluateVisitor* getVisitor() const { return visitor; }
	void setVisitor(EvaluateVisitor* val) { visitor = val; }

	StackFrame* getStackFrame() const { return stackFrame; }
	void setStackFrame(StackFrame* val) { stackFrame = val; }
protected:
	EvaluateVisitor* visitor;
	StackFrame* stackFrame;
};

}//end of namespace bluemei

