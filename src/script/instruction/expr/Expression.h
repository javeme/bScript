#pragma once
#include "Instruction.h"
#include "InstructionVisitor.h"

namespace bluemei{

class ExpressionVisitor;

static const cstring STR_SPACE	= " " ;
static const cstring STR_BR		= "\n";
static const cstring STR_TAB	= "\t";

static const cstring STR_SEMI	= ";";
static const cstring STR_COMMA	= ",";
static const cstring STR_LBRACE	= "{";
static const cstring STR_RBRACE	= "}";
static const cstring STR_NULL	= "null";


class Expression : public Instruction
{
public:
	Expression(){}
	virtual ~Expression(){}
public:
	virtual bool accept(InstructionVisitor* visitor)
	{
		return visitor->visit(this);
	}

	virtual Expression* acceptExpr(ExpressionVisitor* visitor)=0;

public:
	virtual Expression* evaluate(ExpressionVisitor* visitor) { return acceptExpr(visitor); }
/*	
public:
	virtual String getText() const
	{
		if (expr!=nullptr)
		{
			return expr->getText();
		}
		return STR_NULL;
	}
protected:
	Expression* expr;*/
};

}//end of namespace bluemei

