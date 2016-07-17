#pragma once
#include "Expression.h"
#include "InstructionVisitor.h"
#include "StringBuilder.h"
#include "StackFrame.h"

namespace bluemei{

class Sequence : public Instruction
{
public:
	Sequence(){
		expr=nullptr;
		nextSequence=nullptr;
	}
	virtual ~Sequence(){
		delete expr;
		delete nextSequence;
	}
public:
	virtual bool accept(InstructionVisitor* visitor)
	{
		return visitor->visit(this);
	}
	virtual String getText() const
	{
		if (expr!=nullptr)
		{
			String str=expr->getText();
			StringBuilder sb(str.length()*20);

			//String::format("%s;",str.c_str());
			sb.append(str);
			sb.append(STR_SEMI);
			sb.append(STR_BR);

			if (nextSequence!=nullptr)
			{
				str=nextSequence->getText();
				sb.append(str);
			}
			return sb.toString();
		}
		return STR_NULL;
	}
public:
	virtual LanguageNode* getLeftNode() const { return getExpression(); }
	virtual void setLeftNode(LanguageNode* val) { setExpression(dcast<Expression>(val)); }

	virtual LanguageNode* getRightNode() const { return getNextSequence(); }
	virtual void setRightNode(LanguageNode* val) { setNextSequence(dcast<Sequence>(val)); }

	virtual bool hasLeft() const { return expr!=nullptr; }
	virtual bool hasRight() const { return nextSequence!=nullptr; }

	virtual int precedence() const { return PD_SEQUENCE; }
public:
	Expression* getExpression() const { return expr; }
	void setExpression(Expression* val) { expr = val; }

	Sequence* getNextSequence() const { return nextSequence; }
	void setNextSequence(Sequence* val) { nextSequence = val; }
protected:
	Expression* expr;
	Sequence* nextSequence;//下一条语句
};

class Statment : public Instruction
{
public:
	Statment(){
		sequence=nullptr;
	}
	virtual ~Statment(){
		delete sequence;
	}
public:
	virtual bool accept(InstructionVisitor* visitor)
	{
		return visitor->visit(this);
	}
	virtual String getText() const
	{
		if (sequence!=nullptr)
		{
			String str=sequence->getText();
			StringBuilder sb(str.length()*1.2);

			sb.append(STR_LBRACE);
			sb.append(STR_BR);

			sb.append(str);

			sb.append(STR_RBRACE);
			sb.append(STR_BR);

			return sb.toString();
		}
		return STR_NULL;
	}
public:
	virtual LanguageNode* getRightNode() const { return getSequence(); }
	virtual void setRightNode(LanguageNode* val) { setSequence(dcast<Sequence>(val)); }

	virtual bool hasRight() const { return sequence!=nullptr; }

	virtual int precedence() const { return PD_STATMENT; }
public:
	Sequence* getSequence() const { return sequence; }
	void setSequence(Sequence* val) { sequence = val; }
protected:
	Sequence* sequence;
};

class Method : public Instruction
{
public:
	Method(cstring name):methodName(name),stackFrame(16){
		stmt=nullptr;
	}
	virtual ~Method(){
		delete stmt;
	}
public:
	virtual bool accept(InstructionVisitor* visitor)
	{
		return visitor->visit(this);
	}
	virtual String getText() const
	{
		if (stmt!=nullptr)
		{
			String str=stmt->getText();
			StringBuilder sb(str.length()*1.2);
			
			sb.append(methodName);
			;
			sb.append(str);
			;
						
			return sb.toString();
		}
		return STR_NULL;
	}
public:
	virtual LanguageNode* getRightNode() const { return getStatment(); }
	virtual void setRightNode(LanguageNode* val) { setStatment(dcast<Statment>(val)); }

	virtual bool hasRight() const { return stmt!=nullptr; }

	virtual int precedence() const { return PD_METHOD; }
public:
	Statment* getStatment() const { return stmt; }
	void setStatment(Statment* val) { stmt = val; }

	String getMethodName() const { return methodName; }
	void setMethodName(cstring val) { methodName = val; }

	StackFrame* getStackFrame() { return &stackFrame; }
protected:
	Statment* stmt;
	
	String methodName;
	StackFrame stackFrame;
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
	Sequence* rightSequence;//一般不存在
};*/

}//end of namespace bluemei

