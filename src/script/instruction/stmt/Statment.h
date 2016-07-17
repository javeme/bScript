#pragma once
#include "Expression.h"
#include "InstructionVisitor.h"
#include "StringBuilder.h"

namespace bluemei{

class StatmentVisitor;

class Statment : public Instruction
{
public:
	Statment(){
		;
	}
	virtual ~Statment(){
		;
	}
public:
	virtual bool accept(InstructionVisitor* visitor)
	{
		checkNullPtr(visitor);
		return visitor->visit(this);
	}	
	virtual int precedence() const { return PD_STATMENT; }
public:
	virtual bool acceptStmt(StatmentVisitor* visitor)=0;
};


/*
class Sequence : public Instruction
{
public:
	Sequence(){
		leftExpr=nullptr;
		rightExpr=nullptr;
	}
	virtual ~Sequence(){
		delete leftExpr;
		delete rightExpr;
	}
public:
	virtual bool accept(InstructionVisitor* visitor)
	{
		bool success=false;
		if (leftExpr!=nullptr)
		{
			success=visitor->visit(leftExpr);
			if (rightExpr!=nullptr)
			{
				success=visitor->visit(rightExpr);
			}
		}
		return success;
	}

	virtual String getText() const
	{
		if (leftExpr!=nullptr)
		{
			String str=leftExpr->getText();
			if (rightExpr!=nullptr)
			{
				str=String::format("%s%s%s",str.c_str(),STR_BR,leftExpr->getText().c_str());
			}
			return str;
		}
		return STR_NULL;
	}
public:
	Expression* getLeftExpression() const { return leftExpr; }
	void setLeftExpression(Expression* val) { leftExpr = val; }

	Expression* getRightExpression() const { return rightExpr; }
	void setRightExpression(Expression* val) { rightExpr = val; }
protected:
	Expression* leftExpr;
	Expression* rightExpr;
};

class Statment : public Instruction
{
public:
	Statment(){
		leftSequence=nullptr;
		rightSequence=nullptr;
	}
	virtual ~Statment(){
		delete leftSequence;
		delete rightSequence;
	}
public:
	virtual bool accept(InstructionVisitor* visitor)
	{
		return visitor->visit(this);
	}
	virtual String getText() const
	{
		if (leftSequence!=nullptr)
		{
			String str=leftSequence->getText();
			StringBuilder sb(str.length()*4);
			sb.append(str);
			sb.append(STR_BR);
			if (rightSequence!=nullptr)
			{
				str=rightSequence->getText();
				sb.append(str);
				sb.append(STR_BR);
			}
			return sb.toString();
		}
		return STR_NULL;
	}
	virtual int precedence() const { return PD_STATMENT; }
public:
	Sequence* getLeftSequence() const { return leftSequence; }
	void setLeftSequence(Sequence* val) { leftSequence = val; }

	Sequence* getRightSequence() const { return rightSequence; }
	void setRightSequence(Sequence* val) { rightSequence = val; }
protected:
	Sequence* leftSequence;
	Sequence* rightSequence;//Ò»°ã²»´æÔÚ
};*/

}//end of namespace bluemei

