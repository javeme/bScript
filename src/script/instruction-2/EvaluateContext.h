#pragma once
#include "Expression.h"
#include "InstructionVisitor.h"

namespace bluemei{

class EvaluateVisitor;

class StackFrame : public Object
{
public:
	StackFrame(){}
	virtual ~StackFrame(){}
public:
protected:
};

class BSContext : public Object{};
class EvaluateContext : public BSContext
{
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

