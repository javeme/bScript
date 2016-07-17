#pragma once
#include "Object.h"

namespace bluemei{

class Method	;
class Statment	;
class Sequence	;
class Expression;

//节点优先级
enum NodePrecedence{
	PD_LOWEST		= 0		,

	PD_METHOD		= 100	,//Method
	PD_SEQUENCE		= 200	,//Sequence
	PD_STATMENT		= 300	,//Statment

	PD_OPERTOR		= 1000	,//1000-9999为Operator预留

	PD_OPERAND		= 10000	,//Operand

	PD_HIGHEST		= 65535	,
};

class InstructionVisitor : public Object
{
public:
	InstructionVisitor(){}
	virtual ~InstructionVisitor(){}
public:
	virtual bool visit(Method*	 node)=0;
	virtual bool visit(Statment* node)=0;
	virtual bool visit(Expression* node)=0;	
};

}//end of namespace bluemei

