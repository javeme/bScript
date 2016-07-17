#pragma once
#include "stdafx.h"
#include "EvaluateVisitor.h"
#include "SimpleStatment.h"
#include "SequenceStatment.h" 
#include "Operator.h"
#include "Operand.h"

namespace bluemei{

class StandardEvaluateVisitor : public EvaluateVisitor
{
public:
	StandardEvaluateVisitor(EvaluateContext* ctx):EvaluateVisitor(ctx){}
	virtual ~StandardEvaluateVisitor(){}
protected:	
	void checkOperandNumberNull(OperandNumber* operand)throw(NullPointerException)
	{
		if (operand==nullptr || operand->getNumber()==nullptr)
			throwpe(NullPointerException("evaluate number is null"));
	}
	void checkOperandNull(Expression* operand)throw(NullPointerException)
	{
		if (operand==nullptr)
			throwpe(NullPointerException("evaluate operand is null"));
	}
protected:	
	OperandNumber* evaluateNumber(OperandNumber* operand1,OperandNumber* operand2,NumberVisiter& visitor)
	{
		checkOperandNumberNull(operand1);

		Number* num1=operand1->getNumber();
		Number* num2=(operand2==nullptr)?nullptr:operand2->getNumber();

		//比较优先级
		if(num2==nullptr || num1->precedence()>=num2->precedence()){
			//Number* numLow=num1->toThisType(num2);
			num1->accept(&visitor,num2);
		}
		else{
			std::auto_ptr<Number> numHigh(num2->toThisType(num1));
			numHigh->accept(&visitor,num2);
		}
		return new OperandNumber(visitor.detachResult());		
	}
	OperandNumber* evaluateAssign(OperandNumber* operand1,OperandNumber* operand2,NumberVisiter& visitor)
	{
		checkOperandNumberNull(operand1);
		checkOperandNumberNull(operand2);

		Number* num1=operand1->getNumber();
		Number* num2=operand2->getNumber();

		//赋值语句不需要比较优先级
		num1->accept(&visitor,num2);		
		return new OperandNumber(visitor.detachResult());		
	}

public:
	virtual bool visitStmt(SimpleStatment			* node){ 
		checkNullPtr(node);
		
		bool success=false;
		Expression* expr=node->getExpression();
		if(expr!=nullptr)
		{
			success=expr->accept(this);
		}
		return success;
	}
	virtual bool visitStmt(SequenceStatment			* node){ 
		checkNullPtr(node);
		
		bool success=true;
		LinkedList<Statment*> list=node->getStmtList();
		auto i=list.iterator();
		while (i->hasNext())
		{
			Statment* stmt=i->next();

			success=(success && stmt->accept(this));
		}
		list.releaseIterator(i);

		return success;
	}
														  
	virtual bool visitStmt(IfElseStatment	   		* node){ return false; }
	virtual bool visitStmt(SwitchCaseStatment  		* node){ return false; }
	virtual bool visitStmt(WhileStatment	   		* node){ return false; }
	virtual bool visitStmt(DoWhileStatment	   		* node){ return false; }
	virtual bool visitStmt(ForStatment	   			* node){ return false; }
														  
	virtual bool visitStmt(ReturnStatment	   		* node){ return false; }
	virtual bool visitStmt(BreakStatment	   		* node){ return false; }
	virtual bool visitStmt(ContinueStatment	   		* node){ return false; }
public:
	virtual Expression* visitExpr(OperatorAdd			* node){ 
		checkNullPtr(node);
		String t=node->getText();
		Expression* op1=node->getLeftOperand();
		Expression* op2=node->getRightOperand();
		checkOperandNull(op1);
		checkOperandNull(op2);		
		op1=op1->evaluate(this);//计算左子结果(共用this访问)
		op2=op2->evaluate(this);//计算右子结果(共用this访问)
		checkOperandNull(op1);
		checkOperandNull(op2);	
		OperandNumber* operand1=dynamic_cast<OperandNumber*>(op1);
		OperandNumber* operand2=dynamic_cast<OperandNumber*>(op2);		
		checkOperandNumberNull(operand1);
		checkOperandNumberNull(operand2);
		NumberAddVisiter add;
		OperandNumber* result=evaluateNumber(operand1,operand2,add);//运算
		return result;
	}
	virtual Expression* visitExpr(OperatorSub			* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorMul			* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorDiv			* node){ return nullptr; }

	virtual Expression* visitExpr(OperatorLessThan		* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorGreaterThan	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorLessThanEq	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorGreaterThanEq	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorEqual			* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorNotEqual		* node){ return nullptr; }

	virtual Expression* visitExpr(OperatorLeftShift		* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorRightShift	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorAnd			* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorOr			* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorMod			* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorBitAnd		* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorBitOr			* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorBitXor		* node){ return nullptr; }

	virtual Expression* visitExpr(OperatorAssign		* node){
		checkNullPtr(node);
		Expression* op1=node->getLeftOperand();
		Expression* op2=node->getRightOperand();
		checkOperandNull(op1);
		checkOperandNull(op2);		
		//op1=op1->evaluate(this);//计算左子结果(共用this访问)
		op2=op2->evaluate(this);//计算右子结果(共用this访问)
		checkOperandNull(op1);
		checkOperandNull(op2);	
		OperandNumber* operand1=dynamic_cast<OperandNumber*>(op1);
		OperandNumber* operand2=dynamic_cast<OperandNumber*>(op2);			
		NumberAssignVisiter assign;
		OperandNumber* result=evaluateAssign(operand1,operand2,assign);//运算
		return result;
	}
	virtual Expression* visitExpr(OperatorAssignAdd	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorAssignSub	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorAssignMul	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorAssignDiv	* node){ return nullptr; }

	virtual Expression* visitExpr(OperatorAssignMod		* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorAssignRShift	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorAssignLShift	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorAssignBAnd	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorAssignBXor	* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorAssignBOr		* node){ return nullptr; }

	virtual Expression* visitExpr(OperatorNegative		* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorNot			* node){ return nullptr; }
	virtual Expression* visitExpr(OperatorBitNot		* node){ return nullptr; }

	virtual Expression* visitExpr(OperandNumber			* node){ return node; }
	virtual Expression* visitExpr(OperandRefrence		* node){ return nullptr; }
};

}//end of namespace bluemei
