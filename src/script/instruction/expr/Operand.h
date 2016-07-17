#pragma once
#include "Expression.h"
#include "ExpressionVisitor.h"
#include "Number.h"

namespace bluemei{

static const cstring DEFAULT_NAME="var";

class Operand : public Expression
{
public:
	Operand(cstring name):varName(name){}
	virtual ~Operand(){}
public:
	virtual int precedence() const { return PD_OPERAND; }
public:
	String getVarName() const { return varName; }
	void setVarName(String val) { varName = val; }
protected:
	String varName;
};

class OperandNumber : public Operand
{
public:
	OperandNumber(Number* val=nullptr,cstring name=DEFAULT_NAME):Operand(name),number(val){}
	OperandNumber(int val):Operand(DEFAULT_NAME),number(new Integer(val)){}
	OperandNumber(lint val):Operand(DEFAULT_NAME),number(new Long(val)){}
	OperandNumber(float val):Operand(DEFAULT_NAME),number(new Float(val)){}
	OperandNumber(double val):Operand(DEFAULT_NAME),number(new Double(val)){}
	OperandNumber(const Number& val):Operand(DEFAULT_NAME){ number=val.toThisType(&val); }
	virtual ~OperandNumber(){
		delete number;
	}

	virtual OperandNumber& operator=(const OperandNumber& operand)
	{
		Object* obj=operand.number->clone();
		Number* newNum=dcast<Number>(obj);
		if(newNum==nullptr){
			delete obj;
			throwpe(Exception("conv to OperandNumber failed"));
		}
		delete number;
		number=newNum;
		return *this;
	}
public:
	virtual Expression* acceptExpr(ExpressionVisitor* visitor)
	{
		checkNullPtr(visitor);
		return visitor->visitExpr(this);
	}
	virtual String getText() const
	{
		StringBuilder sb(varName.length()+10);
		sb.append(varName);//varName.length()==0

		String str=STR_NULL;
		if (number!=nullptr)
			str=number->toString();
		sb.append("(value=");
		sb.append(str);
		sb.append(')');

		return sb.toString();
	}
public:
	Number* getNumber() const { return number; }
	void setNumber(Number* val) { number = val; }
protected:
	Number* number;
};

class OperandRefrence : public Operand
{
public:
	OperandRefrence(Object* val=nullptr,cstring name=DEFAULT_NAME):Operand(name),refrence(val){}
	virtual ~OperandRefrence(){
		delete refrence;
	}
public:
	virtual Expression* acceptExpr(ExpressionVisitor* visitor)
	{
		checkNullPtr(visitor);
		return visitor->visitExpr(this);
	}
public:
	Object* getRefrence() const { return refrence; }
	void setRefrence(Object* val) { refrence = val; }
protected:
	Object* refrence;
};
}//end of namespace bluemei

